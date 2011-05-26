#pragma once
#include "afxwin.h"
#include "DlgStudentsSetting.h"
#include "DlgTeachersSetting.h"


// CDlgSettings �Ի���

class CDlgSettings : public CBCGPDialog
{
	DECLARE_DYNAMIC(CDlgSettings)

public:
	CDlgSettings(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgSettings();

// �Ի�������
	enum { IDD = IDD_DIALOG_SETTINGS };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CStatic m_ctrlTabLocation;
	CBCGPTabWnd			m_wndTab;
	CDlgStudentsSetting	m_DlgStudents;
	CDlgTeachersSetting	m_DlgTeachers;
	virtual BOOL OnInitDialog(void);
};
