// Start.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CStartApp:
// See Start.cpp for the implementation of this class
//
#include "..\common\LogMapping.h"
#include "..\common\UserInfo.h"
#include "..\common\StartParseXML.h"
#include "SocketAdminServer.h"
class CStartApp : public CWinApp,
				  public CBCGPWorkspace
{
public:
	CStartApp();
	// ����
public:
	//////////////////////////////////////////////////////////////////////////
	/** ����IP��ַ */
	CString		m_strHostIP;
	/** Admin Server����IP��ַ*/
	CString		m_strAdminServerIP;
	/** ����������ͨ��socket������û�������־���� */
	CSocketAdminServer	m_sockAdminServer;
	/** FTP��������ַ*/
	CString     m_strFTPServerIP;
	/** ����XML�����ļ�����·���� */
	CString     m_strLocalXMLFile;
	//////////////////////////////////////////////////////////////////////////
	/** ���շ�����־Socket */
	// CSocketLogInfo		m_sockLogInfo;
	/** ��־�ڴ�ӳ����*/
	CLogMapping			m_LogMapping;
	/** ������־���� */
	CLogBase			m_Log;	
	//////////////////////////////////////////////////////////////////////////
	/** ��ǰ�û���Ϣ */
	CUserInfo			m_UserInfo;
	/** ��¼�ɹ�*/
	BOOL				m_bUserLogin;
// Overrides
public:
	virtual BOOL InitInstance();
	
	BOOL  InitParam();
	BOOL  UninitParam();
// Implementation

	DECLARE_MESSAGE_MAP()
	virtual int ExitInstance();
	// ���ý�����
	// void SetVisualManager(int nVisualIndex);
};

extern CStartApp theApp;