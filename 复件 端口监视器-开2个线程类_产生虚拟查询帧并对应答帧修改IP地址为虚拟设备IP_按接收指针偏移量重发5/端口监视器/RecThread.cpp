// RecThread.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "�˿ڼ�����.h"
#include "RecThread.h"
#include "Parameter.h"
// CRecThread

IMPLEMENT_DYNCREATE(CRecThread, CWinThread)

CRecThread::CRecThread()
: m_uiUdpCount(0)
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
 	int flag =  m_hSocket1.Create(RcvPort1,SOCK_DGRAM);
 	m_hSocket1.SetSockOpt(SO_RCVBUF,&m_hSocket1,RcvBufSize,SOL_SOCKET);
	m_hSocket1.SetSockOpt(SO_SNDBUF,&m_hSocket1,SndBufSize,SOL_SOCKET);
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

		if(dwFrameCount > 0) 
		{
			icount = m_hSocket1.Receive(m_ucUdpBuf,8192);
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
						m_uiUdpCount = 0;
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
						m_uiUdpCount = 0;
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
						m_uiUdpCount = 0;
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
						m_uiUdpCount = 0;
						break;
					}
				default:
					udp_buf[udp_count][m_uiUdpCount] = m_ucUdpBuf[i];
					m_uiUdpCount++;
					if (m_uiUdpCount == 128)
					{
						m_uiUdpCount = 0;
						m_hSocket1.SendTo(udp_buf[udp_count],128,SendPort1,pDlg->m_strReceiveIP);
						pDlg->OnSaveReceiveData(udp_buf[udp_count],128);
						udp_count +=1;
						udp_count = udp_count%8;
					}
					break;
				}
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
void CRecThread::OnClose()
{
	m_hSocket1.ShutDown(2);
	m_hSocket1.Close();
	m_close = true;
}
