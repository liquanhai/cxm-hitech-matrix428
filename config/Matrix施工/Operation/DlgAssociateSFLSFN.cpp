// DlgAssociateSFLSFN.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Operation.h"
#include "DlgAssociateSFLSFN.h"


// CDlgAssociateSFLSFN �Ի���

IMPLEMENT_DYNAMIC(CDlgAssociateSFLSFN, CBCGPDialog)

CDlgAssociateSFLSFN::CDlgAssociateSFLSFN(CWnd* pParent /*=NULL*/)
	: CBCGPDialog(CDlgAssociateSFLSFN::IDD, pParent)
	, m_fSourceLine(0)
	, m_fSourceNumber(0)
{
	EnableVisualManagerStyle();
}

CDlgAssociateSFLSFN::~CDlgAssociateSFLSFN()
{
}

void CDlgAssociateSFLSFN::DoDataExchange(CDataExchange* pDX)
{
	CBCGPDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDITSFL, m_fSourceLine);
	DDX_Text(pDX, IDC_EDITSFN, m_fSourceNumber);
}

BEGIN_MESSAGE_MAP(CDlgAssociateSFLSFN, CBCGPDialog)
END_MESSAGE_MAP()


// CDlgAssociateSFLSFN ��Ϣ�������
