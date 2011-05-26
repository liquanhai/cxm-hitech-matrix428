// LeftViewBar.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "BCGPVisualStudioGUIDemo.h"
#include "LeftViewBarInstrumentBottom.h"

IMPLEMENT_DYNAMIC(CLeftViewBarInstrumentBottom, CBCGPDockingControlBar)

CLeftViewBarInstrumentBottom::CLeftViewBarInstrumentBottom()
{

}

CLeftViewBarInstrumentBottom::~CLeftViewBarInstrumentBottom()
{
}


BEGIN_MESSAGE_MAP(CLeftViewBarInstrumentBottom, CBCGPDockingControlBar)
	//{{AFX_MSG_MAP(CLeftViewBarInstrumentBottom)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_CONTEXTMENU()
	ON_WM_PAINT()
	ON_WM_SETFOCUS()
	//}}AFX_MSG_MAP
	ON_WM_HSCROLL()
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CLeftViewBarInstrumentBottom message handlers

int CLeftViewBarInstrumentBottom::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CBCGPDockingControlBar::OnCreate(lpCreateStruct) == -1)
		return -1;
	RemoveCaptionButtons();

	// �õ��ֳ����ݺͲ�����������
	CMainFrame* pMainFrame = NULL;
	pMainFrame = (CMainFrame*)AfxGetMainWnd();
	m_pSiteData = &pMainFrame->m_oSiteData;

	CRect oRect;
	oRect.SetRectEmpty();

	// �������Ա�
	m_wndPropList.Create (WS_CHILD, oRect, this, 1);
	SetPropListFont();
	InitPropList();

	// �����ػص�ͼ����ͼ
	BOOL bData = m_wndDetourGraphView.Create("DetourGraphView", WS_CHILD, oRect, this, 2);
	// �����ػص�ͼ����ͼ������*/
	m_wndDetourScrollBar.Create (WS_CHILD | SBS_HORZ, oRect, this, 3);
	return 0;
}

void CLeftViewBarInstrumentBottom::OnSize(UINT nType, int cx, int cy) 
{
	CBCGPDockingControlBar::OnSize(nType, cx, cy);
	if (CanAdjustLayout())
	{
		CRect rc;
		GetClientRect(rc);
		m_wndPropList.SetWindowPos(NULL, rc.left, rc.top, rc.Width(), rc.Height(), SWP_NOACTIVATE | SWP_NOZORDER);		

		int iWidth = (m_wndDetourGraphView.m_uiInstrumentCountAll + 1) * m_wndDetourGraphView.m_iGridX;
		if(iWidth <= rc.Width())
		{
			m_wndDetourGraphView.SetWindowPos(NULL, rc.left, rc.top, rc.Width(), rc.Height() - 20, SWP_NOACTIVATE | SWP_NOZORDER);
			m_wndDetourScrollBar.SetWindowPos(NULL, rc.left, rc.top + rc.Height() - 20, rc.Width(), 20, SWP_NOACTIVATE | SWP_NOZORDER);
			m_wndDetourScrollBar.SetScrollRange(0, 0, TRUE);
			m_wndDetourScrollBar.SetScrollPos(0, TRUE);
		}
		else
		{
			m_wndDetourGraphView.SetWindowPos(NULL, rc.left, rc.top, iWidth, rc.Height() - 20, SWP_NOACTIVATE | SWP_NOZORDER);
			m_wndDetourScrollBar.SetWindowPos(NULL, rc.left, rc.top + rc.Height() - 20, rc.Width(), 20, SWP_NOACTIVATE | SWP_NOZORDER);
			m_wndDetourScrollBar.SetScrollRange(0, iWidth - rc.Width(), TRUE);
			m_wndDetourScrollBar.SetScrollPos(0, TRUE);
		}
	}
}

void CLeftViewBarInstrumentBottom::OnContextMenu(CWnd* pWnd, CPoint point) 
{

}

void CLeftViewBarInstrumentBottom::OnPaint() 
{
	CPaintDC dc(this); // device context for painting

	CRect oRect;
	GetClientRect(&oRect);

	CBrush oBrush;
	CBrush* pOldPenBrush;

	oBrush.CreateSolidBrush(RGB(255, 255, 255));
	pOldPenBrush = dc.SelectObject(&oBrush);
	dc.FillRect(&oRect, &oBrush);

	dc.SelectObject(pOldPenBrush);
}

void CLeftViewBarInstrumentBottom::OnSetFocus(CWnd* pOldWnd) 
{
	CBCGPDockingControlBar::OnSetFocus(pOldWnd);
}

void CLeftViewBarInstrumentBottom::SetPropListFont()
{
	::DeleteObject (m_fntPropList.Detach ());

	LOGFONT lf;
	globalData.fontRegular.GetLogFont (&lf);

	NONCLIENTMETRICS info;
	info.cbSize = sizeof(info);

	globalData.GetNonClientMetrics (info);

	lf.lfHeight = info.lfMenuFont.lfHeight;
	lf.lfWeight = info.lfMenuFont.lfWeight;
	lf.lfItalic = info.lfMenuFont.lfItalic;

	m_fntPropList.CreateFontIndirect (&lf);

	m_wndPropList.SetFont (&m_fntPropList);
}

void CLeftViewBarInstrumentBottom::InitPropList()
{
	m_wndPropList.EnableHeaderCtrl (FALSE);
	m_wndPropList.SetVSDotNetLook ();
	m_wndPropList.MarkModifiedProperties ();

	COleVariant oVariant = "";
	CBCGPProp* pGroupBase = new CBCGPProp (_T("Base"));
	pGroupBase->AddSubItem (new CBCGPProp (_T("Serial Nb"), oVariant, _T("")));
	pGroupBase->AddSubItem (new CBCGPProp (_T("Type"), oVariant, _T("")));
	pGroupBase->AddSubItem (new CBCGPProp (_T("IP"), oVariant, _T("")));
		pGroupBase->AddSubItem (new CBCGPProp (_T("Line Nb"), oVariant, _T("")));
			pGroupBase->AddSubItem (new CBCGPProp (_T("Point Nb"), oVariant, _T("")));
				pGroupBase->AddSubItem (new CBCGPProp (_T("Channel Nb"), oVariant, _T("")));
	m_wndPropList.AddProperty (pGroupBase);

	CBCGPProp* pGroupTest = new CBCGPProp (_T("Test"));
	pGroupTest->AddSubItem (new CBCGPProp (_T("Noise"), oVariant, _T("")));
	pGroupTest->AddSubItem (new CBCGPProp (_T("Distortion"), oVariant, _T("")));
	pGroupTest->AddSubItem (new CBCGPProp (_T("Crosstalk"), oVariant, _T("")));
	pGroupTest->AddSubItem (new CBCGPProp (_T("Gain"), oVariant, _T("")));
	pGroupTest->AddSubItem (new CBCGPProp (_T("Phase"), oVariant, _T("")));
	pGroupTest->AddSubItem (new CBCGPProp (_T("CMRR"), oVariant, _T("")));

	m_wndPropList.AddProperty (pGroupTest);
}

/**
* ����
* @param void
* @return void
*/
void CLeftViewBarInstrumentBottom::OnResetBar()
{
	m_wndPropList.ShowWindow(SW_HIDE);
	m_wndDetourGraphView.ShowWindow(SW_HIDE);
	SetWindowText("");
}

/**
* ��Ӧ��ʾ����ֵ
* @param unsigned int uiIndex ����������
* @return void
*/
void CLeftViewBarInstrumentBottom::OnShowProperty(unsigned int uiIndex)
{
	m_wndDetourGraphView.ShowWindow(SW_HIDE);
	m_wndDetourScrollBar.ShowWindow(SW_HIDE);

	CInstrument* pInstrument = &m_pSiteData->m_oInstrumentList.m_pArrayInstrument[uiIndex];
	CString strData;
	COleVariant oVariant = "";
	CBCGPProp* pGroupBase = NULL;
	CBCGPProp* pGroupTest = NULL;
	CBCGPProp* pSub = NULL;

	pGroupBase = m_wndPropList.GetProperty(0);

	pSub = pGroupBase->GetSubItem(0);
	strData.Format("%d", pInstrument->m_uiSN);
	oVariant = strData;
	pSub->SetValue(oVariant);

	pSub = pGroupBase->GetSubItem(1);
	strData = m_pSiteData->GetBoxTypeStringByID(pInstrument->m_uiInstrumentType);
	oVariant = strData;
	pSub->SetValue(oVariant);

	pSub = pGroupBase->GetSubItem(2);
	strData.Format("%d", pInstrument->m_uiIP);
	oVariant = strData;
	pSub->SetValue(oVariant);

	pSub = pGroupBase->GetSubItem(3);
	strData.Format("%d", pInstrument->m_uiLineNb);
	oVariant = strData;
	pSub->SetValue(oVariant);

	pSub = pGroupBase->GetSubItem(4);
	strData.Format("%d", pInstrument->m_uiPointNb);
	oVariant = strData;
	pSub->SetValue(oVariant);

	pSub = pGroupBase->GetSubItem(5);
	strData.Format("%d", pInstrument->m_uiChannelNb);
	oVariant = strData;
	pSub->SetValue(oVariant);

	pGroupTest = m_wndPropList.GetProperty(1);

	// ������������ֵ
	pSub = pGroupTest->GetSubItem(0);
	strData = pInstrument->GetTestResultString(4, 0);
	oVariant = strData;
	pSub->SetValue(oVariant);

	// �����������ֵ
	pSub = pGroupTest->GetSubItem(1);
	strData = pInstrument->GetTestResultString(5, 0);
	oVariant = strData;
	pSub->SetValue(oVariant);

	// ������������ֵ
	pSub = pGroupTest->GetSubItem(2);
	strData = pInstrument->GetTestResultString(7, 0);
	oVariant = strData;
	pSub->SetValue(oVariant);

	// �����������ֵ
	pSub = pGroupTest->GetSubItem(3);
	strData = pInstrument->GetTestResultString(6, 0);
	oVariant = strData;
	pSub->SetValue(oVariant);

	// ������λ����ֵ
	pSub = pGroupTest->GetSubItem(4);
	strData = pInstrument->GetTestResultString(6, 1);
	oVariant = strData;
	pSub->SetValue(oVariant);

	// ������ģ����ֵ
	pSub = pGroupTest->GetSubItem(5);
	strData = pInstrument->GetTestResultString(8, 0);
	oVariant = strData;
	pSub->SetValue(oVariant);

	m_wndPropList.ShowWindow(SW_SHOW);
	SetWindowText("Instrument Properties");
}

