#pragma once
#include "afxwin.h"
#include "SetupGridCtrl.h"


// CDlgTeachersSetting �Ի���

class CDlgTeachersSetting : public CBCGPDialog
{
	DECLARE_DYNAMIC(CDlgTeachersSetting)

public:
	CDlgTeachersSetting(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgTeachersSetting();

// �Ի�������
	enum { IDD = IDD_DLGTEACHERSSETTING };

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
	void Load(CString csteacher);
	// ����һ����ʦ������Ϣ
	void LoadTeacher(CString csteacher);
};
