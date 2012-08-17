
// MainFrm.cpp : CMainFrame ���ʵ��
//

#include "stdafx.h"
#include "Line.h"

#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWndEx)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWndEx)
	ON_WM_CREATE()
	ON_COMMAND(ID_VIEW_CUSTOMIZE, &CMainFrame::OnViewCustomize)
	ON_REGISTERED_MESSAGE(AFX_WM_CREATETOOLBAR, &CMainFrame::OnToolbarCreateNew)
	ON_MESSAGE(WM_MSG_CLIENT, &CMainFrame::OnMsgClient)
	ON_WM_SETTINGCHANGE()
	ON_WM_CLOSE()
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // ״̬��ָʾ��
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

// CMainFrame ����/����

CMainFrame::CMainFrame()
{
	// TODO: �ڴ���ӳ�Ա��ʼ������
	m_uiServerPort = ServerListenPort;
	m_strServerIP = ServerIP;
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWndEx::OnCreate(lpCreateStruct) == -1)
		return -1;

	BOOL bNameValid;

	// �������ڻ��������û�����Ԫ�ص��Ӿ�������
	CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerVS2008));

	if (!m_wndMenuBar.Create(this))
	{
		TRACE0("δ�ܴ����˵���\n");
		return -1;      // δ�ܴ���
	}

	m_wndMenuBar.SetPaneStyle(m_wndMenuBar.GetPaneStyle() | CBRS_SIZE_DYNAMIC | CBRS_TOOLTIPS | CBRS_FLYBY);

	// ��ֹ�˵����ڼ���ʱ��ý���
	CMFCPopupMenu::SetForceMenuFocus(FALSE);

	if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP | CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndToolBar.LoadToolBar(theApp.m_bHiColorIcons ? IDR_MAINFRAME_256 : IDR_MAINFRAME))
	{
		TRACE0("δ�ܴ���������\n");
		return -1;      // δ�ܴ���
	}

	CString strToolBarName;
	bNameValid = strToolBarName.LoadString(IDS_TOOLBAR_STANDARD);
	ASSERT(bNameValid);
	m_wndToolBar.SetWindowText(strToolBarName);

	CString strCustomize;
	bNameValid = strCustomize.LoadString(IDS_TOOLBAR_CUSTOMIZE);
	ASSERT(bNameValid);
	m_wndToolBar.EnableCustomizeButton(TRUE, ID_VIEW_CUSTOMIZE, strCustomize);

	if (!m_wndStatusBar.Create(this))
	{
		TRACE0("δ�ܴ���״̬��\n");
		return -1;      // δ�ܴ���
	}
	m_wndStatusBar.SetIndicators(indicators, sizeof(indicators)/sizeof(UINT));

	// TODO: �������ϣ���������Ͳ˵�����ͣ������ɾ��������
	m_wndMenuBar.EnableDocking(CBRS_ALIGN_ANY);
	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	DockPane(&m_wndMenuBar);
	DockPane(&m_wndToolBar);


	// ���� Visual Studio 2005 ��ʽͣ��������Ϊ
	CDockingManager::SetDockingMode(DT_SMART);
	// ���� Visual Studio 2005 ��ʽͣ�������Զ�������Ϊ
	EnableAutoHidePanes(CBRS_ALIGN_ANY);

	// ���ز˵���ͼ��(�����κα�׼��������):
	CMFCToolBar::AddToolBarForImageCollection(IDR_MENU_IMAGES, theApp.m_bHiColorIcons ? IDB_MENU_IMAGES_24 : 0);

	// ����ͣ������
	if (!CreateDockingWindows())
	{
		TRACE0("δ�ܴ���ͣ������\n");
		return -1;
	}

	m_wndFileView.EnableDocking(CBRS_ALIGN_ANY);
	m_wndClassView.EnableDocking(CBRS_ALIGN_ANY);
	DockPane(&m_wndFileView);
	CDockablePane* pTabbedBar = NULL;
	m_wndClassView.AttachToTabWnd(&m_wndFileView, DM_SHOW, TRUE, &pTabbedBar);
	m_wndOutput.EnableDocking(CBRS_ALIGN_ANY);
	DockPane(&m_wndOutput);
	m_wndProperties.EnableDocking(CBRS_ALIGN_ANY);
	DockPane(&m_wndProperties);


	// ���ù�������ͣ�����ڲ˵��滻
	EnablePaneMenu(TRUE, ID_VIEW_CUSTOMIZE, strCustomize, ID_VIEW_TOOLBAR);

	// ���ÿ���(��ס Alt �϶�)�������Զ���
	CMFCToolBar::EnableQuickCustomization();

	// @@@�˿ں�IP�������в�������

	m_oComDll.OnInit(_T("MatrixCommDll.dll"), m_uiServerPort, m_strServerIP, this->m_hWnd);
	m_oComDll.m_oXMLDllLine.OnInit(_T("MatrixServerDll.dll"));
	m_oComDll.m_hWnd = m_hWnd;
	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWndEx::PreCreateWindow(cs) )
		return FALSE;
	// TODO: �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	return TRUE;
}

