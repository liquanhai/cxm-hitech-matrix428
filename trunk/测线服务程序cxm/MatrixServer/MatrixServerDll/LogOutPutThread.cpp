#include "stdafx.h"
#include "MatrixServerDll.h"

// ������־����߳�
m_oLogOutPutThreadStruct* OnCreateLogOutPutThread(void)
{
	m_oLogOutPutThreadStruct* pLogOutPutThread = NULL;
	pLogOutPutThread = new m_oLogOutPutThreadStruct;
	pLogOutPutThread->m_pThread = new m_oThreadStruct;
	pLogOutPutThread->m_pLogOutPutTimeDelay = NULL;
	pLogOutPutThread->m_pLogOutPutErrorCode = NULL;
	pLogOutPutThread->m_pLogOutPutADCFrameTime = NULL;
	InitializeCriticalSection(&pLogOutPutThread->m_oSecLogOutPutThread);
	return pLogOutPutThread;
}
// �̵߳ȴ�����
void WaitLogOutPutThread(m_oLogOutPutThreadStruct* pLogOutPutThread)
{
	if (pLogOutPutThread == NULL)
	{
		return;
	}
	// ��ʼ���ȴ�����Ϊ0
	int iWaitCount = 0;
	bool bClose = false;
	// ѭ��
	while(true)
	{	// ����50����
		Sleep(pLogOutPutThread->m_pThread->m_pConstVar->m_iOneSleepTime);
		// �ȴ�������1
		iWaitCount++;
		EnterCriticalSection(&pLogOutPutThread->m_oSecLogOutPutThread);
		bClose = pLogOutPutThread->m_pThread->m_bClose;
		LeaveCriticalSection(&pLogOutPutThread->m_oSecLogOutPutThread);
		// �ж��Ƿ���Դ��������
		if(bClose == true)
		{
			// ����
			return;
		}
		// �жϵȴ������Ƿ���ڵ������ȴ�����
		if(pLogOutPutThread->m_pThread->m_pConstVar->m_iLogOutPutSleepTimes == iWaitCount)
		{
			// ����
			return;
		}		
	}
}
// �̺߳���
DWORD WINAPI RunLogOutPutThread(m_oLogOutPutThreadStruct* pLogOutPutThread)
{
	if (pLogOutPutThread == NULL)
	{
		return 0;
	}
	bool bClose = false;
	bool bWork = false;
	while(true)
	{
		EnterCriticalSection(&pLogOutPutThread->m_oSecLogOutPutThread);
		bClose = pLogOutPutThread->m_pThread->m_bClose;
		bWork = pLogOutPutThread->m_pThread->m_bWork;
		LeaveCriticalSection(&pLogOutPutThread->m_oSecLogOutPutThread);
		if (bClose == true)
		{
			break;
		}
		if (bWork == true)
		{
			WriteLogOutPutListToFile(pLogOutPutThread->m_pThread->m_pLogOutPut);
			WriteLogOutPutListToFile(pLogOutPutThread->m_pLogOutPutTimeDelay);
			WriteLogOutPutListToFile(pLogOutPutThread->m_pLogOutPutErrorCode);
			WriteLogOutPutListToFile(pLogOutPutThread->m_pLogOutPutADCFrameTime);
		}
		EnterCriticalSection(&pLogOutPutThread->m_oSecLogOutPutThread);
		bClose = pLogOutPutThread->m_pThread->m_bClose;
		LeaveCriticalSection(&pLogOutPutThread->m_oSecLogOutPutThread);
		if (bClose == true)
		{
			break;
		}
		WaitLogOutPutThread(pLogOutPutThread);
	}
	EnterCriticalSection(&pLogOutPutThread->m_oSecLogOutPutThread);
	// �����¼�����Ϊ���ź�״̬,�ͷŵȴ��̺߳��¼���Ϊ���ź�
	SetEvent(pLogOutPutThread->m_pThread->m_hThreadClose);
	LeaveCriticalSection(&pLogOutPutThread->m_oSecLogOutPutThread);
	return 1;
}
// ��ʼ����־����߳�
bool OnInitLogOutPutThread(m_oLogOutPutThreadStruct* pLogOutPutThread, 
	m_oLogOutPutStruct* pLogOutPut, m_oConstVarStruct* pConstVar)
{
	if (pLogOutPutThread == NULL)
	{
		return false;
	}
	EnterCriticalSection(&pLogOutPutThread->m_oSecLogOutPutThread);
	if (false == OnInitThread(pLogOutPutThread->m_pThread, pLogOutPut, pConstVar))
	{
		LeaveCriticalSection(&pLogOutPutThread->m_oSecLogOutPutThread);
		return false;
	}
	// �����¼�����Ϊ���ź�״̬
	ResetEvent(pLogOutPutThread->m_pThread->m_hThreadClose);
	// �����߳�
	pLogOutPutThread->m_pThread->m_hThread = CreateThread((LPSECURITY_ATTRIBUTES)NULL, 
		0,
		(LPTHREAD_START_ROUTINE)RunLogOutPutThread,
		pLogOutPutThread, 
		0, 
		&pLogOutPutThread->m_pThread->m_dwThreadID);
	if (pLogOutPutThread->m_pThread->m_hThread == NULL)
	{
		LeaveCriticalSection(&pLogOutPutThread->m_oSecLogOutPutThread);
		AddMsgToLogOutPutList(pLogOutPutThread->m_pThread->m_pLogOutPut, "OnInitLogOutPutThread", 
			"pLogOutPutThread->m_pThread->m_hThread", ErrorType, IDS_ERR_CREATE_THREAD);
		return false;
	}
	LeaveCriticalSection(&pLogOutPutThread->m_oSecLogOutPutThread);
	AddMsgToLogOutPutList(pLogOutPutThread->m_pThread->m_pLogOutPut, "OnInitLogOutPutThread", 
		"��־����̴߳����ɹ�");
	return true;
}
// ��ʼ����־����߳�
bool OnInit_LogOutPutThread(m_oEnvironmentStruct* pEnv)
{
	if (pEnv == NULL)
	{
		return false;
	}
	pEnv->m_pLogOutPutThread->m_pLogOutPutTimeDelay = pEnv->m_pLogOutPutTimeDelay;
	pEnv->m_pLogOutPutThread->m_pLogOutPutErrorCode = pEnv->m_pLogOutPutErrorCode;
	pEnv->m_pLogOutPutThread->m_pLogOutPutADCFrameTime = pEnv->m_pLogOutPutADCFrameTime;
	return OnInitLogOutPutThread(pEnv->m_pLogOutPutThread, pEnv->m_pLogOutPutOpt, pEnv->m_pConstVar);
}

