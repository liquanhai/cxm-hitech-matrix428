// RecSocket428XL.cpp : 实现文件
//

#include "stdafx.h"
#include "BLASTER_SHOTPRO.h"
#include "RecSocket428XL.h"


// CRecSocket428XL

CRecSocket428XL::CRecSocket428XL()
{
}

CRecSocket428XL::~CRecSocket428XL()
{
}


// CRecSocket428XL 成员函数

void CRecSocket428XL::OnReceive(int nErrorCode)
{
	// TODO: ÔÚ´ËÌí¼Ó×¨ÓÃ´úÂëºÍ/»òµ÷ÓÃ»ùÀà
	int ret=0;
	CString str;
	CString strshow;
	CWnd* pwnd = AfxGetMainWnd();
	ret=Receive(m_ucRecBuf428XL,256);
	if(ret==ERROR)
	{
		TRACE("ERROR!");
	}
	else if(ret != 0xffffffff) 
	{
		str = &m_ucRecBuf428XL[28];
		int iPos = str.Find(_T("\r\n"), 0);
		strshow = str.Mid(0,iPos);
		pwnd->GetDlgItem(IDC_EDIT_RECSHOW_428XL)->SetWindowText(strshow);
	}

	CSocket::OnReceive(nErrorCode);
}
