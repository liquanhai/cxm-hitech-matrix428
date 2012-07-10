#pragma once
#include "SetupGridCtrl.h"

// CDlgSourceExploSetup �Ի���

class CDlgSourceExploSetup : public CBCGPDialog
{
	DECLARE_DYNAMIC(CDlgSourceExploSetup)

public:
	CDlgSourceExploSetup(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgSourceExploSetup();

// �Ի�������
	enum { IDD = IDD_DIALOG_SOURCEEXPLO };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CGridCtrlList		m_wndListGrid;
	CGridCtrlEdit		m_wndEditGrid;
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedButtonAdd();
	afx_msg void OnBnClickedButtonChange();
	afx_msg void OnBnClickedButtonDelete();
	afx_msg void OnDestroy();
};
