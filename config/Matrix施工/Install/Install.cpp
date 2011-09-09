// Install.cpp : ����Ӧ�ó��������Ϊ��
//

#include "stdafx.h"
#include "Install.h"
#include "MainFrm.h"

#include "InstallDoc.h"
#include "InstallView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CInstallApp
//��ӵı�ʶֻ����һ�ε�������, �Լ�����һ������ֵ,
// �ڴ��������ʱ����SetProp�������ô������ԡ�
CString	 g_strProgName = _T("��װ����ͻ���V2011");
HANDLE   g_hProgValue = (HANDLE)2;               
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

BEGIN_MESSAGE_MAP(CInstallApp, CWinApp)
	ON_COMMAND(ID_APP_ABOUT, &CInstallApp::OnAppAbout)
	// �����ļ��ı�׼�ĵ�����
	ON_COMMAND(ID_FILE_NEW, &CWinApp::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, &CWinApp::OnFileOpen)
END_MESSAGE_MAP()


// CInstallApp ����

CInstallApp::CInstallApp()
{
	// TODO: �ڴ˴���ӹ�����룬
	// ��������Ҫ�ĳ�ʼ�������� InitInstance ��
	m_strHostIP = _T("127.0.0.1");
	m_strAdminServerIP= _T("255.255.255.255");
	m_strFTPServerIP= _T("255.255.255.255");
	m_strLocalXMLFile = CLIENTDIR_XMLFILE;
	m_strLocalXMLFile += INSTALL_XMLFILE;
}


// Ψһ��һ�� CInstallApp ����

CInstallApp theApp;


// CInstallApp ��ʼ��

BOOL CInstallApp::InitInstance()
{
	HWND oldHWnd = NULL;
	EnumWindows(EnumWndProc,(LPARAM)&oldHWnd);    //ö���������еĴ���
	if(oldHWnd != NULL)
	{		
		::ShowWindow(oldHWnd,SW_SHOWNORMAL);          //�����ҵ���ǰһ������
		::SetForegroundWindow(oldHWnd);                //������Ϊǰ������
		return false;                                  //�˳���������
	}
	// ���һ�������� Windows XP �ϵ�Ӧ�ó����嵥ָ��Ҫ
	// ʹ�� ComCtl32.dll �汾 6 ����߰汾�����ÿ��ӻ���ʽ��
	//����Ҫ InitCommonControlsEx()�����򣬽��޷��������ڡ�
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// ��������Ϊ��������Ҫ��Ӧ�ó�����ʹ�õ�
	// �����ؼ��ࡣ
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
	// ��׼��ʼ��
	// ���δʹ����Щ���ܲ�ϣ����С
	// ���տ�ִ���ļ��Ĵ�С����Ӧ�Ƴ�����
	// ����Ҫ���ض���ʼ������
	// �������ڴ洢���õ�ע�����
	// TODO: Ӧ�ʵ��޸ĸ��ַ�����
	// �����޸�Ϊ��˾����֯��
	SetRegistryKey(_T("BCGSoft\\BCGControlBarPro\\Samples"));

//	LoadStdProfileSettings();  // ���ر�׼ INI �ļ�ѡ��(���� MRU)
	SetRegistryBase (_T("Settings"));

	InitContextMenuManager();
	InitKeyboardManager();
	InitParam();
	// ע��Ӧ�ó�����ĵ�ģ�塣�ĵ�ģ��
	// �������ĵ�����ܴ��ں���ͼ֮�������
	CSingleDocTemplate* pDocTemplate;
	pDocTemplate = new CSingleDocTemplate(
		IDR_MAINFRAME,
		RUNTIME_CLASS(CInstallDoc),
		RUNTIME_CLASS(CMainFrame),       // �� SDI ��ܴ���
		RUNTIME_CLASS(CInstallView));
	if (!pDocTemplate)
		return FALSE;
	AddDocTemplate(pDocTemplate);



	// ������׼������DDE�����ļ�������������
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);


	// ��������������ָ����������
	// �� /RegServer��/Register��/Unregserver �� /Unregister ����Ӧ�ó����򷵻� FALSE��
	if (!ProcessShellCommand(cmdInfo))
		return FALSE;

	LoadCustomState ();

	// Ψһ��һ�������ѳ�ʼ���������ʾ����������и���
	m_pMainWnd->ShowWindow(SW_SHOW);
	m_pMainWnd->UpdateWindow();
	// �������к�׺ʱ�ŵ��� DragAcceptFiles
	//  �� SDI Ӧ�ó����У���Ӧ�� ProcessShellCommand ֮����
	return TRUE;
}

// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CBCGPDialog
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CBCGPDialog(CAboutDlg::IDD)
{
	EnableVisualManagerStyle();
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CBCGPDialog)
END_MESSAGE_MAP()

// �������жԻ����Ӧ�ó�������
void CInstallApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}


// CInstallApp ��Ϣ�������


int CInstallApp::ExitInstance()
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
BOOL  CInstallApp::InitParam()
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
	m_strLocalXMLFile += INSTALL_XMLFILE;
	
	// ������ʾ���������̵�Socket�˿�
	if(!m_sockInstall.CreateSocket(INSTALL_SYSPROGRESS,m_strHostIP))
	{
		AfxMessageBox(_T("������װ�����Socket�˿�ʧ��!"));
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
BOOL  CInstallApp::UninitParam()
{	
	m_sockInstall.Close();
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
void    CInstallApp::WriteLog(LPCTSTR strPosition,LPCTSTR strDesc,WORD wType,BOOL bShowed)
{
	CLogBase	ProgramLog;
	ProgramLog.SetHostAndProgram(m_strHostIP,MATRIX_INSTALL);
	ProgramLog.SetLog(strPosition,strDesc,wType,bShowed);
	// �������������־���ɷ�������¼��־��Ϣ
	BYTE    pBuf[SOCKET_LOGFRM_MAXLEN];
	int nSize = ProgramLog.WriteToSocketFrame(pBuf);

	m_sockInstall.SendTo(pBuf,nSize,ADMINSERVER_LOGPORT,m_strAdminServerIP);	
}
/**
 * @brief �������ļ����浽FTP�������ϣ���������Ϣ֪ͨ��������
 * @note  �������ļ����浽FTP�������ϣ���������Ϣ֪ͨ��������
 * @param  void
 * @return �ɹ��򷵻�true��ʧ���򷵻�false
 */
bool	CInstallApp::SaveXMLToFTPServer()
{	// ��XML�ļ����͵���������
	PutMatrixXMLToFTPServer(m_strFTPServerIP,INSTALL_XMLFILE,m_strLocalXMLFile);
	// ������Ϣ֪ͨ���ص���������
	SendMessage(HWND_BROADCAST,WM_NEWXMLFILE,MATRIX_INSTALL,MATRIX_INSTALL_ALL);
	return true;
}