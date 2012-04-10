// ComServer.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MatrixServer.h"
#include "ComServer.h"


// CComServer

CComServer::CComServer()
{
}

CComServer::~CComServer()
{
}


// CComServer ��Ա����


void CComServer::OnAccept(int nErrorCode)
{
	// TODO: �ڴ����ר�ô����/����û���
	CComClient* pComClient = NULL;
	pComClient = new CComClient;
	if (CAsyncSocket::Accept(*pComClient))
	{
		pComClient->m_pComClientMap = &m_oComClientMap;
		pComClient->CreateSocketInformation();
	}
	else
	{
		delete pComClient;
	}
	CAsyncSocket::OnAccept(nErrorCode);
}


// ��ʼ��
void CComServer::OnInit(unsigned int uiSocketPort, int iSocketType, LPCTSTR lpszSocketAddress)
{
	BOOL bFlag = FALSE;
	bFlag = CAsyncSocket::Create(uiSocketPort, iSocketType, 
		FD_ACCEPT|FD_READ|FD_WRITE|FD_CLOSE, lpszSocketAddress);
	if (!bFlag)
	{
		AfxMessageBox(_T("Server Socket Create Error!"));
		PostQuitMessage(0);
		return;
	}
	CAsyncSocket::Listen(ConnectClientMaxNum);
	m_oComClientMap.clear();
}


// �ر�
void CComServer::OnClose(void)
{
	hash_map<SOCKET, CComClient*>::iterator iter;
	for (iter = m_oComClientMap.begin(); iter != m_oComClientMap.end();)
	{
		delete iter->second;
		m_oComClientMap.erase(iter++);
	}
	CAsyncSocket::Close();
}