
// MatrixServerDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MatrixServer.h"
#include "MatrixServerDlg.h"
#include "afxdialogex.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
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

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CMatrixServerDlg �Ի���




CMatrixServerDlg::CMatrixServerDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CMatrixServerDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMatrixServerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CMatrixServerDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BN_START, &CMatrixServerDlg::OnBnClickedBnStart)
	ON_BN_CLICKED(IDC_BN_STOP, &CMatrixServerDlg::OnBnClickedBnStop)
	ON_BN_CLICKED(IDC_BN_CLOSE, &CMatrixServerDlg::OnBnClickedBnClose)
	ON_BN_CLICKED(IDC_BN_REFRESH, &CMatrixServerDlg::OnBnClickedBnRefresh)
	ON_BN_CLICKED(IDC_BN_SAVE, &CMatrixServerDlg::OnBnClickedBnSave)
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_BUTTON_INIT, &CMatrixServerDlg::OnBnClickedButtonInit)
END_MESSAGE_MAP()


// CMatrixServerDlg ��Ϣ�������

BOOL CMatrixServerDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
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
	hMod = LoadLibrary(_T("MatrixServerDll"));
	Create_Instance a = NULL;
	if (hMod)
	{
		a = (Create_Instance)GetProcAddress(hMod, "OnCreateInstance");
		pEnv = (*a)();
	}
	// �ֳ���������ʼ��
//	m_oSiteManage.OnInit();
	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CMatrixServerDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CMatrixServerDlg::OnPaint()
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
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CMatrixServerDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMatrixServerDlg::OnBnClickedBnStart()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	// �ֳ��������
//	m_oSiteManage.OnWork();
	On_Work a = NULL;
	if (hMod)
	{
		a = (On_Work)GetProcAddress(hMod, "OnWork");
		(*a)(pEnv);
	}
}


void CMatrixServerDlg::OnBnClickedBnStop()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	// �ֳ��������
//	m_oSiteManage.OnStop();
	On_Stop a = NULL;
	if (hMod)
	{
		a = (On_Stop)GetProcAddress(hMod, "OnStop");
		(*a)(pEnv);
	}
}


void CMatrixServerDlg::OnBnClickedBnClose()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	// �ֳ��������
//	m_oSiteManage.OnClose();
	On_Close a = NULL;
	if (hMod)
	{
		a = (On_Close)GetProcAddress(hMod, "OnClose");
		(*a)(pEnv);
	}
}


void CMatrixServerDlg::OnBnClickedBnRefresh()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������

}


void CMatrixServerDlg::OnBnClickedBnSave()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������

}


void CMatrixServerDlg::OnDestroy()
{
	CDialogEx::OnDestroy();

	// TODO: �ڴ˴������Ϣ����������
	Free_Instance b = NULL;
	if (hMod)
	{
		b = (Free_Instance)GetProcAddress(hMod, "OnFreeInstance");
		(*b)(pEnv);
		FreeLibrary(hMod);
	}
}


void CMatrixServerDlg::OnBnClickedButtonInit()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	On_Init b = NULL;
	if (hMod)
	{
		b = (On_Init)GetProcAddress(hMod, "OnInit");
		(*b)(pEnv);
	}
}
