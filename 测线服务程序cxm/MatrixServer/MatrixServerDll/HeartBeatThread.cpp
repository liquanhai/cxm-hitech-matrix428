#include "stdafx.h"
#include "MatrixServerDll.h"

// ���������߳�
m_oHeartBeatThreadStruct* OnCreateHeartBeatThread(void)
{
	m_oHeartBeatThreadStruct* pHeartBeatThread = NULL;
	pHeartBeatThread = new m_oHeartBeatThreadStruct;
	pHeartBeatThread->m_pThread = new m_oThreadStruct;
	pHeartBeatThread->m_pHeartBeatFrame = NULL;
	InitializeCriticalSection(&pHeartBeatThread->m_oSecHeartBeatThread);
	return pHeartBeatThread;
}
// �̵߳ȴ�����
void WaitHeartBeatThread(m_oHeartBeatThreadStruct* pHeartBeatThread)
{
	if (pHeartBeatThread == NULL)
	{
		return;
	}
	// ��ʼ���ȴ�����Ϊ0
	int iWaitCount = 0;
	// ѭ��
	while(true)
	{	// ����50����
		Sleep(pHeartBeatThread->m_pThread->m_pConstVar->m_iOneSleepTime);
		// �ȴ�������1
		iWaitCount++;
		EnterCriticalSection(&pHeartBeatThread->m_oSecHeartBeatThread);
		// �ж��Ƿ���Դ��������
		if(pHeartBeatThread->m_pThread->m_bClose == true)
		{
			LeaveCriticalSection(&pHeartBeatThread->m_oSecHeartBeatThread);
			// ����
			return;
		}
		LeaveCriticalSection(&pHeartBeatThread->m_oSecHeartBeatThread);
		// �жϵȴ������Ƿ���ڵ������ȴ�����
		if(pHeartBeatThread->m_pThread->m_pConstVar->m_iHeartBeatSleepTimes == iWaitCount)
		{
			// ����
			return;
		}		
	}
}
// �̺߳���
DWORD WINAPI RunHeartBeatThread(m_oHeartBeatThreadStruct* pHeartBeatThread)
{
	if (pHeartBeatThread == NULL)
	{
		return 0;
	}
	while(true)
	{
		EnterCriticalSection(&pHeartBeatThread->m_oSecHeartBeatThread);
		if (pHeartBeatThread->m_pThread->m_bClose == true)
		{
			LeaveCriticalSection(&pHeartBeatThread->m_oSecHeartBeatThread);
			break;
		}
		if (pHeartBeatThread->m_pThread->m_bWork == true)
		{
			MakeInstrumentHeartBeatFrame(pHeartBeatThread->m_pHeartBeatFrame, 
				pHeartBeatThread->m_pThread->m_pConstVar);
			SendInstrumentHeartBeatFrame(pHeartBeatThread->m_pHeartBeatFrame, 
				pHeartBeatThread->m_pThread->m_pConstVar);
		}
		if (pHeartBeatThread->m_pThread->m_bClose == true)
		{
			LeaveCriticalSection(&pHeartBeatThread->m_oSecHeartBeatThread);
			break;
		}
		LeaveCriticalSection(&pHeartBeatThread->m_oSecHeartBeatThread);
		WaitHeartBeatThread(pHeartBeatThread);
	}
	EnterCriticalSection(&pHeartBeatThread->m_oSecHeartBeatThread);
	// �����¼�����Ϊ���ź�״̬,�ͷŵȴ��̺߳��¼���Ϊ���ź�
	SetEvent(pHeartBeatThread->m_pThread->m_hThreadClose);
	LeaveCriticalSection(&pHeartBeatThread->m_oSecHeartBeatThread);
	return 1;
}
// ��ʼ�������߳�
bool OnInitHeartBeatThread(m_oHeartBeatThreadStruct* pHeartBeatThread, 
	m_oLogOutPutStruct* pLogOutPut, m_oConstVarStruct* pConstVar)
{
	if (pHeartBeatThread == NULL)
	{
		return false;
	}
	EnterCriticalSection(&pHeartBeatThread->m_oSecHeartBeatThread);
	if (false == OnInitThread(pHeartBeatThread->m_pThread, pLogOutPut, pConstVar))
	{
		LeaveCriticalSection(&pHeartBeatThread->m_oSecHeartBeatThread);
		return false;
	}
	ResetEvent(pHeartBeatThread->m_pThread->m_hThreadClose);	// �����¼�����Ϊ���ź�״̬
	// �����߳�
	pHeartBeatThread->m_pThread->m_hThread = CreateThread((LPSECURITY_ATTRIBUTES)NULL, 
		0,
		(LPTHREAD_START_ROUTINE)RunHeartBeatThread,
		pHeartBeatThread, 
		0, 
		&pHeartBeatThread->m_pThread->m_dwThreadID);
	if (pHeartBeatThread->m_pThread->m_hThread == NULL)
	{
		AddMsgToLogOutPutList(pHeartBeatThread->m_pThread->m_pLogOutPut, "OnInitHeartBeatThread", 
			"pHeartBeatThread->m_pThread->m_hThread", ErrorType, IDS_ERR_CREATE_THREAD);
		LeaveCriticalSection(&pHeartBeatThread->m_oSecHeartBeatThread);
		return false;
	}
	AddMsgToLogOutPutList(pHeartBeatThread->m_pThread->m_pLogOutPut, "OnInitHeartBeatThread", 
		"�����̴߳����ɹ�");
	LeaveCriticalSection(&pHeartBeatThread->m_oSecHeartBeatThread);
	return true;
}
// ��ʼ�������߳�
bool OnInit_HeartBeatThread(m_oEnvironmentStruct* pEnv)
{
	if (pEnv == NULL)
	{
		return false;
	}
	pEnv->m_pHeartBeatThread->m_pHeartBeatFrame = pEnv->m_pHeartBeatFrame;
	return OnInitHeartBeatThread(pEnv->m_pHeartBeatThread, pEnv->m_pLogOutPutOpt, pEnv->m_pConstVar);
}
// �ر������߳�
bool OnCloseHeartBeatThread(m_oHeartBeatThreadStruct* pHeartBeatThread)
{
	if (pHeartBeatThread == NULL)
	{
		return false;
	}
	EnterCriticalSection(&pHeartBeatThread->m_oSecHeartBeatThread);
	if(false == OnCloseThread(pHeartBeatThread->m_pThread))
	{
		AddMsgToLogOutPutList(pHeartBeatThread->m_pThread->m_pLogOutPut, "OnCloseHeartBeatThread", 
			"�����߳�ǿ�ƹر�", WarningType);
		LeaveCriticalSection(&pHeartBeatThread->m_oSecHeartBeatThread);
		return false;
	}
	AddMsgToLogOutPutList(pHeartBeatThread->m_pThread->m_pLogOutPut, "OnCloseHeartBeatThread", 
		"�����̳߳ɹ��ر�");
	LeaveCriticalSection(&pHeartBeatThread->m_oSecHeartBeatThread);
	return true;
}
// �ͷ������߳�
void OnFreeHeartBeatThread(m_oHeartBeatThreadStruct* pHeartBeatThread)
{
	if (pHeartBeatThread == NULL)
	{
		return;
	}
	if (pHeartBeatThread->m_pThread != NULL)
	{
		delete pHeartBeatThread->m_pThread;
	}
	DeleteCriticalSection(&pHeartBeatThread->m_oSecHeartBeatThread);
	delete pHeartBeatThread;
}