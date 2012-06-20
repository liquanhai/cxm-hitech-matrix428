/**
@brief	ʵ��AD�ɼ�,ʹ��8�˿�,��ʱʹ��recv��ȡ����,ʹ�õĲ�����Ϊ1K, ��ʱ��: 100MS, Ĭ�϶˿�0x5001 �� 0x5008

@details	����ʵ�ַ���: ÿ�ζ�ʱ������ʱ,��鵱ǰN�˿��Ƿ��յ�����,���һ�	�浽֮ǰ��N-1, N-2, N-3�˿�,
			�������N-1, N-2,N-3�˿��Ƿ��յ�ȫ��AD����,�����ȫ,N-3ֱ�ӱ���AD�ļ���,�����ط�;N-1,N-2�����ط�AD��ѯ����

@file	ad.collection.resp.cpp

@note	ÿһ���豸����Ϊһ���ļ�,�ļ���Ϊ��ǰ�豸��IP��ַ+log,��AD������ط�ʱ, ����Ϣд��ad.recv.data.err��
@see	�����Borland cpp builder ���˿ڳ���
@version	1.0.12.55.2011.8.30.EIGHT.PORTS.1K
@author	kuoxin	
@bug	1.0.12.55.2011.8.30.EIGHT.PORTS.1K	�޸Ļ�����Դ����,�޸���δ��ʼ�ɼ�ʱ,����AD����֡�ط�����
*/

#include "../common/config.h"
#include "../common/typedef.h"
#include "../common/sockimpl.h"
#include "../common/code.conv.h"
#include "matrix.h"
#include "equipment.comm.order.h"
#include "common.functions.h"
#include "ad.collection.resp.h"

/**	\enum (non-name)
	\brief ������ļ���ʹ�õĳ��� 
*/
enum
{
	MATRIX_AD_COLLECTION_RESP_SND_PORT = DESTINATION_PORT,
	MAX_AD_COUNTER = 0x3,
	MAX_AD_WAIT_COUNTER = 0x3,
	DEFAULT_PIPE_SIZE = 0x8,//!< ��ǰ�ļ����˿�����	
	DEFAULT_CHECKING_ARRAY_SIZE = 0x4, //!< �����н�ʹ�õĶ��д�С,��ֵ��Ҫ���ɶ�˿�,�ط�������� 
	DEFAULT_CHECKINg_ARRAY_ITEM_SIZE = 0x2000,//!< ��ǰʹ��0x2000���豸 
	DEFAULT_AD_DATA_COMMAND_SIZE = 0x2000,//!< ��ǰ�����ʹ�õ�AD������С 
	DEFAULT_AD_CIRCLING_COUNTER = 2048,//!< ��ǰADָ���ѭ��������,���ﵽ��ֵ�ǽ����´ӵ�ǰӦ�����ּ�ȥ�������� 
};

/** \struct __tagAD_DATA_COMMAND_PACK
	\brief �����ط����ݰ� 
*/
typedef struct __tagAD_DATA_COMMAND_PACK
{
	unsigned char pack_[MAX_OUTPUT_PACKAGE_SIZE]; //!< ��ǰ�ط����ݰ����� 
	__tagAD_DATA_COMMAND_PACK* next_;				//!< ָ����һ��������ָ��,�����γ�һ������ 
}AD_DATA_COMMAND_PACK, *AD_DATA_COMMAND_PACK_PTR;

/** \struct	__tagAD_DATA_INFO
	\brief AD�ɼ��������ݽṹ 
*/
typedef struct __tagAD_DATA_INFO
{
	EQUIPMENT_ITEM_PTR			equipment_ptr_;		//!< �豸���ݽṹ
	unsigned int				resend_counter_;//!< �ط����������
	unsigned int				offset_;//!< ƫ����
	unsigned char				recv_pack_[MAX_INPUT_PACKAGE_SIZE]; //!< ���ܵ�ָ��
	AD_DATA_COMMAND_PACK_PTR	resent_pack_; //!< ���Ͳ�ѯָ��
	FILE*						output_log_; //!< ÿ���豸AD�ɼ�����ļ�
	bool						be_pack_received_;//!< �Ƿ��յ�����
	unsigned					pkg_time_;	//!< ��ʱ��
}AD_DATA_INFO, *AD_DATA_INFO_PTR;

