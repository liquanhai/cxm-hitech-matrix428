#pragma once
#include "CommProtocol.h"
#include "ClientFrame.h"
#include <list>
using std::list;

class CClientRecFrame : public CClientFrame
{
public:
	CClientRecFrame(void);
	~CClientRecFrame(void);
public:
	// ����֡
	void PhraseFrame(char* cpFrame, unsigned short usSize);
};

