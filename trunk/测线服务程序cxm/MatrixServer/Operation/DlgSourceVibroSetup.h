#pragma once
#include "SetupGridCtrl.h"

// CDlgSourceVibroSetup �Ի���

class CDlgSourceVibroSetup : public CBCGPDialog
{
	DECLARE_DYNAMIC(CDlgSourceVibroSetup)

public:
	CDlgSourceVibroSetup(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgSourceVibroSetup();

// �Ի�������
	enum { IDD = IDD_DIALOG_SOURCEVIBRO };

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
