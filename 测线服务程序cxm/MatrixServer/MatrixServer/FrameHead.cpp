#include "StdAfx.h"
#include "FrameHead.h"

CFrameHead::CFrameHead()
{
	Reset();
}

CFrameHead::~CFrameHead()
{
}

/**
* ���ö���
* @param void
* @return void
*/
void CFrameHead::Reset()
{
	// ����SN��
	m_uiSN = 0;
	// �����װ�ʱ��
	m_uiTimeHeadFrame = 0;
	// ·��IP��ַ
	m_uiRoutIP = 0;
	// ��������ʱ��
	m_uiSysTime = 0;
}

/**
* �����װ�֡
* @param void
* @return bool true���ɹ���false��ʧ��
*/
bool CFrameHead::ParseFrame()
{
	unsigned char	byCommandWord = 0;
	// ����SN��
	int iPos = 28;
	// ���ö���
	Reset();
	while(true)
	{
		memcpy(&byCommandWord, &m_pFrameData[iPos], FrameCmdSize1B);
		iPos += FrameCmdSize1B;
		if (byCommandWord == CmdSn)
		{
			memcpy(&m_uiSN, &m_pFrameData[iPos], FramePacketSize4B);
		}
		else if (byCommandWord == CmdHeadFrameTime)
		{
			memcpy(&m_uiTimeHeadFrame, &m_pFrameData[iPos], FramePacketSize4B);
		}
		else if (byCommandWord == CmdLocalSysTime)
		{
			memcpy(&m_uiSysTime, &m_pFrameData[iPos], FramePacketSize4B);
		}
		else if (byCommandWord == CmdReturnRout)
		{
			memcpy(&m_uiRoutIP, &m_pFrameData[iPos], FramePacketSize4B);
		}
		else if (byCommandWord == CmdEnd)
		{
			break;
		}
		iPos += FramePacketSize4B;
	}
	return true;
}