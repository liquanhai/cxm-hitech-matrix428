// �����ļ��򿪶�ȡ�ٶ�.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CTestFileOpenSpeedApp:
// �йش����ʵ�֣������ �����ļ��򿪶�ȡ�ٶ�.cpp
//

class CTestFileOpenSpeedApp : public CWinApp
{
public:
	CTestFileOpenSpeedApp();

// ��д
	public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CTestFileOpenSpeedApp theApp;