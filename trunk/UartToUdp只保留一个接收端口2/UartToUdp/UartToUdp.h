// UartToUdp.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CUartToUdpApp:
// �йش����ʵ�֣������ UartToUdp.cpp
//

class CUartToUdpApp : public CWinApp
{
public:
	CUartToUdpApp();

// ��д
	public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CUartToUdpApp theApp;