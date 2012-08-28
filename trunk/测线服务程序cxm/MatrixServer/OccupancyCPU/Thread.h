#pragma once



// CThread

class CThread : public CWinThread
{
	DECLARE_DYNCREATE(CThread)

public:
	CThread();           // ��̬������ʹ�õ��ܱ����Ĺ��캯��
	virtual ~CThread();

public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
public:
	CRITICAL_SECTION m_oSec;
	bool m_bClose;
	void Close();
protected:
	DECLARE_MESSAGE_MAP()
public:
	virtual int Run();
};


