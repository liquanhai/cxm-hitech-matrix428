#pragma once

#include "MainFrm.h"
#include "SiteData.h"

#include "GraphViewTopToolBarSeismonitor.h"
#include "GraphViewBottomToolBar.h"
#include "LeftViewBarSeismonitorTop.h"
#include "LeftViewBarSensorBottom.h"
#include "ToolbarLabel.h"
#include "ToolbarGraph.h"
#include "ToolbarImage.h"
#include "ToolbarGraphButton.h"
#include "BCGPSliderButton.h"

// CSeismonitorGraphChildFrame ���

class CSeismonitorGraphChildFrame : public CBCGPMDIChildWnd
{
	DECLARE_DYNCREATE(CSeismonitorGraphChildFrame)
protected:
	CSeismonitorGraphChildFrame();           // ��̬������ʹ�õ��ܱ����Ĺ��캯��
	virtual ~CSeismonitorGraphChildFrame();

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg LRESULT OnToolbarReset(WPARAM,LPARAM);	
	afx_msg void OnShowSensorNb(UINT nID);
	afx_msg void OnSelectSensorNb();
	afx_msg void OnSliderTestLimit();
	afx_msg void OnTestSeismonitor();
	afx_msg void OnZoomIn();
	afx_msg void OnZoomOut();

	afx_msg void OnUpdateUITestSeismonitor(CCmdUI* pCmdUI);

public:	// ����
	/** �ֳ����ݶ���*/
	CSiteData*	m_pSiteData;

	/** �첨��Nb����*/
	unsigned int m_uiSensorNbCount;
	/** Ҫ��ʾ���Խ���ļ첨��Nb*/
	unsigned int m_uiSensorNb;

	CMap<unsigned int, unsigned int, unsigned int, unsigned int> m_oSensorNbMap;

	/**��������*/
	unsigned int m_uiTestType;
	/**��������о�*/
	float m_fSeismonitorLimit;
	/**��������о�*/
	CString m_strSeismonitorLimitA;
	/**��������о�*/
	CString m_strSeismonitorLimitB;
	/** Ұ������������ 1-�������ԣ�0-ֹͣ����*/
	byte m_byTestOperation;

	CGraphViewTopToolBarSeismonitor m_oGraphViewTopToolBar;	// �Ϲ�����
	CGraphViewBottomToolBar m_oGraphViewBottomToolBar;	// �¹�����
	CLeftViewBarSeismonitorTop m_oLeftViewBarSeismonitorTop;	// �󵼺����ϲ�
	CLeftViewBarSensorBottom m_oLeftViewBarSensorBottom;	// �󵼺����²�

public:	// ����
	// ��ʼ�������򰴼첨��Nb������
	void InitButtonForSensorNbComboBox(CBCGPToolbarComboBoxButton* pComboButton);

	// ��ʾ��Ԫ�Ĳ��ߺźͲ���
	void OnShowUnitPosition(unsigned int uiNbLine, unsigned int uiNbPoint);
	// ��Ӧ�����ֲ��Ŵ�
	void OnZoomInNavigater(float fZoomRate, float fRateX, float fRateY);
	// ��Ӧ��ʾ����ֵ
	void OnShowProperty(unsigned int uiIndex);
	// ��Ӧ���ò�������
	void OnSetLineCount(unsigned int uiLineCount);
	// �õ���������о��ַ���
	void SetSeismonitorLimitString();
};


