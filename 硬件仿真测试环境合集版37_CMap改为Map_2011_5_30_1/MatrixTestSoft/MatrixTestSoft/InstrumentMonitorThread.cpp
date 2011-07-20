// InstrumentMonitor.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MatrixTestSoft.h"
#include "InstrumentMonitorThread.h"
#include "Parameter.h"

// CInstrumentMonitor

IMPLEMENT_DYNCREATE(CInstrumentMonitorThread, CWinThread)

CInstrumentMonitorThread::CInstrumentMonitorThread()
: m_bclose(false)
, m_pLogFile(NULL)
, m_pwnd(NULL)
, m_pADCSet(NULL)
, m_pInstrumentList(NULL)
, m_pTailFrame(NULL)
, m_uiTailFrameTimerLAUXCount(0)
, m_uiTailFrameStableLAUXCount(0)
, m_uiTailFrameTimerFDUCount(0)
, m_uiTailFrameStableFDUCount(0)
{
}

CInstrumentMonitorThread::~CInstrumentMonitorThread()
{
}

BOOL CInstrumentMonitorThread::InitInstance()
{
	// TODO: �ڴ�ִ���������̳߳�ʼ��
	return TRUE;
}

int CInstrumentMonitorThread::ExitInstance()
{
	// TODO: �ڴ�ִ���������߳�����
	return CWinThread::ExitInstance();
}

BEGIN_MESSAGE_MAP(CInstrumentMonitorThread, CWinThread)
END_MESSAGE_MAP()


// CInstrumentMonitor ��Ϣ�������

int CInstrumentMonitorThread::Run()
{
	// TODO: �ڴ����ר�ô����/����û���
	// ѭ����ֱ���رձ�־Ϊ��
	while(true)
	{
		if(m_bclose == true)
		{
			break;
		}
 		OnMonitorLAUX();
 		OnMonitorFDU();
		if (m_bclose == true)
		{
			break;
		}
		Sleep(InstrumentMonitorThreadSleepTime);
	}
	::SetEvent(m_hInstrumentMonitorThreadClose);	// �����¼�����Ϊ���ź�״̬,�ͷŵȴ��̺߳��¼���Ϊ���ź�
	return CWinThread::Run();
}

// ��ʼ��
void CInstrumentMonitorThread::OnInit(void)
{
	m_hInstrumentMonitorThreadClose = ::CreateEvent(false, false, NULL, NULL);	// �����¼�����
	if ((m_hInstrumentMonitorThreadClose == NULL)||(GetLastError() == ERROR_ALREADY_EXISTS))
	{
		AfxMessageBox(_T("�����豸�����̹߳ر��¼�����"));
	}
	else
	{
		::ResetEvent(m_hInstrumentMonitorThreadClose);	// �����¼�����Ϊ���ź�״̬
	}
}

// �ر�
void CInstrumentMonitorThread::OnClose(void)
{
	m_bclose = true;
}

