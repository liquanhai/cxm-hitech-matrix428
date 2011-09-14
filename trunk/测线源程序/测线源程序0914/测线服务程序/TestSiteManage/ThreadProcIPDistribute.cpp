// ThreadProcIPDistribute.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "TestSiteManage.h"
#include "ThreadProcIPDistribute.h"


// CThreadProcIPDistribute

IMPLEMENT_DYNCREATE(CThreadProcIPDistribute, CWinThread)

CThreadProcIPDistribute::CThreadProcIPDistribute()
{
	// �Ƿ���״̬
	m_bWork = false;
	// �Ƿ�ر��߳�
	m_bClose = false;
}

CThreadProcIPDistribute::~CThreadProcIPDistribute()
{
}

BOOL CThreadProcIPDistribute::InitInstance()
{
	// TODO: �ڴ�ִ���������̳߳�ʼ��
	return TRUE;
}

int CThreadProcIPDistribute::ExitInstance()
{
	// TODO: �ڴ�ִ���������߳�����
	return CWinThread::ExitInstance();
}

BEGIN_MESSAGE_MAP(CThreadProcIPDistribute, CWinThread)
END_MESSAGE_MAP()

// CThreadProcIPDistribute ��Ϣ�������

/**
* �߳�������
* @param void
* @return int
*/
int CThreadProcIPDistribute::Run()
{
	// ѭ����ֱ���رձ�־Ϊ��
	while(true)
	{
		// �жϹرձ�־�Ƿ�Ϊ��
		if(true == m_bClose)
		{
			break;
		}
		// ����IP��ַ����
		ProcIPDistribute();
		// �жϹرձ�־�Ƿ�Ϊ��
		if(true == m_bClose)
		{
			break;
		}
		// ����1000����
		Wait(20);
	}
	// ����IP��ַ�����̹߳رձ�־Ϊ��
	m_pSiteData->m_bProcIPDistributeClose = true;
	// ����
	return CWinThread::Run();
}

/**
* ��ʼ���߳�
* @param void
* @return bool true���ɹ���false��ʧ��
*/
bool CThreadProcIPDistribute::OnInit()
{
	// �Ƿ���״̬
	m_bWork = false;
	// �Ƿ�ر��߳�
	m_bClose = false;
	// ����IP��ַ����ʱ��
	m_iIPDistributeTime = 0;
	return true;
}

/**
* �ر��߳�
* @param void
* @return bool true���ɹ���false��ʧ��
*/
bool CThreadProcIPDistribute::OnClose()
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
bool CThreadProcIPDistribute::OnWork()
{
	// ����������SN������
	m_oInstrumentAuxSNMap.RemoveAll(); 
	// ��ը������������SN������
	m_oInstrumentBlastMachineSNMap.RemoveAll(); 
	// �ػص��������SN������
	m_oInstrumentDetourLogoSNMap.RemoveAll(); 
	// �ػص�����SN������
	m_oInstrumentDetourSNMap.RemoveAll(); 
	// �ɼ����������SN������
	m_oInstrumentMarkerLogoSNMap.RemoveAll(); 
	// �ɼ�������SN������
	m_oInstrumentMarkerSNMap.RemoveAll(); 
	// �Ƿ���״̬
	m_bWork = true;
	return true;
}

/**
* �߳�ֹͣ����
* @param void
* @return bool true���ɹ���false��ʧ��
*/
bool CThreadProcIPDistribute::OnStop()
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
void CThreadProcIPDistribute::Wait(int iWaitStopCount)
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
* @note �߳������������²������ֳ�ֹͣ��ɾ��������·�ɴ����߳��������У��ֳ���������߳��������У�Ҫ������IP��ַ�����߳���ͣ��
* @param void
* @return bool true����������false��ֹͣ����
*/
bool CThreadProcIPDistribute::JudgeProcCondition()
{	
	// ɾ��������·�ɴ����߳��������У����ֳ���������߳��������У�����ͣҪ��Ҫ������IP��ַ�����߳���ͣ
	if((true == m_pSiteData->m_bProcDeleteRunning) || (true == m_pSiteData->m_bProcSiteDataOutputRunning) || (true == m_pSiteData->m_bPauseRequestForProcIPDistribute))
	{		
		m_pSiteData->m_bProcIPDistributePause = true;	// ����IP��ַ�����߳���ͣ
		return false;
	}
	else
	{		
		m_pSiteData->m_bProcIPDistributePause = false;	// ����IP��ַ�����߳�����
	}
	// �ǹ���״̬
	if(false == m_bWork)
	{		
		m_pSiteData->m_bProcIPDistributeStop = true;	// ����IP��ַ�����߳�ֹͣ
		return false;
	}
	else
	{
		m_pSiteData->m_bProcIPDistributeStop = false;	// ����IP��ַ�����̹߳���
	}
	return true;
}

/**
* ����IP��ַ����
* @param void
* @return void
*/
void CThreadProcIPDistribute::ProcIPDistribute()
{	
	// �ж��Ƿ���Դ��������
	if(false == JudgeProcCondition())
	{
		return;
	}
	// ��������IP��ַ����ʱ��
	m_iIPDistributeTime = GetTickCount();
	// Ϊ����������IP��ַ
	if(false == ProcIPDistributeAux())
	{
		return;
	}
	// Ϊ��ը������������IP��ַ
	if(false == ProcIPDistributeBlastMachine())
	{
		return;
	}
	// Ϊ�ػص�����IP��ַ
	if(false == ProcIPDistributeDetour())
	{
		return;
	}
	// ����ǵ����IP��ַ
	ProcIPDistributeMarker();
}

/**
* ��������IP��ַ����
* @param void
* @return bool true�����Լ������䣻false����ֹ����
*/
bool CThreadProcIPDistribute::ProcIPDistributeAux()
{
	// �õ�����������
	CAuxList* pAuxList = &m_pLogicData->m_oLayoutSetupData.m_oAuxList;
	// ������ָ��Ϊ��
	CAuxData* pAuxData = NULL;
	// ѭ�����õ����и�����
	for(unsigned int i = 0; i < pAuxList->m_uiCountAll; i++)
	{
		// �õ�������
		pAuxData = pAuxList->GetAux(i);
		// ����һ����������IP��ַ����
		ProcIPDistributeAuxOne(pAuxData);
	}
	// ������ڸ��������
	return ProcClearTimeOutAux();
}

/**
* ����һ����������IP��ַ����
* @param CAuxData* pAuxData ������ָ��
* @return void
*/
void CThreadProcIPDistribute::ProcIPDistributeAuxOne(CAuxData* pAuxData)
{	
	// ����ָ��Ϊ��
	CInstrument* pInstrument = NULL;
	// IP��ַ
	unsigned int uiIP;

	// �жϸ�������Ӧ�����Ƿ������ӵ��ֳ�
	if(TRUE == m_pSiteData->GetInstrumentFromSNMapBySN(pAuxData->m_uiSN, pInstrument))
	{
		// �жϣ��������ǲɼ�վ
		if(3 != pInstrument->m_uiInstrumentType)
		{
			return;
		}
		// �õ�������IP��ַ
		uiIP = pAuxData->m_uiIP;

		// �жϣ���������Ӧ����δ����IP��ַ
		if(0 == pInstrument->m_uiIP)
		{
			// ���ø���������Ϊ��
			pInstrument->m_bAux = true;
			// ��������IP��ַ����ʱ��
			pInstrument->m_uiIPDistributeTime = m_iIPDistributeTime;
			// ���ø��������ʱ��
			pInstrument->m_uiAuxTime = m_iIPDistributeTime;
			// ��������IP��ַ
			pInstrument->m_uiIP = uiIP;
			// ��������IP��ַ������
			m_pSiteData->m_oIPInstrumentMap.AddInstrument(pInstrument->m_uiIP, pInstrument);
			// ���븨��������������
			m_oInstrumentAuxSNMap.SetAt(pInstrument->m_uiSN, pInstrument);
			// ��������IP��ַ���ö���
			m_pThreadProcIPSet->AddInstrumentForIPSet(pInstrument);
		}
		// �жϣ���������Ҫ��������IP��ַ
		else if(uiIP != pInstrument->m_uiIP)
		{
			// �жϣ�����Ϊ�ɼ�վ���Ǳ��η���
			if((3 == pInstrument->m_uiInstrumentType) && (m_iIPDistributeTime != pInstrument->m_uiIPDistributeTime))
			{
				// �ͷ�����IP��ַ
				m_pSiteData->ReleaseInstrument(pInstrument->m_uiIP, m_iIPDistributeTime);
			}
			// ���ø�����Ϊ��
			pInstrument->m_bAux = true;
			// ��������IP��ַ����ʱ��
			pInstrument->m_uiIPDistributeTime = m_iIPDistributeTime;
			// ���ø��������ʱ��
			pInstrument->m_uiAuxTime = m_iIPDistributeTime;
			// ��������IP��ַ
			pInstrument->m_uiIP = uiIP;
			// ��������IP��ַ������
			m_pSiteData->m_oIPInstrumentMap.AddInstrument(pInstrument->m_uiIP, pInstrument);
			// ���븨��������������
			m_oInstrumentAuxSNMap.SetAt(pInstrument->m_uiSN, pInstrument);
			// ��������IP��ַ���ö���
			m_pThreadProcIPSet->AddInstrumentForIPSet(pInstrument);
		}
		// �ϴη�����ȷ
		else
		{
			// ��������IP��ַ����ʱ��
			pInstrument->m_uiIPDistributeTime = m_iIPDistributeTime;
			// ���������ʱ��
			pInstrument->m_uiAuxTime = m_iIPDistributeTime;
		}
	}
}

