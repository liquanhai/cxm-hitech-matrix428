#include "stdafx.h"
#include "MatrixServerDll.h"

// ����ADC���ݽ����߳�
m_oADCDataRecThreadStruct* OnCreateADCDataRecThread(void)
{
	m_oADCDataRecThreadStruct* pADCDataRecThread = NULL;
	pADCDataRecThread = new m_oADCDataRecThreadStruct;
	pADCDataRecThread->m_pThread = new m_oThreadStruct;
	pADCDataRecThread->m_pLogOutPutADCFrameTime = NULL;
	pADCDataRecThread->m_pADCDataBufArray = NULL;
	pADCDataRecThread->m_pOptTaskArray = NULL;
	pADCDataRecThread->m_pADCDataFrame = NULL;
	pADCDataRecThread->m_pLineList = NULL;
	InitializeCriticalSection(&pADCDataRecThread->m_oSecADCDataRecThread);
	return pADCDataRecThread;
}
// �̵߳ȴ�����
void WaitADCDataRecThread(m_oADCDataRecThreadStruct* pADCDataRecThread)
{
	ASSERT(pADCDataRecThread != NULL);
	// ��ʼ���ȴ�����Ϊ0
	int iWaitCount = 0;
	bool bClose = false;
	// ѭ��
	while(true)
	{	// ����50����
		Sleep(pADCDataRecThread->m_pThread->m_pConstVar->m_iOneSleepTime);
		// �ȴ�������1
		iWaitCount++;
		EnterCriticalSection(&pADCDataRecThread->m_oSecADCDataRecThread);
		bClose = pADCDataRecThread->m_pThread->m_bClose;
		LeaveCriticalSection(&pADCDataRecThread->m_oSecADCDataRecThread);
		// �ж��Ƿ���Դ��������
		if(bClose == true)
		{
			// ����
			return;
		}
		// �жϵȴ������Ƿ���ڵ������ȴ�����
		if(pADCDataRecThread->m_pThread->m_pConstVar->m_iADCDataRecSleepTimes == iWaitCount)
		{
			// ����
			return;
		}		
	}
}
bool CompareSegdDataHeader(m_oSegdDataHeaderStruct* ptrFirst, m_oSegdDataHeaderStruct* ptrSecond)
{
	return (ptrFirst->m_uiLocation < ptrSecond->m_uiLocation);
}
// �������ݻص�����
// void GetProSampleDateCallBack(m_oADCDataRecThreadStruct* pADCDataRecThread, ProSampleDateCallBack pCallBack)
// {
// 	ASSERT(pADCDataRecThread != NULL);
// 	EnterCriticalSection(&pADCDataRecThread->m_oSecADCDataRecThread);
// 	pADCDataRecThread->m_oProSampleDataCallBack = pCallBack;
// 	LeaveCriticalSection(&pADCDataRecThread->m_oSecADCDataRecThread);
// }
// ��ADC���ݼ��뵽���񻺳���
void AddToADCDataBuf(unsigned int uiIP, unsigned int uiTime, double dPointTime, char* pBuf, 
	unsigned int uiLen, m_oADCDataRecThreadStruct* pADCDataRecThread)
{
	ASSERT(pBuf != NULL);
	ASSERT(pADCDataRecThread != NULL);
	hash_map<unsigned int, m_oOptTaskStruct*>::iterator iter;
	hash_map<unsigned int, m_oOptInstrumentStruct*>::iterator iterOptStr;
	m_oADCDataBufStruct* pADCDataBuf = NULL;
	m_oOptInstrumentStruct* pOptInstr = NULL;
	unsigned int uiPointNum = 0;
	unsigned int uiTS = 0;
	unsigned int uiPos = 0;
	unsigned int uiMov = 0;
	int iADCDataSize3B = pADCDataRecThread->m_pThread->m_pConstVar->m_iADCDataSize3B;
	int iADCDataInOneFrameNum = pADCDataRecThread->m_pThread->m_pConstVar->m_iADCDataInOneFrameNum;
	EnterCriticalSection(&pADCDataRecThread->m_pOptTaskArray->m_oSecOptTaskArray);
	EnterCriticalSection(&pADCDataRecThread->m_pADCDataBufArray->m_oSecADCDataBufArray);
	for (iter = pADCDataRecThread->m_pOptTaskArray->m_oOptTaskWorkMap.begin(); 
		iter != pADCDataRecThread->m_pOptTaskArray->m_oOptTaskWorkMap.end();)
	{
		uiTS = iter->second->m_uiTS;
		if ((FALSE == IfIndexExistInOptTaskIPMap(uiIP, &iter->second->m_oIPMap))
			|| (iter->second->m_uiTB > (uiTime + dPointTime * iADCDataInOneFrameNum)))
		{
			iter++;
			continue;
		}
		if (iter->second->m_bSaveBuf == false)
		{
			// �õ�һ�����е�
			pADCDataBuf = GetFreeADCDataBuf(pADCDataRecThread->m_pADCDataBufArray);
			if (pADCDataBuf == NULL)
			{
				// @@@��������������
				iter++;
				continue;
			}
			iter->second->m_bSaveBuf = true;
			iter->second->m_uiSaveBufNo = pADCDataBuf->m_uiIndex;
			pADCDataBuf->m_uiSampleTime = uiTS - iter->second->m_uiTB;
			pADCDataBuf->m_uiSavePointNum = (uiTS - iter->second->m_uiTB) / dPointTime + 1;
			pADCDataBuf->m_uiOptNo = iter->second->m_uiOptNo;
			pADCDataBuf->m_SaveFilePath = iter->second->m_SaveFilePath;
			pADCDataBuf->m_iSampleRate = iter->second->m_iSampleRate;
			for (iterOptStr = iter->second->m_oIPMap.begin(); iterOptStr != iter->second->m_oIPMap.end(); iterOptStr++)
			{
				m_oSegdDataHeaderStruct* pSegdDataHeader = NULL;
				pSegdDataHeader = new m_oSegdDataHeaderStruct;
				pSegdDataHeader->m_iLineIndex = iterOptStr->second->m_iLineIndex;
				pSegdDataHeader->m_iPointIndex = iterOptStr->second->m_iPointIndex;
				pSegdDataHeader->m_uiLocation = iterOptStr->second->m_uiLocation;
				if (iterOptStr->second->m_bAuxiliary == true)
				{
					pADCDataBuf->m_uiAuxTraceNum++;
				}
				else
				{
					pADCDataBuf->m_uiAcqTraceNum++;
				}
				pADCDataBuf->m_olsSegdDataHeader.push_back(pSegdDataHeader);
			}
			pADCDataBuf->m_olsSegdDataHeader.sort(CompareSegdDataHeader);
			// �����ݴ洢����������������
			AddToADCDataBufMap(pADCDataBuf->m_uiIndex, pADCDataBuf, 
				&pADCDataRecThread->m_pADCDataBufArray->m_oADCDataBufWorkMap);
		}
		pADCDataBuf = GetADCDataBufFromMap(iter->second->m_uiSaveBufNo, 
			&pADCDataRecThread->m_pADCDataBufArray->m_oADCDataBufWorkMap);
		if (pADCDataBuf == NULL)
		{
			iter++;
			continue;
		}
		if (pADCDataBuf->m_bSaveInSegd == true)
		{
			iter++;
			continue;
		}
		uiPointNum = pADCDataBuf->m_uiSavePointNum;
		pOptInstr = GetOptTaskFromIPMap(uiIP,  &iter->second->m_oIPMap);
		if (pOptInstr == NULL)
		{
			iter++;
			continue;
		}
		if (uiTime > uiTS + pADCDataRecThread->m_pThread->m_pConstVar->m_iSEGDCheckFinishTime)
		{
			// ���ݻ��������Ա��浽Segd�ļ�
			pADCDataBuf->m_bSaveInSegd = true;
			// ��ʩ��������뵽�����б�
			AddFreeOptTask(iter->second, pADCDataRecThread->m_pOptTaskArray);
			// ɾ����ʩ������
			pADCDataRecThread->m_pOptTaskArray->m_oOptTaskWorkMap.erase(iter++);
			continue;
		}
		if (uiTime <= uiTS)
		{
			uiPos = pOptInstr->m_uiLocation * uiPointNum * iADCDataSize3B;
			if (uiTime <= iter->second->m_uiTB)
			{
				uiMov = (iter->second->m_uiTB - uiTime) / dPointTime * iADCDataSize3B;
				memcpy(&pADCDataBuf->m_pADCDataBuf[uiPos], &pBuf[uiMov], (uiLen - uiMov) * sizeof(char));
			}
			else if (uiTS <= (uiTime + dPointTime * iADCDataInOneFrameNum))
			{
				uiMov = (uiTS - uiTime) / dPointTime * iADCDataSize3B;
				uiPos = uiPos + uiPointNum * iADCDataSize3B - uiMov;
				memcpy(&pADCDataBuf->m_pADCDataBuf[uiPos], pBuf, uiMov * sizeof(char));
			}
			else
			{
				uiMov = (uiTime - iter->second->m_uiTB) / dPointTime * iADCDataSize3B;
				uiPos = uiPos + uiMov;
				memcpy(&pADCDataBuf->m_pADCDataBuf[uiPos], pBuf, uiLen * sizeof(char));
			}
		}
		iter++;
	}
	LeaveCriticalSection(&pADCDataRecThread->m_pADCDataBufArray->m_oSecADCDataBufArray);
	LeaveCriticalSection(&pADCDataRecThread->m_pOptTaskArray->m_oSecOptTaskArray);
}
// ����û�н��յ����ݵĲɼ�վ
void FindFDUNotRecADCData(m_oADCDataRecThreadStruct* pADCDataRecThread)
{
	hash_map<unsigned int, m_oInstrumentStruct*>::iterator iter;
	CString str = _T("");
	string strConv = "";
	EnterCriticalSection(&pADCDataRecThread->m_pLineList->m_oSecLineList);
	for (iter = pADCDataRecThread->m_pLineList->m_pInstrumentList->m_oIPInstrumentMap.begin();
		iter != pADCDataRecThread->m_pLineList->m_pInstrumentList->m_oIPInstrumentMap.end(); iter++)
	{
		if ((iter->second->m_uiADCDataActualRecFrameNum == 0)
			&& (iter->second->m_iInstrumentType == InstrumentTypeFDU)
			&& (iter->second->m_bCheckADCFrameLate == true))
		{
			str.Format(_T("δ�յ�SN = 0x%x�Ĳɼ�վ��ADC����֡"), iter->second->m_uiSN);
			strConv = (CStringA)str;
			AddMsgToLogOutPutList(pADCDataRecThread->m_pThread->m_pLogOutPut, "", 
				strConv, ErrorType, IDS_ERR_ADCDATANOTREC);
			iter->second->m_bCheckADCFrameLate = false;
		}
	}
	LeaveCriticalSection(&pADCDataRecThread->m_pLineList->m_oSecLineList);
}
// ������ADC����֡
void ProcADCDataRecFrameOne(m_oADCDataRecThreadStruct* pADCDataRecThread)
{
	ASSERT(pADCDataRecThread != NULL);
	unsigned int uiIPInstrument = 0;
	m_oInstrumentStruct* pInstrument = NULL;
	unsigned short usADCDataFramePoint = 0;
	unsigned int uiADCDataFrameSysTimeHigh = 0;
	unsigned short usADCDataFrameSysTimeLow = 0;
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
	unsigned int uiFrameTime = 0;
	double dPointTime = 0.0;
	iADCDataSize3B = pADCDataRecThread->m_pThread->m_pConstVar->m_iADCDataSize3B;
	iADCDataInOneFrameNum = pADCDataRecThread->m_pThread->m_pConstVar->m_iADCDataInOneFrameNum;
	usADCFramePointLimit = pADCDataRecThread->m_pThread->m_pConstVar->m_usADCFramePointLimit;
	uiADCSaveBufSize = iADCDataInOneFrameNum * iADCDataSize3B;
	dPointTime = 1000 / pADCDataRecThread->m_iADCSampleRate;
	uiFrameTime = dPointTime * iADCDataInOneFrameNum;
	EnterCriticalSection(&pADCDataRecThread->m_pADCDataFrame->m_oSecADCDataFrame);
	// �õ�����IP
	uiIPInstrument = pADCDataRecThread->m_pADCDataFrame->m_pCommandStructReturn->m_uiSrcIP;
	// �õ�ָ��ƫ����
	usADCDataFramePoint = pADCDataRecThread->m_pADCDataFrame->m_pCommandStructReturn->m_usADCDataPoint;
	// �õ�����ϵͳʱ��
	uiADCDataFrameSysTimeHigh = pADCDataRecThread->m_pADCDataFrame->m_pCommandStructReturn->m_uiADCSampleSysTimeHigh;
	usADCDataFrameSysTimeLow = pADCDataRecThread->m_pADCDataFrame->m_pCommandStructReturn->m_usADCSampleSysTimeLow;
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
	UpdateLocalSysTime(uiADCDataFrameSysTimeHigh, pADCDataRecThread->m_pLineList);
	EnterCriticalSection(&pADCDataRecThread->m_pLineList->m_oSecLineList);
	if (FALSE == IfIndexExistInMap(uiIPInstrument, &pADCDataRecThread->m_pLineList->m_pInstrumentList->m_oIPInstrumentMap))
	{
		LeaveCriticalSection(&pADCDataRecThread->m_pLineList->m_oSecLineList);
		return;
	}
	pInstrument = GetInstrumentFromMap(uiIPInstrument, &pADCDataRecThread->m_pLineList->m_pInstrumentList->m_oIPInstrumentMap);
	if (pInstrument->m_bInUsed == false)
	{
		return;
	}
	// ���������Ĵ��ʱ��
	UpdateInstrActiveTime(pInstrument);
	pInstrument->m_uiADCDataActualRecFrameNum++;
	// �ڶ�֡���������ҵ�
	if (TRUE == IfIndexExistInADCFrameLostMap(uiIPInstrument, usADCDataFramePoint, 
		&pADCDataRecThread->m_pLineList->m_pInstrumentList->m_oADCLostFrameMap))
	{
		str.Format(_T("�յ�SN = 0x%x��IP��ַ = 0x%x ��ADC�����ط�֡��ָ��ƫ���� = %d"), 
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
			// ��ADC���ݼ��뵽���񻺳���
			AddToADCDataBuf(pInstrument->m_uiIP, pADCLostFrame->m_uiSysTime, dPointTime,
				pADCDataBuf, uiADCSaveBufSize, pADCDataRecThread);
		}
		LeaveCriticalSection(&pADCDataRecThread->m_pLineList->m_oSecLineList);
		return;
	}
	pInstrument->m_uiADCDataShouldRecFrameNum++;
	pInstrument->m_usADCDataFramePointOld = pInstrument->m_usADCDataFramePointNow;
	pInstrument->m_uiADCDataFrameSysTimeOld = pInstrument->m_uiADCDataFrameSysTimeNow;
	pInstrument->m_usADCDataFramePointNow = usADCDataFramePoint;
	pInstrument->m_uiADCDataFrameSysTimeNow = uiADCDataFrameSysTimeHigh;
	if (pInstrument->m_uiADCDataActualRecFrameNum == 1)
	{
		if (pInstrument->m_uiTBHigh != uiADCDataFrameSysTimeHigh)
		{
			str.Format(_T("����SN = 0x%x��IP = 0x%x����һ֡�ı���ʱ�� = 0x%x, TBʱ�� = 0x%x"), pInstrument->m_uiSN, 
				pInstrument->m_uiIP, uiADCDataFrameSysTimeHigh, pInstrument->m_uiTBHigh);
			strConv = (CStringA)str;
			AddMsgToLogOutPutList(pADCDataRecThread->m_pThread->m_pLogOutPut, "ProcADCDataRecFrameOne",
				strConv, ErrorType, IDS_ERR_SAMPLETIME);
		}
	}
	// �յ��ڶ�֡���ݼ������վ�Ƿ��յ�����֡
	else if (pInstrument->m_uiADCDataActualRecFrameNum == 2)
	{
		FindFDUNotRecADCData(pADCDataRecThread);
	}
	//@@@@ 32λ����ʱ������ܹ�����12�죬�ݲ����ǳ���12������
	if (pInstrument->m_uiADCDataFrameSysTimeNow <= pInstrument->m_uiADCDataFrameSysTimeOld)
	{
		LeaveCriticalSection(&pADCDataRecThread->m_pLineList->m_oSecLineList);
		EnterCriticalSection(&pADCDataRecThread->m_pADCDataFrame->m_oSecADCDataFrame);
		GetFrameInfo(pADCDataRecThread->m_pADCDataFrame->m_cpRcvFrameData,
			pADCDataRecThread->m_pThread->m_pConstVar->m_iRcvFrameSize, &strFrameData);
		LeaveCriticalSection(&pADCDataRecThread->m_pADCDataFrame->m_oSecADCDataFrame);
		AddMsgToLogOutPutList(pADCDataRecThread->m_pThread->m_pLogOutPut, "ProcADCDataRecFrameOne", 
			strFrameData, ErrorType, IDS_ERR_ADCFRAMESYSTIME_ERROR);
		str.Format(_T("��ǰ֡����ʱ��Ϊ0x%x�� ǰһ֡�ı���ʱ��Ϊ0x%x"), pInstrument->m_uiADCDataFrameSysTimeNow, 
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
		str.Format(_T("ָ��ƫ��������ƫ������ֵΪ%d"), usADCDataFramePointMove);
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
				// ���뵽��֡������
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
					// ���ݲ�����ȷ��ʱ���
					ADCLostFrame.m_uiSysTime = pInstrument->m_uiADCDataFrameSysTimeOld + (i + 1) * uiFrameTime;
					AddToADCFrameLostMap(pInstrument->m_uiIP, usADCFramePointNb, ADCLostFrame, &pADCDataRecThread->m_pLineList->m_pInstrumentList->m_oADCLostFrameMap);
					pInstrument->m_uiADCDataShouldRecFrameNum++;
					// �ڶ�֡��λ��д��ǰ֡������
					AddToADCDataBuf(pInstrument->m_uiIP, ADCLostFrame.m_uiSysTime, dPointTime,
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
				str.Format(_T("����SN = 0x%x��IP = 0x%x����ʧ֡��Ϊ%d"), pInstrument->m_uiSN, 
					pInstrument->m_uiIP, uiLostFrameNum);
				strConv = (CStringA)str;
				AddMsgToLogOutPutList(pADCDataRecThread->m_pThread->m_pLogOutPut, "ProcADCDataRecFrameOne",
					strConv, WarningType);
				AddMsgToLogOutPutList(pADCDataRecThread->m_pLogOutPutADCFrameTime, "", 
					strConv, WarningType);
			}
		}
		// ���浱ǰ֡������
		AddToADCDataBuf(pInstrument->m_uiIP, pInstrument->m_uiADCDataFrameSysTimeNow, dPointTime,
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
	str.Format(_T("����SN = 0x%x��IP = 0x%x��"), pInstrument->m_uiSN, pInstrument->m_uiIP);
	strOut += str;
	str.Format(_T("����֡��ָ��ƫ����Ϊ %d����ֵΪ %d��"), 
		pInstrument->m_usADCDataFramePointNow, usADCDataFramePointMove);
	strOut += str;
	str.Format(_T("����ʱ���λΪ 0x%x������ʱ���λΪ 0x%x����ֵΪ%d��"), pInstrument->m_uiADCDataFrameSysTimeNow, 
		usADCDataFrameSysTimeLow, pInstrument->m_uiADCDataFrameSysTimeNow - pInstrument->m_uiADCDataFrameSysTimeOld);
	strOut += str;
	strConv = (CStringA)strOut;
	AddMsgToLogOutPutList(pADCDataRecThread->m_pLogOutPutADCFrameTime, "", strConv);
	LeaveCriticalSection(&pADCDataRecThread->m_pLineList->m_oSecLineList);
}
// ����ADC���ݽ���֡
void ProcADCDataRecFrame(m_oADCDataRecThreadStruct* pADCDataRecThread)
{
	ASSERT(pADCDataRecThread != NULL);
	// ֡��������Ϊ0
	int iFrameCount = 0;
	// �õ��װ���������˿�֡����
	EnterCriticalSection(&pADCDataRecThread->m_pADCDataFrame->m_oSecADCDataFrame);
	iFrameCount = GetFrameCount(pADCDataRecThread->m_pADCDataFrame->m_oADCDataFrameSocket,
		pADCDataRecThread->m_pThread->m_pConstVar->m_iRcvFrameSize, 
		pADCDataRecThread->m_pThread->m_pLogOutPut);
	LeaveCriticalSection(&pADCDataRecThread->m_pADCDataFrame->m_oSecADCDataFrame);
	// �ж�֡�����Ƿ����0
	if(iFrameCount > 0)
	{
		// ѭ������ÿ1֡
		for(int i = 0; i < iFrameCount; i++)
		{
			EnterCriticalSection(&pADCDataRecThread->m_pADCDataFrame->m_oSecADCDataFrame);
			// �õ�֡����
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
			// ������ADC����֡
			ProcADCDataRecFrameOne(pADCDataRecThread);
		}
	}
}
// ����ADC�����ط�
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

		// �ط�����С��ָ��������û���յ��ط�֡Ӧ��
		if ((pLostFrame->m_uiCount < 4)
			&& (pLostFrame->m_bReturnOk == false))
		{
			// ����ADC�����ط�֡
			MakeInstrADCDataFrame(pADCDataRecThread->m_pADCDataFrame, 
				pADCDataRecThread->m_pThread->m_pConstVar, iter->first.m_uiIP, iter->first.m_usADCFramePointNb,
				pADCDataRecThread->m_pThread->m_pLogOutPut);
			str.Format(_T("������IP = 0x%x����������ADC�����ط�֡���ط���ָ��ƫ���� = %d"), iter->first.m_uiIP,
				iter->first.m_usADCFramePointNb);
			strConv = (CStringA)str;
			AddMsgToLogOutPutList(pADCDataRecThread->m_pThread->m_pLogOutPut, "ProcADCRetransmission", 
				strConv);
			iter++;
		}
		// �ط���������ָ���������������ɾ��
		else if (pLostFrame->m_uiCount > 6)
		{
			// û���յ��ط�֡Ӧ��
			if (pLostFrame->m_bReturnOk == false)
			{
				// û���յ��ط�֡
				str.Format(_T("����IP = 0x%x������û���յ�ADC�����ط�֡Ӧ���ط���ָ��ƫ���� = %d"), 
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
// �̺߳���
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
			// ����ADC���ݽ���֡
			ProcADCDataRecFrame(pADCDataRecThread);
			// ����ADC�����ط�
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
	// �����¼�����Ϊ���ź�״̬,�ͷŵȴ��̺߳��¼���Ϊ���ź�
	EnterCriticalSection(&pADCDataRecThread->m_oSecADCDataRecThread);
	SetEvent(pADCDataRecThread->m_pThread->m_hThreadClose);
	LeaveCriticalSection(&pADCDataRecThread->m_oSecADCDataRecThread);
	return 1;
}
// ��ʼ��ADC���ݽ����߳�
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
	pADCDataRecThread->m_iADCSampleRate = 1000;	// Ĭ��Ϊ1K������
	// �����¼�����Ϊ���ź�״̬
	ResetEvent(pADCDataRecThread->m_pThread->m_hThreadClose);
	// �����߳�
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
		"ADC���ݽ����̴߳����ɹ�");
	return true;
}
// ��ʼ��ADC���ݽ����߳�
bool OnInit_ADCDataRecThread(m_oEnvironmentStruct* pEnv)
{
	ASSERT(pEnv != NULL);
	pEnv->m_pADCDataRecThread->m_pLogOutPutADCFrameTime = pEnv->m_pLogOutPutADCFrameTime;
	pEnv->m_pADCDataRecThread->m_pADCDataBufArray = pEnv->m_pADCDataBufArray;
	pEnv->m_pADCDataRecThread->m_pOptTaskArray = pEnv->m_pOptTaskArray;
	pEnv->m_pADCDataRecThread->m_pADCDataFrame = pEnv->m_pADCDataFrame;
	pEnv->m_pADCDataRecThread->m_pLineList = pEnv->m_pLineList;
	return OnInitADCDataRecThread(pEnv->m_pADCDataRecThread, pEnv->m_pLogOutPutOpt, pEnv->m_pConstVar);
}
// �ر�ADC���ݽ����߳�
bool OnCloseADCDataRecThread(m_oADCDataRecThreadStruct* pADCDataRecThread)
{
	ASSERT(pADCDataRecThread != NULL);
	EnterCriticalSection(&pADCDataRecThread->m_oSecADCDataRecThread);
	if (false == OnCloseThread(pADCDataRecThread->m_pThread))
	{
		LeaveCriticalSection(&pADCDataRecThread->m_oSecADCDataRecThread);
		AddMsgToLogOutPutList(pADCDataRecThread->m_pThread->m_pLogOutPut, "OnCloseADCDataRecThread", 
			"ADC���ݽ����߳�ǿ�ƹر�", WarningType);
		return false;
	}
	LeaveCriticalSection(&pADCDataRecThread->m_oSecADCDataRecThread);
	AddMsgToLogOutPutList(pADCDataRecThread->m_pThread->m_pLogOutPut, "OnCloseADCDataRecThread", 
		"ADC���ݽ����̳߳ɹ��ر�");
	return true;
}
// �ͷ�ADC���ݽ����߳�
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