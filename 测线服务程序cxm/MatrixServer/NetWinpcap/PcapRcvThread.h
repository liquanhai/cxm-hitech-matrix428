#include "CommThread.h"
#pragma once
class CPcapRcvThread : public CCommThread
{
public:
	CPcapRcvThread(void);
	~CPcapRcvThread(void);
public:
	/**
	* @fn void OnProc(void)
	* @detail ������
	* @param[in] void
	* @return void
	*/
 	void OnProc(void);
};

