#pragma once
#include "CommClient.h"
#include "MatrixDllCall.h"
/**
* @class CCommServer
* @brief ����˵�Socket��
*/
class CCommServer : public CAsyncSocket
{
public:
	CCommServer();
	virtual ~CCommServer();
	virtual void OnAccept(int nErrorCode);
public:
	/** �ͻ�����������*/
	hash_map<SOCKET, CCommClient*> m_oComClientMap;
	/** DLL�����������Ա*/
	CMatrixDllCall* m_pMatrixDllCall;
public:
	// ��ʼ��
	void OnInit(unsigned int uiSocketPort = ServerClientPort, int iSocketType = SOCK_STREAM, LPCTSTR lpszSocketAddress = NULL);
	// �ر�
	void OnClose(void);
};


