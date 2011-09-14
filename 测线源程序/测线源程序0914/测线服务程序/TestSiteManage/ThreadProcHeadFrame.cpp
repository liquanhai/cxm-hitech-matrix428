// ThreadProcHeadFrame.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "TestSiteManage.h"
#include "ThreadProcHeadFrame.h"


// CThreadProcHeadFrame

IMPLEMENT_DYNCREATE(CThreadProcHeadFrame, CWinThread)

CThreadProcHeadFrame::CThreadProcHeadFrame()
{
	// �Ƿ���״̬
	m_bWork = false;
	// �Ƿ�ر��߳�
	m_bClose = false;
}

CThreadProcHeadFrame::~CThreadProcHeadFrame()
{
}

BOOL CThreadProcHeadFrame::InitInstance()
{
	// TODO: �ڴ�ִ���������̳߳�ʼ��
	return TRUE;
}

int CThreadProcHeadFrame::ExitInstance()
{
	// TODO: �ڴ�ִ���������߳�����
	return CWinThread::ExitInstance();
}

BEGIN_MESSAGE_MAP(CThreadProcHeadFrame, CWinThread)
END_MESSAGE_MAP()

// CThreadProcHeadFrame ��Ϣ�������

/**
* �߳�������
* @param void
* @return int
*/
int CThreadProcHeadFrame::Run()
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
		// �����װ�֡
		ProcHeadFrame();
		// �жϹرձ�־�Ƿ�Ϊ��
		if(true == m_bClose)
		{
			// ����ѭ��
			break;
		}
		// ����50����
		Wait(1);
	}
	// �װ������̹߳رձ�־Ϊ��
	m_pSiteData->m_bProcHeadFrameClose = true;
	// ����
	return CWinThread::Run();
}

/**
* ��ʼ���߳�
* @param void
* @return bool true���ɹ���false��ʧ��
*/
bool CThreadProcHeadFrame::OnInit()
{
	// �Ƿ���״̬
	m_bWork = false;
	// �Ƿ�ر��߳�
	m_bClose = false;
	// �Ƿ�������������
	m_bInstrumentAdd = false;
	return true;
}

/**
* �ر��߳�
* @param void
* @return bool true���ɹ���false��ʧ��
*/
bool CThreadProcHeadFrame::OnClose()
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
bool CThreadProcHeadFrame::OnWork()
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
bool CThreadProcHeadFrame::OnStop()
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
void CThreadProcHeadFrame::Wait(int iWaitStopCount)
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
bool CThreadProcHeadFrame::JudgeProcCondition()
{	
	// ɾ��������·�ɴ����߳��������У����ֳ���������߳���������
	if((true == m_pSiteData->m_bProcDeleteRunning) || (true == m_pSiteData->m_bProcSiteDataOutputRunning))
	{		
		m_pSiteData->m_bProcHeadFramePause = true;	// �װ������߳���ͣ
		return false;
	}
	else
	{		
		m_pSiteData->m_bProcHeadFramePause = false;	// �װ������̹߳���
	}
	// �ǹ���״̬
	if(false == m_bWork)
	{		
		m_pSiteData->m_bProcHeadFrameStop = true;	// �װ������߳�ֹͣ
		return false;
	}
	else
	{
		m_pSiteData->m_bProcHeadFrameStop = false;	// �װ������̹߳���
	}
	return true;
}

/**
* �����װ�֡
* @note ������˿ڵõ�Ұ�������������װ�֡����֡����
* @note �Ǵ���״̬ʱ����ȡ�װ�֡��Ȼ����������
* @note �Ǵ���״̬�����ڣ��ֳ�����ֹͣʱ��ɾ��������·�ɴ����߳���������ʱ���ֳ���������߳���������ʱ��
* @param void
* @return void
*/
void CThreadProcHeadFrame::ProcHeadFrame()
{
	// �Ƿ���������������־����Ϊ��
	m_bInstrumentAdd = false;
	// ֡��������Ϊ0
	int iFrameCount = 0;
	// �õ��װ���������˿�֡����
	iFrameCount = m_pSocketHeadFrame->GetFrameCount();
	// �ж�֡�����Ƿ����0
	if(iFrameCount > 0)
	{
		// ѭ������ÿ1֡
		for(int i = 0; i < iFrameCount; i++)
		{
			if(iFrameCount>3)
				int k=0;
			// �õ�֡����
			m_pSocketHeadFrame->GetFrameData();
			// �ж��Ƿ���Դ��������
			if(true ==JudgeProcCondition())
			{
				// �������װ�֡
				ProcHeadFrameOne(&m_pSocketHeadFrame->m_oFrameHead);			
			}
		}		
	}
	// �ж�����������־�Ƿ�Ϊ��
	if(true == m_bInstrumentAdd)
	{
		// �����ϴ��ֳ����ݱ仯ʱ��
		m_pSiteData->UpdateSiteDataChangedTime();
	}
}

