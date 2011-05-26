#include "StdAfx.h"
#include "ThreadManage.h"

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
	m_oHeadFrameThread.m_oInstrumentList = &m_oInstrumentList;
	m_oTailFrameThread.m_oInstrumentList = &m_oInstrumentList; 

	m_oHeartBeatThread.OnInit();
	m_oHeartBeatThread.CreateThread();
	m_oHeartBeatThread.SuspendThread();

	m_oADDataThread.OnInit();
	m_oADDataThread.CreateThread();
	m_oADDataThread.SuspendThread();

	m_oHeadFrameThread.OnInit();
	m_oHeadFrameThread.CreateThread();
	m_oHeadFrameThread.SuspendThread();

	m_oTailFrameThread.OnInit();
	m_oTailFrameThread.CreateThread();
	m_oTailFrameThread.SuspendThread();
}

// �رղ������߳�
void CThreadManage::OnClose(void)
{
	int iResult = 0;
	m_oHeartBeatThread.OnClose();
	iResult = ::WaitForSingleObject(m_oHeartBeatThread.m_hHeartBeatThreadClose,300);
	if (iResult != WAIT_OBJECT_0)
	{
		AfxMessageBox(_T("�����߳���300ms��δ������������"));
	}
	m_oHeadFrameThread.OnClose();
	iResult = ::WaitForSingleObject(m_oHeadFrameThread.m_hHeadFrameThreadClose,300);
	if (iResult != WAIT_OBJECT_0)
	{
		AfxMessageBox(_T("�װ��߳���300ms��δ������������"));
	}
	m_oADDataThread.OnClose();
	iResult = ::WaitForSingleObject(m_oADDataThread.m_hADDDataThreadClose,100);
	if (iResult != WAIT_OBJECT_0)
	{
		AfxMessageBox(_T("���ݲɼ��߳���100ms��δ������������"));
	}
	m_oTailFrameThread.OnClose();
	iResult = ::WaitForSingleObject(m_oTailFrameThread.m_hTailFrameThreadClose,300);
	if (iResult != WAIT_OBJECT_0)
	{
		AfxMessageBox(_T("β���߳���300ms��δ������������"));
	}
	m_oInstrumentList.OnClose();

}

// ��
void CThreadManage::OnOpen(void)
{
	m_oInstrumentList.OnInit();
	m_oInstrumentList.OnOpen();
	m_oHeartBeatThread.ResumeThread();
	m_oHeartBeatThread.OnOpen();

	m_oADDataThread.ResumeThread();
	m_oADDataThread.OnOpen();

	m_oHeadFrameThread.ResumeThread();
	m_oHeadFrameThread.OnOpen();

	m_oTailFrameThread.ResumeThread();
	m_oTailFrameThread.OnOpen();
	
	OnCreateCollectSysTimeBroadcastSocket();
}

// ֹͣ
void CThreadManage::OnStop(void)
{
	m_oInstrumentList.OnStop();

	m_oHeartBeatThread.SuspendThread();
	m_oHeartBeatThread.OnStop();

	m_oADDataThread.SuspendThread();
	m_oADDataThread.OnStop();

	m_oHeadFrameThread.SuspendThread();
	m_oHeadFrameThread.OnStop();

	m_oTailFrameThread.SuspendThread();
	m_oTailFrameThread.OnStop();

//	m_oSysTimeSocket.ShutDown(2);
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
