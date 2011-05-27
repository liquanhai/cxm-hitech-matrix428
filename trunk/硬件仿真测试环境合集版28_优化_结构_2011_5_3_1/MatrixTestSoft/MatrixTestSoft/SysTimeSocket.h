
#include "ADCSet.h"
#include "Parameter.h"
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
	// �ɼ�վ����ʱ�̲�ѯ֡
	byte m_cCollectSysTimeSendData[SndFrameSize];
public:
	// ԴIP��ַ
	CString m_csIPSource;
	// Ŀ��˿�
	unsigned int m_uiSendPort;
	// ADC������ָ��
	CADCSet* m_pADCSet;
	// ����ָ��
	CWnd* m_pwnd;
	// ����ʱ���ѯӦ�����
	unsigned int m_uiSysTimeCount;
protected:
	// ADC����TBʱ�̿�ʼ�ɼ�
	void OnADCStartSample(unsigned int uiIPAim, unsigned int tnow);
	// ��ֹ������ѭ���������޷���Ӧ��Ϣ
	void ProcessMessages(void);
public:
	// ���ɲɼ�վ����ʱ���ѯ֡
	void MakeCollectSysTimeFrameData(int* pSelectObject);
	// ���Ͳɼ�վ����ʱ���ѯ֡
	void SendCollectSysTimeFrameToSocket(void);
	// ������ʱ���ѯӦ��
	void OnProcSysTimeReturn(int iPos);
};


