// ActiveSourceView.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Operation.h"
#include "ActiveSourceView.h"
#include "MainFrm.h"


////////////////////////////////////////////////////////////////////////////////////////////////// 
////////////////////////////////////////////////////////////////////////////////////////////////// 
/////////////////////////CActiveSourceGridCtrl  //////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////// 
////////////////////////////////////////////////////////////////////////////////////////////////// 

IMPLEMENT_DYNAMIC(CActiveSourceGridCtrl, CBCGPGridCtrl)

CActiveSourceGridCtrl::CActiveSourceGridCtrl()
{
	//EnableVisualManagerStyle();
}

CActiveSourceGridCtrl::~CActiveSourceGridCtrl()
{
}


BEGIN_MESSAGE_MAP(CActiveSourceGridCtrl, CBCGPGridCtrl)
END_MESSAGE_MAP()

void CActiveSourceGridCtrl::SetRowHeight()
{
	CBCGPGridCtrl::SetRowHeight();

	m_nRowHeight = m_nRowHeight + 5;
	m_nLargeRowHeight = m_nRowHeight;
}
/**
 * @brief �̳и�����������ѡ��ı�
 * @note  �����б�ѡ�е���Ŀ�����仯ʱ��ϵͳ����øú���֪ͨ�û���
 * @note  ���ݵ�ǰ��ѡ�����Դ��״̬����ʹ�ܻ��߽�ֹ��GO������Stop������Abort��������ť��
 * @param CBCGPGridRow* pNewRow, ��ǰѡ�е���Դ��ָ��
 * @param CBCGPGridRow* pOldRow��ǰһ�α�ѡ�е���Դ��ָ��
 * @return void
 */
void CActiveSourceGridCtrl::OnChangeSelection(CBCGPGridRow* pNewRow,CBCGPGridRow* pOldRow)
{
	int nSourceState;
	CActiveSourceView *pView = (CActiveSourceView*)GetParent();
	if(pNewRow!=NULL)
	{
		// ��ǰѡ��Ĳ��ǿ���
		nSourceState = pNewRow->GetItem(0)->GetImage();
		if(nSourceState==SCR_READY)	// ���а�ťʹ��
		{
			if (   pView->m_btnGo.GetSafeHwnd()
				&& pView->m_btnStop.GetSafeHwnd()
				&& pView->m_btnAbort.GetSafeHwnd())
			{	
				pView->m_btnGo.EnableWindow(TRUE);
				pView->m_btnStop.EnableWindow(TRUE);
				pView->m_btnAbort.EnableWindow(TRUE);
				return;
			}			
		}
		else if(nSourceState==SCR_FOCUS)	// GO��ť��ֹ��������ťʹ��
		{
			if (   pView->m_btnGo.GetSafeHwnd()
				&& pView->m_btnStop.GetSafeHwnd()
				&& pView->m_btnAbort.GetSafeHwnd())
			{	
				pView->m_btnGo.EnableWindow(FALSE);
				pView->m_btnStop.EnableWindow(TRUE);
				pView->m_btnAbort.EnableWindow(TRUE);
				return;
			}

		}

	}
	// û��ѡ�л���ѡ�е���Դû��׼���ã����ֹ��ť
	if (   pView->m_btnGo.GetSafeHwnd()
		&& pView->m_btnStop.GetSafeHwnd()
		&& pView->m_btnAbort.GetSafeHwnd())
	{
		pView->m_btnGo.EnableWindow(FALSE);
		pView->m_btnStop.EnableWindow(FALSE);
		pView->m_btnAbort.EnableWindow(FALSE);
	}
	return CBCGPGridCtrl::OnChangeSelection(pNewRow,pOldRow);
}

////////////////////////////////////////////////////////////////////////////////////////////////// 
////////////////////////////////////////////////////////////////////////////////////////////////// 
/////////////////////////   CActiveSourceView  //////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////// 
////////////////////////////////////////////////////////////////////////////////////////////////// 
IMPLEMENT_DYNCREATE(CActiveSourceView, CBCGPFormView)

CActiveSourceView::CActiveSourceView()
	: CBCGPFormView(CActiveSourceView::IDD)
{
	EnableVisualManagerStyle ();
}

