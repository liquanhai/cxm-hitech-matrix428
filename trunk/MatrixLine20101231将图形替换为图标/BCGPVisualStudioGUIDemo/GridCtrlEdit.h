#pragma once


// CGridCtrlEdit

class CGridCtrlEdit : public CBCGPGridCtrl
{
	DECLARE_DYNAMIC(CGridCtrlEdit)

public:
	CGridCtrlEdit();
	virtual ~CGridCtrlEdit();

protected:
	DECLARE_MESSAGE_MAP()

public:	// ����
	int m_iRowHeightAdd;	// �и��Ӹ߶�

public:	// ����
	virtual void SetRowHeight();
};


