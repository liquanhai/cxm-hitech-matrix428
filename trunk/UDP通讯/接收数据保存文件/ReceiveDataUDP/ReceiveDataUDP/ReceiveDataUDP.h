// ReceiveDataUDP.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CReceiveDataUDPApp:
// �йش����ʵ�֣������ ReceiveDataUDP.cpp
//

class CReceiveDataUDPApp : public CWinApp
{
public:
	CReceiveDataUDPApp();

// ��д
	public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CReceiveDataUDPApp theApp;