CActiveSourceView::~CActiveSourceView()
{
}

void CActiveSourceView::DoDataExchange(CDataExchange* pDX)
{
	CBCGPFormView::DoDataExchange(pDX);
	// DDX_Control(pDX, IDC_STATICGRID, m_wndGridLocation);
	DDX_Control(pDX, IDC_BUTTONGO, m_btnGo);
	DDX_Control(pDX, IDC_BUTTONSTOP, m_btnStop);
	DDX_Control(pDX, IDC_BUTTONABORT, m_btnAbort);
}

BEGIN_MESSAGE_MAP(CActiveSourceView, CBCGPFormView)
	ON_WM_SIZE()
	ON_WM_DESTROY()
	ON_WM_MOUSEACTIVATE()
	ON_BN_CLICKED(IDC_BUTTONGO, &CActiveSourceView::OnBnClickedButtongo)
END_MESSAGE_MAP()


// CActiveSourceView ���

#ifdef _DEBUG
void CActiveSourceView::AssertValid() const
{
	CBCGPFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CActiveSourceView::Dump(CDumpContext& dc) const
{
	CBCGPFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CActiveSourceView ��Ϣ�������
BOOL CActiveSourceView::CreateView(CWnd* pParent, CCreateContext* pContext)
{	
	CRect rect(0,0,300,300);

	if (!Create(NULL, NULL, AFX_WS_DEFAULT_VIEW,
		rect, pParent, AFX_IDW_PANE_FIRST, pContext))
	{
		TRACE0("Warning: couldn't create CMyFormView!\n");
		return FALSE;
	}

	CRect rectGrid;
	m_ImageList.Create (IDB_SOURCESTATE,16,0,RGB (255, 0, 255));
	m_wndGrid.SetImageList (&m_ImageList);
	GetClientRect(&rectGrid);
	rectGrid.bottom = rectGrid.bottom -80;
	m_wndGrid.Create (WS_CHILD | WS_VISIBLE | WS_TABSTOP | WS_BORDER, rectGrid, this, (UINT)-1);
	// ��ֹ������
	m_wndGrid.EnableHeader (TRUE, BCGP_GRID_HEADER_HIDE_ITEMS);
	m_wndGrid.EnableInvertSelOnCtrl (FALSE);
		// ���ô���λ��
	m_wndGrid.SetWindowPos (&CWnd::wndTop, -1, -1, -1, -1, SWP_NOMOVE | SWP_NOSIZE | SWP_NOACTIVATE);

	BCGP_GRID_COLOR_DATA clrData;
	clrData = m_wndGrid.GetColorTheme();
	clrData.m_clrBackground = ::GetSysColor(COLOR_3DFACE);		//globalData.clrBarFace;
	clrData.m_EvenColors.m_clrBackground = RGB(255,255,255);
	clrData.m_OddColors.m_clrBackground = RGB(250,253,253);

	m_wndGrid.SetColorTheme(clrData);
	m_wndGrid.SetReadOnly ();	
	m_wndGrid.SetSingleSel(TRUE);
	m_wndGrid.SetWholeRowSel(TRUE);
	m_wndGrid.EnableDragSelection(FALSE);

	SetGridHead();
	//m_wndGrid.LoadState (_T("ActiveSourceGrid"));
	return TRUE;
}
void CActiveSourceView::OnInitialUpdate()
{
	CBCGPFormView::OnInitialUpdate();

	// TODO: �ڴ����ר�ô����/����û���
	CRect rc;
	GetWindowRect(&rc);
	SendMessage(WM_SIZE,SIZE_RESTORED,MAKELPARAM(rc.Width(),rc.Height()) );

}

void CActiveSourceView::OnSize(UINT nType, int cx, int cy)
{
	CBCGPFormView::OnSize(nType, cx, cy);

	// TODO: �ڴ˴������Ϣ����������
	if (m_wndGrid.GetSafeHwnd())
	{
		m_wndGrid.SetWindowPos (NULL, -1, -1, cx, cy-60, SWP_NOZORDER | SWP_NOACTIVATE); // SWP_NOMOVE | 
	}
 //	CWnd* pBtn=GetDlgItem(IDC_BUTTONGO);
 	if(m_btnGo.GetSafeHwnd())
 	{
 		m_btnGo.SetWindowPos (NULL, cx/2-220, cy-50, 100, 40, SWP_NOZORDER  |SWP_DRAWFRAME);
 	}
	if(m_btnStop.GetSafeHwnd())
	{
		m_btnStop.SetWindowPos (NULL, cx/2-100, cy-50, 100, 40, SWP_NOZORDER |SWP_DRAWFRAME);
	}
	if(m_btnAbort.GetSafeHwnd())
	{
		m_btnAbort.SetWindowPos (NULL, cx/2+20, cy-50, 100, 40, SWP_NOZORDER|SWP_DRAWFRAME );
	}
}
void CActiveSourceView::OnDestroy()
{
	CBCGPFormView::OnDestroy();

	// TODO: �ڴ˴������Ϣ����������
	if (m_wndGrid.GetSafeHwnd())
	{
		// m_wndGrid.SaveState(_T("ActiveSourceGrid"));
		m_wndGrid.RemoveAll();
	}
}
bool CActiveSourceView::SetGridHead(void)
{
	if(!m_wndGrid.GetSafeHwnd())
		return false;	
	
	m_wndGrid.InsertColumn (0, _T("��"), 40);
	m_wndGrid.InsertColumn (1, _T("Rdy"), 40);
	m_wndGrid.InsertColumn (2, _T("Rdy VP"), 60);
	m_wndGrid.InsertColumn (3, _T("Source Name"), 120);
	m_wndGrid.InsertColumn (4, _T("Source Index"), 120);
	m_wndGrid.InsertColumn (5, _T("Shot Nb"), 80);
	m_wndGrid.InsertColumn (6, _T("Dist min"), 80);
//	m_wndGrid.InsertColumn (7, _T("Current Stack"), 120);
	m_wndGrid.InsertColumn (7, _T("SourcePoint Line"), 150);
	m_wndGrid.InsertColumn (8, _T("SourcePoint Number"), 160);
	m_wndGrid.InsertColumn (9, _T("SourcePoint Index"), 160);
	m_wndGrid.InsertColumn (10, _T("Sfl"), 60);
	m_wndGrid.InsertColumn (11, _T("Sfn"), 60);
	m_wndGrid.InsertColumn (12, _T("Spread#"), 80);
	m_wndGrid.InsertColumn (13, _T("SuperSpread"), 100);
	m_wndGrid.InsertColumn (14, _T("ProcessType"), 100);
	m_wndGrid.InsertColumn (15, _T("Swath"), 60);
	//m_wndGrid.SetGridHeaderHeight(100);
	//m_wndGrid.AddRow();
	return true;
}
int CActiveSourceView::OnMouseActivate(CWnd* pDesktopWnd, UINT nHitTest, UINT message)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ

	return CWnd::OnMouseActivate(pDesktopWnd, nHitTest, message);
}
/************************************************************************************
    ��    ����
    
    ��    �룺
    
    ��    ����
  
    �� �� ֵ��
    
    ��    �ܣ�     �û����¡�GO����ť����ʼ���ڡ�
	               ��������Ӧ��GO��ť����ִ������������
				   
				   1������������֪ͨ�������ɼ��߳̿�ʼ�������ݲɼ���
				   2��֪ͨ������ʼ���ݲɼ���
				   3����������֪ͨ��ը�����

    �޸���ʷ��

*************************************************************************************/
void CActiveSourceView::OnBnClickedButtongo()
{
	CMainFrame* pFrm = (CMainFrame*)AfxGetMainWnd();
	CBCGPGridRow* pRow = m_wndGrid.GetCurSel();
	if(!pRow)
	{
		pFrm->MessageBox(_T("First select shot source!"),_T("Alarm"),MB_OK);
		return;
	}
	// �õ�����ǰѡ����к�
	int nRow=pRow->GetRowId();
	if(nRow>=pFrm->m_AllShotSrcs.GetCount())
	{
		return;
	}
	// �ҵ���Դ
	CShotSource* pSource = pFrm->m_AllShotSrcs.GetShotSource(nRow);
	
	// ���Ҽ�����ڵ����Դ����CActiveShot�����÷��ں���
	CActiveShot* pActiveShot = pFrm->m_AllActiveShots.LookActiveShot(pSource);
	if(pActiveShot!=NULL)
	{
		pActiveShot->SendGeneralCMD(OPERATION_CMD_GO);
	}
	
	
}

////////////////////////////////////////////////////////////////////////////////////////////////// | SWP_NOACTIVATE
////////////////////////////////////////////////////////////////////////////////////////////////// SWP_NOMOVE | 
//////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////// | SWP_NOACTIVATE
////////////////////////////////////////////////////////////////////////////////////////////////// | SWP_NOACTIVATE
// CActiveSourceWnd

BEGIN_MESSAGE_MAP(CActiveSourceWnd, CBCGPDockingControlBar)
	//{{AFX_MSG_MAP(CActiveSourceWnd)
	ON_WM_CREATE()
	//ON_WM_PAINT()
	ON_WM_SIZE()
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP	
	ON_WM_CONTEXTMENU()
END_MESSAGE_MAP()

CActiveSourceWnd::CActiveSourceWnd(void):m_pContext(NULL)
{
	CRuntimeClass* pFactory = RUNTIME_CLASS(CActiveSourceView);
	m_pFormView = (CActiveSourceView *)(pFactory->CreateObject());	
}

CActiveSourceWnd::~CActiveSourceWnd(void)
{
}
/////////////////////////////////////////////////////////////////////////////
// CWorkspaceBar message handlers

int CActiveSourceWnd::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CBCGPDockingControlBar::OnCreate(lpCreateStruct) == -1)
		return -1;

	if (m_pFormView != NULL)
	{
		m_pFormView->CreateView(this, m_pContext);
	}
	LoadState (_T("ActiveSourceWnd"));
	return 0;
}
/*
void CActiveSourceWnd::OnPaint() 
{
	CPaintDC dc(this); // device context for painting

	CRect rect;
	GetClientRect (rect);

	dc.FillSolidRect (rect, ::GetSysColor (COLOR_3DFACE));
}
*/
void CActiveSourceWnd::OnSize(UINT nType, int cx, int cy) 
{
	CBCGPDockingControlBar::OnSize(nType, cx, cy);
	
	if (m_pFormView->GetSafeHwnd ())
	{
		m_pFormView->SetWindowPos (NULL, -1, -1, cx, cy, SWP_NOMOVE | SWP_NOZORDER | SWP_NOACTIVATE);
	}	
}


