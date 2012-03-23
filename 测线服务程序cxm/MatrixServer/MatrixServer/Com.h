#pragma once
#include "ThreadComm.h"
#include "ThreadSend.h"

class CCom
{
public:
	CCom(void);
	~CCom(void);
public:
	// �������Ӻͽ����߳�
	CThreadComm m_oThreadComm;
	// ���緢���߳�
	CThreadSend m_oThreadSend;
public:
	// ��ʼ��
	void OnInit(void);
	// �ر�
	void OnClose(void);
	// ��ʼ���׽��ֿ�
	void OnInitSocketLib(void);
	// �ͷ��׽��ֿ�
	void OnCloseSocketLib(void);
};

