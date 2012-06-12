/**
@brief	���ļ�Ϊ����socket�������ʵ���ļ�
@details	
@file	line.socket.cpp
@note	�̳У�CSocket  
@see	
@version	
@author	kuoxin	
@bug
*/


#include "stdafx.h"
#include "line.h"
#include "line.socket.h"

line_socket::line_socket():ip_(__TEXT("")), port_(0), recv_buff_size_(line_socket::CURRENT_RECVBUF_SIZE), stop_event_(FALSE, TRUE)
{
	packet_id_ = timestep_ = GetTickCount();
	recv_proc_thread_ = NULL;
	check_timeout_thread_ = NULL;
	send_proc_thread_ = NULL;
} 

line_socket::~line_socket()
{
	
}

/**
@fn void set_frame_head_and_tail(m_oCommFrameStruct& frame)
@detail ��д���ݰ�ͷβ��Ϣ
@param[in]	frame	���ݰ�ͷ	
@return void
@note	
*/
BOOL line_socket::Create(UINT nSocketPort, int nSocketType,LPCTSTR lpszSocketAddress)
{
	BOOL b_ret = TRUE;

	if(lpszSocketAddress != NULL)	ip_.Format(__TEXT("%s"), lpszSocketAddress);
	if(nSocketPort != 0) port_ = nSocketPort;

	b_ret = CAsyncSocket::Create(0x0,	nSocketType, 	FD_READ|FD_WRITE|FD_CONNECT|FD_CLOSE,  NULL);

	//���ý��ܻ���
	int iOptionValue = recv_buff_size_ != 0 ?recv_buff_size_ : CURRENT_RECVBUF_SIZE;
	int iOptionLen = sizeof(int);
	SetSockOpt(SO_RCVBUF, (void*)&iOptionValue, iOptionLen, SOL_SOCKET);

	//���÷��ͻ���Ϊ0
	iOptionValue = 0;
	iOptionLen = sizeof(int);
	SetSockOpt(SO_SNDBUF, (void*)&iOptionValue, iOptionLen, SOL_SOCKET);

	if(b_ret){
		recv_proc_thread_ = AfxBeginThread(recv_processing_thread_proc, this);
		check_timeout_thread_ = AfxBeginThread(check_timeout_thread_proc, this);
		send_proc_thread_ = AfxBeginThread(send_processing_thread_proc, this);
		if(recv_proc_thread_ == NULL || check_timeout_thread_ == NULL || send_proc_thread_ == NULL){
			Close();
			b_ret = FALSE;
		}
	}

	return b_ret;
}

/**
@fn void SetPackageCmd(SOCKET_PACKAGE_SENT& frame, unsigned short cmd, char cmd_type)
@detail ��д������
@param[in]	frame	����ͷ
@param[in]	cmd		֡�����֣�����֡�Ĺ���	
@param[in]	cmd_type	֡���Ϊ1��Ϊ�������Ϊ2��Ϊ��ѯ���Ϊ3��ΪӦ������
@return void
@note	
*/
void line_socket::SetPackageCmd(SOCKET_PACKAGE_SENT& frame, unsigned short cmd, char cmd_type)
{
	frame.cmd_ = cmd;
	frame.cmd_type_ = cmd_type;
}

/**
@fn void SetPackageNum(SOCKET_PACKAGE_SENT& frame, unsigned int num, unsigned int index)
@detail ��д���ݰ�������
@param[in]	frame	����ͷ
@param[in]	num		��֡��
@param[in]	index	֡���
@return void
@note	
*/
void line_socket::SetPackageNum(SOCKET_PACKAGE_SENT& frame, unsigned int num, unsigned int index)
{
	frame.num_ = num;
	frame.idx_ = index;
}

/**
@fn void SetPackageInfoSize(SOCKET_PACKAGE_SENT& frame, unsigned short size)
@detail ָ����ǰ���ݰ���С
@param[in]	frame	ǰ���ݰ�ͷ
@param[in]	size	֡���ݳ���
@return void
@note	
*/
void line_socket::SetPackageInfoSize(SOCKET_PACKAGE_SENT& frame, unsigned short size)
{
	frame.size_ = size;// + 34;
}

/**
@fn void SetPackage(SOCKET_PACKAGE_SENT& frame, const void* buf, unsigned int size)
@detail ָ����ǰ���ݰ���С
@param[in]	frame	ǰ���ݰ�ͷ
@param[in]	size	֡���ݳ���
@return void
@note	
*/
void line_socket::SetPackage(SOCKET_PACKAGE_SENT& frame, const void* buf, unsigned int size)
{
	CopyMemory(frame.pack_, buf, size);
	SetPackageInfoSize(frame, size);
}

/**
@fn SOCKET_PACKAGE_SENT_PTR pop_free_pack()
@detail �õ�һ���������ݰ�
@param[in]	void
@return ����һ�����ݰ�ָ��,ÿһ�ζ���ɹ�,�����޷������ڴ�,������NULL
@note	
*/
SOCKET_PACKAGE_SENT_PTR line_socket::pop_free_pack()
{
	int size = 0x0;
	SOCKET_PACKAGE_SENT_PTR ptr = NULL;

	free_pack_queue_lock_.Lock();

	size = free_pack_queue_.size();
	if(size > 0){
		
		ptr = *(free_pack_queue_.begin());
		free_pack_queue_.pop_front();

		free_pack_queue_lock_.Unlock();
	}
	else{
		free_pack_queue_lock_.Unlock();
		ptr = new SOCKET_PACKAGE_SENT;
		ZeroMemory(ptr, sizeof(SOCKET_PACKAGE_SENT));
	}

	return ptr;
}

/**
@fn void push_free_pack(SOCKET_PACKAGE_SENT_PTR pack)
@detail �������ݰ��ṹ�嵽���ö�����
@param[in]	pack	���ݰ�ָ��
@return void
@note	
*/
void line_socket::push_free_pack(SOCKET_PACKAGE_SENT_PTR pack)
{
	if(pack != NULL){
		free_pack_queue_lock_.Lock();
		free_pack_queue_.push_back(pack);
		free_pack_queue_lock_.Unlock();
	}
}

/**
@fn void push_back_wait_sending_queue(SOCKET_PACKAGE_SENT_PTR pack)
@detail ���뽫Ҫ�������ݵ��ȴ����Ͷ�����
@param[in]	pack	���ݰ�ָ��
@return void
@note	
*/
void line_socket::push_back_wait_sending_queue(SOCKET_PACKAGE_SENT_PTR pack)
{
	if(pack != NULL){
		wait_sending_pack_queue_lock_.Lock();
		wait_sending_pack_queue_.push_back(pack);
		wait_sending_pack_queue_lock_.Unlock();
	}
}

/**
@fn void push_front_wait_sending_queue(SOCKET_PACKAGE_SENT_PTR pack)
@detail ���뽫Ҫ�������ݵ��ȴ����Ͷ�����
@param[in]	pack	���ݰ�ָ��
@return void
@note
*/
void line_socket::push_front_wait_sending_queue(SOCKET_PACKAGE_SENT_PTR pack)
{
	if(pack != NULL){
		wait_sending_pack_queue_lock_.Lock();
		wait_sending_pack_queue_.push_front(pack);
		wait_sending_pack_queue_lock_.Unlock();
	}
}

/**
@fn SOCKET_PACKAGE_SENT_PTR pop_wait_sending_queue()
@detail �õ�һ��Ҫ���͵����ݰ��ӵȴ����Ͷ�����
@param[in]	void
@return ����һ�����ݰ�ָ��,���û�н�����NULL
@note	
*/
SOCKET_PACKAGE_SENT_PTR line_socket::pop_wait_sending_queue()
{
	int size = 0x0;
	SOCKET_PACKAGE_SENT_PTR ptr = NULL;

	wait_sending_pack_queue_lock_.Lock();
	size = wait_sending_pack_queue_.size();
	if(size > 0){
		ptr = *(wait_sending_pack_queue_.begin());
		wait_sending_pack_queue_.pop_front();
	}

	wait_sending_pack_queue_lock_.Unlock();
	return ptr;
}

/**
@fn void send_private(SOCKET_PACKAGE_SENT_PTR pack_ptr)
@detail ������뵽���Ͷ�����
@param[in]	pack_ptr	
@return void
@note	
*/
void line_socket::send_private(SOCKET_PACKAGE_SENT_PTR pack_ptr)
{
	int size = 0;
	unsigned short tmp_value;
	char pack[FrameSizeLimit];

	ZeroMemory(pack, sizeof(pack));
	pack[size] = FrameHead1;
	pack[++size] = FrameHead2;
	pack[++size] = FrameHead3;
	pack[++size] = FrameHead4;
	++size;

	tmp_value = pack_ptr->size_ + 28;//except m_cFrameHead & m_usFrameLength
	CopyMemory(pack + size, &tmp_value, sizeof(unsigned short));
	size += sizeof(unsigned short);

	tmp_value = pack_ptr->cmd_type_ == 3 ? CmdReturnBit : 0 ;
	tmp_value += pack_ptr->cmd_;
	memcpy(pack + size, &tmp_value, sizeof(tmp_value));
	size += sizeof(pack_ptr->cmd_);

	memcpy(pack + size, &pack_ptr->server_timestep_, sizeof(pack_ptr->server_timestep_));
	size += sizeof(pack_ptr->server_timestep_);

	memcpy(pack + size, &pack_ptr->client_timestep_, sizeof(pack_ptr->client_timestep_));
	size += sizeof(pack_ptr->client_timestep_);

	memcpy(pack + size, &pack_ptr->serial_id_, sizeof(pack_ptr->serial_id_));
	size += sizeof(pack_ptr->serial_id_);

	pack_ptr->cmd_index_ = 0x0;
	memcpy(pack + size, &pack_ptr->cmd_index_, sizeof(pack_ptr->cmd_index_));
	size += sizeof(pack_ptr->cmd_index_);

	memcpy(pack + size, &pack_ptr->num_, sizeof(pack_ptr->num_));
	size += sizeof(pack_ptr->num_);

	memcpy(pack + size, &pack_ptr->idx_, sizeof(pack_ptr->idx_));
	size += sizeof(pack_ptr->idx_);

	pack[size++] = pack_ptr->result_;
	CopyMemory(pack + size, pack_ptr->pack_, pack_ptr->size_);
	size += pack_ptr->size_;

	pack[size++] = pack_ptr->tail_ = FrameTail;
	CopyMemory(pack_ptr->pack_, pack, size);
	pack_ptr->size_ = size;

	push_back_wait_sending_queue(pack_ptr);	
}

/**
@fn void check_timeout_and_resend_data()
@detail ��鳬ʱ���ط�����
@param	void	
@return void
@note	
*/
void line_socket::check_timeout_and_resend_data()
{
	SOCKET_PACKAGE_SENT_PTR package = NULL;
	std::list<SOCKET_PACKAGE_SENT_PTR>::iterator itr;
	std::list<SOCKET_PACKAGE_SENT_PTR> tmp_queue;

	sent_pack_queue_lock_.Lock();
	itr = sent_pack_queue_.begin();
	while( itr != sent_pack_queue_.end()){
		package = *itr;
		if(package->counter_sent_ < MAX_RESEND_COUNTER){
			if(package->time_counter_ < MAX_TIME_COUNTER){
				++package->time_counter_;
			}
			else{
				tmp_queue.push_back(package);
				itr = sent_pack_queue_.erase(itr);
				continue;
			}
		}
		else{
			if(package->cmd_ == CmdSetHeartBeat){
				sent_pack_queue_lock_.Unlock();
				throw_socket_error(SOCKET_CLOSED);
				Close();
				return;
			}
			else{
				sent_pack_queue_.erase(itr);
				throw_socket_error(SOCKET_RESEND_ERROR);
				break;
			}
		}
		++itr;
	}
	sent_pack_queue_lock_.Unlock();

	for(itr = tmp_queue.begin(); itr != tmp_queue.end(); ++itr){
		package = *itr;
		push_back_wait_sending_queue(package);
	}
}

/**
@fn UINT check_timeout_thread_proc(LPVOID pParam)
@detail ��鳬ʱ���ط�����
@param[in]	pParam �ò�����line_socket*
@return �����̴߳�����Ϣ
@note	
*/
UINT __cdecl line_socket::check_timeout_thread_proc(LPVOID pParam)
{
	line_socket* ls = (line_socket*)pParam;

	while(true){

	//	ls->check_timeout_and_resend_data();		
		if(::WaitForSingleObject(ls->stop_event_.m_hObject, ls->WAITING_FOR_RESP_TIME) 
			== WAIT_OBJECT_0) break;
	}

	AfxEndThread(0);
	return 0;
}

/**
@fn void process_resp_pack(line_socket* ls, SOCKET_PACKAGE_RECV_PTR recv_pack_ptr)
@detail	����Ӧ�����ݰ�
@param[in]	ls				line_socket ָ��
@param[in]	recv_pack_ptr	�������ݰ�ָ��
@return void
@note	
*/
void line_socket::send_socket_message(SOCKET_PACKAGE_RECV_PTR recv_pack_ptr)
{
	//AfxGetApp()->m_pMainWnd->SendMessage(WM_SOCKET_NOTIFY, (WPARAM)recv_pack_ptr, NULL);
}

/**
@fn void process_resp_pack(line_socket* ls, SOCKET_PACKAGE_RECV_PTR recv_pack_ptr)
@detail	����Ӧ�����ݰ�
@param[in]	ls				line_socket ָ��
@param[in]	recv_pack_ptr	�������ݰ�ָ��
@return void
@note	
*/
void line_socket::process_resp_pack(line_socket* ls, SOCKET_PACKAGE_RECV_PTR recv_pack_ptr)
{
	ASSERT(recv_pack_ptr != NULL);
	SOCKET_PACKAGE_SENT_PTR pack_ptr = NULL;
	std::list<SOCKET_PACKAGE_SENT_PTR>::iterator itr;

	ls->sent_pack_queue_lock_.Lock();
	for(itr = ls->sent_pack_queue_.begin(); itr != ls->sent_pack_queue_.end(); ++itr){
		
		pack_ptr = *itr;
		if(pack_ptr){
			if(pack_ptr->client_timestep_ == recv_pack_ptr->client_timestep_ &&
				pack_ptr->cmd_ == recv_pack_ptr->cmd_ &&
				pack_ptr->serial_id_ == recv_pack_ptr->serial_id_){
				
				ls->sent_pack_queue_.erase(itr);
				ls->sent_pack_queue_lock_.Unlock();
				ls->push_free_pack(pack_ptr);
				ls->send_socket_message(recv_pack_ptr);
				return;
			}
			
		}else break;
	}

	ls->sent_pack_queue_lock_.Unlock();
}

/**
@fn void process_pack_recvd(line_socket* ls, SOCKET_PACKAGE_RECV_PTR recv_pack_ptr)
@detail	����
@param[in]	ls				line_socket ָ��
@param[in]	recv_pack_ptr	�������ݰ�ָ��
@return void
@note	
*/
void line_socket::process_pack_recvd(line_socket* ls, SOCKET_PACKAGE_RECV_PTR recv_pack_ptr)
{
	ASSERT(recv_pack_ptr != NULL);

	SOCKET_PACKAGE_SENT_PTR sent_ptr = NULL;

	ls->send_socket_message(recv_pack_ptr);
	sent_ptr = ls->pop_free_pack();

	ls->SetPackageCmd(*sent_ptr, recv_pack_ptr->cmd_, 3);
	ls->SetPackageNum(*sent_ptr, 1, 1);
	ls->SetPackageInfoSize(*sent_ptr, 0);
	sent_ptr->client_timestep_ = get_client_timestamp();
	sent_ptr->server_timestep_ = recv_pack_ptr->server_timestep_;
	sent_ptr->serial_id_ = recv_pack_ptr->serial_id_;

	Send(sent_ptr, 1);
}

/**
@fn UINT __cdecl send_processing_thread_proc(LPVOID pParam)
@detail	����OnSendֻ����WSAEWOULDBLOCK����,Accept��Connectʱ,������Ϣ,�����Ҫʹ�÷����߳�	
@param[in]	pParam �ò�����line_socket*
@return �����̴߳�����Ϣ
@note	
*/
UINT __cdecl line_socket::send_processing_thread_proc(LPVOID pParam)
{
	DWORD dwBytes = 0;

	line_socket* ls = (line_socket*)pParam;
	_ASSERTE(ls);

	SOCKET_PACKAGE_SENT_PTR ptr = NULL;

	while(true){

		if(WaitForSingleObject(ls->stop_event_.m_hObject, 
			ls->RECV_PROCESSING_LOOP_TIME) == WAIT_OBJECT_0) break;

		ptr = ls->pop_wait_sending_queue();
		if(ptr == NULL)	continue;

		dwBytes = ls->Send(ptr->pack_, ptr->size_);

		if(dwBytes == SOCKET_ERROR){
			dwBytes = GetLastError();
			if(dwBytes == WSAEWOULDBLOCK){ continue;}
			else{
				ls->throw_socket_error(dwBytes);
				ls->OnClose(dwBytes);
			}
		}
		else{
			if(ptr->cmd_type_ != 3){
				ptr->time_counter_ = 0x0;
				++ptr->counter_sent_;
				ls->push_sent_pack(ptr);
			}
		}
	}

	AfxEndThread(0);
	return 0;
}

/**
@fn UINT __cdecl recv_processing_thread_proc(LPVOID pParam)
@detail		�����̴߳�����յ��ı����ڵȴ���������е����ݰ�
@param[in]	pParam �ò�����line_socket*
@return �����̴߳�����Ϣ
@note	
*/
UINT __cdecl line_socket::recv_processing_thread_proc(LPVOID pParam)
{
	line_socket* ls = (line_socket*)pParam;
	SOCKET_PACKAGE_RECV_PTR recv_ptr = NULL;
	std::list<SOCKET_PACKAGE_RECV_PTR>::iterator itr; 
	std::list<SOCKET_PACKAGE_RECV_PTR> tmp_list;

	while(true){

		if(WaitForSingleObject(ls->stop_event_.m_hObject, 
			ls->RECV_PROCESSING_LOOP_TIME) == WAIT_OBJECT_0) break;
		
		ls->wait_processing_pack_queue_lock_.Lock();

		for(itr = ls->wait_processing_pack_queue_.begin(); itr != ls->wait_processing_pack_queue_.end(); ++itr){
			recv_ptr = *itr;
			if(recv_ptr->cmd_type_ == 3)	{	ls->process_resp_pack(ls, recv_ptr);}
			else												{	ls->process_pack_recvd(ls, recv_ptr);}
			tmp_list.push_back(recv_ptr);
		}

		ls->wait_processing_pack_queue_.clear();
		ls->wait_processing_pack_queue_lock_.Unlock();

		for(itr = tmp_list.begin(); itr != tmp_list.end(); ++itr){
			recv_ptr = *itr;
			ls->push_free_processing_pack(recv_ptr);
		}
		tmp_list.clear();
	}

	AfxEndThread(0);
	return 0;
}

