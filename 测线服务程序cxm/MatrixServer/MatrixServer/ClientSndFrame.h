#pragma once
#include "ClientCommFrame.h"
#include "ClientSocket.h"
class CClientSndFrame : public CClientCommFrame
{
public:
	CClientSndFrame(void);
	~CClientSndFrame(void);
public:
	// �ͻ���Socket��ָ��
	CClientSocket* m_pClientSocket;
public:
	// ����Ӧ��֡
	void MakeReturnFrame(m_oCommFrameStructPtr ptrFrame);
	// ���ɷ���֡
	void MakeSendFrame(m_oCommFrameStructPtr ptrFrame);
};

