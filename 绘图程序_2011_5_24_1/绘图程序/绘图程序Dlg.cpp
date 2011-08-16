// 绘图程序Dlg.cpp : 实现文件
//

#include "stdafx.h"
#include "绘图程序.h"
#include "绘图程序Dlg.h"
#include "HotSpotDlg.h"
#include <math.h>
#include <algorithm>
#include <fstream>
#include  <io.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// 表示可改变大小的图标ID
#ifndef OBM_SIZE
#define OBM_SIZE 32766
#endif
// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
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


// C绘图程序Dlg 对话框




C绘图程序Dlg::C绘图程序Dlg(CWnd* pParent /*=NULL*/)
	: CDialog(C绘图程序Dlg::IDD, pParent)
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
	, m_csOpenFilePath(_T(""))
	, m_uiInstrumentMaxNum(0)
	, m_uiInstrumentADCNum(0)
	, m_uiADCStartNum(0)
	, m_uiADCDataCovNb(0)
	, m_uiADCDataNum(0)
	, m_uiADCDataFduNum(0)
	, m_dbFduData(NULL)
	, m_dbFduShow(NULL)
	, m_viewPortDataSeries(NULL)
	, m_dbDataTemp(NULL)
	, m_uiADCFileLineNum(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}
C绘图程序Dlg::~C绘图程序Dlg()
{
	delete m_ChartViewer.getChart();
	// 记录X轴坐标点信息
	m_DrawPoint_X.clear();
	// 记录各条图线点的信息
	m_DrawLine_Y.clear();
	for (unsigned int i=0; i<m_uiInstrumentADCNum; i++)
	{
		m_dbFduData[i].clear();
		m_dbFduShow[i].clear();
	}
	delete[] m_dbFduData;
	delete[] m_dbFduShow;
}
void C绘图程序Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_ChartViewer, m_ChartViewer);
	DDX_Control(pDX, IDC_PointerPB, m_PointerPB);
	DDX_Control(pDX, IDC_XZoomPB, m_XZoomPB);
	DDX_Control(pDX, IDC_HScrollBar, m_HScrollBar);
	DDX_Control(pDX, IDC_VScrollBar, m_VScrollBar);
	DDX_Control(pDX, IDC_Duration, m_Duration);
}

BEGIN_MESSAGE_MAP(C绘图程序Dlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_PointerPB, &C绘图程序Dlg::OnBnClickedPointerpb)
	ON_BN_CLICKED(IDC_ZoomInPB, &C绘图程序Dlg::OnBnClickedZoominpb)
	ON_BN_CLICKED(IDC_ZoomOutPB, &C绘图程序Dlg::OnBnClickedZoomoutpb)
	ON_BN_CLICKED(IDC_XZoomPB, &C绘图程序Dlg::OnBnClickedXzoompb)
	ON_BN_CLICKED(IDC_XYZoomPB, &C绘图程序Dlg::OnBnClickedXyzoompb)
	ON_BN_CLICKED(IDC_ChartViewer, &C绘图程序Dlg::OnBnClickedChartViewer)
	ON_CONTROL(CVN_ViewPortChanged, IDC_ChartViewer, &C绘图程序Dlg::OnViewPortChanged)
	ON_WM_HSCROLL()
	ON_WM_VSCROLL()
	ON_CBN_SELCHANGE(IDC_Duration, &C绘图程序Dlg::OnCbnSelchangeDuration)
	ON_CBN_KILLFOCUS(IDC_Duration, &C绘图程序Dlg::OnCbnKillfocusDuration)
	ON_WM_SIZE()
	ON_WM_SIZING()
	ON_BN_CLICKED(IDC_BUTTON_SAVECHART, &C绘图程序Dlg::OnBnClickedButtonSavechart)
	ON_BN_CLICKED(IDC_BUTTON_OPENADCFILE, &C绘图程序Dlg::OnBnClickedButtonOpenadcfile)
	ON_BN_CLICKED(IDC_YZoomPB, &C绘图程序Dlg::OnBnClickedYzoompb)
	ON_BN_CLICKED(IDC_BUTTON_REDRAW, &C绘图程序Dlg::OnBnClickedButtonRedraw)
