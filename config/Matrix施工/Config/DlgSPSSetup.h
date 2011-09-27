#pragma once
#include "FraseSPSToXML.h"

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
	CFraseSPSToXML m_oFraseSPSToXML;
public:
	afx_msg void OnBnClickedBtnloadsps();
private:
	// SPS_R�ļ�·��
	CString m_csSPSRFilePath;
	// SPS_X�ļ�·��
	CString m_csSPSXFilePath;
	// ����SPS_R�ļ�·��
	void OnSelectSPSRFilePath(void);
	// ����SPS_X�ļ�·��
	void OnSelectSPSXFilePath(void);
	// ����Ĭ��Operation XML·��
	CString m_csLocalOptXMLFile;
	// ����Ĭ��Line XML·��
	CString m_csLocalLineXMLFile;
	// ����Ĭ��LineInit TXT·��
	CString m_csLocalLineInitTXTFile;
	// ����ǰ·��
	wchar_t m_wcExeCurrentPath[MAX_PATH];
	// ����ʩ��XML
	void OnGenOptXML();
	// ���ɲ���XML
	void OnGenLineXML();
	// ���ɲ��߷��������ļ�
	void OnGenLineInitTXT();
};