#pragma once

// CHeartBeatSocket ����Ŀ��

class CHeartBeatSocket : public CSocket
{
public:
	CHeartBeatSocket();
	virtual ~CHeartBeatSocket();
protected:
	// ֡����
	byte m_pFrameData[128];
public:
	// ��������֡
	void MakeHeartBeatFrame(void);
	// ��������֡
	void SendHeartBeatFrame(void);
	// ���Ͷ˿�
	unsigned int m_uiSendPort;
};


