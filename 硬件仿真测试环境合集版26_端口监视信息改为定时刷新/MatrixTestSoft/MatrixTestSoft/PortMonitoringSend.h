#pragma once
#include "PortMonitoringRecThread.h"
#include <afxmt.h>
// CPortMonitoringSend �Ի���

class CPortMonitoringSend : public CDialog
{
	DECLARE_DYNAMIC(CPortMonitoringSend)

public:
	CPortMonitoringSend(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CPortMonitoringSend();

// �Ի�������
	enum { IDD = IDD_DIALOG_PORTMONITORING_SEND };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnTimer(UINT_PTR nIDEvent);
public:
	// �߳���ָ��
	CPortMonitoringRecThread* m_pRecThread;
	// �����ٽ�������
	CCriticalSection m_Sec;
};
