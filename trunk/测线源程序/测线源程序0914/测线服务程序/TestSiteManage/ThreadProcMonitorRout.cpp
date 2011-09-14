// ThreadProcMonitorRout.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "TestSiteManage.h"
#include "ThreadProcMonitorRout.h"

// CThreadProcMonitorRout

IMPLEMENT_DYNCREATE(CThreadProcMonitorRout, CWinThread)

CThreadProcMonitorRout::CThreadProcMonitorRout()
{
	// �Ƿ���״̬
	m_bWork = false;
	// �Ƿ�ر��߳�
	m_bClose = false;
}

CThreadProcMonitorRout::~CThreadProcMonitorRout()
{
}

BOOL CThreadProcMonitorRout::InitInstance()
{
	// TODO: �ڴ�ִ���������̳߳�ʼ��
	return TRUE;
}

int CThreadProcMonitorRout::ExitInstance()
{
	// TODO: �ڴ�ִ���������߳�����
	return CWinThread::ExitInstance();
}

BEGIN_MESSAGE_MAP(CThreadProcMonitorRout, CWinThread)
END_MESSAGE_MAP()

// CThreadProcMonitorRout ��Ϣ�������

/**
* �߳�������
* @param void
* @return int
*/
int CThreadProcMonitorRout::Run()
{
	// ѭ����ֱ���رձ�־Ϊ��
	while(true)
	{
		// �жϹرձ�־�Ƿ�Ϊ��
		if(true == m_bClose)
		{
			break;
		}
		// ·�ɼ���
		ProcMonitorRout();
		// �жϹرձ�־�Ƿ�Ϊ��
		if(true == m_bClose)
		{
			break;
		}
		// ����1000����
		Wait(20);
	}
	// ·�ɼ����̹߳رձ�־Ϊ��
	m_pSiteData->m_bProcMonitorRoutClose = true;
	// ����
	return CWinThread::Run();
}

/**
* ��ʼ���߳�
* @param void
* @return bool true���ɹ���false��ʧ��
*/
bool CThreadProcMonitorRout::OnInit()
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
bool CThreadProcMonitorRout::OnClose()
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
bool CThreadProcMonitorRout::OnWork()
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
bool CThreadProcMonitorRout::OnStop()
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
void CThreadProcMonitorRout::Wait(int iWaitStopCount)
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
		if(iWaitStopCount == iWaitCount)
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
bool CThreadProcMonitorRout::JudgeProcCondition()
{	
	// ɾ��������·�ɴ����߳��������У����ֳ���������߳���������
	if((true == m_pSiteData->m_bProcDeleteRunning) || (true == m_pSiteData->m_bProcSiteDataOutputRunning))
	{		
		m_pSiteData->m_bProcMonitorRoutPause = true;	// �߳���ͣ
		return false;
	}
	else
	{		
		m_pSiteData->m_bProcMonitorRoutPause = false;	// �߳�����
	}
	// �ǹ���״̬
	if(false == m_bWork)
	{		
		m_pSiteData->m_bProcMonitorRoutStop = true;	// ·�ɼ����߳�ֹͣ
		return false;
	}
	else
	{
		m_pSiteData->m_bProcMonitorRoutStop = false;	// ·�ɼ����̹߳���
	}
	return true;
}

