#pragma once
// �̺߳����ĵȴ�ʱ��
#define WaitForSendThreadSleepTimes	100
// �̹߳رյĵȴ�ʱ��
#define WaitForCloseSendThreadTimes	500
class CThreadSend
{
public:
	CThreadSend(void);
	~CThreadSend(void);
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
};

