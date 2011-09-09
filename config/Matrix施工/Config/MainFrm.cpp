// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "Config.h"
#include "MainFrm.h"
#include "ConfigDoc.h"
#include "ConfigView.h"
#include "StatusView.h"
#include "DlgCrew.h"
#include "DlgUserInfo.h"
#include "DlgSEGDSetup.h"
#include "DlgDiskRecord.h"
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
	ON_WM_SIZE()
	ON_REGISTERED_MESSAGE(BCGM_RESETTOOLBAR, OnToolbarReset)
	ON_COMMAND(ID_SETUP_CREW, &CMainFrame::OnSetupCrew)
	ON_COMMAND(ID_SETUP_USERINFO, &CMainFrame::OnSetupUserinfo)
	ON_COMMAND(ID_SETUP_SEGD, &CMainFrame::OnSetupSegd)
	ON_COMMAND(ID_SETUP_DISKRECORD, &CMainFrame::OnSetupDiskrecord)
	ON_COMMAND(ID_LINE_ON, &CMainFrame::OnLineOn)
	ON_COMMAND(ID_LINE_OFF, &CMainFrame::OnLineOff)
	ON_REGISTERED_MESSAGE(WM_NEWLOG, OnNewLog)
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // status line indicator
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};


// CMainFrame construction/destruction

CMainFrame::CMainFrame()
{
	// TODO: add member initialization code here
	m_bSplitter = FALSE;
	m_bCompactMode = FALSE;
}

CMainFrame::~CMainFrame()
{
}


int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	CBCGPVisualManager2007::SetStyle (CBCGPVisualManager2007::VS2007_Silver);
	CBCGPVisualManager::SetDefaultManager (RUNTIME_CLASS (CBCGPVisualManager2007));

	if (!m_wndMenuBar.Create (this))
	{
		TRACE0("Failed to create menubar\n");
		return -1;      // fail to create
	}
	m_wndMenuBar.SetBarStyle(m_wndMenuBar.GetBarStyle() | CBRS_SIZE_DYNAMIC);

	CClientDC dc (this);
	BOOL bIsHighColor = dc.GetDeviceCaps (BITSPIXEL) > 8;
	UINT uiToolbarHotID = bIsHighColor ? IDB_MAINFRAME256 : IDR_MAINFRAME;
	if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP
		| CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC,CRect(1,1,1,1),IDR_MAINFRAME) ||
		!m_wndToolBar.LoadToolBar(IDR_MAINFRAME, 0, 0, TRUE, 0, 0, uiToolbarHotID))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}
	uiToolbarHotID = bIsHighColor ? IDB_ONOFFLINE256 : IDR_ONOFFLINE;
	if (!m_wndToolBarLine.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP
		| CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC,CRect(1,1,1,1),IDR_ONOFFLINE) ||
		!m_wndToolBarLine.LoadToolBar(IDR_ONOFFLINE, 0, 0, TRUE, 0, 0, uiToolbarHotID))
	{
		TRACE0("Failed to create toolbarline\n");
		return -1;      // fail to create
	}

	if (!m_wndStatusBar.Create(this) ||
		!m_wndStatusBar.SetIndicators(indicators,
		  sizeof(indicators)/sizeof(UINT)))
	{
		TRACE0("Failed to create status bar\n");
		return -1;      // fail to create
	}

	m_wndToolBar.SetWindowText(_T("Setup"));
	m_wndToolBar.SetWindowText(_T("On/Off Line"));
	// TODO: Delete these three lines if you don't want the toolbar to be dockable
	m_wndMenuBar.EnableDocking(CBRS_ALIGN_ANY);
	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	m_wndToolBarLine.EnableDocking(CBRS_ALIGN_ANY);
	
	EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndMenuBar);
	// DockControlBar(&m_wndToolBar);
	DockControlBar(&m_wndToolBarLine);
	DockControlBarLeftOf(&m_wndToolBar,&m_wndToolBarLine);
	// ���ó������ԣ�ȷ�����������һ��	
	SetProp(m_hWnd,g_strProgName,g_hProgValue);
	return 0;
}

BOOL CMainFrame::OnCreateClient(LPCREATESTRUCT lpcs,CCreateContext* pContext)
{		
	// �зִ���Ϊ����������ͼ
	CRect rectclient;
	GetClientRect(&rectclient);
	//////////////////////////////////////////////////////////////////////////
	if (!m_wndSplitter.CreateStatic(this,2,1))
	{
		AfxMessageBox(_T("CreateStatic failed!"));
		return FALSE ;
	}
	//////////////////////////////////////////////////////////////////////////
	if (!m_wndSplitter.CreateView(0,0,RUNTIME_CLASS(CConfigView), CSize(rectclient.Width(),rectclient.Height()/2), pContext))
	{
		AfxMessageBox(_T("CreateView CConfigView failed!"));
		return FALSE ;
	}
	//////////////////////////////////////////////////////////////////////////
	if (!m_wndSplitter.CreateView(1,0,RUNTIME_CLASS(CStatusView), CSize(rectclient.Width(),rectclient.Height()/2), pContext))
	{
		AfxMessageBox(_T("CreateView CStatusView failed!"));
		return FALSE ;
	}
	//////////////////////////////////////////////////////////////////////////
	// �����зֳɹ���־ΪTRUE
	m_bSplitter = TRUE ;
/**/


	//return CFrameWnd::OnCreateClient(lpcs, pContext);
	return TRUE;


}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return TRUE;
}


// CMainFrame diagnostics

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


// CMainFrame message handlers




void CMainFrame::OnSize(UINT nType, int cx, int cy)
{
	CBCGPFrameWnd::OnSize(nType, cx, cy);

	// TODO: �ڴ˴������Ϣ����������	
	if(m_bSplitter)
	{
		CRect r;
		GetClientRect(r);
		if(m_bCompactMode)
		{	// ����ģʽ�£�����ʾ������ͼ
			m_wndSplitter.SetColumnInfo(0,r.Width(),0);
			m_wndSplitter.SetRowInfo(0,r.Height(),0) ;     
			m_wndSplitter.RecalcLayout() ; 
		}
		else
		{	// ����ģʽ�£���ʾ������ͼ��״̬��ͼ
			m_wndSplitter.SetColumnInfo(0,r.Width(),0);
			m_wndSplitter.SetRowInfo(0,r.Height()/2,0) ;     
			m_wndSplitter.RecalcLayout() ; 
		}
	}
	
}
/**
 * @brief ��ӦBCGM_RESETTOOLBAR��Ϣ����������
 * @note  �ڿ�ܳ�������ʱ������Դ���д���������ʱ������ BCGM_RESETTOOLBAR��
 �ú����������Ϣ����ʼ��������������ť��
 * @param  WPARAM wp����������ԴID
 * @return LRESULT
 */
LRESULT CMainFrame::OnToolbarReset(WPARAM wp,LPARAM)
{

	UINT uiToolBarId = (UINT) wp;
	switch (uiToolBarId)
	{
	case IDR_MAINFRAME:
		{			
		}
		break;
	case IDR_ONOFFLINE:
		{	
			m_wndToolBarLine.SetToolBarBtnText(0, _T("On Line"), TRUE, TRUE);
			m_wndToolBarLine.SetToolBarBtnText(1, _T("Off Line"), TRUE, TRUE);
			m_wndToolBarLine.GetButton(2)->SetVisible(FALSE);
			m_wndToolBarLine.GetButton(3)->SetVisible(FALSE);
			m_wndToolBarLine.AdjustSizeImmediate();
		}
		break;
	}
	return 0;
}
/**
 * @brief ��ʾ����ģʽ
 * @note  �û��������ͼ����ʾ���淢���仯��
 ����ģʽ�£��˵�������������״̬����״̬��ͼ���أ�
 * @param  void
 * @return void
 */
