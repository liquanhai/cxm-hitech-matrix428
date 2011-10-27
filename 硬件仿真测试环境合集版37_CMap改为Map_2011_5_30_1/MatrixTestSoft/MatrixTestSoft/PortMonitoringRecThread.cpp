// PortMonitoringRecThread.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MatrixTestSoft.h"
#include "PortMonitoringRecThread.h"

// CPortMonitoringRecThread

IMPLEMENT_DYNCREATE(CPortMonitoringRecThread, CWinThread)

CPortMonitoringRecThread::CPortMonitoringRecThread()
: m_usudp_count(0)
, m_iRecPort(0)
, m_pSaveFile(NULL)
, m_uiHeartBeatNum(0)
, m_uiIPSetNum(0)
, m_uiTailTimeNum(0)
, m_uiDelayTimeSetNum(0)
, m_uiADCSetNum(0)
, m_uiSendFrameNum(0)
, m_bclose(false)
, m_uiUdpCount(0)
, m_pLogFile(NULL)
, m_RecSocket(INVALID_SOCKET)
{
}

CPortMonitoringRecThread::~CPortMonitoringRecThread()
{
}

BOOL CPortMonitoringRecThread::InitInstance()
{
	// TODO: �ڴ�ִ���������̳߳�ʼ��
	return TRUE;
}

int CPortMonitoringRecThread::ExitInstance()
{
	// TODO: �ڴ�ִ���������߳�����
	return CWinThread::ExitInstance();
}

BEGIN_MESSAGE_MAP(CPortMonitoringRecThread, CWinThread)
END_MESSAGE_MAP()


// CPortMonitoringRecThread ��Ϣ�������

int CPortMonitoringRecThread::Run()
{
	// TODO: �ڴ����ר�ô����/����û���

	DWORD dwFrameCount = 0;
	int icount = 0;
	sockaddr_in SenderAddr;
	int n = sizeof(SenderAddr);
	int iError = 0;
	CString str = _T("");
	// ѭ����ֱ���رձ�־Ϊ��
	while(true)
	{
		if(m_bclose == true)
		{
			break;
		}
		// �õ�������ջ����������ֽ���
		// ���Խ��ճ������
		while(SOCKET_ERROR != ioctlsocket(m_RecSocket, FIONREAD, &dwFrameCount))
		{
			if(dwFrameCount > 0) 
			{
				icount = recvfrom(m_RecSocket, reinterpret_cast<char*>(&m_ucUdpBuf), sizeof(m_ucUdpBuf), 0, reinterpret_cast<sockaddr*>(&SenderAddr), &n);
// 				str.Format(_T("�Ӷ˿ڼ��ӽ����߳̽��ջ�������ȡ���ݴ�СΪ%d��"), icount);
// 				m_pLogFile->OnWriteLogFile(_T("CADCDataRecThread::Run"), str, SuccessStatus);
				if (icount != SOCKET_ERROR)
				{
					OnProcess(icount);
				}
				else if(icount == PortMonitoringBufSize)
				{
					str.Format(_T("�˿ڼ��ӽ����߳����ݽ��ճ�����������С����������СΪ%d��"), PortMonitoringBufSize);
					m_pLogFile->OnWriteLogFile(_T("CPortMonitoringRecThread::Run"), str, ErrorStatus);
				}
				else
				{
					iError = WSAGetLastError();
					str.Format(_T("�˿ڼ��ӽ��յĽ���֡���󣬴����Ϊ%d��"), iError);
					m_pLogFile->OnWriteLogFile(_T("CPortMonitoringRecThread::Run"), str, ErrorStatus);
				}
			}
			else
			{
				break;
			}
		}
	
		if (m_bclose == true)
		{
			break;
		}
		Sleep(PortMonitoringRecThreadSleepTime);
	}

	::SetEvent(m_hPortMonitoringRecThreadClose);	// �����¼�����Ϊ���ź�״̬,�ͷŵȴ��̺߳��¼���Ϊ���ź�
	return CWinThread::Run();
}
// ��������
//************************************
// Method:    OnProcess
// FullName:  CPortMonitoringRecThread::OnProcess
// Access:    public 
// Returns:   void
// Qualifier:
// Parameter: int iCount
//************************************
void CPortMonitoringRecThread::OnProcess(int iCount)
{
	unsigned short usCRC16 = 0;
	for (int i=0; i<iCount; i++)
	{
//		ProcessMessages();
		switch(m_uiUdpCount)
		{
		case 0:
			if (m_ucUdpBuf[i] == FrameHeadCheck0)
			{
				m_ucudp_buf[m_usudp_count][0] = m_ucUdpBuf[i];
				m_uiUdpCount++;
				break;
			}
			else
			{
				//	m_uiUdpCount = 0;
				m_uiUdpCount++;
				break;
			}

		case 1:
			if (m_ucUdpBuf[i] == FrameHeadCheck1)
			{
				m_ucudp_buf[m_usudp_count][1] = m_ucUdpBuf[i];
				m_uiUdpCount++;
				break;
			}
			else
			{
				//	m_uiUdpCount = 0;
				m_uiUdpCount++;
				break;
			}
		case 2:
			if (m_ucUdpBuf[i] == FrameHeadCheck2)
			{
				m_ucudp_buf[m_usudp_count][2] = m_ucUdpBuf[i];
				m_uiUdpCount++;
				break;
			}
			else
			{
				//	m_uiUdpCount = 0;
				m_uiUdpCount++;
				break;
			}
		case 3:
			if (m_ucUdpBuf[i] == FrameHeadCheck3)
			{
				m_ucudp_buf[m_usudp_count][3] = m_ucUdpBuf[i];
				m_uiUdpCount++;
				break;
			}
			else
			{
				//	m_uiUdpCount = 0;
				m_uiUdpCount++;
				break;
			}
		default:
			if (m_uiUdpCount >=  SndFrameSize)
			{
				m_uiUdpCount = 0;
				m_usudp_count += 1;
				m_usudp_count = m_usudp_count % RcvBufNum;
				break;
			}
			m_ucudp_buf[m_usudp_count][m_uiUdpCount] = m_ucUdpBuf[i];
			m_uiUdpCount++;
			if (m_uiUdpCount == SndFrameSize)
			{
				m_uiUdpCount = 0;

				memcpy(&usCRC16, &m_ucudp_buf[m_usudp_count][SndFrameSize - CRCSize], CRCSize);
				if (usCRC16 != get_crc_16(&m_ucudp_buf[m_usudp_count][FrameHeadSize], SndFrameSize - FrameHeadSize - CRCCheckSize))
				{
					//	continue;
				}
				OnPortMonitoringProc();
				m_usudp_count += 1;
				m_usudp_count = m_usudp_count % RcvBufNum;
			}
			break;
		}
	}
}
// ��ʼ��
//************************************
// Method:    OnInit
// FullName:  CPortMonitoringRecThread::OnInit
// Access:    public 
// Returns:   void
// Qualifier:
// Parameter: void
//************************************
void CPortMonitoringRecThread::OnInit(void)
{
	m_hPortMonitoringRecThreadClose = ::CreateEvent(false, false, NULL, NULL);	// �����¼�����
	if ((m_hPortMonitoringRecThreadClose == NULL)||(GetLastError() == ERROR_ALREADY_EXISTS))
	{
		AfxMessageBox(_T("�����˿ڼ��ӷ����̹߳ر��¼�����"));
	}
	else
	{
		::ResetEvent(m_hPortMonitoringRecThreadClose);	// �����¼�����Ϊ���ź�״̬
	}
}