BOOL CMainFrame::CreateDockingWindows()
{
	BOOL bNameValid;

	// ��������ͼ
	CString strClassView;
	bNameValid = strClassView.LoadString(IDS_CLASS_VIEW);
	ASSERT(bNameValid);
	if (!m_wndClassView.Create(strClassView, this, CRect(0, 0, 200, 200), TRUE, ID_VIEW_CLASSVIEW, WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | CBRS_LEFT | CBRS_FLOAT_MULTI))
	{
		TRACE0("δ�ܴ���������ͼ������\n");
		return FALSE; // δ�ܴ���
	}

	// �����ļ���ͼ
	CString strFileView;
	bNameValid = strFileView.LoadString(IDS_FILE_VIEW);
	ASSERT(bNameValid);
	if (!m_wndFileView.Create(strFileView, this, CRect(0, 0, 200, 200), TRUE, ID_VIEW_FILEVIEW, WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | CBRS_LEFT| CBRS_FLOAT_MULTI))
	{
		TRACE0("δ�ܴ������ļ���ͼ������\n");
		return FALSE; // δ�ܴ���
	}

	// �����������
	CString strOutputWnd;
	bNameValid = strOutputWnd.LoadString(IDS_OUTPUT_WND);
	ASSERT(bNameValid);
	if (!m_wndOutput.Create(strOutputWnd, this, CRect(0, 0, 100, 100), TRUE, ID_VIEW_OUTPUTWND, WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | CBRS_BOTTOM | CBRS_FLOAT_MULTI))
	{
		TRACE0("δ�ܴ����������\n");
		return FALSE; // δ�ܴ���
	}

	// �������Դ���
	CString strPropertiesWnd;
	bNameValid = strPropertiesWnd.LoadString(IDS_PROPERTIES_WND);
	ASSERT(bNameValid);
	if (!m_wndProperties.Create(strPropertiesWnd, this, CRect(0, 0, 200, 200), TRUE, ID_VIEW_PROPERTIESWND, WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | CBRS_RIGHT | CBRS_FLOAT_MULTI))
	{
		TRACE0("δ�ܴ��������ԡ�����\n");
		return FALSE; // δ�ܴ���
	}

	SetDockingWindowIcons(theApp.m_bHiColorIcons);
	return TRUE;
}

void CMainFrame::SetDockingWindowIcons(BOOL bHiColorIcons)
{
	HICON hFileViewIcon = (HICON) ::LoadImage(::AfxGetResourceHandle(), MAKEINTRESOURCE(bHiColorIcons ? IDI_FILE_VIEW_HC : IDI_FILE_VIEW), IMAGE_ICON, ::GetSystemMetrics(SM_CXSMICON), ::GetSystemMetrics(SM_CYSMICON), 0);
	m_wndFileView.SetIcon(hFileViewIcon, FALSE);

	HICON hClassViewIcon = (HICON) ::LoadImage(::AfxGetResourceHandle(), MAKEINTRESOURCE(bHiColorIcons ? IDI_CLASS_VIEW_HC : IDI_CLASS_VIEW), IMAGE_ICON, ::GetSystemMetrics(SM_CXSMICON), ::GetSystemMetrics(SM_CYSMICON), 0);
	m_wndClassView.SetIcon(hClassViewIcon, FALSE);

	HICON hOutputBarIcon = (HICON) ::LoadImage(::AfxGetResourceHandle(), MAKEINTRESOURCE(bHiColorIcons ? IDI_OUTPUT_WND_HC : IDI_OUTPUT_WND), IMAGE_ICON, ::GetSystemMetrics(SM_CXSMICON), ::GetSystemMetrics(SM_CYSMICON), 0);
	m_wndOutput.SetIcon(hOutputBarIcon, FALSE);

	HICON hPropertiesBarIcon = (HICON) ::LoadImage(::AfxGetResourceHandle(), MAKEINTRESOURCE(bHiColorIcons ? IDI_PROPERTIES_WND_HC : IDI_PROPERTIES_WND), IMAGE_ICON, ::GetSystemMetrics(SM_CXSMICON), ::GetSystemMetrics(SM_CYSMICON), 0);
	m_wndProperties.SetIcon(hPropertiesBarIcon, FALSE);

}

// CMainFrame ���

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWndEx::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWndEx::Dump(dc);
}
#endif //_DEBUG


// CMainFrame ��Ϣ�������

void CMainFrame::OnViewCustomize()
{
	CMFCToolBarsCustomizeDialog* pDlgCust = new CMFCToolBarsCustomizeDialog(this, TRUE /* ɨ��˵�*/);
	pDlgCust->Create();
}

