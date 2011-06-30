
#include "ADCSet.h"
#include "Parameter.h"
#include "ADCFrameInfo.h"
#include "LogFile.h"
#pragma once
// CSysTimeSocket ����Ŀ��

class CSysTime
{
public:
	CSysTime();
	virtual ~CSysTime();
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
	// ��CADCFrameInfo��Ա����ָ��
	CADCFrameInfo* m_pADCFrameInfo;
	// ��־��ָ��
	CLogFile* m_pLogFile;
	// Socket�׽���
	sockaddr_in addr, addr2;
	SOCKET m_SysTimeSocket;
protected:
	// ADC����TBʱ�̿�ʼ�ɼ�
	void OnADCStartSample(unsigned int tnow);
	// ��ֹ������ѭ���������޷���Ӧ��Ϣ
	void ProcessMessages(void);
public:
	// ���ɲɼ�վ����ʱ���ѯ֡
	void MakeCollectSysTimeFrameData(int* pSelectObject);
	// ���Ͳɼ�վ����ʱ���ѯ֡
	void SendCollectSysTimeFrameToSocket(void);
	// ������ʱ���ѯӦ��
	void OnProcSysTimeReturn(int iPos);
	// ��Ϣ������
	void OnReceive(void);
};


