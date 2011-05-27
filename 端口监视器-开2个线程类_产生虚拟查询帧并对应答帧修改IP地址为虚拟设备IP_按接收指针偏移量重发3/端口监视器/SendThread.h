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
	// ADC�����ط�֡
	unsigned char m_ucADCRetransmission[128];
	// ��Ҫ�ط���ADC������Ϣ�ṹ
	typedef struct m_structADC
	{
		unsigned int	uiIPAim;				// Ŀ��IP��ַ
 		unsigned short	uiRetransmissionNum;	// ���յ����ط�����
		unsigned int	uiFrameCount;			// ����ת��ADC����֡����
	};
	// �����ط���ADC������
	CMap<unsigned int, unsigned int, m_structADC, m_structADC&> m_oADCLostMap;
	// ��Ҫ�ط���ADC������
	CMap<unsigned int, unsigned int, m_structADC, m_structADC&> m_oADCSendMap;
	// ����ADC�����ط�
	void OnADCDataRetransmission(unsigned int uiIPAim, unsigned short usDataPointNb);
	// ����ADC�����ط�֡
	void MakeADCDataRetransmissionFrame(unsigned int uiIPAim, unsigned short usDataPointNb);
	// �����е�ÿ���ṹ���֡������һ
	void OnListCountAdd(void);
	// ADC����֡����
	unsigned int m_uiADCFrameCount;
	// ����ADC�����ط�֡
	void SendADCDataRetransmissionFrame(void);
	// �����ط�֡����
	unsigned int m_uiSendADCRetransmissionFramNum;
};


