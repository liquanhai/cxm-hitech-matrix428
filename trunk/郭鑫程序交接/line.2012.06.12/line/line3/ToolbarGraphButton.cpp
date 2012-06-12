
#include "stdafx.h"
#include "ToolbarGraphButton.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

IMPLEMENT_SERIAL(CToolbarGraphButton, CBCGPToolbarButton, 1)
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CToolbarGraphButton::CToolbarGraphButton (UINT uiID)
{
	m_bText = FALSE;	
	m_bImage = TRUE;
	m_nID = uiID;

	/**���*/
	m_iWidth = 20;
	/**ģʽ 0��δѡ�У�1��ѡ��*/
	m_iMode = 0;
	/**��ǩ*/
	m_strLabel = "";
}

CToolbarGraphButton::~CToolbarGraphButton()
{

}

void CToolbarGraphButton::OnDraw(CDC* pDC, const CRect& rectClient, 
							 CBCGPToolBarImages* /*pImages*/, 
							 BOOL /*bHorz*/, BOOL /*bCustomizeMode*/,						
							 BOOL /*bHighlight*/,						
							 BOOL /*bDrawBorder*/, 
							 BOOL /*bGrayDisabledButtons*/)
{
	CPen oPen;
	CPen* pOldPen;
	CBrush oBrushGreen;
	CBrush oBrushWhite;
	CBrush* pOldPenBrush;

	oPen.CreatePen(PS_SOLID, 1, RGB(0, 0, 0));	// ��ɫ
	oBrushGreen.CreateSolidBrush(RGB(0, 255, 0));	// ��ɫ
	oBrushWhite.CreateSolidBrush(RGB(255, 255, 255));	// ��ɫ
	pOldPen = pDC->SelectObject(&oPen);

	CRect oRect;

	oRect.left = rectClient.left;
	oRect.right = rectClient.right;
	oRect.top = rectClient.top;
	oRect.bottom = rectClient.bottom;

	if(0 == m_iMode)
	{
		pOldPenBrush = pDC->SelectObject(&oBrushWhite);
		pDC->FillRect(&oRect, &oBrushWhite);
	}
	else if(1 == m_iMode)
	{
		pOldPenBrush = pDC->SelectObject(&oBrushGreen);
		pDC->FillRect(&oRect, &oBrushGreen);
	}

	pDC->DrawText(m_strLabel, &oRect, DT_CENTER | DT_VCENTER);

	pDC->SelectObject(pOldPen);
	pDC->SelectObject(pOldPenBrush);
}		 


SIZE CToolbarGraphButton::OnCalculateSize(CDC* pDC, const CSize& sizeDefault, BOOL bHorz)
{
	CSize size = sizeDefault;
	size.cx = m_iWidth;
	return size;
}