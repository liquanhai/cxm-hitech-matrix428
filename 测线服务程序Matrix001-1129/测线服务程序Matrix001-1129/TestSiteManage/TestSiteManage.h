// TestSiteManage.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CTestSiteManageApp:
// �йش����ʵ�֣������ TestSiteManage.cpp
//

class CTestSiteManageApp : public CWinApp
{
public:
	CTestSiteManageApp();

// ��д
	public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CTestSiteManageApp theApp;