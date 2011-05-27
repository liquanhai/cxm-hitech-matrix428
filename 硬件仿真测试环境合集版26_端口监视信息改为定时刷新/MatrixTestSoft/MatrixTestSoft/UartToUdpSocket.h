#pragma once
#include "mscomm1.h"
#include "Parameter.h"
// CUartToUdpSocket ����Ŀ��

class CUartToUdpSocket : public CSocket
{
public:
	CUartToUdpSocket();
	virtual ~CUartToUdpSocket();
	virtual void OnReceive(int nErrorCode);
protected:
	// UDP���ջ���������
	unsigned char m_ucUdpBuf[RcvBufNum][UartToUdpRcvSize];
	unsigned short m_usUdpBufCount;
	// �Ӵ��ڷ�������
	void OnSendFromSerialPort(unsigned char* TXDATA, unsigned int uiCount);
public:
	// ����ͨѶ�ؼ��Ŀ��Ʊ���
	CMscomm1* m_pctrlMSComm1;
};


