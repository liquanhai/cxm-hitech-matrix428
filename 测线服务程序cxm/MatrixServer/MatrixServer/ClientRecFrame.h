#pragma once
#include "ClientCommFrame.h"

class CClientRecFrame : public CClientCommFrame
{
public:
	CClientRecFrame(void);
	~CClientRecFrame(void);
public:
	// ����֡
	void PhraseFrame(char* cpFrame, unsigned short usSize);
};

