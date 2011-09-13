// Config.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "Config.h"
#include "MainFrm.h"

#include "ConfigDoc.h"
#include "ConfigView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CConfigApp

BEGIN_MESSAGE_MAP(CConfigApp, CWinApp)
	ON_COMMAND(ID_APP_ABOUT, OnAppAbout)
	// Standard file based document commands
	ON_COMMAND(ID_FILE_NEW, CWinApp::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, CWinApp::OnFileOpen)
END_MESSAGE_MAP()


// CConfigApp construction

CConfigApp::CConfigApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
	m_strHostIP = _T("127.0.0.1");
	m_strAdminServerIP= _T("255.255.255.255");
	m_strFTPServerIP= _T("255.255.255.255");
	m_strLocalXMLFile = CLIENTDIR_XMLFILE;
	m_strLocalXMLFile += CONFIG_XMLFILE;
}


// The one and only CConfigApp object

CConfigApp theApp;


// CConfigApp initialization

BOOL CConfigApp::InitInstance()
{
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

	// Initialize OLE libraries
	if (!AfxOleInit())
	{
		AfxMessageBox(IDP_OLE_INIT_FAILED);
		return FALSE;
	}
	AfxEnableControlContainer();

	globalData.SetDPIAware ();

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	// of your final executable, you should remove from the following
	// the specific initialization routines you do not need
	// Change the registry key under which our settings are stored
	// TODO: You should modify this string to be something appropriate
	// such as the name of your company or organization

	SetRegistryKey(_T("BCGP AppWizard-Generated Applications"));
	LoadStdProfileSettings(4);  // Load standard INI file options (including MRU)

	SetRegistryBase (_T("Settings"));

	InitContextMenuManager();
	InitKeyboardManager();
	InitShellManager();
	InitParam();
	// Register the application's document templates.  Document templates
	//  serve as the connection between documents, frame windows and views
	CSingleDocTemplate* pDocTemplate;
	pDocTemplate = new CSingleDocTemplate(
		IDR_MAINFRAME,
		RUNTIME_CLASS(CConfigDoc),
		RUNTIME_CLASS(CMainFrame),       // main SDI frame window
		RUNTIME_CLASS(CConfigView));
	if (!pDocTemplate)
		return FALSE;
	AddDocTemplate(pDocTemplate);

	// Parse command line for standard shell commands, DDE, file open
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);

	// Dispatch commands specified on the command line.  Will return FALSE if
	// app was launched with /RegServer, /Register, /Unregserver or /Unregister.
	if (!ProcessShellCommand(cmdInfo))
		return FALSE;
	LoadCustomState ();
	// The one and only window has been initialized, so show and update it
	m_pMainWnd->ShowWindow(SW_SHOW);
	m_pMainWnd->UpdateWindow();
	// call DragAcceptFiles only if there's a suffix
	//  In an SDI app, this should occur after ProcessShellCommand
	
	return TRUE;
}

// CAboutDlg dialog used for App About

class CAboutDlg : public CBCGPDialog
{
public:
	CAboutDlg();

// Dialog Data
	enum { IDD = IDD_ABOUTBOX };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CBCGPDialog(CAboutDlg::IDD)
{
	EnableVisualManagerStyle();
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CBCGPDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CBCGPDialog)
END_MESSAGE_MAP()

// App command to run the dialog
void CConfigApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}


// CConfigApp message handlers


int CConfigApp::ExitInstance()
{
	// TODO: �ڴ����ר�ô����/����û���
	UninitParam();
	BCGCBProCleanUp();
	return __super::ExitInstance();
}
/**
 * @brief ��ʼ������
 * @note  ��ʼ����������־�ࡢͨ�Ŷ˿�
 * @param  void
 * @return �ɹ��򷵻�true��ʧ���򷵻�false
 */
BOOL  CConfigApp::InitParam()
{
	// ������־�����ڴ�ӳ����
	if (!m_LogMapping.Open())
	{
		AfxMessageBox(_T("������־�����ڴ�ӳ����ʧ��!"));
		return FALSE;
	}	
	else
	{
		// ����IP
		DWORD dwTemp = m_LogMapping.ReadClientHostIP();
		CLogMapping::DWORDIPToStringIP(dwTemp,m_strHostIP);
		// AdminServer���������IP
		dwTemp = m_LogMapping.ReadAdminServerHostIP();
		CLogMapping::DWORDIPToStringIP(dwTemp,m_strAdminServerIP);
		// FTP������IP��ַ
		dwTemp = m_LogMapping.ReadFTPServerHostIP();
		CLogMapping::DWORDIPToStringIP(dwTemp,m_strFTPServerIP);
	}
	// ��FTP������������XML�����ļ�
	m_strLocalXMLFile = CLIENTDIR_XMLFILE;
	m_strLocalXMLFile += CONFIG_XMLFILE;
	// ������ʾ���������̵�Socket�˿�
	if(!m_sockConfig.CreateSocket(CONFIG_SYSPROGRESS,m_strHostIP))
	{
		AfxMessageBox(_T("������ʾʩ��״̬��Socket�˿�ʧ��!"));
		return FALSE;
	}
	return TRUE;
}
/**
 * @brief �����������
 * @note  ����������󣺹ر��ڴ�ӳ�������ر�ͨ�Ŷ˿�
 * @param  void
 * @return �ɹ��򷵻�true��ʧ���򷵻�false
 */
BOOL  CConfigApp::UninitParam()
{	
	m_sockConfig.Close();
	m_LogMapping.Destroy();
	return TRUE;
}
/**
 * @brief ��־������
 * @note  ������������м�¼ͨ���ú������ͳ�ȥ����AdminServer������պ���֪ͨ�ͻ��ˡ�
 * @param  LPCTSTR strPosition,��־������λ������
 * @param LPCTSTR strDesc,��־����
 * @param WORD wType,��־���ͣ��������쳣�����桢���Ե�
 * @param BOOL bShowed���Ƿ���ʾ���û�
 * @return �ɹ��򷵻�true��ʧ���򷵻�false
 */
void    CConfigApp::WriteLog(LPCTSTR strPosition,LPCTSTR strDesc,WORD wType,BOOL bShowed)
{
	CLogBase	ProgramLog;
	ProgramLog.SetHostAndProgram(m_strHostIP,MATRIX_CONFIG);
	ProgramLog.SetLog(strPosition,strDesc,wType,bShowed);
	// �������������־���ɷ�������¼��־��Ϣ
	BYTE    pBuf[SOCKET_LOGFRM_MAXLEN];
	int nSize = ProgramLog.WriteToSocketFrame(pBuf);
	m_sockConfig.SendTo(pBuf,nSize,ADMINSERVER_LOGPORT,m_strAdminServerIP);	
}
/**
 * @brief �������ļ����浽FTP�������ϣ���������Ϣ֪ͨ��������
 * @note  �������ļ����浽FTP�������ϣ���������Ϣ֪ͨ��������
 * @param  void
 * @return �ɹ��򷵻�true��ʧ���򷵻�false
 */
bool	CConfigApp::SaveXMLToFTPServer()
{	// ��XML�ļ����͵���������
	PutMatrixXMLToFTPServer(m_strFTPServerIP,CONFIG_XMLFILE,m_strLocalXMLFile);
	// ������Ϣ֪ͨ���ص���������
	SendMessage(HWND_BROADCAST,WM_NEWXMLFILE,MATRIX_CONFIG,MATRIX_CONFIG_ALL);
	return true;
}