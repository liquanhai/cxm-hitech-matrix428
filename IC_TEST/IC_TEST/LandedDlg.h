#pragma once
#include "afxwin.h"


// CLandedDlg �Ի���

class CLandedDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CLandedDlg)

public:
	CLandedDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CLandedDlg();

// �Ի�������
	enum { IDD = IDD_DIALOG_LAND };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
public:
	// �û������Ʊ���
	CComboBox m_ctrlUserName;
	// ������Ʊ���
	CEdit m_ctrlPassword;
	virtual void OnOK();
	// ��½
	void OnLand(void);
};
