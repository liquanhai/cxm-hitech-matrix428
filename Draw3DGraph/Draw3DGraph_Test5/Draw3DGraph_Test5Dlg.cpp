// Draw3DGraph_Test5Dlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Draw3DGraph_Test5.h"
#include "Draw3DGraph_Test5Dlg.h"

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


// CDraw3DGraph_Test5Dlg �Ի���




CDraw3DGraph_Test5Dlg::CDraw3DGraph_Test5Dlg(CWnd* pParent /*=NULL*/)
	: CDialog(CDraw3DGraph_Test5Dlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CDraw3DGraph_Test5Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CWGRAPH3D1, m_ctrlGraph3D);
}

BEGIN_MESSAGE_MAP(CDraw3DGraph_Test5Dlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


// CDraw3DGraph_Test5Dlg ��Ϣ�������

BOOL CDraw3DGraph_Test5Dlg::OnInitDialog()
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
	m_ctrlGraph3D.SetProjectionStyle(m_ctrlGraph3D.Perspective);//Ͷ��ģʽ��������ԶС

	m_Axis3D = m_ctrlGraph3D.GetAxes().Item(1);
	m_Axis3D.SetCaption(_T("Y-axis"));
	m_Axis3D.SetCaptionColor(RGB(255, 255, 255));
	m_Axis3D.GetLabels().SetColor(RGB(255, 255, 255));
	m_Axis3D.GetLabels().SetOpposite(true);
	m_Axis3D.GetLabels().SetNormal(false);
	m_Axis3D.SetCaptionOpposite(true);
	m_Axis3D.SetCaptionNormal(false);
	m_Axis3D.SetInverted(true);
/*	m_Axis3D.SetCaptionOrientationStyle(m_Axis3D.FaceCamera);*/
	m_Axis3D.GetTicks().SetMajorTickColor(RGB(255, 255, 255));
	m_Axis3D.GetTicks().SetMajorGridColor(RGB(234, 234, 234));
	m_Axis3D.GetTicks().SetMinorTickColor(RGB(255, 255, 255));
	m_Axis3D.GetTicks().SetMinorGridColor(RGB(234, 234, 234));
	m_Axis3D.GetTicks().SetMinorGrid(true);
	m_Axis3D.GetTicks().SetMajorDivisions(5);
	m_Axis3D.GetTicks().SetMinorDivisions(5);
	m_Axis3D.GetTicks().SetOpposite(true);
	m_Axis3D.GetTicks().SetNormal(false);
 	m_Axis3D.GetTicks().SetOutside(true);
	m_Axis3D.GetTicks().SetInside(false);
	m_Axis3D.SetMinMax(0, 100);

	m_Axis3D = m_ctrlGraph3D.GetAxes().Item(2);
	m_Axis3D.SetCaption(_T("X-axis"));
	m_Axis3D.SetCaptionColor(RGB(255, 255, 255));
	m_Axis3D.GetLabels().SetColor(RGB(255, 255, 255));
	m_Axis3D.GetLabels().SetOpposite(true);
	m_Axis3D.GetLabels().SetNormal(true);
	m_Axis3D.SetCaptionOpposite(true);
	m_Axis3D.SetCaptionNormal(true);
	/*	m_Axis3D.SetCaptionOrientationStyle(m_Axis3D.FaceCamera);*/
	m_Axis3D.GetTicks().SetMajorTickColor(RGB(255, 255, 255));
	m_Axis3D.GetTicks().SetMajorGridColor(RGB(234, 234, 234));
	m_Axis3D.GetTicks().SetMinorTickColor(RGB(255, 255, 255));
	m_Axis3D.GetTicks().SetMinorGridColor(RGB(234, 234, 234));
	m_Axis3D.GetTicks().SetMinorGrid(true);
	m_Axis3D.GetTicks().SetMajorDivisions(5);
	m_Axis3D.GetTicks().SetMinorDivisions(5);
	m_Axis3D.GetTicks().SetOpposite(true);
	m_Axis3D.GetTicks().SetNormal(false);
	m_Axis3D.GetTicks().SetOutside(true);
	m_Axis3D.GetTicks().SetInside(false);
	m_Axis3D.SetMinMax(0, 100);

 	m_Axis3D = m_ctrlGraph3D.GetAxes().Item(3);
 	m_Axis3D.GetLabels().SetColor(RGB(255, 255, 255));
	m_Axis3D.GetTicks().SetMajorTickColor(RGB(255, 255, 255));
	m_Axis3D.GetTicks().SetMajorGridColor(RGB(234, 234, 234));
	m_Axis3D.GetTicks().SetMinorTickColor(RGB(255, 255, 255));
	m_Axis3D.GetTicks().SetMinorGridColor(RGB(234, 234, 234));
	m_Axis3D.GetTicks().SetMinorGrid(true);
	m_Axis3D.GetTicks().SetMajorDivisions(5);
	m_Axis3D.GetTicks().SetMinorDivisions(5);
	m_Axis3D.GetTicks().SetOpposite(false);
	m_Axis3D.GetTicks().SetNormal(false);
	m_Axis3D.GetTicks().SetOutside(false);
	m_Axis3D.GetTicks().SetInside(false);
	m_Axis3D.SetMinMax(25, 35);
	
	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CDraw3DGraph_Test5Dlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CDraw3DGraph_Test5Dlg::OnPaint()
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
HCURSOR CDraw3DGraph_Test5Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

