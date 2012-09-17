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
	pADCDataRecThread->m_pADCDataFrame = NULL;
	pADCDataRecThread->m_pLineList = NULL;
	InitializeCriticalSection(&pADCDataRecThread->m_oSecADCDataRecThread);
	return pADCDataRecThread;
}
// �̵߳ȴ�����
void WaitADCDataRecThread(m_oADCDataRecThreadStruct* pADCDataRecThread)
{
	if (pADCDataRecThread == NULL)
	{
		return;
	}
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
void GetProSampleDateCallBack(m_oADCDataRecThreadStruct* pADCDataRecThread, ProSampleDateCallBack pCallBack)
{
	if (pADCDataRecThread == NULL)
	{
		return;
	}
	EnterCriticalSection(&pADCDataRecThread->m_oSecADCDataRecThread);
	pADCDataRecThread->m_oProSampleDataCallBack = pCallBack;
	LeaveCriticalSection(&pADCDataRecThread->m_oSecADCDataRecThread);
}
// ��ADC���ݼ��뵽�����б�
void AddToADCDataWriteFileList(int iLineIndex, int iPointIndex, unsigned int uiFrameNb,
	unsigned int uiSN, unsigned int uiSysTime, m_oADCDataRecThreadStruct* pADCDataRecThread)
{
	if (pADCDataRecThread == NULL)
	{
		return;
	}
	m_oADCDataBufStruct* pADCDataBuf = NULL;
	pADCDataBuf = GetFreeADCDataBuf(pADCDataRecThread->m_pADCDataBufArray);
	pADCDataBuf->m_uiFrameNb = uiFrameNb;
	pADCDataBuf->m_uiSN = uiSN;
	pADCDataBuf->m_uiSysTime = uiSysTime;
	EnterCriticalSection(&pADCDataRecThread->m_pADCDataFrame->m_oSecADCDataFrame);
	memcpy(pADCDataBuf->m_pADCDataBuf, pADCDataRecThread->m_pADCDataFrame->m_pCommandStructReturn->m_pADCData,
		pADCDataRecThread->m_pThread->m_pConstVar->m_iADCDataInOneFrameNum * sizeof(int));
	// ADC���ݴ���Ļص�����
	(*pADCDataRecThread->m_oProSampleDataCallBack)(iLineIndex, iPointIndex, 
		pADCDataRecThread->m_pADCDataFrame->m_pCommandStructReturn->m_pADCData,
		pADCDataRecThread->m_pThread->m_pConstVar->m_iADCDataInOneFrameNum,
		uiSN);
	LeaveCriticalSection(&pADCDataRecThread->m_pADCDataFrame->m_oSecADCDataFrame);
	EnterCriticalSection(&pADCDataRecThread->m_pADCDataBufArray->m_oSecADCDataBufArray);
	pADCDataRecThread->m_pADCDataBufArray->m_olsADCDataToWrite.push_back(pADCDataBuf);
	LeaveCriticalSection(&pADCDataRecThread->m_pADCDataBufArray->m_oSecADCDataBufArray);
}
// ����û�н��յ����ݵĲɼ�վ
BOOL FindFDUNotRecADCData(m_oADCDataRecThreadStruct* pADCDataRecThread)
{
	hash_map<unsigned int, m_oInstrumentStruct*>::iterator iter;
	CString str = _T("");
	string strConv = "";
	BOOL bReturn = FALSE;
	EnterCriticalSection(&pADCDataRecThread->m_pLineList->m_oSecLineList);
	for (iter = pADCDataRecThread->m_pLineList->m_pInstrumentList->m_oIPInstrumentMap.begin();
		iter != pADCDataRecThread->m_pLineList->m_pInstrumentList->m_oIPInstrumentMap.end(); iter++)
	{
		if ((iter->second->m_uiADCDataActualRecFrameNum == 0)
			&& (iter->second->m_iInstrumentType == pADCDataRecThread->m_pThread->m_pConstVar->m_iInstrumentTypeFDU))
		{
			str.Format(_T("δ�յ�SN = 0x%x�Ĳɼ�վ��ADC����֡"), iter->second->m_uiSN);
			strConv = (CStringA)str;
			AddMsgToLogOutPutList(pADCDataRecThread->m_pThread->m_pLogOutPut, "", 
				strConv, ErrorType, IDS_ERR_ADCDATANOTREC);
			bReturn = TRUE;
		}
	}
	LeaveCriticalSection(&pADCDataRecThread->m_pLineList->m_oSecLineList);
	return bReturn;
}
// ������ADC����֡
void ProcADCDataRecFrameOne(m_oADCDataRecThreadStruct* pADCDataRecThread)
{
	if (pADCDataRecThread == NULL)
	{
		return;
	}
	unsigned int uiIPInstrument = 0;
	m_oInstrumentStruct* pInstrument = NULL;
	CString str = _T("");
	CString strOut = _T("");
	string strFrameData = "";
	string strConv = "";
	unsigned short usADCDataFramePointNow = 0;
	unsigned int uiADCDataFramePointMove = 0;
	unsigned int uiADCDataFrameSysTimeNow = 0;
	unsigned int uiADCDataFrameSysTimeOld = 0;
	int iADCFrameCount = 0;
	unsigned int uiADCDataFrameSysTimeMove = 0;
	unsigned int uiLostFrameNum = 0;
	bool bCheckFDUADCRec = false;
	int iADCDataInOneFrameNum = 0;
	int iADCFrameSaveInOneFileNum = 0;
	unsigned short usADCFramePointLimit = 0;
	unsigned int uiTBHigh = 0;
	ADCLostFrame_Struct* pADCLostFrame = NULL;
	// ֡���
	unsigned int uiFrameNb = 0;
	// ��������
	int iTestData = 0;

	iADCDataInOneFrameNum = pADCDataRecThread->m_pThread->m_pConstVar->m_iADCDataInOneFrameNum;
	usADCFramePointLimit = pADCDataRecThread->m_pThread->m_pConstVar->m_usADCFramePointLimit;
	iADCFrameSaveInOneFileNum = pADCDataRecThread->m_pThread->m_pConstVar->m_iADCFrameSaveInOneFileNum;

	EnterCriticalSection(&pADCDataRecThread->m_oSecADCDataRecThread);
	uiADCDataFrameSysTimeOld = pADCDataRecThread->m_uiADCDataFrameSysTime;
	iADCFrameCount = pADCDataRecThread->m_iADCFrameCount;
	bCheckFDUADCRec = pADCDataRecThread->m_bCheckFDUADCRec;
	LeaveCriticalSection(&pADCDataRecThread->m_oSecADCDataRecThread);

	EnterCriticalSection(&pADCDataRecThread->m_pADCDataFrame->m_oSecADCDataFrame);
	// �õ�����IP
	uiIPInstrument = pADCDataRecThread->m_pADCDataFrame->m_pCommandStructReturn->m_uiSrcIP;
	// �õ�ָ��ƫ����
	usADCDataFramePointNow = pADCDataRecThread->m_pADCDataFrame->m_pCommandStructReturn->m_usADCDataPoint;
	// �õ�����ϵͳʱ��
	uiADCDataFrameSysTimeNow = pADCDataRecThread->m_pADCDataFrame->m_pCommandStructReturn->m_uiADCSampleSysTime;
	// ��������
	iTestData = pADCDataRecThread->m_pADCDataFrame->m_pCommandStructReturn->m_pADCData[0];
	LeaveCriticalSection(&pADCDataRecThread->m_pADCDataFrame->m_oSecADCDataFrame);

	EnterCriticalSection(&pADCDataRecThread->m_pLineList->m_oSecLineList);
	uiTBHigh = pADCDataRecThread->m_pLineList->m_uiTBHigh;
	// ����������������
	if (FALSE == IfIndexExistInMap(uiIPInstrument, &pADCDataRecThread->m_pLineList->m_pInstrumentList->m_oIPInstrumentMap))
	{
		LeaveCriticalSection(&pADCDataRecThread->m_pLineList->m_oSecLineList);
		str.Format(_T("�յ�IP��ַ = 0x%x��ADC����֡"), uiIPInstrument);
		strConv = (CStringA)str;
		AddMsgToLogOutPutList(pADCDataRecThread->m_pThread->m_pLogOutPut, "ProcADCDataRecFrameOne", 
			strConv, ErrorType, IDS_ERR_IPMAP_NOTEXIT);
		return;
	}
	pInstrument = GetInstrumentFromMap(uiIPInstrument, 
		&pADCDataRecThread->m_pLineList->m_pInstrumentList->m_oIPInstrumentMap);
	// �ڶ�֡���������ҵ�
	if (TRUE == IfIndexExistInADCFrameLostMap(uiIPInstrument, usADCDataFramePointNow, 
		&pADCDataRecThread->m_pLineList->m_pInstrumentList->m_oADCLostFrameMap))
	{
		str.Format(_T("�յ�SN = 0x%x��IP��ַ = 0x%x��ADC�����ط�֡��ָ��ƫ���� = %d"), 
			pInstrument->m_uiSN, pInstrument->m_uiIP, usADCDataFramePointNow);
		strConv = (CStringA)str;
		AddMsgToLogOutPutList(pADCDataRecThread->m_pThread->m_pLogOutPut, "ProcADCDataRecFrameOne", 
			strConv);

		pADCLostFrame = GetFromADCFrameLostMap(uiIPInstrument, usADCDataFramePointNow, 
			&pADCDataRecThread->m_pLineList->m_pInstrumentList->m_oADCLostFrameMap);
		if (pADCLostFrame->m_bReturnOk == false)
		{
			pInstrument->m_uiADCDataActualRecFrameNum++;
			pInstrument->m_uiADCDataRetransmissionFrameNum++;
			pADCLostFrame->m_bReturnOk = true;
			// ����Ӧ��֡����д���ļ�
			uiFrameNb = pADCLostFrame->m_uiFrameNb;
			AddToADCDataWriteFileList(pInstrument->m_iLineIndex, pInstrument->m_iPointIndex, 
				uiFrameNb, pInstrument->m_uiSN, pADCLostFrame->m_uiSysTime, pADCDataRecThread);
			if (pInstrument->m_olsADCDataSave.size() == pADCDataRecThread->m_pThread->m_pConstVar->m_uiSaveTestDataNum)
			{
				pInstrument->m_olsADCDataSave.pop_front();
			}
			pInstrument->m_olsADCDataSave.push_back(iTestData);
		}
		LeaveCriticalSection(&pADCDataRecThread->m_pLineList->m_oSecLineList);
		return;
	}
	if (pInstrument->m_uiADCDataActualRecFrameNum > 0)
	{
		// �յ��ڶ�֡���ݼ������վ�Ƿ��յ�����֡
		if ((pInstrument->m_uiADCDataActualRecFrameNum == 1)
			&& (bCheckFDUADCRec == true))
		{
			// ��δ�յ����ݵĲɼ�վд�������־
			if (TRUE == FindFDUNotRecADCData(pADCDataRecThread))
			{
				bCheckFDUADCRec = false;
			}
		}
		if (usADCDataFramePointNow > usADCFramePointLimit)
		{
			LeaveCriticalSection(&pADCDataRecThread->m_pLineList->m_oSecLineList);
			EnterCriticalSection(&pADCDataRecThread->m_pADCDataFrame->m_oSecADCDataFrame);
			GetFrameInfo(pADCDataRecThread->m_pADCDataFrame->m_cpRcvFrameData, 
				pADCDataRecThread->m_pThread->m_pConstVar->m_iRcvFrameSize, &strFrameData);
			LeaveCriticalSection(&pADCDataRecThread->m_pADCDataFrame->m_oSecADCDataFrame);
			AddMsgToLogOutPutList(pADCDataRecThread->m_pThread->m_pLogOutPut, "ProcADCDataRecFrameOne", 
				strFrameData, ErrorType, IDS_ERR_FRAMEPOINT_LIMITOVER);
			return;
		}
		if (usADCDataFramePointNow < pInstrument->m_usADCDataFramePoint)
		{
			uiADCDataFramePointMove = usADCFramePointLimit - pInstrument->m_usADCDataFramePoint 
				+ usADCDataFramePointNow;
		}
		else
		{
			uiADCDataFramePointMove = usADCDataFramePointNow - pInstrument->m_usADCDataFramePoint;
		}

		if (uiADCDataFrameSysTimeNow < pInstrument->m_uiADCDataFrameSysTime)
		{
			uiADCDataFrameSysTimeMove = 0xffffffff - pInstrument->m_uiADCDataFrameSysTime 
				+ uiADCDataFrameSysTimeNow;
		}
		else
		{
			uiADCDataFrameSysTimeMove = uiADCDataFrameSysTimeNow - pInstrument->m_uiADCDataFrameSysTime;
		}
		if (uiADCDataFramePointMove % iADCDataInOneFrameNum != 0)
		{
			LeaveCriticalSection(&pADCDataRecThread->m_pLineList->m_oSecLineList);
			EnterCriticalSection(&pADCDataRecThread->m_pADCDataFrame->m_oSecADCDataFrame);
			GetFrameInfo(pADCDataRecThread->m_pADCDataFrame->m_cpRcvFrameData,
				pADCDataRecThread->m_pThread->m_pConstVar->m_iRcvFrameSize, &strFrameData);
			LeaveCriticalSection(&pADCDataRecThread->m_pADCDataFrame->m_oSecADCDataFrame);
			AddMsgToLogOutPutList(pADCDataRecThread->m_pThread->m_pLogOutPut, "ProcADCDataRecFrameOne", 
				strFrameData, ErrorType, IDS_ERR_FRAMEPOINT_ERROR);
			str.Format(_T("ָ��ƫ��������ƫ������ֵΪ%d"), uiADCDataFramePointMove);
			strConv = (CStringA)str;
			AddMsgToLogOutPutList(pADCDataRecThread->m_pLogOutPutADCFrameTime, "", 
				strConv, ErrorType, IDS_ERR_FRAMEPOINT_ERROR);
			return;
		}
		else
		{
			if (uiADCDataFrameSysTimeNow != uiADCDataFrameSysTimeOld)
			{
				iADCFrameCount++;
			}
			if (pInstrument->m_uiADCDataActualRecFrameNum == 1)
			{
				pInstrument->m_iADCDataFrameStartNum = iADCFrameCount - 1 - 1;
			}

			uiLostFrameNum = uiADCDataFramePointMove / iADCDataInOneFrameNum - 1;
			if (uiLostFrameNum > 0)
			{
				// ���뵽��֡������
				for (unsigned int i=0; i<uiLostFrameNum; i++)
				{
					m_oADCLostFrameStruct ADCLostFrame;
					unsigned int uiIP = pInstrument->m_uiIP;
					unsigned short usADCFramePointNb = static_cast<unsigned short>(pInstrument->m_usADCDataFramePoint 
						+ (i + 1) * iADCDataInOneFrameNum);
					if (usADCFramePointNb >= usADCFramePointLimit)
					{
						usADCFramePointNb = usADCFramePointNb - usADCFramePointLimit;
					}
					ADCLostFrame.m_uiCount = 0;
					ADCLostFrame.m_bReturnOk = false;
					ADCLostFrame.m_uiFrameNb = pInstrument->m_uiADCDataShouldRecFrameNum 
						+ pInstrument->m_iADCDataFrameStartNum;
					// ���ݲ�����ȷ��ʱ���
					ADCLostFrame.m_uiSysTime = pInstrument->m_uiADCDataFrameSysTime 
						+ (i + 1) * (4000 / pADCDataRecThread->m_iADCSampleRate) * iADCDataInOneFrameNum;
					AddToADCFrameLostMap(uiIP, usADCFramePointNb, ADCLostFrame, &pADCDataRecThread->m_pLineList->m_pInstrumentList->m_oADCLostFrameMap);
					pInstrument->m_uiADCDataShouldRecFrameNum++;
					// �ڶ�֡��λ��д��ǰ֡������
					AddToADCDataWriteFileList(pInstrument->m_iLineIndex, pInstrument->m_iPointIndex,
						ADCLostFrame.m_uiFrameNb, pInstrument->m_uiSN, ADCLostFrame.m_uiSysTime, 
						pADCDataRecThread);
					if (pInstrument->m_olsADCDataSave.size() == pADCDataRecThread->m_pThread->m_pConstVar->m_uiSaveTestDataNum)
					{
						pInstrument->m_olsADCDataSave.pop_front();
					}
					pInstrument->m_olsADCDataSave.push_back(iTestData);
				}
				str.Format(_T("����SN = 0x%x��IP = 0x%x����ʧ֡��Ϊ%d"), pInstrument->m_uiSN, 
					pInstrument->m_uiIP, uiLostFrameNum);
				strConv = (CStringA)str;
				AddMsgToLogOutPutList(pADCDataRecThread->m_pThread->m_pLogOutPut, "ProcADCDataRecFrameOne",
					strConv, WarningType);
				AddMsgToLogOutPutList(pADCDataRecThread->m_pLogOutPutADCFrameTime, "", 
					strConv, WarningType);
			}
			uiFrameNb = pInstrument->m_uiADCDataShouldRecFrameNum + pInstrument->m_iADCDataFrameStartNum;
			AddToADCDataWriteFileList(pInstrument->m_iLineIndex, pInstrument->m_iPointIndex, 
				uiFrameNb, pInstrument->m_uiSN, uiADCDataFrameSysTimeNow, pADCDataRecThread);
			if (pInstrument->m_olsADCDataSave.size() == pADCDataRecThread->m_pThread->m_pConstVar->m_uiSaveTestDataNum)
			{
				pInstrument->m_olsADCDataSave.pop_front();
			}
			pInstrument->m_olsADCDataSave.push_back(iTestData);
		}
	}
	else
	{
		if (uiTBHigh + 198 != uiADCDataFrameSysTimeNow)
		{
			str.Format(_T("����SN = 0x%x��IP = 0x%x����һ֡�ı���ʱ�� = 0x%x"), pInstrument->m_uiSN, 
				pInstrument->m_uiIP, uiADCDataFrameSysTimeNow);
			strConv = (CStringA)str;
			AddMsgToLogOutPutList(pADCDataRecThread->m_pThread->m_pLogOutPut, "ProcADCDataRecFrameOne",
				strConv, ErrorType, IDS_ERR_SAMPLETIME);
		}
	}
	pInstrument->m_uiADCDataActualRecFrameNum++;
	pInstrument->m_uiADCDataShouldRecFrameNum++;
	pInstrument->m_usADCDataFramePoint = usADCDataFramePointNow;
	pInstrument->m_uiADCDataFrameSysTime = uiADCDataFrameSysTimeNow;
	str.Format(_T("����SN = 0x%x��IP = 0x%x��"), pInstrument->m_uiSN, pInstrument->m_uiIP);
	strOut += str;
	str.Format(_T("����֡��ָ��ƫ����Ϊ %d����ֵΪ %d��"), 
		pInstrument->m_usADCDataFramePoint, uiADCDataFramePointMove);
	strOut += str;
	str.Format(_T("����ʱ��Ϊ %d����ֵΪ%d��"), 
		pInstrument->m_uiADCDataFrameSysTime, uiADCDataFrameSysTimeMove);
	strOut += str;
	str.Format(_T("Ӧ��֡��Ϊ %d, ��ʼ��֡��Ϊ%d"), 
		pInstrument->m_uiADCDataShouldRecFrameNum, pInstrument->m_iADCDataFrameStartNum);
	strOut += str;
	strConv = (CStringA)strOut;
	AddMsgToLogOutPutList(pADCDataRecThread->m_pLogOutPutADCFrameTime, "", strConv);
	LeaveCriticalSection(&pADCDataRecThread->m_pLineList->m_oSecLineList);
	EnterCriticalSection(&pADCDataRecThread->m_oSecADCDataRecThread);
	pADCDataRecThread->m_uiADCDataFrameSysTime = uiADCDataFrameSysTimeNow;
	pADCDataRecThread->m_iADCFrameCount = iADCFrameCount;
	pADCDataRecThread->m_bCheckFDUADCRec = bCheckFDUADCRec;
	LeaveCriticalSection(&pADCDataRecThread->m_oSecADCDataRecThread);
}
// ����ADC���ݽ���֡
void ProcADCDataRecFrame(m_oADCDataRecThreadStruct* pADCDataRecThread)
{
	if (pADCDataRecThread == NULL)
	{
		return;
	}
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
			if (false == ParseInstrumentADCDataRecFrame(pADCDataRecThread->m_pADCDataFrame, 
					pADCDataRecThread->m_pThread->m_pConstVar))
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
	if (pADCDataRecThread == NULL)
	{
		return;
	}
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
			MakeInstrumentADCDataFrame(pADCDataRecThread->m_pADCDataFrame, 
				pADCDataRecThread->m_pThread->m_pConstVar, iter->first.m_uiIP, iter->first.m_usADCFramePointNb);
			SendInstrumentADCDataFrame(pADCDataRecThread->m_pADCDataFrame, 
				pADCDataRecThread->m_pThread->m_pConstVar);
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
	if (pADCDataRecThread == NULL)
	{
		return 1;
	}
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
	if (pADCDataRecThread == NULL)
	{
		return false;
	}
	EnterCriticalSection(&pADCDataRecThread->m_oSecADCDataRecThread);
	if (false == OnInitThread(pADCDataRecThread->m_pThread, pLogOutPut, pConstVar))
	{
		LeaveCriticalSection(&pADCDataRecThread->m_oSecADCDataRecThread);
		return false;
	}
	pADCDataRecThread->m_uiADCDataFrameSysTime = 0;
	pADCDataRecThread->m_iADCFrameCount = 0;
	pADCDataRecThread->m_iADCSampleRate = 1000;	// Ĭ��Ϊ1K������
	pADCDataRecThread->m_bCheckFDUADCRec = false;
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
	if (pEnv == NULL)
	{
		return false;
	}
	pEnv->m_pADCDataRecThread->m_pLogOutPutADCFrameTime = pEnv->m_pLogOutPutADCFrameTime;
	pEnv->m_pADCDataRecThread->m_pADCDataBufArray = pEnv->m_pADCDataBufArray;
	pEnv->m_pADCDataRecThread->m_pADCDataFrame = pEnv->m_pADCDataFrame;
	pEnv->m_pADCDataRecThread->m_pLineList = pEnv->m_pLineList;
	return OnInitADCDataRecThread(pEnv->m_pADCDataRecThread, pEnv->m_pLogOutPutOpt, pEnv->m_pConstVar);
}
// �ر�ADC���ݽ����߳�
bool OnCloseADCDataRecThread(m_oADCDataRecThreadStruct* pADCDataRecThread)
{
	if (pADCDataRecThread == NULL)
	{
		return false;
	}
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
	if (pADCDataRecThread == NULL)
	{
		return;
	}
	if (pADCDataRecThread->m_pThread != NULL)
	{
		delete pADCDataRecThread->m_pThread;
		pADCDataRecThread->m_pThread = NULL;
	}
	DeleteCriticalSection(&pADCDataRecThread->m_oSecADCDataRecThread);
	delete pADCDataRecThread;
	pADCDataRecThread = NULL;
}