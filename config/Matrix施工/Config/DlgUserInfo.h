#pragma once


// CDlgUserInfo �Ի���
#include "..\common\ConfigParseXML.h"
class CDlgUserInfo : public CBCGPDialog
{
	DECLARE_DYNAMIC(CDlgUserInfo)

public:
	CDlgUserInfo(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgUserInfo();

// �Ի�������
	enum { IDD = IDD_USERINFODLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	// �û���Ϣ
	CString m_strUserInfo;
	afx_msg void OnBnClickedBtnok();
	afx_msg void OnBnClickedBtnapply();
	afx_msg void OnBnClickedBtnreset();
	virtual BOOL OnInitDialog();
};
