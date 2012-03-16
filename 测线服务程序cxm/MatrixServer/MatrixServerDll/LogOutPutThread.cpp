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
	// ѭ��
	while(true)
	{	// ����50����
		Sleep(pLogOutPutThread->m_pThread->m_pConstVar->m_iOneSleepTime);
		// �ȴ�������1
		iWaitCount++;
		// �ж��Ƿ���Դ��������
		if(pLogOutPutThread->m_pThread->m_bClose == true)
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
	while(true)
	{
		if (pLogOutPutThread->m_pThread->m_bClose == true)
		{
			break;
		}
		if (pLogOutPutThread->m_pThread->m_bWork == true)
		{
			WriteLogOutPutListToFile(pLogOutPutThread->m_pThread->m_pLogOutPut);
			WriteLogOutPutListToFile(pLogOutPutThread->m_pLogOutPutTimeDelay);
			WriteLogOutPutListToFile(pLogOutPutThread->m_pLogOutPutErrorCode);
			WriteLogOutPutListToFile(pLogOutPutThread->m_pLogOutPutADCFrameTime);
		}
		if (pLogOutPutThread->m_pThread->m_bClose == true)
		{
			break;
		}
		WaitLogOutPutThread(pLogOutPutThread);
	}
	// �����¼�����Ϊ���ź�״̬,�ͷŵȴ��̺߳��¼���Ϊ���ź�
	SetEvent(pLogOutPutThread->m_pThread->m_hThreadClose);
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
	if (false == OnInitThread(pLogOutPutThread->m_pThread, pLogOutPut, pConstVar))
	{
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
		AddMsgToLogOutPutList(pLogOutPutThread->m_pThread->m_pLogOutPut, "OnInitLogOutPutThread", 
			"pLogOutPutThread->m_pThread->m_hThread", ErrorType, IDS_ERR_CREATE_THREAD);
		return false;
	}
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
	if (false == OnCloseThread(pLogOutPutThread->m_pThread))
	{
		AddMsgToLogOutPutList(pLogOutPutThread->m_pThread->m_pLogOutPut, "OnCloseLogOutPutThread", 
			"��־����߳�ǿ�ƹر�", WarningType);
		return false;
	}
	else
	{
		AddMsgToLogOutPutList(pLogOutPutThread->m_pThread->m_pLogOutPut, "OnCloseLogOutPutThread", 
			"��־����̳߳ɹ��ر�");
		return true;
	}
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
	}
	delete pLogOutPutThread;
}