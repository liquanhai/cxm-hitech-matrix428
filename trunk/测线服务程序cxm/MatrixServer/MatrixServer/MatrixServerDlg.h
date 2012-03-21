
// MatrixServerDlg.h : ͷ�ļ�
//

#pragma once
#include "ServerSocketEvent.h"
#include "MatrixDllCall.h"
#define ServerListenPort 5150

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
	CMatrixDllCall m_oMatrixDllCall;
	SOCKET m_SocketListen;
	SOCKADDR_IN m_ServerInternetAddr;
	DWORD m_dwEventTotal;
	WSAEVENT m_WSAEventArray[WSA_MAXIMUM_WAIT_EVENTS];
	CServerSocketEvent* m_ServerSocketEventArray[WSA_MAXIMUM_WAIT_EVENTS];
	BOOL CreateSocketInformation(SOCKET s);
	void FreeSocketInformation(DWORD Event);
public:
	afx_msg void OnBnClickedBnStart();
	afx_msg void OnBnClickedBnStop();
	afx_msg void OnDestroy();
	afx_msg void OnBnClickedButtonStartsampleAll();
	afx_msg void OnBnClickedButtonStopsampleAll();

	// ��ʼ���׽��ֿ�
	void OnInitSocketLib(void);
	// �ͷ��׽��ֿ�
	void OnCloseSocketLib(void);
	// ����Server�˿ڼ���
	void CreateSocketListen(void);
	// ����Server��ͻ���ͨѶ�߳�
	void OnCreateCommThread(void);
	// �߳̾��
	HANDLE m_hThread;
	// ��ͻ���ͨѶ�̺߳���
	DWORD CommThreadRun(void);
	afx_msg void OnBnClickedBnAdcsetAll();
	afx_msg void OnBnClickedBnAdcsetByrout();
	afx_msg void OnBnClickedBnStartsampleByrout();
	afx_msg void OnBnClickedBnStopsampleByrout();
};
