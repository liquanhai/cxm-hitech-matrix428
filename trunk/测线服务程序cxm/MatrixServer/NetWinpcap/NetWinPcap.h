
// NetWinPcap.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CNetWinPcapApp:
// �йش����ʵ�֣������ NetWinPcap.cpp
//

class CNetWinPcapApp : public CWinApp
{
public:
	CNetWinPcapApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CNetWinPcapApp theApp;