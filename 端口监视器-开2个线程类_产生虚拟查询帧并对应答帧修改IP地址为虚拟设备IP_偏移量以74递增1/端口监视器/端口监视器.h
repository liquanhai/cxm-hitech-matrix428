// �˿ڼ�����.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CPortMonitoringApp:
// �йش����ʵ�֣������ �˿ڼ�����.cpp
//

class CPortMonitoringApp : public CWinApp
{
public:
	CPortMonitoringApp();

// ��д
	public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CPortMonitoringApp theApp;