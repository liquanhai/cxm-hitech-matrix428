// Draw3DGraph.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CDraw3DGraphApp:
// �йش����ʵ�֣������ Draw3DGraph.cpp
//

class CDraw3DGraph_Test1App : public CWinApp
{
public:
	CDraw3DGraph_Test1App();

// ��д
	public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CDraw3DGraph_Test1App theApp;