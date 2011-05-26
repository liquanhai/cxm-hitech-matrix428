// RecThread.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "�˿ڼ�����.h"
#include "RecThread.h"
#include "Parameter.h"
// CRecThread

IMPLEMENT_DYNCREATE(CRecThread, CWinThread)

CRecThread::CRecThread()
{
}

CRecThread::~CRecThread()
{	
}

BOOL CRecThread::InitInstance()
{
	// TODO: �ڴ�ִ���������̳߳�ʼ��
	return TRUE;
}

int CRecThread::ExitInstance()
{
	// TODO: �ڴ�ִ���������߳�����
	return CWinThread::ExitInstance();
}

BEGIN_MESSAGE_MAP(CRecThread, CWinThread)
END_MESSAGE_MAP()


// ��ʼ��

void CRecThread::Init()
{
	udp_count = 0;
	m_close = false;
	m_hRecThreadClose = ::CreateEvent(false, false, NULL, NULL);	// �����¼�����
	::ResetEvent(m_hRecThreadClose);	// �����¼�����Ϊ���ź�״̬
 	int flag =  m_hSocket1.Create(RcvPort1,SOCK_DGRAM);
 	m_hSocket1.SetSockOpt(NULL,&m_hSocket1,65536,SOL_SOCKET);
}
// �̺߳�����Run��ִ��
int CRecThread::Run()
{
	DWORD dwFrameCount = 0;
	int icount = 0;
	// ѭ����ֱ���رձ�־Ϊ��
	while(true)
	{
		if(m_close == true)
		{
			break;
		}

		// �õ�������ջ����������ֽ���
		m_hSocket1.IOCtl(FIONREAD, &dwFrameCount);
		dwFrameCount = dwFrameCount/128;
		if(0 != dwFrameCount)	
		{
			for(unsigned int i = 0; i < dwFrameCount; i++)	// ���μ��ÿ������IP����Ӧ��֡
			{
				icount = m_hSocket1.Receive(udp_buf[udp_count],128);
				if (icount == 128)
				{
					m_hSocket1.SendTo(udp_buf[udp_count],128,SendPort1,pDlg->m_strReceiveIP);
					pDlg->OnSaveReceiveData(udp_buf[udp_count],128);
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
	::SetEvent(m_hRecThreadClose);	// �����¼�����Ϊ���ź�״̬
	// ����
	return CWinThread::Run();
}
void CRecThread::OnClose()
{
	m_hSocket1.ShutDown(2);
	m_hSocket1.Close();
	m_close = true;
}
