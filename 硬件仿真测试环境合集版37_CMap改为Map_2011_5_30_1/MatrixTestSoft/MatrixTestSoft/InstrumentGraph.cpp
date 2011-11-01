// InstrumentGraph.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "TabSample.h"
#include "InstrumentGraph.h"
#include "Parameter.h"
// ��ͼ������ɫ
#define GraphBkColor		RGB(  255,   255,   255)
// ��ͼ������ɫ
#define GraphLineColor		RGB(	0,	0,	255	)
// ������ͼ��ԪX��ߴ�
#define GraphGridInstrumentSizeX		16
// ������ͼ��ԪY��ߴ�
#define GraphGridInstrumentSizeY		16
// �����߻�ͼ��ԪX��ߴ�
#define GraphGridLineSizeX					10
// �����߻�ͼ��ԪY��ߴ�
#define GraphGridLineSizeY					10


// CInstrumentGraph

IMPLEMENT_DYNAMIC(CInstrumentGraph, CWnd)

CInstrumentGraph::CInstrumentGraph()
{
	m_brushBack.CreateSolidBrush(GraphBkColor) ;
	// protected bitmaps to restore the memory DC's
	m_pbitmapOldGrid = NULL ;
	m_oInstrumentGraphRectList.RemoveAll();
	m_uiGridX = GraphGridInstrumentSizeX;
	m_uiGridY = GraphGridInstrumentSizeY;
	m_uiGridLineX = GraphGridLineSizeX;
	m_uiGridLineY = GraphGridLineSizeY;
	m_iPosShowInterval = 30;
	m_iVScrBarInterval = 20;
	m_iHScrBarInterval = 20;
	m_iLauxPosX = 20;
	m_iLauxPosY = 100;
	m_pWndVScr = NULL;
	m_pWndHScr = NULL;
}

CInstrumentGraph::~CInstrumentGraph()
{
	if (m_pbitmapOldGrid != NULL)
		m_dcGraph.SelectObject(m_pbitmapOldGrid) ; 
	m_oInstrumentGraphRectList.RemoveAll();
}


BEGIN_MESSAGE_MAP(CInstrumentGraph, CWnd)
	ON_WM_CREATE()
	ON_WM_PAINT()
	ON_WM_MOUSEMOVE()
	ON_WM_HSCROLL()
	ON_WM_VSCROLL()
END_MESSAGE_MAP()



// CInstrumentGraph ��Ϣ�������

int CInstrumentGraph::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	m_rectClient.left = 0;
	m_rectClient.right = lpCreateStruct->cx;
	m_rectClient.top = 0;
	m_rectClient.bottom = lpCreateStruct->cy;
	m_rectGraph.left = 0;
	m_rectGraph.right = m_rectClient.right - m_iVScrBarInterval;
	m_rectGraph.top = 0;
	m_rectGraph.bottom = m_rectClient.bottom - m_iHScrBarInterval;
	m_rectSave = m_rectGraph;
	CClientDC dc(this) ;  
	// �����û�л�ͼDC����Ϊ������һ���ڴ�DC
	if (m_dcGraph.GetSafeHdc() == NULL)
	{
		m_dcGraph.CreateCompatibleDC(&dc) ;
		m_bitmapGrid.CreateCompatibleBitmap(&dc, m_rectClient.Width(), m_rectClient.Height()) ;
		m_pbitmapOldGrid = m_dcGraph.SelectObject(&m_bitmapGrid) ;
	}

	m_dcGraph.SetBkColor (GraphBkColor) ;
	OnFillBkColor();
	// ˢ�¿ͻ�������
	InvalidateRect(m_rectClient) ;
	static HWND childhwnd1=CreateWindow(TEXT("scrollbar"),NULL,WS_CHILD|WS_VISIBLE|SBS_VERT,
		m_rectClient.right - m_iVScrBarInterval,m_rectClient.top,m_iVScrBarInterval,m_rectClient.bottom,
		this->m_hWnd,(HMENU)1,(HINSTANCE)GetWindowLong(this->m_hWnd,GWL_HINSTANCE),NULL);
	static HWND childhwnd2=CreateWindow(TEXT("scrollbar"),NULL,WS_CHILD|WS_VISIBLE|SBS_HORZ,
		m_rectClient.left,m_rectClient.bottom - m_iHScrBarInterval,m_rectClient.right - m_iVScrBarInterval,m_iHScrBarInterval,
		this->m_hWnd,(HMENU)1,(HINSTANCE)GetWindowLong(this->m_hWnd,GWL_HINSTANCE),NULL);
	m_pWndVScr = FromHandle(childhwnd1);
	m_pWndVScr->EnableWindow(FALSE);
//	m_pWndVScr->SetScrollRange(SB_CTL, 0,10000,FALSE);
// 	m_pWndVScr->SetScrollPos(SB_CTL,60,FALSE);

	m_pWndHScr = FromHandle(childhwnd2);
	m_pWndHScr->EnableWindow(FALSE);
//	pwnd2->SetScrollRange(SB_CTL, 0,0,FALSE);
//	pwnd2->SetScrollPos(SB_CTL,60,FALSE);

	return 0;
}


void CInstrumentGraph::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: �ڴ˴������Ϣ����������
	// ��Ϊ��ͼ��Ϣ���� CWnd::OnPaint()
	CDC memDC ;
	CBitmap memBitmap ;
	CBitmap* oldBitmap ; // bitmap originally found in CMemDC

	// no real plotting work is performed here, 
	// just putting the existing bitmaps on the client

	// to avoid flicker, establish a memory dc, draw to it 
	// and then BitBlt it to the client
	memDC.CreateCompatibleDC(&dc) ;
	memBitmap.CreateCompatibleBitmap(&dc, m_rectGraph.Width(), m_rectGraph.Height()) ;
	oldBitmap = (CBitmap *)memDC.SelectObject(&memBitmap) ;

	if (memDC.GetSafeHdc() != NULL)
	{
		// first drop the grid on the memory dc
		memDC.BitBlt(0, 0, m_rectGraph.Width(), m_rectGraph.Height(), 
			&m_dcGraph, 0, 0, SRCCOPY) ;
		// finally send the result to the display
		dc.BitBlt(0, 0, m_rectGraph.Width(), m_rectGraph.Height(), 
			&memDC, 0, 0, SRCCOPY) ;
	}
	memDC.SelectObject(oldBitmap) ;
}

// ������������
// pDC	CDCָ��
// uiGridX	��Ԫ��X�᷽���С
// uiGridY	��Ԫ��Y�᷽���С
void CInstrumentGraph::DrawUnitAll(void)
{
	POSITION pos = m_oInstrumentGraphRectList.GetHeadPosition();
	m_oInstrumentGraph oInstrumentGraph;
	// ��ʾ�������ߺź͵��
	for (int i=0; i<m_oInstrumentGraphRectList.GetCount(); i++)
	{
		oInstrumentGraph = m_oInstrumentGraphRectList.GetNext(pos);
		DrawUnit(oInstrumentGraph.iUnitIndex, oInstrumentGraph.iLineIndex, oInstrumentGraph.uiLineDirection, 
			oInstrumentGraph.uiType, oInstrumentGraph.uiSN, oInstrumentGraph.uiOpt, false);
	}
}
// ����������Ԫ�����������ߣ�
// pDC								CDCָ��
// uiGridX						��Ԫ��X�᷽���С
// uiGridY						��Ԫ��Y�᷽���С
// uiUnitIndex					��������ͼԪ���
// uiLineNum					���ߺ�
// uiLineDirection			�����߷���1Ϊ�ϣ�2Ϊ�£�3Ϊ��4Ϊ�ң���������Ϊ0
// uiType							��������
void CInstrumentGraph::DrawUnit(int iUnitIndex, int iLineIndex, unsigned int uiLineDirection, unsigned int uiType, unsigned int uiSN, unsigned int uiOpt, bool bSet)
{
	CPen oPenUnit;
	CPen* pOldPen;
	CDC m_MemDc;			//����һ��DC
	CBitmap m_BkBmp;		//����һ��λͼ����
	BITMAP m_BmpInfo;	//����һ��λͼ��Ϣ�ṹ��
	CRect oRectLine;
	CRect oRectInstrument;
	if (uiOpt == GraphInstrumentOffLine)
	{
		oPenUnit.CreatePen(PS_SOLID, 2, GraphBkColor);
	} 
	else
	{
		oPenUnit.CreatePen(PS_SOLID, 2, GraphLineColor);
	}
	pOldPen = m_dcGraph.SelectObject(&oPenUnit);
	if ((uiLineDirection == 1) || (uiLineDirection == 2))
	{
		oRectLine.left = m_iLauxPosX + iUnitIndex * (m_uiGridX + m_uiGridLineX);
		oRectLine.right = oRectLine.left + m_uiGridX;
		oRectInstrument.left = oRectLine.left;
		oRectInstrument.right = oRectLine.right;
		if (uiLineDirection == 1)
		{
			oRectLine.top = m_iLauxPosY + iLineIndex * (m_uiGridY + m_uiGridLineY) + m_uiGridY;
		}
		else
		{
			oRectLine.top = m_iLauxPosY + iLineIndex * (m_uiGridY + m_uiGridLineY) - m_uiGridLineY;
		}
		oRectLine.bottom = oRectLine.top + m_uiGridLineY;
		oRectInstrument.top = m_iLauxPosY + iLineIndex * (m_uiGridY + m_uiGridLineY);
		oRectInstrument.bottom = oRectInstrument.top + m_uiGridY;
		// ������������
		if (uiLineDirection == 1)
		{

		}
		// ������������
		else
		{

		}
		m_dcGraph.MoveTo(CPoint((oRectLine.left + oRectLine.right) / 2, oRectLine.top));
		m_dcGraph.LineTo(CPoint((oRectLine.left + oRectLine.right) / 2, oRectLine.bottom));
	}
	else if ((uiLineDirection == 3) || (uiLineDirection == 4))
	{
		// �����߻�������
		if (uiLineDirection == 3)
		{
			oRectLine.left = m_iLauxPosX + iUnitIndex * (m_uiGridX + m_uiGridLineX) + m_uiGridX;
		}
		else
		{
			oRectLine.left = m_iLauxPosX + iUnitIndex * (m_uiGridX + m_uiGridLineX) - m_uiGridLineX;
		}
		oRectLine.right = oRectLine.left + m_uiGridLineX;
		oRectInstrument.left = m_iLauxPosX + iUnitIndex * (m_uiGridX + m_uiGridLineX);
		oRectInstrument.right = oRectInstrument.left + m_uiGridX;
		oRectLine.top = m_iLauxPosY + iLineIndex * (m_uiGridY + m_uiGridLineY);
		oRectLine.bottom = oRectLine.top + m_uiGridY;
		oRectInstrument.top = oRectLine.top;
		oRectInstrument.bottom = oRectLine.bottom;
		// ������������
		if (uiLineDirection == 3)
		{

		}
		// ������������
		else
		{
			
		}

		m_dcGraph.MoveTo(CPoint(oRectLine.left, (oRectLine.top + oRectLine.bottom) / 2));
		m_dcGraph.LineTo(CPoint(oRectLine.right, (oRectLine.top + oRectLine.bottom) / 2));
	}
	else
	{
		// ������վ����Ҫ��������iUnitIndex = 0
		oRectInstrument.left = m_iLauxPosX;
		oRectInstrument.right = oRectInstrument.left + m_uiGridX;
		oRectInstrument.top = m_iLauxPosY;
		oRectInstrument.bottom = oRectInstrument.top + m_uiGridY;
	}
	switch (uiOpt)
	{
	case GraphInstrumentOnLine:
		if (uiType == InstrumentTypeFDU)
		{
			m_BkBmp.LoadBitmap(IDB_BITMAP_FDU1);
		} 
		else if (uiType == InstrumentTypeLAUL)
		{
			m_BkBmp.LoadBitmap(IDB_BITMAP_LAUL1);
		}
		else if (uiType == InstrumentTypeLAUX)
		{
			m_BkBmp.LoadBitmap(IDB_BITMAP_LAUX1);
		}
		break;
	case GraphInstrumentIPSet:
		if (uiType == InstrumentTypeFDU)
		{
			m_BkBmp.LoadBitmap(IDB_BITMAP_FDU2);
		} 
		else if (uiType == InstrumentTypeLAUL)
		{
			m_BkBmp.LoadBitmap(IDB_BITMAP_LAUL2);
		}
		else if (uiType == InstrumentTypeLAUX)
		{
			m_BkBmp.LoadBitmap(IDB_BITMAP_LAUX2);
		}
		break;
	case GraphInstrumentOffLine:
		// ��䱳����ɫ
		m_dcGraph.FillRect(oRectInstrument, &m_brushBack) ;
		break;
	default:
		break;
	}
	if ((uiOpt == GraphInstrumentOnLine) || (uiOpt == GraphInstrumentIPSet))
	{
		m_BkBmp.GetBitmap(&m_BmpInfo);				// ��ȡλͼ�߿����Ϣ��������λͼ�ṹ����
		m_MemDc.CreateCompatibleDC(&m_dcGraph);			// ����һ��������ĻDC���ڴ�DC��m_MemDc��
		m_MemDc.SelectObject(&m_BkBmp);				// ����λͼѡ�񵽸մ������ڴ�DC�С�

		/*���ڴ�DC��Ķ���������ĻDC��ȥ*/
		m_dcGraph.BitBlt(oRectInstrument.left,oRectInstrument.top,m_BmpInfo.bmWidth,m_BmpInfo.bmHeight,&m_MemDc,0,0,SRCCOPY);
	}
	m_dcGraph.SelectObject(pOldPen);
	if (bSet == true)
	{
		m_oInstrumentGraph oInstrumentGraph;
		oInstrumentGraph.oRect = oRectInstrument;
		oInstrumentGraph.iUnitIndex = iUnitIndex;
		oInstrumentGraph.iLineIndex = iLineIndex;
		oInstrumentGraph.uiType = uiType;
		oInstrumentGraph.uiLineDirection = uiLineDirection;
		oInstrumentGraph.uiSN = uiSN;
		oInstrumentGraph.uiOpt = uiOpt;
		if (uiOpt == GraphInstrumentOnLine)
		{
			if (NULL == m_oInstrumentGraphRectList.Find(oInstrumentGraph))
			{
				m_oInstrumentGraphRectList.AddTail(oInstrumentGraph);
			}
		}
		else if (uiOpt == GraphInstrumentIPSet)
		{
			POSITION pos = m_oInstrumentGraphRectList.Find(oInstrumentGraph);
			oInstrumentGraph = m_oInstrumentGraphRectList.GetAt(pos);
			oInstrumentGraph.uiOpt = GraphInstrumentIPSet;
			m_oInstrumentGraphRectList.SetAt(pos, oInstrumentGraph);
		}
		else if (uiOpt == GraphInstrumentOffLine)
		{
			m_oInstrumentGraphRectList.RemoveAt(m_oInstrumentGraphRectList.Find(oInstrumentGraph));
		}
	}
	InvalidateRect(oRectInstrument);
	InvalidateRect(oRectLine);
}

