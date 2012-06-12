#include "stdafx.h"
#include "GraphInstrumentList.h"

CGraphInstrumentList::CGraphInstrumentList(void)
{
	m_pInstrumentList = NULL;	// ��������ָ��	

	m_pArrayGraphInstrument = NULL;	// ����ͼ�ε�Ԫ����ָ��	
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

	m_oRectArea.SetRectEmpty();	// ͼ����λ��
}

CGraphInstrumentList::~CGraphInstrumentList(void)
{
}

// ��ʼ��
void CGraphInstrumentList::OnInit()
{
	// ��������
	m_pArrayGraphInstrument = new CGraphInstrumentData[m_uiCountAll];
	for(unsigned int i = 0; i < m_uiCountAll; i++)
	{
		m_pArrayGraphInstrument[i].OnReset();
	}	
	m_uiCountUsed = 0;	// ʹ��������	
	m_uiCountFree = m_uiCountAll;	// ��������
}

// �ر�
void CGraphInstrumentList::OnClose()
{
	// ɾ���������
	delete[] m_pArrayGraphInstrument;
	m_oRectArea.SetRectEmpty();	// ͼ����λ��
}

// ����
void CGraphInstrumentList::OnReset()
{	
	m_uiCountUsed = 0;	// ʹ��������	
	m_uiCountFree = m_uiCountAll;	// ��������
	for(unsigned int i = 0; i < m_uiCountAll; i++)
	{
		// ����
		m_pArrayGraphInstrument[i].OnReset();
	}
	m_oGraphInstrumentMap.RemoveAll();	// ͼ�ε�Ԫ������
	m_olsRowLineNb.RemoveAll();	// ��Ԫ����-���ߺŶ�Ӧ�б�
	m_olsColumnPointNb.RemoveAll();	// ��Ԫ����-���Ŷ�Ӧ�б�

	m_uiRowCount = 0;	// ����
	m_uiColumnCount = 0;	// ����
	m_iPaperX = 0;	// ͼ����X����ߴ�
	m_iPaperY = 0;	// ͼ����Y����ߴ�
	m_iGridX = m_iGridXMin;	// ��Ԫ��X����ߴ�
	m_iGridY = m_iGridYMin;	// ��Ԫ��Y����ߴ�
	m_oRectArea.SetRectEmpty();	// ͼ����λ��
}

// ��������ͼ����ͼ����ͼ�ε�Ԫ����
void CGraphInstrumentList::LoadSiteData()
{
	m_uiCountUsed = m_pInstrumentList->m_uiCountUsed;	// ʹ��������
	unsigned int i;
	for(i = 0; i < m_uiCountAll; i++)
	{
		// ӳ���������鵽��Ԫ����
		if(true == m_pInstrumentList->m_pArrayInstrument[i].m_bInUsed)
		{
			m_pArrayGraphInstrument[i].m_bInUsed = true;	// ͼ�ε�Ԫ�Ƿ�ʹ����
			m_pArrayGraphInstrument[i].m_pInstrument = &m_pInstrumentList->m_pArrayInstrument[i];
		}
	}
	// ����������λ�ã��ݹ飻������վΪԭ��
	SetInstrumentPos(m_pInstrumentList->m_pFirstMainCross, 0);
	// �õ���Ҫ��ʾ�ĵ�Ԫ
	for(i = 0; i < m_uiCountAll; i++)
	{
		if(true == m_pInstrumentList->m_pArrayInstrument[i].m_bInUsed)	// ʹ����
		{
			// �����ػص������ǲɼ�վ
			if((false == m_pInstrumentList->m_pArrayInstrument[i].m_bDetour) || (1 == m_pInstrumentList->m_pArrayInstrument[i].m_uiInstrumentType) || (2 == m_pInstrumentList->m_pArrayInstrument[i].m_uiInstrumentType))
			{
				// ����ת��������ԭ����������վ�Ƶ��������Ͻ�
				m_pArrayGraphInstrument[i].m_iPosX = m_pArrayGraphInstrument[i].m_iPosX  - m_oRectArea.left;
				m_pArrayGraphInstrument[i].m_iPosY = m_pArrayGraphInstrument[i].m_iPosY  - m_oRectArea.top;
				// ��������
				m_pArrayGraphInstrument[i].m_iPosIndex = m_pArrayGraphInstrument[i].CreatePosIndex(m_pArrayGraphInstrument[i].m_iPosX, m_pArrayGraphInstrument[i].m_iPosY);
				// ����������
				m_oGraphInstrumentMap.SetAt(m_pArrayGraphInstrument[i].m_iPosIndex, &m_pArrayGraphInstrument[i]);
			}
		}
	}
	// ����ԭ���Ƶ��������Ͻ�
	m_oRectArea.right = m_oRectArea.right - m_oRectArea.left;
	m_oRectArea.bottom = m_oRectArea.bottom - m_oRectArea.top;
	m_oRectArea.left = 0;
	m_oRectArea.top = 0;

	// �õ�����������
	if((m_oRectArea.bottom > 0) || (m_oRectArea.right > 0))
	{
		m_uiRowCount = m_oRectArea.bottom + 1;	// ����
		m_uiColumnCount = m_oRectArea.right + 1;	// ����
	}
	if(1 == m_uiCountUsed)
	{
		m_uiRowCount = 1;	// ����
		m_uiColumnCount = 1;	// ����
	}
	
	// �õ���ͼ�����С
	if(m_uiColumnCount > 0)
	{
		m_iPaperX = (m_uiColumnCount - 1) * m_iGridX;	// X����ߴ�
	}
	if(m_uiRowCount > 0)
	{
		m_iPaperY = (m_uiRowCount - 1) * m_iGridY;	// Y����ߴ�
	}
	// ���õ�Ԫ��������Ͳ��߶�Ӧ��ϵ
	SetLineNbList();
	// ���õ�Ԫ��������Ͳ���Ӧ��ϵ
	SetPointNbList();
}

