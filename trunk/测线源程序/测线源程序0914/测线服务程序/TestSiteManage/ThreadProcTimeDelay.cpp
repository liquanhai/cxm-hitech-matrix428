// ThreadProcTimeDelay.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "TestSiteManage.h"
#include "ThreadProcTimeDelay.h"
#include "Matrixline.h"

// CThreadProcTimeDelay

IMPLEMENT_DYNCREATE(CThreadProcTimeDelay, CWinThread)

CThreadProcTimeDelay::CThreadProcTimeDelay()
{
	// �Ƿ���״̬
	m_bWork = false;
	// �Ƿ�ر��߳�
	m_bClose = false;
	// �Ƿ����״̬
	m_bFree = true;
}

CThreadProcTimeDelay::~CThreadProcTimeDelay()
{
}

BOOL CThreadProcTimeDelay::InitInstance()
{
	// TODO: �ڴ�ִ���������̳߳�ʼ��
	return TRUE;
}

int CThreadProcTimeDelay::ExitInstance()
{
	// TODO: �ڴ�ִ���������߳�����
	return CWinThread::ExitInstance();
}

BEGIN_MESSAGE_MAP(CThreadProcTimeDelay, CWinThread)
END_MESSAGE_MAP()

// CThreadProcTimeDelay ��Ϣ�������

/**
* �߳�������
* @param void
* @return int
*/
int CThreadProcTimeDelay::Run()
{
	// ѭ����ֱ���رձ�־Ϊ��
	while(true)
	{
		// �жϹرձ�־�Ƿ�Ϊ��
		if(true == m_bClose)
		{
			break;
		}
		// ʱ����������
		ProcTimeDelay();
		// �жϹرձ�־�Ƿ�Ϊ��
		if(true == m_bClose)
		{
			break;
		}
		// �Ƿ����״̬
		m_bFree = true;
		// �����߳�
		this->SuspendThread();
		// �Ƿ����״̬
		m_bFree = false;
	}
	// ��������ʱ�Ӵ����̹߳رձ�־Ϊ��
	m_pSiteData->m_bProcTimeDelayClose = true;
	// ����
	return CWinThread::Run();
}

/**
* ��ʼ���߳�
* @param void
* @return bool true���ɹ���false��ʧ��
*/
bool CThreadProcTimeDelay::OnInit()
{
	// �Ƿ���״̬
	m_bWork = false;
	// �Ƿ�ر��߳�
	m_bClose = false;
	// �Ƿ����״̬
	m_bFree = true;
	itmp=0;
	times_Delay=0;
	ifrist=0;
	return true;
}

/**
* �ر��߳�
* @param void
* @return bool true���ɹ���false��ʧ��
*/
bool CThreadProcTimeDelay::OnClose()
{
	// �Ƿ�ر��߳�
	m_bClose = true;
	// �Ƿ����״̬
	if(true == m_bFree)
	{
		// ����ʱ�Ӵ���
		ResumeProcTimeDelay();
	}
	return true;
}

/**
* �߳̿�ʼ����
* @param void
* @return bool true���ɹ���false��ʧ��
*/
bool CThreadProcTimeDelay::OnWork()
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
bool CThreadProcTimeDelay::OnStop()
{
	// �Ƿ���״̬
	m_bWork = false;
	return true;
}

/**
* �ж��Ƿ���Դ��������
* @param void
* @return bool true����������false��ֹͣ����
*/
bool CThreadProcTimeDelay::JudgeProcCondition()
{	
	// �ǹ���״̬
	if(false == m_bWork)
	{		
		m_pSiteData->m_bProcTimeDelayStop = true;	// ����ʱ�Ӵ����߳�ֹͣ
		return false;
	}
	else
	{
		m_pSiteData->m_bProcTimeDelayStop = false;	// ����ʱ�Ӵ����̹߳���
	}
	return true;
}

/**
* �ж��߳��Ƿ����
* @param void
* @return bool true���ǣ�false����
*/
bool CThreadProcTimeDelay::IsThreadFree()
{
	return m_bFree;
}

/**
* �����߳�
* @param void
* @return void
*/
void CThreadProcTimeDelay::ResumeProcTimeDelay()
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
* ������Ҫ����ʱ��������·��
* @param CRout* pRout ·��ָ��
* @return void
*/
void CThreadProcTimeDelay::SetRout(CRout* pRout)
{
	m_pRout = pRout;
}

