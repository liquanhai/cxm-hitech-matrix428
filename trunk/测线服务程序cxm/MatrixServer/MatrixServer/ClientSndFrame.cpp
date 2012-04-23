#include "StdAfx.h"
#include "ClientSndFrame.h"


CClientSndFrame::CClientSndFrame(void)
{
	m_pClientSocket = NULL;
}


CClientSndFrame::~CClientSndFrame(void)
{
}


// ����Ӧ��֡
void CClientSndFrame::MakeReturnFrame(m_oCommFrameStructPtr ptrFrame)
{
	m_oCommFrameStructPtr pFrameStruct = NULL;
	EnterCriticalSection(&m_oSecClientFrame);
	pFrameStruct = GetFreeFrameStruct();
	pFrameStruct->m_cCmdType = CmdTypeReturn;
	pFrameStruct->m_usCmd = ptrFrame->m_usCmd;
	pFrameStruct->m_uiServerTimeStep = GetTickCount();
	pFrameStruct->m_uiClientTimeStep = ptrFrame->m_uiClientTimeStep;
	pFrameStruct->m_uiPacketIndex = ptrFrame->m_uiPacketIndex;
	pFrameStruct->m_uiCmdIndex = ptrFrame->m_uiCmdIndex;
	pFrameStruct->m_uiFrameNum = ptrFrame->m_uiFrameNum;
	pFrameStruct->m_uiFrameIndex = ptrFrame->m_uiFrameIndex;
	// ���յ���֡���Ϊ����֡�����һ֡
	if (ptrFrame->m_uiFrameIndex == ptrFrame->m_uiFrameNum)
	{
		pFrameStruct->m_cResult = CmdResultSuccess;
	}
	else
	{
		pFrameStruct->m_cResult = CmdResultWait;
	}
	pFrameStruct->m_usFrameInfoSize = ptrFrame->m_usFrameInfoSize;
	memcpy(&pFrameStruct->m_pcFrameInfo, &ptrFrame->m_pcFrameInfo, 
		pFrameStruct->m_usFrameInfoSize);
	m_olsCommWorkFrame.push_back(pFrameStruct);
	LeaveCriticalSection(&m_oSecClientFrame);
}
// ���ɷ���֡
void CClientSndFrame::MakeSendFrame(m_oCommFrameStructPtr ptrFrame)
{
	char* pChar = m_pClientSocket->m_cSndBuf;
	int iPos = 0;
	unsigned short usCmd = 0;
	unsigned short usFrameLength = 0;
	memset(pChar, 0, FrameSizeLimit);
	pChar[iPos] = FrameHead1;
	iPos++;
	pChar[iPos] = FrameHead2;
	iPos++;
	pChar[iPos] = FrameHead3;
	iPos++;
	pChar[iPos] = FrameHead4;
	iPos++;
 	// ֡����
	usFrameLength = ptrFrame->m_usFrameInfoSize + FrameTailSize + FrameHeadInfoSize;
 	memcpy(&pChar[iPos], &usFrameLength, 2);
	iPos += 2;
	// ֡�����֣�����֡�Ĺ���
	usCmd = ptrFrame->m_usCmd;
	if (ptrFrame->m_cCmdType == CmdTypeReturn)
	{
		usCmd |= CmdReturnBit;
	}
	memcpy(&pChar[iPos], &usCmd, 2);
	iPos += 2;
	// �����ʱ���
	memcpy(&pChar[iPos], &ptrFrame->m_uiServerTimeStep, 4);
	iPos += 4;
	// �ͻ���ʱ���
	memcpy(&pChar[iPos], &ptrFrame->m_uiClientTimeStep, 4);
	iPos += 4;
	// ����ˮ��
	memcpy(&pChar[iPos], &ptrFrame->m_uiPacketIndex, 4);
	iPos += 4;
	// ������ˮ��
	memcpy(&pChar[iPos], &ptrFrame->m_uiCmdIndex, 4);
	iPos += 4;
	// ��֡��
	memcpy(&pChar[iPos], &ptrFrame->m_uiFrameNum, 4);
	iPos += 4;
	// ֡���
	memcpy(&pChar[iPos], &ptrFrame->m_uiFrameIndex, 4);
	iPos += 4;
	// ֡����ִ�н��
	memcpy(&pChar[iPos], &ptrFrame->m_cResult, 1);
	iPos += 1;
	memcpy(&pChar[iPos], &ptrFrame->m_pcFrameInfo, ptrFrame->m_usFrameInfoSize);
	iPos += ptrFrame->m_usFrameInfoSize;
	pChar[iPos] = FrameTail;
	iPos++;
	m_pClientSocket->Send(pChar, 
		ptrFrame->m_usFrameInfoSize + FrameHeadSize + FrameLengthSize + FrameTailSize + FrameHeadInfoSize);
}
