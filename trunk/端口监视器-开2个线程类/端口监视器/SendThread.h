#pragma once


// CSendThread

class CSendThread : public CWinThread
{

	DECLARE_DYNCREATE(CSendThread)

public:
	CSendThread();           // ��̬������ʹ�õ��ܱ����Ĺ��캯��
	virtual ~CSendThread();
	virtual int Run();
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

protected:
	DECLARE_MESSAGE_MAP()
public:
	CSocket m_hSocket2;
	//CPortMonitoringDlg* m_pTDoc;
	// ��ʼ��
	void Init();
	bool m_close;
	void OnClose();
	unsigned char udp_buf[8][256];
	unsigned char udp_count;
};


