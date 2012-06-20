/*
	��ʱ��������ʹ���˷��Ͷ��еķ�ʽ,ֱ�ӽ�Ҫ���õ�ʱ�ӷ������ݰ����뵽ʱ�Ӷ�����,
	�ɶ��и�����,�ڷ������ݰ���ʹ��:
		DELETION_TOKEN_INDEX = 0x4,	//0������ɾ���� 1��ɾ��,��ʾ�Ѿ����ʱ������
		WAIT_COUNT_TOKEN_INDEX = 0x5, //�ȴ�������,��ʾ�ȴ�ʱ��= SetTimer����ʱ
		PROC_COUNT_TOKEN_INDEX = 0x6, //����ʱ�Ӵ���

*/

#include "../common/config.h"
#include "../common/typedef.h"
#include "../common/sockimpl.h"
#include "../common/code.conv.h"
#include "matrix.h"
#include "the.end.package.proc.h"
#include "the.end.package.time.delay.setting.proc.h"
#include "common.functions.h"
#include "equipment.comm.order.h"

enum
{
	MATRIX_THE_END_PACKAGE_TIME_DELAY_SETTING_PORT = PORT_SET_DELAY,
	MATRIX_THE_END_PACKAGE_TIME_DELAY_SETTING_SND_PORT = DESTINATION_PORT,
	MATRIX_THE_END_PACKAGE_TIME_DELAY_SETTING_SIZE = 1024,
	MAX_THE_END_PACKAGE_TIME_DELAY_WAIT_COUNT = 0x1,
	MAX_THE_END_PACKAGE_TIME_DELAY_PROC_COUNT = 0x3,

	//error
	ROUTE_DIRECTION_ERROR = 0x4001,
	EQUIPMENT_TYPE_NOT_PROC = 0x4002,

};

typedef std::list<TIME_DELAY_SETTING_INFO_PTR> TIME_DELAY_SETTING_LIST;
typedef std::list<TIME_DELAY_SETTING_INFO_PTR>::iterator TIME_DELAY_SETTING_LIST_ITERATOR;

//global variable
extern stdext_hash_map			__route_hash_map;
extern APPLICATION_ENVIRONMENT	__application_environment;
extern CROSS_LING_ARRAY_ITEM	__cross_line_array[MAX_CROSS_LINE_SIZE];

TIME_DELAY_SETTING_INFO __time_delay_setting_array[MATRIX_THE_END_PACKAGE_TIME_DELAY_SETTING_SIZE];
TIME_DELAY_SETTING_INFO_PTR __free_time_delay_setting_list;
TIME_DELAY_SETTING_LIST __time_delay_setting_list; 
SOCKET_IMPL __the_end_package_time_delay_setting_socket;

bool init_the_end_package_time_delay_setting_proc()
{
	bool is_ok = true;
	int i  = 0;

	if(__the_end_package_time_delay_setting_socket.socket_)	close_udp_socket(&__the_end_package_time_delay_setting_socket);
	SecureZeroMemory(&__the_end_package_time_delay_setting_socket, sizeof(__the_end_package_time_delay_setting_socket)); 
	__the_end_package_time_delay_setting_socket.listen_port_ = MATRIX_THE_END_PACKAGE_TIME_DELAY_SETTING_PORT;
	is_ok = create_udp_socket(&__the_end_package_time_delay_setting_socket, SOCKET_BOARDCAST_ADDRESS);
	if(!is_ok) return is_ok;

	SecureZeroMemory(&__time_delay_setting_array, sizeof(__time_delay_setting_array));
	while(i < (sizeof(__time_delay_setting_array)/sizeof(__time_delay_setting_array[0])) - 1){

		__time_delay_setting_array[i].next_ = __time_delay_setting_array + i + 1;
		++i;
	}

	__free_time_delay_setting_list = __time_delay_setting_array;	
	__time_delay_setting_list.clear();

	return is_ok;	
}

void release_the_end_package_time_delay_setting_proc()
{
	if(__the_end_package_time_delay_setting_socket.socket_)
		close_udp_socket(&__the_end_package_time_delay_setting_socket);
}

bool check_set_delay_rec_package(unsigned char* buf, int buf_size, THE_SET_DELAY_PACKAGE_INFO_PTR set_delay_pack_info)
{
	buf_size = buf_size;
	unsigned modify_time_high = 0;
	unsigned modify_time_low = 0;
	unsigned end = 0;

	memcpy(&modify_time_high, &buf[0x1c],1);
	memcpy(&modify_time_low, &buf[0x21], 1);
	memcpy(&end, &buf[0x26], 1);

	memcpy(&set_delay_pack_info->ip_, &buf[0x10],4);
	memcpy(&set_delay_pack_info->cmd_word_, &buf[0x1a], 2);
	memcpy(&set_delay_pack_info->modify_time_high_, &buf[0x1d], 4);
	memcpy(&set_delay_pack_info->modify_time_low_, &buf[0x22], 4);

	if (set_delay_pack_info->cmd_word_ == CMD_SET && end == CMD_END)	return true;
	else																return false;
}

