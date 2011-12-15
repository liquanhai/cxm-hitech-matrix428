#include "StdAfx.h"
#include "FrameTail.h"

CFrameTail::CFrameTail()
{
}

CFrameTail::~CFrameTail()
{
}

/**
* ���ö���
* @param void
* @return void
*/
void CFrameTail::Reset()
{
	// ��������IP��ַ
	m_uiIPInstrument = 0;
	// ����SN��
	m_uiSN = 0;
	// �������� 1-����վ��2-��Դվ��3-�ɼ�վ
	m_uiInstrumentType = 0;
	// ����ϵͳʱ��
	m_uiTimeSystem = 0;
	// ·��IP��ַ��·�ɷ��� 1-�ϣ�2-�£�3-��4-��
	m_uiRoutIP = 0;
}

/**
* ����β��֡
* @param void
* @return bool true���ɹ���false��ʧ��
*/
bool CFrameTail::ParseFrame()
{
	unsigned char	byCommandWord = 0;
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
		else if (byCommandWord == CmdLocalIPAddr)
		{
			memcpy(&m_uiIPInstrument, &m_pFrameData[iPos], FramePacketSize4B);
		}
		else if (byCommandWord == CmdLocalSysTime)
		{
			memcpy(&m_uiTimeSystem, &m_pFrameData[iPos], FramePacketSize4B);
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