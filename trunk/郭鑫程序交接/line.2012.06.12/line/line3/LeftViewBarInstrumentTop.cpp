// LeftViewBar.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "line.h"
#include "LeftViewBarInstrumentTop.h"
#include "InstrumentGraphChildFrame.h"

IMPLEMENT_DYNAMIC(CLeftViewBarInstrumentTop, CBCGPDockingControlBar)

CLeftViewBarInstrumentTop::CLeftViewBarInstrumentTop()
{
	m_bMouseDownLeft = false;	// �������Ƿ���
	m_bDrawSelectArea = false;	// �Ƿ����ѡ������λ��
	m_fZoomRate = 1.0;	// �Ŵ���
	m_fRateX = 0.0;	// ��׼��X
	m_fRateY = 0.0;	// ��׼��Y	
	
	m_iGridY = 0;	// ��Ԫ��Y����ߴ�
	m_iGridYMax = 20;	// ��Ԫ��Y����ߴ����ֵ
	m_iLineHight = 0;	// ���߸߶�
	m_iPaperHeadX = 20;	// ͼ����X����Ԥ���ߴ�	
	m_iPaperHeadTop = 25;	// ͼ�������Ԥ���ߴ�
	m_bCanDrawGraph = false;	// �Ƿ���Ի�ͼ

	m_uiLineCount = 0;	//��������
}

CLeftViewBarInstrumentTop::~CLeftViewBarInstrumentTop()
{
}


BEGIN_MESSAGE_MAP(CLeftViewBarInstrumentTop, CBCGPDockingControlBar)
	//{{AFX_MSG_MAP(CLeftViewBarInstrumentTop)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CLeftViewBarInstrumentTop message handlers

int CLeftViewBarInstrumentTop::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CBCGPDockingControlBar::OnCreate(lpCreateStruct) == -1)
		return -1;
	RemoveCaptionButtons();
	return 0;
}

void CLeftViewBarInstrumentTop::OnSize(UINT nType, int cx, int cy) 
{
	CBCGPDockingControlBar::OnSize(nType, cx, cy);
	if (CanAdjustLayout ())
	{
		m_bDrawSelectArea = false;	// �Ƿ����ѡ������λ��
		if((cx == 0) || (cx == 1))
		{
			CRect oRect;
			GetWindowRect(&oRect);
			oRect.right = m_oRect.left + 250;
			MoveWindow(oRect);
		}
		GetClientRect(&m_oRect);
		// �жϵ�ǰͼ�δ�С�Ƿ���Ի�ͼ
		CheckIfCanDraw();
		RedrawWindow();
	}
}

void CLeftViewBarInstrumentTop::OnPaint() 
{
	CPaintDC dc(this);
	GetClientRect(&m_oRect);

	// ������
	DrawBackground(&dc);
	// �жϣ����Ի�ͼ
	if(true == m_bCanDrawGraph)
	{
		// ������
		DrawLines(&dc);
		// �����ѡ������
		DrawSelectArea(&dc);
	}
}

void CLeftViewBarInstrumentTop::OnLButtonDown(UINT nFlags, CPoint point)
{
	// �жϣ����Ի�ͼ
	if(true == m_bCanDrawGraph)
	{
		CClientDC oDC(this);

		oDC.DPtoLP(&point);	
		m_oPointBase = point;	// ��������ʱ����
		m_oPointLast = m_oPointBase;	// �����ͷ�ʱ����
		m_bMouseDownLeft = true;	// �������Ƿ���
	}

	CBCGPDockingControlBar::OnLButtonDown(nFlags, point);
}

void CLeftViewBarInstrumentTop::OnLButtonUp(UINT nFlags, CPoint point)
{
	// �жϣ��������Ƿ��� && ���Ի�ͼ
	if((true == m_bMouseDownLeft) && (true == m_bCanDrawGraph))
	{
		CClientDC oDC(this);
		oDC.DPtoLP(&point);
		CRect oRect;
		oRect.left = m_oPointBase.x;
		oRect.top = m_oPointBase.y;
		oRect.right = m_oPointLast.x;
		oRect.bottom = m_oPointLast.y;
		oRect.NormalizeRect();	
		oDC.DrawFocusRect(&oRect);
		m_oPointLast = point;	// �����ͷ�ʱ����
		m_bMouseDownLeft = false;	// �������Ƿ���

		// �õ�ѡ�е�����
		if(true == GetSelectAreaPoint())
		{
			m_bDrawSelectArea = true;	// �Ƿ����ѡ������λ��
			Invalidate(TRUE);
		}
		else
		{
			m_bDrawSelectArea = false;	// �Ƿ����ѡ������λ��
			Invalidate(TRUE);
		}
		// �����ֲ��Ŵ�
		OnZoomInNavigater();
	}

	CBCGPDockingControlBar::OnLButtonUp(nFlags, point);
}

