#pragma once
#include <vector>
#include "OScopeCtrl.h"
#include "Parameter.h"
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
	// AD���ݽ���Socket
	CSocket m_ADCDataSocket;
	// �̹߳رձ�־
	bool m_bclose;
	// ADC�������ݻ�����
	byte ADCData[RcvFrameSize];
	// ѡ����������
	int* m_pSelectObject;
	// ѡ�������������������
	int* m_pSelectObjectNoise;
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
	vector <double> m_dSampleTemp[InstrumentNum];
	// ���Զ�֡���
	unsigned int m_uiTestADCLost;
	// ADC���ݱ�����ļ������ݻ�����
	vector <double> m_dADCSave[InstrumentNum];
	// �������ݵ��ļ��Ĵ洢·��
	CString m_csSaveFilePath;
	// ����ADC�����ļ�����
	unsigned int m_uiADCSaveFileNum;
	// �����ļ����ļ�ָ��
	FILE * m_pFileSave;
	// �ļ��򿪱�־λ
	BOOL m_bOpenADCSaveFile;
	// ѡ�е�������������
	char* m_cSelectObjectName[InstrumentNum];
	// �������ADC���ݸ���
	unsigned int m_uiADCDataToSaveNum;
	// ADC���ݱ����ļ��ߴ�
	unsigned int m_uiADCFileLength;
	// ADCͼ����ʾ�豸IP
	unsigned int m_uiADCGraphIP[InstrumentNum];
	// ADC���ݽ�����ʾ������
	double m_dADCDataShow[InstrumentNum];
	// ADC���յ��������ط�֡�����
	unsigned int m_uiADCRetransmissionNb;
	// ����֡���ջ���
	unsigned char udp_buf[8][RcvFrameSize];
	// ���������
	unsigned char udp_count;
	// UDP����ָ֡��ƫ����
	unsigned int m_uiUdpCount;
	// UDP���ջ�����
	unsigned char m_ucUdpBuf[ADCDataBufSize];


public:
	// ��ʼ��
	void OnInit(void);
	// �رղ������߳�
	void OnClose(void);
	// ��
	void OnOpen(void);
	// ֹͣ
	void OnStop(void);
	// ���ղ�������
	void ReceiveSampleData(byte* pSampleData);
	// ����ADC�����ط�֡
	void MakeADCDataRetransmissionFrame(unsigned short usDataPointNb, unsigned int uiIPAim);
	// ADC������Ҫ���·���֡��Ӧ����С����
	unsigned int OnADCRetransimissionMinNb(unsigned int uiInstrumentNb);
	// ��������ADC���������ļ�
	void OnOpenADCSaveFile(void);
	// �ر�ADC���������ļ�
	void OnCloseADCSaveFile(void);
	// ��ADC���ݱ��浽�ļ���
	void OnSaveADCToFile(void);
	// ��ѡ��������ADC���ݸ�������Сֵ
	unsigned int OnADCRecDataMinNum(void);
	// �رղ����󱣴�ʣ������
	void OnSaveRemainADCData(unsigned int uiADCDataNeedToSave);
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
	// ���û������ߴ�
	BOOL OnSetBufferSize(int iBufferSize);
};


