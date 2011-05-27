
#include "ADCSet.h"
#include "Parameter.h"
#include "InstrumentList.h"
#pragma once
// CSysTimeSocket ����Ŀ��

class CSysTimeSocket : public CSocket
{
public:
	CSysTimeSocket();
	virtual ~CSysTimeSocket();
public:
	virtual void OnReceive(int nErrorCode);
protected:
	unsigned char udp_buf[RcvFrameSize];
	unsigned char ADCSampleCmd[SndFrameSize];
	// �ɼ�վ����ʱ��
	unsigned int m_uiSysTime;
	// Ŀ��IP��ַ
	unsigned int m_uiIPAim;
	// ��Ưƫ����
	unsigned char m_ucZeroDrift[InstrumentNum][ADCZeroDriftWritebytesNum];
public:
	// ԴIP��ַ
	CString m_csIPSource;
	// Ŀ��˿�
	unsigned int m_uiSendPort;
	// ADC������ָ��
	CADCSet* m_pADCSet;
	// �豸��ָ��
	CInstrumentList* m_pInstrumentList;
	// �豸ѡ��ָ��
	int* m_pSelectObject;
	// ����ָ��
	CWnd* m_pwnd;
	// ����ʱ���ѯӦ�����
	unsigned int m_uiSysTimeCount;
protected:
	// ADC����TBʱ�̿�ʼ�ɼ�
	void OnADCStartSample(unsigned int uiIPAim, unsigned int tnow);
	// 	// �������ݲ�������֡
	// 	void MakeFrameData(unsigned int uiIPAim, unsigned int tnow);
	// 	// �������ݲ�������֡
	// 	void SendFrameData(void);
	// ��ֹ������ѭ���������޷���Ӧ��Ϣ
	void ProcessMessages(void);
};


