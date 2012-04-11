#pragma once
#include "CommProtocol.h"
#include <hash_map>
using stdext::hash_map;

// CClientSocket ����Ŀ��
class CComClient;
class CClientSocket : public CAsyncSocket
{
public:
	CClientSocket();
	virtual ~CClientSocket();
	virtual void OnReceive(int nErrorCode);
	virtual void OnSend(int nErrorCode);
	virtual void OnClose(int nErrorCode);
public:
	// ���ӿͻ�������ָ��
	hash_map<SOCKET, CComClient*>* m_pComClientMap;
	// ���ջ�������С
	char m_cRecBuf[ServerRecBufSize];
	// ���յ�����
	int m_iPosRec;
	// ���������
	int m_iPosProc;
	// ֡���ݳ���
	unsigned short m_usFrameInfoSize;
	// ���ӿͻ�����ָ��
	CComClient* m_pComClient;
	// ��ʼ��
	void OnInit(CComClient* pComClient, int iSndBufferSize, int iRcvBufferSize);
	// �ر�
	void OnClose(void);
};