/**
* ʱ����������
* @param void
* @return void
*/
void CThreadProcTimeDelay::ProcTimeDelay()
{
	// �жϣ����ܼ�������
	if(false == JudgeProcCondition())
	{
		return;
	}

/*	if(times_Delay>5)
		return;
	times_Delay++;
*/
	// �õ���Ҫʱ��������������������к�������
	GetInstrumentForTailTimeQuery();
	// �жϣ�ֻ��һ������
	if(1 == m_olsInstrument.GetCount())
	{
		return;
	}
	// ����β��ʱ�̲�ѯӦ��֡������ջ�����
	m_pSocketTailTimeFrame->RemoveFrameDataAll();
	Calc_skip=0;
	// ����β��ʱ�̲�ѯ
	if(ProcTailTimeQuery()==false){
		CString strDesc;
		strDesc.Format("RoutIP=%d", m_pRout->m_uiRoutIP);
		// ��������״̬����
		m_pSiteData->m_oRunTimeDataList.Set(1, "CThreadProcTimeDelay", "ProcTimeDelay 1 find wait fail", strDesc);
		return;
	}
	// �жϣ����ܼ�������
	if(false == JudgeProcCondition())
	{
		return;
	}
	if(Calc_skip!=0){
		CString strDesc;
		strDesc.Format("RoutIP=%d", m_pRout->m_uiRoutIP);
		// ��������״̬����
		m_pSiteData->m_oRunTimeDataList.Set(1, "CThreadProcTimeDelay", "ProcTimeDelay 2 find wait fail", strDesc);
		return;
	}
	//m_pSiteData->Calc_skip=Calc_skip;
	// ����ʱ��
	//ProcTimeDelayCalculate();
	if(ProcTimeDelayCalculate_sys()==false){
		CString strDesc;
		strDesc.Format("RoutIP=%d", m_pRout->m_uiRoutIP);
		// ��������״̬����
		m_pSiteData->m_oRunTimeDataList.Set(1, "CThreadProcTimeDelay", "ProcTimeDelay 3 find wait fail", strDesc);
		return;
		}		
	// ����ʱ��
	ProcTimeDelaySet();

	CString strDesc;
	strDesc.Format("RoutIP=%d", m_pRout->m_uiRoutIP);
	// ��������״̬����
	m_pSiteData->m_oRunTimeDataList.Set(1, "CThreadProcTimeDelay", "ProcTimeDelay", strDesc);
}

/**
* �õ���Ҫʱ��������������������к�������
* @param void
* @return void
*/
void CThreadProcTimeDelay::GetInstrumentForTailTimeQuery()
{
	// �����������
	m_olsInstrument.RemoveAll();
	// �������������
	m_oInstrumentMap.RemoveAll();

	// ��Ҫ����ʱ�����������������������к�������
	CInstrument* pInstrument = m_pRout->m_pHead;
	while(true)
	{
		// �ڼ���β��ʱ�̲�ѯ
		pInstrument->m_iTailTimeQueryCount = 0;
		// β��ʱ�̲�ѯ�Ƿ�ɹ�
		pInstrument->m_bTailTimeQueryOK = false;
		// �ڼ�����������ʱ��
		pInstrument->m_iTimeSetCount = 0;
		// ����ʱ�������Ƿ�ɹ�
		pInstrument->m_bTimeSetOK = false;	
		// �������
		m_olsInstrument.AddTail(pInstrument);
		// ����������
		m_oInstrumentMap.SetAt(pInstrument->m_uiIP, pInstrument);
		// �õ���һ����
		pInstrument = GetNextInstrument(pInstrument);
		// ����һ��������
		if(NULL == pInstrument)
		{
			break;
		}
	}
}

/**
* �õ�������·�ɷ��������ӵ���һ������
* @param CInstrument* pInstrument ����ָ��
* @return CInstrument* ���ӵ���һ������ NULL������������
*/
CInstrument* CThreadProcTimeDelay::GetNextInstrument(CInstrument* pInstrument)
{
	CInstrument* pInstrumentNext = NULL;

	// ·���������һ������
	if(m_pRout->m_pTail == pInstrument)
	{
		return NULL;
	}
	// �õ�·�ɷ������һ������
	pInstrumentNext = pInstrument->GetNextInstrument(m_pRout->m_uiRoutDirection);
	// ��һ����������
	if(NULL != pInstrumentNext)
	{
		// ��һ������û������IP��ַ
		if(0 == pInstrumentNext->m_uiIP)
		{
			pInstrumentNext = NULL;
		}
	}
	return pInstrumentNext;
}

