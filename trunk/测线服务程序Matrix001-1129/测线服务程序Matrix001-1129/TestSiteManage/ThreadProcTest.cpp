// ThreadProcTest.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "TestSiteManage.h"
#include "ThreadProcTest.h"


// CThreadProcTest

IMPLEMENT_DYNCREATE(CThreadProcTest, CWinThread)

CThreadProcTest::CThreadProcTest()
{

}

CThreadProcTest::~CThreadProcTest()
{
}

BOOL CThreadProcTest::InitInstance()
{
	// TODO: �ڴ�ִ���������̳߳�ʼ��
	return TRUE;
}

int CThreadProcTest::ExitInstance()
{
	// TODO: �ڴ�ִ���������߳�����
	return CWinThread::ExitInstance();
}

BEGIN_MESSAGE_MAP(CThreadProcTest, CWinThread)
END_MESSAGE_MAP()

// CThreadProcTest ��Ϣ�������

/**
* �߳�������
* @param void
* @return int
*/
int CThreadProcTest::Run()
{
	// ѭ����ֱ���رձ�־Ϊ��
	while(true)
	{
		// �жϣ��رձ�־Ϊ��
		if(true == m_bClose)
		{
			break;
		}
		// ���Դ���
		ProcTest();
		// �жϣ��رձ�־Ϊ��
		if(true == m_bClose)
		{
			break;
		}
		// �����߳̿���
		m_bFree = true;
		// �����߳�
		this->SuspendThread();
		// �����߳�æ
		m_bFree = false;
	}
	// �жϣ�����ʽ 1-��������
	if(1 == m_iProcTestMethod)
	{
		// ���ò����߳��̹߳رձ�־Ϊ�棬��������
		m_pSiteData->m_bProcTestBaseClose = true;
	}
	// �жϣ�����ʽ 2-�������
	else if(2 == m_iProcTestMethod)
	{
		// ���ò����߳��̹߳رձ�־Ϊ�棬�������
		m_pSiteData->m_bProcTestNoiseClose = true;
	}
	// ����
	return CWinThread::Run();
}

/**
* ��ʼ���߳�
* @param void
* @return bool true���ɹ���false��ʧ��
*/
bool CThreadProcTest::OnInit()
{
	// �ǹ���״̬
	m_bWork = false;
	// �ǹر��߳�
	m_bClose = false;
	// ����״̬
	m_bFree = true;
	// ������״̬
	m_bSwitchON = false;
	// �����¼Ӽ첨���ĳ�ʼ����
	m_bProcSensorTestOnField = false;
	
	// ��ʼ����������������緢�ͼ���
	m_uiTestNoiseNetSendCount = 0;
	// ��ʼ����������������緢�Ͳ���
	m_uiTestNoiseNetSendStep = 1;
	
	//Ϊ��ͼת����ʼ��֡����
	FDUNum=0;
	for(int i=0;i<MaxFDUCount;i++)
		FrameNum[i]=0;

	irecevice=0;
	CString strDesc;
	m_pSiteData->m_oProcTestThreadID=GetCurrentThreadId();
	strDesc.Format("CThreadProcTest_id=%d",m_pSiteData->m_oProcTestThreadID);
	m_pSiteData->m_oRunTimeDataList.Set(1, "CThreadProcTest", "ProcTest", strDesc);

	char * tmp=strDesc.GetBuffer(strDesc.GetLength() + 1);
	OutputDebugString(tmp );

	return true;
}

/**
* �ر��߳�
* @param void
* @return bool true���ɹ���false��ʧ��
*/
bool CThreadProcTest::OnClose()
{
	// �ر��߳�
	m_bClose = true;
	// �жϣ��߳̿���״̬
	if(true == m_bFree)
	{
		// ��������
		ResumeProcTest();
	}
	return true;
}

/**
* �߳̿�ʼ����
* @param void
* @return bool true���ɹ���false��ʧ��
*/
bool CThreadProcTest::OnWork()
{
	// ����״̬
	m_bWork = true;
	return true;
}

/**
* �߳�ֹͣ����
* @param void
* @return bool true���ɹ���false��ʧ��
*/
bool CThreadProcTest::OnStop()
{
	// �ǹ���״̬
	m_bWork = false;
	// ������״̬
	m_bSwitchON = false;
	return true;
}

/**
* �ж��߳��Ƿ���Խ��д�����������
* @param void
* @return bool true���ɹ���false��ʧ��
*/
bool CThreadProcTest::JudgeProcCondition()
{	
	// �жϣ��ǹ���״̬���������״̬
	if((false == m_bWork) || (false == m_bSwitchON))
	{		
		// �жϣ�����ʽ 1-��������
		if(1 == m_iProcTestMethod)
		{
			// ���ò����߳��߳�ֹͣ��־Ϊ�棬��������
			m_pSiteData->m_bProcTestBaseStop = true;
		}
		// �жϣ�����ʽ 2-�������
		else if(2 == m_iProcTestMethod)
		{
			// ���ò����߳��߳�ֹͣ��־Ϊ�棬�������
			m_pSiteData->m_bProcTestNoiseStop = true;
		}
		return false;
	}
	else
	{
		// �жϣ�����ʽ 1-��������
		if(1 == m_iProcTestMethod)
		{
			// ���ò����߳��߳�ֹͣ��־Ϊ�棬��������
			m_pSiteData->m_bProcTestBaseStop = false;
		}
		// �жϣ�����ʽ 2-�������
		else if(2 == m_iProcTestMethod)
		{
			// ���ò����߳��߳�ֹͣ��־Ϊ�棬�������
			m_pSiteData->m_bProcTestNoiseStop = false;
		}
	}
	return true;
}

/**
* �̵߳ȴ�
* @param int iWaitStopCount ���ȴ�������ÿ��50����
* @return void
*/
void CThreadProcTest::Wait(int iWaitStopCount)
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
* �ж��߳��Ƿ����
* @param void
* @return bool true���ǣ�false����
*/
bool CThreadProcTest::IsThreadFree()
{
	return m_bFree;
}

/**
* �����̣߳������������߳�ʹ��
* @param void
* @return bool true���ɹ���false��ʧ��
*/
bool CThreadProcTest::Lock()
{
	bool bLock = false;	
	m_pSiteData->m_oCriticalSectionProcTest.Lock();	// Ϊ�����߳�׼�����߳�ͬ����������
		if(true == m_bFree)	// ɾ���߳̿���	
		{		
			m_bFree = false;	// ����ɾ���߳�æ
			bLock = true;
		}		
	m_pSiteData->m_oCriticalSectionProcTest.Unlock();	// Ϊ�����߳�׼�����߳�ͬ���������
	return bLock;
}

/**
* �����̣߳����������߳�ʹ��
* @param void
* @return bool true���ɹ���false��ʧ��
*/
void CThreadProcTest::Unlock()
{
	m_pSiteData->m_oCriticalSectionProcTest.Lock();	// Ϊ�����߳�׼�����߳�ͬ����������		
		m_bFree = true;	// ����ɾ���߳̿���
	m_pSiteData->m_oCriticalSectionProcTest.Unlock();	// Ϊ�����߳�׼�����߳�ͬ���������
}