void CLeftViewBarInstrumentTop::OnMouseMove(UINT nFlags, CPoint point)
{
	// �жϣ��������Ƿ��� && ���Ի�ͼ
	if((true == m_bMouseDownLeft) && (true == m_bCanDrawGraph))
	{
		CClientDC oDC(this);
		oDC.DPtoLP(&point);
		CRect oRect;
		oRect.left = m_oPointBase.x;
		oRect.top = m_oPointBase.y;
		oRect.right = m_oPointLast.x;
		oRect.bottom = m_oPointLast.y;
		oRect.NormalizeRect();	
		oDC.DrawFocusRect(&oRect);

		oRect.left = m_oPointBase.x;
		oRect.top = m_oPointBase.y;
		oRect.right = point.x;
		oRect.bottom = point.y;
		oRect.NormalizeRect();
		oDC.DrawFocusRect(&oRect);

		m_oPointLast = point;	// �����ͷ�ʱ����
	}

	CBCGPDockingControlBar::OnMouseMove(nFlags, point);
}

/**
* �����ֲ��Ŵ�
* @param void
* @return void
*/
void CLeftViewBarInstrumentTop::OnZoomInNavigater()
{
	CInstrumentGraphChildFrame* pParentFrame = (CInstrumentGraphChildFrame*)GetParentFrame();
	// �����ֲ��Ŵ�
	pParentFrame->OnZoomInNavigater(m_fZoomRate, m_fRateX, m_fRateY);
}

/**
* ��Ӧ���ò�������
* @param unsigned int uiLineCount ��������
* @return void
*/
void CLeftViewBarInstrumentTop::OnSetLineCount(unsigned int uiLineCount)
{
	m_bDrawSelectArea = false;	// �Ƿ����ѡ������λ��
	m_uiLineCount = uiLineCount;
	if(TRUE == ::IsWindow(this->m_hWnd))
	{
		// �жϵ�ǰͼ�δ�С�Ƿ���Ի�ͼ
		CheckIfCanDraw();
		RedrawWindow();
	}	
}

/**
* �õ�ѡ�е�����
* @param void
* @return bool true���ɹ���false��ʧ��
*/
bool CLeftViewBarInstrumentTop::GetSelectAreaPoint()
{
	m_oSelectArea.left = m_oPointBase.x;
	m_oSelectArea.top = m_oPointBase.y;
	m_oSelectArea.right = m_oPointLast.x;
	m_oSelectArea.bottom = m_oPointLast.y;
	m_oSelectArea.NormalizeRect();
	if(m_oSelectArea.left < m_iPaperHeadX)
	{
		m_oSelectArea.left = m_iPaperHeadX;
	}
	if(m_oSelectArea.right > m_oRect.right - m_iPaperHeadX)
	{
		m_oSelectArea.right = m_oRect.right - m_iPaperHeadX;
	}
	if(m_oSelectArea.top < m_iPaperHeadTop)
	{
		m_oSelectArea.top = m_iPaperHeadTop;
	}
	if(m_oSelectArea.bottom > m_iGridY * (m_uiLineCount - 1)  + m_iPaperHeadTop)
	{
		m_oSelectArea.bottom = m_iGridY * (m_uiLineCount - 1)  + m_iPaperHeadTop;
	}

	float fWidthDrag = (float)m_oSelectArea.Width();
	if(fWidthDrag < 10.0)
	{
		m_fZoomRate = 1.0;	// �Ŵ���
		m_fRateX = 0.0;	// ��׼��X
		m_fRateY = 0.0;	// ��׼��Y
		return false;
	}
	float fWidthClient = (float)(m_oRect.Width() - 2 * m_iPaperHeadX);
	m_fZoomRate = fWidthClient / fWidthDrag;
	m_fRateX = ((float)(m_oSelectArea.left - m_iPaperHeadX)) / ((float)(m_oRect.Width() - 2 * m_iPaperHeadX));	// ��׼��X
	if(m_uiLineCount > 1)
	{
		m_fRateY = ((float)(m_oSelectArea.top - m_iPaperHeadTop)) / ((float)(m_iGridY * (m_uiLineCount - 1)));	// ��׼��Y
	}
	else
	{
		m_fRateY = 0.0;
	}

	return true;
}