/**
* ����������β��ʱ�̲�ѯ֡
* @param void
* @return void
*/
void CThreadProcTimeDelay::SendTailTimeFrame()
{	
	CInstrument* pInstrument = NULL;	// ����	
	POSITION pos = NULL;	// λ��	
	unsigned int uiKey;	// ������
	int count=0;

	CString strDesc;
	strDesc.Format("SendTailTimeFrame"); 
	//m_pSiteData->m_oRunTimeDataList.Set(3, "CThreadProcTimeDelay", "SendTailTimeFrame", strDesc);

	// �õ���������ʼ����λ��
	pos = m_oInstrumentMap.GetStartPosition();
	while(NULL != pos)
	{
		pInstrument = NULL;
		// �õ�����
		m_oInstrumentMap.GetNextAssoc(pos, uiKey, pInstrument);
		if(NULL != pInstrument)	// �õ�����
		{
			if(pInstrument->m_uiInstrumentType==1){	
				// ��������β��ʱ�̲�ѯ֡
				m_pSocketTailTimeFrame->MakeFrameData(pInstrument);
				// ��������β��ʱ�̲�ѯ֡
				m_pSocketTailTimeFrame->SendTailTimeFrame();
				count=count|0x1;
			}
			else{
				if((count&0x2)==0){
					count=count|0x2;
					// ��������β��ʱ�̲�ѯ֡
					m_pSocketTailTimeFrame->MakeFrameData(pInstrument);
					// ��������β��ʱ�̲�ѯ֡
					m_pSocketTailTimeFrame->SendTailTimeFrame();
				}
			}
			if(count==0x3)
				break;
		}
	}

	/*
	// �õ���������ʼ����λ��
	pos = m_oInstrumentMap.GetStartPosition();
	// ��ǰλ��������
	while(NULL != pos)
	{
		pInstrument = NULL;
		// �õ�����
		m_oInstrumentMap.GetNextAssoc(pos, uiKey, pInstrument);
		if(NULL != pInstrument)	// �õ�����
		{
			// �ڼ���β��ʱ�̲�ѯ
			pInstrument->m_iTailTimeQueryCount++;
			// ��������β��ʱ�̲�ѯ֡
			m_pSocketTailTimeFrame->MakeFrameData(pInstrument);
			// ��������β��ʱ�̲�ѯ֡
			m_pSocketTailTimeFrame->SendTailTimeFrame();
			//TRACE1("SendTailTimeFrame IP=%d \r\n", pInstrument->m_uiIP);
			/*
			if(pInstrument->m_uiInstrumentType==1 && itmp==0){
				for(int j=0;j<10;j++){
					for(int i=0;i<4000;i++)
						m_pSocketTailTimeFrame->SendTailTimeFrame();
					Sleep(1000);
					}
				itmp=1;
			}
			
			if(pInstrument->m_uiSN==8451 && itmp==0){
				for(int j=0;j<1;j++){
					for(int i=0;i<50;i++)
						m_pSocketTailTimeFrame->SendTailTimeFrame();
					Sleep(1);
					}
				itmp=1;
			}
			Sleep(1);
			*/
/*			Sleep(0);
		}
	}
	*/
}

/**
* �õ�����β��ʱ�̲�ѯӦ��֡
* @param void
* @return void
*/
void CThreadProcTimeDelay::GetTailTimeFrame()
{
	int iFrameCount = 0;
	while(true)	// ���ս��ջ�����
	{
		// �õ�����˿�β��ʱ�̲�ѯӦ��֡����
		iFrameCount = m_pSocketTailTimeFrame->GetFrameCount();
		if(0 == iFrameCount)	//������IP����Ӧ��֡
		{
			break;
		}
		if(iFrameCount > 0)	// ��β��ʱ�̲�ѯӦ��֡
		{
			for(int i = 0; i < iFrameCount; i++)	// ���εõ�β��ʱ�̲�ѯӦ��֡
			{
				// �õ�֡����
				m_pSocketTailTimeFrame->GetFrameData();
				// ����
				CInstrument* pInstrument = NULL;
				// ��������IP��ַ����������õ�����
				if(TRUE == GetInstrumentByIP(m_pSocketTailTimeFrame->m_oFrameTailTime.m_uiIPSource, pInstrument))
				{
					// ��������β��ʱ�̲�ѯ���
					//SetInstrumentTimeDelayData(pInstrument, &m_pSocketTailTimeFrame->m_oFrameTailTime);
					if(SetInstrumentTimeDelayData1(pInstrument, &m_pSocketTailTimeFrame->m_oFrameTailTime)==false)
						Calc_skip=1;
					//TRACE2("GetTailTimeFrame IP=%d TBH=%d\r\n", pInstrument->m_uiIP,pInstrument->m_uiTimeSystem);
					// �������ý���վβ������ʱ��
					pInstrument->ResetInstrumentCrossTailFrameReceiveTime(m_pRout->m_uiRoutDirection);
					// ��������β�����ա�����ʱ�̣����θ�2λ
					pInstrument->ResetInstrumentTailFrameTime();
/*
					TRACE1("ʱ�Ӳ�ѯӦ��֡-����SN�ţ�%d\r\n", pInstrument->m_uiSN);
					TRACE1("ʱ�Ӳ�ѯӦ��֡-m_usReceiveTime��%d\r\n", pInstrument->m_usReceiveTime);
					TRACE1("ʱ�Ӳ�ѯӦ��֡-m_usSendTime��%d\r\n", pInstrument->m_usSendTime);
					TRACE1("ʱ�Ӳ�ѯӦ��֡-m_usLineLeftReceiveTime��%d\r\n", pInstrument->m_usLineLeftReceiveTime);
					TRACE1("ʱ�Ӳ�ѯӦ��֡-m_usLineRightReceiveTime��%d\r\n", pInstrument->m_usLineRightReceiveTime);
					TRACE1("ʱ�Ӳ�ѯӦ��֡-m_usCrossTopReceiveTime��%d\r\n", pInstrument->m_usCrossTopReceiveTime);
					TRACE1("ʱ�Ӳ�ѯӦ��֡-m_usCrossDownReceiveTime��%d\r\n", pInstrument->m_usCrossDownReceiveTime);
*/
					// β��ʱ�̲�ѯ�Ƿ�ɹ�
					pInstrument->m_bTailTimeQueryOK = true;
					//TRACE2("ʱ�Ӳ�ѯӦ��֡-����SN�ţ�%d IP=%d\r\n", pInstrument->m_uiSN,pInstrument->m_uiIP);
					// �����������������
					m_oInstrumentMap.RemoveKey(pInstrument->m_uiIP);
				}else
					TRACE1("ʱ��Ӧ��֡����- IP=%d\r\n", m_pSocketTailTimeFrame->m_oFrameTailTime.m_uiIPSource);
			}		
		}
	}
	CString strDesc;
	strDesc.Format("GetTailTimeFrame"); 
	//m_pSiteData->m_oRunTimeDataList.Set(3, "CThreadProcTimeDelay", "GetTailTimeFrame", strDesc);
}

