#include "CommThread.h"
#pragma once
class CPcapSndThread : public CCommThread
{
public:
	CPcapSndThread(void);
	~CPcapSndThread(void);
public:
	/**
	* @fn void OnProc(void)
	* @detail ������
	* @param[in] void
	* @return void
	*/
 	void OnProc(void);
};