/**
@fn int Send(const void* lpBuf, int nBufLen, int nFlags)
@detail ����Send����,�ú�����֧�����ݵķֶη���
@note	
*/
int line_socket::Send(const void* lpBuf, int nBufLen, int nFlags)
{
	int sizeSent = 0x0;
	int size = 0x0;

	while(sizeSent < nBufLen){
		
		if((size = CAsyncSocket::Send((char*)(lpBuf) + sizeSent, nBufLen - sizeSent, nFlags)) != SOCKET_ERROR)
				{	sizeSent += size;	}
		else	{	sizeSent = size;	break;}
	}

	return sizeSent;
}

/**
@fn bool line_socket::Send(SOCKET_PACKAGE_SENT_PTR pack, int pack_num)
@detail �ú���������Ͷ�ݵ����Ͷ�����
@param[in]	pack		�������ݰ�����
@param[in]	pack_num	���ݰ������С
@return ������ͳɹ�������true, ���򽫷���false
@note	
*/
bool line_socket::Send(SOCKET_PACKAGE_SENT_PTR pack, int pack_num)
{
	bool is_ok = true;

	wait_sending_pack_queue_lock_.Lock();
	for(int i = 0; i < pack_num; ++i)
		if((pack + i) != NULL){	send_private(pack + i);	}
	wait_sending_pack_queue_lock_.Unlock();
	return is_ok;
}

/**
@fn SOCKET_PACKAGE_RECV_PTR pop_free_processing_pack()
@detail ����һ������ʹ�õĽ������ݰ�
@return ����ɹ����������ݽṹ, ���򽫷���NULL
@note	
*/
SOCKET_PACKAGE_RECV_PTR line_socket::pop_free_processing_pack()
{
	int size = 0x0;
	SOCKET_PACKAGE_RECV_PTR ptr = NULL;

	free_processing_pack_queue_lock_.Lock();
	size = free_processing_pack_queue_.size();
	if(size > 0){
		ptr = *(free_processing_pack_queue_.begin());
		free_processing_pack_queue_.pop_front();
		free_processing_pack_queue_lock_.Unlock();
	}
	else{
		free_processing_pack_queue_lock_.Unlock();
		ptr = new SOCKET_PACKAGE_RECV;
		ZeroMemory(ptr, sizeof(SOCKET_PACKAGE_RECV));
	}
	return ptr;
}

/**
@fn void push_free_processing_pack(SOCKET_PACKAGE_RECV_PTR pack)
@detail �������ݰ����뱸�ö����� 
@param[in]	pack		�������ݰ�
@return void
@note	
*/
void line_socket::push_free_processing_pack(SOCKET_PACKAGE_RECV_PTR pack)
{
	if(pack){
		free_processing_pack_queue_lock_.Lock();
		free_processing_pack_queue_.push_back(pack);
		free_processing_pack_queue_lock_.Unlock();
	}
}

/**
@fn void push_wait_processing_queue(SOCKET_PACKAGE_RECV_PTR pack)
@detail �ú���������Ͷ�ݵ����Ͷ�����
@param[in]	pack		�������ݰ�����
@param[in]	pack_num	���ݰ������С
@return ������ͳɹ�������true, ���򽫷���false
@note	
*/
void line_socket::push_wait_processing_queue(SOCKET_PACKAGE_RECV_PTR pack)
{
	if(pack){
		wait_processing_pack_queue_lock_.Lock();
		wait_processing_pack_queue_.push_back(pack);
		wait_processing_pack_queue_lock_.Unlock();
	}
}

/**
@fn void push_wait_processing_queue_non_repeat(SOCKET_PACKAGE_RECV_PTR pack)
@detail �ú���������Ͷ�ݵ����Ͷ�����
@param[in]	pack		�������ݰ�����
@param[in]	pack_num	���ݰ������С
@return ������ͳɹ�������true, ���򽫷���false
@note	
*/
void line_socket::push_wait_processing_queue_non_repeat(SOCKET_PACKAGE_RECV_PTR pack)
{
	if(pack){

		bool is_equal = false;
		std::list<SOCKET_PACKAGE_RECV_PTR>::iterator itr;
		SOCKET_PACKAGE_RECV_PTR ptr = NULL;

		wait_processing_pack_queue_lock_.Lock();
		for(itr = wait_processing_pack_queue_.begin(); itr != wait_processing_pack_queue_.end(); ++itr){
			ptr = *itr; 
			if(ptr->cmd_ == pack->cmd_ && ptr->cmd_type_ == pack->cmd_type_&&
				ptr->server_timestep_ == pack->server_timestep_ && ptr->serial_id_ == pack->serial_id_ && 
				ptr->num_ == pack->num_ && ptr->index_ == ptr->index_ &&
				ptr->client_timestep_ == pack->client_timestep_){ is_equal =  true; break;}
		}

		if(!is_equal)	wait_processing_pack_queue_.push_back(pack);
		wait_processing_pack_queue_lock_.Unlock();
	}
}


/**
@fn SOCKET_PACKAGE_RECV_PTR pop_wait_processing_queue()
@detail �ú���������Ͷ�ݵ����Ͷ�����
@param[in]	pack		�������ݰ�����
@param[in]	pack_num	���ݰ������С
@return ������ͳɹ�������true, ���򽫷���false
@note	
*/
SOCKET_PACKAGE_RECV_PTR line_socket::pop_wait_processing_queue()
{
	int size = 0x0;
	SOCKET_PACKAGE_RECV_PTR ptr = NULL;

	wait_processing_pack_queue_lock_.Lock();
	size = wait_processing_pack_queue_.size();
	if(size > 0){
		ptr = *(wait_processing_pack_queue_.begin());
		wait_processing_pack_queue_.pop_front();
		wait_processing_pack_queue_lock_.Unlock();
	}
	else{
		wait_processing_pack_queue_lock_.Unlock();
		ptr = new SOCKET_PACKAGE_RECV;
		ZeroMemory(ptr, sizeof(SOCKET_PACKAGE_RECV));
	}

	return ptr;
}

/**
@fn void throw_socket_error(int error)
@detail �ú���������socket������Ϣ���������
@param[in]	error	socket������
@return void
@note	
*/
void line_socket::throw_socket_error(int error)
{
	((CLineApp*)AfxGetApp())->m_pMainWnd->PostMessage(WM_REPORT_ERROR, (WPARAM)error);
}

/**
@fn void analyze_package_and_push_recv_queue(SOCKET_PACKAGE_RECV_PTR package)
@detail �ֽ����ݰ���������뵽���ܶ�����
@param[in/out]	package	�������ݰ�����
@return void
@note	�޸�package�ڲ�����
*/
void line_socket::analyze_package_and_push_recv_queue(SOCKET_PACKAGE_RECV_PTR package)
{

	SOCKET_PACKAGE_RECV_PTR ptr = pop_free_processing_pack();
	int size = sizeof(package->cmd_);

	CopyMemory(&package->cmd_, package->pack_, size);
	
	package->cmd_type_ = package->cmd_ >> 15;
	package->cmd_type_ = package->cmd_type_ == 0x1 ? 3 : 1;
	if(package->cmd_type_ == 0x3)		package->cmd_ &= 0x7fff;

	CopyMemory(&package->server_timestep_, package->pack_ + size, sizeof(package->server_timestep_));
	size += sizeof(package->server_timestep_);

	CopyMemory(&package->client_timestep_, package->pack_ + size, sizeof(package->client_timestep_));
	size += sizeof(package->client_timestep_);     

	CopyMemory(&package->serial_id_, package->pack_ + size, sizeof(package->serial_id_));
	size += sizeof(package->serial_id_);

	CopyMemory(&package->cmd_index_, package->pack_ + size, sizeof(package->cmd_index_));
	size += sizeof(package->cmd_index_);

	CopyMemory(&package->num_, package->pack_ + size, sizeof(package->num_));
	size += sizeof(package->num_);

	CopyMemory(&package->index_, package->pack_ + size, sizeof(package->index_));
	size += sizeof(package->index_);

	package->result_ = package->pack_[size];
	size += sizeof(package->result_);

	package->tail_ = package->pack_[package->size_ - 1];

	package->size_ = package->length_ - size - sizeof(package->tail_);
	MoveMemory(package->pack_, package->pack_ + size, package->size_);

	CopyMemory(ptr, package, sizeof(SOCKET_PACKAGE_RECV));
	push_wait_processing_queue_non_repeat(ptr);

	ZeroMemory(package, sizeof(SOCKET_PACKAGE_RECV));
}

/**
@fn void normalize_package_and_push_recv_queue(SOCKET_PACKAGE_RECV_PTR package)
@detail �������ݰ�,���������ҳ��µ����ݰ�ͷ����Ӧ������,�������������ݰ�����뵽���ܶ�����
@param[in/out]	package	�������ݰ�����
@return void
@note	�޸�package�ڲ�����
*/
void line_socket::normalize_package_and_push_recv_queue(SOCKET_PACKAGE_RECV_PTR package)
{
	int i = 0x0, tmp_value = 0x0;

	SOCKET_PACKAGE_RECV tmp_pack;
	char frame_head[4] = {0x0};

	frame_head[0] = FrameHead1;
	frame_head[1] = FrameHead2;
	frame_head[2] = FrameHead3;
	frame_head[3] = FrameHead4;

	while(package->size_ > 0){

		i = 0;
		ZeroMemory(&tmp_pack, sizeof(tmp_pack));
		if(package->size_ < sizeof(frame_head)){
			package->status_ = HEAD_RECV;
			break;
		}

		i = sizeof(frame_head);
		CopyMemory(tmp_pack.head_, package->pack_, i);
		if(tmp_pack.head_[0] == frame_head[0] && tmp_pack.head_[1] == frame_head[1] &&
			tmp_pack.head_[2] == frame_head[2] && tmp_pack.head_[3] == frame_head[3]){

			tmp_value = package->size_ - i;
			if(tmp_value < sizeof(unsigned short)){//m_oCommFrameStruct::m_usFrameLength

				package->status_ = LENGTH_RECV;
				break;
			}
			else{

				CopyMemory(&tmp_pack.length_, package->pack_+i, sizeof(unsigned short));
				if(tmp_pack.length_ < FrameSizeLimit){	
					
					i += sizeof(unsigned short);//m_oCommFrameStruct::m_usFrameLength
					tmp_value = package->size_ - i;
					if(tmp_pack.length_ < tmp_value){

						tmp_value = i + tmp_pack.length_;
						tmp_value -= sizeof(char);//m_oCommFrameStruct::m_cFrameTail
						tmp_pack.tail_ = package->pack_[tmp_value];
						if(tmp_pack.tail_ == FrameTail){

							tmp_pack.size_ = tmp_pack.length_;
							CopyMemory(tmp_pack.pack_, package->pack_ + i, tmp_pack.length_);
							analyze_package_and_push_recv_queue(&tmp_pack);
							tmp_value = i + tmp_pack.length_;
							package->size_ -= tmp_value;
							MoveMemory(package->pack_, package->pack_ + i, package->size_);
						}
						else{
							package->size_ -= sizeof(frame_head);//m_oCommFrameStruct::m_cFrameHead
							MoveMemory(package->pack_, package->pack_ + i, package->size_);
						}
					}
					else{
						package->status_ = DATA_RECV;
						break;
					}						
				}
				else{
					package->size_ -= sizeof(frame_head);//m_oCommFrameStruct::m_cFrameHead
					MoveMemory(package->pack_, package->pack_ + i, package->size_);
				}
			}
		}
		else{
			package->size_ -= i;
			MoveMemory(package->pack_, package->pack_ + i, package->size_);
		}
	}

	//���ý�������ͷ��־״̬
	if(package->size_ == 0){	package->status_ = HEAD_RECV; }
}

/**
@fn void OnReceive(int nErrorCode)
@detail �̳���CSocket
@note	
*/
void line_socket::OnReceive(int nErrorCode)
{
	int size = 0;
	char frame_head[4] = {0x0};
	int length = 0x0;
	
	frame_head[0] = FrameHead1;
	frame_head[1] = FrameHead2;
	frame_head[2] = FrameHead3;
	frame_head[3] = FrameHead4;

	if(recv_package_.status_ == HEAD_RECV)
		length = sizeof(frame_head);//CommFrame_Struct::m_cFrameHead
	else if(recv_package_.status_ == LENGTH_RECV)
		length = sizeof(recv_package_.length_);//CommFrame_Struct::m_usFrameLength
	else if(recv_package_.status_ == DATA_RECV)
		length = recv_package_.length_;//CommFrame_Struct::m_usFrameLength

	size = Receive(recv_package_.pack_ + recv_package_.size_, length);
	if(size == SOCKET_ERROR){
		if(WSAGetLastError() != WSAEWOULDBLOCK)//��ȡ����,��֪ͨ�����,��ֹͣ����socket,����
			throw_socket_error(size);
	}
	else if(size == 0){//û������
		throw_socket_error(SOCKET_CLOSED);
		Close();
	}
	else if((size + recv_package_.size_) < length){//��ȡС�����ݰ���ʼ��־��С
		recv_package_.size_ += size;
	}
	else{//�õ���ͷ��־��С��ͬ������
		recv_package_.size_ += size;
		recv_package_.pack_[recv_package_.size_] = 0x0;
		switch(recv_package_.status_){
			case HEAD_RECV://�õ����ݰ�ͷ
				recv_package_.size_ = 0x0;
				if(recv_package_.pack_[0] == frame_head[0] &&
					recv_package_.pack_[1] == frame_head[1] &&
					recv_package_.pack_[2] == frame_head[2] &&
					recv_package_.pack_[3] == frame_head[3] ){//�õ���ͷ��־
					recv_package_.status_ = LENGTH_RECV;
					CopyMemory(recv_package_.head_, recv_package_.pack_, sizeof(recv_package_.head_));
				}
				break;
			case LENGTH_RECV://�õ����ݰ����� 
				recv_package_.size_ = 0x0;
				CopyMemory(&recv_package_.length_, recv_package_.pack_ , sizeof(recv_package_.length_));
				if(recv_package_.length_ > FrameSizeLimit){	recv_package_.status_ = HEAD_RECV;}
				else{										recv_package_.status_ = DATA_RECV;}
				break;
			case DATA_RECV://�õ����ݰ�
				if(static_cast<unsigned char>(recv_package_.pack_[recv_package_.size_ - 1]) == FrameTail){ //��β��־��ȷ,���뵽���Ͷ�����
					analyze_package_and_push_recv_queue(&recv_package_);
					recv_package_.size_ = 0x0;
					recv_package_.status_ = HEAD_RECV;
				}
				else{//��β��־����
					normalize_package_and_push_recv_queue(&recv_package_);
				}
				break;
		}
	}
	CAsyncSocket::OnReceive(nErrorCode);
}

