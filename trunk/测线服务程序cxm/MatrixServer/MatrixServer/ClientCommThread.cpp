/**
@brief ���ļ�Ϊ�������ͻ���ͨѶ�̵߳�ʵ���ļ�
@details
@file ClientCommThread.cpp
@note 
@see	
@version	
@author cxm
@bug
*/
#include "StdAfx.h"
#include "ClientCommThread.h"

CClientCommThread::CClientCommThread(void)
	: m_dwThreadID(0)
	, m_hThread(INVALID_HANDLE_VALUE)
	, m_hThreadClose(INVALID_HANDLE_VALUE)
	, m_bClose(false)
{
}

CClientCommThread::~CClientCommThread(void)
{
}

/**
* @fn DWORD WINAPI RunThread(CClientCommThread* pClientCommThread)
* @detail �̺߳���
* @param[in] pClientCommThread ͨѶ�߳���ָ��	
* @return DWORD
*/
DWORD WINAPI RunThread(CClientCommThread* pClientCommThread)
{
	return pClientCommThread->ThreadRunFunc();
}

// ��ʼ��
void CClientCommThread::OnInit(void)
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
void CClientCommThread::OnClose(void)
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
void CClientCommThread::WaitForThread(void)
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
DWORD CClientCommThread::ThreadRunFunc(void)
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
void CClientCommThread::OnProc(void)
{
}