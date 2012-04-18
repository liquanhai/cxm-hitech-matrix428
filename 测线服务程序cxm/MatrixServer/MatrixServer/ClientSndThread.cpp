#include "StdAfx.h"
#include "ClientSndThread.h"


CClientSndThread::CClientSndThread(void)
{
	m_pClientSndFrame = NULL;
}


CClientSndThread::~CClientSndThread(void)
{
}

// ������
void CClientSndThread::OnProc(void)
{
	int iFrameNum = 0;
	m_oCommFrameStructPtr ptrFrame = NULL;
	EnterCriticalSection(&m_pClientSndFrame->m_oSecClientFrame);

	iFrameNum = m_pClientSndFrame->m_olsCommWorkFrame.size();
	for (int i=0; i<iFrameNum; i++)
	{
		ptrFrame = *m_pClientSndFrame->m_olsCommWorkFrame.begin();
		// ���͸�֡
		ptrFrame->m_uiTimeOutCount = 0;
		ptrFrame->m_uiSndCount = 1;
		m_pClientSndFrame->MakeSendFrame(ptrFrame);
		m_pClientSndFrame->m_olsCommWorkFrame.pop_front();
		// ���Ϊ����֡������뷢��֡����
		if (ptrFrame->m_cCmdType == CmdTypeSet)
		{
			
		}
		// ���ΪӦ��֡���ͺ�������עӦ��
		else if (ptrFrame->m_cCmdType == CmdTypeReturn)
		{
			m_pClientSndFrame->AddFreeFrameStruct(ptrFrame);
		}
	}
	LeaveCriticalSection(&m_pClientSndFrame->m_oSecClientFrame);
}