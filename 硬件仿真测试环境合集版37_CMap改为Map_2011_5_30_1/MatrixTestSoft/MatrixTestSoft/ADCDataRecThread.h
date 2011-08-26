#pragma once
#include "OScopeCtrl.h"
#include "Parameter.h"
#include "ADCDataSaveToFile.h"
#include "ADCFrameInfo.h"
#include "LogFile.h"
#include "InstrumentList.h"
#include <hash_map>

using namespace stdext;
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
	// ADC���ݽ��պ��ط�Socket�׽���
	sockaddr_in m_RecvAddr, m_SendToAddr;
	// ADC����ͼ�λ���ʾ�����׽���
	sockaddr_in m_SendADCGraphToAddr;
	SOCKET m_ADCDataSocket;
	// �̹߳رձ�־
	bool m_bclose;
	// ͼ��ģ��ָ��
	COScopeCtrl* m_pOScopeCtrl[InstrumentNum];
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
	unsigned int m_uiIPSource;
	// ��Ҫ�ط���ADC������Ϣ�ṹ
	typedef struct m_structADC
	{
		unsigned int uiDataCount;		// �ط�֡����Ӧ��֡λ�ã�������
		unsigned short uiRetransmissionNum;	// �ط�����
	};
	// ��Ҫ�ط���ADC������
	hash_map<unsigned int, m_structADC> m_oADCLostMap[InstrumentNum];
	// ��ADC�����ط����ȱ���������������
	int m_iSampleTemp[InstrumentNum][ADCDataTempDataSize];
	// ��ADC�����ط����ȱ��������������ݸ���
	unsigned int m_uiSampleTempNum[InstrumentNum];
	// ADC���ݱ�����ļ������ݻ�����
	int m_iADCSave[InstrumentNum][ADCDataTempDataSize];
	// ADC���ݱ�����ļ������ݻ����������ݸ���
	unsigned int m_uiADCSaveNum[InstrumentNum];
	// ADC���ݴ�����̻�����
	int m_iTemp[ADCDataTempDataSize];
	// ���Զ�֡���
	unsigned int m_uiTestADCLost;
	// ADCͼ����ʾ�豸IP
	unsigned int m_uiADCGraphIP[InstrumentNum];
	// ADC���ݽ�����ʾ������
	unsigned int m_uiADCDataShow[InstrumentNum];
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
	// ��CADCFrameInfo��Ա����ָ��
	CADCFrameInfo* m_pADCFrameInfo;
	// ��־��ָ��
	CLogFile* m_pLogFile;
	// ADC���ݲ�������������
	unsigned int m_uispsSelect;
	// �豸��ָ��
	CInstrumentList* m_pInstrumentList;
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
	// ADC�����ط�
	void OnADCDataRetransmission(unsigned int uiInstrumentNb);
	// ��ֹ������ѭ���������޷���Ӧ��Ϣ
	void ProcessMessages(void);
	// ������֡�Ƿ�Ϊ�ط�֡
	DWORD OnCheckFrameIsRetransmission(unsigned int uiInstrumentNb, unsigned int uiIPAim, unsigned short usDataPointNow);
	// ��֡Ϊ���һ�������ط�֡
	void OnRecOkIsRetransimissionFrame(unsigned int uiInstrumentNb, unsigned int uiIPAim, int* piReceiveData);
	// ��֡Ϊ��ͨ֡��֮ǰû���ط�֡
	void OnRecOkIsNormalFrame(unsigned int uiInstrumentNb, unsigned int uiIPAim, int* piReceiveData);
	// ��֡Ϊ�ط�֡���������һ���ط�֡
	void OnRecNotOkIsRetransimissionFrame(unsigned int uiInstrumentNb, unsigned int uiIPAim, int* piReceiveData);
	// ��֡Ϊ��ͨ֡��֮ǰ���ط�֡
	void OnRecNotOkIsNormalFrame(unsigned int uiInstrumentNb, int* piReceiveData);
	// ���ñ�����ֵ
	void OnReset(void);
	// ���ݴ���
	void OnProcess(int iCount);
	// �ر�UDP�׽���
	void OnCloseUDP(void);
	// ����ADC����ͼ�λ���ʾ֡
	void OnMakeADCGraphShowFrame(unsigned short usCommand);
	// ����ADC����ͼ�λ���ʾ֡
	void OnSendADCGraphShowFrame(void);
};


