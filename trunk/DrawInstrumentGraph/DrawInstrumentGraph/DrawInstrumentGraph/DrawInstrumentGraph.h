// DrawInstrumentGraph.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CDrawInstrumentGraphApp:
// �йش����ʵ�֣������ DrawInstrumentGraph.cpp
//

class CDrawInstrumentGraphApp : public CWinApp
{
public:
	CDrawInstrumentGraphApp();

// ��д
	public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CDrawInstrumentGraphApp theApp;