#pragma once

#include "SiteData.h"

/**
CDlgLookSetup Look���öԻ�����
*/
class CDlgLookSetup : public CDialog
{
	DECLARE_DYNAMIC(CDlgLookSetup)

public:
	CDlgLookSetup(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgLookSetup();

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

public:	// ����
	afx_msg void OnBnClickedButtonApply();
	afx_msg void OnBnClickedButtonReset();
};
