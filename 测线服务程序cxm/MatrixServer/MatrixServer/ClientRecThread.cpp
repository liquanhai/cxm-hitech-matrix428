#include "StdAfx.h"
#include "ClientRecThread.h"


CClientRecThread::CClientRecThread(void)
{
	m_pClientRecFrame = NULL;
	m_pClientSndFrame = NULL;
	m_pMatrixDllCall = NULL;
	m_bCheckConnected = false;
}


CClientRecThread::~CClientRecThread(void)
{
}

// ������
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
		// ���Ϊ����֡
		if (ptrFrameRec->m_cCmdType == CmdTypeSet)
		{
			// ����Ӧ��֡
			m_pClientSndFrame->MakeReturnFrame(ptrFrameRec);
			// ���Ϊ�����������δ��ɵľ��������������
			if (m_pClientRecFrame->m_uiCmdIndex < ptrFrameRec->m_uiCmdIndex)
			{
				m_pClientRecFrame->m_uiCmdIndex = ptrFrameRec->m_uiCmdIndex;
				m_pClientRecFrame->OnResetProcBuf();
			}
			// ��֡���ݼ��������������
			if (m_pClientRecFrame->m_uiCmdIndex == ptrFrameRec->m_uiCmdIndex)
			{
				SaveRecFrameToTask(ptrFrameRec);
			}
			// ���Ϊ���������򲻴���ֻ����Ӧ��
			else
			{
			}
		}
		// ���ΪӦ��֡
		else if (ptrFrameRec->m_cCmdType == CmdTypeReturn)
		{
			// ���ѷ���֡�������ҵ���֡��ɾ��
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
// ��֡���ݼ��������������
void CClientRecThread::SaveRecFrameToTask(m_oCommFrameStructPtr ptrFrame)
{
	unsigned int uiSaveBegin = 0;
	uiSaveBegin = (ptrFrame->m_uiFrameIndex - 1) * FrameInfoSizeLimit;
	memcpy(&m_pClientRecFrame->m_cProcBuf[uiSaveBegin], ptrFrame->m_pcFrameInfo, ptrFrame->m_usFrameInfoSize);
	// ����֡������ȫ
	if (ptrFrame->m_uiFrameIndex == ptrFrame->m_uiFrameNum)
	{
		// ���������
		OnProcRecCmd(ptrFrame->m_usCmd, m_pClientRecFrame->m_cProcBuf, uiSaveBegin + ptrFrame->m_usFrameInfoSize);
	}
}

// ������������
void CClientRecThread::OnProcRecCmd(unsigned short usCmd, char* pChar, unsigned int uiSize)
{
	// �ͻ��˵�½��֤��֡����Ϊ��֤�룩
	if (usCmd == CmdClientConnect)
	{
		// ������У������ƥ��
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
		// �ϵ磨�����ֺ�֡����Ϊ�գ�����ֵΪִ��FieldOnʣ��ʱ�䣬Ϊ0��ʾ����ȴ���
		case CmdSetFieldOn:
			OnProcSetFieldOn();
			break;
		// �ϵ磨�����ֺ�֡����Ϊ�գ�
		case CmdSetFieldOff:
			OnProcSetFieldOff();
			break;
		// ��ѯ SurveyXML �ļ���Ϣ��֡����Ϊ�գ�
		case CmdQuerySurveyXMLInfo:
			OnProcQuerySurveyXMLInfo(usCmd);
			break;
		// ��ѯ PointCode XML�ļ���Ϣ��֡����Ϊ�գ�
		case CmdQueryPointCodeXMLInfo:
			OnProcQueryPointCodeXMLInfo(usCmd);
			break;
		// ��ѯ Sensor XML�ļ���Ϣ��֡����Ϊ�գ�
		case CmdQuerySensorXMLInfo:
			OnProcQuerySensorXMLInfo(usCmd);
			break;
		// ��ѯ Marker XML�ļ���Ϣ��֡����Ϊ�գ�
		case CmdQueryMarkerXMLInfo:
			OnProcQueryMarkerXMLInfo(usCmd);
			break;
		// ��ѯ Aux XML�ļ���Ϣ��֡����Ϊ�գ�
		case CmdQueryAuxXMLInfo:
			OnProcQueryAuxXMLInfo(usCmd);
			break;
		// ��ѯ Detour XML�ļ���Ϣ��֡����Ϊ�գ�
		case CmdQueryDetourXMLInfo:
			OnProcQueryDetourXMLInfo(usCmd);
			break;
		// ��ѯ Mute XML�ļ���Ϣ��֡����Ϊ�գ�
		case CmdQueryMuteXMLInfo:
			OnProcQueryMuteXMLInfo(usCmd);
			break;
		// ��ѯ BlastMachine XML�ļ���Ϣ��֡����Ϊ�գ�
		case CmdQueryBlastMachineXMLInfo:
			OnProcQueryBlastMachineXMLInfo(usCmd);
			break;
		// ��ѯ Absolute XML�ļ���Ϣ��֡����Ϊ�գ�
		case CmdQueryAbsoluteXMLInfo:
			OnProcQueryAbsoluteXMLInfo(usCmd);
			break;
		// ��ѯ Generic XML�ļ���Ϣ��֡����Ϊ�գ�
		case CmdQueryGenericXMLInfo:
			OnProcQueryGenericXMLInfo(usCmd);
			break;
		// ��ѯ Look XML�ļ���Ϣ��֡����Ϊ�գ�
		case CmdQueryLookXMLInfo:
			OnProcQueryLookXMLInfo(usCmd);
			break;
		// ��ѯ InstrumentTestBase XML�ļ���Ϣ��֡����Ϊ�գ�
		case CmdQueryInstrumentTestBaseXMLInfo:
			OnProcQueryInstrumentTestBaseXMLInfo(usCmd);
			break;
		// ��ѯ SensorTestBase XML�ļ���Ϣ��֡����Ϊ�գ�
		case CmdQuerySensorTestBaseXMLInfo:
			OnProcQuerySensorTestBaseXMLInfo(usCmd);
			break;
		// ��ѯ InstrumentTestLimit XML�ļ���Ϣ��֡����Ϊ�գ�
		case CmdQueryInstrumentTestLimitXMLInfo:
			OnProcQueryInstrumentTestLimitXMLInfo(usCmd);
			break;
		// ��ѯ SensorTestLimit XML�ļ���Ϣ��֡����Ϊ�գ�
		case CmdQuerySensorTestLimitXMLInfo:
			OnProcQuerySensorTestLimitXMLInfo(usCmd);
			break;
		// ��ѯ InstrumentTest XML�ļ���Ϣ��֡����Ϊ�գ�
		case CmdQueryInstrumentTestXMLInfo:
			OnProcQueryInstrumentTestXMLInfo(usCmd);
			break;
		// ��ѯ SensorTest XML�ļ���Ϣ��֡����Ϊ�գ�
		case CmdQuerySensorTestXMLInfo:
			OnProcQuerySensorTestXMLInfo(usCmd);
			break;
		// ��ѯ MultipleTest XML�ļ���Ϣ��֡����Ϊ�գ�
		case CmdQueryMultipleTestXMLInfo:
			OnProcQueryMultipleTestXMLInfo(usCmd);
			break;
		// ��ѯ SeisMonitorTest XML�ļ���Ϣ��֡����Ϊ�գ�
		case CmdQuerySeisMonitorTestXMLInfo:
			OnProcQuerySeisMonitorTestXMLInfo(usCmd);
			break;
		// ��ѯ LAULeakage XML�ļ���Ϣ��֡����Ϊ�գ�
		case CmdQueryLAULeakageXMLInfo:
			OnProcQueryLAULeakageXMLInfo(usCmd);
			break;
		// ��ѯ FormLine XML�ļ���Ϣ��֡����Ϊ�գ�
		case CmdQueryFormLineXMLInfo:
			OnProcQueryFormLineXMLInfo(usCmd);
			break;
		default:
			break;
		}
	}
}

// �����ϵ�
void CClientRecThread::OnProcSetFieldOn(void)
{
	unsigned int uiFieldOnNeedTime = 0;;
	uiFieldOnNeedTime = m_pMatrixDllCall->Dll_Work();
	memcpy(m_pClientSndFrame->m_cProcBuf, &uiFieldOnNeedTime, 4);
	m_pClientSndFrame->MakeSetFrame(CmdFieldOnWaitTime, m_pClientSndFrame->m_cProcBuf, 4);
}


// ����ϵ�
void CClientRecThread::OnProcSetFieldOff(void)
{
	m_pMatrixDllCall->Dll_Stop();
}


// ��ѯ SurveyXML �ļ���Ϣ
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


// ��ѯ PointCode XML�ļ���Ϣ
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


// ��ѯ Sensor XML�ļ���Ϣ
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


// ��ѯ Marker XML�ļ���Ϣ
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


// ��ѯ Aux XML�ļ���Ϣ
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


// ��ѯ Detour XML�ļ���Ϣ
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


// ��ѯ Mute XML�ļ���Ϣ
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


// ��ѯ BlastMachine XML�ļ���Ϣ
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


// ��ѯ Absolute XML�ļ���Ϣ
// �ڵ�+���и���+����
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


// ��ѯ Generic XML�ļ���Ϣ
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


// ��ѯ Look XML�ļ���Ϣ
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


// ��ѯ InstrumentTestBase XML�ļ���Ϣ
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


// ��ѯ SensorTestBase XML�ļ���Ϣ
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


// ��ѯ InstrumentTestLimit XML�ļ���Ϣ
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


// ��ѯ SensorTestLimit XML�ļ���Ϣ
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


// ��ѯ InstrumentTest XML�ļ���Ϣ
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


// ��ѯ SensorTest XML�ļ���Ϣ
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


// ��ѯ MultipleTest XML�ļ���Ϣ
// �ؼ��ֽṹ��+���и���+����
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


// ��ѯ SeisMonitorTest XML�ļ���Ϣ
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


// ��ѯ LAULeakage XML�ļ���Ϣ
void CClientRecThread::OnProcQueryLAULeakageXMLInfo(unsigned short usCmd)
{
	m_pMatrixDllCall->Dll_LoadLAULeakageSetupData();
	int iPos = 0;
	memcpy(&m_pClientSndFrame->m_cProcBuf[iPos], 
		&m_pMatrixDllCall->m_pEnv->m_pInstrumentCommInfo->m_oLineSetupData.m_oLAULeakage.m_uiLimit, 4);
	iPos += 4;
	m_pClientSndFrame->MakeSetFrame(usCmd, m_pClientSndFrame->m_cProcBuf, iPos);
}


// ��ѯ FormLine XML�ļ���Ϣ
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
