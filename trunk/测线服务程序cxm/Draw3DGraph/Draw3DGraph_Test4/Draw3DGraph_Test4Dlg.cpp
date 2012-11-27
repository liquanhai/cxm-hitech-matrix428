// Draw3DGraph_Test4Dlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Draw3DGraph_Test4.h"
#include "Draw3DGraph_Test4Dlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


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


// CDraw3DGraph_Test4Dlg �Ի���




CDraw3DGraph_Test4Dlg::CDraw3DGraph_Test4Dlg(CWnd* pParent /*=NULL*/)
	: CDialog(CDraw3DGraph_Test4Dlg::IDD, pParent)
	, m_strFilePath(_T(""))
	, m_uiTraceNume(0)
	, m_iOff(0)
	, m_bOpenFile(false)
	, m_uiTimeCount(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CDraw3DGraph_Test4Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CWGRAPH3D1, m_ctrlGraph3D);
	DDX_Control(pDX, IDC_BTN_START, m_ctrlBtnStart);
	DDX_Control(pDX, IDC_BTN_STOP, m_ctrlBtnStop);
	DDX_Control(pDX, IDC_BTN_SELECTFILE, m_ctrlBtnSelectFile);
}

BEGIN_MESSAGE_MAP(CDraw3DGraph_Test4Dlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_BTN_START, &CDraw3DGraph_Test4Dlg::OnBnClickedBtnStart)
	ON_BN_CLICKED(IDC_BTN_STOP, &CDraw3DGraph_Test4Dlg::OnBnClickedBtnStop)
	ON_BN_CLICKED(IDC_BTN_SELECTFILE, &CDraw3DGraph_Test4Dlg::OnBnClickedBtnSelectfile)
	ON_WM_TIMER()
	ON_WM_DESTROY()
END_MESSAGE_MAP()


// CDraw3DGraph_Test4Dlg ��Ϣ�������

BOOL CDraw3DGraph_Test4Dlg::OnInitDialog()
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
	ShowWindow(SW_SHOWMAXIMIZED);
	CRect rectWindow, rectCtrl;
	GetWindowRect(&rectWindow);
	rectCtrl = rectWindow;
	rectCtrl.right = rectWindow.right * 4 / 5;
	m_ctrlGraph3D.MoveWindow(rectCtrl);

	rectCtrl.left = rectWindow.right * 33 / 40;
	rectCtrl.right = rectWindow.right * 39 / 40;
	rectCtrl.top = rectWindow.bottom / 8;
	rectCtrl.bottom = rectWindow.bottom * 3 / 16;
	m_ctrlBtnStart.MoveWindow(rectCtrl);

	rectCtrl.top = rectWindow.bottom / 4;
	rectCtrl.bottom = rectWindow.bottom * 5 / 16;
	m_ctrlBtnStop.MoveWindow(rectCtrl);

	rectCtrl.top = rectWindow.bottom * 3 / 8;
	rectCtrl.bottom = rectWindow.bottom * 7 / 16;
	m_ctrlBtnSelectFile.MoveWindow(rectCtrl);

