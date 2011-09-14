// ThreadProcSiteDataOutput.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "TestSiteManage.h"
#include "ThreadProcSiteDataOutput.h"


// CThreadProcSiteDataOutput

IMPLEMENT_DYNCREATE(CThreadProcSiteDataOutput, CWinThread)

CThreadProcSiteDataOutput::CThreadProcSiteDataOutput()
{
	// �Ƿ���״̬
	m_bWork = false;
	// �Ƿ�ر��߳�
	m_bClose = false;
}

CThreadProcSiteDataOutput::~CThreadProcSiteDataOutput()
{
}

BOOL CThreadProcSiteDataOutput::InitInstance()
{
	// TODO: �ڴ�ִ���������̳߳�ʼ��
	return TRUE;
}

int CThreadProcSiteDataOutput::ExitInstance()
{
	// TODO: �ڴ�ִ���������߳�����
	return CWinThread::ExitInstance();
}

BEGIN_MESSAGE_MAP(CThreadProcSiteDataOutput, CWinThread)
END_MESSAGE_MAP()

// CThreadProcSiteDataOutput ��Ϣ�������

/**
* �߳�������
* @param void
* @return int
*/
int CThreadProcSiteDataOutput::Run()
{
	// ѭ����ֱ���رձ�־Ϊ��
	while(true)
	{
		// �жϹرձ�־�Ƿ�Ϊ��
		if(true == m_bClose)
		{
			break;
		}
		// �ֳ��������
		ProcSiteDataOutput();
		// �жϹرձ�־�Ƿ�Ϊ��
		if(true == m_bClose)
		{
			break;
		}
		// ����1000����
		Wait(20);
	}
	// �ֳ���������߳��̹߳رձ�־Ϊ��
	m_pSiteData->m_bProcSiteDataOutputClose = true;
	// ����
	return CWinThread::Run();
}

/**
* ��ʼ���߳�
* @param void
* @return bool true���ɹ���false��ʧ��
*/
bool CThreadProcSiteDataOutput::OnInit()
{
	// �Ƿ���״̬
	m_bWork = false;
	// �Ƿ�ر��߳�
	m_bClose = false;

	// ����־�ļ�
	LogFileOpen();
	// ��־�ļ������Ƿ�ر�
	m_bLogFileClose = false;	
	return true;
}

/**
* �ر��߳�
* @param void
* @return bool true���ɹ���false��ʧ��
*/
bool CThreadProcSiteDataOutput::OnClose()
{
	// �Ƿ�ر��߳�
	m_bClose = true;
	// ��־�ļ������Ƿ�ر�
	m_bLogFileClose = true;	
	// ����־�ļ�
	LogFileClose();
	return true;
}

/**
* �߳̿�ʼ����
* @param void
* @return bool true���ɹ���false��ʧ��
*/
bool CThreadProcSiteDataOutput::OnWork()
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
bool CThreadProcSiteDataOutput::OnStop()
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
void CThreadProcSiteDataOutput::Wait(int iWaitStopCount)
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
bool CThreadProcSiteDataOutput::JudgeProcCondition()
{	
	// ɾ��������·�ɴ����߳���������
	if(true == m_pSiteData->m_bProcDeleteRunning)
	{		
		m_pSiteData->m_bProcSiteDataOutputPause = true;	// �߳���ͣ
		return false;
	}
	else
	{		
		m_pSiteData->m_bProcSiteDataOutputPause = false;	// �߳�����
	}
	// �ǹ���״̬
	if(false == m_bWork)
	{		
		m_pSiteData->m_bProcSiteDataOutputStop = true;	// �ֳ���������߳��߳�ֹͣ
		return false;
	}
	else
	{
		m_pSiteData->m_bProcSiteDataOutputStop = false;	// �ֳ���������߳��̹߳���
	}
	return true;
}

