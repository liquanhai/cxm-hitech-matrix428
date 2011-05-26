#pragma once

#include "TabSpreadAbsolute.h"
#include "TabSpreadGeneric.h"

#include "SiteData.h"

/**
CDlgSpreadSetup Spread���öԻ�����
*/
class CDlgSpreadSetup : public CDialog
{
	DECLARE_DYNAMIC(CDlgSpreadSetup)

public:
	CDlgSpreadSetup(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgSpreadSetup();

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
	CTabSpreadAbsolute m_oTabSpreadAbsolute;
	/** ����ҳ�첨����������*/
	CTabSpreadGeneric m_oTabSpreadGeneric;

public:	// ����
	afx_msg void OnBnClickedButtonApply();	
	afx_msg void OnBnClickedButtonReset();
	afx_msg void OnBnClickedButtonAdd();
	afx_msg void OnBnClickedButtonChange();
	afx_msg void OnBnClickedButtonDelete();
};
