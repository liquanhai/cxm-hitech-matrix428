#pragma once
#include "ConnectClients.h"
// �����������˿�
#define ServerListenPort		5150
// �������������ӵĿͻ��˸���
#define ConnectClientNumLimit	10
// �̹߳رյĵȴ�ʱ��
#define WaitForCloseCommThreadTimes	500
class CThreadComm
{
public:
	CThreadComm(void);
	~CThreadComm(void);
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
	// �رձ�־λ
	bool m_bClose;
	// ������
	BOOL OnProcComm(void);
	// ���ӵĿͻ��˶���
	CConnectClients m_oConnectClients;
};

