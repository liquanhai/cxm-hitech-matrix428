#pragma once

// �ڶԻ����˳�ǰ���򸸴��ڷ�����Ϣ��֪ͨ�����ڸ���ģʽ�Ի���׼���˳�
#define WM_DLGLOGINDESTROY (WM_USER + 100)


// CDlgLoginAdminServer �Ի���
class CDlgLoginAdminServer : public CBCGPDialog
{
	DECLARE_DYNAMIC(CDlgLoginAdminServer)

public:
	CDlgLoginAdminServer(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgLoginAdminServer();

// �Ի�������
	enum { IDD = IDD_CONNECTIONDLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
protected:
	virtual void OnOK();
	virtual void OnCancel();
	virtual void PostNcDestroy();
	afx_msg void OnBnClickedBtnconnect();
	afx_msg void OnDestroy();

public:
	CString m_strLabel;
	CString m_strURL;
	CString m_strUserName;
	CString m_strPassword;
	
};
