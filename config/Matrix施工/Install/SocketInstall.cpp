// SocketInstall.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Install.h"
#include "SocketInstall.h"


// CSocketInstall

CSocketInstall::CSocketInstall()
{
}

CSocketInstall::~CSocketInstall()
{
}


// CSocketInstall ��Ա����
/**
 * @brief ����Socket
 * @note  ����Socket�˿�
 * @param  UINT wPort,socket�˿�
 * @param  LPCTSTR strHostIP������IP��ַ
 * @return �����ɹ��򷵻�true��ʧ���򷵻�false
 */
bool CSocketInstall::CreateSocket(UINT wPort, LPCTSTR strHostIP)
{
	// ����socket
	if(!this->Create(wPort,SOCK_DGRAM,strHostIP))
	{		
		return false;
	}
	// ���ý��ջ�������С
	int RevBuf = 512*1024;
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