// TabUartToUdp.cpp : 实现文件
//

#include "stdafx.h"
#include "MatrixTestSoft.h"
#include "TabUartToUdp.h"


// CTabUartToUdp 对话框
// HANDLE	hCom;				// 准备打开的串口的句柄
// HANDLE	hCommWatchThread;	// 辅助线程的全局函数
// UINT CommWatchProc(CTabUartToUdp *pwnd);	// 线程函数

IMPLEMENT_DYNAMIC(CTabUartToUdp, CDialog)

CTabUartToUdp::CTabUartToUdp(CWnd* pParent /*=NULL*/)
	: CDialog(CTabUartToUdp::IDD, pParent)
	, m_usUartBufCount(0)
	, m_uiUartCount(0)
	, m_uiSerialPortComCurSel(0)
	, m_uiSerialPortBaudCurSel(0)
	, m_uiSendPort(0)
	, m_uiRecPort(0)
	, m_csIPAddress(_T(""))
	, m_pLogFile(NULL)
	, m_usUdpBufCount(0)
{

}

CTabUartToUdp::~CTabUartToUdp()
{
	if (m_pLogFile != NULL)
	{
		m_pLogFile = NULL;
		delete m_pLogFile;
	}
}

void CTabUartToUdp::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_SERIALPORT_COM, m_comboSerialPortCom);
	DDX_Control(pDX, IDC_COMBO_SERIALPORT_BAUD, m_comboSerialPortBaud);
	DDX_Control(pDX, IDC_MSCOMM1, m_ctrlMSComm1);
}


BEGIN_MESSAGE_MAP(CTabUartToUdp, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_SERIALPORT_OPEN, &CTabUartToUdp::OnBnClickedButtonSerialportOpen)
	ON_BN_CLICKED(IDC_BUTTON_SERIALPORT_CLOSE, &CTabUartToUdp::OnBnClickedButtonSerialportClose)
	ON_WM_TIMER()
	ON_MESSAGE(WM_UARTTOUDPSOCKET, &CTabUartToUdp::OnSocket)
END_MESSAGE_MAP()

// 初始化设置
//************************************
// Method:    OnInit
// FullName:  CTabUartToUdp::OnInit
// Access:    public 
// Returns:   void
// Qualifier:
// Parameter: void
//************************************
void CTabUartToUdp::OnInit(void)
{
	//端口设置
	CString str = _T("");
	for (int i=0; i<COMNum; i++)
	{
		str.Format(_T("COM%d"), i+1);
		m_comboSerialPortCom.InsertString(i, str);	// 插入下拉菜单选项
	}
	m_comboSerialPortCom.SetCurSel(m_uiSerialPortComCurSel);					// 设置控件初始化显示

	//波特率设置
	str.Format(_T("%d"), BAUD0);
	m_comboSerialPortBaud.InsertString( 0, str );	// 插入下拉菜单选项
	str.Format(_T("%d"), BAUD1);
	m_comboSerialPortBaud.InsertString( 1, str );
	str.Format(_T("%d"), BAUD2);
	m_comboSerialPortBaud.InsertString( 2, str );
	str.Format(_T("%d"), BAUD3);
	m_comboSerialPortBaud.InsertString( 3, str );
	str.Format(_T("%d"), BAUD4);
	m_comboSerialPortBaud.InsertString( 4, str );
	str.Format(_T("%d"), BAUD5);
	m_comboSerialPortBaud.InsertString( 5, str );
	str.Format(_T("%d"), BAUD6);
	m_comboSerialPortBaud.InsertString( 6, str );
	str.Format(_T("%d"), BAUD7);
	m_comboSerialPortBaud.InsertString( 7, str );
	str.Format(_T("%d"), BAUD8);
	m_comboSerialPortBaud.InsertString( 8, str );
	str.Format(_T("%d"), BAUD9);
	m_comboSerialPortBaud.InsertString( 9, str );
	str.Format(_T("%d"), BAUD10);
	m_comboSerialPortBaud.InsertString( 10, str );
	str.Format(_T("%d"), BAUD11);
	m_comboSerialPortBaud.InsertString( 11, str );
	m_comboSerialPortBaud.SetCurSel(m_uiSerialPortBaudCurSel);					// 设置控件初始化显示

	// 串口通讯设置
	m_ctrlMSComm1.put_InBufferCount(0);		// 清空接收缓存
	m_ctrlMSComm1.put_OutBufferCount(0);	// 清空发送缓存
	m_ctrlMSComm1.put_InputMode(1);         // 二进制模式

	GetDlgItem(IDC_IPADDRESS_UARTTOUDP)->SetWindowText(m_csIPAddress);
	str.Format(_T("0x%04x"),m_uiSendPort);
	GetDlgItem(IDC_EDIT_PORT_UARTTOUDP)->SetWindowText(str);	// 0x9001
	str.Format(_T("0x%04x"),m_uiRecPort);
	GetDlgItem(IDC_EDIT_PORT_REC)->SetWindowText(str);			// 0x9002

	m_usUartBufCount = 0;
	m_uiUartCount = 0;
}

