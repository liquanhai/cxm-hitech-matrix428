// MyThread.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "�߳̽���.h"
#include "MyThread.h"


// CMyThread

IMPLEMENT_DYNCREATE(CMyThread, CWinThread)

CMyThread::CMyThread()
: m_uiRcvByteNum(0)
{
}

CMyThread::~CMyThread()
{
}

BOOL CMyThread::InitInstance()
{
	// TODO: �ڴ�ִ���������̳߳�ʼ��
	return TRUE;
}

int CMyThread::ExitInstance()
{
	// TODO: �ڴ�ִ���������߳�����
	return CWinThread::ExitInstance();
}

BEGIN_MESSAGE_MAP(CMyThread, CWinThread)
END_MESSAGE_MAP()


// CMyThread ��Ϣ�������

int CMyThread::Run()
{
	// TODO: �ڴ����ר�ô����/����û���
	while(1)
	{
		DWORD dwReceived;
		unsigned char ucUdpBuf[2048];
		int iCount = 0;
		while(m_Socket.IOCtl(FIONREAD, &dwReceived))
		{
			if (dwReceived > 0)   // Process only if you have enough data
			{
			//	iCount = m_Socket.Receive(ucUdpBuf,2048);
				CString str = _T("192.168.1.56");
				unsigned int uiPort = 0x9001;
				// ReceiveFrom���԰�������Դ����Դ�ص�IP�Ͷ˿ڣ�
				iCount = m_Socket.ReceiveFrom(ucUdpBuf, 2048, str, uiPort);
				m_uiRcvByteNum += iCount;
			}
		}
		Sleep(1);
	}
	return CWinThread::Run();
}
