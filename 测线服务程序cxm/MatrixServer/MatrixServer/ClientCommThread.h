#pragma once
#include "CommProtocol.h"
class CClientCommThread
{
public:
	CClientCommThread(void);
	~CClientCommThread(void);
public:
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
public:
	// ������
	virtual void OnProc(void);
};

