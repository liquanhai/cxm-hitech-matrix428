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
	// �ͻ����ߴ�
	CRect  m_rectClient;
	// ����ˢ��
	CBrush m_brushBack;
	CBitmap* m_pbitmapOldGrid;
	// ����ָ��
	CWnd* m_pWnd;
	// ����ͼԪ�ṹ��
	typedef struct InstrumentGraph
	{
		// ������ͼ����
		CRect oRect;
		// ���
		int iUnitIndex;
		// ���ߺ�
		int iLineIndex;
		// �ɼ�վ���
		unsigned int uiFDUIndex;
		// SN��
		unsigned int uiSN;
		// �����߷���
		unsigned int uiLineDirection;
		// ��������
		unsigned int uiType;
		// ��������
		unsigned int uiOpt;
		bool operator == (const InstrumentGraph& v2) const
		{
			return ((iUnitIndex == v2.iUnitIndex)
				&& (iLineIndex == v2.iLineIndex));
		}
	}m_oGraph;
	// �洢����ͼԪ��ͼ��
	CList <m_oGraph, m_oGraph> m_oInstrumentGraphRectList;
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnPaint();

	// ������������
	void DrawUnitAll(void);
	// ����������Ԫ�����������ߣ�
	void DrawUnit(int iUnitIndex, int iLineIndex, unsigned int uiLineDirection, unsigned int uiType, 
		unsigned int uiSN, unsigned int uiOpt, bool bSet);
private:
	CDC m_dcGraph;
	// ��ͼ���ߴ�
	CRect m_rectGraph;
	// ���������CWndָ��
	CWnd* m_pWndVScr;
	// ���������CWndָ��
	CWnd* m_pWndHScr;
	//����һ��λͼ����
	CBitmap m_oBmpFDU1;
	//����һ��λͼ����
	CBitmap m_oBmpFDU2;
	//����һ��λͼ����
	CBitmap m_oBmpLAUL1;
	//����һ��λͼ����
	CBitmap m_oBmpLAUL2;
	//����һ��λͼ����
	CBitmap m_oBmpLAUX1;
	//����һ��λͼ����
	CBitmap m_oBmpLAUX2;
	//����һ��λͼ����
	CBitmap m_oBmpLCI1;
	//����һ��λͼ����
	CBitmap m_oBmpLCI2;
public:
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
private:
	// �豸��ͼ��ԪX����ߴ�
	unsigned int m_uiGridX;
	// �豸Y�����ͼ�ߴ�
	unsigned int m_uiGridY;
	// ����X�����ͼ�ߴ�
	unsigned int m_uiGridLineX;
	// ����Y�����ͼ�ߴ�
	unsigned int m_uiGridLineY;
	// �жϽ��������Ƿ�ѡ��
	BOOL OnSelectInstrument(CPoint oGraphPoint, m_oGraph &oInstrumentGraph);
	// �������϶�
	int moveScrollBar(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	// ����Ϣ��ʾ�������Ϊ����ɫ
	void OnFillMsgAreaBkColor(void);
public:
	// ��䱳����ɫ
	void OnFillBkColor(CDC* pDC, CRect oRect);
	// �����������ͼ��
	void OnClearAllInstrumentGraph(void);
private:
	// ������Ϣ
	int m_iPosShowInterval;
	// ������������
	int m_iVScrBarInterval;
	// ������������
	int m_iHScrBarInterval;
	// ������վ������ʼλ��X������
	int m_iLauxPosX;
	// ������վ������ʼλ��Y������
	int m_iLauxPosY;
public:
	// �Ҳ����������ƶ�ͼ��DC�Ĵ�С
	int m_iRightMovePos;
	// ������������ƶ�ͼ��DC�Ĵ�С
	int m_iLeftMovePos;
	// �����ͼ����
	void OnOptGraphRect(unsigned int uiOpt);
	// ��ͼ�ν��������������Ϣ
	void OnShowTextOut(CDC* pDC, CPoint point, CString str);
private:
	// �������������
	int m_iHScrPos;
public:
	// ����
	void OnReset(void);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	// ������ɼ�վ��ź�����ڽ������ѡ������
	bool m_bLButtonSelect;
	// ��������ͼ��
	void OnLoadInstrumentBmp(CBitmap* pBmp, int iBmpX, int iBmpY);
};