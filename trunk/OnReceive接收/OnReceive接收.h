// OnReceive����.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// COnReceive����App:
// �йش����ʵ�֣������ OnReceive����.cpp
//

class COnReceive����App : public CWinApp
{
public:
	COnReceive����App();

// ��д
	public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern COnReceive����App theApp;