// SendDataUDP.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CSendDataUDPApp:
// �йش����ʵ�֣������ SendDataUDP.cpp
//

class CSendDataUDPApp : public CWinApp
{
public:
	CSendDataUDPApp();

// ��д
	public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CSendDataUDPApp theApp;