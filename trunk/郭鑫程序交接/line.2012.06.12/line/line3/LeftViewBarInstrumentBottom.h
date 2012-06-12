#pragma once

#include "MainFrm.h"
#include "WndInstrument.h"

/**
*@brief ������ͼ�������ͼ�²���
*/
class CLeftViewBarInstrumentBottom : public CMyBCGPDockingControlBar
{
	DECLARE_DYNAMIC(CLeftViewBarInstrumentBottom)

public:
	CLeftViewBarInstrumentBottom();
	virtual ~CLeftViewBarInstrumentBottom();

protected:
	//{{AFX_MSG(CLeftViewBarInstrumentBottom)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	afx_msg void OnPaint();
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:	// ����
	/** ���Ա�����*/
	CFont m_fntPropList;
	/** ���Ա�*/
	CBCGPPropList m_wndPropList;
	/** �ػص�ͼ����ͼ*/
	CWndInstrument m_wndDetourGraphView;
	/** �ػص�ͼ����ͼ������*/
	CScrollBar m_wndDetourScrollBar;
	
public:	// ����
	// ��ʼ�����Ա�����
	void SetPropListFont();
	// ��ʼ�����Ա�
	void InitPropList();
	// ����
	void OnResetBar();
	// ��Ӧ��ʾ����ֵ
	void OnShowProperty(matrix_data::data_base_helper::device_info& di);
	// ��Ӧ��ʾ�ػص�ͼ����ͼ
	void OnShowDetourGraphView(unsigned int uiCount);
	// �õ�������֣������߼�ֵ
	COleVariant GetMarkerStringByLogic(bool bValue);
};


