#pragma once
#include "ClientCommFrame.h"
class CClientSndFrame : public CClientCommFrame
{
public:
	CClientSndFrame(void);
	~CClientSndFrame(void);
public:


public:
	// ����Ӧ��֡
	void MakeReturnFrame(m_oCommFrameStructPtr ptrFrame);
};

