#pragma once

#include "SetupGridCtrl.h"
// CDlgCommentType �Ի���

class CDlgCommentType : public CBCGPDialog
{
	DECLARE_DYNAMIC(CDlgCommentType)

public:
	CDlgCommentType(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgCommentType();

// �Ի�������
	enum { IDD = IDD_COMMENTTYPESETUPDLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()

public:
	CStatic				m_ctrlEditGridLocation;
	CStatic				m_ctrlListGridLocation;
	CGridCtrlList		m_wndListGrid;
	CGridCtrlEdit		m_wndEditGrid;
	virtual BOOL OnInitDialog();
	CString m_strComment;
};
