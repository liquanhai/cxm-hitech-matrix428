// EepromSocket.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MatrixTestSoft.h"
#include "EepromSocket.h"


// CEepromSocket

CEepromSocket::CEepromSocket()
{
}

CEepromSocket::~CEepromSocket()
{
}


// CEepromSocket ��Ա����

void CEepromSocket::OnReceive(int nErrorCode)
{
	// TODO: �ڴ����ר�ô����/����û���

	CSocket::OnReceive(nErrorCode);
}
