#pragma once
#include "ClientRecFrame.h"
#include "ClientSndFrame.h"
#include "ClientCommThread.h"
// �������Կͻ��˵�֡�߳�
class CClientRecThread : public CClientCommThread
{
public:
	CClientRecThread(void);
	~CClientRecThread(void);
public:
	// ���տͻ�����ָ��
	CClientRecFrame* m_pClientRecFrame;
	// ���Ϳͻ�����ָ��
	CClientSndFrame* m_pClientSndFrame;
 	// ������
 	void OnProc(void);
};

