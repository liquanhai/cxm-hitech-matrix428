// GridCtrlEdit.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "line.h"
#include "GridCtrlEdit.h"


// CGridCtrlEdit

IMPLEMENT_DYNAMIC(CGridCtrlEdit, CBCGPGridCtrl)

CGridCtrlEdit::CGridCtrlEdit()
{
	m_iRowHeightAdd = 0;	// �и��Ӹ߶�
}

CGridCtrlEdit::~CGridCtrlEdit()
{
}


BEGIN_MESSAGE_MAP(CGridCtrlEdit, CBCGPGridCtrl)
END_MESSAGE_MAP()

void CGridCtrlEdit::SetRowHeight()
{
	CBCGPGridCtrl::SetRowHeight();

	m_nRowHeight = m_nRowHeight + m_iRowHeightAdd;
	m_nLargeRowHeight = m_nRowHeight;
}

// CGridCtrlEdit ��Ϣ�������


