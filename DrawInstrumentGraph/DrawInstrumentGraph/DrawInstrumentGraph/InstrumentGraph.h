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
	void DrawUnitAll(CDC* pDC);
	// ����������Ԫ�����������ߣ�
	void DrawUnit(CDC* pDC, int iUnitIndex, int iLineNum, unsigned int uiLineDirection, unsigned int uiType);
private:
	// ��ʼ��������ʱX������
	int m_iPosX;
	// ��ʼ��������ʱY������
	int m_iPosY;
	// ����ͼԪ�ṹ��
	typedef struct InstrumentGraph
	{
		// ������ͼ����
		CRect oRect;
		// ���
		int iUnitIndex;
		// ���ߺ�
		int iLineNum;
	}m_oInstrumentGraph;
	// �洢����ͼԪ��ͼ��
	CList <m_oInstrumentGraph, m_oInstrumentGraph> m_oInstrumentGraphRectList;
	// ����ƶ���¼��ʾ������
	CRect m_oRectMove;
public:
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
private:
	// �豸��ͼ��ԪX����ߴ�
	unsigned int m_uiGridX;
	// �豸Y�����ͼ�ߴ�
	unsigned int m_uiGridY;
	// ����X�����ͼ�ߴ�
	unsigned int m_uiGridLineX;
	// ����Y�����ͼ�ߴ�
	unsigned int m_uiGridLineY;
	// ��ʾ�������ߺź͵��
	BOOL m_bShowInstrumentLabel;
	// ��ʾ�������꣨�������ߺź͵�ţ�
	void OnShowInstrumentAxisPoint(CPoint point);
};


