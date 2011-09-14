#pragma once

#include "GridCtrlEdit.h"
#include "GridCtrlList.h"
#include "SiteData.h"
#include "TabPage.h"

/**
CTabDetour Tab����ҳ�ػص�������
*/
class CTabDetour : public CTabPage
{
	DECLARE_DYNAMIC(CTabDetour)

public:
	CTabDetour();
	virtual ~CTabDetour();

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDestroy();
	// ��굥���б�
	afx_msg void OnGridCtrlListLButtonDown();
	// ��굥��˫���б�
	afx_msg void OnGridCtrlListDblClk();

public:	// ����
	/** �ֳ�����*/
	CSiteData* m_pSiteData;
	/** ������*/
	CGridCtrlEdit m_oGridCtrlEdit;
	/** �б�*/
	CGridCtrlList m_oGridCtrlList;

public:	// ����
	// ���ɱ༭����
	void OnCreateCtrl(LPCREATESTRUCT lpCreateStruct);
	// ��ʼ��BoxType��Ԫ��
	void InitBoxTypeGridItem(CBCGPGridItem* pItem);

	// ��Ӧ��굥����ť��Apply
	void OnBnClickedButtonApply();
	// ��Ӧ��굥����ť��Reset
	void OnBnClickedButtonReset();
	// ��Ӧ��굥����ť��Add
	void OnBnClickedButtonAdd();
	// ��Ӧ��굥����ť��Change
	void OnBnClickedButtonChange();
	// ��Ӧ��굥����ť��Delete
	void OnBnClickedButtonDelete();
	// ��Ӧ��굥����ť��Clear
	void OnBnClickedButtonClear();
	// ��Ӧ����ͼ����ͼ�����˵������ػص�
	void OnGraphViewInstrumentSetDetour(unsigned int uiInstrumentTypeLow, unsigned int uiSNLow, unsigned int uiInstrumentTypeHigh, unsigned int uiSNHight);
};