
// MatrixServerDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MatrixServer.h"
#include "MatrixServerDlg.h"
#include "afxdialogex.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// ����Server��ͻ���ͨѶ�߳�
DWORD WINAPI RunCommThread(CMatrixServerDlg* pDlg)
{
	return pDlg->CommThreadRun();
}
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
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_BN_STARTSAMPLE_ALL, &CMatrixServerDlg::OnBnClickedButtonStartsampleAll)
	ON_BN_CLICKED(IDC_BN_STOPSAMPLE_ALL, &CMatrixServerDlg::OnBnClickedButtonStopsampleAll)
	ON_BN_CLICKED(IDC_BN_ADCSET_ALL, &CMatrixServerDlg::OnBnClickedBnAdcsetAll)
	ON_BN_CLICKED(IDC_BN_ADCSET_BYROUT, &CMatrixServerDlg::OnBnClickedBnAdcsetByrout)
	ON_BN_CLICKED(IDC_BN_STARTSAMPLE_BYROUT, &CMatrixServerDlg::OnBnClickedBnStartsampleByrout)
	ON_BN_CLICKED(IDC_BN_STOPSAMPLE_BYROUT, &CMatrixServerDlg::OnBnClickedBnStopsampleByrout)
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
	// ��ʼ����̬���ӿ�
	m_oMatrixDllCall.OnInit(_T("MatrixServerDll.dll"));
	m_dwEventTotal = 0;
	// ��ʼ���׽��ֿ�
	OnInitSocketLib();
	// ����Server�˿ڼ���
	CreateSocketListen();
	// ����Server��ͻ���ͨѶ�߳�
	OnCreateCommThread();
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
	// DLL��ʼ����
	m_oMatrixDllCall.Dll_Work();
}
void CMatrixServerDlg::OnBnClickedBnStop()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	// DLLֹͣ����
	m_oMatrixDllCall.Dll_Stop();
}
void CMatrixServerDlg::OnDestroy()
{
	CDialogEx::OnDestroy();

	// TODO: �ڴ˴������Ϣ����������
	// �رն�̬���ӿ�
	m_oMatrixDllCall.OnClose();
	// �ͷ��׽��ֿ�
	OnCloseSocketLib();
}
void CMatrixServerDlg::OnBnClickedButtonStartsampleAll()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	// DLL��ʼAD���ݲɼ�
	m_oMatrixDllCall.Dll_StartSample();
}
void CMatrixServerDlg::OnBnClickedButtonStopsampleAll()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	// DLLֹͣAD���ݲɼ�
	m_oMatrixDllCall.Dll_StopSample();
}
BOOL CMatrixServerDlg::CreateSocketInformation(SOCKET s)
{
	CServerSocketEvent* SI;
	if ((m_WSAEventArray[m_dwEventTotal] = WSACreateEvent()) == WSA_INVALID_EVENT)
	{
		printf("WSACreateEvent() failed with error %d\n", WSAGetLastError());
		return FALSE;
	}
	else
	{
		printf("WSACreateEvent() is OK!\n");
	}
	SI = new CServerSocketEvent;
	// Prepare SocketInfo structure for use
	SI->Socket = s;
	SI->BytesSEND = 0;
	SI->BytesRECV = 0;
	m_ServerSocketEventArray[m_dwEventTotal] = SI;
	m_dwEventTotal++;
	return(TRUE);
}
void CMatrixServerDlg::FreeSocketInformation(DWORD Event)
{
	CServerSocketEvent* SI = m_ServerSocketEventArray[Event];
	DWORD i;
	closesocket(SI->Socket);
	delete SI;
	if(WSACloseEvent(m_WSAEventArray[Event]) == TRUE)
		printf("WSACloseEvent() is OK!\n\n");
	else
		printf("WSACloseEvent() failed miserably!\n\n");
	// Squash the socket and event arrays
	for (i = Event; i < m_dwEventTotal; i++)
	{
		m_WSAEventArray[i] = m_WSAEventArray[i + 1];
		m_ServerSocketEventArray[i] = m_ServerSocketEventArray[i + 1];
	}
	m_dwEventTotal--;
}

// ��ʼ���׽��ֿ�
void CMatrixServerDlg::OnInitSocketLib(void)
{
	WSADATA wsaData;
	CString str = _T("");
	if (WSAStartup(0x0202, &wsaData) != 0)
	{
		str.Format(_T("WSAStartup() failed with error %d"), WSAGetLastError());
		AfxMessageBox(str);
		PostQuitMessage(0);
	}
}
// �ͷ��׽��ֿ�
void CMatrixServerDlg::OnCloseSocketLib(void)
{
	CString str = _T("");
	// �ͷ��׽��ֿ�
	if (WSACleanup() != 0)
	{
		str.Format(_T("WSACleanup() failed with error %d"), WSAGetLastError());
		AfxMessageBox(str);
		PostQuitMessage(0);
	}
}


