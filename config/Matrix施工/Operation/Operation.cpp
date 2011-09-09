// Operation.cpp : ����Ӧ�ó��������Ϊ��
//

#include "stdafx.h"
#include "Operation.h"
#include "MainFrm.h"
#include "OperationDoc.h"
#include "OperationView.h"
#include "..\\common\LineStruct.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// COperationApp
//��ӵı�ʶֻ����һ�ε�������, �Լ�����һ������ֵ,
// �ڴ��������ʱ����SetProp�������ô������ԡ�
CString	 g_strProgName = _T("ʩ���ͻ���2011");
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

BEGIN_MESSAGE_MAP(COperationApp, CWinApp)
	ON_COMMAND(ID_APP_ABOUT, &COperationApp::OnAppAbout)
	// �����ļ��ı�׼�ĵ�����
	ON_COMMAND(ID_FILE_NEW, &CWinApp::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, &CWinApp::OnFileOpen)
	// ��׼��ӡ��������
	ON_COMMAND(ID_FILE_PRINT_SETUP, &CWinApp::OnFilePrintSetup)
END_MESSAGE_MAP()


// COperationApp ����
COperationApp::COperationApp():
	CBCGPWorkspace (TRUE /* m_bResourceSmartUpdate */)
{
	// TODO: �ڴ˴���ӹ�����룬
	// ��������Ҫ�ĳ�ʼ�������� InitInstance ��
	m_strHostIP = _T("127.0.0.1");
	m_strAdminServerIP=_T("255.255.255.255");
	m_strFTPServerIP= _T("255.255.255.255");
	m_strLocalXMLFile = CLIENTDIR_XMLFILE;
	m_strLocalXMLFile += OPERATION_XMLFILE;
}


// Ψһ��һ�� COperationApp ����

COperationApp theApp;


// COperationApp ��ʼ��

BOOL COperationApp::InitInstance()
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
	CWinApp::InitInstance();

	
	globalData.SetDPIAware ();
	AfxEnableControlContainer();
	// ��׼��ʼ��
	// ���δʹ����Щ���ܲ�ϣ����С
	// ���տ�ִ���ļ��Ĵ�С����Ӧ�Ƴ�����
	// ����Ҫ���ض���ʼ������
	// �������ڴ洢���õ�ע�����
	// TODO: Ӧ�ʵ��޸ĸ��ַ�����
	// �����޸�Ϊ��˾����֯��	
	m_bSaveState=FALSE;
	SetRegistryKey(_T("BCGSoft\\BCGControlBarPro\\Samples"));

	//LoadStdProfileSettings();  // Load standard INI file options (including MRU)
	SetRegistryBase (_T("Settings"));

// 	SetRegistryBase (_T("SettingsOperation"));
// 	m_hinstBCGCBRes = LoadLibrary (_T("BCGCBProResCHS.dll"));    // *** - language
// 	BCGCBProSetResourceHandle (m_hinstBCGCBRes);

	// Initialize all Managers for usage. They are automatically constructed
	// if not yet present
	InitContextMenuManager();
	InitKeyboardManager();
	InitParam();

	
	//m_dwHostIP = CIPList::GetLocalIP();
	// ע��Ӧ�ó�����ĵ�ģ�塣�ĵ�ģ��
	// �������ĵ�����ܴ��ں���ͼ֮�������
	CSingleDocTemplate* pDocTemplate;
	pDocTemplate = new CSingleDocTemplate(
		IDR_MAINFRAME,
		RUNTIME_CLASS(COperationDoc),
		RUNTIME_CLASS(CMainFrame),       // �� SDI ��ܴ���
		RUNTIME_CLASS(COperationView));
	//RUNTIME_CLASS(CActiveSourceView));
	if (!pDocTemplate)
		return FALSE;
	AddDocTemplate(pDocTemplate);


	// ������׼������DDE�����ļ�������������
	CCommandLineInfo cmdInfo;	
	ParseCommandLine(cmdInfo);
    // cmdInfo.m_nShellCommand = CCommandLineInfo::FileNothing;

	// ��������������ָ����������
	// �� /RegServer��/Register��/Unregserver �� /Unregister ����Ӧ�ó����򷵻� FALSE��
	if (!ProcessShellCommand(cmdInfo))
		return FALSE;

	// Ψһ��һ�������ѳ�ʼ���������ʾ����������и���
	m_pMainWnd->ShowWindow(SW_SHOWMAXIMIZED);
	m_pMainWnd->UpdateWindow();
	// �������к�׺ʱ�ŵ��� DragAcceptFiles
	//  �� SDI Ӧ�ó����У���Ӧ�� ProcessShellCommand ֮����
	return TRUE;
}



// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialog
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

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()

// �������жԻ����Ӧ�ó�������
void COperationApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();

// 	// BCGPShowAboutDlg(AFX_IDS_APP_TITLE);
}


// COperationApp ��Ϣ�������
int COperationApp::ExitInstance()
{
	// TODO: �ڴ����ר�ô����/����û���
	UninitParam();
	BCGCBProCleanUp();
	/*FreeLibrary (m_hinstBCGCBRes);*/
	return __super::ExitInstance();
}

void COperationApp::PreLoadState ()
{

//	GetContextMenuManager()->AddMenu (_T("My menu"), IDR_CONTEXT_MENU);

	// TODO: add another context menus here
}
/**
 * @brief ��ʼ������
 * @note  ��ʼ����������־�ࡢͨ�Ŷ˿�
 * @param  void
 * @return �ɹ��򷵻�true��ʧ���򷵻�false
 */
BOOL  COperationApp::InitParam()
{
	// ������־�����ڴ�ӳ����
	if (!m_LogMapping.Open())
	{
		AfxMessageBox(_T("������־�����ڴ�ӳ����ʧ��!"));
		return FALSE;
	}	
	else
	{ 
		DWORD dwTemp = m_LogMapping.ReadClientHostIP();
		CLogMapping::DWORDIPToStringIP(dwTemp,m_strHostIP);
		dwTemp = m_LogMapping.ReadAdminServerHostIP();
		CLogMapping::DWORDIPToStringIP(dwTemp,m_strAdminServerIP);
		dwTemp = m_LogMapping.ReadFTPServerHostIP();
		CLogMapping::DWORDIPToStringIP(dwTemp,m_strFTPServerIP);
	}
	// ��FTP������������XML�����ļ�
	m_strLocalXMLFile = CLIENTDIR_XMLFILE;
	m_strLocalXMLFile += OPERATION_XMLFILE;
	if(!m_sockLogInfo.CreateSocket(OPERATION_LOGPORT,m_strHostIP))
	{
		AfxMessageBox(_T("������־Socket�˿�ʧ��!"));
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
BOOL  COperationApp::UninitParam()
{
	m_sockLogInfo.Close();
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
void    COperationApp::WriteLog(LPCTSTR strPosition,LPCTSTR strDesc,WORD wType,BOOL bShowed)
{
	CLogBase	ProgramLog;
	ProgramLog.SetHostAndProgram(m_strHostIP,MATRIX_OPERATION);
	ProgramLog.SetLog(strPosition,strDesc,wType,bShowed);
	// �������������־���ɷ�������¼��־��Ϣ
	BYTE    pBuf[SOCKET_LOGFRM_MAXLEN];
	int nSize = ProgramLog.WriteToSocketFrame(pBuf);
	m_sockLogInfo.SendTo(pBuf,nSize,ADMINSERVER_LOGPORT,m_strAdminServerIP);	
}

/**
 * @brief �������ļ����浽FTP�������ϣ���������Ϣ֪ͨ��������
 * @note  �������ļ����浽FTP�������ϣ���������Ϣ֪ͨ��������
 * @param  void
 * @return �ɹ��򷵻�true��ʧ���򷵻�false
 */
bool	COperationApp::SaveXMLToFTPServer( )
{	// ��XML�ļ����͵���������
	PutMatrixXMLToFTPServer(m_strFTPServerIP,OPERATION_XMLFILE,m_strLocalXMLFile);
	// ������Ϣ֪ͨ���ص���������
	SendMessage(HWND_BROADCAST,WM_NEWXMLFILE,MATRIX_OPERATION,MATRIX_OPERATION_ALL);
	return true;
}