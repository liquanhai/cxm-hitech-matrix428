// ReceiveDataUDPDlg.h : ͷ�ļ�
//

#pragma once
#include "Receive.h"

// CReceiveDataUDPDlg �Ի���
class CReceiveDataUDPDlg : public CDialog
{
// ����
public:
	CReceiveDataUDPDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_RECEIVEDATAUDP_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��

public:
	CReceive m_Receive;

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
	afx_msg void OnBnClickedButtonReceive();
};
