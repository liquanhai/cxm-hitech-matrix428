// MainFrm.cpp : CMainFrame ���ʵ��
//

#include "stdafx.h"
#include "Operation.h"
#include "MainFrm.h"
#include "OperationParseXML.h"
#include "OperationDoc.h"
#include "OperationView.h"
#include "DlgResultsOfAckedVP.h"
#include "DlgAssociateVP.h"
#include "DlgAssociateSFLSFN.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMainFrame
//��ӵı�ʶֻ����һ�ε�������, �Լ�����һ������ֵ
extern CString	 g_strProgName;
extern HANDLE    g_hProgValue;  

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	ON_WM_CREATE()
	ON_COMMAND(ID_VIEW_CUSTOMIZE, OnViewCustomize)
	ON_REGISTERED_MESSAGE(BCGM_RESETTOOLBAR, OnToolbarReset)
	ON_REGISTERED_MESSAGE(BCGM_TOOLBARMENU, OnToolbarContextMenu)
	// cxm 2012.3.7
// 	ON_COMMAND(ID_VIEW_WORKSPACE, OnViewWorkspace)
// 	ON_UPDATE_COMMAND_UI(ID_VIEW_WORKSPACE, OnUpdateViewWorkspace)
	ON_COMMAND_RANGE(ID_VIEW_APPLOOK_2000, ID_VIEW_APPLOOK_CARBON, OnAppLook)
	ON_UPDATE_COMMAND_UI_RANGE(ID_VIEW_APPLOOK_2000, ID_VIEW_APPLOOK_CARBON, OnUpdateAppLook)
	ON_WM_DESTROY()
	ON_COMMAND(ID_VIEW_ACTIVESOURCE, &CMainFrame::OnViewActivesource)
	ON_COMMAND(ID_VIEW_ALLVP, &CMainFrame::OnViewAllvp)
	ON_UPDATE_COMMAND_UI(ID_VIEW_ALLVP, &CMainFrame::OnUpdateViewAllvp)
	ON_UPDATE_COMMAND_UI(ID_VIEW_ACTIVESOURCE, &CMainFrame::OnUpdateViewActivesource)
	ON_COMMAND(ID_VIEW_ALLDONE, &CMainFrame::OnViewAlldone)
	ON_UPDATE_COMMAND_UI(ID_VIEW_ALLDONE, &CMainFrame::OnUpdateViewAlldone)
	ON_COMMAND(ID_VIEW_ALLTODO, &CMainFrame::OnViewAlltodo)
	ON_UPDATE_COMMAND_UI(ID_VIEW_ALLTODO, &CMainFrame::OnUpdateViewAlltodo)		
	ON_WM_TIMER()
	ON_COMMAND_RANGE(ID_VPSHOT_ONE, ID_VPDONESHOT_TEN, OnShotPoint)
	ON_COMMAND(ID_SETUP_SOURCE, &CMainFrame::OnSetupSource)
	ON_COMMAND(ID_SETUP_OPERATION, &CMainFrame::OnSetupOperation)
	ON_COMMAND(ID_SETUP_COMMENTS, &CMainFrame::OnSetupComments)
	ON_COMMAND(ID_SETUP_DELAYSTEUP, &CMainFrame::OnSetupDelaysteup)
	ON_COMMAND(ID_SETUP_PROCESSTYPE, &CMainFrame::OnSetupProcesstype)
	// cxm 2012.3.7
// 	ON_REGISTERED_MESSAGE(WM_NEWLOG, OnNewLog)
// 	ON_REGISTERED_MESSAGE(WM_NEWXMLFILE, OnNewXMLFile)
END_MESSAGE_MAP()

//ON_MESSAGE(WM_MSG_SHOT,OnStartShot)
static UINT indicators[] =
{
	ID_SEPARATOR,           // ״̬��ָʾ��
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};


// CMainFrame ����/����
CMainFrame::CMainFrame()
// cxm 2012.3.7
/*: m_pOperationSvrSock(NULL)*/
{
	// TODO: �ڴ���ӳ�Ա��ʼ������
	m_nAppLook = theApp.GetInt (_T("ApplicationLook"), ID_VIEW_APPLOOK_2007_1);
	
}

CMainFrame::~CMainFrame()
{
}


int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	OnAppLook (m_nAppLook);
	
	CBCGPToolBar::EnableQuickCustomization ();
	CList<UINT, UINT>	lstBasicCommands;

	lstBasicCommands.AddTail (ID_VIEW_TOOLBARS);
	lstBasicCommands.AddTail (ID_FILE_NEW);
	lstBasicCommands.AddTail (ID_FILE_OPEN);
	lstBasicCommands.AddTail (ID_FILE_SAVE);
	lstBasicCommands.AddTail (ID_FILE_PRINT);
	lstBasicCommands.AddTail (ID_APP_EXIT);
	lstBasicCommands.AddTail (ID_EDIT_CUT);
	lstBasicCommands.AddTail (ID_EDIT_PASTE);
	lstBasicCommands.AddTail (ID_EDIT_UNDO);
	lstBasicCommands.AddTail (ID_APP_ABOUT);
	lstBasicCommands.AddTail (ID_VIEW_TOOLBAR);
	lstBasicCommands.AddTail (ID_VIEW_CUSTOMIZE);
	lstBasicCommands.AddTail (ID_VIEW_APPLOOK_2000);
	lstBasicCommands.AddTail (ID_VIEW_APPLOOK_XP);
	lstBasicCommands.AddTail (ID_VIEW_APPLOOK_2003);
	lstBasicCommands.AddTail (ID_VIEW_APPLOOK_VS2005);
	lstBasicCommands.AddTail (ID_VIEW_APPLOOK_VS2008);
	lstBasicCommands.AddTail (ID_VIEW_APPLOOK_WIN_XP);
	lstBasicCommands.AddTail (ID_VIEW_APPLOOK_2007_1);
	lstBasicCommands.AddTail (ID_VIEW_APPLOOK_2007_2);
	lstBasicCommands.AddTail (ID_VIEW_APPLOOK_2007_3);
	lstBasicCommands.AddTail (ID_VIEW_APPLOOK_2007_4);
	lstBasicCommands.AddTail (ID_VIEW_APPLOOK_CARBON);

	CBCGPToolBar::SetBasicCommands (lstBasicCommands);
	

	if (!m_wndMenuBar.Create (this))
	{
		TRACE0("Failed to create menubar\n");
		return -1;      // fail to create
	}
	m_wndMenuBar.SetBarStyle(m_wndMenuBar.GetBarStyle() | CBRS_SIZE_DYNAMIC);
	m_wndMenuBar.SetShowAllCommands(TRUE);


	CClientDC dc (this);
	BOOL bIsHighColor = dc.GetDeviceCaps (BITSPIXEL) > 8;

	m_wndToolBarView.SetLockedSizes(CSize(25,16),CSize(25,16));
	UINT uiToolbarHotID = bIsHighColor ? IDB_VIEWBAR256 : 0;
	if (!m_wndToolBarView.CreateEx(this /*, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP
		| CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC*/) ||
		!m_wndToolBarView.LoadToolBar(IDR_VIEWWNDBAR, 0, 0, TRUE, 0, 0, uiToolbarHotID))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}
	//SIZE sizeButton;
	//SIZE sizeImage;

	
	if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP
		| CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndToolBar.LoadToolBar(IDR_MAINFRAME, 0, 0, FALSE, 0, 0, 0))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}	
	m_wndToolBarSetup.SetLockedSizes(CSize(16,16),CSize(16,16));
	uiToolbarHotID = bIsHighColor ? IDB_SETUPBAR256 : 0;
	if (!m_wndToolBarSetup.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP
		| CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndToolBarSetup.LoadToolBar(IDR_SETUPBAR, 0, 0, TRUE, 0, 0, uiToolbarHotID))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}
	
	if (!m_wndStatusBar.Create(this) ||
		!m_wndStatusBar.SetIndicators(indicators,
		sizeof(indicators)/sizeof(UINT)))
	{
		TRACE0("Failed to create status bar\n");
		return -1;      // fail to create
	}

	// TODO: �������Ҫ��ͣ������������ɾ��������
	m_wndMenuBar.EnableDocking(CBRS_ALIGN_ANY);
	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	m_wndToolBarSetup.EnableDocking(CBRS_ALIGN_ANY);
	m_wndToolBarView.EnableDocking(CBRS_ALIGN_ANY);
	m_wndActiveSource.EnableDocking(CBRS_ALIGN_ANY);//CBRS_ALIGN_BOTTOM	
	m_wndVPAll.EnableDocking(CBRS_ALIGN_ANY);
	m_wndVPToDo.EnableDocking(CBRS_ALIGN_ANY);
	m_wndVPDone.EnableDocking(CBRS_ALIGN_ANY);	// CBRS_ALIGN_BOTTOM
	
	EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndMenuBar);
	DockControlBar(&m_wndToolBarView);
	DockControlBarLeftOf(&m_wndToolBarSetup,&m_wndToolBarView);
	DockControlBarLeftOf(&m_wndToolBar,&m_wndToolBarSetup);
	
	DockControlBar(&m_wndActiveSource);
	DockControlBar(&m_wndVPAll);
	m_wndVPToDo.DockToWindow (&m_wndVPAll, CBRS_ALIGN_BOTTOM);
	m_wndVPDone.DockToWindow (&m_wndVPToDo, CBRS_ALIGN_TOP);
	RecalcLayout();

	// cxm 2012.3.7
