// SensorGraphDoc.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "line.h"
#include "SeismonitorGraphDoc.h"


// CSeismonitorGraphDoc

IMPLEMENT_DYNCREATE(CSeismonitorGraphDoc, CDocument)

CSeismonitorGraphDoc::CSeismonitorGraphDoc()
{
}

BOOL CSeismonitorGraphDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;
	return TRUE;
}

CSeismonitorGraphDoc::~CSeismonitorGraphDoc()
{
}


BEGIN_MESSAGE_MAP(CSeismonitorGraphDoc, CDocument)
END_MESSAGE_MAP()


// CSeismonitorGraphDoc ���

#ifdef _DEBUG
void CSeismonitorGraphDoc::AssertValid() const
{
	CDocument::AssertValid();
}

#ifndef _WIN32_WCE
void CSeismonitorGraphDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif
#endif //_DEBUG

#ifndef _WIN32_WCE
// CSeismonitorGraphDoc ���л�

void CSeismonitorGraphDoc::Serialize(CArchive& ar)
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
#endif


// CSeismonitorGraphDoc ����
