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
		unsigned int	uiIPAim;				// �ط�֡IP��ַ
		unsigned short	usDataPointNb;			// �ط�֡��ָ��ƫ����
 		unsigned short	uiRetransmissionNum;	// ���յ����ط�����
		unsigned int	uiFrameCount;			// ����ת��ADC����֡����
		BOOL operator == (const m_structADC&   tdl)const
		{ 

			if(uiIPAim != tdl.uiIPAim) 
				return   FALSE; 
			if(usDataPointNb != tdl.usDataPointNb) 
				return   FALSE; 
			return   TRUE; 
		} 
	};
	// ��Ҫ�ط���ADC��������
	CList <m_structADC, m_structADC&> m_listADC;
	// ����ADC�����ط�
	void OnADCDataRetransmission(unsigned int uiIPAim, unsigned short usDataPointNb, unsigned short usPort);
	// ����ADC�����ط�֡
	void MakeADCDataRetransmissionFrame(unsigned int uiIPAim, unsigned short usDataPointNb, unsigned short usPort);
	// �ﵽָ������֡��������ڵ��ط�֡
	unsigned int m_uiFrameTimeCount;
	// �����е�ÿ���ṹ���֡������һ
	void OnListCountAdd(void);
	// �׸�ָ��ƫ����
	unsigned short m_usDataPointPrevious;
	// ADC����֡����
	unsigned int m_uiADCFrameCount;
};


