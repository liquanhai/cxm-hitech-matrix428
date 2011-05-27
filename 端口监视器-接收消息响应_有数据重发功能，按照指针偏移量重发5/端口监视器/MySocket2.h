#pragma once

// CMySocket2 ����Ŀ��
class CPortMonitoringDlg;
#define InstrumentForTest	75	// ��������������
#define ClearListFrameCount	10	// �ﵽָ��֡�������б��й����ط�֡
#define ADCRetransmissionCmd	0x0003	// ADC�����ط�����
#define SendADCFrameCountMax		75	// ���һ�η���ADC���ݲ�ѯ֡��
#define ADRecPort				0x8300	// AD���ݲɼ����ն˿�
class CMySocket2 : public CSocket
{
public:
	CMySocket2(CPortMonitoringDlg* pTDoc);
	virtual ~CMySocket2();
public:
	virtual void OnReceive(int nErrorCode);

protected:
	unsigned char udp_buf[8][256];
	unsigned char udp_count;
	CPortMonitoringDlg* m_pTDoc;
	// UDP���ջ�����
	unsigned char m_ucUdpBuf[16384];
	// ADC�����ط�֡
	unsigned char m_ucADCRetransmission[128];
public:
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
	// UDP����ָ֡��ƫ����
	unsigned int m_uiUdpCount;
	// Ŀ��2���͵Ķ˿�
	unsigned short m_uiPortNb[18];
};


