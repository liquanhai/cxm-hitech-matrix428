#pragma once
class CCommThread
{
public:
	CCommThread(void);
	~CCommThread(void);
protected:
	/** �߳�ID*/
	DWORD m_dwThreadID;
	/** �̹߳ر��¼�*/
	HANDLE m_hThreadClose;
	/** �̹߳رձ�־λ*/
	bool m_bClose;
public:
	/** �߳̾��*/
	HANDLE m_hThread;
	/** �̺߳����ȴ�һ�ε�ʱ��*/
	unsigned int m_uiThreadSleepTime;
	/** �̺߳����ȴ��Ĵ���*/
	unsigned int m_uiThreadSleepCount;
public:
	/**
	* @fn void OnInit(void)
	* @detail ��ʼ��
	*/
	void OnInit(void);
	/**
	* @fn void OnClose(void)
	* @detail �ر�
	*/
	void OnClose(void);
	/**
	* @fn DWORD ThreadRunFunc(void)
	* @detail �̺߳���
	* @return DWORD
	*/
	DWORD ThreadRunFunc(void);
	/**
	* @fn void WaitForThread(void)
	* @detail �̵߳ȴ�����
	*/
	void WaitForThread(void);
	/**
	* @fn void OnProc(void)
	* @detail ������
	* @note �麯��
	*/
	virtual void OnProc(void);
};