/**
@fn void OnConnect(int nErrorCode)
@detail �̳���CSocket
@note	
*/
void line_socket::OnConnect(int nErrorCode)
{
	// TODO: Add your specialized code here and/or call the base class
	ZeroMemory(&recv_package_, sizeof(recv_package_));
	recv_package_.status_ = HEAD_RECV;
	CAsyncSocket::OnConnect(nErrorCode);
}

/**
@fn SOCKET_PACKAGE_SENT_PTR pop_sent_pack()
@detail ȡ��һ�����ݴ��ѷ��͵ȴ����ܶ�����
@param void
@return SOCKET_PACKAGE_SENT_PTRָ��,�������Ϊ��,������NULL
@note	
*/
SOCKET_PACKAGE_SENT_PTR line_socket::pop_sent_pack()
{
	int size = 0;
	SOCKET_PACKAGE_SENT_PTR ptr = NULL;

	sent_pack_queue_lock_.Lock();
	size = sent_pack_queue_.size();
	if(size > 0){
		ptr = *(sent_pack_queue_.begin());
		sent_pack_queue_.pop_front();
	}
	sent_pack_queue_lock_.Unlock();
	
	return ptr;
}

/**
@fn void push_sent_pack(SOCKET_PACKAGE_SENT_PTR pack)
@detail
@param[in] pack SOCKET_PACKAGE_SENT_PTR ��ӷ��ͺ����ݵ�������ȴ�����
@return void
@note	
*/
void line_socket::push_sent_pack(SOCKET_PACKAGE_SENT_PTR pack)
{
	if(pack){
		sent_pack_queue_lock_.Lock();
		sent_pack_queue_.push_back(pack);
		sent_pack_queue_lock_.Unlock();
	}
}

template<typename T> 
void line_socket::clear(std::list<T> queue, CCriticalSection& lock)
{
	T t;
	std::list<T>::iterator itr;

	lock.Lock();
	for(itr = queue.begin(); itr != queue.end(); ++itr){
		
		t = *itr;
		if(t != NULL){delete t;}
	}

	queue.clear();
	lock.Unlock();
}

/**
@fn void Close()
@detail �̳��Ը���ʵ��
@note	CAsyncSocket::Close()
*/
void line_socket::OnClose(int nErrorCode)
{
	// TODO: Add your specialized code here and/or call the base class
	HANDLE handle[] = {	recv_proc_thread_->m_hThread, 
		check_timeout_thread_->m_hThread,
		send_proc_thread_->m_hThread};

	stop_event_.SetEvent();
	WaitForMultipleObjects(sizeof(handle)/sizeof(handle[0]), handle, TRUE, HIT_TEST_TIME);

	clear<SOCKET_PACKAGE_SENT_PTR>(sent_pack_queue_, sent_pack_queue_lock_);
	clear<SOCKET_PACKAGE_SENT_PTR>(free_pack_queue_, free_pack_queue_lock_);
	clear<SOCKET_PACKAGE_SENT_PTR>(wait_sending_pack_queue_, wait_sending_pack_queue_lock_);

	clear<SOCKET_PACKAGE_RECV_PTR>(wait_processing_pack_queue_, wait_processing_pack_queue_lock_);
	clear<SOCKET_PACKAGE_RECV_PTR>(free_processing_pack_queue_, free_processing_pack_queue_lock_);
	CAsyncSocket::OnClose(nErrorCode);
}
