// SensorGraphDoc.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "BCGPVisualStudioGUIDemo.h"
#include "SensorGraphDoc.h"


// CSensorGraphDoc

IMPLEMENT_DYNCREATE(CSensorGraphDoc, CDocument)

CSensorGraphDoc::CSensorGraphDoc()
{
}

BOOL CSensorGraphDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;
	return TRUE;
}

CSensorGraphDoc::~CSensorGraphDoc()
{
}


BEGIN_MESSAGE_MAP(CSensorGraphDoc, CDocument)
END_MESSAGE_MAP()


// CSensorGraphDoc ���

#ifdef _DEBUG
void CSensorGraphDoc::AssertValid() const
{
	CDocument::AssertValid();
}

#ifndef _WIN32_WCE
void CSensorGraphDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif
#endif //_DEBUG

#ifndef _WIN32_WCE
// CSensorGraphDoc ���л�

void CSensorGraphDoc::Serialize(CArchive& ar)
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


// CSensorGraphDoc ����
