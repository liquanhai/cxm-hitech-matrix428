// ThreadProcIPSet.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "TestSiteManage.h"
#include "ThreadProcIPSet.h"


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
		// ����50����
		Wait(1);
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
	// �ȴ�����IP��ַ����������
	m_olsInstrument.RemoveAll();
	// �ȴ�����IP��ַ������������
	m_oSNInstrumentMap.RemoveAll();
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
bool CThreadProcIPSet::JudgeProcCondition()
{	
	// ɾ��������·�ɴ����߳���������
	if(true == m_pSiteData->m_bProcDeleteRunning)
	{
		m_pSiteData->m_bProcIPSetPause = true;	// ����IP��ַ�����߳���ͣ
		return false;
	}
	else
	{
		m_pSiteData->m_bProcIPSetPause = false;	// ����IP��ַ�����߳���ͣ
	}
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

/**
* ����һ����Ҫ����IP��ַ������������������������
* @param CInstrument* pInstrument ����ָ��
* @return void
*/
void CThreadProcIPSet::AddInstrumentForIPSet(CInstrument* pInstrument)
{
	if(pInstrument->m_uiInstrumentType!=1)
		pInstrument->m_bIPSetOK=pInstrument->m_bIPSetOK;
	if(pInstrument->m_bIPSetOK==true && pInstrument->m_uiInstrumentType!=1)
		pInstrument->m_bIPSetOK=pInstrument->m_bIPSetOK;
	// �������
	if(TRUE == m_oSNInstrumentMap.Lookup(pInstrument->m_uiSN,pInstrument)&& pInstrument->m_uiInstrumentType!=1)
		pInstrument->m_uiSN=pInstrument->m_uiSN;
	// �ڼ�������IP��ַ
	pInstrument->m_iIPSetCount = 0;
	// IP��ַ�����Ƿ�ɹ�
	pInstrument->m_bIPSetOK = false;
	m_olsInstrument.AddTail(pInstrument);
	TRACE2("AddTail SN��=%d IP=%d \r\n", pInstrument->m_uiSN,pInstrument->m_uiIP);
}

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
	// ��������IP����֡
	SendIPSetFrame();
	// �̵߳ȴ�
	Wait(4);
	// �õ�����IP����Ӧ��֡
	GetIPSetReturnFrame();
}

/**
* ��������IP����֡
* @param void
* @return void
*/
void CThreadProcIPSet::SendIPSetFrame()
{
	CInstrument* pInstrument;	// ����ָ��
	unsigned int uiSN;	// ������
	POSITION pos;	// λ��

	if(false == m_olsInstrument.IsEmpty())	// ��Ϊ��
	{
		// ��������״̬����
		m_pSiteData->m_oRunTimeDataList.Set(1, "CThreadProcIPSet", "SendIPSetFrame", "Set Instrument IP");
		// �����ϴ��ֳ����ݱ仯ʱ��
		m_pSiteData->UpdateSiteDataChangedTime();	
	}

	// ѭ�����õ�������������
	while(false == m_olsInstrument.IsEmpty())
	{
		// �Ӷ�������������
		pInstrument = m_olsInstrument.RemoveHead();
		// ��������������
		m_oSNInstrumentMap.SetAt(pInstrument->m_uiSN, pInstrument);
	}
	// Ϊ�������е�ÿ����������IP����֡
	pos = m_oSNInstrumentMap.GetStartPosition();
	// ѭ��
	while(NULL != pos)
	{
		// ���εõ�ÿ����Ҫ����IP��ַ������
		m_oSNInstrumentMap.GetNextAssoc(pos, uiSN, pInstrument);
		if(false == pInstrument->m_bInUsed)	//���δ���ӵ�����
		{
			m_oSNInstrumentMap.RemoveKey(uiSN);
		}
		if(pInstrument->m_bIPSetOK ==true){		//���յ�IPӦ�𻹻ᷢ��IP���� add by zl 04.20
			pInstrument->m_iIPSetCount=0;
			m_oSNInstrumentMap.RemoveKey(uiSN);
			CString strDesc;
			strDesc.Format("m_bIPSetOK Sn=%d IP=%d", pInstrument->m_uiSN, pInstrument->m_uiIP);
			m_pSiteData->m_oRunTimeDataList.Set(1,"CThreadProcIPSet", "SendIPSetFrame3", strDesc);
			TRACE2("�ظ�IP����-����SN��=%x IP=%d \r\n", pInstrument->m_uiSN,pInstrument->m_uiIP);
			continue;
		}
		else if(3 == pInstrument->m_iIPSetCount && pInstrument->m_bIPSetOK ==false)	//���������3�Σ����޷�����IP��ַ������
		{
			CString strDesc;
			strDesc.Format("Instrument IP Set Fail. SN=%d��IP=%d", pInstrument->m_uiSN, pInstrument->m_uiIP);
			// ��������״̬����
			m_pSiteData->m_oRunTimeDataList.Set(2, "CThreadProcIPSet", "SendIPSetFrame1", strDesc);
			m_oSNInstrumentMap.RemoveKey(uiSN);
			TRACE2("IP���� Instrument IP Set Fail. SN=%d��IP=%d\r\n", pInstrument->m_uiSN, pInstrument->m_uiIP);
		}
		else
		{
			CString strDesc;
			strDesc.Format("Sn=%d IP=%d", pInstrument->m_uiSN, pInstrument->m_uiIP);
			m_pSiteData->m_oRunTimeDataList.Set(1,"CThreadProcIPSet", "SendIPSetFrame2", strDesc);
			TRACE2("IP����-����SN��=%d IP=%d \r\n", pInstrument->m_uiSN,pInstrument->m_uiIP);
			if(pInstrument->m_uiSN==0){
				TRACE2("IP����-����SN��=%x IP=%d \r\n", pInstrument->m_uiSN,pInstrument->m_uiIP);
				continue;
			}
			if(pInstrument->m_bIPSetOK ==true)
				break;
			// ��������IP��ַ����֡����
			m_pSocketIPSetFrame->MakeFrameData(pInstrument);
			// ��������IP��ַ����֡
			m_pSocketIPSetFrame->SendIPSetFrame();
			// �ڼ�������IP��ַ
			pInstrument->m_iIPSetCount++;
			Sleep(1);
		}
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
	unsigned int uiSN;	// ������
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
			// �õ�����SN
			uiSN = m_pSocketIPSetFrame->m_oFrameIPSet.m_uiSN;
			// ��������������
			if(TRUE == m_oSNInstrumentMap.Lookup(uiSN, pInstrument))
			{
				// ����������ɾ������
				m_oSNInstrumentMap.RemoveKey(uiSN);
				// ����IP��ַ���óɹ�
				pInstrument->m_bIPSetOK = true;
				CString strDesc;
				if( pInstrument!=NULL){
					strDesc.Format("GetIPSetReturnFrame. SN=%x IP=%d", pInstrument->m_uiSN,pInstrument->m_uiIP);
					TRACE2("IPӦ��-����SN��=%x IP=%d \r\n", pInstrument->m_uiSN,pInstrument->m_uiIP);
					//strDesc.Format("GetIPSetReturnFrame. SN=%x ", uiSN);
					// ��������״̬����
					m_pSiteData->m_oRunTimeDataList.Set(1, "CThreadProcIPSet", "GetIPSetReturnFrame", strDesc);
				}else{
					strDesc.Format("GetIPSetReturnFrame. Fail");
					// ��������״̬����
					m_pSiteData->m_oRunTimeDataList.Set(2, "CThreadProcIPSet", "GetIPSetReturnFrame", strDesc);
				}
			}
		}
	}
}