/**
* �ֳ��������
* @param void
* @return void
*/
void CThreadProcSiteDataOutput::ProcSiteDataOutput()
{	
	// �ж��Ƿ���Դ��������
	if(false == JudgeProcCondition())
	{
		return;
	}

	// ���������Ϣ����־�ļ�
	OutputRunTimeDataToLogFile();

	// �ж��ֳ������Ƿ��ڹ涨ʱ�����ޱ仯
	if(false == m_pSiteData->JudgeSiteDataChangedTime())
	{
		return;
	}
	// �ж�����ɾ���߳�ʧ��
	if(false == m_pThreadProcDelete->Lock())
	{
		return;
	}
	// �����ֳ���������߳��������б�־Ϊ��
	m_pSiteData->m_bProcSiteDataOutputRunning = true;
	// �жϵȴ������߳���ͣ�ɹ�
	if(true == WaitOtherThreadProcPause())
	{
		// �������鵽�������
		CopyArrayForOutput();
		// �����ֳ���������߳��������б�־Ϊ��
		m_pSiteData->m_bProcSiteDataOutputRunning = false;
		// ����ɾ���߳�
		m_pThreadProcDelete->Unlock();
		// �����ϴ��ֳ����ݱ仯ʱ��
		m_pSiteData->ResetSiteDataChangedTime();
		// ����������ļ�
		if(true == OutputToFile())
		{
			// �����ļ����浽FTP������
			if(true == SaveDataFileToFTPServer())
			{
				// ��ͻ��˷����ֳ������������֪ͨ����
				SendSiteOutputCmdToClient();
				// ��������״̬����
				m_pSiteData->m_oRunTimeDataList.Set(1, "CThreadProcSiteDataOutput", "ProcSiteDataOutput", "");
			}
			else
			{
				// ��������״̬����
				m_pSiteData->m_oRunTimeDataList.Set(2, "CThreadProcSiteDataOutput", "ProcSiteDataOutput", "SaveFileToFTPServer Fail");
			}
		}
		else
		{
			// ��������״̬����
			m_pSiteData->m_oRunTimeDataList.Set(2, "CThreadProcSiteDataOutput", "ProcSiteDataOutput", "OutputToFile Fail");
		}
		// �����¼Ӽ첨���ĳ�ʼ����
		ProcSensorTestOnField();
	}
	else	// �ȴ������߳���ͣʧ��
	{
		// �����ֳ���������߳��������б�־Ϊ��
		m_pSiteData->m_bProcSiteDataOutputRunning = false;
		// ����ɾ���߳�
		m_pThreadProcDelete->Unlock();
	}
}

