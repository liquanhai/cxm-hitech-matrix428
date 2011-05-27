#pragma once


// CRecThread

class CRecThread : public CWinThread
{
	
	DECLARE_DYNCREATE(CRecThread)

public:
	CRecThread();           // ��̬������ʹ�õ��ܱ����Ĺ��캯��
	virtual ~CRecThread();
	virtual int Run();
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

protected:
	DECLARE_MESSAGE_MAP()
public:
	CSocket m_hSocket1;
	// ��ʼ��
	void Init();
	bool m_close;
	void OnClose();
	unsigned char udp_buf[8][128];
	unsigned char udp_count;
	// UDP����ָ֡��ƫ����
	unsigned int m_uiUdpCount;
	// UDP���ջ�����
	unsigned char m_ucUdpBuf[8192];
	
};


