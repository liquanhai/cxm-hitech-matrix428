// ����ѹ������.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// C����ѹ������App:
// �йش����ʵ�֣������ ����ѹ������.cpp
//

class C����ѹ������App : public CWinApp
{
public:
	C����ѹ������App();

// ��д
	public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern C����ѹ������App theApp;