/** \struct __tagTHE_AD_DATA_REC_PACKAGE_INFO
	\brief	AD�ɼ�����֡ 
*/
typedef struct __tagTHE_AD_DATA_REC_PACKAGE_INFO	
{
	unsigned ip_;	//!< IP��ַ
	unsigned port_;	//!< �˿�
	unsigned cmd_word_;	//!< �ؼ�ֵ
	unsigned offset_;        //!< ƫ����
	unsigned pkg_time_;      //!< ���ʱ��
	unsigned char* data_addr_ptr_; //!< ��¼ָ��
}THE_AD_DATA_REC_PACKAGE_INFO, *THE_AD_DATA_REC_PACKAGE_INFO_PTR;

/** \typedef AD_DATA_HASH_MAP
 \brief �������AD���ݵĴ洢��hash��
 */
typedef stdext::hash_map<unsigned long, AD_DATA_INFO_PTR> AD_DATA_HASH_MAP;

/** \typedef AD_DATA_HASH_MAP_ITERATOR
 \brief �������AD���ݵĴ洢��hash��ĵ�����
 */
typedef AD_DATA_HASH_MAP::iterator AD_DATA_HASH_MAP_ITERATOR;

extern stdext_hash_map __route_hash_map;
extern stdext_hash_map __ip_hash_map;
extern APPLICATION_ENVIRONMENT	__application_environment;
extern bool __be_ad_collection_stopping; //!< �Ƿ�ֹͣAD�ɼ�

unsigned int __pipe_size; //!< ����ʹ�õĴ洢AD֡��ͨ������
unsigned int __current_pipe_index; //!< ��ǰ��Ҫ���ܵ�AD֡��ͨ����������
SOCKET_IMPL_PTR __ad_collection_sockets; //!< ͨ���洢�ṹ��ָ��, ��ǰʹ���˶�̬�����ڴ淽ʽ
FILE* __error_file = NULL; //!< AD����������Ϣ

AD_DATA_INFO __ad_data_array[DEFAULT_CHECKING_ARRAY_SIZE * DEFAULT_CHECKINg_ARRAY_ITEM_SIZE]; //!< ��Ž���AD�������õ���Ԫ����
AD_DATA_HASH_MAP __ad_data_hash_map[DEFAULT_CHECKING_ARRAY_SIZE];//ʹ��IP��ӦAD�洢�ṹ�� //!< ��Ž��ܵ�AD�ɼ����ݺ�,�����0 ... DEFAULT_CHECKING_ARRAY_SIZE hash������

AD_DATA_COMMAND_PACK __ad_data_commands_array[DEFAULT_AD_DATA_COMMAND_SIZE];//!< ��ŷ��͵�AD����Ԫ���ݶ���
AD_DATA_COMMAND_PACK_PTR __free_ad_data_commands; //!< ����һ�������õ���Դ����,�ñ���ָ���������еĵ�һ��Ԫ��
int __the_first_recv_ad_data_counter; //!< ָʾ�ǲ��ǵ�ǰ�ǵ�һ�β�ѯ��������,���������Ҫ��Ϊ���ڿ�ʼ��������ʱ,�������⴦��
bool __the_first_recv_ad_data; //!< �ǲ��ǵ�һ���յ�����,��ʼ��Ϊtrue, ���յ����ݺ����Ϊfalse

