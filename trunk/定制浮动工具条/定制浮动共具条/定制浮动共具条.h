// ���Ƹ���������.h : ���Ƹ��������� Ӧ�ó������ͷ�ļ�
//
#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"       // ������


// C���Ƹ���������App:
// �йش����ʵ�֣������ ���Ƹ���������.cpp
//

class C���Ƹ���������App : public CWinApp
{
public:
	C���Ƹ���������App();


// ��д
public:
	virtual BOOL InitInstance();

// ʵ��
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern C���Ƹ���������App theApp;