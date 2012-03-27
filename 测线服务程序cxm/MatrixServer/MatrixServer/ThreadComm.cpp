#include "StdAfx.h"
#include "ThreadComm.h"


CThreadComm::CThreadComm(void)
	: m_dwThreadID(0)
	, m_bClose(false)
	, m_hThread(INVALID_HANDLE_VALUE)
	, m_hThreadClose(INVALID_HANDLE_VALUE)
{
}


CThreadComm::~CThreadComm(void)
{
}

// �̺߳���
DWORD WINAPI RunThread(CThreadComm* pClass)
{
	return pClass->ThreadRunFunc();
}
// ��ʼ��
void CThreadComm::OnInit(void)
{
	// ����Server�˿ڼ���
	if (FALSE == m_oConnectClients.OnCreateSocketListen(INADDR_ANY, ServerListenPort, ConnectClientNumLimit))
	{
		return;
	}
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
void CThreadComm::OnClose(void)
{
	if (m_hThread == INVALID_HANDLE_VALUE)
	{
		return;
	}
	m_bClose = true;
	int iResult = WaitForSingleObject(m_hThreadClose, WaitForCloseCommThreadTimes);
	if (iResult != WAIT_OBJECT_0)
	{
		TerminateThread(m_hThread, 0);
	}
	CloseHandle(m_hThread);
	CloseHandle(m_hThreadClose);
}


// �̺߳���
DWORD CThreadComm::ThreadRunFunc(void)
{
	while (1)
	{
		if (m_bClose == true)
		{
			break;
		}
		if (FALSE == OnProcComm())
		{
			break;
		}
	}
	SetEvent(m_hThreadClose);
	return 1;
}


// ������
BOOL CThreadComm::OnProcComm(void)
{
	return m_oConnectClients.OnProcComm();
}