// �õ�ͼ�ε�Ԫ������ͼ�ε�Ԫ��������
CGraphInstrumentData* CGraphInstrumentList::GetGraphInstrumentDataByIndex(unsigned int uiIndex)
{
	return &m_pArrayGraphInstrument[uiIndex];
}

// �õ���������ָ�룬����ͼ�ε�Ԫ��������
CInstrument* CGraphInstrumentList::GetInstrumentByIndex(unsigned int uiIndex)
{
	CGraphInstrumentData* pGraphInstrumentData = GetGraphInstrumentDataByIndex(uiIndex);
	return pGraphInstrumentData->m_pInstrument;
}

// ����������λ�ã��ݹ�
void CGraphInstrumentList::SetInstrumentPos(CInstrument* pInstrument, unsigned int uiDirection)
{
	if(NULL == pInstrument)
	{
		return;
	}
	CGraphInstrumentData* pGraphInstrumentData = NULL;
	CGraphInstrumentData* pGraphInstrumentDataPreview = NULL;
	CInstrument* pInstrumentNext = NULL;
	pGraphInstrumentData = GetGraphInstrumentDataByIndex(pInstrument->m_uiIndex);
	// �жϷ���
	switch(uiDirection)
	{
	case 1:	// ��
		{
			pGraphInstrumentDataPreview = GetGraphInstrumentDataByIndex(pInstrument->m_iIndexCrossTop);
			pGraphInstrumentData->m_iPosY = pGraphInstrumentDataPreview->m_iPosY + 1;
			pGraphInstrumentData->m_iPosX = pGraphInstrumentDataPreview->m_iPosX;
			if(m_oRectArea.bottom < pGraphInstrumentData->m_iPosY)
			{
				m_oRectArea.bottom = pGraphInstrumentData->m_iPosY;
			}
			break;
		}
	case 2:	// ��
		{
			pGraphInstrumentDataPreview = GetGraphInstrumentDataByIndex(pInstrument->m_iIndexCrossDown);
			pGraphInstrumentData->m_iPosY = pGraphInstrumentDataPreview->m_iPosY - 1;
			pGraphInstrumentData->m_iPosX = pGraphInstrumentDataPreview->m_iPosX;
			if(m_oRectArea.top > pGraphInstrumentData->m_iPosY)
			{
				m_oRectArea.top = pGraphInstrumentData->m_iPosY;
			}
			break;
		}
	case 3:	// ��
		{
			if((false == pInstrument->m_bDetour) || (1 == pInstrument->m_uiInstrumentType) || (2 == pInstrument->m_uiInstrumentType))
			{
				pGraphInstrumentDataPreview = GetGraphInstrumentDataByIndex(pInstrument->m_iIndexInstrumentLeft);
				pGraphInstrumentData->m_iPosX = pGraphInstrumentDataPreview->m_iPosX + 1;
				pGraphInstrumentData->m_iPosY = pGraphInstrumentDataPreview->m_iPosY;
				if(m_oRectArea.right < pGraphInstrumentData->m_iPosX)
				{
					m_oRectArea.right = pGraphInstrumentData->m_iPosX;
				}
			}
			else if(true == pInstrument->m_bDetour)
			{
				pGraphInstrumentDataPreview = GetGraphInstrumentDataByIndex(pInstrument->m_iIndexInstrumentLeft);
				pGraphInstrumentData->m_iPosX = pGraphInstrumentDataPreview->m_iPosX;
				pGraphInstrumentData->m_iPosY = pGraphInstrumentDataPreview->m_iPosY;
				if(m_oRectArea.right < pGraphInstrumentData->m_iPosX)
				{
					m_oRectArea.right = pGraphInstrumentData->m_iPosX;
				}
			}
			break;
		}
	case 4:	// ��
		{
			if((false == pInstrument->m_bDetour) || (1 == pInstrument->m_uiInstrumentType) || (2 == pInstrument->m_uiInstrumentType))
			{
				pGraphInstrumentDataPreview = GetGraphInstrumentDataByIndex(pInstrument->m_iIndexInstrumentRight);
				pGraphInstrumentData->m_iPosX = pGraphInstrumentDataPreview->m_iPosX - 1;
				pGraphInstrumentData->m_iPosY = pGraphInstrumentDataPreview->m_iPosY;
				if(m_oRectArea.left > pGraphInstrumentData->m_iPosX)
				{
					m_oRectArea.left = pGraphInstrumentData->m_iPosX;
				}
			}
			else if(true == pInstrument->m_bDetour)
			{
				pGraphInstrumentDataPreview = GetGraphInstrumentDataByIndex(pInstrument->m_iIndexInstrumentRight);
				pGraphInstrumentData->m_iPosX = pGraphInstrumentDataPreview->m_iPosX;
				pGraphInstrumentData->m_iPosY = pGraphInstrumentDataPreview->m_iPosY;
				if(m_oRectArea.left > pGraphInstrumentData->m_iPosX)
				{
					m_oRectArea.left = pGraphInstrumentData->m_iPosX;
				}
			}
			break;
		}
	}

	// ����
	if((1 != uiDirection) && (-1 != pInstrument->m_iIndexCrossTop))	// ���������Ϸ��ģ�����������
	{
		pInstrumentNext = GetInstrumentByIndex(pInstrument->m_iIndexCrossTop);
		// �������ӵ�����
		SetInstrumentPos(pInstrumentNext, 2);
	}
	// ����
	if((2 != uiDirection) && (-1 != pInstrument->m_iIndexCrossDown))	// ���������·��ģ�����������
	{
		pInstrumentNext = GetInstrumentByIndex(pInstrument->m_iIndexCrossDown);
		// �������ӵ�����
		SetInstrumentPos(pInstrumentNext, 1);
	}
	// ����
	if((3 != uiDirection) && (-1 != pInstrument->m_iIndexInstrumentLeft))	// ���������󷽵ģ�����������
	{
		pInstrumentNext = GetInstrumentByIndex(pInstrument->m_iIndexInstrumentLeft);
		// �������ӵ�����
		SetInstrumentPos(pInstrumentNext, 4);
	}
	// ����
	if((4 != uiDirection) && (-1 != pInstrument->m_iIndexInstrumentRight))	// ���������ҷ��ģ�����������
	{
		pInstrumentNext = GetInstrumentByIndex(pInstrument->m_iIndexInstrumentRight);
		// �������ӵ�����
		SetInstrumentPos(pInstrumentNext, 3);
	}
}

