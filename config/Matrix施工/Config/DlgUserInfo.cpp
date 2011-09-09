// DlgUserInfo.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Config.h"
#include "DlgUserInfo.h"


// CDlgUserInfo �Ի���

IMPLEMENT_DYNAMIC(CDlgUserInfo, CBCGPDialog)

CDlgUserInfo::CDlgUserInfo(CWnd* pParent /*=NULL*/)
	: CBCGPDialog(CDlgUserInfo::IDD, pParent)
	, m_strUserInfo(_T(""))
{
	EnableVisualManagerStyle();
}

CDlgUserInfo::~CDlgUserInfo()
{
}

void CDlgUserInfo::DoDataExchange(CDataExchange* pDX)
{
	CBCGPDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDITUSERINFO, m_strUserInfo);
}


BEGIN_MESSAGE_MAP(CDlgUserInfo, CBCGPDialog)
	ON_BN_CLICKED(IDC_BTNOK, &CDlgUserInfo::OnBnClickedBtnok)
	ON_BN_CLICKED(IDC_BTNAPPLY, &CDlgUserInfo::OnBnClickedBtnapply)
	ON_BN_CLICKED(IDC_BTNRESET, &CDlgUserInfo::OnBnClickedBtnreset)
END_MESSAGE_MAP()


// CDlgUserInfo ��Ϣ�������
BOOL CDlgUserInfo::OnInitDialog()
{
	CBCGPDialog::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	OnBnClickedBtnreset();
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}

void CDlgUserInfo::OnBnClickedBtnok()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	OnBnClickedBtnapply();
	OnOK();
}

void CDlgUserInfo::OnBnClickedBtnapply()
{
	CConfigParseXML  ParseXML;
	UpdateData(TRUE);
	ParseXML.WriteUserInfo(theApp.m_strLocalXMLFile,m_strUserInfo);
	theApp.WriteLog(_T("CDlgUserInfo::OnBnClickedBtnapply"),_T("User info setup has been modified!"),LOGTYPE_NORMAL,TRUE);
	theApp.SaveXMLToFTPServer();
}

void CDlgUserInfo::OnBnClickedBtnreset()
{
	CConfigParseXML  ParseXML;
	ParseXML.ParseUserInfo(theApp.m_strLocalXMLFile,m_strUserInfo);
	UpdateData(FALSE);
}