//����__cross_line_array��������
void refresh_cross_line_array(int route_direction) //��ǰֻ�ʺ�1��������
{
	bool is_ok = true;
	EQUIPMENT_ITEM_PTR laux_ptr = NULL, laux_ptr2 = NULL;
	EQUIPMENT_ITEM_PTR lci_ptr = get_master_laux_ptr();

	if(lci_ptr == NULL) return;

	laux_ptr = get_next_laux_equipment_ptr(lci_ptr, route_direction);
	if(laux_ptr){

		if(route_direction == ROUTE_DOWN)		__cross_line_array[0].the_first_station_item_down_ = laux_ptr;
		else if(route_direction == ROUTE_UP)	__cross_line_array[0].the_first_station_item_up_ = laux_ptr;
		else{	output_log(IDS_STRING151, route_direction);	SetLastError(ROUTE_DIRECTION_ERROR); return;}

		while(laux_ptr){
			if(!laux_ptr->is_valid_equipment_)	is_ok = false;
			laux_ptr2 = laux_ptr;
			laux_ptr = get_next_laux_equipment_ptr(laux_ptr, route_direction);
		}

		if(route_direction == ROUTE_DOWN){
			__cross_line_array[0].be_the_following_line_time_delay_setting_completed_ = is_ok;
			__cross_line_array[0].the_end_station_item_down_ = laux_ptr2;
		}
		else{
			__cross_line_array[0].be_the_upper_line_time_delay_setting_completed_ = is_ok;
			__cross_line_array[0].the_end_station_item_up_ = laux_ptr2;
		}		
	}
}

