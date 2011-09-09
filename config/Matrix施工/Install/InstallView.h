// InstallView.h : CInstallView ��Ľӿ�
//


#pragma once
#include "afxwin.h"
#include "SetupMainView.h"
#include "SetupScalabilityView.h"
#include "../common/InstallParam.h"
#include "../common/InstallParseXML.h"
class CInstallView : public CBCGPFormView
{
	DECLARE_DYNCREATE(CInstallView)

protected: // �������л�����
	CInstallView();
	virtual ~CInstallView();

// ����
public:
	enum { IDD = IDD_INSTALLVIEW };
	CInstallParam				m_InstallParam;
	CInstallParseXML			m_ParseXML;
	CButton						m_BtnApply;
	CBCGPTabWnd					m_wndTab;
	CSetupMainView				m_MainView;
	CSetupScalabilityView		m_ScalabilityView;
// ����
public:
	CInstallDoc* GetDocument() const;
// ��д
public:	
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
private:
	void CreateTabWnd(void);

// ʵ��
public:
	
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif
// ���ɵ���Ϣӳ�亯��
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);

	virtual void OnInitialUpdate();
	afx_msg void OnSize(UINT nType, int cx, int cy);

	afx_msg void OnBnClickedBtnapply();
};

#ifndef _DEBUG  // InstallView.cpp �еĵ��԰汾
inline CInstallDoc* CInstallView::GetDocument() const
   { return reinterpret_cast<CInstallDoc*>(m_pDocument); }
#endif

