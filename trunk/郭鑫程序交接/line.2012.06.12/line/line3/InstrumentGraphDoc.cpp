// InstrumentGraphDoc.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "line.h"
#include "InstrumentGraphDoc.h"


// CInstrumentGraphDoc

IMPLEMENT_DYNCREATE(CInstrumentGraphDoc, CDocument)

CInstrumentGraphDoc::CInstrumentGraphDoc()
{
}

BOOL CInstrumentGraphDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;
	return TRUE;
}

CInstrumentGraphDoc::~CInstrumentGraphDoc()
{
}


BEGIN_MESSAGE_MAP(CInstrumentGraphDoc, CDocument)
END_MESSAGE_MAP()


// CInstrumentGraphDoc ���

#ifdef _DEBUG
void CInstrumentGraphDoc::AssertValid() const
{
	CDocument::AssertValid();
}

#ifndef _WIN32_WCE
void CInstrumentGraphDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif
#endif //_DEBUG

#ifndef _WIN32_WCE
// CInstrumentGraphDoc ���л�

void CInstrumentGraphDoc::Serialize(CArchive& ar)
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


// CInstrumentGraphDoc ����
