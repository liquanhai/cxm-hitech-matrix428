// DlgSEGDSetup.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Config.h"
#include "DlgSEGDSetup.h"


// CDlgSEGDSetup �Ի���

IMPLEMENT_DYNAMIC(CDlgSEGDSetup, CBCGPDialog)

CDlgSEGDSetup::CDlgSEGDSetup(CWnd* pParent /*=NULL*/)
	: CBCGPDialog(CDlgSEGDSetup::IDD, pParent)
{
	EnableVisualManagerStyle();
}

CDlgSEGDSetup::~CDlgSEGDSetup()
{
}

void CDlgSEGDSetup::DoDataExchange(CDataExchange* pDX)
{
	CBCGPDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDlgSEGDSetup, CBCGPDialog)
END_MESSAGE_MAP()


// CDlgSEGDSetup ��Ϣ�������
