#include "StdAfx.h"
#include "ClientRecThread.h"


CClientRecThread::CClientRecThread(void)
{
	m_pClientRecFrame = NULL;
	m_pClientSndFrame = NULL;
	m_pMatrixDllCall = NULL;
	m_bCheckConnected = false;
	m_oInstrumentWholeTableMap.clear();
	m_oInstrumentUpdateArea.clear();
	m_uiRowNum = 3;
	m_uiColumnNum = 500;
}


CClientRecThread::~CClientRecThread(void)
{
	m_oInstrumentWholeTableMap.clear();
	m_oInstrumentUpdateArea.clear();
}

// 处理函数
void CClientRecThread::OnProc(void)
{
	int iFrameNum = 0;
	m_oCommFrameStructPtr ptrFrameRec = NULL;
	m_oCommFrameStructPtr ptrFrameSnd = NULL;
	EnterCriticalSection(&m_pClientRecFrame->m_oSecClientFrame);
	EnterCriticalSection(&m_pClientSndFrame->m_oSecClientFrame);
	EnterCriticalSection(&m_pMatrixDllCall->m_pEnv->m_pInstrumentCommInfo->m_oSecCommInfo);
	iFrameNum = m_pClientRecFrame->m_olsCommWorkFrame.size();
	for (int i=0; i<iFrameNum; i++)
	{
		ptrFrameRec = *m_pClientRecFrame->m_olsCommWorkFrame.begin();
		// 如果为设置帧
		if (ptrFrameRec->m_cCmdType == CmdTypeSet)
		{
			// 发送应答帧
			m_pClientSndFrame->MakeReturnFrame(ptrFrameRec);
			// 如果为新命令则清除未完成的旧命令待处理任务
			if (m_pClientRecFrame->m_uiCmdIndex < ptrFrameRec->m_uiCmdIndex)
			{
				m_pClientRecFrame->m_uiCmdIndex = ptrFrameRec->m_uiCmdIndex;
				m_pClientRecFrame->OnResetProcBuf();
			}
			// 将帧内容加入待处理任务中
			if (m_pClientRecFrame->m_uiCmdIndex == ptrFrameRec->m_uiCmdIndex)
			{
				SaveRecFrameToTask(ptrFrameRec);
			}
			// 如果为过期命令则不处理只返回应答
			else
			{
			}
		}
		// 如果为应答帧
		else if (ptrFrameRec->m_cCmdType == CmdTypeReturn)
		{
			// 在已发送帧索引中找到该帧并删除
			if (TRUE == m_pClientSndFrame->IfFramePtrExistInSndMap(ptrFrameRec->m_usCmd, 
				ptrFrameRec->m_uiServerTimeStep, ptrFrameRec->m_uiPacketIndex, 
				&m_pClientSndFrame->m_oSndFrameMap))
			{
				ptrFrameSnd = m_pClientSndFrame->GetFramePtrFromSndMap(ptrFrameRec->m_usCmd, 
					ptrFrameRec->m_uiServerTimeStep, ptrFrameRec->m_uiPacketIndex, 
					&m_pClientSndFrame->m_oSndFrameMap);
				m_pClientSndFrame->DeleteFramePtrFromSndMap(ptrFrameRec->m_usCmd, 
					ptrFrameRec->m_uiServerTimeStep, ptrFrameRec->m_uiPacketIndex, 
					&m_pClientSndFrame->m_oSndFrameMap);
				m_pClientSndFrame->AddFreeFrameStruct(ptrFrameSnd);
			}
		}
		m_pClientRecFrame->m_olsCommWorkFrame.pop_front();
		m_pClientRecFrame->AddFreeFrameStruct(ptrFrameRec);
	}
	LeaveCriticalSection(&m_pMatrixDllCall->m_pEnv->m_pInstrumentCommInfo->m_oSecCommInfo);
	LeaveCriticalSection(&m_pClientSndFrame->m_oSecClientFrame);
	LeaveCriticalSection(&m_pClientRecFrame->m_oSecClientFrame);
}
// 将帧内容加入待处理任务中
void CClientRecThread::SaveRecFrameToTask(m_oCommFrameStructPtr ptrFrame)
{
	unsigned int uiSaveBegin = 0;
	uiSaveBegin = (ptrFrame->m_uiFrameIndex - 1) * FrameInfoSizeLimit;
	memcpy(&m_pClientRecFrame->m_cProcBuf[uiSaveBegin], ptrFrame->m_pcFrameInfo, ptrFrame->m_usFrameInfoSize);
	// 命令帧接收完全
	if (ptrFrame->m_uiFrameIndex == ptrFrame->m_uiFrameNum)
	{
		// 进行命令处理
		OnProcRecCmd(ptrFrame->m_usCmd, m_pClientRecFrame->m_cProcBuf, uiSaveBegin + ptrFrame->m_usFrameInfoSize);
	}
}

// 处理接收命令函数
void CClientRecThread::OnProcRecCmd(unsigned short usCmd, char* pChar, unsigned int uiSize)
{
	// 客户端登陆验证（帧内容为验证码）
	if (usCmd == CmdClientConnect)
	{
		// 与连接校验码相匹配
		if (0 == strcmp(pChar, CommCheck))
		{
			m_bCheckConnected = true;
		}
	}
	else
	{
		if (m_bCheckConnected == false)
		{
			return;
		}
		switch (usCmd)
		{
		// 客户端心跳命令（帧内容为空）
		case CmdSetHeartBeat:
			OnProcInstrumentTableUpdate();
			break;
		case CmdQueryWholeTable:
			m_oInstrumentWholeTableMap.clear();
			m_oInstrumentUpdateArea.clear();
			OnProcInstrumentTableUpdate();
			break;
		// 上电（命令字后帧内容为空，返回值为执行FieldOn剩余时间，为0表示无需等待）
		case CmdSetFieldOn:
			OnProcSetFieldOn();
			break;
		// 断电（命令字后帧内容为空）
		case CmdSetFieldOff:
			OnProcSetFieldOff();
			break;
		// 查询所选仪器全部信息（帧内容为仪器SN，每4个字节一个仪器）
		case CmdQueryInstrumentInfo:

			break;
		// 查询全部仪器的全部信息（应答帧内容为仪器结构体）
		case CmdQueryInstrumentInfoAll:

			break;
		// 查询 SurveyXML 文件信息（帧内容为空）
		case CmdQuerySurveyXMLInfo:
			OnProcQuerySurveyXMLInfo(usCmd);
			break;
		// 设置 SurveyXML 文件信息（帧内容为信息结构体）
		case CmdSetSurveyXMLInfo:
			m_pMatrixDllCall->Dll_SetSurverySetupData(pChar, uiSize);
			break;
		// 查询 PointCode XML文件信息（帧内容为空）
		case CmdQueryPointCodeXMLInfo:
			OnProcQueryPointCodeXMLInfo(usCmd);
			break;
		// 设置 PointCode XML文件信息（帧内容为信息结构体）
		case CmdSetPointCodeXMLInfo:
			m_pMatrixDllCall->Dll_SetPointCodeSetupData(pChar, uiSize);
			break;
		// 查询 Sensor XML文件信息（帧内容为空）
		case CmdQuerySensorXMLInfo:
			OnProcQuerySensorXMLInfo(usCmd);
			break;
		// 设置 Sensor XML文件信息（帧内容为信息结构体）
		case CmdSetSensorXMLInfo:
			m_pMatrixDllCall->Dll_SetSensorSetupData(pChar, uiSize);
			break;
		// 查询 Marker XML文件信息（帧内容为空）
		case CmdQueryMarkerXMLInfo:
			OnProcQueryMarkerXMLInfo(usCmd);
			break;
		// 设置 Marker XML文件信息（帧内容为信息结构体）
		case CmdSetMarkerXMLInfo:
			m_pMatrixDllCall->Dll_SetMarkerSetupData(pChar, uiSize);
			break;
		// 查询 Aux XML文件信息（帧内容为空）
		case CmdQueryAuxXMLInfo:
			OnProcQueryAuxXMLInfo(usCmd);
			break;
		// 设置 Aux XML文件信息（帧内容为信息结构体）
		case CmdSetAuxXMLInfo:
			m_pMatrixDllCall->Dll_SetAuxSetupData(pChar, uiSize);
			break;
		// 查询 Detour XML文件信息（帧内容为空）
		case CmdQueryDetourXMLInfo:
			OnProcQueryDetourXMLInfo(usCmd);
			break;
		// 设置 Detour XML文件信息（帧内容为信息结构体）
		case CmdSetDetourXMLInfo:
			m_pMatrixDllCall->Dll_SetDetourSetupData(pChar, uiSize);
			break;
		// 查询 Mute XML文件信息（帧内容为空）
		case CmdQueryMuteXMLInfo:
			OnProcQueryMuteXMLInfo(usCmd);
			break;
		// 设置 Mute XML文件信息（帧内容为信息结构体）
		case CmdSetMuteXMLInfo:
			m_pMatrixDllCall->Dll_SetMuteSetupData(pChar, uiSize);
			break;
		// 查询 BlastMachine XML文件信息（帧内容为空）
		case CmdQueryBlastMachineXMLInfo:
			OnProcQueryBlastMachineXMLInfo(usCmd);
			break;
		// 设置 BlastMachine XML文件信息（帧内容为信息结构体）
		case CmdSetBlastMachineXMLInfo:
			m_pMatrixDllCall->Dll_SetBlastMachineSetupData(pChar, uiSize);
			break;
		// 查询 Absolute XML文件信息（帧内容为空）
		case CmdQueryAbsoluteXMLInfo:
			OnProcQueryAbsoluteXMLInfo(usCmd);
			break;
		// 设置 Absolute XML文件信息（帧内容为信息结构体）
		case CmdSetAbsoluteXMLInfo:
			m_pMatrixDllCall->Dll_SetAbsoluteSetupData(pChar, uiSize);
			break; 
		// 查询 Generic XML文件信息（帧内容为空）
		case CmdQueryGenericXMLInfo:
			OnProcQueryGenericXMLInfo(usCmd);
			break;
		// 设置 Generic XML文件信息（帧内容为信息结构体）
		case CmdSetGenericXMLInfo:
			m_pMatrixDllCall->Dll_SetGenericSetupData(pChar, uiSize);
			break;
		// 查询 Look XML文件信息（帧内容为空）
		case CmdQueryLookXMLInfo:
			OnProcQueryLookXMLInfo(usCmd);
			break;
		// 设置 Look XML文件信息（帧内容为信息结构体）
		case CmdSetLookXMLInfo:
			m_pMatrixDllCall->Dll_SetLookSetupData(pChar, uiSize);
			break;
		// 查询 InstrumentTestBase XML文件信息（帧内容为空）
		case CmdQueryInstrumentTestBaseXMLInfo:
			OnProcQueryInstrumentTestBaseXMLInfo(usCmd);
			break;
		// 设置 InstrumentTestBase XML文件信息（帧内容为信息结构体）
		case CmdSetInstrumentTestBaseXMLInfo:
			m_pMatrixDllCall->Dll_SetInstrument_SensorTestBaseSetupData(pChar, uiSize, true);
			break;
		// 查询 SensorTestBase XML文件信息（帧内容为空）
		case CmdQuerySensorTestBaseXMLInfo:
			OnProcQuerySensorTestBaseXMLInfo(usCmd);
			break;
			// 设置 SensorTestBase XML文件信息（帧内容为信息结构体）
		case CmdSetSensorTestBaseXMLInfo:
			m_pMatrixDllCall->Dll_SetInstrument_SensorTestBaseSetupData(pChar, uiSize, false);
			break;
		// 查询 InstrumentTestLimit XML文件信息（帧内容为空）
		case CmdQueryInstrumentTestLimitXMLInfo:
			OnProcQueryInstrumentTestLimitXMLInfo(usCmd);
			break;
		// 设置 InstrumentTestLimit XML文件信息（帧内容为信息结构体）
		case CmdSetInstrumentTestLimitXMLInfo:
			m_pMatrixDllCall->Dll_SetInstrument_SensorTestLimitSetupData(pChar, uiSize, true);
			break;
		// 查询 SensorTestLimit XML文件信息（帧内容为空）
		case CmdQuerySensorTestLimitXMLInfo:
			OnProcQuerySensorTestLimitXMLInfo(usCmd);
			break;
		// 设置 SensorTestLimit XML文件信息（帧内容为信息结构体）
		case CmdSetSensorTestLimitXMLInfo:
			m_pMatrixDllCall->Dll_SetInstrument_SensorTestLimitSetupData(pChar, uiSize, false);
			break;
		// 查询 InstrumentTest XML文件信息（帧内容为空）
		case CmdQueryInstrumentTestXMLInfo:
			OnProcQueryInstrumentTestXMLInfo(usCmd);
			break;
		// 设置 InstrumentTest XML文件信息（帧内容为信息结构体）
		case CmdSetInstrumentTestXMLInfo:
			m_pMatrixDllCall->Dll_SetInstrumentTestSetupData(pChar, uiSize);
			break;
		// 查询 SensorTest XML文件信息（帧内容为空）
		case CmdQuerySensorTestXMLInfo:
			OnProcQuerySensorTestXMLInfo(usCmd);
			break;
		// SensorTest XML文件信息（帧内容为信息结构体）
		case CmdSetSensorTestXMLInfo:
			m_pMatrixDllCall->Dll_SetSensorSetupData(pChar, uiSize);
			break;
		// 查询 MultipleTest XML文件信息（帧内容为空）
		case CmdQueryMultipleTestXMLInfo:
			OnProcQueryMultipleTestXMLInfo(usCmd);
			break;
		// 设置 MultipleTest XML文件信息（帧内容为信息结构体）
		case CmdSetMultipleTestXMLInfo:
			m_pMatrixDllCall->Dll_SetMultipleTestSetupData(pChar, uiSize);
			break;
		// 查询 SeisMonitorTest XML文件信息（帧内容为空）
		case CmdQuerySeisMonitorTestXMLInfo:
			OnProcQuerySeisMonitorTestXMLInfo(usCmd);
			break;
		// 设置 SeisMonitorTest XML文件信息（帧内容为信息结构体）
		case CmdSetSeisMonitorTestXMLInfo:
			m_pMatrixDllCall->Dll_SetSeisMonitorSetupData(pChar, uiSize);
			break;
		// 查询 LAULeakage XML文件信息（帧内容为空）
		case CmdQueryLAULeakageXMLInfo:
			OnProcQueryLAULeakageXMLInfo(usCmd);
			break;
		// 设置 LAULeakage XML文件信息（帧内容为信息结构体）
		case CmdSetLAULeakageXMLInfo:
			m_pMatrixDllCall->Dll_SetLAULeakageSetupData(pChar, uiSize);
			break;
		// 查询 FormLine XML文件信息（帧内容为空）
		case CmdQueryFormLineXMLInfo:
			OnProcQueryFormLineXMLInfo(usCmd);
			break;
		// 设置 FormLine XML文件信息（帧内容为信息结构体）
		case CmdSetFormLineXMLInfo:
			m_pMatrixDllCall->Dll_SetFormLineSetupData(pChar, uiSize);
			break;
		default:
			break;
		}
	}
}
// 由线号和点号得到区域位置
void CClientRecThread::GetAreaFromPoint(int iLineIndex, int iPointIndex, m_oAreaStruct* pAreaStruct)
{
	pAreaStruct->m_uiLineNb = m_uiRowNum + iLineIndex;
	pAreaStruct->m_uiAreaNb = m_uiColumnNum + iPointIndex;
	if ((pAreaStruct->m_uiAreaNb % InstrumentTableWindowSize) == 0)
	{
		pAreaStruct->m_uiAreaNb /= InstrumentTableWindowSize;
	}
	else
	{
		pAreaStruct->m_uiAreaNb /= InstrumentTableWindowSize;
		pAreaStruct->m_uiAreaNb += 1;
	}
}
// 由区域号得到线号及点号范围
void CClientRecThread::GetPointRangeFromArea(int* iLineIndex, int* iPointMinIndex, int* iPointMaxIndex, m_oAreaStruct* pAreaStruct)
{
	*iLineIndex = (int)pAreaStruct->m_uiLineNb - m_uiRowNum;
	*iPointMinIndex = ((int)pAreaStruct->m_uiAreaNb - 1) * InstrumentTableWindowSize + 1 - m_uiColumnNum;
	*iPointMaxIndex = ((int)pAreaStruct->m_uiAreaNb) * InstrumentTableWindowSize - m_uiColumnNum;
}
// 判断仪器更新区域是否已加入索引表
BOOL CClientRecThread::IfAreaExistInMap(m_oAreaStruct* pAreaStruct,
	map<m_oAreaStruct, m_oAreaStruct>* pMap)
{
	if ((pMap == NULL) || (pAreaStruct == NULL))
	{
		return FALSE;
	}
	BOOL bResult = FALSE;
	map<m_oAreaStruct, m_oAreaStruct>::iterator iter;
	iter = pMap->find(*pAreaStruct);
	if (iter != pMap->end())
	{
		bResult = TRUE;
	}
	else
	{
		bResult = FALSE;
	}
	return bResult;
}
// 增加对象到索引表
void CClientRecThread::AddAreaToMap(int iLineIndex, int iPointIndex, 
	map<m_oAreaStruct, m_oAreaStruct>* pMap)
{
	if (pMap == NULL)
	{
		return;
	}
	m_oAreaStruct oAreaStruct;
	GetAreaFromPoint(iLineIndex, iPointIndex, &oAreaStruct);
	if (FALSE == IfAreaExistInMap(&oAreaStruct, pMap))
	{
		pMap->insert(map<m_oAreaStruct, m_oAreaStruct>::value_type (oAreaStruct, oAreaStruct));
	}
}
// 处理仪器设备表更新
void CClientRecThread::OnProcInstrumentTableUpdate(void)
{
	map<m_oInstrumentLocationStruct, m_oInstrumentStruct*>::iterator iterLocation;
	map<m_oAreaStruct, m_oAreaStruct>::iterator iterArea;
	int iLineIndex = 0;
	int iPointMinIndex = 0;
	int iPointMaxIndex = 0;
	int iPos = 0;
	m_oInstrumentStruct* pInstrument = NULL;
 	EnterCriticalSection(&m_pMatrixDllCall->m_pEnv->m_pInstrumentList->m_oSecInstrumentList);
	// 将SN索引表与客户端的仪器位置索引表相对照
	for (iterLocation = m_pMatrixDllCall->m_pEnv->m_pInstrumentList->m_oInstrumentLocationMap.begin();
		iterLocation != m_pMatrixDllCall->m_pEnv->m_pInstrumentList->m_oInstrumentLocationMap.end(); iterLocation++)
	{
		// 客户端仪器索引表中找不到该设备
		if (FALSE == m_pMatrixDllCall->Dll_IfLocationExistInMap(iterLocation->first.m_iLineIndex, 
			iterLocation->first.m_iPointIndex, &m_oInstrumentWholeTableMap))
		{
			m_pMatrixDllCall->Dll_AddLocationToMap(iterLocation->first.m_iLineIndex, 
				iterLocation->first.m_iPointIndex, iterLocation->second, &m_oInstrumentWholeTableMap);
			// 增加对象到索引表
			AddAreaToMap(iterLocation->first.m_iLineIndex, 
				iterLocation->first.m_iPointIndex, &m_oInstrumentUpdateArea);
		}
		else
		{
			pInstrument = m_pMatrixDllCall->Dll_GetInstrumentFromLocationMap(iterLocation->first.m_iLineIndex,
				iterLocation->first.m_iPointIndex, &m_oInstrumentWholeTableMap);
			if (pInstrument->m_uiSN != iterLocation->second->m_uiSN)
			{
				pInstrument = iterLocation->second;
				// 增加对象到索引表
				AddAreaToMap(iterLocation->first.m_iLineIndex, iterLocation->first.m_iPointIndex, &m_oInstrumentUpdateArea);
			}
		}
	}
	// 将客户端的仪器位置索引表与SN索引表相对照
	for (iterLocation = m_oInstrumentWholeTableMap.begin(); iterLocation != m_oInstrumentWholeTableMap.end();)
	{
		// 仪器IP地址索引表找不到该设备
		if (FALSE == m_pMatrixDllCall->Dll_IfLocationExistInMap(iterLocation->first.m_iLineIndex, 
			iterLocation->first.m_iPointIndex, &m_pMatrixDllCall->m_pEnv->m_pInstrumentList->m_oInstrumentLocationMap))
		{
			// 增加对象到索引表
			AddAreaToMap(iterLocation->first.m_iLineIndex, iterLocation->first.m_iPointIndex, &m_oInstrumentUpdateArea);
			m_oInstrumentWholeTableMap.erase(iterLocation++);
		}
		else
		{
			pInstrument = m_pMatrixDllCall->Dll_GetInstrumentFromLocationMap(iterLocation->first.m_iLineIndex, 
				iterLocation->first.m_iPointIndex, &m_pMatrixDllCall->m_pEnv->m_pInstrumentList->m_oInstrumentLocationMap);
			// SN不同则删除该仪器
			if (pInstrument->m_uiSN != iterLocation->second->m_uiSN)
			{
				iterLocation->second = pInstrument;
			}
			iterLocation++;
		}
	}
	LeaveCriticalSection(&m_pMatrixDllCall->m_pEnv->m_pInstrumentList->m_oSecInstrumentList);
	// 对照后客户端仪器索引表与服务端仪器SN索引表一致，将变化区域发送到客户端
	for (iterArea = m_oInstrumentUpdateArea.begin(); iterArea != m_oInstrumentUpdateArea.end(); iterArea++)
	{
		// 由区域号得到线号及点号范围
		GetPointRangeFromArea(&iLineIndex, &iPointMinIndex, &iPointMaxIndex, &iterArea->second);
		memcpy(&m_pClientSndFrame->m_cProcBuf[iPos], &iterArea->second.m_uiLineNb, 4);
		iPos += 4;
		memcpy(&m_pClientSndFrame->m_cProcBuf[iPos], &iterArea->second.m_uiAreaNb, 4);
		iPos += 4;
		for (int i = iPointMinIndex; i <= iPointMaxIndex; i++)
		{
			pInstrument = m_pMatrixDllCall->Dll_GetInstrumentFromLocationMap(iLineIndex, i, &m_oInstrumentWholeTableMap);
			memcpy(&m_pClientSndFrame->m_cProcBuf[iPos], &pInstrument->m_uiSN, 4);
			iPos += 4;
		}
	}
	if (iPos > 0)
	{
		m_pClientSndFrame->MakeSetFrame(CmdQueryUpdateTable, m_pClientSndFrame->m_cProcBuf, iPos);
	}
}


// 处理上电
void CClientRecThread::OnProcSetFieldOn(void)
{
	unsigned int uiFieldOnNeedTime = 0;;
	uiFieldOnNeedTime = m_pMatrixDllCall->Dll_Work();
	memcpy(m_pClientSndFrame->m_cProcBuf, &uiFieldOnNeedTime, 4);
	m_pClientSndFrame->MakeSetFrame(CmdFieldOnWaitTime, m_pClientSndFrame->m_cProcBuf, 4);
}


// 处理断电
void CClientRecThread::OnProcSetFieldOff(void)
{
	m_pMatrixDllCall->Dll_Stop();
}


// 查询 SurveyXML 文件信息
void CClientRecThread::OnProcQuerySurveyXMLInfo(unsigned short usCmd)
{
	list<m_oSurveryStruct>::iterator iter;
	int iPos = 0;
	m_pMatrixDllCall->Dll_LoadSurverySetupData();
	for (iter = m_pMatrixDllCall->m_pEnv->m_pInstrumentCommInfo->m_oLineSetupData.m_olsSurveryStruct.begin();
		iter != m_pMatrixDllCall->m_pEnv->m_pInstrumentCommInfo->m_oLineSetupData.m_olsSurveryStruct.end(); iter++)
	{
		memcpy(&m_pClientSndFrame->m_cProcBuf[iPos], &iter->m_uiLine, 4);
		iPos += 4;
		memcpy(&m_pClientSndFrame->m_cProcBuf[iPos], &iter->m_usReceiverSectionSize, 2);
		iPos += 2;
		memcpy(&m_pClientSndFrame->m_cProcBuf[iPos], &iter->m_pcReceiverSection, iter->m_usReceiverSectionSize);
		iPos += iter->m_usReceiverSectionSize;
	}
	m_pClientSndFrame->MakeSetFrame(usCmd, m_pClientSndFrame->m_cProcBuf, iPos);
}


// 查询 PointCode XML文件信息
void CClientRecThread::OnProcQueryPointCodeXMLInfo(unsigned short usCmd)
{
	list<m_oPointCodeStruct>::iterator iter;
	int iPos = 0;
	m_pMatrixDllCall->Dll_LoadPointCodeSetupData();
	for (iter = m_pMatrixDllCall->m_pEnv->m_pInstrumentCommInfo->m_oLineSetupData.m_olsPointCodeStruct.begin();
		iter != m_pMatrixDllCall->m_pEnv->m_pInstrumentCommInfo->m_oLineSetupData.m_olsPointCodeStruct.end(); iter++)
	{
		memcpy(&m_pClientSndFrame->m_cProcBuf[iPos], &iter->m_uiNb, 4);
		iPos += 4;
		memcpy(&m_pClientSndFrame->m_cProcBuf[iPos], &iter->m_usLabelSize, 2);
		iPos += 2;
		memcpy(&m_pClientSndFrame->m_cProcBuf[iPos], &iter->m_pcLabel, iter->m_usLabelSize);
		iPos += iter->m_usLabelSize;
		memcpy(&m_pClientSndFrame->m_cProcBuf[iPos], &iter->m_usSensorTypeSize, 2);
		iPos += 2;
		memcpy(&m_pClientSndFrame->m_cProcBuf[iPos], &iter->m_pcSensorType, iter->m_usSensorTypeSize);
		iPos += iter->m_usSensorTypeSize;
	}
	m_pClientSndFrame->MakeSetFrame(usCmd, m_pClientSndFrame->m_cProcBuf, iPos);
}


// 查询 Sensor XML文件信息
void CClientRecThread::OnProcQuerySensorXMLInfo(unsigned short usCmd)
{
	list<m_oSensorStruct>::iterator iter;
	int iPos = 0;
	m_pMatrixDllCall->Dll_LoadSensorSetupData();
	for (iter = m_pMatrixDllCall->m_pEnv->m_pInstrumentCommInfo->m_oLineSetupData.m_olsSensorStruct.begin();
		iter != m_pMatrixDllCall->m_pEnv->m_pInstrumentCommInfo->m_oLineSetupData.m_olsSensorStruct.end(); iter++)
	{
		memcpy(&m_pClientSndFrame->m_cProcBuf[iPos], &iter->m_uiNb, 4);
		iPos += 4;
		memcpy(&m_pClientSndFrame->m_cProcBuf[iPos], &iter->m_usLabelSize, 2);
		iPos += 2;
		memcpy(&m_pClientSndFrame->m_cProcBuf[iPos], &iter->m_pcLabel, iter->m_usLabelSize);
		iPos += iter->m_usLabelSize;
		memcpy(&m_pClientSndFrame->m_cProcBuf[iPos], &iter->m_fContinuityMin, 4);
		iPos += 4;
		memcpy(&m_pClientSndFrame->m_cProcBuf[iPos], &iter->m_fContinuityMax, 4);
		iPos += 4;
		memcpy(&m_pClientSndFrame->m_cProcBuf[iPos], &iter->m_fTilt, 4);
		iPos += 4;
		memcpy(&m_pClientSndFrame->m_cProcBuf[iPos], &iter->m_fNoise, 4);
		iPos += 4;
		memcpy(&m_pClientSndFrame->m_cProcBuf[iPos], &iter->m_fLeakage, 4);
		iPos += 4;
		memcpy(&m_pClientSndFrame->m_cProcBuf[iPos], &iter->m_uiSEGDCode, 4);
		iPos += 4;
	}
	m_pClientSndFrame->MakeSetFrame(usCmd, m_pClientSndFrame->m_cProcBuf, iPos);
}


// 查询 Marker XML文件信息
void CClientRecThread::OnProcQueryMarkerXMLInfo(unsigned short usCmd)
{
	list<m_oMarkerStruct>::iterator iter;
	int iPos = 0;
	m_pMatrixDllCall->Dll_LoadMarkerSetupData();
	for (iter = m_pMatrixDllCall->m_pEnv->m_pInstrumentCommInfo->m_oLineSetupData.m_olsMarkerStruct.begin();
		iter != m_pMatrixDllCall->m_pEnv->m_pInstrumentCommInfo->m_oLineSetupData.m_olsMarkerStruct.end(); iter++)
	{
		memcpy(&m_pClientSndFrame->m_cProcBuf[iPos], &iter->m_uiBoxType, 4);
		iPos += 4;
		memcpy(&m_pClientSndFrame->m_cProcBuf[iPos], &iter->m_uiSN, 4);
		iPos += 4;
		memcpy(&m_pClientSndFrame->m_cProcBuf[iPos], &iter->m_uiLineName, 4);
		iPos += 4;
		memcpy(&m_pClientSndFrame->m_cProcBuf[iPos], &iter->m_uiPointNb, 4);
		iPos += 4;
		memcpy(&m_pClientSndFrame->m_cProcBuf[iPos], &iter->m_uiChannelNb, 4);
		iPos += 4;
		memcpy(&m_pClientSndFrame->m_cProcBuf[iPos], &iter->m_uiMarkerIncr, 4);
		iPos += 4;
		memcpy(&m_pClientSndFrame->m_cProcBuf[iPos], &iter->m_uiReversed, 4);
		iPos += 4;
	}
	m_pClientSndFrame->MakeSetFrame(usCmd, m_pClientSndFrame->m_cProcBuf, iPos);
}


// 查询 Aux XML文件信息
void CClientRecThread::OnProcQueryAuxXMLInfo(unsigned short usCmd)
{
	list<m_oAuxStruct>::iterator iter;
	int iPos = 0;
	m_pMatrixDllCall->Dll_LoadAuxSetupData();
	for (iter = m_pMatrixDllCall->m_pEnv->m_pInstrumentCommInfo->m_oLineSetupData.m_olsAuxStruct.begin();
		iter != m_pMatrixDllCall->m_pEnv->m_pInstrumentCommInfo->m_oLineSetupData.m_olsAuxStruct.end(); iter++)
	{
		memcpy(&m_pClientSndFrame->m_cProcBuf[iPos], &iter->m_uiNb, 4);
		iPos += 4;
		memcpy(&m_pClientSndFrame->m_cProcBuf[iPos], &iter->m_usLabelSize, 2);
		iPos += 2;
		memcpy(&m_pClientSndFrame->m_cProcBuf[iPos], &iter->m_pcLabel, iter->m_usLabelSize);
		iPos += iter->m_usLabelSize;
		memcpy(&m_pClientSndFrame->m_cProcBuf[iPos], &iter->m_uiBoxType, 4);
		iPos += 4;
		memcpy(&m_pClientSndFrame->m_cProcBuf[iPos], &iter->m_uiSN, 4);
		iPos += 4;
		memcpy(&m_pClientSndFrame->m_cProcBuf[iPos], &iter->m_uiChannelNb, 4);
		iPos += 4;
		memcpy(&m_pClientSndFrame->m_cProcBuf[iPos], &iter->m_uiGain, 4);
		iPos += 4;
		memcpy(&m_pClientSndFrame->m_cProcBuf[iPos], &iter->m_uiDpgNb, 4);
		iPos += 4;
		memcpy(&m_pClientSndFrame->m_cProcBuf[iPos], &iter->m_usCommentsSize, 2);
		iPos += 2;
		memcpy(&m_pClientSndFrame->m_cProcBuf[iPos], &iter->m_pcComments, iter->m_usCommentsSize);
		iPos += iter->m_usCommentsSize;
	}
	m_pClientSndFrame->MakeSetFrame(usCmd, m_pClientSndFrame->m_cProcBuf, iPos);
}


// 查询 Detour XML文件信息
void CClientRecThread::OnProcQueryDetourXMLInfo(unsigned short usCmd)
{
	list<m_oDetourStruct>::iterator iter;
	int iPos = 0;
	m_pMatrixDllCall->Dll_LoadDetourSetupData();
	for (iter = m_pMatrixDllCall->m_pEnv->m_pInstrumentCommInfo->m_oLineSetupData.m_olsDetourStruct.begin();
		iter != m_pMatrixDllCall->m_pEnv->m_pInstrumentCommInfo->m_oLineSetupData.m_olsDetourStruct.end(); iter++)
	{
		memcpy(&m_pClientSndFrame->m_cProcBuf[iPos], &iter->m_uiLowBoxType, 4);
		iPos += 4;
		memcpy(&m_pClientSndFrame->m_cProcBuf[iPos], &iter->m_uiLowSN, 4);
		iPos += 4;
		memcpy(&m_pClientSndFrame->m_cProcBuf[iPos], &iter->m_uiLowChanNb, 4);
		iPos += 4;
		memcpy(&m_pClientSndFrame->m_cProcBuf[iPos], &iter->m_uiHighBoxType, 4);
		iPos += 4;
		memcpy(&m_pClientSndFrame->m_cProcBuf[iPos], &iter->m_uiHighSN, 4);
		iPos += 4;
		memcpy(&m_pClientSndFrame->m_cProcBuf[iPos], &iter->m_uiHighChanNb, 4);
		iPos += 4;
		memcpy(&m_pClientSndFrame->m_cProcBuf[iPos], &iter->m_uiStopMarking, 4);
		iPos += 4;
	}
	m_pClientSndFrame->MakeSetFrame(usCmd, m_pClientSndFrame->m_cProcBuf, iPos);
}


