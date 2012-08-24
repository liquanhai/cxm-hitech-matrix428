
// SocketSendDlg.h : ͷ�ļ�
//

#pragma once


// CSocketSendDlg �Ի���
class CSocketSendDlg : public CDialogEx
{
// ����
public:
	CSocketSendDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_SOCKETSEND_DIALOG };

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
	// Ŀ��˿�
	UINT m_uiDstPort;
	// �Ƿ�㲥
	BOOL m_bBroadCast;
	// ���ջ���
	UINT m_uiRcvBuf;
	// ���ͻ���
	UINT m_uiSndBuf;
	// Socket
	SOCKET m_SocketSnd;
	// Ŀ��
	sockaddr_in m_addrSend;
	// ���ͻ���
	char m_cFrameData[256];
	// ���ͼ���
	unsigned int m_uiCount;
	// ����֡��
	UINT m_uiSndNum;
public:
	afx_msg void OnBnClickedButtonStart();
};