// 	theApp.WriteLog(_T("CMainFrame::OnCreate"),_T("Start initialization configuration parameters!"),LOGTYPE_NORMAL,TRUE);
// 	ParseXMLFile();
// 	// �����ͻ���socket
// 	CreateShotSvrSocket();
	
	// ���ó������ԣ�ȷ�����������һ��	
	SetProp(m_hWnd,g_strProgName,g_hProgValue);
	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	return TRUE;
}


// CMainFrame ���

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}

#endif //_DEBUG


// CMainFrame ��Ϣ�������
void CMainFrame::OnViewCustomize()
{
	//------------------------------------
	// Create a customize toolbars dialog:
	//------------------------------------
	CBCGPToolbarCustomize* pDlgCust = new CBCGPToolbarCustomize (this,
		TRUE /* Automatic menus scaning */
		);

	pDlgCust->Create ();
}

LRESULT CMainFrame::OnToolbarContextMenu(WPARAM,LPARAM lp)
{
	CPoint point (BCG_GET_X_LPARAM(lp), BCG_GET_Y_LPARAM(lp));

	CMenu menu;
	VERIFY(menu.LoadMenu (IDR_POPUP_TOOLBAR));

	CMenu* pPopup = menu.GetSubMenu(0);
	ASSERT(pPopup != NULL);

	CBCGPPopupMenu* pPopupMenu = new CBCGPPopupMenu;
	pPopupMenu->Create (this, point.x, point.y, pPopup->Detach ());

	return 0;
}

afx_msg LRESULT CMainFrame::OnToolbarReset(WPARAM wp, LPARAM)
{
	UINT uiToolBarId = (UINT) wp;
	if (uiToolBarId == IDR_MAINFRAME)
	{
//		CBCGPToolbarButton buttonUpdate (ID_VIEW_UPDATEALLVIEWS, -1, _T("&Update All Views"));
//		m_wndToolBar.InsertButton (buttonUpdate, 3);
	}

	return 0;
}
// cxm 2012.3.7
// BOOL CMainFrame::OnShowPopupMenu (CBCGPPopupMenu* pMenuPopup)
// {
// 	//---------------------------------------------------------
// 	// Replace ID_VIEW_TOOLBARS menu item to the toolbars list:
// 	//---------------------------------------------------------
// 
// 	CFrameWnd::OnShowPopupMenu (pMenuPopup);
// 
// 	if (pMenuPopup != NULL &&
// 		pMenuPopup->GetMenuBar ()->CommandToIndex (ID_VIEW_TOOLBARS) >= 0)
// 	{
// 		if (CBCGPToolBar::IsCustomizeMode ())
// 		{
// 			//----------------------------------------------------
// 			// Don't show toolbars list in the cuztomization mode!
// 			//----------------------------------------------------
// 			return FALSE;
// 		}
// 
// 		pMenuPopup->RemoveAllItems ();
// 
// 		CMenu menu;
// 		VERIFY(menu.LoadMenu (IDR_POPUP_TOOLBAR));
// 
// 		CMenu* pPopup = menu.GetSubMenu(0);
// 		ASSERT(pPopup != NULL);
// 
// 		pMenuPopup->GetMenuBar ()->ImportFromMenu (*pPopup, TRUE);
// 	}
// /**/
// 	return TRUE;
// }

// cxm 2012.3.7
// void CMainFrame::OnViewWorkspace() 
// {
// 	/*
// 	ShowControlBar (&m_wndWorkSpace,
// 		!(m_wndWorkSpace.IsVisible ()),
// 		FALSE, TRUE);
// 	ShowControlBar (&m_wndGridWorkSpace,
// 		!(m_wndGridWorkSpace.IsVisible ()),
// 		FALSE, TRUE);
// 	RecalcLayout ();
// 	*/
// }
// 
// void CMainFrame::OnUpdateViewWorkspace(CCmdUI* pCmdUI) 
// {
// //	pCmdUI->SetCheck (m_wndWorkSpace.IsVisible ());
// }

void CMainFrame::OnAppLook(UINT id)
{
	CBCGPDockManager::SetDockMode (BCGP_DT_SMART);

	m_nAppLook = id;

	CBCGPTabbedControlBar::m_StyleTabWnd = CBCGPTabWnd::STYLE_3D;

	switch (m_nAppLook)
	{
	case ID_VIEW_APPLOOK_2000:
		// enable Office 2000 look:
		CBCGPVisualManager::SetDefaultManager (RUNTIME_CLASS (CBCGPVisualManager));
		break;

	case ID_VIEW_APPLOOK_XP:
		// enable Office XP look:
		CBCGPVisualManager::SetDefaultManager (RUNTIME_CLASS (CBCGPVisualManagerXP));
		break;

	case ID_VIEW_APPLOOK_WIN_XP:
		// enable Windows XP look (in other OS Office XP look will be used):
		CBCGPWinXPVisualManager::m_b3DTabsXPTheme = TRUE;
		CBCGPVisualManager::SetDefaultManager (RUNTIME_CLASS (CBCGPWinXPVisualManager));
		break;

	case ID_VIEW_APPLOOK_2003:
		// enable Office 2003 look:
		CBCGPVisualManager::SetDefaultManager (RUNTIME_CLASS (CBCGPVisualManager2003));
		CBCGPDockManager::SetDockMode (BCGP_DT_SMART);
		break;

	case ID_VIEW_APPLOOK_VS2005:
		// enable VS 2005 Look:
		CBCGPVisualManager::SetDefaultManager (RUNTIME_CLASS (CBCGPVisualManagerVS2005));
		CBCGPTabbedControlBar::m_StyleTabWnd = CBCGPTabWnd::STYLE_3D_ROUNDED;
		CBCGPVisualManager::GetInstance ();
		CBCGPDockManager::SetDockMode (BCGP_DT_SMART);
		break;

	case ID_VIEW_APPLOOK_VS2008:
		// enable VS 2008 Look:
		CBCGPVisualManager::SetDefaultManager (RUNTIME_CLASS (CBCGPVisualManagerVS2008));
		CBCGPVisualManager::GetInstance ();
		CBCGPDockManager::SetDockMode (BCGP_DT_SMART);
		break;

	case ID_VIEW_APPLOOK_2007_1:
		// enable Office 2007 look:
		CBCGPVisualManager2007::SetStyle (CBCGPVisualManager2007::VS2007_LunaBlue);
		CBCGPVisualManager::SetDefaultManager (RUNTIME_CLASS (CBCGPVisualManager2007));
		CBCGPDockManager::SetDockMode (BCGP_DT_SMART);
		break;

	case ID_VIEW_APPLOOK_2007_2:
		// enable Office 2007 look:
		CBCGPVisualManager2007::SetStyle (CBCGPVisualManager2007::VS2007_ObsidianBlack);
		CBCGPVisualManager::SetDefaultManager (RUNTIME_CLASS (CBCGPVisualManager2007));
		CBCGPDockManager::SetDockMode (BCGP_DT_SMART);
		break;

	case ID_VIEW_APPLOOK_2007_3:
		// enable Office 2007 look:
		CBCGPVisualManager2007::SetStyle (CBCGPVisualManager2007::VS2007_Aqua);
		CBCGPVisualManager::SetDefaultManager (RUNTIME_CLASS (CBCGPVisualManager2007));
		CBCGPDockManager::SetDockMode (BCGP_DT_SMART);
		break;

	case ID_VIEW_APPLOOK_2007_4:
		// enable Office 2007 look:
		CBCGPVisualManager2007::SetStyle (CBCGPVisualManager2007::VS2007_Silver);
		CBCGPVisualManager::SetDefaultManager (RUNTIME_CLASS (CBCGPVisualManager2007));
		CBCGPDockManager::SetDockMode (BCGP_DT_SMART);
		break;

	case ID_VIEW_APPLOOK_CARBON:
		// enable Carbon Look:
		CBCGPVisualManager::SetDefaultManager (RUNTIME_CLASS (CBCGPVisualManagerCarbon));
		CBCGPVisualManager::GetInstance ();
		CBCGPDockManager::SetDockMode (BCGP_DT_SMART);
		break;

	default:
		ASSERT (FALSE);
	}

	CBCGPDockManager* pDockManager = GetDockManager ();
	if (pDockManager != NULL)
	{
		ASSERT_VALID (pDockManager);
		pDockManager->AdjustBarFrames ();
	}

	CBCGPTabbedControlBar::ResetTabs ();

	RecalcLayout ();
	RedrawWindow (NULL, NULL, RDW_ALLCHILDREN | RDW_INVALIDATE | RDW_UPDATENOW | RDW_ERASE);

	theApp.WriteInt (_T("ApplicationLook"), m_nAppLook);
}