END_MESSAGE_MAP()


// C绘图程序Dlg 消息处理程序

BOOL C绘图程序Dlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
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

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	// 输入License
	setLicenseCode("R5MNGUVV3UXWFT2CC44B1D7E"); 

	// 载入图标到鼠标用法按钮
	loadButtonIcon(IDC_PointerPB, IDI_PointerPB, 100, 20);  
	loadButtonIcon(IDC_ZoomInPB, IDI_ZoomInPB, 100, 20);    
	loadButtonIcon(IDC_ZoomOutPB, IDI_ZoomOutPB, 100, 20);

	// 载入图标到变焦/滚动位置控制按钮
	loadButtonIcon(IDC_XZoomPB, IDI_YZoomPB, 105, 20);
	loadButtonIcon(IDC_YZoomPB, IDI_XZoomPB, 105, 20);
	loadButtonIcon(IDC_XYZoomPB, IDI_XYZoomPB, 105, 20);

	// 将对话框及其控件设为尺寸可变的
	OnSiteSizeBox();

	// 初始设置鼠标为横向拖动滚动条模式
	m_PointerPB.SetCheck(1);
	m_XZoomPB.SetCheck(1);
	m_ChartViewer.setMouseUsage(Chart::MouseUsageScroll);
	m_ChartViewer.setZoomDirection(Chart::DirectionVertical); 
	m_ChartViewer.setScrollDirection(Chart::DirectionVertical);

	GetDlgItem(IDC_EDIT_LINEINTERVAL)->SetWindowText(_T("0.001"));
	GetDlgItem(IDC_EDIT_LINEZOOM)->SetWindowText(_T("1"));
	
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void C绘图程序Dlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void C绘图程序Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR C绘图程序Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}
// 将对话框及其控件设为尺寸可变的
void C绘图程序Dlg::OnSiteSizeBox(void)
{
	// 设置对话框为可变大小的
	ModifyStyle(0, WS_SIZEBOX);

	// 以对话框的初始大小作为对话框的宽度和高度的最小值
	CRect rectDlg;
	GetWindowRect(rectDlg);
	m_iMinWidth = rectDlg.Width();
	m_iMinHeight = rectDlg.Height();

	// 得到对话框client区域的大小 
	CRect rectClient;
	GetClientRect(rectClient);
	m_iClientWidth = rectClient.Width();
	m_iClientHeight = rectClient.Height();

	// Load图标
	m_bmpSizeIcon.LoadOEMBitmap(OBM_SIZE);
	m_bmpSizeIcon.GetBitmap(&m_bitmap);

	// 创建显示图标的静态控件并放在对话框右下角
	m_wndSizeIcon.Create(NULL, WS_CHILD | WS_VISIBLE | SS_BITMAP, CRect(0, 0, m_bitmap.bmWidth, m_bitmap.bmHeight), this, 0);
	m_wndSizeIcon.SetBitmap(m_bmpSizeIcon);
	m_wndSizeIcon.MoveWindow(m_iClientWidth - m_bitmap.bmWidth, m_iClientHeight - m_bitmap.bmHeight, m_bitmap.bmWidth, m_bitmap.bmHeight);

	// 显示图标
	m_wndSizeIcon.ShowWindow(m_bShowSizeIcon);
	static DLGCTLINFO dcMenuGroup[] = 
	{
		{IDC_STATIC_CONTROL, ELASTICY,	100},
		{IDC_STATIC_CONTROL, ELASTICX,	5},
		{IDC_STATIC_MOUSEMODE, ELASTICY, 20},
		{IDC_STATIC_MOUSEMODE, ELASTICX, 5},
		{IDC_PointerPB, MOVEY, 2},
		{IDC_PointerPB, ELASTICY, 5},
		{IDC_PointerPB, ELASTICX, 5},
		{IDC_ZoomInPB, MOVEY, 8},
		{IDC_ZoomInPB, ELASTICY, 5},
		{IDC_ZoomInPB, ELASTICX, 5},
		{IDC_ZoomOutPB, MOVEY, 14},
		{IDC_ZoomOutPB, ELASTICY, 5},
		{IDC_ZoomOutPB, ELASTICX, 5},
		{IDC_STATIC_ZOOMMODE, MOVEY, 25},
		{IDC_STATIC_ZOOMMODE, ELASTICY, 20},
		{IDC_STATIC_ZOOMMODE, ELASTICX, 5},
		{IDC_XZoomPB, MOVEY, 27},
		{IDC_XZoomPB, ELASTICY, 5},
		{IDC_XZoomPB, ELASTICX, 5},
		{IDC_YZoomPB, MOVEY, 33},
		{IDC_YZoomPB, ELASTICY, 5},
		{IDC_YZoomPB, ELASTICX, 5},
		{IDC_XYZoomPB, MOVEY, 39},
		{IDC_XYZoomPB, ELASTICY, 5},
		{IDC_XYZoomPB, ELASTICX, 5},
		{IDC_STATIC_GRAPHSHOWNUM, MOVEY, 44},
		{IDC_Duration, MOVEY, 46},
		{IDC_Duration, ELASTICX, 5},
		{IDC_BUTTON_OPENADCFILE, MOVEY, 48},
		{IDC_BUTTON_OPENADCFILE, ELASTICY, 5},
		{IDC_BUTTON_OPENADCFILE, ELASTICX, 5},
		{IDC_STATIC_LINEINTERVAL, MOVEY, 53},
		{IDC_STATIC_LINEINTERVAL, ELASTICY, 5},
		{IDC_STATIC_LINEINTERVAL, ELASTICX, 5},
		{IDC_EDIT_LINEINTERVAL, MOVEY, 53},
		{IDC_EDIT_LINEINTERVAL, ELASTICY, 0},
		{IDC_EDIT_LINEINTERVAL, ELASTICX, 5},
		{IDC_STATIC_LINEZOOM, MOVEY, 56},
		{IDC_STATIC_LINEZOOM, ELASTICY, 5},
		{IDC_STATIC_LINEZOOM, ELASTICX, 5},
		{IDC_EDIT_LINEZOOM, MOVEY, 56},
		{IDC_EDIT_LINEZOOM, ELASTICY, 0},
		{IDC_EDIT_LINEZOOM, ELASTICX, 5},
		{IDC_BUTTON_REDRAW, MOVEY, 61},
		{IDC_BUTTON_REDRAW, ELASTICY, 5},
		{IDC_BUTTON_REDRAW, ELASTICX, 5},
		{IDC_BUTTON_SAVECHART, MOVEY, 66},
		{IDC_BUTTON_SAVECHART, ELASTICY, 5},
		{IDC_BUTTON_SAVECHART, ELASTICX, 5},
		{IDC_HScrollBar, MOVEX, 5},
		{IDC_HScrollBar, MOVEY, 100},
		{IDC_HScrollBar, ELASTICX, 95},
		{IDC_VScrollBar, MOVEX, 100},
		{IDC_VScrollBar, MOVEY, 5},
		{IDC_VScrollBar, ELASTICY, 95},
	};
	// 设置控件信息
	SetControlProperty(dcMenuGroup, sizeof(dcMenuGroup)/sizeof(DLGCTLINFO));
}
// 载入一个图标资源到按钮
void C绘图程序Dlg::loadButtonIcon(int buttonId, int iconId, int width, int height)
{
	GetDlgItem(buttonId)->SendMessage(BM_SETIMAGE, IMAGE_ICON, (LPARAM)::LoadImage(
		AfxGetResourceHandle(), MAKEINTRESOURCE(iconId), IMAGE_ICON, width, height, 
		LR_DEFAULTCOLOR));  
}

