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
	void MakeFrameData(unsigned int uiIPAim);
	// �������ݲ�������֡
	void SendFrameData(void);
	// ADC��ʼ��
	void OnADCInit(unsigned int uiTestNb);
	// ADC��Ư����
	void OnADCOffset(unsigned int uiTestNb);
	// ADC�����̽���
	void OnADCFullScale(unsigned int uiTestNb);
	// ��ʼADC���ݲɼ�
	void OnADCStart(unsigned int uiTestNb);
	// ֹͣADC���ݲɼ�
	void OnADCStop(unsigned int uiTestNb);
	// ���ɰ�ͷ
	void MakeHeadFrame(unsigned int uiIPAim, unsigned short usCommand);
	// ����ADC����֡
	void MakeADCSetFrame(unsigned char* buf, int iBufLength);
};


