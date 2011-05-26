// WndInstrument.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "BCGPVisualStudioGUIDemo.h"
#include "WndInstrument.h"

// CWndInstrument

IMPLEMENT_DYNAMIC(CWndInstrument, CBCGPStatic)

CWndInstrument::CWndInstrument()
{
	/** ��������*/
	m_uiInstrumentCountAll = 0;
	/** ͼ�ε�Ԫ���X*/
	m_iGridX = 50;
	/** ͼ�ε�Ԫ���Y*/
	m_iGridY = 50;
	/** ͼ�ε�Ԫ���*/
	m_iUnitWidth = 32;
	/** ͼ�ε�Ԫ�߶�*/
	m_iUnitHight = 32;
	/** ͼ�θ߶�X*/
	m_iPaperHight = 100;
}

CWndInstrument::~CWndInstrument()
{
}


BEGIN_MESSAGE_MAP(CWndInstrument, CBCGPStatic)
	ON_WM_SIZE()
	ON_WM_PAINT()
END_MESSAGE_MAP()



// CWndInstrument ��Ϣ�������



void CWndInstrument::OnSize(UINT nType, int cx, int cy)
{
	CBCGPStatic::OnSize(nType, cx, cy);
	RedrawWindow();
}

void CWndInstrument::OnPaint()
{
	CPaintDC dc(this);
	GetClientRect(&m_oRect);
	m_iPaperHight = m_oRect.bottom - m_iGridY;

	// ������
	DrawBackground(&dc);
	// ��������
	DrawLinkLine(&dc);

	// ��ȫ����Ԫͼ
	if(1 < m_uiInstrumentCountAll)
	{		
		for(unsigned int i = 0; i < m_uiInstrumentCountAll; i++)
		{
			DrawUnit(&dc, i);
		}
	}
}

/**
* ������
* @param CDC* pDC ��ͼ���
* @return void
*/
void CWndInstrument::DrawBackground(CDC* pDC)
{
	CBrush oBrush;
	CBrush* pOldPenBrush;
	oBrush.CreateSolidBrush(RGB(255, 255, 255));
	pOldPenBrush = pDC->SelectObject(&oBrush);
	pDC->FillRect(&m_oRect, &oBrush);
	pDC->SelectObject(pOldPenBrush);
}

/**
* ��������
* @param CDC* pDC ��ͼ���
* @return void
*/
void CWndInstrument::DrawLinkLine(CDC* pDC)
{
	CPen oPenLine;
	CPen* pOldPen;

	oPenLine.CreatePen(PS_SOLID, 3, RGB(0, 128, 0));
	pOldPen = pDC->SelectObject(&oPenLine);

	CPoint ptStart, ptEnd;

	ptStart.x = m_iGridX;
	ptStart.y = m_iPaperHight;

	ptEnd.x = (m_uiInstrumentCountAll) * m_iGridX;
	ptEnd.y = m_iPaperHight;

	pDC->MoveTo(ptStart);
	pDC->LineTo(ptEnd);

	pDC->SelectObject(pOldPen);
}

/**
* ����˵��
* @param CDC* pDC ��ͼ���
* @param int iIndex ͼ�ε�Ԫ����
* @return void
*/
// ����Ԫͼ
void CWndInstrument::DrawUnit(CDC* pDC, int iIndex)
{
	CPen oPenUnit;
	CPen* pOldPen;
	CBrush oBrushUnit;
	CBrush* pOldPenBrush;

	int iCenterX = m_iGridX + iIndex * m_iGridX;
	int iCenterY = m_iPaperHight;
	CRect oRect;
	oRect.left = iCenterX - m_iUnitWidth / 2;
	oRect.top = iCenterY - m_iUnitHight / 2;
	oRect.right = oRect.left + m_iUnitWidth;
	oRect.bottom = oRect.top + m_iUnitHight;

	oPenUnit.CreatePen(PS_SOLID, 0, RGB(0, 0, 0));
	oBrushUnit.CreateSolidBrush(RGB(0, 255, 0));	// ��ɫ

	pOldPen = pDC->SelectObject(&oPenUnit);
	pOldPenBrush = pDC->SelectObject(&oBrushUnit);

	pDC->Ellipse(&oRect);

	pDC->SelectObject(pOldPen);
	pDC->SelectObject(pOldPenBrush);
}

/**
* ��Ӧ��ʾ�ػص�ͼ����ͼ
* @param unsigned int uiCount �ػص�����������
* @return void
*/
void CWndInstrument::OnShowDetourGraphView(unsigned int uiCount)
{
	m_uiInstrumentCountAll = uiCount;
	RedrawWindow();
}