/**
* ������ڸ��������
* @param void
* @return bool true��û��Ҫ����Ĺ��ڱ�ǣ�false����Ҫ����Ĺ��ڱ��
*/
bool CThreadProcIPDistribute::ProcClearTimeOutAux()
{
	bool bReturn = true;

	POSITION pos = NULL;	// λ��	
	unsigned int uiSN;	// �����豸��
	CInstrument* pInstrument = NULL;	// ����
	pos = m_oInstrumentAuxSNMap.GetStartPosition();
	while(NULL != pos)
	{
		m_oInstrumentAuxSNMap.GetNextAssoc(pos, uiSN, pInstrument);
		// �жϣ��Ǳ��η���
		if(pInstrument->m_uiAuxTime != m_iIPDistributeTime)
		{
			// �жϣ�����IP��ַ��0������Ϊ�ɼ�վ���Ǳ��η���
			if((0 != pInstrument->m_uiIP) && (3 == pInstrument->m_uiInstrumentType) && (pInstrument->m_uiIPDistributeTime != m_iIPDistributeTime))
			{
				// �ͷ�����IP��ַ
				m_pSiteData->ReleaseInstrument(pInstrument->m_uiIP, m_iIPDistributeTime);
				// ����IP��ַ
				pInstrument->m_uiIP = 0;
				// ��������IP��ַ���ö���
				m_pThreadProcIPSet->AddInstrumentForIPSet(pInstrument);
				bReturn = false;
			}
			// �Ƿ�����
			pInstrument->m_bAux = false;
			// ��������IP��ַ����ʱ��
			pInstrument->m_uiIPDistributeTime = 0;
			// ���������ʱ��
			pInstrument->m_uiAuxTime = 0;
			m_oInstrumentAuxSNMap.RemoveKey(uiSN);
		}
	}
	return bReturn;
}

/**
* ����ը��������IP��ַ����
* @param void
* @return bool true�����Լ������䣻false����ֹ����
*/
bool CThreadProcIPDistribute::ProcIPDistributeBlastMachine()
{
	// ��ը������������
	CBlastMachineList* pBlastMachineList = &m_pLogicData->m_oLayoutSetupData.m_oBlastMachineList;
	// ��ը��������
	CBlastMachineData* pBlastMachineData;
	for(unsigned int i = 0; i < pBlastMachineList->m_uiCountAll; i++)
	{
		pBlastMachineData = pBlastMachineList->GetBlastMachine(i);
		ProcIPDistributeBlastMachineOne(pBlastMachineData);
	}
	// ������ڱ�ը�����������
	return ProcClearTimeOutBlastMachine();
}

/**
* ����һ����ը����������IP��ַ����
* @param CBlastMachineData* pBlastMachineData ��ը��������ָ��
* @return void
*/
void CThreadProcIPDistribute::ProcIPDistributeBlastMachineOne(CBlastMachineData* pBlastMachineData)
{	
	CInstrument* pInstrument = NULL;	// ����	
	unsigned int uiIP;	// IP��ַ

	// ��ը�������������ӵ��ֳ�
	if(TRUE == m_pSiteData->GetInstrumentFromSNMapBySN(pBlastMachineData->m_uiSN, pInstrument))
	{
		// �жϣ��������ǲɼ�վ
		if(3 != pInstrument->m_uiInstrumentType)
		{
			return;
		}
		// �õ���ը��������IP��ַ
		uiIP = pBlastMachineData->m_uiIP;;

		// �жϣ���ը��������δ����IP��ַ
		if(0 == pInstrument->m_uiIP)
		{
			// �Ƿ�ը��������
			pInstrument->m_bBlastMachine = true;
			// ��������IP��ַ����ʱ��
			pInstrument->m_uiIPDistributeTime = m_iIPDistributeTime;	
			// ��ը�����������ʱ��
			pInstrument->m_uiBlastMachineTime = m_iIPDistributeTime;
			// ����IP��ַ
			pInstrument->m_uiIP = uiIP;
			// ��������IP��ַ������
			m_pSiteData->m_oIPInstrumentMap.AddInstrument(pInstrument->m_uiIP, pInstrument);
			// ���뱬ը����������������
			m_oInstrumentBlastMachineSNMap.SetAt(pInstrument->m_uiSN, pInstrument);
			// ��������IP��ַ���ö���
			m_pThreadProcIPSet->AddInstrumentForIPSet(pInstrument);
		}
		// �жϣ���ը����������Ҫ��������IP��ַ
		else if(uiIP != pInstrument->m_uiIP)
		{
			// �жϣ�����Ϊ�ɼ�վ���Ǳ��η���
			if((3 == pInstrument->m_uiInstrumentType) && (m_iIPDistributeTime != pInstrument->m_uiIPDistributeTime))
			{
				// �ͷ�����IP��ַ
				m_pSiteData->ReleaseInstrument(pInstrument->m_uiIP, m_iIPDistributeTime);
			}
			// �Ƿ�ը��������
			pInstrument->m_bBlastMachine = true;
			// ��������IP��ַ����ʱ��
			pInstrument->m_uiIPDistributeTime = m_iIPDistributeTime;	
			// ��ը�����������ʱ��
			pInstrument->m_uiBlastMachineTime = m_iIPDistributeTime;
			// ����IP��ַ
			pInstrument->m_uiIP = uiIP;
			// ��������IP��ַ������
			m_pSiteData->m_oIPInstrumentMap.AddInstrument(pInstrument->m_uiIP, pInstrument);
			// ���뱬ը������������������
			m_oInstrumentBlastMachineSNMap.SetAt(pInstrument->m_uiSN, pInstrument);
			// ��������IP��ַ���ö���
			m_pThreadProcIPSet->AddInstrumentForIPSet(pInstrument);
		}
		else	// �ϴη�����ȷ
		{
			// ��������IP��ַ����ʱ��
			pInstrument->m_uiIPDistributeTime = m_iIPDistributeTime;	
			// ��ը�����������ʱ��
			pInstrument->m_uiBlastMachineTime = m_iIPDistributeTime;
		}
	}
}

/**
* ������ڱ�ը�����������
* @param void
* @return bool true��û��Ҫ����Ĺ��ڱ�ǣ�false����Ҫ����Ĺ��ڱ��
*/
bool CThreadProcIPDistribute::ProcClearTimeOutBlastMachine()
{
	bool bReturn = true;

	POSITION pos = NULL;	// λ��	
	unsigned int uiSN;	// �����豸��
	CInstrument* pInstrument = NULL;	// ����
	pos = m_oInstrumentBlastMachineSNMap.GetStartPosition();
	while(NULL != pos)
	{
		m_oInstrumentBlastMachineSNMap.GetNextAssoc(pos, uiSN, pInstrument);
		if(pInstrument->m_uiBlastMachineTime != m_iIPDistributeTime)
		{
			// �жϣ�����IP��ַ��0������Ϊ�ɼ�վ���Ǳ��η���
			if((0 != pInstrument->m_uiIP) && (3 == pInstrument->m_uiInstrumentType) && (pInstrument->m_uiIPDistributeTime != m_iIPDistributeTime))
			{
				// �ͷ�����IP��ַ
				m_pSiteData->ReleaseInstrument(pInstrument->m_uiIP, m_iIPDistributeTime);
				// ����IP��ַ
				pInstrument->m_uiIP = 0;
				// ��������IP��ַ���ö���
				m_pThreadProcIPSet->AddInstrumentForIPSet(pInstrument);
				bReturn = false;
			}
			// �Ƿ�ը��������
			pInstrument->m_bBlastMachine = false;
			// ��������IP��ַ����ʱ��
			pInstrument->m_uiIPDistributeTime = 0;
			// ��ը�����������ʱ��
			pInstrument->m_uiBlastMachineTime = 0;
			m_oInstrumentBlastMachineSNMap.RemoveKey(uiSN);
		}
	}
	return bReturn;
}

