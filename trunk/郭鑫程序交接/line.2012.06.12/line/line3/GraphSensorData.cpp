#include "stdafx.h"
#include "GraphSensorData.h"

CGraphSensorData::CGraphSensorData(void)
{
	// ����
	OnReset();
}

CGraphSensorData::~CGraphSensorData(void)
{
}

// ����ͼ�β���
void CGraphSensorData::SetDrawParam()
{

}

// ����
void CGraphSensorData::OnReset()
{
	m_iPosX = 0;	// X����λ��
	m_iPosY = 0;	// Y����λ��
	m_pChannelSetupData = NULL;	// ���ָ��
}

// ��ͼ
void CGraphSensorData::DrawUnit(CDC* pDC, int iGridX, int iGridY, int iUnitWidth, int iUnitHight,  int iUnitSizeMode, unsigned int uiTestType, bool bDrawSensorNb, float fSeismonitorLimit)
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

	// ���첨��
	if(0 < m_pChannelSetupData->m_uiSN)
	{
		// �жϣ��ɼ�վΪ������
		if(true == m_pChannelSetupData->m_bJumped)
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
		// �жϣ��ɼ�վΪ�Ƶ�
		else if(true == m_pChannelSetupData->m_bMute)
		{
			oPenUnit.CreatePen(PS_SOLID, 1, RGB(255, 0, 0));	// ��ɫ
			oBrushUnit.CreateSolidBrush(RGB(255, 0, 0));	// ��ɫ
			pOldPen = pDC->SelectObject(&oPenUnit);
			pOldPenBrush = pDC->SelectObject(&oBrushUnit);

			// ��ʮ��
			pDC->MoveTo(CPoint(oRect.left, iCenterY));
			pDC->LineTo(CPoint(oRect.right, iCenterY));
			pDC->MoveTo(CPoint(iCenterX, oRect.top));
			pDC->LineTo(CPoint(iCenterX, oRect.bottom));
		}
		// �жϣ��ɼ�վΪ�ɼ���
		else
		{
			byte byCheck = m_pChannelSetupData->GetTestResultCheck(uiTestType, fSeismonitorLimit);
			switch(byCheck)
			{
			case 0:	// 0��δ����
				oPenUnit.CreatePen(PS_SOLID, 0, RGB(0, 0, 0));
				oBrushUnit.CreateSolidBrush(RGB(0, 0, 255));	// ��ɫ
				pOldPen = pDC->SelectObject(&oPenUnit);
				pOldPenBrush = pDC->SelectObject(&oBrushUnit);

				pDC->Ellipse(&oRect);
				// ������С��Բ
				pDC->Ellipse(oRect.left + iUnitWidth / 4, oRect.top + iUnitHight / 4, oRect.right - iUnitWidth / 4, oRect.bottom - iUnitHight / 4);
				break;
			case 1:	// 1�����Ժϸ�
				if(22 == uiTestType)
				{
					// �õ��������ͼ�ε�Ԫ�߶�
					int iGraphHight = GetSeismonitorGraphHight(iUnitHight, fSeismonitorLimit);
					oRect.left = iCenterX - iUnitWidth / 2;
					oRect.top = iCenterY - iGraphHight / 2;
					oRect.right = oRect.left + iUnitWidth;
					oRect.bottom = oRect.top + iGraphHight;

					oPenUnit.CreatePen(PS_SOLID, 0, RGB(0, 0, 0));
					GetSeismonitorGraphColour(&oBrushUnit, fSeismonitorLimit);
					pOldPen = pDC->SelectObject(&oPenUnit);
					pOldPenBrush = pDC->SelectObject(&oBrushUnit);

					pDC->FillRect(&oRect, &oBrushUnit);
//					pDC->Rectangle(&oRect);
				}
				else
				{
					oPenUnit.CreatePen(PS_SOLID, 0, RGB(0, 0, 0));
					oBrushUnit.CreateSolidBrush(RGB(0, 255, 0));	// ��ɫ
					pOldPen = pDC->SelectObject(&oPenUnit);
					pOldPenBrush = pDC->SelectObject(&oBrushUnit);

					pDC->Ellipse(&oRect);
					// ������С��Բ
					pDC->Ellipse(oRect.left + iUnitWidth / 4, oRect.top + iUnitWidth / 4, oRect.right - iUnitWidth / 4, oRect.bottom - iUnitWidth / 4);
				}
				break;
			case 2:	// 2�����Բ��ϸ�
				if(22 == uiTestType)
				{
					// �õ��������ͼ�ε�Ԫ�߶�
					int iGraphHight = GetSeismonitorGraphHight(iUnitHight, fSeismonitorLimit);
					oRect.left = iCenterX - iUnitWidth / 2;
					oRect.top = iCenterY - iGraphHight / 2;
					oRect.right = oRect.left + iUnitWidth;
					oRect.bottom = oRect.top + iGraphHight;

					oPenUnit.CreatePen(PS_SOLID, 0, RGB(0, 0, 0));
					oBrushUnit.CreateSolidBrush(RGB(255, 0, 0));	// ��ɫ
					pOldPen = pDC->SelectObject(&oPenUnit);
					pOldPenBrush = pDC->SelectObject(&oBrushUnit);

					pDC->FillRect(&oRect, &oBrushUnit);
//					pDC->Rectangle(&oRect);
				}
				else
				{
					oPenUnit.CreatePen(PS_SOLID, 0, RGB(0, 0, 0));
					oBrushUnit.CreateSolidBrush(RGB(255, 0, 0));	// ��ɫ
					pOldPen = pDC->SelectObject(&oPenUnit);
					pOldPenBrush = pDC->SelectObject(&oBrushUnit);

					pDC->Ellipse(&oRect);
					// ������С��Բ
					pDC->Ellipse(oRect.left + iUnitWidth / 4, oRect.top + iUnitWidth / 4, oRect.right - iUnitWidth / 4, oRect.bottom - iUnitWidth / 4);
				}
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
			}
		}
	}
	// �жϣ�δ����IP��ַ
	else
	{
		// �жϣ��ɼ�վΪ�Ƶ�
		if(true == m_pChannelSetupData->m_bMute)
		{
			oPenUnit.CreatePen(PS_SOLID, 1, RGB(255, 0, 0));	// ��ɫ
			oBrushUnit.CreateSolidBrush(RGB(255, 0, 0));	// ��ɫ
			pOldPen = pDC->SelectObject(&oPenUnit);
			pOldPenBrush = pDC->SelectObject(&oBrushUnit);

			// ��ʮ��
			pDC->MoveTo(CPoint(oRect.left, iCenterY));
			pDC->LineTo(CPoint(oRect.right, iCenterY));
			pDC->MoveTo(CPoint(iCenterX, oRect.top));
			pDC->LineTo(CPoint(iCenterX, oRect.bottom));
		}
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

	}

	if(true == bDrawSensorNb)
	{
		oRect.left = iCenterX - iUnitWidth / 2;
		oRect.top = iCenterY - iUnitHight / 2;
		oRect.right = oRect.left + iUnitWidth;
		oRect.bottom = oRect.top + iUnitHight;

		CString strSensorNb;
		strSensorNb.Format("%d", m_pChannelSetupData->m_uiSensorNb);
		int nPrevMode = pDC->SetBkMode(TRANSPARENT); 		
		pDC->DrawText(strSensorNb, &oRect, DT_CENTER | DT_VCENTER);
		pDC->SetBkMode(nPrevMode);
	}

	pDC->SelectObject(pOldPen);
	pDC->SelectObject(pOldPenBrush);
}

