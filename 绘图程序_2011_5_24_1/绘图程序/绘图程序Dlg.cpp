// ��ͼ����Dlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "��ͼ����.h"
#include "��ͼ����Dlg.h"
#include "HotSpotDlg.h"
#include <math.h>
#include <algorithm>
#include <fstream>
#include  <io.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// ��ʾ�ɸı��С��ͼ��ID
#ifndef OBM_SIZE
#define OBM_SIZE 32766
#endif
// �ɼ�վADC���ݴ洢
vector<double>* m_dbFduData;
// �ɼ�վADC���ݻ�ͼ
vector<double>* m_dbFduShow;

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


// C��ͼ����Dlg �Ի���




C��ͼ����Dlg::C��ͼ����Dlg(CWnd* pParent /*=NULL*/)
	: CDialog(C��ͼ����Dlg::IDD, pParent)
	, m_currentDuration(0)
	, m_dateRange(0)
	, m_minDuration(0)
	, m_iClientWidth(0)
	, m_iClientHeight(0)
	, m_iMinWidth(0)
	, m_iMinHeight(0)
	, m_pControlArray(NULL)
	, m_iControlNumber(0)
	, m_bShowSizeIcon(TRUE)
	, m_uiADCStartNum(0)
	, m_uiADCDataCovNb(0)
	, m_uiADCDataNum(0)
	, m_uiADCDataFduNum(0)
	, m_viewPortDataSeries(NULL)
	, m_uiADCFileLineNum(0)
	, m_uiInstrumentADCNum(0)
	, m_bCheckYAxisFixed(FALSE)
	, m_bStartShow(FALSE)
	, m_uiStartDrawPointsNum(0)
	, m_uiOpenFileNb(0)
	, m_bLoadFile(FALSE)
	, m_uiInstrumentNb(NULL)
	, m_uiEndDrawPointsNumMax(0)
	, m_uiFindLineCount(0)
	, m_uiADCLineBufNum(0)
	, m_pLinebufRead(NULL)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}
C��ͼ����Dlg::~C��ͼ����Dlg()
{
	delete m_ChartViewer.getChart();
	// ��¼X���������Ϣ
	m_DrawPoint_X.clear();
	// ��¼����ͼ�ߵ����Ϣ
	m_DrawLine_Y.clear();
	m_FileInfo.clear();
	m_ADCDataInfo.clear();
	if (m_dbFduData != NULL)
	{
		for (unsigned int i=0; i<m_uiInstrumentADCNum; i++)
		{
			m_dbFduData[i].clear();
		}
		delete[] m_dbFduData;
	}
	if (m_dbFduShow != NULL)
	{
		for (unsigned int i=0; i<m_uiInstrumentADCNum; i++)
		{
			m_dbFduShow[i].clear();
		}
		delete[] m_dbFduShow;
	}
	if (m_uiInstrumentNb != NULL)
	{
		delete[] m_uiInstrumentNb;
	}
	if (m_pLinebufRead != NULL)
	{
		delete[] m_pLinebufRead;
	}
}
void C��ͼ����Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_ChartViewer, m_ChartViewer);
	DDX_Control(pDX, IDC_PointerPB, m_PointerPB);
	DDX_Control(pDX, IDC_XZoomPB, m_XZoomPB);
	DDX_Control(pDX, IDC_HScrollBar, m_HScrollBar);
	DDX_Control(pDX, IDC_VScrollBar, m_VScrollBar);
	DDX_Control(pDX, IDC_Duration, m_Duration);
}

BEGIN_MESSAGE_MAP(C��ͼ����Dlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_PointerPB, &C��ͼ����Dlg::OnBnClickedPointerpb)
	ON_BN_CLICKED(IDC_ZoomInPB, &C��ͼ����Dlg::OnBnClickedZoominpb)
	ON_BN_CLICKED(IDC_ZoomOutPB, &C��ͼ����Dlg::OnBnClickedZoomoutpb)
	ON_BN_CLICKED(IDC_XZoomPB, &C��ͼ����Dlg::OnBnClickedXzoompb)
	ON_BN_CLICKED(IDC_XYZoomPB, &C��ͼ����Dlg::OnBnClickedXyzoompb)
	ON_BN_CLICKED(IDC_ChartViewer, &C��ͼ����Dlg::OnBnClickedChartViewer)
	ON_CONTROL(CVN_ViewPortChanged, IDC_ChartViewer, &C��ͼ����Dlg::OnViewPortChanged)
	ON_WM_HSCROLL()
	ON_WM_VSCROLL()
	ON_CBN_SELCHANGE(IDC_Duration, &C��ͼ����Dlg::OnCbnSelchangeDuration)
	ON_CBN_KILLFOCUS(IDC_Duration, &C��ͼ����Dlg::OnCbnKillfocusDuration)
	ON_WM_SIZE()
	ON_WM_SIZING()
	ON_BN_CLICKED(IDC_BUTTON_SAVECHART, &C��ͼ����Dlg::OnBnClickedButtonSavechart)
	ON_BN_CLICKED(IDC_BUTTON_OPENADCFILE, &C��ͼ����Dlg::OnBnClickedButtonOpenadcfile)
	ON_BN_CLICKED(IDC_YZoomPB, &C��ͼ����Dlg::OnBnClickedYzoompb)
	ON_BN_CLICKED(IDC_BUTTON_REDRAW, &C��ͼ����Dlg::OnBnClickedButtonRedraw)
	ON_WM_CLOSE()
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BUTTON_START, &C��ͼ����Dlg::OnBnClickedButtonStart)
	ON_BN_CLICKED(IDC_BUTTON_STOP, &C��ͼ����Dlg::OnBnClickedButtonStop)
	ON_BN_CLICKED(IDC_CHECK_YAXISFIXED, &C��ͼ����Dlg::OnBnClickedCheckYaxisfixed)
	ON_BN_CLICKED(IDC_BUTTON_OPENADCFOLDER, &C��ͼ����Dlg::OnBnClickedButtonOpenadcfolder)
	ON_LBN_DBLCLK(IDC_LIST_FILE, &C��ͼ����Dlg::OnLbnDblclkListFile)
END_MESSAGE_MAP()


// C��ͼ����Dlg ��Ϣ�������

