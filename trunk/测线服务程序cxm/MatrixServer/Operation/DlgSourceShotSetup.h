#pragma once
#include "SetupGridCtrl.h"

// CDlgSourceShotSetup �Ի���

class CDlgSourceShotSetup : public CBCGPDialog
{
	DECLARE_DYNAMIC(CDlgSourceShotSetup)

public:
	CDlgSourceShotSetup(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgSourceShotSetup();

// �Ի�������
	enum { IDD = IDD_DIALOG_SOURCESHOTSETUP };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CGridCtrlList		m_wndListGrid;
	CGridCtrlEdit		m_wndEditGrid;
public:
	afx_msg void OnBnClickedButtonAdd();
	afx_msg void OnBnClickedButtonChange();
	afx_msg void OnBnClickedButtonDelete();
	afx_msg void OnBnClickedButtonReverse();
	afx_msg void OnBnClickedButtonApply();
	afx_msg void OnBnClickedButtonReset();
	virtual BOOL OnInitDialog();
	afx_msg void OnDestroy();
};
