#pragma once
#include "CommProtocol.h"
/**
* @brief ��ͻ���ͨѶ�̻߳���
*/
class CClientCommThread
{
public:
	CClientCommThread(void);
	virtual ~CClientCommThread(void);
public:
	/** ��ʼ��*/
	void OnInit(void);
	/** �ر�*/
	void OnClose(void);
	/** �߳̾��*/
	HANDLE m_hThread;
	/** �߳�ID*/
	DWORD m_dwThreadID;
	/** �̺߳���*/
	DWORD ThreadRunFunc(void);
	/** �̵߳ȴ�����*/
	void WaitForThread(void);
	/** �̹߳ر��¼�*/
	HANDLE m_hThreadClose;
	/** �̹߳رձ�־λ*/
	bool m_bClose;
public:
	/** ������*/
	virtual void OnProc(void);
};

