// TestSiteManageDlg.h : ͷ�ļ�
//

#pragma once
#include "sitemanage.h"


// CTestSiteManageDlg �Ի���
class CTestSiteManageDlg : public CDialog
{
// ����
public:
	CTestSiteManageDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_TESTSITEMANAGE_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedBnOninit();
	afx_msg void OnBnClickedBnStart();
	afx_msg void OnBnClickedBnStop();
	afx_msg void OnBnClickedBnClose();

public: //����
	/** �ֳ��������*/
	CSiteManage m_oSiteManage;
	afx_msg void OnDestroy();
};
