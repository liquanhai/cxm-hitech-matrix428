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
, m_csIPSource(_T(""))
, m_pHeartBeatSocket(NULL)
{
}

CHeartBeatThread::~CHeartBeatThread()
{
	if (m_pHeartBeatSocket != NULL)
	{
		m_pHeartBeatSocket = NULL;
		delete m_pHeartBeatSocket;
	}
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
//************************************
// Method:    OnInit
// FullName:  CHeartBeatThread::OnInit
// Access:    public 
// Returns:   void
// Qualifier:
// Parameter: void
//************************************
void CHeartBeatThread::OnInit(void)
{
	m_hHeartBeatThreadClose = ::CreateEvent(false, false, NULL, NULL);	// �����¼�����
	if ((m_hHeartBeatThreadClose == NULL)||(GetLastError() == ERROR_ALREADY_EXISTS))
	{
		AfxMessageBox(_T("���������̹߳ر��¼�����"));
	}
	else
	{
		::ResetEvent(m_hHeartBeatThreadClose);	// �����¼�����Ϊ���ź�״̬
	}
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
 		 Sleep(HeartBeatThreadSleepTime);
	}
	::SetEvent(m_hHeartBeatThreadClose);	// �����¼�����Ϊ���ź�״̬,�ͷŵȴ��̺߳��¼���Ϊ���ź�
	// ����
	return CWinThread::Run();
}

// ��������֡
//************************************
// Method:    MakeHeartBeatFrame
// FullName:  CHeartBeatThread::MakeHeartBeatFrame
// Access:    public 
// Returns:   void
// Qualifier:
// Parameter: void
//************************************
void CHeartBeatThread::MakeHeartBeatFrame(void)
{
	unsigned int uiIPSource = 0;
	unsigned int uiIPAim = 0;
	unsigned short usPortAim	=	0;
	unsigned short usCommand	=	0;
	int iPos = 0;
	memset(m_pFrameData, SndFrameBufInit, SndFrameSize);
	m_pFrameData[0] = FrameHeadCheck0;
	m_pFrameData[1] = FrameHeadCheck1;
	m_pFrameData[2] = FrameHeadCheck2;
	m_pFrameData[3] = FrameHeadCheck3;
	memset(&m_pFrameData[FrameHeadCheckSize], SndFrameBufInit, (FrameHeadSize - FrameHeadCheckSize));

	// CStringת��Ϊconst char*
	const char* pChar = ConvertCStringToConstCharPointer(m_csIPSource);

	// ԴIP��ַ
	uiIPSource = inet_addr(pChar);
	// Ŀ��IP��ַ
	uiIPAim = BroadCastPort;
	// Ŀ��˿ں�
	usPortAim = HeartBeatRec;
	// ����� 1-��������Ӧ��2-��ѯ����Ӧ��3-AD���������ط�
	usCommand = SendSetCmd;
	// ԴIP��ַ
	iPos = 16;
	memcpy(&m_pFrameData[iPos], &uiIPSource, FramePacketSize4B);
	iPos += FramePacketSize4B;
	// Ŀ��IP��ַ
	memcpy(&m_pFrameData[iPos], &uiIPAim, FramePacketSize4B);
	iPos += FramePacketSize4B;
	// Ŀ��˿ں�
	memcpy(&m_pFrameData[iPos], &usPortAim, FramePacketSize2B);
	iPos += FramePacketSize2B;
	// ����� 1-��������Ӧ��2-��ѯ����Ӧ��3-AD���������ط�
	memcpy(&m_pFrameData[iPos], &usCommand, FramePacketSize2B);
	iPos += FramePacketSize2B;

	iPos = 32;
	// ����������
	m_pFrameData[iPos] = SndFrameBufInit;

	unsigned short usCRC16 = 0;
	usCRC16 = get_crc_16(&m_pFrameData[FrameHeadSize], SndFrameSize - FrameHeadSize - CRCCheckSize);
	memcpy(&m_pFrameData[SndFrameSize - CRCSize], &usCRC16, CRCSize);
}

// ��������֡
//************************************
// Method:    SendHeartBeatFrame
// FullName:  CHeartBeatThread::SendHeartBeatFrame
// Access:    public 
// Returns:   void
// Qualifier:
// Parameter: void
//************************************
void CHeartBeatThread::SendHeartBeatFrame(void)
{
	// ���͹㲥����֡
	int iCount = m_pHeartBeatSocket->SendTo(m_pFrameData, SndFrameSize, m_uiSendPort, IPBroadcastAddr);
}

// �رղ������߳�
//************************************
// Method:    OnClose
// FullName:  CHeartBeatThread::OnClose
// Access:    public 
// Returns:   void
// Qualifier:
// Parameter: void
//************************************
void CHeartBeatThread::OnClose(void)
{
	m_bclose = true;
}

// ��ֹ������ѭ���������޷���Ӧ��Ϣ
//************************************
// Method:    ProcessMessages
// FullName:  CHeartBeatThread::ProcessMessages
// Access:    public 
// Returns:   void
// Qualifier:
// Parameter: void
//************************************
void CHeartBeatThread::ProcessMessages(void)
{
	MSG msg;
	::PeekMessage(&msg, NULL, 0, 0, PM_REMOVE);
	::DispatchMessage(&msg);
}