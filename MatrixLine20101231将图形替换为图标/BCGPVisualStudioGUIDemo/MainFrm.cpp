//*******************************************************************************
// COPYRIGHT NOTES
// ---------------
// This is a sample for BCGControlBar Library Professional Edition
// Copyright (C) 1998-2010 BCGSoft Ltd.
// All rights reserved.
//
// This source code can be used, distributed or modified
// only under terms and conditions 
// of the accompanying license agreement.
//*******************************************************************************
//
// MainFrm.cpp : implementation of the CMainFrame class

#include "stdafx.h"
#include "BCGPVisualStudioGUIDemo.h"
#include "MainFrm.h"

#include "BCGPTabbedControlBar.h"
#include "BCGPMiniFrameWnd.h"

#include "ChildFrm.h"

#include "SensorListView.h"
#include "InstrumentListView.h"

#include "InstrumentGraphView.h"
#include "SensorGraphView.h"
#include "SeismonitorGraphView.h"
#include "SeismonitorGraphChildFrame.h"


UINT WM_MESSAGE_MATRIX_CMD_100;		// �����ͻ��˵�����	100-�ֳ������������

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMainFrame

IMPLEMENT_DYNAMIC(CMainFrame, CMDIFrameWnd)

const int  iMaxUserToolbars		= 10;
const UINT uiFirstUserToolBarId	= AFX_IDW_CONTROLBAR_FIRST + 40;
const UINT uiLastUserToolBarId	= uiFirstUserToolBarId + iMaxUserToolbars - 1;

BEGIN_MESSAGE_MAP(CMainFrame, CMDIFrameWnd)
	//{{AFX_MSG_MAP(CMainFrame)
	ON_WM_CREATE()
	ON_COMMAND(ID_WINDOW_MANAGER, OnWindowManager)
	ON_COMMAND(ID_HELP_KEYBOARDMAP, OnHelpKeyboardmap)
	ON_COMMAND(ID_FILE_NEW_PROJECT, OnFileNewProject)
	ON_COMMAND(ID_FILE_NEW_BLANK_SOLUTION, OnFileNewBlankSolution)
	ON_COMMAND(ID_FILE_OPEN_SOLUTION, OnFileOpenSolution)
	ON_COMMAND(ID_FILE_CLOSE_SOLUTION, OnFileCloseSolution)
	ON_COMMAND(ID_FILE_SAVE_ALL, OnFileSaveAll)
	ON_COMMAND(ID_VIEW_REFRESH, OnViewRefresh)
	ON_COMMAND(ID_TOOLS_CONNECT_TO_DATABASE, OnToolsConnectToDatabase)
	ON_COMMAND(ID_TOOLS_DEBUG_PROCESSES, OnToolsDebugProcesses)
	ON_COMMAND(ID_VIEW_FULLSCREEN, OnViewFullScreen)
	ON_COMMAND(ID_HELP_WEB, OnHelpWeb)
	ON_COMMAND(ID_MDI_MOVE_TO_NEXT_GROUP, OnMdiMoveToNextGroup)
	ON_COMMAND(ID_MDI_MOVE_TO_PREV_GROUP, OnMdiMoveToPrevGroup)
	ON_COMMAND(ID_MDI_NEW_HORZ_TAB_GROUP, OnMdiNewHorzTabGroup)
	ON_COMMAND(ID_MDI_NEW_VERT_GROUP, OnMdiNewVertGroup)
	ON_COMMAND(ID_MDI_CANCEL, OnMdiCancel)
	ON_WM_CLOSE()
	ON_COMMAND(ID_VIEW_OUTPUT, OnViewOutput)
	ON_UPDATE_COMMAND_UI(ID_VIEW_OUTPUT, OnUpdateViewOutput)
	ON_COMMAND(ID_MDI_TABBED_DOCUMENT, OnMdiTabbedDocument)
	ON_UPDATE_COMMAND_UI(ID_MDI_TABBED_DOCUMENT, OnUpdateMdiTabbedDocument)
	ON_WM_SETTINGCHANGE()
	ON_COMMAND(ID_VIEW_CUSTOMIZE, OnViewCustomize)
	ON_REGISTERED_MESSAGE(BCGM_RESETTOOLBAR, OnToolbarReset)
	ON_REGISTERED_MESSAGE(BCGM_ON_GET_TAB_TOOLTIP, OnGetTabToolTip)
	ON_REGISTERED_MESSAGE(BCGM_CUSTOMIZEHELP, OnHelpCustomizeToolbars)
	ON_REGISTERED_MESSAGE(BCGM_CREATETOOLBAR, OnToolbarCreateNew)
	ON_UPDATE_COMMAND_UI(IDS_CARET_POS, OnUpdateCaretPos)
	ON_REGISTERED_MESSAGE(WM_MESSAGE_MATRIX_CMD_100, OnReloadSiteDataCMD)
	ON_COMMAND(ID_MATRIX_INSTRUMENTLIST, OnMatrixInstrumentList)	// �����б���ͼ�˵�����
	ON_COMMAND(ID_MATRIX_SENSORLIST, OnMatrixSensorList)	// �첨���б���ͼ�˵�����
	ON_COMMAND(ID_MATRIX_INSTRUMENTGRAPH, OnMatrixInstrumentGraph)	// �첨��ͼ����ͼ�˵�����
	ON_COMMAND(ID_MATRIX_SENSORGRAPH, OnMatrixSensorGraph)	// ����ͼ����ͼ�˵�����
	ON_COMMAND(ID_MATRIX_SEISMONITORGRAPH, OnMatrixSeismonitorGraph)	// �������ͼ����ͼ�˵�����	
	ON_COMMAND(ID_MATRIX_SURVEYSETUP, OnMatrixSurveySetup)
	ON_COMMAND(ID_MATRIX_LAYOUTSETUP, OnMatrixLayoutSetup)
	ON_COMMAND(ID_MATRIX_SPREADSETUP, OnMatrixSpreadSetup)
	ON_COMMAND(ID_MATRIX_TESTBASESETUP, OnMatrixTestBaseSetup)
	ON_COMMAND(ID_MATRIX_TESTSETUP, OnMatrixTestSetup)
	ON_COMMAND(ID_MATRIX_LOOKSETUP, OnMatrixLookSetup)
	ON_COMMAND(ID_MATRIX_FORMLINESETUP, OnMatrixFormLineSetup)
	ON_COMMAND(ID_BUTTON_MATRIX_FIELD_ON, OnMatrixFieldOn)
	ON_COMMAND(ID_BUTTON_MATRIX_FIELD_OFF, OnMatrixFieldOff)
	ON_COMMAND(ID_MATRIX_VIEWGRAPH, OnToolbarMatrixViewGraph)
	ON_COMMAND(ID_MATRIX_VIEWLIST, OnToolbarMatrixViewList)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // status line indicator
	IDS_CARET_POS,
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL, 
};

/////////////////////////////////////////////////////////////////////////////
// CMainFrame construction/destruction

CMainFrame::CMainFrame()
{
	CBCGPPopupMenu::SetForceShadow (TRUE);

	m_bCanCovertControlBarToMDIChild = TRUE;
	EnableMDITabsLastActiveActivation(TRUE);

	m_pDlgSurveySetup = NULL;	// ��������
	m_pDlgLayoutSetup = NULL;	// ��������
	m_pDlgSpreadSetup = NULL;	// ��������
	m_pDlgTestBaseSetup = NULL;	// ���Ի�������
	m_pDlgTestSetup = NULL;	// ��������
	m_pDlgLookSetup = NULL;	// Look����
	m_pDlgFormLineSetup = NULL;	// FormLine����

	m_byFieldOperation = 0;	// Field ON
}

