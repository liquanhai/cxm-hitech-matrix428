#pragma once


// CDlgNewUser �Ի���

class CDlgNewUser : public CDialog
{
	DECLARE_DYNAMIC(CDlgNewUser)

public:
	CDlgNewUser(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgNewUser();

// �Ի�������
	enum { IDD = IDD_NEWUSERDLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	// �û���
	CString m_strUserName;
	// �û�����
	CString m_strPassword;
};
