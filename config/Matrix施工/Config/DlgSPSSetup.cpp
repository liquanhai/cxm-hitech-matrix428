// DlgSPSSetup.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Config.h"
#include "DlgSPSSetup.h"


// DlgSPSSetup �Ի���

IMPLEMENT_DYNAMIC(CDlgSPSSetup, CBCGPDialog)

CDlgSPSSetup::CDlgSPSSetup(CWnd* pParent /*=NULL*/)
: CBCGPDialog(CDlgSPSSetup::IDD, pParent)
{
	EnableVisualManagerStyle();
}

CDlgSPSSetup::~CDlgSPSSetup()
{
}

void CDlgSPSSetup::DoDataExchange(CDataExchange* pDX)
{
	CBCGPDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDlgSPSSetup, CBCGPDialog)
	ON_BN_CLICKED(IDC_BTNLOADSPS, &CDlgSPSSetup::OnBnClickedBtnloadsps)
	ON_BN_CLICKED(IDC_BTNGENOPTXML, &CDlgSPSSetup::OnBnClickedBtngenoptxml)
	ON_BN_CLICKED(IDC_BTNGENLINEXML, &CDlgSPSSetup::OnBnClickedBtngenlinexml)
END_MESSAGE_MAP()

// DlgSPSSetup ��Ϣ�������

void CDlgSPSSetup::OnBnClickedBtnloadsps()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}

void CDlgSPSSetup::OnBnClickedBtngenoptxml()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}

void CDlgSPSSetup::OnBnClickedBtngenlinexml()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}
