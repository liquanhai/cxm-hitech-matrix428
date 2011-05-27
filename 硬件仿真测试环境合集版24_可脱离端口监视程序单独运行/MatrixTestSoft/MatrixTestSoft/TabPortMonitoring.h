#pragma once
#include "afxcmn.h"
#include "PortMonitoringRec.h"
#include "PortMonitoringSend.h"
#include "Parameter.h"
#include "SaveFile.h"
#include "PortMonitoringRecThread.h"
#include "PortMonitoringSendThread.h"
#include <afxmt.h>
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
 	CPortMonitoringSendThread m_oThreadSend;
	// �˿ڼ��ӽ����߳�
	CPortMonitoringRecThread m_oThreadRec;

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
	unsigned int m_uiRcvPort1;
	// Ŀ��1���Ͷ˿�
	unsigned int m_uiSendPort1;
	// Ŀ��2���ն˿�
	unsigned int m_uiRcvPort2;
	// Ŀ��2���Ͷ˿�
	unsigned int m_uiSendPort2;
	// ���շ�IP��ַ
	CString m_csIPRec;
	// ���ͷ�IP��ַ
	CString m_csIPSend;
	// �Զ������ļ���С
	int m_iSaveSize;
	// ��CSaveFile�ı���
	CSaveFile m_oSaveFile;
	// �ر�
	void OnClose();
	// �����ٽ�������
	CCriticalSection m_Sec;
	// �˿ڷַ�����ѡ��
	BOOL m_bPortDistribution;
	// ��ֹ������ѭ�����������޷���Ӧ��Ϣ
	void ProcessMessages(void);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	// ��ʼ�˿ڼ��ӱ�־λ
	BOOL m_bPortMonitoringStart;
};
