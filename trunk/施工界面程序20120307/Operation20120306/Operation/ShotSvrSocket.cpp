// ShotSvrSocket.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Operation.h"
#include "ShotSvrSocket.h"
#include "MainFrm.h"

// CShotSvrSocket

CSocketShotServer::CSocketShotServer()
{
}

CSocketShotServer::~CSocketShotServer()
{
}


// CShotSvrSocket ��Ա����
/**
 * @brief ����Socket
 * @note  ����Socket�˿�
 * @param  UINT wPort,socket�˿�
 * @param  LPCTSTR strHostIP������IP��ַ
 * @return �����ɹ��򷵻�true��ʧ���򷵻�false
 */
bool CSocketShotServer::CreateSocket(UINT wPort, LPCTSTR strHostIP)
{
	// ����socket
	if(!this->Create(wPort,SOCK_DGRAM,strHostIP))
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
/******************************************************************************
    ��    ����
    
    ��    �룺
    
    ��    ����
  
    �� �� ֵ��
    
    ��    �ܣ� �������Է�����������

    �޸���ʷ��
*******************************************************************************/
void CSocketShotServer::OnReceive(int nErrorCode)
{
	// TODO: �ڴ����ר�ô����/����û���
	// cxm 2012.3.7
// 	CMainFrame*	pMainFram =(CMainFrame*)AfxGetMainWnd();
// 	if(pMainFram)
// 	{
// 		pMainFram->AnalysisProtocolOfServerSock();
// 	}
	CSocket::OnReceive(nErrorCode);
}
