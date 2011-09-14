#pragma once

#include "MainFrm.h"
#include "SiteData.h"

/**
*@brief �첨����ͼ�������ͼ�²���
*/
class CLeftViewBarSensorBottom : public CBCGPDockingControlBar
{
	DECLARE_DYNAMIC(CLeftViewBarSensorBottom)

public:
	CLeftViewBarSensorBottom();
	virtual ~CLeftViewBarSensorBottom();

protected:
	//{{AFX_MSG(CLeftViewBarSensorBottom)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	afx_msg void OnPaint();
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:	// ����
	CSiteData*	m_pSiteData;	// �ֳ����ݶ���

	/** ���Ա�����*/
	CFont m_fntPropList;
	/** ���Ա�*/
	CBCGPPropList m_wndPropList;
	
public:	// ����
	// ��ʼ�����Ա�����
	void SetPropListFont();
	// ��ʼ�����Ա�
	void InitPropList();
	// ����
	void OnResetBar();
	// ��Ӧ��ʾ����ֵ
	void OnShowProperty(unsigned int uiIndex);
	// �õ����Խ������
	COleVariant GetTestResultString(byte byValue);
};


