#pragma once
#include "afxsock.h"



// ADDataThread

class CADDataThread : public CWinThread
{
	DECLARE_DYNCREATE(CADDataThread)

public:
	CADDataThread();           // ��̬������ʹ�õ��ܱ����Ĺ��캯��
	virtual ~CADDataThread();
	virtual int Run();
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

protected:
	DECLARE_MESSAGE_MAP()
public:

	// ��ʼ��
	void OnInit(void);

	// �رղ������߳�
	void OnClose(void);
	// �̹߳رձ�־
	bool m_bclose;
	// �߳̽����¼�
	HANDLE m_hADDDataThreadClose;
	// AD���ݽ���Socket
	CSocket m_ADDataSocket;
	
	// AD���ݽ��ջ�����
	byte ADData[256];
};


