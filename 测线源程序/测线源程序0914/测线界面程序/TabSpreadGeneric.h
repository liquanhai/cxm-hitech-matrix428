#pragma once

#include "GridCtrlEdit.h"
#include "GridCtrlList.h"
#include "SiteData.h"
#include "TabPage.h"

/**
CTabSpreadGeneric Tab����ҳ��������������
*/
class CTabSpreadGeneric : public CTabPage
{
	DECLARE_DYNAMIC(CTabSpreadGeneric)

public:
	CTabSpreadGeneric();
	virtual ~CTabSpreadGeneric();

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
	/** ������*/
	CGridCtrlEdit m_oGridCtrlEdit;
	/** �б�*/
	CGridCtrlList m_oGridCtrlList;

	/** ����ҳ����*/
	CBCGPTabWnd m_oTabWnd;
	/** ���߱༭��*/
	CEdit m_oEditLine;
	/** ���б༭��*/
	CEdit m_oEditSpread;

	/** �����Ŷ���*/
	CList<int, int> m_olsNb;
	/** ������*/
	unsigned int m_uiTestNb;

public:	// ����
	// ���ɱ༭����
	void OnCreateCtrl(LPCREATESTRUCT lpCreateStruct);
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
};