#include "StdAfx.h"
#include "ClientRecFrame.h"


CClientRecFrame::CClientRecFrame(void)
{
}


CClientRecFrame::~CClientRecFrame(void)
{
}

// ����֡
void CClientRecFrame::PhraseFrame(char* cpFrame, unsigned short usSize)
{
	int iPos = 0;
	unsigned short usCmd = 0;
	m_oCommFrameStructPtr pFrameStruct = NULL;
	pFrameStruct = GetFreeRecFrameStruct();
	// ֡���ݳ���
	pFrameStruct->m_usFrameInfoSize = usSize;
	memcpy(&usCmd, &cpFrame[iPos], 2);
	iPos += 2;
	// ֡��������
	if (usCmd & CmdReturnBit)
	{
		pFrameStruct->m_cCmdType = CmdTypeReturn;
	}
	else
	{
		pFrameStruct->m_cCmdType = CmdTypeSet;
	}
	// ֡�����֣�����֡�Ĺ���
	pFrameStruct->m_usCmd = usCmd & (!CmdReturnBit);
	// �����ʱ���
	memcpy(&pFrameStruct->m_uiServerTimeStep, &cpFrame[iPos], 4);
	iPos += 4;
	// �ͻ���ʱ���
	memcpy(&pFrameStruct->m_uiClientTimeStep, &cpFrame[iPos], 4);
	iPos += 4;
	// ����ˮ��
	memcpy(&pFrameStruct->m_uiPacketIndex, &cpFrame[iPos], 4);
	iPos += 4;
	// ������ˮ��
	memcpy(&pFrameStruct->m_uiCmdIndex, &cpFrame[iPos], 4);
	iPos += 4;
	// ��֡��
	memcpy(&pFrameStruct->m_uiFrameNum, &cpFrame[iPos], 4);
	iPos += 4;
	// ֡���
	memcpy(&pFrameStruct->m_uiFrameIndex, &cpFrame[iPos], 4);
	iPos += 4;
	// ֡����ִ�н��
	memcpy(&pFrameStruct->m_cResult, &cpFrame[iPos], 1);
	iPos += 1;
	// ֡����,���Ϊ��ѯ������֡���ݵ�ǰ�����ֽڷֱ����кź������
	memcpy(&pFrameStruct->m_pcFrameInfo, &cpFrame[iPos], usSize - FrameHeadInfoSize);
	iPos += FrameHeadInfoSize;
	EnterCriticalSection(&m_oSecClientFrame);
	m_olsCommWorkFrame.push_back(pFrameStruct);
	LeaveCriticalSection(&m_oSecClientFrame);
}