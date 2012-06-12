#include "stdafx.h"
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
			}
			// �жϣ��ɼ�վΪ�ɼ���
			else
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
					// ������С��Բ
					pDC->Ellipse(oRect.left + iUnitWidth / 4, oRect.top + iUnitWidth / 4, oRect.right - iUnitWidth / 4, oRect.bottom - iUnitWidth / 4);
					break;
				case 1:	// 1�����Ժϸ�
					oPenUnit.CreatePen(PS_SOLID, 0, RGB(0, 0, 0));
					oBrushUnit.CreateSolidBrush(RGB(0, 255, 0));	// ��ɫ
					pOldPen = pDC->SelectObject(&oPenUnit);
					pOldPenBrush = pDC->SelectObject(&oBrushUnit);

					pDC->Ellipse(&oRect);
					// ������С��Բ
					pDC->Ellipse(oRect.left + iUnitWidth / 4, oRect.top + iUnitWidth / 4, oRect.right - iUnitWidth / 4, oRect.bottom - iUnitWidth / 4);
					break;
				case 2:	// 2�����Բ��ϸ�
					oPenUnit.CreatePen(PS_SOLID, 0, RGB(0, 0, 0));
					oBrushUnit.CreateSolidBrush(RGB(255, 0, 0));	// ��ɫ
					pOldPen = pDC->SelectObject(&oPenUnit);
					pOldPenBrush = pDC->SelectObject(&oBrushUnit);

					pDC->Ellipse(&oRect);
					// ������С��Բ
					pDC->Ellipse(oRect.left + iUnitWidth / 4, oRect.top + iUnitWidth / 4, oRect.right - iUnitWidth / 4, oRect.bottom - iUnitWidth / 4);
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
					break;
// 				case 5: // 5������м�ѡ�в�������
// 					oPenUnit.CreatePen(PS_SOLID, 1, RGB(0, 0, 0));
// 					oBrushUnit.CreateSolidBrush(RGB(190, 190, 190));	// ��ɫ
// 					pOldPen = pDC->SelectObject(&oPenUnit);
// 					pOldPenBrush = pDC->SelectObject(&oBrushUnit);
// 
// 					pDC->Ellipse(&oRect);
// 					// ������С��Բ
// 					pDC->Ellipse(oRect.left + iUnitWidth / 4, oRect.top + iUnitWidth / 4, oRect.right - iUnitWidth / 4, oRect.bottom - iUnitWidth / 4);
// 					break;
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
	}
	pDC->SelectObject(pOldPen);
	pDC->SelectObject(pOldPenBrush);
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
// cxm 2011-09-19
// ���GO��ť���������м�ѡ���豸�Ĳ��Խ��
void CGraphInstrumentData::OnClearCheckInstrumentTestResult(unsigned int uiTestType)
{
	switch(uiTestType)
	{
	case 4:	// ���������� Noise
		m_pInstrument->m_byNoiseCheck = 0;
		break;
	case 5:	// �������䡣 Distortion
		m_pInstrument->m_byDistortionCheck = 0;
		break;
	case 7:	// ���������� Crosstalk
		m_pInstrument->m_byCrosstalkCheck = 0;
		break;
	case 6:	// ��������/ ��λ�� Gain/Phase
		m_pInstrument->m_byGainAndPhaseCheck = 0;
		break;
	case 8:	// ������ģ��CMRR
		m_pInstrument->m_byCMRRCheck = 0;
		break;
	case 30:	// ������������
		m_pInstrument->m_byCheck = 0;
		break;
	}
}