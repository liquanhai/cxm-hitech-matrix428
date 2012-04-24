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
	// ������֤
	bool m_bCheckConnected;
 	// ������
 	void OnProc(void);
	// ��֡���ݼ��������������
	void SaveRecFrameToTask(m_oCommFrameStructPtr ptrFrame);
	// ������������
	void OnProcRecCmd(unsigned short usCmd, char* pChar, unsigned int uiSize);
};