LRESULT CMainFrame::OnToolbarCreateNew(WPARAM wp,LPARAM lp)
{
	LRESULT lres = CFrameWndEx::OnToolbarCreateNew(wp,lp);
	if (lres == 0)
	{
		return 0;
	}

	CMFCToolBar* pUserToolbar = (CMFCToolBar*)lres;
	ASSERT_VALID(pUserToolbar);

	BOOL bNameValid;
	CString strCustomize;
	bNameValid = strCustomize.LoadString(IDS_TOOLBAR_CUSTOMIZE);
	ASSERT(bNameValid);

	pUserToolbar->EnableCustomizeButton(TRUE, ID_VIEW_CUSTOMIZE, strCustomize);
	return lres;
}

void CMainFrame::OnSettingChange(UINT uFlags, LPCTSTR lpszSection)
{
	CFrameWndEx::OnSettingChange(uFlags, lpszSection);
	m_wndOutput.UpdateFonts();
}


void CMainFrame::OnClose()
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	m_oComDll.m_oXMLDllLine.OnClose();
	m_oComDll.OnClose();
	CFrameWndEx::OnClose();
}

LRESULT CMainFrame::OnMsgClient(WPARAM wParam, LPARAM lParam)
{
	switch(wParam)
	{
	case CmdClientConnect:
		m_wndOutput.m_wndOutputBuild.AddString(_T("Connect to Server!"));
// 		// ��ѯ OperationDelay XML�ļ���Ϣ��֡����Ϊ�գ�
// 		m_oComDll.m_pCommClient->m_oSndFrame.MakeSetFrame(CmdQueryDelayOptXMLInfo, NULL, 0);
// 		// ��ѯ �ڱ� XML�ļ���Ϣ��֡����Ϊ�գ�
// 		m_oComDll.m_pCommClient->m_oSndFrame.MakeSetFrame(CmdQuerySourceShotOptXMLInfo, NULL, 0);
// 		// ��ѯ Explo��Դ���� XML�ļ���Ϣ��֡����Ϊ�գ�
// 		m_oComDll.m_pCommClient->m_oSndFrame.MakeSetFrame(CmdQueryExploOptXMLInfo, NULL, 0);
// 		// ��ѯ Vibro��Դ���� XML�ļ���Ϣ��֡����Ϊ�գ�
// 		m_oComDll.m_pCommClient->m_oSndFrame.MakeSetFrame(CmdQueryVibroOptXMLInfo, NULL, 0);
// 		// ��ѯ ProcessRecord XML�ļ���Ϣ��֡����Ϊ�գ�
// 		m_oComDll.m_pCommClient->m_oSndFrame.MakeSetFrame(CmdQueryProcessRecordOptXMLInfo, NULL, 0);
// 		// ��ѯ ProcessAux XML�ļ���Ϣ��֡����Ϊ�գ�
// 		m_oComDll.m_pCommClient->m_oSndFrame.MakeSetFrame(CmdQueryProcessAuxOptXMLInfo, NULL, 0);
// 		// ��ѯ ProcessAcq XML�ļ���Ϣ��֡����Ϊ�գ�
// 		m_oComDll.m_pCommClient->m_oSndFrame.MakeSetFrame(CmdQueryProcessAcqOptXMLInfo, NULL, 0);
// 		// ��ѯ ProcessType XML�ļ���Ϣ��֡����Ϊ�գ�
// 		m_oComDll.m_pCommClient->m_oSndFrame.MakeSetFrame(CmdQueryProcessTypeOptXMLInfo, NULL, 0);
// 		// ��ѯ ע�� XML�ļ���Ϣ��֡����Ϊ�գ�
// 		m_oComDll.m_pCommClient->m_oSndFrame.MakeSetFrame(CmdQueryCommentsOptXMLInfo, NULL, 0);
// 		break;
// 	case CmdSetDelayOptXMLInfo:
// 		m_wndOutput.AppendLog(_T("Receive the information of delay setup !"));
// 		break;
// 	case CmdSetSourceShotOptXMLInfo:
// 		m_wndOutput.AppendLog(_T("Receive the information of source shot setup !"));
// 		break;
// 	case CmdSetExploOptXMLInfo:
// 		m_wndOutput.AppendLog(_T("Receive the information of explo setup !"));
// 		break;
// 	case CmdSetVibroOptXMLInfo:
// 		m_wndOutput.AppendLog(_T("Receive the information of vibro setup !"));
// 		break;
// 	case CmdSetProcessRecordOptXMLInfo:
// 		break;
// 	case CmdSetProcessAuxOptXMLInfo:
// 		break;
// 	case CmdSetProcessAcqOptXMLInfo:
// 		break;
// 	case CmdSetProcessTypeOptXMLInfo:
// 		m_wndOutput.AppendLog(_T("Receive the information of process setup !"));
// 		break;
// 	case CmdSetCommentsOptXMLInfo:
// 		m_wndOutput.AppendLog(_T("Receive the information of comments setup !"));
// 		break;
	default:
		break;
	}

	return TRUE;
}