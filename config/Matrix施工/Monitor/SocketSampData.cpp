// SocketSampData.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "monitor.h"
#include "SocketSampData.h"
#include "Monitordlg.h"

// CSocketSampData

CSocketSampData::CSocketSampData()
: m_pDlg(NULL)
{
}

CSocketSampData::~CSocketSampData()
{
}


// CSocketSampData ��Ա����
bool    CSocketSampData::CreateSocket(WORD  wPort,CDialog* pDlg)
{
	this->m_pDlg = (CMonitorDlg*)pDlg;
	// ����socket
	if(!this->Create(wPort,SOCK_DGRAM))
	{		
		return false;
	}
	// ���ý��ջ�������С
	int RevBuf = 2048*1024;
	if (this->SetSockOpt( SO_RCVBUF, (char*)&RevBuf, sizeof(RevBuf)) == SOCKET_ERROR) 
	{
		this->Close();		
		return false;
	}
	// ���÷��ͻ�������С
	if (this->SetSockOpt(SO_SNDBUF, (char*)&RevBuf, sizeof(RevBuf)) == SOCKET_ERROR) 
	{
		this->Close();		
		return false;
	}
	// ����������ܹ㲥��Ϣ
	RevBuf = 1;
	if (this->SetSockOpt(SO_BROADCAST, (char*)&RevBuf, sizeof(RevBuf)) == SOCKET_ERROR) 
	{
		this->Close();		
		return false;
	}
	return true;
}
void CSocketSampData::OnReceive(int nErrorCode)
{
	// TODO: �ڴ����ר�ô����/����û���
	if(m_pDlg)
	{
		m_pDlg->AnalysisProtocolOfSampleSock();
	}
	CSocket::OnReceive(nErrorCode);
}
