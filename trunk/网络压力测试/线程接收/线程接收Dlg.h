// �߳̽���Dlg.h : ͷ�ļ�
//
#include "MyThread.h"
#include <afxmt.h>
#pragma once


// C�߳̽���Dlg �Ի���
class C�߳̽���Dlg : public CDialog
{
// ����
public:
	C�߳̽���Dlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_MY_DIALOG };

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
	CMyThread m_Thread;
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	// �����ٽ�������
	CCriticalSection m_Sec;
};
