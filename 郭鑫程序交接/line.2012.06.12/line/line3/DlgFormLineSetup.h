#pragma once

#include "TabFormLine.h"

#include "SiteData.h"

/**
*@brief FormLine���öԻ�����
*/
class CDlgFormLineSetup : public CDialog
{
	DECLARE_DYNAMIC(CDlgFormLineSetup)

public:
	CDlgFormLineSetup(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgFormLineSetup();

// �Ի�������
	enum {IDD = 0};

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnClose();

public:	// ����
	/** �ֳ�����*/
	CSiteData* m_pSiteData;

	/** ����ҳ����*/
	CBCGPTabWnd m_oTabWnd;
	/** ����ҳ����*/
	CTabFormLine m_oTabFormLine;

public:	// ����
	afx_msg void OnBnClickedButtonApply();	
	afx_msg void OnBnClickedButtonReset();
	afx_msg void OnBnClickedButtonGO();
	afx_msg void OnBnClickedButtonAdd();
	afx_msg void OnBnClickedButtonChange();
	afx_msg void OnBnClickedButtonDelete();

	// ��Ӧ����ͼ����ͼ�����˵�FormLine����
	void OnGraphViewInstrumentFormLine(unsigned int uiInstrumentType, unsigned int uiSN);
};