/**
* �����̣߳���������
* @param void
* @return void
*/
void CThreadProcTest::ResumeProcTest()
{
	m_bFree = false;	// ����ɾ���߳�æ
	m_bSwitchON = true;	// ����״̬
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
* ���Դ���
* @param void
* @return void
*/
void CThreadProcTest::ProcTest()
{
	CString strDesc;
	strDesc.Format("Test Project Start.Method:%d;Type:%d;Nb:%d", m_iProcTestMethod, m_pTestProject->m_uiProjectType, m_pTestProject->m_uiTestNb);
	// ��������״̬����
	m_pSiteData->m_oRunTimeDataList.Set(1, "CThreadProcTest", "ProcTest", strDesc);

	// ѭ����ֱ�������������Ϊ��
	while(false == m_pTestProject->m_olsTestRequest.IsEmpty())
	{
		m_pSocketTestDataFrame->m_irevFrameCount=0;
		m_pSocketTestDataFrame->m_iFrameCount=0;

		m_pSocketTestSetFrame->strrecv.Empty(); 
		m_pSocketTestSetFrame->adgetcount=0;
		m_pSocketTestSetFrame->adsetcount=0;
		m_pSocketTestSetFrame->gettestcount=0;
		m_pSocketTestSetFrame->getTBcount=0;
		m_pSocketTestSetFrame->resetcheckrecv();

		FDUNum=0;
		for(int i=0;i<MaxFDUCount;i++)
			FrameNum[i]=0;
		ViewBuf=(byte *)malloc(MaxFDUCount*FrameLength);

		// ֹͣ���ڽ������ݲɼ�������
		StopInstrumentWhichIsCollecting();

		// �õ���������
		m_pTestRequest = m_pTestProject->m_olsTestRequest.RemoveHead();
		// ���ݲ������ͣ��õ����Ի�������ָ��
		m_pTestBaseData = m_pTestProject->GetTestBaseDataByTestType(m_pTestRequest->m_uiType);
		// ������������������緢�Ͳ���
		SetTestNoiseNetSendStep();

		strDesc.Format("Test Request Start.Nb=%d msLength=%d,Aim:%d;Type:%d,m_uiADTimeBegin=%d m_uiTimeCollectEnd=%d",m_pTestProject->m_uiTestNb,m_pTestProject->m_uiRecordLength, m_pTestRequest->m_uiAim, m_pTestRequest->m_uiType,m_pSocketTestSetFrame->m_oFrameTestSet.m_uiADTimeBegin,m_pTestRequest->m_uiTimeCollectEnd);
		// ��������״̬����
		m_pSiteData->m_oRunTimeDataList.Set(1, "CThreadProcTest", "ProcTest", strDesc);
		//m_pTestProject->m_uiRecordResult=1;
		// ���Դ���һ�β������󣬿�ʼ
		ProcTestRequestStart();
		strDesc.Format("Test Request Start1.Aim:%d;Type:%d,m_uiADTimeBegin=%d m_uiTimeCollectEnd=%d", m_pTestRequest->m_uiAim, m_pTestRequest->m_uiType,m_pSocketTestSetFrame->m_oFrameTestSet.m_uiADTimeBegin,m_pTestRequest->m_uiTimeCollectEnd);
		// ��������״̬����
		m_pSiteData->m_oRunTimeDataList.Set(1, "CThreadProcTest", "ProcTest", strDesc);
		// ���Դ���һ�β������󣬴���
		ProcTestRequest();
		// ���Դ���һ�β������󣬽���
		ProcTestRequestEnd();

		strDesc.Format("Test Request End");
		// ��������״̬����
		m_pSiteData->m_oRunTimeDataList.Set(1, "CThreadProcTest", "ProcTest", strDesc);
		
		free(ViewBuf);
		// �жϣ����ܼ�������
		if(false == JudgeProcCondition())
		{
			// ֹͣ���ڽ������ݲɼ�������
			StopInstrumentWhichIsCollecting();
			Sleep(100);
			break;
		}
		// �õ���������֮��ĵȴ�ʱ�䣬ÿ�β���֮��ļ�������룩
		int iWaitStopCount = m_pTestProject->m_uiDelayBetweenTest / 50;
		// �ȴ�
		Wait(iWaitStopCount);
		// �жϣ����ܼ�������
		if(false == JudgeProcCondition())
		{
			// ֹͣ���ڽ������ݲɼ�������
			StopInstrumentWhichIsCollecting();
			Sleep(100);
			break;
		}
		// ֹͣ���ڽ������ݲɼ�������
		StopInstrumentWhichIsCollecting();
		Sleep(100);
		CString strDesc;
		strDesc.Format("totalcount=%d recevicecount=%d saveecount=%d,lossframecount=%d",totalcount,recevicecount,saveecount,lossframecount);
		m_pSiteData->m_oRunTimeDataList.Set(3, "CThreadProcTest", "total", strDesc);
		TRACE3("recevicecount=%d saveecount=%d,lossframecount=%d\r\n",recevicecount,saveecount,lossframecount);
		m_pSiteData->m_oSocketTestDataFrame.Lock();
		TRACE3("AD adsetcount=%d getTBcount=%d gettestcout=%d\r\n",m_pSocketTestSetFrame->adsetcount,m_pSocketTestSetFrame->getTBcount,m_pSocketTestSetFrame->gettestcount);
		strDesc.Format("AD adsetcount=%d getTBcount=%d gettestcout=%d",m_pSocketTestSetFrame->adsetcount,m_pSocketTestSetFrame->getTBcount,m_pSocketTestSetFrame->gettestcount);
		m_pSiteData->m_oRunTimeDataList.Set(3, "CThreadProcTest", "totalrecv", strDesc);
		m_pSiteData->m_oSocketTestDataFrame.Unlock();
		TRACE("%s",m_pSocketTestSetFrame->strrecv);

		TRACE1("һ�β���������ɡ��������ͣ�%d\r\n", m_pTestRequest->m_uiType);
	}

	// ���Ͳ��Խ������������-�¼Ӽ첨���ĳ�ʼ����
	SendTestResultBaseForOnFieldTest();
	// �����ϴ��ֳ����ݱ仯ʱ�̣���������
	UpdateSiteDataChangedTimeForTestData();

	// �����¼Ӽ첨���ĳ�ʼ����
	m_bProcSensorTestOnField = false;
	strDesc.Format("Test Project End");
	// ��������״̬����
	m_pSiteData->m_oRunTimeDataList.Set(1, "CThreadProcTest", "ProcTest", strDesc);
}

/**
* ���Դ���һ�β������󣬿�ʼ
* @param void
* @return void
*/
void CThreadProcTest::ProcTestRequestStart()
{
	// ���ã�Ϊһ���µĲ�������
	m_pSocketTestSetFrame->m_pTestElementList->ResetForNewTestRequest();
	// �жϣ���������
	if(1 == m_iProcTestMethod)
	{
		m_pLogicData->SetTestElementListLimit(m_pTestRequest->m_uiType);
	}
	// ���ã�Ϊһ���µĲ�������
	m_pTestDataBuffer->ResetForNewTestRequest(); 

	// �򿪲��������ļ�
	FileTestDataOpen();
	lossframecount=0;
	recevicecount=0;
	saveecount=0;
	totalcount=0;
}

/**
* ���Դ���һ�β������󣬴���
* @param void
* @return void
*/
void CThreadProcTest::ProcTestRequest()
{
	m_pADCDataSaveToFile.OnOpenADCSaveFile(m_pSocketTestSetFrame->m_uiIPCount);
	//����AD����,����ProcSendTestSetFrame
	ADSet();
	// �����Ͳ�������֡
	//ProcSendTestSetFrame();
	// �ȴ�
//	Wait(2);		//�ȴ�AD��������
	// �����Ͳ��Կ�ʼ֡
	//ProcSendTestStartFrame();
	m_pSiteData->m_oCriticalSectionSystemTimeSite.Lock();
		m_pSiteData->m_bProcTimeDelayON_stop = false;	// ����ʱ�Ӵ����߳�ֹͣ
	m_pSiteData->m_oCriticalSectionSystemTimeSite.Unlock();

	ProcSendTestADStart();

	Wait(1);		//�ȴ�AD��������
	CString strDesc;
	m_pSiteData->m_oSocketTestDataFrame.Lock();
	TRACE3("AD1 adsetcount1=%d getTBcount=%d gettestcout=%d\r\n",m_pSocketTestSetFrame->adsetcount,m_pSocketTestSetFrame->getTBcount,m_pSocketTestSetFrame->gettestcount);
	strDesc.Format("AD1 adsetcount1=%d getTBcount=%d gettestcout=%d",m_pSocketTestSetFrame->adsetcount,m_pSocketTestSetFrame->getTBcount,m_pSocketTestSetFrame->gettestcount);
	m_pSiteData->m_oRunTimeDataList.Set(3, "CThreadProcTest", "totalrecv", strDesc);
	m_pSiteData->m_oSocketTestDataFrame.Unlock();
	
	// �õ��������������
	GetAndProcTestData();
	m_pSiteData->m_oCriticalSectionSystemTimeSite.Lock();
		m_pSiteData->m_bProcTimeDelayON_stop = true;	// ����ʱ�Ӵ����̹߳���
		m_pSiteData->iDelayfrist=0;
	//m_pSiteData->m_bProcTimeDelayON_stop = false;	// ��ʱֻ��һ��ʱ������ʱ�Ӵ����߳�ֹͣ
	m_pSiteData->m_oCriticalSectionSystemTimeSite.Unlock();
	m_pADCDataSaveToFile.OnCloseADCSaveFile();
}

/**
* ���Դ���һ�β������󣬽���
* @param void
* @return void
*/
void CThreadProcTest::ProcTestRequestEnd()
{
	// �رղ��������ļ�
	FileTestDataClose();
}

/**
* ���Ͳ��Խ������������-�¼Ӽ첨���ĳ�ʼ����
* @param void
* @return void
*/
void CThreadProcTest::SendTestResultBaseForOnFieldTest()
{
	// �жϣ��Ǵ����¼Ӽ첨���ĳ�ʼ����	
	if(false == m_bProcSensorTestOnField)
	{
		return;
	}
	// �жϣ�����ʽ 2-�������
	if(2 == m_iProcTestMethod)
	{
		return;
	}
	// �жϣ�����������
	if(false == JudgeProcCondition())
	{
		return;
	}

	m_pTestRequest->m_uiType = 45;	// �¼Ӽ첨���ĳ�ʼ����
	// ���Ͳ��Խ������������
	SendTestResultBase();
}

/**
* �����ϴ��ֳ����ݱ仯ʱ�̣���������
* @param void
* @return void
*/
void CThreadProcTest::UpdateSiteDataChangedTimeForTestData()
{
	// �жϣ�����ʽ 2-�������
	if(2 == m_iProcTestMethod)
	{
		return;
	}
	// �жϣ�����������
	if(false == JudgeProcCondition())
	{
		return;
	}

	// �����ϴ��ֳ����ݱ仯ʱ��
	m_pSiteData->UpdateSiteDataChangedTime();
	m_pSiteData->m_bTestDataChanged = true;
}

/**
* �򿪲��������ļ�
* @param void
* @return void
*/
void CThreadProcTest::FileTestDataOpen()
{
	// �жϣ�����¼��������
	if(0 == m_pTestProject->m_uiRecordResult)
	{
		return;
	}

	CString strFileName;
	CString strDate;
	CString strTime;
	SYSTEMTIME oSystemTime;

	// �õ�����ʱ��
	GetLocalTime(&oSystemTime);
	// ����
	strDate.Format("%d-%d-%d", oSystemTime.wYear, oSystemTime.wMonth, oSystemTime.wDay);
	// ʱ��
	strTime.Format("%d %d %d", oSystemTime.wHour, oSystemTime.wMinute, oSystemTime.wSecond);

	// ���ò��������ļ���
	strFileName.Format("TestData%d-%d %s %s.dat", m_pTestProject->m_uiTestNb, m_pTestRequest->m_uiType, strDate, strTime);
	BOOL bData = m_oFileTestData.Open(strFileName, CFile::modeCreate | CFile::modeWrite | CFile::typeBinary);
}

/**
* д���������ļ�
* @param byte* pBlockData ����ָ��
* @param unsigned int uiSize ���ݳ���
* @return void
*/
void CThreadProcTest::FileTestDataWrite(byte* pBlockData, unsigned int uiSize)
{
	// �жϣ�����¼��������
	if(0 == m_pTestProject->m_uiRecordResult)
	{
		return;
	}

	m_oFileTestData.Write(pBlockData, uiSize);

}

/**
* �رղ��������ļ�
* @param void
* @return void
*/
void CThreadProcTest::FileTestDataClose()
{
	// �жϣ�����¼��������
	if(0 == m_pTestProject->m_uiRecordResult)
	{
		return;
	}

	m_oFileTestData.Close();
}

/**
* �������Բ������õĻ�����������
* @param unsigned int uiTestNb ���Ժ�
* @return void
*/
bool CThreadProcTest::OnTestTaskBaseFromTestSetup(unsigned int uiTestNb)
{	
	// �жϣ��̹߳�����
	if(false == Lock())
	{
		return false;
	}
	// ���û���������Ŀ�����Բ������õĲ�������
	if(false == m_pLogicData->OnSetupTestProjectForTestBaseFromTestSetup(uiTestNb))
	{
		Unlock();
		return false;
	}
	m_pTestProject = &m_pLogicData->m_oTestSetupData.m_oTestProjectBase;	// ������Ŀ���ж���
	m_pSocketTestSetFrame->m_pTestElementList = &m_pLogicData->m_oTestSetupData.m_oTestElementListBase;	// ���Ե�Ԫ����
	m_pSocketTestSetFrame->m_uiIPCount = m_pSocketTestSetFrame->m_pTestElementList->m_uiCountUsed;	// ���òμӲ���IP��ַ����
	m_pTestDataBuffer = &m_pLogicData->m_oTestSetupData.m_oTestDataBufferBase;	// �������ݻ�����
	m_bProcSensorTestOnField = false;	// �����¼Ӽ첨���ĳ�ʼ����

	CString strDesc;
	strDesc.Format("Test Project Start.From TestSetup Go Button.Method:%d;Type:%d;Nb:%d", m_iProcTestMethod, m_pTestProject->m_uiProjectType, m_pTestProject->m_uiTestNb);
	// ��������״̬����
	m_pSiteData->m_oRunTimeDataList.Set(1, "CThreadProcTest", "OnTestTaskBaseFromTestSetup", strDesc);

	// ��������
	ResumeProcTest();
	return true;
}

/**
* �������Բ������õ������������
* @param byte byTestOperation ���� 1-�������ԣ�0-ֹͣ����
* @return void
*/
bool CThreadProcTest::OnTestTaskNoise(byte byTestOperation)
{	
	// �жϣ�0-ֹͣ����
	if(0 == byTestOperation)
	{
		// �жϣ��߳̿���
		if(true == IsThreadFree())
		{
			return true;
		}		

		CString strDesc;
		strDesc.Format("Stop SeisMonitor Test.From SeisMonitorView SeisMonitor Button");
		// ��������״̬����
		m_pSiteData->m_oRunTimeDataList.Set(1, "CThreadProcTest", "OnTestTaskNoise", strDesc);

		m_bSwitchON = false;	// ֹͣ״̬
		return true;
	}
	// �жϣ�1-��������
	else if(1 == byTestOperation)
	{	
		// �жϣ��̹߳�����
		if(false == IsThreadFree())
		{
			return true;
		}
		// ��������������Ŀ�����Բ������õĲ�������
		if(false == m_pLogicData->OnSetupTestProjectForTestNoiseFromTestSetup())
		{
			return false;
		}
		m_pTestProject = &m_pLogicData->m_oTestSetupData.m_oTestProjectNoise;	// ������Ŀ���ж���
		m_pSocketTestSetFrame->m_pTestElementList = &m_pLogicData->m_oTestSetupData.m_oTestElementListNoise;	// ���Ե�Ԫ����
		m_pSocketTestSetFrame->m_uiIPCount = m_pSocketTestSetFrame->m_pTestElementList->m_uiCountUsed;	// ���òμӲ���IP��ַ����
		m_pTestDataBuffer = &m_pLogicData->m_oTestSetupData.m_oTestDataBufferNoise;	// �������ݻ�����

		CString strDesc;
		strDesc.Format("Start SeisMonitor Test.From SeisMonitorTestSetup Go Button");
		// ��������״̬����
		m_pSiteData->m_oRunTimeDataList.Set(1, "CThreadProcTest", "OnTestTaskNoise", strDesc);

		// ��������
		ResumeProcTest();
		return true;
	}
	return true;
}

/**
* �������Բ������õ������������
* @param unsigned CString strTestAbsoluteSpread ��������
* @return void
*/
bool CThreadProcTest::OnTestTaskNoise(CString strTestAbsoluteSpread)
{
	// �жϣ��̹߳�����
	if(false == IsThreadFree())
	{
		return true;
	}
	// ��������������Ŀ���������������ͼ�Ĳ�������
	if(false == m_pLogicData->OnSetupTestProjectForTestNoiseFromTestView(strTestAbsoluteSpread))
	{
		return false;
	}
	m_pTestProject = &m_pLogicData->m_oTestSetupData.m_oTestProjectNoise;	// ������Ŀ���ж���
	m_pSocketTestSetFrame->m_pTestElementList = &m_pLogicData->m_oTestSetupData.m_oTestElementListNoise;	// ���Ե�Ԫ����
	m_pSocketTestSetFrame->m_uiIPCount = m_pSocketTestSetFrame->m_pTestElementList->m_uiCountUsed;	// ���òμӲ���IP��ַ����
	m_pTestDataBuffer = &m_pLogicData->m_oTestSetupData.m_oTestDataBufferNoise;	// �������ݻ�����

	CString strDesc;
	strDesc.Format("Start SeisMonitor Test.From SeisMonitorView SeisMonitor Button");
	// ��������״̬����
	m_pSiteData->m_oRunTimeDataList.Set(1, "CThreadProcTest", "OnTestTaskNoise", strDesc);

	// ��������
	ResumeProcTest();
	return true;
}

/**
* �������Բ�����ͼ�Ļ�����������
* @param unsigned int uiTestAim ����Ŀ��
* @param unsigned unsigned int uiTestType �������� 1-�������ԣ�2-�첨������
* @param unsigned CString strTestAbsoluteSpread ��������
* @return bool true���ɹ���false��ʧ��
*/
bool CThreadProcTest::OnTestTaskBaseFromTestView(unsigned int uiTestAim, unsigned int uiTestType, CString strTestAbsoluteSpread)
{	
	// �жϣ��̹߳�����
	if(false == Lock())
	{
		return false;
	}
	// ���û���������Ŀ�����Բ���ͼ�εĲ�������
	if(false == m_pLogicData->OnSetupTestProjectForTestBaseFromTestView(uiTestAim, uiTestType, strTestAbsoluteSpread))
	{
		Unlock();
		return false;
	}
	m_pTestProject = &m_pLogicData->m_oTestSetupData.m_oTestProjectBase;	// ������Ŀ���ж���
	m_pSocketTestSetFrame->m_pTestElementList = &m_pLogicData->m_oTestSetupData.m_oTestElementListBase;	// ���Ե�Ԫ����
	m_pSocketTestSetFrame->m_uiIPCount = m_pSocketTestSetFrame->m_pTestElementList->m_uiCountUsed;	// ���òμӲ���IP��ַ����
	m_pTestDataBuffer = &m_pLogicData->m_oTestSetupData.m_oTestDataBufferBase;	// �������ݻ�����
	m_bProcSensorTestOnField = false;	// �����¼Ӽ첨���ĳ�ʼ����

	CString strDesc;
	strDesc.Format("Start Instrument/Sensor Test.From Instrument/SensorView Go Button");
	// ��������״̬����
	m_pSiteData->m_oRunTimeDataList.Set(1, "CThreadProcTest", "OnTestTaskBaseFromTestView", strDesc);

	// ��������
	ResumeProcTest();
	return true;
}

/**
* �����¼Ӽ첨���ĳ�ʼ����
* @param void
* @return void
*/
void CThreadProcTest::ProcSensorTestOnField()
{	
	// �жϣ��̹߳�����
	if(false == Lock())
	{
		return;
	}
	// ���û���������Ŀ�������¼Ӽ첨���ĳ�ʼ����
	if(false == m_pLogicData->OnSetupTestProjectForSensorTestOnField())
	{
		Unlock();
		return;
	}
	m_pTestProject = &m_pLogicData->m_oTestSetupData.m_oTestProjectBase;	// ������Ŀ���ж���
	m_pSocketTestSetFrame->m_pTestElementList = &m_pLogicData->m_oTestSetupData.m_oTestElementListBase;	// ���Ե�Ԫ����
	m_pSocketTestSetFrame->m_uiIPCount = m_pSocketTestSetFrame->m_pTestElementList->m_uiCountUsed;	// ���òμӲ���IP��ַ����
	m_pTestDataBuffer = &m_pLogicData->m_oTestSetupData.m_oTestDataBufferBase;	// �������ݻ�����
	m_bProcSensorTestOnField = true;	// �����¼Ӽ첨���ĳ�ʼ����	

	CString strDesc;
	strDesc.Format("Start Sensor OnField Test");
	// ��������״̬����
	m_pSiteData->m_oRunTimeDataList.Set(1, "CThreadProcTest", "ProcSensorTestOnField", strDesc);

	// ��������
	ResumeProcTest();
}

/**
* �����Ͳ�������֡
* @param void
* @return void
*/
void CThreadProcTest::ProcSendTestSetFrame()
{
	// ���òɼ���������˿�
	//m_pSocketTestSetFrame->m_oFrameTestSet.m_usPortListen = m_pSocketTestDataFrame->m_uiPortForTestDataFrame;
	m_pSocketTestSetFrame->m_oFrameTestSet.m_usPortListen =(unsigned short)m_pSocketTestSetFrame->m_uiPortForTestSet;

	CTestElementData* pTestElementData = NULL;	// ���Ե�Ԫ
	for(unsigned int i = 0; i < m_pSocketTestSetFrame->m_uiIPCount; i++)
	{
		// �õ�һ����Ԫ
		pTestElementData = m_pSocketTestSetFrame->m_pTestElementList->GetTestElementDataByIndex(i);
		// ����Ŀ��IP��ַ
		m_pSocketTestSetFrame->m_oFrameTestSet.m_uiIPAim = pTestElementData->m_uiIP;
		// ���ɲ�������֡
		m_pSocketTestSetFrame->MakeFrameDataForTestSet();
		// ���Ͳ�������֡
		m_pSocketTestSetFrame->SendTestSetFrame();
	}
}

/**
* ����AD��������
* @param void
* @return void
*/
void CThreadProcTest::ADSet()
{
	// ���òɼ���������˿�
	//m_pSocketTestSetFrame->m_oFrameTestSet.m_usPortListen = m_pSocketTestDataFrame->m_uiPortForTestDataFrame;
	m_pSocketTestSetFrame->m_oFrameTestSet.m_usPortListen =(unsigned short)m_pSocketTestSetFrame->m_uiPortForTestSet;
	// �������ݲɼ������Ŀ�Ķ˿�
	m_pSocketTestSetFrame->m_oFrameTestSet.m_usPortDataOut = (unsigned short)m_pSocketTestDataFrame->m_uiPortForTestDataFrame;

		//���ò�������
	m_pSocketTestSetFrame->m_uiSamplingRate=m_pTestBaseData->m_uiSamplingRate;
	m_pSocketTestSetFrame->m_oFrameTestSet.m_uiSamplingRate = m_pTestBaseData->m_uiSamplingRate;
//	CTestElementData* pTestElementData = NULL;	// ���Ե�Ԫ
	//for(unsigned int i = 0; i < m_pSocketTestSetFrame->m_uiIPCount; i++)
	//�㲥
// 	for(unsigned int i = 0; i < 1; i++)
// 	{
// 		// �õ�һ����Ԫ
// 		pTestElementData = m_pSocketTestSetFrame->m_pTestElementList->GetTestElementDataByIndex(i);
// 		// ����Ŀ��IP��ַ
// 		m_pSocketTestSetFrame->m_oFrameTestSet.m_uiIPAim = pTestElementData->m_uiIP;
// 		m_pSocketTestSetFrame->ofccheck=pTestElementData->ofccheck;
// 		// ���ɲ�������֡
// 		m_pSocketTestSetFrame->MakeFrameADSet();
// 		TRACE1("AD SET IP=%x\r\n", pTestElementData->m_uiIP);
// 		//m_pSocketTestSetFrame->MakeFrameDataForTestSet();
// 		// ���Ͳ�������֡
// 		//m_pSocketTestSetFrame->SendTestSetFrame();
// 	}
	// ���ɲ�������֡
//	m_pSocketTestSetFrame->MakeFrameADSet();
	// ADC��������
	m_pSocketTestSetFrame->OnADCSet();
	// ADC��ƯУ��
	m_pSocketTestSetFrame->OnADCZeroDrift();
}

/**
* �����Ͳ��Կ�ʼ֡
* @param void
* @return void
*/
void CThreadProcTest::ProcSendTestStartFrame()
{
	m_pSiteData->m_oCriticalSectionSystemTimeSite.Lock();
		// �õ�Ұ���豸ϵͳʱ��
		unsigned int uiTimeNow = m_pSiteData->m_uiSystemTimeSite + 1000;
	m_pSiteData->m_oCriticalSectionSystemTimeSite.Unlock();
	
	m_pTestRequest->m_uiTimeADBegin = uiTimeNow + 1000;
	m_pSocketTestSetFrame->m_oFrameTestSet.m_uiADTimeBegin = m_pTestRequest->m_uiTimeADBegin;	// AD�ɼ���ʼʱ��
	m_pTestRequest->m_uiTimeCollectBegin = m_pTestRequest->m_uiTimeADBegin + 500;
	m_pSocketTestSetFrame->m_oFrameTestSet.m_uiCollectTimeBegin = m_pTestRequest->m_uiTimeCollectBegin;	// �ɼ���ʼʱ��	

	// �õ�����ʱ��
	unsigned int uiCollectTime = m_pTestBaseData->m_uiSamplingLength;
	// �жϣ���¼�������ݣ��Ҽ�¼ʱ����ڲ���ʱ��
	if((1 == m_pTestProject->m_uiRecordResult) && (m_pTestProject->m_uiRecordLength > uiCollectTime))
	{
		// ����ʱ����Ϊ��¼ʱ��
		uiCollectTime = m_pTestProject->m_uiRecordLength;
	}
	// �õ����Ӳ���ʱ��
	unsigned int uiCollectTimeTail = FrameADCount * 1000 / m_pTestBaseData->m_uiSamplingRate;
	// �жϣ���С��λ
	if(0 < ((FrameADCount * 1000) % m_pTestBaseData->m_uiSamplingRate))
	{
		//���Ӳ���ʱ������1����
		uiCollectTimeTail++;
	}
	// �õ�����ʱ��
	uiCollectTime = uiCollectTime + uiCollectTimeTail;
	// �жϣ�������ĿΪҰ���������
	if(4000 == m_pTestProject->m_uiTestNb)	// Ұ���������
	{
		// �240Сʱ�������
		uiCollectTime = 864000000;	// 240Сʱ
	}
	// �õ���������ʱ��
	m_pTestRequest->m_uiTimeCollectEnd = m_pTestRequest->m_uiTimeCollectBegin + uiCollectTime;
	// ���ò�������ʱ��
	m_pSocketTestSetFrame->m_oFrameTestSet.m_uiCollectTimeEnd = m_pTestRequest->m_uiTimeCollectEnd;
	// ���òɼ���������˿�
	//m_pSocketTestSetFrame->m_oFrameTestSet.m_usPortListen = m_pSocketTestDataFrame->m_uiPortForTestDataFrame;
	m_pSocketTestSetFrame->m_oFrameTestSet.m_usPortListen =(unsigned short)m_pSocketTestSetFrame->m_uiPortForTestSet;
	// �������ݲɼ������Ŀ�Ķ˿�
	m_pSocketTestSetFrame->m_oFrameTestSet.m_usPortDataOut = (unsigned short)m_pSocketTestDataFrame->m_uiPortForTestDataFrame;
	// ���ɲ��Կ�ʼ֡
	m_pSocketTestSetFrame->MakeFrameDataForTestStart();
	// ����3��
	for(int i = 0; i < 3; i++)
	{
		// ���Ͳ��Կ�ʼ֡
		m_pSocketTestSetFrame->SendTestSetFrame();
	}
}

/**
* �����Ͳ��Կ�ʼ֡
* @param void
* @return void
*/
void CThreadProcTest::ProcSendTestADStart()
{
	irecevice=0;
	unsigned int TBtime=TBSleepTimeHigh;
	CString strDesc;

	// ���ɲ��Կ�ʼ֡
	//m_pSocketTestSetFrame->MakeFrameDataForTestStart();
	//m_pSocketTestSetFrame->MakeFrameADTestStart();
	// ����3��

// 	// ���Ͳ��Կ�ʼ֡
// 	//m_pSocketTestSetFrame->SendTestStartFrame();
// 	TRACE1("ADTimeBegin=%d\r\n", m_pSocketTestSetFrame->m_oFrameTestSet.m_uiADTimeBegin);
// 	//m_pSocketTestSetFrame->MakeFrameADTestStart();
// 	m_pSocketTestSetFrame->MakeFrameADClickTestStart1();
// 	Sleep(200);		//���ڷ����ٶ��������Եȴ�һ��
// 
// 	CTestElementData* pTestElementData = NULL;	// ���Ե�Ԫ
// 	for(unsigned int i = 0; i < m_pSocketTestSetFrame->m_uiIPCount; i++)
// 	{
// 		// �õ�һ����Ԫ
// 		pTestElementData = m_pSocketTestSetFrame->m_pTestElementList->GetTestElementDataByIndex(i);
// 		// ����Ŀ��IP��ַ
// 		m_pSocketTestSetFrame->m_oFrameTestSet.m_uiIPAim = pTestElementData->m_uiIP;
// 		m_pSocketTestSetFrame->ofccheck=pTestElementData->ofccheck;
// 		//strDesc.Format("Test AD REG Write IP=%d,ofccheck=%06x",pTestElementData->m_uiIP,pTestElementData->ofccheck);
// 		//m_pSiteData->m_oRunTimeDataList.Set(1, "CThreadProcTest", "ProcSendTestADStart", strDesc);
// 		// ���ɲ�������֡
// 		m_pSocketTestSetFrame->MakeFrameADIPTestStart();
// 		Sleep(70);		//���ڷ����ٶ��������Եȴ�һ��,���������������Ϊ50ms֡
// 	}
// 	Sleep(500);		//���ڷ����ٶ��������Եȴ�һ��
	// ��ʼADC����׼��
	m_pSocketTestSetFrame->OnADCPrepareToSample();

	m_pSiteData->m_oCriticalSectionSystemTimeSite.Lock();
	// �õ�Ұ���豸ϵͳʱ��
	unsigned int uiTimeNow = m_pSiteData->m_uiSystemTimeSite;
	m_pSiteData->m_oCriticalSectionSystemTimeSite.Unlock();
	TRACE1("Start begintime=%d\r\n", uiTimeNow);
	//TB��ʼ���ʱ��
	uiTimeNow=uiTimeNow+TBtime;

	m_pTestRequest->m_uiTimeADBegin = uiTimeNow + 0;
	m_pSocketTestSetFrame->m_oFrameTestSet.m_uiADTimeBegin = m_pTestRequest->m_uiTimeADBegin;	// AD�ɼ���ʼʱ��
	m_pTestRequest->m_uiTimeCollectBegin = m_pTestRequest->m_uiTimeADBegin + 500;
	m_pSocketTestSetFrame->m_oFrameTestSet.m_uiCollectTimeBegin = m_pTestRequest->m_uiTimeCollectBegin;	// �ɼ���ʼʱ��	

	// �õ�����ʱ��
	unsigned int uiCollectTime = m_pTestBaseData->m_uiSamplingLength;
	// �жϣ���¼�������ݣ��Ҽ�¼ʱ����ڲ���ʱ��
	if((1 == m_pTestProject->m_uiRecordResult) && (m_pTestProject->m_uiRecordLength > uiCollectTime))
	{
		// ����ʱ����Ϊ��¼ʱ��
		uiCollectTime = m_pTestProject->m_uiRecordLength;
	}
	// �õ����Ӳ���ʱ��
	unsigned int uiCollectTimeTail = 1000*(m_pTestBaseData->m_uiSamplingLength/m_pTestBaseData->m_uiSamplingRate) ;
	// �жϣ���С��λ
	if(0 < ((FrameADCount * 1000) % m_pTestBaseData->m_uiSamplingRate))
	{
		//���Ӳ���ʱ������1����
		uiCollectTimeTail++;
	}
	// �õ�����ʱ��
	//uiCollectTime = (uiCollectTime + uiCollectTimeTail)*4;
	uiCollectTime = (uiCollectTime + uiCollectTimeTail)*2;
	// �жϣ�������ĿΪҰ���������
	if(4000 == m_pTestProject->m_uiTestNb)	// Ұ���������
	{
		// �240Сʱ�������
		uiCollectTime = 864000000;	// 240Сʱ
	}
	// �õ���������ʱ��
	m_pTestRequest->m_uiTimeCollectEnd = m_pTestRequest->m_uiTimeCollectBegin + uiCollectTime;
	// ���ò�������ʱ��
	m_pSocketTestSetFrame->m_oFrameTestSet.m_uiCollectTimeEnd = m_pTestRequest->m_uiTimeCollectEnd;
	// ���òɼ���������˿�
	//m_pSocketTestSetFrame->m_oFrameTestSet.m_usPortListen = m_pSocketTestDataFrame->m_uiPortForTestDataFrame;
	m_pSocketTestSetFrame->m_oFrameTestSet.m_usPortListen =(unsigned short)m_pSocketTestSetFrame->m_uiPortForTestSet;
	// �������ݲɼ������Ŀ�Ķ˿�
	m_pSocketTestSetFrame->m_oFrameTestSet.m_usPortDataOut =(unsigned short) m_pSocketTestDataFrame->m_uiPortForTestDataFrame;

	strDesc.Format("Test AD Start tnow=%d,m_uiADTimeBegin=%d m_uiTimeCollectEnd=%d",m_pSiteData->m_uiSystemTimeSite,m_pSocketTestSetFrame->m_oFrameTestSet.m_uiADTimeBegin,m_pTestRequest->m_uiTimeCollectEnd);
	// ��������״̬����
	m_pSiteData->m_oRunTimeDataList.Set(1, "CThreadProcTest", "ProcSendTestADStart", strDesc);
	TRACE3("AD��ʼ tnow=%d,m_uiADTimeBegin=%d m_uiTimeCollectEnd=%d\r\n",m_pSiteData->m_uiSystemTimeSite,m_pSocketTestSetFrame->m_oFrameTestSet.m_uiADTimeBegin,m_pTestRequest->m_uiTimeCollectEnd);
	//��ʼTB
	//m_pSocketTestSetFrame->MakeFrameADClickTestStart2();
	m_pSocketTestDataFrame->okBegin=0;
	m_pSocketTestDataFrame->m_irevFrameCount=0;
	m_pSocketTestDataFrame->m_iFrameCount=0;

	for(int i=0;i<1;i++){
		m_pSocketTestSetFrame->MakeFrameADClickTestStart2();
		if(m_pSocketTestSetFrame->getTBcount>=0x03){
			TRACE2("getTBcount=%d TB Sendtime=%d\r\n", m_pSocketTestSetFrame->getTBcount,m_pSocketTestSetFrame->m_oFrameTestSet.m_uiADTimeBegin);
			break;
		}
		//TRACE2("���·���TB getTBcount=%d TB Sendtime=%d\r\n",m_pSocketTestSetFrame->getTBcount,iTimeNow); 
	}
	//m_pSocketTestSetFrame->MakeFrameADClickTestStart2();
	m_pSiteData->m_oCriticalSectionSystemTimeSite.Lock();
	//uiTimeNow = m_pSiteData->m_uiSystemTimeSite - 500;
	unsigned int iTimeNow = m_pSiteData->m_uiSystemTimeSite;
	m_pSiteData->m_oCriticalSectionSystemTimeSite.Unlock();
	TRACE1("ADClickTestStart2 tnow=%d\r\n",iTimeNow);
//	if(m_pTestRequest->m_uiType==22)
//		m_pSocketTestSetFrame->ViewSet(0);
}

/**
* �õ��������������
* @param void
* @return void
*/
void CThreadProcTest::GetAndProcTestData()
{
	unsigned int uiTimeNow;
	unsigned int uiFrameCount,idatacount=0;
	
	TRACE1("CThreadProcTest1 ID=%d\r\n", GetCurrentThreadId());
	MSG msg;
	while(true)
	{
		while(true)
		{
			// �õ���������յ��Ĳ�������֡������
			uiFrameCount = m_pSocketTestDataFrame->GetFrameCount1();
			// �жϣ���������֡������Ϊ0
			if(0 == uiFrameCount)
			{
				Sleep(5);
				break;
			}

		CString strDesc;
		if (uiFrameCount>200)
		{
			strDesc.Format("CThreadProcTest1 uiFrameCount=%d ",uiFrameCount);
			m_pSiteData->m_oRunTimeDataList.Set(3, "CThreadProcTest", "GetAndProcTestData 1", strDesc);
		}
		m_pSiteData->m_oCriticalSectionSystemTimeSite.Lock();
			uiTimeNow = m_pSiteData->m_uiSystemTimeSite;
		m_pSiteData->m_oCriticalSectionSystemTimeSite.Unlock();

			// ���εõ���������֡
			for(unsigned int i = 0; i < uiFrameCount; i++)
			{
				// �õ���������֡
				m_pSiteData->m_oSocketTestDataFrame.Lock();
				if(m_pSocketTestDataFrame->GetFrameData1()==false){	//�����������֡����������ʼ���ȴ���һ��idx=0
					TRACE2("ERROR m_irevFrameCount=%d m_iFrameCount=%d\r\n", m_pSocketTestDataFrame->m_irevFrameCount,m_pSocketTestDataFrame->m_iFrameCount);
					m_pSocketTestDataFrame->okBegin=0;
					m_pSocketTestDataFrame->m_irevFrameCount=0;
					m_pSocketTestDataFrame->m_iFrameCount=0;
					m_pSiteData->m_oSocketTestDataFrame.Unlock();
					break;
				}
				//GetMessage(&msg,0,0,0);
				m_pSiteData->m_oSocketTestDataFrame.Unlock();
				// ���ò�������
				SetTestData(m_pSocketTestDataFrame->m_oFrameTestData.m_pData,
					m_pSocketTestDataFrame->m_oFrameTestData.m_uiIPSource,
					m_pSocketTestDataFrame->m_oFrameTestData.m_usDataIndex);
				idatacount++;
				//ת����ͼ֡
				if(m_pTestRequest->m_uiType==22 && m_pSocketTestSetFrame->Viewtype==1)
					TranferView(m_pSocketTestDataFrame->m_oFrameTestData.m_pFrameData);
				else
					for(int i=0;i<MaxFDUCount;i++)
						FrameNum[i]=0;
			}

			if(false == JudgeProcCondition())	// �ж��Ƿ���Դ��������
			{
				return;
			}
			if((m_pTestRequest->m_uiTimeCollectEnd  < uiTimeNow))
				break;
		}
		m_pSiteData->m_oCriticalSectionSystemTimeSite.Lock();
			uiTimeNow = m_pSiteData->m_uiSystemTimeSite;
		m_pSiteData->m_oCriticalSectionSystemTimeSite.Unlock();

		m_pSocketTestSetFrame->OnReceiveADCSetReturn(1);
		// �жϣ��ɼ�����ʱ�䵽
		if((m_pTestRequest->m_uiTimeCollectEnd  < uiTimeNow))
		{
			TRACE1("SetTestData uiFrameCount=%d\r\n", uiFrameCount);
			TRACE3("END time=%d m_uiTimeCollectEnd=%d m_uiIPCount=%d\r\n", uiTimeNow,m_pTestRequest->m_uiTimeCollectEnd,m_pSocketTestSetFrame->m_uiIPCount);
			//TRACE2("END time=%d m_pSocketTestSetFrame->m_uiIPCount=%d\r\n", uiTimeNow,m_pSocketTestSetFrame->m_uiIPCount);
			CString strDesc;
			strDesc.Format("END uiTimeNow=%d m_uiTimeCollectEnd=%d m_uiIPCount=%d",uiTimeNow,m_pTestRequest->m_uiTimeCollectEnd,m_pSocketTestSetFrame->m_uiIPCount);
			m_pSiteData->m_oRunTimeDataList.Set(3, "CThreadProcTest", "END time ", strDesc);
			break;
		}
		//Wait(1);
		Sleep(0);
		if(false == JudgeProcCondition())	// �ж��Ƿ���Դ��������
		{
			return;
		}
	}
	if(false == JudgeProcCondition())	// �ж��Ƿ���Դ��������
	{
		return;
	}

	// ����������ݣ�����ǰ
	SetTestDataToProcAll();
}

/**
* ת���ɼ����ݵ���ͼ
* @param byte* lpData ����ָ��
* @param 16~19Ϊ�����豸��ͼ��ţ���0��ʼ
* @param 30~33Ϊ�豸����֡������Ե����豸����0��ʼ��
* @return void
*/
void CThreadProcTest::TranferView(byte* lpData)
{
	 CString m_strIPLCI=ViewIPStr;
	UINT m_uiPortLCI=ViewPort;
	CTestElementData* pTestElementData = NULL;	
	byte* pData = NULL;	
	int iViewGain=m_pSocketTestSetFrame->m_uiSamplingView;
	int itail=0,j=0;
	for(unsigned int i = 0; i < m_pSocketTestSetFrame->m_uiIPCount; i++)
	{
		// �õ�һ����Ԫ
		pTestElementData = m_pSocketTestSetFrame->m_pTestElementList->GetTestElementDataByIndex(i);
		if(m_pSocketTestDataFrame->m_oFrameTestData.m_uiIPSource==pTestElementData->m_uiIP){
			FDUNum=i;
			break;
		}
	}
	if(FrameNum[FDUNum]==0){
		ViewOffset[FDUNum]=0;
		ViewOffsetFrame[FDUNum]=0;
		memcpy(ViewBuf+FDUNum*FrameLength, lpData, FrameLength);
		memset(ViewBuf+FDUNum*FrameLength+36,0x55,FrameADCount72*3);
	}
	//ȡ������ƴ֡
	for(int i=0;ViewOffsetFrame[FDUNum]+i<(FrameADCount72);i+=iViewGain){
		memcpy(ViewBuf+FDUNum*FrameLength+36+ViewOffset[FDUNum]*3+j*3, lpData+36+ViewOffsetFrame[FDUNum]*3+i*3, 3);
		FrameNum[FDUNum]++;
		j++;
		//����֡��
		if(ViewOffsetFrame[FDUNum]+i>FrameADCount72){
			break;
		}
		//����֡��
		if(FrameNum[FDUNum]%FrameADCount72==0){
			//itail=i;
			//ViewOffsetFrame[FDUNum]+=(i+1)*iViewGain;
			break;
		}
	}
	itail=FrameADCount72-((ViewOffsetFrame[FDUNum]+j*iViewGain)%FrameADCount72);
	ViewOffset[FDUNum]+=j;

	//����֡
	if(FrameNum[FDUNum]%FrameADCount72==0){
		memcpy(ViewBuf+FDUNum*FrameLength+16,&FDUNum,sizeof(int));
		int itmp=FrameNum[FDUNum]/FrameADCount72-1;
		memcpy(ViewBuf+FDUNum*FrameLength+30,&itmp,sizeof(int));
		// ����֡
		int iCount = m_pSocketTestSetFrame->SendTo(ViewBuf+FDUNum*FrameLength, FrameLength, m_uiPortLCI, m_strIPLCI);
		ViewOffset[FDUNum]=0;
		memset(ViewBuf+FDUNum*FrameLength+36,0x11,FrameADCount72*3);
		//�������֡ʣ������
		j=0;
		if(itail!=0){
			for(int i=itail;ViewOffsetFrame[FDUNum]+i<(FrameADCount72);i+=iViewGain){
				memcpy(ViewBuf+FDUNum*FrameLength+36+j*3, lpData+36+ViewOffsetFrame[FDUNum]*3+i*3,3);
				FrameNum[FDUNum]++;
				j++;
			}
			itail=(FrameADCount72-(ViewOffsetFrame[FDUNum]+itail+j*iViewGain));
			if(itail!=0)
				ViewOffsetFrame[FDUNum]=(iViewGain-itail%iViewGain)%iViewGain;
			else
				ViewOffsetFrame[FDUNum]=itail;
		}
		ViewOffset[FDUNum]=j;
	}else
		if(itail!=0)
			ViewOffsetFrame[FDUNum]=(iViewGain-itail%iViewGain)%iViewGain;
		else
			ViewOffsetFrame[FDUNum]=itail;
}

/**
* ���ò�������
* @param byte* lpData ����ָ��
* @param unsigned int uiIP ����ָ��
* @param unsigned short usDataIndex ����λ������
* @return void
*/
void CThreadProcTest::SetTestData(byte* lpData, unsigned int uiIP, unsigned short usDataIndex)
{
	CString strDesc;
	CTestElementData* pTestElementData = NULL;
	// �жϣ�����IP��ַ���ڱ��β�����
	if(FALSE == m_pSocketTestSetFrame->m_pTestElementList->GetTestElementDataFromMap(uiIP, pTestElementData))
	{
		CString strDesc;
		strDesc.Format("dIP=%d m_uiFrameIndex=%d ERROR",uiIP,usDataIndex);
		m_pSiteData->m_oRunTimeDataList.Set(2, "CThreadProcTest", "SetTestData 5", strDesc);
		TRACE2("����IP��ַ���ڱ��β����� dIP=%d m_uiFrameIndex=%d\r\n",uiIP, usDataIndex); 
		return;
	}
	totalcount++;
	irecevice++;

	//���ÿ�ʼƫ����
	if(pTestElementData->m_uiDataBegin==-1)
		pTestElementData->m_uiDataBegin = usDataIndex-FrameADCount72;
	// �жϣ�����������λ
	if(usDataIndex < pTestElementData->m_uiDataIndexPreview && usDataIndex<FrameADCount72)	// ��λ
	{
		if(usDataIndex!=pTestElementData->IndexPreview)
		// ����������λ��������һ�ν�λ
		pTestElementData->m_uiDataStep = pTestElementData->m_uiDataStep + ADoffset;
	}
	int itmp=pTestElementData->m_uiFrameIndex;
	//pTestElementData->m_uiFrameIndex = (pTestElementData->m_uiDataStep + usDataIndex) / m_pTestDataBuffer->m_uiGroupDataCount;	// ��������
	if(usDataIndex!= pTestElementData->IndexPreview)
		// �õ�֡����
		pTestElementData->m_uiFrameIndex = (pTestElementData->m_uiDataStep + usDataIndex-pTestElementData->m_uiDataBegin) / m_pTestDataBuffer->m_uiGroupDataCount;	// ��������
	else
		if(pTestElementData->IndexPreview>ADoffset-2*FrameADCount72)
			pTestElementData->m_uiFrameIndex = (pTestElementData->m_uiDataStep + usDataIndex-pTestElementData->m_uiDataBegin-ADoffset) / m_pTestDataBuffer->m_uiGroupDataCount;	// ��������
		else
			pTestElementData->m_uiFrameIndex = (pTestElementData->m_uiDataStep + usDataIndex-pTestElementData->m_uiDataBegin) / m_pTestDataBuffer->m_uiGroupDataCount;	// ��������
	
	//��ֹ���
	if(pTestElementData->m_uiFrameIndex-itmp>12 && itmp-pTestElementData->m_uiFrameIndex>12){
		pTestElementData->m_uiFrameIndex=itmp;
		recevicecount++;
		strDesc.Format("dIP=%d m_uiFrameIndex=%d ERROR",uiIP,usDataIndex);
		m_pSiteData->m_oRunTimeDataList.Set(2, "CThreadProcTest", "SetTestData 4", strDesc);
		TRACE2("ƫ������� dIP=%d m_uiFrameIndex=%d\r\n",uiIP, usDataIndex); 
		return ;
	}

	int x=usDataIndex;
	if(usDataIndex<pTestElementData->m_uiDataIndexPreview && pTestElementData->IndexPreview==-1)
		x=usDataIndex+ADoffset;
	int	iSampleData1 = 0;
	int	iSampleData2 = 0;
	if(FrameADCount72==FrameADCount){
		memcpy(&iSampleData1, lpData, 3);
		memcpy(&iSampleData2, lpData+9, 3);
	}else{
		memcpy(&iSampleData1, lpData, 4);
		memcpy(&iSampleData2, lpData+9, 3);
	}
	if(recevicecount%(MaxFDUCount*5)==0 || recevicecount<MaxFDUCount*4){
	//if(recevicecount%MaxFDUCount==0 || recevicecount<MaxFDUCount){
		strDesc.Format("dIP=%d m_uiFrameIndex=%d %d Index=%d d1=%x d2=%x %d %d %d",uiIP,usDataIndex,x-pTestElementData->m_uiDataIndexPreview,m_pTestDataBuffer->m_uiFrameIndex,iSampleData1,iSampleData2,irecevice,pTestElementData->m_uiDataStep,pTestElementData->IndexPreview);
		m_pSiteData->m_oRunTimeDataList.Set(3, "CThreadProcTest", "SetTestData 1", strDesc);
		//TRACE3("��������֡2=%d %d IP=%d\r\n", usDataIndex,x-pTestElementData->m_uiDataIndexPreview,uiIP );
	}
	if(m_pTestRequest->m_uiType==22 && (recevicecount%(m_pSocketTestSetFrame->m_uiIPCount*600))==0){
		strDesc.Format("dIP=%d m_uiFrameIndex=%d %d Index=%d d1=%x d2=%x %d %d %d",uiIP,usDataIndex,x-pTestElementData->m_uiDataIndexPreview,m_pTestDataBuffer->m_uiFrameIndex,iSampleData1,iSampleData2,irecevice,pTestElementData->m_uiDataStep,pTestElementData->IndexPreview);
		m_pSiteData->m_oRunTimeDataList.Set(3, "CThreadProcTest", "SetTestData 8", strDesc);
	}
	//�жϣ��Ƿ��ж�֡���
	//if(pTestElementData->m_uiFrameIndex - m_pTestDataBuffer->m_uiFrameIndex!=1){
	if(x-pTestElementData->m_uiDataIndexPreview!=FrameADCount72 && x-pTestElementData->m_uiDataIndexPreview!=0 && (x-pTestElementData->m_uiDataIndexPreview)<FrameADCount72*3 && pTestElementData->m_uiFrameIndex>1 && pTestElementData->IndexPreview==-1){
		//��ʱֻ��һ��
		CString strDesc;
		//����һ������
		int y=usDataIndex-FrameADCount72;
		if(y<0)
			y=y+ADoffset;
		if(y!=pTestElementData->IndexPreview){
			strDesc.Format("dIP=%d m_uiFrameIndex=%d",uiIP, y);
			m_pSiteData->m_oRunTimeDataList.Set(3, "CThreadProcTest", "SetTestData 3", strDesc);
			TRACE2("����������֡�� dIP=%d m_uiFrameIndex=%d\r\n",uiIP, y); 
			pTestElementData->IndexPreview=y;
			lossframecount++;
			m_pSocketTestSetFrame->ReloadTestDataFrame(uiIP,y);
		}
	}
	//����ǲ���֡�ɹ�
	if( (pTestElementData->IndexPreview==usDataIndex) ){
		pTestElementData->m_uiDataIndexPreview=usDataIndex+FrameADCount72;
		if(pTestElementData->m_uiDataIndexPreview>ADoffset)
			pTestElementData->m_uiDataIndexPreview=pTestElementData->m_uiDataIndexPreview-ADoffset;
		pTestElementData->IndexPreview=-1;
	}else{
		// ��¼��һ����������
		pTestElementData->m_uiDataIndexPreview = usDataIndex;
		//������2֮֡��û�в���,�ָ�ԭʼ״̬
		if((usDataIndex-pTestElementData->IndexPreview)>FrameADCount72*2)
			pTestElementData->IndexPreview=-1;
	}
	// ���ò�������
	m_pTestDataBuffer->SetElementTestDataOfOneFrame(lpData, pTestElementData->m_uiIndex, pTestElementData->m_uiFrameIndex);
	recevicecount++;

	// �жϣ�Ұ���豸������һ��ɼ�
	if(pTestElementData->m_uiFrameIndex > m_pTestDataBuffer->m_uiFrameIndex)
	{
		// ���ò������ݴ洢����֡����
		m_pTestDataBuffer->m_uiFrameIndex = pTestElementData->m_uiFrameIndex;
		// ���ǰһ��ǰ����������
		if((m_pTestDataBuffer->m_uiFrameIndex - 1) > m_pTestDataBuffer->m_uiFrameIndexWrite)
		{
			saveecount++;
			// �����������
			SetTestDataToProc();
			// ���ò������ݴ洢�����Ѵ���֡����
			m_pTestDataBuffer->m_uiFrameIndexWrite = m_pTestDataBuffer->m_uiFrameIndex - 1;
		}
	}

}

/**
* �����������
* @param void
* @return void
*/
void CThreadProcTest::SetTestDataToProc()
{
	// ����������ݣ��������
	SetTestDataToProcNoise();
	// ����������ݣ������������
	SetTestDataToProcFileTestDataWrite();
}

/**
* ����������ݣ��������
* @param void
* @return void
*/
void CThreadProcTest::SetTestDataToProcNoise()
{
	// �жϣ���������
	if(1 == m_pTestRequest->m_uiAim)
	{
		return;
	}
	// �жϣ���һ֡
	if(0 == m_pTestDataBuffer->m_uiFrameIndex)
	{
		return;
	}
	// �жϣ��������ݴ洢�����Ѵ���֡�������ڵ�����������������緢�ͼ���
	if(m_pTestDataBuffer->m_uiFrameIndexWrite >= m_uiTestNoiseNetSendCount)
	{
		// ������������������緢�ͼ���
		m_uiTestNoiseNetSendCount = m_uiTestNoiseNetSendCount + m_uiTestNoiseNetSendStep;
		CTestElementData* pTestElementData = NULL;	
		byte* pData = NULL;	
//		TRACE1("������⴦��֡������%d\r\n", m_pTestDataBuffer->m_uiFrameIndexWrite);
		for(unsigned int i = 0; i < m_pSocketTestSetFrame->m_uiIPCount; i++)
		{
			// �õ�һ����Ԫ
			pTestElementData = m_pSocketTestSetFrame->m_pTestElementList->GetTestElementDataByIndex(i);
			// �õ����Ե�Ԫһ�β������ݣ��������
			pData = m_pTestDataBuffer->GetElementTestDataOfOneTestForNoiseMonitor(m_pTestDataBuffer->m_uiFrameIndexWrite, i);
			// ����
			pTestElementData->CalculateTestResult(m_pTestRequest->m_uiType, pData, FrameADCount,(float)m_pTestDataBuffer->m_AVGNoiseValue);

		}
		// �������������Խ��
		SendTestResultNoise();
	}
}

/**
* ����������ݣ������������
* @param void
* @return void
*/
void CThreadProcTest::SetTestDataToProcFileTestDataWrite()
{
	// �жϣ���һ֡
	if(0 == m_pTestDataBuffer->m_uiFrameIndex)
	{
		return;
	}
	// �жϣ�����ʽ 2-�������
	if(2 == m_iProcTestMethod)
	{
		return;
	}
	// �жϣ�����¼��������
	if(0 == m_pTestProject->m_uiRecordResult)
	{
		return;
	}

	CTestElementData* pTestElementData = NULL;	
	byte* pBlockData = NULL;	
	for(unsigned int i = m_pTestDataBuffer->m_uiFrameIndexWrite; i < (m_pTestDataBuffer->m_uiFrameIndex - 1); i++)
	{
		// �õ�һ֡�������ݣ���λ��
		pBlockData = m_pTestDataBuffer->GetBlockTestDataOneFrame(i);
		// д���������ļ�
		FileTestDataWrite(pBlockData, m_pTestDataBuffer->m_uiBlockByteSizeUsed);
	}
}

/**
* ����������ݣ�������������ǰ
* @param void
* @return void
*/
void CThreadProcTest::SetTestDataToProcAll()
{
	// �жϣ�����ʽ 2-�������
	if(2 == m_iProcTestMethod)
	{
		return;
	}
	// �жϣ���һ֡
	if(0 == m_pTestDataBuffer->m_uiFrameIndex)
	{
		return;
	}
	
	//����������ݣ�������������ǰ�������������
	SetTestDataToProcAllFileTestDataWrite();
	// �õ����Խ������������
	GetTestResultBase();
	// ���ò��Խ������������
	SetTestResultBase();
	// ���Ͳ��Խ������������
	SendTestResultBase();
}

/**
* ����������ݣ�������������ǰ�������������
* @param void
* @return void
*/
void CThreadProcTest::SetTestDataToProcAllFileTestDataWrite()
{
	if(0 == m_pTestProject->m_uiRecordResult)
	{
		return;
	}
	// ��������д�������ļ�
	byte* pBlockData = NULL;
	TRACE1("�յ���������֡��������%d\r\n", m_pTestDataBuffer->m_uiFrameIndex);
	for(unsigned int i = m_pTestDataBuffer->m_uiFrameIndexWrite; i <= m_pTestDataBuffer->m_uiFrameIndex; i++)
	{
		// �õ�һ֡�������ݣ���λ��
		pBlockData = m_pTestDataBuffer->GetBlockTestDataOneFrame(i);
		// д���������ļ�
		FileTestDataWrite(pBlockData, m_pTestDataBuffer->m_uiBlockByteSizeUsed);
//		TRACE1("д���������ļ� �������%d\r\n", i);
	}
}

/**
* �õ����Խ������������
* @param void
* @return void
*/
void CThreadProcTest::GetTestResultBase()
{
	CTestElementData* pTestElementData = NULL;	
	byte* pData = NULL;	
	bool bfinish=false;
	m_Revidx=0;
	int upADCDataNum=0;
	lineCount=ReceiveDataPoint;
	for(unsigned int i = 0; i < m_pSocketTestSetFrame->m_uiIPCount; i++)
	{
		// �õ�һ����Ԫ
		pTestElementData = m_pSocketTestSetFrame->m_pTestElementList->GetTestElementDataByIndex(i);
		// �õ����Ե�Ԫһ�β�������
		pData = m_pTestDataBuffer->GetElementTestDataOfOneTest(i, m_pTestBaseData->m_uiSamplingPointCount);
		// ����
		pTestElementData->CalculateTestResult(m_pTestRequest->m_uiType, pData, m_pTestBaseData->m_uiSamplingPointCount,(float)m_pTestDataBuffer->m_AVGNoiseValue);
		//TRACE2("m_uiIP=%d m_AVGNoiseValue=%f\r\n",pTestElementData->m_uiIP, pTestElementData->m_fInstrumentNoiseValue);
		rev_count[i]=ReceiveDataPoint;
		m_pADCDataSaveToFile.OnSaveADCToFile(pData+(FrameADCount)*4,&upADCDataNum,rev_count, m_pSocketTestSetFrame->m_uiIPCount, bfinish,0, m_pSocketTestSetFrame->m_uiIPCount);
		// �ж�
		pTestElementData->JudgeTestResult(m_pTestRequest->m_uiType);
	}
}

/**
* ���ò��Խ������������
* @param void
* @return void
*/
void CThreadProcTest::SetTestResultBase()
{
	// �жϣ���������
	if(1 == m_pTestRequest->m_uiAim)
	{
		m_pSiteData->SetTestResultBase(m_pTestRequest->m_uiType, m_pSocketTestSetFrame->m_pTestElementList);
	}
	// �жϣ��첨������
	else if(2 == m_pTestRequest->m_uiAim)
	{
		m_pLogicData->SetTestResultBase(m_pTestRequest->m_uiType, m_pSocketTestSetFrame->m_pTestElementList, m_bProcSensorTestOnField);
	}
}

/**
* ���Ͳ��Խ��
* @param void
* @return void
*/
void CThreadProcTest::SendTestResult()
{
	unsigned int uiDataSize = 0;
	unsigned short usDataCount = 0;
	// �����μ��㣬��������������
	unsigned int uiDataBatchCount = m_pSocketTestSetFrame->m_pTestElementList->GetTestDataBatchCount();
	for(unsigned int i = 0; i < uiDataBatchCount; i++)
	{
		// �����μ��㣬��������������
		m_pSocketTestSetFrame->m_pTestElementList->GetTestDataByBatchIndex(m_pTestRequest->m_uiType, i, uiDataSize, usDataCount);
		// ���ɲ�������֡
		m_pSocketInterfaceDataSend->CreateOutputDataFrameTest(m_pTestRequest->m_uiType, uiDataSize, usDataCount, m_pSocketTestSetFrame->m_pTestElementList->m_pTestData);
		// ��������֡
		int iCount=m_pSocketInterfaceDataSend->SendDataFrame();
		//TRACE2("���Խ��֡���ͣ�֡��С%d %d\r\n", iCount,i);
		// �жϣ����ܼ�������
		if(false == JudgeProcCondition())
		{
			break;
		}
	}
}

/**
* ���Ͳ��Խ������������
* @param void
* @return void
*/
void CThreadProcTest::SendTestResultBase()
{
	// �жϣ�����ʽ 2-�������
	if(2 == m_iProcTestMethod)
	{
		return;
	}
	// ���Ͳ��Խ��
	SendTestResult();
}

/**
* ���Ͳ��Խ�����������
* @param void
* @return void
*/
void CThreadProcTest::SendTestResultNoise()
{
	// �жϣ�����ʽ 1-��������
	if(1 == m_iProcTestMethod)
	{
		return;
	}
	// ���Ͳ��Խ��
	SendTestResult();
}

/**
* ֹͣ���ڽ������ݲɼ�������
* @param void
* @return void
*/
void CThreadProcTest::StopInstrumentWhichIsCollecting()
{
	unsigned int uiFrameCount;
	// ���������Ͳɼ�����֡
	ProcSendTestEndFrame(0xFFFFFFFF);
	while(true)
	{
		// �õ�����˿��յ�����֡����
		uiFrameCount = m_pSocketTestDataFrame->GetFrameCount1();
		TRACE1("�յ�����֡����end��%d\r\n", uiFrameCount);
		if(0 == uiFrameCount)
		{
			break;
		}
		CString strDesc;
		strDesc.Format("End uiFrameCount=%d",uiFrameCount);
		m_pSiteData->m_oRunTimeDataList.Set(3, "CThreadProcTest", "SetTestData STOP", strDesc);

		// ��������
		for(unsigned int i = 0; i < uiFrameCount; i++)
		{
			// �õ�֡���ݣ�������
			m_pSocketTestDataFrame->GetFrameDataNotParse1();

		}
		// �ȴ�
		Wait(2);
	}
}

/**
* ������������������緢�Ͳ���
* @param void
* @return void
*/
void CThreadProcTest::SetTestNoiseNetSendStep()
{
	// �жϣ���������
	if(1 == m_pTestRequest->m_uiAim)
	{
		return;
	}
	// ������������������緢�Ͳ���
	m_uiTestNoiseNetSendStep = NetSendStep / (m_pTestBaseData->m_uiSamplingRate * FrameADCount);
	if(m_uiTestNoiseNetSendStep == 0)
	{
		m_uiTestNoiseNetSendStep = 1;
	}
	// ��������������緢�ͼ���
	m_uiTestNoiseNetSendCount = 0;
}

/**
* �����Ͳ���ֹͣ֡
* @param void
* @return void
*/
void CThreadProcTest::ProcSendTestEndFrame(unsigned int uiInstrumentIP)
{
	m_pSiteData->m_oCriticalSectionSystemTimeSite.Lock();
		m_pSocketTestSetFrame->m_oFrameTestSet.m_uiCollectTimeEnd = m_pSiteData->m_uiSystemTimeSite;	// �ɼ�����ʱ��
	m_pSiteData->m_oCriticalSectionSystemTimeSite.Unlock();
	// ����21��
	for(int i = 0; i <= 1; i++)
	{
		// ���Խ���ʱ�����50����
		m_pSocketTestSetFrame->m_oFrameTestSet.m_uiCollectTimeEnd = m_pSocketTestSetFrame->m_oFrameTestSet.m_uiCollectTimeEnd + 50;
		// ���ɲ��Խ���֡
		m_pSocketTestSetFrame->MakeFrameADTestSTOP(uiInstrumentIP);
		//m_pSocketTestSetFrame->MakeFrameDataForTestEnd(uiInstrumentIP);
		//TRACE1("FrameADTestSTOP��m_uiCollectTimeEnd=%d\r\n", m_pSocketTestSetFrame->m_oFrameTestSet.m_uiCollectTimeEnd);
		// ���Ͳ��Խ���֡
		//m_pSocketTestSetFrame->SendTestEndFrame();
	}
}