BOOL C��ͼ����Dlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	// ����License
	setLicenseCode("R5MNGUVV3UXWFT2CC44B1D7E"); 

	// ����ͼ�굽����÷���ť
	loadButtonIcon(IDC_PointerPB, IDI_PointerPB, 100, 20);  
	loadButtonIcon(IDC_ZoomInPB, IDI_ZoomInPB, 100, 20);    
	loadButtonIcon(IDC_ZoomOutPB, IDI_ZoomOutPB, 100, 20);

	// ����ͼ�굽�佹/����λ�ÿ��ư�ť
	loadButtonIcon(IDC_XZoomPB, IDI_YZoomPB, 105, 20);
	loadButtonIcon(IDC_YZoomPB, IDI_XZoomPB, 105, 20);
	loadButtonIcon(IDC_XYZoomPB, IDI_XYZoomPB, 105, 20);

	// ���Ի�����ؼ���Ϊ�ߴ�ɱ��
	OnSiteSizeBox();

	// ��ʼ�������Ϊ�����϶�������ģʽ
	m_PointerPB.SetCheck(1);
	m_XZoomPB.SetCheck(1);
	m_ChartViewer.setMouseUsage(Chart::MouseUsageScroll);
	m_ChartViewer.setZoomDirection(Chart::DirectionVertical); 
	m_ChartViewer.setScrollDirection(Chart::DirectionVertical);

	GetDlgItem(IDC_EDIT_LINEINTERVAL)->SetWindowText(_T("0.001"));
	GetDlgItem(IDC_EDIT_LINEZOOM)->SetWindowText(_T("1"));
	GetDlgItem(IDC_EDIT_SAMPLINGRATE)->SetWindowText(_T("1"));
	// �ɼ�վADC���ݴ洢
	m_dbFduData = NULL;
	// �ɼ�վADC���ݻ�ͼ
	m_dbFduShow = NULL;

	// ����Socket
	OnCreateADCRecSocket();

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void C��ͼ����Dlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void C��ͼ����Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR C��ͼ����Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}
// ���Ի�����ؼ���Ϊ�ߴ�ɱ��
void C��ͼ����Dlg::OnSiteSizeBox(void)
{
	// ���öԻ���Ϊ�ɱ��С��
	ModifyStyle(0, WS_SIZEBOX);

	// �ԶԻ���ĳ�ʼ��С��Ϊ�Ի���Ŀ�Ⱥ͸߶ȵ���Сֵ
	CRect rectDlg;
	GetWindowRect(rectDlg);
	m_iMinWidth = rectDlg.Width();
	m_iMinHeight = rectDlg.Height();

	// �õ��Ի���client����Ĵ�С 
	CRect rectClient;
	GetClientRect(rectClient);
	m_iClientWidth = rectClient.Width();
	m_iClientHeight = rectClient.Height();

	// Loadͼ��
	m_bmpSizeIcon.LoadOEMBitmap(OBM_SIZE);
	m_bmpSizeIcon.GetBitmap(&m_bitmap);

	// ������ʾͼ��ľ�̬�ؼ������ڶԻ������½�
	m_wndSizeIcon.Create(NULL, WS_CHILD | WS_VISIBLE | SS_BITMAP, CRect(0, 0, m_bitmap.bmWidth, m_bitmap.bmHeight), this, 0);
	m_wndSizeIcon.SetBitmap(m_bmpSizeIcon);
	m_wndSizeIcon.MoveWindow(m_iClientWidth - m_bitmap.bmWidth, m_iClientHeight - m_bitmap.bmHeight, m_bitmap.bmWidth, m_bitmap.bmHeight);

	// ��ʾͼ��
	m_wndSizeIcon.ShowWindow(m_bShowSizeIcon);
	static DLGCTLINFO dcMenuGroup[] = 
	{
		{IDC_STATIC_CONTROL, ELASTICY,	100},
		{IDC_STATIC_CONTROL, ELASTICX,	5},
		{IDC_STATIC_MOUSEMODE, ELASTICY, 16},
		{IDC_STATIC_MOUSEMODE, ELASTICX, 5},
		{IDC_PointerPB, MOVEY, 2},
		{IDC_PointerPB, ELASTICY, 5},
		{IDC_PointerPB, ELASTICX, 2},
		{IDC_ZoomInPB, MOVEX, 3},
		{IDC_ZoomInPB, MOVEY, 2},
		{IDC_ZoomInPB, ELASTICY, 5},
		{IDC_ZoomInPB, ELASTICX, 2},
		{IDC_ZoomOutPB, MOVEY, 9},
		{IDC_ZoomOutPB, ELASTICY, 5},
		{IDC_ZoomOutPB, ELASTICX, 2},
		{IDC_STATIC_ZOOMMODE, MOVEY, 18},
		{IDC_STATIC_ZOOMMODE, ELASTICY, 16},
		{IDC_STATIC_ZOOMMODE, ELASTICX, 5},
		{IDC_XZoomPB, MOVEY, 20},
		{IDC_XZoomPB, ELASTICY, 5},
		{IDC_XZoomPB, ELASTICX, 2},
		{IDC_YZoomPB, MOVEX, 3},
		{IDC_YZoomPB, MOVEY, 20},
		{IDC_YZoomPB, ELASTICY, 5},
		{IDC_YZoomPB, ELASTICX, 2},
		{IDC_XYZoomPB, MOVEY, 27},
		{IDC_XYZoomPB, ELASTICY, 5},
		{IDC_XYZoomPB, ELASTICX, 2},
		{IDC_STATIC_GRAPHSHOWNUM, MOVEY, 35},
		{IDC_Duration, MOVEY, 35},
		{IDC_Duration, ELASTICX, 5},
		{IDC_BUTTON_OPENADCFILE, MOVEY, 37},
		{IDC_BUTTON_OPENADCFILE, ELASTICY, 5},
		{IDC_BUTTON_OPENADCFILE, ELASTICX, 5},
		{IDC_BUTTON_OPENADCFOLDER, MOVEY, 43},
		{IDC_BUTTON_OPENADCFOLDER, ELASTICY, 5},
		{IDC_BUTTON_OPENADCFOLDER, ELASTICX, 5},
		{IDC_STATIC_FILELIST, MOVEY, 48},
		{IDC_LIST_FILE, MOVEY, 48},
		{IDC_LIST_FILE, ELASTICX, 5},
		{IDC_LIST_FILE, ELASTICY, 5},
		{IDC_STATIC_SAMPLINGRATE, MOVEY, 48},
		{IDC_EDIT_SAMPLINGRATE, MOVEY, 48},
		{IDC_CHECK_YAXISFIXED, MOVEY, 48},
		{IDC_CHECK_YAXISFIXED, ELASTICY, 5},
		{IDC_STATIC_LINEINTERVAL, MOVEY, 53},
		{IDC_STATIC_LINEINTERVAL, ELASTICX, 2},
		{IDC_EDIT_LINEINTERVAL, MOVEY, 53},
		{IDC_EDIT_LINEINTERVAL, ELASTICX, 2},
		{IDC_STATIC_LINEZOOM, MOVEY, 53},
		{IDC_STATIC_LINEZOOM, MOVEX, 3},
		{IDC_STATIC_LINEZOOM, ELASTICX, 2},
		{IDC_EDIT_LINEZOOM, MOVEY, 53},
		{IDC_EDIT_LINEZOOM, MOVEX, 3},
		{IDC_EDIT_LINEZOOM, ELASTICX, 2},
		{IDC_BUTTON_REDRAW, MOVEY, 58},
		{IDC_BUTTON_REDRAW, ELASTICY, 5},
		{IDC_BUTTON_REDRAW, ELASTICX, 2},
		{IDC_BUTTON_SAVECHART, MOVEY, 63},
		{IDC_BUTTON_SAVECHART, ELASTICY, 5},
		{IDC_BUTTON_SAVECHART, ELASTICX, 2},
		{IDC_BUTTON_START, MOVEY, 58},
		{IDC_BUTTON_START, MOVEX, 3},
		{IDC_BUTTON_START, ELASTICY, 5},
		{IDC_BUTTON_START, ELASTICX, 2},
		{IDC_BUTTON_STOP, MOVEY, 63},
		{IDC_BUTTON_STOP, MOVEX, 3},
		{IDC_BUTTON_STOP, ELASTICY, 5},
		{IDC_BUTTON_STOP, ELASTICX, 2},
		{IDC_HScrollBar, MOVEX, 5},
		{IDC_HScrollBar, MOVEY, 100},
		{IDC_HScrollBar, ELASTICX, 95},
		{IDC_VScrollBar, MOVEX, 100},
		{IDC_VScrollBar, MOVEY, 5},
		{IDC_VScrollBar, ELASTICY, 95},
	};
	// ���ÿؼ���Ϣ
	SetControlProperty(dcMenuGroup, sizeof(dcMenuGroup)/sizeof(DLGCTLINFO));
}
// ����һ��ͼ����Դ����ť
void C��ͼ����Dlg::loadButtonIcon(int buttonId, int iconId, int width, int height)
{
	GetDlgItem(buttonId)->SendMessage(BM_SETIMAGE, IMAGE_ICON, (LPARAM)::LoadImage(
		AfxGetResourceHandle(), MAKEINTRESOURCE(iconId), IMAGE_ICON, width, height, 
		LR_DEFAULTCOLOR));  
}

// �õ�Ĭ�ϵı�����ɫ
int C��ͼ����Dlg::getDefaultBgColor(void)
{
	LOGBRUSH LogBrush; 
	HBRUSH hBrush = (HBRUSH)SendMessage(WM_CTLCOLORDLG, (WPARAM)CClientDC(this).m_hDC, 
		(LPARAM)m_hWnd); 
	::GetObject(hBrush, sizeof(LOGBRUSH), &LogBrush); 
	int ret = LogBrush.lbColor;
	return ((ret & 0xff) << 16) | (ret & 0xff00) | ((ret & 0xff0000) >> 16);
}
void C��ͼ����Dlg::OnBnClickedPointerpb()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	 m_ChartViewer.setMouseUsage(Chart::MouseUsageScroll);
}

void C��ͼ����Dlg::OnBnClickedZoominpb()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_ChartViewer.setMouseUsage(Chart::MouseUsageZoomIn);
}

void C��ͼ����Dlg::OnBnClickedZoomoutpb()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_ChartViewer.setMouseUsage(Chart::MouseUsageZoomOut);
}

void C��ͼ����Dlg::OnBnClickedXzoompb()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_ChartViewer.setZoomDirection(Chart::DirectionVertical); 
	m_ChartViewer.setScrollDirection(Chart::DirectionVertical);

	// Viewport is always unzoomed as x-axis is auto-scaled
// 	m_ChartViewer.setViewPortLeft(0);
// 	m_ChartViewer.setViewPortWidth(1);
	if (m_dbFduData == NULL)
	{
		return;
	}
	// Update chart to auto-scale axis
	m_ChartViewer.updateViewPort(true, true);
}

void C��ͼ����Dlg::OnBnClickedXyzoompb()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_ChartViewer.setZoomDirection(Chart::DirectionHorizontalVertical); 
	m_ChartViewer.setScrollDirection(Chart::DirectionHorizontalVertical);  
}

void C��ͼ����Dlg::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	if (nSBCode != SB_ENDSCROLL)
	{
		// User is still scrolling

		// Set the view port based on the scroll bar
		m_ChartViewer.setViewPortLeft(moveScrollBar(nSBCode, nPos, pScrollBar));
		// Update the chart image only, but no need to update the image map.
		m_ChartViewer.updateViewPort(true, false);
	}
	else
		// Scroll bar has stoped moving. Can update image map now.
		m_ChartViewer.updateViewPort(false, true);
}

void C��ͼ����Dlg::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	if (nSBCode != SB_ENDSCROLL)
	{
		// User is still scrolling

		// Set the view port based on the scroll bar
		m_ChartViewer.setViewPortTop(moveScrollBar(nSBCode, nPos, pScrollBar));
		// Update the chart image only, but no need to update the image map.
		m_ChartViewer.updateViewPort(true, false);
	}
	else
		// Scroll bar has stoped moving. Can update image map now.
		m_ChartViewer.updateViewPort(false, true);
}
//
// CChartViewer ViewPortChanged event
//
void C��ͼ����Dlg::OnViewPortChanged()
{
	//
	// Set up the scroll bars to reflect the current position and size of the view port
	//
	SCROLLINFO info;
	info.cbSize = sizeof(SCROLLINFO);
	info.fMask = SIF_ALL;
	info.nMin = 0;
	info.nMax = 0x1fffffff;

	m_HScrollBar.EnableWindow(m_ChartViewer.getViewPortWidth() < 1);
	if (m_ChartViewer.getViewPortWidth() < 1)
	{
		info.nPage = (int)ceil(m_ChartViewer.getViewPortWidth() * (info.nMax - info.nMin));
		info.nPos = (int)(0.5 + m_ChartViewer.getViewPortLeft() * (info.nMax - info.nMin))
			+ info.nMin;
		m_HScrollBar.SetScrollInfo(&info);
	}

	m_VScrollBar.EnableWindow(m_ChartViewer.getViewPortHeight() < 1);
	if (m_ChartViewer.getViewPortHeight() < 1)
	{
		info.nPage = (int)ceil(m_ChartViewer.getViewPortHeight() * (info.nMax - info.nMin));
		info.nPos = (int)(0.5 + m_ChartViewer.getViewPortTop() * (info.nMax - info.nMin))
			+ info.nMin;
		m_VScrollBar.SetScrollInfo(&info);
	}

	// Compute the start date (in chartTime) and duration (in seconds) of the view port
	m_currentDuration = (int)(0.5 + m_ChartViewer.getViewPortHeight() * m_dateRange);

	// Set the duration combo box to reflect the duration (in days)
	CString buffer;
	buffer.Format(_T("%d"), (int)(0.5 + m_currentDuration));
	m_Duration.SetWindowText(buffer);
	//
	// Update chart and image map if necessary
	//
	if (m_ChartViewer.needUpdateChart())
		drawChart(&m_ChartViewer);
	if (m_ChartViewer.needUpdateImageMap())
		updateImageMap(&m_ChartViewer);
}
//
// User clicks on the CChartViewer
//
void C��ͼ����Dlg::OnBnClickedChartViewer() 
{
	ImageMapHandler *handler = m_ChartViewer.getImageMapHandler();
	if (0 != handler)
	{
		//
		// Query the ImageMapHandler to see if the mouse is on a clickable hot spot. We 
		// consider the hot spot as clickable if its href ("path") parameter is not empty.
		//
		const char *path = handler->getValue("path");
		if ((0 != path) && (0 != *path))
		{
			// In this sample code, we just show all hot spot parameters.
			CHotSpotDlg hs;
			hs.SetData(handler);
			hs.DoModal();
		}
	}
}

