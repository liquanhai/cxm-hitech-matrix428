// AdminDoc.cpp : CAdminDoc ���ʵ��
//

#include "stdafx.h"
#include "Admin.h"

#include "AdminDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAdminDoc

IMPLEMENT_DYNCREATE(CAdminDoc, CDocument)

BEGIN_MESSAGE_MAP(CAdminDoc, CDocument)
END_MESSAGE_MAP()


// CAdminDoc ����/����

CAdminDoc::CAdminDoc()
{
	// TODO: �ڴ����һ���Թ������

}

CAdminDoc::~CAdminDoc()
{
}

BOOL CAdminDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: �ڴ�������³�ʼ������
	// (SDI �ĵ������ø��ĵ�)
	SetTitle(_T(""));
	return TRUE;
}




// CAdminDoc ���л�

void CAdminDoc::Serialize(CArchive& ar)
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


// CAdminDoc ���

#ifdef _DEBUG
void CAdminDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CAdminDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CAdminDoc ����
