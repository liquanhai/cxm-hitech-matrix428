// DlgStackImpulsive.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Operation.h"
#include "DlgStackImpulsive.h"


// CDlgStackImpulsive �Ի���

IMPLEMENT_DYNAMIC(CDlgStackImpulsive, CBCGPDialog)

CDlgStackImpulsive::CDlgStackImpulsive(CWnd* pParent /*=NULL*/)
	: CBCGPDialog(CDlgStackImpulsive::IDD, pParent)
{

}

CDlgStackImpulsive::~CDlgStackImpulsive()
{
}

void CDlgStackImpulsive::DoDataExchange(CDataExchange* pDX)
{
	CBCGPDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDlgStackImpulsive, CBCGPDialog)
END_MESSAGE_MAP()


// CDlgStackImpulsive ��Ϣ�������

BOOL CDlgStackImpulsive::OnInitDialog(void)
{
	CBCGPDialog::OnInitDialog();

	//���öԻ���ߴ�ΪIDC_STATICPICTURE�ĳߴ�
	CWnd::SetWindowPos(NULL,0,0,dlgRect.Width(),dlgRect.Height(), SWP_NOZORDER|SWP_NOMOVE);
	return 0;
}
