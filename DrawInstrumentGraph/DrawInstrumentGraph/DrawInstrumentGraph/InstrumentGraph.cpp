// InstrumentGraph.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "DrawInstrumentGraph.h"
#include "InstrumentGraph.h"

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
// ��ʼ��������ʱX������
#define GraphPosX				100
// ��ʼ��������ʱY������
#define GraphPosY				100
// ��������
// ��������-�ɼ�վ
#define InstrumentTypeFDU				3
// ��������-��Դվ
#define InstrumentTypeLAUL			2 
// ��������-����վ
#define InstrumentTypeLAUX			1

// CInstrumentGraph

IMPLEMENT_DYNAMIC(CInstrumentGraph, CWnd)

CInstrumentGraph::CInstrumentGraph()
{
	m_brushBack.CreateSolidBrush(GraphBkColor) ;
	m_iPosX = GraphPosX;
	m_iPosY = GraphPosY;
	// protected bitmaps to restore the memory DC's
	m_pbitmapOldGrid = NULL ;
	m_oInstrumentGraphRectList.RemoveAll();
	m_oRectMove = 0;
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
	OnDrawInstrumentGraph();
	return 0;
}

// ��������ͼ��
void CInstrumentGraph::OnDrawInstrumentGraph(void)
{
	CClientDC dc(this) ;  
	// �����û�л�ͼDC����Ϊ������һ���ڴ�DC
	if (m_dcGraph.GetSafeHdc() == NULL)
	{
		m_dcGraph.CreateCompatibleDC(&dc) ;
		m_bitmapGrid.CreateCompatibleBitmap(&dc, m_rectClient.Width(), m_rectClient.Height()) ;
		m_pbitmapOldGrid = m_dcGraph.SelectObject(&m_bitmapGrid) ;
	}

	m_dcGraph.SetBkColor (GraphBkColor) ;
	// ��䱳����ɫ
	m_dcGraph.FillRect(m_rectClient, &m_brushBack) ;
	// ���������豸ͼ
	DrawUnitAll(&m_dcGraph, GraphGridInstrumentSizeX, GraphGridInstrumentSizeY, GraphGridLineSizeX, GraphGridLineSizeY);
	// ˢ�¿ͻ�������
	InvalidateRect(m_rectClient) ;
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
	memBitmap.CreateCompatibleBitmap(&dc, m_rectClient.Width(), m_rectClient.Height()) ;
	oldBitmap = (CBitmap *)memDC.SelectObject(&memBitmap) ;

	if (memDC.GetSafeHdc() != NULL)
	{
		// first drop the grid on the memory dc
		memDC.BitBlt(0, 0, m_rectClient.Width(), m_rectClient.Height(), 
			&m_dcGraph, 0, 0, SRCCOPY) ;
		// finally send the result to the display
		dc.BitBlt(0, 0, m_rectClient.Width(), m_rectClient.Height(), 
			&memDC, 0, 0, SRCCOPY) ;
	}
	memDC.SelectObject(oldBitmap) ;
}