/**
* ������
* @param CDC* pDC ��ͼ���
* @return void
*/
void CLeftViewBarInstrumentTop::DrawBackground(CDC* pDC)
{
	CBrush oBrush;
	CBrush* pOldPenBrush;
	oBrush.CreateSolidBrush(RGB(255, 255, 255));
	pOldPenBrush = pDC->SelectObject(&oBrush);
	pDC->FillRect(&m_oRect, &oBrush);
	pDC->SelectObject(pOldPenBrush);
}

/**
* �жϵ�ǰͼ�δ�С�Ƿ���Ի�ͼ
* @param void
* @return bool true�����ԣ�false��������
*/
bool CLeftViewBarInstrumentTop::CheckIfCanDraw()
{
	if(0 == m_uiLineCount)
	{
		m_bCanDrawGraph = false;
		return false;
	}
	if(m_oRect.Width() <= m_iPaperHeadX * 2)
	{
		m_bCanDrawGraph = false;
		return false;
	}
	if(m_oRect.Height() <= (m_iPaperHeadTop + m_uiLineCount))
	{
		m_bCanDrawGraph = false;
		return false;
	}
	m_iGridY = (m_oRect.Height() - m_iPaperHeadTop) / m_uiLineCount;
	if(m_iGridY > m_iGridYMax)
	{
		m_iGridY = m_iGridYMax;
	}
	m_iLineHight = m_iGridY / 2;
	if(0 == m_iLineHight)
	{
		m_iLineHight = 1;
	}

	m_bCanDrawGraph = true;
	return true;
}

/**
* ������
* @param CDC* pDC
* @return void
*/
void CLeftViewBarInstrumentTop::DrawLines(CDC* pDC)
{
	CPen oPenLine;
	CPen* pOldPen;

	oPenLine.CreatePen(PS_SOLID, m_iLineHight, RGB(128, 128, 128));
	pOldPen = pDC->SelectObject(&oPenLine);

	for(int i = 0; i < m_uiLineCount; i++)
	{
		pDC->MoveTo(m_iPaperHeadX, m_iPaperHeadTop + m_iGridY * i);
		pDC->LineTo(m_oRect.right - m_iPaperHeadX, m_iPaperHeadTop + m_iGridY * i);
	}
	pDC->SelectObject(pOldPen);
}

/**
* �����ѡ������
* @param CDC* pDC
* @return void
*/
void CLeftViewBarInstrumentTop::DrawSelectArea(CDC* pDC)
{
	if(true == m_bDrawSelectArea)	// �Ƿ����ѡ������λ��
	{
		CPen oPen;
		CPen* pOldPen;

		oPen.CreatePen(PS_SOLID, 3, RGB(0, 128, 0));
		pOldPen = pDC->SelectObject(&oPen);

		pDC->MoveTo(CPoint(m_oSelectArea.left, m_oSelectArea.top));
		pDC->LineTo(CPoint(m_oSelectArea.right, m_oSelectArea.top));
		pDC->MoveTo(CPoint(m_oSelectArea.left, m_oSelectArea.bottom));
		pDC->LineTo(CPoint(m_oSelectArea.right, m_oSelectArea.bottom));

		pDC->MoveTo(CPoint(m_oSelectArea.left, m_oSelectArea.top));
		pDC->LineTo(CPoint(m_oSelectArea.left, m_oSelectArea.bottom));
		pDC->MoveTo(CPoint(m_oSelectArea.right, m_oSelectArea.top));
		pDC->LineTo(CPoint(m_oSelectArea.right, m_oSelectArea.bottom));

		pDC->SelectObject(pOldPen);
	}
}

