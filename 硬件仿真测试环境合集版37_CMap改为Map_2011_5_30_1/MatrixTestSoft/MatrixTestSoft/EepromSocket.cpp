// EepromSocket.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MatrixTestSoft.h"
#include "EepromSocket.h"


// CEepromSocket

CEepromSocket::CEepromSocket()
: m_uiNeedToReadNum(0)
, m_uiOneFrameReadMax(0)
, m_uiReadEepromNum(0)
{
}

CEepromSocket::~CEepromSocket()
{
}


// CEepromSocket ��Ա����

void CEepromSocket::OnReceive(int nErrorCode)
{
	// TODO: �ڴ����ר�ô����/����û���
	int ret=0;
	unsigned short uiPort = 0;
	ret = Receive(m_ucRecBuf, RcvFrameSize);
	if(ret == RcvFrameSize) 
	{
		// ����֡����
		ProcFrameOne();
	}
	CSocket::OnReceive(nErrorCode);
}
// ����֡����
void CEepromSocket::ProcFrameOne(void)
{
	unsigned short usCommand = 0;
	unsigned char ucCommand = 0;
	unsigned int uiInstrumentIP = 0;
	unsigned int uiMaxNum = 0;
	unsigned int ui18Count = 0;
	int iPos = FrameHeadSize;
	// [16]��[19]ΪԴ��ַ
	memcpy(&uiInstrumentIP, &m_ucRecBuf[iPos], FramePacketSize4B);
	iPos += FramePacketSize4B;
	iPos += FramePacketSize4B;
	iPos += FramePacketSize2B;
	// ��m_oADCRecFrameBuf[26]��m_oADCRecFrameBuf[27]Ϊ������
	memcpy(&usCommand, &m_ucRecBuf[iPos], FramePacketSize2B);
	iPos += FramePacketSize2B;
	if (usCommand == SendQueryCmd)
	{
		iPos += FrameCmdSize1B;
		iPos += FramePacketSize4B;
		if (m_uiNeedToReadNum < m_uiReadEepromNum + m_uiOneFrameReadMax)
		{
			uiMaxNum = m_uiNeedToReadNum - m_uiReadEepromNum;
		} 
		else
		{
			uiMaxNum = m_uiOneFrameReadMax;
		}
		do 
		{
			memcpy(&ucCommand, &m_ucRecBuf[iPos], FrameCmdSize1B);
			iPos += FrameCmdSize1B;
			if (ucCommand == CmdADCSet)
			{
				if (uiMaxNum <= (ui18Count + FramePacketSize4B))
				{
					memcpy(&m_ucReadEepromBuf[m_uiReadEepromNum], &m_ucRecBuf[iPos], uiMaxNum - ui18Count);
					iPos += uiMaxNum - ui18Count;
					m_uiReadEepromNum += uiMaxNum - ui18Count;
					break;
				}
				memcpy(&m_ucReadEepromBuf[m_uiReadEepromNum], &m_ucRecBuf[iPos], FramePacketSize4B);
				iPos += FramePacketSize4B;
				m_uiReadEepromNum += FramePacketSize4B;
				ui18Count += FramePacketSize4B;
			}
		} while (ucCommand != SndFrameBufInit);
	}
}
// ��ʼ��
void CEepromSocket::OnInit(void)
{
	m_uiNeedToReadNum = 0;
	m_uiOneFrameReadMax = 0;
	m_uiReadEepromNum = 0;
}
