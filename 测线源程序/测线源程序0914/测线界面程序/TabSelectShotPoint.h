#pragma once

#include "GridCtrlEdit.h"
#include "GridCtrlList.h"
#include "TabPage.h"
#include "SiteData.h"
/**
CTabSelectShotPoint Tab����ҳ�ڵ�ѡ��������
*/
class CTabSelectShotPoint : public CTabPage
{
	DECLARE_DYNAMIC(CTabSelectShotPoint)

public:
	CTabSelectShotPoint();
	virtual ~CTabSelectShotPoint();

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDestroy();
	afx_msg void OnGridCtrlListLButtonDown();	// ��굥���б�
	afx_msg void OnGridCtrlListDblClk();	// ��굥��˫���б�

public:	// ����
	/** ������*/
	CGridCtrlEdit m_oGridCtrlEdit;
	/** �б�*/
	CGridCtrlList m_oGridCtrlList;

	/** �����Ŷ���*/
	CList<int, int> m_olsNb;
	/** ������*/
	unsigned int m_uiTestNb;
	/** �ֳ�����*/
	CSiteData* m_pSiteData;

public:	// ����
	// ���ɱ༭����
	void OnCreateCtrl(LPCREATESTRUCT lpCreateStruct);
	// ����
	void OnReset(void);
};
