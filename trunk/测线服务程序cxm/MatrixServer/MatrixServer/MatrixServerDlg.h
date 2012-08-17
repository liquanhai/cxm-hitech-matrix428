
// MatrixServerDlg.h : ͷ�ļ�
//

#pragma once
#include "MatrixDllCall.h"
#include "ServerCommDll.h"

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
	/** DLL�����������Ա*/
	CMatrixDllCall m_oMatrixDllCall;
	/** ��ͻ���ͨѶ���Ա*/
	CServerCommDll m_oComDll;
public:
	afx_msg void OnBnClickedBnStart();
	afx_msg void OnBnClickedBnStop();
	afx_msg void OnDestroy();
	afx_msg void OnBnClickedButtonStartsampleAll();
	afx_msg void OnBnClickedButtonStopsampleAll();
	afx_msg void OnBnClickedBnAdcsetAll();
	afx_msg void OnBnClickedBnAdcsetByrout();
	afx_msg void OnBnClickedBnStartsampleByrout();
	afx_msg void OnBnClickedBnStopsampleByrout();
	afx_msg void OnBnClickedBtnOpenroutpower();
	afx_msg void OnBnClickedBtnGetroutinstrumentnum();
	afx_msg void OnBnClickedBtnGetsnbylocation();
};
