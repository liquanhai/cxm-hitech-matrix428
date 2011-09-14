#include "stdafx.h"
#include "GraphSensorList.h"

CGraphSensorList::CGraphSensorList()
{
	m_pChannelList = NULL;	// �������ָ��	

	m_pArrayGraphSensor = NULL;	// �첨��ͼ�ε�Ԫ����ָ��	
	m_uiCountAll = 0;	// ����	
	m_uiCountUsed = 0;	// ʹ��������	
	m_uiCountFree = 0;	// ��������

	m_oPaperColor = RGB(255, 255, 255);	// ������ɫ
	m_oGridColor = RGB(0, 0, 128);	// ��������ɫ

	m_uiRowCount = 0;	// ����
	m_uiColumnCount = 0;	// ����

	m_iPaperX = 0;	// ͼ����X����ߴ�
	m_iPaperY = 0;	// ͼ����Y����ߴ�

	m_iPaperHeadLeft = 50;	// ͼ�������Ԥ���ߴ�
	m_iPaperHeadTop = 50;	// ͼ�������Ԥ���ߴ�

	m_iGridXMin = 10;	// ��Ԫ��X������С�ߴ�
	m_iGridYMin = 40;	// ��Ԫ��Y������С�ߴ�
	m_iGridXMax = 400;	// ��Ԫ��X�������ߴ�
	m_iGridYMax = 200;	// ��Ԫ��Y�������ߴ�

	m_iSizeModeMin = 40;	// ͼ�ε�Ԫ��С�ߴ�ģʽʱ�����޳ߴ�
	m_iSizeModeMax = 50;	// ͼ�ε�Ԫ���ߴ�ģʽʱ�����޳ߴ�

	m_iUnitWidthMin = 10;	// ͼ�ε�Ԫ��ȣ���С�ߴ�ģʽ
	m_iUnitHightMin = 24;	// ͼ�ε�Ԫ�߶ȣ���С�ߴ�ģʽ

	m_iUnitWidthNormal = 16;	// ͼ�ε�Ԫ��ȣ������ߴ�ģʽ
	m_iUnitHightNormal = 32;	// ͼ�ε�Ԫ�߶ȣ������ߴ�ģʽ

	m_iUnitWidthMax = 32;	// ͼ�ε�Ԫ��ȣ����ߴ�ģʽ	
	m_iUnitHightMax = 32;	// ͼ�ε�Ԫ�߶ȣ����ߴ�ģʽ

	m_iGridX = m_iGridXMin;	// ��Ԫ��X����ߴ�
	m_iGridY = m_iGridYMin;	// ��Ԫ��Y����ߴ�
}

CGraphSensorList::~CGraphSensorList()
{
}

// ��ʼ��
void CGraphSensorList::OnInit()
{
	// ��������
	m_pArrayGraphSensor = new CGraphSensorData[m_uiCountAll];
	// ʹ��������
	m_uiCountUsed = 0;
	// ��������
	m_uiCountFree = m_uiCountAll;
}

// �ر�
void CGraphSensorList::OnClose()
{
	// ɾ���������
	delete[] m_pArrayGraphSensor;
}

// ����
void CGraphSensorList::OnReset()
{
	// ʹ���в�������
	m_uiCountUsed = 0;
	// ���в������
	m_uiCountFree = m_uiCountAll;
	for(unsigned int i = 0; i < m_uiCountAll; i++)
	{
		// ����
		m_pArrayGraphSensor[i].OnReset();
	}

	m_uiRowCount = 0;	// ����
	m_uiColumnCount = 0;	// ����
	m_iPaperX = 0;	// ͼ����X����ߴ�
	m_iPaperY = 0;	// ͼ����Y����ߴ�
	m_iGridX = m_iGridXMin;	// ��Ԫ��X����ߴ�
	m_iGridY = m_iGridYMin;	// ��Ԫ��Y����ߴ�
}

// �õ����ߺ���ͼ�������ڵ�������
unsigned int CGraphSensorList::GetUintRowIndex(unsigned int uiNbLine)
{
	unsigned int uiPosX;
	m_pChannelList->m_oNbLineMap.Lookup(uiNbLine, uiPosX);
	return uiPosX;
}

