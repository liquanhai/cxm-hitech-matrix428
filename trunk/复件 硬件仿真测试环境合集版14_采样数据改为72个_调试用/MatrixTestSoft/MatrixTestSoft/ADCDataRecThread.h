#pragma once
#include <vector>
#include "OScopeCtrl.h"
#include "Parameter.h"
#include <afxmt.h>


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
	byte ADCData[256];
	// ѡ����������
	int* m_pSelectObject;
	// ѡ�������������������
	int* m_pSelectObjectNoise;
	// ͼ��ģ��ָ��
	COScopeCtrl* m_pOScopeCtrl;
	// �����ٽ�������
	CCriticalSection m_Sec;
	// ��¼ǰһ�����յ���ADC���ݵ�ָ��ƫ����                  
	unsigned short m_usDataPointPrevious[GraphViewNum];
	// ��¼ǰһ�ν��յ���ADC����֡�ı���ʱ��
	unsigned int m_uiFDUSystimePrevious[GraphViewNum];
	// ��¼Ӧ����ADC���ݰ�����
	unsigned int m_uiADCDataFrameCount[GraphViewNum];
	// ��¼ʵ�ʽ���ADC���ݰ�����
	unsigned int m_uiADCDataFrameRecCount[GraphViewNum];
	// �ж�ADC������ʼ��־λ�����ڶ���TB֮ǰ����Ч����
	BOOL m_bStartSample;
	// ADC�����ط�֡
	unsigned char m_ucADCRetransmission[128];
	// ԴIP��ַ
	CString m_csIPSource;
	// ���Ͷ˿�
	unsigned int m_uiSendPort;
	// ��Ҫ�ط���ADC������Ϣ�ṹ
	typedef struct m_structADC
	{
		unsigned int uiIPAim;			// �ط�֡IP��ַ
		unsigned short usDataPointNb;	// �ط�֡��ָ��ƫ����
		unsigned int uiDataCount;		// �ط�֡����Ӧ��֡λ�ã�������
		unsigned short uiRetransmissionNum;	// �ط�����
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
	// ��ADC�����ط����ȱ���������������
	vector <double> m_dSampleTemp[GraphViewNum];
	// ���Զ�֡���
	unsigned int m_uiTestADCLost;
	// ADC���ݱ�����ļ������ݻ�����
	vector <double> m_dADCSave[GraphViewNum];
	// �������ݵ��ļ��Ĵ洢·��
	CString m_csSaveFilePath;
	// ����ADC�����ļ�����
	unsigned int m_uiADCSaveFileNum;
	// �����ļ����ļ�ָ��
	FILE * m_pFileSave;
	// �ļ��򿪱�־λ
	BOOL m_bOpenADCSaveFile;
	// ѡ�е�������������
	char* m_cSelectObjectName[GraphViewNum];
	// �������ADC���ݸ���
	unsigned int m_uiADCDataToSaveNum;
	// ADC���ݱ����ļ��ߴ�
	unsigned int m_uiADCFileLength;
	// ADCͼ����ʾ�豸IP
	unsigned int m_uiADCGraphIP;
	// ADC���ݽ�����ʾ������
	double m_dADCDataShow[GraphViewNum];
	// ��¼������ʼʱ��ָ��ƫ����
	unsigned short m_usDataPointStart[GraphViewNum];
	// ��¼����ֹͣʱ��ָ��ƫ����
	unsigned short m_usDataPointStop[GraphViewNum];
	// ADC֡�����ļ����ļ�ָ��
	FILE* m_pFileDataPoint[GraphViewNum];
	// ADC���յ��������ط�֡�����
	unsigned int m_uiADCRetransmissionNb;

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
	unsigned int OnADCRetransimissionMinNb(void);
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
	// ��ADCָ֡��ƫ�����ļ�
	void OnOpenDataPointFile(unsigned int uiInstrumentNb);
	// �ر�ADCָ֡��ƫ�����ļ�
	void OnCloseDataPointFile(unsigned int uiInstrumentNb);
	// ��¼ADCָ֡��ƫ�������ļ�
	void OnSaveDataPointFile(unsigned int uiInstrumentNb, CString strOutput);
	// ������֡�Ƿ�Ϊ�ط�֡
	BOOL OnCheckFrameIsRetransmission(unsigned int uiInstrumentNb, unsigned int uiIPAim, unsigned short usDataPointNow, unsigned int uiFDUSystimeNow);
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