// 得到当前选择的串口号
//************************************
// Method:    OnGetSerialPortCom
// FullName:  CTabUartToUdp::OnGetSerialPortCom
// Access:    private 
// Returns:   int
// Qualifier:
// Parameter: void
//************************************
int CTabUartToUdp::OnGetSerialPortCom(void)
{
	int iCurrentCom = 0;
	CString str = _T("");
	CString strTemp = _T("");
	m_comboSerialPortCom.GetWindowText(str);	
	for (int i=0; i<COMNum; i++)
	{
		strTemp.Format(_T("COM%d"), i+1);
		if (str == strTemp)
		{
			iCurrentCom = i+1;
			break;
		}
	}
	if (iCurrentCom == 0)
	{
		AfxMessageBox(_T("Input Serial Port Com Nb is Wrong!"));
		m_pLogFile->OnWriteLogFile(_T("CTabUartToUdp::OnGetSerialPortCom"), _T("输入串口号错误！"), ErrorStatus);
	}
	else
	{
		str = _T("");
		str = _T("串口选择端口") + strTemp;
		m_pLogFile->OnWriteLogFile(_T("CTabUartToUdp::OnGetSerialPortCom"), str, SuccessStatus);
	}

	return iCurrentCom;
}

// 得到当前选择的波特率
//************************************
// Method:    OnGetSerialPortBaud
// FullName:  CTabUartToUdp::OnGetSerialPortBaud
// Access:    private 
// Returns:   int
// Qualifier:
// Parameter: void
//************************************
int CTabUartToUdp::OnGetSerialPortBaud(void)
{
	int iCurrentBaud = 0;
	CString str = _T("");
	CString strTemp = _T("");
	m_comboSerialPortBaud.GetWindowText(str);	
	strTemp.Format(_T("%d"), BAUD0);
	if (str == strTemp)
	{
		iCurrentBaud = BAUD0;
	}
	strTemp.Format(_T("%d"), BAUD1);
	if (str == strTemp)
	{
		iCurrentBaud = BAUD1;
	}
	strTemp.Format(_T("%d"), BAUD2);
	if (str == strTemp)
	{
		iCurrentBaud = BAUD2;
	}
	strTemp.Format(_T("%d"), BAUD3);
	if (str == strTemp)
	{
		iCurrentBaud = BAUD3;
	}
	strTemp.Format(_T("%d"), BAUD4);
	if (str == strTemp)
	{
		iCurrentBaud = BAUD4;
	}
	strTemp.Format(_T("%d"), BAUD5);
	if (str == strTemp)
	{
		iCurrentBaud = BAUD5;
	}
	strTemp.Format(_T("%d"), BAUD6);
	if (str == strTemp)
	{
		iCurrentBaud = BAUD6;
	}
	strTemp.Format(_T("%d"), BAUD7);
	if (str == strTemp)
	{
		iCurrentBaud = BAUD7;
	}
	strTemp.Format(_T("%d"), BAUD8);
	if (str == strTemp)
	{
		iCurrentBaud = BAUD8;
	}
	strTemp.Format(_T("%d"), BAUD9);
	if (str == strTemp)
	{
		iCurrentBaud = BAUD9;
	}
	strTemp.Format(_T("%d"), BAUD10);
	if (str == strTemp)
	{
		iCurrentBaud = BAUD10;
	}	
	strTemp.Format(_T("%d"), BAUD11);
	if (str == strTemp)
	{
		iCurrentBaud = BAUD11;
	}
	if (iCurrentBaud == 0)
	{
		AfxMessageBox(_T("Input Serial Port Baud is Wrong!"));
		m_pLogFile->OnWriteLogFile(_T("CTabUartToUdp::OnGetSerialPortBaud"), _T("输入串口波特率错误！"), ErrorStatus);
	}
	else
	{
		str = _T("");
		str = _T("串口选择波特率") + strTemp;
		m_pLogFile->OnWriteLogFile(_T("CTabUartToUdp::OnGetSerialPortBaud"), str, SuccessStatus);
	}
	return iCurrentBaud;
}