// �õ��������ͼ�������ڵ�������
unsigned int CGraphSensorList::GetUintColumnIndex(unsigned int uiNbPoint, unsigned int uiNbChannel)
{
	unsigned int uiPosY = (uiNbPoint - m_pChannelList->m_uiNbPointMin) * m_pChannelList->m_uiPointChannelCountMax + uiNbChannel - 1;
	return uiPosY;
}

// �õ�ͼ������������Ӧ�Ĳ��ߺ�
unsigned int CGraphSensorList::GetUintLineNb(unsigned int uiRowIndex)
{
	POSITION pos = m_pChannelList->m_olsNbLine.FindIndex(uiRowIndex);
	unsigned int uiLineNb = m_pChannelList->m_olsNbLine.GetAt(pos);
	return uiLineNb;
}

// �õ�ͼ������������Ӧ�Ĳ���
unsigned int CGraphSensorList::GetUintPointNb(unsigned int uiColumIndex)
{
	unsigned int uiPointNb = (uiColumIndex / m_pChannelList->m_uiPointChannelCountMax) + m_pChannelList->m_uiNbPointMin;
	return uiPointNb;
}

// �õ�ͼ������������Ӧ�Ĳ����
unsigned int CGraphSensorList::GetUintChannelNb(unsigned int uiColumIndex)
{
	unsigned int uiChannelNb = uiColumIndex % m_pChannelList->m_uiPointChannelCountMax + 1;
	return uiChannelNb;
}

// �õ�ͼ��������������Ӧ�Ĳ��
CChannelSetupData* CGraphSensorList::GetChannelSetupData(unsigned int uiRowIndex, unsigned int uiColumIndex)
{
	CChannelSetupData* pChannelSetupData = NULL;
	unsigned int uiLineNb = GetUintLineNb(uiRowIndex);
	unsigned int uiPointNb = GetUintPointNb(uiColumIndex);
	unsigned int uiChannelNb = GetUintChannelNb(uiColumIndex);
	// �õ����
	pChannelSetupData = m_pChannelList->GetChannel(uiLineNb, uiPointNb, uiChannelNb);
	return pChannelSetupData;
}

// ���ؼ첨��ͼ����ͼ�첨��ͼ�ε�Ԫ����
void CGraphSensorList::LoadSiteData()
{
	m_uiRowCount = m_pChannelList->m_uiNbLineCount;	// ����
	unsigned int uiPointCount = m_pChannelList->m_uiNbPointMax - m_pChannelList->m_uiNbPointMin + 1;	// �������
	m_uiColumnCount = uiPointCount * m_pChannelList->m_uiPointChannelCountMax;	// ����

	CChannelSetupData* pChannelSetupData = NULL;
	for(unsigned int i = 0; i < m_pChannelList->m_uiCountUsed; i++)
	{
		// �õ�һ�����
		pChannelSetupData = m_pChannelList->GetChannelByIndex(i);
		m_pArrayGraphSensor[i].m_pChannelSetupData = pChannelSetupData;
		// �õ��������ͼ�������ڵ�������
		m_pArrayGraphSensor[i].m_iPosX = GetUintColumnIndex(pChannelSetupData->m_uiNbPoint, pChannelSetupData->m_uiNbChannel);
		// �õ����ߺ���ͼ�������ڵ�������
		m_pArrayGraphSensor[i].m_iPosY = GetUintRowIndex(pChannelSetupData->m_uiNbLine);	
	}
	m_uiCountUsed = m_pChannelList->m_uiCountUsed;
	m_uiCountFree = m_pChannelList->m_uiCountFree;

	m_iPaperX = (m_uiColumnCount - 1) * m_iGridX;	// X����ߴ�
	m_iPaperY = (m_uiRowCount - 1) * m_iGridY;	// Y����ߴ�
}

// ��ѡ������ת��Ϊ���������ַ���
CString CGraphSensorList::ConvertSelectAreaToAbsoluteSpreadString(CRect* pSelectAreaIndex)
{
	CString strAbsoluteSpread = "";
	CString strLine, strPoint;
	unsigned int uiPointNbStart, uiPointNbEnd;
	unsigned int uiLineNb;

	// �õ�ͼ������������Ӧ�Ĳ��ߺ�
	uiPointNbStart = GetUintPointNb(pSelectAreaIndex->left);
	uiPointNbEnd = GetUintPointNb(pSelectAreaIndex->right);
	strPoint.Format("%d-%d", uiPointNbStart, uiPointNbEnd);
	for(int i = pSelectAreaIndex->top; i <= pSelectAreaIndex->bottom; i++)
	{
		// �õ�ͼ������������Ӧ�Ĳ���
		uiLineNb = GetUintLineNb(i);
		strLine.Format("%d:%s;", uiLineNb, strPoint);
		strAbsoluteSpread = strAbsoluteSpread + strLine;
	}
	strAbsoluteSpread = strAbsoluteSpread.Left(strAbsoluteSpread.GetLength() - 1);
	return strAbsoluteSpread;
}

// ������ͼ
void CGraphSensorList::DrawGrid(CDC* pDC, int iPaperX, int iPaperY, int iGridX, int iGridY)
{

	COLORREF oldBkColor = m_oPaperColor;

	CRect rect;
	rect.left = 0;
	rect.top = 0;
	rect.right = iPaperX;
	rect.bottom = iPaperY;

	// Center lines
	CPen penDash;
	penDash.CreatePen(PS_DASH, 0, m_oGridColor);
	CPen* pOldPen = pDC->SelectObject(&penDash);

	pDC->MoveTo(0, rect.top);
	pDC->LineTo(0, rect.bottom);
	pDC->MoveTo(rect.left, 0);
	pDC->LineTo(rect.right, 0);

	// Major unit lines
	CPen penDot;
	penDot.CreatePen(PS_DOT, 0, m_oGridColor);
	pDC->SelectObject(&penDot);

	for (int x = 0; x < rect.right; x += iGridX)
	{
		if (x != 0)
		{
			pDC->MoveTo(x, rect.top);
			pDC->LineTo(x, rect.bottom);
		}
	}

	for (int y = 0; y < rect.bottom; y += iGridY)
	{
		if (y != 0)
		{
			pDC->MoveTo(rect.left, y);
			pDC->LineTo(rect.right, y);
		}
	}

	// Outlines
	CPen penSolid;
	penSolid.CreatePen(PS_SOLID, 0, m_oGridColor);
	pDC->SelectObject(&penSolid);
	pDC->MoveTo(rect.left, rect.top);
	pDC->LineTo(rect.right, rect.top);
	pDC->LineTo(rect.right, rect.bottom);
	pDC->LineTo(rect.left, rect.bottom);
	pDC->LineTo(rect.left, rect.top);

	pDC->SelectObject(pOldPen);
	pDC->SetBkColor(oldBkColor);
}

// �����߱��
void CGraphSensorList::DrawMarkLineNbAndPointNb(CDC* pDC, int iGridX, int iGridY)
{
	// �����߱��
	DrawMarkLineNb(pDC, iGridY);
	// �������
	DrawMarkPointNb(pDC, iGridX);
}

// �����߱�ߺͲ����
void CGraphSensorList::DrawMarkLineNb(CDC* pDC, int iGridY)
{
	CPen oPen;
	CPen* pOldPen;

	oPen.CreatePen(PS_SOLID, 2, RGB(255, 0, 0));
	pOldPen = pDC->SelectObject(&oPen);

	int iLineNb;
	CString strLineNb;
	CRect oRect;
	for(unsigned int i = 0; i < m_uiRowCount; i++)
	{
		iLineNb = GetUintLineNb(i);
		strLineNb.Format("%d", iLineNb);

		oRect.left = -50;
		oRect.right = 0;
		oRect.top = i * iGridY - m_iUnitHightMin / 2;
		oRect.bottom = oRect.top + m_iUnitHightMax;

		pDC->DrawText(strLineNb, &oRect, DT_LEFT | DT_VCENTER);

	}
	pDC->SelectObject(pOldPen);
}

// �������
void CGraphSensorList::DrawMarkPointNb(CDC* pDC, int iGridX)
{
	int iStep = 1;
	if(iGridX <= 2 * m_iGridXMin)
	{
		iStep = 5;
	}

	CPen oPen;
	CPen* pOldPen;

	oPen.CreatePen(PS_SOLID, 2, RGB(255, 0, 0));
	pOldPen = pDC->SelectObject(&oPen);

	int iPointNb;
	CString strPointNb;
	CRect oRect;
	for(unsigned int i = 0; i < m_uiColumnCount; i++)
	{
		if((((i + 1) % iStep) == 0) || (i == 0))
		{
			iPointNb = GetUintPointNb(i);
			strPointNb.Format("%d", iPointNb);

			oRect.left = i * iGridX - m_iGridXMin / 2;
			oRect.right = oRect.left + m_iGridXMax;
			oRect.top = -50;
			oRect.bottom = 0;

			pDC->DrawText(strPointNb, &oRect, DT_LEFT);
		}
	}
	pDC->SelectObject(pOldPen);
}

// ��ͼ�ε�Ԫ
void CGraphSensorList::DrawUnitAll(CDC* pDC, int iGridX, int iGridY, unsigned int uiTestType, unsigned int uiSensorNbSelest, CMap<unsigned int, unsigned int, unsigned int, unsigned int>& oSensorNbMap, float fSeismonitorLimit)
{
	int iUnitWidth;	// ͼ�ε�Ԫ���
	int iUnitHight;	// ͼ�ε�Ԫ�߶�
	int iUnitSizeMode;	// ͼ�ε�Ԫ�ߴ�ģʽ��1-��С��2-������3-���
	// �õ�ͼ�ε�Ԫ�ߴ�
	GetUnitSize(iGridX, iUnitWidth, iUnitHight, iUnitSizeMode);

	CGraphSensorData* pGraphSensorData = NULL;
	bool bDrawSensorNb;
	unsigned int uiSensorNb;
	for(unsigned int i = 0; i < m_uiCountUsed; i++)
	{
		// �õ�һ����ͼ��Ԫ
		pGraphSensorData = &m_pArrayGraphSensor[i];
		if((100 == uiSensorNbSelest) || (pGraphSensorData->m_pChannelSetupData->m_uiSensorNb == uiSensorNbSelest))
		{
			bDrawSensorNb = false;
			if(TRUE == oSensorNbMap.Lookup(pGraphSensorData->m_pChannelSetupData->m_uiSensorNb, uiSensorNb))
			{
				bDrawSensorNb = true;
			}
			pGraphSensorData->DrawUnit(pDC, iGridX, iGridY, iUnitWidth, iUnitHight, iUnitSizeMode, uiTestType, bDrawSensorNb, fSeismonitorLimit);
		}		
	}
}

// �õ�ͼ�ε�Ԫ�ߴ�
void CGraphSensorList::GetUnitSize(int iGridX, int &iUnitWidth, int &iUnitHight, int &iUnitSizeMode)
{
	if(iGridX < m_iSizeModeMin)	// ͼ�ε�Ԫ��С�ߴ�ģʽʱ�����޳ߴ�
	{
		iUnitSizeMode = 1;	// ͼ�ε�Ԫ�ߴ�ģʽ��1-��С��2-������3-���
		iUnitWidth = m_iUnitWidthMin;	// ͼ�ε�Ԫ��ȣ���С�ߴ�ģʽ
		iUnitHight = m_iUnitHightMin;	// ͼ�ε�Ԫ�߶ȣ���С�ߴ�ģʽ
	}
	else if(iGridX > m_iSizeModeMax)	// ͼ�ε�Ԫ���ߴ�ģʽʱ�����޳ߴ�
	{
		iUnitSizeMode = 3;	// ͼ�ε�Ԫ�ߴ�ģʽ��1-��С��2-������3-���
		iUnitWidth = m_iUnitWidthMax;	// ͼ�ε�Ԫ��ȣ���С�ߴ�ģʽ
		iUnitHight = m_iUnitHightMax;	// ͼ�ε�Ԫ�߶ȣ���С�ߴ�ģʽ
	}
	else
	{
		iUnitSizeMode = 2;	// ͼ�ε�Ԫ�ߴ�ģʽ��1-��С��2-������3-���
		iUnitWidth = m_iUnitWidthNormal;	// ͼ�ε�Ԫ��ȣ���С�ߴ�ģʽ
		iUnitHight = m_iUnitHightNormal;	// ͼ�ε�Ԫ�߶ȣ���С�ߴ�ģʽ
	}
}