void CActiveSourceWnd::OnDestroy()
{
	CBCGPDockingControlBar::OnDestroy();

	// TODO: �ڴ˴������Ϣ����������
	 SaveState(_T("ActiveSourceWnd"));
}
BOOL CActiveSourceWnd::Create(LPCTSTR lpszCaption,CWnd*pParentWnd,const RECT&rect,BOOL bHasGripper,UINT nID,DWORD dwStyle,DWORD dwTabbedStyle,DWORD dwBCGStyle,CCreateContext*pContext)
{
	// TODO: �ڴ����ר�ô����/����û���

	BOOL bFlag=CBCGPDockingControlBar::Create( lpszCaption,pParentWnd,rect, bHasGripper, nID, dwStyle, dwTabbedStyle, dwBCGStyle,pContext);

	SetTabbedControlBarRTC (RUNTIME_CLASS (CBCGPTabbedControlBar));
	// ɾ��Caption��ť���ڱ������������Ƿ���
	RemoveCaptionButtons ();
	return bFlag;
}


/******************************************************************************
    ��    ����
    
    ��    �룺
    
    ��    ����
  
    �� �� ֵ��
    
    ��    �ܣ�

    �޸���ʷ��

*******************************************************************************/
CBCGPGridCtrl* CActiveSourceWnd::GetGridCtrl(void)
{
	if(NULL==m_pFormView)
		return NULL;
	return &(m_pFormView->m_wndGrid);
}
/******************************************************************************
    ��    ����
    
    ��    �룺
    
    ��    ����
  
    �� �� ֵ��
    
    ��    �ܣ� ����Դ����ص�������

    �޸���ʷ��

*******************************************************************************/
void CActiveSourceWnd::LoadShotSources(CShotSources* pShotSrcs)
{
	if(NULL==pShotSrcs)
		return;
	CBCGPGridCtrl* pGridCtrl = GetGridCtrl();
	if(NULL==pGridCtrl)
		return;
	int nCount = pShotSrcs->GetCount();
	pGridCtrl->RemoveAll();
	CShotSource* pSrc = NULL;
	for (int nRow = 0; nRow < nCount; nRow++)
	{
		pSrc=pShotSrcs->GetShotSource(nRow);
		if(!pSrc )
			continue;
		LoadShotSource(pSrc);
	}
	pGridCtrl->AdjustLayout ();
	return;
}
/******************************************************************************
    ��    ����
    
    ��    �룺
    
    ��    ����
  
    �� �� ֵ��
    
    ��    �ܣ� ��һ����Դ���ص�������

    �޸���ʷ��

*******************************************************************************/
void CActiveSourceWnd::LoadShotSource(CShotSource* pShotSrc)
{
	if(NULL==pShotSrc)
		return ;
	CBCGPGridCtrl* pGridCtrl = GetGridCtrl();
	if(NULL==pGridCtrl)
		return;
	CBCGPGridRow* pRow = pGridCtrl->CreateRow (pGridCtrl->GetColumnCount());
	pRow->GetItem (0)->SetImage(pShotSrc->m_bySourceState);
	pRow->GetItem (3)->SetValue (LPCTSTR(pShotSrc->m_strLabel));
	pRow->GetItem (4)->SetValue (pShotSrc->m_dwSourceIndex);
	// �����е���������Ϊ��Դ�ı��
	pRow->SetData(pShotSrc->m_dwSourceNb);
	// ����һ�м�¼
	pGridCtrl->AddRow(pRow);
}


