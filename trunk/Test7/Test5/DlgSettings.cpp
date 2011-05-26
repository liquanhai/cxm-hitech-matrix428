// DlgSettings.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Test5.h"
#include "DlgSettings.h"


// CDlgSettings �Ի���

IMPLEMENT_DYNAMIC(CDlgSettings, CBCGPDialog)

CDlgSettings::CDlgSettings(CWnd* pParent /*=NULL*/)
	: CBCGPDialog(CDlgSettings::IDD, pParent)
{
#ifndef _WIN32_WCE
	EnableActiveAccessibility();
#endif

}

CDlgSettings::~CDlgSettings()
{
}

void CDlgSettings::DoDataExchange(CDataExchange* pDX)
{
	CBCGPDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STATICPICTURE, m_ctrlTabLocation);
}


BEGIN_MESSAGE_MAP(CDlgSettings, CBCGPDialog)
END_MESSAGE_MAP()


// CDlgSettings ��Ϣ�������

BOOL CDlgSettings::OnInitDialog(void)
{
	CBCGPDialog::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	CRect rectTab;

	m_ctrlTabLocation.GetWindowRect (&rectTab);
	ScreenToClient (&rectTab);
	m_wndTab.Create (CBCGPTabWnd::STYLE_3D_ONENOTE, rectTab, this, 1,CBCGPTabWnd::LOCATION_TOP);

	m_DlgStudents.Create(IDD_DLGSTUDENTSSETTING,&m_wndTab);
	m_DlgStudents.SetWindowText (_T("ѧ��"));
 	m_DlgTeachers.Create(IDD_DLGTEACHERSSETTING,&m_wndTab);
 	m_DlgTeachers.SetWindowText (_T("��ʦ"));
	

	m_wndTab.AddTab (&m_DlgTeachers, _T(" ��ʦ "), 0, FALSE);
	m_wndTab.AddTab (&m_DlgStudents, _T(" ѧ�� "), 1, FALSE);

	m_wndTab.EnableTabSwap(FALSE);
	m_wndTab.SetDrawFrame(TRUE);
	m_wndTab.SetButtonsVisible(FALSE);
	m_wndTab.SetFlatFrame(FALSE,TRUE);
	m_wndTab.RecalcLayout ();
	m_wndTab.RedrawWindow ();
	return TRUE;
}
