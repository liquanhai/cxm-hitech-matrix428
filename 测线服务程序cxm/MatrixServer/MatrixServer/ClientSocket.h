#pragma once
#include "CommProtocol.h"
#include <hash_map>
using stdext::hash_map;
class CCommClient;
/**
* @class CClientSocket
* @brief �����ϵĿͻ��˵�Socket��
*/
class CClientSocket : public CAsyncSocket
{
public:
	CClientSocket();
	virtual ~CClientSocket();
	virtual void OnReceive(int nErrorCode);
	virtual void OnClose(int nErrorCode);
public:
	/** ���ӿͻ�������ָ��*/
	hash_map<SOCKET, CCommClient*>* m_pComClientMap;
	/** ���ջ�����*/
	char m_cRecBuf[ServerRecBufSize];
	/** ���ͻ�����*/
	char m_cSndBuf[FrameSizeLimit];
	/** ���յ�����*/
	int m_iPosRec;
	/** ���������*/
	int m_iPosProc;
	/** ֡���ݳ���*/
	unsigned short m_usFrameInfoSize;
	/** ���ӿͻ�����ָ��*/
	CCommClient* m_pComClient;
public:
	/** ��ʼ��*/
	void OnInit(CCommClient* pComClient, int iSndBufferSize, int iRcvBufferSize);
	/** �ر�*/
	void OnClose(void);
	/** �������֡*/
	void OnProcRec(int iSize);
};