/**
* �ط�ʱ�俿����װ�
* @note �������̣���
* @param CFrameHead* pFrameHead �װ�ָ֡��
* @return void
*/
void CThreadProcHeadFrame::SendHeadFrame()
{
	m_pSocketHeadFrame->SendFrameData();
}

/**
* �������װ�֡
* @note �������̣�����SN�Ƿ���SN�������д��������Ƿ���·�ɵ�ַ����
* @param CFrameHead* pFrameHead �װ�ָ֡��
* @return void
*/
void CThreadProcHeadFrame::ProcHeadFrameOne(CFrameHead* pFrameHead)
{
	// �ж�����SN�Ƿ���SN��������
	if(TRUE == m_pSiteData->IfSNExistInSNMap(pFrameHead->m_uiSN))
	{
		// ����·�ɶ����·��ʱ��
		m_pSiteData->UpdateRoutTime(pFrameHead->m_uiRoutIP);
		// ����һ����Ҫ����IP��ַ������
		//AddInstrumentForIPSet(pFrameHead);		//bug,����Ҫ������IP���õ�����
		return;
	}

	CString strDesc;
	strDesc.Format("ProcHeadFrameOne1 SN=%d IP=%d TimeHead=%x RoutIP=%x", pFrameHead->m_uiSN, pFrameHead->m_uiRoutIP,pFrameHead->m_uiTimeHeadFrame,pFrameHead->m_uiRoutIP);
	m_pSiteData->m_oRunTimeDataList.Set(3, "CThreadProcHeadFrame", "ProcHeadFrameOne", strDesc);
	TRACE3("�װ� SN=%d IP=%d TimeHead=%x\r\n",pFrameHead->m_uiSN, pFrameHead->m_uiRoutIP,pFrameHead->m_uiTimeHeadFrame); 

		// �ж������Ƿ���·�ɵ�ַ��û��·�ɵ�ַ������Ϊ������վ
	if(0 == pFrameHead->m_uiRoutIP)
	{
		// ������ָ��Ϊ��
		CInstrument* pInstrument = NULL;
		// �õ�������
		GetFreeInstrument(pInstrument, pFrameHead);
		// ����������־����Ϊ��
		m_bInstrumentAdd = true;
		// �ж��׸�������վָ���Ƿ�Ϊ�գ��׸�������վָ��Ϊ�գ������׸�������վ
		if(NULL == m_pSiteData->m_pFirstMainCross)
		{
			// �׸�������վָ��ָ��������
			m_pSiteData->m_pFirstMainCross = pInstrument;
			// ����������վ
			AddMainCross(pInstrument);
			
			m_pSiteData->HeadminTime=0xffffffff;
			m_pSiteData->HeadCount=0;
			m_pSiteData->HeadEtime=0;
			//��ʼ���������������ݴ�
			m_pSiteData->NetDataCount=0;
			m_pSiteData->NetOrderCount=0;

			// ����״̬����
			CString strDesc;
			// ��ʽ������״̬����
			strDesc.Format("Add First Main Cross SN=%d��IP=%d", pInstrument->m_uiSN, pInstrument->m_uiIP);
			// ��������״̬����
			m_pSiteData->m_oRunTimeDataList.Set(3, "CThreadProcHeadFrame", "ProcHeadFrameOne", strDesc);
		}
		// �׸�������վָ�벻Ϊ�գ�����������վ��������������վ����β��
		else
		{
			// ������վָ��ָ���׸�������վ
			CInstrument* pMainCross = m_pSiteData->m_pFirstMainCross;
			//ѭ����ֱ���ҵ�������վ����β��
			while(NULL != pMainCross->m_pMainCrossNext)
			{
				// �õ����һ��������վ
				pMainCross = pMainCross->m_pMainCrossNext;
			}
			// ��������վ����������վ��β��
			pMainCross->m_pMainCrossNext = pInstrument;
			pMainCross->m_uiSNMainCrossNext = pInstrument->m_uiSN;
			pMainCross->m_iIndexCrossDown = pInstrument->m_uiIndex;
			pInstrument->m_pMainCrossPreview = pMainCross;
			pInstrument->m_uiSNMainCrossPreview = pMainCross->m_uiSN;
			pInstrument->m_iIndexMainCrossPreview = pMainCross->m_uiIndex;

			// ����������վ
			AddMainCross(pInstrument);
		}
		// ����һ����Ҫ����IP��ַ������
		AddInstrumentForIPSet(pInstrument);
	}
	//������·�ɵ�ַ
	else
	{
		if(m_pSiteData->HeadCount<5){
			m_pSiteData->HeadCount++;
			return;
		}

		pFrameHead->m_uiRoutIP=0x0f & pFrameHead->m_uiRoutIP;		// add test by zl 04.12
		// ·��ָ��Ϊ��
		CRout* pRout = NULL;
		// �ж��Ƿ�õ�·�ɶ���
		if(false == m_pSiteData->m_oRoutIPRoutMap.GetRout(pFrameHead->m_uiRoutIP, pRout))
		{
			// �Ҳ���·�ɶ��󣻼�¼������־�ļ�
			m_pSiteData->m_oRunTimeDataList.Set(2, "CThreadProcHeadFrame", "ProcHeadFrameOne", "Can not find Rout");
			return;
		}
		// ������ָ��Ϊ��
		CInstrument* pInstrument = NULL;
		// �õ�������
		GetFreeInstrument(pInstrument, pFrameHead);
		// ·�ɷ��� 1-�ϣ�2-�£�3-��4��
		pInstrument->m_uiRoutDirection = pRout->m_uiRoutDirection;
		// ����������־����Ϊ��
		m_bInstrumentAdd = true;

		// �ж���·�ɵ�ַ�����Խ���վ�Ϸ�
		if(1 == pRout->m_uiRoutDirection)
		{
			//����һ������վ
			AddCrossTop(pInstrument);
		}
		// �ж���·�ɵ�ַ�����Խ���վ�·�
		if(2 == pRout->m_uiRoutDirection)
		{
			//����һ������վ
			AddCrossDown(pInstrument);
		}
		// �ж���·�ɵ�ַ�����Խ���վ��
		if(3 == pRout->m_uiRoutDirection)
		{
			// �ж�����Ϊ����վ���������� 1-����վ��2-��Դվ��3-�ɼ�վ
			if(1 == pInstrument->m_uiInstrumentType)
			{
				// ���ӽ���վ���߷������Խ���վ��
				AddCrossLeft(pInstrument);
			}
			// �ж�����Ϊ��Դվ���������� 1-����վ��2-��Դվ��3-�ɼ�վ
			if(2 == pInstrument->m_uiInstrumentType)
			{
				// ���ӵ�Դվ�����Խ���վ��
				AddPowerLeft(pInstrument);
			}
			// �ж�����Ϊ�ɼ�վ���������� 1-����վ��2-��Դվ��3-�ɼ�վ
			if(3 == pInstrument->m_uiInstrumentType)
			{
				// ���Ӳɼ�վ�����Խ���վ��
				AddCollectLeft(pInstrument);
			}
		}
		// �ж���·�ɵ�ַ�����Խ���վ�ҷ�
		if(4 == pRout->m_uiRoutDirection)
		{
			// �ж�����Ϊ����վ���������� 1-����վ��2-��Դվ��3-�ɼ�վ
			if(1 == pInstrument->m_uiInstrumentType)
			{
				// ���ӽ���վ���߷������Խ���վ�ҷ�
				AddCrossRight(pInstrument);
			}
			// �ж�����Ϊ��Դվ���������� 1-����վ��2-��Դվ��3-�ɼ�վ
			if(2 == pInstrument->m_uiInstrumentType)
			{
				// ���ӵ�Դվ�����Խ���վ�ҷ�
				AddPowerRight(pInstrument);
			}
			// �ж�����Ϊ�ɼ�վ���������� 1-����վ��2-��Դվ��3-�ɼ�վ
			if(3 == pInstrument->m_uiInstrumentType)
			{
				// ���Ӳɼ�վ�����Խ���վ�ҷ�
				AddCollectRight(pInstrument);
			}
		}
		// ����һ����Ҫ����IP��ַ������		�ظ���IP���䣬ȡ�� 2011.9.13
		//AddInstrumentForIPSet(pInstrument);

		// ����״̬����
		CString strDesc;
		// ��ʽ������״̬����
		strDesc.Format("Add Instrument SN=%d IP=%d TimeHead=%x", pInstrument->m_uiSN, pInstrument->m_uiIP,pInstrument->m_uiTimeHeadFrame);
		// ��������״̬����
		m_pSiteData->m_oRunTimeDataList.Set(3, "CThreadProcHeadFrame", "ProcHeadFrameOne", strDesc);
		TRACE3("IP���� Instrument SN=%d IP=%d TimeHead=%x\r\n",pInstrument->m_uiSN, pInstrument->m_uiIP,pInstrument->m_uiTimeHeadFrame); 
	}
}

