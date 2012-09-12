#include "StdAfx.h"
#include "PcapSndThread.h"


CPcapSndThread::CPcapSndThread(void)
{
	m_pNetPcapComm = NULL;
}


CPcapSndThread::~CPcapSndThread(void)
{
}
// ������
void CPcapSndThread::OnProc(void)
{
	int iFrameNum = 0;
	CNetPcapComm::FrameDataStruct* pFrameData = NULL;
	EnterCriticalSection(&m_pNetPcapComm->m_oSec);
	iFrameNum = m_pNetPcapComm->m_olsFrameDataUpStream.size();
	for (int i=0; i<iFrameNum; i++)
	{
		pFrameData = *m_pNetPcapComm->m_olsFrameDataUpStream.begin();
		// ���͸�֡
		if (pFrameData->m_uiLength == m_pNetPcapComm->SocketSndFrameData(pFrameData))
		{
			_InterlockedIncrement(&m_pNetPcapComm->m_lUpStreamNetSndFrameNum);
		}
		else
		{
			OutputDebugString(_T("����֡����ʧ�ܣ�"));
		}
		m_pNetPcapComm->m_olsFrameDataUpStream.pop_front();
		m_pNetPcapComm->AddFreeFrameData(pFrameData);
	}
	iFrameNum = m_pNetPcapComm->m_olsFrameDataDownStream.size();
	if (iFrameNum > 4)
	{
		iFrameNum = 4;
	}
	for (int i=0; i<iFrameNum; i++)
	{
		pFrameData = *m_pNetPcapComm->m_olsFrameDataDownStream.begin();
		// ���͸�֡
		if (pFrameData->m_uiLength == m_pNetPcapComm->SocketSndFrameData(pFrameData))
		{
			_InterlockedIncrement(&m_pNetPcapComm->m_lDownStreamNetSndFrameNum);
		}
		else
		{
			OutputDebugString(_T("����֡����ʧ�ܣ�"));
		}
		m_pNetPcapComm->m_olsFrameDataDownStream.pop_front();
		m_pNetPcapComm->AddFreeFrameData(pFrameData);
	}
	LeaveCriticalSection(&m_pNetPcapComm->m_oSec);
}