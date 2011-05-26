// MySocket.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "�˿ڼ�����.h"
#include "MySocket.h"
#include "PortMonitoringDlg.h"

// CMySocket

CMySocket::CMySocket(CPortMonitoringDlg* pTDoc)
{
	m_pTDoc=pTDoc;
	udp_count = 0;
}

CMySocket::~CMySocket()
{
}


// CMySocket ��Ա����
void CMySocket::OnReceive(int nErrorCode) 
{
	// TODO: Add your specialized code here and/or call the base class
	int ret=0;

	ret=Receive(udp_buf[udp_count],1024);

	if(ret==ERROR)
	{
		TRACE("ERROR!");
	}
	else if(ret != 0xffffffff) 
	{
		SendTo(udp_buf[udp_count],ret,SendPort1,m_pTDoc->m_strReceiveIP);
		m_pTDoc->OnSaveReceiveData(udp_buf[udp_count],ret);
		udp_count +=1;
		udp_count = udp_count%8;
	}
	CAsyncSocket::OnReceive(nErrorCode);
}