// �õ�ͼ�ε�Ԫ������ͼ��������
CGraphInstrumentData* CGraphInstrumentList::GetGraphInstrumentDataByPosIndex(unsigned int uiPosX, unsigned int uiPosY)
{
	CGraphInstrumentData* pGraphInstrumentData = NULL;
	unsigned int uiPosIndex = CGraphInstrumentData::CreatePosIndex(uiPosX, uiPosY);

	if(TRUE == m_oGraphInstrumentMap.Lookup(uiPosIndex, pGraphInstrumentData))
	{
		return pGraphInstrumentData;		
	}	
	return NULL;
}

// �õ���������ָ�룬����ͼ��������
CInstrument* CGraphInstrumentList::GetInstrumentByPosIndex(unsigned int uiPosX, unsigned int uiPosY)
{
	CGraphInstrumentData* pGraphInstrumentData = GetGraphInstrumentDataByPosIndex(uiPosX, uiPosY);
	if(NULL != pGraphInstrumentData)
	{
		return pGraphInstrumentData->m_pInstrument;
	}
	return NULL;
}

// ���õ�Ԫ��������Ͳ��߶�Ӧ��ϵ
void CGraphInstrumentList::SetLineNbList()
{
	unsigned int i, j;
	unsigned int uiLineNb;
	CGraphInstrumentData* pGraphInstrumentData = NULL;
	for(i = 0; i < m_uiRowCount; i++)
	{
		m_olsRowLineNb.AddTail(-1);
		for(j = 0; j < m_uiColumnCount; j++)
		{
			pGraphInstrumentData = GetGraphInstrumentDataByPosIndex(j, i);
			if(NULL != pGraphInstrumentData)
			{
				if(0 != pGraphInstrumentData->m_pInstrument->m_uiLineNb)
				{
					uiLineNb = pGraphInstrumentData->m_pInstrument->m_uiLineNb;
					m_olsRowLineNb.RemoveTail();
					m_olsRowLineNb.AddTail(uiLineNb);
					break;
				}
			}
		}
	}
}

