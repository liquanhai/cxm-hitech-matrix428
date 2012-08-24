
// SocketSendDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "SocketSend.h"
#include "SocketSendDlg.h"
#include "afxdialogex.h"
#include <string>
using std::string;

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


// CSocketSendDlg �Ի���


CSocketSendDlg::CSocketSendDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CSocketSendDlg::IDD, pParent)
	, m_uiDstPort(0)
	, m_bBroadCast(FALSE)
	, m_uiRcvBuf(0)
	, m_uiSndBuf(0)
	, m_SocketSnd(INVALID_SOCKET)
	, m_uiCount(0)
	, m_uiSndNum(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CSocketSendDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_DSTPORT, m_uiDstPort);
	DDX_Check(pDX, IDC_CHECK_BROADCAST, m_bBroadCast);
	DDX_Text(pDX, IDC_EDIT_RCVBUF, m_uiRcvBuf);
	DDX_Text(pDX, IDC_EDIT_SNDBUF, m_uiSndBuf);
	DDX_Text(pDX, IDC_EDIT_SNDNUM, m_uiSndNum);
}

BEGIN_MESSAGE_MAP(CSocketSendDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_START, &CSocketSendDlg::OnBnClickedButtonStart)
END_MESSAGE_MAP()


// CSocketSendDlg ��Ϣ�������

BOOL CSocketSendDlg::OnInitDialog()
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
	m_uiDstPort = 36666;
	m_bBroadCast = FALSE;
	m_uiRcvBuf = 4000000;
	m_uiSndBuf = 4000000;
	m_uiSndNum = 2000000;
	UpdateData(FALSE);
	GetDlgItem(IDC_IPADDRESS_DST)->SetWindowText(_T("192.168.100.19"));
	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CSocketSendDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CSocketSendDlg::OnPaint()
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
HCURSOR CSocketSendDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CSocketSendDlg::OnBnClickedButtonStart()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
	CString str = _T("");
	string strConv = "";
	int ret = 0;
	timeval time_val = {0};
	fd_set write_fds;
	int	iOptval = 0;
	int iOptlen = 0;
	int iCount = 0;
	LARGE_INTEGER liFrq;
	LARGE_INTEGER liCountOld;
	LARGE_INTEGER liCountNow;
	double dbTime = 0;
	// ����׽��ֵ�ַ�ṹ
	m_SocketSnd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	if (m_bBroadCast == TRUE)
	{
		//���ù㲥ģʽ
		iOptlen = sizeof(int);
		iOptval = 1;
		if (SOCKET_ERROR == setsockopt(m_SocketSnd, SOL_SOCKET, SO_BROADCAST, 
			reinterpret_cast<const char *>(&iOptval), iOptlen))
		{
			AfxMessageBox(_T("�㲥�˿�����ʧ�ܣ�"));
		}
	}
	if (SOCKET_ERROR == setsockopt(m_SocketSnd, SOL_SOCKET, SO_RCVBUF,  
		reinterpret_cast<const char *>(&m_uiRcvBuf), sizeof(int)))
	{
		AfxMessageBox(_T("���ջ���������ʧ�ܣ�"));
	}
	if (SOCKET_ERROR == setsockopt(m_SocketSnd, SOL_SOCKET, SO_SNDBUF,  
		reinterpret_cast<const char *>(&m_uiSndBuf), sizeof(int)))
	{
		AfxMessageBox(_T("���ͻ���������ʧ�ܣ�"));
	}

	// ����׽��ֵ�ַ�ṹ
	m_addrSend.sin_family = AF_INET;
	m_addrSend.sin_port = htons(m_uiDstPort);
	GetDlgItem(IDC_IPADDRESS_DST)->GetWindowText(str);
	strConv = (CStringA)str;
	m_addrSend.sin_addr.S_un.S_addr = inet_addr(strConv.c_str());
	m_uiCount = 0;
	QueryPerformanceFrequency(&liFrq);
	QueryPerformanceCounter(&liCountOld);
	while(m_uiCount < m_uiSndNum)
	{
		FD_ZERO(&write_fds);
		FD_SET(m_SocketSnd, &write_fds);
		ret = select(NULL, NULL, &write_fds, NULL, &time_val);

		if((ret == 0) || (ret == SOCKET_ERROR))
		{
			continue;
		}
		iCount = sendto(m_SocketSnd, m_cFrameData, 256, 0, 
			reinterpret_cast<sockaddr*>(&m_addrSend), sizeof(m_addrSend));
		if (iCount == 256)
		{
			m_uiCount++;
		}
	}
	QueryPerformanceCounter(&liCountNow);
	dbTime = (double)(liCountNow.LowPart - liCountOld.LowPart);
	dbTime /= liFrq.LowPart;
	str.Format(_T("�ѷ��� %d ֡����ʱ%.5f��!"), m_uiCount, dbTime);
	AfxMessageBox(str);
}