// 得到默认的背景颜色
int C绘图程序Dlg::getDefaultBgColor(void)
{
	LOGBRUSH LogBrush; 
	HBRUSH hBrush = (HBRUSH)SendMessage(WM_CTLCOLORDLG, (WPARAM)CClientDC(this).m_hDC, 
		(LPARAM)m_hWnd); 
	::GetObject(hBrush, sizeof(LOGBRUSH), &LogBrush); 
	int ret = LogBrush.lbColor;
	return ((ret & 0xff) << 16) | (ret & 0xff00) | ((ret & 0xff0000) >> 16);
}

// 载入数据
BOOL C绘图程序Dlg::OnOpenFile(void)
{
	const wchar_t pszFilter[] = _T("文本文件(*.text)|*.text|文本文件(*.txt)|*.txt|All Files (*.*)|*.*||");
	CFileDialog dlg(TRUE, _T(".text"), _T("1.text"), OFN_HIDEREADONLY| OFN_OVERWRITEPROMPT, pszFilter, this);

	if ( dlg.DoModal()!=IDOK )
	{
		return FALSE;
	}
	m_csOpenFilePath=dlg.GetPathName();
	return LoadData(m_csOpenFilePath);
}

void C绘图程序Dlg::OnBnClickedPointerpb()
{
	// TODO: 在此添加控件通知处理程序代码
	 m_ChartViewer.setMouseUsage(Chart::MouseUsageScroll);
}

