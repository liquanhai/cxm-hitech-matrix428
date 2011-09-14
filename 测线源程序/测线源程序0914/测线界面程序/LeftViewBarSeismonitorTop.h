#pragma once

/**
*@brief �첨����ͼ�������ͼ�ϲ���
*/
class CLeftViewBarSeismonitorTop : public CBCGPDockingControlBar
{
	DECLARE_DYNAMIC(CLeftViewBarSeismonitorTop)

public:
	CLeftViewBarSeismonitorTop();
	virtual ~CLeftViewBarSeismonitorTop();

protected:
	//{{AFX_MSG(CLeftViewBarSeismonitorTop)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	afx_msg void OnPaint();
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:	// ����

public:	// ����
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);

public: // ����
	/** ��ͼ����X*/
	CRect m_oRect;

	/** ��������ʱ����*/
	CPoint m_oPointBase;
	/** �����ͷ�ʱ����*/
	CPoint m_oPointLast;
	/** ����ѡ������λ�ã���λ����*/
	CRect m_oSelectArea;

	/** �������Ƿ���*/
	bool m_bMouseDownLeft;
	/** �Ƿ����ѡ������λ��*/
	bool m_bDrawSelectArea;

	/** �Ŵ���*/
	float m_fZoomRate;
	/** ��׼��X*/
	float m_fRateX;
	/** ��׼��Y*/
	float m_fRateY;


	/** ��Ԫ��Y����ߴ�*/
	int m_iGridY;
	/** ��Ԫ��Y����ߴ����ֵ*/
	int m_iGridYMax;
	/** ���߸߶�*/
	int m_iLineHight;
	/** ͼ����X����Ԥ���ߴ�*/
	int m_iPaperHeadX;
	/** ͼ�������Ԥ���ߴ�*/
	int m_iPaperHeadTop;
	/** �Ƿ���Ի�ͼ*/
	bool m_bCanDrawGraph;

	/** ��������*/
	unsigned int m_uiLineCount;

public: // ����
	// �����ֲ��Ŵ�
	void OnZoomInNavigater();
	// ��Ӧ���ò�������
	void OnSetLineCount(unsigned int uiLineCount);

	// �õ�ѡ�е�����
	bool GetSelectAreaPoint();
	// �жϵ�ǰͼ�δ�С�Ƿ���Ի�ͼ
	bool CheckIfCanDraw();

	// ������
	void DrawBackground(CDC* pDC);
	// �����ѡ������
	void DrawSelectArea(CDC* pDC);
	// ������
	void DrawLines(CDC* pDC);
};


