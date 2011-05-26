#pragma once

#include "GridCtrlEdit.h"
#include "GridCtrlList.h"
#include "SiteData.h"
#include "TabPage.h"

/**
CTabTestLimit Tab����ҳTestLimit������
*/
class CTabTestLimit : public CTabPage
{
	DECLARE_DYNAMIC(CTabTestLimit)

public:
	CTabTestLimit();
	virtual ~CTabTestLimit();

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
	/** TestLimit����*/
	CTestLimitData m_oTestLimitData;
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
	// ��Ӧ��굥����ť��Apply
	void OnBnClickedButtonApply();
	// ��Ӧ��굥����ť��Reset
	void OnBnClickedButtonReset();
	// ��Ӧ��굥����ť��Change
	void OnBnClickedButtonChange();
};