/**
* �ɿ����������еõ������������װ�֡�������������Ը�ֵ��������������������SN������
* @param CInstrument* &pInstrument ������ָ�룬����
* @param CFrameHead* pFrameHead �װ�ָ֡��
* @return void
*/
void CThreadProcHeadFrame::GetFreeInstrument(CInstrument* &pInstrument, CFrameHead* pFrameHead)
{
	// �õ�һ��������
	pInstrument = m_pSiteData->GetFreeInstrument();
	//������������SN
	pInstrument->m_uiSN = pFrameHead->m_uiSN;
	//��������������������
	pInstrument->m_uiInstrumentType = pFrameHead->m_uiInstrumentType;
	//������������·��IP��ַ
	pInstrument->m_uiRoutIP = pFrameHead->m_uiRoutIP;
	//�������������װ�ʱ��
	pInstrument->m_uiTimeHeadFrame = pFrameHead->m_uiTimeHeadFrame;
	// ����������SN������
	m_pSiteData->m_oSNInstrumentMap.AddInstrument(pInstrument->m_uiSN, pInstrument);
}

/**
* ����������վ
* @param CInstrument* &pInstrument ����ָ��
* @return void
*/
void CThreadProcHeadFrame::AddMainCross(CInstrument* pInstrument)
{
	// Ϊ����������IP��ַ
	pInstrument->m_uiIP = m_pSiteData->m_oIPList.GetFreeCrossIP();
	// ����������IP������
	m_pSiteData->m_oIPInstrumentMap.AddInstrument(pInstrument->m_uiIP, pInstrument);

	if(1 == m_pLogicData->m_oLookSetupData.m_uiLookAuto)	// �Զ�ʶ��
	{
		// ���ý���վ·�ɷ�����
		SetCrossRout(pInstrument, 1);
		// ���ý���վ·�ɷ�����
		SetCrossRout(pInstrument, 2);
		// ���ý���վ·�ɷ�����
		SetCrossRout(pInstrument, 3);
		// ���ý���վ·�ɷ�����
		SetCrossRout(pInstrument, 4);
	}
}

