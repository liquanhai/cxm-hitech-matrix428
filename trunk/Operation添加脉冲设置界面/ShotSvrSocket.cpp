// ShotSvrSocket.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Operation.h"
#include "ShotSvrSocket.h"
#include "MainFrm.h"

// CShotSvrSocket

CShotServerSocket::CShotServerSocket()
{
}

CShotServerSocket::~CShotServerSocket()
{
}


// CShotSvrSocket ��Ա����
/******************************************************************************
    ��    ����
    
    ��    �룺
    
    ��    ����
  
    �� �� ֵ��
    
    ��    �ܣ� �������Է�����������

    �޸���ʷ��
*******************************************************************************/
void CShotServerSocket::OnReceive(int nErrorCode)
{
	// TODO: �ڴ����ר�ô����/����û���
	CMainFrame*	pMainFram =(CMainFrame*)AfxGetMainWnd();
	pMainFram->AnalysisProtocolOfServerSock();
	CSocket::OnReceive(nErrorCode);
}