// ����Server�˿ڼ���
void CMatrixServerDlg::CreateSocketListen(void)
{
	CString str = _T("");
	if ((m_SocketListen = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET)
	{
		str.Format(_T("socket() failed with error %d"), WSAGetLastError());
		AfxMessageBox(str);
		PostQuitMessage(0);
	}
	if(CreateSocketInformation(m_SocketListen) == FALSE)
	{
		AfxMessageBox(_T("CreateSocketInformation() failed!"));
		PostQuitMessage(0);
	}
	if (WSAEventSelect(m_SocketListen, m_WSAEventArray[m_dwEventTotal - 1], FD_ACCEPT|FD_CLOSE) == SOCKET_ERROR)
	{
		str.Format(_T("WSAEventSelect() failed with error %d"), WSAGetLastError());
		AfxMessageBox(str);
		PostQuitMessage(0);
	}
	m_ServerInternetAddr.sin_family = AF_INET;
	m_ServerInternetAddr.sin_addr.s_addr = htonl(INADDR_ANY);
	m_ServerInternetAddr.sin_port = htons(ServerListenPort);
	if (bind(m_SocketListen, (PSOCKADDR) &m_ServerInternetAddr, sizeof(m_ServerInternetAddr)) == SOCKET_ERROR)
	{
		str.Format(_T("bind() failed with error %d"), WSAGetLastError());
		AfxMessageBox(str);
		PostQuitMessage(0);
	}
	if (listen(m_SocketListen, 10))
	{
		str.Format(_T("listen() failed with error %d"), WSAGetLastError());
		AfxMessageBox(str);
		PostQuitMessage(0);
	}
}


// ����Server��ͻ���ͨѶ�߳�
void CMatrixServerDlg::OnCreateCommThread(void)
{
	DWORD dwThreadID;
	m_hThread = CreateThread((LPSECURITY_ATTRIBUTES)NULL, 
		0,
		(LPTHREAD_START_ROUTINE)RunCommThread,
		this, 
		0, 
		&dwThreadID);
}


// ��ͻ���ͨѶ�̺߳���
DWORD CMatrixServerDlg::CommThreadRun(void)
{
	SOCKET SocketAccept;
	CServerSocketEvent* pSocketInfo;
	DWORD Event;
	WSANETWORKEVENTS NetworkEvents;
	DWORD Flags;
	CString str = _T("");
	DWORD RecvBytes;
	DWORD SendBytes;
	while(true)
	{
		// Wait for one of the sockets to receive I/O notification and 
		if ((Event = WSAWaitForMultipleEvents(m_dwEventTotal, m_WSAEventArray, FALSE, WSA_INFINITE, FALSE)) == WSA_WAIT_FAILED)
		{
			str.Format(_T("WSAWaitForMultipleEvents() failed with error %d"), WSAGetLastError());
			AfxMessageBox(str);
			return 1;
		}
		if (WSAEnumNetworkEvents(m_ServerSocketEventArray[Event - WSA_WAIT_EVENT_0]->Socket,
			m_WSAEventArray[Event - WSA_WAIT_EVENT_0], &NetworkEvents) == SOCKET_ERROR)
		{
			str.Format(_T("WSAEnumNetworkEvents() failed with error %d"), WSAGetLastError());
			AfxMessageBox(str);
			return 1;
		}
		if (NetworkEvents.lNetworkEvents & FD_ACCEPT)
		{
			if (NetworkEvents.iErrorCode[FD_ACCEPT_BIT] != 0)
			{
				str.Format(_T("FD_ACCEPT failed with error %d"), NetworkEvents.iErrorCode[FD_ACCEPT_BIT]);
				AfxMessageBox(str);
				break;
			}
			if ((SocketAccept = accept(m_ServerSocketEventArray[Event - WSA_WAIT_EVENT_0]->Socket, NULL, NULL)) == INVALID_SOCKET)
			{
				printf("accept() failed with error %d\n", WSAGetLastError());
				break;
			}
			if (m_dwEventTotal > WSA_MAXIMUM_WAIT_EVENTS)
			{
				printf("Too many connections - closing socket...\n");
				closesocket(SocketAccept);
				break;
			}
			CreateSocketInformation(SocketAccept);
			if (WSAEventSelect(SocketAccept, m_WSAEventArray[m_dwEventTotal - 1], FD_READ|FD_WRITE|FD_CLOSE) == SOCKET_ERROR)
			{
				printf("WSAEventSelect() failed with error %d\n", WSAGetLastError());
				return 1;
			}
			printf("Socket %d got connected...\n", SocketAccept);
		}
		// Try to read and write data to and from the data buffer if read and write events occur
		if (NetworkEvents.lNetworkEvents & FD_READ || NetworkEvents.lNetworkEvents & FD_WRITE)
		{
			if (NetworkEvents.lNetworkEvents & FD_READ && NetworkEvents.iErrorCode[FD_READ_BIT] != 0)
			{
				printf("FD_READ failed with error %d\n", NetworkEvents.iErrorCode[FD_READ_BIT]);
				break;
			}
			else
				printf("FD_READ is OK!\n");
			if (NetworkEvents.lNetworkEvents & FD_WRITE && NetworkEvents.iErrorCode[FD_WRITE_BIT] != 0)
			{
				printf("FD_WRITE failed with error %d\n", NetworkEvents.iErrorCode[FD_WRITE_BIT]);
				break;
			}
			else
				printf("FD_WRITE is OK!\n");
			pSocketInfo = m_ServerSocketEventArray[Event - WSA_WAIT_EVENT_0];
			// Read data only if the receive buffer is empty
			if (pSocketInfo->BytesRECV == 0)
			{
				pSocketInfo->DataBuf.buf = pSocketInfo->Buffer;
				pSocketInfo->DataBuf.len = DATA_BUFSIZE;
				Flags = 0;
				if (WSARecv(pSocketInfo->Socket, &(pSocketInfo->DataBuf), 1, &RecvBytes, &Flags, NULL, NULL) == SOCKET_ERROR)
				{
					if (WSAGetLastError() != WSAEWOULDBLOCK)
					{
						printf("WSARecv() failed with error %d\n", WSAGetLastError());
						FreeSocketInformation(Event - WSA_WAIT_EVENT_0);
						return 1;
					}
				}
				else
				{
					printf("WSARecv() is working!\n");
					pSocketInfo->BytesRECV = RecvBytes;
				}
			}
			// Write buffer data if it is available
			if (pSocketInfo->BytesRECV > pSocketInfo->BytesSEND)
			{
				pSocketInfo->DataBuf.buf = pSocketInfo->Buffer + pSocketInfo->BytesSEND;
				pSocketInfo->DataBuf.len = pSocketInfo->BytesRECV - pSocketInfo->BytesSEND;
				if (WSASend(pSocketInfo->Socket, &(pSocketInfo->DataBuf), 1, &SendBytes, 0, NULL, NULL) == SOCKET_ERROR)
				{
					if (WSAGetLastError() != WSAEWOULDBLOCK)
					{
						printf("WSASend() failed with error %d\n", WSAGetLastError());
						FreeSocketInformation(Event - WSA_WAIT_EVENT_0);
						return 1;
					}
					// A WSAEWOULDBLOCK error has occurred. An FD_WRITE event will be posted
					// when more buffer space becomes available
				}
				else
				{
					printf("WSASend() is fine! Thank you...\n");
					pSocketInfo->BytesSEND += SendBytes;
					if (pSocketInfo->BytesSEND == pSocketInfo->BytesRECV)
					{
						pSocketInfo->BytesSEND = 0;
						pSocketInfo->BytesRECV = 0;
					}
				}
			}
		}
		if (NetworkEvents.lNetworkEvents & FD_CLOSE)
		{
			if (NetworkEvents.iErrorCode[FD_CLOSE_BIT] != 0)
			{
				printf("FD_CLOSE failed with error %d\n", NetworkEvents.iErrorCode[FD_CLOSE_BIT]);
				break;
			}
			else
				printf("FD_CLOSE is OK!\n");
			printf("Closing socket information %d\n", m_ServerSocketEventArray[Event - WSA_WAIT_EVENT_0]->Socket);
			FreeSocketInformation(Event - WSA_WAIT_EVENT_0);
		}
	}
	return 1;
}


void CMatrixServerDlg::OnBnClickedBnAdcsetAll()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	// AD��������
	m_oMatrixDllCall.Dll_ADCSet();
}


void CMatrixServerDlg::OnBnClickedBnAdcsetByrout()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString str = _T("");
	GetDlgItem(IDC_EDIT_ROUT)->GetWindowText(str);
	m_oMatrixDllCall.Dll_ADCSet_Part(_ttoi(str), 1);
}


void CMatrixServerDlg::OnBnClickedBnStartsampleByrout()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString str = _T("");
	GetDlgItem(IDC_EDIT_ROUT)->GetWindowText(str);
	m_oMatrixDllCall.Dll_ADCSet_Part(_ttoi(str), 2);
}


void CMatrixServerDlg::OnBnClickedBnStopsampleByrout()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString str = _T("");
	GetDlgItem(IDC_EDIT_ROUT)->GetWindowText(str);
	m_oMatrixDllCall.Dll_ADCSet_Part(_ttoi(str), 3);
}
