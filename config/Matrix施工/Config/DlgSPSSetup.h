#pragma once


// DlgSPSSetup �Ի���
class CDlgSPSSetup : public CBCGPDialog
{
	DECLARE_DYNAMIC(CDlgSPSSetup)

public:
	CDlgSPSSetup(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgSPSSetup();

	// �Ի�������
	enum { IDD = IDD_SPSDLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedBtnloadsps();
	afx_msg void OnBnClickedBtngenoptxml();
	afx_msg void OnBnClickedBtngenlinexml();
};