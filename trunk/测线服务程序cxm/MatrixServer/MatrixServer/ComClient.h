#pragma once
#include "ClientRecFrame.h"
#include "ClientRecThread.h"
#include "ClientSocket.h"

// CComClient ����Ŀ��

class CComClient
{
public:
	CComClient();
	virtual ~CComClient();
public:
	// ���տͻ���֡��Ա��
	CClientRecFrame m_oClientRecFrame;
	// ���տͻ���֡�Ĵ����̳߳�Ա��
	CClientRecThread m_oClientRecThread;
	// ���տͻ���ͨѶ��Ա��
	CClientSocket m_oClientSocket;
public:
	// ����һ���ͻ���������Ϣ
	void OnInit();
	// �ͷ�һ���ͻ���������Ϣ
	void OnClose();
};


