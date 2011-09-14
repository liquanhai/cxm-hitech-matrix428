// ThreadProcTailFrame.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "TestSiteManage.h"
#include "ThreadProcTailFrame.h"


// CThreadProcTailFrame

IMPLEMENT_DYNCREATE(CThreadProcTailFrame, CWinThread)

CThreadProcTailFrame::CThreadProcTailFrame()
{
	// �Ƿ���״̬
	m_bWork = false;
	// �Ƿ�ر��߳�
	m_bClose = false;
}

CThreadProcTailFrame::~CThreadProcTailFrame()
{
}

BOOL CThreadProcTailFrame::InitInstance()
{
	// TODO: �ڴ�ִ���������̳߳�ʼ��
	return TRUE;
}

int CThreadProcTailFrame::ExitInstance()
{
	// TODO: �ڴ�ִ���������߳�����
	return CWinThread::ExitInstance();
}

BEGIN_MESSAGE_MAP(CThreadProcTailFrame, CWinThread)
END_MESSAGE_MAP()

// CThreadProcTailFrame ��Ϣ�������

/**
* �߳�������
* @param void
* @return int
*/
int CThreadProcTailFrame::Run()
{
	// ѭ����ֱ���رձ�־Ϊ��
	while(true)
	{
		// �жϹرձ�־�Ƿ�Ϊ��
		if(true == m_bClose)
		{
			break;
		}
		// ����β��֡
		ProcTailFrame();
		// �жϹرձ�־�Ƿ�Ϊ��
		if(true == m_bClose)
		{
			break;
		}
		// ����50����
		Wait(1);
	}
	// ����β�������̹߳رձ�־Ϊ��
	m_pSiteData->m_bProcTailFrameClose = true;
	// ����
	return CWinThread::Run();
}

/**
* ��ʼ���߳�
* @param void
* @return bool true���ɹ���false��ʧ��
*/
bool CThreadProcTailFrame::OnInit()
{
	// �Ƿ���״̬
	m_bWork = false;
	// �Ƿ�ر��߳�
	m_bClose = false;
	return true;
}

/**
* �ر��߳�
* @param void
* @return bool true���ɹ���false��ʧ��
*/
bool CThreadProcTailFrame::OnClose()
{
	// �Ƿ�ر��߳�
	m_bClose = true;
	return true;
}

/**
* �߳̿�ʼ����
* @param void
* @return bool true���ɹ���false��ʧ��
*/
bool CThreadProcTailFrame::OnWork()
{
	// �Ƿ���״̬
	m_bWork = true;
	return true;
}

/**
* �߳�ֹͣ����
* @param void
* @return bool true���ɹ���false��ʧ��
*/
bool CThreadProcTailFrame::OnStop()
{
	// �Ƿ���״̬
	m_bWork = false;
	return true;
}

/**
* �̵߳ȴ�
* @param int iWaitStopCount ���ȴ�������ÿ��50����
* @return void
*/
void CThreadProcTailFrame::Wait(int iWaitStopCount)
{
	// �ȴ�����
	int iWaitCount = 0;
	while(true)
	{	
		Sleep(50);	// ����
		iWaitCount++;	// �ȴ�����
		// �ж��Ƿ���Դ��������
		if(false == JudgeProcCondition())
		{
			return;
		}
		// �ȴ�����
		if(iWaitStopCount <= iWaitCount)
		{
			return;
		}		
	}
}

/**
* �ж��Ƿ���Դ��������
* @param void
* @return bool true����������false��ֹͣ����
*/
bool CThreadProcTailFrame::JudgeProcCondition()
{	
	// ɾ��������·�ɴ����߳��������У����ֳ���������߳���������
	if((true == m_pSiteData->m_bProcDeleteRunning) || (true == m_pSiteData->m_bProcSiteDataOutputRunning))
	{		
		m_pSiteData->m_bProcTailFramePause = true;	// β�������߳���ͣ
		return false;
	}
	else
	{		
		m_pSiteData->m_bProcTailFramePause = false;	// β�������̹߳���
	}
	// �ǹ���״̬
	if(false == m_bWork)
	{		
		m_pSiteData->m_bProcTailFrameStop = true;	// β�������߳�ֹͣ
		return false;
	}
	else
	{
		m_pSiteData->m_bProcTailFrameStop = false;	// β�������̹߳���
	}
	return true;
}

