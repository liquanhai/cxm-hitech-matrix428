// DlgAssociateVP.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Operation.h"
#include "DlgAssociateVP.h"


// CDlgAssociateVP �Ի���

IMPLEMENT_DYNAMIC(CDlgAssociateVP, CBCGPDialog)

CDlgAssociateVP::CDlgAssociateVP(CWnd* pParent /*=NULL*/)
	: CBCGPDialog(CDlgAssociateVP::IDD, pParent)
	, m_dwShotNb(0)
{
	EnableVisualManagerStyle();
}

CDlgAssociateVP::~CDlgAssociateVP()
{
}

void CDlgAssociateVP::DoDataExchange(CDataExchange* pDX)
{
	CBCGPDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDITSHOTNUMBER, m_dwShotNb);
}
BEGIN_MESSAGE_MAP(CDlgAssociateVP, CBCGPDialog)
END_MESSAGE_MAP()


// CDlgAssociateVP ��Ϣ�������
