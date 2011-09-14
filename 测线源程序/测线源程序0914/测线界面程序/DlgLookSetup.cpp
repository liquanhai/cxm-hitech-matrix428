// DlgLookSetup.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "BCGPVisualStudioGUIDemo.h"
#include "DlgLookSetup.h"


// CDlgLookSetup �Ի���

IMPLEMENT_DYNAMIC(CDlgLookSetup, CDialog)

CDlgLookSetup::CDlgLookSetup(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgLookSetup::IDD, pParent)
{

}

CDlgLookSetup::~CDlgLookSetup()
{
}

void CDlgLookSetup::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDlgLookSetup, CDialog)
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_BUTTON_APPLY, &CDlgLookSetup::OnBnClickedButtonApply)
	ON_BN_CLICKED(IDC_BUTTON_RESET, &CDlgLookSetup::OnBnClickedButtonReset)
END_MESSAGE_MAP()

// CDlgLookSetup ��Ϣ�������

/**
* OnInitDialog()
* @param void
* @return BOOL
*/
BOOL CDlgLookSetup::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��

	OnBnClickedButtonReset();

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}

/**
* OnClose()
* @param void
* @return void
*/
void CDlgLookSetup::OnClose()
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	ShowWindow(SW_HIDE);
//	CDialog::OnClose();
}

/**
* ��ť�����Ӧ��Apply
* @param void
* @return void
*/
void CDlgLookSetup::OnBnClickedButtonApply()
{
	m_pSiteData->m_oLookSetupData.m_uiLookAuto = IsDlgButtonChecked(IDC_CHECK_LOOKAUTO);
	m_pSiteData->m_oLookSetupData.m_uiTestResistance = IsDlgButtonChecked(IDC_CHECK_RESISTANCE);
	m_pSiteData->m_oLookSetupData.m_uiTestTilt = IsDlgButtonChecked(IDC_CHECK_TILT);
	m_pSiteData->m_oLookSetupData.m_uiTestLeakage = IsDlgButtonChecked(IDC_CHECK_LEAKAGE);
	// ����Look�������ݣ�Apply
	m_pSiteData->OnApplyLookSetupData();
	// ����Look����Apply֪ͨ����֡
	m_pSiteData->OnSendCMDFrameForApplyLookSetupData();
}

/**
* ��ť�����Ӧ��Reset
* @param void
* @return void
*/
void CDlgLookSetup::OnBnClickedButtonReset()
{
	// ����Look��������
	m_pSiteData->OnLoadLookSetupData();
	CheckDlgButton(IDC_CHECK_LOOKAUTO, m_pSiteData->m_oLookSetupData.m_uiLookAuto);
	CheckDlgButton(IDC_CHECK_RESISTANCE, m_pSiteData->m_oLookSetupData.m_uiTestResistance);
	CheckDlgButton(IDC_CHECK_TILT, m_pSiteData->m_oLookSetupData.m_uiTestTilt);
	CheckDlgButton(IDC_CHECK_LEAKAGE, m_pSiteData->m_oLookSetupData.m_uiTestLeakage);
}
