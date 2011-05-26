#pragma once
#include "afxwin.h"
#include "SetupGridCtrl.h"


// CDlgStudentsSetting �Ի���

class CDlgStudentsSetting : public CBCGPDialog
{
	DECLARE_DYNAMIC(CDlgStudentsSetting)

public:
	CDlgStudentsSetting(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgStudentsSetting();

// �Ի�������
	enum { IDD = IDD_DLGSTUDENTSSETTING };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CStatic m_ctrlEditGridLocation;
	CStatic m_ctrlGridLocation;
	CGridCtrlList			m_wndListGrid;
	CGridCtrlEdit			m_wndEditGrid;
	virtual BOOL OnInitDialog(void);
	// ����������
	void Load(CString csstudents);
	// ����һ��ѧ��������Ϣ
	void LoadStudent(CString csstudent);
};