// 从UDP发送数据
//************************************
// Method:    OnSendFromUDP
// FullName:  CTabUartToUdp::OnSendFromUDP
// Access:    private 
// Returns:   void
// Qualifier:
// Parameter: unsigned char * TXDATA
// Parameter: unsigned int uiCount
//************************************
void CTabUartToUdp::OnSendFromUDP(unsigned char* TXDATA, unsigned int uiCount)
{
	unsigned int uiFrameCount = 0;
	unsigned char ucTxdata[RcvFrameSize];
	CString str = _T("");
	CString strIP = _T("");
	int iSendPort = 0;
	unsigned int uiFrameSize = RcvFrameSize;
	uiFrameCount = uiCount/uiFrameSize;
	if (uiFrameCount == 0)
	{
		return;
	}
	GetDlgItem(IDC_EDIT_PORT_UARTTOUDP)->GetWindowText(str);
	_stscanf_s(str, _T("%x"), &iSendPort);
	GetDlgItem(IDC_IPADDRESS_UARTTOUDP)->GetWindowText(str);
	strIP = str;

	addr2.sin_family = AF_INET;											// 填充套接字地址结构
	addr2.sin_port = htons(iSendPort);
	addr2.sin_addr.S_un.S_addr = inet_addr(ConvertCStringToConstCharPointer(strIP));

	for (unsigned int i=0; i<uiFrameCount; i++)
	{
//		ProcessMessages();
		memcpy(&ucTxdata, &TXDATA[i*uiFrameSize], uiFrameSize);
//		m_socketUartToUdp.SendTo(ucTxdata, uiFrameSize, iSendPort, strIP);
		sendto(m_UdpSocket, (const char*)&ucTxdata, uiFrameSize, 0, (sockaddr*)&addr2, sizeof(addr2));
	}
}

void CTabUartToUdp::OnBnClickedButtonSerialportOpen()
{
	// TODO: ÔÚ´ËÌí¼Ó¿Ø¼þÍ¨Öª´¦Àí³ÌÐò´úÂë
	// 打开串口
	OnOpenCom();
	GetDlgItem(IDC_BUTTON_SERIALPORT_OPEN)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_SERIALPORT_CLOSE)->EnableWindow(TRUE);
}

void CTabUartToUdp::OnBnClickedButtonSerialportClose()
{
	// TODO: ÔÚ´ËÌí¼Ó¿Ø¼þÍ¨Öª´¦Àí³ÌÐò´úÂë
	OnCloseCom();
	OnCloseUDP();
	ControlEnable();
	if (!m_ctrlMSComm1.get_PortOpen())
	{
		CString str = _T("");
		str = _T("成功关闭串口!");
		AfxMessageBox(str);
		m_pLogFile->OnWriteLogFile(_T("CTabUartToUdp::OnBnClickedButtonSerialportClose"), str, SuccessStatus);
	}
	GetDlgItem(IDC_BUTTON_SERIALPORT_OPEN)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_SERIALPORT_CLOSE)->EnableWindow(FALSE);
}

// 使能控件
//************************************
// Method:    ControlEnable
// FullName:  CTabUartToUdp::ControlEnable
// Access:    public 
// Returns:   void
// Qualifier:
// Parameter: void
//************************************
void CTabUartToUdp::ControlEnable(void)
{
	GetDlgItem(IDC_COMBO_SERIALPORT_COM)->EnableWindow(TRUE);
	GetDlgItem(IDC_COMBO_SERIALPORT_BAUD)->EnableWindow(TRUE);
	GetDlgItem(IDC_IPADDRESS_UARTTOUDP)->EnableWindow(TRUE);
	GetDlgItem(IDC_EDIT_PORT_UARTTOUDP)->EnableWindow(TRUE);
	GetDlgItem(IDC_EDIT_PORT_REC)->EnableWindow(TRUE);
}

