// ��ͼ����.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// C��ͼ����App:
// �йش����ʵ�֣������ ��ͼ����.cpp
//

class C��ͼ����App : public CWinApp
{
public:
	C��ͼ����App();

// ��д
	public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern C��ͼ����App theApp;