#include "StdAfx.h"
#include "ThreadManage.h"

// ����β��ʱ�̲�ѯ֡����
unsigned int m_uiSendTailTimeFrameCount;
// ���յ���β��ʱ�̲�ѯ֡����
unsigned int m_uiRecTailTimeFrameCount;

CThreadManage::CThreadManage(void)
{
}

CThreadManage::~CThreadManage(void)
{
}

// ��ʼ��
void CThreadManage::OnInit(void)
{
	m_oInstrumentList.OnInit();
	m_HeadFrameSocket.m_oInstrumentList = &m_oInstrumentList;
	m_IPSetSocket.m_oInstrumentList = &m_oInstrumentList;
	m_TailFrameSocket.m_oInstrumentList = &m_oInstrumentList;
	m_TailTimeFrameSocket.m_oInstrumentList = &m_oInstrumentList;

	m_oHeartBeatThread.OnInit();
	m_oHeartBeatThread.CreateThread();
	m_oHeartBeatThread.SuspendThread();

	OnCreateHeadSocket();
	OnCreateIPSetSocket();
	OnCreateTailSocket();
	OnCreateTailTimeSocket();
	OnCreateADCDataSocket();

	for (int i=0; i<GraphViewNum; i++)
	{
		m_ADCDataSocket.m_uiDataFrameNum[i] = 0;
		m_ADCDataSocket.m_uiDataPointLast[i] = 0;
	}
	
	// ����β��ʱ�̲�ѯ֡����
	m_uiSendTailTimeFrameCount = 0;
	// ���յ���β��ʱ�̲�ѯ֡����
	m_uiRecTailTimeFrameCount = 0;
}

// �رղ������߳�
void CThreadManage::OnClose(void)
{
	int iResult = 0;
	m_oHeartBeatThread.OnClose();
	iResult = ::WaitForSingleObject(m_oHeartBeatThread.m_hHeartBeatThreadClose,550);
	if (iResult != WAIT_OBJECT_0)
	{
		AfxMessageBox(_T("�����߳���300ms��δ������������"));
	}

	m_HeadFrameSocket.Close();
	m_IPSetSocket.Close();
	m_ADCDataSocket.Close();
	m_TailFrameSocket.Close();
	m_TailTimeFrameSocket.Close();
	m_oInstrumentList.OnClose();
}

// ��
void CThreadManage::OnOpen(void)
{
	m_oInstrumentList.OnInit();
	m_oInstrumentList.OnOpen();
	m_oHeartBeatThread.ResumeThread();
	m_oHeartBeatThread.OnOpen();

	OnCreateHeadSocket();
	OnCreateIPSetSocket();
	OnCreateTailSocket();
	OnCreateTailTimeSocket();
	OnCreateADCDataSocket();

	// ����β��ʱ�̲�ѯ֡����
	m_uiSendTailTimeFrameCount = 0;
	// ���յ���β��ʱ�̲�ѯ֡����
	m_uiRecTailTimeFrameCount = 0;
	
	OnCreateCollectSysTimeBroadcastSocket();
}

// ֹͣ
void CThreadManage::OnStop(void)
{
	m_oInstrumentList.OnStop();

	m_oHeartBeatThread.SuspendThread();
	m_oHeartBeatThread.OnStop();

	m_ADCDataSocket.Close();
	m_HeadFrameSocket.Close();
	m_IPSetSocket.Close();
	m_TailFrameSocket.Close();
	m_TailTimeFrameSocket.Close();
	m_oSysTimeSocket.Close();
}

// ������ѯ�ɼ�վ����ʱ��Ĺ㲥�˿�
void CThreadManage::OnCreateCollectSysTimeBroadcastSocket(void)
{
	m_oSysTimeSocket.Close();
	BOOL bReturn = FALSE;
	// ��������˿ڣ����շ�������Ӧ��֡��create����д�����������IP��ַ����չ̶�IP��ַ���͵�֡����д��ȫ������
	bReturn = m_oSysTimeSocket.Create(CollectSysTimePort, SOCK_DGRAM);
	if (bReturn == FALSE)
	{
		AfxMessageBox(_T("����㲥�˿ڴ���ʧ�ܣ�"));
	}

	//���ù㲥ģʽ
	int	iOptval, iOptlen;
	iOptlen = sizeof(int);
	iOptval = 1;
	m_oSysTimeSocket.SetSockOpt(SO_BROADCAST, &iOptval, iOptlen, SOL_SOCKET);
}

