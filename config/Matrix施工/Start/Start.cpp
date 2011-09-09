// Start.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "Start.h"
#include "StartDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CStartApp
//��ӵı�ʶֻ����һ�ε�������, �Լ�����һ������ֵ,
// �ڴ��������ʱ����SetProp�������ô������ԡ�
CString	 g_strProgName = _T("����������");
HANDLE   g_hProgValue = (HANDLE)1;               
// ��EnumWindows�������õĻص��������������Բ��Ҵ���
BOOL CALLBACK EnumWndProc(HWND hwnd,LPARAM lParam)
{
	HANDLE h = GetProp(hwnd,g_strProgName);
	if( h == g_hProgValue)
	{
		*(HWND*)lParam = hwnd;
		return false;
	}
	return true;
}
BEGIN_MESSAGE_MAP(CStartApp, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CStartApp construction

CStartApp::CStartApp()
: m_strHostIP(_T("192.168.0.12"))
, m_strAdminServerIP(_T("192.168.0.12"))
, m_strFTPServerIP(_T("192.168.0.12"))
, m_bUserLogin(FALSE)
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
	globalData.m_bUseVisualManagerInBuiltInDialogs = TRUE;
	m_strLocalXMLFile = CLIENTDIR_XMLFILE;
	m_strLocalXMLFile +=START_XMLFILE;
}


// The one and only CStartApp object

CStartApp theApp;


// CStartApp initialization

BOOL CStartApp::InitInstance()
{
	HWND oldHWnd = NULL;
	EnumWindows(EnumWndProc,(LPARAM)&oldHWnd);    //ö���������еĴ���
	if(oldHWnd != NULL)
	{		
		::ShowWindow(oldHWnd,SW_SHOWNORMAL);          //�����ҵ���ǰһ������
		::SetForegroundWindow(oldHWnd);                //������Ϊǰ������
		return false;                                  //�˳���������
	}

	globalData.SetDPIAware ();
	// InitCommonControlsEx() is required on Windows XP if an application
	// manifest specifies use of ComCtl32.dll version 6 or later to enable
	// visual styles.  Otherwise, any window creation will fail.
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// Set this to include all the common control classes you want to use
	// in your application.
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();

	if (!AfxSocketInit())
	{
		AfxMessageBox(IDP_SOCKETS_INIT_FAILED);
		return FALSE;
	}
	// ��ʼ�� OLE ��
	if (!AfxOleInit())
	{
		AfxMessageBox(IDP_OLE_INIT_FAILED);
		return FALSE;
	}
	AfxEnableControlContainer();

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	// of your final executable, you should remove from the following
	// the specific initialization routines you do not need
	// Change the registry key under which our settings are stored
	// TODO: You should modify this string to be something appropriate
	// such as the name of your company or organization
	SetRegistryKey(_T("BCGSoft\\BCGControlBarPro\\Samples"));
	SetRegistryBase (_T("Settings"));

	InitContextMenuManager();
	InitKeyboardManager();
	InitParam();
	CBCGPVisualManager2007::SetStyle (CBCGPVisualManager2007::VS2007_Silver);
	CBCGPVisualManager::SetDefaultManager (RUNTIME_CLASS (CBCGPVisualManager2007));


	CStartDlg dlg;
	m_pMainWnd = &dlg;
	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with OK
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with Cancel
	}

	// Since the dialog has been closed, return FALSE so that we exit the
	//  application, rather than start the application's message pump.
	return FALSE;
}

int CStartApp::ExitInstance()
{
	// TODO: �ڴ����ר�ô����/����û���
	UninitParam();
	BCGCBProCleanUp();
	return __super::ExitInstance();
}
/**
 * @brief ��ʼ���������
 * @note  �������ļ���������ͨ�Ŷ˿ڣ����������ڴ档
 * @param  void
 * @return BOOL���ɹ�����TRUE��ʧ�ܷ���FALSE
 */
