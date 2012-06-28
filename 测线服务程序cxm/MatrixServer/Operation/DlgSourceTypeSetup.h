#pragma once
#include "DlgSourceExploSetup.h"
#include "DlgSourceVibroSetup.h"
// CDlgSourceTypeSetup �Ի���

class CDlgSourceTypeSetup : public CBCGPDialog
{
	DECLARE_DYNAMIC(CDlgSourceTypeSetup)

public:
	CDlgSourceTypeSetup(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgSourceTypeSetup();

// �Ի�������
	enum { IDD = IDD_DIALOG_SOURCESETUP };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CBCGPTabWnd		m_wndTab;
	CDlgSourceExploSetup	m_DlgExplo;
	CDlgSourceVibroSetup	m_DlgVibro;
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedButtonApply();
	afx_msg void OnBnClickedButtonReset();
};
