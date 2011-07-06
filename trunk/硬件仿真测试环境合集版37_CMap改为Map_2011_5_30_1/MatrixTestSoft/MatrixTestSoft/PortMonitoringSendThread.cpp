// PortMonitoringSendThread.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MatrixTestSoft.h"
#include "PortMonitoringSendThread.h"

// CPortMonitoringSendThread

IMPLEMENT_DYNCREATE(CPortMonitoringSendThread, CWinThread)

CPortMonitoringSendThread::CPortMonitoringSendThread()
: m_usudp_count(0)
, m_iRecPort(0)
, m_iSendPort(0)
, m_csIP(_T(""))
, m_uiHeadFrameNum(0)
, m_uiIPSetReturnNum(0)
, m_uiTailFrameNum(0)
, m_uiTailTimeReturnNum(0)
, m_uiDelayTimeReturnNum(0)
, m_uiADCSetReturnNum(0)
, m_uiErrorCodeReturnNum(0)
, m_uiCollectSysTimeReturnNum(0)
, m_uiADCRecNum(0)
, m_csHeadFrameShow(_T(""))
, m_csIPSetReturnShow(_T(""))
, m_csTailFrameShow(_T(""))
, m_csTailTimeReturnShow(_T(""))
, m_csDelayTimeReturnShow(_T(""))
, m_csErrorCodeReturnShow(_T(""))
, m_uiRecFrameNum(0)
, m_pSaveFile(NULL)
, m_bPortDistribution(FALSE)
, m_bclose(false)
, m_uiUdpCount(0)
, m_pLogFile(NULL)
{
}

CPortMonitoringSendThread::~CPortMonitoringSendThread()
{
}

BOOL CPortMonitoringSendThread::InitInstance()
{
	// TODO: �ڴ�ִ���������̳߳�ʼ��
	return TRUE;
}

int CPortMonitoringSendThread::ExitInstance()
{
	// TODO: �ڴ�ִ���������߳�����
	return CWinThread::ExitInstance();
}

BEGIN_MESSAGE_MAP(CPortMonitoringSendThread, CWinThread)
END_MESSAGE_MAP()


// CPortMonitoringSendThread ��Ϣ�������

int CPortMonitoringSendThread::Run()
{
	// TODO: �ڴ����ר�ô����/����û���
	DWORD dwFrameCount = 0;
	int icount = 0;
	int n = sizeof(addr);
	// ѭ����ֱ���رձ�־Ϊ��
	while(true)
	{
		if (m_bclose == true)
		{
			break;
		}
		// �õ�������ջ����������ֽ���
		// ���Խ��ճ������
		while(SOCKET_ERROR != ioctlsocket(m_SendSocket, FIONREAD, &dwFrameCount))
		{
			if(dwFrameCount > 0) 
			{
				icount = recvfrom(m_SendSocket, (char*)&m_ucUdpBuf, sizeof(m_ucUdpBuf), 0, (sockaddr*)&addr, &n);
				if (icount != SOCKET_ERROR)
				{
					OnProcess(icount);
				}
				else
				{
					int iError = 0;
					CString str = _T("");
					iError = WSAGetLastError();
					str.Format(_T("�˿ڼ��ӷ��͵Ľ���֡���󣬴����Ϊ%d��"), iError);
					m_pLogFile->OnWriteLogFile(_T("CPortMonitoringSendThread::Run"), str, ErrorStatus);
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
		Sleep(PortMonitoringSendThreadSleepTime);
	}
	::SetEvent(m_hPortMonitoringSendThreadClose);	// �����¼�����Ϊ���ź�״̬,�ͷŵȴ��̺߳��¼���Ϊ���ź�
	return CWinThread::Run();
}
// ���ݴ���
//************************************
// Method:    OnProcess
// FullName:  CPortMonitoringSendThread::OnProcess
// Access:    public 
// Returns:   void
// Qualifier:
// Parameter: int iCount
//************************************
void CPortMonitoringSendThread::OnProcess(int iCount)
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
			if (m_uiUdpCount >=  RcvFrameSize)
			{
				m_uiUdpCount = 0;
				m_usudp_count += 1;
				m_usudp_count = m_usudp_count % RcvBufNum;
				break;
			}
			m_ucudp_buf[m_usudp_count][m_uiUdpCount] = m_ucUdpBuf[i];
			m_uiUdpCount++;
			if (m_uiUdpCount == RcvFrameSize)
			{
				m_uiUdpCount = 0;

				memcpy(&usCRC16, &m_ucudp_buf[m_usudp_count][RcvFrameSize - CRCSize], CRCSize);
				if (usCRC16 != get_crc_16(&m_ucudp_buf[m_usudp_count][FrameHeadSize], RcvFrameSize - FrameHeadSize - CRCCheckSize))
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
// FullName:  CPortMonitoringSendThread::OnInit
// Access:    public 
// Returns:   void
// Qualifier:
// Parameter: void
//************************************
void CPortMonitoringSendThread::OnInit(void)
{
	m_hPortMonitoringSendThreadClose = ::CreateEvent(false, false, NULL, NULL);	// �����¼�����
	if ((m_hPortMonitoringSendThreadClose == NULL)||(GetLastError() == ERROR_ALREADY_EXISTS))
	{
		AfxMessageBox(_T("�����˿ڼ��ӷ����̹߳ر��¼�����"));
	}
	else
	{
		::ResetEvent(m_hPortMonitoringSendThreadClose);	// �����¼�����Ϊ���ź�״̬
	}
	for (int i=0; i<InstrumentNum; i++)
	{
		m_uiErrorCodeReturnCount[i] = 0;
		memset(&m_ucErrorCodeReturn[i], SndFrameBufInit, QueryErrorCodeNum);
	}
}

// ��
//************************************
// Method:    OnOpen
// FullName:  CPortMonitoringSendThread::OnOpen
// Access:    public 
// Returns:   void
// Qualifier:
// Parameter: void
//************************************
void CPortMonitoringSendThread::OnOpen(void)
{
	CString str = _T("");
	m_SendSocket = socket(AF_INET, SOCK_DGRAM, 0);
	addr.sin_family = AF_INET;											// ����׽��ֵ�ַ�ṹ
	addr.sin_port = htons(m_iRecPort);
	addr.sin_addr.S_un.S_addr = INADDR_ANY;
	int iReturn = bind(m_SendSocket, (sockaddr*)&addr, sizeof(addr));	// �󶨱��ص�ַ
	listen(m_SendSocket, 2);
	if (iReturn == SOCKET_ERROR)
	{
		str = _T("�˿ڼ��ӳ���ķ��Ͷ˿ڴ���ʧ�ܣ�");
		AfxMessageBox(str);
		m_pLogFile->OnWriteLogFile(_T("CPortMonitoringSendThread::OnOpen"), str, ErrorStatus);
	}
	else
	{
		int nSendBuf = PortMonitoringBufSize;
		iReturn = setsockopt(m_SendSocket, SOL_SOCKET, SO_SNDBUF,  ( const char* )&nSendBuf, sizeof(int));
		if (iReturn == SOCKET_ERROR)
		{
			str = _T("�˿ڼ��ӳ���Ľ��ն˿ڷ��ͻ���������ʧ�ܣ�");
			AfxMessageBox(str);
			m_pLogFile->OnWriteLogFile(_T("CPortMonitoringSendThread::OnOpen"), str, ErrorStatus);
		}
		int nRecvBuf = PortMonitoringBufSize;
		iReturn = setsockopt(m_SendSocket, SOL_SOCKET, SO_RCVBUF,  ( const char* )&nRecvBuf, sizeof(int));
		if (iReturn == SOCKET_ERROR)
		{
			str = _T("�˿ڼ��ӳ���ķ��Ͷ˿ڽ��ջ���������ʧ�ܣ�");
			AfxMessageBox(str);
			m_pLogFile->OnWriteLogFile(_T("CPortMonitoringSendThread::OnOpen"), str, ErrorStatus);
		}
		// ����˿�����
		OnAvoidIOBlock(m_SendSocket);
	}
}
// ����˿�����
//************************************
// Method:    OnAvoidIOBlock
// FullName:  CPortMonitoringSendThread::OnAvoidIOBlock
// Access:    public 
// Returns:   void
// Qualifier:
// Parameter: SOCKET socket
//************************************
void CPortMonitoringSendThread::OnAvoidIOBlock(SOCKET socket)
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
// FullName:  CPortMonitoringSendThread::OnStop
// Access:    public 
// Returns:   void
// Qualifier:
// Parameter: void
//************************************
void CPortMonitoringSendThread::OnStop(void)
{
	OnCloseUDP();
	// Ӳ���豸�����ѯӦ��֡����
	m_uiErrorCodeReturnNum = 0;
	for (int i=0; i<InstrumentNum; i++)
	{
		m_uiErrorCodeReturnCount[i] = 0;
		memset(&m_ucErrorCodeReturn[i], SndFrameBufInit, QueryErrorCodeNum);
	}
}

// �ر�
//************************************
// Method:    OnClose
// FullName:  CPortMonitoringSendThread::OnClose
// Access:    public 
// Returns:   void
// Qualifier:
// Parameter: void
//************************************
void CPortMonitoringSendThread::OnClose(void)
{
	OnCloseUDP();
	m_bclose = true;
}
// ���ý���
//************************************
// Method:    OnReset
// FullName:  CPortMonitoringSendThread::OnReset
// Access:    public 
// Returns:   void
// Qualifier:
// Parameter: void
//************************************
void CPortMonitoringSendThread::OnReset(void)
{
	// �װ�����
	m_uiHeadFrameNum = 0;
	// IP��ַ���ü���
	m_uiIPSetReturnNum = 0;
	// β������
	m_uiTailFrameNum = 0;
	// β��ʱ�̲�ѯӦ�����
	m_uiTailTimeReturnNum = 0;
	// ʱ������Ӧ�����
	m_uiDelayTimeReturnNum = 0;
	// ADC����Ӧ�����
	m_uiADCSetReturnNum = 0;
	// Ӳ���豸�����ѯӦ��֡����
	m_uiErrorCodeReturnNum = 0;
	// ��ѯ�õ��ı���ʱ��֡��
	m_uiCollectSysTimeReturnNum = 0;
	// ���յõ���ADC����֡��
	m_uiADCRecNum = 0;
	// ��ʾ�װ�֡������SN���װ�ʱ��
	m_csHeadFrameShow.Empty();
	// ��ʾIP��ַ����Ӧ��֡������SN�����õ�IP��ַ
	m_csIPSetReturnShow.Empty();
	// ��ʾβ��֡������SN
	m_csTailFrameShow.Empty();
	// ��ʾβ��ʱ�̲�ѯӦ��֡������IP��ַ�Ͳ�ѯ���
	m_csTailTimeReturnShow.Empty();
	// ��ʾʱ������Ӧ��֡������IP��ַ����������
	m_csDelayTimeReturnShow.Empty();
	// ��ʾӲ������������
	m_csErrorCodeReturnShow.Empty();
	// ����֡��
	m_uiRecFrameNum = 0;
}
// ��ֹ������ѭ���������޷���Ӧ��Ϣ
//************************************
// Method:    ProcessMessages
// FullName:  CPortMonitoringSendThread::ProcessMessages
// Access:    public 
// Returns:   void
// Qualifier:
// Parameter: void
//************************************
void CPortMonitoringSendThread::ProcessMessages(void)
{
	MSG msg;
	::PeekMessage(&msg, NULL, 0, 0, PM_REMOVE);
	::DispatchMessage(&msg);
}

// �˿ڼ��Ӵ�����
//************************************
// Method:    OnPortMonitoringProc
// FullName:  CPortMonitoringSendThread::OnPortMonitoringProc
// Access:    public 
// Returns:   void
// Qualifier:
// Parameter: void
//************************************
void CPortMonitoringSendThread::OnPortMonitoringProc(void)
{
	unsigned short uiPort = 0;
	CString strTemp = _T("");
	unsigned int uiTemp = 0;
	unsigned int uiCommand = 0;
	int iPos = 0;
	// ����˿ڷַ�����
	iPos = 24;
	memcpy(&uiPort, &m_ucudp_buf[m_usudp_count][iPos], FramePacketSize2B);
	if (uiPort == HeadFramePort)
	{
		iPos = 28;
		memcpy(&uiCommand, &m_ucudp_buf[m_usudp_count][iPos], FrameCmdSize1B);
		if (uiCommand == CmdSn)
		{
			iPos += FrameCmdSize1B;
			// ��ʾSN
			for (int j=0; j<FramePacketSize4B; j++)
			{
				strTemp.Format(_T("%02x "), m_ucudp_buf[m_usudp_count][iPos]);
				iPos++;
				m_csHeadFrameShow += strTemp;
			}
			m_csHeadFrameShow += _T("\t");
			// ��ʾ�װ�ʱ��
			iPos = 34;
			for (int k=0; k<FramePacketSize4B; k++)
			{
				strTemp.Format(_T("%02x "), m_ucudp_buf[m_usudp_count][iPos]);
				iPos++;
				m_csHeadFrameShow += strTemp;
			}
			m_csHeadFrameShow += _T("\r\n");
			m_uiHeadFrameNum++;
		}
		else
		{
			strTemp.Format(_T("�װ��˿���ȷ�������ִ��󣬴����������Ϊ%d"), uiCommand);
			m_pLogFile->OnWriteLogFile(_T("CPortMonitoringSendThread::OnPortMonitoringProc"), strTemp, ErrorStatus);
		}
	}
	else if (uiPort == IPSetPort)
	{
		iPos = 28;
		memcpy(&uiCommand, &m_ucudp_buf[m_usudp_count][iPos], FrameCmdSize1B);
		if (uiCommand == CmdSn)
		{
			iPos += FrameCmdSize1B;
			// ��ʾSN
			for (int j=0; j<FramePacketSize4B; j++)
			{
				strTemp.Format(_T("%02x "), m_ucudp_buf[m_usudp_count][iPos]);
				iPos++;
				m_csIPSetReturnShow += strTemp;
			}
			m_csIPSetReturnShow += _T("\t");
			// ��ʾIP
			iPos = 34;
			for (int k=0; k<FramePacketSize4B; k++)
			{
				strTemp.Format(_T("%02x "), m_ucudp_buf[m_usudp_count][iPos]);
				iPos++;
				m_csIPSetReturnShow += strTemp;
			}
			m_csIPSetReturnShow += _T("\r\n");
			m_uiIPSetReturnNum++;
		}
		else
		{
			strTemp.Format(_T("IP��ַ����Ӧ��˿���ȷ�������ִ��󣬴����������Ϊ%d"), uiCommand);
			m_pLogFile->OnWriteLogFile(_T("CPortMonitoringSendThread::OnPortMonitoringProc"), strTemp, ErrorStatus);
		}
	}
	else if (uiPort == TailFramePort)
	{
		iPos = 33;
		memcpy(&uiCommand, &m_ucudp_buf[m_usudp_count][iPos], FrameCmdSize1B);
		if (uiCommand == CmdSn)
		{
			iPos += FrameCmdSize1B;
			// ��ʾSN
			for (int j=0; j<FramePacketSize4B; j++)
			{
				strTemp.Format(_T("%02x "), m_ucudp_buf[m_usudp_count][iPos]);
				iPos++;
				m_csTailFrameShow += strTemp;
			}
			m_csTailFrameShow += _T("\t");

			// ��ʾIP
			iPos = 29;
			for (int k=0; k<FramePacketSize4B; k++)
			{
				strTemp.Format(_T("%02x "),m_ucudp_buf[m_usudp_count][iPos]);
				iPos++;
				m_csTailFrameShow += strTemp;
			}
			m_csTailFrameShow += _T("\r\n");
			m_uiTailFrameNum++;
		}
		else
		{
			strTemp.Format(_T("β���˿���ȷ�������ִ��󣬴����������Ϊ%d"), uiCommand);
			m_pLogFile->OnWriteLogFile(_T("CPortMonitoringSendThread::OnPortMonitoringProc"), strTemp, ErrorStatus);
		}
	}
	else if (uiPort == TailTimeFramePort)
	{
		iPos = 28;
		memcpy(&uiCommand, &m_ucudp_buf[m_usudp_count][iPos], FrameCmdSize1B);
		if (uiCommand == CmdSn)
		{
			iPos += FrameCmdSize1B;
			// ��ʾSN
			for (int j=0; j<FramePacketSize4B; j++)
			{
				strTemp.Format(_T("%02x "),m_ucudp_buf[m_usudp_count][iPos]);
				iPos++;
				m_csTailTimeReturnShow += strTemp;
			}
			m_csTailTimeReturnShow += _T(" ");
			// ��ʾ����ʱ��
			iPos = 34;
			for (int k=0; k<FramePacketSize4B; k++)
			{
				strTemp.Format(_T("%02x "),m_ucudp_buf[m_usudp_count][iPos]);
				iPos++;
				m_csTailTimeReturnShow += strTemp;
			}
			m_csTailTimeReturnShow += _T(" ");
			// ��ʾ����ʱ��
			iPos = 39;
			for (int p=0; p<FramePacketSize4B; p++)
			{
				strTemp.Format(_T("%02x "),m_ucudp_buf[m_usudp_count][iPos]);
				iPos++;
				m_csTailTimeReturnShow += strTemp;
			}
			m_csTailTimeReturnShow += _T("\r\n");
			m_uiTailTimeReturnNum++;
		}
		else
		{
			strTemp.Format(_T("β��ʱ�̲�ѯӦ��˿���ȷ�������ִ��󣬴����������Ϊ%d"), uiCommand);
			m_pLogFile->OnWriteLogFile(_T("CPortMonitoringSendThread::OnPortMonitoringProc"), strTemp, ErrorStatus);
		}
	}
	else if (uiPort == TimeSetPort)
	{
		iPos = 28;
		memcpy(&uiCommand, &m_ucudp_buf[m_usudp_count][iPos], FrameCmdSize1B);
		if (uiCommand == CmdLocalFixedTimeHigh)
		{
			// ��ʾIP
			iPos = 16;
			for (int j=0; j<FramePacketSize4B; j++)
			{
				strTemp.Format(_T("%02x "),m_ucudp_buf[m_usudp_count][iPos]);
				iPos++;
				m_csDelayTimeReturnShow += strTemp;
			}
			m_csDelayTimeReturnShow += _T(" ");

			// ��ʾ��ʱ������λ
			iPos = 29;
			for (int k=0; k<FramePacketSize4B; k++)
			{
				strTemp.Format(_T("%02x "),m_ucudp_buf[m_usudp_count][iPos]);
				iPos++;
				m_csDelayTimeReturnShow += strTemp;
			}
			m_csDelayTimeReturnShow += _T(" ");

			// ��ʾ��ʱ������λ
			iPos = 34;
			for (int p=0; p<FramePacketSize4B; p++)
			{
				strTemp.Format(_T("%02x "),m_ucudp_buf[m_usudp_count][iPos]);
				iPos++;
				m_csDelayTimeReturnShow += strTemp;
			}
			m_csDelayTimeReturnShow += _T("\r\n");
			m_uiDelayTimeReturnNum++;
		}
		else
		{
			strTemp.Format(_T("ʱͳ����Ӧ��˿���ȷ�������ִ��󣬴����������Ϊ%d"), uiCommand);
			m_pLogFile->OnWriteLogFile(_T("CPortMonitoringSendThread::OnPortMonitoringProc"), strTemp, ErrorStatus);
		}
	}
	else if (uiPort == ADSetReturnPort)
	{
		// ÿ�βɼ�ֻ��һ��ADC����Ӧ��֡
		m_uiADCSetReturnNum++;
	}
	else if (uiPort == QueryErrorCodePort)
	{
		unsigned int uiIP = 0;
		unsigned int uiInstrumentNb = 0;
		// ��ʾIP
		iPos = 16;
		for (int j=0; j<FramePacketSize4B; j++)
		{
			strTemp.Format(_T("%02x "),m_ucudp_buf[m_usudp_count][iPos]);
			iPos++;
			m_csErrorCodeReturnShow += strTemp;
		}
		iPos = 16;
		memcpy(&uiIP, &m_ucudp_buf[m_usudp_count][iPos], FramePacketSize4B);
		for (int k=0; k<InstrumentMaxCount; k++)
		{
			if (uiIP == (IPSetAddrStart + k * IPSetAddrInterval))
			{
				uiInstrumentNb = k;
				m_uiErrorCodeReturnCount[uiInstrumentNb]++;
				break;
			}
		}
		iPos = 33;
		memcpy(&uiCommand, &m_ucudp_buf[m_usudp_count][iPos], FrameCmdSize1B);
		if (uiCommand == CmdFDUErrorCode)
		{
			iPos += FrameCmdSize1B;
			m_csErrorCodeReturnShow += _T("\t");
			for (int j=0; j<FramePacketSize4B; j++)
			{
				strTemp.Format(_T("%02x "),m_ucudp_buf[m_usudp_count][iPos]);
				iPos++;
				m_csErrorCodeReturnShow += strTemp;
			}
			m_csErrorCodeReturnShow += _T("\t");
			if (m_uiErrorCodeReturnCount[uiInstrumentNb] == 1)
			{
				iPos = 34;
				for (int j=0; j<FramePacketSize4B; j++)
				{
					m_ucErrorCodeReturn[uiInstrumentNb][j] = m_ucudp_buf[m_usudp_count][iPos];
					strTemp.Format(_T("%02x "), m_ucudp_buf[m_usudp_count][iPos]);
					iPos++;
					m_csErrorCodeReturnShow += strTemp;
				}
			}
			else
			{
				iPos = 34;
				for (int j=0; j<FramePacketSize4B; j++)
				{
					if (m_ucudp_buf[m_usudp_count][iPos] < m_ucErrorCodeReturn[uiInstrumentNb][j])
					{
						uiTemp = 256 + m_ucudp_buf[m_usudp_count][iPos] - m_ucErrorCodeReturn[uiInstrumentNb][j];
					}
					else
					{
						uiTemp = m_ucudp_buf[m_usudp_count][iPos] - m_ucErrorCodeReturn[uiInstrumentNb][j] ;
					}
					m_ucErrorCodeReturn[uiInstrumentNb][j] = m_ucudp_buf[m_usudp_count][iPos];
					strTemp.Format(_T("%02x "), uiTemp);
					iPos++;
					m_csErrorCodeReturnShow += strTemp;
				}
			}
			m_csErrorCodeReturnShow += _T("\r\n");
		}
		else if (uiCommand == CmdLAUXErrorCode1)
		{
			m_csErrorCodeReturnShow += _T("\t");
			iPos = 34;
			for (int j=0; j<FramePacketSize4B; j++)
			{
				strTemp.Format(_T("%02x "),m_ucudp_buf[m_usudp_count][iPos]);
				iPos++;
				if (iPos == 36)
				{
					iPos = 39;
				}
				m_csErrorCodeReturnShow += strTemp;
			}
			m_csErrorCodeReturnShow += _T("\t");
			if (m_uiErrorCodeReturnCount[uiInstrumentNb] == 1)
			{
				iPos = 34;
				for (int j=0; j<FramePacketSize4B; j++)
				{
					m_ucErrorCodeReturn[uiInstrumentNb][j] = m_ucudp_buf[m_usudp_count][iPos];
					strTemp.Format(_T("%02x "), m_ucudp_buf[m_usudp_count][iPos]);
					iPos++;
					if (iPos == 36)
					{
						iPos = 39;
					}
					m_csErrorCodeReturnShow += strTemp;
				}
			}
			else
			{
				iPos = 34;
				for (int j=0; j<FramePacketSize4B; j++)
				{
					if (m_ucudp_buf[m_usudp_count][iPos] < m_ucErrorCodeReturn[uiInstrumentNb][j])
					{
						uiTemp = 256 + m_ucudp_buf[m_usudp_count][iPos] - m_ucErrorCodeReturn[uiInstrumentNb][j];
					}
					else
					{
						uiTemp = m_ucudp_buf[m_usudp_count][iPos] - m_ucErrorCodeReturn[uiInstrumentNb][j] ;
					}
					m_ucErrorCodeReturn[uiInstrumentNb][j] = m_ucudp_buf[m_usudp_count][iPos];
					strTemp.Format(_T("%02x "), uiTemp);
					iPos++;
					if (iPos == 36)
					{
						iPos = 39;
					}
					m_csErrorCodeReturnShow += strTemp;
				}
			}
			m_csErrorCodeReturnShow += _T("\r\n");
		}
		else
		{
			strTemp.Format(_T("�����ѯӦ��˿���ȷ�������ִ��󣬴����������Ϊ%d"), uiCommand);
			m_pLogFile->OnWriteLogFile(_T("CPortMonitoringSendThread::OnPortMonitoringProc"), strTemp, ErrorStatus);
		}
		m_uiErrorCodeReturnNum++;
	}
	else if (uiPort == CollectSysTimePort)
	{
		m_uiCollectSysTimeReturnNum++;
	}
	else if (uiPort == ADRecPort)
	{
		m_uiADCRecNum++;
	}
	else
	{
		strTemp.Format(_T("����Ķ˿ں�%d"), uiPort);
		m_pLogFile->OnWriteLogFile(_T("CPortMonitoringSendThread::OnPortMonitoringProc"), strTemp, ErrorStatus);
	}
	m_uiRecFrameNum++;
	if (m_bPortDistribution == TRUE)
	{
		addr2.sin_family = AF_INET;											// ����׽��ֵ�ַ�ṹ
		addr2.sin_port = htons(uiPort);
		addr2.sin_addr.S_un.S_addr = inet_addr(ConvertCStringToConstCharPointer(m_csIP));

		// �����˿ڷַ�����
		sendto(m_SendSocket, (const char*)&m_ucudp_buf[m_usudp_count], RcvFrameSize, 0, (sockaddr*)&addr2, sizeof(addr2));
	}
	else
	{
		addr2.sin_family = AF_INET;											// ����׽��ֵ�ַ�ṹ
		addr2.sin_port = htons(m_iSendPort);
		addr2.sin_addr.S_un.S_addr = inet_addr(ConvertCStringToConstCharPointer(m_csIP));

		sendto(m_SendSocket, (const char*)&m_ucudp_buf[m_usudp_count], RcvFrameSize, 0, (sockaddr*)&addr2, sizeof(addr2));
	}
	m_pSaveFile->OnSaveSendData(m_ucudp_buf[m_usudp_count],RcvFrameSize);
}
// �ر�UDP�׽���
void CPortMonitoringSendThread::OnCloseUDP(void)
{
	shutdown(m_SendSocket, SD_BOTH);
	closesocket(m_SendSocket);
	m_SendSocket = INVALID_SOCKET;
}