/**
* ���ӽ���վ�������߷����Ϸ�
* @param CInstrument* &pInstrument ����ָ��
* @return void
*/
void CThreadProcHeadFrame::AddCrossTop(CInstrument* pInstrument)
{
	// Ϊ����������IP��ַ
	pInstrument->m_uiIP = m_pSiteData->m_oIPList.GetFreeCrossIP();
	// ����������IP������
	m_pSiteData->m_oIPInstrumentMap.AddInstrument(pInstrument->m_uiIP, pInstrument);

	// �������з���·�ɵ�ַ
	pInstrument->m_uiRoutIPDown = 0xFFFF;
	if(1 == m_pLogicData->m_oLookSetupData.m_uiLookAuto)	// �Զ�ʶ��
	{
		// ���ý���վ·�ɷ�����
//		SetCrossRout(pInstrument, 1);
		// ���ý���վ·�ɷ�����
		SetCrossRout(pInstrument, 3);
		// ���ý���վ·�ɷ�����
		SetCrossRout(pInstrument, 4);
	}

	CRout* pRout = NULL;
	// �õ�·�ɶ���
	m_pSiteData->m_oRoutIPRoutMap.GetRout(pInstrument->m_uiRoutIP, pRout);
	// ����·�ɶ����·��ʱ��
	pRout->UpdateRoutTime();
	// �жϣ�����վ·�ɷ���û����������
	if(NULL == pRout->m_pTail)
	{
		// ������������������ָ��ָ��·��ͷָ��
		pInstrument->m_pCrossDown = pRout->m_pHead;
		pInstrument->m_uiSNCrossDown = pRout->m_pHead->m_uiSN;
		pInstrument->m_iIndexCrossDown = pRout->m_pHead->m_uiIndex;

		// ����������·��ͷ������ָ��ָ��������
		pRout->m_pHead->m_pCrossTop = pInstrument;
		pRout->m_pHead->m_uiSNCrossTop = pInstrument->m_uiSN;
		pRout->m_pHead->m_iIndexCrossTop = pInstrument->m_uiIndex;

		// ����·�ɶ���βָ��
		pRout->m_pTail = pInstrument;
		pRout->m_uiSNTail = pInstrument->m_uiSN;
		pRout->m_iIndexTail = pInstrument->m_uiIndex;
	}
	// �жϣ�����վ·�ɷ�����������
	else
	{
		// ������������������ָ��ָ��·��β����
		pInstrument->m_pCrossDown = pRout->m_pTail;
		pInstrument->m_uiSNCrossDown = pRout->m_pTail->m_uiSN;
		pInstrument->m_iIndexCrossDown = pRout->m_pTail->m_uiIndex;

		// ����������·��β������ָ��ָ��������
		pRout->m_pTail->m_pCrossTop = pInstrument;
		pRout->m_pTail->m_uiSNCrossTop = pInstrument->m_uiSN;
		pRout->m_pTail->m_iIndexCrossTop = pInstrument->m_uiIndex;

		// ����·�ɶ���βָ��
		pRout->m_pTail = pInstrument;
		pRout->m_uiSNTail = pInstrument->m_uiSN;
		pRout->m_iIndexTail = pInstrument->m_uiIndex;
	}
}

