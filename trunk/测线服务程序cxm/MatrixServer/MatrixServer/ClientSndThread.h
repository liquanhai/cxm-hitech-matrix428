#pragma once
#include "ClientSndFrame.h"
#include "ClientCommThread.h"
/**
* @class CClientSndThread
* @brief ��ͻ���ͨѶ�����߳���
*/
class CClientSndThread : public CClientCommThread
{
public:
	CClientSndThread(void);
	~CClientSndThread(void);
public:
	/** ���Ϳͻ�����ָ��*/
	CClientSndFrame* m_pClientSndFrame;
	/** ������*/
	void OnProc(void);
};

