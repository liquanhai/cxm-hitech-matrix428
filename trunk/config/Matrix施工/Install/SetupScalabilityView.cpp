// SetupScalabilityView.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Install.h"
#include "SetupScalabilityView.h"


// CSetupScalabilityView

IMPLEMENT_DYNCREATE(CSetupScalabilityView, CBCGPDialog)

CSetupScalabilityView::CSetupScalabilityView()
	: CBCGPDialog(CSetupScalabilityView::IDD)
{
	EnableVisualManagerStyle();
}

CSetupScalabilityView::~CSetupScalabilityView()
{
}

void CSetupScalabilityView::DoDataExchange(CDataExchange* pDX)
{
	CBCGPDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CSetupScalabilityView, CBCGPDialog)
END_MESSAGE_MAP()


// CSetupScalabilityView ���
/*
#ifdef _DEBUG
void CSetupScalabilityView::AssertValid() const
{
	CBCGPDialog::AssertValid();
}

#ifndef _WIN32_WCE
void CSetupScalabilityView::Dump(CDumpContext& dc) const
{
	CBCGPDialog::Dump(dc);
}
#endif
#endif //_DEBUG
*/

// CSetupScalabilityView ��Ϣ�������
