#pragma once
#include "OScopeCtrl.h"
#include "Parameter.h"
#include "ADCDataSaveToFile.h"
#include <afxmt.h>
using namespace std;

// CADCDataRecThread

class CADCDataRecThread : public CWinThread
{
	DECLARE_DYNCREATE(CADCDataRecThread)

public:
	CADCDataRecThread();           // ��̬������ʹ�õ��ܱ����Ĺ��캯��
	virtual ~CADCDataRecThread();

public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

protected:
	DECLARE_MESSAGE_MAP()
public:
	virtual int Run();
public:
	// �߳̽����¼�
	HANDLE m_hADCDataThreadClose;
	// ADC���ݽ���Socket
	CSocket* m_pADCDataSocket;
	// �̹߳رձ�־
	bool m_bclose;
	// ѡ����������
	int m_iSelectObject[InstrumentNum];
	// ѡ�������������������
	int m_iSelectObjectNoise[InstrumentNum];
	// ͼ��ģ��ָ��
	COScopeCtrl* m_pOScopeCtrl[InstrumentNum];
	// �����ٽ�������
	CCriticalSection m_Sec;
	// ��¼ǰһ�����յ���ADC���ݵ�ָ��ƫ����                  
	unsigned short m_usDataPointPrevious[InstrumentNum];
	// ��¼Ӧ����ADC���ݰ�����
	unsigned int m_uiADCDataFrameCount[InstrumentNum];
	// ��¼ʵ�ʽ���ADC���ݰ�����
	unsigned int m_uiADCDataFrameRecCount[InstrumentNum];
	// �ж�ADC������ʼ��־λ�����ڶ���TB֮ǰ����Ч����
	BOOL m_bStartSample;
	// ADC�����ط�֡
	unsigned char m_ucADCRetransmission[SndFrameSize];
	// ԴIP��ַ
	CString m_csIPSource;
	// ���Ͷ˿�
	unsigned int m_uiSendPort;
	// ��Ҫ�ط���ADC������Ϣ�ṹ
	typedef struct m_structADC
	{
		unsigned int uiDataCount;		// �ط�֡����Ӧ��֡λ�ã�������
		unsigned short uiRetransmissionNum;	// �ط�����
	};
	// ��Ҫ�ط���ADC������
	CMap<unsigned int, unsigned int, m_structADC, m_structADC&> m_oADCLostMap[InstrumentNum];
	// ��ADC�����ط����ȱ���������������
	double m_dSampleTemp[InstrumentNum][ADCDataTempDataSize];
	// ��ADC�����ط����ȱ��������������ݸ���
	unsigned int m_uiSampleTempNum[InstrumentNum];
	// ADC���ݱ�����ļ������ݻ�����
	double m_dADCSave[InstrumentNum][ADCDataTempDataSize];
	// ADC���ݱ�����ļ������ݻ����������ݸ���
	unsigned int m_uiADCSaveNum[InstrumentNum];
	// ADC���ݴ�����̻�����
	double m_dTemp[ADCDataTempDataSize];
	// ADC���ݴ�����̻����������ݸ���
	unsigned int m_uiTempNum;
	// ���Զ�֡���
	unsigned int m_uiTestADCLost;
	// ADCͼ����ʾ�豸IP
	unsigned int m_uiADCGraphIP[InstrumentNum];
	// ADC���ݽ�����ʾ������
	double m_dADCDataShow[InstrumentNum];
	// ADC���յ��������ط�֡�����
	unsigned int m_uiADCRetransmissionNb;
	// ����֡���ջ���
	unsigned char m_ucudp_buf[RcvBufNum][RcvFrameSize];
	// ���������
	unsigned short m_usudp_count;
	// UDP����ָ֡��ƫ����
	unsigned int m_uiUdpCount;
	// UDP���ջ�����
	unsigned char m_ucUdpBuf[ADCDataBufSize];
	// ��CADCDataSaveToFile��Ա����ָ��
	CADCDataSaveToFile* m_pADCDataSaveToFile;
protected:
	// ��ѡ��������ADC���ݸ�������Сֵ
	unsigned int OnADCRecDataMinNum(void);
	// ��ѡ��������ADC���ݸ��������ֵ
	unsigned int OnADCRecDataMaxNum(void);
public:
	// ��ʼ��
	void OnInit(void);
	// �رղ������߳�
	void OnClose(void);
	// ���ղ�������
	void ReceiveSampleData(byte* pSampleData);
	// ����ADC�����ط�֡
	void MakeADCDataRetransmissionFrame(unsigned short usDataPointNb, unsigned int uiIPAim);
	// ADC������Ҫ���·���֡��Ӧ����С����
	unsigned int OnADCRetransimissionMinNb(unsigned int uiInstrumentNb);
	// ��ADC���ݱ��浽�ļ���
	void OnSaveADCToFile(bool bfinish);
	// ADC�����ط�
	void OnADCDataRetransmission(void);
	// ��ֹ������ѭ���������޷���Ӧ��Ϣ
	void ProcessMessages(void);
	// ������֡�Ƿ�Ϊ�ط�֡
	BOOL OnCheckFrameIsRetransmission(unsigned int uiInstrumentNb, unsigned int uiIPAim, unsigned short usDataPointNow);
	// ��֡Ϊ���һ�������ط�֡
	void OnRecOkIsRetransimissionFrame(unsigned int uiInstrumentNb, unsigned int uiIPAim, double* pReceiveData);
	// ��֡Ϊ��ͨ֡��֮ǰû���ط�֡
	void OnRecOkIsNormalFrame(unsigned int uiInstrumentNb, unsigned int uiIPAim, double* pReceiveData);
	// ��֡Ϊ�ط�֡���������һ���ط�֡
	void OnRecNotOkIsRetransimissionFrame(unsigned int uiInstrumentNb, unsigned int uiIPAim, double* pReceiveData);
	// ��֡Ϊ��ͨ֡��֮ǰ���ط�֡
	void OnRecNotOkIsNormalFrame(unsigned int uiInstrumentNb, double* pReceiveData);
	// ���ñ�����ֵ
	void OnReset(void);
	// ���ݴ���
	void OnProcess(int iCount);
};


