#include "stdafx.h"
#include "MatrixServerDll.h"

// 创建ADC数据接收线程
m_oADCDataRecThreadStruct* OnCreateADCDataRecThread(void)
{
	m_oADCDataRecThreadStruct* pADCDataRecThread = NULL;
	pADCDataRecThread = new m_oADCDataRecThreadStruct;
	pADCDataRecThread->m_pThread = new m_oThreadStruct;
	pADCDataRecThread->m_pLogOutPutADCFrameTime = NULL;
	pADCDataRecThread->m_pADCDataBufArray = NULL;
	pADCDataRecThread->m_pADCDataFrame = NULL;
	pADCDataRecThread->m_pLineList = NULL;
	InitializeCriticalSection(&pADCDataRecThread->m_oSecADCDataRecThread);
	return pADCDataRecThread;
}
// 线程等待函数
void WaitADCDataRecThread(m_oADCDataRecThreadStruct* pADCDataRecThread)
{
	ASSERT(pADCDataRecThread != NULL);
	// 初始化等待次数为0
	int iWaitCount = 0;
	bool bClose = false;
	// 循环
	while(true)
	{	// 休眠50毫秒
		Sleep(pADCDataRecThread->m_pThread->m_pConstVar->m_iOneSleepTime);
		// 等待次数加1
		iWaitCount++;
		EnterCriticalSection(&pADCDataRecThread->m_oSecADCDataRecThread);
		bClose = pADCDataRecThread->m_pThread->m_bClose;
		LeaveCriticalSection(&pADCDataRecThread->m_oSecADCDataRecThread);
		// 判断是否可以处理的条件
		if(bClose == true)
		{
			// 返回
			return;
		}
		// 判断等待次数是否大于等于最多等待次数
		if(pADCDataRecThread->m_pThread->m_pConstVar->m_iADCDataRecSleepTimes == iWaitCount)
		{
			// 返回
			return;
		}		
	}
}
// 采样数据回调函数
// void GetProSampleDateCallBack(m_oADCDataRecThreadStruct* pADCDataRecThread, ProSampleDateCallBack pCallBack)
// {
// 	ASSERT(pADCDataRecThread != NULL);
// 	EnterCriticalSection(&pADCDataRecThread->m_oSecADCDataRecThread);
// 	pADCDataRecThread->m_oProSampleDataCallBack = pCallBack;
// 	LeaveCriticalSection(&pADCDataRecThread->m_oSecADCDataRecThread);
// }
// 将ADC数据加入到任务缓冲区
void AddToADCDataBuf(unsigned int uiIP, unsigned int uiTime, char* pBuf, 
	unsigned int uiLen, m_oADCDataRecThreadStruct* pADCDataRecThread)
{
	ASSERT(pADCDataRecThread != NULL);
	ASSERT(pBuf != NULL);
// 	m_oADCDataBufStruct* pADCDataBuf = NULL;
// 	pADCDataBuf = GetFreeADCDataBuf(pADCDataRecThread->m_pADCDataBufArray);
// 	pADCDataBuf->m_uiFrameNb = uiFrameNb;
// 	pADCDataBuf->m_uiIP = uiIP;
// 	pADCDataBuf->m_uiSysTime = uiSysTime;
// 	EnterCriticalSection(&pADCDataRecThread->m_pADCDataFrame->m_oSecADCDataFrame);
// 	memcpy(pADCDataBuf->m_pADCDataBuf, pADCDataRecThread->m_pADCDataFrame->m_pCommandStructReturn->m_pADCData,
// 		pADCDataRecThread->m_pThread->m_pConstVar->m_iADCDataInOneFrameNum * sizeof(int));
	// ADC数据处理的回调函数
// 	(*pADCDataRecThread->m_oProSampleDataCallBack)(iLineIndex, iPointIndex, 
// 		pADCDataRecThread->m_pADCDataFrame->m_pCommandStructReturn->m_pADCData,
// 		pADCDataRecThread->m_pThread->m_pConstVar->m_iADCDataInOneFrameNum,
// 		uiSN);
// 	LeaveCriticalSection(&pADCDataRecThread->m_pADCDataFrame->m_oSecADCDataFrame);
// 	EnterCriticalSection(&pADCDataRecThread->m_pADCDataBufArray->m_oSecADCDataBufArray);
// 	pADCDataRecThread->m_pADCDataBufArray->m_olsADCDataToWrite.push_back(pADCDataBuf);
// 	LeaveCriticalSection(&pADCDataRecThread->m_pADCDataBufArray->m_oSecADCDataBufArray);
}
// 查找没有接收到数据的采集站
void FindFDUNotRecADCData(m_oADCDataRecThreadStruct* pADCDataRecThread)
{
	hash_map<unsigned int, m_oInstrumentStruct*>::iterator iter;
	CString str = _T("");
	string strConv = "";
	EnterCriticalSection(&pADCDataRecThread->m_pLineList->m_oSecLineList);
	for (iter = pADCDataRecThread->m_pLineList->m_pInstrumentList->m_oOptInstrumentMap.begin();
		iter != pADCDataRecThread->m_pLineList->m_pInstrumentList->m_oOptInstrumentMap.end(); iter++)
	{
		if ((iter->second->m_uiADCDataActualRecFrameNum == 0)
			&& (iter->second->m_iInstrumentType == InstrumentTypeFDU)
			&& (iter->second->m_bCheckADCFrameLate == true))
		{
			str.Format(_T("未收到SN = 0x%x的采集站的ADC数据帧"), iter->second->m_uiSN);
			strConv = (CStringA)str;
			AddMsgToLogOutPutList(pADCDataRecThread->m_pThread->m_pLogOutPut, "", 
				strConv, ErrorType, IDS_ERR_ADCDATANOTREC);
			iter->second->m_bCheckADCFrameLate = false;
		}
	}
	LeaveCriticalSection(&pADCDataRecThread->m_pLineList->m_oSecLineList);
}
// 处理单个ADC数据帧
void ProcADCDataRecFrameOne(m_oADCDataRecThreadStruct* pADCDataRecThread)
{
	ASSERT(pADCDataRecThread != NULL);
	unsigned int uiIPInstrument = 0;
	m_oInstrumentStruct* pInstrument = NULL;
	unsigned short usADCDataFramePoint = 0;
	unsigned int uiADCDataFrameSysTime = 0;
	int iADCDataInOneFrameNum = 0;
	unsigned short usADCFramePointLimit = 0;
	unsigned short usADCDataFramePointMove = 0;
	unsigned short usADCFramePointNb = 0;
	unsigned int uiLostFrameNum = 0;
	CString str = _T("");
	CString strOut = _T("");
	string strConv = "";
	string strFrameData = "";
	unsigned int uiADCSaveBufSize = 0;
	m_oADCLostFrameStruct* pADCLostFrame = NULL;
	int iADCDataTemp = 0;
	int iADCDataSize3B = 0;
	char* pADCDataBuf = NULL;
	iADCDataSize3B = pADCDataRecThread->m_pThread->m_pConstVar->m_iADCDataSize3B;
	iADCDataInOneFrameNum = pADCDataRecThread->m_pThread->m_pConstVar->m_iADCDataInOneFrameNum;
	usADCFramePointLimit = pADCDataRecThread->m_pThread->m_pConstVar->m_usADCFramePointLimit;
	uiADCSaveBufSize = iADCDataInOneFrameNum * iADCDataSize3B;
	EnterCriticalSection(&pADCDataRecThread->m_pADCDataFrame->m_oSecADCDataFrame);
	// 得到仪器IP
	uiIPInstrument = pADCDataRecThread->m_pADCDataFrame->m_pCommandStructReturn->m_uiSrcIP;
	// 得到指针偏移量
	usADCDataFramePoint = pADCDataRecThread->m_pADCDataFrame->m_pCommandStructReturn->m_usADCDataPoint;
	// 得到本地系统时间
	uiADCDataFrameSysTime = pADCDataRecThread->m_pADCDataFrame->m_pCommandStructReturn->m_uiADCSampleSysTime;
	pADCDataBuf = pADCDataRecThread->m_pADCDataFrame->m_pCommandStructReturn->m_pADCDataBuf;
	if (usADCDataFramePoint > usADCFramePointLimit)
	{
		GetFrameInfo(pADCDataRecThread->m_pADCDataFrame->m_cpRcvFrameData, 
			pADCDataRecThread->m_pThread->m_pConstVar->m_iRcvFrameSize, &strFrameData);
		LeaveCriticalSection(&pADCDataRecThread->m_pADCDataFrame->m_oSecADCDataFrame);
		AddMsgToLogOutPutList(pADCDataRecThread->m_pThread->m_pLogOutPut, "ProcADCDataRecFrameOne", 
			strFrameData, ErrorType, IDS_ERR_FRAMEPOINT_LIMITOVER);
		return;
	}
	LeaveCriticalSection(&pADCDataRecThread->m_pADCDataFrame->m_oSecADCDataFrame);
	EnterCriticalSection(&pADCDataRecThread->m_pLineList->m_oSecLineList);
	if (FALSE == IfIndexExistInMap(uiIPInstrument, &pADCDataRecThread->m_pLineList->m_pInstrumentList->m_oOptInstrumentMap))
	{
		LeaveCriticalSection(&pADCDataRecThread->m_pLineList->m_oSecLineList);
		return;
	}
	pInstrument = GetInstrumentFromMap(uiIPInstrument, &pADCDataRecThread->m_pLineList->m_pInstrumentList->m_oOptInstrumentMap);
	// 更新仪器的存活时间
	UpdateInstrActiveTime(pInstrument);
	pInstrument->m_uiADCDataActualRecFrameNum++;
	// 在丢帧索引表中找到
	if (TRUE == IfIndexExistInADCFrameLostMap(uiIPInstrument, usADCDataFramePoint, 
		&pADCDataRecThread->m_pLineList->m_pInstrumentList->m_oADCLostFrameMap))
	{
		str.Format(_T("收到SN = 0x%x，IP地址 = 0x%x 的ADC数据重发帧，指针偏移量 = %d"), 
			pInstrument->m_uiSN, pInstrument->m_uiIP, usADCDataFramePoint);
		strConv = (CStringA)str;
		AddMsgToLogOutPutList(pADCDataRecThread->m_pThread->m_pLogOutPut, "ProcADCDataRecFrameOne", 
			strConv);
		OutputDebugString(str);
		pADCLostFrame = GetFromADCFrameLostMap(uiIPInstrument, usADCDataFramePoint, 
			&pADCDataRecThread->m_pLineList->m_pInstrumentList->m_oADCLostFrameMap);
		if (pADCLostFrame->m_bReturnOk == false)
		{
			pInstrument->m_uiADCDataRetransmissionFrameNum++;
			pADCLostFrame->m_bReturnOk = true;
			// 将ADC数据加入到任务缓冲区
			AddToADCDataBuf(pInstrument->m_uiIP, pADCLostFrame->m_uiSysTime, 
				pADCDataBuf, uiADCSaveBufSize, pADCDataRecThread);
		}
		LeaveCriticalSection(&pADCDataRecThread->m_pLineList->m_oSecLineList);
		return;
	}
	pInstrument->m_uiADCDataShouldRecFrameNum++;
	pInstrument->m_usADCDataFramePointOld = pInstrument->m_usADCDataFramePointNow;
	pInstrument->m_uiADCDataFrameSysTimeOld = pInstrument->m_uiADCDataFrameSysTimeNow;
	pInstrument->m_usADCDataFramePointNow = usADCDataFramePoint;
	pInstrument->m_uiADCDataFrameSysTimeNow = uiADCDataFrameSysTime;
	if (pInstrument->m_uiADCDataActualRecFrameNum == 1)
	{
		if (pInstrument->m_uiTBHigh != uiADCDataFrameSysTime)
		{
			str.Format(_T("仪器SN = 0x%x，IP = 0x%x，第一帧的本地时间 = 0x%x, TB时间 = 0x%x"), pInstrument->m_uiSN, 
				pInstrument->m_uiIP, uiADCDataFrameSysTime, pInstrument->m_uiTBHigh);
			strConv = (CStringA)str;
			AddMsgToLogOutPutList(pADCDataRecThread->m_pThread->m_pLogOutPut, "ProcADCDataRecFrameOne",
				strConv, ErrorType, IDS_ERR_SAMPLETIME);
		}
	}
	// 收到第二帧数据检查其他站是否收到数据帧
	else if (pInstrument->m_uiADCDataActualRecFrameNum == 2)
	{
		FindFDUNotRecADCData(pADCDataRecThread);
	}
	//@@@@ 32位本地时间计数能够运行12天，暂不考虑超过12天的情况
	if (pInstrument->m_uiADCDataFrameSysTimeNow <= pInstrument->m_uiADCDataFrameSysTimeOld)
	{
		LeaveCriticalSection(&pADCDataRecThread->m_pLineList->m_oSecLineList);
		EnterCriticalSection(&pADCDataRecThread->m_pADCDataFrame->m_oSecADCDataFrame);
		GetFrameInfo(pADCDataRecThread->m_pADCDataFrame->m_cpRcvFrameData,
			pADCDataRecThread->m_pThread->m_pConstVar->m_iRcvFrameSize, &strFrameData);
		LeaveCriticalSection(&pADCDataRecThread->m_pADCDataFrame->m_oSecADCDataFrame);
		AddMsgToLogOutPutList(pADCDataRecThread->m_pThread->m_pLogOutPut, "ProcADCDataRecFrameOne", 
			strFrameData, ErrorType, IDS_ERR_ADCFRAMESYSTIME_ERROR);
		str.Format(_T("当前帧本地时间为%d， 前一帧的本地时间为%d"), pInstrument->m_uiADCDataFrameSysTimeNow, 
			pInstrument->m_uiADCDataFrameSysTimeOld);
		strConv = (CStringA)str;
		AddMsgToLogOutPutList(pADCDataRecThread->m_pLogOutPutADCFrameTime, "", 
			strConv, ErrorType, IDS_ERR_ADCFRAMESYSTIME_ERROR);
		AddMsgToLogOutPutList(pADCDataRecThread->m_pThread->m_pLogOutPut, "ProcADCDataRecFrameOne", 
			strConv, ErrorType, IDS_ERR_ADCFRAMESYSTIME_ERROR);
		return;
	}
	if (pInstrument->m_usADCDataFramePointNow < pInstrument->m_usADCDataFramePointOld)
	{
		usADCDataFramePointMove = usADCFramePointLimit - pInstrument->m_usADCDataFramePointOld 
			+ pInstrument->m_usADCDataFramePointNow;
	}
	else
	{
		usADCDataFramePointMove = pInstrument->m_usADCDataFramePointNow - pInstrument->m_usADCDataFramePointOld;
	}
	if (usADCDataFramePointMove % iADCDataInOneFrameNum != 0)
	{
		LeaveCriticalSection(&pADCDataRecThread->m_pLineList->m_oSecLineList);
		EnterCriticalSection(&pADCDataRecThread->m_pADCDataFrame->m_oSecADCDataFrame);
		GetFrameInfo(pADCDataRecThread->m_pADCDataFrame->m_cpRcvFrameData,
			pADCDataRecThread->m_pThread->m_pConstVar->m_iRcvFrameSize, &strFrameData);
		LeaveCriticalSection(&pADCDataRecThread->m_pADCDataFrame->m_oSecADCDataFrame);
		AddMsgToLogOutPutList(pADCDataRecThread->m_pThread->m_pLogOutPut, "ProcADCDataRecFrameOne", 
			strFrameData, ErrorType, IDS_ERR_FRAMEPOINT_ERROR);
		str.Format(_T("指针偏移量出错，偏移量差值为%d"), usADCDataFramePointMove);
		strConv = (CStringA)str;
		AddMsgToLogOutPutList(pADCDataRecThread->m_pLogOutPutADCFrameTime, "", 
			strConv, ErrorType, IDS_ERR_FRAMEPOINT_ERROR);
		AddMsgToLogOutPutList(pADCDataRecThread->m_pThread->m_pLogOutPut, "ProcADCDataRecFrameOne", 
			strConv, ErrorType, IDS_ERR_FRAMEPOINT_ERROR);
		return;
	}
	else
	{
		if (usADCDataFramePointMove != 0)
		{
			uiLostFrameNum = usADCDataFramePointMove / iADCDataInOneFrameNum - 1;
			if (uiLostFrameNum != 0)
			{
				// 加入到丢帧索引表
				for (unsigned int i=0; i<uiLostFrameNum; i++)
				{
					m_oADCLostFrameStruct ADCLostFrame;
					usADCFramePointNb = static_cast<unsigned short>(pInstrument->m_usADCDataFramePointOld 
						+ (i + 1) * iADCDataInOneFrameNum);
					if (usADCFramePointNb >= usADCFramePointLimit)
					{
						usADCFramePointNb -= usADCFramePointLimit;
					}
					ADCLostFrame.m_uiCount = 0;
					ADCLostFrame.m_bReturnOk = false;
					// 根据采样率确定时间差
					ADCLostFrame.m_uiSysTime = pInstrument->m_uiADCDataFrameSysTimeOld 
						+ (i + 1) * (4000 / pADCDataRecThread->m_iADCSampleRate) * iADCDataInOneFrameNum;
					AddToADCFrameLostMap(pInstrument->m_uiIP, usADCFramePointNb, ADCLostFrame, &pADCDataRecThread->m_pLineList->m_pInstrumentList->m_oADCLostFrameMap);
					pInstrument->m_uiADCDataShouldRecFrameNum++;
					// 在丢帧的位置写当前帧的内容
					AddToADCDataBuf(pInstrument->m_uiIP, ADCLostFrame.m_uiSysTime, 
						pADCDataBuf, uiADCSaveBufSize, pADCDataRecThread);
					for (int i=0; i<iADCDataInOneFrameNum; i++)
					{
						iADCDataTemp = 0;
						memcpy(&iADCDataTemp, &pADCDataBuf[i * iADCDataSize3B], iADCDataSize3B);
						if (iADCDataTemp > 0x800000)
						{
							iADCDataTemp = -(0xffffff - iADCDataTemp);
						}
						if (pInstrument->m_olsADCDataSave.size() == pADCDataRecThread->m_pThread->m_pConstVar->m_uiSaveTestDataNum)
						{
							pInstrument->m_olsADCDataSave.pop_front();
						}
						pInstrument->m_olsADCDataSave.push_back(iADCDataTemp);
					}
				}
				str.Format(_T("仪器SN = 0x%x，IP = 0x%x，丢失帧数为%d"), pInstrument->m_uiSN, 
					pInstrument->m_uiIP, uiLostFrameNum);
				strConv = (CStringA)str;
				AddMsgToLogOutPutList(pADCDataRecThread->m_pThread->m_pLogOutPut, "ProcADCDataRecFrameOne",
					strConv, WarningType);
				AddMsgToLogOutPutList(pADCDataRecThread->m_pLogOutPutADCFrameTime, "", 
					strConv, WarningType);
			}
		}
		// 保存当前帧的内容
		AddToADCDataBuf(pInstrument->m_uiIP, pInstrument->m_uiADCDataFrameSysTimeNow, 
			pADCDataBuf, uiADCSaveBufSize, pADCDataRecThread);
		for (int i=0; i<iADCDataInOneFrameNum; i++)
		{
			iADCDataTemp = 0;
			memcpy(&iADCDataTemp, &pADCDataBuf[i * iADCDataSize3B], iADCDataSize3B);
			if (iADCDataTemp > 0x800000)
			{
				iADCDataTemp = -(0xffffff - iADCDataTemp);
			}
			if (pInstrument->m_olsADCDataSave.size() == pADCDataRecThread->m_pThread->m_pConstVar->m_uiSaveTestDataNum)
			{
				pInstrument->m_olsADCDataSave.pop_front();
			}
			pInstrument->m_olsADCDataSave.push_back(iADCDataTemp);
		}
	}
	str.Format(_T("仪器SN = 0x%x，IP = 0x%x；"), pInstrument->m_uiSN, pInstrument->m_uiIP);
	strOut += str;
	str.Format(_T("接收帧的指针偏移量为 %d，差值为 %d；"), 
		pInstrument->m_usADCDataFramePointNow, usADCDataFramePointMove);
	strOut += str;
	str.Format(_T("本地时间为 %d，差值为%d；"), pInstrument->m_uiADCDataFrameSysTimeNow, 
		pInstrument->m_uiADCDataFrameSysTimeNow - pInstrument->m_uiADCDataFrameSysTimeOld);
	strOut += str;
	strConv = (CStringA)strOut;
	AddMsgToLogOutPutList(pADCDataRecThread->m_pLogOutPutADCFrameTime, "", strConv);
	LeaveCriticalSection(&pADCDataRecThread->m_pLineList->m_oSecLineList);
	



// 	EnterCriticalSection(&pADCDataRecThread->m_oSecADCDataRecThread);
// 	uiADCDataFrameSysTimeOld = pADCDataRecThread->m_uiADCDataFrameSysTime;
// 	iADCFrameCount = pADCDataRecThread->m_iADCFrameCount;
// 	bCheckFDUADCRec = pADCDataRecThread->m_bCheckFDUADCRec;
// 	LeaveCriticalSection(&pADCDataRecThread->m_oSecADCDataRecThread);
	EnterCriticalSection(&pADCDataRecThread->m_pADCDataFrame->m_oSecADCDataFrame);
// 	// 测试数据
// 	iTestData = pADCDataRecThread->m_pADCDataFrame->m_pCommandStructReturn->m_pADCData[0];
// 	for (int i=0; i<pConstVar->m_iADCDataInOneFrameNum; i++)
// 	{
// 		iTemp = 0;
// 		memcpy(&iTemp, &pFrameData[iPos], iADCDataSize3B);
// 		iPos += iADCDataSize3B;
// 		if (iTemp > 0x800000)
// 		{
// 			iTemp = -(0xffffff - iTemp);
// 		}
// 		pCommand->m_pADCData[i] = iTemp;
// 	}
	LeaveCriticalSection(&pADCDataRecThread->m_pADCDataFrame->m_oSecADCDataFrame);

	EnterCriticalSection(&pADCDataRecThread->m_pLineList->m_oSecLineList);
// 	uiTBHigh = pADCDataRecThread->m_pLineList->m_uiTBHigh;
// 	// 仪器不在索引表中
// 	if (FALSE == IfIndexExistInMap(uiIPInstrument, &pADCDataRecThread->m_pLineList->m_pInstrumentList->m_oIPInstrumentMap))
// 	{
// 		LeaveCriticalSection(&pADCDataRecThread->m_pLineList->m_oSecLineList);
// 		str.Format(_T("收到IP地址 = 0x%x的ADC数据帧"), uiIPInstrument);
// 		strConv = (CStringA)str;
// 		AddMsgToLogOutPutList(pADCDataRecThread->m_pThread->m_pLogOutPut, "ProcADCDataRecFrameOne", 
// 			strConv, ErrorType, IDS_ERR_IPMAP_NOTEXIT);
// 		return;
// 	}
// 	pInstrument = GetInstrumentFromMap(uiIPInstrument, 
// 		&pADCDataRecThread->m_pLineList->m_pInstrumentList->m_oIPInstrumentMap);
// 	// 更新仪器的存活时间
// 	UpdateInstrActiveTime(pInstrument);
// 	// 在丢帧索引表中找到
// 	if (TRUE == IfIndexExistInADCFrameLostMap(uiIPInstrument, usADCDataFramePointNow, 
// 		&pADCDataRecThread->m_pLineList->m_pInstrumentList->m_oADCLostFrameMap))
// 	{
// 		str.Format(_T("收到SN = 0x%x，IP地址 = 0x%x的ADC数据重发帧，指针偏移量 = %d"), 
// 			pInstrument->m_uiSN, pInstrument->m_uiIP, usADCDataFramePointNow);
// 		strConv = (CStringA)str;
// 		AddMsgToLogOutPutList(pADCDataRecThread->m_pThread->m_pLogOutPut, "ProcADCDataRecFrameOne", 
// 			strConv);
// 		OutputDebugString(str);
// 		pADCLostFrame = GetFromADCFrameLostMap(uiIPInstrument, usADCDataFramePointNow, 
// 			&pADCDataRecThread->m_pLineList->m_pInstrumentList->m_oADCLostFrameMap);
// 		if (pADCLostFrame->m_bReturnOk == false)
// 		{
// 			pInstrument->m_uiADCDataActualRecFrameNum++;
// 			pInstrument->m_uiADCDataRetransmissionFrameNum++;
// 			pADCLostFrame->m_bReturnOk = true;
// // 			// 将该应答帧数据写入文件
// // 			uiFrameNb = pADCLostFrame->m_uiFrameNb;
// // 			AddToADCDataWriteFileList(pInstrument->m_iLineIndex, pInstrument->m_iPointIndex, 
// // 				uiFrameNb, uiIPInstrument, pADCLostFrame->m_uiSysTime, pADCDataRecThread);
// 			if (pInstrument->m_olsADCDataSave.size() == pADCDataRecThread->m_pThread->m_pConstVar->m_uiSaveTestDataNum)
// 			{
// 				pInstrument->m_olsADCDataSave.pop_front();
// 			}
// 			pInstrument->m_olsADCDataSave.push_back(iTestData);
// 		}
// 		LeaveCriticalSection(&pADCDataRecThread->m_pLineList->m_oSecLineList);
// 		return;
// 	}
	if (pInstrument->m_uiADCDataActualRecFrameNum > 0)
	{

// 		if (usADCDataFramePointNow > usADCFramePointLimit)
// 		{
// 			LeaveCriticalSection(&pADCDataRecThread->m_pLineList->m_oSecLineList);
// 			EnterCriticalSection(&pADCDataRecThread->m_pADCDataFrame->m_oSecADCDataFrame);
// 			GetFrameInfo(pADCDataRecThread->m_pADCDataFrame->m_cpRcvFrameData, 
// 				pADCDataRecThread->m_pThread->m_pConstVar->m_iRcvFrameSize, &strFrameData);
// 			LeaveCriticalSection(&pADCDataRecThread->m_pADCDataFrame->m_oSecADCDataFrame);
// 			AddMsgToLogOutPutList(pADCDataRecThread->m_pThread->m_pLogOutPut, "ProcADCDataRecFrameOne", 
// 				strFrameData, ErrorType, IDS_ERR_FRAMEPOINT_LIMITOVER);
// 			return;
// 		}
// 		if (usADCDataFramePointNow < pInstrument->m_usADCDataFramePointNow)
// 		{
// 			usADCDataFramePointMove = usADCFramePointLimit - pInstrument->m_usADCDataFramePointNow 
// 				+ usADCDataFramePointNow;
// 		}
// 		else
// 		{
// 			usADCDataFramePointMove = usADCDataFramePointNow - pInstrument->m_usADCDataFramePointNow;
// 		}
// 		//@@@@ 32位本地时间计数能够运行12天，暂不考虑超过12天的情况
// 		if (uiADCDataFrameSysTimeNow < pInstrument->m_uiADCDataFrameSysTimeNow)
// 		{
// 			LeaveCriticalSection(&pADCDataRecThread->m_pLineList->m_oSecLineList);
// 			EnterCriticalSection(&pADCDataRecThread->m_pADCDataFrame->m_oSecADCDataFrame);
// 			GetFrameInfo(pADCDataRecThread->m_pADCDataFrame->m_cpRcvFrameData,
// 				pADCDataRecThread->m_pThread->m_pConstVar->m_iRcvFrameSize, &strFrameData);
// 			LeaveCriticalSection(&pADCDataRecThread->m_pADCDataFrame->m_oSecADCDataFrame);
// 			AddMsgToLogOutPutList(pADCDataRecThread->m_pThread->m_pLogOutPut, "ProcADCDataRecFrameOne", 
// 				strFrameData, ErrorType, IDS_ERR_ADCFRAMESYSTIME_ERROR);
// 			str.Format(_T("当前帧本地时间为%d， 前一帧的本地时间为%d"), uiADCDataFrameSysTimeNow, 
// 				pInstrument->m_uiADCDataFrameSysTimeNow);
// 			strConv = (CStringA)str;
// 			AddMsgToLogOutPutList(pADCDataRecThread->m_pLogOutPutADCFrameTime, "", 
// 				strConv, ErrorType, IDS_ERR_ADCFRAMESYSTIME_ERROR);
// 			AddMsgToLogOutPutList(pADCDataRecThread->m_pThread->m_pLogOutPut, "ProcADCDataRecFrameOne", 
// 				strConv, ErrorType, IDS_ERR_ADCFRAMESYSTIME_ERROR);
// 			return;
// 		}
		if (usADCDataFramePointMove % iADCDataInOneFrameNum != 0)
		{
// 			LeaveCriticalSection(&pADCDataRecThread->m_pLineList->m_oSecLineList);
// 			EnterCriticalSection(&pADCDataRecThread->m_pADCDataFrame->m_oSecADCDataFrame);
// 			GetFrameInfo(pADCDataRecThread->m_pADCDataFrame->m_cpRcvFrameData,
// 				pADCDataRecThread->m_pThread->m_pConstVar->m_iRcvFrameSize, &strFrameData);
// 			LeaveCriticalSection(&pADCDataRecThread->m_pADCDataFrame->m_oSecADCDataFrame);
// 			AddMsgToLogOutPutList(pADCDataRecThread->m_pThread->m_pLogOutPut, "ProcADCDataRecFrameOne", 
// 				strFrameData, ErrorType, IDS_ERR_FRAMEPOINT_ERROR);
// 			str.Format(_T("指针偏移量出错，偏移量差值为%d"), usADCDataFramePointMove);
// 			strConv = (CStringA)str;
// 			AddMsgToLogOutPutList(pADCDataRecThread->m_pLogOutPutADCFrameTime, "", 
// 				strConv, ErrorType, IDS_ERR_FRAMEPOINT_ERROR);
// 			AddMsgToLogOutPutList(pADCDataRecThread->m_pThread->m_pLogOutPut, "ProcADCDataRecFrameOne", 
// 				strConv, ErrorType, IDS_ERR_FRAMEPOINT_ERROR);
			return;
		}
		else
		{
// 			if (uiADCDataFrameSysTimeNow != uiADCDataFrameSysTimeOld)
// 			{
// 				iADCFrameCount++;
// 			}
// 			if (pInstrument->m_uiADCDataActualRecFrameNum == 1)
// 			{
// 				pInstrument->m_iADCDataFrameStartNum = iADCFrameCount - 1 - 1;
// 			}

// 			uiLostFrameNum = usADCDataFramePointMove / iADCDataInOneFrameNum - 1;
// 			if (uiLostFrameNum > 0)
// 			{
// 				// 加入到丢帧索引表
// 				for (unsigned int i=0; i<uiLostFrameNum; i++)
// 				{
// 					m_oADCLostFrameStruct ADCLostFrame;
// 					unsigned int uiIP = pInstrument->m_uiIP;
// 					unsigned short usADCFramePointNb = static_cast<unsigned short>(pInstrument->m_usADCDataFramePointNow 
// 						+ (i + 1) * iADCDataInOneFrameNum);
// 					if (usADCFramePointNb >= usADCFramePointLimit)
// 					{
// 						usADCFramePointNb = usADCFramePointNb - usADCFramePointLimit;
// 					}
// 					ADCLostFrame.m_uiCount = 0;
// 					ADCLostFrame.m_bReturnOk = false;
// // 					ADCLostFrame.m_uiFrameNb = pInstrument->m_uiADCDataShouldRecFrameNum 
// // 						+ pInstrument->m_iADCDataFrameStartNum;
// 					// 根据采样率确定时间差
// 					ADCLostFrame.m_uiSysTime = pInstrument->m_uiADCDataFrameSysTimeNow 
// 						+ (i + 1) * (4000 / pADCDataRecThread->m_iADCSampleRate) * iADCDataInOneFrameNum;
// 					AddToADCFrameLostMap(uiIP, usADCFramePointNb, ADCLostFrame, &pADCDataRecThread->m_pLineList->m_pInstrumentList->m_oADCLostFrameMap);
// 					pInstrument->m_uiADCDataShouldRecFrameNum++;
// 					// 在丢帧的位置写当前帧的内容
// 					AddToADCDataWriteFileList(pInstrument->m_iLineIndex, pInstrument->m_iPointIndex,
// 						ADCLostFrame.m_uiFrameNb, uiIPInstrument, ADCLostFrame.m_uiSysTime, 
// 						pADCDataRecThread);
// 					if (pInstrument->m_olsADCDataSave.size() == pADCDataRecThread->m_pThread->m_pConstVar->m_uiSaveTestDataNum)
// 					{
// 						pInstrument->m_olsADCDataSave.pop_front();
// 					}
// 					pInstrument->m_olsADCDataSave.push_back(iTestData);
// 				}
// 				str.Format(_T("仪器SN = 0x%x，IP = 0x%x，丢失帧数为%d"), pInstrument->m_uiSN, 
// 					pInstrument->m_uiIP, uiLostFrameNum);
// 				strConv = (CStringA)str;
// 				AddMsgToLogOutPutList(pADCDataRecThread->m_pThread->m_pLogOutPut, "ProcADCDataRecFrameOne",
// 					strConv, WarningType);
// 				AddMsgToLogOutPutList(pADCDataRecThread->m_pLogOutPutADCFrameTime, "", 
// 					strConv, WarningType);
// 			}
//			uiFrameNb = pInstrument->m_uiADCDataShouldRecFrameNum + pInstrument->m_iADCDataFrameStartNum;
// 			AddToADCDataWriteFileList(pInstrument->m_iLineIndex, pInstrument->m_iPointIndex, 
// 				uiFrameNb, uiIPInstrument, uiADCDataFrameSysTimeNow, pADCDataRecThread);
// 			if (pInstrument->m_olsADCDataSave.size() == pADCDataRecThread->m_pThread->m_pConstVar->m_uiSaveTestDataNum)
// 			{
// 				pInstrument->m_olsADCDataSave.pop_front();
// 			}
// 			pInstrument->m_olsADCDataSave.push_back(iTestData);
		}
	}
	else
	{
// 		if (uiTBHigh != uiADCDataFrameSysTimeNow)
// 		{
// 			str.Format(_T("仪器SN = 0x%x，IP = 0x%x，第一帧的本地时间 = 0x%x"), pInstrument->m_uiSN, 
// 				pInstrument->m_uiIP, uiADCDataFrameSysTimeNow);
// 			strConv = (CStringA)str;
// 			AddMsgToLogOutPutList(pADCDataRecThread->m_pThread->m_pLogOutPut, "ProcADCDataRecFrameOne",
// 				strConv, ErrorType, IDS_ERR_SAMPLETIME);
// 		}
	}
// 	pInstrument->m_uiADCDataActualRecFrameNum++;
// 	pInstrument->m_uiADCDataShouldRecFrameNum++;
// 	pInstrument->m_usADCDataFramePointNow = usADCDataFramePointNow;
// 	pInstrument->m_uiADCDataFrameSysTimeNow = uiADCDataFrameSysTimeNow;
// 	str.Format(_T("仪器SN = 0x%x，IP = 0x%x；"), pInstrument->m_uiSN, pInstrument->m_uiIP);
// 	strOut += str;
// 	str.Format(_T("接收帧的指针偏移量为 %d，差值为 %d；"), 
// 		pInstrument->m_usADCDataFramePointNow, usADCDataFramePointMove);
// 	strOut += str;
// 	str.Format(_T("本地时间为 %d，差值为%d；"), 
// 		pInstrument->m_uiADCDataFrameSysTimeNow, uiADCDataFrameSysTimeMove);
// 	strOut += str;
//	str.Format(_T("应收帧数为 %d, 起始的帧数为%d"), 
//		pInstrument->m_uiADCDataShouldRecFrameNum, pInstrument->m_iADCDataFrameStartNum);
// 	strOut += str;
// 	strConv = (CStringA)strOut;
// 	AddMsgToLogOutPutList(pADCDataRecThread->m_pLogOutPutADCFrameTime, "", strConv);
// 	LeaveCriticalSection(&pADCDataRecThread->m_pLineList->m_oSecLineList);
//	EnterCriticalSection(&pADCDataRecThread->m_oSecADCDataRecThread);
//	pADCDataRecThread->m_uiADCDataFrameSysTime = uiADCDataFrameSysTimeNow;
//	pADCDataRecThread->m_iADCFrameCount = iADCFrameCount;
//	LeaveCriticalSection(&pADCDataRecThread->m_oSecADCDataRecThread);
}
// 处理ADC数据接收帧
void ProcADCDataRecFrame(m_oADCDataRecThreadStruct* pADCDataRecThread)
{
	ASSERT(pADCDataRecThread != NULL);
	// 帧数量设置为0
	int iFrameCount = 0;
	// 得到首包接收网络端口帧数量
	EnterCriticalSection(&pADCDataRecThread->m_pADCDataFrame->m_oSecADCDataFrame);
	iFrameCount = GetFrameCount(pADCDataRecThread->m_pADCDataFrame->m_oADCDataFrameSocket,
		pADCDataRecThread->m_pThread->m_pConstVar->m_iRcvFrameSize, 
		pADCDataRecThread->m_pThread->m_pLogOutPut);
	LeaveCriticalSection(&pADCDataRecThread->m_pADCDataFrame->m_oSecADCDataFrame);
	// 判断帧数量是否大于0
	if(iFrameCount > 0)
	{
		// 循环处理每1帧
		for(int i = 0; i < iFrameCount; i++)
		{
			EnterCriticalSection(&pADCDataRecThread->m_pADCDataFrame->m_oSecADCDataFrame);
			// 得到帧数据
			if (false == GetFrameData(pADCDataRecThread->m_pADCDataFrame->m_oADCDataFrameSocket,
				pADCDataRecThread->m_pADCDataFrame->m_cpRcvFrameData, 
				pADCDataRecThread->m_pThread->m_pConstVar->m_iRcvFrameSize, 
				pADCDataRecThread->m_pThread->m_pLogOutPut))
			{
				LeaveCriticalSection(&pADCDataRecThread->m_pADCDataFrame->m_oSecADCDataFrame);
				continue;
			}
			LeaveCriticalSection(&pADCDataRecThread->m_pADCDataFrame->m_oSecADCDataFrame);
			if (false == ParseInstrADCDataRecFrame(pADCDataRecThread->m_pADCDataFrame, 
					pADCDataRecThread->m_pThread->m_pConstVar, pADCDataRecThread->m_pThread->m_pLogOutPut))
			{
				AddMsgToLogOutPutList(pADCDataRecThread->m_pThread->m_pLogOutPut, "ParseInstrumentADCDataRecFrame",
					"", ErrorType, IDS_ERR_PARSE_ADCDATARECFRAME);
				continue;
			}
			// 处理单个ADC数据帧
			ProcADCDataRecFrameOne(pADCDataRecThread);
		}
	}
}
// 处理ADC数据重发
void ProcADCRetransmission(m_oADCDataRecThreadStruct* pADCDataRecThread)
{
	ASSERT(pADCDataRecThread != NULL);
	map<m_oADCLostFrameKeyStruct, m_oADCLostFrameStruct> ::iterator iter;
	m_oADCLostFrameStruct* pLostFrame = NULL;
	CString str = _T("");
	string strConv = "";
	EnterCriticalSection(&pADCDataRecThread->m_pLineList->m_oSecLineList);
	for (iter = pADCDataRecThread->m_pLineList->m_pInstrumentList->m_oADCLostFrameMap.begin(); 
		iter != pADCDataRecThread->m_pLineList->m_pInstrumentList->m_oADCLostFrameMap.end();)
	{
		pLostFrame = &iter->second;
		pLostFrame->m_uiCount++;

		// 重发次数小于指定次数且没有收到重发帧应答
		if ((pLostFrame->m_uiCount < 4)
			&& (pLostFrame->m_bReturnOk == false))
		{
			// 生成ADC数据重发帧
			MakeInstrADCDataFrame(pADCDataRecThread->m_pADCDataFrame, 
				pADCDataRecThread->m_pThread->m_pConstVar, iter->first.m_uiIP, iter->first.m_usADCFramePointNb,
				pADCDataRecThread->m_pThread->m_pLogOutPut);
			str.Format(_T("向仪器IP = 0x%x的仪器发送ADC数据重发帧，重发的指针偏移量 = %d"), iter->first.m_uiIP,
				iter->first.m_usADCFramePointNb);
			strConv = (CStringA)str;
			AddMsgToLogOutPutList(pADCDataRecThread->m_pThread->m_pLogOutPut, "ProcADCRetransmission", 
				strConv);
			iter++;
		}
		// 重发次数大于指定次数则从索引中删除
		else if (pLostFrame->m_uiCount > 6)
		{
			// 没有收到重发帧应答
			if (pLostFrame->m_bReturnOk == false)
			{
				// 没有收到重发帧
				str.Format(_T("仪器IP = 0x%x的仪器没有收到ADC数据重发帧应答，重发的指针偏移量 = %d"), 
					iter->first.m_uiIP, iter->first.m_usADCFramePointNb);
				strConv = (CStringA)str;
				AddMsgToLogOutPutList(pADCDataRecThread->m_pThread->m_pLogOutPut, "ProcADCRetransmission", 
					strConv);
			}
			pADCDataRecThread->m_pLineList->m_pInstrumentList->m_oADCLostFrameMap.erase(iter++);
		}
		else
		{
			iter++;
		}
	}
	LeaveCriticalSection(&pADCDataRecThread->m_pLineList->m_oSecLineList);
}
// 线程函数
DWORD WINAPI RunADCDataRecThread(m_oADCDataRecThreadStruct* pADCDataRecThread)
{
	ASSERT(pADCDataRecThread != NULL);
	bool bClose = false;
	bool bWork = false;
	while(true)
	{
		EnterCriticalSection(&pADCDataRecThread->m_oSecADCDataRecThread);
		bClose = pADCDataRecThread->m_pThread->m_bClose;
		bWork = pADCDataRecThread->m_pThread->m_bWork;
		LeaveCriticalSection(&pADCDataRecThread->m_oSecADCDataRecThread);
		if (bClose == true)
		{
			break;
		}
		if (bWork == true)
		{
			// 处理ADC数据接收帧
			ProcADCDataRecFrame(pADCDataRecThread);
			// 处理ADC数据重发
			ProcADCRetransmission(pADCDataRecThread);
		}
		EnterCriticalSection(&pADCDataRecThread->m_oSecADCDataRecThread);
		bClose = pADCDataRecThread->m_pThread->m_bClose;
		LeaveCriticalSection(&pADCDataRecThread->m_oSecADCDataRecThread);
		if (bClose == true)
		{
			break;
		}
		WaitADCDataRecThread(pADCDataRecThread);
	}
	// 设置事件对象为有信号状态,释放等待线程后将事件置为无信号
	EnterCriticalSection(&pADCDataRecThread->m_oSecADCDataRecThread);
	SetEvent(pADCDataRecThread->m_pThread->m_hThreadClose);
	LeaveCriticalSection(&pADCDataRecThread->m_oSecADCDataRecThread);
	return 1;
}
// 初始化ADC数据接收线程
bool OnInitADCDataRecThread(m_oADCDataRecThreadStruct* pADCDataRecThread, 
	m_oLogOutPutStruct* pLogOutPut, m_oConstVarStruct* pConstVar)
{
	ASSERT(pADCDataRecThread != NULL);
	EnterCriticalSection(&pADCDataRecThread->m_oSecADCDataRecThread);
	if (false == OnInitThread(pADCDataRecThread->m_pThread, pLogOutPut, pConstVar))
	{
		LeaveCriticalSection(&pADCDataRecThread->m_oSecADCDataRecThread);
		return false;
	}
//	pADCDataRecThread->m_uiADCDataFrameSysTime = 0;
//	pADCDataRecThread->m_iADCFrameCount = 0;
	pADCDataRecThread->m_iADCSampleRate = 1000;	// 默认为1K采样率
	// 设置事件对象为无信号状态
	ResetEvent(pADCDataRecThread->m_pThread->m_hThreadClose);
	// 创建线程
	pADCDataRecThread->m_pThread->m_hThread = CreateThread((LPSECURITY_ATTRIBUTES)NULL, 
		0,
		(LPTHREAD_START_ROUTINE)RunADCDataRecThread,
		pADCDataRecThread, 
		0, 
		&pADCDataRecThread->m_pThread->m_dwThreadID);
	if (pADCDataRecThread->m_pThread->m_hThread == NULL)
	{
		LeaveCriticalSection(&pADCDataRecThread->m_oSecADCDataRecThread);
		AddMsgToLogOutPutList(pADCDataRecThread->m_pThread->m_pLogOutPut, "OnInitADCDataRecThread", 
			"pADCDataRecThread->m_pThread->m_hThread", ErrorType, IDS_ERR_CREATE_THREAD);
		return false;
	}
	LeaveCriticalSection(&pADCDataRecThread->m_oSecADCDataRecThread);
	AddMsgToLogOutPutList(pADCDataRecThread->m_pThread->m_pLogOutPut, "OnInitADCDataRecThread", 
		"ADC数据接收线程创建成功");
	return true;
}
// 初始化ADC数据接收线程
bool OnInit_ADCDataRecThread(m_oEnvironmentStruct* pEnv)
{
	ASSERT(pEnv != NULL);
	pEnv->m_pADCDataRecThread->m_pLogOutPutADCFrameTime = pEnv->m_pLogOutPutADCFrameTime;
	pEnv->m_pADCDataRecThread->m_pADCDataBufArray = pEnv->m_pADCDataBufArray;
	pEnv->m_pADCDataRecThread->m_pADCDataFrame = pEnv->m_pADCDataFrame;
	pEnv->m_pADCDataRecThread->m_pLineList = pEnv->m_pLineList;
	return OnInitADCDataRecThread(pEnv->m_pADCDataRecThread, pEnv->m_pLogOutPutOpt, pEnv->m_pConstVar);
}
// 关闭ADC数据接收线程
bool OnCloseADCDataRecThread(m_oADCDataRecThreadStruct* pADCDataRecThread)
{
	ASSERT(pADCDataRecThread != NULL);
	EnterCriticalSection(&pADCDataRecThread->m_oSecADCDataRecThread);
	if (false == OnCloseThread(pADCDataRecThread->m_pThread))
	{
		LeaveCriticalSection(&pADCDataRecThread->m_oSecADCDataRecThread);
		AddMsgToLogOutPutList(pADCDataRecThread->m_pThread->m_pLogOutPut, "OnCloseADCDataRecThread", 
			"ADC数据接收线程强制关闭", WarningType);
		return false;
	}
	LeaveCriticalSection(&pADCDataRecThread->m_oSecADCDataRecThread);
	AddMsgToLogOutPutList(pADCDataRecThread->m_pThread->m_pLogOutPut, "OnCloseADCDataRecThread", 
		"ADC数据接收线程成功关闭");
	return true;
}
// 释放ADC数据接收线程
void OnFreeADCDataRecThread(m_oADCDataRecThreadStruct* pADCDataRecThread)
{
	ASSERT(pADCDataRecThread != NULL);
	if (pADCDataRecThread->m_pThread != NULL)
	{
		delete pADCDataRecThread->m_pThread;
		pADCDataRecThread->m_pThread = NULL;
	}
	DeleteCriticalSection(&pADCDataRecThread->m_oSecADCDataRecThread);
	delete pADCDataRecThread;
	pADCDataRecThread = NULL;
}