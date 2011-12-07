// ThreadProcDelete.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "TestSiteManage.h"
#include "ThreadProcDelete.h"


// CThreadProcDelete

IMPLEMENT_DYNCREATE(CThreadProcDelete, CWinThread)

CThreadProcDelete::CThreadProcDelete()
{
	// �Ƿ���״̬
	m_bWork = false;
	// �Ƿ�ر��߳�
	m_bClose = false;
	// �Ƿ����״̬
	m_bFree = true;
}

CThreadProcDelete::~CThreadProcDelete()
{
}

BOOL CThreadProcDelete::InitInstance()
{
	// TODO: �ڴ�ִ���������̳߳�ʼ��
	return TRUE;
}

int CThreadProcDelete::ExitInstance()
{
	// TODO: �ڴ�ִ���������߳�����
	return CWinThread::ExitInstance();
}

BEGIN_MESSAGE_MAP(CThreadProcDelete, CWinThread)
END_MESSAGE_MAP()

// CThreadProcDelete ��Ϣ�������

/**
* �߳�������
* @param void
* @return int
*/
int CThreadProcDelete::Run()
{
	// ѭ����ֱ���رձ�־Ϊ��
	while(true)
	{
		// �жϹرձ�־�Ƿ�Ϊ��
		if(true == m_bClose)
		{
			// ����ѭ��
			break;
		}
		// ����ɾ������
		ProcDelete();
		// �жϹرձ�־�Ƿ�Ϊ��
		if(true == m_bClose)
		{
			// ����ѭ��
			break;
		}
		// ����ɾ���߳̿���
		m_bFree = true;
		// �����߳�
		this->SuspendThread();
		// ����ɾ���߳�æ
		m_bFree = false;
	}
	// ɾ��������·�ɴ����̱߳�־Ϊ��
	m_pSiteData->m_bProcDeleteClose = true;
	// ����
	return CWinThread::Run();
}

/**
* ��ʼ���߳�
* @param void
* @return bool true���ɹ���false��ʧ��
*/
bool CThreadProcDelete::OnInit()
{
	// �Ƿ���״̬
	m_bWork = false;
	// �Ƿ�ر��߳�
	m_bClose = false;
	// �Ƿ����״̬
	m_bFree = true;
	return true;
}

/**
* �ر��߳�
* @param void
* @return bool true���ɹ���false��ʧ��
*/
bool CThreadProcDelete::OnClose()
{
	// �Ƿ�ر��߳�
	m_bClose = true;
	// �Ƿ����״̬
	if(true == m_bFree)
	{
		// ����ʱ�Ӵ���
		ResumeProcDelete();
	}
	return true;
}

/**
* �߳̿�ʼ����
* @param void
* @return bool true���ɹ���false��ʧ��
*/
bool CThreadProcDelete::OnWork()
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
bool CThreadProcDelete::OnStop()
{
	// �Ƿ���״̬
	m_bWork = false;
	return true;
}

/**
* �ж��߳��Ƿ���Խ��д�����������
* @param void
* @return bool true���ɹ���false��ʧ��
*/
bool CThreadProcDelete::JudgeProcCondition()
{	
	// �ǹ���״̬
	if(false == m_bWork)
	{		
		m_pSiteData->m_bProcDeleteStop = true;	// ɾ��������·�ɴ����߳�ֹͣ
		return false;
	}
	else
	{
		m_pSiteData->m_bProcDeleteStop = false;	// ɾ��������·�ɴ����̹߳���
	}
	return true;
}

/**
* �ж��߳��Ƿ����
* @param void
* @return bool true���ǣ�false����
*/
bool CThreadProcDelete::IsThreadFree()
{
	return m_bFree;
}

/**
* �����߳�
* @param void
* @return void
*/
void CThreadProcDelete::ResumeProcDelete()
{
	DWORD dwData;	
	while(true)
	{
		dwData = ResumeThread();	// �����߳�
		if(1 == dwData)
		{
			break;
		}
		Sleep(50);
	}	
}

/**
* �����̣߳������������߳�ʹ��
* @param void
* @return bool true���ɹ���false��ʧ��
*/
bool CThreadProcDelete::Lock()
{
	bool bLock = false;	
	m_pSiteData->m_oCriticalSectionProcDelete.Lock();	// Ϊɾ��������·�ɴ����߳�׼�����߳�ͬ����������
		if(true == m_bFree)	// ɾ���߳̿���	
		{		
			m_bFree = false;	// ����ɾ���߳�æ
			bLock = true;
		}		
	m_pSiteData->m_oCriticalSectionProcDelete.Unlock();	// Ϊɾ��������·�ɴ����߳�׼�����߳�ͬ���������
	return bLock;
}

/**
* �����̣߳����������߳�ʹ��
* @param void
* @return bool true���ɹ���false��ʧ��
*/
void CThreadProcDelete::Unlock()
{
	m_pSiteData->m_oCriticalSectionProcDelete.Lock();	// Ϊɾ��������·�ɴ����߳�׼�����߳�ͬ����������		
		m_bFree = true;	// ����ɾ���߳̿���
	m_pSiteData->m_oCriticalSectionProcDelete.Unlock();	// Ϊɾ��������·�ɴ����߳�׼�����߳�ͬ���������
}

/**
* ����һ����Ҫɾ��������������ȴ�ɾ������������
* @param CInstrument* pInstrument ��Ҫɾ��������ָ��
* @return void
*/
void CThreadProcDelete::AddInstrumentForDelete(CInstrument* pInstrument)
{
	// �ȴ�ɾ������������
	m_olsInstrument.AddTail(pInstrument);
}