/*
	����ʱ������Ӧ��,���Ҵ����Ӧ��,���ʧ��,���ط�,����ط���������3��
*/
bool proc_the_tail_package_time_delay_setting()
{
	bool is_ok = false;
	int recv_size = 0,
		route_direction = 0x0;
	char recv_buf[MAX_INPUT_PACKAGE_SIZE] = {0};
	char error_buf[MAX_INPUT_PACKAGE_SIZE * 6] = {0};
	unsigned long ioctl_argp = 0L;
	THE_SET_DELAY_PACKAGE_INFO pack;
	TIME_DELAY_SETTING_LIST_ITERATOR itr;
	TIME_DELAY_SETTING_INFO_PTR time_delay_setting_ptr = NULL;
	EQUIPMENT_ITEM_PTR equipment_ptr = NULL;

	SOCKADDR_IN remote_ip;

	SecureZeroMemory(&remote_ip, sizeof(remote_ip));
	remote_ip.sin_family = AF_INET;
	remote_ip.sin_port = htons(MATRIX_THE_END_PACKAGE_TIME_DELAY_SETTING_SND_PORT);
	remote_ip.sin_addr.s_addr = htonl(INADDR_BROADCAST);

#ifdef __MATRIX_DEBUG__
	char dbuf[MAX_STRING_SIZE] = {0};
	int dsize = 0x0;
#endif //__MATRIX_DEBUG__

	while(true){

		if(ioctlsocket(__the_end_package_time_delay_setting_socket.socket_, FIONREAD, &ioctl_argp) == 0){

			if(ioctl_argp > 0){

				recv_size = recv(__the_end_package_time_delay_setting_socket.socket_, recv_buf, sizeof(recv_buf), 0);

				if(recv_size == SOCKET_ERROR)	break;
				else if(recv_size == 0x0){

					WSASetLastError(REMOTE_CLOSE_CONNECTION_GRACEFULLY);
					break;
				}
				else if(recv_size > MAX_INPUT_PACKAGE_SIZE){

					recv_size = bin_to_ansi((unsigned char*)recv_buf, recv_size, error_buf, sizeof(error_buf));
					output_log(IDS_STRING126, error_buf);
					continue;
				}
				else{

#ifdef __MATRIX_DEBUG__
					output_log(IDS_STRING173, __FILE__, __FUNCTION__, __MATRIX_TEXT("����ʱ��������Ӧ�����ʱ�����ݰ��Ϸ���"), "NULL");

					ZeroMemory(error_buf, sizeof(error_buf));
					bin_to_ansi((unsigned char*)recv_buf, sizeof(recv_buf),error_buf, sizeof(error_buf));
					output_log(IDS_STRING173, __FILE__, __FUNCTION__, __MATRIX_TEXT("����ʱ��������Ӧ"), error_buf);
#endif //__MATRIX_DEBUG__

					//process time_delay-setting-resp package
					SecureZeroMemory(&pack, sizeof(pack));
					if(!check_set_delay_rec_package((unsigned char*)recv_buf, recv_size, &pack)){

						recv_size = bin_to_ansi((unsigned char*)recv_buf, recv_size, error_buf, sizeof(error_buf));
						output_log(IDS_STRING140, error_buf);
						continue;
					}

					//�����������Ƿ���������ݰ�ͬip�����ݽṹ,������ֻ�ǱȽ�IP��ַ��û�бȽ��������ݰ��е�����,����ܴ�������
					for(itr = __time_delay_setting_list.begin(); itr != __time_delay_setting_list.end(); ++itr){

						time_delay_setting_ptr = *itr;
						if(time_delay_setting_ptr->equipment_item_->ip_ == pack.ip_){

							time_delay_setting_ptr->pack_[DELETION_TOKEN_INDEX] = 1;
							equipment_ptr = time_delay_setting_ptr->equipment_item_;
#ifdef __MATRIX_DEBUG__
							sprintf_s(dbuf, sizeof(dbuf), __MATRIX_TEXT("IP - %08X"), pack.ip_);
							output_log(IDS_STRING173, __FILE__, __FUNCTION__, __MATRIX_TEXT("���ܵ�ʱ����Ӧ"), dbuf);
#endif //__MATRIX_DEBUG__

							break;
						}
					}
				}
			}
			else	break;
		}
		else	break;
	}

	//��������ʱ�����÷��Ͷ���,�������Ƿ��Ѿ����������͹���
	itr = __time_delay_setting_list.begin();
	while(itr != __time_delay_setting_list.end()){			

		time_delay_setting_ptr = *itr;
		if(time_delay_setting_ptr->pack_[DELETION_TOKEN_INDEX] == 1){//�յ�Ӧ��

			time_delay_setting_ptr->equipment_item_->is_valid_equipment_ = true;
			itr = __time_delay_setting_list.erase(itr);

			//���շ�����Դ�����Ͷ���
			time_delay_setting_ptr->next_ = __free_time_delay_setting_list;
			__free_time_delay_setting_list = time_delay_setting_ptr;

#ifdef __MATRIX_DEBUG__
			sprintf_s(dbuf, sizeof(dbuf), __MATRIX_TEXT("IP - %08X"), time_delay_setting_ptr->equipment_item_->ip_);
			output_log(IDS_STRING173, __FILE__, __FUNCTION__, __MATRIX_TEXT("����ʱ�ӳɹ�"), dbuf);
#endif //__MATRIX_DEBUG__
		}
		else{//���û���յ�Ӧ����Ϣ

			//�жϴ�������ǲ���С��MAX_THE_END_PACKAGE_TIME_DELAY_PROC_COUNT, ���С��Լ��,���ط�
			if(time_delay_setting_ptr->pack_[PROC_COUNT_TOKEN_INDEX] < MAX_THE_END_PACKAGE_TIME_DELAY_PROC_COUNT){ 

				//�ȴ�ʱ�䳬��MAX_THE_END_PACKAGE_TIME_DELAY_WAIT_COUNTʱ, ���ط�
				if(time_delay_setting_ptr->pack_[WAIT_COUNT_TOKEN_INDEX] >= MAX_THE_END_PACKAGE_TIME_DELAY_WAIT_COUNT){

#ifdef __MATRIX_DEBUG__
					ZeroMemory(error_buf, sizeof(error_buf));
					bin_to_ansi(time_delay_setting_ptr->pack_, sizeof(time_delay_setting_ptr->pack_), error_buf, sizeof(error_buf));
					output_log(IDS_STRING173, __FILE__, __FUNCTION__, "ʱ������", error_buf);
#endif //__MATRIX_DEBUG__

					recv_size = udp_send(&__the_end_package_time_delay_setting_socket, (char*)time_delay_setting_ptr->pack_, 
										sizeof(time_delay_setting_ptr->pack_), (SOCKADDR*)&remote_ip);

					if(recv_size != sizeof(time_delay_setting_ptr->pack_)){ //����ʧ�ܴ��� 
						output_log(IDS_STRING141, time_delay_setting_ptr->equipment_item_->ip_);
					}
					else{//���ͳɹ�

						time_delay_setting_ptr->pack_[WAIT_COUNT_TOKEN_INDEX] = 0x0; //�ȴ�ʱ�����������
						++time_delay_setting_ptr->pack_[PROC_COUNT_TOKEN_INDEX];//�ط������ۼ�1
#ifdef __MATRIX_DEBUG__
						sprintf_s(dbuf, sizeof(dbuf), __MATRIX_TEXT("IP %08X; �ȴ�ʱ�����������; �ط�����: %X"), 
							time_delay_setting_ptr->equipment_item_->ip_, time_delay_setting_ptr->pack_[PROC_COUNT_TOKEN_INDEX]);
						output_log(IDS_STRING173, __FILE__, __FUNCTION__, __MATRIX_TEXT("�ط�ʱ�����óɹ�"), dbuf);
#endif //__MATRIX_DEBUG__

					}
				}
				else{	
					++time_delay_setting_ptr->pack_[WAIT_COUNT_TOKEN_INDEX]; //��ӵȴ�ʱ�������
#ifdef __MATRIX_DEBUG__
					sprintf_s(dbuf, sizeof(dbuf), __MATRIX_TEXT("IP %08X; �ȴ�ʱ������� %X; �ط�����: %X"), 
						time_delay_setting_ptr->equipment_item_->ip_, 
						++time_delay_setting_ptr->pack_[WAIT_COUNT_TOKEN_INDEX], 
						time_delay_setting_ptr->pack_[PROC_COUNT_TOKEN_INDEX]);
					output_log(IDS_STRING173, __FILE__, __FUNCTION__, __MATRIX_TEXT("�ȴ�ʱ������Ӧ��"), dbuf);
#endif //__MATRIX_DEBUG__

				}

				++itr;				
			}
			else{ //����ط����,��û���յ�Ӧ��,˵�����豸��������,������ʧЧ
				recv_size = bin_to_ansi((unsigned char*)time_delay_setting_ptr->pack_, sizeof(time_delay_setting_ptr->pack_), 
					error_buf, sizeof(error_buf));

				output_log(IDS_STRING146, time_delay_setting_ptr->pack_[PROC_COUNT_TOKEN_INDEX], 
							time_delay_setting_ptr->equipment_item_->ip_, error_buf);

				//�����豸ʧЧ
				time_delay_setting_ptr->equipment_item_->is_valid_equipment_ = false;

				//������Դ
				itr = __time_delay_setting_list.erase(itr);
				time_delay_setting_ptr->next_ = __free_time_delay_setting_list;
				__free_time_delay_setting_list = time_delay_setting_ptr;
			}
		}
	}

	//�ж��Ƿ��������
	if(__time_delay_setting_list.size() == 0){

		if(equipment_ptr){

			if(equipment_ptr->type_ == LAUX){//����ǽ���վ
				if(equipment_ptr->route_[CROSS_LINE_A_INDEX] == ROUTE_UP)	route_direction = ROUTE_DOWN;
				else														route_direction = ROUTE_UP;

				refresh_cross_line_array(route_direction);//���½���վ����
			}
			else if(equipment_ptr->type_ == FDU || equipment_ptr->type_ == LAUL){ refresh_lines_array(equipment_ptr->route_[0]);}//���´�������
			else{ SetLastError(EQUIPMENT_TYPE_NOT_PROC);	output_log(IDS_STRING152, equipment_ptr->type_); }

			output_log(IDS_STRING150, "OK");
		}
		else{ //û�н��ܵ��κ�����,�����ö���Ϊ��,˵�����ܴ�������

			output_log(IDS_STRING150, "Fault");
		}

		stop_the_end_package();
		is_ok = true;
	}

	return is_ok;
}