void CMainFrame::OnUpdateAppLook(CCmdUI* pCmdUI)
{
	pCmdUI->SetRadio (m_nAppLook == pCmdUI->m_nID);
}


BOOL CMainFrame::OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext) 
{
	if (!CFrameWnd::OnCreateClient(lpcs, pContext))
	{
		return FALSE;
	}
/*
	m_wndWorkSpace.SetContext (pContext);

	if (!m_wndWorkSpace.Create (_T("View  1"), this, CRect (0, 0, 300, 300),
		TRUE, ID_VIEW_WORKSPACE,
		WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | CBRS_LEFT | CBRS_FLOAT_MULTI))
	{
		TRACE0("Failed to create Workspace bar\n");
		return FALSE;      // fail to create
	}
*/
	m_wndActiveSource.SetContext (pContext);
	if (!m_wndActiveSource.Create (_T("Active Source"), this, CRect (0, 0, 1024, 200),
		TRUE, ID_VIEW_WORKSPACE+10,
		WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | CBRS_TOP | CBRS_FLOAT_MULTI))
	{
		TRACE0("Failed to create ActiveSource Workspace bar\n");
		return FALSE;      // fail to create
	}

	m_wndVPAll.SetContext (pContext);
	if (!m_wndVPAll.Create (_T("All VP"), this, CRect (0, 201, 1024, 500),
		TRUE, ID_VIEW_WORKSPACE,
		WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | CBRS_TOP  | CBRS_FLOAT_MULTI))
	{
		TRACE0("Failed to create VPAll Workspace bar\n");
		return FALSE;      // fail to create
	}

	m_wndVPToDo.SetContext (pContext);
	if (!m_wndVPToDo.Create (_T("VP To Do"), this, CRect (0, 501, 1024, 700),
		TRUE, ID_VIEW_WORKSPACE+2,
		WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | CBRS_TOP  | CBRS_FLOAT_MULTI))
	{
		TRACE0("Failed to create VP To Do Workspace bar\n");
		return FALSE;      // fail to create
	}

	m_wndVPDone.SetContext (pContext);
	if (!m_wndVPDone.Create (_T("VP Done"), this, CRect (0, 701, 1024, 900),
		TRUE, ID_VIEW_WORKSPACE+3,
		WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | CBRS_TOP| CBRS_FLOAT_MULTI  ))	// 
	{
		TRACE0("Failed to create VP Done Workspace bar\n");
		return FALSE;      // fail to create
	}
	return TRUE;
}

void CMainFrame::OnDestroy()
{
	CBCGPFrameWnd::OnDestroy();

	// TODO: �ڴ˴������Ϣ����������
	// cxm 2012.3.7
// 	if(m_pOperationSvrSock)
// 	{
// 		m_pOperationSvrSock->Close();
// 		delete m_pOperationSvrSock;
// 		m_pOperationSvrSock = NULL;
// 	}
	// �ͷ����еĲɼ�������
	m_ChannelList.OnClose();

}

// cxm 2012.3.7
/******************************************************************************
    ��    ����
    
    ��    �룺
    
    ��    ����
  
    �� �� ֵ��
    
    ��    �ܣ�  ����XML�����ļ���������ڱ���Դ���������͡��ɼ�����
 
    �޸���ʷ��

*******************************************************************************/
// bool CMainFrame::ParseXMLFile(void)
// {
// 	//-----------------------------------------------------------------
// 	// �ɼ�վ������Ϣ
// 	CConfigParseXML		ConfigXML;
// 	CString    strPath = CLIENTDIR_XMLFILE;
// 	ConfigXML.ParseCrewConfig(strPath+CONFIG_XMLFILE,&m_FDUConfig);
// 	ConfigXML.ParseDiskRecord(strPath+CONFIG_XMLFILE,&m_DiskConfig);
// 
// 	//-----------------------------------------------------------------
// 	COperationParseXML		OperaXML;
// 	// �Ӳ��߶����ļ��ж�ȡ������
// 	if(!OperaXML.ParseAuxChannel(strPath+MATRIX_XMLFILE,&m_AllAuxChannels))
// 	{
// 		// WriteLog(_T("Read Matrix Aux channel file error��"));
// 		return FALSE;
// 	}
// 	// ����ϵͳ���ã�IP��ַ���˿ڵ�
// 	// OperaXML.ParseClientSetup(OPERATION_XMLFILE);	
// 	// ����������Ϣ
// 	OperaXML.ParseComments(theApp.m_strLocalXMLFile,&m_AllComments);
// 	// �������ڱ�
// 	OperaXML.ParseOperationTable(theApp.m_strLocalXMLFile,&m_AllShotPoints);	
// 	m_wndVPAll.LoadShotPoints(&m_AllShotPoints);
// 	m_wndVPToDo.LoadShotPoints(&m_AllShotPoints);
// 	m_wndVPDone.LoadShotPoints(&m_AllShotPoints);
// 	// ������Դ
// 	OperaXML.ParseSourceType(theApp.m_strLocalXMLFile,&m_AllShotSources);
// 	m_wndActiveSource.LoadShotSources(&m_AllShotSources);	
// 	// ������������
// 	OperaXML.ParseProcessType(theApp.m_strLocalXMLFile,&m_AllProcesses);
// 
// 	// ��ȡ�ɼ�����
// 	m_ChannelList.OnInit();
// 	m_ChannelList.LoadSiteData();
// 	strPath = CLIENTDIR_XMLFILE;
// 	OperaXML.ParseAllAbsoluteSpread(strPath+MATRIX_XMLFILE,&m_AllSpreads,&m_ChannelList);
// 	theApp.WriteLog(_T("CMainFrame::ParseXMLFile"),_T("Complete the initialization configuration parameters!"),LOGTYPE_NORMAL,TRUE);
// 	return false;
// }
// cxm 2012.3.7
/**
 * @brief ��Ӧ��WM_NEWXMLFILE����Ϣ
 * @note  ��Ӧ��WM_NEWXMLFILE����Ϣ���ж���һ��XML�����ļ����޸ģ���������Ӧ�Ĳ�����
 * @param  WPARAM wParam, ���޸ĵ�XML�ļ���ţ���MatrixDef.h�ļ��ж����������
 * @param  LPARAM lParam�����������ļ�����һ���������޸�
 * @return LRESULT
 */