/**
* ��������IP��ַ����������õ�һ����������ָ�����÷�ʽ�õ�����
* @param unsigned int uiIP ����IP��ַ
* @param CInstrument* &pInstrument ����ָ�룬���õ���
* @return BOOL TRUE���õ������ɹ���FALSE���õ�����ʧ��
*/
BOOL CThreadProcTimeDelay::GetInstrumentByIP(unsigned int uiIP, CInstrument* &pInstrument)
{
	return m_oInstrumentMap.Lookup(uiIP, pInstrument);
}

/**
* ����β��ʱ�̲�ѯ
* @param void
* @return bool true���ɹ���false��ʧ��
*/
bool CThreadProcTimeDelay::ProcTailTimeQuery()
{
	int iTimeDelay = 100;
	// �����߷���
	if((1 == m_pRout->m_uiRoutDirection) || (2 == m_pRout->m_uiRoutDirection))
	{
		iTimeDelay = 50;
	}
	// ��1�δ���β��ʱ�̲�ѯ
	if(true == ProcTailTimeQueryOnce(iTimeDelay))
	{
		return true;
	}
	iTimeDelay = 151;
	// �����߷���
	if((1 == m_pRout->m_uiRoutDirection) || (2 == m_pRout->m_uiRoutDirection))
	{
		iTimeDelay = 25;
	}
	// ��2�δ���β��ʱ�̲�ѯ
	if(true == ProcTailTimeQueryOnce(iTimeDelay))
	{
		return true;
	}
	// ��3�δ���β��ʱ�̲�ѯ
	if(true == ProcTailTimeQueryOnce(iTimeDelay))
	{
		return true;
	}

	return true;
}

/**
* ����һ��β��ʱ�̲�ѯ
* @param int iTimeDelay ���Ͳ�ѯ֡�ͽ��ղ�ѯ֮֡���ʱ��������λ����
* @return bool true���ɹ���false��ʧ��
*/
bool CThreadProcTimeDelay::ProcTailTimeQueryOnce(int iTimeDelay)
{
	// �ж��Ƿ���Դ��������
	if(false == JudgeProcCondition())
	{
		return false;
	}
	// ����������β��ʱ�̲�ѯ֡
	if(iTimeDelay!=151)
		SendTailTimeFrame();
	// �ж��Ƿ���Դ��������
	if(false == JudgeProcCondition())
	{
		return false;
	}
	// ����
	Sleep(iTimeDelay);
	// �ж��Ƿ���Դ��������
	if(false == JudgeProcCondition())
	{
		return false;
	}
	// �õ�����β��ʱ�̲�ѯӦ��֡
	GetTailTimeFrame();
	// �յ�����Ӧ��֡
	if(TRUE == m_oInstrumentMap.IsEmpty())
	{
		return true;
	}
	return false;
}

