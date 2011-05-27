// PortMonitoringDlg.h : ͷ�ļ�
//

#pragma once
#include "afxcmn.h"

#define RcvPort1	0x8202	// Ŀ��1���ն˿�
#define SendPort1	0x9002	// Ŀ��1���Ͷ˿�
#define RcvPort2	0x9001	// Ŀ��2���ն˿�
#define SendPort2	0x8201	// Ŀ��2���Ͷ˿�
#define UDPPortNb	18		// Ŀ��2���͵Ķ˿���
class CMySocket;
class CMySocket2;
// CPortMonitoringDlg �Ի���
class CPortMonitoringDlg : public CDialog
{
// ����
public:
	CPortMonitoringDlg(CWnd* pParent = NULL);	// ��׼���캯��
	~CPortMonitoringDlg();
// �Ի�������
	enum { IDD = IDD_MY_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��

public:
	// ����ͨѶ�ļ�
	CString m_csSaveFile;
	// �����������
	void OnSaveReceiveData(unsigned char* buf, int iRecLength);
	// ���淢������
	void OnSaveSendData(unsigned char* buf, int iSendLength, bool berror);
	// ���浽�ļ���
	void OnSaveToFile();
	// �����ļ�
	FILE* m_file;
	// ������������ļ���·��
	char cSaveToFilePath[MAX_PATH];
	CString strFilePath;
	// ����ͨѶ���ݿ�ʼ��־λ
	BOOL m_bStartSave;
	// ���շ�IP��ַ
	CString m_strReceiveIP;
	// ���ͷ�IP��ַ
	CString m_strSendIP;
	CMySocket* m_hSocket1;
	CMySocket2* m_hSocket2;



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
	afx_msg void OnBnClickedButtonSavefilepath();
	afx_msg void OnBnClickedButtonStartsave();
	afx_msg void OnBnClickedButtonStopsave();
	// ��ʾ�յ��ͷ���֡
	CString m_cseditshow;
	afx_msg void OnBnClickedButtonClearscreen();
	// �Զ������ļ���С
	int m_iSaveSize;
	// ���շ�IP��ַ���Ʊ���
	CIPAddressCtrl m_IPreceive;
	// ���ͷ�IP��ַ���Ʊ���
	CIPAddressCtrl m_IPsend;
	// Ŀ��1���ն˿�
	CString m_csRcvPort1;
	// Ŀ��1���Ͷ˿�
	CString m_csSendPort1;
	// Ŀ��2���ն˿�
	CString m_csRcvPort2;
	// Ŀ��2���Ͷ˿�
	CString m_csSendPort2;
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnBnClickedButtonStart();
	afx_msg void OnBnClickedButtonStop();
	// ������ʼ��־λ
	BOOL m_bStartSample;
};