// ��
//************************************
// Method:    OnOpen
// FullName:  CPortMonitoringRecThread::OnOpen
// Access:    public 
// Returns:   void
// Qualifier:
// Parameter: void
//************************************
void CPortMonitoringRecThread::OnOpen(void)
{
	CString str = _T("");
	m_RecSocket = socket(AF_INET, SOCK_DGRAM, 0);
	m_RecvAddr.sin_family = AF_INET;											// ����׽��ֵ�ַ�ṹ
	m_RecvAddr.sin_port = htons(static_cast<unsigned short>(m_iRecPort));
	m_RecvAddr.sin_addr.S_un.S_addr = INADDR_ANY;
	int iReturn = bind(m_RecSocket, reinterpret_cast<sockaddr*>(&m_RecvAddr), sizeof(m_RecvAddr));	// �󶨱��ص�ַ
	listen(m_RecSocket, 2);
	if (iReturn == SOCKET_ERROR)
	{
		str = _T("�˿ڼ��ӳ���Ľ��ն˿ڴ���ʧ�ܣ�");
		AfxMessageBox(str);
		m_pLogFile->OnWriteLogFile(_T("CPortMonitoringRecThread::OnOpen"), str, ErrorStatus);
	}
	else
	{
		int nSendBuf = PortMonitoringBufSize;
		iReturn = setsockopt(m_RecSocket, SOL_SOCKET, SO_SNDBUF,  reinterpret_cast<const char *>(&nSendBuf), sizeof(int));
		if (iReturn == SOCKET_ERROR)
		{
			str = _T("�˿ڼ��ӳ���Ľ��ն˿ڷ��ͻ���������ʧ�ܣ�");
			AfxMessageBox(str);
			m_pLogFile->OnWriteLogFile(_T("CPortMonitoringRecThread::OnOpen"), str, ErrorStatus);
		}
		int nRecvBuf = PortMonitoringBufSize;
		iReturn = setsockopt(m_RecSocket, SOL_SOCKET, SO_RCVBUF,  reinterpret_cast<const char *>(&nRecvBuf), sizeof(int));
		if (iReturn == SOCKET_ERROR)
		{
			str = _T("�˿ڼ��ӳ���Ľ��ն˿ڽ��ջ���������ʧ�ܣ�");
			AfxMessageBox(str);
			m_pLogFile->OnWriteLogFile(_T("CPortMonitoringRecThread::OnOpen"), str, ErrorStatus);
		}
		//���ù㲥ģʽ
		int iOptlen = sizeof(int);
		int iOptval = 1;
		iReturn = setsockopt(m_RecSocket, SOL_SOCKET, SO_BROADCAST, reinterpret_cast<const char *>(&iOptval), iOptlen);
		if (iReturn == SOCKET_ERROR)
		{
			str = _T("�˿ڼ��ӳ���Ľ��ն˿�����Ϊ�㲥�˿�ʧ�ܣ�");
			AfxMessageBox(str);
			m_pLogFile->OnWriteLogFile(_T("CPortMonitoringRecThread::OnOpen"), str, ErrorStatus);
		}
		// ����˿�����
		OnAvoidIOBlock(m_RecSocket);
	}
}
// ����˿�����
//************************************
// Method:    OnAvoidIOBlock
// FullName:  CPortMonitoringRecThread::OnAvoidIOBlock
// Access:    public 
// Returns:   void
// Qualifier:
// Parameter: SOCKET socket
//************************************
void CPortMonitoringRecThread::OnAvoidIOBlock(SOCKET socket)
{
	DWORD dwBytesReturned = 0;
	BOOL bNewBehavior = FALSE;
	DWORD status = 0;
	status = WSAIoctl(socket, SIO_UDP_CONNRESET ,
		&bNewBehavior, sizeof(bNewBehavior),
		NULL, 0, &dwBytesReturned,
		NULL, NULL);
}
// ֹͣ
//************************************
// Method:    OnStop
// FullName:  CPortMonitoringRecThread::OnStop
// Access:    public 
// Returns:   void
// Qualifier:
// Parameter: void
//************************************
void CPortMonitoringRecThread::OnStop(void)
{
	OnCloseUDP();
}