/**
* �ȴ������߳���ͣ
* @note ɾ���̹߳���ʱ����Ҫ��ͣ���̣߳��װ������̡߳�β�������̡߳�·�ɼ����̡߳�����IP��ַ�����߳�
* @param void
* @return bool true���ɹ���false��ʧ��
*/
bool CThreadProcSiteDataOutput::WaitOtherThreadProcPause()
{
	// �ȴ�����
	int iWaitCount = 0;
	while(true)
	{	
		if((true == m_pSiteData->m_bProcHeadFramePause)	// �װ������߳���ͣ
			&& (true == m_pSiteData->m_bProcTailFramePause)	// β�������߳���ͣ
			&& (true == m_pSiteData->m_bProcMonitorRoutPause)	// ·�ɼ����߳���ͣ
			&& (true == m_pSiteData->m_bProcIPDistributePause))	// ����IP��ַ�����߳���ͣ
		{
			break;
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
* �����ֳ��������鵽�����������
* @param void
* @return bool true���ɹ���false��ʧ��
*/
bool CThreadProcSiteDataOutput::CopyArrayForOutput()
{
	// �����������鵽�������
	m_pSiteData->m_oInstrumentList.CopyInstrumentArrayForOutput();
	// ����·�����鵽�������
	m_pSiteData->m_oRoutList.CopyRoutArrayForOutput();
	// ���Ʋ�����鵽�������
	m_pLogicData->m_oSurveySetupData.m_oChannelList.CopyChannelArrayForOutput();
	return true;
}

/**
* ����ֳ����ݵ������ļ�
* @param void
* @return bool true���ɹ���false��ʧ��
*/
bool CThreadProcSiteDataOutput::OutputToFile()
{
	try
	{
		CString strFileInstrument, strFileRout, strFileChannel;
		UINT uiFileSize;
		strFileInstrument = "..\\data\\FileInstrument.dat";
		strFileRout = "..\\data\\FileRout.dat";
		strFileChannel = "..\\data\\FileChannel.dat";
		uiFileSize = sizeof(CInstrument) * m_pSiteData->m_oInstrumentList.m_uiCountAll;
		OutputToFile(strFileInstrument, (byte*)m_pSiteData->m_oInstrumentList.m_pArrayInstrumentOutput, uiFileSize);
		uiFileSize = sizeof(CRout) * m_pSiteData->m_oRoutList.m_uiCountAll;
		OutputToFile(strFileRout, (byte*)m_pSiteData->m_oRoutList.m_pArrayRoutOutput, uiFileSize);
		uiFileSize = sizeof(CChannelSetupData) * m_pLogicData->m_oSurveySetupData.m_oChannelList.m_uiCountAll;
		OutputToFile(strFileChannel, (byte*)m_pLogicData->m_oSurveySetupData.m_oChannelList.m_pArrayChannelOutput, uiFileSize);
		return true;
	}
	catch (CException* e)
	{
		return false;
	}
}

/**
* �����ļ����浽FTP������
* @param void
* @return bool true���ɹ���false��ʧ��
*/
bool CThreadProcSiteDataOutput::SaveDataFileToFTPServer()
{
	bool bReturn = false;
	CInternetSession oSession;
	BOOL bData;
	CFtpConnection* pConnection = oSession.GetFtpConnection(m_pSiteData->m_strIPFTPServer);

	bData = SaveDataFileToFTPServer(pConnection, "..\\data\\FileInstrument.dat", "\\data\\FileInstrument.dat");
	if(TRUE == bData)
	{
		bData = SaveDataFileToFTPServer(pConnection, "..\\data\\FileRout.dat", "\\data\\FileRout.dat");
		if(TRUE == bData)
		{
			bData = SaveDataFileToFTPServer(pConnection, "..\\data\\FileChannel.dat", "\\data\\FileChannel.dat");
			if(TRUE == bData)
			{
				bReturn = true;
			}
		}
	}
	pConnection->Close();
	delete pConnection;
	return bReturn;
}

/**
* �����ļ����浽FTP������
* @param CFtpConnection* pConnection FTP����
* @param CString strFile Դ�ļ���
* @param CString strFile Ŀ���ļ���
* @return bool true���ɹ���false��ʧ��
*/
bool CThreadProcSiteDataOutput::SaveDataFileToFTPServer(CFtpConnection* pConnection, CString strFileSource, CString strFileAim)
{
	BOOL bData;
	int iCount = 0;
	while(true)
	{
		bData = pConnection->PutFile(strFileSource, strFileAim);
		if(TRUE == bData)
		{
			return true;
		}
		// �ж��Ƿ���Դ��������
		if(false == JudgeProcCondition())
		{
			return false;
		}
		iCount++;
		if(4 <= iCount)
		{
			return false;
		}
		Sleep(50);
	}
	return false;
}

/**
* ����ֳ����ݵ������ļ�
* @param CString strFileName �ļ���
* @param byte* pData ����ָ��
* @param UINT uiFileSize ���ݳ���
* @return bool true���ɹ���false��ʧ��
*/
bool CThreadProcSiteDataOutput::OutputToFile(CString strFileName, byte* pData, UINT uiFileSize)
{
	CStdioFile oFile;
	oFile.Open(strFileName, CFile::modeCreate | CFile::modeWrite | CFile::typeBinary);
	oFile.Write(pData, uiFileSize);
	oFile.Close();
	return true;
}

/**
* ��ͻ��˷����ֳ������������֪ͨ����
* @param void
* @return void
*/
void CThreadProcSiteDataOutput::SendSiteOutputCmdToClient()
{
	// �жϣ����������ޱ仯
	if(false == m_pSiteData->m_bTestDataChanged)
	{
		// Ϊ������������֡��������ӿ�׼�����߳�ͬ����������
		m_pSiteData->m_oCriticalSectionInterfaceCmdSend.Lock();
			// �����ֳ��������֪ͨ����֡
			m_pSocketInterfaceCmdSend->m_oFrameInterface.MakeSiteDataOutputCmdFrame();
			// ��������֡
			m_pSocketInterfaceCmdSend->SendCommandFrame();
		// Ϊ������������֡��������ӿ�׼�����߳�ͬ���������
		m_pSiteData->m_oCriticalSectionInterfaceCmdSend.Unlock();
	}
	// �жϣ����������б仯
	else
	{
		m_pSiteData->m_bTestDataChanged = false;
	}
}

/**
* ������ú���ֳ�����
* @param void
* @return void
*/
void CThreadProcSiteDataOutput::OutputToFileForReset()
{
	// �������鵽�������
	CopyArrayForOutput();
	// ����������ļ�
	if(true == OutputToFile())
	{
		// �����ļ����浽FTP������
		if(true == SaveDataFileToFTPServer())
		{
			// ��ͻ��˷����ֳ������������֪ͨ����
			SendSiteOutputCmdToClient();
			// ��������״̬����
			m_pSiteData->m_oRunTimeDataList.Set(1, "CThreadProcSiteDataOutput", "OutputToFileForReset", "");
			return;
		}
	}
	// ��������״̬����
	m_pSiteData->m_oRunTimeDataList.Set(2, "CThreadProcSiteDataOutput", "OutputToFileForReset", "Reset Fail");
}

/**
* ����־�ļ�
* @param void
* @return void
*/
void CThreadProcSiteDataOutput::LogFileOpen()
{
	SYSTEMTIME oSystemTime;
	GetLocalTime(&oSystemTime);
	CString strDate;	// ����
	CString strTime;	// ʱ��
	CString strFileName;	// ʱ��
	strDate.Format("%d-%d-%d", oSystemTime.wYear, oSystemTime.wMonth, oSystemTime.wDay);	// ����
	strTime.Format("%d %d %d", oSystemTime.wHour, oSystemTime.wMinute, oSystemTime.wSecond);	// ʱ��
	strFileName.Format("..\\LogFileLine\\LogFileLine%s %s.xml", strDate, strTime);
	m_oLogFile.Open(strFileName, CFile::modeCreate | CFile::modeWrite | CFile::typeText);
}

/**
* �ر���־�ļ�
* @param void
* @return void
*/
void CThreadProcSiteDataOutput::LogFileClose()
{
	m_oLogFile.Close();
}

/**
* ���������Ϣ����־�ļ�
* @param void
* @return void
*/
void CThreadProcSiteDataOutput::OutputRunTimeDataToLogFile()
{
	// ��־�ļ������Ƿ�ر�
	if(true == m_bLogFileClose)
	{
		return;
	}
	CString strData = "";
	while(true)
	{
		strData = m_pSiteData->m_oRunTimeDataList.Get();
		if(strData == "")
		{
			break;
		}
		m_oLogFile.WriteString(strData);
	}
}

/**
* �����¼Ӽ첨���ĳ�ʼ����
* @param void
* @return void
*/
void CThreadProcSiteDataOutput::ProcSensorTestOnField()
{
	m_pThreadProcTestBase->ProcSensorTestOnField();
}