#pragma once


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

	DECLARE_MESSAGE_MAP()
};