/**
* ���ӽ���վ�������߷����·�
* @param CInstrument* &pInstrument ����ָ��
* @return void
*/
void CThreadProcHeadFrame::AddCrossDown(CInstrument* pInstrument)
{
	// Ϊ����������IP��ַ
	pInstrument->m_uiIP = m_pSiteData->m_oIPList.GetFreeCrossIP();
	// ����������IP������
	m_pSiteData->m_oIPInstrumentMap.AddInstrument(pInstrument->m_uiIP, pInstrument);

	// �������з���·�ɵ�ַ
	pInstrument->m_uiRoutIPTop = 0xFFFF;
	if(1 == m_pLogicData->m_oLookSetupData.m_uiLookAuto)	// �Զ�ʶ��
	{
		// ���ý���վ·�ɷ�����
//		SetCrossRout(pInstrument, 2);
		// ���ý���վ·�ɷ�����
		SetCrossRout(pInstrument, 3);
		// ���ý���վ·�ɷ�����
		SetCrossRout(pInstrument, 4);
	}

	CRout* pRout = NULL;
	// �õ�·�ɶ���
	m_pSiteData->m_oRoutIPRoutMap.GetRout(pInstrument->m_uiRoutIP, pRout);
	// ����·�ɶ����·��ʱ��
	pRout->UpdateRoutTime();
	// �жϣ�����վ·�ɷ���û����������
	if(NULL == pRout->m_pTail)
	{
		// ������������������ָ��ָ��·��ͷָ��
		pInstrument->m_pCrossTop = pRout->m_pHead;
		pInstrument->m_uiSNCrossTop = pRout->m_pHead->m_uiSN;
		pInstrument->m_iIndexCrossTop = pRout->m_pHead->m_uiIndex;

		// ����������·��ͷ������ָ��ָ��������
		pRout->m_pHead->m_pCrossDown = pInstrument;
		pRout->m_pHead->m_uiSNCrossDown = pInstrument->m_uiSN;
		pRout->m_pHead->m_iIndexCrossDown = pInstrument->m_uiIndex;

		// ����·�ɶ���βָ��
		pRout->m_pTail = pInstrument;
		pRout->m_uiSNTail = pInstrument->m_uiSN;
		pRout->m_iIndexTail = pInstrument->m_uiIndex;
	}
	// �жϣ�����վ·�ɷ�����������
	else
	{
		// ������������������ָ��ָ��·��β����
		pInstrument->m_pCrossTop = pRout->m_pTail;
		pInstrument->m_uiSNCrossTop = pRout->m_pTail->m_uiSN;
		pInstrument->m_iIndexCrossTop = pRout->m_pTail->m_uiIndex;

		// ����������·��β������ָ��ָ��������
		pRout->m_pTail->m_pCrossDown = pInstrument;
		pRout->m_pTail->m_uiSNCrossDown = pInstrument->m_uiSN;
		pRout->m_pTail->m_iIndexCrossDown = pInstrument->m_uiIndex;

		// ����·�ɶ���βָ��
		pRout->m_pTail = pInstrument;
		pRout->m_uiSNTail = pInstrument->m_uiSN;
		pRout->m_iIndexTail = pInstrument->m_uiIndex;
	}
}

/**
* ���ӽ���վ�����߷�����
* @param CInstrument* &pInstrument ����ָ��
* @return void
*/
void CThreadProcHeadFrame::AddCrossLeft(CInstrument* pInstrument)
{
	// Ϊ����������IP��ַ
	pInstrument->m_uiIP = m_pSiteData->m_oIPList.GetFreeCrossIP();
	// ����������IP������
	m_pSiteData->m_oIPInstrumentMap.AddInstrument(pInstrument->m_uiIP, pInstrument);

	// �������з���·�ɵ�ַ
	pInstrument->m_uiRoutIPRight = 0xFFFF;

	// ���ӽ���վ���߷�����
	AddCollectLeft(pInstrument);
}

/**
* ���ӽ���վ�����߷����ҷ�
* @param CInstrument* &pInstrument ����ָ��
* @return void
*/
void CThreadProcHeadFrame::AddCrossRight(CInstrument* pInstrument)
{
	// Ϊ����������IP��ַ
	pInstrument->m_uiIP = m_pSiteData->m_oIPList.GetFreeCrossIP();
	// ����������IP������
	m_pSiteData->m_oIPInstrumentMap.AddInstrument(pInstrument->m_uiIP, pInstrument);

	// �������з���·�ɵ�ַ
	pInstrument->m_uiRoutIPLeft = 0xFFFF;

	// ���ӵ�Դվ���߷����ҷ�
	AddCollectRight(pInstrument);	
}

/**
* ���ӵ�Դվ�����߷�����
* @param CInstrument* &pInstrument ����ָ��
* @return void
*/
void CThreadProcHeadFrame::AddPowerLeft(CInstrument* pInstrument)
{
	// Ϊ����������IP��ַ
	pInstrument->m_uiIP = m_pSiteData->m_oIPList.GetFreePowerIP();
	// ����������IP������
	m_pSiteData->m_oIPInstrumentMap.AddInstrument(pInstrument->m_uiIP, pInstrument);

	// ���ӵ�Դվ���߷�����
	AddCollectLeft(pInstrument);
}

