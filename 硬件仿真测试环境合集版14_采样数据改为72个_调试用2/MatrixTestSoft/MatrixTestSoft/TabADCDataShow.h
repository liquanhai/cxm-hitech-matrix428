#pragma once

// CTabADCDataShow 对话框

class CTabADCDataShow : public CDialog
{
	DECLARE_DYNAMIC(CTabADCDataShow)

public:
	CTabADCDataShow(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CTabADCDataShow();

// 对话框数据
	enum { IDD = IDD_DIALOG_ADCDATASHOW };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnTimer(UINT_PTR nIDEvent);
public:
	// ADC数据界面显示缓冲区指针
	double* m_pADCDataShow;

};
