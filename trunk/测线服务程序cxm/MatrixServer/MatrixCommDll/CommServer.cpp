#include "stdafx.h"
#include "MatrixCommDll.h"

CCommServer::CCommServer()
{
	m_pComClientMap = NULL;
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
	CloseInvalidClient();
	if (CAsyncSocket::Accept(pComClient->m_oClientSocket))
	{
		pComClient->m_pComClientMap = m_pComClientMap;
		pComClient->m_oProcRecCmdCallBack = m_oProcRecCmdCallBack;
		pComClient->OnInit();
	}
	else
	{
		delete pComClient;
		pComClient = NULL;
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
		AfxMessageBox(_T("Server Socket Create Error or Server already exists!"));
		PostQuitMessage(0);
		return;
	}
	CAsyncSocket::Listen(ListenClientMaxNum);
}


// �ر�
void CCommServer::OnClose(void)
{
	hash_map<SOCKET, CCommClient*>::iterator iter;
	int iSize = m_pComClientMap->size();
	for (int i=0; i<iSize; i++)
	{
		iter = m_pComClientMap->begin();
		iter->second->OnClose();
	}
	Close();
}

void CCommServer::CloseInvalidClient(void)
{
	hash_map<SOCKET, CCommClient*>::iterator iter;
	list<CCommClient*>::iterator iterList;
	bool bConnectValid = true;
	for (iter = m_pComClientMap->begin(); iter != m_pComClientMap->end(); iter++)
	{
		EnterCriticalSection(&iter->second->m_oSndFrame.m_oSecClientFrame);
		bConnectValid = iter->second->m_oSndFrame.m_bConnectValid;
		LeaveCriticalSection(&iter->second->m_oSndFrame.m_oSecClientFrame);
		if (bConnectValid == false)
		{
			m_olsClientClose.push_back(iter->second);
		}
	}
	for (iterList = m_olsClientClose.begin(); iterList != m_olsClientClose.end(); iterList++)
	{
		(*iterList)->OnClose();
	}
	m_olsClientClose.clear();
}