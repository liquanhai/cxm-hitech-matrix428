// SendThread.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "�˿ڼ�����.h"
#include "SendThread.h"
#include "Parameter.h"

// CSendThread

IMPLEMENT_DYNCREATE(CSendThread, CWinThread)

CSendThread::CSendThread()
: m_uiFrameTimeCount(0)
, m_usDataPointPrevious(0)
, m_uiADCFrameCount(0)
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
	unsigned int uiInstrumentTest = InstrumentForTest;
	unsigned int uiFrameCount = ClearListFrameCount;
	m_uiFrameTimeCount = uiInstrumentTest * uiFrameCount;
	udp_count = 0;
	m_close = false;
	m_listADC.RemoveAll();
	int flag =  m_hSocket2.Create(RcvPort2,SOCK_DGRAM);
	m_hSocket2.SetSockOpt(SO_RCVBUF,&m_hSocket2,RcvBufSize,SOL_SOCKET);
	m_hSocket2.SetSockOpt(SO_SNDBUF,&m_hSocket2,SndBufSize,SOL_SOCKET);
}
// �̺߳�����Run��ִ��
int CSendThread::Run()
{
	unsigned short	usPort = 0;
	unsigned int	uiIPAim = 0;			// Ŀ��IP��ַ
	unsigned short	usDataPointNow = 0;		// ָ��ƫ����
	unsigned short	usCommand = 0;			// ������
	DWORD dwFrameCount = 0;
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
		m_hSocket2.IOCtl(FIONREAD, &dwFrameCount);
		dwFrameCount = dwFrameCount/256;
		if(0 != dwFrameCount)	
		{
			for(unsigned int i = 0; i < dwFrameCount; i++)	// ���μ��ÿ������IP����Ӧ��֡
			{

				icount = m_hSocket2.Receive(udp_buf[udp_count],256);
				if (icount == 256)
				{
					usPort = 0;
					// ����˿ڷַ�����
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

						// ��ADC�����������������ط�
						OnADCDataRetransmission(uiIPAim, usDataPointNow, usPort);
					}
					
					m_hSocket2.SendTo(udp_buf[udp_count],256,usPort,pDlg->m_strSendIP);
					pDlg->OnSaveSendData(udp_buf[udp_count],256);
					udp_count +=1;
					udp_count = udp_count%8;
				}
				else
				{
					break;
				}
			}
		}

		if (m_close == true)
		{
			break;
		}
		Sleep(50);
	}
	
	// ����
	return CWinThread::Run();
}
void CSendThread::OnClose()
{
	m_hSocket2.ShutDown(2);
	m_hSocket2.Close();
	m_listADC.RemoveAll();
	m_close = true;
}
// ����ADC�����ط�
void CSendThread::OnADCDataRetransmission(unsigned int uiIPAim, unsigned short usDataPointNb, unsigned short usPort)
{
	m_structADC ADCFindFromStruct;
	POSITION pos;
	unsigned int uiIPAimForTest = 0;
	ADCFindFromStruct.uiIPAim = uiIPAim;
	ADCFindFromStruct.usDataPointNb = usDataPointNb;
	pos = m_listADC.Find(ADCFindFromStruct, NULL);
	// ���յ���ADC���ݲ����ط�����
	if (pos == NULL)
	{

		m_uiADCFrameCount++;
		if (m_uiADCFrameCount == 1)
		{
			m_usDataPointPrevious = usDataPointNb;
		}
		else
		{
			m_usDataPointPrevious += 74;
			if (m_usDataPointPrevious > 2048)
			{
				m_usDataPointPrevious -= 2048;
			}
		}
		OnListCountAdd();
		m_structADC ADCDataStruct;
		ADCDataStruct.uiIPAim = uiIPAim;
		ADCDataStruct.usDataPointNb = m_usDataPointPrevious;
		ADCDataStruct.uiRetransmissionNum = 0;
		m_listADC.AddTail(ADCDataStruct);
		// �����ط�֡
		for (int i=0; i<InstrumentForTest; i++)
		{
			MakeADCDataRetransmissionFrame(uiIPAim, m_usDataPointPrevious, usPort);
			Sleep(1);
		}
	}
	else
	{
		// ���Ϊ�ط��������޸�IP��ַΪ��������IP��ַ

		m_structADC ADCDataStruct;
		ADCDataStruct = m_listADC.GetAt(pos);
		ADCDataStruct.uiRetransmissionNum ++;
		m_listADC.SetAt(pos, ADCDataStruct);
		uiIPAimForTest = uiIPAim + ADCDataStruct.uiRetransmissionNum * 10;
		memcpy(&udp_buf[udp_count][16], &uiIPAimForTest, 4);
		if (ADCDataStruct.uiRetransmissionNum == InstrumentForTest)
		{
			m_listADC.RemoveAt(pos);
		}
	}
}

// ����ADC�����ط�֡
void CSendThread::MakeADCDataRetransmissionFrame(unsigned int uiIPAim, unsigned short usDataPointNb, unsigned short usPort)
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
	usPortAim	=	usPort;
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

	int icount = m_hSocket2.SendTo(m_ucADCRetransmission, 128, SendPort1, pDlg->m_strReceiveIP);
}
// �����е�ÿ���ṹ���֡������һ
void CSendThread::OnListCountAdd(void)
{
	POSITION pos = m_listADC.GetHeadPosition();
	int icount = m_listADC.GetCount();
	m_structADC ADCStructTemp;
	for (int i = 0; i < icount; i++)
	{
		ADCStructTemp = m_listADC.GetNext(pos);
		ADCStructTemp.uiFrameCount++;
		if (ADCStructTemp.uiFrameCount == m_uiFrameTimeCount)
		{
			m_listADC.RemoveAt(pos);
			icount--;
		}
	} 
}