void C绘图程序Dlg::OnBnClickedZoominpb()
{
	// TODO: 在此添加控件通知处理程序代码
	m_ChartViewer.setMouseUsage(Chart::MouseUsageZoomIn);
}

void C绘图程序Dlg::OnBnClickedZoomoutpb()
{
	// TODO: 在此添加控件通知处理程序代码
	m_ChartViewer.setMouseUsage(Chart::MouseUsageZoomOut);
}

void C绘图程序Dlg::OnBnClickedXzoompb()
{
	// TODO: 在此添加控件通知处理程序代码
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

void C绘图程序Dlg::OnBnClickedXyzoompb()
{
	// TODO: 在此添加控件通知处理程序代码
	m_ChartViewer.setZoomDirection(Chart::DirectionHorizontalVertical); 
	m_ChartViewer.setScrollDirection(Chart::DirectionHorizontalVertical);  
}

void C绘图程序Dlg::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
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

void C绘图程序Dlg::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
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
void C绘图程序Dlg::OnViewPortChanged()
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
void C绘图程序Dlg::OnBnClickedChartViewer() 
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
double C绘图程序Dlg::moveScrollBar(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
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
void C绘图程序Dlg::validateDuration(const CString &text)
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
void C绘图程序Dlg::drawChart(CChartViewer *viewer)
{
	//
	// In this demo, we copy the visible part of the data to a separate buffer for chart
	// plotting. 
	//
	// Note that if you only have a small amount of data (a few hundred data points), it
	// may be easier to just plot all data in any case (so the following copying code is 
	// not needed), and let ChartDirector "clip" the chart to the plot area. 
	//

	// Using ViewPortLeft and ViewPortWidth, get the start and end dates of the view port.
	double viewPortStartDate = m_minData + (__int64)(viewer->getViewPortTop() * 
		m_dateRange + 0.5);
	double viewPortEndDate = viewPortStartDate + (__int64)(viewer->getViewPortHeight() * 
		m_dateRange + 0.5);

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
		str.Format(_T("FDU #%d"), i+1);
		int ansiCount = WideCharToMultiByte(CP_ACP, 0, str, -1, NULL, 0, NULL, NULL);
		char * pTempChar = (char*)malloc(ansiCount*sizeof(char));
		memset(pTempChar, 0, ansiCount);
		WideCharToMultiByte(CP_ACP, 0, str, -1, pTempChar, ansiCount, NULL, NULL);
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
 	// 输出绘图
// 	c->makeChart("Matrix428.bmp");

	// 释放资源
	delete[] viewPortTimeStamps;
}
//
// Update the image map
//
void C绘图程序Dlg::updateImageMap(CChartViewer *viewer)
{
	if (0 == viewer->getImageMapHandler())
	{
		// no existing image map - creates a new one
		viewer->setImageMap(viewer->getChart()->getHTMLImageMap("clickable", "",
			"title='[{dataSetName}] {x|1}: Volt {value|9}'"));
	}
}
void C绘图程序Dlg::OnCbnSelchangeDuration()
{
	// TODO: 在此添加控件通知处理程序代码
	// Get the selected duration
	CString text;
	m_Duration.GetLBText(m_Duration.GetCurSel(), text);

	// Validate and update the chart
	validateDuration(text);
}

void C绘图程序Dlg::OnCbnKillfocusDuration()
{
	// TODO: 在此添加控件通知处理程序代码
	// Get the duration text
	CString text;
	m_Duration.GetWindowText(text);

	// Validate and update the chart
	validateDuration(text);
}

void C绘图程序Dlg::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);

	// TODO: 在此处添加消息处理程序代码
	// 对话框宽度和高度的增量 
	int iIncrementX = cx - m_iClientWidth;
	int iIncrementY = cy - m_iClientHeight;

	// 最小化时增量为0
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

		// 无效值
		if ((iPercent < 0) || (iPercent > 100))
			continue;

		// 得到控件指针
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
			case MOVEX: // X方向移动
				iLeft += (iIncrementX * iPercent / 100);
				break;
			case MOVEY: // Y方向移动
				iTop += (iIncrementY * iPercent / 100);
				break;

			case MOVEXY: // X方向和Y方向同时移动
				iLeft += (iIncrementX * iPercent / 100);
				iTop += (iIncrementY * iPercent / 100);
				break;

			case ELASTICX: // X方向改变大小
				iWidth += (iIncrementX * iPercent / 100);
				break;

			case ELASTICY: // Y方向改变大小
				iHeight += (iIncrementY * iPercent / 100);
				break;

			case ELASTICXY: // X方向和Y方向同时改变大小
				iWidth += (iIncrementX * iPercent / 100);
				iHeight += (iIncrementY * iPercent / 100);
				break;

			default:
				;
			}

			// 把控件移动到新位置
			pWndCtrl->MoveWindow(iLeft, iTop, iWidth, iHeight);
		}
	}

	// 把图标移动到对话框右下角
	if (IsWindow(m_wndSizeIcon.GetSafeHwnd()))
		m_wndSizeIcon.MoveWindow(cx - m_bitmap.bmWidth, cy - m_bitmap.bmHeight, m_bitmap.bmWidth, m_bitmap.bmHeight);

	// 记录对话框client区域的大小
	if (nType != SIZE_MINIMIZED)
	{
		m_iClientWidth = cx;
		m_iClientHeight = cy;
	}
	// 重绘绘图区
	//
	// Update chart and image map if necessary
	//
	if (NULL != m_ChartViewer.getChart())
	{
//		drawChart(&m_ChartViewer);
		// 重绘绘图区
		m_ChartViewer.updateViewPort(true, false);
	}
	Invalidate(TRUE);//刷新界面
}

