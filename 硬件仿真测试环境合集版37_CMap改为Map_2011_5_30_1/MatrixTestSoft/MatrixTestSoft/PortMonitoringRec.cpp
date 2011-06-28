// PortMonitoringRec.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MatrixTestSoft.h"
#include "PortMonitoringRec.h"


// CPortMonitoringRec �Ի���

IMPLEMENT_DYNAMIC(CPortMonitoringRec, CDialog)

CPortMonitoringRec::CPortMonitoringRec(CWnd* pParent /*=NULL*/)
	: CDialog(CPortMonitoringRec::IDD, pParent)
	, m_pSendThread(NULL)
{

}

CPortMonitoringRec::~CPortMonitoringRec()
{
	if (m_pSendThread != NULL)
	{
		m_pSendThread = NULL;
		delete m_pSendThread;
	}
}

void CPortMonitoringRec::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CPortMonitoringRec, CDialog)
	ON_WM_TIMER()
END_MESSAGE_MAP()

// CPortMonitoringRec ��Ϣ�������
void CPortMonitoringRec::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	if (nIDEvent == PortMonitoringRecTimerNb)
	{

		CString strTemp = _T("");
		CString str = _T("");
		unsigned int uiTemp = 0;
		unsigned int uiHeadFrameNum = 0;
		unsigned int uiIPSetReturnNum = 0;
		unsigned int uiTailFrameNum = 0;
		unsigned int uiTailTimeReturnNum = 0;
		unsigned int uiDelayTimeReturnNum = 0;
		unsigned int uiADCSetReturnNum = 0;
		unsigned int uiErrorCodeReturnNum = 0;
		unsigned int uiCollectSysTimeReturnNum = 0;
		unsigned int uiADCRecNum = 0;
		CString csHeadFrameShow = _T("");
		CString csIPSetReturnShow = _T("");
		CString csTailFrameShow = _T("");
		CString csTailTimeReturnShow = _T("");
		CString csDelayTimeReturnShow = _T("");
//		CString csErrorCodeReturnShow = _T("");
		m_Sec_PortMonitorRec.Lock();
		uiHeadFrameNum = m_pSendThread->m_uiHeadFrameNum;
		uiIPSetReturnNum = m_pSendThread->m_uiIPSetReturnNum;
		uiTailFrameNum = m_pSendThread->m_uiTailFrameNum;
		uiTailTimeReturnNum = m_pSendThread->m_uiTailTimeReturnNum;
		uiDelayTimeReturnNum = m_pSendThread->m_uiDelayTimeReturnNum;
		uiErrorCodeReturnNum = m_pSendThread->m_uiErrorCodeReturnNum;
		uiADCSetReturnNum = m_pSendThread->m_uiADCSetReturnNum;
		uiCollectSysTimeReturnNum = m_pSendThread->m_uiCollectSysTimeReturnNum;
		uiADCRecNum = m_pSendThread->m_uiADCRecNum;
		csHeadFrameShow = m_pSendThread->m_csHeadFrameShow;
		csIPSetReturnShow = m_pSendThread->m_csIPSetReturnShow;
		csTailFrameShow = m_pSendThread->m_csTailFrameShow;
		csTailTimeReturnShow = m_pSendThread->m_csTailTimeReturnShow;
		csDelayTimeReturnShow = m_pSendThread->m_csDelayTimeReturnShow;
//		csErrorCodeReturnShow = m_pSendThread->m_csErrorCodeReturnShow;
		m_Sec_PortMonitorRec.Unlock();

		// �װ�����
		GetDlgItem(IDC_STATIC_HEADFRAMENUM)->GetWindowText(str);
		uiTemp = _tstoi(str);
		if (uiTemp != uiHeadFrameNum)
		{
			strTemp.Format(_T("%d"), uiHeadFrameNum);
			GetDlgItem(IDC_STATIC_HEADFRAMENUM)->SetWindowText(strTemp);
		}
		// IP��ַ���ü���
		GetDlgItem(IDC_STATIC_IPSETRETURNNUM)->GetWindowText(str);
		uiTemp = _tstoi(str);
		if (uiTemp != uiIPSetReturnNum)
		{
			strTemp.Format(_T("%d"), uiIPSetReturnNum);
			GetDlgItem(IDC_STATIC_IPSETRETURNNUM)->SetWindowText(strTemp);
		}
		// β������
		GetDlgItem(IDC_STATIC_TAILFRAMENUM)->GetWindowText(str);
		uiTemp = _tstoi(str);
		if (uiTemp != uiTailFrameNum)
		{
			strTemp.Format(_T("%d"), uiTailFrameNum);
			GetDlgItem(IDC_STATIC_TAILFRAMENUM)->SetWindowText(strTemp);
		}
		// β��ʱ�̲�ѯӦ�����
		GetDlgItem(IDC_STATIC_TAILTIMERETURNNUM)->GetWindowText(str);
		uiTemp = _tstoi(str);
		if (uiTemp != uiTailTimeReturnNum)
		{
			strTemp.Format(_T("%d"), uiTailTimeReturnNum);
			GetDlgItem(IDC_STATIC_TAILTIMERETURNNUM)->SetWindowText(strTemp);
		}
		// ʱ������Ӧ�����
		GetDlgItem(IDC_STATIC_DELAYTIMERETURNNUM)->GetWindowText(str);
		uiTemp = _tstoi(str);
		if (uiTemp != uiDelayTimeReturnNum)
		{
			strTemp.Format(_T("%d"), uiDelayTimeReturnNum);
			GetDlgItem(IDC_STATIC_DELAYTIMERETURNNUM)->SetWindowText(strTemp);
		}
		// ADC����Ӧ�����
		GetDlgItem(IDC_STATIC_ADCSETRETURNNUM)->GetWindowText(str);
		uiTemp = _tstoi(str);
		if (uiTemp != uiADCSetReturnNum)
		{
			strTemp.Format(_T("%d"), uiADCSetReturnNum);
			GetDlgItem(IDC_STATIC_ADCSETRETURNNUM)->SetWindowText(strTemp);
		}
		// Ӳ���豸�����ѯӦ��֡����
		GetDlgItem(IDC_STATIC_ERRORCODERETURNNUM)->GetWindowText(str);
		uiTemp = _tstoi(str);
		if (uiTemp != uiErrorCodeReturnNum)
		{
			strTemp.Format(_T("%d"), uiErrorCodeReturnNum);
			GetDlgItem(IDC_STATIC_ERRORCODERETURNNUM)->SetWindowText(strTemp);
		}
		// ��ѯ�õ��ı���ʱ��֡��
		GetDlgItem(IDC_STATIC_COLLECTSYSTIMERETURNNUM)->GetWindowText(str);
		uiTemp = _tstoi(str);
		if (uiTemp != uiCollectSysTimeReturnNum)
		{
			strTemp.Format(_T("%d"), uiCollectSysTimeReturnNum);
			GetDlgItem(IDC_STATIC_COLLECTSYSTIMERETURNNUM)->SetWindowText(strTemp);
		}
		// ���յõ���ADC����֡��
		GetDlgItem(IDC_STATIC_ADCRECNUM)->GetWindowText(str);
		uiTemp = _tstoi(str);
		if (uiTemp != uiADCRecNum)
		{
			strTemp.Format(_T("%d"), uiADCRecNum);
			GetDlgItem(IDC_STATIC_ADCRECNUM)->SetWindowText(strTemp);
		}

		// ��ʾ�װ�֡������SN���װ�ʱ��
		GetDlgItem(IDC_EDIT_HEADFRAMESHOW)->GetWindowText(strTemp);
		if (strTemp != csHeadFrameShow)
		{
			GetDlgItem(IDC_EDIT_HEADFRAMESHOW)->SetWindowText(csHeadFrameShow);
		}
		// ��ʾIP��ַ����Ӧ��֡������SN�����õ�IP��ַ
		GetDlgItem(IDC_EDIT_IPSETRETURNSHOW)->GetWindowText(strTemp);
		if (strTemp != csIPSetReturnShow)
		{
			GetDlgItem(IDC_EDIT_IPSETRETURNSHOW)->SetWindowText(csIPSetReturnShow);
		}
		// ��ʾβ��֡������SN
		GetDlgItem(IDC_EDIT_TAILFRAMESHOW)->GetWindowText(strTemp);
		if (strTemp != csTailFrameShow)
		{
			GetDlgItem(IDC_EDIT_TAILFRAMESHOW)->SetWindowText(csTailFrameShow);
		}
		// ��ʾβ��ʱ�̲�ѯӦ��֡������IP��ַ�Ͳ�ѯ���
		GetDlgItem(IDC_EDIT_TAILTIMERETURNSHOW)->GetWindowText(strTemp);
		if (strTemp != csTailTimeReturnShow)
		{
			GetDlgItem(IDC_EDIT_TAILTIMERETURNSHOW)->SetWindowText(csTailTimeReturnShow);
		}
		// ��ʾʱ������Ӧ��֡������IP��ַ����������
		GetDlgItem(IDC_EDIT_DELAYTIMERETURNSHOW)->GetWindowText(strTemp);
		if (strTemp != csDelayTimeReturnShow)
		{
			GetDlgItem(IDC_EDIT_DELAYTIMERETURNSHOW)->SetWindowText(csDelayTimeReturnShow);
		}
		// ��ʾӲ������������
// 		GetDlgItem(IDC_EDIT_ERRORCODERETURNSHOW)->GetWindowText(strTemp);
// 		if (strTemp != csErrorCodeReturnShow)
// 		{
// 			GetDlgItem(IDC_EDIT_ERRORCODERETURNSHOW)->SetWindowText(csErrorCodeReturnShow);
// 		}
	}
	CDialog::OnTimer(nIDEvent);
}