void CMainFrame::ShowCompactMode()
{	
	CRect rectWindow;
	CRect rectClient;
	m_bCompactMode = !m_bCompactMode;
	if(m_bCompactMode)
	{
		// ���ز˵�������������״̬��
		ShowControlBar(&m_wndMenuBar ,FALSE ,FALSE,FALSE);		
		m_wndStatusBar.ShowWindow(SW_HIDE);
		ShowControlBar(&m_wndToolBar ,FALSE ,FALSE,FALSE);
		ShowControlBar(&m_wndToolBarLine ,FALSE ,FALSE,FALSE);
		// �����µĴ���λ�ã���ԭ������λ�û����ϣ����˼��ϲ˵������������ĸ߶ȣ��׶˼�ȥ״̬���ĸ߶ȣ��Դ���С����
		GetWindowRect( &rectWindow );
		m_wndMenuBar.GetWindowRect(&rectClient);
		rectWindow.top+=rectClient.Height();
		m_wndToolBar.GetWindowRect(&rectClient);
		rectWindow.top+=rectClient.Height();
		m_wndStatusBar.GetWindowRect(&rectClient);
		rectWindow.bottom-=rectClient.Height();
		SetWindowPos(&wndTop, rectWindow.left, rectWindow.top, rectWindow.Width(), rectWindow.Height(), SWP_SHOWWINDOW );
		// �޸Ĳ����ͼ�Ĵ�С
		if(m_bSplitter)
		{	
			GetClientRect( &rectClient );
			m_wndSplitter.SetRowInfo(0,rectClient.Height(),0) ;     
			m_wndSplitter.RecalcLayout();
		}
	}
	else
	{
		// ��ʾ�˵�������������״̬��
		ShowControlBar(&m_wndMenuBar,TRUE ,FALSE,TRUE);
		m_wndStatusBar.ShowWindow(SW_SHOW);
		ShowControlBar(&m_wndToolBar,TRUE ,FALSE,TRUE);
		ShowControlBar(&m_wndToolBarLine,TRUE ,FALSE,TRUE);
		// �����µĴ���λ�ã���ԭ������λ�û����ϣ����˼�ȥ�˵��������������׶˼���״̬���ĸ߶ȣ��Դ˷Ŵ󴰿�
		GetWindowRect( &rectWindow );
		m_wndMenuBar.GetWindowRect(&rectClient);
		rectWindow.top-=rectClient.Height();
		m_wndToolBar.GetWindowRect(&rectClient);
		rectWindow.top-=rectClient.Height();
		m_wndStatusBar.GetWindowRect(&rectClient);
		rectWindow.bottom+=rectClient.Height();
		SetWindowPos(&wndTop, rectWindow.left, rectWindow.top, rectWindow.Width(), rectWindow.Height(), SWP_SHOWWINDOW );
		// �޸Ĳ����ͼ��С
		if(m_bSplitter)
		{
			GetClientRect( & rectClient );			
			m_wndSplitter.SetRowInfo(0,rectClient.Height()/2,0) ;   			
			m_wndSplitter.RecalcLayout();
		}
	}
	
	// SetWindowPos(&wndTop, rectWindow.left, rectWindow.top, rectWindow.Width(), rectWindow.Height(), SWP_SHOWWINDOW );
}
LRESULT CMainFrame::OnNewLog(WPARAM wParam, LPARAM lParam)
{
	CLogBase   LogRecord;
	// ���ڴ��ж�ȡ��־
	if(!theApp.m_LogMapping.ReadRecord((int)lParam,&LogRecord))
	{
		return -1;
	}
	CString  strLog;
	// ������Ҫ��ʾ����־�ı��ַ���
	LogRecord.GetShowString(strLog);
	
	CStatusView *pView = (CStatusView*)m_wndSplitter.GetPane(1,0);
	// ��ʾ����ͼ��
	pView->AppendLog(strLog);
	
	return 0;
}
void CMainFrame::OnSetupCrew()
{
	// TODO: �ڴ���������������
	CDlgCrew	dlg;
	dlg.DoModal();
}

void CMainFrame::OnSetupUserinfo()
{
	// TODO: �ڴ���������������
	CDlgUserInfo    dlg;
	dlg.DoModal();
}

void CMainFrame::OnSetupSegd()
{
	// TODO: �ڴ���������������
	CDlgSEGDSetup   dlg;
	dlg.DoModal();
}

void CMainFrame::OnSetupDiskrecord()
{
	// TODO: �ڴ���������������
	CDlgDiskRecord  dlg;
	dlg.DoModal();
}
/**
 * @brief ����ON Line�¼�
 * @note  ��� ��On Line�����������ݲɼ��ͼ�¼
 * @param  void
 * @return void
 */
void CMainFrame::OnLineOn()
{
	CBCGPToolbarButton* pBtn=NULL;
	pBtn = m_wndToolBarLine.GetButton(0);
	pBtn->SetImage(CImageHash::GetImageOfCommand(ID_LINE_ONBACK,FALSE));
	pBtn = m_wndToolBarLine.GetButton(1);
	pBtn->SetImage(CImageHash::GetImageOfCommand(ID_LINE_OFFBACK,FALSE));
	m_wndToolBarLine.InvalidateButton(0);
	m_wndToolBarLine.InvalidateButton(1);

}
/**
 * @brief ����Off Line�¼�
 * @note  �����Off Line����ֹͣ���ݲɼ��ͼ�¼������ͼ���û�����
 �����ñ��ع��ܣ�ϵͳ�����ڸ������ڵ� ��Setup�� �˵��жԲ������ý����κθ��ġ�
 * @param  void
 * @return void
 */
void CMainFrame::OnLineOff()
{
	CBCGPToolbarButton* pBtn=NULL;
	pBtn = m_wndToolBarLine.GetButton(0);
	pBtn->SetImage(CImageHash::GetImageOfCommand(ID_LINE_OFFBACK,FALSE));
	pBtn = m_wndToolBarLine.GetButton(1);
	pBtn->SetImage(CImageHash::GetImageOfCommand(ID_LINE_ONBACK,FALSE));
	m_wndToolBarLine.InvalidateButton(0);
	m_wndToolBarLine.InvalidateButton(1);

}