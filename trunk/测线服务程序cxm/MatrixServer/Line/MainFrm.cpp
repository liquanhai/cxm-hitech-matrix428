
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
//	char pParameter[256];
// 	CString str = _T("");
// 	pParameter[0] = '0';
// 	pParameter[1] = '3';
// 	pParameter[2] = '2';
// 	pParameter[3] = '7';
// 	str = CString(pParameter);
//	memcpy(pParameter, "0327", 4);
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
// ��ѯ SurveyXML �ļ���Ϣ
// void QuerySurverySetupData(char* cProcBuf, int& iPos, m_oLineSetupDataStruct* pLineSetupData)
// {
// 	list<m_oSurveryStruct>::iterator iter;
// 	EnterCriticalSection(&pLineSetupData->m_oSecCommInfo);
// 	for (iter = pLineSetupData->m_olsSurveryStruct.begin();
// 		iter != pLineSetupData->m_olsSurveryStruct.end(); iter++)
// 	{
// 		memcpy(&cProcBuf[iPos], &iter->m_uiLine, 4);
// 		iPos += 4;
// 		memcpy(&cProcBuf[iPos], &iter->m_usReceiverSectionSize, 2);
// 		iPos += 2;
// 		memcpy(&cProcBuf[iPos], iter->m_pcReceiverSection, iter->m_usReceiverSectionSize);
// 		iPos += iter->m_usReceiverSectionSize;
// 	}
// 	LeaveCriticalSection(&pLineSetupData->m_oSecCommInfo);
// }
LRESULT CMainFrame::OnMsgClient(WPARAM wParam, LPARAM lParam)
{
	CString str = _T("");
// 	int iPos = 0;
// 	char cp[20000];
	switch(wParam)
	{
	case CmdClientConnect:
		m_wndOutput.m_wndOutputBuild.AddString(_T("Connect to Server!"));
		// ��ѯ��������֡����Ϊ������4���ֽڣ�+������4���ֽڣ���
		m_oComDll.m_pCommClient->m_oSndFrame.MakeSetFrame(CmdQueryRevSection, NULL, 0);
		// ��ѯ SurveyXML �ļ���Ϣ
		m_oComDll.m_pCommClient->m_oSndFrame.MakeSetFrame(CmdQuerySurveyXMLInfo, NULL, 0);
		// ��ѯ PointCode �ļ���Ϣ
		m_oComDll.m_pCommClient->m_oSndFrame.MakeSetFrame(CmdQueryPointCodeXMLInfo, NULL, 0);
		// ��ѯ Sensor XML�ļ���Ϣ
		m_oComDll.m_pCommClient->m_oSndFrame.MakeSetFrame(CmdQuerySensorXMLInfo, NULL, 0);
		// ��ѯ Marker XML�ļ���Ϣ
		m_oComDll.m_pCommClient->m_oSndFrame.MakeSetFrame(CmdQueryMarkerXMLInfo, NULL, 0);
		// ��ѯ Aux XML�ļ���Ϣ
		m_oComDll.m_pCommClient->m_oSndFrame.MakeSetFrame(CmdQueryAuxXMLInfo, NULL, 0);
		// ��ѯ Detour XML�ļ���Ϣ
		m_oComDll.m_pCommClient->m_oSndFrame.MakeSetFrame(CmdQueryDetourXMLInfo, NULL, 0);
		// ��ѯ Mute XML�ļ���Ϣ
		m_oComDll.m_pCommClient->m_oSndFrame.MakeSetFrame(CmdQueryMuteXMLInfo, NULL, 0);
		// ��ѯ BlastMachine XML�ļ���Ϣ
		m_oComDll.m_pCommClient->m_oSndFrame.MakeSetFrame(CmdQueryBlastMachineXMLInfo, NULL, 0);
		// ��ѯ Absolute XML�ļ���Ϣ
		m_oComDll.m_pCommClient->m_oSndFrame.MakeSetFrame(CmdQueryAbsoluteXMLInfo, NULL, 0);
		// ��ѯ Generic XML�ļ���Ϣ
		m_oComDll.m_pCommClient->m_oSndFrame.MakeSetFrame(CmdQueryGenericXMLInfo, NULL, 0);
		// ��ѯ Look XML�ļ���Ϣ
		m_oComDll.m_pCommClient->m_oSndFrame.MakeSetFrame(CmdQueryLookXMLInfo, NULL, 0);
		// ��ѯ InstrumentTestBase XML�ļ���Ϣ
		m_oComDll.m_pCommClient->m_oSndFrame.MakeSetFrame(CmdQueryInstrumentTestBaseXMLInfo, NULL, 0);
		// ��ѯ SensorTestBase XML�ļ���Ϣ
		m_oComDll.m_pCommClient->m_oSndFrame.MakeSetFrame(CmdQuerySensorTestBaseXMLInfo, NULL, 0);
		// ��ѯ InstrumentTestLimit XML�ļ���Ϣ
		m_oComDll.m_pCommClient->m_oSndFrame.MakeSetFrame(CmdQueryInstrumentTestLimitXMLInfo, NULL, 0);
		// ��ѯ SensorTestLimit XML�ļ���Ϣ
		m_oComDll.m_pCommClient->m_oSndFrame.MakeSetFrame(CmdQuerySensorTestLimitXMLInfo, NULL, 0);
		// ��ѯ InstrumentTest XML�ļ���Ϣ
		m_oComDll.m_pCommClient->m_oSndFrame.MakeSetFrame(CmdQueryInstrumentTestXMLInfo, NULL, 0);
		// ��ѯ SensorTest XML�ļ���Ϣ
		m_oComDll.m_pCommClient->m_oSndFrame.MakeSetFrame(CmdQuerySensorTestXMLInfo, NULL, 0);
		// ��ѯ MultipleTest XML�ļ���Ϣ
		m_oComDll.m_pCommClient->m_oSndFrame.MakeSetFrame(CmdQueryMultipleTestXMLInfo, NULL, 0);
		// ��ѯ SeisMonitorTest XML�ļ���Ϣ
		m_oComDll.m_pCommClient->m_oSndFrame.MakeSetFrame(CmdQuerySeisMonitorTestXMLInfo, NULL, 0);
		// ��ѯ LAULeakage XML�ļ���Ϣ
		m_oComDll.m_pCommClient->m_oSndFrame.MakeSetFrame(CmdQueryLAULeakageXMLInfo, NULL, 0);
		// ��ѯ FormLine XML�ļ���Ϣ
		m_oComDll.m_pCommClient->m_oSndFrame.MakeSetFrame(CmdQueryFormLineXMLInfo, NULL, 0);
		break;
		// ��ѯ��������
	case CmdQueryRevSection:
		m_wndOutput.m_wndOutputBuild.AddString(_T("Receive the size of receive section!"));
		break;
	case CmdSetFieldOn:
		// �ϵ�
		m_wndOutput.m_wndOutputBuild.AddString(_T("Receive the command of Field On return!"));
		break;
	case CmdSetFieldOff:
		// �ϵ�
		m_wndOutput.m_wndOutputBuild.AddString(_T("Receive the command of Field On return!"));
		break;
		// Field On��Ҫ�ȴ���ʱ�䣨֡����Ϊִ��FieldOnʣ��ʱ�䣬Ϊ0��ʾ����ȴ���
	case CmdFieldOnWaitTime:
		str.Format(_T("Field on needs to wait about %ds!"), lParam);
		m_wndOutput.m_wndOutputBuild.AddString(str);
		if (lParam != 0)
		{
			AfxMessageBox(str);
		}
		break;
		// ���� SurveyXML �ļ���Ϣ��֡����Ϊ��Ϣ�ṹ�壩
	case CmdSetSurveyXMLInfo:
		m_wndOutput.m_wndOutputBuild.AddString(_T("Receive the informations of survey setup!"));
		break;
		// ���� PointCode XML�ļ���Ϣ��֡����Ϊ��Ϣ�ṹ�壩
	case CmdSetPointCodeXMLInfo:
		m_wndOutput.m_wndOutputBuild.AddString(_T("Receive the informations of point code setup!"));
		break;
		// ���� Sensor XML�ļ���Ϣ��֡����Ϊ��Ϣ�ṹ�壩
	case CmdSetSensorXMLInfo:
		m_wndOutput.m_wndOutputBuild.AddString(_T("Receive the informations of sensor setup!"));
		break;
		// ���� Marker XML�ļ���Ϣ��֡����Ϊ��Ϣ�ṹ�壩
	case CmdSetMarkerXMLInfo:
		m_wndOutput.m_wndOutputBuild.AddString(_T("Receive the informations of marker setup!"));
		break;
		// ���� Aux XML�ļ���Ϣ��֡����Ϊ��Ϣ�ṹ�壩
	case CmdSetAuxXMLInfo:
		m_wndOutput.m_wndOutputBuild.AddString(_T("Receive the informations of aux setup!"));
		break;
		// ���� Detour XML�ļ���Ϣ��֡����Ϊ��Ϣ�ṹ�壩
	case CmdSetDetourXMLInfo:
		m_wndOutput.m_wndOutputBuild.AddString(_T("Receive the informations of detour setup!"));
		break;
		// ���� Mute XML�ļ���Ϣ��֡����Ϊ��Ϣ�ṹ�壩
	case CmdSetMuteXMLInfo:
		m_wndOutput.m_wndOutputBuild.AddString(_T("Receive the informations of mute setup!"));
		break;
		// ���� BlastMachine XML�ļ���Ϣ��֡����Ϊ��Ϣ�ṹ�壩
	case CmdSetBlastMachineXMLInfo:
		m_wndOutput.m_wndOutputBuild.AddString(_T("Receive the informations of blastmachine setup!"));
		break;
		// ���� Absolute XML�ļ���Ϣ��֡����Ϊ��Ϣ�ṹ�壩
	case CmdSetAbsoluteXMLInfo:
		m_wndOutput.m_wndOutputBuild.AddString(_T("Receive the informations of absolute setup!"));
		break;
		// ���� Generic XML�ļ���Ϣ��֡����Ϊ��Ϣ�ṹ�壩
	case CmdSetGenericXMLInfo:
		m_wndOutput.m_wndOutputBuild.AddString(_T("Receive the informations of generic setup!"));
		break;
		// ���� Look XML�ļ���Ϣ��֡����Ϊ��Ϣ�ṹ�壩
	case CmdSetLookXMLInfo:
		m_wndOutput.m_wndOutputBuild.AddString(_T("Receive the informations of look setup!"));
		break;
		// ���� InstrumentTestBase XML�ļ���Ϣ��֡����Ϊ��Ϣ�ṹ�壩
	case CmdSetInstrumentTestBaseXMLInfo:
		m_wndOutput.m_wndOutputBuild.AddString(_T("Receive the informations of instrument test base setup!"));
		break;
		// ���� SensorTestBase XML�ļ���Ϣ��֡����Ϊ��Ϣ�ṹ�壩
	case CmdSetSensorTestBaseXMLInfo:
		m_wndOutput.m_wndOutputBuild.AddString(_T("Receive the informations of sensor test base setup!"));
		break;
		// ���� InstrumentTestLimit XML�ļ���Ϣ��֡����Ϊ��Ϣ�ṹ�壩
	case CmdSetInstrumentTestLimitXMLInfo:
		m_wndOutput.m_wndOutputBuild.AddString(_T("Receive the informations of instrument test limit setup!"));
		break;
	case CmdSetSensorTestLimitXMLInfo:
		// ���� SensorTestLimit XML�ļ���Ϣ��֡����Ϊ��Ϣ�ṹ�壩
		m_wndOutput.m_wndOutputBuild.AddString(_T("Receive the informations of sensor test limit setup!"));
		break;
		// ���� InstrumentTest XML�ļ���Ϣ��֡����Ϊ��Ϣ�ṹ�壩
	case CmdSetInstrumentTestXMLInfo:
		m_wndOutput.m_wndOutputBuild.AddString(_T("Receive the informations of instrument test setup!"));
		break;
		// ���� SensorTest XML�ļ���Ϣ��֡����Ϊ��Ϣ�ṹ�壩
	case CmdSetSensorTestXMLInfo:
		m_wndOutput.m_wndOutputBuild.AddString(_T("Receive the informations of sensor test setup!"));
		break;
		// ���� MultipleTest XML�ļ���Ϣ��֡����Ϊ��Ϣ�ṹ�壩
	case CmdSetMultipleTestXMLInfo:
		m_wndOutput.m_wndOutputBuild.AddString(_T("Receive the informations of multiple test setup!"));
		break;
		// ���� SeisMonitorTest XML�ļ���Ϣ��֡����Ϊ��Ϣ�ṹ�壩
	case CmdSetSeisMonitorTestXMLInfo:
		m_wndOutput.m_wndOutputBuild.AddString(_T("Receive the informations of seismonitor setup!"));
		break;
		// ���� LAULeakage XML�ļ���Ϣ��֡����Ϊ��Ϣ�ṹ�壩
	case CmdSetLAULeakageXMLInfo:
		m_wndOutput.m_wndOutputBuild.AddString(_T("Receive the informations of lauleakage setup!"));
		break;
		// ���� FormLine XML�ļ���Ϣ��֡����Ϊ��Ϣ�ṹ�壩
	case CmdSetFormLineXMLInfo:
		m_wndOutput.m_wndOutputBuild.AddString(_T("Receive the informations of form line setup!"));
		// ����д���ݵ������������ļ�
// 		m_oComDll.m_oXMLDllLine.m_pLineSetupData->m_olsSurveryStruct.begin()->m_pcReceiverSection[0] = '2';
// 		m_oComDll.m_oXMLDllLine.m_pLineSetupData->m_olsSurveryStruct.begin()->m_pcReceiverSection[1] = '-';
// 		m_oComDll.m_oXMLDllLine.m_pLineSetupData->m_olsSurveryStruct.begin()->m_pcReceiverSection[2] = '1';
// 		m_oComDll.m_oXMLDllLine.m_pLineSetupData->m_olsSurveryStruct.begin()->m_pcReceiverSection[3] = '2';
// 		m_oComDll.m_oXMLDllLine.m_pLineSetupData->m_olsSurveryStruct.begin()->m_pcReceiverSection[4] = '5';
// 		m_oComDll.m_oXMLDllLine.m_pLineSetupData->m_olsSurveryStruct.begin()->m_pcReceiverSection[5] = 'p';
// 		m_oComDll.m_oXMLDllLine.m_pLineSetupData->m_olsSurveryStruct.begin()->m_pcReceiverSection[6] = '2';
// 		QuerySurverySetupData(cp, iPos, m_oComDll.m_oXMLDllLine.m_pLineSetupData);
// 		m_oComDll.m_pCommClient->m_oSndFrame.MakeSetFrame(CmdSetSurveyXMLInfo, cp, iPos);
		break;
	default:
		break;
	}

	return TRUE;
}