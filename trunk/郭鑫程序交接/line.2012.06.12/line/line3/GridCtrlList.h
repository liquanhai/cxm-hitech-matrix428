#pragma once

// CGridCtrlList

class CGridCtrlList : public CBCGPGridCtrl
{
	DECLARE_DYNAMIC(CGridCtrlList)

public:
	CGridCtrlList();
	virtual ~CGridCtrlList();

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);

public:	// ����
	int m_iRowHeightAdd;	// �и��Ӹ߶�

public:	// ����
	virtual void SetRowHeight();
};


