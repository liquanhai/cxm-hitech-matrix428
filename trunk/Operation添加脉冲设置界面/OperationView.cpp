// OperationView.cpp : COperationView ���ʵ��
//

#include "stdafx.h"
#include "Operation.h"
#include "MainFrm.h"
#include "OperationDoc.h"
#include "OperationView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// COperationView

IMPLEMENT_DYNCREATE(COperationView, CBCGPFormView)

BEGIN_MESSAGE_MAP(COperationView, CBCGPFormView)
	// ��׼��ӡ����
	ON_COMMAND(ID_FILE_PRINT, &CBCGPFormView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CBCGPFormView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CBCGPFormView::OnFilePrintPreview)
	ON_WM_SIZE()
END_MESSAGE_MAP()

// COperationView ����/����

COperationView::COperationView()
	: CBCGPFormView(COperationView::IDD)
{
	// TODO: �ڴ˴���ӹ������
	EnableVisualManagerStyle();
}

COperationView::~COperationView()
{
}

void COperationView::DoDataExchange(CDataExchange* pDX)
{
	CBCGPFormView::DoDataExchange(pDX);	

	DDX_Control(pDX, IDC_LISTSTATUSMAIL, m_ctrlListBox);
	DDX_Control(pDX, IDC_STATICSTATUSMAIL, m_ctrlStatic);
}

BOOL COperationView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	return CBCGPFormView::PreCreateWindow(cs);
}

// COperationView ����

void COperationView::OnDraw(CDC* pDC)
{
	COperationDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: �ڴ˴�Ϊ����������ӻ��ƴ���
	RECT  rcClient;
	GetClientRect(&rcClient);
	pDC->FillSolidRect(&rcClient,::GetSysColor(COLOR_3DFACE));

}


// COperationView ��ӡ

BOOL COperationView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// Ĭ��׼��
	return DoPreparePrinting(pInfo);
}

void COperationView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӷ���Ĵ�ӡǰ���еĳ�ʼ������
}

void COperationView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӵ�ӡ����е��������
}


// COperationView ���

#ifdef _DEBUG
void COperationView::AssertValid() const
{
	CBCGPFormView::AssertValid();
}

void COperationView::Dump(CDumpContext& dc) const
{
	CBCGPFormView::Dump(dc);
}

COperationDoc* COperationView::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(COperationDoc)));
	return (COperationDoc*)m_pDocument;
}
#endif //_DEBUG


// COperationView ��Ϣ�������

void COperationView::OnInitialUpdate()
{
	CBCGPFormView::OnInitialUpdate();

	// TODO: �ڴ����ר�ô����/����û���
	m_OperationLog.m_pListBox = &m_ctrlListBox;

	CRect rc,rcVPDone,rcVPToDo,rcVPAll,rcActive;
	GetWindowRect(&rc);
	SendMessage(WM_SIZE,SIZE_RESTORED,MAKELPARAM(rc.Width(),rc.Height()));
//	MoveWindow(	0,rc.bottom-100 ,rc.Width(),100 ,TRUE);
	
	CMainFrame *pFrm = (CMainFrame*)AfxGetMainWnd();
	CBCGPDockBar *pBottomBar=NULL;	// �������
	CBCGPDockBar *pUpBottomBar=NULL;		// �������������
	CRect      rcBottom,rcUpBottom;
	if(    pFrm->m_wndVPDone.GetSafeHwnd() 	&& pFrm->m_wndVPToDo.GetSafeHwnd()
		&& pFrm->m_wndVPAll.GetSafeHwnd()   && pFrm->m_wndActiveSource.GetSafeHwnd())
	{
		/*
		pFrm->m_wndVPDone.GetWindowRect(&rcVPDone);
		pFrm->m_wndVPToDo.GetWindowRect(&rcVPToDo);
		pFrm->m_wndVPAll.GetWindowRect(&rcVPAll);
		pFrm->m_wndActiveSource.GetWindowRect(&rcActive);
		if(rcVPDone.bottom>rcVPToDo.bottom)
		{	
			
		}
		else
		{

		}
		
		
		pFrm->m_wndVPDone.GetWindowRect(&rcVPDone);
		pFrm->m_wndVPToDo.GetWindowRect(&rcVPToDo);
		pFrm->m_wndVPAll.GetWindowRect(&rcVPAll);
		if(rcVPAll.bottom >= rcVPToDo.bottom && rcVPAll.bottom >= rcVPDone.bottom )
		{
			rcVPAll.bottom = rc.bottom-100;
			pFrm->m_wndVPAll.MoveWindow(rcVPAll,TRUE);			
		}
		else if (rcVPToDo.bottom >= rcVPAll.bottom && rcVPToDo.bottom >= rcVPDone.bottom)
		{
			rcVPToDo.bottom = rc.bottom-100;
			pFrm->m_wndVPToDo.MoveWindow(rcVPToDo,TRUE);
			if(rcVPAll.bottom>=rcVPDone.bottom)
			{
				pFrm->m_wndVPToDo.DockToWindow(&pFrm->m_wndVPAll,CBRS_ALIGN_BOTTOM);
			}
			else
			{
				pFrm->m_wndVPToDo.DockToWindow(&pFrm->m_wndVPDone,CBRS_ALIGN_BOTTOM);
			}
		}
		else if(rcVPDone.bottom >= rcVPAll.bottom && rcVPDone.bottom >= rcVPToDo.bottom)
		{
			rcVPDone.bottom = rc.bottom-100;
			pFrm->m_wndVPDone.MoveWindow(rcVPDone,TRUE);
			if(rcVPAll.bottom>=rcVPToDo.bottom)
			{
				pFrm->m_wndVPDone.DockToWindow(&pFrm->m_wndVPAll,CBRS_ALIGN_BOTTOM);
			}
			else
			{
				pFrm->m_wndVPDone.DockToWindow(&pFrm->m_wndVPToDo,CBRS_ALIGN_BOTTOM);
			}

		}
		*/
	}
	
}

void COperationView::OnSize(UINT nType, int cx, int cy)
{
	CBCGPFormView::OnSize(nType, cx, cy);

	// TODO: �ڴ˴������Ϣ����������
	if (m_ctrlListBox.GetSafeHwnd())
	{
		m_ctrlListBox.SetWindowPos (NULL, 0, 20, cx, cy-22, SWP_NOMOVE | SWP_NOZORDER | SWP_NOACTIVATE);
	}
	if (m_ctrlStatic.GetSafeHwnd())
	{
		m_ctrlStatic.SetWindowPos (NULL, 0, 0, cx, cy, SWP_NOMOVE | SWP_NOZORDER | SWP_NOACTIVATE);
	}

}
