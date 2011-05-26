// SendThread.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "�˿ڼ�����.h"
#include "SendThread.h"
#include "Parameter.h"

// CSendThread

IMPLEMENT_DYNCREATE(CSendThread, CWinThread)

CSendThread::CSendThread()
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
	int flag =  m_hSocket2.Create(RcvPort2,SOCK_DGRAM);
	m_hSocket2.SetSockOpt(SO_RCVBUF,&m_hSocket2,RcvBufSize,SOL_SOCKET);
	m_hSocket2.SetSockOpt(SO_SNDBUF,&m_hSocket2,SndBufSize,SOL_SOCKET);
}
// �̺߳�����Run��ִ��
int CSendThread::Run()
{
	unsigned short uiPort = 0;
	DWORD dwFrameCount = 0;
	int icount = 0;
	// ѭ����ֱ���رձ�־Ϊ��
	while(true)
	{
		if (m_close == true)
		{
			break;
		}

		// �õ�������ջ����������ֽ���
		while(m_hSocket2.IOCtl(FIONREAD, &dwFrameCount))
		{
			dwFrameCount = dwFrameCount/256;
			if(0 != dwFrameCount)	
			{
				for(unsigned int i = 0; i < dwFrameCount; i++)	// ���μ��ÿ������IP����Ӧ��֡
				{

					icount = m_hSocket2.Receive(udp_buf[udp_count],256);
					if (icount == 256)
					{
						// ����˿ڷַ�����
						memcpy(&uiPort, &udp_buf[udp_count][24], 2);
						m_hSocket2.SendTo(udp_buf[udp_count],256,uiPort,pDlg->m_strSendIP);
						//m_hSocket2.SendTo(udp_buf[udp_count],256,SendPort2,pDlg->m_strSendIP);
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
			else
			{
				break;
			}
		}
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
	m_hSocket2.ShutDown(2);
	m_hSocket2.Close();
	m_close = true;
}