/**
* �����ػص�IP��ַ����
* @param void
* @return bool true�����Լ������䣻false����ֹ����
*/
bool CThreadProcIPDistribute::ProcIPDistributeDetour()
{
	// �õ��ػص�����
	CDetourList* pDetourList = &m_pLogicData->m_oLayoutSetupData.m_oDetourList;
	// �ػص�ָ��Ϊ��
	CDetourData* pDetourData = NULL;
	// ѭ�������δ��������ػص�
	for(unsigned int i = 0; i < pDetourList->m_uiCountAll; i++)
	{
		// �õ��ػص�ָ��
		pDetourData = pDetourList->GetDetour(i);
		// ����һ���ػص�IP��ַ����
		ProcIPDistributeDetourOne(pDetourData);
	}
	// ��������ػص����
	return ProcClearTimeOutDetour();
}

/**
* ����һ���ػص�IP��ַ����
* @param CDetourData* pDetourData �ػص�ָ��
* @return void
*/
void CThreadProcIPDistribute::ProcIPDistributeDetourOne(CDetourData* pDetourData)
{	
	// �����ػص��Ͷ�����ָ��Ϊ��
	CInstrument* pInstrumentLow = NULL;
	// �����ػص��߶�����ָ��Ϊ��
	CInstrument* pInstrumentHigh= NULL;
	// ��������ָ��Ϊ��
	CInstrument* pInstrument = NULL;

	// �жϣ��ػص��Ͷ����������ӵ��ֳ�
	if(TRUE == m_pSiteData->GetInstrumentFromSNMapBySN(pDetourData->m_uiSNLow, pInstrumentLow))
	{
		// �жϣ��ϴ�������ȷ
		if((true == pInstrumentLow->m_bDetourMarkerLow) && (pInstrumentLow->m_uiStopMarking == pDetourData->m_uiStopMarking))
		{
			// �ػص����ʱ��
			pInstrumentLow->m_uiDetourLogoTime = m_iIPDistributeTime;
		}
		// ���øı�
		else
		{
			// �����Ƿ��ػص�ֹͣ���
			pInstrumentLow->m_uiStopMarking = pDetourData->m_uiStopMarking;
			// �����Ƿ��ػص��Ͷ˱�ǵ�
			pInstrumentLow->m_bDetourMarkerLow = true;
			// �����ػص����ʱ��
			pInstrumentLow->m_uiDetourLogoTime = m_iIPDistributeTime;
			// �����ػص��������������
			m_oInstrumentDetourLogoSNMap.SetAt(pInstrumentLow->m_uiSN, pInstrumentLow);
		}
	}
	// �ж��ػص��߶����������ӵ��ֳ�
	if(TRUE == m_pSiteData->GetInstrumentFromSNMapBySN(pDetourData->m_uiSNHigh, pInstrumentHigh))
	{
		// �ж��ϴ�������ȷ
		if((true == pInstrumentHigh->m_bDetourMarkerHigh) && (pInstrumentHigh->m_uiStopMarking == pDetourData->m_uiStopMarking))
		{
			// �����ػص����ʱ��
			pInstrumentHigh->m_uiDetourLogoTime = m_iIPDistributeTime;
		}
		// ���øı�
		else
		{
			// �����Ƿ��ػص�ֹͣ���
			pInstrumentHigh->m_uiStopMarking = pDetourData->m_uiStopMarking;
			// �����Ƿ��ػص��߶˱�ǵ�
			pInstrumentHigh->m_bDetourMarkerHigh= true;
			// �����ػص����ʱ��
			pInstrumentHigh->m_uiDetourLogoTime = m_iIPDistributeTime;
			// �����ػص��������������
			m_oInstrumentDetourLogoSNMap.SetAt(pInstrumentHigh->m_uiSN, pInstrumentHigh);
		}
	}
	// �ж��ػص��Ͷ����������ӵ��ֳ�,�ػص��߶�����δ���ӵ��ֳ�
	if((NULL != pInstrumentLow) && (NULL == pInstrumentHigh))
	{
		// ��������ָ��ָ��Ͷ�����������������
		pInstrument = pInstrumentLow->m_pInstrumentRight;
		// �߶˷������ӵ������������ҷ���Ϊ�ػص�
		// ѭ����ֱ������ָ��Ϊ��
		while(true)
		{
			// �ж�����ָ��Ϊ��
			if(NULL == pInstrument)
			{
				break;
			}
			// ����һ���������ػص�IP��ַ����
			ProcIPDistributeDetourOneInstrument(pInstrument);
			// �õ��ұ����ӵ�����
			pInstrument = pInstrument->m_pInstrumentRight;
		}
	}

	// �ػص��Ͷ�����δ���ӵ��ֳ�,�ػص��߶����������ӵ��ֳ�
	if((NULL == pInstrumentLow) && (NULL != pInstrumentHigh))
	{
		// ��������ָ��ָ��߶�����������������
		pInstrument = pInstrumentHigh->m_pInstrumentLeft;
		// �Ͷ˷������ӵ������������󷽣�Ϊ�ػص�
		// ѭ����ֱ������ָ��Ϊ��
		while(true)
		{
			// �ж�����ָ��Ϊ��
			if(NULL == pInstrument)
			{
				break;
			}
			// ����һ���������ػص�IP��ַ����
			ProcIPDistributeDetourOneInstrument(pInstrument);
			// �õ�������ӵ�����
			pInstrument = pInstrument->m_pInstrumentLeft;
		}
	}

	// �ػص��Ͷ����������ӵ��ֳ�,�ػص��߶����������ӵ��ֳ�
	if((NULL != pInstrumentLow) && (NULL != pInstrumentHigh))
	{
		// ��������ָ��ָ��Ͷ�����������������
		pInstrument = pInstrumentLow->m_pInstrumentRight;
		// �Ͷ˺͸߶��ʼ����ӵ���������Ϊ�ػص�
		// ѭ����ֱ������ָ��Ϊ�գ�������ָ��ָ��߶�����
		while(true)
		{
			// �ж�����ָ��Ϊ��
			if(NULL == pInstrument)
			{
				break;
			}
			// �ж�����ָ��ָ��߶�����
			if(pInstrumentHigh == pInstrument)
			{
				break;
			}
			// ����һ���������ػص�IP��ַ����
			ProcIPDistributeDetourOneInstrument(pInstrument);
			// �õ��ұ����ӵ�����
			pInstrument = pInstrument->m_pInstrumentRight;
		}
	}
}

/**
* ����һ���������ػص�IP��ַ����
* @param CInstrument* pInstrument ����ָ��
* @return void
*/
void CThreadProcIPDistribute::ProcIPDistributeDetourOneInstrument(CInstrument* pInstrument)
{
	// �жϣ�����δ����IP��ַ
	if(0 == pInstrument->m_uiIP)
	{
		// �Ƿ��ػص�
		pInstrument->m_bDetour = true;
		// ��������IP��ַ����ʱ��
		pInstrument->m_uiIPDistributeTime = m_iIPDistributeTime;
		// �ػص����ʱ��
		pInstrument->m_uiDetourTime = m_iIPDistributeTime;
		// �õ��ػص�����IP��ַ
		pInstrument->m_uiIP = m_pSiteData->m_oIPList.GetDetourIP();
		// ��������IP��ַ������
		m_pSiteData->m_oIPInstrumentMap.AddInstrument(pInstrument->m_uiIP, pInstrument);
		// �����ػص�����������
		m_oInstrumentDetourSNMap.SetAt(pInstrument->m_uiSN, pInstrument);
		// ��������IP��ַ���ö���
		m_pThreadProcIPSet->AddInstrumentForIPSet(pInstrument);
	}
	// ������IP��ַ
	else
	{
		// �жϣ��ϴ�������Ϊ�ػص�
		if(true == pInstrument->m_bDetour)
		{
			// ��������IP��ַ����ʱ��
			pInstrument->m_uiIPDistributeTime = m_iIPDistributeTime;
			// �ػص����ʱ��
			pInstrument->m_uiDetourTime = m_iIPDistributeTime;
		}
		// �ϴβ�������Ϊ�ػص�
		else
		{
			// �жϣ�����Ϊ�ɼ�վ���Ǳ��η���
			if((3 == pInstrument->m_uiInstrumentType) && (pInstrument->m_uiIPDistributeTime != m_iIPDistributeTime))
			{
				// �ͷ�����IP��ַ
				m_pSiteData->ReleaseInstrument(pInstrument->m_uiIP, m_iIPDistributeTime);
			}
			// �Ƿ��ػص�
			pInstrument->m_bDetour = true;
			// ��������IP��ַ����ʱ��
			pInstrument->m_uiIPDistributeTime = m_iIPDistributeTime;
			// �ػص����ʱ��
			pInstrument->m_uiDetourTime = m_iIPDistributeTime;
			// �õ��ػص�����IP��ַ
			pInstrument->m_uiIP = m_pSiteData->m_oIPList.GetDetourIP();
			// ��������IP��ַ������
			m_pSiteData->m_oIPInstrumentMap.AddInstrument(pInstrument->m_uiIP, pInstrument);
			// �����ػص�����������
			m_oInstrumentDetourSNMap.SetAt(pInstrument->m_uiSN, pInstrument);
			// ��������IP��ַ���ö���
			m_pThreadProcIPSet->AddInstrumentForIPSet(pInstrument);
		}
	}
}

/**
* ��������ػص����
* @param void
* @return bool true��û��Ҫ����Ĺ��ڱ�ǣ�false����Ҫ����Ĺ��ڱ��
*/
bool CThreadProcIPDistribute::ProcClearTimeOutDetour()
{
	bool bReturn = true;

	POSITION pos = NULL;	// λ��	
	unsigned int uiSN;	// �����豸��
	CInstrument* pInstrument = NULL;	// ����

	pos = m_oInstrumentDetourLogoSNMap.GetStartPosition();
	while(NULL != pos)
	{
		m_oInstrumentDetourLogoSNMap.GetNextAssoc(pos, uiSN, pInstrument);
		if(pInstrument->m_uiDetourLogoTime != m_iIPDistributeTime)
		{
			// �Ƿ��ػص��Ͷ˱�ǵ�
			pInstrument->m_bDetourMarkerLow = false;
			// �Ƿ��ػص��߶˱�ǵ�
			pInstrument->m_bDetourMarkerHigh= false;
			// �Ƿ��ػص�ֹͣ���
			pInstrument->m_uiStopMarking = 0;
			// �ػص����ʱ��
			pInstrument->m_uiDetourLogoTime = 0;
			m_oInstrumentDetourLogoSNMap.RemoveKey(uiSN);
		}
	}

	pos = m_oInstrumentDetourSNMap.GetStartPosition();
	while(NULL != pos)
	{
		m_oInstrumentDetourSNMap.GetNextAssoc(pos, uiSN, pInstrument);
		if(pInstrument->m_uiDetourTime != m_iIPDistributeTime)
		{
			// �жϣ�����IP��ַ��0������Ϊ�ɼ�վ���Ǳ��η���
			if((0 != pInstrument->m_uiIP) && (3 == pInstrument->m_uiInstrumentType) && (pInstrument->m_uiIPDistributeTime != m_iIPDistributeTime))
			{
				// �ͷ�����IP��ַ
				m_pSiteData->ReleaseInstrument(pInstrument->m_uiIP, m_iIPDistributeTime);
				// ����IP��ַ
				pInstrument->m_uiIP = 0;
				// ��������IP��ַ���ö���
				m_pThreadProcIPSet->AddInstrumentForIPSet(pInstrument);
				bReturn = false;
			}
			// �Ƿ��ػص�
			pInstrument->m_bDetour = false;
			// ��������IP��ַ����ʱ��
			pInstrument->m_uiIPDistributeTime = 0;
			// �ػص����ʱ��
			pInstrument->m_uiDetourTime = 0;
			m_oInstrumentDetourSNMap.RemoveKey(uiSN);
		}
	}
	return bReturn;
}

/**
* �����ǵ�IP��ַ����
* @param void
* @return void
*/
void CThreadProcIPDistribute::ProcIPDistributeMarker()
{
	// �õ���ǵ����
	CMarkerList* pMarkerList = &m_pLogicData->m_oLayoutSetupData.m_oMarkerList;
	// ���ñ�ǵ�Ϊ��
	CMarkerData* pMarkerData = NULL;
	// ѭ�������δ���ÿ����ǵ�
	for(unsigned int i = 0; i < pMarkerList->m_uiCountAll; i++)
	{
		// �õ���ǵ�
		pMarkerData = pMarkerList->GetMarker(i);
		// ��������ǵ�IP��ַ����
		ProcIPDistributeMarkerOne(pMarkerData);
	}
	// ������ڲɼ������
	ProcClearTimeOutMarker();
}

/**
* ��������ǵ�IP��ַ����
* @param CMarkerData* pMarkerData ��ǵ�ָ��
* @return void
*/
void CThreadProcIPDistribute::ProcIPDistributeMarkerOne(CMarkerData* pMarkerData)
{
	// �жϱ�ǵ��Ƿ����������˳��
	if(0 == pMarkerData->m_uiReversed)
	{
		// ��������ǵ�IP��ַ���䣬����˳��
		ProcIPDistributeMarkerOneNormal(pMarkerData);
	}
	// �жϱ�ǵ��Ƿ��Ƿ�ת���˳��
	else if(1 == pMarkerData->m_uiReversed)
	{
		// ��������ǵ�IP��ַ���䣬��ת˳��
		ProcIPDistributeMarkerOneReversed(pMarkerData);
	}
}