// ������������
// pDC	CDCָ��
// uiGridX	��Ԫ��X�᷽���С
// uiGridY	��Ԫ��Y�᷽���С
void CInstrumentGraph::DrawUnitAll(CDC* pDC, unsigned int uiGridX, unsigned int uiGridY, unsigned int uiGridLineX, unsigned int uiGridLineY)
{
	int iUnitIndex = 0;
	int iLineNum = 0;
	unsigned int uiLineDirection = 0;
	unsigned int uiType = InstrumentTypeLAUX;
	DrawUnit(pDC, uiGridX, uiGridY, uiGridLineX, uiGridLineY, iUnitIndex, iLineNum, uiLineDirection, uiType);
	uiType = InstrumentTypeFDU;
	iUnitIndex = 1;
	uiLineDirection = 4;
	DrawUnit(pDC, uiGridX, uiGridY, uiGridLineX, uiGridLineY, iUnitIndex, iLineNum, uiLineDirection, uiType);
	iUnitIndex = 2;
	uiLineDirection = 4;
	DrawUnit(pDC, uiGridX, uiGridY, uiGridLineX, uiGridLineY, iUnitIndex, iLineNum, uiLineDirection, uiType);
	iUnitIndex = -1;
	uiLineDirection = 3;
	DrawUnit(pDC, uiGridX, uiGridY, uiGridLineX, uiGridLineY, iUnitIndex, iLineNum, uiLineDirection, uiType);
	iUnitIndex = -2;
	uiLineDirection = 3;
	DrawUnit(pDC, uiGridX, uiGridY, uiGridLineX, uiGridLineY, iUnitIndex, iLineNum, uiLineDirection, uiType);

	iLineNum = 1;
// 	iUnitIndex = 0;
// 	uiLineDirection = 0;
// 	DrawUnit(pDC, uiGridX, uiGridY, uiGridLineX, uiGridLineY, iUnitIndex, uiLineNum, uiLineDirection, uiType);
	iUnitIndex = 1;
	uiLineDirection = 4;
	DrawUnit(pDC, uiGridX, uiGridY, uiGridLineX, uiGridLineY, iUnitIndex, iLineNum, uiLineDirection, uiType);
	iUnitIndex = 2;
	uiLineDirection = 4;
	DrawUnit(pDC, uiGridX, uiGridY, uiGridLineX, uiGridLineY, iUnitIndex, iLineNum, uiLineDirection, uiType);
	iUnitIndex = -3;
	uiLineDirection = 4;
	DrawUnit(pDC, uiGridX, uiGridY, uiGridLineX, uiGridLineY, iUnitIndex, iLineNum, uiLineDirection, uiType);
	iLineNum = -1;
	iUnitIndex = -3;
	uiLineDirection = 4;
	DrawUnit(pDC, uiGridX, uiGridY, uiGridLineX, uiGridLineY, iUnitIndex, iLineNum, uiLineDirection, uiType);
	iLineNum = 1;
	uiLineDirection = 2;
	iUnitIndex = 0;
	DrawUnit(pDC, uiGridX, uiGridY, uiGridLineX, uiGridLineY, iUnitIndex, iLineNum, uiLineDirection, uiType);
	iLineNum = -1;
	uiLineDirection = 1;
	iUnitIndex = 0;
	DrawUnit(pDC, uiGridX, uiGridY, uiGridLineX, uiGridLineY, iUnitIndex, iLineNum, uiLineDirection, uiType);
	iLineNum = -2;
	uiLineDirection = 1;
	iUnitIndex = 0;
	DrawUnit(pDC, uiGridX, uiGridY, uiGridLineX, uiGridLineY, iUnitIndex, iLineNum, uiLineDirection, uiType);
	iLineNum = 2;
	uiLineDirection = 2;
	iUnitIndex = 0;
	DrawUnit(pDC, uiGridX, uiGridY, uiGridLineX, uiGridLineY, iUnitIndex, iLineNum, uiLineDirection, uiType);
}

