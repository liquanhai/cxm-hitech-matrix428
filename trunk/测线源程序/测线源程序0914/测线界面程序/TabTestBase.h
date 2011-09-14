#pragma once

#include "GridCtrlEdit.h"
#include "GridCtrlList.h"
#include "SiteData.h"
#include "TabPage.h"

/**
CTabTestBase Tab����ҳTestBase������
*/
class CTabTestBase : public CTabPage
{
	DECLARE_DYNAMIC(CTabTestBase)

public:
	CTabTestBase();
	virtual ~CTabTestBase();

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDestroy();
	afx_msg void OnGridCtrlListLButtonDown();	// ��굥���б�
	afx_msg void OnGridCtrlListDblClk();	// ��굥��˫���б�

public:	// ����
	/** �ֳ�����*/
	CSiteData* m_pSiteData;
	/** TestBase����*/
	CTestBaseData m_oTestBaseData;
	/** ������*/
	CGridCtrlEdit m_oGridCtrlEdit;
	/** �б�*/
	CGridCtrlList m_oGridCtrlList;
	/** �����Ŷ���*/
	CList<int, int> m_olsNb;

	/** ���Զ��� 1-������2-�첨��*/
	unsigned int m_uiAim;

public:	// ����
	// ���ɱ༭����
	void OnCreateCtrl(LPCREATESTRUCT lpCreateStruct);
	// ��ʼ��Gain��Ԫ��
	void InitGainGridItem(CBCGPGridItem* pItem);
	// ��ʼ��FilterType��Ԫ��
	void InitFilterTypeGridItem(CBCGPGridItem* pItem);
	// ��ʼ��ADCType��Ԫ��
	void InitADCTypeGridItem(CBCGPGridItem* pItem);
	// ��ʼ��DACType��Ԫ��
	void InitDACTypeGridItem(CBCGPGridItem* pItem);
	// ��Ӧ��굥����ť��Apply
	void OnBnClickedButtonApply();
	// ��Ӧ��굥����ť��Reset
	void OnBnClickedButtonReset();
	// ��Ӧ��굥����ť��Change
	void OnBnClickedButtonChange();
};