//
// Handle scroll bar events
//
double C��ͼ����Dlg::moveScrollBar(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	//
	// Get current scroll bar position
	//
	SCROLLINFO info;
	info.cbSize = sizeof(SCROLLINFO);
	info.fMask = SIF_ALL;
	pScrollBar->GetScrollInfo(&info);

	//
	// Compute new position based on the type of scroll bar events
	//
	int newPos = info.nPos;
	switch (nSBCode)
	{
	case SB_LEFT:
		newPos = info.nMin;
		break;
	case SB_RIGHT:
		newPos = info.nMax;
		break;
	case SB_LINELEFT:
		newPos -= (info.nPage > 10) ? info.nPage / 10 : 1;
		break;
	case SB_LINERIGHT:
		newPos += (info.nPage > 10) ? info.nPage / 10 : 1;
		break;
	case SB_PAGELEFT:
		newPos -= info.nPage;
		break;
	case SB_PAGERIGHT:
		newPos += info.nPage;
		break;
	case SB_THUMBTRACK:
		newPos = info.nTrackPos;
		break;
	}
	if (newPos < info.nMin) newPos = info.nMin;
	if (newPos > info.nMax) newPos = info.nMax;

	// Update the scroll bar with the new position
	pScrollBar->SetScrollPos(newPos);

	// Returns the position of the scroll bar as a ratio of its total length
	return ((double)(newPos - info.nMin)) / (info.nMax - info.nMin);
}
//
// Validate the contents of the duration combo box and update ViewPortWidth accordingly
//
void C��ͼ����Dlg::validateDuration(const CString &text)
{
	// Parse the duration text
	double newDuration = _tcstod(text, 0);

	// Duration too short or not numeric?
	if (newDuration < m_minDuration) 
		newDuration = m_minDuration;

	if (newDuration != m_currentDuration)
	{
		// Set the ViewPortWidth according to the new duration
		m_currentDuration = newDuration;
		m_ChartViewer.setViewPortHeight(newDuration / m_dateRange);

		// Update the chart
		m_ChartViewer.updateViewPort(true, true);
	}
}
//
// Draw the chart and display it in the given viewer
//
void C��ͼ����Dlg::drawChart(CChartViewer *viewer)
{
	//
	// In this demo, we copy the visible part of the data to a separate buffer for chart
	// plotting. 
	//
	// Note that if you only have a small amount of data (a few hundred data points), it
	// may be easier to just plot all data in any case (so the following copying code is 
	// not needed), and let ChartDirector "clip" the chart to the plot area. 
	//

	if (m_dbFduShow == NULL)
	{
		return;
	}

	// Using ViewPortLeft and ViewPortWidth, get the start and end dates of the view port.
	double viewPortStartDate = m_minData + (__int32)(viewer->getViewPortTop() * 
		m_dateRange + 0.5);
	double viewPortEndDate = viewPortStartDate + (__int32)(viewer->getViewPortHeight() * 
		m_dateRange + 0.5);
	
	if (m_bLoadFile == TRUE)
	{
		if (FALSE == FraseDataToDraw((unsigned int)(viewPortStartDate), (unsigned int)(viewPortEndDate)))
		{
			return;
		}
	}
	// Get the starting index of the array using the start date
	int startIndex = (int)(std::lower_bound(&m_DrawPoint_X[0], &m_DrawPoint_X[0] + m_DrawPoint_X.size(), 
		viewPortStartDate) - &m_DrawPoint_X[0]);
	if ((startIndex > 0) && (m_DrawPoint_X[startIndex] != viewPortStartDate)) 
		--startIndex;
	
	// Get the ending index of the array using the end date
	int endIndex = (int)(std::upper_bound(&m_DrawPoint_X[0], &m_DrawPoint_X[0] + m_DrawPoint_X.size(), 
		viewPortEndDate) - &m_DrawPoint_X[0]);
	if (endIndex >= ((int)(m_DrawPoint_X.size()) - 1))
		endIndex = m_DrawPoint_X.size() - 1;

	// Get the length
	int noOfPoints = endIndex - startIndex + 1;

	// We copy the visible data from the main arrays to separate data arrays
	double* viewPortTimeStamps = new double[noOfPoints];


	int arraySizeInBytes = noOfPoints * sizeof(double);
	memcpy(viewPortTimeStamps, &m_DrawPoint_X[startIndex], arraySizeInBytes);


// 	if (noOfPoints >= FullScreenLineShowPointsNum)
// 	{
// 		//
// 		// Zoomable chart with high zooming ratios often need to plot many thousands of 
// 		// points when fully zoomed out. However, it is usually not needed to plot more
// 		// data points than the resolution of the chart. Plotting too many points may cause
// 		// the points and the lines to overlap. So rather than increasing resolution, this 
// 		// reduces the clarity of the chart. So it is better to aggregate the data first if
// 		// there are too many points.
// 		//
// 		// In our current example, the chart only has 520 pixels in width and is using a 2
// 		// pixel line width. So if there are more than 520 data points, we aggregate the 
// 		// data using the ChartDirector aggregation utility method.
// 		//
// 		// If in your real application, you do not have too many data points, you may 
// 		// remove the following code altogether.
// 		//
// 
// 		// Set up an aggregator to aggregate the data based on regular sized slots
// 		ArrayMath m(DoubleArray(viewPortTimeStamps, noOfPoints));
// 		m.selectRegularSpacing(noOfPoints / (FullScreenLineShowPointsNum / 2));
// 
// 		// For the timestamps, take the first timestamp on each slot
// 		int aggregatedNoOfPoints = m.aggregate(DoubleArray(viewPortTimeStamps, noOfPoints), 
// 			Chart::AggregateFirst).len;
// 
// 		// For the data values, aggregate by taking the averages
// 		for (unsigned int i=0; i<m_uiInstrumentADCNum; i++)
// 		{
// 			m.aggregate(DoubleArray(&m_dbFduData[i][startIndex], noOfPoints), Chart::AggregateAvg);
// 		}
// 		noOfPoints = aggregatedNoOfPoints;
// 	}

	//
	// Now we have obtained the data, we can plot the chart. 
	//

	///////////////////////////////////////////////////////////////////////////////////////
	// Step 1 - Configure overall chart appearance. 
	///////////////////////////////////////////////////////////////////////////////////////

	// Create an XYChart object 600 x 300 pixels in size, with pale blue (0xf0f0ff) 
	// background, black (000000) border, 1 pixel raised effect, and with a rounded frame.
	CRect rectWindow, rectWindowDlg, rectWindowCtrl;
/*	GetDlgItem(IDC_GRAPH)->GetWindowRect(&rectWindow);*/
	GetClientRect(&rectWindowDlg);
	GetDlgItem(IDC_STATIC_CONTROL)->GetClientRect(&rectWindowCtrl);
	rectWindow.left = rectWindowCtrl.right + SetPlotCtrlXInterval;
	rectWindow.right = rectWindowDlg.right - SetVScrollWidth - SetPlotCtrlXInterval;
	rectWindow.top = rectWindowCtrl.top + SetPlotCtrlYInterval;
	rectWindow.bottom = rectWindowCtrl.bottom;
	GetDlgItem(IDC_ChartViewer)->MoveWindow(&rectWindow);

	XYChart *c = new XYChart(rectWindow.Width(), rectWindow.Height(), SetPlotCtrlBackgroundColor, 0, 1);
	c->setRoundedFrame(m_extBgColor);

	// Set the plotarea at (55, 58) and of size 520 x 195 pixels, with white
	// background. Turn on both horizontal and vertical grid lines with light grey
	// color (0xcccccc). Set clipping mode to clip the data lines to the plot area.
	int iWidth = 0;
	int iHeight = 0;
	iWidth = rectWindow.Width() - SetLegendWidth - m_uiIntervalNum * SetPlotAreaXInterval - SetLegendXInterval;
	iHeight = rectWindow.Height() - SetPlotAreaYInterval - SetPlotAreaBottomInterval;
	c->setPlotArea(m_uiIntervalNum * SetPlotAreaXInterval, SetPlotAreaYInterval, iWidth, iHeight, SetPlotAreaBackgroundColor, -1, -1, SetHGridColor, SetVGridColor);
	c->setClipping();

	// Add a legend box at (50, 30) (top of the chart) with horizontal layout. Use 9
	// pts Arial Bold font. Set the background and border color to Transparent.
	c->addLegend(rectWindow.Width() - SetLegendWidth, SetLegendYInterval, false, "arialbd.ttf", SetLegnedBoxFontSize)->setBackground(Chart::Transparent);

	// Add a title box to the chart using 15 pts Times Bold Italic font, on a light
	// blue (CCCCFF) background with glass effect. white (0xffffff) on a dark red
	// (0x800000) background, with a 1 pixel 3D border.
	c->addTitle("Hitech Matrix428", "timesbi.ttf", SetTitleBoxFontSize)->setBackground(
		SetTitleBackgroundColor, SetTitleEdgeColor, Chart::glassEffect());

 	// Swap the x and y axis to become a rotated chart
 	c->swapXY();
	 
	// Set the y axis on the top side (right + rotated = top)
	c->setYAxisOnRight(false);

 	// Reverse the x axis so it is pointing downwards
 	c->xAxis()->setReverse();

	// Set the labels on the x axis.
	//	c->xAxis()->setLabels(StringArray(labels, sizeof(labels)/sizeof(labels[0])));


	// Display 1 out of 3 labels on the x-axis.
//	c->xAxis()->setLabelStep(3);

	// 	// Add a title to the x axis
	// 	c->xAxis()->setTitle("Jun 12, 2006");

	///////////////////////////////////////////////////////////////////////////////////////
	// Step 2 - Add data to chart
	///////////////////////////////////////////////////////////////////////////////////////

	// 
	// In this example, we represent the data by lines. You may modify the code below if 
	// you want to use other representations (areas, scatter plot, etc).
	//

	// Add a line layer to the chart
	LineLayer *layer = c->addLineLayer();

	// Set the default line width to 2 pixels
	layer->setLineWidth(SetLineWidth);

	// Set the axes width to 2 pixels
	c->xAxis()->setWidth(SetXAxisWidth);
	c->yAxis()->setWidth(SetYAxisWidth);

	// Now we add the 3 data series to a line layer, using the color red (ff0000), green
	// (00cc00) and blue (0000ff)
	layer->setXData(DoubleArray(viewPortTimeStamps, noOfPoints));
// 	layer->addDataSet(DoubleArray(&m_dbFduData[0][startIndex], noOfPoints), 0xff0000, "FDU #1");
// 	layer->addDataSet(DoubleArray(&m_dbFduData[1][startIndex], noOfPoints), 0x00cc00, "FDU #2");
// 	layer->addDataSet(DoubleArray(&m_dbFduData[2][startIndex], noOfPoints), 0x0000ff, "FDU #3");

	for (unsigned int i=0; i<m_uiInstrumentADCNum; i++)
	{
		CString str = _T("");
		int color = -1;
		if (i % 3 == 0)
		{
			color = RedColor;
		} 
		else if(i % 3 == 1)
		{
			color = GreenColor;
		}
		else
		{
			color = BlueColor;
		}
		if (m_bLoadFile == TRUE)
		{
			str.Format(_T("FDU #%d"), m_uiInstrumentNb[i]);
		}
		else
		{
			str.Format(_T("FDU #%d"), m_oSocketADCDataRec.m_uiInstrumentNb[i]);
		}
		int ansiCount = WideCharToMultiByte(CP_ACP, 0, str, -1, NULL, 0, NULL, NULL);
		char * pTempChar = (char*)malloc(ansiCount*sizeof(char));
		memset(pTempChar, 0, ansiCount);
		WideCharToMultiByte(CP_ACP, 0, str, -1, pTempChar, ansiCount, NULL, NULL);
/*		layer->addDataSet(DoubleArray(&m_dbFduShow[i][startIndex - m_uiADCStartNum], noOfPoints), color, pTempChar);*/
		layer->addDataSet(DoubleArray(&m_dbFduShow[i][startIndex], noOfPoints), color, pTempChar);
		free(pTempChar);
//		layer->addDataSet(DoubleArray(&m_dbFduData[i][startIndex], noOfPoints), color, str);
	}

	///////////////////////////////////////////////////////////////////////////////////////
	// Step 3 - Set up x-axis scale
	///////////////////////////////////////////////////////////////////////////////////////

	// Set x-axis date scale to the view port date range. 
	c->xAxis()->setDateScale(viewPortStartDate, viewPortEndDate);

	// Configure the x-axis to auto-scale with at least 75 pixels between major tick and 
	// 15  pixels between minor ticks. This shows more minor grid lines on the chart.
//	c->xAxis()->setTickDensity(80, 8);

	//
	// In the current demo, the x-axis range can be from a few years to a few days. We can 
	// let ChartDirector auto-determine the date/time format. However, for more beautiful 
	// formatting, we set up several label formats to be applied at different conditions. 
	//

// 	// If all ticks are yearly aligned, then we use "yyyy" as the label format.
// 	c->xAxis()->setFormatCondition("align", 360 * 86400);
// 	c->xAxis()->setLabelFormat("{value|yyyy}");
// 
// 	// If all ticks are monthly aligned, then we use "mmm yyyy" in bold font as the first 
// 	// label of a year, and "mmm" for other labels.
// 	c->xAxis()->setFormatCondition("align", 30 * 86400);
// 	c->xAxis()->setMultiFormat(Chart::StartOfYearFilter(), "<*font=bold*>{value|mmm yyyy}", 
// 		Chart::AllPassFilter(), "{value|mmm}");
// 
// 	// If all ticks are daily algined, then we use "mmm dd<*br*>yyyy" in bold font as the 
// 	// first label of a year, and "mmm dd" in bold font as the first label of a month, and
// 	// "dd" for other labels.
// 	c->xAxis()->setFormatCondition("align", 86400);
// 	c->xAxis()->setMultiFormat(Chart::StartOfYearFilter(), 
// 		"<*block,halign=left*><*font=bold*>{value|mmm dd<*br*>yyyy}", 
// 		Chart::StartOfMonthFilter(), "<*font=bold*>{value|mmm dd}");
// 	c->xAxis()->setMultiFormat(Chart::AllPassFilter(), "{value|dd}");
// 
// 	// For all other cases (sub-daily ticks), use "hh:nn<*br*>mmm dd" for the first label of
// 	// a day, and "hh:nn" for other labels.
// 	c->xAxis()->setFormatCondition("else");
// 	c->xAxis()->setMultiFormat(Chart::StartOfDayFilter(), 
// 		"<*font=bold*>{value|hh:nn<*br*>mmm dd}", Chart::AllPassFilter(), "{value|hh:nn}");

	///////////////////////////////////////////////////////////////////////////////////////
	// Step 4 - Set up y-axis scale
	///////////////////////////////////////////////////////////////////////////////////////

// 	if ((viewer->getZoomDirection() == Chart::DirectionVertical) || 
// 		((m_minValue == 0) && (m_maxValue == 0)))
	if (((m_minValue == 0) && (m_maxValue == 0)))
	{
		// y-axis is auto-scaled - save the chosen y-axis scaled to support xy-zoom mode
		c->layout();
		m_minValue = c->yAxis()->getMinValue();
		m_maxValue = c->yAxis()->getMaxValue();
	}
	else
	{
		// xy-zoom mode - compute the actual axis scale in the view port 
		double axisLowerLimit = m_minValue + (m_maxValue - m_minValue) * viewer->getViewPortLeft();
		double axisUpperLimit = m_minValue + (m_maxValue - m_minValue) * (viewer->getViewPortLeft() + viewer->getViewPortWidth());
		// *** use the following formula if you are using a log scale axis ***
		// double axisLowerLimit = m_maxValue * pow(m_minValue / m_maxValue, 
		//  viewer->getViewPortTop() + viewer->getViewPortHeight());
		// double axisUpperLimit = m_maxValue * pow(m_minValue / m_maxValue, 
		//  viewer->getViewPortTop());

		// use the zoomed-in scale
		c->yAxis()->setLinearScale(axisLowerLimit, axisUpperLimit);
		c->yAxis()->setRounding(false, false);
	}

	///////////////////////////////////////////////////////////////////////////////////////
	// Step 5 - Display the chart
	///////////////////////////////////////////////////////////////////////////////////////

	// Set the chart image to the WinChartViewer
	delete m_ChartViewer.getChart();
	m_ChartViewer.setChart(c);
 	// �����ͼ
// 	c->makeChart("Matrix428.bmp");

	// �ͷ���Դ
	delete[] viewPortTimeStamps;
}
//
// Update the image map
//
void C��ͼ����Dlg::updateImageMap(CChartViewer *viewer)
{
	if (0 == viewer->getImageMapHandler())
	{
		// no existing image map - creates a new one
		viewer->setImageMap(viewer->getChart()->getHTMLImageMap("clickable", "",
			"title='[{dataSetName}] {x|1}: Volt {value|9}'"));
	}
}
void C��ͼ����Dlg::OnCbnSelchangeDuration()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	// Get the selected duration
	CString text;
	m_Duration.GetLBText(m_Duration.GetCurSel(), text);

	// Validate and update the chart
	validateDuration(text);
}

