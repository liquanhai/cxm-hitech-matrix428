// MatrixTestSoftDlg.h : header file
//

#pragma once
#include "afxcmn.h"
#include "TabUartToUdp.h"
#include "TabPortMonitoring.h"
#include "TabSample.h"
#include "TabADCSettings.h"
#include "TabADCDataShow.h"

// CMatrixTestSoftDlg dialog
class CMatrixTestSoftDlg : public CDialog
{
// Construction
public:
	CMatrixTestSoftDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_MATRIXTESTSOFT_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


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
	// TabContrl�ؼ��Ŀ��Ʊ���
	CTabCtrl m_cTabCtrlItems;
	// CTabUartToUdp��ı���
	CTabUartToUdp m_oTabUartToUdp;
	// CTabPortMonitoring��ı���
	CTabPortMonitoring m_oTabPortMonitoring;
	// CTabGraphView��ı���
	CTabSample m_oTabSample;
	// CTabADCSettings��ı���
	CTabADCSettings m_oTabADCSettings;
	// CTabADCDataShow��ı���
	CTabADCDataShow m_oTabADCDataShow;
	
	// ��ʼ��ѡ��ؼ�
	void InitTabControlItems(void);
	afx_msg void OnTcnSelchangeTabItems(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnClose();
	// ����XML�����ļ�
	void LoadXmlFile(CString csXmlFileName);
	// ��XML�����ļ�
	void OpenXmlFile(CString csXmlFileName);
	/** XMLDOM�ļ�����*/
	CXMLDOMDocument m_oXMLDOMDocument;
	// ���봮��תUDP����
	bool LoadUartToUDPSetup(void);
	// ����UDP�˿ڼ�������
	bool LoadUDPPortMonitoringSetup(void);
	// �����������
	bool LoadSampleSetup(void);
	// ����ADC������������
	bool LoadADCSettingsSetup(void);
	// �رճ��������ļ�
	void CloseXmlFile(void);
	// ���洮��תUDP����
	bool SaveUartToUDPSetup(void);
	// ����UDP�˿ڼ�������
	bool SaveUDPPortMonitoringSetup(void);
	// �����������
	bool SaveSampleSetup(void);
	// ����ADC������������
	bool SaveADCSettingsSetup(void);
	// ���������ļ�
	void SaveXmlFile(void);
};
