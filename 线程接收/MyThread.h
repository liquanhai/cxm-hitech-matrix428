#pragma once
#include "afxsock.h"



// CMyThread

class CMyThread : public CWinThread
{
	DECLARE_DYNCREATE(CMyThread)

public:
	CMyThread();           // ��̬������ʹ�õ��ܱ����Ĺ��캯��
	virtual ~CMyThread();

public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

protected:
	DECLARE_MESSAGE_MAP()
public:
	// Socket����
	CSocket m_Socket;
	virtual int Run();
	// ���յ����ֽ���
	unsigned int m_uiRcvByteNum;
};


