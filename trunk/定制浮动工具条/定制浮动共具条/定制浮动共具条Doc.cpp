// ���Ƹ���������Doc.cpp : C���Ƹ���������Doc ���ʵ��
//

#include "stdafx.h"
#include "���Ƹ���������.h"

#include "���Ƹ���������Doc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// C���Ƹ���������Doc

IMPLEMENT_DYNCREATE(C���Ƹ���������Doc, CDocument)

BEGIN_MESSAGE_MAP(C���Ƹ���������Doc, CDocument)
END_MESSAGE_MAP()


// C���Ƹ���������Doc ����/����

C���Ƹ���������Doc::C���Ƹ���������Doc()
{
	// TODO: �ڴ����һ���Թ������

}

C���Ƹ���������Doc::~C���Ƹ���������Doc()
{
}

BOOL C���Ƹ���������Doc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: �ڴ�������³�ʼ������
	// (SDI �ĵ������ø��ĵ�)

	return TRUE;
}




// C���Ƹ���������Doc ���л�

void C���Ƹ���������Doc::Serialize(CArchive& ar)
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


// C���Ƹ���������Doc ���

#ifdef _DEBUG
void C���Ƹ���������Doc::AssertValid() const
{
	CDocument::AssertValid();
}

void C���Ƹ���������Doc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// C���Ƹ���������Doc ����
