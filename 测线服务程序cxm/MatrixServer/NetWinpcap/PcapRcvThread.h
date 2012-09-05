#pragma once
#include "CommThread.h"
#include "NetFrameHeader.h"
#include "NetPcapComm.h"

class CPcapRcvThread : public CCommThread
{
public:
	CPcapRcvThread(void);
	~CPcapRcvThread(void);
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

