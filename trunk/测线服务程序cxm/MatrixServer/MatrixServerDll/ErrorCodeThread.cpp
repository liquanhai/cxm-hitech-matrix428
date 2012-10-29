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
	pErrorCodeThread->m_pLineList = NULL;
	InitializeCriticalSection(&pErrorCodeThread->m_oSecErrorCodeThread);
	return pErrorCodeThread;
}
// �̵߳ȴ�����
void WaitErrorCodeThread(m_oErrorCodeThreadStruct* pErrorCodeThread)
{
	ASSERT(pErrorCodeThread != NULL);
	// ��ʼ���ȴ�����Ϊ0
	int iWaitCount = 0;
	bool bClose = false;
	// ѭ��
	while(true)
	{	// ����50����
		Sleep(pErrorCodeThread->m_pThread->m_pConstVar->m_iOneSleepTime);
		// �ȴ�������1
		iWaitCount++;
		EnterCriticalSection(&pErrorCodeThread->m_oSecErrorCodeThread);
		bClose = pErrorCodeThread->m_pThread->m_bClose;
		LeaveCriticalSection(&pErrorCodeThread->m_oSecErrorCodeThread);
		// �ж��Ƿ���Դ��������
		if(bClose == true)
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
	ASSERT(pErrorCodeThread != NULL);
	unsigned int uiIPInstrument = 0;
	m_oInstrumentStruct* pInstrument = NULL;
	m_oRoutStruct* pRout = NULL;
	CString str = _T("");
	CString strOutPut = _T("");
	CString strDebug = _T("");
	bool bStrDebug = false;
	string strFrameData = "";
	string strConv = "";
	char cLAUXErrorCodeDataLineACount = 0;
	char cLAUXErrorCodeDataLineBCount = 0;
	char cLAUXErrorCodeDataLAUXLineACount = 0;
	char cLAUXErrorCodeDataLAUXLineBCount = 0;
	char cLAUXErrorCodeCmdCount = 0;
	char cFDUErrorCodeDataCount = 0;
	char cFDUErrorCodeCmdCount = 0;
	unsigned int uiSysTime = 0;
	int iTemp = 0;
	EnterCriticalSection(&pErrorCodeThread->m_pErrorCodeFrame->m_oSecErrorCodeFrame);
	// �õ�����IP
	uiIPInstrument = pErrorCodeThread->m_pErrorCodeFrame->m_pCommandStructReturn->m_uiSrcIP;
	cLAUXErrorCodeDataLineACount = pErrorCodeThread->m_pErrorCodeFrame->m_pCommandStructReturn->m_cLAUXErrorCodeDataLineACount;
	cLAUXErrorCodeDataLineBCount = pErrorCodeThread->m_pErrorCodeFrame->m_pCommandStructReturn->m_cLAUXErrorCodeDataLineBCount;
	cLAUXErrorCodeDataLAUXLineACount = pErrorCodeThread->m_pErrorCodeFrame->m_pCommandStructReturn->m_cLAUXErrorCodeDataLAUXLineACount;
	cLAUXErrorCodeDataLAUXLineBCount = pErrorCodeThread->m_pErrorCodeFrame->m_pCommandStructReturn->m_cLAUXErrorCodeDataLAUXLineBCount;
	cLAUXErrorCodeCmdCount = pErrorCodeThread->m_pErrorCodeFrame->m_pCommandStructReturn->m_cLAUXErrorCodeCmdCount;
	cFDUErrorCodeDataCount = pErrorCodeThread->m_pErrorCodeFrame->m_pCommandStructReturn->m_cFDUErrorCodeDataCount;
	cFDUErrorCodeCmdCount = pErrorCodeThread->m_pErrorCodeFrame->m_pCommandStructReturn->m_cFDUErrorCodeCmdCount;
	uiSysTime = pErrorCodeThread->m_pErrorCodeFrame->m_pCommandStructReturn->m_uiSysTime;
	LeaveCriticalSection(&pErrorCodeThread->m_pErrorCodeFrame->m_oSecErrorCodeFrame);
	EnterCriticalSection(&pErrorCodeThread->m_pLineList->m_oSecLineList);
	// ��������������
	if (FALSE == IfIndexExistInMap(uiIPInstrument, &pErrorCodeThread->m_pLineList->m_pInstrumentList->m_oIPInstrumentMap))
	{
		LeaveCriticalSection(&pErrorCodeThread->m_pLineList->m_oSecLineList);
		EnterCriticalSection(&pErrorCodeThread->m_pErrorCodeFrame->m_oSecErrorCodeFrame);
		GetFrameInfo(pErrorCodeThread->m_pErrorCodeFrame->m_cpRcvFrameData,
			pErrorCodeThread->m_pThread->m_pConstVar->m_iRcvFrameSize, &strFrameData);
		LeaveCriticalSection(&pErrorCodeThread->m_pErrorCodeFrame->m_oSecErrorCodeFrame);
		AddMsgToLogOutPutList(pErrorCodeThread->m_pThread->m_pLogOutPut, "ProcErrorCodeReturnFrameOne",
			strFrameData, ErrorType, IDS_ERR_IPSETMAP_NOTEXIT);
		return;
	}
	pInstrument = GetInstrumentFromMap(uiIPInstrument, 
		&pErrorCodeThread->m_pLineList->m_pInstrumentList->m_oIPInstrumentMap);
	if (FALSE == GetRoutByRoutIP(pInstrument->m_uiRoutIP, pErrorCodeThread->m_pLineList->m_pRoutList, &pRout))
	{
		LeaveCriticalSection(&pErrorCodeThread->m_pLineList->m_oSecLineList);
		EnterCriticalSection(&pErrorCodeThread->m_pErrorCodeFrame->m_oSecErrorCodeFrame);
		GetFrameInfo(pErrorCodeThread->m_pErrorCodeFrame->m_cpRcvFrameData,
			pErrorCodeThread->m_pThread->m_pConstVar->m_iRcvFrameSize, &strFrameData);
		LeaveCriticalSection(&pErrorCodeThread->m_pErrorCodeFrame->m_oSecErrorCodeFrame);
		AddMsgToLogOutPutList(pErrorCodeThread->m_pThread->m_pLogOutPut, "ProcErrorCodeReturnFrameOne",
			strFrameData, ErrorType, IDS_ERR_ROUT_NOTEXIT);
		return;
	}
	// ���������Ĵ��ʱ��
	UpdateInstrActiveTime(pInstrument);
	if (NULL == GetNextInstrAlongRout(pInstrument, pRout->m_iRoutDirection))
	{
		LeaveCriticalSection(&pErrorCodeThread->m_pLineList->m_oSecLineList);
		return;
	}
	str.Format(_T("����SN = 0x%x��IP = %d������λ�� = %d "), pInstrument->m_uiSN, pInstrument->m_uiIP, pInstrument->m_iPointIndex);
	strOutPut += str;
	strDebug += str;
	// ��������ΪLCI���߽���վ
	if ((pInstrument->m_iInstrumentType == InstrumentTypeLCI)
		|| (pInstrument->m_iInstrumentType == InstrumentTypeLAUX))
	{
		// ����վ����A���ݹ���
		if (pInstrument->m_uiErrorCodeReturnNum != 0)
		{
			if (pInstrument->m_cLAUXErrorCodeDataLineACountOld > cLAUXErrorCodeDataLineACount)
			{
				iTemp = 256 + cLAUXErrorCodeDataLineACount - pInstrument->m_cLAUXErrorCodeDataLineACountOld;
			}
			else
			{
				iTemp = cLAUXErrorCodeDataLineACount - pInstrument->m_cLAUXErrorCodeDataLineACountOld;
			}
			pInstrument->m_iLAUXErrorCodeDataLineACount += iTemp;
		}
		pInstrument->m_cLAUXErrorCodeDataLineACountOld = cLAUXErrorCodeDataLineACount;
		str.Format(_T("����A���ݹ�����=%d��"),iTemp);
		strOutPut += str;
		if (iTemp != 0)
		{
			strDebug += str;
		}
		// ����վ����B���ݹ���
		if (pInstrument->m_uiErrorCodeReturnNum != 0)
		{
			if (pInstrument->m_cLAUXErrorCodeDataLineBCountOld > cLAUXErrorCodeDataLineBCount)
			{
				iTemp = 256 + cLAUXErrorCodeDataLineBCount - pInstrument->m_cLAUXErrorCodeDataLineBCountOld;
			}
			else
			{
				iTemp = cLAUXErrorCodeDataLineBCount - pInstrument->m_cLAUXErrorCodeDataLineBCountOld;
			}
			pInstrument->m_iLAUXErrorCodeDataLineBCount += iTemp;
		}
		pInstrument->m_cLAUXErrorCodeDataLineBCountOld = cLAUXErrorCodeDataLineBCount;
		str.Format(_T("����B���ݹ�����=%d��"), iTemp);
		strOutPut += str;
		if (iTemp != 0)
		{
			strDebug += str;
		}
		// ����վ������A���ݹ���
		if (pInstrument->m_uiErrorCodeReturnNum != 0)
		{
			if (pInstrument->m_cLAUXErrorCodeDataLAUXLineACountOld > cLAUXErrorCodeDataLAUXLineACount)
			{
				iTemp = 256 + cLAUXErrorCodeDataLAUXLineACount - pInstrument->m_cLAUXErrorCodeDataLAUXLineACountOld;
			}
			else
			{
				iTemp = cLAUXErrorCodeDataLAUXLineACount - pInstrument->m_cLAUXErrorCodeDataLAUXLineACountOld;
			}
			pInstrument->m_iLAUXErrorCodeDataLAUXLineACount += iTemp;
		}
		pInstrument->m_cLAUXErrorCodeDataLAUXLineACountOld = cLAUXErrorCodeDataLAUXLineACount;
		str.Format(_T("������A���ݹ�����=%d��"), iTemp);
		strOutPut += str;
		if (iTemp != 0)
		{
			strDebug += str;
		}
		// ����վ������B���ݹ���
		if (pInstrument->m_uiErrorCodeReturnNum != 0)
		{
			if (pInstrument->m_cLAUXErrorCodeDataLAUXLineBCountOld > cLAUXErrorCodeDataLAUXLineBCount)
			{
				iTemp = 256 + cLAUXErrorCodeDataLAUXLineBCount - pInstrument->m_cLAUXErrorCodeDataLAUXLineBCountOld;
			}
			else
			{
				iTemp = cLAUXErrorCodeDataLAUXLineBCount - pInstrument->m_cLAUXErrorCodeDataLAUXLineBCountOld;
			}
			pInstrument->m_iLAUXErrorCodeDataLAUXLineBCount += iTemp;
		}
		pInstrument->m_cLAUXErrorCodeDataLAUXLineBCountOld = cLAUXErrorCodeDataLAUXLineBCount;
		str.Format(_T("������B���ݹ�����=%d��"), iTemp);
		strOutPut += str;
		if (iTemp != 0)
		{
			strDebug += str;
		}
		// ����վ����ڹ���
		if (pInstrument->m_uiErrorCodeReturnNum != 0)
		{
			if (pInstrument->m_cLAUXErrorCodeCmdCountOld > cLAUXErrorCodeCmdCount)
			{
				iTemp = 256 + cLAUXErrorCodeCmdCount - pInstrument->m_cLAUXErrorCodeCmdCountOld;
			}
			else
			{
				iTemp = cLAUXErrorCodeCmdCount - pInstrument->m_cLAUXErrorCodeCmdCountOld;
			}
			// LCI��������������
			if (pInstrument->m_iInstrumentType == InstrumentTypeLCI)
			{
				iTemp = 0;
			}
			pInstrument->m_iLAUXErrorCodeCmdCount += iTemp;
		}
		pInstrument->m_cLAUXErrorCodeCmdCountOld = cLAUXErrorCodeCmdCount;
		str.Format(_T("����ڹ�����=%d��"), iTemp);
		strOutPut += str;
		if (iTemp != 0)
		{
			strDebug += str;
		}
	}
	// ��������Ϊ�ɼ�վ���ߵ�Դվ
	else
	{
		// �ɼ�վ�͵�Դվ�������ݴ������
		if (pInstrument->m_uiErrorCodeReturnNum != 0)
		{
			if (pInstrument->m_cFDUErrorCodeDataCountOld > cFDUErrorCodeDataCount)
			{
				iTemp = 256 + cFDUErrorCodeDataCount - pInstrument->m_cFDUErrorCodeDataCountOld;
			}
			else
			{
				iTemp = cFDUErrorCodeDataCount - pInstrument->m_cFDUErrorCodeDataCountOld;
			}
			pInstrument->m_iFDUErrorCodeDataCount += iTemp;
		}
		pInstrument->m_cFDUErrorCodeDataCountOld = cFDUErrorCodeDataCount;
		str.Format(_T("�������ݴ������=%d��"), iTemp);
		strOutPut += str;
		if (iTemp != 0)
		{
			strDebug += str;
		}
		// �ɼ�վ�͵�Դվ����������
		if (pInstrument->m_uiErrorCodeReturnNum != 0)
		{
			if (pInstrument->m_cFDUErrorCodeCmdCountOld > cFDUErrorCodeCmdCount)
			{
				iTemp = 256 + cFDUErrorCodeCmdCount - pInstrument->m_cFDUErrorCodeCmdCountOld;
			}
			else
			{
				iTemp = cFDUErrorCodeCmdCount - pInstrument->m_cFDUErrorCodeCmdCountOld;
			}
			pInstrument->m_iFDUErrorCodeCmdCount += iTemp;
		}
		pInstrument->m_cFDUErrorCodeCmdCountOld = cFDUErrorCodeCmdCount;
		str.Format(_T("����������=%d��"), iTemp);
		strOutPut += str;
		if (iTemp != 0)
		{
			strDebug += str;
		}
	}
	pInstrument->m_uiErrorCodeReturnNum++;
	str.Format(_T("����֡��=%d "), pInstrument->m_uiErrorCodeReturnNum);
	strOutPut += str;
	if (pInstrument->m_iLAUXErrorCodeDataLineACount != 0)
	{
		str.Format(_T("����A���ݹ�������=%d��"),pInstrument->m_iLAUXErrorCodeDataLineACount);
		strDebug += str;
		bStrDebug = true;
	}
	if (pInstrument->m_iLAUXErrorCodeDataLineBCount != 0)
	{
		str.Format(_T("����B���ݹ�������=%d��"),pInstrument->m_iLAUXErrorCodeDataLineBCount);
		strDebug += str;
		bStrDebug = true;
	}
	if (pInstrument->m_iLAUXErrorCodeDataLAUXLineACount != 0)
	{
		str.Format(_T("������A���ݹ�������=%d��"),pInstrument->m_iLAUXErrorCodeDataLAUXLineACount);
		strDebug += str;
		bStrDebug = true;
	}
	if (pInstrument->m_iLAUXErrorCodeDataLAUXLineBCount != 0)
	{
		str.Format(_T("������B���ݹ�������=%d��"),pInstrument->m_iLAUXErrorCodeDataLAUXLineBCount);
		strDebug += str;
		bStrDebug = true;
	}
	if (pInstrument->m_iLAUXErrorCodeCmdCount != 0)
	{
		str.Format(_T("����ڹ�������=%d��"),pInstrument->m_iLAUXErrorCodeCmdCount);
		strDebug += str;
		bStrDebug = true;
	}
	if (pInstrument->m_iFDUErrorCodeDataCount != 0)
	{
		str.Format(_T("�������ݴ����������=%d��"),pInstrument->m_iFDUErrorCodeDataCount);
		strDebug += str;
		bStrDebug = true;
	}
	if (pInstrument->m_iFDUErrorCodeCmdCount != 0)
	{
		str.Format(_T("��������������=%d��"),pInstrument->m_iFDUErrorCodeCmdCount);
		strDebug += str;
		bStrDebug = true;
	}
	LeaveCriticalSection(&pErrorCodeThread->m_pLineList->m_oSecLineList);
	str.Format(_T("����ʱ�� = 0x%x"), uiSysTime);
	strOutPut += str;
	strConv = (CStringA)strOutPut;
	AddMsgToLogOutPutList(pErrorCodeThread->m_pLogOutPutErrorCode, "", strConv);
	if (bStrDebug == true)
	{
		OutputDebugString(strDebug);
	}
}
// ���������ѯӦ��֡
void ProcErrorCodeReturnFrame(m_oErrorCodeThreadStruct* pErrorCodeThread)
{
	ASSERT(pErrorCodeThread != NULL);
	// ֡��������Ϊ0
	int iFrameCount = 0;
	// �õ��װ���������˿�֡����
	EnterCriticalSection(&pErrorCodeThread->m_pErrorCodeFrame->m_oSecErrorCodeFrame);
	iFrameCount = GetFrameCount(pErrorCodeThread->m_pErrorCodeFrame->m_oErrorCodeFrameSocket,
		pErrorCodeThread->m_pThread->m_pConstVar->m_iRcvFrameSize, 
		pErrorCodeThread->m_pThread->m_pLogOutPut);
	LeaveCriticalSection(&pErrorCodeThread->m_pErrorCodeFrame->m_oSecErrorCodeFrame);
	// �ж�֡�����Ƿ����0
	if(iFrameCount > 0)
	{
		// ѭ������ÿ1֡
		for(int i = 0; i < iFrameCount; i++)
		{
			EnterCriticalSection(&pErrorCodeThread->m_pErrorCodeFrame->m_oSecErrorCodeFrame);
			// �õ�֡����
			if (false == GetFrameData(pErrorCodeThread->m_pErrorCodeFrame->m_oErrorCodeFrameSocket,
				pErrorCodeThread->m_pErrorCodeFrame->m_cpRcvFrameData, 
				pErrorCodeThread->m_pThread->m_pConstVar->m_iRcvFrameSize, 
				pErrorCodeThread->m_pThread->m_pLogOutPut))
			{
				LeaveCriticalSection(&pErrorCodeThread->m_pErrorCodeFrame->m_oSecErrorCodeFrame);
				continue;
			}
			LeaveCriticalSection(&pErrorCodeThread->m_pErrorCodeFrame->m_oSecErrorCodeFrame);
			if (false == ParseInstrErrorCodeReturnFrame(pErrorCodeThread->m_pErrorCodeFrame, 
				pErrorCodeThread->m_pThread->m_pConstVar, pErrorCodeThread->m_pThread->m_pLogOutPut))
			{
				AddMsgToLogOutPutList(pErrorCodeThread->m_pThread->m_pLogOutPut, 
					"ParseInstrumentErrorCodeReturnFrame","", 
					ErrorType, IDS_ERR_PARSE_ERRORCODERETURNFRAME);
				continue;
			}
			// ������IP��ַ����Ӧ��֡
			ProcErrorCodeReturnFrameOne(pErrorCodeThread);		
		}		
	}
}
// ���������ѯ֡
void ProcErrorCodeQueryFrame(m_oErrorCodeThreadStruct* pErrorCodeThread)
{
	ASSERT(pErrorCodeThread != NULL);
	hash_map<unsigned int, m_oRoutStruct*> ::iterator iter;
	m_oRoutStruct* pRout = NULL;
	m_oInstrumentStruct* pInstrument = NULL;
	CString str = _T("");
	string strConv = "";
	EnterCriticalSection(&pErrorCodeThread->m_pLineList->m_oSecLineList);
	for (iter = pErrorCodeThread->m_pLineList->m_pRoutList->m_oRoutMap.begin();
		iter != pErrorCodeThread->m_pLineList->m_pRoutList->m_oRoutMap.end();
		iter++)
	{
		pRout = iter->second;
		if (pRout->m_pTail != NULL)
		{
			pInstrument = pRout->m_pHead;
			do 
			{
				pInstrument = GetNextInstrAlongRout(pInstrument, pRout->m_iRoutDirection);
				if (pInstrument == NULL)
				{
					break;
				}
				pInstrument->m_uiErrorCodeQueryNum++;
			} while (pInstrument != pRout->m_pTail);
			// �㲥���������ѯ֡
			MakeInstrErrorCodeQueryFrame(pErrorCodeThread->m_pErrorCodeFrame,
				pErrorCodeThread->m_pThread->m_pConstVar, pRout->m_pTail->m_uiBroadCastPort,
				pErrorCodeThread->m_pThread->m_pLogOutPut);
			str.Format(_T("��·��IP = 0x%x�㲥���������ѯ֡"), pRout->m_uiRoutIP);
			strConv = (CStringA)str;
			AddMsgToLogOutPutList(pErrorCodeThread->m_pLogOutPutErrorCode, "", strConv);
		}
	}
	LeaveCriticalSection(&pErrorCodeThread->m_pLineList->m_oSecLineList);
}
// �̺߳���
DWORD WINAPI RunErrorCodeThread(m_oErrorCodeThreadStruct* pErrorCodeThread)
{
	ASSERT(pErrorCodeThread != NULL);
	bool bClose = false;
	bool bWork = false;
	while(true)
	{
		EnterCriticalSection(&pErrorCodeThread->m_oSecErrorCodeThread);
		bClose = pErrorCodeThread->m_pThread->m_bClose;
		bWork = pErrorCodeThread->m_pThread->m_bWork;
		LeaveCriticalSection(&pErrorCodeThread->m_oSecErrorCodeThread);
		if (bClose == true)
		{
			break;
		}
		if (bWork == true)
		{
			// ���������ѯӦ��֡
			ProcErrorCodeReturnFrame(pErrorCodeThread);
			// ���������ѯ֡
			ProcErrorCodeQueryFrame(pErrorCodeThread);
		}
		EnterCriticalSection(&pErrorCodeThread->m_oSecErrorCodeThread);
		bClose = pErrorCodeThread->m_pThread->m_bClose;
		LeaveCriticalSection(&pErrorCodeThread->m_oSecErrorCodeThread);
		if (bClose == true)
		{
			break;
		}
		WaitErrorCodeThread(pErrorCodeThread);
	}
	EnterCriticalSection(&pErrorCodeThread->m_oSecErrorCodeThread);
	// �����¼�����Ϊ���ź�״̬,�ͷŵȴ��̺߳��¼���Ϊ���ź�
	SetEvent(pErrorCodeThread->m_pThread->m_hThreadClose);
	LeaveCriticalSection(&pErrorCodeThread->m_oSecErrorCodeThread);
	return 1;
}
// ��ʼ�������ѯ�߳�
bool OnInitErrorCodeThread(m_oErrorCodeThreadStruct* pErrorCodeThread, 
	m_oLogOutPutStruct* pLogOutPut, m_oConstVarStruct* pConstVar)
{
	ASSERT(pErrorCodeThread != NULL);
	EnterCriticalSection(&pErrorCodeThread->m_oSecErrorCodeThread);
	if (false == OnInitThread(pErrorCodeThread->m_pThread, pLogOutPut, pConstVar))
	{
		LeaveCriticalSection(&pErrorCodeThread->m_oSecErrorCodeThread);
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
		LeaveCriticalSection(&pErrorCodeThread->m_oSecErrorCodeThread);
		AddMsgToLogOutPutList(pErrorCodeThread->m_pThread->m_pLogOutPut, "OnInitErrorCodeThread", 
			"pErrorCodeThread->m_pThread->m_hThread", ErrorType, IDS_ERR_CREATE_THREAD);
		return false;
	}
	LeaveCriticalSection(&pErrorCodeThread->m_oSecErrorCodeThread);
	AddMsgToLogOutPutList(pErrorCodeThread->m_pThread->m_pLogOutPut, "OnInitErrorCodeThread", 
		"�����ѯ�̴߳����ɹ�");
	return true;
}
// ��ʼ�������ѯ�߳�
bool OnInit_ErrorCodeThread(m_oEnvironmentStruct* pEnv)
{
	ASSERT(pEnv != NULL);
	pEnv->m_pErrorCodeThread->m_pLogOutPutErrorCode = pEnv->m_pLogOutPutErrorCode;
	pEnv->m_pErrorCodeThread->m_pErrorCodeFrame = pEnv->m_pErrorCodeFrame;
	pEnv->m_pErrorCodeThread->m_pLineList = pEnv->m_pLineList;
	return OnInitErrorCodeThread(pEnv->m_pErrorCodeThread, pEnv->m_pLogOutPutOpt, pEnv->m_pConstVar);
}
// �ر������ѯ�߳�
bool OnCloseErrorCodeThread(m_oErrorCodeThreadStruct* pErrorCodeThread)
{
	ASSERT(pErrorCodeThread != NULL);
	EnterCriticalSection(&pErrorCodeThread->m_oSecErrorCodeThread);
	if (false == OnCloseThread(pErrorCodeThread->m_pThread))
	{
		LeaveCriticalSection(&pErrorCodeThread->m_oSecErrorCodeThread);
		AddMsgToLogOutPutList(pErrorCodeThread->m_pThread->m_pLogOutPut, "OnCloseErrorCodeThread", 
			"�����ѯ�߳�ǿ�ƹر�", WarningType);
		return false;
	}
	LeaveCriticalSection(&pErrorCodeThread->m_oSecErrorCodeThread);
	AddMsgToLogOutPutList(pErrorCodeThread->m_pThread->m_pLogOutPut, "OnCloseErrorCodeThread", 
		"�����ѯ�̳߳ɹ��ر�");
	return true;
}
// �ͷ������ѯ�߳�
void OnFreeErrorCodeThread(m_oErrorCodeThreadStruct* pErrorCodeThread)
{
	ASSERT(pErrorCodeThread != NULL);
	if (pErrorCodeThread->m_pThread != NULL)
	{
		delete pErrorCodeThread->m_pThread;
		pErrorCodeThread->m_pThread = NULL;
	}
	DeleteCriticalSection(&pErrorCodeThread->m_oSecErrorCodeThread);
	delete pErrorCodeThread;
	pErrorCodeThread = NULL;
}