#pragma once
#include "Parameter.h"
#include <afxmt.h>
#include "ADCDataProcessThread.h"

// CADCRecSocket ����Ŀ��

class CADCRecSocket : public CSocket
{
public:
	CADCRecSocket();
	virtual ~CADCRecSocket();
	virtual void OnReceive(int nErrorCode);
public:
	// ����֡���ջ���
	unsigned char udp_buf[ADCRecBufNum][RcvFrameSize];
	// ���������
	unsigned int udp_count;
	// UDP����ָ֡��ƫ����
	unsigned int m_uiUdpCount;
	// UDP���ջ�����
	unsigned char m_ucUdpBuf[ADCDataBufSize];
	// �ж�ADC������ʼ��־λ�����ڶ���TB֮ǰ����Ч����
	BOOL m_bStartSample;
	// ADC���ݽ�����ʾ������
	double m_dADCDataShow[GraphViewNum];
	// ѡ����������
	int* m_pSelectObject;
	// �����ٽ�������
	CCriticalSection m_Sec;
	// ADC���ݴ����߳�ָ��
	CADCDataProcessThread* m_pADCDataProcessThread;

public:
	// ��ֹ������ѭ���������޷���Ӧ��Ϣ
	void ProcessMessages(void);
	// ��ADC���ݽ������ݴ���
	void OnProcess(unsigned char* ucUdpBuf);
	// �����ݽ���ADC���ݴ����߳�
	void OnProcessADCData(unsigned int uiInstrumentNb, unsigned short usDataPoint, double* pReceiveData);
	// ADC���ݴ����������
	unsigned int m_uiADCProcCountForTest;
};


