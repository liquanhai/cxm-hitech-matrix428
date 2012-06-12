/**
@brief	
@details	
@file	
@note	
@see	
@version	1.0.0.1.2011.12.07
@author	kuoxin	
@bug
*/
#ifndef __NETD_APPLICATION_H__
#define __NETD_APPLICATION_H__

class netd_application;

#include "..\core\matrix.application.h"
#include "..\core\matrix.queue.h"
#include "netd.socket.serv.h"
#include "netd.pcap.serv.h"

class inp_data
{
public:
	enum{MAX_IN_BUFFER_SIZE = 128};//256

	inp_data(){SecureZeroMemory(buf_, sizeof(buf_));};
	inp_data(inp_data& data){
		if(&data != this){
			CopyMemory(buf_, data.buf_, sizeof(buf_));
		}
	};
	~inp_data(){};
	unsigned char buf_[MAX_IN_BUFFER_SIZE];
	inp_data& operator= (inp_data const& d){
		if(this != &d){
			CopyMemory(buf_, d.buf_, sizeof(buf_));
		}
		return *this;
	};
	unsigned int copy(const unsigned char* buf, unsigned int size){
		int length = 0;
		SecureZeroMemory(buf_, sizeof(buf_));
		if(size <= MAX_IN_BUFFER_SIZE){	CopyMemory(buf_, buf, length = size);}
		else{							CopyMemory(buf_, buf, length = sizeof(buf_));}
		return length;		 
	};
};

class outp_data
{
public:
	enum{MAX_OUT_BUFFER_SIZE = 128};

public:
	outp_data(unsigned char* buf, unsigned int size){
		SecureZeroMemory(buf_, sizeof(buf_));
		copy(buf, size);
	};

	outp_data(){SecureZeroMemory(buf_, sizeof(buf_));};

	outp_data(outp_data& data){
		if(&data != this){
			CopyMemory(buf_, data.buf_, sizeof(buf_));
		}
	};

	~outp_data(){};

	unsigned char buf_[MAX_OUT_BUFFER_SIZE];

	outp_data& operator= (outp_data const& d){
		if(this != &d){
			CopyMemory(buf_, d.buf_, sizeof(buf_));
		}
		return *this;
	};

	unsigned int copy(const unsigned char* buf, unsigned int size){
		int length = 0;
		SecureZeroMemory(buf_, sizeof(buf_));
		if(size <= MAX_OUT_BUFFER_SIZE){	CopyMemory(buf_, buf, length = size);}
		else{								CopyMemory(buf_, buf, length = sizeof(buf_));}
		return length;		 
	};
};


class netd_application:public matrix_application
{
public:
	netd_application(int argc, char_t **argv, char_t **envp = NULL);
	~netd_application();

public:
	void output_log(TCHAR* log);

protected:
	int run_private();
	bool init_instance_private();
	void release_instance_private();
	void start();
	void stop();
	void clear_console();
	void show_helper(bool first_running, TCHAR cmd_char);
	void show_status_dialog();
	int  read_opt();
	unsigned get_line(FILE* file_ptr, char* buf, int buf_size);

protected:
	static unsigned __stdcall status_dialog_thread_proc(void* args);
	static INT_PTR CALLBACK status_dialog_proc(HWND window_handle, UINT message, WPARAM w_param, LPARAM l_param);

public:
	unsigned int netcard_id_; //!< pcap���������
	unsigned int lci_ip_;//!< LCI ip��ַ(pcap��ȡ�������ݵ���ip) 
	unsigned int lci_inp_port_;//<! pcap��ȡLCI �˿�
	unsigned int lci_outp_port_;//<! pcapд��˿�

	unsigned int matrix_service_ip_;//!< ��λ��ip��ַ(socket������ip,����LCI�������ݰ����͵���ip)
	unsigned int matrix_service_listen_port_;//<! 36866 #socketд����λ���˿�

	unsigned int netd_ip_; //!< ��ת����ip��ַ
	unsigned int netd_listen_port_; //!< ��ת��������˿�
	unsigned int netd_outp_port_; //!< ��ת����ͨ��pcapд�뵽LCI����ת�����Ͷ˿�
	unsigned int netd_recv_buffer_size_;//<! 10485760 #socket��λ�����ܻ���
	unsigned int netd_snd_buffer_size_;//<! 10485760 #socket��λ�����ͻ���

	unsigned int pcap_buff_size_; //<! pcap�����С
	unsigned int pcap_max_package_size_;//!< pcapָ��������ݰ���С
	unsigned int pcap_timeout_;	//!< pcap������ʱʱ���Ժ���Ϊ��λ
	unsigned int pcap_outp_poll_time_; //!< pcapд��LCIʱ,��ѯoutp_queue����ʱ��
	char pcap_filter_[MAX_STRING_SIZE]; //!< ָ����ǰpcapʹ�õĹ���������

	unsigned int inp_queue_size_;//!< ���pcap����(��ȡ)���л����С 
	unsigned int outp_queue_size_;//!< ���pcap���(д��)���л����С

	unsigned int netd_recv_poll_time_;//<! 10 #��ת�������λ���������ݵ���ѯʱ��
	unsigned int netd_snd_poll_time_;//<! 10 #��ת��������λ����������ʱ,��ѯ�������ʱ��

	volatile long pcap_data_inp_num_; //!< pcap������������
	volatile long pcap_data_outp_num_; //!< pcap������������
	volatile long socket_data_received_num_; //!< socket������λ����������
	volatile long socket_data_sent_num_; //!< socket���͸���λ����������

	matrix_queue<inp_data>* inp_queue_; //!< pcap����(��ȡ)����
	matrix_queue<outp_data>* outp_queue_; //!< pcap�����(д��)����

private:
	HWND status_dialog_;//!< ͳ�ƶԻ��� 
	HINSTANCE instance_;//!< ��ǰ����ʵ�����
	HANDLE status_dialog_thread_handle_;//!< ͳ�ƶԻ����߳̾��
	unsigned status_dialog_state_;//!< ���嵱ǰ����ͳ�ƶԻ���״̬ 0 : û�д�������, 1: ��ʾ����, 2: ���ش���

	UINT_PTR event_id_; //!< ͳ�ƶԻ����timer���ID

	CRITICAL_SECTION log_critial_section_; //!< ��־����ٽ�ֵ

	netd_socket_service* socket_service_ptr_;//!< ��λ�����ܷ���������
	netd_pcap_service* pcap_service_ptr_; //!< pcap���ܷ������ݵ�LCI��

	bool netd_service_be_started_;//!<��ǰ�����Ƿ�ʼ��ת����,���Ϊtrue��ʾ��ʼ,����û�п�ʼ;Ĭ��Ϊfalseû�п�ʼ
};

#endif /*__NETD_APPLICATION_H__*/