CMainFrame::~CMainFrame()
{
	if(NULL != m_pDlgSurveySetup)	// ��������
	{
		m_pDlgSurveySetup->DestroyWindow();
		delete m_pDlgSurveySetup;
		m_pDlgSurveySetup = NULL;
	}
	if(NULL != m_pDlgLayoutSetup)	// ��������
	{
		m_pDlgLayoutSetup->DestroyWindow();
		delete m_pDlgLayoutSetup;
		m_pDlgLayoutSetup = NULL;
	}
	if(NULL != m_pDlgSpreadSetup)	// ��������
	{
		m_pDlgSpreadSetup->DestroyWindow();
		delete m_pDlgSpreadSetup;
		m_pDlgSpreadSetup = NULL;
	}
	if(NULL != m_pDlgTestBaseSetup)	// ���Ի�������
	{
		m_pDlgTestBaseSetup->DestroyWindow();
		delete m_pDlgTestBaseSetup;
		m_pDlgTestBaseSetup = NULL;
	}
	if(NULL != m_pDlgTestSetup)	// ��������
	{
		m_pDlgTestSetup->DestroyWindow();
		delete m_pDlgTestSetup;
		m_pDlgTestSetup = NULL;
	}
	if(NULL != m_pDlgLookSetup)	// Look����
	{
		m_pDlgLookSetup->DestroyWindow();
		delete m_pDlgLookSetup;
		m_pDlgLookSetup = NULL;
	}
	if(NULL != m_pDlgFormLineSetup)	// FormLine����
	{
		m_pDlgFormLineSetup->DestroyWindow();
		delete m_pDlgFormLineSetup;
		m_pDlgFormLineSetup = NULL;
	}

	// �ֳ����ݶ�������
	OnSiteDataClose();
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CMDIFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
//////////////////////////////////////////////////////////////////////////
	// ע���ڲ���������Ϣ
	RegisterWindowMessageForProc();
//////////////////////////////////////////////////////////////////////////

	CBCGPVisualManager::SetDefaultManager (RUNTIME_CLASS (CBCGPVisualManagerVS2005));

	CBCGPToolbarComboBoxButton::SetFlatMode ();

	//--------------------------
	// Load toolbar user images:
	//--------------------------
	if (!m_UserImages.Load (_T(".\\UserImages.bmp")))
	{
		TRACE(_T("Failed to load user images\n"));
		ASSERT (FALSE);
	}
	else
	{
		CBCGPToolBar::SetUserImages (&m_UserImages);
	}

	CBCGPToolBar::EnableQuickCustomization ();

	//-----------------
	// Create menu bar:
	//-----------------
	if (!m_wndMenuBar.Create (this))
	{
		TRACE0("Failed to create menubar\n");
		return -1;      // fail to create
	}

	m_wndMenuBar.SetBarStyle(m_wndMenuBar.GetBarStyle() | CBRS_SIZE_DYNAMIC | CBRS_TOOLTIPS | CBRS_FLYBY);

	//--------------------------------------------
	// Menu will not take the focus on activation:
	//--------------------------------------------
	CBCGPPopupMenu::SetForceMenuFocus (FALSE);

	//---------------------
	// Create main toolbar:
	//---------------------
	if (!m_wndToolBarMatrixFile.CreateEx(this,
		TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP | CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndToolBarMatrixFile.LoadToolBar(IDR_MAINFRAME))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}

	CString strMainToolbarTitle;
	strMainToolbarTitle.LoadString (IDS_MAIN_TOOLBAR);
	m_wndToolBarMatrixFile.SetWindowText (strMainToolbarTitle);

	//---------------------
	// Create Matrix Edit toolbar:
	//---------------------
	if (!m_wndToolBarMatrixEdit.Create(this,
		WS_CHILD | WS_VISIBLE | CBRS_TOP | CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC,
		ID_VIEW_EDIT_TOOLBAR) ||
		!m_wndToolBarMatrixEdit.LoadToolBar (IDR_EDIT))
	{
		TRACE0("Failed to create Matrix FieldON/OFF toolbar\n");
		return FALSE;      // fail to create
	}
	m_wndToolBarMatrixEdit.SetWindowText ("Matrix Edit");

	//---------------------
	// Create Matrix View toolbar:
	//---------------------
	if (!m_wndToolBarMatrixView.Create(this,
		WS_CHILD | WS_VISIBLE | CBRS_TOP | CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC,
		ID_VIEW_VIEW_TOOLBAR) ||
		!m_wndToolBarMatrixView.LoadToolBar (IDR_TOOLBAR_MATRIX_VIEW))
	{
		TRACE0("Failed to create Matrix FieldON/OFF toolbar\n");
		return FALSE;      // fail to create
	}
	m_wndToolBarMatrixView.SetWindowText ("Matrix View");

	//---------------------
	// Create Matrix Setup toolbar:
	//---------------------
	if (!m_wndToolBarMatrixSetup.Create(this,
		WS_CHILD | WS_VISIBLE | CBRS_TOP | CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC,
		ID_VIEW_SETUP_TOOLBAR) ||
		!m_wndToolBarMatrixSetup.LoadToolBar (IDR_TOOLBAR_MATRIX_SETUP))
	{
		TRACE0("Failed to create Matrix FieldON/OFF toolbar\n");
		return FALSE;      // fail to create
	}
	m_wndToolBarMatrixSetup.SetWindowText ("Matrix Setup");

	//---------------------
	// Create Matrix FieldON/OFF toolbar:
	//---------------------
	if (!m_wndToolBarMatrixField.Create(this,
		WS_CHILD | WS_VISIBLE | CBRS_TOP | CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC,
		ID_VIEW_FIELD_TOOLBAR) ||
		!m_wndToolBarMatrixField.LoadToolBar (IDR_TOOLBAR_MATRIX_FIELD))
	{
		TRACE0("Failed to create Matrix FieldON/OFF toolbar\n");
		return FALSE;      // fail to create
	}
	m_wndToolBarMatrixField.SetWindowText ("Matrix Field");

	//--------------------------------------------------------------
	// Load menu items images (not placed on the standard toolbars):
	//--------------------------------------------------------------
	CBCGPToolBar::AddToolBarForImageCollection (IDR_MENU_IMAGES);

	//-------------------
	// Create status bar:
	//-------------------
	if (!m_wndStatusBar.Create(this) ||
		!m_wndStatusBar.SetIndicators(indicators,
		  sizeof(indicators)/sizeof(UINT)))
	{
		TRACE0("Failed to create status bar\n");
		return -1;      // fail to create
	}

	m_wndStatusBar.SetPaneStyle (0, SBPS_STRETCH);
	m_wndStatusBar.SendMessage(WM_IDLEUPDATECMDUI, (WPARAM)TRUE);

	//--------------------------------
	// Create docking control windows:
	//--------------------------------
	if (!CreateDockingBars ())
	{
		return -1;
	}

	m_wndMenuBar.EnableDocking(CBRS_ALIGN_ANY);
	m_wndOutputView.EnableDocking(CBRS_ALIGN_ANY);

	m_wndToolBarMatrixFile.EnableDocking(CBRS_ALIGN_ANY);
	m_wndToolBarMatrixEdit.EnableDocking(CBRS_ALIGN_ANY);
	m_wndToolBarMatrixView.EnableDocking(CBRS_ALIGN_ANY);
	m_wndToolBarMatrixSetup.EnableDocking(CBRS_ALIGN_ANY);
	m_wndToolBarMatrixField.EnableDocking(CBRS_ALIGN_ANY);	

	EnableDocking(CBRS_ALIGN_ANY);

	EnableAutoHideBars(CBRS_ALIGN_ANY);

	DockControlBar(&m_wndMenuBar);
	DockControlBar(&m_wndOutputView);

	DockControlBar(&m_wndToolBarMatrixField);
	DockControlBarLeftOf(&m_wndToolBarMatrixSetup, &m_wndToolBarMatrixField);
	DockControlBarLeftOf(&m_wndToolBarMatrixView, &m_wndToolBarMatrixSetup);
	DockControlBarLeftOf(&m_wndToolBarMatrixEdit, &m_wndToolBarMatrixView);
	DockControlBarLeftOf(&m_wndToolBarMatrixFile, &m_wndToolBarMatrixEdit);

	CRect rectMainToolBar;
	m_wndToolBarMatrixFile.GetWindowRect (&rectMainToolBar);

	//----------------------------------------
	// Allow user-defined toolbars operations:
	//----------------------------------------
	InitUserToobars (NULL, uiFirstUserToolBarId, uiLastUserToolBarId);

	//------------------------
	// Enable windows manager:
	//------------------------
	EnableWindowsDialog (ID_WINDOW_MANAGER, _T("Windows..."), TRUE);

	//--------------------------------------------------------------------
	// Enable conttol bar context menu (list of bars + customize command):
	//--------------------------------------------------------------------
	EnableControlBarMenu (	TRUE, ID_VIEW_CUSTOMIZE, 
							_T("Customize..."), ID_VIEW_TOOLBARS,
							FALSE, TRUE);

	EnableFullScreenMode (ID_VIEW_FULLSCREEN);	

	return 0;
}

/////////////////////////////////////////////////////////////////////////////
// CMainFrame diagnostics

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CMDIFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CMDIFrameWnd::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMainFrame message handlers


void CMainFrame::OnViewCustomize()
{
	//------------------------------------
	// Create a customize toolbars dialog:
	//------------------------------------
	CBCGPToolbarCustomize* pDlgCust = new CBCGPToolbarCustomize (this,
		TRUE /* Automatic menus scaning */,
		BCGCUSTOMIZE_MENU_SHADOWS | BCGCUSTOMIZE_TEXT_LABELS | 
		BCGCUSTOMIZE_LOOK_2000 | BCGCUSTOMIZE_MENU_ANIMATIONS);

	pDlgCust->EnableUserDefinedToolbars ();

	pDlgCust->Create ();
}