/**
* ����ʱ��
* @param void
* @return bool true���ɹ���false��ʧ��
*/
bool CThreadProcTimeDelay::ProcTimeDelayCalculate()
{
	// �ж��Ƿ���Դ��������
	if(false == JudgeProcCondition())
	{
		return false;
	}
	// �����������
	m_olsInstrument.RemoveAll();
	// �������������
	m_oInstrumentMap.RemoveAll();

	CInstrument* pInstrument = NULL;
	CInstrument* pInstrumentNext = NULL;
	pInstrument = m_pRout->m_pHead;
	while(true)
	{
		// �õ���һ����
		pInstrumentNext = GetNextInstrument(pInstrument);
		// �жϣ���ǰ����β��ʱ�̲�ѯʧ�ܣ�������һ��������������һ��������δ����IP��ַ������һ��������β��ʱ�̲�ѯʧ��
		if((False == pInstrument->m_bTailTimeQueryOK) || (NULL == pInstrumentNext) || (0 == pInstrumentNext->m_uiIP) || (False == pInstrumentNext->m_bTailTimeQueryOK))
		{
			break;
		}
		// ����ʱ��
		
		if(pInstrument->m_usReceiveTime > pInstrumentNext->m_usSendTime)
		{
			pInstrumentNext->m_uiTimeDelay = pInstrument->m_uiTimeDelay + (pInstrument->m_usReceiveTime - pInstrumentNext->m_usSendTime) / 2;
		}
		else
		{
			pInstrumentNext->m_uiTimeDelay = pInstrument->m_uiTimeDelay + (TLOffset + pInstrument->m_usReceiveTime - pInstrumentNext->m_usSendTime) / 2;
		}
		// ����ʱ��������λ
		pInstrumentNext->m_uiTimeHigh = pInstrumentNext->m_uiTimeDelay / 0x10000;
		// ����ʱ��������λ
		pInstrumentNext->m_uiTimeLow = pInstrumentNext->m_uiTimeDelay % 0x10000;
/*
		TRACE1("ʱ������֡-����SN�ţ�%d\r\n", pInstrument->m_uiSN);
		TRACE1("ʱ������֡-m_usReceiveTime��%d\r\n", pInstrument->m_usReceiveTime);
		TRACE1("ʱ������֡-m_uiTimeDelay��%d\r\n", pInstrument->m_uiTimeDelay);
		TRACE1("ʱ������֡-NEXT-����SN�ţ�%d\r\n", pInstrumentNext->m_uiSN);
		TRACE1("ʱ������֡-NEXT-m_usReceiveTime��%d\r\n", pInstrumentNext->m_usReceiveTime);
		TRACE1("ʱ������֡-NEXT-m_usSendTime��%d\r\n", pInstrumentNext->m_usSendTime);
		TRACE1("ʱ������֡-NEXT-m_uiTimeDelay��%d\r\n", pInstrumentNext->m_uiTimeDelay);
		TRACE1("ʱ������֡-NEXT-m_uiTimeHigh��%d\r\n", pInstrumentNext->m_uiTimeHigh);
		TRACE1("ʱ������֡-NEXT-m_uiTimeLow��%d\r\n", pInstrumentNext->m_uiTimeLow);
*/
//		TRACE1("ʱ������֡-NEXT-����SN�ţ�%d\r\n", pInstrumentNext->m_uiSN);
//		TRACE1("ʱ������֡-NEXT-m_uiTimeDelay��%d\r\n", pInstrumentNext->m_uiTimeDelay);
		// �������
		m_olsInstrument.AddTail(pInstrumentNext);
		// ����������
		m_oInstrumentMap.SetAt(pInstrument->m_uiIP, pInstrumentNext);
		// ·��β����
		if(pInstrumentNext == m_pRout->m_pTail)
		{
			break;
		}
		pInstrument = pInstrumentNext;
	}
	return true;
}