// ���ɲɼ�վ����ʱ���ѯ֡
void CThreadManage::MakeCollectSysTimeFrameData(unsigned int uiTestNb)
{
	unsigned int uiIPSource =	0;
	unsigned int uiIPAim	=	0;
	unsigned int usPortAim	=	0;
	unsigned int usCommand	=	0;
	m_cCollectSysTimeSendData[0] = 0x11;
	m_cCollectSysTimeSendData[1] = 0x22;
	m_cCollectSysTimeSendData[2] = 0x33;
	m_cCollectSysTimeSendData[3] = 0x44;
	m_cCollectSysTimeSendData[4] = 0x00;
	m_cCollectSysTimeSendData[5] = 0x00;
	m_cCollectSysTimeSendData[6] = 0x00;
	m_cCollectSysTimeSendData[7] = 0x00;
	m_cCollectSysTimeSendData[8] = 0x00;
	m_cCollectSysTimeSendData[9] = 0x00;
	m_cCollectSysTimeSendData[10] = 0x00;
	m_cCollectSysTimeSendData[11] = 0x00;
	m_cCollectSysTimeSendData[12] = 0x00;
	m_cCollectSysTimeSendData[13] = 0x00;
	m_cCollectSysTimeSendData[14] = 0x00;
	m_cCollectSysTimeSendData[15] = 0x00;
	
	CString str;
	str = m_oSysTimeSocket.m_csIPSource;
	uiIPSource	=	inet_addr(str);
	for (int i=0; i<GraphViewNum; i++)
	{
		if ((uiTestNb & (0x01<<i)) != 0)
		{
			uiIPAim	= 111 - 10*i;
			break;
		}
	}
	/*	uiIPAim = 111;*/
	usPortAim	=	CollectSysTimePort;
	usCommand	=	2;
	// ԴIP��ַ
	memcpy(&m_cCollectSysTimeSendData[16], &uiIPSource, 4);
	// Ŀ��IP��ַ
	memcpy(&m_cCollectSysTimeSendData[20], &uiIPAim, 4);
	TRACE1("β��ʱ�̲�ѯ֡-����IP��ַ��%d\r\n", uiIPAim);
	// Ŀ��˿ں�
	memcpy(&m_cCollectSysTimeSendData[24], &usPortAim, 2);
	// ����� 1-��������Ӧ��2-��ѯ����Ӧ��3-AD���������ط�
	memcpy(&m_cCollectSysTimeSendData[26], &usCommand, 2);

	int iPos = 32;

	// ������0x04��ȡ����ϵͳʱ��
	m_cCollectSysTimeSendData[iPos] = 0x04;
	iPos++;
	memset(&m_cCollectSysTimeSendData[iPos], 0, 4);
	iPos = iPos + 4;

	// ���������ֽ���
	m_cCollectSysTimeSendData[iPos] = 0x00;

}

// ���Ͳɼ�վ����ʱ���ѯ֡
void CThreadManage::SendCollectSysTimeFrameToSocket(void)
{
	// ����֡
	int iCount = m_oSysTimeSocket.SendTo(m_cCollectSysTimeSendData, 128, m_oSysTimeSocket.m_uiSendPort, IPBroadcastAddr);
}

// �����װ�Socket
void CThreadManage::OnCreateHeadSocket(void)
{
	m_HeadFrameSocket.Close();
	BOOL flag = FALSE; 
	flag =  m_HeadFrameSocket.Create(HeadFramePort,SOCK_DGRAM);
	if (flag == FALSE)
	{
		AfxMessageBox(_T("�װ����ն˿ڴ���ʧ�ܣ�"));
	}
	//���ù㲥ģʽ
	int	iOptval, iOptlen;
	iOptlen = sizeof(int);
	iOptval = 1;
	m_HeadFrameSocket.SetSockOpt(SO_BROADCAST, &iOptval, iOptlen, SOL_SOCKET);
}

// ����IP��ַ����Socket
void CThreadManage::OnCreateIPSetSocket(void)
{
	m_IPSetSocket.Close();
	BOOL flag = FALSE;
	// ��������˿ڣ����շ�������Ӧ��֡��create����д�����������IP��ַ����չ̶�IP��ַ���͵�֡����д��ȫ������
	flag = m_IPSetSocket.Create(IPSetPort, SOCK_DGRAM);
	if (flag == FALSE)
	{
		AfxMessageBox(_T("IP��ַ���ö˿ڴ���ʧ�ܣ�"));
	}
}

// ����β��Socket
void CThreadManage::OnCreateTailSocket(void)
{
	m_TailFrameSocket.Close();
	BOOL flag = FALSE; 
	flag =  m_TailFrameSocket.Create(TailFramePort,SOCK_DGRAM);
	if (flag == FALSE)
	{
		AfxMessageBox(_T("β�����ն˿ڴ���ʧ�ܣ�"));
	}

	//���ù㲥ģʽ
	int	iOptval, iOptlen;
	iOptlen = sizeof(int);
	iOptval = 1;
	m_TailFrameSocket.SetSockOpt(SO_BROADCAST, &iOptval, iOptlen, SOL_SOCKET);

}

// ����β��ʱ�̲�ѯ��ʱͳSocket
void CThreadManage::OnCreateTailTimeSocket(void)
{
	m_TailTimeFrameSocket.Close();
	BOOL flag = FALSE;
	// ��������˿ڣ����շ�������Ӧ��֡��create����д�����������IP��ַ����չ̶�IP��ַ���͵�֡����д��ȫ������
	flag = m_TailTimeFrameSocket.Create(TailTimeFramePort, SOCK_DGRAM);
	if (flag == FALSE)
	{
		AfxMessageBox(_T("β��ʱ�̲�ѯ��ʱͳ�˿ڴ���ʧ�ܣ�"));
	}
	//���ù㲥ģʽ
	int	iOptval, iOptlen;
	iOptlen = sizeof(int);
	iOptval = 1;
	m_TailTimeFrameSocket.SetSockOpt(SO_BROADCAST, &iOptval, iOptlen, SOL_SOCKET);
}

// ����ADC���ݽ���Socket
void CThreadManage::OnCreateADCDataSocket(void)
{
	m_ADCDataSocket.Close();
	BOOL flag = FALSE; 
	flag =  m_ADCDataSocket.Create(ADRecPort,SOCK_DGRAM);
	if (flag == FALSE)
	{
		AfxMessageBox(_T("ADC���ݽ��ն˿ڴ���ʧ�ܣ�"));
	}
}
