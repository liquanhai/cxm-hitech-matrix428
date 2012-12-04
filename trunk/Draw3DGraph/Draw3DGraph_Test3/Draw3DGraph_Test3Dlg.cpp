// Draw3DGraph_Test3Dlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Draw3DGraph_Test3.h"
#include "Draw3DGraph_Test3Dlg.h"

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


// CDraw3DGraph_Test3Dlg �Ի���




CDraw3DGraph_Test3Dlg::CDraw3DGraph_Test3Dlg(CWnd* pParent /*=NULL*/)
	: CDialog(CDraw3DGraph_Test3Dlg::IDD, pParent)
	, m_strFilePath(_T(""))
	, m_uiTraceNume(0)
	, m_iOff(0)
	, m_bOpenFile(false)
	, m_uiTimeCount(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CDraw3DGraph_Test3Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BTN_SELECTFILE, m_ctrlBtnSelectFile);
	DDX_Control(pDX, IDC_CWGRAPH3D1, m_ctrlGraph3D);
	DDX_Control(pDX, IDC_BTN_START, m_ctrlBtnStart);
	DDX_Control(pDX, IDC_BTN_STOP, m_ctrlBtnStop);
}

BEGIN_MESSAGE_MAP(CDraw3DGraph_Test3Dlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_BTN_SELECTFILE, &CDraw3DGraph_Test3Dlg::OnBnClickedBtnSelectfile)
	ON_BN_CLICKED(IDC_BTN_START, &CDraw3DGraph_Test3Dlg::OnBnClickedBtnStart)
	ON_BN_CLICKED(IDC_BTN_STOP, &CDraw3DGraph_Test3Dlg::OnBnClickedBtnStop)
	ON_BN_CLICKED(IDC_RADIO_SURFACE, &CDraw3DGraph_Test3Dlg::OnBnClickedRadioSurface)
	ON_BN_CLICKED(IDC_RADIO_SURFACELINE, &CDraw3DGraph_Test3Dlg::OnBnClickedRadioSurfaceline)
	ON_WM_TIMER()
	ON_WM_DESTROY()
END_MESSAGE_MAP()


// CDraw3DGraph_Test3Dlg ��Ϣ�������

BOOL CDraw3DGraph_Test3Dlg::OnInitDialog()
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
	rectCtrl.bottom = rectWindow.bottom * 13 / 32;
	GetDlgItem(IDC_RADIO_SURFACE)->MoveWindow(rectCtrl);

	rectCtrl.top = rectWindow.bottom * 7 / 16;
	rectCtrl.bottom = rectWindow.bottom * 15 / 32;
	GetDlgItem(IDC_RADIO_SURFACELINE)->MoveWindow(rectCtrl);

	rectCtrl.top = rectWindow.bottom * 1 / 2;
	rectCtrl.bottom = rectWindow.bottom * 9 / 16;
	m_ctrlBtnSelectFile.MoveWindow(rectCtrl);

	m_xTimeData.SetSize(SampleTime);

	m_ctrlGraph3D.SetPlotAreaColor(RGB(128, 128, 128));
	/*m_ctrlGraph3D.GetPlots().Item(1).SetProjectionYZ(TRUE);*/
	m_ctrlGraph3D.GetPlots().Item(1).SetFillColor(RGB(0, 0, 0));
	m_ctrlGraph3D.Plots.Item(1).ColorMapStyle = CNiPlot3D::None;
	m_Axis3D = m_ctrlGraph3D.GetAxes().Item(1);
	m_Axis3D.SetCaption(_T("Time"));
	m_Axis3D.SetCaptionColor(RGB(255, 0, 0));
	m_Axis3D = m_ctrlGraph3D.GetAxes().Item(2);
	m_Axis3D.SetCaption(_T("Trace"));
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


	m_ctrlBtnStart.EnableWindow(FALSE);
	m_ctrlBtnStop.EnableWindow(FALSE);
	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CDraw3DGraph_Test3Dlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CDraw3DGraph_Test3Dlg::OnPaint()
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
HCURSOR CDraw3DGraph_Test3Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


// ѡ��Ҫ�򿪵��ļ�
CString CDraw3DGraph_Test3Dlg::SelectOpenFile(void)
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
void CDraw3DGraph_Test3Dlg::OnBnClickedBtnSelectfile()
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
	m_uiTraceNume = 0;
	m_iOff = 0;
	m_bOpenFile = false;
	m_uiTimeCount = 0;
	char temp = 9;
	m_fin.open(m_strFilePath, ios::_Nocreate);
	getline(m_fin, str, '\n');
	getline(m_fin, str, '\n');
	getline(m_fin, str, '\n');
	m_iOff = m_fin.tellg();
	
	m_fin.read(data, 3);
	while(temp != m_fin.peek())
	{
		m_fin.seekg(1, ios::cur);
	}
	m_fin.seekg(1, ios::cur);
	while(1)
	{
		if (m_fin.peek() == 0x0a)
		{
			break;
		}
		m_fin.read(data, DataBytesNum);
		m_uiTraceNume++;
	}
	m_yTraceData.SetSize(m_uiTraceNume);
	for (unsigned int i=0; i<m_uiTraceNume; i++)
	{
		m_yTraceData[i] = i;
	}
	m_zAmpData.SetSize(SampleTime, m_uiTraceNume);
	for (unsigned int i=0; i< SampleTime; i++)
	{
		for (unsigned int j = 0; j< m_uiTraceNume; j++)
		{
			m_zAmpData(i, j) = 0.0;
		}
	}
	m_bOpenFile = true;

// 	while(1)
// 	{
// 		if ((iCount % 445 == 0) && (iCount > 0))
// 		{
// 			m_fin.seekg(2, ios::cur);
// 		}
// 		if (iCount % (445 * 72) == 0)
// 		{
// 			m_fin.seekg(13, ios::cur);
// 		}
// 		m_fin.read(data, 10);
// 		if (m_fin.fail() == true)
// 		{
// 			break;
// 		}
// 		s = data;
// 		sscanf_s(s, _T("%8d /t"), &i);
// 		iCount ++;
// 	}
}

void CDraw3DGraph_Test3Dlg::OnBnClickedBtnStart()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if (m_bOpenFile == false)
	{
		return;
	}
	SetTimer(TimerID, TimerDelay, NULL);
}

void CDraw3DGraph_Test3Dlg::OnBnClickedBtnStop()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if (m_bOpenFile == false)
	{
		return;
	}
	KillTimer(TimerID);
}

void CDraw3DGraph_Test3Dlg::OnBnClickedRadioSurface()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if (m_bOpenFile == false)
	{
		return;
	}
	m_ctrlGraph3D.GetPlots().Item(1).SetStyle(CNiPlot3D::Surface);
}

void CDraw3DGraph_Test3Dlg::OnBnClickedRadioSurfaceline()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if (m_bOpenFile == false)
	{
		return;
	}
	m_ctrlGraph3D.GetPlots().Item(1).SetLineColor(RGB(0, 255, 0));
	m_ctrlGraph3D.GetPlots().Item(1).SetStyle(CNiPlot3D::SurfaceLine);
}

void CDraw3DGraph_Test3Dlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	if (nIDEvent == TimerID)
	{
		CString s = _T("");
		char data[10];
		unsigned int uiCounter = 0;
		unsigned int x = 0;
		// �����Ʊ��Ϊ9
		char temp = 9;
		int iTemp = 0;
		if (m_uiTimeCount < SampleTime)
		{
			x = m_uiTimeCount;
			for (int i = 0; i < SampleTime; i++)
			{
				m_xTimeData[i] = i;
			}
		}
		else
		{
			x = SampleTime - 1;
			for (unsigned int i = 0; i < SampleTime; i++)
			{
				m_xTimeData[i] = i + m_uiTimeCount - SampleTime + 1;
			}
			for (unsigned int i = 1; i < SampleTime; i++)
			{
				for (unsigned int j = 0; j < m_uiTraceNume; j++)
				{
					m_zAmpData(i-1, j) = m_zAmpData(i, j);
				}
			}
 			m_Axis3D = m_ctrlGraph3D.GetAxes().Item(1);
 			m_Axis3D.SetMinMax(m_xTimeData[0], m_xTimeData[SampleTime - 1]);
		}
		if (m_uiTimeCount % 72 == 0)
		{
			m_fin.read(data, 3);
			if (m_fin.fail() == true)
			{
				CDialog::OnTimer(nIDEvent);
				return;
			}
			while(temp != m_fin.peek())
			{
				m_fin.seekg(1, ios::cur);
			}
			m_fin.seekg(1, ios::cur);
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
			m_zAmpData(x, uiCounter) = iTemp;
			uiCounter ++;
		}
		m_fin.seekg(2, ios::cur);
		m_uiTimeCount++;
		m_iOff = m_fin.tellg();
		m_ctrlGraph3D.GetPlots().Item(1).Plot3DSurface(m_xTimeData, m_yTraceData, m_zAmpData);
	}
	CDialog::OnTimer(nIDEvent);
}

void CDraw3DGraph_Test3Dlg::OnDestroy()
{
	CDialog::OnDestroy();

	// TODO: �ڴ˴������Ϣ����������
	if (m_fin.is_open())
	{
		m_fin.close();
	}
}
