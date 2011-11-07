// OScopeCtrl.h : header file
//

#ifndef __OScopeCtrl_H__
#define __OScopeCtrl_H__

/////////////////////////////////////////////////////////////////////////////
// COScopeCtrl window

class COScopeCtrl : public CWnd
{
	// Construction
public:
	COScopeCtrl();

	// Attributes
public:
	void AppendPoint(double* dpNewPoint, UINT uiNewPointSize);
	void SetRange(double dLower, double dUpper, int nDecimalPlaces=1);
	void SetXUnits(CString string);
	void SetYUnits(CString string);
	void SetGridColor(COLORREF color);
	void SetPlotColor(COLORREF color);
	void SetBackgroundColor(COLORREF color);
	void InvalidateCtrl(bool bXMaxLableDefault);
	void DrawPoint(double dNewPoint, UINT uiDrawPointMove);
	  // vivi 2010.11.29
	// ���������ƣ�ͼ������
	void LeftDrawPoint(double* dSampleData, UINT uiLength, int iMathValueIdNum, UINT uiLeftDrawPointNum);
	// ���������ƣ�ͼ������
	void RightDrawPoint(double* dSampleData, UINT uiLength, int iMathValueIdNum, UINT uiRightDrawPointNum);

	void Reset(bool bXMaxLableDefault);
	void DrawPoint(double dNewPoint);

	// Operations
public:

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(COScopeCtrl)
public:
	virtual BOOL Create(DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID=NULL);
	//}}AFX_VIRTUAL

	// Implementation
public:
	int m_nShiftPixels;          // amount to shift with each new point 
	int m_nYDecimals;

	CString m_strXUnitsString;
	CString m_strYUnitsString;

	COLORREF m_crBackColor;        // background color
	COLORREF m_crGridColor;        // grid color
	COLORREF m_crPlotColor;        // data color  

	double m_dCurrentPosition;   // current position
	double m_dPreviousPosition;  // previous position

	// vivi 2010.11.29
	UINT m_uiXAxisLabelMin;	// X���ǩ����Сֵ
	UINT m_uiXAxisLabelMax;	// X���ǩ�����ֵ
	UINT m_uiXAxisPointNum;	// X���ͬʱ���ɵ�ĸ���
	UINT m_uiPointNum;			// �����˵ĵ�ĸ���
	CWnd* m_pParentWnd;	// ��ǰ���ھ��
	int m_iMousepointX;		// ����X���ֵ
	double m_dMousepointY;	// ����Y���ֵ

	virtual ~COScopeCtrl();

	// Generated message map functions
protected:
	//{{AFX_MSG(COScopeCtrl)
	afx_msg void OnPaint();
	afx_msg void OnSize(UINT nType, int cx, int cy); 
	// vivi 2010.11.29
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	int m_nHalfShiftPixels;
	int m_nPlotShiftPixels;
	int m_nClientHeight;
	int m_nClientWidth;
	int m_nPlotHeight;
	int m_nPlotWidth;

	double m_dLowerLimit;        // lower bounds
	double m_dUpperLimit;        // upper bounds
	double m_dRange;
	double m_dVerticalFactor;

	CRect  m_rectClient;
	CRect  m_rectPlot;
	CPen   m_penPlot;
	CBrush m_brushBack;

	CDC     m_dcGrid;
	CDC     m_dcPlot;
	CBitmap* m_pbitmapOldGrid;
	CBitmap* m_pbitmapOldPlot;
	CBitmap m_bitmapGrid;
	CBitmap m_bitmapPlot;

public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	// �Ŵ��϶�����ʼ������
	POINT m_pointStart;
	// ���������±�־λ��ΪTRUE=���������ΪFALSE=û�������
	BOOL m_bLButtonDown;
	// ����϶��Ľ���������
	POINT m_pointEnd;
	// �ж�����϶��Ի��ƾ��Σ�TRUE=���ƾ��Σ�FALSE=������
	BOOL m_bMouseDrag;
	// ����϶���ǰ������
	POINT m_pointMouseDragCur;
	// ��������϶��Ŵ���ο�
	void OnDrawMouseDragRect(CDC* pDC, POINT StartPoint, POINT EndPoint);
	// ����ֹͣ��־λָ��
	BOOL m_bStopSample;
	// ��ֹ������ѭ���������޷���Ӧ��Ϣ
	void ProcessMessages(void);
};

/////////////////////////////////////////////////////////////////////////////
#endif
