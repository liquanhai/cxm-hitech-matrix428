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
}

void CPortMonitoringSend::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CPortMonitoringSend, CDialog)
	ON_WM_TIMER()
END_MESSAGE_MAP()

// CPortMonitoringSend ��Ϣ�������
BOOL CPortMonitoringSend::OnInitDialog()
{
	CDialog::OnInitDialog();
	SetTimer(1, 1000, NULL);
	return TRUE;
}
void CPortMonitoringSend::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	if (nIDEvent == 1)
	{
		CString strTemp = _T("");
		unsigned int uiHeartBeatNum = 0;
		unsigned int uiIPSetNum = 0;
		unsigned int uiTailTimeNum = 0;
		unsigned int uiDelayTimeSetNum = 0;
		unsigned int uiADCSetNum = 0;

		m_Sec.Lock();
		uiHeartBeatNum = m_pRecThread->m_uiHeartBeatNum;
		uiIPSetNum = m_pRecThread->m_uiIPSetNum;
		uiTailTimeNum = m_pRecThread->m_uiTailTimeNum;
		uiDelayTimeSetNum = m_pRecThread->m_uiDelayTimeSetNum;
		uiADCSetNum = m_pRecThread->m_uiADCSetNum;
		m_Sec.Unlock();

		GetDlgItem(IDC_STATIC_HEARTBEATFRAMENUM)->SetWindowText(strTemp);
		strTemp.Format(_T("%d"), uiHeartBeatNum);
		GetDlgItem(IDC_STATIC_HEARTBEATFRAMENUM)->SetWindowText(strTemp);
		strTemp.Format(_T("%d"), uiIPSetNum);
		GetDlgItem(IDC_STATIC_IPSETNUM)->SetWindowText(strTemp);
		strTemp.Format(_T("%d"), uiTailTimeNum);
		GetDlgItem(IDC_STATIC_TAILTIMESETNUM)->SetWindowText(strTemp);
		strTemp.Format(_T("%d"), uiDelayTimeSetNum);
		GetDlgItem(IDC_STATIC_DELAYTIMESETNUM)->SetWindowText(strTemp);
		strTemp.Format(_T("%d"), uiADCSetNum);
		GetDlgItem(IDC_STATIC_ADCSETNUM)->SetWindowText(strTemp);
	}
	CDialog::OnTimer(nIDEvent);
}