void C绘图程序Dlg::OnSizing(UINT fwSide, LPRECT pRect)
{
	CDialog::OnSizing(fwSide, pRect);

	// TODO: 在此处添加消息处理程序代码
	int iWidth = pRect->right - pRect->left;
	int iHeight = pRect->bottom - pRect->top;

	if (iWidth <= m_iMinWidth)
		pRect->right = pRect->left + m_iMinWidth;

	if(iHeight <= m_iMinHeight)
		pRect->bottom = pRect->top + m_iMinHeight;
}
BOOL C绘图程序Dlg::SetControlProperty(PDLGCTLINFO lp, int nElements)
{
	// 设置控件数组信息
	if (NULL == lp)
		return FALSE;

	if (nElements <= 0)
		return FALSE;

	m_pControlArray = lp;
	m_iControlNumber = nElements;
	return TRUE;
}

void C绘图程序Dlg::ShowSizeIcon(BOOL bShow /*=NULL*/)
{
	m_bShowSizeIcon = bShow;
}
void C绘图程序Dlg::OnBnClickedButtonSavechart()
{
	// TODO: 在此添加控件通知处理程序代码
	CString sPathName = _T("");
	const wchar_t pszFilter[] = _T("位图(*.bmp)|*.bmp||");
//	const char pszFilter[] = _T("位图(*.bmp)|*.bmp||");
	CFileDialog dlg(FALSE, _T(".bmp"), _T("Matrix428.bmp"),OFN_HIDEREADONLY| OFN_OVERWRITEPROMPT,pszFilter, this);

	if ( dlg.DoModal()!=IDOK )
		return;
	sPathName=dlg.GetPathName();
	if (NULL != m_ChartViewer.getChart())
	{
		//因为需要保存的内容包含中文，所以需要如下的转换过程
		int ansiCount = WideCharToMultiByte(CP_ACP, 0, sPathName, -1, NULL, 0, NULL, NULL);
		char * pTempChar = (char*)malloc(ansiCount*sizeof(char));
		memset(pTempChar, 0, ansiCount);
		WideCharToMultiByte(CP_ACP, 0, sPathName, -1, pTempChar, ansiCount, NULL, NULL);
		m_ChartViewer.getChart()->makeChart(pTempChar);
 		free(pTempChar);
	}
}

