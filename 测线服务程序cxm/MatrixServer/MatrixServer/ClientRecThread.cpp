#include "StdAfx.h"
#include "ClientRecThread.h"


CClientRecThread::CClientRecThread(void)
	: m_dwThreadID(0)
	, m_hThread(INVALID_HANDLE_VALUE)
	, m_hThreadClose(INVALID_HANDLE_VALUE)
	, m_hThreadRun(INVALID_HANDLE_VALUE)
	, m_pClientRecFrame(NULL)
{
}


CClientRecThread::~CClientRecThread(void)
{
}

// �̺߳���
DWORD WINAPI RunThread(CClientRecThread* pClientRecThread)
{
	return pClientRecThread->ThreadRunFunc();
}
// ��ʼ��
void CClientRecThread::OnInit(void)
{
	m_hThreadClose = CreateEvent(false, false, NULL, NULL);
	m_hThreadRun = CreateEvent(false, false, NULL, NULL);
	ResetEvent(m_hThreadClose);
	ResetEvent(m_hThreadRun);
	m_hThread = CreateThread((LPSECURITY_ATTRIBUTES)NULL, 
		0,
		(LPTHREAD_START_ROUTINE)RunThread,
		this, 
		0, 
		&m_dwThreadID);
}


// �ر�
void CClientRecThread::OnClose(void)
{
	if (m_hThread == INVALID_HANDLE_VALUE)
	{
		return;
	}
	SetEvent(m_hThreadRun);
	if (WaitForSingleObject(m_hThreadClose, CloseClientRecThreadTimes) != WAIT_OBJECT_0)
	{
		TerminateThread(m_hThread, 0);
	}
	CloseHandle(m_hThread);
	CloseHandle(m_hThreadRun);
	CloseHandle(m_hThreadClose);
}


// �̺߳���
DWORD CClientRecThread::ThreadRunFunc(void)
{
	while (1)
	{
		OnProcRecFrame();
		if(WaitForSingleObject(m_hThreadRun, RunClientRecThreadTimes) == WAIT_OBJECT_0) 
		{
			break;
		}
	}
	SetEvent(m_hThreadClose);
	return 1;
}

// �������֡
void CClientRecThread::OnProcRecFrame(void)
{
	int iFrameNum = 0;
	m_oCommFrameStructPtr ptrFrame = NULL;
	EnterCriticalSection(&m_pClientRecFrame->m_oSecClientFrame);
	iFrameNum = m_pClientRecFrame->m_olsCommWorkFrame.size();
	for (int i=0; i<iFrameNum; i++)
	{
		ptrFrame = *m_pClientRecFrame->m_olsCommWorkFrame.begin();
		// ���Ϊ����֡
		if (ptrFrame->m_cCmdType == CmdTypeSet)
		{
			// ��֡���ݼ��������������
		}
		// ���ΪӦ��֡
		else if (ptrFrame->m_cCmdType == CmdTypeReturn)
		{
			// ���ѷ���֡�������ҵ���֡
		}
		m_pClientRecFrame->m_olsCommWorkFrame.pop_front();
	}
	LeaveCriticalSection(&m_pClientRecFrame->m_oSecClientFrame);
}
