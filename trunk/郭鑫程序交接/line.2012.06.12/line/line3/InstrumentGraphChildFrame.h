#pragma once

#include "MainFrm.h"
#include "SiteData.h"

#include "GraphViewTopToolBarInstrument.h"
#include "GraphViewBottomToolBar.h"
#include "LeftViewBarInstrumentTop.h"
#include "LeftViewBarInstrumentBottom.h"
#include "ToolbarLabel.h"
#include "ToolbarGraph.h"
#include "ToolbarImage.h"

// CInstrumentGraphChildFrame ���

class CInstrumentGraphChildFrame : public CBCGPMDIChildWnd
{
	DECLARE_DYNCREATE(CInstrumentGraphChildFrame)
protected:
	CInstrumentGraphChildFrame();           // ��̬������ʹ�õ��ܱ����Ĺ��캯��
	virtual ~CInstrumentGraphChildFrame();

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg LRESULT OnToolbarReset(WPARAM,LPARAM);
	afx_msg void OnShowLineNbPointNb();
	afx_msg void OnShowLinkLine();
	afx_msg void OnShowInstrumentCross();
	afx_msg void OnShowInstrumentPower();
	afx_msg void OnShowInstrumentCollect();
	afx_msg void OnLook();
	afx_msg void OnSelectTestType();
	afx_msg void OnTestGo();
	afx_msg void OnZoomIn();
	afx_msg void OnZoomOut();
protected:

public:	// ����
	/** �ֳ����ݶ���*/
	//CSiteData*	m_pSiteData;
	matrix_data::data_base_helper* data_base_helper_;

	/**��������*/
	unsigned int m_uiTestType;
	/**��������*/
	CString m_strTestType;
	/**�Ƿ���ʾ��������*/
	bool m_bShowLineNbPointNb;
	/**�Ƿ���ʾ������*/
	bool m_bShowLinkLine;
	/**�Ƿ���ʾ����վ*/
	bool m_bShowInstrumentCross;
	/**�Ƿ���ʾ��Դվ*/
	bool m_bShowInstrumentPower;
	/**�Ƿ���ʾ�ɼ�վ*/
	bool m_bShowInstrumentCollect;

	CGraphViewTopToolBarInstrument m_oGraphViewTopToolBar;	// �Ϲ�����
	CGraphViewBottomToolBar m_oGraphViewBottomToolBar;	// �¹�����
	CLeftViewBarInstrumentTop m_oLeftViewBarInstrumentTop;	// �󵼺����ϲ�
	CLeftViewBarInstrumentBottom m_oLeftViewBarInstrumentBottom;	// �󵼺����²�

public:	// ����
	// ��ʼ��������ť��������������
	void InitButtonForTestTyperComboBox(CBCGPToolbarComboBoxButton* pComboButton);

	// ��ʾ��Ԫ�Ĳ��ߺźͲ���
	void OnShowUnitPosition(unsigned int uiNbLine, unsigned int uiNbPoint);
	// ��Ӧ�����ֲ��Ŵ�
	void OnZoomInNavigater(float fZoomRate, float fRateX, float fRateY);
	// ��Ӧ��ʾ����ֵ
	void OnShowProperty(unsigned int uiIndex);
	// ��Ӧ��ʾ�ػص�ͼ����ͼ
	void OnShowDetourGraphView(unsigned int uiCount);
	// ��Ӧ���ò�������
	void OnSetLineCount(unsigned int uiLineCount);
};


