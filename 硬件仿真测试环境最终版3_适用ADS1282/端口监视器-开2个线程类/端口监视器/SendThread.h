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
	// �߳̽����¼�
	HANDLE m_hSendThreadClose;
	//CPortMonitoringDlg* m_pTDoc;
	// ��ʼ��
	void Init();
	bool m_close;
	void OnClose();
	void OnReset();
	// ���ݽ��ջ���
	unsigned char udp_buf[8][256];
	unsigned char udp_count;
	// �װ�����
	unsigned int m_uiHeadFrameNum;
	// IP��ַ���ü���
	unsigned int m_uiIPSetReturnNum;
	// β������
	unsigned int m_uiTailFrameNum;
	// β��ʱ�̲�ѯӦ�����
	unsigned int m_uiTailTimeReturnNum;
	// ʱ������Ӧ�����
	unsigned int m_uiDelayTimeReturnNum;
	// ADC����Ӧ�����
	unsigned int m_uiADCSetReturnNum;
	// ADC���ݲɼ�֡����
	unsigned int m_uiADCDataRecNum;
	// ��ʾ�װ�֡������SN���װ�ʱ��
	CString m_csHeadFrameShow;
	// ��ʾIP��ַ����Ӧ��֡������SN�����õ�IP��ַ
	CString m_csIPSetReturnShow;
	// ��ʾβ��֡������SN
	CString m_csTailFrameShow;
	// ��ʾβ��ʱ�̲�ѯӦ��֡������IP��ַ�Ͳ�ѯ���
	CString m_csTailTimeReturnShow;
	// ��ʾʱ������Ӧ��֡������IP��ַ����������
	CString m_csDelayTimeReturnShow;
	// ��ʾADC��������֡������IP��ַ��֡�����Ͳ�������֡����
	CString m_csADCDataRecShow;
	// ��ʾ״̬��ѯӦ��֡����������ʱ�䡢TBʱ���λ��TBʱ���λ��TCʱ���λ��TCʱ���λ��TEʱ���λ��TEʱ���λ��3D����
	CString m_csGetStatusReturnShow;
	// ����֡��
	unsigned int m_uiRecFrameNum;
	// ADC���ݲɼ���һ֡������ָ��ƫ����
	unsigned short m_usADCLastDataPoint;
};


