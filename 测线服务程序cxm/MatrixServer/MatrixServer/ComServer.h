#pragma once
#include "ComClient.h"

// CComServer ����Ŀ��

class CComServer : public CAsyncSocket
{
public:
	CComServer();
	virtual ~CComServer();
	virtual void OnAccept(int nErrorCode);
public:
	// �ͻ�����������
	hash_map<SOCKET, CComClient*> m_oComClientMap;
public:
	// ��ʼ��
	void OnInit(unsigned int uiSocketPort = 8080, int iSocketType = SOCK_STREAM, LPCTSTR lpszSocketAddress = NULL);
	// �ر�
	void OnClose(void);
};


