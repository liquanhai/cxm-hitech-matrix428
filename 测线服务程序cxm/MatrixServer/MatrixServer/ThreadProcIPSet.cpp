// ThreadProcIPSet.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MatrixServer.h"
#include "ThreadProcIPSet.h"
#include "..\\parameter\\Parameter.h"
#include <hash_map>
using stdext::hash_map;
// CThreadProcIPSet

IMPLEMENT_DYNCREATE(CThreadProcIPSet, CWinThread)

CThreadProcIPSet::CThreadProcIPSet()
{
	// �Ƿ���״̬
	m_bWork = false;
	// �Ƿ�ر��߳�
	m_bClose = false;
}

CThreadProcIPSet::~CThreadProcIPSet()
{
}

BOOL CThreadProcIPSet::InitInstance()
{
	// TODO: �ڴ�ִ���������̳߳�ʼ��
	return TRUE;
}

int CThreadProcIPSet::ExitInstance()
{
	// TODO: �ڴ�ִ���������߳�����
	return CWinThread::ExitInstance();
}

BEGIN_MESSAGE_MAP(CThreadProcIPSet, CWinThread)
END_MESSAGE_MAP()

// CThreadProcIPSet ��Ϣ�������

/**
* �߳�������
* @param void
* @return int
*/
int CThreadProcIPSet::Run()
{
	// ѭ����ֱ���رձ�־Ϊ��	
	while(true)
	{
		// �жϹرձ�־�Ƿ�Ϊ��
		if(true == m_bClose)
		{
			break;
		}
		//��������IP��ַ����
		ProcIPSet();
		// �жϹرձ�־�Ƿ�Ϊ��
		if(true == m_bClose)
		{
			break;
		}
		// ����100ms
		Wait(IPSetFrameSleepTimes);
	}
	// ����IP��ַ�����̹߳رձ�־Ϊ��
	m_pSiteData->m_bProcIPSetClose = true;
	// ����
	return CWinThread::Run();
}

