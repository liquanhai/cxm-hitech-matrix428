// StartDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Start.h"
#include "StartDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CStartDlg dialog
//��ӵı�ʶֻ����һ�ε�������, �Լ�����һ������ֵ
extern CString	 g_strProgName;
extern HANDLE    g_hProgValue;  
CStartDlg::CStartDlg(CWnd* pParent /*=NULL*/)
	: CBCGPDialog(CStartDlg::IDD, pParent)
	,m_pDlgLogin(NULL)
	, m_strLocalTime(_T("08:00:00"))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	
	// CBCGPVisualManager2007::SetStyle (CBCGPVisualManager2007::VS2007_Silver);
	// CBCGPVisualManager::SetDefaultManager (RUNTIME_CLASS (CBCGPVisualManager2007));
}

void CStartDlg::DoDataExchange(CDataExchange* pDX)
{
	CBCGPDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BTNCONNECT, m_btnConnect);
	DDX_Control(pDX, IDC_BTNADMINISTRATION, m_btnAdmin);
	DDX_Control(pDX, IDC_BTNINSTALL, m_btnInstall);
	DDX_Control(pDX, IDC_BTNCONFIG, m_btnConfig);
	DDX_Control(pDX, IDC_BTNLINE, m_btnLine);
	DDX_Control(pDX, IDC_BTNOPERATION, m_btnOperation);
	DDX_Control(pDX, IDC_BTNEXPLORER, m_btnExplorer);
	DDX_Text(pDX, IDC_STATICTIME, m_strLocalTime);
	DDX_Control(pDX, IDC_BTNPOSITION, m_btnPosition);
	DDX_Control(pDX, IDC_BTNEXPORT, m_btnExport);
	DDX_Control(pDX, IDC_BTNLOG, m_btnLog);
	DDX_Control(pDX, IDC_BTNPLOTTER, m_btnPlotter);
}

BEGIN_MESSAGE_MAP(CStartDlg, CBCGPDialog)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_BTNINSTALL, &CStartDlg::OnBnClickedBtninstall)
	ON_WM_CONTEXTMENU()
	ON_COMMAND(ID_START_EXIT, &CStartDlg::OnStartExit)
	ON_BN_CLICKED(IDC_BTNCONFIG, &CStartDlg::OnBnClickedBtnconfig)
	ON_BN_CLICKED(IDC_BTNLINE, &CStartDlg::OnBnClickedBtnline)
	ON_BN_CLICKED(IDC_BTNOPERATION, &CStartDlg::OnBnClickedBtnoperation)
	ON_COMMAND(ID_START_CONNECTION, &CStartDlg::OnStartConnection)
	ON_BN_CLICKED(IDC_BTNCONNECT, &CStartDlg::OnBnClickedBtnconnect)
	ON_MESSAGE(WM_DLGLOGINDESTROY,&CStartDlg::OnDlgLoginDestroy)
	ON_WM_DESTROY()
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BTNEXPLORER, &CStartDlg::OnBnClickedBtnexplorer)
	ON_WM_NCHITTEST()
	ON_BN_CLICKED(IDC_BTNADMINISTRATION, &CStartDlg::OnBnClickedBtnadministration)
END_MESSAGE_MAP()


// CStartDlg message handlers

