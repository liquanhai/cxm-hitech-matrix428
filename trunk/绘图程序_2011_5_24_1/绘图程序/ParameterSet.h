#pragma once
#include "afxcmn.h"


// CParameterSet �Ի���

class CParameterSet : public CDialog
{
	DECLARE_DYNAMIC(CParameterSet)

public:
	CParameterSet(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CParameterSet();

// �Ի�������
	enum { IDD = IDD_DIALOG_PARAMETER };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonApply();
	afx_msg void OnBnClickedButtonSelectxmlpath();
	// Ŀ��IP��ַ
	CString m_csIPAddrAim;
	// ���Ͷ˿�
	CString m_csSendPort;
	// ���ն˿�
	CString m_csRcvPort;
	// ͼ����ʾ����
	CString m_csShowGraphType;
	// �����ļ�·��
	CString m_csXMLPath;
	// XMLDOM�ļ�����
	CXMLDOMDocument m_oXMLDOMDocument;
	// ͼ����ʾ�ķ���
	unsigned int m_uiShowDirection;
	// ���������ļ�
	void LoadXmlFile(void);
	// ���������ļ�
	void SaveXmlFile(void);
	// ��XML�����ļ�
	BOOL OpenXmlFile(void);
	// ѡ��XML�ļ�·��
	void OnSelectXMLPath(void);
	// �رճ��������ļ�
	void CloseXmlFile(void);
	// ����ͼ����ʾ����
	bool LoadGraphShowSetup(void);
	// ����ͼ����ʾ����
	bool SaveGraphShowSetup(void);
	// ����XML�ļ�·��
	bool SaveXmlFilePath(void);
};
