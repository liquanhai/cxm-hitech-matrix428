#pragma once
#include "ComServer.h"

class CCom
{
public:
	CCom(void);
	~CCom(void);
public:
	// �����CAsyncSocket
	CComServer m_oServerAsyncSocket;
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

