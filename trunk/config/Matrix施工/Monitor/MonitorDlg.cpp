// MonitorDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Monitor.h"
#include "MonitorDlg.h"
#include "CiPlotChannelX.h"
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


// CMonitorDlg �Ի���




CMonitorDlg::CMonitorDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CMonitorDlg::IDD, pParent)
	,m_dwXValue(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMonitorDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_IPLOTX1, m_iPlotX);
}

BEGIN_MESSAGE_MAP(CMonitorDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_BUTTON1, &CMonitorDlg::OnBnClickedButton1)
END_MESSAGE_MAP()


// CMonitorDlg ��Ϣ�������

BOOL CMonitorDlg::OnInitDialog()
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
	if(!m_SockSample.CreateSocket(0xDF00,this))
	{
		 AfxMessageBox(_T("��m_SocketData�Ķ˿�ʧ�ܣ�"));
	}
	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CMonitorDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CMonitorDlg::OnPaint()
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
HCURSOR CMonitorDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CMonitorDlg::AnalysisProtocolOfSampleSock(void)
{
	static unsigned char	pBuf[46100];	// ���ݻ�������󳤶��Ƿ��Ͳɼ����е�����֡
	WORD			wFrmLen = 46100;		// ֡��: ��ʼ��Ϊ�������Ĵ�С����ReceiveFrom����ʹ��
	WORD			wFDUCount;			
	DWORD			dwFrmIndex;				// ֡����	
	int				i,nReadSize;
	DWORD			dwTemp;
	CString         strTemp;
	DWORD			dwFDUIP;		// FDU IP��ַ
	DWORD			dwSampIndex;	// ��������֡����

	// �������Կͻ��˵�����
	nReadSize = m_SockSample.Receive( pBuf, wFrmLen);
	switch (nReadSize)
	{
	case 0:		// û���յ����� 
		return;
		break;
	case SOCKET_ERROR:	// �������󣬼�¼��־
		if (GetLastError() != WSAEWOULDBLOCK) 
		{  //����socket����
			strTemp=_T(" socket�������ݴ���");
			AfxMessageBox(strTemp);
			return;
		}
		break;
	default:
		break;
	}
	// -----------����֡��ʽ---------------------------------------------------------
	// �ж�֡ͷ�Ƿ�0xEB, 0x90
	if (pBuf[0]!=0xEB || pBuf[1]!=0x90)
	{
		strTemp.Format(_T(" Frame head(%d,%d)is wrong��"),pBuf[0],pBuf[1]);
		AfxMessageBox(strTemp);
		return;
	}
	// ����֡����
	wFrmLen = MAKEWORD(pBuf[2],pBuf[3]);
	// 	if(wFrmLen>24576)
	// 	{	// ֡���ȳ��������������¼��־		
	// 		strTemp.Format(_T(" Frame length(%d)is wrong��"),wFrmLen);
	// 		AfxMessageBox(strTemp);		
	// 		return;
	// 	}
	// ����֡����
	memcpy_s(&dwFrmIndex,sizeof(dwFrmIndex),pBuf+4 , 4);
	// ֡β
	if(pBuf[wFrmLen-2]!=0x14 || pBuf[wFrmLen-1]!=0x6F)
	{
		// ֡β������Ҫ���¶�λ֡ͷ
		strTemp.Format(_T(" Frame end(%d,%d)is wrong��"),pBuf[wFrmLen-2],pBuf[wFrmLen-1]);
		AfxMessageBox(strTemp);
		return;
	}
	// -------------------���������룬���������������Ӧ����-------------------------------
	// �ɼ���
	wFDUCount=MAKEWORD(pBuf[11],pBuf[12]);
	// 
	CiPlotChannelX iPlotChn;
	iPlotChn = m_iPlotX.get_Channel(0);
	// ����ʾ��һ������
	memcpy_s(&dwFDUIP,sizeof(dwFDUIP),pBuf+13 , 4);
	memcpy_s(&dwSampIndex,sizeof(dwSampIndex),pBuf+17 , 4);
	for (i=0;i<74;i++)
	{
		memcpy_s(&dwTemp,sizeof(dwTemp),pBuf+21+i*3,4);
		dwTemp = dwTemp & 0x00FFFFFF;
		m_dwXValue++;		
		iPlotChn.AddXY(m_dwXValue,dwTemp);
		// m_OScopeCtrl.AppendPoint(dwTemp);
	}
}
void CMonitorDlg::OnDestroy()
{
	CDialog::OnDestroy();

	// TODO: �ڴ˴������Ϣ����������
	m_SockSample.Close();
}

void CMonitorDlg::OnBnClickedButton1()
{
	static unsigned char	pBuf[250];
	//static unsigned long  dwData=1;
	static unsigned char  byData=0;
	pBuf[0] = 0xEB;
	pBuf[1] = 0x90;

	// ֡��
	pBuf[2] = 246;
	pBuf[3] = 0;
	// ֡����
	// memcpy_s(pBuf+4,4,&dwFrmIndex,4);
	memset(pBuf+4,0,4);
	// ֡����
	pBuf[8] = 0x02;
	// ������
	pBuf[9]  =0;
	pBuf[10] = 0;
	// ���ݸ���
	pBuf[11] =1;
	pBuf[12] =0;
	// �����߳�������
	memset(pBuf+13,0,4);
	memset(pBuf+17,0,4);

	for(int i=0;i<74;i++)
	{
		// memcpy_s(pBuf+21+i*3,4,&dwData,4);
		memset(pBuf+21,byData,222);
	}
	byData++;
	//dwData+=10;
	//if(dwData>0xFFFFF0)
	//	dwData = 1;
	// ֡У��
	pBuf[243]=0;
	// ֡β
	pBuf[244] = 0x14;
	pBuf[245] = 0x6F;

	m_SockSample.SendTo(pBuf,246,0xDF00,_T("192.168.0.12"));
}