// ����������Ԫ�����������ߣ�
// pDC								CDCָ��
// uiGridX						��Ԫ��X�᷽���С
// uiGridY						��Ԫ��Y�᷽���С
// uiUnitIndex					��������ͼԪ���
// uiLineNum					���ߺ�
// uiLineDirection			�����߷���1Ϊ�ϣ�2Ϊ�£�3Ϊ��4Ϊ�ң���������Ϊ0
// ������ͼԪ�ߴ������ͼԪ�ߴ����
// uiType							��������
void CInstrumentGraph::DrawUnit(CDC* pDC, unsigned int uiGridX, unsigned int uiGridY, unsigned int uiGridLineX, unsigned int uiGridLineY, 
								int iUnitIndex, int iLineNum, unsigned int uiLineDirection, unsigned int uiType)
{
	CPen oPenUnit;
	CPen* pOldPen;
	CDC m_MemDc;			//����һ��DC
	CBitmap m_BkBmp;		//����һ��λͼ����
	BITMAP m_BmpInfo;	//����һ��λͼ��Ϣ�ṹ��
	CRect oRectLine;
	CRect oRectInstrument;

	oPenUnit.CreatePen(PS_SOLID, 2, GraphLineColor);
	pOldPen = pDC->SelectObject(&oPenUnit);
	if ((uiLineDirection == 1) || (uiLineDirection == 2))
	{
		oRectLine.left = m_iPosX + iUnitIndex * (uiGridX + uiGridLineX);
		oRectLine.right = oRectLine.left + uiGridX;
		oRectInstrument.left = oRectLine.left;
		oRectInstrument.right = oRectLine.right;
		if (uiLineDirection == 1)
		{
			oRectLine.top = m_iPosY + iLineNum * (uiGridY + uiGridLineY) + uiGridY;
		}
		else
		{
			oRectLine.top = m_iPosY + iLineNum * (uiGridY + uiGridLineY) - uiGridLineY;
		}
		oRectLine.bottom = oRectLine.top + uiGridLineY;
		oRectInstrument.top = m_iPosY + iLineNum * (uiGridY + uiGridLineY);
		oRectInstrument.bottom = oRectInstrument.top + uiGridY;
		pDC->MoveTo(CPoint((oRectLine.left + oRectLine.right) / 2, oRectLine.top));
		pDC->LineTo(CPoint((oRectLine.left + oRectLine.right) / 2, oRectLine.bottom));
	}
	else if ((uiLineDirection == 3) || (uiLineDirection == 4))
	{
		// �����߻�������
		if (uiLineDirection == 3)
		{
			oRectLine.left = m_iPosX + iUnitIndex * (uiGridX + uiGridLineX) + uiGridX;
		}
		else
		{
			oRectLine.left = m_iPosX + iUnitIndex * (uiGridX + uiGridLineX) - uiGridLineX;
		}
		oRectLine.right = oRectLine.left + uiGridLineX;
		oRectInstrument.left = m_iPosX + iUnitIndex * (uiGridX + uiGridLineX);
		oRectInstrument.right = oRectInstrument.left + uiGridX;
		oRectLine.top = m_iPosY + iLineNum * (uiGridY + uiGridLineY);
		oRectLine.bottom = oRectLine.top + uiGridY;
		oRectInstrument.top = oRectLine.top;
		oRectInstrument.bottom = oRectLine.bottom;
		pDC->MoveTo(CPoint(oRectLine.left, (oRectLine.top + oRectLine.bottom) / 2));
		pDC->LineTo(CPoint(oRectLine.right, (oRectLine.top + oRectLine.bottom) / 2));
	}
	else
	{
		// ������վ����Ҫ��������iUnitIndex = 0
		oRectInstrument.left = m_iPosX;
		oRectInstrument.right = oRectLine.left + uiGridX;
		oRectInstrument.top = m_iPosY;
		oRectInstrument.bottom = oRectLine.top + uiGridY;
	}
	if (uiType == InstrumentTypeFDU)
	{
		m_BkBmp.LoadBitmap(IDB_BITMAP_FDU2);	// �˴�Ϊ�ո���ӽ�����λͼ��ԴID
	}
	else if (uiType == InstrumentTypeLAUX)
	{
		m_BkBmp.LoadBitmap(IDB_BITMAP_LAUX2);
	}
	m_BkBmp.GetBitmap(&m_BmpInfo);				// ��ȡλͼ�߿����Ϣ��������λͼ�ṹ����
	m_MemDc.CreateCompatibleDC(pDC);			// ����һ��������ĻDC���ڴ�DC��m_MemDc��
	m_MemDc.SelectObject(&m_BkBmp);				// ����λͼѡ�񵽸մ������ڴ�DC�С�

	/*���ڴ�DC��Ķ���������ĻDC��ȥ*/
	pDC->BitBlt(oRectInstrument.left,oRectInstrument.top,m_BmpInfo.bmWidth,m_BmpInfo.bmHeight,&m_MemDc,0,0,SRCCOPY);
	pDC->SelectObject(pOldPen);
	m_oInstrumentGraph oInstrumentGraph;
	oInstrumentGraph.oRect = oRectInstrument;
	oInstrumentGraph.iUnitIndex = iUnitIndex;
	oInstrumentGraph.iLineNum = iLineNum;
	m_oInstrumentGraphRectList.AddTail(oInstrumentGraph);
}

void CInstrumentGraph::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	CString str;
	CRect oRect;
	POSITION pos = m_oInstrumentGraphRectList.GetHeadPosition();
	m_oInstrumentGraph oInstrumentGraph;
	if ((m_oRectMove.left <= point.x) && (m_oRectMove.right >= point.x)
		&&(m_oRectMove.top <= point.y) && (m_oRectMove.bottom >= point.y))
	{
	}
	else
	{
		for (int i=0; i<m_oInstrumentGraphRectList.GetCount(); i++)
		{
			oInstrumentGraph = m_oInstrumentGraphRectList.GetNext(pos);
			oRect = oInstrumentGraph.oRect;
			if ((oRect.left <= point.x) && (oRect.right >= point.x)
				&&(oRect.top <= point.y) && (oRect.bottom >= point.y))
			{
				m_dcGraph.SetTextAlign (TA_LEFT|TA_TOP) ;
				str.Format(_T("�ߺ� = %d ��� = %d"), oInstrumentGraph.iLineNum, oInstrumentGraph.iUnitIndex);
				m_dcGraph.TextOut (point.x, point.y, str) ;
				InvalidateRect( m_rectClient, FALSE );
				m_oRectMove = oInstrumentGraph.oRect;
				break;
			}
		}
	}

	CWnd::OnMouseMove(nFlags, point);
}
