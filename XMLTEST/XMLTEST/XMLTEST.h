// XMLTEST.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CXMLTESTApp:
// �йش����ʵ�֣������ XMLTEST.cpp
//

class CXMLTESTApp : public CWinApp
{
public:
	CXMLTESTApp();

// ��д
	public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CXMLTESTApp theApp;