void CActiveSourceWnd::OnContextMenu(CWnd* /*pWnd*/, CPoint point)
{
	// TODO: �ڴ˴������Ϣ���������� IDR_POPUP_VPSHOT
	
}
/******************************************************************************
    ��    ����
    
    ��    �룺
    
    ��    ����
  
    �� �� ֵ��
    
    ��    �ܣ� �û�ѡ����Դ���ں�׼������ʱ�����ںŵ���Ϣ��CShotPoint��д������ж�Ӧ����Դ����

    �޸���ʷ��

*******************************************************************************/
int CActiveSourceWnd::LoadShotPointBySource(CShotSource* pSource, CShotPoint* pShotPoint)
{
	if(!pSource || !pShotPoint)
		return -1;
	CBCGPGridCtrl* pGridCtrl = GetGridCtrl();
	if(NULL==pGridCtrl)
		return -1;

	CBCGPGridRow *pRow=NULL;
	int nRowCount = pGridCtrl->GetRowCount();
	//_variant_t  vt;
	for(int i=0;i<nRowCount;i++)
	{
		pRow = pGridCtrl->GetRow(i);
		//vt = pRow->GetItem(3)->GetValue();
		// �ж�ÿ�е�������������Դ�ı���Ƿ����
		if(pRow->GetData()==pSource->m_dwSourceNb)
		{
			// װ���ڵ������
			pRow->GetItem (5)->SetValue (pShotPoint->m_dwShotNb);
			pRow->GetItem (6)->SetValue (_T("-"));
			pRow->GetItem (7)->SetValue (pShotPoint->m_fSourceLine);
			pRow->GetItem (8)->SetValue (pShotPoint->m_fSourceNb);
			pRow->GetItem (9)->SetValue (pShotPoint->m_dwSourcePointIndex);
			pRow->GetItem (10)->SetValue (pShotPoint->m_dwSpreadSFL);
			pRow->GetItem (11)->SetValue (pShotPoint->m_dwSpreadSFN);
			pRow->GetItem (12)->SetValue (pShotPoint->m_dwSpreadNb);
			pRow->GetItem (13)->SetValue (pShotPoint->m_dwSuperSpread);
			pRow->GetItem (14)->SetValue (pShotPoint->m_dwProcessNb);
			pRow->GetItem (15)->SetValue (pShotPoint->m_dwSwathNb);
			return 1;
		}
	}
	
	return 1;

}

