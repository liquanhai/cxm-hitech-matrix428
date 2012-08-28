// Thread.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "OccupancyCPU.h"
#include "Thread.h"


// CThread

IMPLEMENT_DYNCREATE(CThread, CWinThread)

CThread::CThread()
{
	m_bClose = false;
}

CThread::~CThread()
{
}

BOOL CThread::InitInstance()
{
	// TODO: �ڴ�ִ���������̳߳�ʼ��
	InitializeCriticalSection(&m_oSec);
	return TRUE;
}

int CThread::ExitInstance()
{
	// TODO: �ڴ�ִ���������߳�����
	return CWinThread::ExitInstance();
}

BEGIN_MESSAGE_MAP(CThread, CWinThread)
END_MESSAGE_MAP()


// CThread ��Ϣ�������


int CThread::Run()
{
	// TODO: �ڴ����ר�ô����/����û���
	bool bClose = false;
	while(1)
	{
		EnterCriticalSection(&m_oSec);
		bClose = m_bClose;
		LeaveCriticalSection(&m_oSec);
		if (bClose == true)
		{
			break;
		}
	}
	DeleteCriticalSection(&m_oSec);
	return CWinThread::Run();
}
void CThread::Close()
{
	EnterCriticalSection(&m_oSec);
	m_bClose = true;
	LeaveCriticalSection(&m_oSec);
}