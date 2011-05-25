#pragma once
#include "Tab4.h"
#include "Tab5.h"
#include "afxcmn.h"

// CTab1 �Ի���

class CTab1 : public CDialog
{
	DECLARE_DYNAMIC(CTab1)

public:
	CTab1(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CTab1();

// �Ի�������
	enum { IDD = IDD_DIALOG1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CTabCtrl m_tab_in;
	virtual BOOL OnInitDialog();
	CTab4 m_tab4;
	CTab5 m_tab5;
	afx_msg void OnTcnSelchangeTab2(NMHDR *pNMHDR, LRESULT *pResult);
};
