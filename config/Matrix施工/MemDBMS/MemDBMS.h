// MemDBMS.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CMemDBMSApp:
// �йش����ʵ�֣������ MemDBMS.cpp
//

class CMemDBMSApp : public CWinApp
{
public:
	CMemDBMSApp();

// ��д
	public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CMemDBMSApp theApp;