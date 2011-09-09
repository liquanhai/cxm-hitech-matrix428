// Admin.h : Admin Ӧ�ó������ͷ�ļ�
//
#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"       // ������


#include "..\common\UserInfo.h"
#include "..\common\SocketParam.h"
#include "..\common\LogMapping.h"
#include "SocketUserAdmin.h"
// �Զ�����Ϣ
// �յ�����������ȫ���û���Ϣ�󣬷��͸���Ϣ
#define		WM_GETALLUSERINFO		WM_USER+200

// CAdminApp:
// �йش����ʵ�֣������ Admin.cpp
//
class CAdminApp : public CWinApp,
			      public CBCGPWorkspace
{
public:
	CAdminApp();

	//////////////////////////////////////////////////////////////////////////
	/** ����IP */ 
	CString			m_strHostIP;
	/** Admin Server����IP��ַ*/
	CString		m_strAdminServerIP;
	////////////////////////////�û�����//////////////////////////////////////
	/** �����û���Ϣ*/
	CUserInfos		m_AllUserInfo;
	/** �����û��˿�*/
	CSocketUserAdmin	m_sockUserAdmin;
	/** ��־�ڴ�ӳ����*/
	CLogMapping		m_LogMapping;
	// ����
public:	
	/// ��ʼ������
	BOOL		InitParam();
	/// �ͷŲ���
	BOOL		UninitParam();
	/// д��־
	void		WriteLog(LPCTSTR strPosition,LPCTSTR strDesc,WORD wType=LOGTYPE_NORMAL,BOOL bShowed=FALSE);
// ��д
public:
	virtual BOOL InitInstance();

// ʵ��
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()

	virtual int ExitInstance();
};

extern CAdminApp theApp;