void C��ͼ����Dlg::OnCbnKillfocusDuration()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	// Get the duration text
	CString text;
	m_Duration.GetWindowText(text);

	// Validate and update the chart
	validateDuration(text);
}

void C��ͼ����Dlg::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);

	// TODO: �ڴ˴������Ϣ����������
	// �Ի����Ⱥ͸߶ȵ����� 
	int iIncrementX = cx - m_iClientWidth;
	int iIncrementY = cy - m_iClientHeight;

	// ��С��ʱ����Ϊ0
	if (nType == SIZE_MINIMIZED)
	{
		iIncrementX = iIncrementY = 0;
	}

	for (int i = 0; i < m_iControlNumber; i++)
	{
		CWnd *pWndCtrl = NULL;

		int iId = m_pControlArray[i].iId;
		int iFlag = m_pControlArray[i].iFlag;
		int iPercent = m_pControlArray[i].iPercent;

		// ��Чֵ
		if ((iPercent < 0) || (iPercent > 100))
			continue;

		// �õ��ؼ�ָ��
		pWndCtrl = GetDlgItem(iId);
		if ((NULL != pWndCtrl) && IsWindow(pWndCtrl->GetSafeHwnd()))
		{
			CRect rectCtrl;
			pWndCtrl->GetWindowRect(rectCtrl);

			ScreenToClient(rectCtrl);

			int iLeft = rectCtrl.left;
			int iTop = rectCtrl.top;
			int iWidth = rectCtrl.Width();
			int iHeight = rectCtrl.Height();

			switch (iFlag)
			{
			case MOVEX: // X�����ƶ�
				iLeft += (iIncrementX * iPercent / 100);
				break;
			case MOVEY: // Y�����ƶ�
				iTop += (iIncrementY * iPercent / 100);
				break;

			case MOVEXY: // X�����Y����ͬʱ�ƶ�
				iLeft += (iIncrementX * iPercent / 100);
				iTop += (iIncrementY * iPercent / 100);
				break;

			case ELASTICX: // X����ı��С
				iWidth += (iIncrementX * iPercent / 100);
				break;

			case ELASTICY: // Y����ı��С
				iHeight += (iIncrementY * iPercent / 100);
				break;

			case ELASTICXY: // X�����Y����ͬʱ�ı��С
				iWidth += (iIncrementX * iPercent / 100);
				iHeight += (iIncrementY * iPercent / 100);
				break;

			default:
				;
			}

			// �ѿؼ��ƶ�����λ��
			pWndCtrl->MoveWindow(iLeft, iTop, iWidth, iHeight);
		}
	}

	// ��ͼ���ƶ����Ի������½�
	if (IsWindow(m_wndSizeIcon.GetSafeHwnd()))
		m_wndSizeIcon.MoveWindow(cx - m_bitmap.bmWidth, cy - m_bitmap.bmHeight, m_bitmap.bmWidth, m_bitmap.bmHeight);

	// ��¼�Ի���client����Ĵ�С
	if (nType != SIZE_MINIMIZED)
	{
		m_iClientWidth = cx;
		m_iClientHeight = cy;
	}
	// �ػ��ͼ��
	//
	// Update chart and image map if necessary
	//
	if (NULL != m_ChartViewer.getChart())
	{
//		drawChart(&m_ChartViewer);
		// �ػ��ͼ��
		m_ChartViewer.updateViewPort(true, false);
	}
	Invalidate(TRUE);//ˢ�½���
}