//	m_xTimeData.SetSize(SampleTime);

	m_ctrlGraph3D.SetPlotAreaColor(RGB(128, 128, 128));
	/*m_ctrlGraph3D.GetPlots().Item(1).SetProjectionYZ(TRUE);*/
	m_ctrlGraph3D.GetPlots().Item(1).SetFillColor(RGB(0, 0, 0));
	m_ctrlGraph3D.Plots.Item(1).ColorMapStyle = CNiPlot3D::None;
	m_Axis3D = m_ctrlGraph3D.GetAxes().Item(1);
	m_Axis3D.SetCaption(_T("Row"));
	m_Axis3D.SetCaptionColor(RGB(255, 0, 0));
	m_Axis3D = m_ctrlGraph3D.GetAxes().Item(2);
	m_Axis3D.SetCaption(_T("Column"));
	m_Axis3D.SetCaptionColor(RGB(255, 0, 0));
	m_Axis3D.GetLabels().SetOpposite(true);
	m_Axis3D.GetLabels().SetNormal(false);
	m_Axis3D.SetCaptionOpposite(true);
	m_Axis3D.SetCaptionNormal(false);
	m_Axis3D = m_ctrlGraph3D.GetAxes().Item(3);
	m_Axis3D.SetMinMax(SampleAmpMin, SampleAmpMax);
	m_Axis3D.SetCaption(_T("Amp"));
	m_Axis3D.SetCaptionColor(RGB(255, 0, 0));
	m_ctrlGraph3D.SetCaptionColor(RGB(213, 43, 213));
	m_ctrlGraph3D.SetGridFrameColor(RGB(128, 0, 0));
	//	m_ctrlGraph3D.SetPlotAreaColor(RGB(0, 128, 0));
	m_ctrlGraph3D.GetPlots().Item(1).SetLineColor(RGB(0, 255, 0));
	m_ctrlGraph3D.GetPlots().Item(1).SetStyle(CNiPlot3D::SurfaceLine);
//	m_ctrlGraph3D.GetPlots().Item(1).SetStyle(CNiPlot3D::HiddenLine);

	m_ctrlBtnStart.EnableWindow(FALSE);
	m_ctrlBtnStop.EnableWindow(FALSE);
	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CDraw3DGraph_Test4Dlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CDraw3DGraph_Test4Dlg::OnPaint()
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
HCURSOR CDraw3DGraph_Test4Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CDraw3DGraph_Test4Dlg::OnBnClickedBtnStart()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if (m_bOpenFile == false)
	{
		return;
	}
	SetTimer(TimerID, TimerDelay, NULL);
}

