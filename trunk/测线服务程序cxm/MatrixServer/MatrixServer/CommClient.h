#pragma once
#include "ClientRecFrame.h"
#include "ClientRecThread.h"
#include "ClientSndFrame.h"
#include "ClientSndThread.h"
#include "ClientSocket.h"
#include "MatrixDllCall.h"
/**
* @class CCommClient
* @brief ����������ӵĿͻ��˳�Ա��
*/
class CCommClient
{
public:
	CCommClient();
	virtual ~CCommClient();
public:
	/** ���տͻ���֡��Ա��*/
	CClientRecFrame m_oClientRecFrame;
	/** ���տͻ���֡�Ĵ����̳߳�Ա��*/
	CClientRecThread m_oClientRecThread;
	/** ���Ϳͻ���֡��Ա��*/
	CClientSndFrame m_oClientSndFrame;
	/** ���Ϳͻ���֡�Ĵ����̳߳�Ա��*/
	CClientSndThread m_oClientSndThread;
	/** ���տͻ���ͨѶ��Ա��*/
	CClientSocket m_oClientSocket;
	/** DLL�����������Ա*/
	CMatrixDllCall* m_pMatrixDllCall;
	/** ���ӿͻ�������ָ��*/
	hash_map<SOCKET, CCommClient*>* m_pComClientMap;
public:
	// ����һ���ͻ���������Ϣ
	void OnInit();
	// �ͷ�һ���ͻ���������Ϣ
	void OnClose();
};