/**
* ��������ǵ�IP��ַ���䣬����˳��
* @param CMarkerData* pMarkerData ��ǵ�ָ��
* @return void
*/
void CThreadProcIPDistribute::ProcIPDistributeMarkerOneNormal(CMarkerData* pMarkerData)
{
	// ���ñ�ǵ�����ָ��Ϊ��
	CInstrument* pInstrumentMarker = NULL;
	// ���ñ�ǵ���ָ��Ϊ��
	CChannelSetupData* pChannelMarker = NULL;
	// �жϱ�ǵ�δ���ӵ��ֳ�
	if(TRUE != m_pSiteData->GetInstrumentFromSNMapBySN(pMarkerData->m_uiSN, pInstrumentMarker))
	{
		return;
	}
	// �жϣ��ϴ�������Ϊ��ǵ�
	if(true == pInstrumentMarker->m_bMarker)
	{
		// ��ǵ���ʱ��
		pInstrumentMarker->m_uiMarkerLogoTime = m_iIPDistributeTime;
	}
	// �жϣ��ϴβ�������Ϊ��ǵ�
	else
	{
		// �Ƿ��ǵ�
		pInstrumentMarker->m_bMarker = true;
		// ��ǵ���ʱ��
		pInstrumentMarker->m_uiMarkerLogoTime = m_iIPDistributeTime;
		// ����ɼ����������������
		m_oInstrumentMarkerLogoSNMap.SetAt(pInstrumentMarker->m_uiSN, pInstrumentMarker);
	}

	// ���òɼ�վָ��Ϊ��
	CInstrument* pInstrumentCollect = NULL;
	// ���ò��ָ��Ϊ��
	CChannelSetupData* pChannel = NULL;
	// ����õ��ɼ�վ
	pInstrumentCollect = m_pSiteData->GetInstrumentCollect(pInstrumentMarker, 3);
	// �жϲɼ�վָ�벻Ϊ��
	if(NULL != pInstrumentCollect)
	{
		// �õ����
		pChannelMarker = m_pLogicData->m_oSurveySetupData.GetChannel(pMarkerData->m_uiLineName, pMarkerData->m_uiPointNb, pMarkerData->m_uiChannelNb);
		// �жϲ��ָ�벻Ϊ��
		if(NULL != pChannelMarker)
		{
			// �������ɼ�վIP��ַ����
			ProcIPDistributeMarkerOneInstrument(pInstrumentCollect, pChannelMarker);
			// �жϣ����ػص��߶˱�ǵ㣬����ػص�ֹͣ���
			if((false == pInstrumentCollect->m_bDetourMarkerHigh) || (0 == pInstrumentCollect->m_uiStopMarking))
			{
				// �õ����
				CPointSetupData* pPoint = m_pLogicData->m_oSurveySetupData.GetPoint(pChannelMarker->m_uiIndexPoint);
				// �жϱ���㱾��������в��
				if(pPoint->m_pChannelHead != pChannelMarker)
				{
					// ������䱾����������
					 CInstrument* pInstrumentLeft = ProcIPDistributeMarkerOnePointLeft(pPoint, pInstrumentCollect->m_pInstrumentLeft, pChannelMarker->m_pChannelLeft);
					 // �ж�������ָ�벻Ϊ��
					if(NULL != pInstrumentLeft)
					 {
						 // ���������ͷ��򣬵õ��������ڵ�
						 pPoint = m_pLogicData->m_oSurveySetupData.GetPointByIncrementAndDirection(pPoint, pMarkerData->m_uiMarkerIncr, 3);
						 // �������η�����IP��ַ
						 ProcIPDistributeMarkerPointLeft(pPoint, pInstrumentLeft->m_pInstrumentLeft, pMarkerData->m_uiMarkerIncr);
					 }			
				}
				// ����㱾��������޲��
				else
				{
					// ���������ͷ��򣬵õ��������ڵ�
					pPoint = m_pLogicData->m_oSurveySetupData.GetPointByIncrementAndDirection(pPoint, pMarkerData->m_uiMarkerIncr, 3);
					// �������η�����IP��ַ
					ProcIPDistributeMarkerPointLeft(pPoint, pInstrumentCollect->m_pInstrumentLeft, pMarkerData->m_uiMarkerIncr);			
				}
			}

			// �жϣ����ػص��Ͷ˱�ǵ㣬����ػص�ֹͣ���
			if((false == pInstrumentCollect->m_bDetourMarkerLow) || (0 == pInstrumentCollect->m_uiStopMarking))
			{
				// �õ����
				CPointSetupData* pPoint = m_pLogicData->m_oSurveySetupData.GetPoint(pChannelMarker->m_uiIndexPoint);
				// �жϱ���㱾��������в��
				if(pPoint->m_pChannelTail != pChannelMarker)
				{
					// ���ҷ��䱾����������
					CInstrument* pInstrumentRight = ProcIPDistributeMarkerOnePointRight(pPoint, pInstrumentCollect->m_pInstrumentRight, pChannelMarker->m_pChannelRight);
					// �ж�������ָ�벻Ϊ��
					if(NULL != pInstrumentRight)
					{
						// ���������ͷ��򣬵õ��������ڵ�
						pPoint = m_pLogicData->m_oSurveySetupData.GetPointByIncrementAndDirection(pPoint, pMarkerData->m_uiMarkerIncr, 4);
						// �������η�����IP��ַ
						ProcIPDistributeMarkerPointRight(pPoint, pInstrumentRight->m_pInstrumentRight, pMarkerData->m_uiMarkerIncr);
					}				
				}
				// ����㱾��������޲��
				else
				{
					// ���������ͷ��򣬵õ��������ڵ�
					pPoint = m_pLogicData->m_oSurveySetupData.GetPointByIncrementAndDirection(pPoint, pMarkerData->m_uiMarkerIncr, 4);
					// �������η�����IP��ַ
					ProcIPDistributeMarkerPointRight(pPoint, pInstrumentCollect->m_pInstrumentRight, pMarkerData->m_uiMarkerIncr);		
				}
			}
		}
		// ���Ϊ��
		else
		{
			// �õ�����
			CLineSetupData* pLine = m_pLogicData->m_oSurveySetupData.GetLine(pMarkerData->m_uiLineName);
			// �жϲ��߲�Ϊ��
			if(NULL != pLine)
			{
				// �õ����
				CPointSetupData* pPoint = pLine->m_pPointHead;
				// �������η�����IP��ַ
				ProcIPDistributeMarkerPointRight(pPoint, pInstrumentCollect->m_pInstrumentRight, pMarkerData->m_uiMarkerIncr);	
			}			
		}
	}
	// û���ҵ��ɼ�վ
	else
	{
		// ���ҵõ��ɼ�վ
		pInstrumentCollect = m_pSiteData->GetInstrumentCollect(pInstrumentMarker, 4);
		// �жϲɼ�վΪ��
		if(NULL == pInstrumentCollect)
		{
			return;
		}
		// �õ����
		pChannelMarker = m_pLogicData->m_oSurveySetupData.GetChannel(pMarkerData->m_uiLineName, pMarkerData->m_uiPointNb, pMarkerData->m_uiChannelNb);		
		// �жϱ�ǲ����Ϊ��
		if(NULL != pChannelMarker)
		{
			// ���ҵõ����
			pChannel = pChannelMarker->m_pChannelRight;
		}
		// �жϲ����Ϊ��
		if(NULL != pChannel)
		{
			// �������ɼ�վIP��ַ����
			ProcIPDistributeMarkerOneInstrument(pInstrumentCollect, pChannel);
			// �жϣ����ػص��Ͷ˱�ǵ㣬����ػص�ֹͣ���
			if((false == pInstrumentCollect->m_bDetourMarkerLow) || (0 == pInstrumentCollect->m_uiStopMarking))
			{
				// �õ����
				CPointSetupData* pPoint = m_pLogicData->m_oSurveySetupData.GetPoint(pChannel->m_uiIndexPoint);
				// �жϱ���㱾��������в��
				if(pPoint->m_pChannelTail != pChannel)
				{
					// ���ҷ��䱾����������
					CInstrument* pInstrumentRight = ProcIPDistributeMarkerOnePointRight(pPoint, pInstrumentCollect->m_pInstrumentRight, pChannel->m_pChannelRight);
					// �ж���������Ϊ��
					if(NULL != pInstrumentRight)
					{
						// ���������ͷ��򣬵õ��������ڵ�
						pPoint = m_pLogicData->m_oSurveySetupData.GetPointByIncrementAndDirection(pPoint, pMarkerData->m_uiMarkerIncr, 4);
						// �������η�����IP��ַ
						ProcIPDistributeMarkerPointRight(pPoint, pInstrumentRight->m_pInstrumentRight, pMarkerData->m_uiMarkerIncr);
					}				
				}
				// ����㱾��������޲��
				else
				{
					// ���������ͷ��򣬵õ��������ڵ�
					pPoint = m_pLogicData->m_oSurveySetupData.GetPointByIncrementAndDirection(pPoint, pMarkerData->m_uiMarkerIncr, 4);
					// �������η�����IP��ַ
					ProcIPDistributeMarkerPointRight(pPoint, pInstrumentCollect->m_pInstrumentRight, pMarkerData->m_uiMarkerIncr);		
				}
			}
		}
	}
}

