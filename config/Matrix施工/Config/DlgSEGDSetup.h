#pragma once


// CDlgSEGDSetup �Ի���

class CDlgSEGDSetup : public CBCGPDialog
{
	DECLARE_DYNAMIC(CDlgSEGDSetup)

public:
	CDlgSEGDSetup(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgSEGDSetup();

// �Ի�������
	enum { IDD = IDD_SEGDDLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
};
