// InstrumentListDoc.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "line.h"
#include "InstrumentListDoc.h"


// CInstrumentListDoc

IMPLEMENT_DYNCREATE(CInstrumentListDoc, CDocument)

CInstrumentListDoc::CInstrumentListDoc()
{
}

BOOL CInstrumentListDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;
	return TRUE;
}

CInstrumentListDoc::~CInstrumentListDoc()
{
}


BEGIN_MESSAGE_MAP(CInstrumentListDoc, CDocument)
END_MESSAGE_MAP()


// CInstrumentListDoc ���

#ifdef _DEBUG
void CInstrumentListDoc::AssertValid() const
{
	CDocument::AssertValid();
}

#ifndef _WIN32_WCE
void CInstrumentListDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif
#endif //_DEBUG

#ifndef _WIN32_WCE
// CInstrumentListDoc ���л�

void CInstrumentListDoc::Serialize(CArchive& ar)
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


// CInstrumentListDoc ����
