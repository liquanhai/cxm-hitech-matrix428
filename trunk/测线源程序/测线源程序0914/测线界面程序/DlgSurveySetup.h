#pragma once

#include "TabSurvey.h"
#include "TabPointCode.h"
#include "TabSensor.h"

#include "SiteData.h"

/**
CDlgSurveySetup �������öԻ�����
*/
class CDlgSurveySetup : public CDialog
{
	DECLARE_DYNAMIC(CDlgSurveySetup)

public:
	CDlgSurveySetup(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgSurveySetup();

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
	CTabSurvey m_oTabSurvey;
	/** ����ҳ�����*/
	CTabPointCode m_oTabPointCode;
	/** ����ҳ�첨��*/
	CTabSensor m_oTabSensor;

public:	// ����
	afx_msg void OnBnClickedButtonApplyAll();
	afx_msg void OnBnClickedButtonApplySensor();
	afx_msg void OnBnClickedButtonReset();
	afx_msg void OnBnClickedButtonAdd();
	afx_msg void OnBnClickedButtonChange();
	afx_msg void OnBnClickedButtonDelete();
	afx_msg void OnBnClickedButtonReverse();
};
