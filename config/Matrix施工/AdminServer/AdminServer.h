// AdminServer.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols

#include "..\common\UserInfo.h"
#include "..\common\SocketParam.h"
#include "..\common\XMLFileNameParam.h"
#include "..\common\CLogBase.h"
#include "LogFile.h"
#include "SocketLogInfo.h"
// CAdminServerApp:
// See AdminServer.cpp for the implementation of this class
//

class CAdminServerApp : public CWinApp
{
public:
	CAdminServerApp();
// ����
public:
	//////////////////////////////////////////////////////////////////////////
	/** ����IP */
	CString			m_strHostIP;
	/** ���������ļ�*/
	CString			m_strLocalXMLFile;
	////////////////////////////�û�����//////////////////////////////////////
	/** �����û���Ϣ*/
	CUserInfos		m_AllUserInfo;
	////////////////////////////��־����////////////////////////////////
	/** ��־��¼*/
	CLogBase		m_Log;
	/** д��־�ļ� */
	CLogFile		m_LogFile;
	/** ������־��Ϣ */
	CSocketLogInfo	m_sockLogInfo;
	//////////////////////////////////////////////////////////////////////////
// Overrides
public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
	virtual int ExitInstance();
};

extern CAdminServerApp theApp;