// LRESULT CMainFrame::OnNewXMLFile(WPARAM wParam, LPARAM lParam)
// {
// 	CString    strPath= CLIENTDIR_XMLFILE;
// 	// ----------------------------------------------------------
// 	//  Config���������ļ��޸�
// 	if(wParam == MATRIX_CONFIG)
// 	{
// 		CConfigParseXML		ConfigXML;
// 		strPath = CLIENTDIR_XMLFILE;
// 		ConfigXML.ParseCrewConfig(strPath+CONFIG_XMLFILE,&m_FDUConfig);
// 		ConfigXML.ParseDiskRecord(strPath+CONFIG_XMLFILE,&m_DiskConfig);
// 		return 0;
// 	}
// 	// -------------------------------------------------------
// 	// ���߳��������ļ��޸�
// 	if(wParam == MATRIX_LINE)
// 	{
// 		// ����������Ϣ
// 		COperationParseXML		OperaXML;
// 		switch(lParam)
// 		{
// 		case MATRIX_LINE_AUXI:			// ���¸���������
// 			strPath = CLIENTDIR_XMLFILE;
// 			m_AllAuxChannels.RemoveAll();
// 			if(OperaXML.ParseAuxChannel(strPath+MATRIX_XMLFILE,&m_AllAuxChannels))
// 			{			
// 				theApp.WriteLog(_T("CMainFrame::OnNewXMLFile"),_T("Matrix Auxiliary channels has been modified."),LOGTYPE_NORMAL,TRUE);			
// 			}
// 			else
// 			{
// 				theApp.WriteLog(_T("CMainFrame::OnNewXMLFile"),_T("Fail to read Matrix Aux channel file!"),LOGTYPE_ERROR,TRUE);
// 				return 0;
// 			}
// 			break;
// 		case MATRIX_LINE_SPREAD:			// ��ȡ����
// 			// ��ȡ�ɼ�����
// 			m_ChannelList.OnReset();
// 			m_ChannelList.LoadSiteData();
// 			m_AllSpreads.RemoveAll();
// 			strPath = CLIENTDIR_XMLFILE;
// 			if(OperaXML.ParseAllAbsoluteSpread(strPath+MATRIX_XMLFILE,&m_AllSpreads,&m_ChannelList)<0)
// 			{
// 				// ������������
// 				theApp.WriteLog(_T("CMainFrame::OnNewXMLFile"),_T("Fail to read Matrix spread type file!"),LOGTYPE_ERROR,TRUE);
// 				return 0;
// 			}
// 			break;
// 		}	
// 	}
// 	return 0;
// }
// cxm 2012.3.7
/******************************************************************************
    ��    ����CreateShotSvrSocket
    
    ��    �룺
    
    ��    ����
  
    �� �� ֵ��
    
    ��    �ܣ� ������ʩ��������ͨ�ŵ�socket

    �޸���ʷ��

*******************************************************************************/
// bool CMainFrame::CreateShotSvrSocket(void)
// {
// 	if(m_pOperationSvrSock)
// 	{
// 		m_pOperationSvrSock->Close();
// 		delete m_pOperationSvrSock;
// 		m_pOperationSvrSock = NULL;
// 	}
// 	m_pOperationSvrSock = new CSocketShotServer;
// 	// ������ʩ��������ͨ�ŵ�Socket
// 	if(m_pOperationSvrSock)
// 	{
// 		if(!m_pOperationSvrSock->CreateSocket(OPERATION_CLIENTPORT,theApp.m_strHostIP))
// 		{
// 			AfxMessageBox(_T("������ʩ��������ͨ�ŵ�Socketʧ�ܣ����IP��ַ���ã�"));
// 			delete m_pOperationSvrSock;
// 			m_pOperationSvrSock = NULL;
// 			return false;
// 		}
// 	}
// 	theApp.WriteLog(_T("CMainFrame::CreateShotSvrSocket"),_T("Successfully created a client communication interface!"),LOGTYPE_NORMAL,TRUE);
// 	return true;
// }
/******************************************************************************
    ��    ����
    
    ��    �룺
    
    ��    ����
  
    �� �� ֵ��
    
    ��    �ܣ� ����һ��

    �޸���ʷ��

*******************************************************************************/

void CMainFrame::OnViewActivesource()
{
	// TODO: �ڴ���������������
	ShowControlBar (&m_wndActiveSource,	!(m_wndActiveSource.IsVisible ()),	FALSE, TRUE);
}
void CMainFrame::OnUpdateViewActivesource(CCmdUI *pCmdUI)
{
	// TODO: �ڴ������������û����洦��������
	pCmdUI->SetCheck(m_wndActiveSource.IsVisible ());
}

void CMainFrame::OnViewAllvp()
{
	// TODO: �ڴ���������������
	ShowControlBar (&m_wndVPAll, !(m_wndVPAll.IsVisible ()),	FALSE, TRUE);
	// cxm 2012.3.7
//	theApp.WriteLog(_T("CMainFrame::OnViewAllvp"),_T("Show All VP succeed!"),LOGTYPE_NORMAL,TRUE);
}

void CMainFrame::OnUpdateViewAllvp(CCmdUI *pCmdUI)
{
	// TODO: �ڴ������������û����洦��������
	pCmdUI->SetCheck(m_wndVPAll.IsVisible ());
}

void CMainFrame::OnViewAlldone()
{
	// TODO: �ڴ���������������
	ShowControlBar (&m_wndVPDone, !(m_wndVPDone.IsVisible ()),	FALSE, TRUE);
}

void CMainFrame::OnUpdateViewAlldone(CCmdUI *pCmdUI)
{
	// TODO: �ڴ������������û����洦��������
	pCmdUI->SetCheck(m_wndVPDone.IsVisible ());
}

void CMainFrame::OnViewAlltodo()
{
	// TODO: �ڴ���������������
	ShowControlBar (&m_wndVPToDo, !(m_wndVPToDo.IsVisible ()),	FALSE, TRUE);	
}

void CMainFrame::OnUpdateViewAlltodo(CCmdUI *pCmdUI)
{
	// TODO: �ڴ������������û����洦��������
	pCmdUI->SetCheck(m_wndVPToDo.IsVisible ());
}
// cxm 2012.3.7
// LRESULT CMainFrame::OnNewLog(WPARAM wParam, LPARAM lParam)
// {
// 	CLogBase   LogRecord;
// 	// ���ڴ��ж�ȡ��־
// 	if(!theApp.m_LogMapping.ReadRecord((int)lParam,&LogRecord))
// 	{
// 		return -1;
// 	}
// 	CString  strLog;
// 	// ������Ҫ��ʾ����־�ı��ַ���
// 	LogRecord.GetShowString(strLog);
// 	COperationView *pView = (COperationView*)GetActiveView();
// 	// ��ʾ����ͼ��
// 	pView->AppendLog(strLog);
// 	return 0;
// }
/**
 * @brief �����ڵ��״̬
 * @note  �����ڵ��״̬����Ҫ���µ�״̬������
			1��m_AllShotPoints�б���Ķ���
			2��m_wndVPAll��������ʾ��
 * @param  CShotSource* pShotSource, ��Դ����ָ��
 * @param  unsigned char byVPState����״̬
 * @return void
 */
void CMainFrame::SetShotPointState(CShotPoint* pShotPoint,unsigned char byVPState)
{	
	// int i,nCount;
	if(!pShotPoint)
	{
		return ;
	}
	// ����״̬
	pShotPoint->m_VPState = byVPState;
	// ����All VP ����
	m_wndVPAll.RefreshShotPointState(pShotPoint);
	// �ж��Ƿ��Ѿ��������
	if(byVPState == VP_DONE)
	{
		m_wndVPDone.RefreshShotPointState(pShotPoint);
	}
	return ;
}
/**
 * @brief ������Դ��״̬
 * @note  ����ĳһ��Դ��״̬����ˢ����ʾ
 * @param  CShotSource* pShotSource, ��Դ����ָ��
 * @param  unsigned char byVPState����״̬
 * @return void
 */
void CMainFrame::SetShotSourceState(CShotSource* pShotSource,unsigned char byVPState)
{
	if(!pShotSource)
		return ;
	// ����״̬
	pShotSource->m_bySourceState = byVPState;
	// ˢ�½���
	m_wndActiveSource.RefrestShotSourceState(pShotSource);
	return ;
}

/**
 * @brief �������Է�����������֡
 * @note  �����ӷ��������ܵ�����,��CSocketShotServer::OnReceive��������

 ����֡��ʽ��
			֡ͷ��2Byte����֡���ȣ�2Byte��  ��֡������4Byte����֡���ͣ�1Byte��			   
			������(2Byte)�����ݸ�����2Byte�������������䳤�� ��У��λ��1Byte����֡β��2Byte��
 * @param  int nActiveShotIndex, ������ڶ�������
 * @param  unsigned char *pBuf��Ӧ��������ָ֡��
 * @return void
 */
