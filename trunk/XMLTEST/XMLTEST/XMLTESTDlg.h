// XMLTESTDlg.h : ͷ�ļ�
//

#pragma once
#include "afxwin.h"


// CXMLTESTDlg �Ի���
class CXMLTESTDlg : public CDialog
{
// ����
public:
	CXMLTESTDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_XMLTEST_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��
public:
	// XMLDOM�ļ�����
	CXMLDOMDocument m_oXMLDOMDocument;

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
	afx_msg void OnBnClickedButtonReadxml();

public:
	void OpenXMLFile(CString PathName);
	void CloseXMLFile();
	afx_msg void OnBnClickedButtonWritexml();
	// �༭��ؼ�
	CEdit m_EditXML;
};
