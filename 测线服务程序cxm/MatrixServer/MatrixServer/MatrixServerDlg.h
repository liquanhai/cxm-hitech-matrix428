
// MatrixServerDlg.h : ͷ�ļ�
//

#pragma once
#include "..\\MatrixServerDll\\MatrixServerDll.h"
// CMatrixServerDlg �Ի���
class CMatrixServerDlg : public CDialogEx
{
// ����
public:
	CMatrixServerDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_MATRIXSERVER_DIALOG };

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
	afx_msg void OnBnClickedBnStart();
	afx_msg void OnBnClickedBnStop();
	afx_msg void OnBnClickedBnClose();
	afx_msg void OnBnClickedBnRefresh();
	afx_msg void OnBnClickedBnSave();
public:
	HMODULE hMod;
	m_oEnvironmentStruct* pEnv;
	afx_msg void OnDestroy();
	afx_msg void OnBnClickedButtonInit();
	afx_msg void OnBnClickedButtonStartsample();
	afx_msg void OnBnClickedButtonStopsample();
};
