// IC_TESTDlg.h : header file
//

#pragma once
#include "afxwin.h"
#include "d:\program files (x86)\codejock software\mfc\xtreme toolkitpro v15.3.1\source\controls\edit\xtphexedit.h"
#include <vector>
#include "afxcmn.h"
using std::vector;
// ����Ĭ�ϻ�������С
#define DefaultBufSize	10240
// ����Ĭ�ϻ�������ֵ
#define DefaultBufValue	0xff
// ����SRC��ַ
#define SRCAddr			1039
// ����IRC4M��ַ
#define IRC4MAddr		1038
// ����IRC1K��ַ
#define IRC1KAddr		1037
// CIC_TESTDlg dialog
class CIC_TESTDlg : public CDialog
{
// Construction
public:
	CIC_TESTDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	enum { IDD = IDD_IC_TEST_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	// ��Ϣ�б���Ʊ���
	CListBox m_ctrlListMsg;
	// ��д�ļ���Ϣ��ʾ���Ʊ���
	CXTPHexEdit m_ctrlEditHex;
	// ��д����
	LPBYTE  m_pProData;
	// Hex���ݵ�ַ���ֵ
	unsigned int m_uiAddrMax;
	// Hex���ݵ�ַ��Сֵ
	unsigned int m_uiAddrMin;
	// SCR��ֵ
	BYTE m_bySCR;
	// IRC4M��ֵ
	BYTE m_byIRC4M;
	// IRC1K��ֵ
	BYTE m_byIRC1K;
	// ���ÿؼ�
	void RefreshControls(void);
	afx_msg void OnBnClickedBtnReset();
	afx_msg void OnBnClickedBtnResetMsg();
	afx_msg void OnBnClickedBtnOpenfile();
	afx_msg void OnDestroy();
	// SRC��Spin�ؼ����Ʊ���
	CSpinButtonCtrl m_ctrlSpinSRC;
	// IRC4M��Spin�ؼ����Ʊ���
	CSpinButtonCtrl m_ctrlSpinIRC4M;
	// IRC1K��Spin�ؼ����Ʊ���
	CSpinButtonCtrl m_ctrlSpinIRC1K;
};
