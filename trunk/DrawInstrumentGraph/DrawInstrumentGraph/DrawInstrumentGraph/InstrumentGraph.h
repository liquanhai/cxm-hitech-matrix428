#pragma once


// CInstrumentGraph

class CInstrumentGraph : public CWnd
{
	DECLARE_DYNAMIC(CInstrumentGraph)

public:
	CInstrumentGraph();
	virtual ~CInstrumentGraph();

protected:
	DECLARE_MESSAGE_MAP()
public:
	CRect  m_rectClient;
	CBrush m_brushBack;

	CDC     m_dcGraph;
	CBitmap *m_pbitmapOldGrid;
	CBitmap m_bitmapGrid;
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	// ��������ͼ��
	void OnDrawInstrumentGraph(void);
	afx_msg void OnPaint();

	// ������������
	void DrawUnitAll(CDC* pDC, unsigned int uiGridX, unsigned int uiGridY, unsigned int uiGridLineX, unsigned int uiGridLineY);
	// ����������Ԫ�����������ߣ�
	void DrawUnit(CDC* pDC, unsigned int uiGridX, unsigned int uiGridY, unsigned int uiGridLineX, unsigned int uiGridLineY, 
		int iUnitIndex, int iLineNum, unsigned int uiLineDirection, unsigned int uiType);
private:
	// ��ʼ��������ʱX������
	int m_iPosX;
	// ��ʼ��������ʱY������
	int m_iPosY;
};


