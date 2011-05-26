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
};