/**
* ��ʼ���߳�
* @param void
* @return bool true���ɹ���false��ʧ��
*/
bool CThreadProcIPSet::OnInit()
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
bool CThreadProcIPSet::OnClose()
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
bool CThreadProcIPSet::OnWork()
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
bool CThreadProcIPSet::OnStop()
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
void CThreadProcIPSet::Wait(int iWaitStopCount)
{
	// �ȴ�����
	int iWaitCount = 0;
	while(true)
	{	
		Sleep(OneSleepTime);	// ����
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
bool CThreadProcIPSet::JudgeProcCondition()
{	
// 	// ɾ��������·�ɴ����߳���������
// 	if(true == m_pSiteData->m_bProcDeleteRunning)
// 	{
// 		m_pSiteData->m_bProcIPSetPause = true;	// ����IP��ַ�����߳���ͣ
// 		return false;
// 	}
// 	else
// 	{
// 		m_pSiteData->m_bProcIPSetPause = false;	// ����IP��ַ�����߳���ͣ
// 	}
	if(false == m_bWork)	// �ǹ���״̬
	{		
		m_pSiteData->m_bProcIPSetStop = true;	// ����IP��ַ�����߳�ֹͣ
		return false;
	}
	else	// ����״̬
	{
		m_pSiteData->m_bProcIPSetStop = false;	// ����IP��ַ�����̹߳���
	}
	return true;
}

// /**
// * ����һ����Ҫ����IP��ַ������������������������
// * @param CInstrument* pInstrument ����ָ��
// * @return void
// */
// void CThreadProcIPSet::AddInstrumentForIPSet(CInstrument* pInstrument)
// {
// 	// �������
// 	if(TRUE == m_oSNInstrumentMap.Lookup(pInstrument->m_uiSN,pInstrument)&& pInstrument->m_uiInstrumentType!=1)
// 		pInstrument->m_uiSN=pInstrument->m_uiSN;
// 	// �ڼ�������IP��ַ
// 	pInstrument->m_iIPSetCount = 0;
// 	// IP��ַ�����Ƿ�ɹ�
// 	pInstrument->m_bIPSetOK = false;
// 	m_olsInstrument.AddTail(pInstrument);
// 	//TRACE2("AddTail SN��=%d IP=%d \r\n", pInstrument->m_uiSN,pInstrument->m_uiIP);
// }

/**
* ��������IP��ַ����
* @param void
* @return void
*/
void CThreadProcIPSet::ProcIPSet()
{
	// �ж��Ƿ���Դ��������
	if(false == JudgeProcCondition())
	{
		return;
	}
	// �õ�����IP����Ӧ��֡
	GetIPSetReturnFrame();
	// ��������IP����֡
	SendIPSetFrame();
// 	// �̵߳ȴ�
// 	Wait(4);
}

/**
* ��������IP����֡
* @param void
* @return void
*/
void CThreadProcIPSet::SendIPSetFrame()
{
	// hash_map������
	hash_map<unsigned int, CInstrument*>::iterator  iter;
	// IP��ַ����������Ϊ��
	if (false == m_pSiteData->m_oInstrumentList.m_oIPSetMap.empty())
	{
		// �������������豸��IP��ַ����֡
		for(iter = m_pSiteData->m_oInstrumentList.m_oIPSetMap.begin(); iter != m_pSiteData->m_oInstrumentList.m_oIPSetMap.end();)
		{
			// IP��ַ���ô���Ϊ0
			if (iter->second->m_iIPSetCount == 0)
			{
				// ��������IP��ַ����֡����
				m_pSocketIPSetFrame->MakeFrameData(iter->second, SendSetCmd);
				// ��������IP��ַ����֡
				m_pSocketIPSetFrame->SendIPSetFrame();
				// �ڼ�������IP��ַ
				iter->second->m_iIPSetCount++;
				iter++;
			}
			// IP��ַ���ô���������ָ����������������IP��ַ�Ͳ�ѯIP��ַ
			else if (iter->second->m_iIPSetCount <= IPAddrResetTimes)
			{
				// ��������IP��ַ��ѯ֡����
				m_pSocketIPSetFrame->MakeFrameData(iter->second, SendQueryCmd);
				// ��������IP��ַ����֡
				m_pSocketIPSetFrame->SendIPSetFrame();
				// ��������IP��ַ����֡����
				m_pSocketIPSetFrame->MakeFrameData(iter->second, SendSetCmd);
				// ��������IP��ַ����֡
				m_pSocketIPSetFrame->SendIPSetFrame();
				// �ڼ�������IP��ַ
				iter->second->m_iIPSetCount++;
				iter++;
			}
			// IP��ַ���ô�������ָ�����������������ɾ��������ָ��
			else
			{
				iter->second->m_iIPSetCount = 0;
				m_pSiteData->m_oInstrumentList.m_oIPSetMap.erase(iter++);
			}
		}
		// �����ϴ��ֳ����ݱ仯ʱ��
		m_pSiteData->UpdateSiteDataChangedTime();
	}
}

/**
* �õ�����IP����Ӧ��֡
* @param void
* @return void
*/
void CThreadProcIPSet::GetIPSetReturnFrame()
{
	if(false == m_bWork)	// �Ƿ���״̬
	{
		return;
	}

	CInstrument* pInstrument;	// ����ָ��
	unsigned int uiIPInstrument;// ����IP��ַ
	int iFrameCount = 0;

	while(true)	// ���ս��ջ�����
	{
		// �õ�����IP����Ӧ��֡��
		iFrameCount = m_pSocketIPSetFrame->GetFrameCount();
		if(0 == iFrameCount)	//������IP����Ӧ��֡
		{
			break;
		}
		for(int i = 0; i < iFrameCount; i++)	// ���μ��ÿ������IP����Ӧ��֡
		{
			// �õ�����IP����Ӧ��֡
			m_pSocketIPSetFrame->GetFrameData();
			// �õ�����IP
			uiIPInstrument = m_pSocketIPSetFrame->m_oFrameIPSet.m_uiIPInstrument;
			// ��������������
			if (TRUE == m_pSiteData->m_oInstrumentList.IfIndexExistInIPSetMap(uiIPInstrument))
			{
				m_pSiteData->m_oInstrumentList.GetInstrumentFromIPSetMap(uiIPInstrument, pInstrument);
				// ��IP��ַ������������ɾ������
				m_pSiteData->m_oInstrumentList.DeleteInstrumentFromIPSetMap(uiIPInstrument);
				// ����������IP��ַ������
				pInstrument->m_bIPSetOK = true;
				m_pSiteData->m_oInstrumentList.AddInstrumentToIPSetMap(uiIPInstrument, pInstrument);
				//�����ֳ����ݱ仯
 				m_pSiteData->UpdateSiteDataChangedTime();
			}
		}
	}
}
