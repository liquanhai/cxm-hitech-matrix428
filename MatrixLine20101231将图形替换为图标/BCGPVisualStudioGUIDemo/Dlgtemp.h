#pragma once


// CDlgtemp �Ի���

class CDlgtemp : public CDialog
{
	DECLARE_DYNAMIC(CDlgtemp)

public:
	CDlgtemp(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgtemp();

// �Ի�������
	enum { IDD = IDD_DIALOG1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
};
