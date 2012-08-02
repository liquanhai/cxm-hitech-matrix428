#include "stdafx.h"
#include "MatrixCommDll.h"

CCommSndThread::CCommSndThread(void)
{
	m_pCommSndFrame = NULL;
}


CCommSndThread::~CCommSndThread(void)
{
}

// ������
void CCommSndThread::OnProc(void)
{
	int iFrameNum = 0;
	bool bReSend = true;
	m_oCommFrameStructPtr ptrFrame = NULL;
	EnterCriticalSection(&m_pCommSndFrame->m_oSecClientFrame);
	iFrameNum = m_pCommSndFrame->m_olsCommWorkFrame.size();
	for (int i=0; i<iFrameNum; i++)
	{
		ptrFrame = *m_pCommSndFrame->m_olsCommWorkFrame.begin();
		// ���͸�֡
		ptrFrame->m_uiTimeOutCount = 0;
		ptrFrame->m_uiSndCount = 1;
		m_pCommSndFrame->MakeSendFrame(ptrFrame);
		m_pCommSndFrame->m_olsCommWorkFrame.pop_front();
		// ���Ϊ����֡��������ѷ���֡����
		if (ptrFrame->m_cCmdType == CmdTypeSet)
		{
			m_pCommSndFrame->AddFramePtrToSndMap(ptrFrame->m_usCmd, ptrFrame->m_uiSrcTimeStep, 
				ptrFrame->m_uiPacketIndex, ptrFrame, &m_pCommSndFrame->m_oSndFrameMap);
		}
		// ���ΪӦ��֡���ͺ�������עӦ��
		else if (ptrFrame->m_cCmdType == CmdTypeReturn)
		{
			m_pCommSndFrame->AddFreeFrameStruct(ptrFrame);
		}
	}
	bReSend = m_pCommSndFrame->OnReSendFrame();
	LeaveCriticalSection(&m_pCommSndFrame->m_oSecClientFrame);
	if (bReSend == false)
	{
		EnterCriticalSection(&m_pCommSndFrame->m_oSecClientFrame);
		m_pCommSndFrame->m_bConnectValid = false;
		LeaveCriticalSection(&m_pCommSndFrame->m_oSecClientFrame);
	}
}