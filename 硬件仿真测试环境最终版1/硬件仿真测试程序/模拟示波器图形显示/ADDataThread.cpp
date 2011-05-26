// ADDataThread.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ģ��ʾ����ͼ����ʾ.h"
#include "ADDataThread.h"
#include "Parameter.h"

// ADDataThread

IMPLEMENT_DYNCREATE(CADDataThread, CWinThread)

CADDataThread::CADDataThread()
: m_bclose(false)
{
}

CADDataThread::~CADDataThread()
{
}

BOOL CADDataThread::InitInstance()
{
	// TODO: �ڴ�ִ���������̳߳�ʼ��
	return TRUE;
}

int CADDataThread::ExitInstance()
{
	// TODO: �ڴ�ִ���������߳�����
	return CWinThread::ExitInstance();
}

BEGIN_MESSAGE_MAP(CADDataThread, CWinThread)
END_MESSAGE_MAP()


// ADDataThread ��Ϣ�������
// ��ʼ��
void CADDataThread::OnInit(void)
{
	m_hADDDataThreadClose = ::CreateEvent(false, false, NULL, NULL);	// �����¼�����
	::ResetEvent(m_hADDDataThreadClose);	// �����¼�����Ϊ���ź�״̬
	BOOL flag = FALSE; 
	flag =  m_ADDataSocket.Create(ADRecPort,SOCK_DGRAM);
	if (flag == FALSE)
	{
		AfxMessageBox(_T("���ն˿ڴ���ʧ�ܣ�"));
	}

}
// �̺߳�����Run��ִ��
int CADDataThread::Run()
{
	DWORD dwFrameCount = 0;
	int icount = 0;
	// ѭ����ֱ���رձ�־Ϊ��
	while(true)
	{
		if(m_bclose == true)
		{
			break;
		}

		// �õ�������ջ����������ֽ���
		m_ADDataSocket.IOCtl(FIONREAD, &dwFrameCount);
		dwFrameCount = dwFrameCount/256;
		if(0 != dwFrameCount)	
		{
			for(unsigned int i = 0; i < dwFrameCount; i++)	// ���μ��ÿ������IP����Ӧ��֡
			{
				icount = m_ADDataSocket.Receive(ADData,256);
				if (icount == 256)
				{
					byte* pSampleData = &(ADData[16]);
					pHardwareTestDlg->ReceiveSampleData(pSampleData);
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
		Sleep(50);
	}
	::SetEvent(m_hADDDataThreadClose);	// �����¼�����Ϊ���ź�״̬
	// ����
	return CWinThread::Run();
}
// �رղ������߳�
void CADDataThread::OnClose(void)
{
 //	m_ADDataSocket.ShutDown(2);
 	m_ADDataSocket.Close();
	m_bclose = true;
}
