// SendDataUDPDlg.h : ͷ�ļ�
//

#pragma once
#include <vector>
using namespace std;

// CSendDataUDPDlg �Ի���
class CSendDataUDPDlg : public CDialog
{
// ����
public:
	CSendDataUDPDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_SENDDATAUDP_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��
public:
	vector <UCHAR> m_SendData;
	DWORD StringIPToDWORDIP(CString& strIP);
	void ReadSeletedFile();
	void SendData();

// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonSend();
};
