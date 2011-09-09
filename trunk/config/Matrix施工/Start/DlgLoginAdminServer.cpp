// DlgLoginAdminServer.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Start.h"
#include "DlgLoginAdminServer.h"


// CDlgLoginAdminServer �Ի���

IMPLEMENT_DYNAMIC(CDlgLoginAdminServer, CBCGPDialog)

CDlgLoginAdminServer::CDlgLoginAdminServer(CWnd* pParent /*=NULL*/)
	: CBCGPDialog(CDlgLoginAdminServer::IDD, pParent)
	, m_strLabel(_T("428GUI"))
	, m_strURL(_T("192.168.0.12"))
	, m_strUserName(_T("User"))
	, m_strPassword(_T(""))
{
	EnableVisualManagerStyle();
}

CDlgLoginAdminServer::~CDlgLoginAdminServer()
{
	m_hWnd = NULL;
}

void CDlgLoginAdminServer::DoDataExchange(CDataExchange* pDX)
{
	CBCGPDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDITLABEL, m_strLabel);
	DDX_Text(pDX, IDC_EDITURL, m_strURL);
	DDX_Text(pDX, IDC_EDITUSERNAME, m_strUserName);
	DDX_Text(pDX, IDC_EDITPASSWORD, m_strPassword);
}


BEGIN_MESSAGE_MAP(CDlgLoginAdminServer, CBCGPDialog)
	ON_BN_CLICKED(IDC_BTNCONNECT, &CDlgLoginAdminServer::OnBnClickedBtnconnect)
	ON_WM_DESTROY()
END_MESSAGE_MAP()


// CDlgLoginAdminServer ��Ϣ�������

BOOL CDlgLoginAdminServer::OnInitDialog()
{
	CBCGPDialog::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}

void CDlgLoginAdminServer::OnOK()
{
	// TODO: �ڴ����ר�ô����/����û���
	UpdateData(TRUE);
	DestroyWindow();
	//CBCGPDialog::OnOK();
}

void CDlgLoginAdminServer::OnCancel()
{
	// TODO: �ڴ����ר�ô����/����û���
	DestroyWindow();
	//CBCGPDialog::OnCancel();
}
void CDlgLoginAdminServer::OnDestroy()
{
	CBCGPDialog::OnDestroy();
	// �˳�ǰ��������
	GetParent()->SendMessage(WM_DLGLOGINDESTROY,0,0);
	
}

void CDlgLoginAdminServer::PostNcDestroy()
{
	// ��Ϊ��ģʽ�Ի����Զ�ɾ������
	delete this;
	CBCGPDialog::PostNcDestroy();
}
/**
 * @brief ��ӦConnect��ť
 * @note  ��ӦConnect��ť��������������û���¼����֡
 * @param void
 * @return void
 */
void CDlgLoginAdminServer::OnBnClickedBtnconnect()
{
	UpdateData(TRUE);
	theApp.m_sockAdminServer.SendFrm_UserLogin(m_strUserName,m_strPassword,m_strURL);
}