BOOL CStartDlg::OnInitDialog()
{
	CBCGPDialog::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
	SetProp(m_hWnd,g_strProgName,g_hProgValue);
	// ���ð�ť�ķ��
	SetButtonStyle(m_btnConnect,IDB_BITMAPCONNECT,_T("Connection"));
	SetButtonStyle(m_btnAdmin,IDB_BITMAPADMIN,_T("Administration"));
	SetButtonStyle(m_btnInstall,IDB_BITMAPINSTALL,_T("Installation"));
	SetButtonStyle(m_btnConfig,IDB_BITMAPCONFIG,_T("Configuration"));
	SetButtonStyle(m_btnLine,IDB_BITMAPLINE,_T("Line"));
	SetButtonStyle(m_btnOperation,IDB_BITMAPOPERATION,_T("Operation"));
	SetButtonStyle(m_btnPosition,IDB_BITMAPPOSITION,_T("Positioning"));
	SetButtonStyle(m_btnExport,IDB_BITMAPEXPORT,_T("Export"));
	SetButtonStyle(m_btnLog,IDB_BITMAPLOG,_T("Log"));
	SetButtonStyle(m_btnPlotter,IDB_BITMAPPLOTTER,_T("Plotter"));
	SetButtonStyle(m_btnExplorer,IDB_BITMAPEXPLORER,_T("WebSite"));
		
	CBCGPVisualManager2007::SetStyle (CBCGPVisualManager2007::VS2007_Silver);
	CBCGPVisualManager::SetDefaultManager (RUNTIME_CLASS (CBCGPVisualManager2007));
	EnableVisualManagerStyle(TRUE,TRUE);
	// ��ֹ������ģ�����������ť
	EnableProgramButton(FALSE);

	DisplayLocalTime();
	SetTimer(100,1000,NULL);
	theApp.m_sockAdminServer.m_pDlg = this;
	if(!theApp.m_sockAdminServer.CreateSocket(START_USERANDLOGPORT,theApp.m_strHostIP))
	{
		AfxMessageBox(_T("Creating socket port failed!"));
	}
	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CStartDlg::OnPaint()
{
	if (IsIconic())
	{		
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CBCGPDialog::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CStartDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CStartDlg::OnDestroy()
{
	CBCGPDialog::OnDestroy();
	theApp.m_sockAdminServer.Close();
}

/**
 * @brief ���ð�ť�ķ��
 * @note  ���öԻ����и�����������ť�ķ��
 * @param  CBCGPButton& ctrlButton, ��ť����
 * @param  UINT nBitmapID, ��ʾ��λͼ
 * @param  LPCTSTR strTooltip�� ��ʾ��ʾ��Ϣ�����Ϊ��ָ�룬����ʾ��
 * @return void
 */
void CStartDlg::SetButtonStyle(CBCGPButton& ctrlButton,UINT nBitmapID,LPCTSTR strTooltip)
{
	ctrlButton.m_nFlatStyle = CBCGPButton::BUTTONSTYLE_SEMIFLAT;
	ctrlButton.SetWindowText (_T(""));
	// ͼ��λ�ڰ�ť����
	ctrlButton.m_bRighImage = FALSE;
	ctrlButton.m_bTopImage = TRUE;
	ctrlButton.SetImage(nBitmapID);
	if(strTooltip)
	{
		ctrlButton.SetTooltip(strTooltip);
	}
}
/**
 * @brief ʹ�ܳ���������ť
 * @note  �û���¼�ɹ���ʹ�ܸ�����������ť��ʧ�����ֹ������ť
 * @param  bool bEnable�Ƿ�ʹ�ܣ�
 * @return void
 */
void CStartDlg::EnableProgramButton(bool bEnable)
{
	m_btnAdmin.EnableWindow(bEnable);
	m_btnInstall.EnableWindow(bEnable);
	m_btnConfig.EnableWindow(bEnable);
	m_btnLine.EnableWindow(bEnable);
	m_btnOperation.EnableWindow(bEnable);

	m_btnPosition.EnableWindow(bEnable);
	m_btnExport.EnableWindow(bEnable);
	m_btnLog.EnableWindow(bEnable);
	m_btnPlotter.EnableWindow(bEnable);
//	m_btnExplorer.EnableWindow(bEnable);
}

/**
 * @brief ��Ӧ����Ҽ�����ʾ�����˵�
 * @note  ��Ӧ����Ҽ�����ʾ�����˵�
 * @param  CWnd* pWnd, CPoint point
 * @return void
 */
void CStartDlg::OnContextMenu(CWnd* /*pWnd*/, CPoint point)
{
	// TODO: �ڴ˴������Ϣ����������	
	/*
	CRect rc;
	m_btnConnect.GetWindowRect(&rc);
	if(!rc.PtInRect(point))
		return;
	*/
	CMenu menu;
	VERIFY(menu.LoadMenu (IDR_POPUP_CONNECTION));

	CMenu* pPopup = menu.GetSubMenu(0);
	ASSERT(pPopup != NULL);

	CBCGPPopupMenu* pPopupMenu = new CBCGPPopupMenu;
	pPopupMenu->Create (this, point.x, point.y, pPopup->Detach (),FALSE,TRUE);

	return ;
}

void CStartDlg::DisplayLocalTime(void)
{
	SYSTEMTIME	sysTime;
	GetLocalTime(&sysTime);
	m_strLocalTime.Format(_T("%02d:%02d:%02d"),sysTime.wHour,sysTime.wMinute,sysTime.wSecond);
	UpdateData(FALSE);
}

void CStartDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	DisplayLocalTime();
	CBCGPDialog::OnTimer(nIDEvent);
}
// ��ӦWM_NCHITTEST��Ϣ����������϶��Ի���
LRESULT CStartDlg::OnNcHitTest(CPoint point)
{	
	UINT nHitTest=CBCGPDialog::OnNcHitTest(point);
	if (nHitTest==HTCLIENT)     // ����ǿͻ���
	{
		nHitTest = HTCAPTION;  // ��������ɱ�����
	}
	return nHitTest;
	//return CBCGPDialog::OnNcHitTest(point);
}
/**
 * @brief �˳�����
 * @note  ��Ӧ�˵� ID_START_EXIT��Ϣ���˳�����
 * @param  void
 * @return void
 */
void CStartDlg::OnStartExit()
{
	if(BCGPMessageBox(_T("Are you sure to exit ?"),MB_YESNO)==IDYES)
		OnOK();
}
/**
 * @brief �û���¼�ɹ�
 * @note  �յ����Է���������֤����֡���û���¼�ɹ�
 * @param  void
 * @return void
 */
void CStartDlg::Login_Success()
{
	if(m_pDlgLogin)
	{
		m_pDlgLogin->DestroyWindow();
		m_pDlgLogin = NULL;
	}
	EnableProgramButton(TRUE);

	//add some code by kuoxin
	PROCESS_INFORMATION process_information;
	STARTUPINFO startup_info;
	BOOL is_ok;
	SecureZeroMemory(&process_information, sizeof(process_information));
	SecureZeroMemory(&startup_info, sizeof(startup_info));

	startup_info.cb = sizeof(startup_info);
	startup_info.dwFlags = STARTF_USESHOWWINDOW;
	startup_info.wShowWindow = SW_MINIMIZE;

	is_ok = CreateProcess(__TEXT("TestSiteManage.exe"), NULL, NULL, NULL, FALSE, NORMAL_PRIORITY_CLASS, 
							NULL, NULL,	&startup_info, &process_information);
	if(is_ok){
		
		Sleep(1000);
		SecureZeroMemory(&process_information, sizeof(process_information));
		CreateProcess(__TEXT("OperationServer.exe"), NULL, NULL, NULL, FALSE, NORMAL_PRIORITY_CLASS, 
					NULL, NULL,	&startup_info, &process_information);
	}
}
/**
 * @brief �û���¼ʧ��
 * @note  �յ����Է���������֤����֡���û���¼ʧ��
 * @param  void
 * @return void
 */
void CStartDlg::Login_Fail()
{
	if(m_pDlgLogin && m_pDlgLogin->GetSafeHwnd())
	{
		m_pDlgLogin->MessageBox(_T("User name or Password is error!"),_T("Error"),MB_OK);
	}
	EnableProgramButton(FALSE);
}
/**
 * @brief ��Ӧ�����Զ�����ϢWM_DLGLOGINDESTROY,�����¼�Ի����˳�
 * @note  ��¼�Ի����˳�ʱ���򸸴��ڷ����Զ�����ϢWM_DLGLOGINDESTROY��֪ͨ�����ڽ���Ӧ��
 ����ָ����ΪNULL��
 * @param  void
 * @return void
 */
LRESULT  CStartDlg::OnDlgLoginDestroy(WPARAM,LPARAM)
{
	m_pDlgLogin = NULL;
	return 0;
}
/**
 * @brief ��Ӧ�������ϵġ�Connect����ť
 * @note  ��Ӧ�������ϵġ�Connect����ť�����һ��˵���Connection��������ͬ��
 ������ģʽ��¼�Ի������û���д��Ҫ��¼�ķ�������ַ���û������������Ϣ��
 * @param  void
 * @return void
 */
void CStartDlg::OnBnClickedBtnconnect()
{
	OnStartConnection();
}

/**
 * @brief ��Ӧ�Ҽ��ġ�Connection���˵�
 * @note  ������ģʽ��¼�Ի������û���д��Ҫ��¼�ķ�������ַ���û������������Ϣ
 * @param  void
 * @return void
 */
void CStartDlg::OnStartConnection()
{
	// TODO: �ڴ���������������
	if(m_pDlgLogin && m_pDlgLogin->GetSafeHwnd())
	{
		m_pDlgLogin->DestroyWindow();
		delete m_pDlgLogin;
		m_pDlgLogin = NULL;
	}
	m_pDlgLogin = new CDlgLoginAdminServer;
	m_pDlgLogin->Create(IDD_CONNECTIONDLG,this);
	m_pDlgLogin->ShowWindow(SW_SHOW);
}
/**
 * @brief ����Admin����
 * @note  ���Admin��ť�������������������
 * @param  void
 * @return void
 */
void CStartDlg::OnBnClickedBtnadministration()
{
	PROCESS_INFORMATION pi;
	STARTUPINFO si;
	//��ʼ������
	memset(&si,0,sizeof(si));
	si.cb=sizeof(si);
	si.wShowWindow=SW_SHOW;
	si.dwFlags=STARTF_USESHOWWINDOW;

	CString CmdLine=_T("Admin.exe ");
	//CmdLine+=theApp.m_strHostIP;
	//CmdLine+=_T(" ");
	//CmdLine+=theApp.m_strAdminServerIP;
	// LPTSTR Cmd=(LPTSTR)(LPCTSTR)CmdLine;
	//�򿪼��±�����
	BOOL fRet=CreateProcess(_T("Admin.exe "),
		NULL,
		NULL,
		NULL,
		FALSE,
		NORMAL_PRIORITY_CLASS|CREATE_NEW_CONSOLE,
		NULL,
		NULL,
		&si,
		&pi);

	if(!fRet)
	{			
		BCGPMessageBox(_T("Start the Admin program fails!"),MB_OK);
		return;
	}
	// �ȵ��ӽ��̲���.
	//WaitForSingleObject( pi.hProcess, INFINITE );
	// Close process and thread handles. 
	CloseHandle( pi.hProcess );
	CloseHandle( pi.hThread );
}

/**
 * @brief ������װ����
 * @note  ���Install��ť��������װ����
 * @param  void
 * @return void
 */
void CStartDlg::OnBnClickedBtninstall()
{
	PROCESS_INFORMATION pi;
	STARTUPINFO si;
	//��ʼ������
	memset(&si,0,sizeof(si));
	si.cb=sizeof(si);
	si.wShowWindow=SW_SHOW;
	si.dwFlags=STARTF_USESHOWWINDOW;

	CString CmdLine=_T("Install.exe");  
	// LPTSTR Cmd=(LPTSTR)(LPCTSTR)CmdLine;
	// �򿪼��±�����
	BOOL fRet=CreateProcess(CmdLine,
		NULL,
		NULL,
		NULL,
		FALSE,
		NORMAL_PRIORITY_CLASS|CREATE_NEW_CONSOLE,
		NULL,
		NULL,
		&si,
		&pi);

	if(!fRet)
	{			
		BCGPMessageBox(_T("Start the Install program fails!"),MB_OK);
		return;
	}
	// �ȵ��ӽ��̲���.
	//WaitForSingleObject( pi.hProcess, INFINITE );
	// Close process and thread handles. 
	CloseHandle( pi.hProcess );
	CloseHandle( pi.hThread );
}
/**
 * @brief �������ó���
 * @note  ���Config��ť���������ó���
 * @param  void
 * @return void
 */
void CStartDlg::OnBnClickedBtnconfig()
{
	PROCESS_INFORMATION pi;
	STARTUPINFO si;
	//��ʼ������
	memset(&si,0,sizeof(si));
	si.cb=sizeof(si);
	si.wShowWindow=SW_SHOW;
	si.dwFlags=STARTF_USESHOWWINDOW;

	CString CmdLine=_T("Config.exe");  
	// LPTSTR Cmd=(LPTSTR)(LPCTSTR)CmdLine;
	//�򿪼��±�����
	BOOL fRet=CreateProcess(CmdLine,
		NULL,
		NULL,
		NULL,
		FALSE,
		NORMAL_PRIORITY_CLASS|CREATE_NEW_CONSOLE,
		NULL,
		NULL,
		&si,
		&pi);

	if(!fRet)
	{			
		BCGPMessageBox(_T("Start the Config program fails!"),MB_OK);
		return;
	}
	// �ȵ��ӽ��̲���.
	//WaitForSingleObject( pi.hProcess, INFINITE );
	// Close process and thread handles. 
	CloseHandle( pi.hProcess );
	CloseHandle( pi.hThread );
}
/**
 * @brief �������ó���
 * @note  ���Config��ť���������ó���
 * @param  void
 * @return void
 */
void CStartDlg::OnBnClickedBtnline()
{
	PROCESS_INFORMATION pi;
	STARTUPINFO si;
	//��ʼ������
	memset(&si,0,sizeof(si));
	si.cb=sizeof(si);
	si.wShowWindow=SW_SHOW;
	si.dwFlags=STARTF_USESHOWWINDOW;

	CString CmdLine=_T("Line.exe");  
	// LPTSTR Cmd=(LPTSTR)(LPCTSTR)CmdLine;
	//�򿪼��±�����
	BOOL fRet=CreateProcess(CmdLine,
		NULL,
		NULL,
		NULL,
		FALSE,
		NORMAL_PRIORITY_CLASS|CREATE_NEW_CONSOLE,
		NULL,
		NULL,
		&si,
		&pi);

	if(!fRet)
	{			
		BCGPMessageBox(_T("Start the Line program fails!"),MB_OK);
		return;
	}
	// �ȵ��ӽ��̲���.
	//WaitForSingleObject( pi.hProcess, INFINITE );
	// Close process and thread handles. 
	CloseHandle( pi.hProcess );
	CloseHandle( pi.hThread );
}
/**
 * @brief ����ʩ������
 * @note  ���Operation��ť������ʩ������
 * @param  void
 * @return void
 */
void CStartDlg::OnBnClickedBtnoperation()
{
	PROCESS_INFORMATION pi;
	STARTUPINFO si;
	//��ʼ������
	memset(&si,0,sizeof(si));
	si.cb=sizeof(si);
	si.wShowWindow=SW_SHOW;
	si.dwFlags=STARTF_USESHOWWINDOW;

	CString CmdLine=_T("Operation.exe");  
	// LPTSTR Cmd=(LPTSTR)(LPCTSTR)CmdLine;
	//�򿪼��±�����
	BOOL fRet=CreateProcess(CmdLine,
		NULL,
		NULL,
		NULL,
		FALSE,
		NORMAL_PRIORITY_CLASS|CREATE_NEW_CONSOLE,
		NULL,
		NULL,
		&si,
		&pi);

	if(!fRet)
	{			
		BCGPMessageBox(_T("Start the Operation program fails!"),MB_OK);
		return;
	}
	// �ȵ��ӽ��̲���.
	//WaitForSingleObject( pi.hProcess, INFINITE );
	// Close process and thread handles. 
	CloseHandle( pi.hProcess );
	CloseHandle( pi.hThread );
}



void CStartDlg::OnBnClickedBtnexplorer()
{
	SHELLEXECUTEINFO ShExecInfo;
	ShExecInfo.cbSize = sizeof(SHELLEXECUTEINFO);
	ShExecInfo.fMask      = NULL;
	ShExecInfo.hwnd      = NULL;
	ShExecInfo.lpVerb     = NULL;
	ShExecInfo.lpFile      = _T("iexplore.exe");         // ִ�еĳ�����
	ShExecInfo.lpParameters = NULL;
	ShExecInfo.lpDirectory      = NULL;
	ShExecInfo.nShow           = SW_MAXIMIZE;                 // ȫ����ʾ�������
	ShExecInfo.hInstApp = NULL;

	ShellExecuteEx(&ShExecInfo);
//  ShellExecute(0,   NULL,   "http://www.szonline.net ",   NULL,NULL,   SW_NORMAL);
	/*
	PROCESS_INFORMATION pi;
	STARTUPINFO si;
	//��ʼ������
	memset(&si,0,sizeof(si));
	si.cb=sizeof(si);
	si.wShowWindow=SW_SHOW;
	si.dwFlags=STARTF_USESHOWWINDOW;
	
	CString CmdLine=_T("IExplorer.exe");  
	LPTSTR Cmd=(LPTSTR)(LPCTSTR)CmdLine;
	//�򿪼��±�����
	BOOL fRet=CreateProcess(NULL,
		Cmd,
		NULL,
		NULL,
		FALSE,
		NORMAL_PRIORITY_CLASS|CREATE_NEW_CONSOLE,
		NULL,
		NULL,
		&si,
		&pi);

	if(!fRet)
	{			
		BCGPMessageBox(_T("Start the Operation program fails!"),MB_OK);
		return;
	}
	// �ȵ��ӽ��̲���.
	//WaitForSingleObject( pi.hProcess, INFINITE );
	// Close process and thread handles. 
	CloseHandle( pi.hProcess );
	CloseHandle( pi.hThread );
	*/
}


