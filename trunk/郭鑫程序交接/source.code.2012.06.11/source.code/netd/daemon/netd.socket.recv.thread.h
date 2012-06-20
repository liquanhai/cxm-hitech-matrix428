/**
@brief	����netd_socket_recv_thread��
@details	������Ҫʵ��socket�Ľ������ݹ���
@file	matrix.socket.h
@note	
@see	
@version	1.0.0.1.2012.02.14
@author	kuoxin	
@bug
*/
#ifndef __NETD_SOCKET_RECV_THREAD__
#define __NETD_SOCKET_RECV_THREAD__

#include "netd.socket.serv.h"
#include "..\core\matrix.thread.h"

class netd_socket_recv_thread : public matrix_thread
{
public:
	netd_socket_recv_thread(netd_socket_service* socket_service_ptr);
	~netd_socket_recv_thread();
public:
	void stop();

protected:
	void run();

private:
	HANDLE stop_event_;//!<�������̵߳�ʱ��֪ͨ
	netd_socket_service* socket_service_ptr_;
};

#endif /*__NETD_SOCKET_RECV_THREAD__*/