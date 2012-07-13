#pragma once
#include "SetupGridCtrl.h"

// CDlgCommentTypeSetup �Ի���

class CDlgCommentTypeSetup : public CBCGPDialog
{
	DECLARE_DYNAMIC(CDlgCommentTypeSetup)

public:
	CDlgCommentTypeSetup(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgCommentTypeSetup();

// �Ի�������
	enum { IDD = IDD_DIALOG_COMMENTSETUP };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CGridCtrlList		m_wndListGrid;
	CGridCtrlEdit		m_wndEditGrid;
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnDestroy();
	afx_msg void OnBnClickedButtonAdd();
	afx_msg void OnBnClickedButtonChange();
	afx_msg void OnBnClickedButtonDelete();
	afx_msg void OnBnClickedButtonApply();
	afx_msg void OnBnClickedButtonReset();
};
