/**
@brief	����matrix_socket��
@details	������Ҫʵ��socket�Ļ�������
@file	matrix.socket.h
@note	
@see	
@version	1.0.0.1.2012.02.14
@author	kuoxin	
@bug
*/
#ifndef __MATRIX_SOCKET_H__
#define __MATRIX_SOCKET_H__

#include "matrix.object.h"

/**
@enum matrix_socket_type
@brief ����socket����
*/
enum matrix_socket_type
{
	matrix_tcp_socket_type,	/*!< tcp socket���� */
	matrix_udp_socket_type, /*!< udp socket���� */
	matrix_unknown_socket_type /*!< socket���Ͳ�ȷ�� */
};

/**
@enum matrix_socket_state
@brief ����socket״̬
*/
enum matrix_socket_state
{
	matrix_socket_unconnected_State, 
	matrix_socket_host_lookup_state, 
	matrix_socket_connecting_state,
	matrix_socket_connected_state,
	matrix_socket_listening_state
};

/**
@enum matrix_socket_network_layer_protocol
@brief ���������Э��
*/
enum matrix_socket_network_layer_protocol 
{ 
	matrix_socket_ipv4_protocol, /**!< ipv4Э�� */
	matrix_socket_ipv6_protocol, /**!< ipv6Э�� */
	matrix_socket_unknown_network_layer_protocol /**!< ipЭ�鲻ȷ�� */
};

/**
@enum matrix_socket_error
@brief ����socket����
*/
enum matrix_socket_error 
{ 
	matrix_socket_not_create_socket_error,
	matrix_socket_connected_error,//!< �Ѿ�����,����رղ����ٴ�����
	matrix_socket_connection_refused_error, 
	matrix_socket_remote_host_closed_error, 
	matrix_socket_host_not_found_error, 
	matrix_socket_socket_access_error, 
	matrix_socket_unknown_socket_error 
};

/**
@enum matrix_socket_type
@brief ����socketѡ��
*/
enum matrix_socket_option 
{ 
	matrix_socket_normal_option = 0x00,
	matrix_socket_low_delay_option = 0x01,
	matrix_socket_keep_alive_option = 0x02,
	matrix_socket_boardcast_option = 0x04,	
	matrix_socket_multicast_ttl_option = 0x8,
	matrix_socket_multicast_loopback_option = 0x10
};

class matrix_socket : public matrix_object
{
public:
	matrix_socket(matrix_socket_type socket_type = matrix_udp_socket_type, matrix_object* parent_object_ptr = NULL);
	virtual ~matrix_socket();

public:
	bool create(char const* listen_ip, unsigned short listen_port, 
				char const* remote_ip, unsigned short remote_port,
				unsigned int recv_buffer_size, unsigned int send_buffer_size);

	int recv(void* args = NULL, int flags = 0x0);
	int send(const char* send_buf, unsigned int send_buf_size, const SOCKADDR* remote_ip = NULL, int flag = 0); 
	void close();
	void release();

protected:
	virtual bool recv_private(void* args, const char* buf, unsigned int buf_size);

private:
	SOCKET socket_;

	unsigned int listen_ip_;
	unsigned int remote_ip_;
	unsigned short listen_port_;
	unsigned int recv_buffer_size_;
	unsigned int send_buffer_size_;
	unsigned short remote_port_;

	enum matrix_socket_type socket_type_;
	enum matrix_socket_state socket_state_;
	unsigned int socket_option_;
};

#endif /*__MATRIX_SOCKET_H__*/