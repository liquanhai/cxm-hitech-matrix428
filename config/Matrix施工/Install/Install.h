// Install.h : Install Ӧ�ó������ͷ�ļ�
//
#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"       // ������


// CInstallApp:
// �йش����ʵ�֣������ Install.cpp
//
#include "..\common\SocketParam.h"
#include "..\common\XMLFileNameParam.h"
#include "..\common\LogMapping.h"
#include "SocketInstall.h"
class CInstallApp : public CWinApp,
					public CBCGPWorkspace
{
public:
	CInstallApp();
public:
	/** ����IP��ַ*/
	CString			m_strHostIP;
	/** Admin Server����IP��ַ*/
	CString		m_strAdminServerIP;
	/** FTP��������ַ*/
	CString     m_strFTPServerIP;
	/** ����XML�����ļ�����·���� */
	CString     m_strLocalXMLFile;
	/** ������־��Socket�˿� */
	CSocketInstall	m_sockInstall;
	/** ��־�ڴ�ӳ����*/
	CLogMapping		m_LogMapping;

// ��д
public:
	/// ��ʼ������
	BOOL		InitParam();
	/// �ͷŲ���
	BOOL		UninitParam();
	/// ��XML�����ļ�д�뵽FTP��������
	bool		SaveXMLToFTPServer();
	/// д��־
	void		WriteLog(LPCTSTR strPosition,LPCTSTR strDesc,WORD wType=LOGTYPE_NORMAL,BOOL bShowed=FALSE);
public:
	virtual BOOL InitInstance();

// ʵ��
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
	virtual int ExitInstance();
};

extern CInstallApp theApp;