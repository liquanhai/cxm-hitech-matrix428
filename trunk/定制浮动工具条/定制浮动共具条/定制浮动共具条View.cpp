// ���Ƹ���������View.cpp : C���Ƹ���������View ���ʵ��
//

#include "stdafx.h"
#include "���Ƹ���������.h"

#include "���Ƹ���������Doc.h"
#include "���Ƹ���������View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// C���Ƹ���������View

IMPLEMENT_DYNCREATE(C���Ƹ���������View, CView)

BEGIN_MESSAGE_MAP(C���Ƹ���������View, CView)
	// ��׼��ӡ����
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
END_MESSAGE_MAP()

// C���Ƹ���������View ����/����

C���Ƹ���������View::C���Ƹ���������View()
{
	// TODO: �ڴ˴���ӹ������

}

C���Ƹ���������View::~C���Ƹ���������View()
{
}

BOOL C���Ƹ���������View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	return CView::PreCreateWindow(cs);
}

// C���Ƹ���������View ����

void C���Ƹ���������View::OnDraw(CDC* /*pDC*/)
{
	C���Ƹ���������Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: �ڴ˴�Ϊ����������ӻ��ƴ���
}


// C���Ƹ���������View ��ӡ

BOOL C���Ƹ���������View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// Ĭ��׼��
	return DoPreparePrinting(pInfo);
}

void C���Ƹ���������View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӷ���Ĵ�ӡǰ���еĳ�ʼ������
}

void C���Ƹ���������View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӵ�ӡ����е��������
}


// C���Ƹ���������View ���

#ifdef _DEBUG
void C���Ƹ���������View::AssertValid() const
{
	CView::AssertValid();
}

void C���Ƹ���������View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

C���Ƹ���������Doc* C���Ƹ���������View::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(C���Ƹ���������Doc)));
	return (C���Ƹ���������Doc*)m_pDocument;
}
#endif //_DEBUG


// C���Ƹ���������View ��Ϣ�������
