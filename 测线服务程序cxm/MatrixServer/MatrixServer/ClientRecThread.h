#pragma once
#include "ClientRecFrame.h"
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
 	// ������
 	void OnProc(void);
};