/**
* ��������ǵ�IP��ַ���䣬��ת˳��
* @param CMarkerData* pMarkerData ��ǵ�ָ��
* @return void
*/
void CThreadProcIPDistribute::ProcIPDistributeMarkerOneReversed(CMarkerData* pMarkerData)
{
	CInstrument* pInstrumentMarker = NULL;	// ��ǵ�����	
	CChannelSetupData* pChannelMarker = NULL;	// ��ǵ���
	// ��ǵ�δ���ӵ��ֳ�
	if(TRUE != m_pSiteData->GetInstrumentFromSNMapBySN(pMarkerData->m_uiSN, pInstrumentMarker))
	{
		return;
	}
	// �жϣ��ϴ�������Ϊ��ǵ�
	if(true == pInstrumentMarker->m_bMarker)
	{
		// ��ǵ���ʱ��
		pInstrumentMarker->m_uiMarkerLogoTime = m_iIPDistributeTime;
	}
	// �жϣ��ϴβ�������Ϊ��ǵ�
	else
	{
		// �Ƿ��ǵ�
		pInstrumentMarker->m_bMarker = true;
		// ��ǵ���ʱ��
		pInstrumentMarker->m_uiMarkerLogoTime = m_iIPDistributeTime;
		// ����ɼ����������������
		m_oInstrumentMarkerLogoSNMap.SetAt(pInstrumentMarker->m_uiSN, pInstrumentMarker);
	}

	CInstrument* pInstrumentCollect = NULL;	// �ɼ�վ
	CChannelSetupData* pChannel = NULL;	// ���
	// ���ҵõ��ɼ�վ
	pInstrumentCollect = m_pSiteData->GetInstrumentCollect(pInstrumentMarker, 4);	
	if(NULL != pInstrumentCollect)	// �ҵ��ɼ�վ
	{
		// �õ����
		pChannelMarker = m_pLogicData->m_oSurveySetupData.GetChannel(pMarkerData->m_uiLineName, pMarkerData->m_uiPointNb, pMarkerData->m_uiChannelNb);
		// �����Ϊ��
		if(NULL != pChannelMarker)
		{
			// �������ɼ�վIP��ַ����
			ProcIPDistributeMarkerOneInstrument(pInstrumentCollect, pChannelMarker);
			// ���ػص��Ͷ˱�ǵ㣬����ػص�ֹͣ���
			if((false == pInstrumentCollect->m_bDetourMarkerLow) || (0 == pInstrumentCollect->m_uiStopMarking))
			{
				// ���
				CPointSetupData* pPoint = m_pLogicData->m_oSurveySetupData.GetPoint(pChannelMarker->m_uiIndexPoint);
				if(pPoint->m_pChannelHead != pChannelMarker)	// ����㱾��������в��
				{
					// ������䱾����������
					CInstrument* pInstrumentRight = ProcIPDistributeMarkerOnePointLeftReversed(pPoint, pInstrumentCollect->m_pInstrumentRight, pChannelMarker->m_pChannelLeft);
					if(NULL != pInstrumentRight)	// �ɹ�
					{
						// ���������ͷ��򣬵õ��������ڵ�
						pPoint = m_pLogicData->m_oSurveySetupData.GetPointByIncrementAndDirection(pPoint, pMarkerData->m_uiMarkerIncr, 3);
						// �������η�����IP��ַ
						ProcIPDistributeMarkerPointLeftReversed(pPoint, pInstrumentRight->m_pInstrumentRight, pMarkerData->m_uiMarkerIncr);
					}			
				}
				else	// ����㱾��������޲��
				{
					// ���������ͷ��򣬵õ��������ڵ�
					pPoint = m_pLogicData->m_oSurveySetupData.GetPointByIncrementAndDirection(pPoint, pMarkerData->m_uiMarkerIncr, 3);
					// �������η�����IP��ַ
					ProcIPDistributeMarkerPointLeftReversed(pPoint, pInstrumentCollect->m_pInstrumentRight, pMarkerData->m_uiMarkerIncr);			
				}
			}

			// ���ػص��߶˱�ǵ㣬����ػص�ֹͣ���
			if((false == pInstrumentCollect->m_bDetourMarkerHigh) || (0 == pInstrumentCollect->m_uiStopMarking))
			{
				// ���
				CPointSetupData* pPoint = m_pLogicData->m_oSurveySetupData.GetPoint(pChannelMarker->m_uiIndexPoint);
				if(pPoint->m_pChannelTail != pChannelMarker)	// ����㱾��������в��
				{
					// ���ҷ��䱾����������
					CInstrument* pInstrumentLeft = ProcIPDistributeMarkerOnePointRightReversed(pPoint, pInstrumentCollect->m_pInstrumentLeft, pChannelMarker->m_pChannelRight);
					if(NULL != pInstrumentLeft)	// �ɹ�
					{
						// ���������ͷ��򣬵õ��������ڵ�
						pPoint = m_pLogicData->m_oSurveySetupData.GetPointByIncrementAndDirection(pPoint, pMarkerData->m_uiMarkerIncr, 4);
						// �������η�����IP��ַ
						ProcIPDistributeMarkerPointRightReversed(pPoint, pInstrumentLeft->m_pInstrumentLeft, pMarkerData->m_uiMarkerIncr);
					}				
				}
				else	// ����㱾��������޲��
				{
					// ���������ͷ��򣬵õ��������ڵ�
					pPoint = m_pLogicData->m_oSurveySetupData.GetPointByIncrementAndDirection(pPoint, pMarkerData->m_uiMarkerIncr, 4);
					// �������η�����IP��ַ
					ProcIPDistributeMarkerPointRightReversed(pPoint, pInstrumentCollect->m_pInstrumentLeft, pMarkerData->m_uiMarkerIncr);		
				}
			}
		}
		else	// ���Ϊ��
		{
			// �õ�����
			CLineSetupData* pLine = m_pLogicData->m_oSurveySetupData.GetLine(pChannelMarker->m_uiNbLine);
			if(NULL != pLine)
			{
				// �õ����
				CPointSetupData* pPoint = pLine->m_pPointHead;
				// �������η�����IP��ַ
				ProcIPDistributeMarkerPointRightReversed(pPoint, pInstrumentCollect->m_pInstrumentLeft, pMarkerData->m_uiMarkerIncr);	
			}			
		}
	}
	else	// û���ҵ��ɼ�վ
	{
		// ����õ��ɼ�վ
		pInstrumentCollect = m_pSiteData->GetInstrumentCollect(pInstrumentMarker, 3);	
		if(NULL == pInstrumentCollect)	// �ɼ�վΪ��
		{
			return;
		}

		// �õ����
		pChannelMarker = m_pLogicData->m_oSurveySetupData.GetChannel(pMarkerData->m_uiLineName, pMarkerData->m_uiPointNb, pMarkerData->m_uiChannelNb);		
		if(NULL != pChannelMarker)	// �����Ϊ��
		{
			// ���ҵõ����
			pChannel = pChannelMarker->m_pChannelRight;	// ���
		}

		if(NULL != pChannel)	// �����Ϊ��
		{
			// �������ɼ�վIP��ַ����
			ProcIPDistributeMarkerOneInstrument(pInstrumentCollect, pChannel);
			// ���ػص��߶˱�ǵ㣬����ػص�ֹͣ���
			if((false == pInstrumentCollect->m_bDetourMarkerHigh) || (0 == pInstrumentCollect->m_uiStopMarking))
			{
				// ���
				CPointSetupData* pPoint = m_pLogicData->m_oSurveySetupData.GetPoint(pChannel->m_uiIndexPoint);
				if(pPoint->m_pChannelTail != pChannel)	// ����㱾��������в��
				{
					// ���ҷ��䱾����������
					CInstrument* pInstrumentLeft = ProcIPDistributeMarkerOnePointRightReversed(pPoint, pInstrumentCollect->m_pInstrumentLeft, pChannel->m_pChannelRight);
					if(NULL != pInstrumentLeft)	// �ɹ�
					{
						// ���������ͷ��򣬵õ��������ڵ�
						pPoint = m_pLogicData->m_oSurveySetupData.GetPointByIncrementAndDirection(pPoint, pMarkerData->m_uiMarkerIncr, 4);
						// �������η�����IP��ַ
						ProcIPDistributeMarkerPointRightReversed(pPoint, pInstrumentLeft->m_pInstrumentLeft, pMarkerData->m_uiMarkerIncr);
					}				
				}
				else	// ����㱾��������޲��
				{
					// ���������ͷ��򣬵õ��������ڵ�
					pPoint = m_pLogicData->m_oSurveySetupData.GetPointByIncrementAndDirection(pPoint, pMarkerData->m_uiMarkerIncr, 4);
					// �������η�����IP��ַ
					ProcIPDistributeMarkerPointRightReversed(pPoint, pInstrumentCollect->m_pInstrumentLeft, pMarkerData->m_uiMarkerIncr);		
				}
			}
		}
	}
}

