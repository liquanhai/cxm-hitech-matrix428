// Operation.h : Operation Ӧ�ó������ͷ�ļ�
//
#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"       // ������


// COperationApp:
// �йش����ʵ�֣������ Operation.cpp
//

class COperationApp : public CWinApp,public CBCGPWorkspace
{
	// ����
public:
	COperationApp();


	HINSTANCE    m_hinstBCGCBRes;
//	DWORD		 m_dwHostIP;
	CString		 m_strHostIP;
	
	
	// Override from CBCGPWorkspace
	virtual void PreLoadState ();
// ��д
public:
	virtual BOOL InitInstance();

// ʵ��
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
	virtual int ExitInstance();
};

extern COperationApp theApp;