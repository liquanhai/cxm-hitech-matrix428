#pragma once
#include "Parameter.h"


// CHeartBeatThread

class CHeartBeatThread : public CWinThread
{
	DECLARE_DYNCREATE(CHeartBeatThread)

public:
	CHeartBeatThread();           // ��̬������ʹ�õ��ܱ����Ĺ��캯��
	virtual ~CHeartBeatThread();
	virtual int Run();
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

protected:
	DECLARE_MESSAGE_MAP()
protected:
	// ֡����
	byte m_pFrameData[SndFrameSize];
public:
	// ԴIP��ַ
	unsigned int m_uiIPSource;
	// �̹߳رձ�־
	bool m_bclose;
	// �߳̽����¼�
	HANDLE m_hHeartBeatThreadClose;
	// ����Socket�׽���
	sockaddr_in m_RecvAddr, m_SendToAddr;
	SOCKET m_HeartBeatSocket;
protected:
	// ��������֡
	void MakeHeartBeatFrame(void);
	// ��������֡
	void SendHeartBeatFrame(void);
	// ��ֹ������ѭ���������޷���Ӧ��Ϣ
	void ProcessMessages(void);
public:
	// ��ʼ��
	void OnInit(void);
	// �رղ������߳�
	void OnClose(void);
	// �ر�UDP�׽���
	void OnCloseUDP(void);
};