/**
* �������ɼ�վIP��ַ����
* @param CInstrument* pInstrumentCollect �ɼ�վָ��
* @param CChannelSetupData* pChannel ���ָ��
* @return void
*/
void CThreadProcIPDistribute::ProcIPDistributeMarkerOneInstrument(CInstrument* pInstrumentCollect, CChannelSetupData* pChannel)
{
	if((NULL != pInstrumentCollect) && (NULL != pChannel))
	{
		// �жϣ�����δ�����IP��ַ
		if(0 == pInstrumentCollect->m_uiIP)
		{
			// ����IP��ַ
			pInstrumentCollect->m_uiIP = pChannel->m_uiIP;
			// �������ߺ�
			pInstrumentCollect->m_uiLineNb = pChannel->m_uiNbLine;
			// ��������
			pInstrumentCollect->m_uiPointNb = pChannel->m_uiNbPoint;
			// ���������
			pInstrumentCollect->m_uiChannelNb = pChannel->m_uiNbChannel;
			// �Ƿ����Ӽ첨��
			pInstrumentCollect->m_bSensor = true;
			// �Ƿ�������
			pInstrumentCollect->m_bJumpedChannel = pChannel->m_bJumped;
			// ��������IP��ַ����ʱ��
			pInstrumentCollect->m_uiIPDistributeTime = m_iIPDistributeTime;
			// ��ǵ���ʱ��
			pInstrumentCollect->m_uiMarkerTime = m_iIPDistributeTime;
			// �����豸��
			pChannel->m_uiSN = pInstrumentCollect->m_uiSN;
			// ����ɼ�������SN������
			m_oInstrumentMarkerSNMap.SetAt(pInstrumentCollect->m_uiSN, pInstrumentCollect);
			// ��������IP��ַ������
			m_pSiteData->m_oIPInstrumentMap.AddInstrument(pInstrumentCollect->m_uiIP, pInstrumentCollect);
			// ��������IP��ַ���ö���
			m_pThreadProcIPSet->AddInstrumentForIPSet(pInstrumentCollect);
			TRACE2("Marker IPSet SN��=%d IP=%d \r\n", pInstrumentCollect->m_uiSN,pInstrumentCollect->m_uiIP);
		}
		// �жϣ�������Ҫ��������IP��ַ
		else if(pChannel->m_uiIP != pInstrumentCollect->m_uiIP)
		{
			// �жϣ�����Ϊ�ɼ�վ���Ǳ��η���
			if((3 == pInstrumentCollect->m_uiInstrumentType) && (pInstrumentCollect->m_uiIPDistributeTime != m_iIPDistributeTime))
			{
				// �ͷ�����IP��ַ
				m_pSiteData->ReleaseInstrument(pInstrumentCollect->m_uiIP, m_iIPDistributeTime);
			}
			// ����IP��ַ
			pInstrumentCollect->m_uiIP = pChannel->m_uiIP;
			// �������ߺ�
			pInstrumentCollect->m_uiLineNb = pChannel->m_uiNbLine;
			// ��������
			pInstrumentCollect->m_uiPointNb = pChannel->m_uiNbPoint;
			// ���������
			pInstrumentCollect->m_uiChannelNb = pChannel->m_uiNbChannel;
			// �Ƿ����Ӽ첨��
			pInstrumentCollect->m_bSensor = true;
			// �Ƿ�������
			pInstrumentCollect->m_bJumpedChannel = pChannel->m_bJumped;
			// ��������IP��ַ����ʱ��
			pInstrumentCollect->m_uiIPDistributeTime = m_iIPDistributeTime;
			// ��ǵ���ʱ��
			pInstrumentCollect->m_uiMarkerTime = m_iIPDistributeTime;
			// �����豸��
			pChannel->m_uiSN = pInstrumentCollect->m_uiSN;
			// ����ɼ�������SN������
			m_oInstrumentMarkerSNMap.SetAt(pInstrumentCollect->m_uiSN, pInstrumentCollect);
			// ��������IP��ַ������
			m_pSiteData->m_oIPInstrumentMap.AddInstrument(pInstrumentCollect->m_uiIP, pInstrumentCollect);
			// ��������IP��ַ���ö���
			m_pThreadProcIPSet->AddInstrumentForIPSet(pInstrumentCollect);
			TRACE2("pChannel IPSet SN��=%d IP=%d \r\n", pInstrumentCollect->m_uiSN,pInstrumentCollect->m_uiIP);
		}
		else	// �ϴη�����ȷ
		{
			// ��������IP��ַ����ʱ��
			pInstrumentCollect->m_uiIPDistributeTime = m_iIPDistributeTime;
			// ��ǵ���ʱ��
			pInstrumentCollect->m_uiMarkerTime = m_iIPDistributeTime;
		}
	}
}

/**
* ���������IP��ַ���䣬�������
* @param CPointSetupData* pPoint ���ָ��
* @param CInstrument* pInstrumentCollect �ɼ�վָ��
* @param CChannelSetupData* pChannel ���ָ��
* @return void
*/
CInstrument* CThreadProcIPDistribute::ProcIPDistributeMarkerOnePointLeft(CPointSetupData* pPoint, CInstrument* pInstrument, CChannelSetupData* pChannel)
{
	CInstrument* pInstrumentCollect = pInstrument;
	CChannelSetupData* pChannelMarker = pChannel;

	while(true)
	{
		if(NULL == pInstrument)
		{
			return NULL;
		}
		if(NULL == pChannel)
		{
			return NULL;
		}
		pInstrumentCollect = m_pSiteData->GetInstrumentCollect(pInstrumentCollect, 3);
		if(NULL == pInstrumentCollect)
		{
			return NULL;
		}
		// �������ɼ�վIP��ַ����
		ProcIPDistributeMarkerOneInstrument(pInstrumentCollect, pChannelMarker);
		// �ػص��߶˱�ǵ㣬���ػص�ֹͣ���
		if((true == pInstrumentCollect->m_bDetourMarkerHigh) && (1 == pInstrumentCollect->m_uiStopMarking))
		{
			return NULL;
		}
		if(pPoint->m_pChannelHead == pChannelMarker)
		{
			return pInstrumentCollect;
		}
		pInstrumentCollect = pInstrumentCollect->m_pInstrumentLeft;
		pChannelMarker = pChannelMarker->m_pChannelLeft;
	}
	return NULL;
}

/**
* ���������IP��ַ���䣬���ҷ���
* @param CPointSetupData* pPoint ���ָ��
* @param CInstrument* pInstrumentCollect �ɼ�վָ��
* @param CChannelSetupData* pChannel ���ָ��
* @return void
*/
CInstrument* CThreadProcIPDistribute::ProcIPDistributeMarkerOnePointRight(CPointSetupData* pPoint, CInstrument* pInstrument, CChannelSetupData* pChannel)
{

	CInstrument* pInstrumentCollect = pInstrument;
	CChannelSetupData* pChannelMarker = pChannel;

	while(true)
	{
		if(NULL == pInstrument)
		{
			return NULL;
		}
		if(NULL == pChannel)
		{
			return NULL;
		}
		pInstrumentCollect = m_pSiteData->GetInstrumentCollect(pInstrumentCollect, 4);
		if(NULL == pInstrumentCollect)
		{
			return NULL;
		}
		// �������ɼ�վIP��ַ����
		ProcIPDistributeMarkerOneInstrument(pInstrumentCollect, pChannelMarker);
		// �ػص��Ͷ˱�ǵ㣬���ػص�ֹͣ���
		if((true == pInstrumentCollect->m_bDetourMarkerLow) && (1 == pInstrumentCollect->m_uiStopMarking))
		{
			return NULL;
		}
		if(pPoint->m_pChannelTail== pChannelMarker)
		{
			return pInstrumentCollect;
		}
		pInstrumentCollect = pInstrumentCollect->m_pInstrumentRight;
		pChannelMarker = pChannelMarker->m_pChannelRight;
	}
	return false;
}

/**
* ������IP��ַ���䣬�������
* @param CPointSetupData* pPoint ���ָ��
* @param CInstrument* pInstrumentCollect �ɼ�վָ��
* @param unsigned int uiIncrement �������
* @return void
*/
void CThreadProcIPDistribute::ProcIPDistributeMarkerPointLeft(CPointSetupData* pPoint, CInstrument* pInstrument, unsigned int uiIncrement)
{
	CInstrument* pInstrumentCollect = pInstrument;

	if(NULL == pInstrument)
	{
		return;
	}
	if(NULL == pPoint)
	{
		return;
	}

	pInstrumentCollect = ProcIPDistributeMarkerOnePointLeft(pPoint, pInstrumentCollect, pPoint->m_pChannelTail);
	if(NULL == pInstrumentCollect)
	{
		return;
	}
	// ���������ͷ��򣬵õ��������ڵ�
	pPoint = m_pLogicData->m_oSurveySetupData.GetPointByIncrementAndDirection(pPoint, uiIncrement, 3);
	// �������ɼ�վIP��ַ����
	ProcIPDistributeMarkerPointLeft(pPoint, pInstrumentCollect->m_pInstrumentLeft, uiIncrement);
}

/**
* ������IP��ַ���䣬���ҷ���
* @param CPointSetupData* pPoint ���ָ��
* @param CInstrument* pInstrumentCollect �ɼ�վָ��
* @param unsigned int uiIncrement �������
* @return void
*/
void CThreadProcIPDistribute::ProcIPDistributeMarkerPointRight(CPointSetupData* pPoint, CInstrument* pInstrument, unsigned int uiIncrement)
{
	CInstrument* pInstrumentCollect = pInstrument;

	if(NULL == pInstrument)
	{
		return;
	}
	if(NULL == pPoint)
	{
		return;
	}

	pInstrumentCollect = ProcIPDistributeMarkerOnePointRight(pPoint, pInstrumentCollect, pPoint->m_pChannelHead);
	if(NULL == pInstrumentCollect)
	{
		return;
	}
	// ���������ͷ��򣬵õ��������ڵ�
	pPoint = m_pLogicData->m_oSurveySetupData.GetPointByIncrementAndDirection(pPoint, uiIncrement, 4);
	// �������ɼ�վIP��ַ����
	ProcIPDistributeMarkerPointRight(pPoint, pInstrumentCollect->m_pInstrumentRight, uiIncrement);
}

