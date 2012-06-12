// OperationView.cpp : implementation of the COperationView class
//

#include "stdafx.h"
#include "Operation.h"

#include "OperationDoc.h"
#include "OperationView.h"
#include "MainFrm.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// COperationView

IMPLEMENT_DYNCREATE(COperationView, CView)

BEGIN_MESSAGE_MAP(COperationView, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, OnFilePrintPreview)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_SETUP_SOURCE, &COperationView::OnSetupSource)
	ON_COMMAND(ID_SETUP_OPERATION, &COperationView::OnSetupOperation)
	ON_COMMAND(ID_SETUP_PROCESSTYPE, &COperationView::OnSetupProcesstype)
	ON_COMMAND(ID_SETUP_NOISEEDITING, &COperationView::OnSetupNoiseediting)
	ON_COMMAND(ID_SETUP_COMMENTS, &COperationView::OnSetupComments)
	ON_COMMAND(ID_SETUP_OPTIONS, &COperationView::OnSetupOptions)
	ON_COMMAND(ID_SETUP_DELAYSETUP, &COperationView::OnSetupDelaysetup)
	ON_COMMAND(ID_SETUP_PREFERENCES, &COperationView::OnSetupPreferences)
	ON_COMMAND(ID_VIEW_ALLVPBAR, &COperationView::OnViewAllVPBar)
	ON_UPDATE_COMMAND_UI(ID_VIEW_ALLVPBAR, &COperationView::OnUpdataViewAllVPBar)
	ON_COMMAND(ID_VIEW_VPTODUBAR, &COperationView::OnViewVPToDoBar)
	ON_UPDATE_COMMAND_UI(ID_VIEW_VPTODUBAR, &COperationView::OnUpdataViewVPToDoBar)
	ON_COMMAND(ID_VIEW_VPDONEBAR, &COperationView::OnViewVPDoneBar)
	ON_UPDATE_COMMAND_UI(ID_VIEW_VPDONEBAR, &COperationView::OnUpdataViewVPDoneBar)
	ON_COMMAND(ID_VIEW_ACTIVESOURCEBAR, &COperationView::OnViewActiveSourceBar)
	ON_UPDATE_COMMAND_UI(ID_VIEW_ACTIVESOURCEBAR, &COperationView::OnUpdataViewActiveSourceBar)
END_MESSAGE_MAP()

// COperationView construction/destruction

COperationView::COperationView()
{
	// TODO: add construction code here

}

COperationView::~COperationView()
{
}

BOOL COperationView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// COperationView drawing

void COperationView::OnDraw(CDC* /*pDC*/)
{
	COperationDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	// TODO: add draw code for native data here
}


// COperationView printing

void COperationView::OnFilePrintPreview()
{
	BCGPPrintPreview (this);
}

BOOL COperationView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void COperationView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void COperationView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}


// COperationView diagnostics

#ifdef _DEBUG
void COperationView::AssertValid() const
{
	CView::AssertValid();
}

void COperationView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

COperationDoc* COperationView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(COperationDoc)));
	return (COperationDoc*)m_pDocument;
}
#endif //_DEBUG


// COperationView message handlers


void COperationView::OnSetupSource()
{
	// TODO: 在此添加命令处理程序代码
	int itest = 0;
}


void COperationView::OnSetupOperation()
{
	// TODO: 在此添加命令处理程序代码
}


void COperationView::OnSetupProcesstype()
{
	// TODO: 在此添加命令处理程序代码
}


void COperationView::OnSetupNoiseediting()
{
	// TODO: 在此添加命令处理程序代码
}


void COperationView::OnSetupComments()
{
	// TODO: 在此添加命令处理程序代码
}


void COperationView::OnSetupOptions()
{
	// TODO: 在此添加命令处理程序代码
}


void COperationView::OnSetupDelaysetup()
{
	// TODO: 在此添加命令处理程序代码
}


void COperationView::OnSetupPreferences()
{
	// TODO: 在此添加命令处理程序代码
}

void COperationView::OnViewAllVPBar()
{
	CMainFrame* pMainFrame = (CMainFrame*)AfxGetMainWnd();
	pMainFrame->ShowControlBar(&pMainFrame->m_wndAllVP, !(pMainFrame->m_wndAllVP.IsVisible()), FALSE, TRUE);
	
}

void COperationView::OnUpdataViewAllVPBar(CCmdUI *pCmdUI)
{
	CMainFrame* pMainFrame = (CMainFrame*)AfxGetMainWnd();
	pCmdUI->SetCheck(pMainFrame->m_wndAllVP.IsVisible());
}

void COperationView::OnViewVPToDoBar()
{
	CMainFrame* pMainFrame = (CMainFrame*)AfxGetMainWnd();
	pMainFrame->ShowControlBar (&pMainFrame->m_wndVPToDo, !(pMainFrame->m_wndVPToDo.IsVisible()), FALSE, TRUE);
}

void COperationView::OnUpdataViewVPToDoBar(CCmdUI *pCmdUI)
{
	CMainFrame* pMainFrame = (CMainFrame*)AfxGetMainWnd();
	pCmdUI->SetCheck(pMainFrame->m_wndVPToDo.IsVisible());
}

void COperationView::OnViewVPDoneBar()
{
	CMainFrame* pMainFrame = (CMainFrame*)AfxGetMainWnd();
	pMainFrame->ShowControlBar (&pMainFrame->m_wndVPDone, !(pMainFrame->m_wndVPDone.IsVisible()), FALSE, TRUE);
}

void COperationView::OnUpdataViewVPDoneBar(CCmdUI *pCmdUI)
{
	CMainFrame* pMainFrame = (CMainFrame*)AfxGetMainWnd();
	pCmdUI->SetCheck(pMainFrame->m_wndVPDone.IsVisible());
}

void COperationView::OnViewActiveSourceBar()
{
	CMainFrame* pMainFrame = (CMainFrame*)AfxGetMainWnd();
	pMainFrame->ShowControlBar (&pMainFrame->m_wndActiveSource, !(pMainFrame->m_wndActiveSource.IsVisible()), FALSE, TRUE);
}

void COperationView::OnUpdataViewActiveSourceBar(CCmdUI *pCmdUI)
{
	CMainFrame* pMainFrame = (CMainFrame*)AfxGetMainWnd();
	pCmdUI->SetCheck(pMainFrame->m_wndActiveSource.IsVisible());
}