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
	ON_BN_CLICKED(IDC_RADIO_COLOR_SINGLE, &CDraw3DGraph_Test4Dlg::OnBnClickedRadioColorSingle)
	ON_BN_CLICKED(IDC_RADIO_COLOR_SPECTRUM, &CDraw3DGraph_Test4Dlg::OnBnClickedRadioColorSpectrum)
	ON_BN_CLICKED(IDC_RADIO_XYVIEW, &CDraw3DGraph_Test4Dlg::OnBnClickedRadioXyview)
	ON_BN_CLICKED(IDC_XZVIEW, &CDraw3DGraph_Test4Dlg::OnBnClickedXzview)
	ON_BN_CLICKED(IDC_RADIO_YZVIEW, &CDraw3DGraph_Test4Dlg::OnBnClickedRadioYzview)
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

	rectCtrl.top = rectWindow.bottom * 1 / 2;
	rectCtrl.bottom = rectWindow.bottom * 17 / 32;
	GetDlgItem(IDC_RADIO_COLOR_SINGLE)->MoveWindow(rectCtrl);

	rectCtrl.top = rectWindow.bottom * 9 / 16;
	rectCtrl.bottom = rectWindow.bottom * 19 / 32;
	GetDlgItem(IDC_RADIO_COLOR_SPECTRUM)->MoveWindow(rectCtrl);

	rectCtrl.top = rectWindow.bottom * 5 / 8;
	rectCtrl.bottom = rectWindow.bottom * 21 / 32;
	GetDlgItem(IDC_RADIO_XYVIEW)->MoveWindow(rectCtrl);

	rectCtrl.top = rectWindow.bottom * 11 / 16;
	rectCtrl.bottom = rectWindow.bottom * 23 / 32;
	GetDlgItem(IDC_RADIO_XZVIEW)->MoveWindow(rectCtrl);

	rectCtrl.top = rectWindow.bottom * 3 / 4;
	rectCtrl.bottom = rectWindow.bottom * 25 / 32;
	GetDlgItem(IDC_RADIO_YZVIEW)->MoveWindow(rectCtrl);

	OnInitGraph3D();
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
	OnInitCursor();
}
// ѡ��Ҫ�򿪵��ļ�
CString CDraw3DGraph_Test4Dlg::SelectOpenFile(void)
{
	CString strPath = _T("");
	CFileDialog hFileDlg(true,NULL ,
		NULL,
		OFN_FILEMUSTEXIST | OFN_READONLY | OFN_PATHMUSTEXIST,
		TEXT("�����ļ� (*.text)|*.text|*.txt|�����ļ�(*.*)|*.*"),
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
	unsigned int uiCurveRowNum = 0;
	unsigned int uiCurveColumnNum = 0;
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
	uiRowNum = m_uiTraceNume / ColumnNum;  //22=445/20
	m_xRow.SetSize(uiRowNum);           //X������
	uiCurveRowNum = uiRowNum * (InterpolateRowNum + 1) - InterpolateRowNum;//211=22*(9+1)-9
	m_xCurveRow.SetSize(uiCurveRowNum); //��ֵ�����x������
	m_dtRow.SetSize(uiRowNum);          //x�᷽����������
	m_zAmpRowTemp.SetSize(uiRowNum);    //X�᷽�����������ʱ����
	for (unsigned int i=0; i<uiRowNum; i++)
	{
		m_xRow[i] = i + 1;
	}
	for (unsigned int i=0; i<uiCurveRowNum; i++)
	{
		m_xCurveRow[i] = 1.0 / (InterpolateRowNum + 1) * i + 1;
	}
	m_yColumn.SetSize(ColumnNum);
	uiCurveColumnNum = ColumnNum * (InterpolateColumnNum + 1) - InterpolateColumnNum;
	m_yCurveColumn.SetSize(uiCurveColumnNum);
	m_dtColumn.SetSize(ColumnNum);
	m_zAmpColumnTemp.SetSize(ColumnNum);
	for (unsigned int i=0; i<ColumnNum; i++)
	{
		m_yColumn[i] = i + 1;
	}
	for (unsigned int i=0; i<uiCurveColumnNum; i++)
	{
		m_yCurveColumn[i] = 1.0 / (InterpolateColumnNum + 1) * i + 1;
	}
	m_zAmpData.SetSize(uiRowNum, ColumnNum);                 //��������
	m_zCurveAmpData.SetSize(uiCurveRowNum, uiCurveColumnNum);//��ֵ�����Z������
	for (unsigned int i=0; i< uiRowNum; i++)
	{
		for (unsigned int j = 0; j< ColumnNum; j++)
		{
			m_zAmpData(i, j) = 0.0;
		}
	}
	m_bOpenFile = true;
}  
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
			if (uiCounter < (m_uiTraceNume / ColumnNum) * ColumnNum)//�����ݴ���20*22�Ļ�����,ֻȡ440������
			{
				m_zAmpData(uiCounter / ColumnNum, uiCounter % ColumnNum) = iTemp;
			}
			uiCounter ++;
		}
		m_fin.seekg(2, ios::cur);
		m_uiTimeCount++;
		m_iOff = m_fin.tellg();
		// �Ȱ������ֵ
		for (unsigned int j=0; j<ColumnNum; j++)
		{
			for (unsigned int i=0; i<m_uiTraceNume / ColumnNum; i++)
			{
				m_zAmpRowTemp[i] = m_zAmpData(i, j);
			}
			CNiMath::Spline(m_xRow, m_zAmpRowTemp, 1, 1, m_dtRow);//��б��
			for (unsigned int i=0; i<m_xCurveRow.GetSize(); i++)
			{
				CNiMath::InterpolateSpline(m_xRow, m_zAmpRowTemp, m_dtRow, m_xCurveRow[i], m_zCurveAmpData(i, j * (InterpolateColumnNum + 1)));//
			}
		}
 		// �������ֵ
		for (unsigned int i=0; i<m_xCurveRow.GetSize(); i++)
		{
			for (unsigned int j=0; j<ColumnNum; j++)
			{
				m_zAmpColumnTemp[j] = m_zCurveAmpData(i, j * (InterpolateColumnNum + 1));
			}
			CNiMath::Spline(m_yColumn, m_zAmpColumnTemp, 1, 1, m_dtColumn);
			for (unsigned int j=0; j<m_yCurveColumn.GetSize(); j++)
			{
				CNiMath::InterpolateSpline(m_yColumn, m_zAmpColumnTemp, m_dtColumn, m_yCurveColumn[j], m_zCurveAmpData(i, j));
			}
		}

		m_ctrlGraph3D.GetPlots().Item(1).Plot3DSurface(m_xCurveRow, m_yCurveColumn, m_zCurveAmpData);
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

// ��ʼ�����
void CDraw3DGraph_Test4Dlg::OnInitCursor(void)
{
	m_ctrlGraph3D.Cursors.RemoveAll();
	m_Cursor = m_ctrlGraph3D.Cursors.Add();
	m_Cursor.Name = _T("Cursor 1");
	m_Cursor.Enabled = true;
	m_Cursor.Visible = true;
	m_Cursor.NameVisible = true;
	m_Cursor.TextColor = CNiColor(0, 0, 0);

	m_Cursor.XPosition = 5.0;
	m_Cursor.YPosition = 5.0;
	m_Cursor.ZPosition = 5.0;
	m_Cursor.PositionVisible = true;
	m_Cursor.SnapMode = CNiCursor3D::SnapNearestPlot;

	m_Cursor.PointSize = 10.0;
	m_Cursor.PointColor = CNiColor(0, 0, 128);
	m_Cursor.PointStyle = CNiCursor3D::Asterisk;

	m_Cursor.LineWidth = 1.0;
	m_Cursor.LineColor = CNiColor(255, 0, 0);
	m_Cursor.LineStyle = CNiCursor3D::LineSolid;

	m_Cursor.Transparency = 75;
	m_Cursor.PlaneColor = CNiColor(0, 128, 0);
	m_Cursor.XYPlaneVisible = false;
	m_Cursor.XZPlaneVisible = false;
	m_Cursor.YZPlaneVisible = false;
}

// ��ʼ����ͼ�ؼ�
void CDraw3DGraph_Test4Dlg::OnInitGraph3D(void)
{
	m_ctrlGraph3D.FastDraw = true;
	m_ctrlGraph3D.SetPlotAreaColor(RGB(128, 128, 128));
	// 	m_ctrlGraph3D.SetCaptionColor(RGB(213, 43, 213));
	// 	m_ctrlGraph3D.SetGridFrameColor(RGB(128, 0, 0));
	//	m_ctrlGraph3D.SetPlotAreaColor(RGB(0, 128, 0));
	/*m_ctrlGraph3D.GetPlots().Item(1).SetProjectionYZ(TRUE);*/

	m_ctrlGraph3D.GetPlots().Item(1).SetFillColor(RGB(0, 0, 0));
	//	m_ctrlGraph3D.Plots.Item(1).ColorMapStyle = CNiPlot3D::None;
	m_ctrlGraph3D.Plots.Item(1).ColorMapStyle = CNiPlot3D::ColorSpectrum;
	m_ctrlGraph3D.GetPlots().Item(1).SetLineColor(RGB(0, 191, 255));
	m_ctrlGraph3D.GetPlots().Item(1).SetStyle(CNiPlot3D::SurfaceLine);
	/*	m_ctrlGraph3D.GetPlots().Item(1).SetStyle(CNiPlot3D::SurfaceContour);*/

//	m_ctrlGraph3D.SetViewMode(CNiGraph3D::ViewXYPlane);
	OnInitAxis3D();
}

// ��ʼ��3D������
void CDraw3DGraph_Test4Dlg::OnInitAxis3D(void)
{
	m_Axis3D = m_ctrlGraph3D.GetAxes().Item(1);
	m_Axis3D.SetCaption(_T("Row"));
	m_Axis3D.SetCaptionColor(RGB(255, 0, 0));
	m_Axis3D = m_ctrlGraph3D.GetAxes().Item(2);
	m_Axis3D.SetCaption(_T("Column"));
	m_Axis3D.SetCaptionColor(RGB(255, 0, 0));
// 	m_Axis3D.GetLabels().SetOpposite(true);
// 	m_Axis3D.GetLabels().SetNormal(false);
// 	m_Axis3D.SetCaptionOpposite(true);
// 	m_Axis3D.SetCaptionNormal(false);
	m_Axis3D = m_ctrlGraph3D.GetAxes().Item(3);
	m_Axis3D.SetMinMax(SampleAmpMin, SampleAmpMax);
	m_Axis3D.SetCaption(_T("Amp"));
	m_Axis3D.SetCaptionColor(RGB(255, 0, 0));
}

void CDraw3DGraph_Test4Dlg::OnBnClickedRadioColorSingle()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_ctrlGraph3D.Plots.Item(1).ColorMapStyle = CNiPlot3D::None;
	m_ctrlGraph3D.GetPlots().Item(1).SetLineColor(RGB(0, 255, 0));
	((CButton*)GetDlgItem(IDC_RADIO_COLOR_SINGLE))->SetCheck(1); 
	((CButton*)GetDlgItem(IDC_RADIO_COLOR_SPECTRUM))->SetCheck(0); 
}

void CDraw3DGraph_Test4Dlg::OnBnClickedRadioColorSpectrum()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_ctrlGraph3D.Plots.Item(1).ColorMapStyle = CNiPlot3D::ColorSpectrum;
	m_ctrlGraph3D.GetPlots().Item(1).SetLineColor(RGB(0, 191, 255));
	((CButton*)GetDlgItem(IDC_RADIO_COLOR_SINGLE))->SetCheck(0); 
	((CButton*)GetDlgItem(IDC_RADIO_COLOR_SPECTRUM))->SetCheck(1); 
}

void CDraw3DGraph_Test4Dlg::OnBnClickedRadioXyview()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	((CButton*)GetDlgItem(IDC_RADIO_XYVIEW))->SetCheck(1);
	((CButton*)GetDlgItem(IDC_RADIO_YZVIEW))->SetCheck(0);
	((CButton*)GetDlgItem(IDC_RADIO_XZVIEW))->SetCheck(0);
	m_ctrlGraph3D.SetViewMode(CNiGraph3D::ViewXYPlane);
}

void CDraw3DGraph_Test4Dlg::OnBnClickedXzview()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	((CButton*)GetDlgItem(IDC_RADIO_XYVIEW))->SetCheck(0);
	((CButton*)GetDlgItem(IDC_RADIO_YZVIEW))->SetCheck(0);
	((CButton*)GetDlgItem(IDC_RADIO_XZVIEW))->SetCheck(1);
	m_ctrlGraph3D.SetViewMode(CNiGraph3D::ViewXZPlane);
}

void CDraw3DGraph_Test4Dlg::OnBnClickedRadioYzview()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	((CButton*)GetDlgItem(IDC_RADIO_XYVIEW))->SetCheck(0);
	((CButton*)GetDlgItem(IDC_RADIO_YZVIEW))->SetCheck(1);
	((CButton*)GetDlgItem(IDC_RADIO_XZVIEW))->SetCheck(0);
	m_ctrlGraph3D.SetViewMode(CNiGraph3D::ViewYZPlane);
}