/**
* ����ʱ��
* @param void
* @return bool true���ɹ���false��ʧ��
*/
bool CThreadProcTimeDelay::ProcTimeDelayCalculate_sys()
{
	// �ж��Ƿ���Դ��������
	if(false == JudgeProcCondition())
	{
		return false;
	}
	// �����������
	m_olsInstrument.RemoveAll();
	// �������������
	m_oInstrumentMap.RemoveAll();

	CInstrument* pInstrument = NULL;
	CInstrument* pInstrumentNext = NULL;
	pInstrument = m_pRout->m_pHead;
	unsigned int m_uiSystemTimeSite=0;

	//ȡ����վ��ʱ��
	while(true)
	{	 
		if((False == pInstrument->m_bTailTimeQueryOK) || pInstrument->m_bIPSetOK==false )
		{
			break;
		}
		if(pInstrument->m_uiInstrumentType==3){		// by zl
			if(time_init0==0){
				time_init0=pInstrument->m_uiNetTime;
				m_uiSystemTimeSite=pInstrument->m_uiNetTime;
				break;
				//m_pSiteData->m_uiSystemTimeSite=pInstrument->m_uiNetTime;
			}
			else{
				if(pInstrument->m_uiNetTime==m_uiSystemTimeSite)
					break;
					//return false;
				m_uiSystemTimeSite=pInstrument->m_uiNetTime;
				//m_pSiteData->m_uiSystemTimeSite=pInstrument->m_uiNetTime;
			}
		}
		// �õ���һ����
		pInstrumentNext = GetNextInstrument(pInstrument);
		if(pInstrumentNext == m_pRout->m_pTail)
		{
			break;
		}
		pInstrument = pInstrumentNext;
	}
	
	pInstrument = NULL;
	pInstrumentNext = NULL;
	pInstrument = m_pRout->m_pHead;
    int iTimeDelayH =0,iTimeDelayHH=0;
	int iTimeDelayL=0;
	int inDelaylast=0,Delayinit0=4112;

	//ifrist=0;
	int iDelayL=0;

	while(true)
	{	 
		if((False == pInstrument->m_bTailTimeQueryOK) || pInstrument->m_bIPSetOK==false )
		{
			break;
		}
		// �õ���һ����
		pInstrumentNext = GetNextInstrument(pInstrument);
		// �жϣ���ǰ����β��ʱ�̲�ѯʧ�ܣ�������һ��������������һ��������δ����IP��ַ������һ��������β��ʱ�̲�ѯʧ��
		if((False == pInstrument->m_bTailTimeQueryOK) || (NULL == pInstrumentNext) || (0 == pInstrumentNext->m_uiIP) || (False == pInstrumentNext->m_bTailTimeQueryOK))
		{
			break;
		}
		// ����ʱ��

		//if(ifrist<10 && ifrist>5){
		if(ifrist==5){
			// ����ʱ��������λ
			//iTimeDelayH =iTimeDelayH+(m_uiSystemTimeSite-pInstrument->m_uiNetTime);
			iTimeDelayH =pInstrument->m_uiTimeSystem-pInstrument->m_uiNetTime;
			iTimeDelayHH=iTimeDelayH;
			m_pSiteData->m_bProcTimeDelayON_stop=true;
			//iTimeDelayH =pInstrument->m_uiTimeSystem;
		}else{
			iTimeDelayH =0;
			//iTimeDelayH =iTimeDelayH+(m_uiSystemTimeSite-pInstrument->m_uiNetTime);
			iTimeDelayHH=pInstrument->m_uiTimeSystem-pInstrument->m_uiNetTime;
			m_pSiteData->m_bProcTimeDelayON_stop=false;
			//ifrist=20;
		}
/*		if(pInstrument->m_uiInstrumentType==1){
			iTimeDelayH=0;
			pInstrument->m_uiTimeHigh =0;
			pInstrument->m_uiTimeLow =0;
			inDelaylast=0;
		}
*/	//	iTimeDelayH =pInstrument->m_uiNetTime-pInstrument->m_uiTimeSystem;
		iTimeDelayH =0;
		int t1=pInstrument->m_usReceiveTime-pInstrumentNext->m_usSendTime;
		if(t1<0)
			t1=t1+TLOffset;
		inDelaylast=t1;
		// ����ʱ��������λ
		iTimeDelayL=iTimeDelayL-(inDelaylast-Delayinit0);
		if(iTimeDelayL>=TLOffset)
			iTimeDelayH++;
		//iTimeDelayL=iTimeDelayL%TLOffset;
		pInstrumentNext->m_uiTimeHigh =iTimeDelayH;
		//pInstrumentNext->m_uiTimeLow =iTimeDelayL%0xffff;
		iDelayL = iDelayL + iDelayL/2 +10;
		iDelayL=0;
		pInstrumentNext->m_uiTimeLow =iDelayL %0xffff;

		// �������
		m_olsInstrument.AddTail(pInstrument);
		// ����������
		m_oInstrumentMap.SetAt(pInstrument->m_uiIP, pInstrument);
		//���±���ʱ��
/*		if(ifrist==1){
			m_pSiteData->m_oCriticalSectionSystemTimeSite.Lock();
				//m_pSiteData->m_uiSystemTimeSite = (unsigned int)(pInstrumentNext->m_uiTimeSystem/ 4096.0 * 1000.0);
			m_pSiteData->m_uiSystemTimeSite = pInstrumentNext->m_uiTimeSystem;
			m_pSiteData->m_oCriticalSectionSystemTimeSite.Unlock();
		}
*/			if(ifrist==2){
				//TRACE3("m_uiTimeLow=%d ReceiveTime=%d SendTime=%d\r\n", pInstrument->m_uiTimeLow,pInstrument->m_usReceiveTime,pInstrumentNext->m_usSendTime);
				CString strDesc;
				strDesc.Format("Get1 Sn=%x,m_uiSystemTimeSite= %u m_uiTimeSystem= %u m_uiNetTime= %u m_uiTimeDelay= %d m_uiTimeHigh= %d m_uiTimeLow= %d rev= %u send= %u %d",pInstrument->m_uiSN,m_uiSystemTimeSite,pInstrument->m_uiTimeSystem,pInstrument->m_uiNetTime,iTimeDelayHH,pInstrument->m_uiTimeHigh,pInstrument->m_uiTimeLow,pInstrument->m_usReceiveTime,pInstrumentNext->m_usSendTime,inDelaylast-Delayinit0); 
				m_pSiteData->m_oRunTimeDataList.Set(3, "CThreadProcTimeDelay", "Calculate1", strDesc);
			}
		pInstrument = pInstrumentNext;
		// ·��β����
		if(pInstrumentNext == m_pRout->m_pTail)
		{
/*			if(ifrist==5){
				// ����ʱ��������λ
				//iTimeDelayH =iTimeDelayH+(m_uiSystemTimeSite-pInstrument->m_uiNetTime);
				iTimeDelayH =pInstrument->m_uiNetTime-pInstrument->m_uiTimeSystem;
				m_pSiteData->m_bProcTimeDelayON_stop=true;
				iTimeDelayH =0;
				pInstrument->m_uiTimeHigh =iTimeDelayH;
				iTimeDelayL=0;
				pInstrument->m_uiTimeLow =iTimeDelayL%TLOffset;
			}
*/			break;
		}
	}
		ifrist++;
/*
	if(isum>1)
		inDelay=inDelaylast/isum-Delayinit0;
*/	// �������
	m_olsInstrument.AddTail(pInstrument);
	// ����������
	m_oInstrumentMap.SetAt(pInstrument->m_uiIP, pInstrument);
	CString strDesc;
	strDesc.Format("Get2 Sn=%x,m_uiSystemTimeSite= %u m_uiTimeSystem= %u m_uiNetTime=%u m_uiTimeDelay= %d m_uiTimeHigh= %u m_uiTimeLow= %u rev= %u %u data=%d order=%d",pInstrument->m_uiSN,m_pSiteData->m_uiSystemTimeSite,pInstrument->m_uiTimeSystem,pInstrument->m_uiNetTime,iTimeDelayH,pInstrument->m_uiTimeHigh,(int)pInstrument->m_uiTimeLow,pInstrument->m_usReceiveTime,inDelaylast-Delayinit0,m_pSiteData->NetDataCount,m_pSiteData->NetOrderCount); 
	m_pSiteData->m_oRunTimeDataList.Set(3, "CThreadProcTimeDelay", "Calculate1", strDesc);
	return true;
}

