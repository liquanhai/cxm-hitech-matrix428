
// SocketSend.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CSocketSendApp:
// �йش����ʵ�֣������ SocketSend.cpp
//

class CSocketSendApp : public CWinApp
{
public:
	CSocketSendApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CSocketSendApp theApp;