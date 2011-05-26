#pragma once
#include "RecThread.h"
#include "SendThread.h"

class CThreadManage
{
public:
	CThreadManage(void);
	~CThreadManage(void);

public:
	CRecThread m_RecThread;
 	CSendThread m_SendThread;
	// ��ʼ��
	void Init();
	void OnClose();
};