// ���õ�Ԫ��������Ͳ���Ӧ��ϵ
void CGraphInstrumentList::SetPointNbList()
{
	unsigned int i, j;
	unsigned int uiPointNb;
	CGraphInstrumentData* pGraphInstrumentData = NULL;
	for(i = 0; i < m_uiColumnCount; i++)
		{m_olsColumnPointNb.AddTail(-1);	
		for(j = 0; j < m_uiRowCount; j++)
		{
			pGraphInstrumentData = GetGraphInstrumentDataByPosIndex(i, j);
			if(NULL != pGraphInstrumentData)
			{
				if(0 != pGraphInstrumentData->m_pInstrument->m_uiLineNb)
				{
					uiPointNb = pGraphInstrumentData->m_pInstrument->m_uiPointNb;
					m_olsColumnPointNb.RemoveTail();
					m_olsColumnPointNb.AddTail(uiPointNb);
					break;
				}
			}
		}
	}
}

// �õ���������Ӧ�Ĳ��ߺ�
int CGraphInstrumentList::GetLineNbByRowIndex(unsigned int uiRowIndex)
{
	POSITION pos = m_olsRowLineNb.FindIndex(uiRowIndex);
	int iLineNb = m_olsRowLineNb.GetAt(pos);
	return iLineNb;
}

// �õ���������Ӧ�Ĳ���
int CGraphInstrumentList::GetPointNbByColumnIndex(unsigned int uiColumnIndex)
{
	POSITION pos = m_olsColumnPointNb.FindIndex(uiColumnIndex);
	int iPointNb = m_olsColumnPointNb.GetAt(pos);
	return iPointNb;
}

// ��ѡ������ת��Ϊ���������ַ���
CString CGraphInstrumentList::ConvertSelectAreaToAbsoluteSpreadString(CRect* pSelectAreaIndex)
{
	CString strAbsoluteSpread = "";
	CString strLine, strPoint;
	int iPointNb, iPointNbStart, iPointNbEnd;
	int iLineNb;
	CMap<int, int, CString, CString> oLineNbMap;

	for(int i = pSelectAreaIndex->top; i <= pSelectAreaIndex->bottom; i++)
	{
		// �õ�ͼ������������Ӧ�Ĳ��ߺ�
		iLineNb = GetLineNbByRowIndex(i);
		if(iLineNb > 0)	// ������Ч
		{
			iPointNbStart = GetPointNbByColumnIndex(pSelectAreaIndex->left);	// �õ���ʼ���
			iPointNbEnd = GetPointNbByColumnIndex(pSelectAreaIndex->right);	// �õ���ֹ���
			if((iPointNbStart > 0) && (iPointNbEnd > 0))	// �����Ч
			{
				if(iPointNbStart > iPointNbEnd)
				{
					iPointNb = iPointNbStart;
					iPointNbStart = iPointNbEnd;
					iPointNbEnd = iPointNb;
				}
				strPoint.Format("%d-%d", iPointNbStart, iPointNbEnd);	// ����ַ���
				strLine.Format("%d:%s;", iLineNb, strPoint);	// �����ַ���
				oLineNbMap.SetAt(iLineNb, strLine);	// ����������
			}
		}
	}
	POSITION pos = oLineNbMap.GetStartPosition();
	while(NULL != pos)
	{
		oLineNbMap.GetNextAssoc(pos, iLineNb, strLine);
		strAbsoluteSpread = strAbsoluteSpread + strLine;	// ���Ӳ����ַ���
	}
	if(strAbsoluteSpread.GetLength() > 0)
	{
		strAbsoluteSpread = strAbsoluteSpread.Left(strAbsoluteSpread.GetLength() - 1);	// ȥ�����һ���ַ���;��
	}
	oLineNbMap.RemoveAll();
	return strAbsoluteSpread;
}

