// ComServer.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MatrixServer.h"
#include "CommServer.h"


// CComServer

CCommServer::CCommServer()
{
	m_pMatrixDllCall = NULL;
}

CCommServer::~CCommServer()
{
}


// CComServer ��Ա����


void CCommServer::OnAccept(int nErrorCode)
{
	// TODO: �ڴ����ר�ô����/����û���
	CCommClient* pComClient = NULL;
	pComClient = new CCommClient;
	if (CAsyncSocket::Accept(pComClient->m_oClientSocket))
	{
		pComClient->m_oClientSocket.m_pComClientMap = &m_oComClientMap;
		pComClient->m_pMatrixDllCall = m_pMatrixDllCall;
		pComClient->OnInit();
	}
	else
	{
		delete pComClient;
	}
	CAsyncSocket::OnAccept(nErrorCode);
}


// ��ʼ��
void CCommServer::OnInit(unsigned int uiSocketPort, int iSocketType, LPCTSTR lpszSocketAddress)
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
	CAsyncSocket::Listen(ListenClientMaxNum);
	m_oComClientMap.clear();
}


// �ر�
void CCommServer::OnClose(void)
{
	hash_map<SOCKET, CCommClient*>::iterator iter;
	int iSize = m_oComClientMap.size();
	for (int i=0; i<iSize; i++)
	{
		iter = m_oComClientMap.begin();
		iter->second->OnClose();
	}
	Close();
}