void C��ͼ����Dlg::OnSizing(UINT fwSide, LPRECT pRect)
{
	CDialog::OnSizing(fwSide, pRect);

	// TODO: �ڴ˴������Ϣ����������
	int iWidth = pRect->right - pRect->left;
	int iHeight = pRect->bottom - pRect->top;

	if (iWidth <= m_iMinWidth)
		pRect->right = pRect->left + m_iMinWidth;

	if(iHeight <= m_iMinHeight)
		pRect->bottom = pRect->top + m_iMinHeight;
}
BOOL C��ͼ����Dlg::SetControlProperty(PDLGCTLINFO lp, int nElements)
{
	// ���ÿؼ�������Ϣ
	if (NULL == lp)
		return FALSE;

	if (nElements <= 0)
		return FALSE;

	m_pControlArray = lp;
	m_iControlNumber = nElements;
	return TRUE;
}

void C��ͼ����Dlg::ShowSizeIcon(BOOL bShow /*=NULL*/)
{
	m_bShowSizeIcon = bShow;
}
void C��ͼ����Dlg::OnBnClickedButtonSavechart()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString sPathName = _T("");
	const wchar_t pszFilter[] = _T("λͼ(*.bmp)|*.bmp||");
//	const char pszFilter[] = _T("λͼ(*.bmp)|*.bmp||");
	CFileDialog dlg(FALSE, _T(".bmp"), _T("Matrix428.bmp"),OFN_HIDEREADONLY| OFN_OVERWRITEPROMPT,pszFilter, this);

	if ( dlg.DoModal()!=IDOK )
		return;
	sPathName=dlg.GetPathName();
	if (NULL != m_ChartViewer.getChart())
	{
		//��Ϊ��Ҫ��������ݰ������ģ�������Ҫ���µ�ת������
		int ansiCount = WideCharToMultiByte(CP_ACP, 0, sPathName, -1, NULL, 0, NULL, NULL);
		char * pTempChar = (char*)malloc(ansiCount*sizeof(char));
		memset(pTempChar, 0, ansiCount);
		WideCharToMultiByte(CP_ACP, 0, sPathName, -1, pTempChar, ansiCount, NULL, NULL);
		m_ChartViewer.getChart()->makeChart(pTempChar);
 		free(pTempChar);
	}
}

void C��ͼ����Dlg::OnBnClickedButtonOpenadcfile()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	// ���ļ�
	const wchar_t pszFilter[] = _T("�ı��ļ�(*.text)|*.text|�ı��ļ�(*.txt)|*.txt|All Files (*.*)|*.*||");
	CFileDialog dlg(TRUE, _T(".text"), _T("1.text"), OFN_HIDEREADONLY| OFN_OVERWRITEPROMPT, pszFilter, this);

	if ( dlg.DoModal()!=IDOK )
	{
		return;
	}

	// ��������
	m_ADCDataInfo.clear();
	// ��ȡ�ļ������ݵ�����
	m_uiADCFileLineNum = 0;
	if(FALSE == LoadData(dlg.GetPathName(), FALSE))
	{
		return;
	}
	if (FALSE == FraseDataAndDrawGraph())
	{
		return;
	}
	// ��ͼ
	OnPrepareToDrawGraph();
}

// ���ļ�����������
BOOL C��ͼ����Dlg::LoadData(CString csOpenFilePath, BOOL bLoadLastFile)
{
	if ((_taccess(csOpenFilePath,0)) != -1)
	{
		CFile file;
		if(file.Open(csOpenFilePath, CFile::modeRead) == FALSE)
		{
			AfxMessageBox(_T("�����ݲ����ļ�����"));	
			return FALSE;
		}
		else
		{
			CString str = _T("");
			CArchive ar(&file, CArchive::load);
			unsigned int uiADCLastFileLineNum = 0;

			// ����ADC���ݲɼ��Ĳɼ�վ�豸��
			m_uiInstrumentADCNum = 0;
			// ADC���ݿ�ʼ�����ݵ���
			m_uiADCStartNum = 0;
			// ADC����ת����ʽ
			m_uiADCDataCovNb = 0;
			// ADC���ݲ�����ʼʱ��
			ar.ReadString(str);

			// ��ʼ������
			m_DrawPoint_X.clear();
			if (m_dbFduData != NULL)
			{
				for (unsigned int i=0; i<m_uiInstrumentADCNum; i++)
				{
					m_dbFduData[i].clear();
				}
				delete[] m_dbFduData;
				m_dbFduData = NULL;
			}
			if (m_dbFduShow != NULL)
			{
				for (unsigned int i=0; i<m_uiInstrumentADCNum; i++)
				{
					m_dbFduShow[i].clear();
				}
				delete[] m_dbFduShow;
				m_dbFduShow = NULL;
			}
			if (m_uiInstrumentNb != NULL)
			{
				delete[] m_uiInstrumentNb;
				m_uiInstrumentNb = NULL;
			}
			// ADC���ݲ�����Ϣ
			ar.ReadString(str);
			_stscanf_s(str, _T("�ɼ�վ�豸����%d���ӵ�%d�����ݿ�ʼ�洢ADC���ݣ�����ת����ʽ���÷�ʽ%d��"), &m_uiInstrumentADCNum, &m_uiADCStartNum, &m_uiADCDataCovNb);
			if (m_uiInstrumentADCNum == 0)
			{
//				fp_str.close();
				ar.Close();
				file.Close();
				AfxMessageBox(_T("�ɼ�վ�豸����Ϊ0��"));
				return FALSE;
			}
			m_uiInstrumentNb = new unsigned int[m_uiInstrumentADCNum];
			for (unsigned int i=0; i<m_uiInstrumentADCNum; i++)
			{
				m_uiInstrumentNb[i] = 0;
			}
			// �ɼ�վ�豸��ǩ
			ar.ReadString(str);
			OnPhraseLabels(str);
			while(ar.ReadString(str))
			{
				m_uiADCFileLineNum++;
				if (bLoadLastFile == TRUE)
				{
					uiADCLastFileLineNum++;
				}
				m_ADCDataInfo.push_back(str);
			}
			ar.Close();
			file.Close();
			if (bLoadLastFile == TRUE)
			{
				vector<CString> temp;
				for (unsigned int i=0; i<(m_uiADCFileLineNum - uiADCLastFileLineNum); i++)
				{
					temp.push_back(m_ADCDataInfo[i]);
				}
				m_ADCDataInfo.erase(m_ADCDataInfo.begin(), m_ADCDataInfo.begin() + m_uiADCFileLineNum - uiADCLastFileLineNum);
				for (unsigned int i=0; i<(m_uiADCFileLineNum - uiADCLastFileLineNum); i++)
				{
					m_ADCDataInfo.push_back(temp[i]);
				}
				temp.clear();
			}
			return TRUE;
		}
	}
	else
	{
		return FALSE;
	}
}
// ����һ��ADC����
void C��ͼ����Dlg::OnPhraseEachLine(CString str)
{
	int iDirectionPrevious = 0;
	int iDirectionNow = 0;
	int iDirectionEnd = 0;
	CString cstmp = _T("");
	iDirectionEnd = str.GetLength();
	while(iDirectionEnd != iDirectionPrevious)
	{
		iDirectionNow = str.Find(_T(" \t"), iDirectionPrevious);
		cstmp = str.Mid(iDirectionPrevious, iDirectionNow-iDirectionPrevious);
		iDirectionPrevious = iDirectionNow + ADCDataInterval;
		if (cstmp == _T(" "))
		{
			iDirectionPrevious += ADCDataInterval;
			continue;
		}
		else
		{
			m_dbFduData[m_uiADCDataNum%m_uiInstrumentADCNum].push_back(_tstof(cstmp));
			m_uiADCDataNum++;
		}
	}
}

void C��ͼ����Dlg::OnBnClickedYzoompb()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_ChartViewer.setZoomDirection(Chart::DirectionHorizontal); 
	m_ChartViewer.setScrollDirection(Chart::DirectionHorizontal);
	if (m_dbFduData == NULL)
	{
		return;
	}
	// Viewport is always unzoomed as x-axis is auto-scaled
// 	m_ChartViewer.setViewPortTop(1);
// 	m_ChartViewer.setViewPortHeight(0);

	// Update chart to auto-scale axis
	m_ChartViewer.updateViewPort(true, true);
}