void C绘图程序Dlg::OnBnClickedButtonOpenadcfile()
{
	// TODO: 在此添加控件通知处理程序代码
	//
	// 初始化成员变量
	//
	// 得到默认背景颜色
	m_extBgColor = getDefaultBgColor();
	// Y轴范围
	m_minValue = m_maxValue = 0;

	if(FALSE == OnOpenFile())
	{
		return;
	}
	// 初始状态每条线显示的点数
	if (m_uiADCDataFduNum > ShowLinePointsNumNow)
	{
		m_currentDuration = ShowLinePointsNumNow;
	} 
	else
	{
		m_currentDuration = m_uiADCDataFduNum;
	}
	// 横坐标的最小值为m_timeStamps数组的第一个值
	m_minData = m_DrawPoint_X[0];
	m_maxData = m_DrawPoint_X[m_DrawPoint_X.size() - 1];

	// 横坐标取值的变化范围
	m_dateRange = m_maxData - m_minData;
	if (m_uiADCDataFduNum > ShowLinePointsNumMin)
	{
		m_minDuration = ShowLinePointsNumMin;
	}
	else
	{
		m_minDuration = m_uiADCDataFduNum;
	}

	// 绘图区域左侧间隔个数
	double maxData = 0.0;
	maxData = m_maxData;
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
	// 设置ChartViewer能反映有效且最小的持续时间
	m_ChartViewer.setZoomInHeightLimit(m_minDuration / m_dateRange);
	m_ChartViewer.setViewPortHeight(m_currentDuration / m_dateRange);
	m_ChartViewer.setViewPortTop(1 - m_ChartViewer.getViewPortHeight());

	// 重绘绘图区
	m_ChartViewer.updateViewPort(true, true);
}