void CDraw3DGraph_Test4Dlg::OnBnClickedBtnStop()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if (m_bOpenFile == false)
	{
		return;
	}
	KillTimer(TimerID);
}
// ѡ��Ҫ�򿪵��ļ�
CString CDraw3DGraph_Test4Dlg::SelectOpenFile(void)
{
	CString strPath = _T("");
	CFileDialog hFileDlg(true,NULL ,
		NULL,
		OFN_FILEMUSTEXIST | OFN_READONLY | OFN_PATHMUSTEXIST,
		TEXT("�����ļ� (*.text)|*.text|*.txt|�����ļ�(*.*)|*.*|"),
		NULL);
	if(hFileDlg.DoModal() == IDOK)
	{
		strPath = hFileDlg.GetPathName();
	}
	return strPath;
}
void CDraw3DGraph_Test4Dlg::OnBnClickedBtnSelectfile()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_ctrlBtnStart.EnableWindow(FALSE);
	m_ctrlBtnStop.EnableWindow(FALSE);
	m_strFilePath = SelectOpenFile();
	if (m_strFilePath == _T(""))
	{
		AfxMessageBox(_T("��ѡ�������ļ���"));
		return;
	}
	m_ctrlBtnStart.EnableWindow(TRUE);
	m_ctrlBtnStop.EnableWindow(TRUE);
	if (m_fin.is_open())
	{
		m_fin.close();
	}
	string str = "";
	char data[10];
	unsigned int uiRowNum = 0;
	m_uiTraceNume = 0;
	m_iOff = 0;
	m_bOpenFile = false;
	m_uiTimeCount = 0;

	m_fin.open(m_strFilePath, ios::_Nocreate);
	getline(m_fin, str, '\n');
	getline(m_fin, str, '\n');
	getline(m_fin, str, '\n');
	m_iOff = m_fin.tellg();
	m_fin.seekg(FrameTimeBytesNume + m_iOff, ios::beg);
	while(1)
	{
		if (m_fin.peek() == 0x0a)
		{
			break;
		}
		m_fin.read(data, DataBytesNum);
		m_uiTraceNume++;
	}
	uiRowNum = m_uiTraceNume / ColumnNum;
	m_xRow.SetSize(uiRowNum);
	for (unsigned int i=0; i<uiRowNum; i++)
	{
		m_xRow[i] = i + 1;
	}
	m_yColumn.SetSize(ColumnNum);
	for (unsigned int i=0; i<ColumnNum; i++)
	{
		m_yColumn[i] = i + 1;
	}
	m_zAmpData.SetSize(uiRowNum, ColumnNum);
	for (unsigned int i=0; i< uiRowNum; i++)
	{
		for (unsigned int j = 0; j< ColumnNum; j++)
		{
			m_zAmpData(i, j) = 0.0;
		}
	}
	m_bOpenFile = true;
}
void CDraw3DGraph_Test4Dlg::CreateCurve(CNiReal64Vector vSrc, CNiReal64Vector vDst)
{  
	// ���Ƶ�����ϵ�� ��������0.6�Ϻã�CvPoint��opencv�ģ������ж���ṹ��(x,y)
	double scale = 0.6;
	int iSrcSize = vSrc.GetSize();
	if (iSrcSize < 2)
	{
		return;
	}
	int iMidPointSize = iSrcSize - 1;
	CNiReal64Vector vMidPoints;
	vMidPoints.SetSize(iMidPointSize);
	// �����е�
	// @@@���ҵ�Ӧ�������𣬲�����β���ӵ��ߣ�����һ���ĸĶ�
	for(int i = 0; i < iMidPointSize; i++)
	{
		int nexti = (i + 1) % iSrcSize;
		vMidPoints[i] = (vSrc[i] + vSrc[nexti]) / 2.0;
	}
	//ƽ���е�
	CNiReal64Vector vExtraPoints;
	vExtraPoints.SetSize(2 * (iMidPointSize - 1));
// 	14.    for(int i = 0 ;i < originCount ; i++){  
// 		15.         int nexti = (i + 1) % originCount;  
// 		16.         int backi = (i + originCount - 1) % originCount;  
// 		17.         CvPoint midinmid;  
// 		18.         midinmid.x = (midpoints[i].x + midpoints[backi].x)/2.0;  
// 		19.         midinmid.y = (midpoints[i].y + midpoints[backi].y)/2.0;  
// 		20.         int offsetx = originPoint[i].x - midinmid.x;  
// 		21.         int offsety = originPoint[i].y - midinmid.y;  
// 		22.         int extraindex = 2 * i;  
// 		23.         extrapoints[extraindex].x = midpoints[backi].x + offsetx;  
// 		24.         extrapoints[extraindex].y = midpoints[backi].y + offsety;  
// 		25.         //�� originPoint[i]��������   
// 			26.         int addx = (extrapoints[extraindex].x - originPoint[i].x) * scale;  
// 		27.         int addy = (extrapoints[extraindex].y - originPoint[i].y) * scale;  
// 		28.         extrapoints[extraindex].x = originPoint[i].x + addx;  
// 		29.         extrapoints[extraindex].y = originPoint[i].y + addy;  
// 		30.           
// 			31.         int extranexti = (extraindex + 1)%(2 * originCount);  
// 		32.         extrapoints[extranexti].x = midpoints[i].x + offsetx;  
// 		33.         extrapoints[extranexti].y = midpoints[i].y + offsety;  
// 		34.         //�� originPoint[i]��������   
// 			35.         addx = (extrapoints[extranexti].x - originPoint[i].x) * scale;  
// 		36.         addy = (extrapoints[extranexti].y - originPoint[i].y) * scale;  
// 		37.         extrapoints[extranexti].x = originPoint[i].x + addx;  
// 		38.         extrapoints[extranexti].y = originPoint[i].y + addy;  
// 		39.           
// 			40.    }      
// 	41.      
// 		42.    CvPoint controlPoint[4];  
// 	43.    //����4���Ƶ㣬��������������  
// 		44.    for(int i = 0 ;i < originCount ; i++){  
// 			45.           controlPoint[0] = originPoint[i];  
// 			46.           int extraindex = 2 * i;  
// 			47.           controlPoint[1] = extrapoints[extraindex + 1];  
// 			48.           int extranexti = (extraindex + 2) % (2 * originCount);  
// 			49.           controlPoint[2] = extrapoints[extranexti];  
// 			50.           int nexti = (i + 1) % originCount;  
// 			51.           controlPoint[3] = originPoint[nexti];      
// 			52.           float u = 1;  
// 			53.           while(u >= 0){  
// 				54.               int px = bezier3funcX(u,controlPoint);  
// 				55.               int py = bezier3funcY(u,controlPoint);  
// 				56.               //u�Ĳ����������ߵ�����  
// 					57.               u -= 0.005;  
// 				58.               CvPoint tempP = cvPoint(px,py);  
// 				59.               //�������ߵ�   
// 					60.               curvePoint.push_back(tempP);  
// 				61.           }      
// 			62.    }  
}  
//���α���������  
// 66.float bezier3funcX(float uu,CvPoint *controlP){  
// 	67.   float part0 = controlP[0].x * uu * uu * uu;  
// 	68.   float part1 = 3 * controlP[1].x * uu * uu * (1 - uu);  
// 	69.   float part2 = 3 * controlP[2].x * uu * (1 - uu) * (1 - uu);  
// 	70.   float part3 = controlP[3].x * (1 - uu) * (1 - uu) * (1 - uu);     
// 	71.   return part0 + part1 + part2 + part3;   
// 	72.}      
// 73.  
// 74.float bezier3funcY(float uu,CvPoint *controlP){  
// 	75.   float part0 = controlP[0].y * uu * uu * uu;  
// 	76.   float part1 = 3 * controlP[1].y * uu * uu * (1 - uu);  
// 	77.   float part2 = 3 * controlP[2].y * uu * (1 - uu) * (1 - uu);  
// 	78.   float part3 = controlP[3].y * (1 - uu) * (1 - uu) * (1 - uu);     
// 	79.   return part0 + part1 + part2 + part3;   
// 	80.}   
void CDraw3DGraph_Test4Dlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	if (nIDEvent == TimerID)
	{
		CString s = _T("");
		char data[10];
		unsigned int uiCounter = 0;
		int iTemp = 0;
		if (m_uiTimeCount % 72 == 0)
		{
			m_fin.seekg(FrameTimeBytesNume + m_iOff, ios::beg);
		}
		while(1)
		{
			if (m_fin.peek() == 0x0a)
			{
				break;
			}
			m_fin.read(data, DataBytesNum);
			if (m_fin.fail() == true)
			{
				break;
			}
			s = data;
			sscanf_s(s, _T("%8d /t"), &iTemp);
			if (iTemp > 10000)
			{
				iTemp = 0;
			}
			else if (iTemp < -10000)
			{
				iTemp = 0;
			}
			if (uiCounter < (m_uiTraceNume / ColumnNum) * ColumnNum)
			{
				m_zAmpData(uiCounter / ColumnNum, uiCounter % ColumnNum) = iTemp;
			}
			uiCounter ++;
		}
		m_fin.seekg(2, ios::cur);
		m_uiTimeCount++;
		m_iOff = m_fin.tellg();

		m_ctrlGraph3D.GetPlots().Item(1).Plot3DSurface(m_xRow, m_yColumn, m_zAmpData);
	}
	CDialog::OnTimer(nIDEvent);
}

void CDraw3DGraph_Test4Dlg::OnDestroy()
{
	CDialog::OnDestroy();

	// TODO: �ڴ˴������Ϣ����������
	if (m_fin.is_open())
	{
		m_fin.close();
	}
}
