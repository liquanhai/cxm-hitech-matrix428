#pragma once



// CShowThread

class CShowThread : public CWinThread
{
	DECLARE_DYNCREATE(CShowThread)

public:
	CShowThread();           // ��̬������ʹ�õ��ܱ����Ĺ��캯��
	virtual ~CShowThread();
	virtual int Run();
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

public:
	// ��ʼ��
	void Init();
	bool m_close;
	void OnClose();
	int m_icsEditShowLength;	// ��һ�ε��ַ������� 
protected:
	DECLARE_MESSAGE_MAP()
};


