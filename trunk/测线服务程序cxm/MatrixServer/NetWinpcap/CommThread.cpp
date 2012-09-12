#include "StdAfx.h"
#include "CommThread.h"


CCommThread::CCommThread(void)
	: m_dwThreadID(0)
	, m_hThread(INVALID_HANDLE_VALUE)
	, m_hThreadClose(INVALID_HANDLE_VALUE)
	, m_hThreadStop(INVALID_HANDLE_VALUE)
	, m_uiThreadSleepTime(1)
{
}


CCommThread::~CCommThread(void)
{
}

/**
* @fn DWORD WINAPI RunThread(CCommThread* pClientCommThread)
* @detail �̺߳���
* @param[in] pClientCommThread ͨѶ�߳���ָ��	
* @return DWORD
*/
DWORD WINAPI RunThread(CCommThread* pCommThread)
{
	return pCommThread->ThreadRunFunc();
}

// ��ʼ��
void CCommThread::OnInit(void)
{
	m_hThreadClose = CreateEvent(false, false, NULL, NULL);
	m_hThreadStop = CreateEvent(false, false, NULL, NULL);
	ResetEvent(m_hThreadClose);
	ResetEvent(m_hThreadStop);
	m_hThread = CreateThread((LPSECURITY_ATTRIBUTES)NULL, 
		0,
		(LPTHREAD_START_ROUTINE)RunThread,
		this, 
		0, 
		&m_dwThreadID);
}

// �ر�
void CCommThread::OnClose(void)
{
	if (m_hThread == INVALID_HANDLE_VALUE)
	{
		return;
	}
	SetEvent(m_hThreadStop);
	if (WaitForSingleObject(m_hThreadClose, 100) != WAIT_OBJECT_0)
	{
		TerminateThread(m_hThread, 0);
	}
	else
	{
		CloseHandle(m_hThread);
		m_hThread = INVALID_HANDLE_VALUE;
	}
	CloseHandle(m_hThreadClose);
	CloseHandle(m_hThreadStop);
	m_hThreadClose = INVALID_HANDLE_VALUE;
	m_hThreadStop = INVALID_HANDLE_VALUE;
}

// �̺߳���
DWORD CCommThread::ThreadRunFunc(void)
{
	while (1)
	{
		OnProc();
		if(WaitForSingleObject(m_hThreadStop, m_uiThreadSleepTime) == WAIT_OBJECT_0)	break;
	}
	SetEvent(m_hThreadClose);
	return 1;
}

// ������
void CCommThread::OnProc(void)
{
}