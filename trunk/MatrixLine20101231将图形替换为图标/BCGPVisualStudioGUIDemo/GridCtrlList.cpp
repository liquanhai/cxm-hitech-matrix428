// GridCtrlList.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "BCGPVisualStudioGUIDemo.h"
#include "GridCtrlList.h"


// CGridCtrlList

IMPLEMENT_DYNAMIC(CGridCtrlList, CBCGPGridCtrl)

CGridCtrlList::CGridCtrlList()
{
	m_iRowHeightAdd = 0;	// �и��Ӹ߶�
}

CGridCtrlList::~CGridCtrlList()
{
}


BEGIN_MESSAGE_MAP(CGridCtrlList, CBCGPGridCtrl)
	ON_WM_LBUTTONDBLCLK()
	ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()

// CGridCtrlList ��Ϣ�������

void CGridCtrlList::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	CWnd* pWnd = GetParent();
	pWnd->SendMessage(WM_COMMAND, MAKEWPARAM(IDC_GRID_LIST_DBLCLK, BN_CLICKED));

	CBCGPGridCtrl::OnLButtonDblClk(nFlags, point);
}

void CGridCtrlList::OnLButtonDown(UINT nFlags, CPoint point)
{
	CWnd* pWnd = GetParent();
	pWnd->PostMessage(WM_COMMAND, MAKEWPARAM(IDC_GRID_LIST_LBBUTTONDOWN, BN_CLICKED));

	CBCGPGridCtrl::OnLButtonDown(nFlags, point);
}

void CGridCtrlList::SetRowHeight()
{
	CBCGPGridCtrl::SetRowHeight();

	m_nRowHeight = m_nRowHeight + m_iRowHeightAdd;
	m_nLargeRowHeight = m_nRowHeight;
}