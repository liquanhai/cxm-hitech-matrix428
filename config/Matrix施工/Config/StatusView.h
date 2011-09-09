#pragma once
#include "afxwin.h"



// CStatusView ������ͼ

class CStatusView : public CBCGPFormView
{
	DECLARE_DYNCREATE(CStatusView)

protected:
	CStatusView();           // ��̬������ʹ�õ��ܱ����Ĺ��캯��
	virtual ~CStatusView();
public:
	CStatic m_ctrlStatic;
	CListBox m_ctrlListBox;
public:
	enum { IDD = IDD_CONFIG_STATUS };
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	afx_msg void OnSize(UINT nType, int cx, int cy);
	DECLARE_MESSAGE_MAP()
public:
	virtual void OnInitialUpdate();
	void AppendLog(LPCTSTR strLog);
	
};



