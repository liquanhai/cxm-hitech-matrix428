// FDUSocket.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "OperationTest.h"
#include "FDUSocket.h"
#include "OperationTestDlg.h"

// CFDUSocket

CFDUSocket::CFDUSocket()
: m_pDlg(NULL)
{
}

CFDUSocket::~CFDUSocket()
{
}


// CFDUSocket ��Ա����

void CFDUSocket::OnReceive(int nErrorCode)
{
	// TODO: �ڴ����ר�ô����/����û���
	char   pBuf[128];
	if(Receive(pBuf,128)>0)
	{
		// �����ط�
		m_pDlg->ProcessRetrans(pBuf);
	}
	CSocket::OnReceive(nErrorCode);
}
