#pragma once
#include <afxmt.h>
// CTabADCDataShow �Ի���

class CTabADCDataShow : public CDialog
{
	DECLARE_DYNAMIC(CTabADCDataShow)

public:
	CTabADCDataShow(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CTabADCDataShow();

// �Ի�������
	enum { IDD = IDD_DIALOG_ADCDATASHOW };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnTimer(UINT_PTR nIDEvent);
public:
	// ADC���ݽ�����ʾ������ָ��
	double* m_pADCDataShow;
	// �����ٽ�������
	CCriticalSection m_Sec;
	// ��ֹ������ѭ���������޷���Ӧ��Ϣ
	void ProcessMessages(void);
};