// ���Ӻ���
void CInstrumentMonitorThread::OnMonitorLAUX(void)
{
	BOOL bTailRecLAUX = FALSE;
	unsigned int uiTailRecLAUXCount = 0;
	m_Sec_InstrumentMonitor.Lock();
	bTailRecLAUX = m_pTailFrame->m_bTailRecLAUX;
	uiTailRecLAUXCount = m_pTailFrame->m_uiTailRecLAUXCount;
	m_Sec_InstrumentMonitor.Unlock();
	// �����Ƿ��н���վβ��
 	if (bTailRecLAUX == TRUE)
 	{
		CString str = _T("");
		m_uiTailFrameTimerLAUXCount++;
 		if (m_uiTailFrameTimerLAUXCount > uiTailRecLAUXCount)
 		{
 			if ((m_uiTailFrameTimerLAUXCount - uiTailRecLAUXCount) > TailFrameLAUXCount)
 			{
 				str.Format(_T("�޽���վβ������ʱ��ʱ������%d��β������%d��ɾ������������ֹͣ�ɼ���")
 					, m_uiTailFrameTimerLAUXCount, uiTailRecLAUXCount);
 				m_pLogFile->OnWriteLogFile(_T("CInstrumentMonitorThread::OnMonitor"), str, WarningStatus);
				m_Sec_InstrumentMonitor.Lock();
 				m_pTailFrame->m_bTailRecLAUX = FALSE;
				m_pTailFrame->m_bTailRecFDU = FALSE;
				m_Sec_InstrumentMonitor.Unlock();
				OnResetLAUXCounter();
				// ����5��δ�յ�����վβ����ɾ����������
				m_pInstrumentList->DeleteAllInstrument();
				OnStopOperation();
			}
			else
			{
				m_uiTailFrameStableLAUXCount++;
				if (m_uiTailFrameStableLAUXCount == TailFrameStableLAUXCount)
				{
					OnResetLAUXCounter();
				}
			}
 		}
		else
		{
			OnResetLAUXCounter();
		}
 	}
	else
	{
		OnResetLAUXCounter();
	}
}
// ���Ӻ���
void CInstrumentMonitorThread::OnMonitorFDU(void)
{
	BOOL bTailRecFDU = FALSE;
	unsigned int uiTailRecFDUCount = 0;
	m_Sec_InstrumentMonitor.Lock();
	bTailRecFDU = m_pTailFrame->m_bTailRecFDU;
	uiTailRecFDUCount = m_pTailFrame->m_uiTailRecFDUCount;
	m_Sec_InstrumentMonitor.Unlock();
	// �����Ƿ��вɼ�վβ��
	if (bTailRecFDU == TRUE)
	{
		CString str = _T("");
		m_uiTailFrameTimerFDUCount++;
		if (m_uiTailFrameTimerFDUCount > uiTailRecFDUCount)
		{
			if ((m_uiTailFrameTimerFDUCount - uiTailRecFDUCount) > TailFrameFDUCount)
			{
				CInstrument* pInstrument = NULL;
				str.Format(_T("�޲ɼ�վβ������ʱ��ʱ������%d��β������%d��ɾ������������ֹͣ�ɼ���")
					, m_uiTailFrameTimerFDUCount, uiTailRecFDUCount);
				m_pLogFile->OnWriteLogFile(_T("CInstrumentMonitorThread::OnMonitor"), str, WarningStatus);
				m_Sec_InstrumentMonitor.Lock();
				m_pTailFrame->m_bTailRecFDU = FALSE;
				m_Sec_InstrumentMonitor.Unlock();
				// ����5��δ�յ��ɼ�վβ����ɾ������վ����������
				if(TRUE == m_pInstrumentList->GetInstrumentFromSNMap(m_pTailFrame->m_uiSN, pInstrument))
				{
					m_pInstrumentList->TailFrameDeleteInstrument(pInstrument);
				}
				OnResetFDUCounter();
				OnStopOperation();
			}
			else
			{
				m_uiTailFrameStableFDUCount++;
				if (m_uiTailFrameStableFDUCount == TailFrameStableFDUCount)
				{
					OnResetFDUCounter();
				}
			}
		}
		else
		{
			OnResetFDUCounter();
		}
	}
	else
	{
		OnResetFDUCounter();
	}
}
void CInstrumentMonitorThread::OnStopOperation(void)
{
	// ���Ͳ���������������֡
	m_pADCSet->OnADCSampleStop();
	m_pwnd->SetTimer(TabSampleStopSampleTimerNb, TabSampleStopSampleTimerSet, NULL);
	m_pwnd->KillTimer(TabSampleQueryErrorCountTimerNb);
	m_pwnd->GetDlgItem(IDC_BUTTON_SETBYHAND)->EnableWindow(FALSE);
	m_pwnd->GetDlgItem(IDC_BUTTON_TIMECAL)->EnableWindow(FALSE);
	m_pwnd->GetDlgItem(IDC_BUTTON_SETADC)->EnableWindow(FALSE);
}
// ���ý���վβ��������
void CInstrumentMonitorThread::OnResetLAUXCounter(void)
{
	m_Sec_InstrumentMonitor.Lock();
	m_pTailFrame->m_uiTailRecLAUXCount = 0;
	m_Sec_InstrumentMonitor.Unlock();
	m_uiTailFrameTimerLAUXCount = 0;
	m_uiTailFrameStableLAUXCount = 0;
}

// ���òɼ�վβ��������
void CInstrumentMonitorThread::OnResetFDUCounter(void)
{
	m_Sec_InstrumentMonitor.Lock();
	m_pTailFrame->m_uiTailRecFDUCount = 0;
	m_Sec_InstrumentMonitor.Unlock();
	m_uiTailFrameTimerFDUCount = 0;
	m_uiTailFrameStableFDUCount = 0;
}
