// FDUDownSocket.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "OperationTest.h"
#include "FDUDownSocket.h"
#include "OperationTestDlg.h"

// CMainCrossDownSocket

CMainCrossDownSocket::CMainCrossDownSocket()
: m_pDlg(NULL)
{
}

CMainCrossDownSocket::~CMainCrossDownSocket()
{
}

// CMainCrossDownSocket ��Ա����

void CMainCrossDownSocket::OnReceive(int nErrorCode)
{
	// TODO: �ڴ����ר�ô����/����û���
	unsigned char  pBuf[128];
	/*
	WORD   wPort;
	DWORD  dwIP;
	sockaddr_in MainCrsAddr;
	MainCrsAddr.sin_family = AF_INET;
	MainCrsAddr.sin_port = htons(0x9002);
	MainCrsAddr.sin_addr.s_addr = dwIP;
	*/
	int nSize = Receive(pBuf,128);
	if(nSize>0)
	{
		SendTo(pBuf,128,0x9002,_T("192.168.0.12"));
		// if(dwIP ==0 || dwIP ==)
		if(m_pDlg)
		{				
			m_pDlg->SaveMatrixDownData(pBuf,nSize);			
		}
	}
	CSocket::OnReceive(nErrorCode);
}