// 禁用控件
//************************************
// Method:    ControlDisable
// FullName:  CTabUartToUdp::ControlDisable
// Access:    public 
// Returns:   void
// Qualifier:
// Parameter: void
//************************************
void CTabUartToUdp::ControlDisable(void)
{
	GetDlgItem(IDC_COMBO_SERIALPORT_COM)->EnableWindow(FALSE);
	GetDlgItem(IDC_COMBO_SERIALPORT_BAUD)->EnableWindow(FALSE);
	GetDlgItem(IDC_IPADDRESS_UARTTOUDP)->EnableWindow(FALSE);
	GetDlgItem(IDC_EDIT_PORT_UARTTOUDP)->EnableWindow(FALSE);
	GetDlgItem(IDC_EDIT_PORT_REC)->EnableWindow(FALSE);
}

// 打开串口
//************************************
// Method:    OnOpenCom
// FullName:  CTabUartToUdp::OnOpenCom
// Access:    public 
// Returns:   void
// Qualifier:
// Parameter: void
//************************************
void CTabUartToUdp::OnOpenCom(void)
{
	int iPort = 0;
	int iBaud = 0;
	CString str = _T("");
	OnCloseCom();
	UpdateData(TRUE);
	iPort = OnGetSerialPortCom();
	iBaud = OnGetSerialPortBaud();
	m_ctrlMSComm1.put_CommPort(iPort);
	str.Format(_T("%d,n,8,1"), iBaud);
	m_ctrlMSComm1.put_Settings(str);

	if(!m_ctrlMSComm1.get_PortOpen())
	{
		m_ctrlMSComm1.put_PortOpen(TRUE);
		m_pLogFile->OnWriteLogFile(_T("CTabUartToUdp::OnOpenCom"), _T("成功打开串口！"), SuccessStatus);
		GetDlgItem(IDC_EDIT_PORT_REC)->GetWindowText(str);			// 0x9002
		_stscanf_s(str,_T("%x"), &m_uiRecPort);
		m_uiSerialPortComCurSel = m_comboSerialPortCom.GetCurSel();
		m_uiSerialPortBaudCurSel = m_comboSerialPortBaud.GetCurSel();
	
		// 创建Socket
//		BOOL bReturn =  m_socketUartToUdp.Create(m_uiRecPort,SOCK_DGRAM);
		m_UdpSocket = ::socket(AF_INET, SOCK_DGRAM, 0);
		addr.sin_family = AF_INET;											// 填充套接字地址结构
		addr.sin_port = htons(m_uiRecPort);
		addr.sin_addr.S_un.S_addr = INADDR_ANY;
		int iReturn = bind(m_UdpSocket, (sockaddr*)&addr, sizeof(addr));	// 绑定本地地址
		listen(m_UdpSocket, 2);
		WSAAsyncSelect(m_UdpSocket, this->m_hWnd, WM_UARTTOUDPSOCKET, FD_READ);	// 设置异步套接字
//		if (bReturn == FALSE)
		if (iReturn == SOCKET_ERROR)
		{
			str = _T("串口转UDP端口创建失败！");
			m_pLogFile->OnWriteLogFile(_T("CTabUartToUdp::OnOpenCom"), str, ErrorStatus);
			AfxMessageBox(str);
		}
		else
		{
			m_pLogFile->OnWriteLogFile(_T("CTabUartToUdp::OnOpenCom"), _T("串口转UDP端口创建成功！"), SuccessStatus);
//			bReturn = m_socketUartToUdp.SetSockOpt(SO_SNDBUF,&m_socketUartToUdp,UartToUDPBufSize,SOL_SOCKET);
			int nSendBuf = UartToUDPBufSize;
			iReturn = setsockopt(m_UdpSocket, SOL_SOCKET, SO_SNDBUF,  ( const char* )&nSendBuf, sizeof(int));
//			if (bReturn == FALSE)
			if (iReturn == SOCKET_ERROR)
			{
				str = _T("UDP转串口端口设置发送缓冲区设置失败！");
				AfxMessageBox(str);
				m_pLogFile->OnWriteLogFile(_T("CTabUartToUdp::OnOpenCom"), str, ErrorStatus);
			}
//			bReturn = m_socketUartToUdp.SetSockOpt(SO_RCVBUF,&m_socketUartToUdp,UartToUDPBufSize,SOL_SOCKET);
			int nRecvBuf = UartToUDPBufSize;
			iReturn = setsockopt(m_UdpSocket, SOL_SOCKET, SO_RCVBUF,  ( const char* )&nRecvBuf, sizeof(int));
//			if (bReturn == FALSE)
			if (iReturn == SOCKET_ERROR)
			{
				str = _T("UDP转串口端口设置接收缓冲区设置失败！");
				AfxMessageBox(str);
				m_pLogFile->OnWriteLogFile(_T("CTabUartToUdp::OnOpenCom"), str, ErrorStatus);
			}
			// 避免端口阻塞
			OnAvoidIOBlock(m_UdpSocket);
		}
		ControlDisable();
		AfxMessageBox(_T("Open Serial Port Successful!"));
	}
	KillTimer(TabUartToUdpRecTimerNb);
	SetTimer(TabUartToUdpRecTimerNb, TabUartToUdpRecTimerSet, NULL);
}
// 避免端口阻塞
//************************************
// Method:    OnAvoidIOBlock
// FullName:  CTabUartToUdp::OnAvoidIOBlock
// Access:    public 
// Returns:   void
// Qualifier:
// Parameter: SOCKET socket
//************************************
void CTabUartToUdp::OnAvoidIOBlock(SOCKET socket)
{
	DWORD dwBytesReturned = 0;
	BOOL bNewBehavior = FALSE;
	DWORD status = 0;
	status = WSAIoctl(socket, SIO_UDP_CONNRESET ,
		&bNewBehavior, sizeof(bNewBehavior),
		NULL, 0, &dwBytesReturned,
		NULL, NULL);
}
// 串口接收数据
void CTabUartToUdp::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: ÔÚ´ËÌí¼ÓÏûÏ¢´¦Àí³ÌÐò´úÂëºÍ/»òµ÷ÓÃÄ¬ÈÏÖµ
	if (nIDEvent == TabUartToUdpRecTimerNb)
	{
		KillTimer(TabUartToUdpRecTimerNb);
		VARIANT vResponse;
		int len = 0;
		unsigned char* Rxdata = NULL;

		len = m_ctrlMSComm1.get_InBufferCount(); //接收到的字符数目

		if(len > 0) 
		{
			// 设置需要读取的输入缓冲区大小，为了不丢帧
			m_ctrlMSComm1.put_InputLen(len);
			vResponse=m_ctrlMSComm1.get_Input(); //read
			Rxdata = (unsigned char*) vResponse.parray->pvData;

			for (int i=0; i<len; i++)
			{
//				ProcessMessages();
				switch(m_uiUartCount)
				{
				case 0:
					if (Rxdata[i] == FrameHeadCheck0)
					{
						m_ucUartBuf[m_usUartBufCount][0] = Rxdata[i];
						m_uiUartCount++;
						break;
					}
					else
					{
						m_uiUartCount = 0;
						break;
					}

				case 1:
					if (Rxdata[i] == FrameHeadCheck1)
					{
						m_ucUartBuf[m_usUartBufCount][1] = Rxdata[i];
						m_uiUartCount++;
						break;
					}
					else
					{
						m_uiUartCount = 0;
						break;
					}
				case 2:
					if (Rxdata[i] == FrameHeadCheck2)
					{
						m_ucUartBuf[m_usUartBufCount][2] = Rxdata[i];
						m_uiUartCount++;
						break;
					}
					else
					{
						m_uiUartCount = 0;
						break;
					}
				case 3:
					if (Rxdata[i] == FrameHeadCheck3)
					{
						m_ucUartBuf[m_usUartBufCount][3] = Rxdata[i];
						m_uiUartCount++;
						break;
					}
					else
					{
						m_uiUartCount = 0;
						break;
					}
				default:
					if (m_uiUartCount <  RcvFrameSize)
					{
						m_ucUartBuf[m_usUartBufCount][m_uiUartCount] = Rxdata[i];
						m_uiUartCount++;
						if (m_uiUartCount == RcvFrameSize)
						{
							m_uiUartCount = 0;
							OnSendFromUDP(m_ucUartBuf[m_usUartBufCount], RcvFrameSize);
							m_usUartBufCount += 1;
							m_usUartBufCount = m_usUartBufCount % RcvBufNum;
						}
					}
					break;
				}
			}
		} 
		// 接收到字符，MSComm控件发送事件 
		SetTimer(TabUartToUdpRecTimerNb, TabUartToUdpRecTimerSet, NULL);
	}
	
	CDialog::OnTimer(nIDEvent);
}

