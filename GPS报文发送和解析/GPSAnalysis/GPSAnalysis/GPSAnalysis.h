// GPSAnalysis.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CGPSAnalysisApp:
// �йش����ʵ�֣������ GPSAnalysis.cpp
//

class CGPSAnalysisApp : public CWinApp
{
public:
	CGPSAnalysisApp();

// ��д
	public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CGPSAnalysisApp theApp;