void C��ͼ����Dlg::OnBnClickedButtonRedraw()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString str = _T("");
	double dbLineInterval = 0.0;
	double dbLineZoom = 0.0;
	// �ж��Ƿ������ݿ����ػ�
	if (m_dbFduData == NULL)
	{
		return;
	}
	// ���ð���ֱ����ͼ�ػ�������
	GetDlgItem(IDC_BUTTON_REDRAW)->EnableWindow(FALSE);
	// �õ���������ֵ
	GetDlgItem(IDC_EDIT_LINEINTERVAL)->GetWindowText(str);
	dbLineInterval = _tstof(str);
	GetDlgItem(IDC_EDIT_LINEZOOM)->GetWindowText(str);
	dbLineZoom = _tstof(str);

// 	for (unsigned int i=0; i<m_uiInstrumentADCNum; i++)
// 	{
// 		for (unsigned int j=0; j<m_uiADCDataFduNum; j++)
// 		{
// 			m_dbFduShow[i][j] = m_dbFduData[i][j] * dbLineZoom + i * dbLineInterval;
// 		}
// 	}
	unsigned int icurrentDuration = (unsigned int)m_currentDuration;
	for (unsigned int i=0; i<m_uiInstrumentADCNum; i++)
	{
		for (unsigned int j=0; j<icurrentDuration; j++)
		{
			m_dbFduShow[i][j] = m_dbFduData[i][j] * dbLineZoom + i * dbLineInterval;
		}
	}
	// �ػ��ͼ��
	m_ChartViewer.updateViewPort(true, true);

	GetDlgItem(IDC_BUTTON_REDRAW)->EnableWindow(TRUE);
}

// ����ADC���ݽ���Socket
void C��ͼ����Dlg::OnCreateADCRecSocket(void)
{
	BOOL bReturn = FALSE;
	// ��������˿ڣ����շ�������Ӧ��֡��create����д�����������IP��ַ����չ̶�IP��ַ���͵�֡����д��ȫ������
	m_oSocketADCDataRec.Close();
	bReturn = m_oSocketADCDataRec.Create(ADCGraphShowPort, SOCK_DGRAM);
	if (bReturn == FALSE)
	{
		AfxMessageBox(_T("ADC���ݽ��ն˿ڴ���ʧ�ܣ�"));
	}
	else
	{
		int iOptionValue = ADCRecPortBufSize;
		int iOptionLen = sizeof(int);
		bReturn = m_oSocketADCDataRec.SetSockOpt(SO_RCVBUF, (void*)&iOptionValue, iOptionLen, SOL_SOCKET);
		if (bReturn == FALSE)
		{
			AfxMessageBox(_T("ADC���ݽ��ն˿ڽ��ջ���������ʧ�ܣ�"));
		}
	}
}

void C��ͼ����Dlg::OnClose()
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	m_oSocketADCDataRec.Close();
	CDialog::OnClose();
}

void C��ͼ����Dlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	// ADC��������Ӧ�����
	if (nIDEvent == GraphRefreshTimerNb)
	{
		KillTimer(GraphRefreshTimerNb);
		// ���л�ͼ����
		OnNetADCGraph();
		SetTimer(GraphRefreshTimerNb, GraphRefreshTimerSet, NULL);
	}

	CDialog::OnTimer(nIDEvent);
}

void C��ͼ����Dlg::OnBnClickedButtonStart()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	GetDlgItem(IDC_BUTTON_START)->EnableWindow(FALSE);
	m_bLoadFile = FALSE;
	SetTimer(GraphRefreshTimerNb, GraphRefreshTimerSet, NULL);
	m_bStartShow = TRUE;
	GetDlgItem(IDC_BUTTON_STOP)->EnableWindow(TRUE);
}

void C��ͼ����Dlg::OnBnClickedButtonStop()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	GetDlgItem(IDC_BUTTON_STOP)->EnableWindow(FALSE);
	KillTimer(GraphRefreshTimerNb);
	GetDlgItem(IDC_BUTTON_START)->EnableWindow(TRUE);
}

// ��������ADC����
void C��ͼ����Dlg::OnNetADCGraph(void)
{
	// �õ�Ĭ�ϱ�����ɫ
	m_extBgColor = getDefaultBgColor();
	// Y�᷶Χ
	// ���Y������̶���ֻ�е�һ����Ҫ���»�Y������
	if (m_bStartShow == TRUE)
	{
		m_bStartShow = FALSE;
		// ���»�Y������
		m_minValue = m_maxValue = 0;
	} 
	else
	{
		// ���Y�����겻�̶���ÿ�ζ����»�Y������
		if (m_bCheckYAxisFixed == FALSE)
		{
			m_minValue = m_maxValue = 0;
		}
	}

	// ��ʼ״̬ÿ������ʾ�ĵ���
	unsigned int uiRecFrameNumMinNb = 0;
	unsigned int uiRecFrameNumMaxNb = 0;
	if (m_oSocketADCDataRec.m_uipRecFrameNum == NULL)
	{
		return;
	}
	uiRecFrameNumMinNb = m_oSocketADCDataRec.GetRecFrameNumMin();
	uiRecFrameNumMaxNb = m_oSocketADCDataRec.GetRecFrameNumMax();
	if (m_oSocketADCDataRec.m_uipRecFrameNum[uiRecFrameNumMinNb] == 0)
	{
		return;
	}
	else if (m_oSocketADCDataRec.m_uipRecFrameNum[uiRecFrameNumMinNb] < ADCRecFrameShowNum)
	{
		m_currentDuration = m_oSocketADCDataRec.m_uipRecFrameNum[uiRecFrameNumMinNb] * ReceiveDataNum;
	}
	else
	{
		m_currentDuration = (ADCRecFrameShowNum - ( m_oSocketADCDataRec.m_uipRecFrameNum[uiRecFrameNumMaxNb] 
		-  m_oSocketADCDataRec.m_uipRecFrameNum[uiRecFrameNumMinNb])) * ReceiveDataNum;
	}
	if (m_oSocketADCDataRec.m_uipRecFrameNum[uiRecFrameNumMinNb] * ReceiveDataNum > ShowLinePointsNumMin)
	{
		m_minDuration = ShowLinePointsNumMin;
	}
	else
	{
		m_minDuration = m_oSocketADCDataRec.m_uipRecFrameNum[uiRecFrameNumMinNb] * ReceiveDataNum;
	}
	unsigned int icurrentDuration = (unsigned int)m_currentDuration;
	m_DrawPoint_X.clear();
	m_uiInstrumentADCNum = m_oSocketADCDataRec.m_uiInstrumentADCNum;
	for (unsigned int i=0; i<m_uiInstrumentADCNum; i++)
	{
		m_dbFduShow[i].clear();
	}
	for (unsigned int i=0; i<icurrentDuration; i++)
	{
		m_DrawPoint_X.push_back(m_oSocketADCDataRec.m_DrawPoint_X[i]);
	}

	double dbLineInterval = 0.0;
	double dbLineZoom = 0.0;
	CString str = _T("");
	GetDlgItem(IDC_EDIT_LINEINTERVAL)->GetWindowText(str);
	dbLineInterval = _tstof(str);
	GetDlgItem(IDC_EDIT_LINEZOOM)->GetWindowText(str);
	dbLineZoom = _tstof(str);
	for (unsigned int i=0; i<m_uiInstrumentADCNum; i++)
	{
		for (unsigned int j=0; j<icurrentDuration; j++)
		{
			m_dbFduShow[i].push_back(m_dbFduData[i][j] * dbLineZoom + i * dbLineInterval);
		}
	}

	// ���������СֵΪm_DrawPoint_X����ĵ�һ��ֵ
	m_minData = m_DrawPoint_X[0];
	m_maxData = m_DrawPoint_X[m_DrawPoint_X.size() - 1];
	OnSetXAxisRange(m_maxData, m_minData);
	// �ػ��ͼ��
	m_ChartViewer.updateViewPort(true, false);
}

// ����X��ȡֵ��Χ�ͱ�ǩ���
void C��ͼ����Dlg::OnSetXAxisRange(double dbmaxData, double dbminData)
{
	// ������ȡֵ�ı仯��Χ
	m_dateRange = dbmaxData - dbminData + 1;

	// ��ͼ�������������
	double maxData = 0.0;
	maxData = dbmaxData;
	m_uiIntervalNum = 0;
	while(maxData > 1)
	{
		maxData = maxData / 10;
		m_uiIntervalNum++;
	}
	if (m_uiIntervalNum < SetLegendXIntervalNumMin)
	{
		m_uiIntervalNum = SetLegendXIntervalNumMin;
	}
	// ����ChartViewer�ܷ�ӳ��Ч����С�ĳ���ʱ��
	m_ChartViewer.setZoomInHeightLimit(m_minDuration / m_dateRange);
	m_ChartViewer.setViewPortHeight(m_currentDuration / m_dateRange);
	m_ChartViewer.setViewPortTop(1 - m_ChartViewer.getViewPortHeight());
}

void C��ͼ����Dlg::OnBnClickedCheckYaxisfixed()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	BOOL bStatus = (BOOL)::SendMessage(GetDlgItem(IDC_CHECK_YAXISFIXED)->GetSafeHwnd(),   BM_GETCHECK,   0,   0);
	if (bStatus == TRUE)
	{
		m_bCheckYAxisFixed = TRUE;
	}
	else
	{
		m_bCheckYAxisFixed = FALSE;
	}
}

// ���������ļ�������ͼ��׼������
void C��ͼ����Dlg::OnPrepareToDrawGraph(void)
{
	//
	// ��ʼ����Ա����
	//
	// �õ�Ĭ�ϱ�����ɫ
	m_extBgColor = getDefaultBgColor();
	// Y�᷶Χ
	m_minValue = m_maxValue = 0;

	// ��ʼ״̬ÿ������ʾ�ĵ���
	if (m_uiADCDataFduNum > ShowLinePointsNumNow)
	{
		m_currentDuration = ShowLinePointsNumNow;
	} 
	else
	{
		m_currentDuration = m_uiADCDataFduNum;
	}
	if (m_uiADCDataFduNum > ShowLinePointsNumMin)
	{
		m_minDuration = ShowLinePointsNumMin;
	}
	else
	{
		m_minDuration = m_uiADCDataFduNum;
	}
	// ���������СֵΪm_timeStamps����ĵ�һ��ֵ
// 	m_minData = m_DrawPoint_X[0];
// 	m_maxData = m_DrawPoint_X[m_DrawPoint_X.size() - 1];
	m_minData = 0;
	m_maxData = m_DrawPoint_X[m_uiADCDataFduNum - 1];

	OnSetXAxisRange(m_maxData, m_minData);
	// �ػ��ͼ��
	m_ChartViewer.updateViewPort(true, true);
}