/**
* ���������IP��ַ���䣬������䣬��ת
* @param CPointSetupData* pPoint ���ָ��
* @param CInstrument* pInstrumentCollect �ɼ�վָ��
* @param CChannelSetupData* pChannel ���ָ��
* @return void
*/
CInstrument* CThreadProcIPDistribute::ProcIPDistributeMarkerOnePointLeftReversed(CPointSetupData* pPoint, CInstrument* pInstrument, CChannelSetupData* pChannel)
{
	CInstrument* pInstrumentCollect = pInstrument;
	CChannelSetupData* pChannelMarker = pChannel;

	while(true)
	{
		if(NULL == pInstrument)
		{
			return NULL;
		}
		if(NULL == pChannel)
		{
			return NULL;
		}
		pInstrumentCollect = m_pSiteData->GetInstrumentCollect(pInstrumentCollect, 4);
		if(NULL == pInstrumentCollect)
		{
			return NULL;
		}
		// �������ɼ�վIP��ַ����
		ProcIPDistributeMarkerOneInstrument(pInstrumentCollect, pChannelMarker);
		// �ػص��Ͷ˱�ǵ㣬���ػص�ֹͣ���
		if((true == pInstrumentCollect->m_bDetourMarkerLow) && (1 == pInstrumentCollect->m_uiStopMarking))
		{
			return NULL;
		}
		if(pPoint->m_pChannelHead == pChannelMarker)
		{
			return pInstrumentCollect;
		}
		pInstrumentCollect = pInstrumentCollect->m_pInstrumentRight;
		pChannelMarker = pChannelMarker->m_pChannelLeft;
	}
	return NULL;
}

/**
* ���������IP��ַ���䣬���ҷ��䣬��ת
* @param CPointSetupData* pPoint ���ָ��
* @param CInstrument* pInstrumentCollect �ɼ�վָ��
* @param CChannelSetupData* pChannel ���ָ��
* @return void
*/
CInstrument* CThreadProcIPDistribute::ProcIPDistributeMarkerOnePointRightReversed(CPointSetupData* pPoint, CInstrument* pInstrument, CChannelSetupData* pChannel)
{

	CInstrument* pInstrumentCollect = pInstrument;
	CChannelSetupData* pChannelMarker = pChannel;

	while(true)
	{
		if(NULL == pInstrument)
		{
			return NULL;
		}
		if(NULL == pChannel)
		{
			return NULL;
		}
		pInstrumentCollect = m_pSiteData->GetInstrumentCollect(pInstrumentCollect, 3);
		if(NULL == pInstrumentCollect)
		{
			return NULL;
		}
		// �������ɼ�վIP��ַ����
		ProcIPDistributeMarkerOneInstrument(pInstrumentCollect, pChannelMarker);
		// �ػص��߶˱�ǵ㣬���ػص�ֹͣ���
		if((true == pInstrumentCollect->m_bDetourMarkerHigh) && (1 == pInstrumentCollect->m_uiStopMarking))
		{
			return NULL;
		}
		if(pPoint->m_pChannelTail== pChannelMarker)
		{
			return pInstrumentCollect;
		}
		pInstrumentCollect = pInstrumentCollect->m_pInstrumentLeft;
		pChannelMarker = pChannelMarker->m_pChannelRight;
	}
	return false;
}

/**
* ������IP��ַ���䣬������䣬��ת
* @param CPointSetupData* pPoint ���ָ��
* @param CInstrument* pInstrumentCollect �ɼ�վָ��
* @param unsigned int uiIncrement �������
* @return void
*/
void CThreadProcIPDistribute::ProcIPDistributeMarkerPointLeftReversed(CPointSetupData* pPoint, CInstrument* pInstrument, unsigned int uiIncrement)
{
	CInstrument* pInstrumentCollect = pInstrument;

	if(NULL == pInstrument)
	{
		return;
	}
	if(NULL == pPoint)
	{
		return;
	}

	pInstrumentCollect = ProcIPDistributeMarkerOnePointLeftReversed(pPoint, pInstrumentCollect, pPoint->m_pChannelTail);
	if(NULL == pInstrumentCollect)
	{
		return;
	}
	// ���������ͷ��򣬵õ��������ڵ�
	pPoint = m_pLogicData->m_oSurveySetupData.GetPointByIncrementAndDirection(pPoint, uiIncrement, 3);
	// �������ɼ�վIP��ַ����
	ProcIPDistributeMarkerPointLeftReversed(pPoint, pInstrumentCollect->m_pInstrumentRight, uiIncrement);
}

/**
* ������IP��ַ���䣬���ҷ��䣬��ת
* @param CPointSetupData* pPoint ���ָ��
* @param CInstrument* pInstrumentCollect �ɼ�վָ��
* @param unsigned int uiIncrement �������
* @return void
*/
void CThreadProcIPDistribute::ProcIPDistributeMarkerPointRightReversed(CPointSetupData* pPoint, CInstrument* pInstrument, unsigned int uiIncrement)
{
	CInstrument* pInstrumentCollect = pInstrument;

	if(NULL == pInstrument)
	{
		return;
	}
	if(NULL == pPoint)
	{
		return;
	}

	pInstrumentCollect = ProcIPDistributeMarkerOnePointRightReversed(pPoint, pInstrumentCollect, pPoint->m_pChannelHead);
	if(NULL == pInstrumentCollect)
	{
		return;
	}
	// ���������ͷ��򣬵õ��������ڵ�
	pPoint = m_pLogicData->m_oSurveySetupData.GetPointByIncrementAndDirection(pPoint, uiIncrement, 4);
	// �������ɼ�վIP��ַ����
	ProcIPDistributeMarkerPointRightReversed(pPoint, pInstrumentCollect->m_pInstrumentLeft, uiIncrement);
}

/**
* ������ڲɼ������
* @param void
* @return bool true��û��Ҫ����Ĺ��ڱ�ǣ�false����Ҫ����Ĺ��ڱ��
*/
bool CThreadProcIPDistribute::ProcClearTimeOutMarker()
{
	bool bReturn = true;

	POSITION pos = NULL;	// λ��	
	unsigned int uiSN;	// �����豸��
	CInstrument* pInstrument = NULL;	// ����

	pos = m_oInstrumentMarkerLogoSNMap.GetStartPosition();
	while(NULL != pos)
	{
		m_oInstrumentMarkerLogoSNMap.GetNextAssoc(pos, uiSN, pInstrument);
		if(pInstrument->m_uiMarkerLogoTime != m_iIPDistributeTime)
		{
			// �Ƿ�ɼ���
			pInstrument->m_bMarker = false;
			// �ɼ������ʱ��
			pInstrument->m_uiMarkerLogoTime = 0;
			m_oInstrumentMarkerLogoSNMap.RemoveKey(uiSN);
		}
	}

	pos = m_oInstrumentMarkerSNMap.GetStartPosition();
	while(NULL != pos)
	{
		m_oInstrumentMarkerSNMap.GetNextAssoc(pos, uiSN, pInstrument);
		if(pInstrument->m_uiMarkerTime != m_iIPDistributeTime)
		{
			// �жϣ�����IP��ַ��0������Ϊ�ɼ�վ���Ǳ��η���
			if((0 != pInstrument->m_uiIP) && (3 == pInstrument->m_uiInstrumentType) && (pInstrument->m_uiIPDistributeTime != m_iIPDistributeTime))
			{
				// �ͷ�����IP��ַ
				m_pSiteData->ReleaseInstrument(pInstrument->m_uiIP, m_iIPDistributeTime);
				// ����IP��ַ
				pInstrument->m_uiIP = 0;
				// ��������IP��ַ���ö���
				m_pThreadProcIPSet->AddInstrumentForIPSet(pInstrument);
				bReturn = false;
			}
			// ����IP��ַ
			pInstrument->m_uiIP = 0;
			// ��������IP��ַ���ö���
			m_pThreadProcIPSet->AddInstrumentForIPSet(pInstrument);
			// �������ߺ�
			pInstrument->m_uiLineNb = 0;
			// ��������
			pInstrument->m_uiPointNb = 0;
			// ���������
			pInstrument->m_uiChannelNb = 0;
			// �Ƿ����Ӽ첨��
			pInstrument->m_bSensor = false;
			// �Ƿ�������
			pInstrument->m_bJumpedChannel = false;
			// ��������IP��ַ����ʱ��
			pInstrument->m_uiIPDistributeTime = 0;
			// �ɼ������ʱ��
			pInstrument->m_uiMarkerTime = 0;
			m_oInstrumentMarkerSNMap.RemoveKey(uiSN);
		}
	}
	return bReturn;
}