// 查询 Mute XML文件信息
void CClientRecThread::OnProcQueryMuteXMLInfo(unsigned short usCmd)
{
	list<m_oMuteStruct>::iterator iter;
	int iPos = 0;
	m_pMatrixDllCall->Dll_LoadMuteSetupData();
	for (iter = m_pMatrixDllCall->m_pEnv->m_pInstrumentCommInfo->m_oLineSetupData.m_olsMuteStruct.begin();
		iter != m_pMatrixDllCall->m_pEnv->m_pInstrumentCommInfo->m_oLineSetupData.m_olsMuteStruct.end(); iter++)
	{
		memcpy(&m_pClientSndFrame->m_cProcBuf[iPos], &iter->m_uiLineName, 4);
		iPos += 4;
		memcpy(&m_pClientSndFrame->m_cProcBuf[iPos], &iter->m_uiPointNb, 4);
		iPos += 4;
	}
	m_pClientSndFrame->MakeSetFrame(usCmd, m_pClientSndFrame->m_cProcBuf, iPos);
}


// 查询 BlastMachine XML文件信息
void CClientRecThread::OnProcQueryBlastMachineXMLInfo(unsigned short usCmd)
{
	list<m_oBlastMachineStruct>::iterator iter;
	int iPos = 0;
	m_pMatrixDllCall->Dll_LoadBlastMachineSetupData();
	for (iter = m_pMatrixDllCall->m_pEnv->m_pInstrumentCommInfo->m_oLineSetupData.m_olsBlastMachineStruct.begin();
		iter != m_pMatrixDllCall->m_pEnv->m_pInstrumentCommInfo->m_oLineSetupData.m_olsBlastMachineStruct.end(); iter++)
	{
		memcpy(&m_pClientSndFrame->m_cProcBuf[iPos], &iter->m_uiNb, 4);
		iPos += 4;
		memcpy(&m_pClientSndFrame->m_cProcBuf[iPos], &iter->m_usLabelSize, 2);
		iPos += 2;
		memcpy(&m_pClientSndFrame->m_cProcBuf[iPos], &iter->m_pcLabel, iter->m_usLabelSize);
		iPos += iter->m_usLabelSize;
		memcpy(&m_pClientSndFrame->m_cProcBuf[iPos], &iter->m_uiBoxType, 4);
		iPos += 4;
		memcpy(&m_pClientSndFrame->m_cProcBuf[iPos], &iter->m_uiSN, 4);
		iPos += 4;
		memcpy(&m_pClientSndFrame->m_cProcBuf[iPos], &iter->m_uiChannelNb, 4);
		iPos += 4;
		memcpy(&m_pClientSndFrame->m_cProcBuf[iPos], &iter->m_uiGain, 4);
		iPos += 4;
		memcpy(&m_pClientSndFrame->m_cProcBuf[iPos], &iter->m_uiDpgNb, 4);
		iPos += 4;
		memcpy(&m_pClientSndFrame->m_cProcBuf[iPos], &iter->m_usCommentsSize, 2);
		iPos += 2;
		memcpy(&m_pClientSndFrame->m_cProcBuf[iPos], &iter->m_pcComments, iter->m_usCommentsSize);
		iPos += iter->m_usCommentsSize;
	}
	m_pClientSndFrame->MakeSetFrame(usCmd, m_pClientSndFrame->m_cProcBuf, iPos);
}


// 查询 Absolute XML文件信息
// 炮点+排列个数+排列
void CClientRecThread::OnProcQueryAbsoluteXMLInfo(unsigned short usCmd)
{
	map<unsigned int, list<m_oAbsoluteStruct>>::iterator iterMap;
	list<m_oAbsoluteStruct>::iterator iter;
	int iPos = 0;
	unsigned int uiSize = 0;
	m_pMatrixDllCall->Dll_LoadAbsoluteSetupData();
	for (iterMap = m_pMatrixDllCall->m_pEnv->m_pInstrumentCommInfo->m_oLineSetupData.m_oAbsoluteStructMap.begin();
		iterMap != m_pMatrixDllCall->m_pEnv->m_pInstrumentCommInfo->m_oLineSetupData.m_oAbsoluteStructMap.end(); iterMap++)
	{
		memcpy(&m_pClientSndFrame->m_cProcBuf[iPos], &iterMap->first, 4);
		iPos += 4;
		uiSize = iterMap->second.size();
		memcpy(&m_pClientSndFrame->m_cProcBuf[iPos], &uiSize, 4);
		iPos += 4;
		for (iter = iterMap->second.begin(); iter != iterMap->second.end(); iter++)
		{
			memcpy(&m_pClientSndFrame->m_cProcBuf[iPos], &iter->m_uiNb, 4);
			iPos += 4;
			memcpy(&m_pClientSndFrame->m_cProcBuf[iPos], &iter->m_usLabelSize, 2);
			iPos += 2;
			memcpy(&m_pClientSndFrame->m_cProcBuf[iPos], &iter->m_pcLabel, iter->m_usLabelSize);
			iPos += iter->m_usLabelSize;
			memcpy(&m_pClientSndFrame->m_cProcBuf[iPos], &iter->m_usAbsoluteSpreadSize, 2);
			iPos += 2;
			memcpy(&m_pClientSndFrame->m_cProcBuf[iPos], &iter->m_pcAbsoluteSpread, iter->m_usAbsoluteSpreadSize);
			iPos += iter->m_usAbsoluteSpreadSize;
		}
	}
	m_pClientSndFrame->MakeSetFrame(usCmd, m_pClientSndFrame->m_cProcBuf, iPos);
}


// 查询 Generic XML文件信息
void CClientRecThread::OnProcQueryGenericXMLInfo(unsigned short usCmd)
{
	list<m_oGenericStruct>::iterator iter;
	int iPos = 0;
	m_pMatrixDllCall->Dll_LoadGenericSetupData();
	for (iter = m_pMatrixDllCall->m_pEnv->m_pInstrumentCommInfo->m_oLineSetupData.m_olsGenericStruct.begin();
		iter != m_pMatrixDllCall->m_pEnv->m_pInstrumentCommInfo->m_oLineSetupData.m_olsGenericStruct.end(); iter++)
	{
		memcpy(&m_pClientSndFrame->m_cProcBuf[iPos], &iter->m_uiNb, 4);
		iPos += 4;
		memcpy(&m_pClientSndFrame->m_cProcBuf[iPos], &iter->m_usLabelSize, 2);
		iPos += 2;
		memcpy(&m_pClientSndFrame->m_cProcBuf[iPos], &iter->m_pcLabel, iter->m_usLabelSize);
		iPos += iter->m_usLabelSize;
		memcpy(&m_pClientSndFrame->m_cProcBuf[iPos], &iter->m_usLineSize, 2);
		iPos += 2;
		memcpy(&m_pClientSndFrame->m_cProcBuf[iPos], &iter->m_pcLine, iter->m_usLineSize);
		iPos += iter->m_usLineSize;
		memcpy(&m_pClientSndFrame->m_cProcBuf[iPos], &iter->m_usSpreadSize, 2);
		iPos += 2;
		memcpy(&m_pClientSndFrame->m_cProcBuf[iPos], &iter->m_pcSpread, iter->m_usSpreadSize);
		iPos += iter->m_usSpreadSize;
	}
	m_pClientSndFrame->MakeSetFrame(usCmd, m_pClientSndFrame->m_cProcBuf, iPos);
}


// 查询 Look XML文件信息
void CClientRecThread::OnProcQueryLookXMLInfo(unsigned short usCmd)
{
	m_pMatrixDllCall->Dll_LoadLookSetupData();
	int iPos = 0;
	memcpy(&m_pClientSndFrame->m_cProcBuf[iPos], 
		&m_pMatrixDllCall->m_pEnv->m_pInstrumentCommInfo->m_oLineSetupData.m_oLook.m_uiAutoLook, 4);
	iPos += 4;
	memcpy(&m_pClientSndFrame->m_cProcBuf[iPos], 
		&m_pMatrixDllCall->m_pEnv->m_pInstrumentCommInfo->m_oLineSetupData.m_oLook.m_uiResistance, 4);
	iPos += 4;
	memcpy(&m_pClientSndFrame->m_cProcBuf[iPos], 
		&m_pMatrixDllCall->m_pEnv->m_pInstrumentCommInfo->m_oLineSetupData.m_oLook.m_uiTilt, 4);
	iPos += 4;
	memcpy(&m_pClientSndFrame->m_cProcBuf[iPos], 
		&m_pMatrixDllCall->m_pEnv->m_pInstrumentCommInfo->m_oLineSetupData.m_oLook.m_uiLeakage, 4);
	iPos += 4;
	m_pClientSndFrame->MakeSetFrame(usCmd, m_pClientSndFrame->m_cProcBuf, iPos);
}


// 查询 InstrumentTestBase XML文件信息
void CClientRecThread::OnProcQueryInstrumentTestBaseXMLInfo(unsigned short usCmd)
{
	list<m_oInstrumentTestBaseStruct>::iterator iter;
	int iPos = 0;
	m_pMatrixDllCall->Dll_LoadInstrument_SensorTestBaseSetupData(true);
	for (iter = m_pMatrixDllCall->m_pEnv->m_pInstrumentCommInfo->m_oLineSetupData.m_olsInstrumentTestBaseStruct.begin();
		iter != m_pMatrixDllCall->m_pEnv->m_pInstrumentCommInfo->m_oLineSetupData.m_olsInstrumentTestBaseStruct.end(); iter++)
	{
		memcpy(&m_pClientSndFrame->m_cProcBuf[iPos], &iter->m_uiNb, 4);
		iPos += 4;
		memcpy(&m_pClientSndFrame->m_cProcBuf[iPos], &iter->m_usDescrSize, 2);
		iPos += 2;
		memcpy(&m_pClientSndFrame->m_cProcBuf[iPos], &iter->m_pcDescr, iter->m_usDescrSize);
		iPos += iter->m_usDescrSize;
		memcpy(&m_pClientSndFrame->m_cProcBuf[iPos], &iter->m_uiTestType, 4);
		iPos += 4;
		memcpy(&m_pClientSndFrame->m_cProcBuf[iPos], &iter->m_uiADC, 4);
		iPos += 4;
		memcpy(&m_pClientSndFrame->m_cProcBuf[iPos], &iter->m_uiGain, 4);
		iPos += 4;
		memcpy(&m_pClientSndFrame->m_cProcBuf[iPos], &iter->m_uiDAC, 4);
		iPos += 4;
		memcpy(&m_pClientSndFrame->m_cProcBuf[iPos], &iter->m_uiFilter, 4);
		iPos += 4;
		memcpy(&m_pClientSndFrame->m_cProcBuf[iPos], &iter->m_uiSamplingRate, 4);
		iPos += 4;
		memcpy(&m_pClientSndFrame->m_cProcBuf[iPos], &iter->m_uiSamplingLength, 4);
		iPos += 4;
	}
	m_pClientSndFrame->MakeSetFrame(usCmd, m_pClientSndFrame->m_cProcBuf, iPos);
}


// 查询 SensorTestBase XML文件信息
void CClientRecThread::OnProcQuerySensorTestBaseXMLInfo(unsigned short usCmd)
{
	list<m_oSensorTestBaseStruct>::iterator iter;
	int iPos = 0;
	m_pMatrixDllCall->Dll_LoadInstrument_SensorTestBaseSetupData(false);
	for (iter = m_pMatrixDllCall->m_pEnv->m_pInstrumentCommInfo->m_oLineSetupData.m_olsSensorTestBaseStruct.begin();
		iter != m_pMatrixDllCall->m_pEnv->m_pInstrumentCommInfo->m_oLineSetupData.m_olsSensorTestBaseStruct.end(); iter++)
	{
		memcpy(&m_pClientSndFrame->m_cProcBuf[iPos], &iter->m_uiNb, 4);
		iPos += 4;
		memcpy(&m_pClientSndFrame->m_cProcBuf[iPos], &iter->m_usDescrSize, 2);
		iPos += 2;
		memcpy(&m_pClientSndFrame->m_cProcBuf[iPos], &iter->m_pcDescr, iter->m_usDescrSize);
		iPos += iter->m_usDescrSize;
		memcpy(&m_pClientSndFrame->m_cProcBuf[iPos], &iter->m_uiTestType, 4);
		iPos += 4;
		memcpy(&m_pClientSndFrame->m_cProcBuf[iPos], &iter->m_uiADC, 4);
		iPos += 4;
		memcpy(&m_pClientSndFrame->m_cProcBuf[iPos], &iter->m_uiGain, 4);
		iPos += 4;
		memcpy(&m_pClientSndFrame->m_cProcBuf[iPos], &iter->m_uiDAC, 4);
		iPos += 4;
		memcpy(&m_pClientSndFrame->m_cProcBuf[iPos], &iter->m_uiFilter, 4);
		iPos += 4;
		memcpy(&m_pClientSndFrame->m_cProcBuf[iPos], &iter->m_uiSamplingRate, 4);
		iPos += 4;
		memcpy(&m_pClientSndFrame->m_cProcBuf[iPos], &iter->m_uiSamplingLength, 4);
		iPos += 4;
	}
	m_pClientSndFrame->MakeSetFrame(usCmd, m_pClientSndFrame->m_cProcBuf, iPos);
}


// 查询 InstrumentTestLimit XML文件信息
void CClientRecThread::OnProcQueryInstrumentTestLimitXMLInfo(unsigned short usCmd)
{
	list<m_oInstrumentTestLimitStruct>::iterator iter;
	int iPos = 0;
	m_pMatrixDllCall->Dll_LoadInstrument_SensorTestLimitSetupData(true);
	for (iter = m_pMatrixDllCall->m_pEnv->m_pInstrumentCommInfo->m_oLineSetupData.m_olsInstrumentTestLimitStruct.begin();
		iter != m_pMatrixDllCall->m_pEnv->m_pInstrumentCommInfo->m_oLineSetupData.m_olsInstrumentTestLimitStruct.end(); iter++)
	{
		memcpy(&m_pClientSndFrame->m_cProcBuf[iPos], &iter->m_uiNb, 4);
		iPos += 4;
		memcpy(&m_pClientSndFrame->m_cProcBuf[iPos], &iter->m_usDescrSize, 2);
		iPos += 2;
		memcpy(&m_pClientSndFrame->m_cProcBuf[iPos], &iter->m_pcDescr, iter->m_usDescrSize);
		iPos += iter->m_usDescrSize;
		memcpy(&m_pClientSndFrame->m_cProcBuf[iPos], &iter->m_usUnitSize, 2);
		iPos += 2;
		memcpy(&m_pClientSndFrame->m_cProcBuf[iPos], &iter->m_pcUnit, iter->m_usUnitSize);
		iPos += iter->m_usUnitSize;
		memcpy(&m_pClientSndFrame->m_cProcBuf[iPos], &iter->m_uiTestAim, 4);
		iPos += 4;
		memcpy(&m_pClientSndFrame->m_cProcBuf[iPos], &iter->m_uiTestType, 4);
		iPos += 4;
		memcpy(&m_pClientSndFrame->m_cProcBuf[iPos], &iter->m_fLimit, 4);
		iPos += 4;
	}
	m_pClientSndFrame->MakeSetFrame(usCmd, m_pClientSndFrame->m_cProcBuf, iPos);
}


// 查询 SensorTestLimit XML文件信息
void CClientRecThread::OnProcQuerySensorTestLimitXMLInfo(unsigned short usCmd)
{
	list<m_oSensorTestLimitStruct>::iterator iter;
	int iPos = 0;
	m_pMatrixDllCall->Dll_LoadInstrument_SensorTestLimitSetupData(false);
	for (iter = m_pMatrixDllCall->m_pEnv->m_pInstrumentCommInfo->m_oLineSetupData.m_olsSensorTestLimitStruct.begin();
		iter != m_pMatrixDllCall->m_pEnv->m_pInstrumentCommInfo->m_oLineSetupData.m_olsSensorTestLimitStruct.end(); iter++)
	{
		memcpy(&m_pClientSndFrame->m_cProcBuf[iPos], &iter->m_uiNb, 4);
		iPos += 4;
		memcpy(&m_pClientSndFrame->m_cProcBuf[iPos], &iter->m_usDescrSize, 2);
		iPos += 2;
		memcpy(&m_pClientSndFrame->m_cProcBuf[iPos], &iter->m_pcDescr, iter->m_usDescrSize);
		iPos += iter->m_usDescrSize;
		memcpy(&m_pClientSndFrame->m_cProcBuf[iPos], &iter->m_usUnitSize, 2);
		iPos += 2;
		memcpy(&m_pClientSndFrame->m_cProcBuf[iPos], &iter->m_pcUnit, iter->m_usUnitSize);
		iPos += iter->m_usUnitSize;
		memcpy(&m_pClientSndFrame->m_cProcBuf[iPos], &iter->m_uiTestAim, 4);
		iPos += 4;
		memcpy(&m_pClientSndFrame->m_cProcBuf[iPos], &iter->m_uiTestType, 4);
		iPos += 4;
		memcpy(&m_pClientSndFrame->m_cProcBuf[iPos], &iter->m_fLimit, 4);
		iPos += 4;
	}
	m_pClientSndFrame->MakeSetFrame(usCmd, m_pClientSndFrame->m_cProcBuf, iPos);
}


// 查询 InstrumentTest XML文件信息
void CClientRecThread::OnProcQueryInstrumentTestXMLInfo(unsigned short usCmd)
{
	list<m_oInstrumentTestStruct>::iterator iter;
	int iPos = 0;
	m_pMatrixDllCall->Dll_LoadInstrumentTestSetupData();
	for (iter = m_pMatrixDllCall->m_pEnv->m_pInstrumentCommInfo->m_oLineSetupData.m_olsInstrumentTestStruct.begin();
		iter != m_pMatrixDllCall->m_pEnv->m_pInstrumentCommInfo->m_oLineSetupData.m_olsInstrumentTestStruct.end(); iter++)
	{
		memcpy(&m_pClientSndFrame->m_cProcBuf[iPos], &iter->m_uiNb, 4);
		iPos += 4;
		memcpy(&m_pClientSndFrame->m_cProcBuf[iPos], &iter->m_uiTestType, 4);
		iPos += 4;
		memcpy(&m_pClientSndFrame->m_cProcBuf[iPos], &iter->m_uiGain, 4);
		iPos += 4;
		memcpy(&m_pClientSndFrame->m_cProcBuf[iPos], &iter->m_uiRecordLength, 4);
		iPos += 4;
		memcpy(&m_pClientSndFrame->m_cProcBuf[iPos], &iter->m_uiRecorded, 4);
		iPos += 4;
		memcpy(&m_pClientSndFrame->m_cProcBuf[iPos], &iter->m_usAuxiliaryDescrSize, 2);
		iPos += 2;
		memcpy(&m_pClientSndFrame->m_cProcBuf[iPos], &iter->m_pcAuxiliaryDescr, iter->m_usAuxiliaryDescrSize);
		iPos += iter->m_usAuxiliaryDescrSize;
		memcpy(&m_pClientSndFrame->m_cProcBuf[iPos], &iter->m_usAbsoluteSpreadSize, 2);
		iPos += 2;
		memcpy(&m_pClientSndFrame->m_cProcBuf[iPos], &iter->m_pcAbsoluteSpread, iter->m_usAbsoluteSpreadSize);
		iPos += iter->m_usAbsoluteSpreadSize;
	}
	m_pClientSndFrame->MakeSetFrame(usCmd, m_pClientSndFrame->m_cProcBuf, iPos);
}


// 查询 SensorTest XML文件信息
void CClientRecThread::OnProcQuerySensorTestXMLInfo(unsigned short usCmd)
{
	list<m_oSensorTestStruct>::iterator iter;
	int iPos = 0;
	m_pMatrixDllCall->Dll_LoadSensorTestSetupData();
	for (iter = m_pMatrixDllCall->m_pEnv->m_pInstrumentCommInfo->m_oLineSetupData.m_olsSensorTestStruct.begin();
		iter != m_pMatrixDllCall->m_pEnv->m_pInstrumentCommInfo->m_oLineSetupData.m_olsSensorTestStruct.end(); iter++)
	{
		memcpy(&m_pClientSndFrame->m_cProcBuf[iPos], &iter->m_uiNb, 4);
		iPos += 4;
		memcpy(&m_pClientSndFrame->m_cProcBuf[iPos], &iter->m_uiTestType, 4);
		iPos += 4;
		memcpy(&m_pClientSndFrame->m_cProcBuf[iPos], &iter->m_uiRecorded, 4);
		iPos += 4;
		memcpy(&m_pClientSndFrame->m_cProcBuf[iPos], &iter->m_usAbsoluteSpreadSize, 2);
		iPos += 2;
		memcpy(&m_pClientSndFrame->m_cProcBuf[iPos], &iter->m_pcAbsoluteSpread, iter->m_usAbsoluteSpreadSize);
		iPos += iter->m_usAbsoluteSpreadSize;
	}
	m_pClientSndFrame->MakeSetFrame(usCmd, m_pClientSndFrame->m_cProcBuf, iPos);
}


// 查询 MultipleTest XML文件信息
// 关键字结构体+排列个数+排列
void CClientRecThread::OnProcQueryMultipleTestXMLInfo(unsigned short usCmd)
{
	map<m_oMultipleTestKeyStruct, list<m_oMultipleTestTaskStruct>>::iterator iterMap;
	list<m_oMultipleTestTaskStruct>::iterator iter;
	int iPos = 0;
	unsigned int uiSize = 0;
	m_pMatrixDllCall->Dll_LoadMultipleTestSetupData();
	for (iterMap = m_pMatrixDllCall->m_pEnv->m_pInstrumentCommInfo->m_oLineSetupData.m_oMultpleTestStructMap.begin();
		iterMap != m_pMatrixDllCall->m_pEnv->m_pInstrumentCommInfo->m_oLineSetupData.m_oMultpleTestStructMap.end(); iterMap++)
	{
		memcpy(&m_pClientSndFrame->m_cProcBuf[iPos], &iterMap->first.m_uiNb, 4);
		iPos += 4;
		memcpy(&m_pClientSndFrame->m_cProcBuf[iPos], &iterMap->first.m_usTestNameSize, 2);
		iPos += 2;
		memcpy(&m_pClientSndFrame->m_cProcBuf[iPos], &iterMap->first.m_pcTestName, iterMap->first.m_usTestNameSize);
		iPos += iterMap->first.m_usTestNameSize;
		memcpy(&m_pClientSndFrame->m_cProcBuf[iPos], &iterMap->first.m_usAuxiliaryDescrSize, 2);
		iPos += 2;
		memcpy(&m_pClientSndFrame->m_cProcBuf[iPos], &iterMap->first.m_pcAuxiliaryDescr, iterMap->first.m_usAuxiliaryDescrSize);
		iPos += iterMap->first.m_usAuxiliaryDescrSize;
		memcpy(&m_pClientSndFrame->m_cProcBuf[iPos], &iterMap->first.m_usAbsoluteSpreadSize, 2);
		iPos += 2;
		memcpy(&m_pClientSndFrame->m_cProcBuf[iPos], &iterMap->first.m_pcAbsoluteSpread, iterMap->first.m_usAbsoluteSpreadSize);
		iPos += iterMap->first.m_usAbsoluteSpreadSize;
		memcpy(&m_pClientSndFrame->m_cProcBuf[iPos], &iterMap->first.m_uiDelayBetweenTest, 4);
		iPos += 4;
		memcpy(&m_pClientSndFrame->m_cProcBuf[iPos], &iterMap->first.m_uiRecordResults, 4);
		iPos += 4;
		memcpy(&m_pClientSndFrame->m_cProcBuf[iPos], &iterMap->first.m_uiRecordLength, 4);
		iPos += 4;
		memcpy(&m_pClientSndFrame->m_cProcBuf[iPos], &iterMap->first.m_uiTestFileNb, 4);
		iPos += 4;
		uiSize = iterMap->second.size();
		memcpy(&m_pClientSndFrame->m_cProcBuf[iPos], &uiSize, 4);
		iPos += 4;
		for (iter = iterMap->second.begin(); iter != iterMap->second.end(); iter++)
		{
			memcpy(&m_pClientSndFrame->m_cProcBuf[iPos], &iter->m_uiLineNb, 4);
			iPos += 4;
			memcpy(&m_pClientSndFrame->m_cProcBuf[iPos], &iter->m_uiTestType, 4);
			iPos += 4;
			memcpy(&m_pClientSndFrame->m_cProcBuf[iPos], &iter->m_uiGain, 4);
			iPos += 4;
			memcpy(&m_pClientSndFrame->m_cProcBuf[iPos], &iter->m_uiLoopLineNb, 4);
			iPos += 4;
			memcpy(&m_pClientSndFrame->m_cProcBuf[iPos], &iter->m_uiNbLoops, 4);
			iPos += 4;
		}
	}
	m_pClientSndFrame->MakeSetFrame(usCmd, m_pClientSndFrame->m_cProcBuf, iPos);
}