// �ر�
//************************************
// Method:    OnClose
// FullName:  CPortMonitoringRecThread::OnClose
// Access:    public 
// Returns:   void
// Qualifier:
// Parameter: void
//************************************
void CPortMonitoringRecThread::OnClose(void)
{
	OnCloseUDP();
	m_bclose = true;
}
// ���ý���
//************************************
// Method:    OnReset
// FullName:  CPortMonitoringRecThread::OnReset
// Access:    public 
// Returns:   void
// Qualifier:
// Parameter: void
//************************************
void CPortMonitoringRecThread::OnReset(void)
{
	m_uiHeartBeatNum = 0;
	m_uiIPSetNum = 0;
	m_uiTailTimeNum = 0;
	m_uiDelayTimeSetNum = 0;
	m_uiADCSetNum = 0;
	m_uiSendFrameNum = 0;
}
// ��ֹ������ѭ���������޷���Ӧ��Ϣ
//************************************
// Method:    ProcessMessages
// FullName:  CPortMonitoringRecThread::ProcessMessages
// Access:    public 
// Returns:   void
// Qualifier:
// Parameter: void
//************************************
void CPortMonitoringRecThread::ProcessMessages(void)
{
	MSG msg;
	::PeekMessage(&msg, NULL, 0, 0, PM_REMOVE);
	::DispatchMessage(&msg);
}

// �˿ڼ��Ӵ�����
void CPortMonitoringRecThread::OnPortMonitoringProc(void)
{
	CString strTemp = _T("");
	int iPos = 0;
	unsigned short uiPort = 0;

	// ע�͵�����������Ϣ����ADC�������ú���Ư�����������Ͳ������ͣ������
	// ͨ���˿�ʶ����
	iPos = 24;
	memcpy(&uiPort, &m_ucudp_buf[m_usudp_count][iPos], FramePacketSize2B);
	if (uiPort == HeartBeatPort)
	{
		m_uiHeartBeatNum ++;
	}
	else if (uiPort == IPSetPort)
	{
		m_uiIPSetNum ++;
	}
	else if (uiPort == TailTimeFramePort)
	{
		m_uiTailTimeNum ++;
	}
	else if (uiPort == TimeSetPort)
	{
		m_uiDelayTimeSetNum ++;
	}
	else if (uiPort == ADSetReturnPort)
	{
		m_uiADCSetNum ++;
	}
	m_uiSendFrameNum ++;

	int icount = sendto(m_RecSocket, reinterpret_cast<const char*>(&m_ucudp_buf[m_usudp_count]), SndFrameSize, 0, reinterpret_cast<sockaddr*>(&m_SendToAddr), sizeof(m_SendToAddr));
	if (icount == SOCKET_ERROR)
	{
		CString str = _T("");
		int iError = WSAGetLastError();
		str.Format(_T("�˿ڼ��ӽ����߳�sendto����, �������Ϊ%d"), iError);
		m_pLogFile->OnWriteLogFile(_T("CPortMonitoringRecThread::OnPortMonitoringProc"), str, ErrorStatus);
	}
	m_pSaveFile->OnSaveReceiveData(m_ucudp_buf[m_usudp_count],SndFrameSize);
}
// �ر�UDP�׽���
void CPortMonitoringRecThread::OnCloseUDP(void)
{
	shutdown(m_RecSocket, SD_BOTH);
	closesocket(m_RecSocket);
	m_RecSocket = INVALID_SOCKET;
}