// cxm 2012.3.7
// void CMainFrame::AnalysisProtocolOfServerSock(void)
// {
// 	unsigned char	pBuf[8196];
// 	WORD		wFrmLen;			// ֡��
// 	WORD		wFrmCmdCode;		// ������
// 	DWORD		dwFrmIndex;			// ֡����
// 	DWORD		dwNb1;				// �ں�
// 	DWORD		dwNb2;				// ��Դ��
// 	int			nSize,nReadSize;
// 	CString		strTemp;
// 
// 	if(!m_pOperationSvrSock)
// 		return;
// 
// 	sockaddr_in sockShotServer;
// 	sockShotServer.sin_family = AF_INET;
// 	nSize = sizeof(sockShotServer);
// 	// ��������,nReadSizeΪ���յ������ֽ���
// 	nReadSize = m_pOperationSvrSock->ReceiveFrom( pBuf, 8196, (SOCKADDR*)&sockShotServer , &nSize );
// 	switch (nReadSize)
// 	{
// 	case 0:		// û���յ����� 
// 		return;
// 		break;
// 	case SOCKET_ERROR:	// �������󣬼�¼��־
// 		if (GetLastError() != WSAEWOULDBLOCK) 
// 		{  //����socket���� 
// 			return;
// 		}
// 		break;
// 	default:
// 		break;
// 	}
// 	// -----------����֡��ʽ---------------------------------------------------------
// 	// �ж�֡ͷ�Ƿ�0xEB, 0x90
// 	if (pBuf[0]!=0xEB || pBuf[1]!=0x90)
// 	{		
// 		theApp.WriteLog(_T("CMainFrame::AnalysisProtocolOfServerSock"),_T("Error Frame Head!"),LOGTYPE_ERROR,FALSE);
// 		return;
// 	}
// 	// ����֡����
// 	wFrmLen = MAKEWORD(pBuf[2],pBuf[3]);
// // 	if(wFrmLen>8196)
// // 	{	// ֡���ȳ��������������¼��־	
// // 		WriteLog(_T("Error Frame Length!"),3);
// // 		return;
// // 	}
// 	// ����֡����
// 	memcpy_s(&dwFrmIndex,sizeof(dwFrmIndex),pBuf+4 , 4);	
// 	// ֡β
// 	if(pBuf[wFrmLen-2]!=0x14 || pBuf[wFrmLen-1]!=0x6F)
// 	{
// 		// ֡β������Ҫ���¶�λ֡ͷ
// 		theApp.WriteLog(_T("CMainFrame::AnalysisProtocolOfServerSock"),_T("Error Frame Tail!"),LOGTYPE_ERROR,FALSE);
// 		return;
// 	}
// 	// ������
// 	wFrmCmdCode=MAKEWORD(pBuf[9],pBuf[10]);
// 	// �������ںź���Դ�ţ�Ҳ������ͨ��ID���߳�ID
// 	memcpy_s(&dwNb1,4,pBuf+13,4);
// 	memcpy_s(&dwNb2,4,pBuf+17,4);
// 	// ��ǰ����ķ��ڶ���	
// 	CActiveShot *pActiveShot=NULL;
// 	switch(wFrmCmdCode)
// 	{
// 	case OPERATION_CMD_REQUEST:	// �յ����������Ӧ��
// 		{	// ͨ��Nb���Ҽ���ķ��ڹ������			
// 			pActiveShot = m_AllActiveShots.FindActiveShotByNb(dwNb1,dwNb2);// ||pActiveShot->m_dwServerIP != inet_addr(("255.255.255.255"))
// 			if(!pActiveShot )
// 			{	// �Ѿ����յ���������Ӧ����������ʩ���ͻ��˵�Ӧ�𣬲���Ҫ����
// 				strTemp.Format(_T("Error Shot Nb# %d or Source Nb# %d ."),dwNb1,dwNb2);			
// 				theApp.WriteLog(_T("CMainFrame::AnalysisProtocolOfServerSock"),strTemp,LOGTYPE_WARNING,TRUE);
// 				return;
// 			}
// 			if( pActiveShot->m_dwServerID)
// 			{	// ������ڹ������ķ�����ID��Ϊ0����ʾ���з������߳����ڴ���
// 				strTemp.Format(_T("Error Shot Nb# %d ,Source Nb# %d,Thread ID# %d already selected."),dwNb1,dwNb2,pActiveShot->m_dwServerID);
// 				theApp.WriteLog(_T("CMainFrame::AnalysisProtocolOfServerSock"),strTemp,LOGTYPE_WARNING,TRUE);
// 				return;
// 			}
// 			// �����������IP��ַ�Ͷ˿ڣ���ʱ�����ж��������Ӧ��ֻ�ܱ������һ��
// 			pActiveShot->m_dwServerIP = sockShotServer.sin_addr.s_addr;
// 			pActiveShot->m_wServerPort = ntohs(sockShotServer.sin_port);
// 			KillTimer(pActiveShot->m_dwTimerID);
// 			// ����ȷ������
// 			pBuf[4] = 0x01;								// ֡����
// 			pBuf[8] = 0x01;								// ֡����
// 			pBuf[9] = LOBYTE(OPERATION_CMD_CONFIRM);	// �������λ
// 			pBuf[10]= HIBYTE(OPERATION_CMD_CONFIRM);	// �������λ
// 			pActiveShot->SendToServer(pBuf,nReadSize);
// 			strTemp.Format(_T("Shot Nb# %d, Source Nb# %d, Received Server Ack! "),dwNb1,dwNb2);			
// 			theApp.WriteLog(_T("CMainFrame::AnalysisProtocolOfServerSock"),strTemp,LOGTYPE_NORMAL,TRUE);
// 			return;			
// 		}
// 		break;
// 	case OPERATION_CMD_CONFIRM: // �ҵ�ʩ�������̣߳��·�����
// 		{	// �����ڵ��ź���Դ��Ų��ҵ�ǰ����ķ��ڶ���
// 			pActiveShot = m_AllActiveShots.FindActiveShotByNb(dwNb1,dwNb2);
// 			if(!pActiveShot )
// 			{
// 				strTemp.Format(_T("Shot Nb# %d or Source Nb# %d is wrong."),dwNb1,dwNb2);			
// 				theApp.WriteLog(_T("CMainFrame::AnalysisProtocolOfServerSock"),strTemp,LOGTYPE_ERROR,TRUE);
// 				return;
// 			}
// 			if( pActiveShot->m_dwServerID)
// 			{	// ������ڹ������ķ�����ID��Ϊ0����ʾ���з������߳����ڴ���
// 				strTemp.Format(_T("Shot Nb# %d ,Source Nb# %d,Server Thread ID# %d already selected."),dwNb1,dwNb2,pActiveShot->m_dwServerID);
// 				theApp.WriteLog(_T("CMainFrame::AnalysisProtocolOfServerSock"),strTemp,LOGTYPE_ERROR,TRUE);
// 				return;
// 			}
// 			// ����������ṩ��ͨ��ID
// 			memcpy_s(&pActiveShot->m_dwServerID,4,pBuf+25,4);		
// 			// �߳�ID
// 			memcpy_s(&pActiveShot->m_dwThreadID,4,pBuf+29,4);
// 			// �����������IP��ַ�Ͷ˿ڣ���ʱ�����һ��ȷ��Ӧ��ķ�������ַ
// 			pActiveShot->m_dwServerIP = sockShotServer.sin_addr.s_addr;
// 			pActiveShot->m_wServerPort = ntohs(sockShotServer.sin_port);
// 			// �����ںż� ��Դ
// 			pActiveShot->SendShotPointAndSource();
// 			// ���ʹ������Ͷ���
// 			pActiveShot->SendProcessType();
// 			// ���Ͳɼ�վ������Ϣ
// 			pActiveShot->SendFDUConfig(&m_FDUConfig,&m_DiskConfig);
// 			// ���Ͳɼ�����
// 			pActiveShot->SendShotSpreadLabel();
// 			//pActiveShot->SendShotSpreadChannel();
// 			pActiveShot->SendShotSpreadChannel(&m_AllSpreads,pActiveShot->m_dwSpreadSFL);
// 			// ��������
// 			pActiveShot->SendGeneralCMD(OPERATION_CMD_START);
// 			strTemp.Format(_T("Received Server confired ack frame: Shot Nb# %d ,Source Nb# %d,Thread ID# %d."),dwNb1,dwNb2,pActiveShot->m_dwThreadID);			
// 			theApp.WriteLog(_T("CMainFrame::AnalysisProtocolOfServerSock"),strTemp,LOGTYPE_NORMAL,TRUE);
// 			return;			
// 		}
// 		break;
// 	case OPERATION_ACK_NAME:		// �յ��ɼ�վ�������
// 		{
// 			// ����ͨ��ID��ServerID�����̱߳�ţ�ThreadID�����ҵ�ǰ����ķ��ڶ���
// 			nSize=m_AllActiveShots.FindActiveShotByID(dwNb1,dwNb2);
// 			if(nSize<0)
// 			{				
// 				theApp.WriteLog(_T("CMainFrame::AnalysisProtocolOfServerSock"),_T("1 ServerID or Thread ID is wrong!"),LOGTYPE_ERROR,FALSE);
// 				return;
// 			}
// 			// �������Է������Ĳɼ�վ�������
// 			AnalysisProtocolOfAckResultFrm(nSize,pBuf);
// 		}
// 		break;
// 	case OPERATION_CMD_SRCRDY:	// ��ը��������׼�����źţ�Ready��
// 		{
// 			// �յ���ը��������׼�����ź�: Ӧ���ȸ�����Դ��ͼ�꣬���жϸ���Դ�Ƿ�����ںţ��������������ںŵ�ͼ�ꡣ
// 			nSize=m_AllActiveShots.FindActiveShotByID(dwNb1,dwNb2);
// 			if(nSize<0)
// 			{
// 				theApp.WriteLog(_T("CMainFrame::AnalysisProtocolOfServerSock"),_T("2 ServerID or Thread ID is wrong!"),LOGTYPE_ERROR,FALSE);
// 				return;
// 			}
// 			pActiveShot = m_AllActiveShots.GetActiveShot(nSize);
// 			// �ı���Դ��״̬
// 			SetShotSourceState(pActiveShot->m_pShotSource,SHOTSOURCE_READY);
// 
// 		}
// 		break;
// 	case OPERATION_CMD_TBUPHOLE:	// �յ���ը��״̬����: TB������ʱ��
// 		{
// 			// �յ���ը����: Ӧ���ȸ�����Դ��ͼ�꣬���жϸ���Դ�Ƿ�����ںţ��������������ںŵ�ͼ�ꡣ
// 			nSize=m_AllActiveShots.FindActiveShotByID(dwNb1,dwNb2);
// 			if(nSize<0)
// 			{
// 				theApp.WriteLog(_T("CMainFrame::AnalysisProtocolOfServerSock"),_T("2 ServerID or Thread ID is wrong!"),LOGTYPE_ERROR,FALSE);
// 				return;
// 			}
// 			pActiveShot = m_AllActiveShots.GetActiveShot(nSize);
// 			if(!pActiveShot)
// 			{
// 				return;
// 			}
// 			// ����ȷ��TB������ʱ�䡢��ը��״̬������
// 			pActiveShot->m_byBlasterState = pBuf[29];
// 			memcpy_s(&pActiveShot->m_fConfirmedTB,4,pBuf+33,4);
// 			memcpy_s(&pActiveShot->m_fUpholeTime,4,pBuf+37,4);
// 			pActiveShot->m_bNewBlaster = TRUE;
// 			// ������ʾ����
// 			m_wndActiveSource.RefreshBlasterState();
// 		}
// 		break;
// 	case OPERATION_CMD_ITBERR:   // ITB����
// 		{
// 			nSize=m_AllActiveShots.FindActiveShotByID(dwNb1,dwNb2);
// 			if(nSize<0)
// 			{
// 				theApp.WriteLog(_T("CMainFrame::AnalysisProtocolOfServerSock"),_T("2 ServerID or Thread ID is wrong!"),LOGTYPE_ERROR,FALSE);
// 				return;
// 			}
// 			pActiveShot = m_AllActiveShots.GetActiveShot(nSize);
// 			if(!pActiveShot)
// 			{
// 				return;
// 			}
// 			pActiveShot->m_bITBErr = TRUE;
// 			pActiveShot->m_bNewBlaster = TRUE;
// 			// ������ʾ����
// 			m_wndActiveSource.RefreshBlasterState();
// 		}
// 		break;
// 	case OPERATION_CMD_RCVING:	// ��ʼ���ݲ���
// 		{
// 			// ˢ����Դ���ڵ����ʾ״̬
// 			strTemp.Format(_T("Start Sampling: Server ID# %d, Thread ID# %d "),dwNb1,dwNb2);			
// 			theApp.WriteLog(_T("CMainFrame::AnalysisProtocolOfServerSock"),strTemp,LOGTYPE_NORMAL,TRUE);
// 		}
// 		break;
// 	case OPERATION_CMD_RCVED:   // ���ݲ�������
// 		{
// 			nSize=m_AllActiveShots.FindActiveShotByID(dwNb1,dwNb2);
// 			if(nSize<0)
// 			{
// 				theApp.WriteLog(_T("CMainFrame::AnalysisProtocolOfServerSock"),_T("2 ServerID or Thread ID is wrong!"),LOGTYPE_ERROR,FALSE);
// 				return;
// 			}
// 			pActiveShot = m_AllActiveShots.GetActiveShot(nSize);			
// 			// ����ITB���󵯳��Ի����ɿͻ��ж��Ƿ����
// /*			if(pActiveShot->m_bITBErr)
// 			{
// 				if (MessageBox(_T("Internal Time break! \n Do you want to record?"),_T("ACQUISITION"),MB_OKCANCEL)==IDCANCEL)
// 				{	// ȡ�����ݼ�¼��֪ͨ��������ֹ�˴����ݲ���
// 					pActiveShot->SendGeneralCMD(OPERATION_CMD_CANCEL);
// 					strTemp.Format(_T("Server ID# %d, Thread ID# %d: Internal Time break! Cancel to record."),dwNb1,dwNb2);
// 					theApp.WriteLog(_T("CMainFrame::AnalysisProtocolOfServerSock"),strTemp,LOGTYPE_WARNING,TRUE);
// 					return;
// 				}
// 			}
// */			// ���Ϳ�ʼ��������֪ͨ������������ԭʼ����ת��ΪSEGD�ļ�
// 			pActiveShot->SendGeneralCMD(OPERATION_CMD_PROCGO);
// 			
// 		 }
// 		break;
// 	case OPERATION_CMD_PROCING:	// ���ݴ���ʼ
// 		{
// 			// ˢ����Դ���ڵ����ʾ״̬
// 			strTemp.Format(_T("Start Processing: Server ID# %d, Thread ID# %d "),dwNb1,dwNb2);			
// 			theApp.WriteLog(_T("CMainFrame::AnalysisProtocolOfServerSock"),strTemp,LOGTYPE_NORMAL,TRUE);
// 		}
// 		break;
// 	case OPERATION_CMD_PROCED:	// ���ݴ������
// 		{
// 			// ˢ����Դ���ڵ����ʾ״̬
// 			strTemp.Format(_T("End of Process: Server ID# %d, Thread ID# %d "),dwNb1,dwNb2);			
// 			theApp.WriteLog(_T("CMainFrame::AnalysisProtocolOfServerSock"),strTemp,LOGTYPE_NORMAL,TRUE);
// 		}
// 		break;
// 	case OPERATION_CMD_OUTING:	// �����ʼ
// 		break;
// 	case OPERATION_CMD_OUTED:	// �������
// 		break;
// 	case OPERATION_CMD_SHOTEND:	// ���ڽ������ɷ�����֪ͨ�ͻ���
// 		break;
// 	default:	// ���������
// 		{
// 			strTemp.Format(_T("Command Code 0x%X is wrong!"),wFrmCmdCode);
// 			theApp.WriteLog(_T("CMainFrame::AnalysisProtocolOfServerSock"),strTemp,LOGTYPE_ERROR,FALSE);
// 		}
// 		break;
// 	}
// 	
// }
/**
 * @brief �����ɼ����е���Ӧ����֡
 * @note  �ɼ����з���ǰ�ȵ�����������Ӧ���ԣ�ʩ���������յ������Ľ���󣬽����������͸��ͻ��ˡ�
 �ú�����ʾ��������Ӧ��Ĳɼ�վ��Ϣ������ʾ�û��������ڻ���ֹͣ����
 * @param  int nActiveShotIndex, ������ڶ�������
 * @param  unsigned char *pBuf��Ӧ��������ָ֡��
 * @return void
 */
