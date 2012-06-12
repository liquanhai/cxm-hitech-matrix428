#pragma once

#include "TabTestInstrument.h"
#include "TabTestSensor.h"
#include "TabTestMultiple.h"
#include "TabTestSeisMonitor.h"

#include "SiteData.h"

/**
CDlgTestSetup Test���öԻ�����
*/
class CDlgTestSetup : public CDialog
{
	DECLARE_DYNAMIC(CDlgTestSetup)

public:
	CDlgTestSetup(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgTestSetup();

// �Ի�������
	enum {IDD = 0};

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnClose();

public:	// ����
	/** �ֳ�����*/
	CSiteData* m_pSiteData;

	/** ����ҳ����*/
	CBCGPTabWnd m_oTabWnd;
	/** ����ҳ������������*/
	CTabTestInstrument m_oTabTestInstrument;
	/** ����ҳ�첨����������*/
	CTabTestSensor m_oTabTestSensor;
	/** ����ҳ���ϲ�������*/
	CBCGPTabWnd m_oTabWndTestMultiple;
	/** ����ҳ���ϲ�������*/
	CTabTestMultiple* m_pTabTestMultiple;
	/** ����ҳ�����������*/
	CTabTestSeisMonitor m_oTabTestSeisMonitor;

public:	// ����
	afx_msg void OnBnClickedButtonApply();	
	afx_msg void OnBnClickedButtonReset();
	afx_msg void OnBnClickedButtonGO();
	afx_msg void OnBnClickedButtonAdd();
	afx_msg void OnBnClickedButtonChange();
	afx_msg void OnBnClickedButtonDelete();
	afx_msg void OnBnClickedButtonClear();
};
