// PortMonitoringDlg.h : ͷ�ļ�
//

#pragma once
#include "afxcmn.h"
#include "Resource.h"
#include "ThreadManage.h"
#include "Parameter.h"
#include <afxmt.h>

// CPortMonitoringDlg �Ի���
class CPortMonitoringDlg : public CDialog
{
// ����
public:
	CPortMonitoringDlg(CWnd* pParent = NULL);	// ��׼���캯��
	~CPortMonitoringDlg(void);
// �Ի�������
	enum { IDD = IDD_MY_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��

public:

	// �����������
	void OnSaveReceiveData(unsigned char* buf, int iRecLength);
	// ���淢������
	void OnSaveSendData(unsigned char* buf, int iSendLength);
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
	CThreadManage m_oThreadManage;

	// ��ʾ�յ��ͷ���֡
	CString m_csEditShow;
	// ����ͨѶ�ļ�
	CString m_csSaveFile;
	// ������յ����ݵ��ļ�
	CString m_csSaveReceiveFile;
	// ���淢�͵����ݵ��ļ�
	CString m_csSaveSendFile;
	// �����ٽ���ȫ�ֱ���
	CCriticalSection m_Sec;
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
	afx_msg void OnBnClickedButtonOnReset();
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
	afx_msg void OnClose();
};
