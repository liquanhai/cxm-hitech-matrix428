#pragma once
#include "ClientSndFrame.h"
#include "ClientCommThread.h"
#include "ClientSocket.h"
// ��ͻ��˷���֡�ķ����߳�
class CClientSndThread : public CClientCommThread
{
public:
	CClientSndThread(void);
	~CClientSndThread(void);
public:
	// ���Ϳͻ�����ָ��
	CClientSndFrame* m_pClientSndFrame;
	// 
	CClientSocket* m_pClientSocket;
	// ������
	void OnProc(void);
};

