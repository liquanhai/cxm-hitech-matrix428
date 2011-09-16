#pragma once
#include "Resource.h"
#include "TabSelectShotPoint.h"
#include "SiteData.h"
// CDlgSelectShotPoint �Ի���

class CDlgSelectShotPoint : public CDialog
{
	DECLARE_DYNAMIC(CDlgSelectShotPoint)

public:
	CDlgSelectShotPoint(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgSelectShotPoint();

// �Ի�������
	enum { IDD = IDD_DIALOG_SELECTSHOTPOINT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
public:
	/** ����ҳ����*/
	CBCGPTabWnd m_oTabWnd;
	/** ����ҳ������������*/
	CTabSelectShotPoint m_oTabSelectShotPoint;
	/** �ֳ�����*/
	CSiteData* m_pSiteData;
	// ��������ҳ��ָ��
	CTabSpreadAbsolute* m_pTabSpreadAbsolute;
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
};
