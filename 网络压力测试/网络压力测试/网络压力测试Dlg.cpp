// ����ѹ������Dlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "����ѹ������.h"
#include "����ѹ������Dlg.h"

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


// C����ѹ������Dlg �Ի���




C����ѹ������Dlg::C����ѹ������Dlg(CWnd* pParent /*=NULL*/)
	: CDialog(C����ѹ������Dlg::IDD, pParent)
	, m_uiTimeDelay(0)
	, m_uiSendFrameNum(0)
	, m_csIPAim(_T(""))
	, m_uiAimPort(0)
	, m_uiRealTimeDelay(0)
	, m_uiRealSendFrameNum(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void C����ѹ������Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(C����ѹ������Dlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_BUTTON_START, &C����ѹ������Dlg::OnBnClickedButtonStart)
	ON_BN_CLICKED(IDC_BUTTON_STOP, &C����ѹ������Dlg::OnBnClickedButtonStop)
	ON_WM_TIMER()
END_MESSAGE_MAP()


// C����ѹ������Dlg ��Ϣ�������

BOOL C����ѹ������Dlg::OnInitDialog()
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
	CString str;
	GetDlgItem(IDC_EDIT_TIMEDELAY)->SetWindowText(_T("10"));
	GetDlgItem(IDC_EDIT_SENDFRAME)->SetWindowText(_T("20"));
	GetDlgItem(IDC_EDIT_REALTIMEDELAY)->SetWindowText(_T("0"));
	GetDlgItem(IDC_EDIT_REALSENDFRAME)->SetWindowText(_T("0"));
	GetDlgItem(IDC_IPADDRESS_AIM)->SetWindowText(_T("192.168.0.11"));
	str.Format(_T("%d"), SendPort);
	GetDlgItem(IDC_EDIT_PORT)->SetWindowText(str);
	GetDlgItem(IDC_BUTTON_STOP)->EnableWindow(FALSE);
	m_ucSendFrame[0] = 0x11;
	m_ucSendFrame[1] = 0x22;
	m_ucSendFrame[2] = 0x33;
	m_ucSendFrame[3] = 0x44;

	SetTimer(2, 1000, NULL);

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void C����ѹ������Dlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void C����ѹ������Dlg::OnPaint()
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
HCURSOR C����ѹ������Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void C����ѹ������Dlg::OnBnClickedButtonStart()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString str = _T("");
	GetDlgItem(IDC_BUTTON_STOP)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_START)->EnableWindow(FALSE);

	GetDlgItem(IDC_EDIT_TIMEDELAY)->GetWindowText(str);
	m_uiTimeDelay = _ttoi(str);
	GetDlgItem(IDC_EDIT_SENDFRAME)->GetWindowText(str);
	m_uiSendFrameNum = _ttoi(str);
	GetDlgItem(IDC_IPADDRESS_AIM)->GetWindowText(m_csIPAim);
	GetDlgItem(IDC_EDIT_PORT)->GetWindowText(str);
	
	m_uiAimPort = _ttoi(str);
	
	m_uiRealSendFrameNum = 0;
	m_uiRealTimeDelay = 0;

	m_hSocket.Close();
	if (FALSE == m_hSocket.Create(RcvPort, SOCK_DGRAM))
	{
		AfxMessageBox(_T("�˿ڴ���ʧ�ܣ�"));
	}
	if (FALSE == m_hSocket.SetSockOpt(SO_SNDBUF,&m_hSocket,SndBufSize,SOL_SOCKET))
	{
		AfxMessageBox(_T("���÷��ͻ�������Сʧ�ܣ�"));
	}

	KillTimer(1);
	SetTimer(1, m_uiTimeDelay, NULL);
}

void C����ѹ������Dlg::OnBnClickedButtonStop()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	GetDlgItem(IDC_BUTTON_STOP)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_START)->EnableWindow(TRUE);
	m_hSocket.Close();
	KillTimer(1);
}

void C����ѹ������Dlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	int icount = 0;
	DWORD dwTimeDelay1 = 0;
	DWORD dwTimeDelay2 = 0;
	if (1 == nIDEvent)
	{
		KillTimer(1);
		dwTimeDelay1 = GetTickCount();
		if (m_uiSendFrameNum > 0)
		{
			for (unsigned int i=0; i<m_uiSendFrameNum; i++)
			{
				icount = m_hSocket.SendTo(m_ucSendFrame, 256, m_uiAimPort, m_csIPAim);
				if (icount == 256)
				{
					m_uiRealSendFrameNum++;
				}
				else
				{
					AfxMessageBox(_T("��������֡ʧ�ܣ�"));
				}
			}
		}
		dwTimeDelay2 = GetTickCount();
		m_uiRealTimeDelay = dwTimeDelay2 - dwTimeDelay1;
		SetTimer(1, m_uiTimeDelay, NULL);
	}
	if (2 == nIDEvent)
	{
		CString str = _T("");
		str.Format(_T("%u"), m_uiRealTimeDelay);
		GetDlgItem(IDC_EDIT_REALTIMEDELAY)->SetWindowText(str);
		str.Format(_T("%u"), m_uiRealSendFrameNum);
		GetDlgItem(IDC_EDIT_REALSENDFRAME)->SetWindowText(str);
	}
	CDialog::OnTimer(nIDEvent);
}