// �õ��������ͼ�ε�Ԫ��Ը߶�
int CGraphSensorData::GetSeismonitorGraphHight(float fSeismonitorLimit)
{
	float fDis = (fSeismonitorLimit - m_pChannelSetupData->m_fNoiseMonitorValue) / 6.0;
	int iDis = abs((int)fDis);
	if(0 == iDis)
	{
		iDis = 1;
	}
	else if(8 < iDis)
	{
		iDis = 8;
	}
	return iDis;
}

// �õ��������ͼ�ε�Ԫ�߶�
int CGraphSensorData::GetSeismonitorGraphHight(int iUnitHight, float fSeismonitorLimit)
{
	int iDis = GetSeismonitorGraphHight(fSeismonitorLimit);
	int iGraphHight = iUnitHight * iDis / 8;

	return iGraphHight;
}

// �õ��������ͼ�ε�Ԫ��ɫ
void CGraphSensorData::GetSeismonitorGraphColour(CBrush *oBrushUnit, float fSeismonitorLimit)
{
	int iDis = GetSeismonitorGraphHight(fSeismonitorLimit);
	switch (iDis)
	{
	case 1:
		oBrushUnit->CreateSolidBrush(RGB(255, 0, 0));	// ��ɫ
		break;
	case 2:
		oBrushUnit->CreateSolidBrush(RGB(255, 128, 0));	// ɫ6
		break;
	case 3:
		oBrushUnit->CreateSolidBrush(RGB(255, 128, 64));	// ɫ5
		break;
	case 4:
		oBrushUnit->CreateSolidBrush(RGB(255, 192, 64));	// ɫ4
		break;
	case 5:
		oBrushUnit->CreateSolidBrush(RGB(255, 255, 0));	// ɫ3����ɫ
		break;
	case 6:
		oBrushUnit->CreateSolidBrush(RGB(255, 255, 200));	// ɫ2
		break;
	case 7:
		oBrushUnit->CreateSolidBrush(RGB(255, 255, 255));	// ɫ1����ɫ
		break;
	case 8:
		oBrushUnit->CreateSolidBrush(RGB(0, 255, 0));	// ��ɫ
		break;
	}
}
// cxm 2011-09-19
// ���GO��ť���������м�ѡ���豸�Ĳ��Խ��
void CGraphSensorData::OnClearCheckInstrumentTestResult(unsigned int uiTestType)
{
	switch(uiTestType)
	{
	case 15:	// �첨�����衣 Resistance
		m_pChannelSetupData->m_byResistanceCheck = 0;
		break;
	case 14:	// �첨��©�硣 Leakage
		m_pChannelSetupData->m_byLeakageCheck = 0;
		break;
	case 1:	// �첨�������� Noise
		m_pChannelSetupData->m_byNoiseCheck = 0;
		break;
	case 20:	// �첨����б�ȡ� Tilt
		m_pChannelSetupData->m_byTiltCheck = 0;
		break;
	case 21:	// �첨����б��ģ�͡�Tilt Model
		m_pChannelSetupData->m_byTiltModelCheck = 0;
		break;
	case 22:	// �첨���������
		m_pChannelSetupData->m_byNoiseMonitorCheck = 0;
		break;
	case 40:	// ���м첨������
		m_pChannelSetupData->m_byCheck = 0;
		break;
	}
}