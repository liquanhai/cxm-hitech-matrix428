// DlgNewUser.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Admin.h"
#include "DlgNewUser.h"


// CDlgNewUser �Ի���

IMPLEMENT_DYNAMIC(CDlgNewUser, CDialog)

CDlgNewUser::CDlgNewUser(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgNewUser::IDD, pParent)
	, m_strUserName(_T(""))
	, m_strPassword(_T(""))
{

}

CDlgNewUser::~CDlgNewUser()
{
}

void CDlgNewUser::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDITNAME, m_strUserName);
	DDX_Text(pDX, IDC_EDITPASSWORD, m_strPassword);
}


BEGIN_MESSAGE_MAP(CDlgNewUser, CDialog)
END_MESSAGE_MAP()


// CDlgNewUser ��Ϣ�������
