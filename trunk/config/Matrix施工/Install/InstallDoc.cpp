// InstallDoc.cpp : CInstallDoc ���ʵ��
//

#include "stdafx.h"
#include "Install.h"

#include "InstallDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CInstallDoc

IMPLEMENT_DYNCREATE(CInstallDoc, CDocument)

BEGIN_MESSAGE_MAP(CInstallDoc, CDocument)
END_MESSAGE_MAP()


// CInstallDoc ����/����

CInstallDoc::CInstallDoc()
{
	// TODO: �ڴ����һ���Թ������

}

CInstallDoc::~CInstallDoc()
{
}

BOOL CInstallDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: �ڴ�������³�ʼ������
	// (SDI �ĵ������ø��ĵ�)
	SetTitle(_T(""));
	//SetTitle(NULL);
	return TRUE;
}




// CInstallDoc ���л�

void CInstallDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: �ڴ���Ӵ洢����
	}
	else
	{
		// TODO: �ڴ���Ӽ��ش���
	}
}


// CInstallDoc ���

#ifdef _DEBUG
void CInstallDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CInstallDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CInstallDoc ����
