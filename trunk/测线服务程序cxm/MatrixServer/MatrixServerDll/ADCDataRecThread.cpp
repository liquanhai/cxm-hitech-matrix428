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
// �������ݻص�����
// void GetProSampleDateCallBack(m_oADCDataRecThreadStruct* pADCDataRecThread, ProSampleDateCallBack pCallBack)
// {
// 	ASSERT(pADCDataRecThread != NULL);
// 	EnterCriticalSection(&pADCDataRecThread->m_oSecADCDataRecThread);
// 	pADCDataRecThread->m_oProSampleDataCallBack = pCallBack;
// 	LeaveCriticalSection(&pADCDataRecThread->m_oSecADCDataRecThread);
// }
// ��ADC���ݼ��뵽���񻺳���
void AddToADCDataBuf(unsigned int uiIP, unsigned int uiTime, unsigned int uiPointTime, char* pBuf, unsigned int uiLen, 
	m_oOptTaskArrayStruct* pOptTaskArray, m_oADCDataBufArrayStruct* pADCDataSaveBufArray, m_oConstVarStruct* pConstVar)
{
	ASSERT(pBuf != NULL);
	ASSERT(pOptTaskArray != NULL);
	ASSERT(pADCDataSaveBufArray != NULL);
	ASSERT(pConstVar != NULL);
	hash_map<unsigned int, m_oOptTaskStruct*>::iterator iter;
	m_oADCDataBufStruct* pADCDataBuf = NULL;
	m_oOptInstrumentStruct* pOptInstr = NULL;
	unsigned int uiPointNum = 0;
	unsigned int uiPos = 0;
	unsigned int uiMov = 0;
	EnterCriticalSection(&pOptTaskArray->m_oSecOptTaskArray);
	EnterCriticalSection(&pADCDataSaveBufArray->m_oSecADCDataBufArray);
	for (iter = pOptTaskArray->m_oOptTaskWorkMap.begin(); iter != pOptTaskArray->m_oOptTaskWorkMap.end(); iter++)
	{
		if (FALSE == IfIndexExistInOptTaskIPMap(uiIP, &iter->second->m_oIPMap))
		{
			continue;
		}
		if ((iter->second->m_uiTB > (uiTime + uiPointTime * pConstVar->m_iADCDataInOneFrameNum)) || (uiTime > iter->second->m_uiTS))
		{
			continue;
		}
		else
		{
			if (iter->second->m_bSaveBuf == false)
			{
				// �õ�һ�����е�
				pADCDataBuf = GetFreeADCDataBuf(pADCDataSaveBufArray);
				if (pADCDataBuf == NULL)
				{
					// @@@��������������
					continue;
				}
				iter->second->m_bSaveBuf = true;
				iter->second->m_uiSaveBufNo = pADCDataBuf->m_uiIndex;
				// �����ݴ洢����������������
				AddToADCDataBufMap(pADCDataBuf->m_uiIndex, pADCDataBuf, &pADCDataSaveBufArray->m_oADCDataToWriteMap);
			}
			pADCDataBuf = GetADCDataBufFromMap(pADCDataBuf->m_uiIndex, &pADCDataSaveBufArray->m_oADCDataToWriteMap);
			pOptInstr = GetOptTaskFromIPMap(uiIP,  &iter->second->m_oIPMap);
			uiPointNum = (iter->second->m_uiTS - iter->second->m_uiTB) / uiPointTime;
			uiPos = pOptInstr->m_uiLocation * uiPointNum * pConstVar->m_iADCDataSize3B;
			if (uiTime < iter->second->m_uiTB)
			{
				uiMov = (iter->second->m_uiTB - uiTime) / uiPointTime * pConstVar->m_iADCDataSize3B;
				memcpy(&pADCDataBuf->m_pADCDataBuf[uiPos], &pBuf[uiMov], (uiLen - uiMov) * sizeof(char));
			}
			else if (iter->second->m_uiTS < (uiTime + uiPointTime * pConstVar->m_iADCDataInOneFrameNum))
			{
				uiMov = (iter->second->m_uiTS - uiTime) / uiPointTime * pConstVar->m_iADCDataSize3B;
				uiPos = uiPos + uiPointNum * pConstVar->m_iADCDataSize3B - uiMov;
				memcpy(&pADCDataBuf->m_pADCDataBuf[uiPos], &pBuf[uiMov], (uiLen - uiMov) * sizeof(char));
			}
			else
			{
				uiMov = (uiTime - iter->second->m_uiTB) / uiPointTime * pConstVar->m_iADCDataSize3B;
				uiPos = uiPos + uiMov - uiLen;
				memcpy(&pADCDataBuf->m_pADCDataBuf[uiPos], pBuf, uiLen * sizeof(char));
			}
		}
	}
	LeaveCriticalSection(&pADCDataSaveBufArray->m_oSecADCDataBufArray);
	LeaveCriticalSection(&pOptTaskArray->m_oSecOptTaskArray);
}
// ����û�н��յ����ݵĲɼ�վ
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
	unsigned int uiFrameTime = 0;
	unsigned int uiPointTime = 0;
	iADCDataSize3B = pADCDataRecThread->m_pThread->m_pConstVar->m_iADCDataSize3B;
	iADCDataInOneFrameNum = pADCDataRecThread->m_pThread->m_pConstVar->m_iADCDataInOneFrameNum;
	usADCFramePointLimit = pADCDataRecThread->m_pThread->m_pConstVar->m_usADCFramePointLimit;
	uiADCSaveBufSize = iADCDataInOneFrameNum * iADCDataSize3B;
	uiPointTime = 4000 / pADCDataRecThread->m_iADCSampleRate;
	uiFrameTime = uiPointTime * iADCDataInOneFrameNum;
	EnterCriticalSection(&pADCDataRecThread->m_pADCDataFrame->m_oSecADCDataFrame);
	// �õ�����IP
	uiIPInstrument = pADCDataRecThread->m_pADCDataFrame->m_pCommandStructReturn->m_uiSrcIP;
	// �õ�ָ��ƫ����
	usADCDataFramePoint = pADCDataRecThread->m_pADCDataFrame->m_pCommandStructReturn->m_usADCDataPoint;
	// �õ�����ϵͳʱ��
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
	UpdataLocalSysTime(uiADCDataFrameSysTime, pADCDataRecThread->m_pLineList);
	EnterCriticalSection(&pADCDataRecThread->m_pLineList->m_oSecLineList);
	if (FALSE == IfIndexExistInMap(uiIPInstrument, &pADCDataRecThread->m_pLineList->m_pInstrumentList->m_oOptInstrumentMap))
	{
		LeaveCriticalSection(&pADCDataRecThread->m_pLineList->m_oSecLineList);
		return;
	}
	pInstrument = GetInstrumentFromMap(uiIPInstrument, &pADCDataRecThread->m_pLineList->m_pInstrumentList->m_oOptInstrumentMap);
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
			AddToADCDataBuf(pInstrument->m_uiIP, pADCLostFrame->m_uiSysTime, uiPointTime,
				pADCDataBuf, uiADCSaveBufSize, pADCDataRecThread->m_pOptTaskArray, pADCDataRecThread->m_pADCDataBufArray,
				pADCDataRecThread->m_pThread->m_pConstVar);
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
			str.Format(_T("����SN = 0x%x��IP = 0x%x����һ֡�ı���ʱ�� = 0x%x, TBʱ�� = 0x%x"), pInstrument->m_uiSN, 
				pInstrument->m_uiIP, uiADCDataFrameSysTime, pInstrument->m_uiTBHigh);
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
		str.Format(_T("��ǰ֡����ʱ��Ϊ%d�� ǰһ֡�ı���ʱ��Ϊ%d"), pInstrument->m_uiADCDataFrameSysTimeNow, 
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
					AddToADCDataBuf(pInstrument->m_uiIP, ADCLostFrame.m_uiSysTime, uiPointTime,
						pADCDataBuf, uiADCSaveBufSize, pADCDataRecThread->m_pOptTaskArray, pADCDataRecThread->m_pADCDataBufArray,
						pADCDataRecThread->m_pThread->m_pConstVar);
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
		AddToADCDataBuf(pInstrument->m_uiIP, pInstrument->m_uiADCDataFrameSysTimeNow, uiPointTime,
			pADCDataBuf, uiADCSaveBufSize, pADCDataRecThread->m_pOptTaskArray, pADCDataRecThread->m_pADCDataBufArray,
			pADCDataRecThread->m_pThread->m_pConstVar);
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
	str.Format(_T("����ʱ��Ϊ %d����ֵΪ%d��"), pInstrument->m_uiADCDataFrameSysTimeNow, 
		pInstrument->m_uiADCDataFrameSysTimeNow - pInstrument->m_uiADCDataFrameSysTimeOld);
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