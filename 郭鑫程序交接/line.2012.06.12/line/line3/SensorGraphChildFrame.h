#pragma once

#include "MainFrm.h"
#include "SiteData.h"

#include "GraphViewTopToolBarSensor.h"
#include "GraphViewBottomToolBar.h"
#include "LeftViewBarSensorTop.h"
#include "LeftViewBarSensorBottom.h"
#include "ToolbarLabel.h"
#include "ToolbarGraph.h"
#include "ToolbarImage.h"
#include "ToolbarGraphButton.h"

// CSensorGraphChildFrame ���

class CSensorGraphChildFrame : public CBCGPMDIChildWnd
{
	DECLARE_DYNCREATE(CSensorGraphChildFrame)
protected:
	CSensorGraphChildFrame();           // ��̬������ʹ�õ��ܱ����Ĺ��캯��
	virtual ~CSensorGraphChildFrame();

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg LRESULT OnToolbarReset(WPARAM,LPARAM);	
	afx_msg void OnShowSensorNb(UINT nID);
	afx_msg void OnLook();
	afx_msg void OnSelectSensorNb();
	afx_msg void OnSelectTestType();
	afx_msg void OnTestGo();
	afx_msg void OnZoomIn();
	afx_msg void OnZoomOut();

public:	// ����
	/** �ֳ����ݶ���*/
//	CSiteData*	m_pSiteData;
	matrix_data::data_base_helper* data_base_helper_;

	/** �첨��Nb����*/
	unsigned int m_uiSensorNbCount;
	/** Ҫ��ʾ���Խ���ļ첨��Nb*/
	unsigned int m_uiSensorNb;

	CMap<unsigned int, unsigned int, unsigned int, unsigned int> m_oSensorNbMap;

	/**��������*/
	unsigned int m_uiTestType;
	/**��������*/
	CString m_strTestType;

	CGraphViewTopToolBarSensor m_oGraphViewTopToolBar;	// �Ϲ�����
	CGraphViewBottomToolBar m_oGraphViewBottomToolBar;	// �¹�����
	CLeftViewBarSensorTop m_oLeftViewBarSensorTop;	// �󵼺����ϲ�
	CLeftViewBarSensorBottom m_oLeftViewBarSensorBottom;	// �󵼺����²�

public:	// ����
	// ��ʼ��������ť��������������
	void InitButtonForTestTypeComboBox(CBCGPToolbarComboBoxButton* pComboButton);
	// ��ʼ�������򰴼첨��Nb������
	void InitButtonForSensorNbComboBox(CBCGPToolbarComboBoxButton* pComboButton);

	// ��ʾ��Ԫ�Ĳ��ߺźͲ���
	void OnShowUnitPosition(unsigned int uiNbLine, unsigned int uiNbPoint);
	// ��Ӧ�����ֲ��Ŵ�
	void OnZoomInNavigater(float fZoomRate, float fRateX, float fRateY);
	// ��Ӧ��ʾ����ֵ
	void OnShowProperty(matrix_data::data_base_helper::const_device_info& di);
	// ��Ӧ���ò�������
	void OnSetLineCount(unsigned int uiLineCount);
};


