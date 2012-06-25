/**
@brief	����netd_pcap_recv_thread��
@details	������Ҫʵ��pcap�Ľ������ݹ���
@file	netd.pcap.recv.thread.h
@note	
@see	
@version	1.0.2.8.2012.02.17
@author	kuoxin	
@bug
*/
#ifndef __NETD_PCAP_RECV_THREAD__
#define __NETD_PCAP_RECV_THREAD__

#include "..\core\matrix.thread.h"
#define RunTimes	2000
class netd_pcap_service;
class netd_pcap_recv_thread : public matrix_thread
{
public:
	netd_pcap_recv_thread(netd_pcap_service* pcap_service_ptr);
	~netd_pcap_recv_thread();
public:
	void stop();

protected:
	void run();
private:
	HANDLE stop_event_;//!<�������̵߳�ʱ��֪ͨ
	netd_pcap_service* pcap_service_ptr_;
	// 2012.06.21 cxm
	int m_iRunTimes;
	// ��ʱ��ʼ����������
	DWORD m_dwStartCount[RunTimes];
	// ��ʱ��������������
	DWORD m_dwStopCount[RunTimes];
};

#endif /*__NETD_PCAP_RECV_THREAD__*/