LRESULT CMainFrame::OnToolbarReset(WPARAM wp,LPARAM)
{
	UINT uiToolBarId = (UINT) wp;

	switch (uiToolBarId)
	{
	case IDR_TOOLBAR_MATRIX_VIEW:
		{
			CMenu menuViewGraph;
			menuViewGraph.LoadMenu (IDR_MENU_MATRIX_VIEW_GRAPH);
			CBCGPToolbarMenuButton bnViewGraph(ID_MATRIX_VIEWGRAPH, menuViewGraph.GetSubMenu (0)->GetSafeHmenu(), -1);
			m_wndToolBarMatrixView.ReplaceButton(ID_MATRIX_VIEWGRAPH, bnViewGraph);

			CMenu menuViewList;
			menuViewList.LoadMenu (IDR_MENU_MATRIX_VIEW_LIST);
			CBCGPToolbarMenuButton bnViewList(ID_MATRIX_VIEWLIST, menuViewList.GetSubMenu (0)->GetSafeHmenu(), -1);
			m_wndToolBarMatrixView.ReplaceButton(ID_MATRIX_VIEWLIST, bnViewList);
		}
		break;
	case IDR_TOOLBAR_MATRIX_FIELD:
		{		
			m_wndToolBarMatrixField.SetToolBarBtnText (0, NULL, TRUE, TRUE);
			m_wndToolBarMatrixField.SetToolBarBtnText (1, NULL, TRUE, TRUE);
		}
		break;
	}

	return 0;
}

LRESULT CMainFrame::OnHelpCustomizeToolbars(WPARAM /*wp*/, LPARAM lp)
{
//	int iPageNum = (int) wp;

	CBCGPToolbarCustomize* pDlg = (CBCGPToolbarCustomize*) lp;
	ASSERT_VALID (pDlg);

	// TODO: show help about page number iPageNum


	return 0;
}

BOOL CMainFrame::OnShowMDITabContextMenu (CPoint point, DWORD dwAllowedItems, BOOL bDrop)
{
	CMenu menu;
	VERIFY(menu.LoadMenu (bDrop ? IDR_POPUP_DROP_MDITABS : IDR_POPUP_MDITABS));

	CMenu* pPopup = menu.GetSubMenu(0);
	ASSERT(pPopup != NULL);

	if ((dwAllowedItems & BCGP_MDI_CREATE_HORZ_GROUP) == 0)
	{
		pPopup->DeleteMenu (ID_MDI_NEW_HORZ_TAB_GROUP, MF_BYCOMMAND);
	}

	if ((dwAllowedItems & BCGP_MDI_CREATE_VERT_GROUP) == 0)
	{
		pPopup->DeleteMenu (ID_MDI_NEW_VERT_GROUP, MF_BYCOMMAND);
	}

	if ((dwAllowedItems & BCGP_MDI_CAN_MOVE_NEXT) == 0)
	{
		pPopup->DeleteMenu (ID_MDI_MOVE_TO_NEXT_GROUP, MF_BYCOMMAND);
	}

	if ((dwAllowedItems & BCGP_MDI_CAN_MOVE_PREV) == 0)
	{
		pPopup->DeleteMenu (ID_MDI_MOVE_TO_PREV_GROUP, MF_BYCOMMAND);
	}

	if ((dwAllowedItems & BCGP_MDI_CAN_BE_DOCKED) == 0)
	{
		pPopup->DeleteMenu (ID_MDI_TABBED_DOCUMENT, MF_BYCOMMAND);
	}

	CBCGPPopupMenu* pPopupMenu = new CBCGPPopupMenu;
	pPopupMenu->SetAutoDestroy (FALSE);
	pPopupMenu->Create (this, point.x, point.y, pPopup->GetSafeHmenu ());

	return TRUE;
}

void CMainFrame::OnWindowManager() 
{
	ShowWindowsDialog ();
}

BOOL CMainFrame::LoadFrame(UINT nIDResource, DWORD dwDefaultStyle, CWnd* pParentWnd, CCreateContext* pContext) 
{
	if (!CMDIFrameWnd::LoadFrame(nIDResource, dwDefaultStyle, pParentWnd, pContext))
	{
		return FALSE;
	}

	// Add some tools for example....
	CBCGPUserToolsManager* pUserToolsManager = theApp.GetUserToolsManager ();
	if (pUserToolsManager != NULL &&
		pUserToolsManager->GetUserTools ().IsEmpty ())
	{
		CBCGPUserTool* pTool1 = pUserToolsManager->CreateNewTool ();
		pTool1->m_strLabel = _T("Notepad");
		pTool1->SetCommand (_T("notepad.exe"));

		CBCGPUserTool* pTool2 = pUserToolsManager->CreateNewTool ();
		pTool2->m_strLabel = _T("Paint Brush");
		pTool2->SetCommand (_T("mspaint.exe"));

		CBCGPUserTool* pTool3 = pUserToolsManager->CreateNewTool ();
		pTool3->m_strLabel = _T("Windows Explorer");
		pTool3->SetCommand (_T("explorer.exe"));

		CBCGPUserTool* pTool4 = pUserToolsManager->CreateNewTool ();
		pTool4->m_strLabel = _T("BCGSoft On-Line");
		pTool4->SetCommand (_T("http://www.bcgsoft.com"));
	}

	CBCGPMDITabParams mdiTabParams;
	mdiTabParams.m_bTabCustomTooltips = TRUE;

	EnableMDITabbedGroups (TRUE, mdiTabParams);

	//----------------------------------------------------
	// Enable customization button fore all user toolbars:
	//----------------------------------------------------
	for (int i = 0; i < iMaxUserToolbars; i ++)
	{
		CBCGPToolBar* pUserToolbar = GetUserBarByIndex (i);
		if (pUserToolbar != NULL)
		{
			pUserToolbar->EnableCustomizeButton (TRUE, ID_VIEW_CUSTOMIZE, _T("Customize..."));
		}
	}


	return TRUE;
}

BOOL CMainFrame::OnCommand(WPARAM wParam, LPARAM lParam) 
{
	UINT uiCmd = LOWORD (wParam);
	switch (uiCmd)
	{
	case ID_EDIT_PASTE:
		::SendMessage (::GetFocus (), WM_PASTE, 0, 0);
		return TRUE;

	case ID_EDIT_COPY:
		::SendMessage (::GetFocus (), WM_COPY, 0, 0);
		return TRUE;

	case ID_EDIT_CUT:
		::SendMessage (::GetFocus (), WM_CUT, 0, 0);
		return TRUE;
	}
	
	return CMDIFrameWnd::OnCommand(wParam, lParam);
}

void CMainFrame::OnHelpKeyboardmap() 
{
	CBCGPKeyMapDlg dlg (this, TRUE /* Enable Print */);
	dlg.DoModal ();
}

LRESULT CMainFrame::OnToolbarCreateNew(WPARAM wp,LPARAM lp)
{
	LRESULT lres = CBCGPMDIFrameWnd::OnToolbarCreateNew (wp,lp);
	if (lres == 0)
	{
		return 0;
	}

	CBCGPToolBar* pUserToolbar = (CBCGPToolBar*) lres;
	ASSERT_VALID (pUserToolbar);

	pUserToolbar->EnableCustomizeButton (TRUE, ID_VIEW_CUSTOMIZE, _T("Customize..."));
	return lres;
}

