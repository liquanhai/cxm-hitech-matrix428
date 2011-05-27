
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
	unsigned char udp_buf[1024];
	unsigned char ADCSampleCmd[128];
public:
	// �ɼ�վ����ʱ��
	unsigned int m_uiSysTime;
	// Ŀ��IP��ַ
	unsigned int m_uiIPAim;
	// �������ݲ�������֡
	void MakeFrameData(unsigned int uiIPAim, unsigned int tnow);
	// �������ݲ�������֡
	void SendFrameData(void);
	// ԴIP��ַ
	CString m_csIPSource;
	// Ŀ��˿�
	unsigned int m_uiSendPort;
	// ADC����TBʱ�̿�ʼ�ɼ�
	void OnADCStartSample(unsigned int uiIPAim, unsigned int tnow);
	// ADC������ָ��
	CADCSet* m_pADCSet;
	// ��Ưƫ����
	unsigned char m_ucZeroDrift[GraphViewNum][6];
	// �豸��ָ��
	CInstrumentList* m_pInstrumentList;
	// �豸ѡ��ָ��
	int* m_pSelectObject;
	// ����ָ��
	CWnd* m_pwnd;
};