// 关闭
//************************************
// Method:    OnClose
// FullName:  CTabUartToUdp::OnClose
// Access:    public 
// Returns:   void
// Qualifier:
// Parameter: void
//************************************
void CTabUartToUdp::OnClose(void)
{
	OnCloseCom();
	OnCloseUDP();
}

// 防止程序在循环中运行无法响应消息
//************************************
// Method:    ProcessMessages
// FullName:  CTabUartToUdp::ProcessMessages
// Access:    private 
// Returns:   void
// Qualifier:
// Parameter: void
//************************************
void CTabUartToUdp::ProcessMessages(void)
{
	MSG msg;
	::PeekMessage(&msg, NULL, 0, 0, PM_REMOVE);
	::DispatchMessage(&msg);
}
// 关闭串口
//************************************
// Method:    OnCloseCom
// FullName:  CTabUartToUdp::OnCloseCom
// Access:    private 
// Returns:   void
// Qualifier:
// Parameter: void
//************************************
void CTabUartToUdp::OnCloseCom(void)
{
	if(m_ctrlMSComm1.get_PortOpen())
	{
		m_ctrlMSComm1.put_PortOpen(FALSE);
	}
}

// 关闭UDP端口
//************************************
// Method:    OnCloseUDP
// FullName:  CTabUartToUdp::OnCloseUDP
// Access:    private 
// Returns:   void
// Qualifier:
// Parameter: void
//************************************
void CTabUartToUdp::OnCloseUDP(void)
{
// 	m_socketUartToUdp.ShutDown(2);
// 	m_socketUartToUdp.Close();
	shutdown(m_UdpSocket, SD_BOTH);
	closesocket(m_UdpSocket);
}
LRESULT CTabUartToUdp::OnSocket(WPARAM wParam, LPARAM lParam)
{
	switch(lParam)
	{
	case FD_READ:
		{
			int ret=0;
			int n = sizeof(addr);
			//	ret = Receive(m_ucUdpBuf[m_usUdpBufCount],UartToUdpRcvSize);
			ret = recvfrom(m_UdpSocket, (char*)&m_ucUdpBuf[m_usUdpBufCount], sizeof(m_ucUdpBuf[m_usUdpBufCount]), 0, (sockaddr*)&addr, &n);
			if(ret == SOCKET_ERROR)
			{
				TRACE("ERROR!");
			}
			else if(ret != 0) 
			{
				OnSendFromSerialPort(m_ucUdpBuf[m_usUdpBufCount], ret);
				m_usUdpBufCount += 1;
				m_usUdpBufCount = m_usUdpBufCount % RcvBufNum;
			}
		}
		break;
	}
	return TRUE;
}

// 从串口发送数据
//************************************
// Method:    OnSendFromSerialPort
// FullName:  CUartToUdpSocket::OnSendFromSerialPort
// Access:    private 
// Returns:   void
// Qualifier:
// Parameter: unsigned char * TXDATA
// Parameter: unsigned int uiCount
//************************************
void CTabUartToUdp::OnSendFromSerialPort(unsigned char* TXDATA, unsigned int uiCount)
{
	if(m_ctrlMSComm1.get_PortOpen() == FALSE)
	{
		return;
	}
	CByteArray array;
	array.RemoveAll();
	array.SetSize(uiCount);
	for(unsigned int i=0; i<uiCount; i++)
	{
		array.SetAt(i, TXDATA[i]);
	}
	m_ctrlMSComm1.put_Output(COleVariant(array)); // 发送数据
}
