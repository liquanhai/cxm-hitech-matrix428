#pragma once


// CPortMonitoringRec �Ի���

class CPortMonitoringRec : public CDialog
{
	DECLARE_DYNAMIC(CPortMonitoringRec)

public:
	CPortMonitoringRec(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CPortMonitoringRec();

// �Ի�������
	enum { IDD = IDD_DIALOG_PORTMONITORING_REC };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()

};
