// SensorListDoc.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "line.h"
#include "SensorListDoc.h"


// CSensorListDoc

IMPLEMENT_DYNCREATE(CSensorListDoc, CDocument)

CSensorListDoc::CSensorListDoc()
{
}

BOOL CSensorListDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;
	return TRUE;
}

CSensorListDoc::~CSensorListDoc()
{
}


BEGIN_MESSAGE_MAP(CSensorListDoc, CDocument)
END_MESSAGE_MAP()


// CSensorListDoc ���

#ifdef _DEBUG
void CSensorListDoc::AssertValid() const
{
	CDocument::AssertValid();
}

#ifndef _WIN32_WCE
void CSensorListDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif
#endif //_DEBUG

#ifndef _WIN32_WCE
// CSensorListDoc ���л�

void CSensorListDoc::Serialize(CArchive& ar)
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


// CSensorListDoc ����
