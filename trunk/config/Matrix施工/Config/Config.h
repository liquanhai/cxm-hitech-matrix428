// Config.h : main header file for the Config application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// CConfigApp:
// See Config.cpp for the implementation of this class
//
#include "..\common\SocketParam.h"
#include "..\common\XMLFileNameParam.h"
#include "..\common\LogMapping.h"
#include "SocketConfig.h"
class CConfigApp : public CWinApp,
					public CBCGPWorkspace
{
public:
	CConfigApp();
	/** ����IP��ַ*/
	CString			m_strHostIP;
	/** Admin Server����IP��ַ*/
	CString		m_strAdminServerIP;
	/** FTP��������ַ*/
	CString     m_strFTPServerIP;
	/** ����XML�����ļ�����·���� */
	CString     m_strLocalXMLFile;
	/** ������־��Socket�˿� */
	CSocketConfig	m_sockConfig;
	/** ��־�ڴ�ӳ����*/
	CLogMapping		m_LogMapping;
// ����
public:	
	/// ��ʼ������
	BOOL		InitParam();
	/// �ͷŲ���
	BOOL		UninitParam();
	/// ��XML�����ļ�д�뵽FTP��������
	bool	SaveXMLToFTPServer();
	/// д��־
	void		WriteLog(LPCTSTR strPosition,LPCTSTR strDesc,WORD wType=LOGTYPE_NORMAL,BOOL bShowed=FALSE);
// Overrides
public:
// Implementation
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
	
};

extern CConfigApp theApp;