/**
* ·�ɼ���
* @param void
* @return void
*/
void CThreadProcMonitorRout::ProcMonitorRout()
{	
	// �жϣ����ܼ�������
	if(false == JudgeProcCondition())
	{
		return;
	}
	
	bool bResumeProcDelete = false;	// �Ƿ���ɾ���߳�	
	bool bDelete = false;	// �Ƿ�����ɾ����������ɾ��·��	
	CRout* pRout = NULL;	// ·�ɶ���ָ��	
	POSITION pos = NULL;	// λ��	
	unsigned int uiKey;	// ������

	// �õ���������ʼ·��λ��
	pos = m_pSiteData->m_oRoutIPRoutMap.m_oRoutMap.GetStartPosition();
	// ѭ�����õ�·������������·��
	while(NULL != pos)
	{
		pRout = NULL;
		// �õ�·�ɶ���
		m_pSiteData->m_oRoutIPRoutMap.m_oRoutMap.GetNextAssoc(pos, uiKey, pRout);
		// �жϣ�·��ָ�벻Ϊ��
		if(NULL != pRout)
		{
			// Ϊ·�ɼ����߳�׼�����߳�ͬ����������
			m_pSiteData->m_oCriticalSectionProcMonitorRout.Lock();
				// ɾ��·��IP��ַ����ֹ��·�ɶ��������ӵ�����
				bDelete = DeleteLinkInstrumentRoutWhenRoutIPDisable(pRout);
				// �жϣ�������ɾ����������ɾ��·��
				if(true == bDelete)	
				{
					// ���û���ɾ���̱߳�־Ϊ��
					bResumeProcDelete = true;
				}
				// ɾ��·��IP��ַ����ֹ��·�ɶ���
				bDelete = DeleteRoutWhenRoutIPDisable(pRout);
				// �жϣ�������ɾ����������ɾ��·��
				if(true == bDelete)
				{
					// ���û���ɾ���̱߳�־Ϊ��
					bResumeProcDelete = true;
				}
			// Ϊ·�ɼ����߳�׼�����߳�ͬ���������
			m_pSiteData->m_oCriticalSectionProcMonitorRout.Unlock();

			// ɾ��·��ʱ����ڵ�·�ɶ��������ӵ�����
			bDelete = DeleteRoutLinkInstrumentWhenRoutTimeExpired(pRout);
			// �жϣ�������ɾ����������ɾ��·��
			if(true == bDelete)
			{
				// ���û���ɾ���̱߳�־Ϊ��
				bResumeProcDelete = true;
			}
		}
	}
	// �жϣ�������ɾ����������ɾ��·��
	if(true == bResumeProcDelete)
	{
		// �жϣ�ɾ���߳̿���
		if(true == m_pThreadProcDelete->Lock())
		{
			// ɾ����������·�ɼ���ɾ���̶߳���
			AddDeleteInstrumentAndRoutToProcDelete();
			// ����ɾ���߳�
			m_pThreadProcDelete->ResumeProcDelete();
		}
		else	// ɾ���߳�æ
		{
			// ��յȴ�ɾ������������
			m_olsInstrument.RemoveAll();
			// ��յȴ�ɾ����·�ɶ���
			m_olsRout.RemoveAll();
		}
	}
}

/**
* ɾ��·��IP��ַ����ֹ��·�ɶ��������ӵ�����
* @param CRout* pRout ·�ɶ���ָ��
* @return bool true��ɾ���ɹ���false��û��Ҫɾ��������
*/
bool CThreadProcMonitorRout::DeleteLinkInstrumentRoutWhenRoutIPDisable(CRout* pRout)
{
	// �Ƿ���ɾ��·�����ӵ���������
	bool bDelete = false;

	// �ж�·�ɷ����Ƿ�����������
	if(NULL == pRout->m_pTail)	// ·�ɷ���û����������
	{
		return bDelete;
	}

	// �ж�·�ɷ���
	switch(pRout->m_uiRoutDirection)
	{
	case 1:	// ��
		{
			if(0 == pRout->m_pHead->m_uiRoutIPTop)
			{
				// ɾ��·�����ӵ�����
				bDelete = DeleteRoutLinkInstrument(pRout);
			}
			break;
		}
	case 2:	// ��
		{
			if(0 == pRout->m_pHead->m_uiRoutIPDown)
			{
				// ɾ��·�����ӵ�����
				bDelete = DeleteRoutLinkInstrument(pRout);
			}
			break;
		}
	case 3:	// ��
		{
			if(0 == pRout->m_pHead->m_uiRoutIPLeft)
			{
				// ɾ��·�����ӵ�����
				bDelete = DeleteRoutLinkInstrument(pRout);
			}
			break;
		}
	case 4:	// ��
		{
			if(0 == pRout->m_pHead->m_uiRoutIPRight)
			{
				// ɾ��·�����ӵ�����
				bDelete = DeleteRoutLinkInstrument(pRout);
			}
			break;
		}
	}

	return bDelete;
}

/**
* ɾ��·��IP��ַ����ֹ��·��
* @param CRout* pRout ·��ָ��
* @return bool true��ɾ���ɹ���false��û��Ҫɾ����·��
*/
bool CThreadProcMonitorRout::DeleteRoutWhenRoutIPDisable(CRout* pRout)
{
	// �Ƿ���ɾ��·�ɶ������
	bool bDelete = false;

	// �ж�·�ɷ���
	switch(pRout->m_uiRoutDirection)
	{
	case 1:	// ��
		{
			if(0 == pRout->m_pHead->m_uiRoutIPTop)
			{
				// ����һ����Ҫ����ɾ����·��
				m_olsRout.AddTail(pRout);
				bDelete = true;
			}
			break;
		}
	case 2:	// ��
		{
			if(0 == pRout->m_pHead->m_uiRoutIPDown)
			{
				// ����һ����Ҫ����ɾ����·��
				m_olsRout.AddTail(pRout);
				bDelete = true;
			}
			break;
		}
	case 3:	// ��
		{
			if(0 == pRout->m_pHead->m_uiRoutIPLeft)
			{
				// ����һ����Ҫ����ɾ����·��
				m_olsRout.AddTail(pRout);
				bDelete = true;
			}
			break;
		}
	case 4:	// ��
		{
			if(0 == pRout->m_pHead->m_uiRoutIPRight)
			{
				// ����һ����Ҫ����ɾ����·��
				m_olsRout.AddTail(pRout);
				bDelete = true;
			}
			break;
		}
	}
	return bDelete;
}

