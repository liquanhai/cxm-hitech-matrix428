#pragma once

#include "GridCtrlEdit.h"
#include "GridCtrlList.h"
#include "SiteData.h"
#include "TabPage.h"

/**
CTabBlastMachine Tab����ҳ��ը��������������
*/
class CTabBlastMachine : public CTabPage
{
	DECLARE_DYNAMIC(CTabBlastMachine)

public:
	CTabBlastMachine();
	virtual ~CTabBlastMachine();

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
	/** �����Ŷ���*/
	CList<int, int> m_olsNb;

public:	// ����
	// ���ɱ༭����
	void OnCreateCtrl(LPCREATESTRUCT lpCreateStruct);
	// ��ʼ��BoxType��Ԫ��
	void InitBoxTypeGridItem(CBCGPGridItem* pItem);
	// ��ʼ��Gain��Ԫ��
	void InitGainGridItem(CBCGPGridItem* pItem);
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
};