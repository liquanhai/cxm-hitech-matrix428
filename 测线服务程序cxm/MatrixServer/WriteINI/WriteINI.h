
// WriteINI.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CWriteINIApp:
// �йش����ʵ�֣������ WriteINI.cpp
//

class CWriteINIApp : public CWinApp
{
public:
	CWriteINIApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CWriteINIApp theApp;