BOOL CMainFrame::OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext) 
{
	if (!CBCGPMDIFrameWnd::OnCreateClient(lpcs, pContext))
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CMainFrame::CreateDockingBars ()
{
	//////////////////////////////////New Output////////////////////////////////////////
	if (!m_wndOutputView.Create (_T("Output"), this, CRect (0, 0, 200, 100),
		TRUE, 
		ID_VIEW_OUTPUT,
		WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | CBRS_BOTTOM | CBRS_FLOAT_MULTI))
	{
		TRACE0("Failed to create output bar\n");
		return FALSE;      // fail to create
	}

	SetDockingBarsIcons (FALSE);

	return TRUE;
}

void CMainFrame::SetDockingBarsIcons (BOOL bHiColorIcons)
{
	HICON hOutputBarIcon = (HICON) ::LoadImage (::AfxGetResourceHandle (), 
				MAKEINTRESOURCE (bHiColorIcons ? IDI_OUTPUT_BAR_HC : IDI_OUTPUT_BAR),
				IMAGE_ICON, ::GetSystemMetrics (SM_CXSMICON), ::GetSystemMetrics (SM_CYSMICON), 0);
	m_wndOutputView.SetIcon (hOutputBarIcon, FALSE);

	UpdateMDITabbedBarsIcons ();
}

void CMainFrame::OnFileNewProject() 
{
	// TODO: Add your command handler code here
	
}

void CMainFrame::OnFileNewBlankSolution() 
{
	// TODO: Add your command handler code here
	
}

void CMainFrame::OnFileOpenSolution() 
{
	// TODO: Add your command handler code here
	
}

void CMainFrame::OnFileCloseSolution() 
{
	// TODO: Add your command handler code here
	
}

void CMainFrame::OnFileSaveAll() 
{
	// TODO: Add your command handler code here
	
}

void CMainFrame::OnViewRefresh() 
{
	// TODO: Add your command handler code here
}

void CMainFrame::OnToolsConnectToDatabase() 
{
	// TODO: Add your command handler code here
}

void CMainFrame::OnToolsDebugProcesses() 
{
	// TODO: Add your command handler code here
	
}

void CMainFrame::OnViewFullScreen()
{
	ShowFullScreen ();
}

void CMainFrame::OnChangeLook (BOOL bOneNoteTabs, BOOL bMDITabColors, BOOL bIsVSDotNetLook,
							   BOOL bDockTabColors, BOOL bMDITabsVS2005Look,
							   BOOL bIsToolBoxEx, BOOL bActiveTabCloseButton, BOOL bDocumentMenu)
{
	CBCGPMDITabParams mdiTabParams;
	mdiTabParams.m_bTabCustomTooltips = TRUE;
	mdiTabParams.m_bDocumentMenu = bDocumentMenu;

	if (bMDITabsVS2005Look)
	{
		mdiTabParams.m_style = CBCGPTabWnd::STYLE_3D_VS2005;
	}
	else if (bOneNoteTabs)
	{
		mdiTabParams.m_style = CBCGPTabWnd::STYLE_3D_ONENOTE;
		mdiTabParams.m_bAutoColor = bMDITabColors;
	}

	if (bActiveTabCloseButton)
	{
		mdiTabParams.m_bTabCloseButton = FALSE;
		mdiTabParams.m_bActiveTabCloseButton = TRUE;
	}

	EnableMDITabbedGroups (TRUE, mdiTabParams);

	CBCGPTabbedControlBar::EnableTabAutoColor (bDockTabColors);

	//-----------------------
	// Reload toolbar images:
	//-----------------------

	CBCGPToolBar::ResetAllImages ();

//	m_wndToolBarMatrixFile.LoadBitmap (theApp.m_bHiColorIcons ? IDB_MAINFRAME_HC : IDR_MAINFRAME);
	m_wndToolBarMatrixFile.LoadBitmap (IDR_MAINFRAME);
	m_wndToolBarMatrixEdit.LoadBitmap (IDR_EDIT);
	m_wndToolBarMatrixView.LoadBitmap (IDR_TOOLBAR_MATRIX_VIEW);
	m_wndToolBarMatrixSetup.LoadBitmap (IDR_TOOLBAR_MATRIX_SETUP);
	m_wndToolBarMatrixField.LoadBitmap (IDR_TOOLBAR_MATRIX_FIELD);

	CBCGPToolBar::AddToolBarForImageCollection (IDR_MENU_IMAGES, 
		theApp.m_bHiColorIcons ? IDR_MENU_IMAGES : 0);
	//------------------
	// Inform all views:
	//------------------
	for (CWnd* pWndChild = m_wndClientArea.GetWindow (GW_CHILD); 
		pWndChild != NULL; pWndChild = pWndChild->GetNextWindow ())
	{
		CBCGPMDIChildWnd* pMDIChild = DYNAMIC_DOWNCAST(CBCGPMDIChildWnd, pWndChild);
		if (pMDIChild != NULL)
		{
			CSensorListView* pView = DYNAMIC_DOWNCAST (
				CSensorListView, pMDIChild->GetActiveView ());
			if (pView != NULL)
			{
				// pView->OnChangeVisualStyle ();	// ******
			}
		}
	}

	CBCGPDockManager* pDockManager = GetDockManager ();
	ASSERT_VALID (pDockManager);

	SetDockingBarsIcons (theApp.m_bHiColorIcons);

	pDockManager->AdjustBarFrames ();

	RecalcLayout ();
	RedrawWindow (NULL, NULL, RDW_ALLCHILDREN | RDW_INVALIDATE | RDW_UPDATENOW | RDW_ERASE);
}

void CMainFrame::OnHelpWeb() 
{
	::ShellExecute (NULL, NULL, _T("http://www.bcgsoft.com"), NULL, NULL, NULL);
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs) 
{
	return CMDIFrameWnd::PreCreateWindow(cs);
}

BOOL CMainFrame::DestroyWindow() 
{	
	return CMDIFrameWnd::DestroyWindow();
}

void CMainFrame::OnMdiMoveToNextGroup() 
{
	MDITabMoveToNextGroup ();
}

void CMainFrame::OnMdiMoveToPrevGroup() 
{
	MDITabMoveToNextGroup (FALSE);
}

void CMainFrame::OnMdiNewHorzTabGroup() 
{
	MDITabNewGroup (FALSE);
}

void CMainFrame::OnMdiNewVertGroup() 
{
	MDITabNewGroup ();
}

void CMainFrame::OnMdiCancel() 
{
	// TODO: Add your command handler code here
	
}

CBCGPMDIChildWnd* CMainFrame::CreateDocumentWindow (LPCTSTR lpcszDocName, CObject* /*pObj*/)
{
	if (lpcszDocName != NULL && lpcszDocName [0] != '\0')
	{
		CDocument* pDoc = AfxGetApp()->OpenDocumentFile (lpcszDocName);

		if (pDoc != NULL)
		{
			POSITION pos = pDoc->GetFirstViewPosition();

			if (pos != NULL)
			{
				CView* pView = pDoc->GetNextView (pos);
				return DYNAMIC_DOWNCAST (CBCGPMDIChildWnd, pView->GetParent ());
			}   
		}

	}

	return NULL;
}

void CMainFrame::OnClose() 
{
	SaveMDIState (theApp.GetRegSectionPath ());
	CMDIFrameWnd::OnClose();
}

LRESULT CMainFrame::OnGetTabToolTip(WPARAM /*wp*/, LPARAM lp)
{
	CBCGPTabToolTipInfo* pInfo = (CBCGPTabToolTipInfo*) lp;
	ASSERT (pInfo != NULL);
	ASSERT_VALID (pInfo->m_pTabWnd);

	if (!pInfo->m_pTabWnd->IsMDITab ())
	{
		return 0;
	}

	CFrameWnd* pFrame = DYNAMIC_DOWNCAST (CFrameWnd,
		pInfo->m_pTabWnd->GetTabWnd (pInfo->m_nTabIndex));
	if (pFrame == NULL)
	{
		return 0;
	}

	CDocument* pDoc = pFrame->GetActiveDocument ();
	if (pDoc == NULL)
	{
		return 0;
	}

	pInfo->m_strText = pDoc->GetPathName ();
	return 0;
}

void CMainFrame::OnViewOutput() 
{
	m_wndOutputView.ShowControlBar (!m_wndOutputView.IsVisible (), FALSE, TRUE);
}

void CMainFrame::OnUpdateViewOutput(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck (m_wndOutputView.IsVisible ());
} 

void CMainFrame::OnMdiTabbedDocument() 
{
	CBCGPMDIChildWnd* pMDIChild = DYNAMIC_DOWNCAST(CBCGPMDIChildWnd, MDIGetActive ());
	if (pMDIChild == NULL)
	{
		ASSERT (FALSE);
		return;
	}

	TabbedDocumentToControlBar (pMDIChild);
}

void CMainFrame::OnUpdateMdiTabbedDocument(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck ();
}

void CMainFrame::OnUpdateCaretPos(CCmdUI* pCmdUI)
{
	pCmdUI->SetText (_T(""));
}

void CMainFrame::OnSettingChange(UINT uFlags, LPCTSTR lpszSection) 
{
	CMDIFrameWnd::OnSettingChange(uFlags, lpszSection);
	
	m_wndOutputView.UpdateFonts();
}

//////////////////////////////////////////////////////////////////////////
// �����б���ͼ�˵�����
void CMainFrame::OnMatrixInstrumentList()
{
	CBCGPToolbarMenuButton* pButton =  DYNAMIC_DOWNCAST (CBCGPToolbarMenuButton,
		m_wndToolBarMatrixView.GetButton (1));
	if (pButton != NULL)
	{
		pButton->SetImage (CImageHash::GetImageOfCommand (ID_MATRIX_INSTRUMENTLIST));
		m_wndToolBarMatrixView.Invalidate ();
		m_wndToolBarMatrixView.UpdateWindow ();
	}

	((CBCGPVisualStudioGUIDemoApp*)AfxGetApp())->m_pDocTemplateInstrumentList->OpenDocumentFile(NULL);
}

// �첨���б���ͼ�˵�����
void CMainFrame::OnMatrixSensorList()
{
	CBCGPToolbarMenuButton* pButton =  DYNAMIC_DOWNCAST (CBCGPToolbarMenuButton,
		m_wndToolBarMatrixView.GetButton (1));
	if (pButton != NULL)
	{
		pButton->SetImage (CImageHash::GetImageOfCommand (ID_MATRIX_SENSORLIST));
		m_wndToolBarMatrixView.Invalidate ();
		m_wndToolBarMatrixView.UpdateWindow ();
	}

	((CBCGPVisualStudioGUIDemoApp*)AfxGetApp())->m_pDocTemplateSensorList->OpenDocumentFile(NULL);
}

// ����ͼ����ͼ�˵�����
void CMainFrame::OnMatrixInstrumentGraph()
{
	CBCGPToolbarMenuButton* pButton =  DYNAMIC_DOWNCAST (CBCGPToolbarMenuButton,
		m_wndToolBarMatrixView.GetButton (0));
	if (pButton != NULL)
	{
		pButton->SetImage (CImageHash::GetImageOfCommand (ID_MATRIX_INSTRUMENTGRAPH));
		m_wndToolBarMatrixView.Invalidate ();
		m_wndToolBarMatrixView.UpdateWindow ();
	}

	((CBCGPVisualStudioGUIDemoApp*)AfxGetApp())->m_pDocTemplateInstrumentGraph->OpenDocumentFile(NULL);
}

// �첨��ͼ����ͼ�˵�����
void CMainFrame::OnMatrixSensorGraph()
{
	CBCGPToolbarMenuButton* pButton =  DYNAMIC_DOWNCAST (CBCGPToolbarMenuButton,
		m_wndToolBarMatrixView.GetButton (0));
	if (pButton != NULL)
	{
		pButton->SetImage (CImageHash::GetImageOfCommand (ID_MATRIX_SENSORGRAPH));
		m_wndToolBarMatrixView.Invalidate ();
		m_wndToolBarMatrixView.UpdateWindow ();
	}

	((CBCGPVisualStudioGUIDemoApp*)AfxGetApp())->m_pDocTemplateSensorGraph->OpenDocumentFile(NULL);
}

/**
* �������ͼ����ͼ�˵�����
* @param void
* @return void
*/
void CMainFrame::OnMatrixSeismonitorGraph()
{
	CBCGPToolbarMenuButton* pButton =  DYNAMIC_DOWNCAST (CBCGPToolbarMenuButton,
		m_wndToolBarMatrixView.GetButton (0));
	if (pButton != NULL)
	{
		pButton->SetImage (CImageHash::GetImageOfCommand (ID_MATRIX_SEISMONITORGRAPH));
		m_wndToolBarMatrixView.Invalidate ();
		m_wndToolBarMatrixView.UpdateWindow ();
	}

	CBCGPVisualStudioGUIDemoApp* pApp = (CBCGPVisualStudioGUIDemoApp*)AfxGetApp();
	POSITION posDoc = NULL;
	// ���������ͼ����ͼ
	posDoc = pApp->m_pDocTemplateSeismonitorGraph->GetFirstDocPosition();
	if(NULL == posDoc)
	{
		((CBCGPVisualStudioGUIDemoApp*)AfxGetApp())->m_pDocTemplateSeismonitorGraph->OpenDocumentFile(NULL);
	}	
}

// ע���ڲ���������Ϣ
void CMainFrame::RegisterWindowMessageForProc()
{
	WM_MESSAGE_MATRIX_CMD_100 = RegisterWindowMessage(_T("WM_MESSAGE_MATRIX_CMD_100"));
}
// ���ע���ڲ���������Ϣ
void CMainFrame::UnRegisterWindowMessageForProc()
{

}

// �ֳ����ݶ����ʼ��
void CMainFrame::OnSiteDataInit()
{
	m_oSiteData.OnInit();	// �ֳ����ݶ���
}

// �ֳ����ݶ�������
void CMainFrame::OnSiteDataClose()
{
	m_oSiteData.OnClose();	// �ֳ����ݶ���
}

// �����ֳ�����
void CMainFrame::LoadSiteData()
{
	m_oSiteData.LoadSiteData();
}


// �����ڲ���������֡
void CMainFrame::OnProcInterFaceCommand(CFrameInterface* pFrameInterface)
{
	switch(pFrameInterface->m_usCommand)
	{
	case 100:	// ����	100-�ֳ������������֪ͨ����
		ProcInterFaceCommandForSiteDataOutput();
		break;
	case 101:	// ���� 101-Server Field ON/OFF
		ProcInterFaceCommandForServerField(pFrameInterface->m_byFieldOperation);
		break;
	case 200 + 4:	// �����������	200 + 4 ��������-��������-��������
		ProcInterFaceDataForInstrumentTest(pFrameInterface, 4);
		break;
	case 200 + 5:	// �����������	200 + 5 ��������-��������-��������
		ProcInterFaceDataForInstrumentTest(pFrameInterface, 5);
		break;
	case 200 + 7:	// �����������	200 + 7 ��������-��������-��������
		ProcInterFaceDataForInstrumentTest(pFrameInterface, 7);
		break;
	case 200 + 6:	// �����������	200 + 6 ��������-��������-��������/��λ
		ProcInterFaceDataForInstrumentTest(pFrameInterface, 6);
		break;
	case 200 + 8:	// �����������	200 + 8 ��������-��������-������ģ
		ProcInterFaceDataForInstrumentTest(pFrameInterface, 8);
		break;
	case 200 + 15:	// �����������	200 + 15 ��������-�첨������-�첨������
		ProcInterFaceDataForSensorTest(pFrameInterface, 15);
		break;
	case 200 + 14:	// �����������	200 + 14 ��������-�첨������-�첨��©��
		ProcInterFaceDataForSensorTest(pFrameInterface, 14);
		break;
	case 200 + 1:	// �����������	200 + 1 ��������-�첨������-�첨������
		ProcInterFaceDataForSensorTest(pFrameInterface, 1);
		break;
	case 200 + 20:	// �����������	200 + 20 ��������-�첨������-�첨����б��
		ProcInterFaceDataForSensorTest(pFrameInterface, 20);
		break;
	case 200 + 21:	// �����������	200 + 21 ��������-�첨������-�첨����б��ģ��
		ProcInterFaceDataForSensorTest(pFrameInterface, 21);
		break;
	case 200 + 22:	// �����������	200 + 22 ��������-�첨������-�첨���������
		ProcInterFaceDataForSeismonitorTest(pFrameInterface);
		break;
	}
}

// ��������	100-�ֳ������������֪ͨ����
void CMainFrame::ProcInterFaceCommandForSiteDataOutput()
{
	m_oSiteData.ProcInterSiteDataOutputCMD();

	CBCGPVisualStudioGUIDemoApp* pApp = (CBCGPVisualStudioGUIDemoApp*)AfxGetApp();

	POSITION posDoc = NULL;
	POSITION posView = NULL;
	// �첨���б���ͼ����
	posDoc = pApp->m_pDocTemplateSensorList->GetFirstDocPosition();
	while(NULL != posDoc)
	{
		CDocument* pDocument = pApp->m_pDocTemplateSensorList->GetNextDoc(posDoc);
		posView = pDocument->GetFirstViewPosition();
		while(NULL != posView)
		{
			CSensorListView* pSensorListView = (CSensorListView*)pDocument->GetNextView(posView);
			pSensorListView->OnReloadSiteDataCMD();
		}
	}
	// �����б���ͼ����
	posDoc = pApp->m_pDocTemplateInstrumentList->GetFirstDocPosition();
	while(NULL != posDoc)
	{
		CDocument* pDocument = pApp->m_pDocTemplateInstrumentList->GetNextDoc(posDoc);
		posView = pDocument->GetFirstViewPosition();
		while(NULL != posView)
		{
			CInstrumentListView* pInstrumentListView = (CInstrumentListView*)pDocument->GetNextView(posView);
			pInstrumentListView->OnReloadSiteDataCMD();
		}
	}

	// �첨��ͼ����ͼ����
	posDoc = pApp->m_pDocTemplateSensorGraph->GetFirstDocPosition();
	while(NULL != posDoc)
	{
		CDocument* pDocument = pApp->m_pDocTemplateSensorGraph->GetNextDoc(posDoc);
		posView = pDocument->GetFirstViewPosition();
		while(NULL != posView)
		{
			CSensorGraphView* pSensorGraphView = (CSensorGraphView*)pDocument->GetNextView(posView);
			pSensorGraphView->OnReloadSiteDataCMD();
		}
	}

	// ����ͼ����ͼ����
	posDoc = pApp->m_pDocTemplateInstrumentGraph->GetFirstDocPosition();
	while(NULL != posDoc)
	{
		CDocument* pDocument = pApp->m_pDocTemplateInstrumentGraph->GetNextDoc(posDoc);
		posView = pDocument->GetFirstViewPosition();
		while(NULL != posView)
		{
			CInstrumentGraphView* pInstrumentGraphView = (CInstrumentGraphView*)pDocument->GetNextView(posView);
			pInstrumentGraphView->OnReloadSiteDataCMD();
		}
	}

	// �������ͼ����ͼ����
	posDoc = pApp->m_pDocTemplateSeismonitorGraph->GetFirstDocPosition();
	while(NULL != posDoc)
	{
		CDocument* pDocument = pApp->m_pDocTemplateSeismonitorGraph->GetNextDoc(posDoc);
		posView = pDocument->GetFirstViewPosition();
		while(NULL != posView)
		{
			CSeismonitorGraphView* pSeismonitorGraphView = (CSeismonitorGraphView*)pDocument->GetNextView(posView);
			pSeismonitorGraphView->OnReloadSiteDataCMD();
		}
	}

	::PostMessage(HWND_BROADCAST, WM_MESSAGE_MATRIX_CMD_100, 0, 0);
}

/**
* �����ڲ���������֡������	101-ServerField ON/OFF
* @param byte byFieldOperation ServerFieldON/OFF 0��OFF��1��ON
* @return void
*/
void CMainFrame::ProcInterFaceCommandForServerField(byte byFieldOperation)
{
	// �жϣ�ServerField OFF
	if(0 == byFieldOperation)
	{
		ProcInterFaceCommandForServerFieldOff();
	}
	// �жϣ�ServerField ON
	else if(1 == byFieldOperation)
	{
		ProcInterFaceCommandForServerFieldOn();
	}
}

/**
* �յ��µĲ������ݺ󣬸��������б���ͼ������ͼ����ͼ
* @param int iTestType ��������
* @return void
*/
void CMainFrame::OnRefreshInstrumentViewForNewTestValue(int iTestType)
{
	CBCGPVisualStudioGUIDemoApp* pApp = (CBCGPVisualStudioGUIDemoApp*)AfxGetApp();

	POSITION posDoc = NULL;
	POSITION posView = NULL;

	// �����б���ͼ����
	posDoc = pApp->m_pDocTemplateInstrumentList->GetFirstDocPosition();
	while(NULL != posDoc)
	{
		CDocument* pDocument = pApp->m_pDocTemplateInstrumentList->GetNextDoc(posDoc);
		posView = pDocument->GetFirstViewPosition();
		while(NULL != posView)
		{
			CInstrumentListView* pInstrumentListView = (CInstrumentListView*)pDocument->GetNextView(posView);
			pInstrumentListView->OnRefreshForNewTestValue(iTestType);
		}
	}

	// ����ͼ����ͼ����
	posDoc = pApp->m_pDocTemplateInstrumentGraph->GetFirstDocPosition();
	while(NULL != posDoc)
	{
		CDocument* pDocument = pApp->m_pDocTemplateInstrumentGraph->GetNextDoc(posDoc);
		posView = pDocument->GetFirstViewPosition();
		while(NULL != posView)
		{
			CInstrumentGraphView* pInstrumentGraphView = (CInstrumentGraphView*)pDocument->GetNextView(posView);
			pInstrumentGraphView->OnRefreshForNewTestValue(iTestType);
		}
	}
}

/**
* �յ��µĲ������ݺ󣬸��¼첨���б���ͼ�ͼ첨��ͼ����ͼ
* @param int iTestType ��������
* @return void
*/
void CMainFrame::OnRefreshSensorViewForNewTestValue(int iTestType)
{
	CBCGPVisualStudioGUIDemoApp* pApp = (CBCGPVisualStudioGUIDemoApp*)AfxGetApp();

	POSITION posDoc = NULL;
	POSITION posView = NULL;

	// �첨���б���ͼ����
	posDoc = pApp->m_pDocTemplateSensorList->GetFirstDocPosition();
	while(NULL != posDoc)
	{
		CDocument* pDocument = pApp->m_pDocTemplateSensorList->GetNextDoc(posDoc);
		posView = pDocument->GetFirstViewPosition();
		while(NULL != posView)
		{
			CSensorListView* pSensorListView = (CSensorListView*)pDocument->GetNextView(posView);
			pSensorListView->OnRefreshForNewTestValue(iTestType);
		}
	}

	// �첨��ͼ����ͼ����
	posDoc = pApp->m_pDocTemplateSensorGraph->GetFirstDocPosition();
	while(NULL != posDoc)
	{
		CDocument* pDocument = pApp->m_pDocTemplateSensorGraph->GetNextDoc(posDoc);
		posView = pDocument->GetFirstViewPosition();
		while(NULL != posView)
		{
			CSensorGraphView* pSensorGraphView = (CSensorGraphView*)pDocument->GetNextView(posView);
			pSensorGraphView->OnRefreshForNewTestValue(iTestType);
		}
	}
}

/**
* �յ��µĲ������ݺ󣬸��¼첨���������ͼ����ͼ
* @return void
*/
void CMainFrame::OnRefreshSeismonitorViewForNewTestValue()
{
	CBCGPVisualStudioGUIDemoApp* pApp = (CBCGPVisualStudioGUIDemoApp*)AfxGetApp();

	POSITION posDoc = NULL;
	POSITION posView = NULL;

	// �������ͼ����ͼ����
	posDoc = pApp->m_pDocTemplateSeismonitorGraph->GetFirstDocPosition();
	while(NULL != posDoc)
	{
		CDocument* pDocument = pApp->m_pDocTemplateSeismonitorGraph->GetNextDoc(posDoc);
		posView = pDocument->GetFirstViewPosition();
		while(NULL != posView)
		{
			CSeismonitorGraphView* pSeismonitorGraphView = (CSeismonitorGraphView*)pDocument->GetNextView(posView);
			pSeismonitorGraphView->OnRefreshForNewTestValue();
		}
	}
}

/**
* ����������ݣ���������
* @param CFrameInterface* pFrameInterface ����ָ֡��
* @param int iTestType ��������
* @return void
*/
void CMainFrame::ProcInterFaceDataForInstrumentTest(CFrameInterface* pFrameInterface, int iTestType)
{
	m_oSiteData.m_olsIPInstrument.RemoveAll();

	byte* pTestData = &(pFrameInterface->m_pFrameData[13]);
	int iDataCount = pFrameInterface->m_usCommandCount;
	int iPos = 0;
	unsigned int uiIP;
	float fTestValue;
	byte byTestCheck;
	float fTestValue1;
	byte byTestCheck1;
	byte byTestCheck2;
	byte byTestCheckAll;
	CInstrument* pInstrument = NULL;
	for(int i = 0; i < iDataCount; i++)
	{
		if(6 == iTestType)
		{
			iPos = 0;
			memcpy(&uiIP, &pTestData[i * 16], 4);
			iPos = iPos + 4;
			memcpy(&fTestValue, &pTestData[i * 16 + iPos], 4);
			iPos = iPos + 4;
			memcpy(&byTestCheck, &pTestData[i * 16 + iPos], 1);
			iPos = iPos + 1;
			memcpy(&fTestValue1, &pTestData[i * 16 + iPos], 4);
			iPos = iPos + 4;
			memcpy(&byTestCheck1, &pTestData[i * 16 + iPos], 1);
			iPos = iPos + 1;
			memcpy(&byTestCheck2, &pTestData[i * 16 + iPos], 1);
			iPos = iPos + 1;
			memcpy(&byTestCheckAll, &pTestData[i * 16 + iPos], 1);
		}
		else
		{
			iPos = 0;
			memcpy(&uiIP, &pTestData[i * 10], 4);
			iPos = iPos + 4;
			memcpy(&fTestValue, &pTestData[i * 10 + iPos], 4);
			iPos = iPos + 4;
			memcpy(&byTestCheck, &pTestData[i * 10 + iPos], 1);
			iPos = iPos + 1;
			memcpy(&byTestCheckAll, &pTestData[i * 10 + iPos], 1);
		}

		if(TRUE == m_oSiteData.m_oInstrumentList.m_oIPInstrumentMap.GetInstrument(uiIP, pInstrument))
		{
			m_oSiteData.m_olsIPInstrument.AddTail(uiIP);
			pInstrument->m_byCheck = byTestCheckAll;
			switch(iTestType)
			{
			case 4:	// ��������
				pInstrument->m_fNoiseValue = fTestValue;
				pInstrument->m_byNoiseCheck = byTestCheck;
				break;
			case 5:	// ��������
				pInstrument->m_fDistortionValue = fTestValue;
				pInstrument->m_byDistortionCheck = byTestCheck;
				break;
			case 7:	// ��������
				pInstrument->m_fCrosstalkValue = fTestValue;
				pInstrument->m_byCrosstalkCheck = byTestCheck;
				break;
			case 6:	// ��������/��λ
				pInstrument->m_fGainValue = fTestValue;
				pInstrument->m_byGainCheck = byTestCheck;
				pInstrument->m_fPhaseValue = fTestValue1;
				pInstrument->m_byPhaseCheck = byTestCheck1;
				pInstrument->m_byGainAndPhaseCheck = byTestCheck2;
				break;
			case 8:	// ������ģ
				pInstrument->m_fCMRRValue = fTestValue;
				pInstrument->m_byCMRRCheck = byTestCheck;
				break;
			}
		}
	}
	// �յ��µĲ������ݺ󣬸��������б���ͼ������ͼ����ͼ
	OnRefreshInstrumentViewForNewTestValue(iTestType);
}

/**
* ����������ݣ��첨������
* @param CFrameInterface* pFrameInterface ����ָ֡��
* @param int iTestType ��������
* @return void
*/
void CMainFrame::ProcInterFaceDataForSensorTest(CFrameInterface* pFrameInterface, int iTestType)
{
	m_oSiteData.m_olsIPSensor.RemoveAll();

	byte* pTestData = &(pFrameInterface->m_pFrameData[13]);
	int iDataCount = pFrameInterface->m_usCommandCount;
	int iPos = 0;
	unsigned int uiIP;
	float fTestValue;
	byte byTestCheck;
	byte byTestCheckAll;
	CChannelSetupData* pSensor = NULL;
	for(int i = 0; i < iDataCount; i++)
	{
		iPos = 0;
		memcpy(&uiIP, &pTestData[i * 10], 4);
		iPos = iPos + 4;
		memcpy(&fTestValue, &pTestData[i * 10 + iPos], 4);
		iPos = iPos + 4;
		memcpy(&byTestCheck, &pTestData[i * 10 + iPos], 1);
		iPos = iPos + 1;
		memcpy(&byTestCheckAll, &pTestData[i * 10 + iPos], 1);

		if(TRUE == m_oSiteData.m_oChannelList.m_oChannelMap.Lookup(uiIP, pSensor))
		{
			m_oSiteData.m_olsIPSensor.AddTail(uiIP);
			pSensor->m_byCheck = byTestCheckAll;
			switch(iTestType)
			{
			case 15:	// �첨������
				pSensor->m_fResistanceValue = fTestValue;
				pSensor->m_byResistanceCheck = byTestCheck;
				break;
			case 14:	// �첨��©��
				pSensor->m_fLeakageValue = fTestValue;
				pSensor->m_byLeakageCheck = byTestCheck;
				break;
			case 1:	// �첨������
				pSensor->m_fNoiseValue = fTestValue;
				pSensor->m_byNoiseCheck = byTestCheck;
				break;
			case 20:	// �첨��Ұ����б��
				pSensor->m_fTiltValue = fTestValue;
				pSensor->m_byTiltCheck = byTestCheck;
				break;
			case 21:	// �첨����б��ģ��
				pSensor->m_fTiltModelValue = fTestValue;
				pSensor->m_byTiltModelCheck = byTestCheck;
				break;
			}
		}
	}
	// �յ��µĲ������ݺ󣬸��¼첨���б���ͼ�ͼ첨��ͼ����ͼ
	OnRefreshSensorViewForNewTestValue(iTestType);
}

/**
* ����������ݣ��첨������������
* @param CFrameInterface* pFrameInterface ����ָ֡��
* @return void
*/
void CMainFrame::ProcInterFaceDataForSeismonitorTest(CFrameInterface* pFrameInterface)
{
	// �μ��������첨������
	m_oSiteData.m_olsIPSeismonitor.RemoveAll();

	byte* pTestData = &(pFrameInterface->m_pFrameData[13]);
	int iDataCount = pFrameInterface->m_usCommandCount;
	int iPos = 0;
	unsigned int uiIP;
	float fTestValue;
	byte byTestCheck;
	CChannelSetupData* pSensor = NULL;
	for(int i = 0; i < iDataCount; i++)
	{
		iPos = 0;
		memcpy(&uiIP, &pTestData[i * 9], 4);
		iPos = iPos + 4;
		memcpy(&fTestValue, &pTestData[i * 9 + iPos], 4);
		iPos = iPos + 4;
		memcpy(&byTestCheck, &pTestData[i * 9 + iPos], 1);

		if(TRUE == m_oSiteData.m_oChannelList.m_oChannelMap.Lookup(uiIP, pSensor))
		{
			m_oSiteData.m_olsIPSeismonitor.AddTail(uiIP);
			pSensor->m_fNoiseMonitorValue = fTestValue;
			pSensor->m_byNoiseMonitorCheck = byTestCheck;
		}
	}
	// �յ��µĲ������ݺ󣬸��¼첨���������ͼ����ͼ
	OnRefreshSeismonitorViewForNewTestValue();
}

LRESULT CMainFrame::OnReloadSiteDataCMD(WPARAM wParam, LPARAM lParam)
{
	return 0;
}

// ��������
void CMainFrame::OnMatrixSurveySetup()
{
	if(NULL == m_pDlgSurveySetup)	// ��������
	{
		m_pDlgSurveySetup = new CDlgSurveySetup;
		m_pDlgSurveySetup->m_pSiteData = &m_oSiteData;	// �ֳ�����
		m_pDlgSurveySetup->Create(IDD_DIALOG_SURVEYSETUP, this);
	}
	m_pDlgSurveySetup->ShowWindow(SW_SHOWNORMAL);
}

// ��������
void CMainFrame::OnMatrixLayoutSetup()
{
	if(NULL == m_pDlgLayoutSetup)	// ��������
	{
		m_pDlgLayoutSetup = new CDlgLayoutSetup;
		m_pDlgLayoutSetup->m_pSiteData = &m_oSiteData;	// �ֳ�����
		m_pDlgLayoutSetup->Create(IDD_DIALOG_LAYOUTSETUP, this);
	}
	m_pDlgLayoutSetup->ShowWindow(SW_SHOWNORMAL);
}

// ��������
void CMainFrame::OnMatrixSpreadSetup()
{
	if(NULL == m_pDlgSpreadSetup)	// ��������
	{
		m_pDlgSpreadSetup = new CDlgSpreadSetup;
		m_pDlgSpreadSetup->m_pSiteData = &m_oSiteData;	// �ֳ�����
		m_pDlgSpreadSetup->Create(IDD_DIALOG_SPREADSETUP, this);
	}
	m_pDlgSpreadSetup->ShowWindow(SW_SHOWNORMAL);
}

// ���Ի�������
void CMainFrame::OnMatrixTestBaseSetup()
{
	if(NULL == m_pDlgTestBaseSetup)	// ���Ի�������
	{
		m_pDlgTestBaseSetup = new CDlgTestBaseSetup;
		m_pDlgTestBaseSetup->m_pSiteData = &m_oSiteData;	// �ֳ�����
		m_pDlgTestBaseSetup->Create(IDD_DIALOG_TESTBASESETUP, this);
	}
	m_pDlgTestBaseSetup->ShowWindow(SW_SHOWNORMAL);
}

// ��������
void CMainFrame::OnMatrixTestSetup()
{
	if(NULL == m_pDlgTestSetup)	// ��������
	{
		m_pDlgTestSetup = new CDlgTestSetup;
		m_pDlgTestSetup->m_pSiteData = &m_oSiteData;	// �ֳ�����
		m_pDlgTestSetup->Create(IDD_DIALOG_TESTSETUP, this);
	}
	m_pDlgTestSetup->ShowWindow(SW_SHOWNORMAL);
}

// Look����
void CMainFrame::OnMatrixLookSetup()
{
	if(NULL == m_pDlgLookSetup)	// Look����
	{
		m_pDlgLookSetup = new CDlgLookSetup;
		m_pDlgLookSetup->m_pSiteData = &m_oSiteData;	// �ֳ�����
		m_pDlgLookSetup->Create(IDD_DIALOG_LOOKSETUP, this);
	}
	m_pDlgLookSetup->ShowWindow(SW_SHOWNORMAL);
}

// FormLine����
void CMainFrame::OnMatrixFormLineSetup()
{
	if(NULL == m_pDlgFormLineSetup)	// FormLine����
	{
		m_pDlgFormLineSetup = new CDlgFormLineSetup;
		m_pDlgFormLineSetup->m_pSiteData = &m_oSiteData;	// �ֳ�����
		m_pDlgFormLineSetup->Create(IDD_DIALOG_FORMLINESETUP, this);
	}
	m_pDlgFormLineSetup->ShowWindow(SW_SHOWNORMAL);
}

// 
void CMainFrame::OnMatrixFieldOn()
{
	m_byFieldOperation = 1;	// Field ON
	// ��Ӧ����ͼ����ͼ�����˵�FieldOn/Off����
	OnToolBarFieldOperation();
}

// 
void CMainFrame::OnMatrixFieldOff()
{
	m_byFieldOperation = 0;	// Field ON
	// ��Ӧ����ͼ����ͼ�����˵�FieldOn/Off����
	OnToolBarFieldOperation();
}

/**
* ��������	101-Server Field ON
* @param void
* @return void
*/
void CMainFrame::ProcInterFaceCommandForServerFieldOn()
{
	m_byFieldOperation = 1;	// Field ON

	CBCGPToolbarButton* pBN = NULL;
	pBN = m_wndToolBarMatrixField.GetButton(0);	
	pBN->SetImage(CImageHash::GetImageOfCommand (ID_BUTTON_MATRIX_FIELD_ON_GRAPH, FALSE));

	pBN = m_wndToolBarMatrixField.GetButton(1);	
	pBN->SetImage(CImageHash::GetImageOfCommand (ID_BUTTON_MATRIX_FIELD_OFF_GRAPH, FALSE));

	m_wndToolBarMatrixField.InvalidateButton(0);
	m_wndToolBarMatrixField.InvalidateButton(1);
	m_wndToolBarMatrixField.RedrawWindow();
}

/**
* ��������	101-Server Field OFF
* @param void
* @return void
*/
void CMainFrame::ProcInterFaceCommandForServerFieldOff()
{
	m_byFieldOperation = 0;	// Field OFF

	CBCGPToolbarButton* pBN = NULL;
	pBN = m_wndToolBarMatrixField.GetButton(0);	
	pBN->SetImage(CImageHash::GetImageOfCommand (ID_BUTTON_MATRIX_FIELD_OFF_GRAPH, FALSE));

	pBN = m_wndToolBarMatrixField.GetButton(1);	
	pBN->SetImage(CImageHash::GetImageOfCommand (ID_BUTTON_MATRIX_FIELD_ON_GRAPH, FALSE));

	m_wndToolBarMatrixField.InvalidateButton(0);
	m_wndToolBarMatrixField.InvalidateButton(1);
	m_wndToolBarMatrixField.RedrawWindow();

	CBCGPVisualStudioGUIDemoApp* pApp = (CBCGPVisualStudioGUIDemoApp*)AfxGetApp();

	POSITION posDoc = NULL;
	POSITION posView = NULL;

	// �������ͼ����ͼ����
	posDoc = pApp->m_pDocTemplateSeismonitorGraph->GetFirstDocPosition();
	while(NULL != posDoc)
	{
		CDocument* pDocument = pApp->m_pDocTemplateSeismonitorGraph->GetNextDoc(posDoc);
		posView = pDocument->GetFirstViewPosition();
		while(NULL != posView)
		{
			CSeismonitorGraphView* pSeismonitorGraphView = (CSeismonitorGraphView*)pDocument->GetNextView(posView);
			CSeismonitorGraphChildFrame* pParentFrame = (CSeismonitorGraphChildFrame*)pSeismonitorGraphView->GetParentFrame();
			// Ұ������������ 0-ֹͣ����
			pParentFrame->m_byTestOperation = 0;
		}
	}
}

/**
* ��Ӧ����ͼ����ͼ�����˵����ñ�ǵ�
* @param unsigned int uiInstrumentType �������� 1-����վ��2-��Դվ��3-�ɼ�վ
* @param unsigned int uiSN �����豸��
* @return void
*/
void CMainFrame::OnGraphViewInstrumentSetMarker(unsigned int uiInstrumentType, unsigned int uiSN)
{
	// ��������
	OnMatrixLayoutSetup();
	m_pDlgLayoutSetup->m_oTabWnd.SetActiveTab(0);
	m_pDlgLayoutSetup->OnGraphViewInstrumentSetMarker(uiInstrumentType, uiSN);

}

/**
* ��Ӧ����ͼ����ͼ�����˵����ø�����
* @param unsigned int uiInstrumentType �������� 1-����վ��2-��Դվ��3-�ɼ�վ
* @param unsigned int uiSN �����豸��
* @return void
*/
void CMainFrame::OnGraphViewInstrumentSetAuxiliary(unsigned int uiInstrumentType, unsigned int uiSN)
{
	// ��������
	OnMatrixLayoutSetup();
	m_pDlgLayoutSetup->m_oTabWnd.SetActiveTab(1);
	m_pDlgLayoutSetup->OnGraphViewInstrumentSetAuxiliary(uiInstrumentType, uiSN);
}

/**
* ��Ӧ����ͼ����ͼ�����˵������ػص�
* @param unsigned int uiInstrumentType �Ͷ��������� 1-����վ��2-��Դվ��3-�ɼ�վ
* @param unsigned int uiSN �Ͷ������豸��
* @param unsigned int uiInstrumentType �߶��������� 1-����վ��2-��Դվ��3-�ɼ�վ
* @param unsigned int uiSN �߶������豸��
* @return void
*/
void CMainFrame::OnGraphViewInstrumentSetDetour(unsigned int uiInstrumentTypeLow, unsigned int uiSNLow, unsigned int uiInstrumentTypeHigh, unsigned int uiSNHight)
{
	// ��������
	OnMatrixLayoutSetup();
	m_pDlgLayoutSetup->m_oTabWnd.SetActiveTab(2);
	m_pDlgLayoutSetup->OnGraphViewInstrumentSetDetour(uiInstrumentTypeLow, uiSNLow, uiInstrumentTypeHigh, uiSNHight);
}

/**
* ��Ӧ����ͼ����ͼ�����˵�FormLine����
* @param unsigned int uiInstrumentType �������� 1-����վ��2-��Դվ��3-�ɼ�վ
* @param unsigned int uiSN �����豸��
* @return void
*/
void CMainFrame::OnGraphViewInstrumentFormLine(unsigned int uiInstrumentType, unsigned int uiSN)
{
	// FormLine����
	OnMatrixFormLineSetup();
	m_pDlgFormLineSetup->OnGraphViewInstrumentFormLine(uiInstrumentType, uiSN);
}

/**
* ��Ӧ�첨��ͼ����ͼ�����˵�Mute����
* @param unsigned int uiNbLine ���ߺ�
* @param unsigned int uiNbPoint	����
* @return void
*/
void CMainFrame::OnGraphViewSensorSetMute(unsigned int uiNbLine, unsigned int uiNbPoint)
{
	// ��������
	OnMatrixLayoutSetup();
	m_pDlgLayoutSetup->m_oTabWnd.SetActiveTab(3);
	m_pDlgLayoutSetup->OnGraphViewSensorSetMute(uiNbLine, uiNbPoint);
}

/**
* ��Ӧ����ͼ����ͼ�����˵�FieldOn/Off����
* @param void
* @return void
*/
// 
void CMainFrame::OnToolBarFieldOperation()
{
	m_oSiteData.m_oSocketInterfaceCmdSend.m_oFrameInterface.m_byFieldOperation = m_byFieldOperation;
	m_oSiteData.m_oSocketInterfaceCmdSend.m_oFrameInterface.MakeFieldFrame();
	m_oSiteData.m_oSocketInterfaceCmdSend.SendCommandFrame();
}

// ���ù�����
void CMainFrame::OnResetToolBarMatrix()
{
	CBCGPToolbarMenuButton* pButtonGraph =  DYNAMIC_DOWNCAST (CBCGPToolbarMenuButton, m_wndToolBarMatrixView.GetButton (0));
	if (pButtonGraph != NULL)
	{
		pButtonGraph->SetImage (CImageHash::GetImageOfCommand (ID_MATRIX_VIEWGRAPH));
	}

	CBCGPToolbarMenuButton* pButtonList =  DYNAMIC_DOWNCAST (CBCGPToolbarMenuButton, m_wndToolBarMatrixView.GetButton (1));
	if (pButtonList != NULL)
	{
		pButtonList->SetImage (CImageHash::GetImageOfCommand (ID_MATRIX_VIEWLIST));
	}
	m_wndToolBarMatrixView.Invalidate ();
	m_wndToolBarMatrixView.UpdateWindow ();

	CBCGPToolbarButton* pBN = NULL;
	pBN = m_wndToolBarMatrixField.GetButton(0);	
	pBN->SetImage(CImageHash::GetImageOfCommand (ID_BUTTON_MATRIX_FIELD_ON, FALSE));

	pBN = m_wndToolBarMatrixField.GetButton(1);	
	pBN->SetImage(CImageHash::GetImageOfCommand (ID_BUTTON_MATRIX_FIELD_OFF, FALSE));

	m_wndToolBarMatrixField.Invalidate ();
	m_wndToolBarMatrixField.RedrawWindow();
}

void CMainFrame::OnToolbarMatrixViewGraph()
{

}

void CMainFrame::OnToolbarMatrixViewList()
{

}