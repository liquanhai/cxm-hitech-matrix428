#pragma once


// CDlgDiskRecord �Ի���
#include "..\common\ConfigParseXML.h"
#include "afxwin.h"
class CDlgDiskRecord : public CBCGPDialog
{
	DECLARE_DYNAMIC(CDlgDiskRecord)

public:
	CDlgDiskRecord(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgDiskRecord();

// �Ի�������
	enum { IDD = IDD_DISKRECORD };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	// Standard����Advanceģʽ
	int m_nDiskRecordMode;
	int m_nBackupSettings;
	
	CBCGPEdit m_ctrlFilePath;
	CString m_strFilePath;
	CString m_strNormalPath;
	CString m_strTestPath;
public:
	void SetParams(CDiskRecordConfig* pDiskRecord);
	void ApplyParams(CDiskRecordConfig* pDiskRecord);
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedBtnok();
	afx_msg void OnBnClickedBtnapply();
	afx_msg void OnBnClickedBtnreset();
	afx_msg void OnBnClickedRadioflat();
	afx_msg void OnBnClickedRadioday();
};