/**
* ɾ��·��ʱ����ڵ�·�ɶ��������ӵ�����
* @param CRout* pRout ·��ָ��
* @return bool true��ɾ���ɹ���false��û��Ҫɾ��������
*/
bool CThreadProcMonitorRout::DeleteRoutLinkInstrumentWhenRoutTimeExpired(CRout* pRout)
{
	// �Ƿ���ɾ��·�����ӵ���������
	bool bDelete = false;

	// �ж�·�ɷ����Ƿ�����������
	if(NULL == pRout->m_pTail)	// ·�ɷ���û����������
	{
		return bDelete;
	}

	// �õ���ǰϵͳʱ��
	unsigned int uiTimeNow = GetTickCount();
	// �ж�·�ɶ����·��ʱ���Ƿ����
	if(7000 < (uiTimeNow - pRout->m_uiRoutTime))	// ����
	//if(3000 < (uiTimeNow - pRout->m_uiRoutTime))	// ����
	{
		m_pSiteData->m_oCriticalSectionSiteDataChanged.Lock();
		m_pSiteData->HeadminTime=0xffffffff;
		m_pSiteData->HeadCount=0;
		m_pSiteData->m_oCriticalSectionSiteDataChanged.Unlock();
		// ɾ��·�����ӵ�����
		bDelete = DeleteRoutLinkInstrument(pRout);
	}
	return bDelete;
}

/**
* ɾ��·�����ӵ�����
* @param CRout* pRout ·��ָ��
* @return bool true��ɾ���ɹ���false��û��Ҫɾ��������
*/
bool CThreadProcMonitorRout::DeleteRoutLinkInstrument(CRout* pRout)
{
	bool bDelete = false;

	// �ж�·�ɷ����Ƿ���������
	if(NULL == pRout->m_pTail)	// ·�ɷ���û����������
	{
		return bDelete;
	}

	// �ж�·�ɷ���
	switch(pRout->m_uiRoutDirection)
	{
	case 1:	// ��
		{
			// ɾ������
			pRout->m_pHead->m_pCrossTop->m_uiDeleteDirection = 2;
			// ����һ����Ҫ����ɾ��������
			m_olsInstrument.AddTail(pRout->m_pHead->m_pCrossTop);			
			bDelete = true;
			break;
		}
	case 2:	// ��
		{
			// ɾ������
			pRout->m_pHead->m_pCrossDown->m_uiDeleteDirection = 1;
			// ����һ����Ҫ����ɾ��������
			m_olsInstrument.AddTail(pRout->m_pHead->m_pCrossDown);
			bDelete = true;
			break;
		}
	case 3:	// ��
		{
			// ɾ������
			pRout->m_pHead->m_pInstrumentLeft->m_uiDeleteDirection = 4;
			// ����һ����Ҫ����ɾ��������
			m_olsInstrument.AddTail(pRout->m_pHead->m_pInstrumentLeft);
			bDelete = true;
			break;
		}
	case 4:	// ��
		{
			// ɾ������
			pRout->m_pHead->m_pInstrumentRight->m_uiDeleteDirection = 3;
			// ����һ����Ҫ����ɾ��������
			m_olsInstrument.AddTail(pRout->m_pHead->m_pInstrumentRight);
			bDelete = true;
			break;
		}
	}
	return bDelete;
}

/**
* ɾ����������·�ɼ���ɾ���̶߳���
* @param void
* @return void
*/
void CThreadProcMonitorRout::AddDeleteInstrumentAndRoutToProcDelete()
{
	// �ȴ�ɾ��������ָ��
	CInstrument* pInstrument = NULL;
	// �ȴ�ɾ�����������в�Ϊ��
	while(FALSE == m_olsInstrument.IsEmpty())
	{
		// �õ�����
		pInstrument = m_olsInstrument.RemoveHead();
		// ����һ����Ҫ����ɾ��������
		m_pThreadProcDelete->AddInstrumentForDelete(pInstrument);
	}

	// �ȴ�ɾ����·��ָ��
	CRout* pRout = NULL;
	// �ȴ�ɾ����·�ɶ��в�Ϊ��
	while(FALSE == m_olsRout.IsEmpty())
	{
		// �õ�·�ɶ���
		pRout = m_olsRout.RemoveHead();
		// ����һ����Ҫ����ɾ����·��
		m_pThreadProcDelete->AddRoutForDelete(pRout);	
	}
}