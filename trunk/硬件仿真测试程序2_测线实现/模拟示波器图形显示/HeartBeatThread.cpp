// HeartBeatThread.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ģ��ʾ����ͼ����ʾ.h"
#include "HeartBeatThread.h"
#include "Parameter.h"

// CHeartBeatThread

IMPLEMENT_DYNCREATE(CHeartBeatThread, CWinThread)

CHeartBeatThread::CHeartBeatThread()
: m_bclose(false)
{
}

CHeartBeatThread::~CHeartBeatThread()
{
}

BOOL CHeartBeatThread::InitInstance()
{
	// TODO: �ڴ�ִ���������̳߳�ʼ��
	return TRUE;
}

int CHeartBeatThread::ExitInstance()
{
	// TODO: �ڴ�ִ���������߳�����
	return CWinThread::ExitInstance();
}

BEGIN_MESSAGE_MAP(CHeartBeatThread, CWinThread)
END_MESSAGE_MAP()

// ��ʼ��
void CHeartBeatThread::OnInit(void)
{
	BOOL bReturn = FALSE;
	// ��������˿ڣ����շ�������Ӧ��֡��create����д�����������IP��ַ����չ̶�IP��ַ���͵�֡����д��ȫ������
	bReturn = m_HeartBeatSocket.Create(HeartBeatRec, SOCK_DGRAM);
	if (bReturn == FALSE)
	{
		AfxMessageBox(_T("����㲥�˿ڴ���ʧ�ܣ�"));
	}

	//���ù㲥ģʽ
	int	iOptval, iOptlen;
	iOptlen = sizeof(int);
	iOptval = 1;
	m_HeartBeatSocket.SetSockOpt(SO_BROADCAST, &iOptval, iOptlen, SOL_SOCKET);
	MakeHeartBeatFrame();
}
// �̺߳�����Run��ִ��
int CHeartBeatThread::Run()
{
	// ѭ����ֱ���رձ�־Ϊ��
	while(true)
	{
		if(m_bclose == true)
		{
			break;
		}
		// ��������֡
		SendHeartBeatFrame();
		if (m_bclose == true)
		{
			break;
		}
		Sleep(50);
	}

	// ����
	return CWinThread::Run();
}

// ��������֡
void CHeartBeatThread::MakeHeartBeatFrame(void)
{
	m_iFrameSize = 128;

	m_pFrameData[0] = 0x11;
	m_pFrameData[1] = 0x22;
	m_pFrameData[2] = 0x33;
	m_pFrameData[3] = 0x44;
	m_pFrameData[4] = 0x00;
	m_pFrameData[5] = 0x00;
	m_pFrameData[6] = 0x00;
	m_pFrameData[7] = 0x00;
	m_pFrameData[8] = 0x00;
	m_pFrameData[9] = 0x00;
	m_pFrameData[10] = 0x00;
	m_pFrameData[11] = 0x00;
	m_pFrameData[12] = 0x00;
	m_pFrameData[13] = 0x00;
	m_pFrameData[14] = 0x00;
	m_pFrameData[15] = 0x00;
	// ԴIP��ַ
	m_uiIPSource = 0x00000000;
	// Ŀ��IP��ַ
	m_uiIPAim = 0x00000000;
	// Ŀ��˿ں�
	m_usPortAim = 0;
	// ����� 1-��������Ӧ��2-��ѯ����Ӧ��3-AD���������ط�
	m_usCommand = 1;
	// ԴIP��ַ
	memcpy(&m_pFrameData[16], &m_uiIPSource, 4);
	// Ŀ��IP��ַ
	memcpy(&m_pFrameData[20], &m_uiIPAim, 4);
	// Ŀ��˿ں�
	memcpy(&m_pFrameData[24], &m_usPortAim, 2);
	// ����� 1-��������Ӧ��2-��ѯ����Ӧ��3-AD���������ط�
	memcpy(&m_pFrameData[26], &m_usCommand, 2);

	int iPos = 32;
	// ����������
	m_pFrameData[iPos] = 0x00;
}

// ��������֡
void CHeartBeatThread::SendHeartBeatFrame(void)
{
	// ���͹㲥����֡
	int iCount = m_HeartBeatSocket.SendTo(m_pFrameData, m_iFrameSize, SendPort, IPBroadcastAddr);
}

// �رղ������߳�
void CHeartBeatThread::OnClose(void)
{
// 	m_HeartBeatSocket.ShutDown(2);
 	m_HeartBeatSocket.Close();
	m_bclose = true;
}
