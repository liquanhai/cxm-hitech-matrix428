// Draw3DGraphDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Draw3DGraph.h"
#include "Draw3DGraphDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define PI 3.1415926535
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


// CDraw3DGraphDlg �Ի���




CDraw3DGraphDlg::CDraw3DGraphDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CDraw3DGraphDlg::IDD, pParent)
	, m_iCounter(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CDraw3DGraphDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CWGRAPH3D1, m_ctrlGraph3D);
	DDX_Control(pDX, IDC_BTN_START, m_ctrlBtnStart);
	DDX_Control(pDX, IDC_BTN_STOP, m_ctrlBtnStop);
}

BEGIN_MESSAGE_MAP(CDraw3DGraphDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_BTN_START, &CDraw3DGraphDlg::OnBnClickedBtnStart)
	ON_BN_CLICKED(IDC_BTN_STOP, &CDraw3DGraphDlg::OnBnClickedBtnStop)
	ON_BN_CLICKED(IDC_RADIO_SURFACE, &CDraw3DGraphDlg::OnBnClickedRadioSurface)
	ON_BN_CLICKED(IDC_RADIO_SURFACELINE, &CDraw3DGraphDlg::OnBnClickedRadioSurfaceline)
	ON_WM_TIMER()
END_MESSAGE_MAP()


// CDraw3DGraphDlg ��Ϣ�������

BOOL CDraw3DGraphDlg::OnInitDialog()
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

	m_xTimeData.SetSize(SampleTime);
	m_yTraceData.SetSize(TraceNum);
	m_zAmpData.SetSize(SampleTime, TraceNum);
	for (int i = 0; i < TraceNum; i++)
	{
		m_yTraceData[i] = i;
	}
	for (int i = 0; i < SampleTime; i++)
	{
		m_xTimeData[i] = i;
	}
// 	// Plot the data
// 	m_ctrlGraph3D.GetPlots().Item(1).Plot3DSurface(xData, yData, zData);
// 	m_ctrlGraph3D.GetPlots().Add();
// 	m_ctrlGraph3D.GetPlots().Item(2).Plot3DSurface(xData, yData, zData2);
	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CDraw3DGraphDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CDraw3DGraphDlg::OnPaint()
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
HCURSOR CDraw3DGraphDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CDraw3DGraphDlg::OnBnClickedBtnStart()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	SetTimer(TimerID, TimerDelay, NULL);
}

void CDraw3DGraphDlg::OnBnClickedBtnStop()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	KillTimer(TimerID);
}

void CDraw3DGraphDlg::OnBnClickedRadioSurface()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_ctrlGraph3D.GetPlots().Item(1).SetStyle(CNiPlot3D::Surface);
}

void CDraw3DGraphDlg::OnBnClickedRadioSurfaceline()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_ctrlGraph3D.GetPlots().Item(1).SetStyle(CNiPlot3D::SurfaceLine);
}

void CDraw3DGraphDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	if (nIDEvent == TimerID)
	{
		if (m_iCounter < SampleTime)
		{
			for (int i = 0; i < m_iCounter; i++)
			{
				for (int j = 0; j < TraceNum; j++)
				{
					if (j < (TraceNum - 1) / 2)
					{
						m_zAmpData(i, j) = SampleAmpMax * sin((m_xTimeData[i] + m_iCounter) / 20 * PI + j * PI / (TraceNum - 1));
					}
					else
					{
						m_zAmpData(i, j) = SampleAmpMax * sin((m_xTimeData[i] + m_iCounter) / 20 * PI + (TraceNum - 1 - j) * PI / (TraceNum - 1));
					}
				}
			}
		}
		else
		{
			for (int i = 0; i < SampleTime; i++)
			{
				for (int j = 0; j < TraceNum; j++)
				{
					if (j < (TraceNum - 1) / 2)
					{
						m_zAmpData(i, j) = SampleAmpMax * sin((m_xTimeData[i] + m_iCounter) / 20 * PI + j * PI / (TraceNum - 1));
					}
					else
					{
						m_zAmpData(i, j) = SampleAmpMax * sin((m_xTimeData[i] + m_iCounter) / 20 * PI + (TraceNum - 1 - j) * PI / (TraceNum - 1));
					}
				}
			}
		}
		m_ctrlGraph3D.GetPlots().Item(1).Plot3DSurface(m_xTimeData, m_yTraceData, m_zAmpData);
		m_iCounter++;
	}
	CDialog::OnTimer(nIDEvent);
}
