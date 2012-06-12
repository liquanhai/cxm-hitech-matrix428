#pragma once

#include "GridCtrlEdit.h"
#include "GridCtrlList.h"
#include "SiteData.h"
#include "TabPage.h"

/**
CTabTestInstrument Tab����ҳ��������������
*/
class CTabTestInstrument : public CTabPage
{
	DECLARE_DYNAMIC(CTabTestInstrument)

public:
	CTabTestInstrument();
	virtual ~CTabTestInstrument();

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
	/** ���������*/
	CButton m_oStaticAuxiliaryDescr;
	/** �����������*/
	CButton m_oStaticAbsoluteSpread;
	/** �������༭��*/
	CEdit m_oEditAuxiliaryDescr;
	/** �������б༭��*/
	CEdit m_oEditAbsoluteSpread;

	/** �����Ŷ���*/
	CList<int, int> m_olsNb;
	/** ������*/
	unsigned int m_uiTestNb;

public:	// ����
	// ���ɱ༭����
	void OnCreateCtrl(LPCREATESTRUCT lpCreateStruct);
	// ��ʼ��TestType��Ԫ��
	void InitTestTypeGridItem(CBCGPGridItem* pItem);
	// ��ʼ��Gain��Ԫ��
	void InitGainGridItem(CBCGPGridItem* pItem);
	// ��Ӧ��굥����ť��Apply
	void OnBnClickedButtonApply();
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