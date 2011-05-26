#pragma once

// CUartToUdpSocket ����Ŀ��

class CUartToUdpSocket : public CSocket
{
public:
	CUartToUdpSocket();
	virtual ~CUartToUdpSocket();
	virtual void OnReceive(int nErrorCode);
protected:
	// UDP���ջ���������
	unsigned char m_ucUdpBuf[8][1024];
	unsigned short m_usUdpBufCount;
	// �Ӵ��ڷ�������
	void OnSendFromSerialPort(unsigned char* TXDATA, unsigned int uiCount);
};