/**
* ���ӵ�Դվ�����߷����ҷ�
* @param CInstrument* &pInstrument ����ָ��
* @return void
*/
void CThreadProcHeadFrame::AddPowerRight(CInstrument* pInstrument)
{
	// Ϊ����������IP��ַ
	pInstrument->m_uiIP = m_pSiteData->m_oIPList.GetFreePowerIP();
	// ����������IP������
	m_pSiteData->m_oIPInstrumentMap.AddInstrument(pInstrument->m_uiIP, pInstrument);

	// ���ӵ�Դվ���߷����ҷ�
	AddCollectRight(pInstrument);	
}

/**
* ���Ӳɼ�վ�����߷�����
* @param CInstrument* &pInstrument ����ָ��
* @return void
*/
void CThreadProcHeadFrame::AddCollectLeft(CInstrument* pInstrument)
{
	CRout* pRout = NULL;
	// �õ�·�ɶ���
	m_pSiteData->m_oRoutIPRoutMap.GetRout(pInstrument->m_uiRoutIP, pRout);
	// ����·�ɶ����·��ʱ��
	pRout->UpdateRoutTime();

	if(NULL == pRout->m_pTail)	// ����վ·�ɷ���û����������
	{
		// ������������������ָ��ָ��·��ͷ����
		pInstrument->m_pInstrumentRight = pRout->m_pHead;
		pInstrument->m_uiSNInstrumentRight = pRout->m_pHead->m_uiSN;
		pInstrument->m_iIndexInstrumentRight = pRout->m_pHead->m_uiIndex;

		// ����������·��ͷ������ָ��ָ��������
		pRout->m_pHead->m_pInstrumentLeft = pInstrument;
		pRout->m_pHead->m_uiSNInstrumentLeft = pInstrument->m_uiSN;
		pRout->m_pHead->m_iIndexInstrumentLeft = pInstrument->m_uiIndex;

		// ����·�ɶ���βָ��
		pRout->m_pTail = pInstrument;
		pRout->m_uiSNTail = pInstrument->m_uiSN;
		pRout->m_iIndexTail = pInstrument->m_uiIndex;
	}
	else	// ����վ·�ɷ�������������
	{
		// �жϣ������װ�ʱ�̴���·����β�����װ�ʱ��		
		if(pInstrument->m_uiTimeHeadFrame > pRout->m_pTail->m_uiTimeHeadFrame)	// ����������·��������β
		{
			// ������������������ָ��ָ��·��β����
			pInstrument->m_pInstrumentRight = pRout->m_pTail;
			pInstrument->m_uiSNInstrumentRight = pRout->m_pTail->m_uiSN;
			pInstrument->m_iIndexInstrumentRight = pRout->m_pTail->m_uiIndex;
			TRACE3("����������β SN=%d IP=%d TimeHead=%x\r\n",pInstrument->m_uiSN, pInstrument->m_uiIP,pInstrument->m_uiTimeHeadFrame); 
			
			// ����������·��β������ָ��ָ��������
			pRout->m_pTail->m_pInstrumentLeft = pInstrument;
			pRout->m_pTail->m_uiSNInstrumentLeft = pInstrument->m_uiSN;
			pRout->m_pTail->m_iIndexInstrumentLeft = pInstrument->m_uiIndex;

			// ����·�ɶ���βָ��
			pRout->m_pTail = pInstrument;
			pRout->m_uiSNTail = pInstrument->m_uiSN;
			pRout->m_iIndexTail = pInstrument->m_uiIndex;
		}
		// �жϣ������װ�ʱ��С��·����β�����װ�ʱ��
		else
		{
			// ��·����β������ʼ���ҵ��װ�ʱ��С�������װ�ʱ�̵�����
			// ���Ϊβ�����ұߵ�һ������
			CInstrument* pInstrumentTemp = pRout->m_pTail->m_pInstrumentRight;
			// ��β����ͷ����
			// �������װ�ʱ��С�ڱ��Ƚ�����
			while(pInstrument->m_uiTimeHeadFrame < pInstrumentTemp->m_uiTimeHeadFrame)
			{
				// ��ͷ������õ���һ������
				pInstrumentTemp = pInstrumentTemp->m_pInstrumentRight;
			}
			// �ҵ��������װ�ʱ��С�����������������������ҵ����������
			// ������������������ָ��ָ���ҵ�����
			pInstrument->m_pInstrumentRight = pInstrumentTemp;
			pInstrument->m_uiSNInstrumentRight = pInstrumentTemp->m_uiSN;
			pInstrument->m_iIndexInstrumentRight = pInstrumentTemp->m_uiIndex;

			// ������������������ָ��ָ���ҵ���������ָ��
			pInstrument->m_pInstrumentLeft = pInstrumentTemp->m_pInstrumentLeft;
			pInstrument->m_uiSNInstrumentLeft = pInstrumentTemp->m_pInstrumentLeft->m_uiSN;
			pInstrument->m_iIndexInstrumentLeft = pInstrumentTemp->m_pInstrumentLeft->m_uiIndex;

			// ���������������������������ָ��ָ��������
			pInstrumentTemp->m_pInstrumentLeft->m_pInstrumentRight = pInstrument;
			pInstrumentTemp->m_pInstrumentLeft->m_uiSNInstrumentRight = pInstrument->m_uiSN;
			pInstrumentTemp->m_pInstrumentLeft->m_iIndexInstrumentRight = pInstrument->m_uiIndex;

			TRACE3("����������� SN=%d IP=%d TimeHead=%x\r\n",pInstrument->m_uiSN, pInstrument->m_uiIP,pInstrument->m_uiTimeHeadFrame); 
			pInstrumentTemp->m_pInstrumentLeft = pInstrument;
			pInstrumentTemp->m_uiSNInstrumentLeft = pInstrument->m_uiSN;
			pInstrumentTemp->m_iIndexInstrumentLeft = pInstrument->m_uiIndex;
		}
	}	
}