// 从文件中载入数据
BOOL C绘图程序Dlg::LoadData(CString csOpenFilePath)
{
	if ((_taccess(csOpenFilePath,0))!=-1)
	{
		CFile file;
		if(file.Open(csOpenFilePath, CFile::modeRead) == FALSE)
		{
			AfxMessageBox(_T("打开数据采样文件出错！"));	
			return FALSE;
		}
		else
		{
			CString str = _T("");
			CArchive ar(&file, CArchive::load);
			// 初始化变量
			m_DrawPoint_X.clear();
			for (unsigned int i=0; i<m_uiInstrumentADCNum; i++)
			{
				m_dbFduData[i].clear();
				m_dbFduShow[i].clear();
			}
			delete[] m_dbFduData;
			delete[] m_dbFduShow;
			// 采集站设备总数
			m_uiInstrumentMaxNum = 0;
			// 参与ADC数据采集的采集站设备数
			m_uiInstrumentADCNum = 0;
			// ADC数据开始的数据点数
			m_uiADCStartNum = 0;
			// ADC数据转换格式
			m_uiADCDataCovNb = 0;
			// 采集站采集到的ADC数据总数
			m_uiADCDataNum = 0;
			// 每个采集站采集到的ADC数据个数
			m_uiADCDataFduNum = 0;
			// 读取文件中数据的行数
			m_uiADCFileLineNum = 0;
			// ADC数据采样开始时间
			ar.ReadString(str);
			// ADC数据采样信息
			ar.ReadString(str);
			_stscanf_s(str, _T("采集站设备总数%d，从第%d个数据开始存储ADC数据，数据转换方式采用方式%d！"), &m_uiInstrumentMaxNum, &m_uiADCStartNum, &m_uiADCDataCovNb);
			if (m_uiInstrumentMaxNum == 0)
			{
//				fp_str.close();
				ar.Close();
				file.Close();
				AfxMessageBox(_T("采集站设备总数为0！"));
				return FALSE;
			}
			// 采集站设备标签
			ar.ReadString(str);
			m_dbDataTemp = new double[m_uiInstrumentMaxNum];
			while(ar.ReadString(str))
			{
				OnPhraseFirstLine(str);
				m_uiADCFileLineNum++;
			}
			ar.Close();
			file.Close();

			m_uiADCDataFduNum = m_uiADCDataNum / m_uiInstrumentADCNum;
			m_uiADCDataNum = m_uiADCDataFduNum * m_uiInstrumentADCNum;
			for (unsigned int i=0; i<m_uiADCDataFduNum; i++)
			{
				m_DrawPoint_X.push_back(i + m_uiADCStartNum);
			}
			
			double dbLineInterval = 0.0;
			double dbLineZoom = 0.0;
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
	}
	else
	{
		return FALSE;
	}
}
// 解码一行ADC数据
void C绘图程序Dlg::OnPhraseFirstLine(CString str)
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
			// 第一行ADC数据，用于分析参与采集的站的个数
			if (m_uiADCFileLineNum == 0)
			{
				m_dbDataTemp[m_uiInstrumentADCNum] = _tstof(cstmp);
				m_uiInstrumentADCNum++;
			}
			else
			{
				m_dbFduData[m_uiADCDataNum%m_uiInstrumentADCNum].push_back(_tstof(cstmp));
			}
			m_uiADCDataNum++;
		}
	}
	if (m_uiADCFileLineNum == 0)
	{
		m_dbFduData = new vector<double>[m_uiInstrumentADCNum];
		m_dbFduShow = new vector<double>[m_uiInstrumentADCNum];
		for (unsigned int i=0; i<m_uiInstrumentADCNum; i++)
		{
			m_dbFduData[i].push_back(m_dbDataTemp[i]);
		}
		delete[] m_dbDataTemp;
	}
}

void C绘图程序Dlg::OnBnClickedYzoompb()
{
	// TODO: 在此添加控件通知处理程序代码
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

void C绘图程序Dlg::OnBnClickedButtonRedraw()
{
	// TODO: 在此添加控件通知处理程序代码
	CString str = _T("");
	double dbLineInterval = 0.0;
	double dbLineZoom = 0.0;
	// 判断是否有数据可以重绘
	if (m_dbFduData == NULL)
	{
		return;
	}
	// 禁用按键直到绘图重绘操作完成
	GetDlgItem(IDC_BUTTON_REDRAW)->EnableWindow(FALSE);
	// 得到界面设置值
	GetDlgItem(IDC_EDIT_LINEINTERVAL)->GetWindowText(str);
	dbLineInterval = _tstof(str);
	GetDlgItem(IDC_EDIT_LINEZOOM)->GetWindowText(str);
	dbLineZoom = _tstof(str);
	for (unsigned int i=0; i<m_uiInstrumentADCNum; i++)
	{
		for (unsigned int j=0; j<m_uiADCDataFduNum; j++)
		{
			m_dbFduShow[i][j] = m_dbFduData[i][j] * dbLineZoom + i * dbLineInterval;
		}
	}
	// 重绘绘图区
	m_ChartViewer.updateViewPort(true, true);

	GetDlgItem(IDC_BUTTON_REDRAW)->EnableWindow(TRUE);
}
