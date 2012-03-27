#include "stdafx.h"
#include "MatrixServerDll.h"

// ���������ѯ�߳�
m_oErrorCodeThreadStruct* OnCreateErrorCodeThread(void)
{
	m_oErrorCodeThreadStruct* pErrorCodeThread = NULL;
	pErrorCodeThread = new m_oErrorCodeThreadStruct;
	pErrorCodeThread->m_pThread = new m_oThreadStruct;
	pErrorCodeThread->m_pLogOutPutErrorCode = NULL;
	pErrorCodeThread->m_pErrorCodeFrame = NULL;
	pErrorCodeThread->m_pRoutList = NULL;
	pErrorCodeThread->m_pInstrumentList = NULL;
	return pErrorCodeThread;
}
// �̵߳ȴ�����
void WaitErrorCodeThread(m_oErrorCodeThreadStruct* pErrorCodeThread)
{
	if (pErrorCodeThread == NULL)
	{
		return;
	}
	// ��ʼ���ȴ�����Ϊ0
	int iWaitCount = 0;
	// ѭ��
	while(true)
	{	// ����50����
		Sleep(pErrorCodeThread->m_pThread->m_pConstVar->m_iOneSleepTime);
		// �ȴ�������1
		iWaitCount++;
		// �ж��Ƿ���Դ��������
		if(pErrorCodeThread->m_pThread->m_bClose == true)
		{
			// ����
			return;
		}
		// �жϵȴ������Ƿ���ڵ������ȴ�����
		if(pErrorCodeThread->m_pThread->m_pConstVar->m_iErrorCodeSleepTimes == iWaitCount)
		{
			// ����
			return;
		}		
	}
}
// �����������ѯӦ��֡
void ProcErrorCodeReturnFrameOne(m_oErrorCodeThreadStruct* pErrorCodeThread)
{
	if (pErrorCodeThread == NULL)
	{
		return;
	}
	unsigned int uiIPInstrument = 0;
	m_oInstrumentStruct* pInstrument = NULL;
	CString str = _T("");
	CString strOutPut = _T("");
	string strFrameData = "";
	string strConv = "";
	char byTemp = 0;
	int iTemp = 0;
	// �õ�����IP
	uiIPInstrument = pErrorCodeThread->m_pErrorCodeFrame->m_pCommandStructReturn->m_uiSrcIP;
	// ��������������
	if (TRUE == IfIndexExistInMap(uiIPInstrument, &pErrorCodeThread->m_pInstrumentList->m_oIPInstrumentMap))
	{
		pInstrument = GetInstrumentFromMap(uiIPInstrument, 
			&pErrorCodeThread->m_pInstrumentList->m_oIPInstrumentMap);
		str.Format(_T("����SN = 0x%x��IP = 0x%x��"), pInstrument->m_uiSN, pInstrument->m_uiIP);
		strOutPut += str;
		// ��������ΪLCI���߽���վ
		if ((pInstrument->m_iInstrumentType == pErrorCodeThread->m_pThread->m_pConstVar->m_iInstrumentTypeLCI)
			|| (pInstrument->m_iInstrumentType == pErrorCodeThread->m_pThread->m_pConstVar->m_iInstrumentTypeLAUX))
		{
			// ����վ����A���ݹ���
			byTemp = pErrorCodeThread->m_pErrorCodeFrame->m_pCommandStructReturn->m_cLAUXErrorCodeDataLineACount;
			if (pInstrument->m_uiErrorCodeReturnNum != 0)
			{
				if (pInstrument->m_cLAUXErrorCodeDataLineACountOld > byTemp)
				{
					iTemp = 256 + byTemp - pInstrument->m_cLAUXErrorCodeDataLineACountOld;
				}
				else
				{
					iTemp = byTemp - pInstrument->m_cLAUXErrorCodeDataLineACountOld;
				}
				pInstrument->m_iLAUXErrorCodeDataLineACount += iTemp;
			}
			pInstrument->m_cLAUXErrorCodeDataLineACountOld = byTemp;
			str.Format(_T("����A���ݹ�����=%d��"),iTemp);
			strOutPut += str;
			// ����վ����B���ݹ���
			byTemp = pErrorCodeThread->m_pErrorCodeFrame->m_pCommandStructReturn->m_cLAUXErrorCodeDataLineBCount;
			if (pInstrument->m_uiErrorCodeReturnNum != 0)
			{
				if (pInstrument->m_cLAUXErrorCodeDataLineBCountOld > byTemp)
				{
					iTemp = 256 + byTemp - pInstrument->m_cLAUXErrorCodeDataLineBCountOld;
				}
				else
				{
					iTemp = byTemp - pInstrument->m_cLAUXErrorCodeDataLineBCountOld;
				}
				pInstrument->m_iLAUXErrorCodeDataLineBCount += iTemp;
			}
			pInstrument->m_cLAUXErrorCodeDataLineBCountOld = byTemp;
			str.Format(_T("����B���ݹ�����=%d��"), iTemp);
			strOutPut += str;
			// ����վ������A���ݹ���
			byTemp = pErrorCodeThread->m_pErrorCodeFrame->m_pCommandStructReturn->m_cLAUXErrorCodeDataLAUXLineACount;
			if (pInstrument->m_uiErrorCodeReturnNum != 0)
			{
				if (pInstrument->m_cLAUXErrorCodeDataLAUXLineACountOld > byTemp)
				{
					iTemp = 256 + byTemp - pInstrument->m_cLAUXErrorCodeDataLAUXLineACountOld;
				}
				else
				{
					iTemp = byTemp - pInstrument->m_cLAUXErrorCodeDataLAUXLineACountOld;
				}
				pInstrument->m_iLAUXErrorCodeDataLAUXLineACount += iTemp;
			}
			pInstrument->m_cLAUXErrorCodeDataLAUXLineACountOld = byTemp;
			str.Format(_T("������A���ݹ�����=%d��"), iTemp);
			strOutPut += str;
			// ����վ������B���ݹ���
			byTemp = pErrorCodeThread->m_pErrorCodeFrame->m_pCommandStructReturn->m_cLAUXErrorCodeDataLAUXLineBCount;
			if (pInstrument->m_uiErrorCodeReturnNum != 0)
			{
				if (pInstrument->m_cLAUXErrorCodeDataLAUXLineBCountOld > byTemp)
				{
					iTemp = 256 + byTemp - pInstrument->m_cLAUXErrorCodeDataLAUXLineBCountOld;
				}
				else
				{
					iTemp = byTemp - pInstrument->m_cLAUXErrorCodeDataLAUXLineBCountOld;
				}
				pInstrument->m_iLAUXErrorCodeDataLAUXLineBCount += iTemp;
			}
			pInstrument->m_cLAUXErrorCodeDataLAUXLineBCountOld = byTemp;
			str.Format(_T("������B���ݹ�����=%d��"), iTemp);
			strOutPut += str;
			// ����վ����ڹ���
			byTemp = pErrorCodeThread->m_pErrorCodeFrame->m_pCommandStructReturn->m_cLAUXErrorCodeCmdCount;
			if (pInstrument->m_uiErrorCodeReturnNum != 0)
			{
				if (pInstrument->m_cLAUXErrorCodeCmdCountOld > byTemp)
				{
					iTemp = 256 + byTemp - pInstrument->m_cLAUXErrorCodeCmdCountOld;
				}
				else
				{
					iTemp = byTemp - pInstrument->m_cLAUXErrorCodeCmdCountOld;
				}
				// LCI��������������
				if (pInstrument->m_iInstrumentType == pErrorCodeThread->m_pThread->m_pConstVar->m_iInstrumentTypeLCI)
				{
					iTemp = 0;
				}
				pInstrument->m_iLAUXErrorCodeCmdCount += iTemp;
			}
			pInstrument->m_cLAUXErrorCodeCmdCountOld = byTemp;
			str.Format(_T("����ڹ�����=%d��"), iTemp);
			strOutPut += str;
		}
		// ��������Ϊ�ɼ�վ���ߵ�Դվ
		else
		{
			// �ɼ�վ�͵�Դվ�������ݴ������
			byTemp = pErrorCodeThread->m_pErrorCodeFrame->m_pCommandStructReturn->m_cFDUErrorCodeDataCount;
			if (pInstrument->m_uiErrorCodeReturnNum != 0)
			{
				if (pInstrument->m_cFDUErrorCodeDataCountOld > byTemp)
				{
					iTemp = 256 + byTemp - pInstrument->m_cFDUErrorCodeDataCountOld;
				}
				else
				{
					iTemp = byTemp - pInstrument->m_cFDUErrorCodeDataCountOld;
				}
				pInstrument->m_iFDUErrorCodeDataCount += iTemp;
			}
			pInstrument->m_cFDUErrorCodeDataCountOld = byTemp;
			str.Format(_T("�������ݴ������=%d��"), iTemp);
			strOutPut += str;
			// �ɼ�վ�͵�Դվ����������
			byTemp = pErrorCodeThread->m_pErrorCodeFrame->m_pCommandStructReturn->m_cFDUErrorCodeCmdCount;
			if (pInstrument->m_uiErrorCodeReturnNum != 0)
			{
				if (pInstrument->m_cFDUErrorCodeCmdCountOld > byTemp)
				{
					iTemp = 256 + byTemp - pInstrument->m_cFDUErrorCodeCmdCountOld;
				}
				else
				{
					iTemp = byTemp - pInstrument->m_cFDUErrorCodeCmdCountOld;
				}
				pInstrument->m_iFDUErrorCodeCmdCount += iTemp;
			}
			pInstrument->m_cFDUErrorCodeCmdCountOld = byTemp;
			str.Format(_T("����������=%d��"), iTemp);
			strOutPut += str;
		}
		pInstrument->m_uiErrorCodeReturnNum++;
		str.Format(_T("����֡��=%d"), pInstrument->m_uiErrorCodeReturnNum);
		strOutPut += str;
		ConvertCStrToStr(strOutPut, &strConv);
		AddMsgToLogOutPutList(pErrorCodeThread->m_pLogOutPutErrorCode, "", strConv);
	}
	else
	{
		GetFrameInfo(pErrorCodeThread->m_pErrorCodeFrame->m_cpRcvFrameData,
			pErrorCodeThread->m_pThread->m_pConstVar->m_iRcvFrameSize, &strFrameData);
		AddMsgToLogOutPutList(pErrorCodeThread->m_pThread->m_pLogOutPut, "ProcErrorCodeReturnFrameOne",
			strFrameData, ErrorType, IDS_ERR_IPSETMAP_NOTEXIT);
	}
}
// ���������ѯӦ��֡
void ProcErrorCodeReturnFrame(m_oErrorCodeThreadStruct* pErrorCodeThread)
{
	if (pErrorCodeThread == NULL)
	{
		return;
	}
	// ֡��������Ϊ0
	int iFrameCount = 0;
	// �õ��װ���������˿�֡����
	iFrameCount = GetFrameCount(pErrorCodeThread->m_pErrorCodeFrame->m_oErrorCodeFrameSocket,
		pErrorCodeThread->m_pThread->m_pConstVar->m_iRcvFrameSize, 
		pErrorCodeThread->m_pThread->m_pLogOutPut);
	// �ж�֡�����Ƿ����0
	if(iFrameCount > 0)
	{
		// ѭ������ÿ1֡
		for(int i = 0; i < iFrameCount; i++)
		{
			// �õ�֡����
			if (true == GetFrameData(pErrorCodeThread->m_pErrorCodeFrame->m_oErrorCodeFrameSocket,
				pErrorCodeThread->m_pErrorCodeFrame->m_cpRcvFrameData, 
				pErrorCodeThread->m_pThread->m_pConstVar->m_iRcvFrameSize, 
				pErrorCodeThread->m_pThread->m_pLogOutPut))
			{
				if (false == ParseInstrumentErrorCodeReturnFrame(pErrorCodeThread->m_pErrorCodeFrame, 
					pErrorCodeThread->m_pThread->m_pConstVar))
				{
					AddMsgToLogOutPutList(pErrorCodeThread->m_pThread->m_pLogOutPut, 
						"ParseInstrumentErrorCodeReturnFrame","", 
						ErrorType, IDS_ERR_PARSE_ERRORCODERETURNFRAME);
				}
				else
				{
					EnterCriticalSection(&pErrorCodeThread->m_pInstrumentList->m_oSecInstrumentList);
					// ������IP��ַ����Ӧ��֡
					ProcErrorCodeReturnFrameOne(pErrorCodeThread);
					LeaveCriticalSection(&pErrorCodeThread->m_pInstrumentList->m_oSecInstrumentList);
				}	
			}		
		}		
	}
}
// ���������ѯ֡
void ProcErrorCodeQueryFrame(m_oErrorCodeThreadStruct* pErrorCodeThread)
{
	if (pErrorCodeThread == NULL)
	{
		return;
	}
	hash_map<unsigned int, m_oRoutStruct*> ::iterator iter;
	m_oRoutStruct* pRout = NULL;
	m_oInstrumentStruct* pInstrument = NULL;
	m_oInstrumentStruct* pInstrumentNext = NULL;
	CString str = _T("");
	string strConv = "";
	EnterCriticalSection(&pErrorCodeThread->m_pRoutList->m_oSecRoutList);
	for (iter = pErrorCodeThread->m_pRoutList->m_oRoutMap.begin();
		iter != pErrorCodeThread->m_pRoutList->m_oRoutMap.end();
		iter++)
	{
		pRout = iter->second;
		if (pRout->m_pTail != NULL)
		{
			pInstrument = pRout->m_pHead;
			do 
			{
				pInstrumentNext = GetNextInstrument(pRout->m_iRoutDirection, pInstrument, 
					pErrorCodeThread->m_pThread->m_pConstVar);
				pInstrumentNext->m_uiErrorCodeQueryNum++;
				pInstrument = pInstrumentNext;
			} while (pInstrumentNext != pRout->m_pTail);
			// �㲥���������ѯ֡
			MakeInstrumentErrorCodeQueryFrame(pErrorCodeThread->m_pErrorCodeFrame,
				pErrorCodeThread->m_pThread->m_pConstVar, pRout->m_pTail->m_uiBroadCastPort);
			SendInstrumentErrorCodeFrame(pErrorCodeThread->m_pErrorCodeFrame,
				pErrorCodeThread->m_pThread->m_pConstVar);
			str.Format(_T("��·��IP = 0x%x�㲥���������ѯ֡"), pRout->m_uiRoutIP);
			ConvertCStrToStr(str, &strConv);
			AddMsgToLogOutPutList(pErrorCodeThread->m_pLogOutPutErrorCode, "", strConv);
		}
	}
	LeaveCriticalSection(&pErrorCodeThread->m_pRoutList->m_oSecRoutList);
}
// �̺߳���
DWORD WINAPI RunErrorCodeThread(m_oErrorCodeThreadStruct* pErrorCodeThread)
{
	if (pErrorCodeThread == NULL)
	{
		return 1;
	}
	while(true)
	{
		if (pErrorCodeThread->m_pThread->m_bClose == true)
		{
			break;
		}
		if (pErrorCodeThread->m_pThread->m_bWork == true)
		{
			// ���������ѯӦ��֡
			ProcErrorCodeReturnFrame(pErrorCodeThread);
			// ���������ѯ֡
			ProcErrorCodeQueryFrame(pErrorCodeThread);
		}
		if (pErrorCodeThread->m_pThread->m_bClose == true)
		{
			break;
		}
		WaitErrorCodeThread(pErrorCodeThread);
	}
	// �����¼�����Ϊ���ź�״̬,�ͷŵȴ��̺߳��¼���Ϊ���ź�
	SetEvent(pErrorCodeThread->m_pThread->m_hThreadClose);
	return 1;
}
// ��ʼ�������ѯ�߳�
bool OnInitErrorCodeThread(m_oErrorCodeThreadStruct* pErrorCodeThread, 
	m_oLogOutPutStruct* pLogOutPut, m_oConstVarStruct* pConstVar)
{
	if (pErrorCodeThread == NULL)
	{
		return false;
	}
	if (false == OnInitThread(pErrorCodeThread->m_pThread, pLogOutPut, pConstVar))
	{
		return false;
	}
	// �����¼�����Ϊ���ź�״̬
	ResetEvent(pErrorCodeThread->m_pThread->m_hThreadClose);
	// �����߳�
	pErrorCodeThread->m_pThread->m_hThread = CreateThread((LPSECURITY_ATTRIBUTES)NULL, 
		0,
		(LPTHREAD_START_ROUTINE)RunErrorCodeThread,
		pErrorCodeThread, 
		0, 
		&pErrorCodeThread->m_pThread->m_dwThreadID);
	if (pErrorCodeThread->m_pThread->m_hThread == NULL)
	{
		AddMsgToLogOutPutList(pErrorCodeThread->m_pThread->m_pLogOutPut, "OnInitErrorCodeThread", 
			"pErrorCodeThread->m_pThread->m_hThread", ErrorType, IDS_ERR_CREATE_THREAD);
		return false;
	}
	AddMsgToLogOutPutList(pErrorCodeThread->m_pThread->m_pLogOutPut, "OnInitErrorCodeThread", 
		"�����ѯ�̴߳����ɹ�");
	return true;
}
// ��ʼ�������ѯ�߳�
bool OnInit_ErrorCodeThread(m_oEnvironmentStruct* pEnv)
{
	if (pEnv == NULL)
	{
		return false;
	}
	pEnv->m_pErrorCodeThread->m_pLogOutPutErrorCode = pEnv->m_pLogOutPutErrorCode;
	pEnv->m_pErrorCodeThread->m_pErrorCodeFrame = pEnv->m_pErrorCodeFrame;
	pEnv->m_pErrorCodeThread->m_pRoutList = pEnv->m_pRoutList;
	pEnv->m_pErrorCodeThread->m_pInstrumentList = pEnv->m_pInstrumentList;
	return OnInitErrorCodeThread(pEnv->m_pErrorCodeThread, pEnv->m_pLogOutPutOpt, pEnv->m_pConstVar);
}
// �ر������ѯ�߳�
bool OnCloseErrorCodeThread(m_oErrorCodeThreadStruct* pErrorCodeThread)
{
	if (pErrorCodeThread == NULL)
	{
		return false;
	}
	if (false == OnCloseThread(pErrorCodeThread->m_pThread))
	{
		AddMsgToLogOutPutList(pErrorCodeThread->m_pThread->m_pLogOutPut, "OnCloseErrorCodeThread", 
			"�����ѯ�߳�ǿ�ƹر�", WarningType);
		return false;
	}
	else
	{
		AddMsgToLogOutPutList(pErrorCodeThread->m_pThread->m_pLogOutPut, "OnCloseErrorCodeThread", 
			"�����ѯ�̳߳ɹ��ر�");
		return true;
	}
}
// �ͷ������ѯ�߳�
void OnFreeErrorCodeThread(m_oErrorCodeThreadStruct* pErrorCodeThread)
{
	if (pErrorCodeThread == NULL)
	{
		return;
	}
	if (pErrorCodeThread->m_pThread != NULL)
	{
		delete pErrorCodeThread->m_pThread;
	}
	delete pErrorCodeThread;
}