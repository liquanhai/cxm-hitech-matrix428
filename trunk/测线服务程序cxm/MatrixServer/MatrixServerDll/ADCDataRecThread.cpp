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
	pADCDataRecThread->m_pInstrumentList = NULL;
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
	// ѭ��
	while(true)
	{	// ����50����
		Sleep(pADCDataRecThread->m_pThread->m_pConstVar->m_iOneSleepTime);
		// �ȴ�������1
		iWaitCount++;
		// �ж��Ƿ���Դ��������
		if(pADCDataRecThread->m_pThread->m_bClose == true)
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
// ��ADC���ݼ��뵽�����б�
void AddToADCDataWriteFileList(unsigned int uiFrameNb, unsigned int uiSN, 
	unsigned int uiSysTime, m_oADCDataRecThreadStruct* pADCDataRecThread)
{
	if (pADCDataRecThread == NULL)
	{
		return;
	}
	// @@@@������
	// 	CString str = _T("");
	// 	str.Format(_T("����IP = 0x%x��д���ļ���� = %d��֡��� = %d"), uiIP, uiFileNb, uiFrameInFileNb);
	// 	AddMsgToLogOutPutList(pADCDataRecThread->m_pLogOutPutADCFrameTime, "", ConvertCStrToStr(str));
	m_oADCDataBufStruct* pADCDataBuf = NULL;
	EnterCriticalSection(&pADCDataRecThread->m_pADCDataFrame->m_oSecADCDataFrame);
	EnterCriticalSection(&pADCDataRecThread->m_pADCDataBufArray->m_oSecADCDataBufArray);
	pADCDataBuf = GetFreeADCDataBuf(pADCDataRecThread->m_pADCDataBufArray);
	pADCDataBuf->m_uiFrameNb = uiFrameNb;
	pADCDataBuf->m_uiSN = uiSN;
	pADCDataBuf->m_uiSysTime = uiSysTime;
	memcpy(pADCDataBuf->m_pADCDataBuf, pADCDataRecThread->m_pADCDataFrame->m_pCommandStructReturn->m_pADCData,
		pADCDataRecThread->m_pThread->m_pConstVar->m_iADCDataInOneFrameNum * sizeof(int));
	pADCDataRecThread->m_pADCDataBufArray->m_olsADCDataToWrite.push_back(pADCDataBuf);
	LeaveCriticalSection(&pADCDataRecThread->m_pADCDataBufArray->m_oSecADCDataBufArray);
	LeaveCriticalSection(&pADCDataRecThread->m_pADCDataFrame->m_oSecADCDataFrame);
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
	unsigned int uiADCDataFrameSysTimeMove = 0;
	unsigned int uiLostFrameNum = 0;
	int iADCDataInOneFrameNum = 0;
	int iADCFrameSaveInOneFileNum = 0;
	unsigned short usADCFramePointLimit = 0;
	m_oADCLostFrameKeyStruct oLostFrameKey;
	ADCLostFrame_Struct* pADCLostFrame = NULL;
	// ֡���
	unsigned int uiFrameNb = 0;

	iADCDataInOneFrameNum = pADCDataRecThread->m_pThread->m_pConstVar->m_iADCDataInOneFrameNum;
	usADCFramePointLimit = pADCDataRecThread->m_pThread->m_pConstVar->m_usADCFramePointLimit;
	iADCFrameSaveInOneFileNum = pADCDataRecThread->m_pThread->m_pConstVar->m_iADCFrameSaveInOneFileNum;
	// �õ�����IP
	uiIPInstrument = pADCDataRecThread->m_pADCDataFrame->m_pCommandStructReturn->m_uiSrcIP;
	// �õ�ָ��ƫ����
	usADCDataFramePointNow = pADCDataRecThread->m_pADCDataFrame->m_pCommandStructReturn->m_usADCDataPoint;
	// �õ�����ϵͳʱ��
	uiADCDataFrameSysTimeNow = pADCDataRecThread->m_pADCDataFrame->m_pCommandStructReturn->m_uiADCSampleSysTime;

	// ��������������
	if (TRUE == IfIndexExistInMap(uiIPInstrument, &pADCDataRecThread->m_pInstrumentList->m_oIPInstrumentMap))
	{
		pInstrument = GetInstrumentFromMap(uiIPInstrument, 
			&pADCDataRecThread->m_pInstrumentList->m_oIPInstrumentMap);
		// �ж��Ƿ�Ϊ�ط�֡
		oLostFrameKey.m_uiIP = uiIPInstrument;
		oLostFrameKey.m_usADCFramePointNb = usADCDataFramePointNow;
		// �ڶ�֡���������ҵ�
		if (TRUE == IfIndexExistInADCFrameLostMap(oLostFrameKey, &pADCDataRecThread->m_oADCLostFrameMap))
		{
			str.Format(_T("�յ�SN = 0x%x��IP��ַ = 0x%x��ADC�����ط�֡��ָ��ƫ���� = %d"), 
				pInstrument->m_uiSN, pInstrument->m_uiIP, usADCDataFramePointNow);
			ConvertCStrToStr(str, &strConv);
			AddMsgToLogOutPutList(pADCDataRecThread->m_pThread->m_pLogOutPut, "ProcADCDataRecFrameOne", 
				strConv);

			pADCLostFrame = GetFromADCFrameLostMap(oLostFrameKey, &pADCDataRecThread->m_oADCLostFrameMap);
			if (pADCLostFrame->m_bReturnOk == false)
			{
				pInstrument->m_uiADCDataActualRecFrameNum++;
				pInstrument->m_uiADCDataRetransmissionFrameNum++;
				pADCLostFrame->m_bReturnOk = true;
				// ����Ӧ��֡����д���ļ�
				uiFrameNb = pADCLostFrame->m_uiFrameNb;
				AddToADCDataWriteFileList(uiFrameNb, pInstrument->m_uiSN, pADCLostFrame->m_uiSysTime, 
					pADCDataRecThread);
			}
			return;
		}
		// 		// ������
		// 		if (usADCDataFramePointNow == 288)
		// 		{
		// 			return;
		// 		}
		if (pInstrument->m_uiADCDataActualRecFrameNum > 0)
		{
			if (usADCDataFramePointNow > usADCFramePointLimit)
			{
				GetFrameInfo(pADCDataRecThread->m_pADCDataFrame->m_cpRcvFrameData, 
					pADCDataRecThread->m_pADCDataFrame->m_uiRcvBufferSize, &strFrameData);
				AddMsgToLogOutPutList(pADCDataRecThread->m_pThread->m_pLogOutPut, "ProcADCDataRecFrameOne", 
					strFrameData, ErrorType, IDS_ERR_FRAMEPOINT_LIMITOVER);
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
				GetFrameInfo(pADCDataRecThread->m_pADCDataFrame->m_cpRcvFrameData,
					pADCDataRecThread->m_pADCDataFrame->m_uiRcvBufferSize, &strFrameData);
				AddMsgToLogOutPutList(pADCDataRecThread->m_pThread->m_pLogOutPut, "ProcADCDataRecFrameOne", 
					strFrameData, ErrorType, IDS_ERR_FRAMEPOINT_ERROR);
				str.Format(_T("ָ��ƫ��������ƫ������ֵΪ%d"), uiADCDataFramePointMove);
				ConvertCStrToStr(str, &strConv);
				AddMsgToLogOutPutList(pADCDataRecThread->m_pLogOutPutADCFrameTime, "", 
					strConv, ErrorType, IDS_ERR_FRAMEPOINT_ERROR);
			}
			else
			{
				if (uiADCDataFrameSysTimeNow != pADCDataRecThread->m_uiADCDataFrameSysTime)
				{
					pADCDataRecThread->m_iADCFrameCount++;
				}
				if (pInstrument->m_uiADCDataActualRecFrameNum == 1)
				{
					pInstrument->m_iADCDataFrameStartNum = pADCDataRecThread->m_iADCFrameCount - 1 - 1;
				}

				uiLostFrameNum = uiADCDataFramePointMove / iADCDataInOneFrameNum - 1;
				if (uiLostFrameNum > 0)
				{
					// ���뵽��֡������
					for (unsigned int i=0; i<uiLostFrameNum; i++)
					{
						m_oADCLostFrameKeyStruct Key;
						m_oADCLostFrameStruct ADCLostFrame;
						Key.m_uiIP = pInstrument->m_uiIP;
						Key.m_usADCFramePointNb = static_cast<unsigned short>(pInstrument->m_usADCDataFramePoint 
							+ (i + 1) * iADCDataInOneFrameNum);
						if (Key.m_usADCFramePointNb >= usADCFramePointLimit)
						{
							Key.m_usADCFramePointNb = Key.m_usADCFramePointNb - usADCFramePointLimit;
						}
						ADCLostFrame.m_uiCount = 0;
						ADCLostFrame.m_bReturnOk = false;
						ADCLostFrame.m_uiFrameNb = pInstrument->m_uiADCDataShouldRecFrameNum 
							+ pInstrument->m_iADCDataFrameStartNum;
						// @@@@1K�����ʵ�ʱ���Ϊ288
						ADCLostFrame.m_uiSysTime = pInstrument->m_uiADCDataFrameSysTime + (i + 1) * 288;
						AddToADCFrameLostMap(Key, ADCLostFrame, &pADCDataRecThread->m_oADCLostFrameMap);
						pInstrument->m_uiADCDataShouldRecFrameNum++;
						// �ڶ�֡��λ��д��ǰ֡������
						AddToADCDataWriteFileList(ADCLostFrame.m_uiFrameNb, pInstrument->m_uiSN, 
							ADCLostFrame.m_uiSysTime, pADCDataRecThread);
					}
					str.Format(_T("����SN = 0x%x��IP = 0x%x����ʧ֡��Ϊ%d"), pInstrument->m_uiSN, 
						pInstrument->m_uiIP, uiLostFrameNum);
					ConvertCStrToStr(str, &strConv);
					AddMsgToLogOutPutList(pADCDataRecThread->m_pThread->m_pLogOutPut, "ProcADCDataRecFrameOne",
						strConv, WarningType);
					AddMsgToLogOutPutList(pADCDataRecThread->m_pLogOutPutADCFrameTime, "", 
						strConv, WarningType);
				}
				uiFrameNb = pInstrument->m_uiADCDataShouldRecFrameNum + pInstrument->m_iADCDataFrameStartNum;
				AddToADCDataWriteFileList(uiFrameNb, pInstrument->m_uiSN, uiADCDataFrameSysTimeNow, pADCDataRecThread);
			}
		}

		pADCDataRecThread->m_uiADCDataFrameSysTime = uiADCDataFrameSysTimeNow;
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
		ConvertCStrToStr(strOut, &strConv);
		AddMsgToLogOutPutList(pADCDataRecThread->m_pLogOutPutADCFrameTime, "", strConv);
	}
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
	iFrameCount = GetFrameCount(pADCDataRecThread->m_pADCDataFrame->m_oADCDataFrameSocket,
		pADCDataRecThread->m_pThread->m_pConstVar->m_iRcvFrameSize, 
		pADCDataRecThread->m_pThread->m_pLogOutPut);
	// �ж�֡�����Ƿ����0
	if(iFrameCount > 0)
	{
		// ѭ������ÿ1֡
		for(int i = 0; i < iFrameCount; i++)
		{
			// �õ�֡����
			if (true == GetFrameData(pADCDataRecThread->m_pADCDataFrame->m_oADCDataFrameSocket,
				pADCDataRecThread->m_pADCDataFrame->m_cpRcvFrameData, 
				pADCDataRecThread->m_pThread->m_pConstVar->m_iRcvFrameSize, 
				pADCDataRecThread->m_pThread->m_pLogOutPut))
			{
				if (false == ParseInstrumentADCDataRecFrame(pADCDataRecThread->m_pADCDataFrame, 
					pADCDataRecThread->m_pThread->m_pConstVar))
				{
					AddMsgToLogOutPutList(pADCDataRecThread->m_pThread->m_pLogOutPut, "ParseInstrumentADCDataRecFrame",
						"", ErrorType, IDS_ERR_PARSE_ADCDATARECFRAME);
				}
				else
				{
					EnterCriticalSection(&pADCDataRecThread->m_pInstrumentList->m_oSecInstrumentList);
					// ������ADC����֡
					ProcADCDataRecFrameOne(pADCDataRecThread);
					LeaveCriticalSection(&pADCDataRecThread->m_pInstrumentList->m_oSecInstrumentList);
				}	
			}		
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
	for (iter = pADCDataRecThread->m_oADCLostFrameMap.begin(); 
		iter != pADCDataRecThread->m_oADCLostFrameMap.end();)
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
			ConvertCStrToStr(str, &strConv);
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
				ConvertCStrToStr(str, &strConv);
				AddMsgToLogOutPutList(pADCDataRecThread->m_pThread->m_pLogOutPut, "ProcADCRetransmission", 
					strConv);
			}
			pADCDataRecThread->m_oADCLostFrameMap.erase(iter++);
		}
		else
		{
			iter++;
		}
	}
}
// �̺߳���
DWORD WINAPI RunADCDataRecThread(m_oADCDataRecThreadStruct* pADCDataRecThread)
{
	if (pADCDataRecThread == NULL)
	{
		return 1;
	}
	while(true)
	{
		if (pADCDataRecThread->m_pThread->m_bClose == true)
		{
			break;
		}
		if (pADCDataRecThread->m_pThread->m_bWork == true)
		{
			// ����ADC���ݽ���֡
			ProcADCDataRecFrame(pADCDataRecThread);
			// ����ADC�����ط�
			ProcADCRetransmission(pADCDataRecThread);
		}
		if (pADCDataRecThread->m_pThread->m_bClose == true)
		{
			break;
		}
		WaitADCDataRecThread(pADCDataRecThread);
	}
	// �����¼�����Ϊ���ź�״̬,�ͷŵȴ��̺߳��¼���Ϊ���ź�
	SetEvent(pADCDataRecThread->m_pThread->m_hThreadClose);
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
	if (false == OnInitThread(pADCDataRecThread->m_pThread, pLogOutPut, pConstVar))
	{
		return false;
	}
	pADCDataRecThread->m_uiADCDataFrameSysTime = 0;
	pADCDataRecThread->m_iADCFrameCount = 0;
	pADCDataRecThread->m_oADCLostFrameMap.clear();
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
		AddMsgToLogOutPutList(pADCDataRecThread->m_pThread->m_pLogOutPut, "OnInitADCDataRecThread", 
			"pADCDataRecThread->m_pThread->m_hThread", ErrorType, IDS_ERR_CREATE_THREAD);
		return false;
	}
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
	pEnv->m_pADCDataRecThread->m_pInstrumentList = pEnv->m_pInstrumentList;
	return OnInitADCDataRecThread(pEnv->m_pADCDataRecThread, pEnv->m_pLogOutPutOpt, pEnv->m_pConstVar);
}
// �ر�ADC���ݽ����߳�
bool OnCloseADCDataRecThread(m_oADCDataRecThreadStruct* pADCDataRecThread)
{
	if (pADCDataRecThread == NULL)
	{
		return false;
	}
	// ��ն�֡����
	pADCDataRecThread->m_oADCLostFrameMap.clear();
	if (false == OnCloseThread(pADCDataRecThread->m_pThread))
	{
		AddMsgToLogOutPutList(pADCDataRecThread->m_pThread->m_pLogOutPut, "OnCloseADCDataRecThread", 
			"ADC���ݽ����߳�ǿ�ƹر�", WarningType);
		return false;
	}
	else
	{
		AddMsgToLogOutPutList(pADCDataRecThread->m_pThread->m_pLogOutPut, "OnCloseADCDataRecThread", 
			"ADC���ݽ����̳߳ɹ��ر�");
		return true;
	}
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
	}
	delete pADCDataRecThread;
}