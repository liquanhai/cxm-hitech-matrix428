// OnReceive����Dlg.h : ͷ�ļ�
//
#include "MySocket.h"
#pragma once


// COnReceive����Dlg �Ի���
class COnReceive����Dlg : public CDialog
{
// ����
public:
	COnReceive����Dlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_ONRECEIVE_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


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
	CMySocket m_Socket;
	afx_msg void OnTimer(UINT_PTR nIDEvent);
};