/**
* ����β��֡
* @note ������˿ڵõ�Ұ������������β��֡����֡����
* @note �Ǵ���״̬ʱ����ȡβ��֡��Ȼ����������
* @note �Ǵ���״̬�����ڣ��ֳ�����ֹͣʱ��ɾ��������·�ɴ����߳���������ʱ���ֳ���������߳���������ʱ��
* @param void
* @return void
*/
void CThreadProcTailFrame::ProcTailFrame()
{
	// ֡��������Ϊ0
	int iFrameCount = 0;
	// �õ�����˿�β��֡����
	iFrameCount = m_pSocketTailFrame->GetFrameCount();
	// �ж�֡�����Ƿ����0
	if(iFrameCount > 0)
	{
		// ѭ������ÿ1֡
		for(int i = 0; i < iFrameCount; i++)
		{
			// �õ�֡����
			m_pSocketTailFrame->GetFrameData();
			// �ж��Ƿ���Դ��������
			if(true ==JudgeProcCondition())
			{
				// ������β��֡
				ProcTailFrameOne(&m_pSocketTailFrame->m_oFrameTail);
			}
		}		
	}
}

/**
* ������β��֡
* @param CFrameTail* pFrameTail β��ָ֡��
* @return void
*/
void CThreadProcTailFrame::ProcTailFrameOne(CFrameTail* pFrameTail)
{
	// ��������ָ��Ϊ��
	CInstrument* pInstrument = NULL;
	// �жϣ���������SN�ҵ���������
	if(TRUE == m_pSiteData->m_oSNInstrumentMap.GetInstrument(pFrameTail->m_uiSN, pInstrument))
	{
		// ����β��������1
		pInstrument->m_uiTailFrameCount++;
		// �жϣ�����β������С��3
		if(pInstrument->m_uiTailFrameCount < 3 )
		{
			return;
		}
	}
	else
	{
		return;
	}
	pFrameTail->m_uiRoutIP=0x0f & pFrameTail->m_uiRoutIP;		// add test by zl 04.12
	// �жϣ�������վ������β��
	if((0 == pFrameTail->m_uiRoutIP) && (1 == pFrameTail->m_uiInstrumentType))
	{
		// ����Ұ���豸ϵͳʱ��		//��ȡm_pSiteData->m_uiSystemTimeSite����ȡ���������ɼ�վ��ȡ 04.12
//		unsigned int uiSystemTimeSite = (unsigned int)(((double)pFrameTail->m_uiTimeSystem / 4096.0) * 1000.0);
/*		m_pSiteData->m_oCriticalSectionSystemTimeSite.Lock();
			//m_pSiteData->m_uiSystemTimeSite = uiSystemTimeSite;
			m_pSiteData->m_uiSystemTimeSite =pFrameTail->m_uiTimeSystem;
		m_pSiteData->m_oCriticalSectionSystemTimeSite.Unlock();
*///		TRACE1("ϵͳʱ��%d\r\n", m_pSiteData->m_uiSystemTimeSite);
		return;
	}

	// �жϣ�����վ������β��
	if((0 != pFrameTail->m_uiRoutIP) && (1 == pFrameTail->m_uiInstrumentType))
	{
		// ����·��ָ��Ϊ��
		CRout* pRout = NULL;
		// �жϣ�����·��IP��ַ�ҵ�·�ɶ���
		if(TRUE == m_pSiteData->m_oRoutIPRoutMap.GetRout(pFrameTail->m_uiRoutIP, pRout))
		{
			// �жϣ�β�����Խ����߷���
			if((1 == pRout->m_uiRoutDirection) || (2 == pRout->m_uiRoutDirection))
			{
				// ����·��ʱ��
				pRout->UpdateRoutTime();	
				// ����ʱͳ
				ProcTimeDelay(pRout);
			}
			// �жϣ�β�����Դ��߷���
			else if((3 == pRout->m_uiRoutDirection) || (4 == pRout->m_uiRoutDirection))
			{
				// ��������ָ��Ϊ��
				CInstrument* pInstrument = NULL;
				// �жϣ���������SN�ҵ���������
				if(TRUE == m_pSiteData->m_oSNInstrumentMap.GetInstrument(pFrameTail->m_uiSN, pInstrument))
				{
					// �жϣ�·�ɷ�������������������
					if((pRout->m_pTail != NULL) && (pRout->m_pTail != pInstrument))
					{
						// ����������ʱ�����β������	add by zl 2011.9.5
						CInstrument* pInstrument1 = pRout->m_pHead;
						while(true)
						{
							// �õ���һ����
							pInstrument1 = m_pThreadProcTimeDelay->GetNextInstrument(pInstrument1);
							if(pInstrument1==NULL)
								break;
							pInstrument1->m_uiTailFrameCount=0;
							// ����һ��������
							if(NULL == pInstrument1)
							{
								break;
							}
						}
						// �жϣ�·�ɷ�������������ָ�벻Ϊ��
						if((3 == pRout->m_uiRoutDirection) && (NULL != pInstrument->m_pInstrumentLeft))
						{
							// �жϣ�ɾ���߳̿���
							if(true == m_pThreadProcDelete->Lock())
							{
								// ɾ�����������ұ�
								pInstrument->m_pInstrumentLeft->m_uiDeleteDirection = 4;
								// ����һ����Ҫ����ɾ��������
								m_pThreadProcDelete->AddInstrumentForDelete(pInstrument->m_pInstrumentLeft);
								// ����ɾ���߳�
								m_pThreadProcDelete->ResumeProcDelete();
							}
						}
						// �жϣ�·�ɷ������ң�������ָ�벻Ϊ��
						if((4 == pRout->m_uiRoutDirection) && (NULL != pInstrument->m_pInstrumentRight))
						{
							// �жϣ�ɾ���߳̿���
							if(true == m_pThreadProcDelete->Lock())
							{
								// ɾ�������������
								pInstrument->m_pInstrumentRight->m_uiDeleteDirection = 3;
								// ����һ����Ҫ����ɾ��������
								m_pThreadProcDelete->AddInstrumentForDelete(pInstrument->m_pInstrumentRight);
								// ����ɾ���߳�
								m_pThreadProcDelete->ResumeProcDelete();
							}
						}
					}
				}
			}
		}
		// ����·��IP��ַû���ҵ�·�ɶ���
		else
		{	
			CString strDesc;
			strDesc.Format("Can not find Rout In RoutMap. RoutIP=%d", pFrameTail->m_uiRoutIP);
			// ��¼������־�ļ�
			m_pSiteData->m_oRunTimeDataList.Set(2, "CThreadProcTailFrame", "ProcTailFrameOne", strDesc);
		}
		return;
	}
	// �жϣ��ɼ�վ���Դվ������β��
	if((0 != pFrameTail->m_uiRoutIP) && (1 != pFrameTail->m_uiInstrumentType))
	{
		// ����·��ָ��Ϊ��
		CRout* pRout = NULL;
		// �жϣ�����·��IP��ַ�ҵ�·�ɶ���
		if(TRUE == m_pSiteData->m_oRoutIPRoutMap.GetRout(pFrameTail->m_uiRoutIP, pRout))
		{
			//����β��ʱ�̶�ȡ
			//unsigned int uiSystemTimeSite = (unsigned int)(((double)pFrameTail->m_uiTimeSystem / 4096.0) * 1000.0);
			m_pSiteData->m_oCriticalSectionSystemTimeSite.Lock();
				m_pSiteData->m_uiSystemTimeSite =pFrameTail->m_uiTimeSystem;
			m_pSiteData->m_oCriticalSectionSystemTimeSite.Unlock();

			// ����·��ʱ��
			pRout->UpdateRoutTime();
			// ����ʱͳ
			ProcTimeDelay(pRout);
			// ��������ָ��Ϊ��
			CInstrument* pInstrument = NULL;
			// �жϣ���������SN�ҵ���������
			if(TRUE == m_pSiteData->m_oSNInstrumentMap.GetInstrument(pFrameTail->m_uiSN, pInstrument))
			{
				// �жϣ�·�ɷ�������������������
				if((pRout->m_pTail != NULL) && (pRout->m_pTail != pInstrument))
				{
					// ����������ʱ�����β������	add by zl 2011.9.5
					CInstrument* pInstrument1 = pRout->m_pHead;
					while(true)
					{
						// �õ���һ����
						pInstrument1 = m_pThreadProcTimeDelay->GetNextInstrument(pInstrument1);
						if(pInstrument1==NULL)
							break;
						pInstrument1->m_uiTailFrameCount=0;
						// ����һ��������
						if(NULL == pInstrument1)
						{
							break;
						}
					}
					// �жϣ�·�ɷ�������������ָ�벻Ϊ��
					if((3 == pRout->m_uiRoutDirection) && (NULL != pInstrument->m_pInstrumentLeft))
					{
						// �жϣ�ɾ���߳̿���
						if(true == m_pThreadProcDelete->Lock())
						{
							// ɾ�����������ұ�
							pInstrument->m_pInstrumentLeft->m_uiDeleteDirection = 4;
							// ����һ����Ҫ����ɾ��������
							m_pThreadProcDelete->AddInstrumentForDelete(pInstrument->m_pInstrumentLeft);
							// ����ɾ���߳�
							m_pThreadProcDelete->ResumeProcDelete();
						}
					}
					// �жϣ�·�ɷ������ң�������ָ�벻Ϊ��
					if((4 == pRout->m_uiRoutDirection) && (NULL != pInstrument->m_pInstrumentRight))
					{
						// �жϣ�ɾ���߳̿���
						if(true == m_pThreadProcDelete->Lock())
						{
							// ɾ�������������
							pInstrument->m_pInstrumentRight->m_uiDeleteDirection = 3;
							// ����һ����Ҫ����ɾ��������
							m_pThreadProcDelete->AddInstrumentForDelete(pInstrument->m_pInstrumentRight);
							// ����ɾ���߳�
							m_pThreadProcDelete->ResumeProcDelete();
						}
					}
				}
			}
		}
		// ����·��IP��ַû���ҵ�·�ɶ���
		else
		{	
			CString strDesc;
			strDesc.Format("Can not find Rout In RoutMap. RoutIP=%d", pFrameTail->m_uiRoutIP);
			// ��¼������־�ļ�
			m_pSiteData->m_oRunTimeDataList.Set(2, "CThreadProcTailFrame", "ProcTailFrameOne", strDesc);
		}
	}
}

/**
* ����·��ʱͳ
* @param CRout* pRout ·��ָ��
* @return void
*/
void CThreadProcTailFrame::ProcTimeDelay(CRout* pRout)
{
	// ʱ�Ӵ����߳̿���
	if(true == m_pThreadProcTimeDelay->IsThreadFree())
	{
		// �ж�·���Ƿ������û��ʱ��������·��
		if(true == m_pSiteData->m_oRoutIPRoutMap.JudgeRoutIsLongestTime(pRout))
		{
			// �����ϴ�ʱͳ����ʱ��
			pRout->UpdateDelayProcTime();
			// ʱ�Ӵ���������
			m_pThreadProcTimeDelay->m_bFree = false;
			// ����·�ɶ���
			m_pThreadProcTimeDelay->SetRout(pRout);
			// ����ʱ�Ӵ���
			m_pThreadProcTimeDelay->ResumeProcTimeDelay();
//			TRACE1("ʱ�Ӵ���-����SN�ţ�%d\r\n", pRout->m_uiSNTail);
		}
	}
}