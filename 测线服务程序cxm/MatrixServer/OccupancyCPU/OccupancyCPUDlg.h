
// OccupancyCPUDlg.h : ͷ�ļ�
//
#include "Thread.h"
#pragma once


// COccupancyCPUDlg �Ի���
class COccupancyCPUDlg : public CDialogEx
{
// ����
public:
	COccupancyCPUDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_OCCUPANCYCPU_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��
public:
	CThread* m_pThreadArray;
	// �̸߳���
	unsigned int m_uiThreadNum;
// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnClose();
	afx_msg void OnBnClickedButtonStart();
	afx_msg void OnBnClickedButtonStop();
};
