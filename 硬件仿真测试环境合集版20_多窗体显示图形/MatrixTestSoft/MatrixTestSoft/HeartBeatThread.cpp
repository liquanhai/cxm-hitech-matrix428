// HeartBeatThread.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MatrixTestSoft.h"
#include "HeartBeatThread.h"
#include "Parameter.h"

// CHeartBeatThread

IMPLEMENT_DYNCREATE(CHeartBeatThread, CWinThread)

CHeartBeatThread::CHeartBeatThread()
: m_bclose(false)
, m_uiSendPort(0)
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
	m_hHeartBeatThreadClose = ::CreateEvent(false, false, NULL, NULL);	// �����¼�����
	::ResetEvent(m_hHeartBeatThreadClose);	// �����¼�����Ϊ���ź�״̬

	m_hHeartBeatThreadWork = ::CreateEvent(false, false, NULL, NULL);	// �����¼�����
	::ResetEvent(m_hHeartBeatThreadWork);	// �����¼�����Ϊ���ź�״̬
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
		// Sleep(500);
		::WaitForSingleObject(m_hHeartBeatThreadWork, 100);
		::ResetEvent(m_hHeartBeatThreadWork); // �����¼�����Ϊ���ź�״̬
	}
	::SetEvent(m_hHeartBeatThreadClose);	// �����¼�����Ϊ���ź�״̬,�ͷŵȴ��̺߳��¼���Ϊ���ź�
	// ����
	return CWinThread::Run();
}

// ��������֡
void CHeartBeatThread::MakeHeartBeatFrame(void)
{
	m_iFrameSize = SndFrameSize;
	for(int i=0; i<SndFrameSize; i++)
	{
		m_pFrameData[i] = 0x00;
	}

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
	m_uiIPAim = 0xffffffff;
	// Ŀ��˿ں�
	m_usPortAim = HeartBeatRec;
	// ����� 1-��������Ӧ��2-��ѯ����Ӧ��3-AD���������ط�
	m_usCommand = SendSetCmd;
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

	unsigned short usCRC16 = 0;
	usCRC16 = get_crc_16(&m_pFrameData[FrameHeadSize], SndFrameSize - FrameHeadSize - CRCCheckSize);
	memcpy(&m_pFrameData[SndFrameSize - CRCSize], &usCRC16, 2);
}

// ��������֡
void CHeartBeatThread::SendHeartBeatFrame(void)
{
	// ���͹㲥����֡
	int iCount = m_HeartBeatSocket.SendTo(m_pFrameData, m_iFrameSize, m_uiSendPort, IPBroadcastAddr);
}

// �رղ������߳�
void CHeartBeatThread::OnClose(void)
{
//	m_HeartBeatSocket.ShutDown(2);
	m_HeartBeatSocket.Close();
	m_bclose = true;
}

// ��
void CHeartBeatThread::OnOpen(void)
{
	m_HeartBeatSocket.Close();
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
	int iHeartBeatSndBufSize = HeartBeatSndBufSize;
	int iSndFrameSize = SndFrameSize;
	OnSetBufferSize(iHeartBeatSndBufSize * iSndFrameSize);
	MakeHeartBeatFrame();
}

// ֹͣ
void CHeartBeatThread::OnStop(void)
{
//	m_HeartBeatSocket.ShutDown(2);
	m_HeartBeatSocket.Close();
}

// ��ֹ������ѭ���������޷���Ӧ��Ϣ
void CHeartBeatThread::ProcessMessages(void)
{
	MSG msg;
	::PeekMessage(&msg, NULL, 0, 0, PM_REMOVE);
	::DispatchMessage(&msg);
}

// ���û������ߴ�
BOOL CHeartBeatThread::OnSetBufferSize(int iBufferSize)
{
	BOOL bReturn = false;

	int iOptionValue = iBufferSize;
	int iOptionLen = sizeof(int);
	bReturn = m_HeartBeatSocket.SetSockOpt(SO_SNDBUF, (void*)&iOptionValue, iOptionLen, SOL_SOCKET);

	return bReturn;
}
