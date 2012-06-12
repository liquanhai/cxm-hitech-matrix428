// DlgSpreadSetup.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "line.h"
#include "DlgSpreadSetup.h"


// CDlgSpreadSetup �Ի���

IMPLEMENT_DYNAMIC(CDlgSpreadSetup, CDialog)

CDlgSpreadSetup::CDlgSpreadSetup(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgSpreadSetup::IDD, pParent)
{

}

CDlgSpreadSetup::~CDlgSpreadSetup()
{
}

void CDlgSpreadSetup::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDlgSpreadSetup, CDialog)
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_BUTTON_APPLY, &CDlgSpreadSetup::OnBnClickedButtonApply)
	ON_BN_CLICKED(IDC_BUTTON_RESET, &CDlgSpreadSetup::OnBnClickedButtonReset)
	ON_BN_CLICKED(IDC_BUTTON_ADD, &CDlgSpreadSetup::OnBnClickedButtonAdd)
	ON_BN_CLICKED(IDC_BUTTON_CHANGE, &CDlgSpreadSetup::OnBnClickedButtonChange)
	ON_BN_CLICKED(IDC_BUTTON_DELETE, &CDlgSpreadSetup::OnBnClickedButtonDelete)
	//2012-03-01
//	ON_BN_CLICKED(IDC_BUTTON_SELECTSHOTPOINT, &CDlgSpreadSetup::OnBnClickedButtonSelectShotPoint)
END_MESSAGE_MAP()

// CDlgSpreadSetup ��Ϣ�������

/**
* OnInitDialog()
* @param void
* @return BOOL
*/
BOOL CDlgSpreadSetup::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	CRect oRect;
	CWnd* pWnd = GetDlgItem(IDC_STATIC_TAB);
	pWnd->GetWindowRect(&oRect);
	ScreenToClient(&oRect);

	m_oTabWnd.Create(CBCGPTabWnd::STYLE_3D, oRect, this, 1, CBCGPTabWnd::LOCATION_TOP);	// ����ҳ����

	m_oTabSpreadAbsolute.m_pSiteData = m_pSiteData;	// �ֳ�����
	m_oTabSpreadAbsolute.Create("", WS_CHILD | WS_VISIBLE, oRect, &m_oTabWnd, 1);	// ����ҳSpreadAbsolute
	m_oTabSpreadGeneric.m_pSiteData = m_pSiteData;	// �ֳ�����
	m_oTabSpreadGeneric.Create("", WS_CHILD | WS_VISIBLE, oRect, &m_oTabWnd, 2);	// ����ҳSpreadGeneric
	//2012-03-01
//	m_oDlgSelectShotPoint.m_pSiteData = m_pSiteData;
//	m_oDlgSelectShotPoint.m_pTabSpreadAbsolute = &m_oTabSpreadAbsolute;

	m_oTabWnd.AddTab(&m_oTabSpreadAbsolute, "    Absolute    ");	// ����ҳSpreadAbsolute
	m_oTabWnd.AddTab(&m_oTabSpreadGeneric, "    Generic    ");	// ����ҳSpreadGeneric

	m_oTabWnd.RecalcLayout();
	m_oTabWnd.SetActiveTab(0);

	// ���ؾ���������������
	m_pSiteData->OnLoadSpreadSetupDataForAbsolute();
	// �������������������
	m_pSiteData->OnLoadSpreadSetupDataForGeneric();

 	m_oTabSpreadAbsolute.OnBnClickedButtonReset();
 	m_oTabSpreadGeneric.OnBnClickedButtonReset();

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}

/**
* OnClose()
* @param void
* @return void
*/
void CDlgSpreadSetup::OnClose()
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
void CDlgSpreadSetup::OnBnClickedButtonApply()
{
	int iActiveTab = m_oTabWnd.GetActiveTab();
	switch(iActiveTab)
	{
	case 0:
		try
		{
			m_oTabSpreadAbsolute.OnBnClickedButtonApply();
		}
		catch (CException* e)
		{
			AfxMessageBox("Illegal Data.\r\nPlease Check Data.", MB_OK | MB_ICONSTOP);
			return;
		}

		// Apply����������������
		m_pSiteData->OnApplySpreadSetupDataForAbsolute();
		// ���Ͳ��Ծ��������������ݱ仯֪ͨ����֡
		m_pSiteData->OnSendCMDFrameForApplySpreadSetupDataForAbsolute();
		break;
	case 1:
		try
		{
			m_oTabSpreadGeneric.OnBnClickedButtonApply();
		}
		catch (CException* e)
		{
			AfxMessageBox("Illegal Data.\r\nPlease Check Data.", MB_OK | MB_ICONSTOP);
			return;
		}

		// Apply���������������
		m_pSiteData->OnApplySpreadSetupDataForGeneric();
		// ���Ͳ�����������������ݱ仯֪ͨ����֡
		m_pSiteData->OnSendCMDFrameForApplySpreadSetupDataForGeneric();
		break;
	}
}

/**
* ��ť�����Ӧ��Reset
* @param void
* @return void
*/
void CDlgSpreadSetup::OnBnClickedButtonReset()
{
	int iActiveTab = m_oTabWnd.GetActiveTab();
	switch(iActiveTab)
	{
	case 0:
		// ���ؾ���������������
		m_pSiteData->OnLoadSpreadSetupDataForAbsolute();
		m_oTabSpreadAbsolute.OnBnClickedButtonReset();
		break;
	case 1:
		// �������������������
		m_pSiteData->OnLoadSpreadSetupDataForGeneric();
		m_oTabSpreadGeneric.OnBnClickedButtonReset();
		break;
	}
}

/**
* ��ť�����Ӧ��Add
* @param void
* @return void
*/
void CDlgSpreadSetup::OnBnClickedButtonAdd()
{
	int iActiveTab = m_oTabWnd.GetActiveTab();
	switch(iActiveTab)
	{
	case 0:
		m_oTabSpreadAbsolute.OnBnClickedButtonAdd();
		break;
	case 1:
		m_oTabSpreadGeneric.OnBnClickedButtonAdd();
		break;
	}	
}

/**
* ��ť�����Ӧ��Change
* @param void
* @return void
*/
void CDlgSpreadSetup::OnBnClickedButtonChange()
{
	int iActiveTab = m_oTabWnd.GetActiveTab();
	switch(iActiveTab)
	{
	case 0:
		m_oTabSpreadAbsolute.OnBnClickedButtonChange();
		break;
	case 1:
		m_oTabSpreadGeneric.OnBnClickedButtonChange();
		break;
	}
}

/**
* ��ť�����Ӧ��Delete
* @param void
* @return void
*/
void CDlgSpreadSetup::OnBnClickedButtonDelete()
{
	int iActiveTab = m_oTabWnd.GetActiveTab();
	switch(iActiveTab)
	{
	case 0:
		m_oTabSpreadAbsolute.OnBnClickedButtonDelete();
		break;
	case 1:
		m_oTabSpreadGeneric.OnBnClickedButtonDelete();
		break;
	}
}
//2012-03-01
/*void CDlgSpreadSetup::OnBnClickedButtonSelectShotPoint()
{
	m_oDlgSelectShotPoint.DoModal();
}*/