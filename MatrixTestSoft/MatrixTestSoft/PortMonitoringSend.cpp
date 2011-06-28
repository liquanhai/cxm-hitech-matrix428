// PortMonitoringSend.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MatrixTestSoft.h"
#include "PortMonitoringSend.h"


// CPortMonitoringSend �Ի���

IMPLEMENT_DYNAMIC(CPortMonitoringSend, CDialog)

CPortMonitoringSend::CPortMonitoringSend(CWnd* pParent /*=NULL*/)
	: CDialog(CPortMonitoringSend::IDD, pParent)
	, m_pRecThread(NULL)
{

}

CPortMonitoringSend::~CPortMonitoringSend()
{
	if (m_pRecThread != NULL)
	{
		m_pRecThread = NULL;
		delete m_pRecThread;
	}
}

void CPortMonitoringSend::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CPortMonitoringSend, CDialog)
	ON_WM_TIMER()
END_MESSAGE_MAP()

// CPortMonitoringSend ��Ϣ��������
void CPortMonitoringSend::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: �ڴ�������Ϣ������������/�����Ĭ��ֵ
	if (nIDEvent == PortMonitoringSendTimerNb)
	{
		CString strTemp = _T("");
		CString str = _T("");
		unsigned int uiTemp = 0;
		unsigned int uiHeartBeatNum = 0;
		unsigned int uiIPSetNum = 0;
		unsigned int uiTailTimeNum = 0;
		unsigned int uiDelayTimeSetNum = 0;
		unsigned int uiADCSetNum = 0;
		
		m_Sec_PortMonitorSend.Lock();
		uiHeartBeatNum = m_pRecThread->m_uiHeartBeatNum;
		uiIPSetNum = m_pRecThread->m_uiIPSetNum;
		uiTailTimeNum = m_pRecThread->m_uiTailTimeNum;
		uiDelayTimeSetNum = m_pRecThread->m_uiDelayTimeSetNum;
		uiADCSetNum = m_pRecThread->m_uiADCSetNum;
		m_Sec_PortMonitorSend.Unlock();

		// ����
		GetDlgItem(IDC_STATIC_HEARTBEATFRAMENUM)->GetWindowText(str);
		uiTemp = _tstoi(str);
		if (uiTemp != uiHeartBeatNum)
		{
			strTemp.Format(_T("%d"), uiHeartBeatNum);
			GetDlgItem(IDC_STATIC_HEARTBEATFRAMENUM)->SetWindowText(strTemp);
		}
		// IP��ַ����
		GetDlgItem(IDC_STATIC_IPSETNUM)->GetWindowText(str);
		uiTemp = _tstoi(str);
		if (uiTemp != uiIPSetNum)
		{
			strTemp.Format(_T("%d"), uiIPSetNum);
			GetDlgItem(IDC_STATIC_IPSETNUM)->SetWindowText(strTemp);
		}
		// β��ʱ�̲�ѯ
		GetDlgItem(IDC_STATIC_TAILTIMESETNUM)->GetWindowText(str);
		uiTemp = _tstoi(str);
		if (uiTemp != uiTailTimeNum)
		{
			strTemp.Format(_T("%d"), uiTailTimeNum);
			GetDlgItem(IDC_STATIC_TAILTIMESETNUM)->SetWindowText(strTemp);
		}
		// ʱͳ����
		GetDlgItem(IDC_STATIC_DELAYTIMESETNUM)->GetWindowText(str);
		uiTemp = _tstoi(str);
		if (uiTemp != uiDelayTimeSetNum)
		{
			strTemp.Format(_T("%d"), uiDelayTimeSetNum);
			GetDlgItem(IDC_STATIC_DELAYTIMESETNUM)->SetWindowText(strTemp);
		}
		// ADC��������
		GetDlgItem(IDC_STATIC_ADCSETNUM)->GetWindowText(str);
		uiTemp = _tstoi(str);
		if (uiTemp != uiADCSetNum)
		{
			strTemp.Format(_T("%d"), uiADCSetNum);
			GetDlgItem(IDC_STATIC_ADCSETNUM)->SetWindowText(strTemp);
		}
	}
	CDialog::OnTimer(nIDEvent);
}