/**
* ���Ӳɼ�վ�����߷����ҷ�
* @param CInstrument* &pInstrument ����ָ��
* @return void
*/
void CThreadProcHeadFrame::AddCollectRight(CInstrument* pInstrument)
{
	CRout* pRout = NULL;
	// �õ�·�ɶ���
	m_pSiteData->m_oRoutIPRoutMap.GetRout(pInstrument->m_uiRoutIP, pRout);
	// ����·�ɶ����·��ʱ��
	pRout->UpdateRoutTime();

	if(NULL == pRout->m_pTail)	// ����վ·�ɷ���û����������
	{
		// ������������������ָ��ָ��·��ͷ����
		pInstrument->m_pInstrumentLeft = pRout->m_pHead;
		pInstrument->m_uiSNInstrumentLeft = pRout->m_pHead->m_uiSN;
		pInstrument->m_iIndexInstrumentLeft = pRout->m_pHead->m_uiIndex;

		// ����������·��ͷ������ָ��ָ��������
		pRout->m_pHead->m_pInstrumentRight = pInstrument;
		pRout->m_pHead->m_uiSNInstrumentRight = pInstrument->m_uiSN;
		pRout->m_pHead->m_iIndexInstrumentRight = pInstrument->m_uiIndex;

		// ����·�ɶ���βָ��
		pRout->m_pTail = pInstrument;
		pRout->m_uiSNTail = pInstrument->m_uiSN;
		pRout->m_iIndexTail = pInstrument->m_uiIndex;
	}
	else	// ����վ·�ɷ�������������
	{
		if(pInstrument->m_uiTimeHeadFrame > pRout->m_pTail->m_uiTimeHeadFrame)	// �����װ�ʱ�̴���·����β�����װ�ʱ��
		{
			// ������������������ָ��ָ��·��β����
			TRACE3("����������β SN=%d IP=%d TimeHead=%x\r\n",pInstrument->m_uiSN, pInstrument->m_uiIP,pInstrument->m_uiTimeHeadFrame); 
			pInstrument->m_pInstrumentLeft = pRout->m_pTail;
			pInstrument->m_uiSNInstrumentLeft = pRout->m_pTail->m_uiSN;
			pInstrument->m_iIndexInstrumentLeft = pRout->m_pTail->m_uiIndex;

			// ����������·��β������ָ��ָ��������
			pRout->m_pTail->m_pInstrumentRight = pInstrument;
			pRout->m_pTail->m_uiSNInstrumentRight = pInstrument->m_uiSN;
			pRout->m_pTail->m_iIndexInstrumentRight = pInstrument->m_uiIndex;

			// ����·�ɶ���βָ��
			pRout->m_pTail = pInstrument;
			pRout->m_uiSNTail = pInstrument->m_uiSN;
			pRout->m_iIndexTail = pInstrument->m_uiIndex;
		}
		else	// �����װ�ʱ��С��·����β�����װ�ʱ��
		{
			// ��·����β������ʼ���ҵ��װ�ʱ��С�������װ�ʱ�̵�����
			// ���Ϊβ������ߵ�һ������
			CInstrument* pInstrumentTemp = pRout->m_pTail->m_pInstrumentLeft;
			// ��β����ͷ����
			// �������װ�ʱ��С�ڱ��Ƚ�����
			while(pInstrument->m_uiTimeHeadFrame < pInstrumentTemp->m_uiTimeHeadFrame)
			{
				// ��ͷ������õ���һ������
				pInstrumentTemp = pInstrumentTemp->m_pInstrumentLeft;
			}
			// �ҵ��������װ�ʱ��С�����������������������ҵ��������ұ�
			// ������������������ָ��ָ���ҵ�����
			pInstrument->m_pInstrumentLeft = pInstrumentTemp;
			pInstrument->m_uiSNInstrumentLeft = pInstrumentTemp->m_uiSN;
			pInstrument->m_iIndexInstrumentLeft = pInstrumentTemp->m_uiIndex;

			// ������������������ָ��ָ���ҵ���������ָ��
			pInstrument->m_pInstrumentRight = pInstrumentTemp->m_pInstrumentRight;
			pInstrument->m_uiSNInstrumentRight = pInstrumentTemp->m_pInstrumentRight->m_uiSN;
			pInstrument->m_iIndexInstrumentRight = pInstrumentTemp->m_pInstrumentRight->m_uiIndex;

			// �����������������ұ���������ָ��ָ��������
			pInstrumentTemp->m_pInstrumentRight->m_pInstrumentLeft = pInstrument;
			pInstrumentTemp->m_pInstrumentRight->m_uiSNInstrumentLeft = pInstrument->m_uiSN;
			pInstrumentTemp->m_pInstrumentRight->m_iIndexInstrumentLeft = pInstrument->m_uiIndex;

			// �����������ҵ���������ָ��ָ��������
			TRACE3("�Ҳ��������� SN=%d IP=%d TimeHead=%x\r\n",pInstrument->m_uiSN, pInstrument->m_uiIP,pInstrument->m_uiTimeHeadFrame); 
			pInstrumentTemp->m_pInstrumentRight = pInstrument;
			pInstrumentTemp->m_uiSNInstrumentRight = pInstrument->m_uiSN;
			pInstrumentTemp->m_iIndexInstrumentRight = pInstrument->m_uiIndex;
		}
	}	
}

