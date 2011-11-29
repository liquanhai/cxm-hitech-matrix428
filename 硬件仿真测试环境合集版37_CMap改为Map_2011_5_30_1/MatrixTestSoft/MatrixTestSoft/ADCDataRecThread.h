#pragma once
#include "OScopeCtrl.h"
#include "Parameter.h"
#include "ADCDataSaveToFile.h"
#include "ADCFrameInfo.h"
#include "LogFile.h"
#include "InstrumentList.h"
#include <hash_map>

using stdext::hash_map;
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
	// ADC���ݽ���sockaddr_in
	sockaddr_in m_RecvAddr;
	// ADC�����ط�sockaddr_in
	sockaddr_in m_SendToAddr;
	// ADC����ͼ�λ���ʾ����sockaddr_in
	sockaddr_in m_SendADCGraphToAddr;
	// ADC���ݽ��պͷ���Socket�׽���
	SOCKET m_ADCDataSocket;
	// ADC����ͼ�λ���ʾSocket�׽���
	SOCKET m_ADCGraphShowSocket;
	// ͼ��ģ��ָ��
	COScopeCtrl* m_pOScopeCtrl[InstrumentMaxCount];
	// ��¼Ӧ����ADC���ݰ�����
	unsigned int m_uiADCDataFrameCount[InstrumentMaxCount];
	// �ж�ADC������ʼ��־λ�����ڶ���TB֮ǰ����Ч����
	BOOL m_bStartSample;
	// ԴIP��ַ
	unsigned int m_uiIPSource;
	// ADCͼ����ʾ�豸IP
	unsigned int m_uiADCGraphIP[InstrumentMaxCount];
	// ADC���ݽ�����ʾ������
	unsigned int m_uiADCDataShow[InstrumentMaxCount];
	// ��CADCDataSaveToFile��Ա����ָ��
	CADCDataSaveToFile* m_pADCDataSaveToFile;
	// ��CADCFrameInfo��Ա����ָ��
	CADCFrameInfo* m_pADCFrameInfo;
	// ��־��ָ��
	CLogFile* m_pLogFile;
	// ADC���ݲ�������������
	unsigned int m_uispsSelect;
	// �豸��ָ��
	CInstrumentList* m_pInstrumentList;

private:
	// �̹߳رձ�־
	bool m_bclose;
	// ��¼ǰһ�����յ���ADC���ݵ�ָ��ƫ����                  
	unsigned short m_usDataPointPrevious[InstrumentMaxCount];
	// ��¼ʵ�ʽ���ADC���ݰ�����
	unsigned int m_uiADCDataFrameRecCount[InstrumentMaxCount];
	// ADC�����ط�֡
	unsigned char m_ucADCRetransmission[SndFrameSize];
	// ��Ҫ�ط���ADC������Ϣ�ṹ
	typedef struct m_structADC
	{
		unsigned int uiDataCount;		// �ط�֡����Ӧ��֡λ�ã�������
		unsigned short uiRetransmissionNum;	// �ط�����
	};
	// ��Ҫ�ط���ADC������
	hash_map<unsigned int, m_structADC> m_oADCLostMap[InstrumentMaxCount];
	// ��ADC�����ط����ȱ���������������
	int m_iSampleTemp[InstrumentMaxCount][ADCDataTempDataSize];
	// ��ADC�����ط����ȱ��������������ݸ���
	unsigned int m_uiSampleTempNum[InstrumentMaxCount];
	// ADC���ݱ�����ļ������ݻ�����
	int m_iADCSave[InstrumentMaxCount][ADCDataTempDataSize];
	// ADC���ݱ�����ļ������ݻ����������ݸ���
	unsigned int m_uiADCSaveNum[InstrumentMaxCount];
	// ADC���ݴ�����̻�����
	int m_iTemp[ADCDataTempDataSize];
	// ���Զ�֡���
	unsigned int m_uiTestADCLost;
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
	// ADC����ͼ�λ���ʾ���ý��ջ�����
	byte m_pADCGraphSetFrameData[RcvFrameSize];
	// ADC����ͼ�λ���ʾ������
	unsigned int m_uiSamplingRate;
	// ��ʼADC����ͼ�λ���ʾ��־λ
	BOOL m_bStartGraphShow;
	// ������������豸Ӧ��ADC���ݰ������Ƿ�һ��
	BOOL m_bCheckADCDataFrameCountEqule;
	// ADC����ͼ�λ���ʾ���û�����
	unsigned char m_ucADCGraphShowSetFrame[RcvFrameSize];
	// ADC����ͼ�λ���ʾ���ݻ�����
	unsigned char m_ucADCGraphShowDataFrame[InstrumentMaxCount][RcvFrameSize];
	// ADC����ͼ�λ���ʾ��������
	unsigned int m_uiADCGraphShowSamplingNum[InstrumentMaxCount];
	// ADC����ͼ�λ���ʾ����Դָ������
	unsigned int m_uiADCGraphShowSourcePoint[InstrumentMaxCount];
private:
	// ���ղ�������
	void ReceiveSampleData(byte* pSampleData);
	// ��ѡ����������ֵ�Ƚ�
	int OnADCRecDataCheckOpt(unsigned short usOperation, unsigned int* pData);
	// ����ADC�����ط�֡
	void MakeADCDataRetransmissionFrame(unsigned short usDataPointNb, unsigned int uiIPAim);
	// ADC������Ҫ���·���֡��Ӧ����С����
	unsigned int OnADCRetransimissionMinNb(unsigned int uiInstrumentNb);
	// ADC�����ط�
	void OnADCDataRetransmission(void);
	// ADC�����ط�
	void OnADCDataRetransmission(unsigned int uiInstrumentNb);
	// ��ֹ������ѭ���������޷���Ӧ��Ϣ
	void ProcessMessages(void);
	// ������֡�Ƿ�Ϊ�ط�֡
	DWORD OnCheckFrameIsRetransmission(unsigned int uiInstrumentNb, unsigned int uiIP, unsigned short usDataPointNow);
	// ��֡Ϊ���һ�������ط�֡
	void OnRecOkIsRetransimissionFrame(unsigned int uiInstrumentNb, int* piReceiveData);
	// ��֡Ϊ��ͨ֡��֮ǰû���ط�֡
	void OnRecOkIsNormalFrame(unsigned int uiInstrumentNb, int* piReceiveData);
	// ��֡Ϊ�ط�֡���������һ���ط�֡
	void OnRecNotOkIsRetransimissionFrame(unsigned int uiInstrumentNb, int* piReceiveData);
	// ��֡Ϊ��ͨ֡��֮ǰ���ط�֡
	void OnRecNotOkIsNormalFrame(unsigned int uiInstrumentNb, int* piReceiveData);
	// ���ݴ���
	void OnProcess(int iCount);
	// ����ADC����ͼ�λ���ʾ֡
	void OnMakeADCGraphShowFrame(unsigned short usCommand);
	// ADCͼ�λ���ʾ����֡������
	void ProcADCGraphSetFrame(void);
public:
	// ��ʼ��
	void OnInit(void);
	// �رղ������߳�
	void OnClose(void);
	// ���ñ�����ֵ
	void OnReset(void);
	// �ر�UDP�׽���
	void OnCloseUDP(void);
	// ADC����ͼ�λ���ʾ���ý��պ���
	void OnReceive(void);
	// ��ADC���ݱ��浽�ļ���
	void OnSaveADCToFile(bool bfinish);
};


