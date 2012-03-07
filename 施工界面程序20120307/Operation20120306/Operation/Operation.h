// Operation.h : Operation Ӧ�ó������ͷ�ļ�
//
#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"       // ������

#include "..\common\SocketParam.h"
#include "..\common\XMLFileNameParam.h"
#include "..\common\ConfigParseXML.h"
#include "..\common\LogMapping.h"
#include "SocketLogInfo.h"
// COperationApp:
// �йش����ʵ�֣������ Operation.cpp
//

class COperationApp : public CWinApp,public CBCGPWorkspace
{
	// ����
public:
	COperationApp();
	/** ����IP��ַ*/
	CString		 m_strHostIP;
	/** Admin Server����IP��ַ*/
	CString		m_strAdminServerIP;
	/** FTP��������ַ*/
	CString     m_strFTPServerIP;
	/** ����XML�����ļ�����·���� */
	CString     m_strLocalXMLFile;
	/** ������־��Socket�˿� */
	CSocketLogInfo	m_sockLogInfo;
	/** ��־�ڴ�ӳ����*/
	CLogMapping		m_LogMapping;
protected:
	HINSTANCE    m_hinstBCGCBRes;

public:	
	// cxm 2012.3.7
// 	BOOL  InitParam();
// 	BOOL  UninitParam();
// 	bool  SaveXMLToFTPServer();
// 	void  WriteLog(LPCTSTR strPosition,LPCTSTR strDesc,WORD wType=LOGTYPE_NORMAL,BOOL bShowed=FALSE);	
// ��д
public:
	// Override from CBCGPWorkspace
	virtual void PreLoadState ();
	virtual BOOL InitInstance();
	
// ʵ��
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
	virtual int ExitInstance();
};

extern COperationApp theApp;