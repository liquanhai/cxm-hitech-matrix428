// NetWinPcapDlg.h : ͷ�ļ�
//

#pragma once
#include "PcapRcvThread.h"
#include "PcapSndThread.h"
#include "NetPcapComm.h"
#include "afxwin.h"
#define RevSndFrameNumTimerEventID	1
#define RevSndFrameNumTimer			1000
// CNetWinPcapDlg �Ի���
class CNetWinPcapDlg : public CDialogEx
{
// ����
public:
	CNetWinPcapDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_NETWINPCAP_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��
public:
	/** Pcap�����̳߳�Ա����*/
	CPcapRcvThread m_oPcapRcvThread;
	/** Pcap�����̳߳�Ա����*/
	CPcapSndThread m_oPcapSndThread;
	/** PcapͨѶ���Ա����*/
	CNetPcapComm m_oNetPcapComm;
public:
	// �ؼ�IDC_EDIT_DOWNSTREAM_RCVNUM����ֵ����
	long m_lEditDownStreamRcvNum;
	// �ؼ�IDC_EDIT_DOWNSTREAM_SNDNUM����ֵ����
	long m_lEditDownStreamSndNum;
	// �ؼ�IDC_EDIT_UPSTREAM_RCVNUM����ֵ����
	long m_lEditUpStreamRcvNum;
	// �ؼ�IDC_EDIT_UPSTREAM_SNDNUM����ֵ����
	long m_lEditUpStreamSndNum;
public:
	/** �����в�������*/
	void PhraseCommandLine(CString str);
// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnWindowPosChanging(WINDOWPOS* lpwndpos);
	afx_msg void OnClose();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnBnClickedButtonResetnum();
};
