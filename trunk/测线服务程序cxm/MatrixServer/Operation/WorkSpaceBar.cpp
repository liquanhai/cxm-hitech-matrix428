// workspace2.cpp : implementation of the CWorkSpaceBar class
//

#include "stdafx.h"
#include "Operation.h"
#include "WorkSpaceBar.h"
#include "MainFrm.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


/////////////////////////////////////////////////////////////////////////////
// CWorkSpaceBar

BEGIN_MESSAGE_MAP(CWorkSpaceBar, CBCGPDockingControlBar)
	//{{AFX_MSG_MAP(CWorkSpaceBar)
	ON_WM_CREATE()
	ON_WM_SIZE()
	//}}AFX_MSG_MAP
	ON_WM_CONTEXTMENU()
	ON_WM_DESTROY()
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CWorkSpaceBar construction/destruction

CWorkSpaceBar::CWorkSpaceBar()
{
	// TODO: add one-time construction code here
}

CWorkSpaceBar::~CWorkSpaceBar()
{
}

/////////////////////////////////////////////////////////////////////////////
// CWorkSpaceBar message handlers

int CWorkSpaceBar::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CBCGPDockingControlBar::OnCreate(lpCreateStruct) == -1)
		return -1;

	CRect rectDummy;
	rectDummy.SetRectEmpty ();
	// TODO: create your own tab windows here:
	const DWORD dwViewStyle =	WS_CHILD | WS_VISIBLE | TVS_HASLINES | 
								TVS_LINESATROOT | TVS_HASBUTTONS;
	if (!m_GridView.Create(dwViewStyle, rectDummy, this, 1))
	{
		TRACE0("Failed to create Grid View!\n");
		return -1;
	}
	BCGP_GRID_COLOR_DATA clrData;
	clrData = m_GridView.GetColorTheme();
	clrData.m_clrBackground = ::GetSysColor(COLOR_3DFACE);
	clrData.m_EvenColors.m_clrBackground = RGB(255,255,255);	// ������
	clrData.m_OddColors.m_clrBackground = RGB(250,250,250);		// ż����

	m_GridView.SetColorTheme(clrData);	
	m_GridView.SetReadOnly();	
	m_GridView.SetSingleSel(TRUE);
	m_GridView.SetWholeRowSel(TRUE);	
	m_GridView.EnableHeader (TRUE, BCGP_GRID_HEADER_HIDE_ITEMS);
	m_GridView.EnableDragSelection(FALSE);

	// ���ñ�ͷ
	SetGridHead();
	m_ImageList.Create (IDB_BITMAP_VP, 16, 0, RGB (255, 0, 255));
	m_GridView.SetImageList (&m_ImageList);
	return 0;
}

void CWorkSpaceBar::OnSize(UINT nType, int cx, int cy) 
{
	CBCGPDockingControlBar::OnSize(nType, cx, cy);

	// Tab control should cover a whole client area:
	if (m_GridView.GetSafeHwnd ())
	{
		m_GridView.SetWindowPos (NULL, -1, -1, cx, cy, SWP_NOMOVE | SWP_NOZORDER | SWP_NOACTIVATE);
	}
}

// �����Ҽ��˵���WM_CONTEXTMENU��Ϣ��Ӧ����
void CWorkSpaceBar::OnContextMenu(CWnd* pWnd, CPoint point)
{
	// TODO: �ڴ˴������Ϣ����������
	CBCGPGridRow* pRow= m_GridView.GetCurSel();
	if(NULL==pRow)
		return;
	CMenu menu;
	VERIFY(menu.LoadMenu (IDR_POPUP_VPSHOT));
	CMenu* pPopup = menu.GetSubMenu(0);
	ASSERT(pPopup != NULL);
	// ��̬��Ӳ˵�
	CMainFrame* pFrm = (CMainFrame*)AfxGetMainWnd();
	int i;
	int nCount = pFrm->m_wndActiveSource.m_GridView.GetRowCount();
	CString  strTemp;
	for(i=0;i<nCount;i++)
	{	
		// �õ���Դ
		//		strTemp = _T("Start Seismonitor with ")+;
		strTemp.Format(_T("Start Seismonitor with %d"), i);
		// ��̬��Ӳ˵�
		pPopup->AppendMenu(MF_STRING ,m_iActiveSourceID[i], strTemp);
		pPopup->EnableMenuItem(m_iActiveSourceID[i],MF_BYCOMMAND | MF_ENABLED);		 
	}

	CBCGPPopupMenu* pPopupMenu = new CBCGPPopupMenu;
	// ��ʾ�˵������������Ӧ�˵�
	pPopupMenu->Create (pFrm, point.x, point.y,pPopup->Detach(),FALSE,TRUE); //pPopup->m_hMenu 
}


// ���ñ�ͷ
bool CWorkSpaceBar::SetGridHead(void)
{
	return false;
}


// ����ȫ���ڵ���Ϣ
void CWorkSpaceBar::LoadShotPoints(void)
{
}


// ���뵥���ڵ���Ϣ
void CWorkSpaceBar::LoadShotPoint(void)
{
}


void CWorkSpaceBar::OnDestroy()
{
	CBCGPDockingControlBar::OnDestroy();

	// TODO: �ڴ˴������Ϣ����������
	m_GridView.RemoveAll();
}

