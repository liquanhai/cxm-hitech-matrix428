// LandedDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "IC_TEST.h"
#include "LandedDlg.h"
#include "afxdialogex.h"
#include "Parameter.h"

// CLandedDlg �Ի���

IMPLEMENT_DYNAMIC(CLandedDlg, CDialogEx)

CLandedDlg::CLandedDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CLandedDlg::IDD, pParent)
{

}

CLandedDlg::~CLandedDlg()
{
}

void CLandedDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_LANDED, m_ctrlUserName);
	DDX_Control(pDX, IDC_EDIT_PASSWORD, m_ctrlPassword);
}


BEGIN_MESSAGE_MAP(CLandedDlg, CDialogEx)
END_MESSAGE_MAP()


// CLandedDlg ��Ϣ�������
BOOL CLandedDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	((CComboBox*)GetDlgItem(IDC_COMBO_LANDED))->SetCurSel(0);
	return TRUE;
}

void CLandedDlg::OnOK()
{
	// TODO: �ڴ����ר�ô����/����û���
	OnLand();
	CDialogEx::OnOK();
}


// ��½
void CLandedDlg::OnLand(void)
{
	CString strUser = _T("");
	CString strPassword = _T("");
	m_ctrlUserName.GetWindowText(strUser);
	m_ctrlPassword.GetWindowText(strPassword);
	if (strUser == _T("Admin"))
	{
		if (strPassword == _T("gxb"))
		{
			m_bAdmin = true;
		}
	}
	else
	{
		m_bAdmin = false;
	}
}
