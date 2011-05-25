#pragma once

#define IPSource "127.0.0.1"
#define RecGPSPort 0x8210

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
	// GPS֡����Socket
	CSocket m_Socket;
	// �̹߳رձ�־λ
	bool m_bclose;
	// �߳̽����¼�
	HANDLE m_hRecThreadClose;
	// ���յ���GPS֡
	byte m_pRecFrameData[256]; 
	// ֡ͷ����
	CString m_csHeadFrame;
	// UTCʱ�����
	double m_dUTCTime;
	// ״̬����
	CString m_csStatus;
	// γ��ֵ����
	double m_dLatitudeValue;
	// γ�ȱ���
	CString m_csLatitude;
	// ����ֵ����
	double m_dLongitudeValue;
	// ���ȱ���
	CString m_csLongitude;
	// �ٶȱ���
	double m_dSpeed;
	// ��λ�Ǳ���
	double m_dAzimuth;
	// UTC���ڱ���
	CString m_csUTCData;
	// ��ƫ�Ǳ���
	double m_dMagneticdeclination;
	// ��ƫ�Ƿ���
	CString m_csMagneticdeclination_Direction;
	// ģʽ����
	CString m_csMode;
	// У���
	char m_cCheckSum;
public:
	
	// �̳߳�ʼ��
	void Init(void);
	// �̹߳ر�
	void OnClose(void);
	// ������GPS֡
	void ProcGPSFrameOne(void);
	// ����
	void OnReset(void);
};


