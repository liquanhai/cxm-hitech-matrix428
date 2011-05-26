#pragma once

#include "GridCtrlEdit.h"
#include "GridCtrlList.h"
#include "SiteData.h"
#include "TabPage.h"

/**
CTabTestMultiple Tab����ҳ���ϲ���������
*/
class CTabTestMultiple : public CTabPage
{
	DECLARE_DYNAMIC(CTabTestMultiple)

public:
	CTabTestMultiple();
	virtual ~CTabTestMultiple();

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
	/** ͨ�����*/
	CButton m_oStaticCommonParam;
	/** ÿ�β���֮��ļ�������룩*/
	CStatic m_oStaticDelayBetweenTest;
	/** ÿ�β���֮��ļ�������룩*/
	CEdit m_oEditDelayBetweenTest;
	/** �Ƿ��¼��������*/
	CStatic m_oStaticRecordResult;
	/** �Ƿ��¼��������*/
	CButton m_oButtonRecordResult;
	/** ���Լ�¼ʱ�䣨���룩*/
	CStatic m_oStaticRecordLength;
	/** ���Լ�¼ʱ�䣨���룩*/
	CEdit m_oEditRecordLength;
	/** �����ļ���*/
	CStatic m_oStaticTestFileNb;
	/** �����ļ���*/
	CEdit m_oEditTestFileNb;

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