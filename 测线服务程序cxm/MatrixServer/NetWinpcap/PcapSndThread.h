#pragma once
#include "CommThread.h"
#include "NetPcapComm.h"
class CPcapSndThread : public CCommThread
{
public:
	CPcapSndThread(void);
	~CPcapSndThread(void);
public:
	/** PcapͨѶ��ָ��*/
	CNetPcapComm* m_pNetPcapComm;
public:
	/**
	* @fn void OnProc(void)
	* @detail ������
	* @param[in] void
	* @return void
	*/
 	void OnProc(void);
};