void C��ͼ����Dlg::OnBnClickedButtonOpenadcfolder()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	wchar_t szDir[MAX_PATH];
	//	char szDir[MAX_PATH];
	BROWSEINFO bi;
	ITEMIDLIST *pidl;
	CString csSaveFolderPath = _T("");
	bi.hwndOwner = this->m_hWnd; // ָ�������ڣ��ڶԻ�����ʾ�ڼ䣬�����ڽ������� 
	bi.pidlRoot = NULL; // ���ָ��NULL�����ԡ����桱Ϊ�� 
	bi.pszDisplayName = szDir; 
	bi.lpszTitle = _T("��ѡ��������ݴ洢Ŀ¼"); // ��һ�н���ʾ�ڶԻ���Ķ��� 
	bi.ulFlags = BIF_STATUSTEXT | BIF_USENEWUI | BIF_RETURNONLYFSDIRS;
	bi.lpfn = NULL;
	bi.lParam = 0;
	bi.iImage = 0;
	pidl = SHBrowseForFolder(&bi);

	if(pidl == NULL) 
	{
		return;
	}
	if(!SHGetPathFromIDList(pidl, szDir))
	{	
		return;
	}
	else
	{
		csSaveFolderPath = szDir;
		m_FileInfo.clear();
		FindFileAndList(csSaveFolderPath);
	}
}

// �����ļ����µ��ļ����г�
void C��ͼ����Dlg::FindFileAndList(CString csSaveFolderPath)
{
	CListBox* pListBox = (CListBox* )GetDlgItem(IDC_LIST_FILE);
	CFileFind findFile;	// �ļ����Ҷ���
	CString strPath = csSaveFolderPath + _T("\\*.text");
	CString strFileName = _T("");
	CString strFilePath = _T("");
	BOOL bWorking = findFile.FindFile(strPath);          //ִ���ļ�����
	vector<int> fileNb;
	fileNb.clear();
	// �����ListBox�ؼ�
	int icount = pListBox->GetCount();
	for (int i = icount - 1; i >= 0; i--)
	{
		pListBox->DeleteString(i);
	}
	while(bWorking)
	{
		 bWorking = findFile.FindNextFile();						//������һ���ļ�
		 if(findFile.IsDirectory())										//��ΪĿ¼����������ѭ��
		 {
			 continue;
		 }
		 if (findFile.IsDots())
		 {
			 continue;
		 }
		strFileName=findFile.GetFileName();					//��ȡ�ļ����ƣ�������׺
		int iDirectionLable = 0;
		int iLength = strFileName.GetLength();
		CString csTemp = _T("");
		iDirectionLable = strFileName.Find(_T(".text"), 0);
		csTemp = strFileName.Mid(0, iDirectionLable);
		fileNb.push_back(_ttoi(csTemp));
	}
	sort(fileNb.begin(), fileNb.end());
	for (unsigned int i=0; i<fileNb.size(); i++)
	{
		strFileName.Format(_T("%d.text"), fileNb[i]);
		pListBox->AddString(strFileName);						// ���뵽ListBox�ؼ���
		strFilePath = csSaveFolderPath + _T("\\") + strFileName;
		m_FileInfo.push_back(strFilePath);
	}
	fileNb.clear();
	if (FALSE == LoadLastADCDataFromFile())
	{
		return;
	}
	LoadADCDataFromFile(0, 90400);
}

void C��ͼ����Dlg::OnLbnDblclkListFile()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CListBox* pListBox = (CListBox* )GetDlgItem(IDC_LIST_FILE);
	int nIndex = pListBox->GetCurSel();
	CString csOpenFilePath = _T("");
	if (nIndex == CB_ERR)
	{
		return;
	}
// 	CString strFileName = _T("");
// 	int n = pListBox->GetTextLen(nIndex);
// 	pListBox->GetText(nIndex, strFileName.GetBuffer(n));
// 	strFileName.ReleaseBuffer();
	
	csOpenFilePath = m_FileInfo[nIndex];
	m_uiOpenFileNb = nIndex;

	m_ADCDataInfo.clear();
	// ��ȡ�ļ������ݵ�����
	m_uiADCFileLineNum = 0;
	// ��������
	if(FALSE == LoadData(csOpenFilePath, FALSE))
	{
		return;
	}
	if (FALSE == FraseDataAndDrawGraph())
	{
		return;
	}
	// ��ͼ
	OnPrepareToDrawGraph();
}


// ��ADC������Ϣ�������н����������ڻ�ͼ
BOOL C��ͼ����Dlg::FraseDataToDraw(unsigned int uiStartDrawPointsNum, unsigned int uiEndDrawPointsNum)
{
	CString str = _T("");
	double dbLineInterval = 0.0;
	double dbLineZoom = 0.0;
	unsigned int uiSamplingRate = 0;
	if (m_uiADCFileLineNum == 0)
	{
		return FALSE;
	}
	m_bLoadFile = TRUE;
	if (uiStartDrawPointsNum < m_uiADCStartNum)
	{
		CString csOpenFilePath = _T("");
		if (m_uiOpenFileNb >= 1)
		{
			m_uiOpenFileNb = m_uiOpenFileNb - 1;
			csOpenFilePath = m_FileInfo[m_uiOpenFileNb];
			// ��������
			if(FALSE == LoadData(csOpenFilePath, TRUE))
			{
				return FALSE;
			}
		}
		else
		{
			AfxMessageBox(_T("�ļ������ڣ�"));
			return FALSE;
		}
	}
	// ��ʼ������
	m_DrawPoint_X.clear();
	if (m_dbFduData != NULL)
	{
		for (unsigned int i=0; i<m_uiInstrumentADCNum; i++)
		{
			m_dbFduData[i].clear();
		}
		delete[] m_dbFduData;
		m_dbFduData = NULL;
	}
	if (m_dbFduShow != NULL)
	{
		for (unsigned int i=0; i<m_uiInstrumentADCNum; i++)
		{
			m_dbFduShow[i].clear();
		}
		delete[] m_dbFduShow;
		m_dbFduShow = NULL;
	}

	// �ɼ�վ�ɼ�����ADC��������
	m_uiADCDataNum = 0;
	// ÿ���ɼ�վ�ɼ�����ADC���ݸ���
	m_uiADCDataFduNum = 0;
	m_dbFduData = new vector<double>[m_uiInstrumentADCNum];
	m_dbFduShow = new vector<double>[m_uiInstrumentADCNum];

	GetDlgItem(IDC_EDIT_SAMPLINGRATE)->GetWindowText(str);
	uiSamplingRate = _tstoi(str);
	for (unsigned int i=0; i<(uiEndDrawPointsNum - uiStartDrawPointsNum); i++)
	{
		if (i % uiSamplingRate == 0)
		{
			OnPhraseEachLine(m_ADCDataInfo[i + uiStartDrawPointsNum - m_uiADCStartNum]);
		}
	}
	if ((uiEndDrawPointsNum - uiStartDrawPointsNum - 1) % uiSamplingRate != 0)
	{
		OnPhraseEachLine(m_ADCDataInfo[uiEndDrawPointsNum - m_uiADCStartNum - 1]);
	}

	m_uiADCDataFduNum = m_uiADCDataNum / m_uiInstrumentADCNum;

	for (unsigned int i=0; i<(m_uiADCDataFduNum - 1); i++)
	{
		m_DrawPoint_X.push_back(i * uiSamplingRate + uiStartDrawPointsNum);
	}
	m_DrawPoint_X.push_back(uiEndDrawPointsNum -1 );
	GetDlgItem(IDC_EDIT_LINEINTERVAL)->GetWindowText(str);
	dbLineInterval = _tstof(str);
	GetDlgItem(IDC_EDIT_LINEZOOM)->GetWindowText(str);
	dbLineZoom = _tstof(str);
	for (unsigned int i=0; i<m_uiInstrumentADCNum; i++)
	{
		for (unsigned int j=0; j<m_uiADCDataFduNum; j++)
		{
			m_dbFduShow[i].push_back(m_dbFduData[i][j] * dbLineZoom + i * dbLineInterval);
		}
	}
	return TRUE;
}

// �������ݲ���ͼ
BOOL C��ͼ����Dlg::FraseDataAndDrawGraph(void)
{
	unsigned int uiStartDrawPointsNum = 0;
	unsigned int uiEndDrawPointsNum = 0;
	if ((m_uiADCFileLineNum + m_uiADCStartNum) > ShowLinePointsNumNow)
	{
		uiStartDrawPointsNum = m_uiADCFileLineNum + m_uiADCStartNum - ShowLinePointsNumNow;
	}
	else
	{
		uiStartDrawPointsNum = m_uiADCStartNum;
	}
	uiEndDrawPointsNum = m_uiADCFileLineNum + m_uiADCStartNum;
	if (FALSE == FraseDataToDraw(uiStartDrawPointsNum, uiEndDrawPointsNum))
	{
		return FALSE;
	}
	return TRUE;
}

