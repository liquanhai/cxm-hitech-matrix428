#if !defined(AFX_BCGCBDOTNETEXAMPLE_H__AEAC1B76_E65E_4075_9A38_537CC10CEC1F__INCLUDED_)
#define AFX_BCGCBDOTNETEXAMPLE_H__AEAC1B76_E65E_4075_9A38_537CC10CEC1F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols
#include "../common/MatrixDef.h"
/**
*@brief ���߿ͻ���App��
*/
class CBCGPVisualStudioGUIDemoApp : public CWinApp , public CBCGPWorkspace
{
public:
	CBCGPVisualStudioGUIDemoApp();
	virtual ~CBCGPVisualStudioGUIDemoApp();

	BOOL	m_bHiColorIcons;
	
	// Override from CBCGPWorkspace
	virtual void PreLoadState();
	virtual void LoadCustomState ();
	virtual void SaveCustomState ();

	/** �����б��ĵ�ģ��*/
	CMultiDocTemplate* m_pDocTemplateInstrumentList;
	/** �첨���б��ĵ�ģ��*/
	CMultiDocTemplate* m_pDocTemplateSensorList;

	/** ����ͼ���ĵ�ģ��*/
	CMultiDocTemplate* m_pDocTemplateInstrumentGraph;
	/** �첨��ͼ���ĵ�ģ��*/
	CMultiDocTemplate* m_pDocTemplateSensorGraph;
	/** �������ͼ���ĵ�ģ��*/
	CMultiDocTemplate* m_pDocTemplateSeismonitorGraph;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBCGPVisualStudioGUIDemoApp)
	public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	virtual BOOL SaveAllModified();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CBCGPVisualStudioGUIDemoApp)
	afx_msg void OnAppAbout();
	afx_msg void OnViewAppLook();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


extern CBCGPVisualStudioGUIDemoApp theApp;


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BCGCBDOTNETEXAMPLE_H__AEAC1B76_E65E_4075_9A38_537CC10CEC1F__INCLUDED_)
