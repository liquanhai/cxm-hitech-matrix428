// ThreadProcHeartBeat.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MatrixServer.h"
#include "ThreadProcHeartBeat.h"
#include "Parameter.h"

// CThreadProcHeartBeat

IMPLEMENT_DYNCREATE(CThreadProcHeartBeat, CWinThread)

CThreadProcHeartBeat::CThreadProcHeartBeat()
{
	// �Ƿ���״̬
	m_bWork = false;
	// �Ƿ�ر��߳�
	m_bClose = false;
}

CThreadProcHeartBeat::~CThreadProcHeartBeat()
{
}

BOOL CThreadProcHeartBeat::InitInstance()
{
	// TODO: �ڴ�ִ���������̳߳�ʼ��
	return TRUE;
}

int CThreadProcHeartBeat::ExitInstance()
{
	// TODO: �ڴ�ִ���������߳�����
	return CWinThread::ExitInstance();
}

BEGIN_MESSAGE_MAP(CThreadProcHeartBeat, CWinThread)
END_MESSAGE_MAP()

// CThreadProcHeartBeat ��Ϣ�������

/**
* �߳�������
* @param void
* @return int
*/
int CThreadProcHeartBeat::Run()
{
	// ѭ����ֱ���رձ�־Ϊ��
	while(true)
	{
		// �жϹرձ�־�Ƿ�Ϊ��
		if(true == m_bClose)
		{
			// ����ѭ��
			break;
		}
		// ��������֡
		SendHeartBeatFrame();
		// �жϹرձ�־�Ƿ�Ϊ��
		if(true == m_bClose)
		{
			// ����ѭ��
			break;
		}
		// ����250ms
		Wait(HertBeatSleepTimes);
	}
	// ���������̹߳رձ�־Ϊ��
	m_pSiteData->m_bProcHeartBeatClose = true;
	// ����
	return CWinThread::Run();
}

/**
* ��ʼ���߳�
* @param void
* @return bool true���ɹ���false��ʧ��
*/
bool CThreadProcHeartBeat::OnInit()
{
	// �Ƿ���״̬
	m_bWork = false;
	// �Ƿ�ر��߳�
	m_bClose = false;
	return true;
}

/**
* �ر��߳�
* @param void
* @return bool true���ɹ���false��ʧ��
*/
bool CThreadProcHeartBeat::OnClose()
{
	// �Ƿ�ر��߳�
	m_bClose = true;
	return true;
}

/**
* �߳̿�ʼ����
* @param void
* @return bool true���ɹ���false��ʧ��
*/
bool CThreadProcHeartBeat::OnWork()
{
	// �Ƿ���״̬
	m_bWork = true;
	return true;
}

/**
* �߳�ֹͣ����
* @param void
* @return bool true���ɹ���false��ʧ��
*/
bool CThreadProcHeartBeat::OnStop()
{
	// �Ƿ���״̬
	m_bWork = false;
	return true;
}

/**
* �̵߳ȴ�
* @param int iWaitStopCount ���ȴ�������ÿ��50����
* @return void
*/
void CThreadProcHeartBeat::Wait(int iWaitStopCount)
{
	// ��ʼ���ȴ�����Ϊ0
	int iWaitCount = 0;
	// ѭ��
	while(true)
	{	// ����50����
		Sleep(OneSleepTime);
		// �ȴ�������1
		iWaitCount++;
		// �ж��Ƿ���Դ��������
		if(false == JudgeProcCondition())
		{
			// ����
			return;
		}
		// �жϵȴ������Ƿ���ڵ������ȴ�����
		if(iWaitStopCount <= iWaitCount)
		{
			// ����
			return;
		}		
	}
}

/**
* �ж��Ƿ���Դ��������
* @param void
* @return bool true����������false��ֹͣ����
*/
bool CThreadProcHeartBeat::JudgeProcCondition()
{	
	if(false == m_bWork)	// �ǹ���״̬
	{		
		m_pSiteData->m_bProcHeartBeatStop = true;	// ���������߳�ֹͣ
		return false;
	}
	else	// ����״̬
	{
		m_pSiteData->m_bProcHeartBeatStop = false;	// ���������̹߳���
		return true;
	}
}

/**
* ��������֡
* @param void
* @return void
*/
void CThreadProcHeartBeat::SendHeartBeatFrame()
{
	if(false == m_bWork)	// �Ƿ���״̬
	{
		return;
	}
	// ��������֡
	m_pSocketHeartBeatFrame->SendIHeartBeatFrame();
}