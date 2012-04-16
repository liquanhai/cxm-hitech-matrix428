#pragma once
#include "CommClient.h"

// CComServer ����Ŀ��

class CCommServer : public CAsyncSocket
{
public:
	CCommServer();
	virtual ~CCommServer();
	virtual void OnAccept(int nErrorCode);
public:
	// �ͻ�����������
	hash_map<SOCKET, CCommClient*> m_oComClientMap;
public:
	// ��ʼ��
	void OnInit(unsigned int uiSocketPort = 8080, int iSocketType = SOCK_STREAM, LPCTSTR lpszSocketAddress = NULL);
	// �ر�
	void OnClose(void);
};


