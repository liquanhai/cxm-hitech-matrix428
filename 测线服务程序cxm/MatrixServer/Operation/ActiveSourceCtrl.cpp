// ActiveSourceCtrl.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Operation.h"
#include "ActiveSourceCtrl.h"



// CActiveSourceCtrl �Ի���

IMPLEMENT_DYNCREATE(CActiveSourceCtrl, CBCGPFormView)
CActiveSourceCtrl::CActiveSourceCtrl()
	: CBCGPFormView(CActiveSourceCtrl::IDD)
{

}

CActiveSourceCtrl::~CActiveSourceCtrl()
{
}

void CActiveSourceCtrl::DoDataExchange(CDataExchange* pDX)
{
	CBCGPFormView::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CActiveSourceCtrl, CBCGPFormView)
	ON_BN_CLICKED(IDC_BUTTONGO, &CActiveSourceCtrl::OnBnClickedButtongo)
END_MESSAGE_MAP()


// CActiveSourceCtrl ��Ϣ�������

BOOL CActiveSourceCtrl::CreateView(CWnd* pParent, CRect rect, CCreateContext* pContext)
{
	if (!Create(NULL, NULL, AFX_WS_DEFAULT_VIEW,
		rect, pParent, AFX_IDW_PANE_FIRST, pContext))
	{
		TRACE0("Warning: couldn't create CActiveSourceCtrl!\n");
		return FALSE;
	}
	return TRUE;
}

void CActiveSourceCtrl::OnBnClickedButtongo()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}