/**
@fn	AD_DATA_COMMAND_PACK_PTR get_ad_command_pack()
@brief ��AD������Դ�б��еõ��յ�AD�������ݽṹ
@param	void
@return	AD_DATA_COMMAND_PACK_PTR	����һ����Чָ��,Ҫô����NULL
@sa:
*/
AD_DATA_COMMAND_PACK_PTR get_ad_command_pack()
{
	AD_DATA_COMMAND_PACK_PTR pack_ptr = NULL;

	if(__free_ad_data_commands)	{	pack_ptr = __free_ad_data_commands;	__free_ad_data_commands = __free_ad_data_commands->next_;}
	else						{	pack_ptr = NULL;}
	return pack_ptr;
}

/**
@fn	bool init_ad_collection_resp(unsigned int pipe_size, unsigned short base_port)
@brief ��ʼ������AD�ɼ�����
@param	pipe_size	uint	ָ����ǰ���Խ��ܵ�ͨ������,�ò�������Ϊ8�ı���	
@param	base_port	ushort	ָ����ǰ���Խ��ܵĶ˿ڵ���С�˿ں�, ��ʼ��ʱ,������ͨ������,�������������˿�
@return	bool	����ɹ�����true,���򷵻�false
@sa:����pipe_sizeҪ��ʹ����8�ı���,����б�Ҫȥ���
*/
bool init_ad_collection_resp(unsigned int pipe_size, unsigned short base_port)
{
	bool is_ok = true;
	int size = 0x0;
	int i = 0, j = 0;
	SOCKET_IMPL_PTR socket_ptr = NULL;
	char buf[MAX_STRING_SIZE] = {0};

	if(pipe_size <= 0)	__pipe_size = DEFAULT_PIPE_SIZE;
	else				__pipe_size = pipe_size;

	if(__ad_collection_sockets)	free(__ad_collection_sockets);

	//create socket
	size = __pipe_size * sizeof(SOCKET_IMPL);
	__ad_collection_sockets = (SOCKET_IMPL_PTR)malloc(size);
	if(__ad_collection_sockets == NULL){SetLastError(ALLOC_MEMORY_ERROR); return is_ok = false;}

	SecureZeroMemory(__ad_collection_sockets, size);
	for(socket_ptr = __ad_collection_sockets, i = 0; i < __pipe_size; ++i, ++socket_ptr){

		socket_ptr->listen_port_ = base_port + i;
		socket_ptr->remote_port_ = MATRIX_AD_COLLECTION_RESP_SND_PORT;
		is_ok = create_udp_socket(socket_ptr, SOCKET_BOARDCAST_ADDRESS);
		if(!is_ok){	SetLastError(CREATE_SOCKET_ERROR); return is_ok;}
	}

	__current_pipe_index = 0x0;
	SecureZeroMemory(&__ad_data_array, sizeof(__ad_data_array));
	SecureZeroMemory(__ad_data_commands_array, sizeof(__ad_data_commands_array));

	//make a free data pool
	__free_ad_data_commands = __ad_data_commands_array;
	size = sizeof(__ad_data_commands_array) / sizeof(__ad_data_commands_array[0]) - 1;
	for(i = 0; i < size; ++i)	__ad_data_commands_array[i].next_ = __ad_data_commands_array + i + 1;

	for(i = 0; i < DEFAULT_CHECKING_ARRAY_SIZE; ++i)	__ad_data_hash_map[i].clear();

	//AD data structure
	size = sizeof(__ad_data_array) / sizeof(__ad_data_array[0]);
	if(size < (__ip_hash_map.size() * 4)){	
		SetLastError(ALLOCATE_MEMORY_SIZE_TOO_SMALL);	
		output_log(IDS_STRING165, size, __ip_hash_map.size() * 4);	
		return is_ok = false;
	}

	//create a file for per-ip
	i = 0;
	for(stdext_hash_map::iterator itr = __ip_hash_map.begin(); itr != __ip_hash_map.end(); ++itr){
		
		__ad_data_array[i].equipment_ptr_ = itr->second;
		if(__ad_data_array[i].equipment_ptr_->is_valid_equipment_ && __ad_data_array[i].equipment_ptr_->type_ == FDU){

			sprintf_s(buf, sizeof(buf), "%X.log", itr->first);
			__ad_data_array[i].output_log_ = fopen(buf, "w");
			if(__ad_data_array[i].output_log_ == NULL) {SetLastError(CREATE_AD_DATA_FILE_ERROR); return is_ok = false;}
			
			for(j = 0; j < DEFAULT_CHECKING_ARRAY_SIZE; ++j){

				memcpy(__ad_data_array + i + j, __ad_data_array + i, sizeof(__ad_data_array[0]));
				__ad_data_hash_map[j][itr->first] = __ad_data_array + i + j;
			}
			i += j;
		}
	}

	//error file
	__error_file = fopen("ad.recv.data.err", "w");
	if(__error_file == NULL){SetLastError(CREATE_AD_DATA_ERROR_FILE_ERROR); return is_ok = false;}

	__the_first_recv_ad_data_counter = 0; //ָʾ�ǲ��ǵ�ǰ�ǵ�һ�ν�������
	__the_first_recv_ad_data = true;
	__be_ad_collection_stopping = false;
	return is_ok;
}

void release_ad_collection_resp()
{
	int i = 0;
	SOCKET_IMPL_PTR sock_ptr = __ad_collection_sockets;

	if(sock_ptr != NULL){
		for(i = 0; i < __pipe_size; ++i, ++sock_ptr)	if(sock_ptr)	close_udp_socket(sock_ptr);

		free(__ad_collection_sockets);
		__ad_collection_sockets = NULL;
	}

	for(AD_DATA_HASH_MAP_ITERATOR itr = __ad_data_hash_map[0].begin(); itr != __ad_data_hash_map[0].end(); ++itr){
		fclose(itr->second->output_log_);
		itr->second->output_log_ = NULL;
	}

	for(i = 0; i < DEFAULT_CHECKING_ARRAY_SIZE; ++i)	__ad_data_hash_map[i].clear();

	if(__error_file) fclose(__error_file);

}

bool check_legal_package(unsigned char* buf, int buf_size, THE_AD_DATA_REC_PACKAGE_INFO_PTR ad_data_rec_pack_info)
{
	memcpy(&ad_data_rec_pack_info->ip_, &buf[0x10], 4);
	memcpy(&ad_data_rec_pack_info->port_, &buf[0x18], 2);
	memcpy(&ad_data_rec_pack_info->cmd_word_, &buf[0x1a], 2);
	if (ad_data_rec_pack_info->cmd_word_ == CMD_AD)
	{
		memcpy(&ad_data_rec_pack_info->offset_, &buf[0x1c], 2);
		memcpy(&ad_data_rec_pack_info->pkg_time_, &buf[0x1e], 2);
		ad_data_rec_pack_info->data_addr_ptr_ = buf + 0x24;
		return true;
	}
	else 
		return false;
}

int get_next_pipe_index()
{
	int tmp = __current_pipe_index;
	if(++tmp >= __pipe_size)	tmp = 0;
	return tmp;
}

int get_next_pipe_index(unsigned int current_pipe_index)
{
	int tmp = current_pipe_index;
	if(++tmp >= __pipe_size)	tmp = 0;
	return tmp;
}

int get_prev_pipe_index()
{
	int tmp = __current_pipe_index;
	if(--tmp < 0) tmp += DEFAULT_PIPE_SIZE;
	return tmp;
}

int get_prev_pipe_index(unsigned int current_pipe_index)
{
	int tmp = current_pipe_index;
	if(--tmp < 0) tmp += DEFAULT_PIPE_SIZE;
	return tmp;
}

int get_current_pipe_index(){	return __current_pipe_index;}

int get_ad_data_index_from_pipe_index(int pipe_index)
{
	int resend_array_index = 0x0;
	if(pipe_index < 4)  resend_array_index = pipe_index;
	else				resend_array_index = pipe_index - DEFAULT_CHECKING_ARRAY_SIZE;
	return resend_array_index;
}

bool is_valid_ad_frame(unsigned prev_offset, unsigned current_offset)
{
	bool is_ok = false;
	unsigned tmp = current_offset - prev_offset;
	if(tmp < 0) tmp += DEFAULT_AD_CIRCLING_COUNTER;
	return is_ok = (tmp / 72) == 1 ? true : false;
}

/*@
function:	void proc_ad_collection_resp_private(SOCKET_IMPL_PTR socket_impl_ptr, 
												unsigned pipe_index, 
												bool be_ad_data_resent_again)
args:	socket_impl_ptr			[in]	��ǰʹ�õ�socket���ݽṹָ��,���Ҹ�ָ��Ҫ����ָ���������
		pipe_index				[in]	�ܵ�����
		be_ad_data_resent_again	[in]	�Ƿ�����ط����
return:	void
comment: �ú�����ÿ�ζ�socket���б����ж��Ƿ��������.
*/
void proc_ad_collection_resp_private(SOCKET_IMPL_PTR socket_impl_ptr, unsigned pipe_index, bool be_ad_data_resent_again)
{
	char recv_buf[MAX_INPUT_PACKAGE_SIZE] = {0};
	char error_buf[MAX_INPUT_PACKAGE_SIZE * 6] = {0};
	unsigned long ioctl_argp = 0L;
	int recv_size = 0;
	THE_AD_DATA_REC_PACKAGE_INFO pack;
	SOCKADDR_IN remote_ip;
	unsigned ad_data_index = 0x0;
	AD_DATA_HASH_MAP_ITERATOR itr;	
	AD_DATA_INFO_PTR ad_data_ptr = NULL;
	
	SecureZeroMemory(&remote_ip, sizeof(remote_ip));
	remote_ip.sin_family = AF_INET;
	remote_ip.sin_port = htons(MATRIX_AD_COLLECTION_RESP_SND_PORT);
	remote_ip.sin_addr.s_addr = htonl(INADDR_BROADCAST);

	ad_data_index = get_ad_data_index_from_pipe_index(pipe_index);
	while(true){

		if(ioctlsocket(socket_impl_ptr->socket_, FIONREAD, &ioctl_argp) == 0){

			if(ioctl_argp > 0){

				recv_size = recv(socket_impl_ptr->socket_, recv_buf, sizeof(recv_buf), 0);

				if(recv_size == SOCKET_ERROR)	break;
				else if(recv_size == 0x0){

					WSASetLastError(REMOTE_CLOSE_CONNECTION_GRACEFULLY);
					break;
				}
				else if(recv_size > MAX_INPUT_PACKAGE_SIZE){

					WSASetLastError(AD_DATA_RECV_SIZE_ERROR);
					recv_size = bin_to_ansi((unsigned char*)recv_buf, recv_size, error_buf, sizeof(error_buf));
					output_log(IDS_STRING163, recv_size, error_buf);
					continue;
				}
				else{

					__the_first_recv_ad_data = false;
					SecureZeroMemory(&pack, sizeof(pack));
					//check this data package
					if(!check_legal_package((unsigned char*)recv_buf, recv_size, &pack)){
						SetLastError(AD_DATA_FORMAT_ERROR);
						recv_size = bin_to_ansi((unsigned char*)recv_buf, recv_size, error_buf, sizeof(error_buf));
						output_log(IDS_STRING164, error_buf);
						continue;
					}

					itr = __ad_data_hash_map[ad_data_index].find(pack.ip_);
					if(itr != __ad_data_hash_map[ad_data_index].end()){
						
						ad_data_ptr = itr->second;
						/*��ʾ:
							ǰ��	
								1. ���뱣֤��ǰ������ٶ��ܺ�AD��������ٶȱ�������ȶ�,�������תȦ����
								2. Ӳ���ܹ���֤׼ȷһ�µķ���AD���ݲ�������ж�����

							����	��ǰ��ı�֤�¿��Բ��ÿ���ƫ��������,Ŀǰ��ʵ�ַ�������ȥ���ǱȽ�ƫ����
							תȦ����	��ǰ������һ�����ٶ�����������ֻ�ܴ���1K���������µ����,����1Kʹ�õ�
									ǰ�Ķ�˿ڻ����תȦ����,ʹ�����ñȽϸ���,������ֱ��ʹ�õ��˿ڴ���
							ע��	����˵���ǻ��ڸ��˶��ڵ�ǰ��Ŀ�����,���ܱ�֤׼ȷ��,ֻ�ܲο�
						*/

						ad_data_ptr->be_pack_received_ = true;
						ad_data_ptr->offset_ = pack.offset_;
						ad_data_ptr->pkg_time_ = pack.pkg_time_;
						memcpy(ad_data_ptr->recv_pack_, recv_buf, recv_size);
					}
					else{
						
						WSASetLastError(NOT_FIND_IP_ADDR);
						recv_size = bin_to_ansi((unsigned char*)recv_buf, recv_size, error_buf, sizeof(error_buf));
						output_log(IDS_STRING166, pack.ip_, error_buf);
						continue;
					}
				}
			}
			else	break;
		}
		else	break;
	}

	if(be_ad_data_resent_again && !__the_first_recv_ad_data && !__be_ad_collection_stopping){

		itr = __ad_data_hash_map[ad_data_index].begin();
		while(itr != __ad_data_hash_map[ad_data_index].end()){

			ad_data_ptr = itr->second;
			if(!ad_data_ptr->be_pack_received_){

				ad_data_ptr->resent_pack_ = get_ad_command_pack();
				if(ad_data_ptr->resent_pack_ == NULL){	

					output_log(IDS_STRING167, sizeof(__ad_data_commands_array));	
					SetLastError(NOT_ENOUGH_AD_COMMAND_BUFFER);	
					PostMessage(__application_environment.main_window_, WM_CLOSE, NULL, NULL);
					return;
				}

				if(ad_data_ptr->resend_counter_ == 0)
					make_ad_loss_req_package(ad_data_ptr->equipment_ptr_, ad_data_ptr->resent_pack_->pack_, 
					sizeof(ad_data_ptr->resent_pack_->pack_), 
					socket_impl_ptr->listen_port_, ad_data_ptr->offset_);

				recv_size = udp_send(socket_impl_ptr, (char*)ad_data_ptr->resent_pack_->pack_, 
					sizeof(ad_data_ptr->resent_pack_->pack_), (SOCKADDR*)&remote_ip);

				if(recv_size != sizeof(ad_data_ptr->resent_pack_->pack_)){
					output_log(IDS_STRING169, recv_size, sizeof(ad_data_ptr->resent_pack_->pack_));
					continue;
				}
				else if(recv_size == SOCKET_ERROR){	output_log(IDS_STRING168, WSAGetLastError());	continue;}

				++ad_data_ptr->resend_counter_;
			}
			++itr;
		}
	}
}

void save_ad_data(int pipe_index)
{
	unsigned ad_data_index = get_ad_data_index_from_pipe_index(pipe_index);
	AD_DATA_INFO_PTR ad_data_ptr = NULL;
	AD_DATA_HASH_MAP_ITERATOR itr;

	unsigned int size = 0;
	char buf[MAX_INPUT_PACKAGE_SIZE * 6];

	itr = __ad_data_hash_map[ad_data_index].begin();
	while(itr != __ad_data_hash_map[ad_data_index].end()){

		ad_data_ptr = itr->second;
		if(ad_data_ptr->be_pack_received_){ //д��AD�����ļ�

			size = bin_to_ansi(ad_data_ptr->recv_pack_, sizeof(ad_data_ptr->recv_pack_), buf, sizeof(buf));
			buf[size] = 0x0;
			fprintf(ad_data_ptr->output_log_, "[SN: %X][IP: %X][time: %d][offset: %d] %s\n", 
				ad_data_ptr->equipment_ptr_->serial_no_,
				ad_data_ptr->equipment_ptr_->ip_,
				ad_data_ptr->pkg_time_, ad_data_ptr->offset_, buf);

			//fflush(ad_data_ptr->output_log_);

			if(ad_data_ptr->resend_counter_ > 0){
				fprintf(__error_file, "��ǰSNΪ %X, IP��ַΪ %X���豸, ��ƫ����Ϊ %d�ĵط�, ͨ���ظ�����AD����%d��,�Ž������һ�...\n", 
				ad_data_ptr->equipment_ptr_->serial_no_, ad_data_ptr->equipment_ptr_->ip_,
				ad_data_ptr->offset_, ad_data_ptr->resend_counter_);
			//	fflush(__error_file);
			}

		}
		else{//д�������־

			fprintf(__error_file, "��ǰSNΪ %X, IP��ַΪ %X���豸, ��ƫ����Ϊ %d�ĵط�, ͨ���ظ�AD����%d������, ����û���յ�AD�ɼ�����...\n", 
				ad_data_ptr->equipment_ptr_->serial_no_, ad_data_ptr->equipment_ptr_->ip_,
				ad_data_ptr->offset_, ad_data_ptr->resend_counter_);
			//fflush(__error_file);
		}

		ad_data_ptr->be_pack_received_ = false;
		ad_data_ptr->offset_ = 0x0;
		ad_data_ptr->pkg_time_ = 0x0;
		ad_data_ptr->resend_counter_ = 0x0;

		//�����ط���Դ
		if(ad_data_ptr->resent_pack_){
			ad_data_ptr->resent_pack_->next_ = __free_ad_data_commands;
			__free_ad_data_commands = ad_data_ptr->resent_pack_;
			ad_data_ptr->resent_pack_ = NULL;
		}

		++itr;
	}
}

/**

*/
void proc_ad_collection_resp()
{
	int pipe_index = 0x0;

	//��鵱ǰ�Ķ˿��Ƿ���AD����
	if(__the_first_recv_ad_data_counter >= 0){
		pipe_index = get_current_pipe_index();
		proc_ad_collection_resp_private(__ad_collection_sockets + pipe_index, pipe_index, true);
	}

	//��鵱ǰ�˿�ǰ1���˿�
	if(__the_first_recv_ad_data_counter >= 1){
		pipe_index = get_prev_pipe_index(pipe_index);
		proc_ad_collection_resp_private(__ad_collection_sockets + pipe_index, pipe_index, true);
	}

	//��鵱ǰ�˿�ǰ2���˿�
	if(__the_first_recv_ad_data_counter >= 2){
		pipe_index = get_prev_pipe_index(pipe_index);
		proc_ad_collection_resp_private(__ad_collection_sockets + pipe_index, pipe_index, true);
	}

	//��鵱ǰ�˿�ǰ3���˿��Ƿ��Ѿ����ռ��������
	if(__the_first_recv_ad_data_counter >= 3){
		pipe_index = get_prev_pipe_index(pipe_index);
		proc_ad_collection_resp_private(__ad_collection_sockets + pipe_index, pipe_index, false);
	}

	if(!__the_first_recv_ad_data){

		if(++__current_pipe_index >= __pipe_size)	__current_pipe_index = 0x0;

		//��鵱ǰ�˿�ǰ3���˿��Ƿ��Ѿ����ռ��������,����д�ļ�,����������Ҳд�ļ�
		if(__the_first_recv_ad_data_counter >= 3 && !__be_ad_collection_stopping)
			save_ad_data(pipe_index);

		if(++__the_first_recv_ad_data_counter > __pipe_size)	
			__the_first_recv_ad_data_counter = __pipe_size;
	}
}

