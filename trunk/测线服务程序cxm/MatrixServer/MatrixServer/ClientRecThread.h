#pragma once
#include "ClientRecFrame.h"

class CClientRecThread
{
public:
	CClientRecThread(void);
	~CClientRecThread(void);
	// ��ʼ��
	void OnInit(void);
	// �ر�
	void OnClose(void);
	// �߳̾��
	HANDLE m_hThread;
	// �߳�ID
	DWORD m_dwThreadID;
	// �̺߳���
	DWORD ThreadRunFunc(void);
	// �̹߳ر��¼�
	HANDLE m_hThreadClose;
	// �߳�ִ���¼�
	HANDLE m_hThreadRun;
	// ���տͻ�����ָ��
	CClientRecFrame* m_pClientRecFrame;
	// �������֡
	void OnProcRecFrame(void);
};

