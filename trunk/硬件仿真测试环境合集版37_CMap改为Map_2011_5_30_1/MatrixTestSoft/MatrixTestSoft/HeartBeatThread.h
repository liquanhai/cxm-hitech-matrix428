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
	CString m_csIPSource;
	// �̹߳رձ�־
	bool m_bclose;
	// �߳̽����¼�
	HANDLE m_hHeartBeatThreadClose;
	// ���Ͷ˿�
	unsigned int m_uiSendPort;
	// ����Socket�׽���
	sockaddr_in addr, addr2;
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
};