/**
* ����ʱ��
* @param void
* @return bool true���ɹ���false��ʧ��
*/
bool CThreadProcTimeDelay::ProcTimeDelaySet()
{
	// �ж��Ƿ���Դ��������
	if(false == JudgeProcCondition())
	{
		return false;
	}

	CInstrument* pInstrument = NULL;
	while(false == m_olsInstrument.IsEmpty())
	{
		pInstrument = m_olsInstrument.RemoveHead();
		// �ڼ�����������ʱ��
		pInstrument->m_iTimeSetCount++;
		// ����ʱ�������Ƿ�ɹ�
		pInstrument->m_bTimeSetOK = true;	
		m_pSocketTimeSetFrame->MakeFrameData(pInstrument);
		if(m_pSiteData->m_bProcTimeDelayON_stop==true){
			m_pSocketTimeSetFrame->SendTimeSetFrame();
			TRACE3("ProcTimeDelaySet IP=%d TBH=%d  TBL=%d\r\n", pInstrument->m_uiIP,pInstrument->m_uiTimeHigh,pInstrument->m_uiTimeLow);
			//TRACE3("ProcTimeDelaySet IP=%d m_uiTimeSystem=%d  m_uiNetTime=%d\r\n", pInstrument->m_uiIP,pInstrument->m_uiTimeSystem,pInstrument->m_uiNetTime);
		}
		Sleep(1);
	}
	//ֻ��һ��ʱͳ
	//m_pSiteData->m_bProcTimeDelayON_stop=false;
	return true;
}

/**
* ��������β��ʱ�̲�ѯ���
* @param CInstrument* pInstrument ����ָ��
* @return CFrameTailTime* pFrameTailTime β��ָ��
* @return void
*/
void CThreadProcTimeDelay::SetInstrumentTimeDelayData(CInstrument* pInstrument, CFrameTailTime* pFrameTailTime)
{
	pInstrument->m_usReceiveTime = pFrameTailTime->m_usReceiveTime;	// 16bitsʱ�䣬����ʱ�̵�λ
	pInstrument->m_usSendTime = pFrameTailTime->m_usSendTime;	// 16bitsʱ�䣬����ʱ�̵�λ

	pInstrument->m_usLineLeftReceiveTime = pFrameTailTime->m_usLineLeftReceiveTime;	// 16bits ���߷�������β������ʱ��
	pInstrument->m_usLineRightReceiveTime = pFrameTailTime->m_usLineRightReceiveTime;	// 16bits ���߷�������β������ʱ��

	pInstrument->m_usCrossTopReceiveTime = pFrameTailTime->m_usCrossTopReceiveTime;	// 16bits �����߷�������β������ʱ��
	pInstrument->m_usCrossDownReceiveTime = pFrameTailTime->m_usCrossDownReceiveTime;	// 16bits �����߷�����β������ʱ��

	pInstrument->m_uiTimeSystem = pFrameTailTime->m_uiTimeSystem; //by zl
	pInstrument->m_uiNetTime = pFrameTailTime->m_uiNetTime; //by zl

}