// �ر���־����߳�
bool OnCloseLogOutPutThread(m_oLogOutPutThreadStruct* pLogOutPutThread)
{
	if (pLogOutPutThread == NULL)
	{
		return false;
	}
	EnterCriticalSection(&pLogOutPutThread->m_oSecLogOutPutThread);
	if (false == OnCloseThread(pLogOutPutThread->m_pThread))
	{
		LeaveCriticalSection(&pLogOutPutThread->m_oSecLogOutPutThread);
		AddMsgToLogOutPutList(pLogOutPutThread->m_pThread->m_pLogOutPut, "OnCloseLogOutPutThread", 
			"��־����߳�ǿ�ƹر�", WarningType);
		return false;
	}
	LeaveCriticalSection(&pLogOutPutThread->m_oSecLogOutPutThread);
	AddMsgToLogOutPutList(pLogOutPutThread->m_pThread->m_pLogOutPut, "OnCloseLogOutPutThread", 
		"��־����̳߳ɹ��ر�");
	return true;
}
// �ͷ���־����߳�
void OnFreeLogOutPutThread(m_oLogOutPutThreadStruct* pLogOutPutThread)
{
	if (pLogOutPutThread == NULL)
	{
		return;
	}
	if (pLogOutPutThread->m_pThread != NULL)
	{
		delete pLogOutPutThread->m_pThread;
		pLogOutPutThread->m_pThread = NULL;
	}
	DeleteCriticalSection(&pLogOutPutThread->m_oSecLogOutPutThread);
	delete pLogOutPutThread;
	pLogOutPutThread = NULL;
}