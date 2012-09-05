// NetWinPcapDlg.h : ͷ�ļ�
//

#pragma once
#include "PcapRcvThread.h"
#include "PcapSndThread.h"
#include "NetPcapComm.h"

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
};
