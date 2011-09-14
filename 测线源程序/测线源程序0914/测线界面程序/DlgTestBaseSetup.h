#pragma once

#include "TabTestBase.h"
#include "TabTestLimit.h"

#include "SiteData.h"

/**
CDlgTestBaseSetup TestBase���öԻ�����
*/
class CDlgTestBaseSetup : public CDialog
{
	DECLARE_DYNAMIC(CDlgTestBaseSetup)

public:
	CDlgTestBaseSetup(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgTestBaseSetup();

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
	/** ����ҳ���Ի������ã�����*/
	CTabTestBase m_oTabTestBaseInstrument;
	/** ����ҳ���Ի������ã��첨��*/
	CTabTestBase m_oTabTestBaseSensor;
	/** ����ҳ�����о����ã�����*/
	CTabTestLimit m_oTabTestLimitInstrument;
	/** ����ҳ�����о����ã��첨��*/
	CTabTestLimit m_oTabTestLimitSensor;

public:	// ����
	afx_msg void OnBnClickedButtonApply();	
	afx_msg void OnBnClickedButtonReset();
	afx_msg void OnBnClickedButtonChange();
};