/**
* ����һ����Ҫɾ����·�ɣ�����ȴ�ɾ����·�ɶ���
* @param CRout* pRout ��Ҫɾ����·��ָ��
* @return void
*/
void CThreadProcDelete::AddRoutForDelete(CRout* pRout)
{
	// �ȴ�ɾ����·�ɶ���
	m_olsRout.AddTail(pRout);
}

/**
* ����ɾ������
* @param void
* @return void
*/
void CThreadProcDelete::ProcDelete()
{
	// �ж��Ƿ���Դ��������
	if(false == JudgeProcCondition())
	{
		// ����
		return;
	}
	// ɾ��������·�ɴ����߳��������б�־Ϊ��
	m_pSiteData->m_bProcDeleteRunning = true;
		// �жϵȴ������߳���ͣ�Ƿ�ɹ�
		if(true == WaitOtherThreadProcPause())
		{
			// ����ɾ����������
			ProcDeleteInstrument();
			// ����ɾ��·�ɲ���
			ProcDeleteRout();
		}
		// �ȴ���ʱ
		else
		{
			// ��յȴ�ɾ������������
			m_olsInstrument.RemoveAll();
			// ��յȴ�ɾ����·�ɶ���
			m_olsRout.RemoveAll();
		}
	// ɾ��������·�ɴ����߳�ֹͣ���б�־Ϊ��
	m_pSiteData->m_bProcDeleteRunning = false;
	// �����ϴ��ֳ����ݱ仯ʱ��
	m_pSiteData->UpdateSiteDataChangedTime();

	// ��������״̬������־����
	m_pSiteData->m_oRunTimeDataList.Set(1, "CThreadProcDelete", "ProcDelete", "Delete Operation");
}

/**
* �ȴ������߳���ͣ
* @note ɾ���̹߳���ʱ����Ҫ��ͣ���̣߳��װ������̡߳�β�������̡߳�·�ɼ����̡߳�����IP��ַ�����̡߳�����IP��ַ�����̡߳��ֳ���������̡߳�ʱ�Ӵ����߳�
* @param void
* @return bool true���ɹ���false��ʧ��
*/
bool CThreadProcDelete::WaitOtherThreadProcPause()
{
	// �ȴ�����
	int iWaitCount = 0;
	while(true)
	{	
		if((true == m_pSiteData->m_bProcHeadFramePause)	// �װ������߳���ͣ
			&& (true == m_pSiteData->m_bProcTailFramePause)	// β�������߳���ͣ
			&& (true == m_pSiteData->m_bProcMonitorRoutPause)	// ·�ɼ����߳���ͣ
			&& (true == m_pSiteData->m_bProcIPDistributePause)	// ����IP��ַ�����߳���ͣ
			&& (true == m_pSiteData->m_bProcIPSetPause)	// ����IP��ַ�����߳���ͣ
			&& (true == m_pSiteData->m_bProcSiteDataOutputPause))	// �ֳ���������߳���ͣ
		{
			//ȡ�� ʱ�Ӵ����̶߳������ 2011.11.24 by zl
			//break;
			// ʱ�Ӵ����̶߳������
			if(true == m_pThreadProcTimeDelay->IsThreadFree())
			{
				break;
			}			
		}
		// �ȴ�����
		iWaitCount++;
		// ����
		Sleep(50);
		// �ȴ�����
		if(40 == iWaitCount)
		{
			return false;
		}
	}
	return true;
}

/**
* ����ɾ����������
* @param void
* @return void
*/
void CThreadProcDelete::ProcDeleteInstrument()
{
	// �ȴ�ɾ��������ָ��
	CInstrument* pInstrument = NULL;
	// �ȴ�ɾ�����������в�Ϊ��
	while(FALSE == m_olsInstrument.IsEmpty())
	{
		// �õ�����
		pInstrument = m_olsInstrument.RemoveHead();
		if(NULL != pInstrument)
		{
		CString strDesc;
		strDesc.Format("DeleteInstrumentLink Sn=%x", pInstrument->m_uiSN);
		m_pSiteData->m_oRunTimeDataList.Set(3, "CThreadProcDelete", "ProcDeleteInstrument ", strDesc);
		//���⴦���Դվ 2011.11.24 by zl
		//if(pInstrument->m_uiInstrumentType==2)
		//	return;
		TRACE1("ɾ������Sn=%x \r\n",pInstrument->m_uiSN); 
			// ɾ��������
			m_pSiteData->DeleteInstrumentLink(pInstrument, pInstrument->m_uiDeleteDirection);
			// ������ɾ��ʱ��ɾ������ 1-�ϣ�2-�£�3-��4��
			pInstrument->m_uiDeleteDirection = 0;
			pInstrument = NULL;
		}
	}
}

/**
* ����ɾ��·�ɲ���
* @param void
* @return void
*/
void CThreadProcDelete::ProcDeleteRout()
{
	// �ȴ�ɾ����·��ָ��
	CRout* pRout = NULL;
	// �ȴ�ɾ����·�ɶ��в�Ϊ��
	while(FALSE == m_olsRout.IsEmpty())
	{
		// �õ�·�ɶ���
		pRout = m_olsRout.RemoveHead();
		// ·�ɶ���Ϊ��
		if(NULL != pRout)
		{
			// ɾ��·��
			m_pSiteData->DeleteRout(pRout);
			pRout = NULL;
		}
	}
}