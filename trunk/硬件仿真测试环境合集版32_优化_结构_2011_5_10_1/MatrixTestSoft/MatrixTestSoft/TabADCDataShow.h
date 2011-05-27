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
private:
	// �����ٽ�������
	CCriticalSection m_Sec;
	// ��ֹ������ѭ���������޷���Ӧ��Ϣ
	void ProcessMessages(void);
public:
	// ADC���ݽ�����ʾ������ָ��
	double* m_pADCDataShow;
public:
	afx_msg void OnTimer(UINT_PTR nIDEvent);
};