/**
* ��Ӧ��ʾ�ػص�ͼ����ͼ
* @param unsigned int uiCount �ػص�����������
* @return void
*/
void CLeftViewBarInstrumentBottom::OnShowDetourGraphView(unsigned int uiCount)
{
	m_wndPropList.ShowWindow(SW_HIDE);

	CRect rc;
	GetClientRect(rc);
	
	int iWidth = (uiCount + 1) * m_wndDetourGraphView.m_iGridX;
	if(iWidth <= rc.Width())
	{
		m_wndDetourGraphView.SetWindowPos(NULL, rc.left, rc.top, rc.Width(), rc.Height() - 20, SWP_NOACTIVATE | SWP_NOZORDER);
		m_wndDetourScrollBar.SetScrollRange(0, 0, TRUE);
		m_wndDetourScrollBar.SetScrollPos(0, TRUE);
	}
	else
	{
		m_wndDetourGraphView.SetWindowPos(NULL, rc.left, rc.top, iWidth, rc.Height() - 20, SWP_NOACTIVATE | SWP_NOZORDER);
		m_wndDetourScrollBar.SetScrollRange(0, iWidth - rc.Width(), TRUE);
		m_wndDetourScrollBar.SetScrollPos(0, TRUE);
	}

	m_wndDetourGraphView.ShowWindow(SW_SHOW);
	m_wndDetourScrollBar.ShowWindow(SW_SHOW);
	SetWindowText("Detour Graph View");
	m_wndDetourGraphView.OnShowDetourGraphView(uiCount);
}
void CLeftViewBarInstrumentBottom::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// Get the minimum and maximum scroll-bar positions.
	int minpos;
	int maxpos;
	pScrollBar->GetScrollRange(&minpos, &maxpos); 
	maxpos = pScrollBar->GetScrollLimit();

	// Get the current position of scroll box.
	int curpos = pScrollBar->GetScrollPos();

	// Determine the new position of scroll box.
	switch (nSBCode)
	{
	case SB_LEFT:      // Scroll to far left.
		curpos = minpos;
		break;

	case SB_RIGHT:      // Scroll to far right.
		curpos = maxpos;
		break;

	case SB_ENDSCROLL:   // End scroll.
		break;

	case SB_LINELEFT:      // Scroll left.
		if (curpos > minpos)
			curpos--;
		break;

	case SB_LINERIGHT:   // Scroll right.
		if (curpos < maxpos)
			curpos++;
		break;

	case SB_PAGELEFT:    // Scroll one page left.
		{
			curpos = curpos - m_wndDetourGraphView.m_iGridX;
		}
		break;

	case SB_PAGERIGHT:      // Scroll one page right.
		{
			curpos = curpos + m_wndDetourGraphView.m_iGridX;
		}
		break;

	case SB_THUMBPOSITION: // Scroll to absolute position. nPos is the position
		curpos = nPos;      // of the scroll box at the end of the drag operation.
		break;

	case SB_THUMBTRACK:   // Drag scroll box to specified position. nPos is the
		curpos = nPos;     // position that the scroll box has been dragged to.
		break;
	}

	// Set the new position of the thumb (scroll box).
	pScrollBar->SetScrollPos(curpos, TRUE);

	CRect rc;
	GetClientRect(rc);
	int iWidth = (m_wndDetourGraphView.m_uiInstrumentCountAll + 1) * m_wndDetourGraphView.m_iGridX;
	if(iWidth > rc.Width())
	{
		m_wndDetourGraphView.SetWindowPos(NULL, rc.left - curpos, rc.top, iWidth, rc.Height() - 20, SWP_NOACTIVATE | SWP_NOZORDER);
	}

	CBCGPDockingControlBar::OnHScroll(nSBCode, nPos, pScrollBar);
}