// cxm 2012.3.7
// void CMainFrame::AnalysisProtocolOfAckResultFrm(int nActiveShotIndex,unsigned char *pBuf)
// {
// 	CActiveShot *pActiveShot = m_AllActiveShots.GetActiveShot(nActiveShotIndex);
// 	if(!pActiveShot)
// 		return;
// 	
// 	int			i,nPos;
// 	WORD		wNoAckedFrmLen;
// 	DWORD		dwNoAcked,dwSpreadCount,dwIP;
// 	CString		strTemp;	
// 	CShotSpread*	pShotSpread =pActiveShot->m_pSpread;
// 	// �������ܵ���Ӧ��ɼ�������
// 	memcpy_s(&dwNoAcked,4,pBuf+21,4);
// 	// ����������֡�д��͹�������Ӧ��ɼ�����ռ�ֽ���
// 	wNoAckedFrmLen = MAKEWORD(pBuf[11],pBuf[12]);
// 	// wNoAckedInFrm = (wNoAckedInFrm-12)/4;		// ����֡��ʽ�������ʱ��ʽ
// 	wNoAckedFrmLen -=12;
// 	// �ɼ���������
// 	int nIndex=0;
// 	int k= m_AllSpreads.GetCount();
// 	for(int j=0;j<k;j++)
// 	{
// 		CShotSpread *pSpread = m_AllSpreads.GetShotSpreadBySN(j+1);
// 		nIndex += pSpread->GetCount();
// 	}
// 	dwSpreadCount = (DWORD)nIndex;
// 	//dwSpreadCount = (DWORD)(pShotSpread->GetCount());			
// 
// 	strTemp.Format(_T("Response Results: Shot Nb# %d ,Source Nb# %d, Spread Count %d, No Acked Count %d"),
// 						pActiveShot->GetShotPointNb(),pActiveShot->GetShotSourceNb(), dwSpreadCount, dwNoAcked);
// 	theApp.WriteLog(_T("CMainFrame::AnalysisProtocolOfAckResultFrm"),strTemp,LOGTYPE_WARNING,TRUE);
// 	TRACE2("Response Results: Spread Count=%d,dwNoAcked=%d \r\n",dwSpreadCount,dwNoAcked);
// 	// WriteLog(strTemp);
// 	// �ɼ����к�Ӧ��ĵ��������ֱ��ˢ�½��棬׼������
// 	if(dwNoAcked == 0)
// 	{
// 		// ����״̬��ˢ����ʾ����
// 		m_wndActiveSource.LoadShotPointBySource(pActiveShot->m_pShotSource, pActiveShot->m_pShotPoint);		
// 		return;
// 	}
// 	// ���û���ʾ��Ӧ��ɼ�վ��Ϣ�Ի���
// 	CDlgResultsOfAckedVP	DlgResult;
// 	DlgResult.m_strResult.Format(_T("%d No Response"),dwNoAcked);
// 	// ������֡���ҳ�������Ӧ��Ĳɼ�վIP��ַ
// 	wNoAckedFrmLen +=24;
// 	for (i=25;i<wNoAckedFrmLen;i+=4)
// 	{
// 		memcpy_s(&dwIP,4,pBuf+i,4);
// 		// ͨ��IP��ַ���Ҷ���
// 		nPos = pShotSpread->Find(dwIP);
// 		if(nPos>=0)
// 		{	// ������ʾ��Ϣ
// 			strTemp.Format(_T("Line Name:% 5d , Point Nb:% 5d  No Response"),pShotSpread->m_arrSpread[nPos].m_dwLineNb,
// 																		pShotSpread->m_arrSpread[nPos].m_dwPointNb);
// 			DlgResult.m_arrResult.Add(strTemp);
// 			// 
// 		}
// 	}
// 	// �ɼ����к�Ӧ��ĵ�������ȣ���ѯ���û�����ѡ��
// 	//if(MessageBox(strTemp,_T("Caution"),MB_YESNO|MB_ICONQUESTION)==IDYES)
// 	if(DlgResult.DoModal()==IDOK)
// 	{	// ȷ�Ϸ��ڣ����ڵ�������ӵ�������Դ���Ա���
// 		m_wndActiveSource.LoadShotPointBySource(pActiveShot->m_pShotSource, pActiveShot->m_pShotPoint);
// 	}
// 	else
// 	{
// 		// ֪ͨ��������ȡ���˴η���
// 		pActiveShot->SendGeneralCMD(OPERATION_CMD_CANCEL);
// 		// �ı���Դ��״̬
// 		SetShotSourceState(pActiveShot->m_pShotSource,SHOTSOURCE_UNUSED);		
// 		strTemp.Format(_T("Cancel Shotting: Shot Nb# %d,Source Nb# %d, Spread Count %d, No Acked Count %d !"),
// 						pActiveShot->GetShotPointNb(),pActiveShot->GetShotSourceNb(),dwSpreadCount, dwNoAcked);
// 		theApp.WriteLog(_T("CMainFrame::AnalysisProtocolOfAckResultFrm"),strTemp,LOGTYPE_WARNING,TRUE);
// 		// ɾ����ǰ����ķ��ڹ������
// 		m_AllActiveShots.RemoveActiveShotAt(nActiveShotIndex);
// 		return;
// 	}
// }
/**
 * @brief ��Ӧ����Ҽ����ڵ���Ϣ
 * @note  �û��ڷ��ڱ�Ĵ��ڵ������Ҽ��󣬸�����Դ��̬�����һ��˵������ݣ��û�ѡ����Դ���з��ڡ�
 * @note  �� VP All���ڣ� ��Ӧ�Ĳ˵� �� ID_VPSHOT_ONE �� ID_VPSHOT_TEN
 * @note  �� VP TODO���ڣ���Ӧ�Ĳ˵��� ID_VPTODOSHOT_ONE �� ID_VPTODOSHOT_TEN  
 * @note  �� VP DONE���ڣ���Ӧ�Ĳ˵��� ID_VPDONESHOT_ONE �� ID_VPDONESHOT_TEN  
 * @param  UINT id, �˵���ID��
 * @return void
 */
