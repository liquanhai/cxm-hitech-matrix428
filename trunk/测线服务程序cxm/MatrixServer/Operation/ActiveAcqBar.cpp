#include "StdAfx.h"
#include "Operation.h"
#include "ActiveAcqBar.h"


CActiveAcqBar::CActiveAcqBar(void)
{
}


CActiveAcqBar::~CActiveAcqBar(void)
{
}
BEGIN_MESSAGE_MAP(CActiveAcqBar, CBCGPDockingControlBar)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_DESTROY()
	ON_WM_CONTEXTMENU()
END_MESSAGE_MAP()


int CActiveAcqBar::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CBCGPDockingControlBar::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  �ڴ������ר�õĴ�������
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
	m_ImageList.Create (IDB_BITMAP_ACQ, 16, 0, RGB (255, 0, 255));
	m_GridView.SetImageList (&m_ImageList);
	return 0;
}


void CActiveAcqBar::OnSize(UINT nType, int cx, int cy)
{
	CBCGPDockingControlBar::OnSize(nType, cx, cy);

	// TODO: �ڴ˴������Ϣ����������
	if (m_GridView.GetSafeHwnd ())
	{
		m_GridView.SetWindowPos (NULL, -1, -1, cx, cy, SWP_NOMOVE | SWP_NOZORDER | SWP_NOACTIVATE);
	}
}


void CActiveAcqBar::OnDestroy()
{
	CBCGPDockingControlBar::OnDestroy();

	// TODO: �ڴ˴������Ϣ����������
	m_GridView.RemoveAll();
}

// ���ñ�ͷ
bool CActiveAcqBar::SetGridHead(void)
{
	if(!m_GridView.GetSafeHwnd())		
		return false;
	m_GridView.InsertColumn (0, _T(""), 50);
	m_GridView.InsertColumn (1, _T("Shot#"), 150);
	m_GridView.SetHeaderAlign (1, HDF_LEFT);
	m_GridView.SetColumnAlign (1, HDF_RIGHT);
	m_GridView.InsertColumn (2, _T("Acq Nb"), 150);
	m_GridView.SetHeaderAlign (2, HDF_LEFT);
	m_GridView.SetColumnAlign (2, HDF_RIGHT);
	m_GridView.InsertColumn (3, _T("Acq Type"), 150);
	m_GridView.SetHeaderAlign (3, HDF_LEFT);
	m_GridView.SetColumnAlign (3, HDF_RIGHT);
	m_GridView.InsertColumn (4, _T("Dump"), 150);
	m_GridView.SetHeaderAlign (4, HDF_LEFT);
	m_GridView.SetColumnAlign (4, HDF_RIGHT);
	return true;
}


// ����ȫ��Acq��Ϣ
void CActiveAcqBar::LoadAcqInfos(void)
{
	m_GridView.RemoveAll();
	for (int i =0; i<5; i++)
	{
		LoadAcqInfo();
	}
}


// ���뵥��Acq��Ϣ
void CActiveAcqBar::LoadAcqInfo(void)
{
	CBCGPGridRow* pRow = m_GridView.CreateRow (5);
	pRow->GetItem (0)->SetImage(1);
	pRow->GetItem (1)->SetValue (1);
	pRow->GetItem (2)->SetValue (1);
	pRow->GetItem (3)->SetValue (1);
	pRow->GetItem (4)->SetValue (1);
	m_GridView.AddRow (pRow, TRUE);
}


void CActiveAcqBar::OnContextMenu(CWnd* /*pWnd*/, CPoint /*point*/)
{
	// TODO: �ڴ˴������Ϣ����������
}
