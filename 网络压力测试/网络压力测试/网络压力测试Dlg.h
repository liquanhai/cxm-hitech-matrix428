// ����ѹ������Dlg.h : ͷ�ļ�
//

#pragma once
#include "afxsock.h"

#define SendPort	0x9001	// ���Ͷ˿�
#define RcvPort		0x7200	// ���ն˿�
#define SndBufSize	655360	// ���÷��ͻ�������С
// C����ѹ������Dlg �Ի���
class C����ѹ������Dlg : public CDialog
{
// ����
public:
	C����ѹ������Dlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_MY_DIALOG };

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
	afx_msg void OnBnClickedButtonStart();
	afx_msg void OnBnClickedButtonStop();
	// CSocket����
	CSocket m_hSocket;
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	// ����֡��ʱ����
	unsigned int m_uiTimeDelay;
	// ÿ�η���֡��
	unsigned int m_uiSendFrameNum;
	// Ŀ��IP��ַ
	CString m_csIPAim;
	// Ŀ��˿�
	unsigned int m_uiAimPort;
	// ��ʵ���ط�ʱ����
	unsigned char m_ucSendFrame[256];
	unsigned int m_uiRealTimeDelay;
	// ��ʵ����֡��
	unsigned int m_uiRealSendFrameNum;
};