BOOL  CStartApp::InitParam()
{
	// �������ļ�
	CStartParseXML		ParseXMLFile;
	m_strLocalXMLFile = CLIENTDIR_XMLFILE;
	m_strLocalXMLFile +=START_XMLFILE;
	if(!ParseXMLFile.ParseClientComputer(m_strLocalXMLFile,m_strHostIP,m_strFTPServerIP))
	{
		AfxMessageBox(_T("��ȡ�����ļ�ʧ�ܣ�"));
		return FALSE;
	}
	// ������־�����ڴ�ӳ����
	if (!m_LogMapping.Create())
	{
		AfxMessageBox(_T("������־�����ڴ�ӳ����ʧ��!"));
		return FALSE;
	}
	m_LogMapping.WriteClientHostIP(m_strHostIP);
	m_LogMapping.WriteFTPServerHostIP(m_strFTPServerIP);
	return TRUE;
}
/**
 * @brief �ͷų������
 * @note  �ر�����ͨ�Ŷ˿ڡ��ͷŹ����ڴ档
 * @param  void
 * @return BOOL���ɹ�����TRUE��ʧ�ܷ���FALSE
 */
BOOL  CStartApp::UninitParam()
{
	m_LogMapping.Destroy();
	return TRUE;
}
/*
void CStartApp::SetVisualManager(int nVisualIndex) 
{	
	switch (nVisualIndex)
	{
	case 0:
		CBCGPVisualManager::SetDefaultManager (RUNTIME_CLASS (CBCGPVisualManager2003));
		break;

	case 1:
		CBCGPVisualManager::SetDefaultManager (RUNTIME_CLASS (CBCGPWinXPVisualManager));
		break;

	case 2:
		CBCGPVisualManager2007::SetStyle (CBCGPVisualManager2007::VS2007_LunaBlue);
		CBCGPVisualManager::SetDefaultManager (RUNTIME_CLASS (CBCGPVisualManager2007));
		break;

	case 3:
		CBCGPVisualManager2007::SetStyle (CBCGPVisualManager2007::VS2007_ObsidianBlack);
		CBCGPVisualManager::SetDefaultManager (RUNTIME_CLASS (CBCGPVisualManager2007));
		break;

	case 4:
		CBCGPVisualManager2007::SetStyle (CBCGPVisualManager2007::VS2007_Silver);
		CBCGPVisualManager::SetDefaultManager (RUNTIME_CLASS (CBCGPVisualManager2007));
		break;

	case 5:
		CBCGPVisualManager2007::SetStyle (CBCGPVisualManager2007::VS2007_Aqua);
		CBCGPVisualManager::SetDefaultManager (RUNTIME_CLASS (CBCGPVisualManager2007));
		break;

	case 6:
		CBCGPVisualManager::SetDefaultManager (RUNTIME_CLASS (CBCGPVisualManagerCarbon));
		break;

	case 7:
		CBCGPVisualManager::SetDefaultManager (RUNTIME_CLASS (CBCGPVisualManagerVS2010));
		break;

	case 8:
		CBCGPVisualManager2010::SetStyle (CBCGPVisualManager2010::VS2010_Blue);
		CBCGPVisualManager::SetDefaultManager (RUNTIME_CLASS (CBCGPVisualManager2010));
		break;

	case 9:
		CBCGPVisualManager2010::SetStyle (CBCGPVisualManager2010::VS2010_Silver);
		CBCGPVisualManager::SetDefaultManager (RUNTIME_CLASS (CBCGPVisualManager2010));
		break;

	case 10:
		CBCGPVisualManager2010::SetStyle (CBCGPVisualManager2010::VS2010_Black);
		CBCGPVisualManager::SetDefaultManager (RUNTIME_CLASS (CBCGPVisualManager2010));
		break;

	}
	 CBCGPVisualManager::GetInstance()->RedrawAll();
}*/