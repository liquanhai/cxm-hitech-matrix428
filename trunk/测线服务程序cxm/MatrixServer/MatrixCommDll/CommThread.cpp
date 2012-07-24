#include "stdafx.h"
#include "MatrixCommDll.h"

CCommThread::CCommThread(void)
	: m_dwThreadID(0)
	, m_hThread(INVALID_HANDLE_VALUE)
	, m_hThreadClose(INVALID_HANDLE_VALUE)
	, m_bClose(false)
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
DWORD WINAPI RunThread(CCommThread* pClientCommThread)
{
	return pClientCommThread->ThreadRunFunc();
}

// ��ʼ��
void CCommThread::OnInit(void)
{
	m_hThreadClose = CreateEvent(false, false, NULL, NULL);
	ResetEvent(m_hThreadClose);
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
	m_bClose = true;
	if (WaitForSingleObject(m_hThreadClose, CloseClientCommThreadTimes) != WAIT_OBJECT_0)
	{
		TerminateThread(m_hThread, 0);
	}
	else
	{
		CloseHandle(m_hThread);
		m_hThread = INVALID_HANDLE_VALUE;
	}
	CloseHandle(m_hThreadClose);
	m_hThreadClose = INVALID_HANDLE_VALUE;
}

// �̵߳ȴ�����
void CCommThread::WaitForThread(void)
{
	// ��ʼ���ȴ�����Ϊ0
	int iWaitCount = 0;
	// ѭ��
	while(true)
	{	// ����50����
		Sleep(ClientCommThreadWaitTime);
		// �ȴ�������1
		iWaitCount++;
		// �ж��Ƿ���Դ��������
		if(m_bClose == true)
		{
			// ����
			return;
		}
		// �жϵȴ������Ƿ���ڵ������ȴ�����
		if(iWaitCount == ClientCommThreadWaitTimes)
		{
			// ����
			return;
		}		
	}
}

// �̺߳���
DWORD CCommThread::ThreadRunFunc(void)
{
	while (1)
	{
		if (m_bClose == true)
		{
			break;
		}
		OnProc();
		if (m_bClose == true)
		{
			break;
		}
		WaitForThread();
	}
	SetEvent(m_hThreadClose);
	return 1;
}

// ������
void CCommThread::OnProc(void)
{
}