#include "stdafx.h"
#include "resource.h"
#include "GraphInstrumentData.h"

CGraphInstrumentData::CGraphInstrumentData(void)
{
}

CGraphInstrumentData::~CGraphInstrumentData(void)
{
}

// ����ͼ�β���
void CGraphInstrumentData::SetDrawParam()
{

}

// ����
void CGraphInstrumentData::OnReset()
{
	m_bInUsed = false;	// ͼ�ε�Ԫ�Ƿ�ʹ����
	
	m_iPosX = 0;	// X����λ��
	m_iPosY = 0;	// Y����λ��
	m_iPosIndex = 0;	// ����λ������

	m_pInstrument = NULL;	// ����ָ��
}
// ��������λ������
int CGraphInstrumentData::CreatePosIndex(int iPosX, int iPosY)
{
	return iPosX * 100000 + iPosY;
}

// ��ͼ
void CGraphInstrumentData::DrawUnit(CDC* pDC, int iGridX, int iGridY, int iUnitWidth, int iUnitHight,  int iUnitSizeMode, unsigned int uiTestType)
{
	CPen oPenUnit;
	CPen* pOldPen;
	CBrush oBrushUnit;
	CBrush* pOldPenBrush;

	int iCenterX = m_iPosX * iGridX;
	int iCenterY = m_iPosY * iGridY;
	CRect oRect;
	oRect.left = iCenterX - iUnitWidth / 2;
	oRect.top = iCenterY - iUnitWidth / 2;
	oRect.right = oRect.left + iUnitWidth;
	oRect.bottom = oRect.top + iUnitWidth;

	// by vivi 2011-01-12
	CDC m_MemDc;//����һ��DC
	CBitmap m_BkBmp;//�����λͼ����
	BITMAP m_BmpInfo;//����һ��λͼ��Ϣ�ṹ��

	// ������
	if(0 < m_pInstrument->m_uiIP)
	{
		if(1 == m_pInstrument->m_uiInstrumentType)	// ����վ
		{
			oPenUnit.CreatePen(PS_SOLID, 0, RGB(0, 0, 0));
			oBrushUnit.CreateSolidBrush(RGB(0, 255, 0));	// ��ɫ
			pOldPen = pDC->SelectObject(&oPenUnit);
			pOldPenBrush = pDC->SelectObject(&oBrushUnit);
			pDC->FillRect(&oRect, &oBrushUnit);
			pDC->Rectangle(&oRect);
			// ��X��
			pDC->MoveTo(CPoint(oRect.left, oRect.top));
			pDC->LineTo(CPoint(oRect.right, oRect.bottom));
			pDC->MoveTo(CPoint(oRect.left, oRect.bottom));
			pDC->LineTo(CPoint(oRect.right, oRect.top));

			// by vivi 2011-01-12
			pDC->SelectObject(pOldPen);
			pDC->SelectObject(pOldPenBrush);
		}
		else if(2 == m_pInstrument->m_uiInstrumentType)	// ��Դվ
		{
			oPenUnit.CreatePen(PS_SOLID, 0, RGB(0, 0, 0));
			oBrushUnit.CreateSolidBrush(RGB(0, 255, 0));	// ��ɫ
			pOldPen = pDC->SelectObject(&oPenUnit);
			pOldPenBrush = pDC->SelectObject(&oBrushUnit);
			pDC->FillRect(&oRect, &oBrushUnit);
			pDC->Rectangle(&oRect);
			// ������С����
			pDC->Rectangle(oRect.left + iUnitWidth / 4, oRect.top + iUnitWidth / 4, oRect.right - iUnitWidth / 4, oRect.bottom - iUnitWidth / 4);
			// by vivi 2011-01-12
			pDC->SelectObject(pOldPen);
			pDC->SelectObject(pOldPenBrush);
		}
		// �жϣ��ɼ�վ
		else
		{
			// �жϣ��ɼ�վ���ӱ�ը��������
			if(true == m_pInstrument->m_bBlastMachine)
			{
				oPenUnit.CreatePen(PS_SOLID, 0, RGB(0, 0, 0));
				oBrushUnit.CreateSolidBrush(RGB(0, 255, 0));	// ��ɫ
				pOldPen = pDC->SelectObject(&oPenUnit);
				pOldPenBrush = pDC->SelectObject(&oBrushUnit);

				pDC->Ellipse(&oRect);
				// ������С����
				pDC->Rectangle(oRect.left + iUnitWidth / 4, oRect.top + iUnitWidth / 4, oRect.right - iUnitWidth / 4, oRect.bottom - iUnitWidth / 4);
				// by vivi 2011-01-12
				pDC->SelectObject(pOldPen);
				pDC->SelectObject(pOldPenBrush);
			}
			// �жϣ��ɼ�վΪ������
			else if(true == m_pInstrument->m_bJumpedChannel)
			{
				oPenUnit.CreatePen(PS_SOLID, 1, RGB(0, 255, 0));	// ��ɫ
				oBrushUnit.CreateSolidBrush(RGB(0, 255, 0));	// ��ɫ
				pOldPen = pDC->SelectObject(&oPenUnit);
				pOldPenBrush = pDC->SelectObject(&oBrushUnit);

				// ��ʮ��
				pDC->MoveTo(CPoint(oRect.left, iCenterY));
				pDC->LineTo(CPoint(oRect.right, iCenterY));
				pDC->MoveTo(CPoint(iCenterX, oRect.top));
				pDC->LineTo(CPoint(iCenterX, oRect.bottom));
				// by vivi 2011-01-12
				pDC->SelectObject(pOldPen);
				pDC->SelectObject(pOldPenBrush);
			}
			// �жϣ��ɼ�վΪ������
			else if(true == m_pInstrument->m_bAux)
			{
				byte byCheck = m_pInstrument->GetTestResultCheck(uiTestType);
				switch(byCheck)
				{
				case 0:	// 0��δ����
					oPenUnit.CreatePen(PS_SOLID, 0, RGB(0, 0, 0));
					oBrushUnit.CreateSolidBrush(RGB(0, 0, 255));	// ��ɫ
					pOldPen = pDC->SelectObject(&oPenUnit);
					pOldPenBrush = pDC->SelectObject(&oBrushUnit);

					pDC->Ellipse(&oRect);
					break;
				case 1:	// 1�����Ժϸ�
					oPenUnit.CreatePen(PS_SOLID, 0, RGB(0, 0, 0));
					oBrushUnit.CreateSolidBrush(RGB(0, 255, 0));	// ��ɫ
					pOldPen = pDC->SelectObject(&oPenUnit);
					pOldPenBrush = pDC->SelectObject(&oBrushUnit);

					pDC->Ellipse(&oRect);
					break;
				case 2:	// 2�����Բ��ϸ�
					oPenUnit.CreatePen(PS_SOLID, 0, RGB(0, 0, 0));
					oBrushUnit.CreateSolidBrush(RGB(255, 0, 0));	// ��ɫ
					pOldPen = pDC->SelectObject(&oPenUnit);
					pOldPenBrush = pDC->SelectObject(&oBrushUnit);

					pDC->Ellipse(&oRect);
					break;
				case 3:	// 3�����ź�
					oPenUnit.CreatePen(PS_SOLID, 1, RGB(0, 0, 255));	// ��ɫ
					oBrushUnit.CreateSolidBrush(RGB(0, 0, 255));	// ��ɫ
					pOldPen = pDC->SelectObject(&oPenUnit);
					pOldPenBrush = pDC->SelectObject(&oBrushUnit);

					// ��ʮ��
					pDC->MoveTo(CPoint(oRect.left, iCenterY));
					pDC->LineTo(CPoint(oRect.right, iCenterY));
					pDC->MoveTo(CPoint(iCenterX, oRect.top));
					pDC->LineTo(CPoint(iCenterX, oRect.bottom));
					break;
				}
				// by vivi 2011-01-12
				pDC->SelectObject(pOldPen);
				pDC->SelectObject(pOldPenBrush);
			}
			// �жϣ��ɼ�վΪ�ɼ���
			else
			{
				byte byCheck = m_pInstrument->GetTestResultCheck(uiTestType);
				switch(byCheck)
				{
				case 0:	// 0��δ����
					// by vivi 2011-01-12
// 					oPenUnit.CreatePen(PS_SOLID, 0, RGB(0, 0, 0));
// 					oBrushUnit.CreateSolidBrush(RGB(0, 0, 255));	// ��ɫ
// 					pOldPen = pDC->SelectObject(&oPenUnit);
// 					pOldPenBrush = pDC->SelectObject(&oBrushUnit);
// 
// 					pDC->Ellipse(&oRect);
// 					// ������С��Բ
// 					pDC->Ellipse(oRect.left + iUnitWidth / 4, oRect.top + iUnitWidth / 4, oRect.right - iUnitWidth / 4, oRect.bottom - iUnitWidth / 4);
					
					if (iUnitSizeMode == 1)
					{
						m_BkBmp.LoadBitmap(IDB_BITMAP_FDU_1);	// �˴�Ϊ�ո���ӽ�����λͼ��ԴID
					}
					else if (iUnitSizeMode == 2)
					{
						m_BkBmp.LoadBitmap(IDB_BITMAP_FDU_2);	// �˴�Ϊ�ո���ӽ�����λͼ��ԴID
					} 
					else if (iUnitSizeMode == 3)
					{
						m_BkBmp.LoadBitmap(IDB_BITMAP_FDU_3);	// �˴�Ϊ�ո���ӽ�����λͼ��ԴID
					}
					else
					{
						break;
					}
					m_BkBmp.GetBitmap(&m_BmpInfo);				// ��ȡλͼ�߿����Ϣ��������λͼ�ṹ����
					m_MemDc.CreateCompatibleDC(pDC);			// ����һ��������ĻDC���ڴ�DC��m_MemDc��
					m_MemDc.SelectObject(&m_BkBmp);				// ����λͼѡ�񵽸մ������ڴ�DC�С�

					/*���ڴ�DC��Ķ���������ĻDC��ȥ*/
					pDC->BitBlt(oRect.left,oRect.top,m_BmpInfo.bmWidth,m_BmpInfo.bmHeight,&m_MemDc,0,0,SRCCOPY);
					break;
				case 1:	// 1�����Ժϸ�
					oPenUnit.CreatePen(PS_SOLID, 0, RGB(0, 0, 0));
					oBrushUnit.CreateSolidBrush(RGB(0, 255, 0));	// ��ɫ
					pOldPen = pDC->SelectObject(&oPenUnit);
					pOldPenBrush = pDC->SelectObject(&oBrushUnit);

					pDC->Ellipse(&oRect);
					// ������С��Բ
					pDC->Ellipse(oRect.left + iUnitWidth / 4, oRect.top + iUnitWidth / 4, oRect.right - iUnitWidth / 4, oRect.bottom - iUnitWidth / 4);
					// by vivi 2011-01-12
					pDC->SelectObject(pOldPen);
					pDC->SelectObject(pOldPenBrush);
					break;
				case 2:	// 2�����Բ��ϸ�
					oPenUnit.CreatePen(PS_SOLID, 0, RGB(0, 0, 0));
					oBrushUnit.CreateSolidBrush(RGB(255, 0, 0));	// ��ɫ
					pOldPen = pDC->SelectObject(&oPenUnit);
					pOldPenBrush = pDC->SelectObject(&oBrushUnit);

					pDC->Ellipse(&oRect);
					// ������С��Բ
					pDC->Ellipse(oRect.left + iUnitWidth / 4, oRect.top + iUnitWidth / 4, oRect.right - iUnitWidth / 4, oRect.bottom - iUnitWidth / 4);
					// by vivi 2011-01-12
					pDC->SelectObject(pOldPen);
					pDC->SelectObject(pOldPenBrush);
					break;
				case 3:	// 3�����ź�
				case 4:	// 4��δ�ж�
					oPenUnit.CreatePen(PS_SOLID, 1, RGB(0, 0, 0));
					oBrushUnit.CreateSolidBrush(RGB(255, 255, 0));	// ��ɫ
					pOldPen = pDC->SelectObject(&oPenUnit);
					pOldPenBrush = pDC->SelectObject(&oBrushUnit);

					pDC->Ellipse(&oRect);
					// ������С��Բ
					pDC->Ellipse(oRect.left + iUnitWidth / 4, oRect.top + iUnitWidth / 4, oRect.right - iUnitWidth / 4, oRect.bottom - iUnitWidth / 4);
					// by vivi 2011-01-12
					pDC->SelectObject(pOldPen);
					pDC->SelectObject(pOldPenBrush);
					break;
				}
			}
		}
	}
	// �жϣ�δ����IP��ַ
	else
	{
		oPenUnit.CreatePen(PS_SOLID, 1, RGB(255, 255, 0));	// ��ɫ
		oBrushUnit.CreateSolidBrush(RGB(255, 255, 0));	// ��ɫ
		pOldPen = pDC->SelectObject(&oPenUnit);
		pOldPenBrush = pDC->SelectObject(&oBrushUnit);

		// ��ʮ��
		pDC->MoveTo(CPoint(oRect.left, iCenterY));
		pDC->LineTo(CPoint(oRect.right, iCenterY));
		pDC->MoveTo(CPoint(iCenterX, oRect.top));
		pDC->LineTo(CPoint(iCenterX, oRect.bottom));
		// by vivi 2011-01-12
		pDC->SelectObject(pOldPen);
		pDC->SelectObject(pOldPenBrush);
	}

	// by vivi 2011-01-12
//  	pDC->SelectObject(pOldPen);
//  	pDC->SelectObject(pOldPenBrush);
}

// ��ͼ����Ԫ������
void CGraphInstrumentData::DrawUnitLinkLine(CDC* pDC, int iGridX, int iGridY)
{
	if((m_pInstrument->m_uiSNInstrumentRight == 0) && (m_pInstrument->m_uiSNCrossDown == 0))
	{
		return;
	}

	CPen oPenLine;
	CPen* pOldPen;

	int iCenterX = m_iPosX * iGridX;
	int iCenterY = m_iPosY * iGridY;

	// �������ߣ����һ�
	// �жϣ��ػص��Ͷ�
	if(true == m_pInstrument->m_bDetourMarkerLow)
	{
		oPenLine.CreatePen(PS_DOT, 5, RGB(0, 0, 255));	// ��ɫ
	}
	else
	{
		oPenLine.CreatePen(PS_SOLID, 1, RGB(0, 255, 0));	// ��ɫ
	}
	
	pOldPen = pDC->SelectObject(&oPenLine);
	if(m_pInstrument->m_uiSNInstrumentRight > 0)
	{
		pDC->MoveTo(CPoint(iCenterX, iCenterY));
		pDC->LineTo(CPoint(iCenterX + iGridX, iCenterY));
	}
	// �������ߣ����»�
	if(m_pInstrument->m_uiSNCrossDown > 0)
	{
		pDC->MoveTo(CPoint(iCenterX, iCenterY));
		pDC->LineTo(CPoint(iCenterX, iCenterY + iGridY));
	}
	pDC->SelectObject(pOldPen);
}