void CInstrumentGraph::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	OnShowInstrumentAxisPoint(point);
	CWnd::OnMouseMove(nFlags, point);
}

// ��ʾ�������꣨�������ߺź͵�ţ�
void CInstrumentGraph::OnShowInstrumentAxisPoint(CPoint point)
{
	CString str = _T("");
	CRect oRect = 0;
	POSITION pos = m_oInstrumentGraphRectList.GetHeadPosition();
	m_oInstrumentGraph oInstrumentGraph;
	m_dcGraph.SetTextAlign (TA_LEFT|TA_TOP) ;
	// ��ʾ�������ߺź͵��
	for (int i=0; i<m_oInstrumentGraphRectList.GetCount(); i++)
	{
		oInstrumentGraph = m_oInstrumentGraphRectList.GetNext(pos);
		oRect = oInstrumentGraph.oRect;
		if ((oRect.left <= point.x) && (oRect.right >= point.x)
			&&(oRect.top <= point.y) && (oRect.bottom >= point.y))
		{
			str.Format(_T("�ߺ� = %d    ��� = %d    SN = 0x%04x    "), oInstrumentGraph.iLineIndex, oInstrumentGraph.iUnitIndex, oInstrumentGraph.uiSN);
			m_dcGraph.TextOut (m_rectClient.left, m_rectClient.bottom - m_iPosShowInterval - m_iHScrBarInterval, str) ;
 			InvalidateRect( m_rectClient, FALSE );
			return;
		}
	}
	str.Format(_T("                                                                                                     "));
	m_dcGraph.TextOut (m_rectClient.left, m_rectClient.bottom - m_iPosShowInterval - m_iHScrBarInterval, str) ;
	InvalidateRect( m_rectClient, FALSE );
}

// ��䱳����ɫ
void CInstrumentGraph::OnFillBkColor(void)
{
	// ��䱳����ɫ
	m_dcGraph.FillRect(m_rectClient, &m_brushBack) ;
}

// �����������ͼ��
void CInstrumentGraph::OnClearAllInstrumentGraph(void)
{
	OnFillBkColor();
	m_oInstrumentGraphRectList.RemoveAll();
	// ˢ�¿ͻ�������
	InvalidateRect(m_rectClient) ;
}
void CInstrumentGraph::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	int newPos = moveScrollBar(nSBCode, nPos, pScrollBar);
}
void CInstrumentGraph::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	int newPos = moveScrollBar(nSBCode, nPos, pScrollBar);
}
int CInstrumentGraph::moveScrollBar(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	//
	// Get current scroll bar position
	//
	SCROLLINFO info;
	info.cbSize = sizeof(SCROLLINFO);
	info.fMask = SIF_ALL;
	pScrollBar->GetScrollInfo(&info);

	//
	// Compute new position based on the type of scroll bar events
	//
	int newPos = info.nPos;
	switch (nSBCode)
	{
	case SB_LEFT:
		newPos = info.nMin;
		break;
	case SB_RIGHT:
		newPos = info.nMax;
		break;
	case SB_LINELEFT:
		newPos -= 10;
		break;
	case SB_LINERIGHT:
		newPos += 10;
		break;
	case SB_PAGELEFT:
		newPos -= 30;
		break;
	case SB_PAGERIGHT:
		newPos += 30;
		break;
	case SB_THUMBTRACK:
		newPos = info.nTrackPos;
		break;
	}
	if (newPos < info.nMin) newPos = info.nMin;
	if (newPos > info.nMax) newPos = info.nMax;

	// Update the scroll bar with the new position
	pScrollBar->SetScrollPos(newPos);

	// Returns the position of the scroll bar as a ratio of its total length
	return newPos;
}