/**
* ���ý���վĳ�������·��
* @param CInstrument* &pInstrument ����ָ��
* @param unsigned int uiRoutDirection ·�ɷ���
* @return void
*/
void CThreadProcHeadFrame::SetCrossRout(CInstrument* pInstrument, unsigned int uiRoutDirection)
{
	CRout* pRout = NULL;
	// �õ�����·�ɶ���
	pRout = m_pSiteData->m_oRoutList.GetFreeRout();

	// �жϷ�����������·�ɵ�ַ
	switch(uiRoutDirection)
	{
	case 1:	// ��
		{
			pInstrument->m_uiRoutIPTop = pRout->m_uiRoutIP;
			break;
		}
	case 2:	// ��
		{
			pInstrument->m_uiRoutIPDown = pRout->m_uiRoutIP;
			break;
		}
	case 3:	// ��
		{
			pInstrument->m_uiRoutIPLeft = pRout->m_uiRoutIP;
			break;
		}
	case 4:	// ��
		{
			pInstrument->m_uiRoutIPRight = pRout->m_uiRoutIP;
			break;
		}
	}

	// ���ý���վ·�ɷ���
	pRout->m_uiRoutDirection = uiRoutDirection;
	// ����·��ͷ
	pRout->m_pHead = pInstrument;
	pRout->m_uiSNHead = pInstrument->m_uiSN;
	pRout->m_iIndexHead = pInstrument->m_uiIndex;
	// ����·��β
	pRout->m_pTail = NULL;
	// ����·�ɶ����·��ʱ��
	pRout->UpdateRoutTime();
	// ·�ɶ������·��������
	m_pSiteData->m_oRoutIPRoutMap.AddRout(pRout->m_uiRoutIP, pRout);
}

/**
* ����һ����Ҫ����IP��ַ������
* @note ����IP��ַ�����̵߳Ĵ�����IP��ַ��������
* @param CInstrument* &pInstrument ����ָ��
* @return void
*/
void CThreadProcHeadFrame::AddInstrumentForIPSet(CInstrument* pInstrument)
{
	if(pInstrument->m_uiIP > 0)	//������������IP��ַ
	{
		// ���������IP��ַ��������
		m_pThreadProcIPSet->AddInstrumentForIPSet(pInstrument);
	}
}

/**
* ����һ����Ҫ����IP��ַ������
* @note ����IP��ַ�����̵߳Ĵ�����IP��ַ��������
* @param CFrameHead* pFrameHead �װ�ָ֡��
* @return void
*/
void CThreadProcHeadFrame::AddInstrumentForIPSet(CFrameHead* pFrameHead)
{
	// ����ָ��
	CInstrument* pInstrument = NULL;
	// ������SN�ŵõ�����
	if(TRUE == m_pSiteData->m_oSNInstrumentMap.GetInstrument(pFrameHead->m_uiSN, pInstrument))
	{
		// ����һ����Ҫ����IP��ַ������
		AddInstrumentForIPSet(pInstrument);
	}
}