void CMainFrame::OnShotPoint(UINT nMenuItemID)
{	
	int				nIndex;
	DWORD			dwShotNb;
	CShotSource*	pShotSource = NULL;
	// ��VP All�Ĵ����Ҽ��˵�ѡ��
	if(nMenuItemID>=ID_VPSHOT_ONE && nMenuItemID<=ID_VPSHOT_TEN)
	{
		if(!m_wndVPAll.GetActiveShotPointNb(&dwShotNb))
		{
			return;
		}
		// ������ѡ�����Դ��������λ��
		nIndex = nMenuItemID-ID_VPSHOT_ONE;
		if(nIndex>m_AllShotSources.GetCount())
			return;
		// �����Դ���
		pShotSource=m_AllShotSources.GetShotSource(nIndex);
		if(pShotSource==NULL)
			return;
		// ׼������
		OnStartShot(dwShotNb, pShotSource->m_dwSourceNb);				
		return;
	}
	// ��VP ToDo�Ĵ����Ҽ��˵�ѡ��
	if(nMenuItemID>=ID_VPTODOSHOT_ONE && nMenuItemID<=ID_VPTODOSHOT_ONE)
	{
		if(!m_wndVPToDo.GetActiveShotPointNb(&dwShotNb))
		{
			return;
		}
		// ������ѡ�����Դ��������λ��
		nIndex = nMenuItemID-ID_VPTODOSHOT_ONE;
		if(nIndex>m_AllShotSources.GetCount())
			return;
		// �����Դ���
		pShotSource = m_AllShotSources.GetShotSource(nIndex);
		if(pShotSource==NULL)
			return;
		// ׼������
		OnStartShot(dwShotNb, pShotSource->m_dwSourceNb);					
		return;
	}
	// ��VP Done�Ĵ����Ҽ��˵�ѡ��
	if(nMenuItemID>=ID_VPDONESHOT_ONE && nMenuItemID<=ID_VPDONESHOT_TEN)
	{
		if(!m_wndVPDone.GetActiveShotPointNb(&dwShotNb))
		{
			return;
		}
		// ������ѡ�����Դ��������λ��
		nIndex = nMenuItemID-ID_VPDONESHOT_ONE;
		if(nIndex>m_AllShotSources.GetCount())
			return;
		// �����Դ���
		pShotSource = m_AllShotSources.GetShotSource(nIndex);
		if(pShotSource==NULL)
			return;
		// ׼������
		OnStartShot(dwShotNb, pShotSource->m_dwSourceNb);					
		return;
	}
	
}
/******************************************************************************************
    ��    ����
    
    ��    �룺DWORD dwShotNb, DWORD dwSourceNb
    
    ��    ����
  
    �� �� ֵ��
    
    ��    �ܣ�

			   һ�����û��ڽ����ϵ���һ��˵���ѡ��ĳһ�ںŻ�����Դ��ʼ���ڣ����͸���Ϣ��

			   �������Զ�����ģʽ�£���ϵͳ�Զ��жϷ��ڡ�

    �޸���ʷ��

*******************************************************************************************/
bool CMainFrame::OnStartShot( DWORD dwShotNb, DWORD dwSourceNb)
{	
	// �����ڵ����
	CShotPoint* pShotPoint = m_AllShotPoints.GetShotPointByNb(dwShotNb);
	// ������Դ����
	CShotSource* pShotSrc = m_AllShotSources.GetShotSourceByNb(dwSourceNb); 
	if(!pShotPoint || !pShotSrc)
	{
		// ��������
		return false;
	}
	// ���Ҳɼ�����
	CShotSpread *pSpread = m_AllSpreads.GetShotSpreadBySN(pShotPoint->m_dwSpreadNb);
	// ���Ҵ������Ͷ���
	CProcessType *pProcess = m_AllProcesses.GetProcessTypeByNb(pShotPoint->m_dwProcessNb);
	if(!pSpread || !pProcess)
	{
		// ��������
		return false;
	}
	// �������ڹ������
	CActiveShot *pActiveShot = new CActiveShot;
	if(!pActiveShot)
	{	// �������ڹ������ʧ��
		return false;
	}
	// ���÷��ڵ㡢�ɼ����С���������
	pActiveShot->SetShotPoint(pShotPoint,pSpread,pProcess);
	// ������Դ��������
	pActiveShot->SetShotSource( pShotSrc,&m_AllAuxChannels);
	m_AllActiveShots.Add(pActiveShot);
	pActiveShot->m_dwTimerID = m_AllActiveShots.GetCount();
	// cxm 2012.3.7
//  	// ������ʩ��������ͨ�ŵ�SOCKET
//  	pActiveShot->m_pSvrSocket= m_pOperationSvrSock;
	// ��������ַ������Ϊ�㲥��ַ�����յ�������Ӧ����¼ʩ��������IP
	pActiveShot->m_dwServerIP = inet_addr(("255.255.255.255"));		
	pActiveShot->m_wServerPort = OPERATION_SVRPORT;
	// ����������������������
	pActiveShot->SendRequestShotService();
	// �ı���Դ��״̬
	SetShotSourceState(pShotSrc,SHOTSOURCE_NEXT);
	// �����ط���ʱ��
	SetTimer(pActiveShot->m_dwTimerID,1000,NULL);
	CString  strTemp;
	strTemp.Format(_T("Shot Nb#: %d, Source Nb#: %d, Request to Shot! "),dwShotNb,dwSourceNb);
	// cxm 2012.3.7
//	theApp.WriteLog(_T("CMainFrame::OnStartShot"),strTemp,LOGTYPE_NORMAL,TRUE);
	return true;
}
/******************************************************************************
    ��    ����
    
    ��    �룺
    
    ��    ����
  
    �� �� ֵ��
    
    ��    �ܣ� ��ʱ����������

    �޸���ʷ��

*******************************************************************************/
void CMainFrame::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	int i;
	int nCount = m_AllActiveShots.GetCount();
	CActiveShot* pActiveShot = NULL;
	for (i=0;i<nCount;i++)
	{
		pActiveShot=m_AllActiveShots.GetActiveShot(i);
		if(pActiveShot->m_dwTimerID !=nIDEvent )
			continue;
		// �ط�������
		pActiveShot->m_dwRetransCount++;
		if(pActiveShot->m_dwRetransCount>2)
		{
			KillTimer(pActiveShot->m_dwTimerID);
			// �ط�������Ӧ����ʾ������Ϣ���رն�ʱ��		
			// cxm 2012.3.7
//			theApp.WriteLog(_T("CMainFrame::OnTimer"),_T("Operation Server No Answer,Stop to Shot!"),LOGTYPE_WARNING,TRUE);
			m_AllActiveShots.RemoveActiveShotAt(i);			
		}
		else
		{
			// �ط�����
			pActiveShot->SendRequestShotService();		
			// cxm 2012.3.7
//			theApp.WriteLog(_T("CMainFrame::OnTimer"),_T("Operation Server No Answer, Request to Shot !!"),LOGTYPE_WARNING,TRUE);
		}
	}
	CBCGPFrameWnd::OnTimer(nIDEvent);
}
/**
 * @brief ������Դ
 * @note  ��ӦSetup�µ�Source�˵���������Դ���öԻ������ɾ����Դ��������Դ���ԡ�
 * @param  void
 * @return void
 */
