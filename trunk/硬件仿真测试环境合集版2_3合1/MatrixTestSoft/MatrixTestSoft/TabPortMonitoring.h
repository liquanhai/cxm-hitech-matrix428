#pragma once
#include "afxcmn.h"
#include "PortMonitoringRec.h"
#include "PortMonitoringSend.h"
#include "PortMonitoringThreadSend.h"
#include "PortMonitoringThreadRec.h"
#include "Parameter.h"
#include "SaveFile.h"
// CPortMonitoring �Ի���

class CTabPortMonitoring : public CDialog
{
	DECLARE_DYNAMIC(CTabPortMonitoring)

public:
	CTabPortMonitoring(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CTabPortMonitoring();

// �Ի�������
	enum { IDD = IDD_DIALOG_PORTMONITORING };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	// TabControl���Ʊ���
	CTabCtrl m_cTabCtrlItems;
	// ��ʼ��ѡ��ؼ�
	void InitTabControlItems(void);
	// ��CPortMonitoringRec�ı���
	CPortMonitoringRec m_oPortMonitorRec;
	// ��CPortMonitoringSend�ı���
	CPortMonitoringSend m_oPortMonitorSend;
	// �˿ڼ��ӷ����߳�
	CPortMonitoringThreadSend m_oThreadSend;
	// �˿ڼ��ӽ����߳�
	CPortMonitoringThreadRec m_oThreadRec;
	afx_msg void OnTcnSelchangeTabPortmonitoring(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedButtonPortmonitoringOpen();
	afx_msg void OnBnClickedButtonPortmonitoringClose();
	afx_msg void OnBnClickedButtonStartsave();
	afx_msg void OnBnClickedButtonStopsave();
	afx_msg void OnBnClickedButtonSavefilepath();
	afx_msg void OnBnClickedButtonReset();
	// ��ʼ��
	void OnInit(void);
	// ���շ�IP��ַ���Ʊ���
	CIPAddressCtrl m_IPctrlRec;
	// ���ͷ�IP��ַ���Ʊ���
	CIPAddressCtrl m_IPctrlSend;
	// Ŀ��1���ն˿�
	CString m_csRcvPort1;
	// Ŀ��1���Ͷ˿�
	CString m_csSendPort1;
	// Ŀ��2���ն˿�
	CString m_csRcvPort2;
	// Ŀ��2���Ͷ˿�
	CString m_csSendPort2;
	// ���շ�IP��ַ
	CString m_csIPRec;
	// ���ͷ�IP��ַ
	CString m_csIPSend;
	// �Զ������ļ���С
	int m_iSaveSize;
	// ��CSaveFile�ı���
	CSaveFile m_oSaveFile;
	afx_msg void OnClose();

	// �˿ڷַ�����ѡ��
	BOOL m_bPortDistribution;
};
