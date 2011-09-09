#pragma once
#include "afxwin.h"



// CSetupMainView ������ͼ

class CSetupMainView : public CBCGPDialog
{
	DECLARE_DYNCREATE(CSetupMainView)

public:
	CSetupMainView();           // ��̬������ʹ�õ��ܱ����Ĺ��캯��
	virtual ~CSetupMainView();

public:
	enum { IDD = IDD_SETUPMAINVIEW };
/*
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif
*/
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	// afx_msg void OnWindowPosChanging(WINDOWPOS* lpwndpos);
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
	void SetBaudRate(int nBaudRate);
	int GetBaudRate(void);
	// void MouseWheel(short zDelta);
	int m_nVibratorType;
	int m_nBlasterType;
	int m_nNbOfPlotters;
	int m_nPlotterType1;
	CString m_strPlotterName1;
	CString m_strPlotterMacAddress1;
	int m_nPlotterType2;
	CString m_strPlotterName2;
	CString m_strPlotterMacAddress2;
	CComboBox m_ctrlBaudRate;
	
};


