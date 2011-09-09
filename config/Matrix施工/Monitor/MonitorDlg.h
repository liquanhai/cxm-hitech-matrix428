// MonitorDlg.h : ͷ�ļ�
//

#pragma once
#include "SocketSampData.h"
#include "iplotx1.h"

// CMonitorDlg �Ի���
class CMonitorDlg : public CDialog
{
// ����
public:
	CMonitorDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_MONITOR_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��
public:

	CSocketSampData	m_SockSample;
	DWORD			m_dwXValue;
// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnDestroy();
	DECLARE_MESSAGE_MAP()
	
public:
	void AnalysisProtocolOfSampleSock(void);

	
	CIplotx1 m_iPlotX;
	afx_msg void OnBnClickedButton1();
};
