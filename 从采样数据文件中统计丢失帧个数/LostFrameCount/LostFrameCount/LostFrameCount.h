// LostFrameCount.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CLostFrameCountApp:
// �йش����ʵ�֣������ LostFrameCount.cpp
//

class CLostFrameCountApp : public CWinApp
{
public:
	CLostFrameCountApp();

// ��д
	public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CLostFrameCountApp theApp;