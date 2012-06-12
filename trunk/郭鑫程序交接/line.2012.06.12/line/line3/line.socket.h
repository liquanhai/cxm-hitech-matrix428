/**
@brief	���ļ�Ϊ����socket������������ļ�
@details	
@file	line.socket.h
@note	�̳У�CSocket  
@see	
@version	
@author	kuoxin	
@bug
*/


#ifndef __LINE_SOCKET__
#define __LINE_SOCKET__

#include "net.protocol.h"
#include <list>

#define __in__
#define __out__
#define __in_out__

#define SOCKET_CLOSED 0xff10 //!< ��ʾ�û�,�ÿͻ������������Ѿ��ж�
#define SOCKET_RESEND_ERROR	0xff20//!< �ط�������ݰ�,�����ݰ���������
//#define WM_LINE_SOCKET_NOTIFY WM_USER + 0x100 //!< �Զ���socket֪ͨ��Ϣ

/**
@struct	__tagSOCKET_PACKAGE_SENT
@brief ��ŷ��͵����ݰ���Ϣ
@note	
*/
typedef struct __tagSOCKET_PACKAGE_SENT
{
	unsigned short cmd_;//!< ������
	unsigned char cmd_type_; //!< ����������1Ϊ����, 3ΪӦ��
	unsigned int server_timestep_;//!< �����ʱ���
	unsigned int client_timestep_;//!< �ͻ���ʱ���
	unsigned int serial_id_;//!< ����ˮ��
	unsigned int cmd_index_;//!< // ������ˮ��
	unsigned int num_; //!< �����������ݰ�����
	unsigned int idx_; //!< ��ǰ���ݰ��Ǹ������ֵĵڼ���,��0��ʼ
	char pack_[FrameSizeLimit]; //!< �������ݰ�
	unsigned int size_; //!< �������ݰ���С ����С��FrameSizeLimit
	unsigned int counter_sent_;//!< ���ͼ�����,���ò�������line_socket::MAX_RESEND_COUNTER������,�����ݰ���������,������ʾ�û�
	unsigned int time_counter_;//!< ���ͳ�ʱ��ʱ��
	char result_;//!< Ӧ�����úͲ�ѯ�����Ƿ�ɹ�
	char tail_;//!< ֡β
	int flag_;//!< ���ͱ�־
}SOCKET_PACKAGE_SENT, *SOCKET_PACKAGE_SENT_PTR;

enum __enuPACKET_RECV_STATUS
{	HEAD_RECV = 0x0, LENGTH_RECV, DATA_RECV,};

/**
@struct	__tagSOCKET_PACKAGE_RECV
@brief ��Ž������ݰ���Ϣ
@note	
	֡�����֡�ʱ���������ˮ�ž���ͬ������Ϊ��ͬһ֡
*/
typedef struct __tagSOCKET_PACKAGE_RECV
{
	enum __enuPACKET_RECV_STATUS status_; //!< ����״̬
	char head_[4];//!< ֡ͷ��־
	unsigned short length_;//!< ֡�����ܳ��ȣ�С��֡������
	unsigned short cmd_;//!< ֡�����֣�����֡�Ĺ���
	char cmd_type_;//!< ֡���Ϊ1��Ϊ����,Ϊ3��ΪӦ������
	unsigned int server_timestep_;//!< �����ʱ���
	unsigned int client_timestep_;//!< �ͻ���ʱ���
	unsigned int serial_id_;//!< ����ˮ��
	unsigned int cmd_index_;//!<  ������ˮ��
	unsigned int num_;//!< ��֡��
	unsigned int index_;//!< ֡���
	char result_;//!< Ӧ�����úͲ�ѯ�����Ƿ�ɹ�
	char tail_;//!< ֡β
	unsigned int size_;//!< �������ݽṹ��С
	char pack_[FrameSizeLimit];//!< �������ݰ���С
}SOCKET_PACKAGE_RECV, *SOCKET_PACKAGE_RECV_PTR;

/**
@class line_socket
@brief ��Ҫʵ��socket����
@note ����̳���CSocket
*/
class line_socket : public CAsyncSocket
{
public:
	line_socket();
	~line_socket();

public:
	static const int CURRENT_RECVBUF_SIZE = 10*1024*1024;//!< ���ͻ���
	static const int MAX_RESEND_COUNTER = 3;//!< �ط�����
	static const int HIT_TEST_TIME = 500;//!< ��������ʱ���Ժ���Ϊ��λ
	static const int WAITING_FOR_RESP_TIME = 100000;//!< �ȴ���ʱʱ��
	static const int MAX_TIME_COUNTER = 3;//!< ���ȴ�������Ӧ��ʱ����
	static const int RECV_PROCESSING_LOOP_TIME = 100;//!< ���ܴ���ѭ���ȴ�ʱ��,�Ժ���Ϊ��λ

public:
	virtual void OnReceive(int nErrorCode);
	virtual int Send(const void* lpBuf, int nBufLen, int nFlags = 0);
	virtual void OnConnect(int nErrorCode);
	BOOL Create(UINT nSocketPort = 0,int nSocketType = SOCK_STREAM,LPCTSTR lpszSocketAddress = NULL);

public:
	bool Send(__in__ SOCKET_PACKAGE_SENT_PTR pack, __in__ int pack_num);
	void SetPackageCmd(__in_out__ SOCKET_PACKAGE_SENT& frame, __in__ unsigned short cmd, __in__ char cmd_type);
	void SetPackageNum(__in_out__ SOCKET_PACKAGE_SENT& frame, __in__ unsigned int num, __in__ unsigned int index);
	void SetPackageInfoSize(__in_out__ SOCKET_PACKAGE_SENT& frame, __in__ unsigned short size);
	void SetPackage(__in_out__ SOCKET_PACKAGE_SENT& frame, __in__ const void* buf, __in__ unsigned int size);
	SOCKET_PACKAGE_SENT_PTR GetFreePackSent(){return pop_free_pack();};

protected:
	virtual void send_socket_message(SOCKET_PACKAGE_RECV_PTR recv_pack_ptr);
protected:

	SOCKET_PACKAGE_SENT_PTR pop_free_pack();
	void push_free_pack(SOCKET_PACKAGE_SENT_PTR pack);

	SOCKET_PACKAGE_SENT_PTR pop_sent_pack();
	void push_sent_pack(SOCKET_PACKAGE_SENT_PTR pack);

	void push_back_wait_sending_queue(SOCKET_PACKAGE_SENT_PTR pack);
	void push_front_wait_sending_queue(SOCKET_PACKAGE_SENT_PTR pack);
	SOCKET_PACKAGE_SENT_PTR pop_wait_sending_queue();

	void send_private(SOCKET_PACKAGE_SENT_PTR pack_ptr);

	SOCKET_PACKAGE_RECV_PTR pop_free_processing_pack();
	void push_free_processing_pack(SOCKET_PACKAGE_RECV_PTR pack);

	void push_wait_processing_queue_non_repeat(SOCKET_PACKAGE_RECV_PTR pack);
	void push_wait_processing_queue(SOCKET_PACKAGE_RECV_PTR pack);
	SOCKET_PACKAGE_RECV_PTR pop_wait_processing_queue();

	static UINT __cdecl recv_processing_thread_proc(LPVOID pParam);
	static UINT __cdecl check_timeout_thread_proc(LPVOID pParam);
	static UINT __cdecl send_processing_thread_proc(LPVOID pParam);

	void throw_socket_error(int error);

	void analyze_package_and_push_recv_queue(SOCKET_PACKAGE_RECV_PTR package);
	void normalize_package_and_push_recv_queue(SOCKET_PACKAGE_RECV_PTR package);
	void check_timeout_and_resend_data();
	void process_resp_pack(line_socket* ls, SOCKET_PACKAGE_RECV_PTR recv_pack_ptr);
	void process_pack_recvd(line_socket* ls, SOCKET_PACKAGE_RECV_PTR recv_pack_ptr);

	template<typename T> void clear(std::list<T> queue, CCriticalSection& lock);

	LONG get_client_timestamp(){	return InterlockedIncrement(&timestep_);};
	LONG get_client_pack_id(){	return InterlockedIncrement(&packet_id_);};

protected:
	CString ip_; //!< ������ip��ַ
	unsigned short port_; //!< �������˿�
	unsigned int recv_buff_size_; //!< ���ܻ����С
private:
	CCriticalSection sent_pack_queue_lock_; //!< ������ɵȴ�Ӧ�����ݰ���
	CCriticalSection wait_sending_pack_queue_lock_; //!< �ȴ��������ݰ���
	CCriticalSection free_pack_queue_lock_; //!< ���÷������ݰ���
	std::list<SOCKET_PACKAGE_SENT_PTR> wait_sending_pack_queue_; //!< �ȴ��������ݰ�
	std::list<SOCKET_PACKAGE_SENT_PTR> free_pack_queue_; //!< ���÷������ݰ�,��������Ҫʱȡ�����ڷ���
	std::list<SOCKET_PACKAGE_SENT_PTR> sent_pack_queue_; //!< ������ɵȴ�Ӧ�����ݰ�

	CCriticalSection wait_processing_pack_queue_lock_; //!< �ȴ��������ݰ���
	CCriticalSection free_processing_pack_queue_lock_; //!< ���ô������ݰ���
	std::list<SOCKET_PACKAGE_RECV_PTR> wait_processing_pack_queue_; //!< �ȴ��������ݰ�
	std::list<SOCKET_PACKAGE_RECV_PTR> free_processing_pack_queue_; //!< ���ô������ݰ�

	CWinThread* recv_proc_thread_; //!< ������������߳�,���߳̽����ڷַ��������ݰ�ͬʱ�ṩӦ�����ݰ��Ƚ�
	CWinThread* check_timeout_thread_;//!< ��鳬ʱ�ط��߳�
	CWinThread* send_proc_thread_; //!<����OnSendֻ����WSAEWOULDBLOCK����,Accept��Connectʱ,������Ϣ,�����Ҫʹ�÷����߳�
	
	CEvent stop_event_; //!< ֹͣѭ��֪ͨ�¼�

	SOCKET_PACKAGE_RECV recv_package_; //!< ��ǰ�������ݰ����λ��

	volatile unsigned int timestep_;// �ͻ���ʱ���
	volatile unsigned int packet_id_;// ����ˮ��
public:
	virtual void OnClose(int nErrorCode);
};

#endif /*__LINE_SOCKET__*/