// 查询 SeisMonitorTest XML文件信息
void CClientRecThread::OnProcQuerySeisMonitorTestXMLInfo(unsigned short usCmd)
{
	int iPos = 0;
	m_pMatrixDllCall->Dll_LoadSeisMonitorSetupData();
	memcpy(&m_pClientSndFrame->m_cProcBuf[iPos], &m_pMatrixDllCall->m_pEnv->m_pInstrumentCommInfo->m_oLineSetupData.m_oSeisMonitor.m_usAbsoluteSpreadSize, 2);
	iPos += 2;
	memcpy(&m_pClientSndFrame->m_cProcBuf[iPos], 
		&m_pMatrixDllCall->m_pEnv->m_pInstrumentCommInfo->m_oLineSetupData.m_oSeisMonitor.m_pcAbsoluteSpread, 
		m_pMatrixDllCall->m_pEnv->m_pInstrumentCommInfo->m_oLineSetupData.m_oSeisMonitor.m_usAbsoluteSpreadSize);
	iPos += m_pMatrixDllCall->m_pEnv->m_pInstrumentCommInfo->m_oLineSetupData.m_oSeisMonitor.m_usAbsoluteSpreadSize;
	m_pClientSndFrame->MakeSetFrame(usCmd, m_pClientSndFrame->m_cProcBuf, iPos);
}


// 查询 LAULeakage XML文件信息
void CClientRecThread::OnProcQueryLAULeakageXMLInfo(unsigned short usCmd)
{
	m_pMatrixDllCall->Dll_LoadLAULeakageSetupData();
	int iPos = 0;
	memcpy(&m_pClientSndFrame->m_cProcBuf[iPos], 
		&m_pMatrixDllCall->m_pEnv->m_pInstrumentCommInfo->m_oLineSetupData.m_oLAULeakage.m_uiLimit, 4);
	iPos += 4;
	m_pClientSndFrame->MakeSetFrame(usCmd, m_pClientSndFrame->m_cProcBuf, iPos);
}


// 查询 FormLine XML文件信息
void CClientRecThread::OnProcQueryFormLineXMLInfo(unsigned short usCmd)
{
	list<m_oFormLineStruct>::iterator iter;
	int iPos = 0;
	m_pMatrixDllCall->Dll_LoadFormLineSetupData();
	for (iter = m_pMatrixDllCall->m_pEnv->m_pInstrumentCommInfo->m_oLineSetupData.m_olsFormLineStruct.begin();
		iter != m_pMatrixDllCall->m_pEnv->m_pInstrumentCommInfo->m_oLineSetupData.m_olsFormLineStruct.end(); iter++)
	{
		memcpy(&m_pClientSndFrame->m_cProcBuf[iPos], &iter->m_uiNb, 4);
		iPos += 4;
		memcpy(&m_pClientSndFrame->m_cProcBuf[iPos], &iter->m_uiBoxType, 4);
		iPos += 4;
		memcpy(&m_pClientSndFrame->m_cProcBuf[iPos], &iter->m_uiSN, 4);
		iPos += 4;
	}
	m_pClientSndFrame->MakeSetFrame(usCmd, m_pClientSndFrame->m_cProcBuf, iPos);
}


// 处理仪器信息查询
void CClientRecThread::OnProcQueryInstrumentInfo(char* pChar, unsigned int uiSize)
{
	unsigned int uiPos = 0;
	m_oAreaStruct oAreaStruct;
	while(uiPos < uiSize)
	{
		memcpy(&oAreaStruct.m_uiLineNb, &pChar[uiPos], 4);
		uiPos += 4;
		memcpy(&oAreaStruct.m_uiAreaNb, &pChar[uiPos], 4);
		uiPos += 4;
		uiPos = QueryInstrumentInfoByArea(&oAreaStruct, uiPos);
	}
	m_pClientSndFrame->MakeSetFrame(CmdQueryInstrumentInfo, m_pClientSndFrame->m_cProcBuf, uiPos);
}


// 按区域查询仪器信息
unsigned int CClientRecThread::QueryInstrumentInfoByArea(m_oAreaStruct* pArea, unsigned int uiStartPos)
{
	unsigned int uiPos = uiStartPos;
	m_oInstrumentStruct* pInstrument = NULL;
	int iLineIndex = 0;
	int iPointMinIndex = 0;
	int iPointMaxIndex = 0;
	EnterCriticalSection(&m_pMatrixDllCall->m_pEnv->m_pInstrumentList->m_oSecInstrumentList);
	// 由区域号得到线号及点号范围
	GetPointRangeFromArea(&iLineIndex, &iPointMinIndex, &iPointMaxIndex, pArea);
	for (int i = iPointMinIndex; i <= iPointMaxIndex; i++)
	{
		pInstrument = m_pMatrixDllCall->Dll_GetInstrumentFromLocationMap(iLineIndex, i, 
			&m_pMatrixDllCall->m_pEnv->m_pInstrumentList->m_oInstrumentLocationMap);
		if (pInstrument != NULL)
		{
			memcpy(&m_pClientSndFrame->m_cProcBuf[uiPos], &pInstrument->m_uiSN, 4);
			uiPos += 4;
			memcpy(&m_pClientSndFrame->m_cProcBuf[uiPos], &pInstrument->m_iLineIndex, 4);
			uiPos += 4;
			memcpy(&m_pClientSndFrame->m_cProcBuf[uiPos], &pInstrument->m_iPointIndex, 4);
			uiPos += 4;
			memcpy(&m_pClientSndFrame->m_cProcBuf[uiPos], &pInstrument->m_uiLineNb, 4);
			uiPos += 4;
			memcpy(&m_pClientSndFrame->m_cProcBuf[uiPos], &pInstrument->m_uiPointNb, 4);
			uiPos += 4;
			memcpy(&m_pClientSndFrame->m_cProcBuf[uiPos], &pInstrument->m_bJumpedChannel, 1);
			uiPos += 1;
			memcpy(&m_pClientSndFrame->m_cProcBuf[uiPos], &pInstrument->m_bSensor, 1);
			uiPos += 1;
			memcpy(&m_pClientSndFrame->m_cProcBuf[uiPos], &pInstrument->m_bAux, 1);
			uiPos += 1;
			memcpy(&m_pClientSndFrame->m_cProcBuf[uiPos], &pInstrument->m_bBlastMachine, 1);
			uiPos += 1;
			memcpy(&m_pClientSndFrame->m_cProcBuf[uiPos], &pInstrument->m_bDetour, 1);
			uiPos += 1;
			memcpy(&m_pClientSndFrame->m_cProcBuf[uiPos], &pInstrument->m_bDetourMarkerLow, 1);
			uiPos += 1;
			memcpy(&m_pClientSndFrame->m_cProcBuf[uiPos], &pInstrument->m_bDetourMarkerHigh, 1);
			uiPos += 1;
			memcpy(&m_pClientSndFrame->m_cProcBuf[uiPos], &pInstrument->m_bStopMarking, 1);
			uiPos += 1;
			memcpy(&m_pClientSndFrame->m_cProcBuf[uiPos], &pInstrument->m_bMarker, 1);
			uiPos += 1;
			memcpy(&m_pClientSndFrame->m_cProcBuf[uiPos], &pInstrument->m_bMute, 1);
			uiPos += 1;
		}
		else
		{
			memset(&m_pClientSndFrame->m_cProcBuf[uiPos], 0, 30);
			uiPos += 30;
		}
	}
	LeaveCriticalSection(&m_pMatrixDllCall->m_pEnv->m_pInstrumentList->m_oSecInstrumentList);
	return uiPos;
}


// 处理全部仪器信息查询
void CClientRecThread::OnProcQueryInstrumentInfoAll(void)
{

}