void CMainFrame::OnSetupSource()
{
	// TODO: �ڴ���������������
	CDlgSourceType	dlg;
	dlg.DoModal();
}
/**
 * @brief ���÷��ڱ�
 * @note  �������ڱ����öԻ���
 * @param  void
 * @return void
 */
void CMainFrame::OnSetupOperation()
{
	// TODO: �ڴ���������������
	CDlgShotPoint dlg;
	dlg.DoModal();
}

void CMainFrame::OnSetupComments()
{
	CDlgCommentType  dlg;
	dlg.DoModal();
}

void CMainFrame::OnSetupDelaysteup()
{
	CDlgDelaySetup dlg;
	dlg.DoModal();
}

void CMainFrame::OnSetupProcesstype()
{
	CDlgProcessType  dlg;
	dlg.DoModal();
}
/**
 * @brief Disassociate VP,��ͣ��Դʹ��
 * @note  ����ϣ������ʹ��ĳһ��Դ������Ҫ�����������״̬������Ҫ�ֹ����������һ
 �� VP������Active Source�����Ҽ��˵���ѡ��Disassociate VP����ͣ����Դ��ʩ����
 �ڻ���ɨ���ģʽ����ǰ�������δ����Դ��ʣ�� VP �������ԡ�
 * @param  void
 * @return ������ͣ����Դ����ָ��
 */
CShotSource* CMainFrame::OnDisassociatevp(DWORD  dwShotSourceNb)
{	
	// ͨ����ԴNb�ҵ���Դ����
	CShotSource* pSource=m_AllShotSources.GetShotSourceByNb(dwShotSourceNb);
	if(!pSource)
		return NULL;
	// ͨ����Դ���ҵ����ڹ������
	int iIndex = m_AllActiveShots.FindFirstActiveShotBySource(pSource);
	CActiveShot* pActiveShot = m_AllActiveShots.GetActiveShot(iIndex);
	if(pActiveShot)
	{	
		// ֪ͨ������ֹͣ����
		pActiveShot->SendGeneralCMD(OPERATION_CMD_CANCEL);
		// ����ҵ�������ɾ���ö���
		m_AllActiveShots.RemoveActiveShotAt(iIndex);
	}
	// �ı���Դ��״̬����ʱ����Ҫˢ�£��ú�����Active Source��ͼ����ʱˢ��	
	SetShotSourceState(pSource,SHOTSOURCE_UNUSED);
	return pSource;
}
/**
 * @brief "Associate VP",Ϊ��Դ�����ڵ�
 * @note  ��һ����ָ��Ҫ��ͨ�������� Shot Number�����������Դ�� VP �ĶԻ�������������Ҽ�������ڱ���
���������ġ�Start Seismonitor with Vib Source������Ч��������ͬ��
 * @param  DWORD  dwShotSourceNb����Դ���
 * @return void
 */
CShotSource* CMainFrame::OnAssociatevp(DWORD  dwShotSourceNb)
{
	// ͨ����ԴNb�ҵ���Դ����
	CShotSource* pSource=m_AllShotSources.GetShotSourceByNb(dwShotSourceNb);
	if(!pSource)
		return NULL;
	// �����Ի���
	CDlgAssociateVP		DlgAssociateVP;
	if(DlgAssociateVP.DoModal()==IDCANCEL)
		return NULL;
	// �õ��ڵ�Nb
	DWORD	dwShotNb = DlgAssociateVP.m_dwShotNb;
	// �õ��ڵ����
	CShotPoint*		pShotPoint = m_AllShotPoints.GetShotPointByNb(dwShotNb);
	if(!pShotPoint)
	{	// û���ҵ��ڵ������ʾ�ڵ�Nb����
		CString strTemp;
		strTemp.Format(_T("Shot Nb#%d ,No source point found!"),dwShotNb);
		// cxm 2012.3.7
//		theApp.WriteLog(_T("CMainFrame::OnAssociatevp"),strTemp,LOGTYPE_ERROR,TRUE);
		return NULL;
	}
	// ��ʼ����
	OnStartShot(dwShotNb,dwShotSourceNb);
	return pSource;
}

CShotSource*  CMainFrame::OnAssociateSPLSPN(DWORD  dwShotSourceNb)
{
	// ͨ����ԴNb�ҵ���Դ����
	CShotSource* pSource=m_AllShotSources.GetShotSourceByNb(dwShotSourceNb);
	if(!pSource)
		return NULL;
	// �����Ի���
	CDlgAssociateSFLSFN		Dlg;
	if(Dlg.DoModal()==IDCANCEL)
		return NULL;
	// �õ��ڵ����
	CShotPoint*		pShotPoint = m_AllShotPoints.GetShotPointBySPLSPN(Dlg.m_fSourceLine,Dlg.m_fSourceNumber);
	if(!pShotPoint)
	{	// û���ҵ��ڵ������ʾ�ڵ�Nb����
		CString strTemp;
		strTemp.Format(_T("SPL %.1f,SPN %.1f,No source point found!"),Dlg.m_fSourceLine,Dlg.m_fSourceNumber);
		// cxm 2012.3.7
//		theApp.WriteLog(_T("CMainFrame::OnAssociateSPLSPN"),strTemp,LOGTYPE_ERROR,TRUE);
		return NULL;
	}
	// ��ʼ����
	OnStartShot(pShotPoint->m_dwShotNb,dwShotSourceNb);
	return pSource;
}