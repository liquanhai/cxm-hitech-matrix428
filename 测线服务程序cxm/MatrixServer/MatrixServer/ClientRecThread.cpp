#include "StdAfx.h"
#include "ClientRecThread.h"


CClientRecThread::CClientRecThread(void)
{
	m_pClientRecFrame = NULL;
	m_pClientSndFrame = NULL;
}


CClientRecThread::~CClientRecThread(void)
{
}

// ������
void CClientRecThread::OnProc(void)
{
	int iFrameNum = 0;
	m_oCommFrameStructPtr ptrFrame = NULL;
	EnterCriticalSection(&m_pClientRecFrame->m_oSecClientFrame);
	iFrameNum = m_pClientRecFrame->m_olsCommWorkFrame.size();
	for (int i=0; i<iFrameNum; i++)
	{
		ptrFrame = *m_pClientRecFrame->m_olsCommWorkFrame.begin();
		// ���Ϊ����֡
		if (ptrFrame->m_cCmdType == CmdTypeSet)
		{
			// ��֡���ݼ��������������

			// ����Ӧ��֡
			m_pClientSndFrame->MakeReturnFrame(ptrFrame);
		}
		// ���ΪӦ��֡
		else if (ptrFrame->m_cCmdType == CmdTypeReturn)
		{
			// ���ѷ���֡�������ҵ���֡��ɾ��
		}
		m_pClientRecFrame->m_olsCommWorkFrame.pop_front();
	}
	LeaveCriticalSection(&m_pClientRecFrame->m_oSecClientFrame);
}
