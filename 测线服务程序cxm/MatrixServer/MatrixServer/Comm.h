#pragma once
#include "CommServer.h"

class CComm
{
public:
	CComm(void);
	~CComm(void);
public:
	// �����CAsyncSocket
	CCommServer m_oServerAsyncSocket;
public:
	// ��ʼ��
	void OnInit(void);
	// �ر�
	void OnClose(void);
	// ��ʼ���׽��ֿ�
	void OnInitSocketLib(void);
	// �ͷ��׽��ֿ�
	void OnCloseSocketLib(void);
};

