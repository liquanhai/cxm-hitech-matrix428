#include "stdafx.h"
#include "MatrixCommDll.h"

CCommRecFrame::CCommRecFrame(void)
{
}


CCommRecFrame::~CCommRecFrame(void)
{
}

// ����֡
void CCommRecFrame::PhraseFrame(char* cpFrame, unsigned short usSize)
{
	int iPos = 0;
	unsigned short usCmd = 0;
	m_oCommFrameStructPtr pFrameStruct = NULL;
	EnterCriticalSection(&m_oSecClientFrame);
	pFrameStruct = GetFreeFrameStruct();
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
	pFrameStruct->m_usCmd = usCmd & (~CmdReturnBit);
	// �����ʱ���
	memcpy(&pFrameStruct->m_uiSrcTimeStep, &cpFrame[iPos], 4);
	iPos += 4;
	// �ͻ���ʱ���
	memcpy(&pFrameStruct->m_uiDstTimeStep, &cpFrame[iPos], 4);
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
	memcpy(&pFrameStruct->m_pcFrameInfo, &cpFrame[iPos], usSize);
	iPos += FrameHeadInfoSize;
	m_olsCommWorkFrame.push_back(pFrameStruct);
	LeaveCriticalSection(&m_oSecClientFrame);
}