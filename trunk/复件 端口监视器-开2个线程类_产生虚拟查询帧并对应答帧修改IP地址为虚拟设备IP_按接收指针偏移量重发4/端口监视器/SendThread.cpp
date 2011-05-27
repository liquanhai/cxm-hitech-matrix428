// SendThread.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "�˿ڼ�����.h"
#include "SendThread.h"
#include "Parameter.h"

// CSendThread

IMPLEMENT_DYNCREATE(CSendThread, CWinThread)

CSendThread::CSendThread()
: m_uiADCFrameCount(0)
, m_uiSendADCRetransmissionFramNum(0)
, m_uiUdpCount(0)
, m_uiRcvByte(0)
{
	
}

CSendThread::~CSendThread()
{

}

BOOL CSendThread::InitInstance()
{
	// TODO: �ڴ�ִ���������̳߳�ʼ��
	return TRUE;
}

int CSendThread::ExitInstance()
{
	// TODO: �ڴ�ִ���������߳�����
	return CWinThread::ExitInstance();
}

BEGIN_MESSAGE_MAP(CSendThread, CWinThread)
END_MESSAGE_MAP()


// ��ʼ��

void CSendThread::Init()
{
	udp_count = 0;
	m_close = false;
	m_oADCLostMap.RemoveAll();
	m_oADCSendMap.RemoveAll();
// 	int flag =  m_hSocket2.Create(RcvPort2,SOCK_DGRAM);
// 	m_hSocket2.SetSockOpt(SO_RCVBUF,&m_hSocket2,RcvBufSize,SOL_SOCKET);
// 	m_hSocket2.SetSockOpt(SO_SNDBUF,&m_hSocket2,SndBufSize,SOL_SOCKET);
	int            nValidSocket;
	struct sockaddr_in HostIP;
	HostIP.sin_family = AF_INET;
	HostIP.sin_addr.S_un.S_addr = inet_addr("192.168.0.11");
	HostIP.sin_port = htons(RcvPort2);
	m_hSocket = socket(AF_INET,SOCK_DGRAM,IPPROTO_UDP);
	if(SOCKET_ERROR == bind(m_hSocket,(struct sockaddr*)&HostIP,sizeof(HostIP)))
	{
		AfxMessageBox("�˿ڴ���ʧ��1��");
	}
	// ���ջ�������С
	nValidSocket = RcvBufSize;	
	if (setsockopt(m_hSocket, SOL_SOCKET, SO_RCVBUF, (char*)&nValidSocket, sizeof(nValidSocket)) == SOCKET_ERROR) 
	{
		closesocket(m_hSocket);
		AfxMessageBox("�˿ڴ���ʧ��2��");
	}
	// ��Ϊ��ʱ���������ͻ�������С
	nValidSocket = SndBufSize;	
	if (setsockopt(m_hSocket, SOL_SOCKET, SO_SNDBUF, (char*)&nValidSocket, sizeof(nValidSocket)) == SOCKET_ERROR) 
	{
		closesocket(m_hSocket);
		AfxMessageBox("�˿ڴ���ʧ��3��");
	}
}
// �̺߳�����Run��ִ��
int CSendThread::Run()
{
	unsigned short	usPort = 0;
	unsigned int	uiIPAim = 0;			// Ŀ��IP��ַ
	unsigned short	usDataPointNow = 0;		// ָ��ƫ����
	unsigned short	usCommand = 0;			// ������
	DWORD dwFrameCount = 0;
	DWORD dwTmp = 0;
	int icount = 0;
	// ѭ����ֱ���رձ�־Ϊ��
	while(true)
	{
		if (m_close == true)
		{
			break;
		}

		DWORD dwFrameCount = 0;

		// �õ�������ջ����������ֽ���
//		m_hSocket2.IOCtl(FIONREAD, &dwFrameCount);
		icount = recvfrom(m_hSocket,(char *)m_ucUdpBuf,163840,0,NULL,NULL);
//		if(dwFrameCount > 0) 
		if (icount > 0)
		{
			m_uiRcvByte += icount;
//			icount = m_hSocket2.Receive(m_ucUdpBuf,16384);
		
			for (int i=0; i<icount; i++)
			{
				switch(m_uiUdpCount)
				{
				case 0:
					if (m_ucUdpBuf[i] == 0x11)
					{
						udp_buf[udp_count][0] = m_ucUdpBuf[i];
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
					if (m_ucUdpBuf[i] == 0x22)
					{
						udp_buf[udp_count][1] = m_ucUdpBuf[i];
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
					if (m_ucUdpBuf[i] == 0x33)
					{
						udp_buf[udp_count][2] = m_ucUdpBuf[i];
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
					if (m_ucUdpBuf[i] == 0x44)
					{
						udp_buf[udp_count][3] = m_ucUdpBuf[i];
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
					udp_buf[udp_count][m_uiUdpCount] = m_ucUdpBuf[i];
					m_uiUdpCount++;
					if (m_uiUdpCount == 256)
					{
						m_uiUdpCount = 0;
						
						// ����˿ڷַ�����
						usPort = 0;
						memcpy(&usPort, &udp_buf[udp_count][24], 2);
						usCommand = 0;
						memcpy(&usCommand, &udp_buf[udp_count][26], 2);
						// ͨ���������ж���ADC��������
						if (usCommand == ADCRetransmissionCmd)
						{
							uiIPAim = 0;			// Ŀ��IP��ַ
							memcpy(&uiIPAim, &udp_buf[udp_count][16], 4);
							usDataPointNow = 0;		// ָ��ƫ����
							memcpy(&usDataPointNow, &udp_buf[udp_count][28], 2);
							m_uiADCFrameCount++;
							if (pDlg->m_bStartSample == TRUE)
							{
								// ��ADC�����������������ط�
								OnADCDataRetransmission(uiIPAim, usDataPointNow);
							}
						}

						sockaddr_in MainCrsAddr;
						MainCrsAddr.sin_family = AF_INET;
						MainCrsAddr.sin_port = htons(usPort);
						MainCrsAddr.sin_addr.s_addr = inet_addr(pDlg->m_strSendIP);
						int icount = sendto(m_hSocket,(char*)udp_buf[udp_count],256,0,(sockaddr*)&MainCrsAddr,sizeof(sockaddr_in));	
			/*			m_hSocket2.SendTo(udp_buf[udp_count],256,usPort,pDlg->m_strSendIP);*/
						pDlg->OnSaveSendData(udp_buf[udp_count],256);
						udp_count +=1;
						udp_count = udp_count%8;
						if (pDlg->m_bStartSample == TRUE)
						{
							SendADCDataRetransmissionFrame();
						}
					}
					break;
				}
			}
		}
	/*	SendADCDataRetransmissionFrame();*/
		if (m_close == true)
		{
			break;
		}
		Sleep(1);
	}
	
	// ����
	return CWinThread::Run();
}
void CSendThread::OnClose()
{
// 	m_hSocket2.ShutDown(2);
// 	m_hSocket2.Close();
	closesocket(m_hSocket);
	m_oADCLostMap.RemoveAll();
	m_oADCSendMap.RemoveAll();
	m_close = true;
}
// ����ADC�����ط�
void CSendThread::OnADCDataRetransmission(unsigned int uiIPAim, unsigned short usDataPointNb)
{
	m_structADC ADCFindFromStruct;
	unsigned int uiIPAimForTest = 0;
	// ���յ���ADC���ݲ����ط�����
	if (m_oADCLostMap.Lookup(usDataPointNb, ADCFindFromStruct) == NULL)
	{
		OnListCountAdd();
		m_structADC ADCDataStruct;
		ADCDataStruct.uiRetransmissionNum = 0;
		ADCDataStruct.uiFrameCount = 0;
		ADCDataStruct.uiIPAim = uiIPAim;
		m_oADCLostMap.SetAt(usDataPointNb, ADCDataStruct);
		m_oADCSendMap.SetAt(usDataPointNb, ADCDataStruct);
	}
	else
	{
		// ���Ϊ�ط��������޸�IP��ַΪ��������IP��ַ
		ADCFindFromStruct.uiRetransmissionNum++;
		uiIPAimForTest = uiIPAim + ADCFindFromStruct.uiRetransmissionNum * 10;
		memcpy(&udp_buf[udp_count][16], &uiIPAimForTest, 4);
		if (ADCFindFromStruct.uiRetransmissionNum == InstrumentForTest)
		{
			m_oADCLostMap.RemoveKey(usDataPointNb);
		}
		else
		{
			m_oADCLostMap.SetAt(usDataPointNb, ADCFindFromStruct);
		}
	}
}

// ����ADC�����ط�֡
void CSendThread::MakeADCDataRetransmissionFrame(unsigned int uiIPAim, unsigned short usDataPointNb)
{
	unsigned int uiIPSource =	0;
	unsigned int usPortAim	=	0;
	unsigned int usCommand	=	0;
	m_ucADCRetransmission[0] = 0x11;
	m_ucADCRetransmission[1] = 0x22;
	m_ucADCRetransmission[2] = 0x33;
	m_ucADCRetransmission[3] = 0x44;
	m_ucADCRetransmission[4] = 0x00;
	m_ucADCRetransmission[5] = 0x00;
	m_ucADCRetransmission[6] = 0x00;
	m_ucADCRetransmission[7] = 0x00;
	m_ucADCRetransmission[8] = 0x00;
	m_ucADCRetransmission[9] = 0x00;
	m_ucADCRetransmission[10] = 0x00;
	m_ucADCRetransmission[11] = 0x00;
	m_ucADCRetransmission[12] = 0x00;
	m_ucADCRetransmission[13] = 0x00;
	m_ucADCRetransmission[14] = 0x00;
	m_ucADCRetransmission[15] = 0x00;


	uiIPSource	=	inet_addr("127.0.0.1");
	usPortAim	=	ADRecPort;
	usCommand	=	ADCRetransmissionCmd;
	// ԴIP��ַ
	memcpy(&m_ucADCRetransmission[16], &uiIPSource, 4);
	// Ŀ��IP��ַ
	memcpy(&m_ucADCRetransmission[20], &uiIPAim, 4);
	// Ŀ��˿ں�
	memcpy(&m_ucADCRetransmission[24], &usPortAim, 2);
	// ����� 1-��������Ӧ��2-��ѯ����Ӧ��3-AD���������ط�
	memcpy(&m_ucADCRetransmission[26], &usCommand, 2);

	int iPos = 32;

	memmove(m_ucADCRetransmission + iPos, &usDataPointNb, 2);
	iPos = iPos + 2;
	m_ucADCRetransmission[iPos] = 0x00;


	sockaddr_in MainCrsAddr;
	MainCrsAddr.sin_family = AF_INET;
	MainCrsAddr.sin_port = htons(SendPort1);
	MainCrsAddr.sin_addr.s_addr = inet_addr(pDlg->m_strReceiveIP);
	int icount = sendto(m_hSocket,(char*)m_ucADCRetransmission,128,0,(sockaddr*)&MainCrsAddr,sizeof(sockaddr_in));	
//	int icount = m_hSocket2.SendTo(m_ucADCRetransmission, 128, SendPort1, pDlg->m_strReceiveIP);
}
// �����е�ÿ���ṹ���֡������һ
void CSendThread::OnListCountAdd(void)
{
	POSITION pos = m_oADCLostMap.GetStartPosition();	// �õ���������ʼλ��
	unsigned int uiKey;									// ������	

	while(NULL != pos)
	{
		m_structADC ADCStructTemp;	
		m_oADCLostMap.GetNextAssoc(pos, uiKey, ADCStructTemp);	// �õ���������
		ADCStructTemp.uiFrameCount++;
		if (ADCStructTemp.uiFrameCount == ClearListFrameCount)
		{
			m_oADCLostMap.RemoveKey(uiKey);
		} 
		else
		{
			m_oADCLostMap.SetAt(uiKey, ADCStructTemp);
		}
	}
}

// ����ADC�����ط�֡
void CSendThread::SendADCDataRetransmissionFrame(void)
{
	// �����ط�֡

	POSITION pos = m_oADCSendMap.GetStartPosition();	// �õ���������ʼλ��
	unsigned int uiKey;					// ������	

	if (NULL != pos)
	{
		m_structADC ADCStructTemp;	
		m_oADCSendMap.GetNextAssoc(pos, uiKey, ADCStructTemp);	// �õ���������

		for (int i=0; i<SendADCFrameCountMax; i++)
		{
			MakeADCDataRetransmissionFrame(ADCStructTemp.uiIPAim, uiKey);
			ADCStructTemp.uiRetransmissionNum++;
			m_uiSendADCRetransmissionFramNum++;
			if (ADCStructTemp.uiRetransmissionNum == InstrumentForTest)
			{
				m_oADCSendMap.RemoveKey(uiKey);
				return;
			}
		}
		m_oADCSendMap.SetAt(uiKey, ADCStructTemp);	
	}
}
