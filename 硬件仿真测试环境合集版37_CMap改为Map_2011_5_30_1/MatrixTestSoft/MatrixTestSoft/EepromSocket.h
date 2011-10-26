#pragma once
#include "Parameter.h"
// CEepromSocket ����Ŀ��

class CEepromSocket : public CSocket
{
public:
	CEepromSocket();
	virtual ~CEepromSocket();
	virtual void OnReceive(int nErrorCode);
private:
	// �������֡������
	unsigned char m_ucRecBuf[RcvFrameSize];
public:
	// ��ȡEEPROM�Ľ������ݸ���
	unsigned int m_uiReadEepromNum;
	// ��ȡEEPROM�Ľ��ջ�����
	unsigned char m_ucReadEepromBuf[EEPROMCapacity];
private:
	// ����֡����
	void ProcFrameOne(void);
public:
	// ��Ҫ��ȡEEPROM�����ݸ���
	unsigned int m_uiNeedToReadNum;
	// һ֡���ݿɶ�ȡ��������
	unsigned int m_uiOneFrameReadMax;
	// ��ʼ��
	void OnInit(void);
};


