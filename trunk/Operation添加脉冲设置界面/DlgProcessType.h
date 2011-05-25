#pragma once
#include "afxwin.h"
#include "DlgImpulsive.h"
#include "DlgStackImpulsive.h"

// CDlgProcessType �Ի���
// vivi 2010.11.8

class CDlgProcessType : public CBCGPDialog
{
	DECLARE_DYNAMIC(CDlgProcessType)

public:
	CDlgProcessType(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgProcessType();

// �Ի�������
	enum { IDD = IDD_PROCESSSETUPDLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	BOOL OnInitDialog(void);
	// �ؼ�IDC_COMBO_PROCESSTYPESELECT�Ŀ��Ʊ���
	int m_cbindexProcessType;

	afx_msg void OnCbnSelchangeProcessType();
	
	void OnShowWindow(BOOL bShow, UINT nStatus);
	CDlgImpulsive m_dlgImpulsive;
	CDlgStackImpulsive m_dlgStackImpulsive;
	int m_radioProcessSetup;
	afx_msg void OnBnClickedRadioStandard();
	afx_msg void OnBnClickedRadioAdvanced();
};
