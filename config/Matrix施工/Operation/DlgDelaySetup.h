#pragma once
#include "afxcmn.h"


// CDlgDelaySetup �Ի���

class CDlgDelaySetup : public CBCGPDialog
{
	DECLARE_DYNAMIC(CDlgDelaySetup)

public:
	CDlgDelaySetup(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgDelaySetup();

// �Ի�������
	enum { IDD = IDD_DELAYSETUPDLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnTRBNThumbPosChangingSliderendofacq(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMThemeChangedSliderendofacq(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMReleasedcaptureSliderendofacq(NMHDR *pNMHDR, LRESULT *pResult);

	float m_fEndOfAcq;
	float m_fEndOfVP;
	
	CSliderCtrl m_SliderEndOfAcq;
	CSliderCtrl m_SliderEndOfVP;
	virtual BOOL OnInitDialog();
};
