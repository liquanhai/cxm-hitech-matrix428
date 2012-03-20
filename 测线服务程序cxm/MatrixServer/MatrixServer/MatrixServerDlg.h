
// MatrixServerDlg.h : ͷ�ļ�
//

#pragma once
#include "..\\MatrixServerDll\\MatrixServerDll.h"
#include "ServerSocketEvent.h"
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
	HMODULE m_hDllMod;
	m_oEnvironmentStruct* m_pEnv;
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
	afx_msg void OnBnClickedButtonStartsample();
	afx_msg void OnBnClickedButtonStopsample();
	// DLL����ʵ��
	void Dll_Create_Instance(void);
	// DLL��ʼ��
	void Dll_Init_Instance(void);
	// ��ʼ���׽��ֿ�
	void OnInitSocketLib(void);
	// �ͷ��׽��ֿ�
	void OnCloseSocketLib(void);
	// ����Server�˿ڼ���
	void CreateSocketListen(void);
	// DLL�ر�ʵ��
	void Dll_Close_Instance(void);
	// DLL�ͷ�ʵ��
	void Dll_Free_Instance(void);
	// ����Server��ͻ���ͨѶ�߳�
	void OnCreateCommThread(void);
	// �߳̾��
	HANDLE m_hThread;
	// ��ͻ���ͨѶ�̺߳���
	DWORD CommThreadRun(void);
	// DLL��ʼAD���ݲɼ�
	void Dll_StartSample(void);
	// DLLֹͣAD���ݲɼ�
	void Dll_StopSample(void);
	// DLL��ʼ����
	void Dll_Work(void);
	// DLLֹͣ����
	void Dll_Stop(void);
};
