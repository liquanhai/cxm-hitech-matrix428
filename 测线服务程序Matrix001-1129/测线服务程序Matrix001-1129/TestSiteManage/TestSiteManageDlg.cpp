// TestSiteManageDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "TestSiteManage.h"
#include "TestSiteManageDlg.h"

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


// CTestSiteManageDlg �Ի���




CTestSiteManageDlg::CTestSiteManageDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CTestSiteManageDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CTestSiteManageDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CTestSiteManageDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_BN_ONINIT, &CTestSiteManageDlg::OnBnClickedBnOninit)
	ON_BN_CLICKED(IDC_BN_START, &CTestSiteManageDlg::OnBnClickedBnStart)
	ON_BN_CLICKED(IDC_BN_STOP, &CTestSiteManageDlg::OnBnClickedBnStop)
	ON_BN_CLICKED(IDC_BN_CLOSE, &CTestSiteManageDlg::OnBnClickedBnClose)
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDOK, &CTestSiteManageDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CTestSiteManageDlg::OnBnClickedCancel)
END_MESSAGE_MAP()


// CTestSiteManageDlg ��Ϣ�������

BOOL CTestSiteManageDlg::OnInitDialog()
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
	OnBnClickedBnOninit();

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CTestSiteManageDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CTestSiteManageDlg::OnPaint()
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
HCURSOR CTestSiteManageDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

/**
* ��ʼ��
* @param void
* @return void
*/
void CTestSiteManageDlg::OnBnClickedBnOninit()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	// �ֳ��������
	m_oSiteManage.OnInit();
}

/**
* ��ʼ����
* @param void
* @return void
*/
void CTestSiteManageDlg::OnBnClickedBnStart()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	// �ֳ��������
	m_oSiteManage.OnWork();
}

/**
* ֹͣ����
* @param void
* @return void
*/
void CTestSiteManageDlg::OnBnClickedBnStop()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	// �ֳ��������
	m_oSiteManage.OnStop();
}

/**
* �ر�
* @param void
* @return void
*/
void CTestSiteManageDlg::OnBnClickedBnClose()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	// �ֳ��������
	m_oSiteManage.OnClose();
}

void CTestSiteManageDlg::OnDestroy()
{
	CDialog::OnDestroy();

	// TODO: �ڴ˴������Ϣ����������
	OnBnClickedBnClose();
}

void CTestSiteManageDlg::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	OnOK();
}

void CTestSiteManageDlg::OnBnClickedCancel()
{
	// TODO: Add your control notification handler code here
	OnCancel();
}
