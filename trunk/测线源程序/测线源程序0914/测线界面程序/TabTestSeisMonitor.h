#pragma once

#include "GridCtrlEdit.h"
#include "GridCtrlList.h"
#include "SiteData.h"
#include "TabPage.h"

/**
CTabTestSeisMonitor Tab����ҳ�첨������������
*/
class CTabTestSeisMonitor : public CTabPage
{
	DECLARE_DYNAMIC(CTabTestSeisMonitor)

public:
	CTabTestSeisMonitor();
	virtual ~CTabTestSeisMonitor();

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDestroy();

public:	// ����
	/** �ֳ�����*/
	CSiteData* m_pSiteData;
	/** �����������*/
	CButton m_oStaticAbsoluteSpread;
	/** �������б༭��*/
	CEdit m_oEditAbsoluteSpread;

public:	// ����
	// ���ɱ༭����
	void OnCreateCtrl(LPCREATESTRUCT lpCreateStruct);
	// ��ʼ��TestType��Ԫ��
	void InitTestTypeGridItem(CBCGPGridItem* pItem);
	// ��Ӧ��굥����ť��Apply
	bool OnBnClickedButtonApply();
	// ��Ӧ��굥����ť��Reset
	void OnBnClickedButtonReset();
	// ��Ӧ��굥����ť��GO
	bool OnBnClickedButtonGO();
	// ��Ӧ��굥����ť��Add
	void OnBnClickedButtonAdd();
	// ��Ӧ��굥����ť��Change
	void OnBnClickedButtonChange();
	// ��Ӧ��굥����ť��Delete
	void OnBnClickedButtonDelete();
	// ��Ӧ��굥����ť��Clear
	void OnBnClickedButtonClear();
};