#pragma once
#include "afxcmn.h"


// CDlgDelaySetup �Ի���

class CDlgDelaySetup : public CDialog
{
	DECLARE_DYNAMIC(CDlgDelaySetup)

public:
	CDlgDelaySetup(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgDelaySetup();

// �Ի�������
	enum { IDD = IDD_DIALOG_DELAYSETUP };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonApply();
	afx_msg void OnBnClickedButtonReset();
	// �ؼ�����ֵ����
	float m_feditAcq;
	// �ؼ�����ֵ����
	float m_feditVP;
	// �ؼ��Ŀ��Ʊ���
	CSliderCtrl m_ctrlsliderAcq;
	// �ؼ��Ŀ��Ʊ���
	CSliderCtrl m_ctrlsliderVP;
	virtual BOOL OnInitDialog();
	afx_msg void OnNMCustomdrawSliderAcq(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMCustomdrawSliderVp(NMHDR *pNMHDR, LRESULT *pResult);
};