/**
* ��������β��ʱ�̲�ѯ���
* @param CInstrument* pInstrument ����ָ��
* @return CFrameTailTime* pFrameTailTime β��ָ��
* @return void
*/
bool CThreadProcTimeDelay::SetInstrumentTimeDelayData1(CInstrument* pInstrument, CFrameTailTime* pFrameTailTime)
{
	pInstrument->m_usReceiveTime = pFrameTailTime->m_usReceiveTime%0x4000;	// 16bitsʱ�䣬����ʱ�̵�λ
	pInstrument->m_usSendTime = pFrameTailTime->m_usSendTime%0x4000;	// 16bitsʱ�䣬����ʱ�̵�λ

	pInstrument->m_usLineLeftReceiveTime = pFrameTailTime->m_usLineLeftReceiveTime%0x4000;	// 16bits ���߷�������β������ʱ��
	pInstrument->m_usLineRightReceiveTime = pFrameTailTime->m_usLineRightReceiveTime%0x4000;	// 16bits ���߷�������β������ʱ��

	pInstrument->m_usCrossTopReceiveTime = pFrameTailTime->m_usCrossTopReceiveTime%0x4000;	// 16bits �����߷�������β������ʱ��
	pInstrument->m_usCrossDownReceiveTime = pFrameTailTime->m_usCrossDownReceiveTime%0x4000;	// 16bits �����߷�����β������ʱ��

	if(pInstrument->m_uiInstrumentType==1){
		if(pInstrument->m_usLineLeftReceiveTime!=0)
			pInstrument->m_usReceiveTime=pInstrument->m_usLineLeftReceiveTime;
		else
			pInstrument->m_usReceiveTime=pInstrument->m_usLineRightReceiveTime;
	}
	if(pInstrument->m_uiTimeSystem==pFrameTailTime->m_uiTimeSystem){
		pInstrument->m_uiTimeSystem = pFrameTailTime->m_uiTimeSystem; //by zl
		pInstrument->m_uiNetTime = pFrameTailTime->m_uiNetTime; //by zl
		return false;
	}
	pInstrument->m_uiTimeSystem = pFrameTailTime->m_uiTimeSystem; 
	pInstrument->m_uiNetTime = pFrameTailTime->m_uiNetTime; 

	if(m_pSiteData->NetOrderCount==0)
		pInstrument->m_uiNetOrder=pFrameTailTime->m_uiNetOrder;
	int itmp=pFrameTailTime->m_uiNetOrder;
	if(pInstrument->m_uiNetOrder!=pFrameTailTime->m_uiNetOrder)
		m_pSiteData->NetOrderCount+=pFrameTailTime->m_uiNetOrder-pInstrument->m_uiNetOrder;
	pInstrument->m_uiNetOrder = pFrameTailTime->m_uiNetOrder;

	CString strDesc;
/*	if(pInstrument->m_uiNetState!=pFrameTailTime->m_uiNetState){
		strDesc.Format("Sn=%d,lastNetState=%x,NetState=%x,%x NetOrder=%x",pInstrument->m_uiSN,pInstrument->m_uiNetState,pFrameTailTime->m_uiNetState,pInstrument->m_uiNetState-pFrameTailTime->m_uiNetState,pFrameTailTime->m_uiNetOrder); 
		m_pSiteData->m_oRunTimeDataList.Set(3, "CThreadProcTimeDelay", "m_uiNetState", strDesc);
	}
	
	if( pInstrument->m_uiNetState!=pFrameTailTime->m_uiNetState ){
		strDesc.Format("Sn=%d,lastNetState=%x,NetState=%x,%x",pInstrument->m_uiSN,pInstrument->m_uiNetState,pFrameTailTime->m_uiNetState&0xffff,pInstrument->m_uiNetState-pFrameTailTime->m_uiNetState&0xffff); 
		m_pSiteData->m_oRunTimeDataList.Set(3, "CThreadProcTimeDelay", "m_uiNetState", strDesc);
	}
	*/
	if(m_pSiteData->NetDataCount==0)
		pInstrument->m_uiNetState=pFrameTailTime->m_uiNetState;
	if(pInstrument->m_uiNetState!=pFrameTailTime->m_uiNetState)
		m_pSiteData->NetDataCount+=pFrameTailTime->m_uiNetState-pInstrument->m_uiNetState;
	pInstrument->m_uiNetState = pFrameTailTime->m_uiNetState;
/*	CString strDesc;
	strDesc.Format("Sn=%x m_uiSystemTimeSite= %u m_uiTimeSystem= %u m_uiNetTime=%u m_uiTimeHeadFrame= %u m_usRec= %05u m_usSend= %05u LeftRec= %u RightRec= %u CrossTopRec= %u CrossDownRec= %u", pInstrument->m_uiSN,m_pSiteData->m_uiSystemTimeSite,pInstrument->m_uiTimeSystem,pInstrument->m_uiNetTime,pInstrument->m_uiTimeHeadFrame, pInstrument->m_usReceiveTime,pInstrument->m_usSendTime,pInstrument->m_usLineLeftReceiveTime,pInstrument->m_usLineRightReceiveTime,pInstrument->m_usCrossTopReceiveTime,pInstrument->m_usCrossDownReceiveTime);
	// ��������״̬����
	m_pSiteData->m_oRunTimeDataList.Set(3, "CThreadProcTimeDelay", "TimeDelayDat", strDesc);
*/	return true;
}