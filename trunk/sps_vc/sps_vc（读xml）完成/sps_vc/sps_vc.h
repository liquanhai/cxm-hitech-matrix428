// sps_vc.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// Csps_vcApp:
// �йش����ʵ�֣������ sps_vc.cpp
//

class Csps_vcApp : public CWinApp
{
public:
	Csps_vcApp();

// ��д
	public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern Csps_vcApp theApp;