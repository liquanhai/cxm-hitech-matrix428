#pragma once
#include "ClientRecFrame.h"
#include <hash_map>
using stdext::hash_map;
#define RecBufSize	819200

// CComClient ����Ŀ��

class CComClient : public CAsyncSocket
{
public:
	CComClient();
	virtual ~CComClient();
	virtual void OnReceive(int nErrorCode);
	virtual void OnSend(int nErrorCode);
	virtual void OnClose(int nErrorCode);
public:
	// �ͻ�����������ָ��
	hash_map<SOCKET, CComClient*>* m_pComClientMap;
	// �ͻ��˽���֡��Ա��
	CClientRecFrame m_oClientRecFrame;
	// ���ջ�������С
	char m_cRecBuf[RecBufSize];
	// ���յ�����
	int m_iPosRec;
	// ���������
	int m_iPosProc;
	// ֡���ݳ���
	unsigned short m_usFrameInfoSize;
public:
	// ����һ���ͻ���������Ϣ
	void CreateSocketInformation();
	// �ͷ�һ���ͻ���������Ϣ
	void FreeSocketInformation();
};


