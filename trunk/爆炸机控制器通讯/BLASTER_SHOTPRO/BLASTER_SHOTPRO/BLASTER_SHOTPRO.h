// BLASTER_SHOTPRO.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CBLASTER_SHOTPROApp:
// �йش����ʵ�֣������ BLASTER_SHOTPRO.cpp
//

class CBLASTER_SHOTPROApp : public CWinApp
{
public:
	CBLASTER_SHOTPROApp();

// ��д
	public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CBLASTER_SHOTPROApp theApp;