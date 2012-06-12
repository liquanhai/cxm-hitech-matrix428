// SensorListView.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "line.h"
#include "SensorListView.h"


// CSensorListView

IMPLEMENT_DYNCREATE(CSensorListView, CBCGPGridView)

CSensorListView::CSensorListView()
{

}

CSensorListView::~CSensorListView()
{

}

void CSensorListView::OnInitialUpdate() 
{
	CDocument* pDoc = GetDocument ();
	ASSERT_VALID (pDoc);

	pDoc->SetTitle (_T("Sensor List View"));
}

BEGIN_MESSAGE_MAP(CSensorListView, CBCGPGridView)
	// ��׼��ӡ����
	ON_COMMAND(ID_FILE_PRINT, OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, OnFilePrintPreview)

	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_SETFOCUS()
END_MESSAGE_MAP()


// CSensorListView ��ͼ

void CSensorListView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: �ڴ���ӻ��ƴ���
}


// CSensorListView ���

#ifdef _DEBUG
void CSensorListView::AssertValid() const
{
	CView::AssertValid();
}

#ifndef _WIN32_WCE
void CSensorListView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
#endif
#endif //_DEBUG

// CSensorListView ��ӡ

void CSensorListView::OnFilePrintPreview()
{
	BCGPPrintPreview(this);
}

void CSensorListView::OnFilePrint()
{
	CBCGPGridView::OnFilePrint();
}

BOOL CSensorListView::OnPreparePrinting(CPrintInfo* pInfo)
{
	return CBCGPGridView::OnPreparePrinting (pInfo);
}

void CSensorListView::OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo)
{
	CBCGPGridView::OnBeginPrinting (pDC, pInfo);
}

void CSensorListView::OnEndPrinting(CDC* pDC, CPrintInfo* pInfo)
{
	CBCGPGridView::OnEndPrinting (pDC, pInfo);
}

// CSensorListView ��Ϣ�������

int CSensorListView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  �ڴ������ר�õĴ�������
	m_pSensorListCtrl = new CSensorListCtrl;
	CRect rectClient;
	GetClientRect (rectClient);
	if (FALSE == m_pSensorListCtrl->Create (WS_CHILD, rectClient, this, 1))
	{
		return -1;
	}
	m_pSensorListCtrl->SetScrollBarsStyle (CBCGPScrollBar::BCGP_SBSTYLE_VISUAL_MANAGER);
	m_pSensorListCtrl->ShowWindow (SW_SHOW);

	m_pWndGridCtrl = m_pSensorListCtrl;
	return 0;
}

void CSensorListView::OnDestroy() 
{
	if (m_pSensorListCtrl->GetSafeHwnd () != NULL)
	{
		m_pSensorListCtrl->DestroyWindow ();
		delete m_pSensorListCtrl;
	}

	m_pSensorListCtrl = NULL;
	m_pWndGridCtrl = NULL;

	CBCGPGridView::OnDestroy();
}

void CSensorListView::OnSize(UINT nType, int cx, int cy)
{
	CBCGPGridView::OnSize(nType, cx, cy);

	// TODO: �ڴ˴������Ϣ����������
	AdjustLayout();
}

void CSensorListView::OnSetFocus(CWnd* pOldWnd)
{
	CBCGPGridView::OnSetFocus(pOldWnd);

	// TODO: �ڴ˴������Ϣ����������
	if (m_pSensorListCtrl->GetSafeHwnd () != NULL)
	{
		m_pSensorListCtrl->SetFocus ();
	}
}

// ����
void CSensorListView::AdjustLayout()
{
	if (m_pSensorListCtrl->GetSafeHwnd () == NULL)
	{
		return;
	}
	CRect rectClient;
	GetClientRect (rectClient);
	m_pSensorListCtrl->SetWindowPos (NULL, 0, 0, rectClient.Width (), rectClient.Height (), SWP_NOACTIVATE | SWP_NOZORDER);
}

// ���¼����ֳ���������
void CSensorListView::OnReloadSiteDataCMD()
{
	m_pSensorListCtrl->OnReloadSiteDataCMD();
}

// Ϊ�µĲ�������ˢ����ʾ
void CSensorListView::OnRefreshForNewTestValue(int iTestType)
{
	m_pSensorListCtrl->OnRefreshForNewTestValue(iTestType);
}