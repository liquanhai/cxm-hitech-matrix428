#include "StdAfx.h"
#include "FrameIPSet.h"

CFrameIPSet::CFrameIPSet()
{
	Reset();
}

CFrameIPSet::~CFrameIPSet()
{
}

/**
* ���ö���
* @param void
* @return void
*/
void CFrameIPSet::Reset()
{
	// ԴIP��ַ
	m_uiIPSource = 0;
	// Ŀ��IP��ַ
	m_uiIPAim = IPBroadcastAddr;
	// Ŀ��˿ں�
	m_usPortAim = 0;
	// ����� 1-��������Ӧ��2-��ѯ����Ӧ��3-AD���������ط�
	m_usCommand = 0;
	// ����SN��
	m_uiSN = 0;
	// �������� 1-����վ��2-��Դվ��3-�ɼ�վ
	m_uiInstrumentType = 0;
	// ��������IP
	m_uiIPInstrument = 0;
	// ·��IP��ַ��·�ɷ��� 1-��
	m_uiRoutIPTop = 0;
	// ·��IP��ַ��·�ɷ��� 2-��
	m_uiRoutIPDown = 0;
	// ·��IP��ַ��·�ɷ��� 3-��
	m_uiRoutIPLeft = 0;
	// ·��IP��ַ��·�ɷ��� 4-��
	m_uiRoutIPRight = 0;
	// ·��IP��ַ
	m_uiRoutIP = 0;
	// �㲥�˿�
	m_uiBroadCastPort = 0;
	// ·�ɿ���
	m_uiRoutOpen = 0;
}

/**
* ����IP��ַ����Ӧ��֡
* @param void
* @return bool true���ɹ���false��ʧ��
*/
bool CFrameIPSet::ParseFrame()
{
	unsigned char	byCommandWord = 0;
	int iPos = 28;
	// ���ö���
	Reset();
	while(true)
	{
		memcpy(&byCommandWord, &m_pRcvFrameData[iPos], FrameCmdSize1B);
		iPos += FrameCmdSize1B;
		if (byCommandWord == CmdSn)
		{
			memcpy(&m_uiSN, &m_pRcvFrameData[iPos], FramePacketSize4B);
		}
		else if (byCommandWord == CmdLocalIPAddr)
		{
			memcpy(&m_uiIPInstrument, &m_pRcvFrameData[iPos], FramePacketSize4B);
		}
		else if (byCommandWord == CmdEnd)
		{
			break;
		}
		iPos += FramePacketSize4B;
	}
	return true;
}

void CFrameIPSet::MakeFrameData()
{
	memset(m_pSndFrameData, SndFrameBufInit, SndFrameSize);
	m_pSndFrameData[0] = FrameHeadCheck0;
	m_pSndFrameData[1] = FrameHeadCheck1;
	m_pSndFrameData[2] = FrameHeadCheck2;
	m_pSndFrameData[3] = FrameHeadCheck3;
	// ԴIP��ַ
	int iPos = FrameHeadSize;
	memcpy(&m_pSndFrameData[iPos], &m_uiIPSource, FramePacketSize4B);
	iPos += FramePacketSize4B;
	// Ŀ��IP��ַ
	memcpy(&m_pSndFrameData[iPos], &m_uiIPAim, FramePacketSize4B);
	iPos += FramePacketSize4B;
	// Ŀ��˿ں�
	memcpy(&m_pSndFrameData[iPos], &m_usPortAim, FramePacketSize2B);
	iPos += FramePacketSize2B;
	// ����� 1-��������Ӧ��2-��ѯ����Ӧ��3-AD���������ط�
	memcpy(&m_pSndFrameData[iPos], &m_usCommand, FramePacketSize2B);
	iPos += FramePacketSize2B;
	// ��ʱ��
	iPos += FramePacketSize4B;
	if (m_usCommand == SendSetCmd)
	{
		// ������������������
		m_pSndFrameData[iPos] = CmdSn;
		iPos += FrameCmdSize1B;
		// ����SN��
		memcpy(&m_pSndFrameData[iPos], &m_uiSN, FramePacketSize4B);
		iPos += FramePacketSize4B;

		// ��������վ��IP��ַ����������
		m_pSndFrameData[iPos] = CmdLocalIPAddr;
		iPos += FrameCmdSize1B;
		// ��������IP
		memcpy(&m_pSndFrameData[iPos], &m_uiIPInstrument, FramePacketSize4B);
		iPos += FramePacketSize4B;
		// �ɼ�վ�͵�Դվ����·�ɵ�ַ���òɼ�վ�㲥�˿�
		if((m_uiInstrumentType == InstrumentTypeFDU)	
			|| (m_uiInstrumentType == InstrumentTypeLAUL))// �������� 1-����վ��2-��Դվ��3-�ɼ�վ
		{
			// �㲥����
			m_pSndFrameData[iPos] = CmdSetBroadCastPort;
			iPos += FrameCmdSize1B;
			// ���ù㲥�˿�    
			memcpy(&m_pSndFrameData[iPos], &m_uiBroadCastPort, FramePacketSize4B);
			iPos += FramePacketSize4B;
		}
		// LCI�ͽ���վ��Ҫ����·��IP��ַ
		else
		{
			// ����·�ɵ�ַ����������
			m_pSndFrameData[iPos] = CmdLAUXSetRout;
			iPos += FrameCmdSize1B;
			// ·��IP��ַ��·�ɷ��� 4-��
			memcpy(&m_pSndFrameData[iPos], &m_uiRoutIPRight, FramePacketSize4B);
			iPos += FramePacketSize4B;
			// ����·�ɵ�ַ����������
			m_pSndFrameData[iPos] = CmdLAUXSetRout;
			iPos += FrameCmdSize1B;
			// ·��IP��ַ��·�ɷ��� 3-��
			memcpy(&m_pSndFrameData[iPos], &m_uiRoutIPLeft, FramePacketSize4B);
			iPos += FramePacketSize4B;
			// ����·�ɵ�ַ����������
			m_pSndFrameData[iPos] = CmdLAUXSetRout;
			iPos += FrameCmdSize1B;
			// ·��IP��ַ��·�ɷ��� 1-��
			memcpy(&m_pSndFrameData[iPos], &m_uiRoutIPTop, FramePacketSize4B);
			iPos += FramePacketSize4B;
			// ����·�ɵ�ַ����������
			m_pSndFrameData[iPos] = CmdLAUXSetRout;
			iPos += FrameCmdSize1B;
			// ·��IP��ַ��·�ɷ��� 2-��
			memcpy(&m_pSndFrameData[iPos], &m_uiRoutIPDown, FramePacketSize4B);
			iPos += FramePacketSize4B;

			// ���Ϊ����վ���4�������·��
			// ����·�ɿ�������������
			m_pSndFrameData[iPos] = CmdLAUXRoutOpenSet;
			iPos += FrameCmdSize1B;
			// ·�ɿ��ش�
			memcpy(&m_pSndFrameData[iPos], &m_uiRoutOpen, FramePacketSize4B);
			iPos += FramePacketSize4B;
		}
		m_pSndFrameData[iPos] = CmdEnd;
	}
	else if (m_usCommand == SendQueryCmd)
	{
		// ��������վ��IP��ַ����������
		m_pSndFrameData[iPos] = CmdLocalIPAddr;
		iPos += FrameCmdSize1B;
		iPos += FramePacketSize4B;
		m_pSndFrameData[iPos] = CmdEnd;
	}
}