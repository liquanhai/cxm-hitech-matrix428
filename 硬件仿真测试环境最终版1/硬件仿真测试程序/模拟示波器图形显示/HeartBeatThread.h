#pragma once



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
public:
	CSocket m_HeartBeatSocket;
	// ֡��С
	int m_iFrameSize;
	// ֡����
	byte m_pFrameData[256];
	// ԴIP��ַ
	unsigned int m_uiIPSource;
	// Ŀ��IP��ַ
	unsigned int m_uiIPAim;
	// Ŀ��˿ں�
	unsigned short m_usPortAim;
	// ����� 1-��������Ӧ��2-��ѯ����Ӧ��3-AD���������ط�
	unsigned short m_usCommand;
	// ��ʼ��
	void OnInit(void);
	// �رղ������߳�
	void OnClose(void);
	// �̹߳رձ�־
	bool m_bclose;
	// �߳̽����¼�
	HANDLE m_hHeartBeatThreadClose;
	// ��������֡
	void MakeHeartBeatFrame(void);
	// ��������֡
	void SendHeartBeatFrame(void);
};