bool insert_into_time_delay_setting_resp_list(EQUIPMENT_ITEM_PTR equipment_ptr)
{
	bool is_ok = true;
	TIME_DELAY_SETTING_INFO_PTR ptr = NULL;

#ifdef __MATRIX_DEBUG__
	char dbuf[MAX_STRING_SIZE * 4] = {0};
	int dsize = 0;
#endif //__MATRIX_DEBUG__
	if(__free_time_delay_setting_list == NULL){

		output_log(IDS_STRING147, sizeof(__time_delay_setting_array) / sizeof(__time_delay_setting_array[0]));
		return false;
	}

	ptr = __free_time_delay_setting_list;
	__free_time_delay_setting_list = __free_time_delay_setting_list->next_;

	ptr->equipment_item_ = equipment_ptr;
	ptr->next_ = NULL;

	make_set_delay_package(ptr->equipment_item_, ptr->pack_, sizeof(ptr->pack_));
	__time_delay_setting_list.push_back(ptr);
#ifdef __MATRIX_DEBUG__
	dsize = bin_to_ansi(ptr->pack_, sizeof(ptr->pack_), dbuf, sizeof(dbuf));
	dbuf[dsize] = 0x0;
	output_log(IDS_STRING173, __FILE__, __FUNCTION__, __MATRIX_TEXT("����ʱ���������ݰ���ʱ��������"), dbuf);
#endif //__MATRIX_DEBUG__


	return is_ok;
}

