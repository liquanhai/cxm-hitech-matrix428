// ShowLocalIPAddress.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CShowLocalIPAddressApp:
// �йش����ʵ�֣������ ShowLocalIPAddress.cpp
//

class CShowLocalIPAddressApp : public CWinApp
{
public:
	CShowLocalIPAddressApp();

// ��д
	public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CShowLocalIPAddressApp theApp;