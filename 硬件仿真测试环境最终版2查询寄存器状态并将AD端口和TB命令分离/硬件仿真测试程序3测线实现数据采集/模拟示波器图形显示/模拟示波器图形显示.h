// ģ��ʾ����ͼ����ʾ.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CHardwareTestApp:
// �йش����ʵ�֣������ ģ��ʾ����ͼ����ʾ.cpp
//

class CHardwareTestApp : public CWinApp
{
public:
	CHardwareTestApp();

// ��д
	public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CHardwareTestApp theApp;