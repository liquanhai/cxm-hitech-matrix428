// HeartBeatSocket.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MatrixTestSoft.h"
#include "HeartBeatSocket.h"
#include "Parameter.h"

// CHeartBeatSocket

CHeartBeatSocket::CHeartBeatSocket()
: m_uiSendPort(0)
{
}

CHeartBeatSocket::~CHeartBeatSocket()
{
}


// CHeartBeatSocket ��Ա����
// ��������֡
void CHeartBeatSocket::MakeHeartBeatFrame(void)
{
	unsigned int uiIPSource = 0;
	unsigned int uiIPAim = 0;
	unsigned short usPortAim = 0;
	unsigned short usCommand = 0;
	m_pFrameData[0] = 0x11;
	m_pFrameData[1] = 0x22;
	m_pFrameData[2] = 0x33;
	m_pFrameData[3] = 0x44;
	m_pFrameData[4] = 0x00;
	m_pFrameData[5] = 0x00;
	m_pFrameData[6] = 0x00;
	m_pFrameData[7] = 0x00;
	m_pFrameData[8] = 0x00;
	m_pFrameData[9] = 0x00;
	m_pFrameData[10] = 0x00;
	m_pFrameData[11] = 0x00;
	m_pFrameData[12] = 0x00;
	m_pFrameData[13] = 0x00;
	m_pFrameData[14] = 0x00;
	m_pFrameData[15] = 0x00;
	// ԴIP��ַ
	uiIPSource = 0x00000000;
	// Ŀ��IP��ַ
	uiIPAim = 0x00000000;
	// Ŀ��˿ں�
	usPortAim = HeartBeatRec;
	// ����� 1-��������Ӧ��2-��ѯ����Ӧ��3-AD���������ط�
	usCommand = 1;
	// ԴIP��ַ
	memcpy(&m_pFrameData[16], &uiIPSource, 4);
	// Ŀ��IP��ַ
	memcpy(&m_pFrameData[20], &uiIPAim, 4);
	// Ŀ��˿ں�
	memcpy(&m_pFrameData[24], &usPortAim, 2);
	// ����� 1-��������Ӧ��2-��ѯ����Ӧ��3-AD���������ط�
	memcpy(&m_pFrameData[26], &usCommand, 2);

	int iPos = 32;
	// ����������
	m_pFrameData[iPos] = 0x00;
}

// ��������֡
void CHeartBeatSocket::SendHeartBeatFrame(void)
{
	// ���͹㲥����֡
	int iCount = SendTo(m_pFrameData, 128, m_uiSendPort, IPBroadcastAddr);
}