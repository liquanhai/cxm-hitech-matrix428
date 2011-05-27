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
protected:
	// �����ٽ�������
	CCriticalSection m_Sec;
public:
	// �߳���ָ��
	CPortMonitoringRecThread* m_pRecThread;
public:
	afx_msg void OnTimer(UINT_PTR nIDEvent);
};
