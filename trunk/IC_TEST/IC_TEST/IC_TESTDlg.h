// IC_TESTDlg.h : header file
//

#pragma once
#include "afxwin.h"
#include "d:\program files (x86)\codejock software\mfc\xtreme toolkitpro v15.3.1\source\controls\edit\xtphexedit.h"
#include <vector>
#include "afxcmn.h"
#include "LandedDlg.h"
#include "Uart.h"
using std::vector;
using std::string;
// ����Ĭ�ϻ�������С
#define DefaultBufSize	10240
// ����Ĭ�ϻ�������ֵ
#define DefaultBufValue	0xff
// ����SCR��ַ
#define SCRAddr			1039
// ����IRC4M��ַ
#define IRC4MAddr		1038
// ����IRC1K��ַ
#define IRC1KAddr		1037
// ���������ģʽ
// #define ReadMode		0
// ����д����ģʽ
// #define WriteMode		1
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
	// ���ڽ������ݻص�����
	static void CALLBACK OnUartRead(void* pFatherPtr, BYTE buf);
	afx_msg void OnBnClickedBtnReset();
	afx_msg void OnBnClickedBtnResetMsg();
	afx_msg void OnBnClickedBtnOpenfile();
	afx_msg void OnDestroy();

	// ��дģʽ�����˵����Ʊ���
	CComboBox m_ctrlComboProMode;
	// �˿ںű༭�ؼ����Ʊ���
	CEdit m_ctrlComNo;
	// ��½
	void OnLanded(void);
	afx_msg void OnBnClickedBtnLanded();
	// ���ý���
	void RefreshView(void);
	// ��ʾ�ؼ�
	void ShowControls(int iStyle);
	// SCR��Spin�ؼ����Ʊ���
	CSpinButtonCtrl m_ctrlSpinSCR;
	CEdit m_ctrlEditSCR;
	CComboBox m_ctrlComboSCR;
	// IRC4M��Spin�ؼ����Ʊ���
	CSpinButtonCtrl m_ctrlSpinIRC4M;
	CEdit m_ctrlEditIRC4M;
	CComboBox m_ctrlComboIRC4M;
	// IRC1K��Spin�ؼ����Ʊ���
	CSpinButtonCtrl m_ctrlSpinIRC1K;
	CEdit m_ctrlEditIRC1K;
	CComboBox m_ctrlComboIRC1K;
	// ���ز˵����Ʊ���
	CComboBox m_ctrlComboReadback;
	// ����ͨѶ���Ա
	CUart m_oUart;
	// �������ݶ���
	CList<BYTE> m_olsSendData;
	// ����������ֽ���
	unsigned int m_uiRecDataNum;
	// �������ݶ���
	CList<BYTE> m_olsRecData;
	afx_msg void OnBnClickedBtnOpencom();
	afx_msg void OnBnClickedBtnClosecom();
	afx_msg void OnBnClickedBtnReadbackDo();
	afx_msg void OnBnClickedBtnProgramDo();
	afx_msg void OnBnClickedBtnSCRDo();
	afx_msg void OnBnClickedBtnIrc4mDo();
	afx_msg void OnBnClickedBtnIrc1kDo();
	afx_msg void OnBnClickedBtnSavefile();
	// SCR���ļ���λ��
	unsigned int m_uiSCRPosition;
	// IRC4M���ļ��е�λ��
	unsigned int m_uiIRC4MPosition;
	// IRC1K���ļ��е�λ��
	unsigned int m_uiIRC1KPosition;
	// ��д�ļ�·��
	CString m_strProFilePath;
	// ���������ģʽ
	enum {ReadMode, WriteMode};
	// �򴮿�дģʽ
	bool m_bModeWrite;
	// ��Ҫ���յ���ADC����
	unsigned int m_uiRecDataNeed;
	// æ״̬
	bool m_bBusy;
};
