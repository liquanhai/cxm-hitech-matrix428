// PortMonitoringRecThread.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MatrixTestSoft.h"
#include "PortMonitoringRecThread.h"


// CPortMonitoringRecThread

IMPLEMENT_DYNCREATE(CPortMonitoringRecThread, CWinThread)

CPortMonitoringRecThread::CPortMonitoringRecThread()
: m_usudp_count(0)
, m_iRecPort(0)
, m_iSendPort(0)
, m_csIP(_T(""))
, m_pSaveFile(NULL)
, m_uiHeartBeatNum(0)
, m_uiIPSetNum(0)
, m_uiTailTimeNum(0)
, m_uiDelayTimeSetNum(0)
, m_uiADCSetNum(0)
, m_uiSendFrameNum(0)
, m_bclose(false)
{
}

CPortMonitoringRecThread::~CPortMonitoringRecThread()
{
}

BOOL CPortMonitoringRecThread::InitInstance()
{
	// TODO: �ڴ�ִ���������̳߳�ʼ��
	return TRUE;
}

int CPortMonitoringRecThread::ExitInstance()
{
	// TODO: �ڴ�ִ���������߳�����
	return CWinThread::ExitInstance();
}

BEGIN_MESSAGE_MAP(CPortMonitoringRecThread, CWinThread)
END_MESSAGE_MAP()


// CPortMonitoringRecThread ��Ϣ�������

int CPortMonitoringRecThread::Run()
{
	// TODO: �ڴ����ר�ô����/����û���

	DWORD dwFrameCount = 0;
	int icount = 0;
	unsigned short uiPort = 0;
	// ѭ����ֱ���رձ�־Ϊ��
	while(true)
	{
		if(m_bclose == true)
		{
			break;
		}
	
		// �õ�������ջ����������ֽ���
		m_RecSocket.IOCtl(FIONREAD, &dwFrameCount);
		dwFrameCount = dwFrameCount/SndFrameSize;
		if(0 != dwFrameCount)	
		{
			for(unsigned int i = 0; i < dwFrameCount; i++)	// ���μ��ÿ������IP����Ӧ��֡
			{
				ProcessMessages();
				icount = m_RecSocket.Receive(m_ucudp_buf[m_usudp_count],SndFrameSize);
				if (icount == SndFrameSize)
				{ 
					CString strTemp = _T("");
					unsigned int uiCommand = 0;
					// ע�͵�����������Ϣ����ADC�������ú���Ư�����������Ͳ������ͣ������
					// ͨ���˿�ʶ����
					memcpy(&uiPort, &m_ucudp_buf[m_usudp_count][24], 2);
					if (uiPort == HeartBeatRec)
					{
						m_uiHeartBeatNum ++;
					}
					else if (uiPort == IPSetPort)
					{
						m_uiIPSetNum ++;
					}
					else if (uiPort == TailTimeFramePort)
					{
						m_uiTailTimeNum ++;
					}
					else if (uiPort == TimeSetPort)
					{
						m_uiDelayTimeSetNum ++;
					}
					else if (uiPort == ADSetReturnPort)
					{
						m_uiADCSetNum ++;
					}
					m_uiSendFrameNum ++;

					m_RecSocket.SendTo(m_ucudp_buf[m_usudp_count],SndFrameSize,m_iSendPort,m_csIP);
					m_pSaveFile->OnSaveReceiveData(m_ucudp_buf[m_usudp_count],SndFrameSize);

					m_usudp_count +=1;
					m_usudp_count = m_usudp_count%8;
				}
				else
				{
					break;
				}
			}
		}
		if (m_bclose == true)
		{
			break;
		}
		Sleep(1);
	}

	::SetEvent(m_hPortMonitoringRecThreadClose);	// �����¼�����Ϊ���ź�״̬,�ͷŵȴ��̺߳��¼���Ϊ���ź�
	return CWinThread::Run();
}

// ��ʼ��
void CPortMonitoringRecThread::OnInit(void)
{
	m_hPortMonitoringRecThreadClose = ::CreateEvent(false, false, NULL, NULL);	// �����¼�����
	if ((m_hPortMonitoringRecThreadClose == NULL)||(GetLastError() == ERROR_ALREADY_EXISTS))
	{
		AfxMessageBox(_T("�����˿ڼ��ӷ����̹߳ر��¼�����"));
	}
	else
	{
		::ResetEvent(m_hPortMonitoringRecThreadClose);	// �����¼�����Ϊ���ź�״̬
	}
}

// ��
void CPortMonitoringRecThread::OnOpen(void)
{
	m_RecSocket.Close();
	int flag =  m_RecSocket.Create(m_iRecPort,SOCK_DGRAM);
	m_RecSocket.SetSockOpt(SO_RCVBUF,&m_RecSocket,PortMonitoringBufSize,SOL_SOCKET);
	m_RecSocket.SetSockOpt(SO_SNDBUF,&m_RecSocket,PortMonitoringBufSize,SOL_SOCKET);
}

// ֹͣ
void CPortMonitoringRecThread::OnStop(void)
{
	m_RecSocket.Close();
}

// �ر�
void CPortMonitoringRecThread::OnClose(void)
{
	m_RecSocket.Close();
	m_bclose = true;
}
// ���ý���
void CPortMonitoringRecThread::OnReset(void)
{
	CString strTemp;
	m_uiHeartBeatNum = 0;
	m_uiIPSetNum = 0;
	m_uiTailTimeNum = 0;
	m_uiDelayTimeSetNum = 0;
	m_uiADCSetNum = 0;
	m_uiSendFrameNum = 0;
}
// ��ֹ������ѭ���������޷���Ӧ��Ϣ
void CPortMonitoringRecThread::ProcessMessages(void)
{
	MSG msg;
	::PeekMessage(&msg, NULL, 0, 0, PM_REMOVE);
	::DispatchMessage(&msg);
}
