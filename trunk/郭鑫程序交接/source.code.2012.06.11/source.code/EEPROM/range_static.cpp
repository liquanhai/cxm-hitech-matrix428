// range_static.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "E2PROM_TOOL.h"
#include "range_static.h"


// range_static

IMPLEMENT_DYNAMIC(range_static, CStatic)

range_static::range_static()
{

}

range_static::~range_static()
{
}


BEGIN_MESSAGE_MAP(range_static, CStatic)
	ON_WM_CREATE()
END_MESSAGE_MAP()

// range_static ��Ϣ�������
int range_static::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CStatic::OnCreate(lpCreateStruct) == -1)
		return -1;


	return 0;
}


