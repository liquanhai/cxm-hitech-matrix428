// OperationDoc.cpp : COperationDoc ���ʵ��
//

#include "stdafx.h"
#include "Operation.h"

#include "OperationDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// COperationDoc

IMPLEMENT_DYNCREATE(COperationDoc, CDocument)

BEGIN_MESSAGE_MAP(COperationDoc, CDocument)
END_MESSAGE_MAP()


// COperationDoc ����/����

COperationDoc::COperationDoc()
{
	// TODO: �ڴ����һ���Թ������

}

COperationDoc::~COperationDoc()
{
}

BOOL COperationDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: �ڴ�������³�ʼ������
	// (SDI �ĵ������ø��ĵ�)

	return TRUE;
}




// COperationDoc ���л�

void COperationDoc::Serialize(CArchive& ar)
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


// COperationDoc ���

#ifdef _DEBUG
void COperationDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void COperationDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// COperationDoc ����
