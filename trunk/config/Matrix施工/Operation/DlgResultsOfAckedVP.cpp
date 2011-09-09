// DlgResultsOfAckedVP.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Operation.h"
#include "DlgResultsOfAckedVP.h"


// CDlgResultsOfAckedVP �Ի���

IMPLEMENT_DYNAMIC(CDlgResultsOfAckedVP, CBCGPDialog)

CDlgResultsOfAckedVP::CDlgResultsOfAckedVP(CWnd* pParent /*=NULL*/)
	: CBCGPDialog(CDlgResultsOfAckedVP::IDD, pParent)
	, m_strResult(_T(""))
{
	EnableVisualManagerStyle();
}

CDlgResultsOfAckedVP::~CDlgResultsOfAckedVP()
{
	m_arrResult.RemoveAll();
}

void CDlgResultsOfAckedVP::DoDataExchange(CDataExchange* pDX)
{
	CBCGPDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LISTRESULT, m_ctrlListResult);
	DDX_Text(pDX, IDC_STATICRESULT, m_strResult);
}


BEGIN_MESSAGE_MAP(CDlgResultsOfAckedVP, CBCGPDialog)
END_MESSAGE_MAP()


// CDlgResultsOfAckedVP ��Ϣ�������

BOOL CDlgResultsOfAckedVP::OnInitDialog()
{
	CBCGPDialog::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	int  i,nCount;
	nCount = m_arrResult.GetCount();
	for (i=0;i<nCount;i++)
	{
		// m_ctrlListResult.InsertItem(m_ctrlListResult.GetItemCount(),m_arrResult[i]);
		// ��ÿ����Ӧ��ɼ�����Ϣд���б��
		m_ctrlListResult.AddString(m_arrResult[i]);
	}
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}