// ������ͼ
void CGraphInstrumentList::DrawGrid(CDC* pDC, int iPaperX, int iPaperY, int iGridX, int iGridY)
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
void CGraphInstrumentList::DrawMarkLineNbAndPointNb(CDC* pDC, int iGridX, int iGridY)
{
	// �����߱��
	DrawMarkLineNb(pDC, iGridY);
	// �������
	DrawMarkPointNb(pDC, iGridX);
}

// �����߱�ߺͲ����
void CGraphInstrumentList::DrawMarkLineNb(CDC* pDC, int iGridY)
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
		iLineNb = GetLineNbByRowIndex(i);
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
void CGraphInstrumentList::DrawMarkPointNb(CDC* pDC, int iGridX)
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
			iPointNb = GetPointNbByColumnIndex(i);
			strPointNb.Format("%d", iPointNb);

			oRect.left = i * iGridX - m_iGridXMin / 2;
			oRect.right = oRect.left + m_iGridXMax;
			oRect.top = -50;
			oRect.bottom = 0;
		}

		pDC->DrawText(strPointNb, &oRect, DT_LEFT);

	}
	pDC->SelectObject(pOldPen);
}

// ��ͼ�ε�Ԫ������
void CGraphInstrumentList::DrawUnitLinkLineAll(CDC* pDC, int iGridX, int iGridY)
{
	POSITION pos = m_oGraphInstrumentMap.GetStartPosition();
	CGraphInstrumentData* pGraphInstrumentData = NULL;
	unsigned int uiPosIndex;	// ����λ������
	while(NULL != pos)
	{
		// �õ�һ����ͼ��Ԫ
		m_oGraphInstrumentMap.GetNextAssoc(pos, uiPosIndex, pGraphInstrumentData);
		pGraphInstrumentData->DrawUnitLinkLine(pDC, iGridX, iGridY);
	}
}

// ��ͼ�ε�Ԫ
void CGraphInstrumentList::DrawUnitAll(CDC* pDC, int iGridX, int iGridY, unsigned int uiTestType, bool bShowCross, bool bShowPower, bool bShowCollect)
{
	int iUnitWidth;	// ͼ�ε�Ԫ���
	int iUnitHight;	// ͼ�ε�Ԫ�߶�
	int iUnitSizeMode;	// ͼ�ε�Ԫ�ߴ�ģʽ��1-��С��2-������3-���
	// �õ�ͼ�ε�Ԫ�ߴ�
	GetUnitSize(iGridX, iUnitWidth, iUnitHight, iUnitSizeMode);

	POSITION pos = m_oGraphInstrumentMap.GetStartPosition();
	CGraphInstrumentData* pGraphInstrumentData = NULL;
	unsigned int uiPosIndex;	// ����λ������
	while(NULL != pos)
	{
		// �õ�һ����ͼ��Ԫ
		m_oGraphInstrumentMap.GetNextAssoc(pos, uiPosIndex, pGraphInstrumentData);
		if((pGraphInstrumentData->m_pInstrument->m_uiInstrumentType == 1) && (bShowCross == true))
		{
			pGraphInstrumentData->DrawUnit(pDC, iGridX, iGridY, iUnitWidth, iUnitHight, iUnitSizeMode, uiTestType);
		}
		else if((pGraphInstrumentData->m_pInstrument->m_uiInstrumentType == 2) && (bShowPower == true))
		{
			pGraphInstrumentData->DrawUnit(pDC, iGridX, iGridY, iUnitWidth, iUnitHight, iUnitSizeMode, uiTestType);
		}
		else if((pGraphInstrumentData->m_pInstrument->m_uiInstrumentType == 3) && (bShowCollect == true))
		{
			pGraphInstrumentData->DrawUnit(pDC, iGridX, iGridY, iUnitWidth, iUnitHight, iUnitSizeMode, uiTestType);
		}
	}
}

// �õ�ͼ�ε�Ԫ�ߴ�
void CGraphInstrumentList::GetUnitSize(int iGridX, int &iUnitWidth, int &iUnitHight, int &iUnitSizeMode)
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