// ���ļ�����������
void C��ͼ����Dlg::LoadADCDataFromFile(unsigned int uiStartDrawPointsNum, unsigned int uiEndDrawPointsNum)
{
	unsigned int uiStartFileNb = uiStartDrawPointsNum / (SaveADCDataPackageNum * ReceiveDataNum);
	ULONGLONG ullPointer = 0;
	unsigned int uiSamplingRate = 0;
	double dbLineInterval = 0.0;
	double dbLineZoom = 0.0;
	CString str = _T("");
	GetDlgItem(IDC_EDIT_SAMPLINGRATE)->GetWindowText(str);
	uiSamplingRate = _tstoi(str);

	// ��ʼ������
	m_DrawPoint_X.clear();
	if (m_dbFduData != NULL)
	{
		for (unsigned int i=0; i<m_uiInstrumentADCNum; i++)
		{
			m_dbFduData[i].clear();
		}
	}
	if (m_dbFduShow != NULL)
	{
		for (unsigned int i=0; i<m_uiInstrumentADCNum; i++)
		{
			m_dbFduShow[i].clear();
		}
	}
	m_uiFindLineCount = 0;

	for (unsigned int i=uiStartFileNb; i<m_FileInfo.size(); i++)
	{
		if ((_taccess(m_FileInfo[i], 0)) != -1)
		{
			if(m_file.Open(m_FileInfo[i], CFile::modeRead) == FALSE)
			{
				AfxMessageBox(_T("�����ݲ����ļ�����"));	
				break;
			}
			else
			{
				CArchive ar(&m_file, CArchive::load);
				ULONGLONG lActual;
				unsigned int uiLength = 0;
				unsigned int uiRead = 0;
				m_file.SeekToBegin();
				ULONGLONG ullEnd = m_file.SeekToEnd();

				// ����ƶ�Ϊ�ַ�����+2(\n����)
				m_file.SeekToBegin();
				// ADC���ݲ�����ʼʱ��
				ar.ReadString(str);
				uiLength += (str.GetLength() + 2) * sizeof(wchar_t);
				lActual = m_file.Seek(uiLength, CFile::begin);
				// ADC���ݲ�����Ϣ
				ar.ReadString(str);
				uiLength  += (str.GetLength() + 2) * sizeof(wchar_t);
				lActual = m_file.Seek(uiLength, CFile::begin);
				// �ɼ�վ�豸��ǩ
				ar.ReadString(str);
				uiLength  += (str.GetLength() + 2) * sizeof(wchar_t);
				lActual = m_file.Seek(uiLength, CFile::begin);

				if (i == uiStartFileNb)
				{
					ullPointer = uiStartDrawPointsNum % (SaveADCDataPackageNum * ReceiveDataNum);
				}
				// ����
				lActual = m_file.Seek(m_uiADCLineBufNum * sizeof(wchar_t)* ullPointer, CFile::current);
				do 
				{
					if (m_uiFindLineCount == (uiEndDrawPointsNum - uiStartDrawPointsNum))
					{
						break;
					}
					else
					{
						memset(m_pLinebufRead, 0, m_uiADCLineBufNum * sizeof(wchar_t));
						// ��1������
						uiRead = m_file.Read(m_pLinebufRead, m_uiADCLineBufNum * sizeof(wchar_t));
						str = m_pLinebufRead;
						OnPhraseEachLine(str);
						if (uiRead == 0)
						{
							break;
						}
						else
						{
							m_uiFindLineCount++;
							// ����ƶ�Ϊ�ַ�����+4(\r\n����)
							// ����
							lActual = m_file.Seek(m_uiADCLineBufNum * sizeof(wchar_t)* (uiSamplingRate - 1), CFile::current);
						}
					}
				} while (lActual <ullEnd);
				if ((uiRead != 0) && (m_uiFindLineCount != (uiEndDrawPointsNum - uiStartDrawPointsNum)))
				{
					ullPointer = (lActual - ullEnd) / (m_uiADCLineBufNum * sizeof(wchar_t)); 
				}
				m_file.SeekToEnd();
				ar.Close();
				m_file.Close();
				break;
			}
		}
		else
		{
			break;
		}
	}
	m_uiADCDataFduNum = m_uiADCDataNum / m_uiInstrumentADCNum;

	for (unsigned int i=0; i<(m_uiADCDataFduNum - 1); i++)
	{
		m_DrawPoint_X.push_back(i * uiSamplingRate + uiStartDrawPointsNum);
	}
	m_DrawPoint_X.push_back(uiEndDrawPointsNum -1 );
	GetDlgItem(IDC_EDIT_LINEINTERVAL)->GetWindowText(str);
	dbLineInterval = _tstof(str);
	GetDlgItem(IDC_EDIT_LINEZOOM)->GetWindowText(str);
	dbLineZoom = _tstof(str);
	for (unsigned int i=0; i<m_uiInstrumentADCNum; i++)
	{
		for (unsigned int j=0; j<m_uiADCDataFduNum; j++)
		{
			m_dbFduShow[i].push_back(m_dbFduData[i][j] * dbLineZoom + i * dbLineInterval);
		}
	}
}

// �������һ��ADC���ݲ����ļ�
BOOL C��ͼ����Dlg::LoadLastADCDataFromFile(void)
{
	unsigned int uiLastFileNb = m_FileInfo.size() - 1;
	if ((_taccess(m_FileInfo[uiLastFileNb], 0)) != -1)
	{
		if(m_file.Open(m_FileInfo[uiLastFileNb], CFile::modeRead) == FALSE)
		{
			AfxMessageBox(_T("�����һ�����ݲ����ļ�����"));	
			return FALSE;
		}
		else
		{
			CString str = _T("");
			CArchive ar(&m_file, CArchive::load);
			unsigned int uiADCLastFileLineNum = 0;
			ULONGLONG lActual = 0;
			ULONGLONG ullEnd = 0;
			unsigned int uiLength = 0;
			unsigned int uiLineNum = 0;
			// ��ʼ������
			m_DrawPoint_X.clear();
			if (m_dbFduData != NULL)
			{
				for (unsigned int i=0; i<m_uiInstrumentADCNum; i++)
				{
					m_dbFduData[i].clear();
				}
				delete[] m_dbFduData;
				m_dbFduData = NULL;
			}
			if (m_dbFduShow != NULL)
			{
				for (unsigned int i=0; i<m_uiInstrumentADCNum; i++)
				{
					m_dbFduShow[i].clear();
				}
				delete[] m_dbFduShow;
				m_dbFduShow = NULL;
			}
			if (m_uiInstrumentNb != NULL)
			{
				delete[] m_uiInstrumentNb;
				m_uiInstrumentNb = NULL;
			}
			if (m_pLinebufRead != NULL)
			{
				delete[] m_pLinebufRead;
				m_pLinebufRead = NULL;
			}
			// ����ADC���ݲɼ��Ĳɼ�վ�豸��
			m_uiInstrumentADCNum = 0;
			// ADC���ݿ�ʼ�����ݵ���
			m_uiADCStartNum = 0;
			// ADC����ת����ʽ
			m_uiADCDataCovNb = 0;
			// ADC�����ļ�һ����ռ�ֽ���
			m_uiADCLineBufNum = 0;

			m_file.SeekToBegin();
			ullEnd = m_file.SeekToEnd();
			// ����ƶ�Ϊ�ַ�����+2(\n����)
			m_file.SeekToBegin();

			// ADC���ݲ�����ʼʱ��
			ar.ReadString(str);
			uiLength += (str.GetLength() + 2) * sizeof(wchar_t);
			lActual = m_file.Seek(uiLength, CFile::begin);
			// ADC���ݲ�����Ϣ
			ar.ReadString(str);
			uiLength  += (str.GetLength() + 2) * sizeof(wchar_t);
			lActual = m_file.Seek(uiLength, CFile::begin);
			_stscanf_s(str, _T("�ɼ�վ�豸����%d���ӵ�%d�����ݿ�ʼ�洢ADC���ݣ�����ת����ʽ���÷�ʽ%d��"), &m_uiInstrumentADCNum, &m_uiADCStartNum, &m_uiADCDataCovNb);
			if (m_uiInstrumentADCNum == 0)
			{
				//				fp_str.close();
				ar.Close();
				m_file.Close();
				AfxMessageBox(_T("�ɼ�վ�豸����Ϊ0��"));
				return FALSE;
			}
			m_uiInstrumentNb = new unsigned int[m_uiInstrumentADCNum];
			m_dbFduData = new vector<double>[m_uiInstrumentADCNum];
			m_dbFduShow = new vector<double>[m_uiInstrumentADCNum];
			m_uiADCLineBufNum = ADCDataSaveSize * m_uiInstrumentADCNum + 2;
			m_pLinebufRead = new wchar_t[m_uiADCLineBufNum];
			for (unsigned int i=0; i<m_uiInstrumentADCNum; i++)
			{
				m_uiInstrumentNb[i] = 0;
			}
			// �ɼ�վ�豸��ǩ
			ar.ReadString(str);
			OnPhraseLabels(str);
			uiLength  += (str.GetLength() + 2) * sizeof(wchar_t);
			lActual = m_file.Seek(uiLength, CFile::begin);	
			
			m_file.SeekToEnd();
			ar.Close();
			m_file.Close();
			uiLineNum = (unsigned int)((ullEnd - lActual) / (m_uiADCLineBufNum * sizeof(wchar_t)));
			m_uiEndDrawPointsNumMax = m_uiADCStartNum + uiLineNum;
			return TRUE;
		}
	}
	else
	{
		return FALSE;
	}
}

// �����豸��ǩ
void C��ͼ����Dlg::OnPhraseLabels(CString str)
{
	int iDirectionPrevious = 0;
	int iDirectionNow = 0;
	int iDirectionEnd = 0;
	CString cstmp = _T("");
	unsigned int uiNb = 0;
	unsigned int uiLocation = 0;
	iDirectionEnd = str.GetLength();
	while(iDirectionEnd != iDirectionPrevious)
	{
		iDirectionNow = str.Find(_T(" \t"), iDirectionPrevious);
		cstmp = str.Mid(iDirectionPrevious, iDirectionNow-iDirectionPrevious);
		iDirectionPrevious = iDirectionNow + ADCDataInterval;
		if (cstmp == _T(" "))
		{
			iDirectionPrevious += ADCDataInterval;
			continue;
		}
		else
		{
			int iDirectionLable = 0;
			int iLength = cstmp.GetLength();
			CString csTemp = _T("");
			iDirectionLable = cstmp.Find(_T("����"), 0);
			csTemp = cstmp.Mid(iDirectionLable, iLength);
			_stscanf_s(csTemp, _T("����%d"), &uiLocation);
			m_uiInstrumentNb[uiNb] = uiLocation;
			uiNb++;
		}
	}
}
