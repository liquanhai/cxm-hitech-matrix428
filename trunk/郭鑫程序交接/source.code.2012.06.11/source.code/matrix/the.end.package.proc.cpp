/*
�жϵ�ǰʱ����Կ�ʼʱ�Ӳ�ѯ���������£�
1. ��ǰû�����յ��װ������Ǽ���������THE_FIRST_PACKAGE_OPTR_COMPELETED_COUNTER
2. ��ǰip�����Ѿ���ɣ�ʹ�÷���Ϊ�鿴ip_setting_list�Ƿ�Ϊ�գ����Ҽ��������ڵ���THE_FIRST_PACKAGE_OPTR_COMPELETED_COUNTER
3. Ҫ��ǰ��·�����ȶ���Ŀǰ����Ϊβ��������Ҫ�����TIME_DELAY_SETTING_CONDITION

ʱ�ӿ�ʼ˳��
1. ���ȿ�ʼ��֤���������ȶ�
2. ���������߽���ʱ�Ӳ�ѯ��Ȼ�����ʱͳ
3. ˳��Ը�����վ����AB��ʱ�Ӻ�ʱͳ
*/

#include "../common/config.h"
#include "../common/typedef.h"
#include "../common/sockimpl.h"
#include "../common/code.conv.h"
#include "matrix.h"
#include "the.end.package.proc.h"
#include "the.end.package.time.delay.proc.h"
#include "common.functions.h"
#include "equipment.comm.order.h"

enum __enuTHE_END_PACKAGE_PROC_IMPL_ERROR
{
	THE_END_PACKAGE_RECV_SIZE_ERROR = 0x100,	//���ܵ��װ���С���ڹ涨��С256
	THE_END_PACKAGE_FORMAT_ERROR = 0x110,		//�����װ�Ϊ�Ƿ����ݰ�
	THE_END_PACKAGE_TIME_ERROR = 0x120,		//�����װ�ʱ����ԭ�װ�ʱ�̲����
	EQUIPMENT_SERIAL_NO_FIND = 0x130,			//����������û�з�����ô������Ӧ����Ϣ
	EQUIPMENT_DELETION_LIST_IS_NULL = 0x140, //�豸���ն���Ϊ�գ������ڴ��Ҫ���յ��豸��Ϣ
	NOT_FIND_ROUTE_ABOUT_THE_EQUIPMENT = 0x150,//û�з������·������ص��豸
};

enum
{
	MATRIX_THE_END_PACKAGE_PROC_PORT = 0x9000,
	EQUIMPMENT_DELETION_ARRAY_SIZE = 1024,
	MATRIX_REQUIRE_TIME_DELAY_SEND_PORT = DESTINATION_PORT,
};

//global variable
extern stdext_hash_map		__serial_no_hash_map;
extern stdext_hash_map		__route_hash_map;
extern int					__work_items_size;	//ʹ���豸����
extern EQUIPMENT_ITEM_PTR	__free_items; //û��ʹ���豸
extern EQUIPMENT_ITEM_PTR	__work_items;

extern LING_ARRAY_ITEM			__line_array[MAX_BIG_LINE_SIZE]; //�������飬��־ÿ���������豸
extern APPLICATION_ENVIRONMENT	__application_environment;
extern unsigned long volatile	__the_first_package_idled_counter; //û���յ����ݣ�����յ�+1, �������zero
extern THE_END_PACKAGE_PROC_RUNNING	__the_end_package_proc_running; //ĳ����·(������A,B; ����A,B)��β���������ڽ�����...

CROSS_LING_ARRAY_ITEM		__cross_line_array[MAX_CROSS_LINE_SIZE];
EQUIPMENT_DELETION_ITEM		__equipment_deletion_array[EQUIMPMENT_DELETION_ARRAY_SIZE];
EQUIPMENT_DELETION_ITEM_PTR __equipment_deletion_list = NULL;
EQUIPMENT_DELETION_ITEM_PTR __equipment_deletion_list_used = NULL; 
SOCKET_IMPL					__the_end_package_socket;

void proc_the_end_package();

EQUIPMENT_ITEM_PTR get_master_laux_ptr(){ return __work_items;}

bool is_starting_the_end_package(EQUIPMENT_ITEM_PTR equipment_ptr, int route)
{
	bool is_ok = false;

	if(__the_end_package_proc_running.the_end_package_status_ == start_the_tail_package_proc){
		if(__the_end_package_proc_running.equipment_ptr_ == equipment_ptr && 
			__the_end_package_proc_running.route_ == route) is_ok = true;
	}	

	return is_ok; 
}

bool is_starting_the_end_package_time_delay(EQUIPMENT_ITEM_PTR equipment_ptr, int route)
{
	bool is_ok = false;

	if(__the_end_package_proc_running.the_end_package_status_ == start_the_tail_package_time_delay_req){
		if(__the_end_package_proc_running.equipment_ptr_ == equipment_ptr && 
			__the_end_package_proc_running.route_ == route) is_ok = true;
	}	

	return is_ok; 
}

bool is_starting_the_end_package_time_delay_setting()
{
	bool is_ok = false;
	if(__the_end_package_proc_running.the_end_package_status_ == start_the_tail_package_time_delay_setting) is_ok = true;
	return is_ok; 
}

bool is_stoppping_the_end_package(){return __the_end_package_proc_running.the_end_package_status_ == stop_the_tail_package_proc ? true :false;};

void start_the_end_package_time_delay(EQUIPMENT_ITEM_PTR equipment_ptr, int route)
{ 
	__the_end_package_proc_running.the_end_package_status_ = start_the_tail_package_time_delay_req; 
	__the_end_package_proc_running.equipment_ptr_ = equipment_ptr;
	__the_end_package_proc_running.route_ = route;
}

void start_the_end_package(EQUIPMENT_ITEM_PTR equipment_ptr, int route)
{ 
	__the_end_package_proc_running.the_end_package_status_ = start_the_tail_package_proc; 
	__the_end_package_proc_running.equipment_ptr_ = equipment_ptr;
	__the_end_package_proc_running.route_ = route;
}

void start_the_end_package_time_delay_setting()
{ 
	__the_end_package_proc_running.the_end_package_status_ = start_the_tail_package_time_delay_setting; 
}

void stop_the_end_package(){	SecureZeroMemory(&__the_end_package_proc_running, sizeof(__the_end_package_proc_running)); }

bool init_the_end_package_proc(TCHAR const* remote_ip)
{
	bool is_ok = true;
	int i = 0;
	int size = sizeof(__equipment_deletion_array)/sizeof(__equipment_deletion_array[0]) - 1;

	if(__the_end_package_socket.socket_)	close_udp_socket(&__the_end_package_socket);

	SecureZeroMemory(&__the_end_package_socket, sizeof(__the_end_package_socket)); 

	__the_end_package_socket.listen_port_ = MATRIX_THE_END_PACKAGE_PROC_PORT;
	__the_end_package_socket.remote_port_ = MATRIX_REQUIRE_TIME_DELAY_SEND_PORT;

	is_ok = create_udp_socket(&__the_end_package_socket, remote_ip);
	if(!is_ok) return is_ok;

	SecureZeroMemory(__equipment_deletion_array, sizeof(__equipment_deletion_array));
	for(i = 0; i < size; ++i)	__equipment_deletion_array[i].next_ = __equipment_deletion_array + i + 1;

	__equipment_deletion_list = __equipment_deletion_array;
	__equipment_deletion_list_used = NULL;

	stop_the_end_package();

	SecureZeroMemory(__cross_line_array, sizeof(__cross_line_array));

	is_ok = async_select(&__the_end_package_socket, __application_environment.main_window_,
						WM_THE_END_PACKAGE_RECV_MESSAGE, FD_READ);
	return is_ok;	
}

void release_the_end_package_proc()
{
	if(__the_end_package_socket.socket_){

		async_select(&__the_end_package_socket, __application_environment.main_window_, 0, 0);
		close_udp_socket(&__the_end_package_socket);
	}
}

//�жϵ�ǰ�����������Ƿ��Ѿ����β������,�ú���ֻ�ʺ�һ��������
bool is_time_delay_setting_of_the_cross_line_completed()
{
	bool is_ok = true;

	if(__cross_line_array[0].the_end_station_item_down_)
		if(!__cross_line_array[0].be_the_following_line_time_delay_setting_completed_)
			return is_ok = false;

	if(__cross_line_array[0].the_end_station_item_up_)
		if(!__cross_line_array[0].be_the_upper_line_time_delay_setting_completed_) is_ok = false;

	return is_ok;
}

/*
�ú�������β������,���õķ�ʽΪWindows message��ʽ��OnReceive
*/
BOOL on_receive_the_end_package(WPARAM wparam, LPARAM lparam)
{
	UNREFERENCED_PARAMETER(wparam);
	int error_code = WSAGETSELECTERROR(lparam);
	fd_set fds;
	int ready;
	timeval timeout = {0};

	if(WSAGETSELECTEVENT(lparam) == FD_READ){

		FD_ZERO(&fds);
		FD_SET(__the_end_package_socket.socket_, &fds);
		ready = select(0, &fds, NULL, NULL, &timeout);
		if(ready == SOCKET_ERROR)	error_code = WSAGetLastError();

		if(ready == 1)	proc_the_end_package();
		else			output_log(IDS_STRING124, error_code);
	}

	return TRUE;	
}

bool check_the_end_package(unsigned char* buf, unsigned buf_size, THE_END_PACKAGE_INFO_PTR pack)
{
	buf_size = buf_size;
	unsigned sn = 0;
	unsigned system_time = 0;
	unsigned route = 0;
	unsigned end = 0;
	unsigned sn_l = 0;
	unsigned ip = 0;

	memcpy(&sn, &buf[0x21], 1);
	memcpy(&ip, &buf[0x1c], 1);
	memcpy(&system_time, &buf[0x26], 1);
	memcpy(&route, &buf[0x2b], 1);
	memcpy(&end, &buf[0x30], 1);
	memcpy(&sn_l, &buf[0x22], 1);

	memcpy(&pack->cmd_word_, &buf[0x1a], 2);
	memcpy(&pack->ip_, &buf[0x1d],4);
	memcpy(&pack->serial_no_, &buf[0x22], 4);
	memcpy(&pack->system_time_, &buf[0x27], 4);

	if (pack->cmd_word_ == CMD_SEARCH && sn == CMD_SN && system_time == CMD_SYSTEM_TIME){
		if(route == CMD_ROUTE_REC && end == CMD_END){

			memcpy(&pack->route_, &buf[0x2c], 4);
			if (sn_l == LAUX)		pack->type_ = LAUX;			
			else if (sn_l == LAUL)	pack->type_ = LAUL;
			else if (sn_l == FDU)	pack->type_ = FDU;
			else					return false;
		}
		else if(route == 0x00 && pack->serial_no_ == SN_MAIN_LAUX){	pack->type_ = SN_MAIN_LAUX;}
		else{	return false;}
	}
	else
		return false;

	return true;
}

//���豸���뵽���ն�����
bool add_equipment_into_deletion_list(EQUIPMENT_ITEM_PTR fdu_equipment_ptr)
{
	EQUIPMENT_DELETION_ITEM_PTR del_ptr = NULL;

	if(__equipment_deletion_list == NULL){

		SetLastError(EQUIPMENT_DELETION_LIST_IS_NULL);
		return false;
	}

	del_ptr = __equipment_deletion_list;
	__equipment_deletion_list = del_ptr->next_;
	del_ptr->next_ = NULL;

	del_ptr->equimpment_ptr_ = fdu_equipment_ptr;
	if(__equipment_deletion_list_used != NULL) del_ptr->next_ = __equipment_deletion_list_used;
	__equipment_deletion_list_used = del_ptr;

	return true;
}

void proc_master_laux_tail_package(EQUIPMENT_ITEM_PTR equipment_ptr, THE_END_PACKAGE_INFO_PTR pack_ptr)
{
	if(!equipment_ptr->is_valid_equipment_){
		pack_ptr = pack_ptr;
		equipment_ptr->is_valid_equipment_ = true;
		equipment_ptr->is_valid_the_end_package_time_delay_resp_ = true;
	}
}

/*
	������ն��в�Ϊ�յĻ�,ÿ�ν�����һ���豸,�ڵ�ǰ���������Ҫ���յ��豸,���ܽ���վ,�ɼ�վ�͵�Դվ
	���ڲ�ͬ�豸�����ò�ͬ�ķ�ʽ:
	����վ:	Ҫע���佻����A,B;����A��B�����Ƿ�����豸,������ڵĻ�,Ҫ����Щ�豸���뵽ɾ���б���,
			ͬʱҪ����Щ�豸ָ��ǰ����վ�����ָ������ΪNULL,Ȼ�����ɾ�����豸
	�ɼ�վ:	�����豸������豸���뵽���ն�����(������ں����豸),Ȼ�����ɾ�����豸
	��Դվ:	ͬ�ɼ�վ

	���豸�ṹ�����·��뵽��ʹ�ö�����
*/
void proc_deletion_equipment_list()
{
	EQUIPMENT_ITEM_PTR equipment_ptr = NULL;
	
	equipment_ptr = __equipment_deletion_list_used != NULL ? __equipment_deletion_list_used->equimpment_ptr_ : NULL;
	if(equipment_ptr){
		
		switch(equipment_ptr->type_){
			case LAUX:
				if(equipment_ptr->down_){
					equipment_ptr->down_->up_ = NULL;
					add_equipment_into_deletion_list(equipment_ptr->down_);
				}

				if(equipment_ptr->up_){
					equipment_ptr->up_->down_ = NULL;
					add_equipment_into_deletion_list(equipment_ptr->up_);
				}

			case LAUL:
			case FDU:
				if(equipment_ptr->left_){
					equipment_ptr->left_->right_ = NULL;
					add_equipment_into_deletion_list(equipment_ptr->left_);
				}

				if(equipment_ptr->right_){
					equipment_ptr->right_->left_ = NULL;
					add_equipment_into_deletion_list(equipment_ptr->right_);
				}

				//reuse 
				--__work_items_size;
				SecureZeroMemory(equipment_ptr, sizeof(EQUIPMENT_ITEM));
				equipment_ptr->right_ = __free_items;
				__free_items = equipment_ptr;
				break;
		}
	}	
}

/*
��������:
	1.	����վβ����ʱ����(�Ƿ���ϴ��������������װ����ͺ͵�ǰҪ������վ���ȶ����ϴ��װ�),�ж��Ƿ����
		��������β��������̴���,���û�жԵ�ǰ����վ����β������,���а���ʱ�����õȲ���
	2. ���յ�ǰ����վ������,����治��ʹ�õĽ����豸
*/
bool proc_laux_time_delay(EQUIPMENT_ITEM_PTR equipment_ptr, THE_END_PACKAGE_INFO_PTR pack_ptr)
{
	bool is_zero_value = true;
	int route = pack_ptr->route_ & ROUTE_DIRECTION_VALUE_MASK;
	EQUIPMENT_ITEM_PTR	cross_equipment_ptr = NULL;
	stdext_hash_map_iterator itr;

	if(__the_first_package_idled_counter >= THE_FIRST_PACKAGE_OPTR_COMPELETED_COUNTER){//�����յ��װ�����
		if(equipment_ptr->the_end_package_count_ >= TIME_DELAY_SETTING_CONDITION){//��ǰ����վ�ȶ�β��

			//�˻����ղ���ʹ�õ���Դ���ȶ�β��׼��ʱͳ
			is_zero_value = true;
			cross_equipment_ptr = get_next_laux_equipment_ptr(equipment_ptr, route);
			while(cross_equipment_ptr){

				if(cross_equipment_ptr->the_end_package_count_ > 0){is_zero_value = false; break;}
				cross_equipment_ptr = get_next_laux_equipment_ptr(cross_equipment_ptr, route);
			}

			if(is_zero_value){
				cross_equipment_ptr = get_next_laux_equipment_ptr(equipment_ptr, route);
				if(cross_equipment_ptr != NULL){

					if(route == ROUTE_UP)	cross_equipment_ptr->up_ = equipment_ptr->down_ = NULL;
					else					cross_equipment_ptr->down_ = equipment_ptr->up_ = NULL;

					add_equipment_into_deletion_list(cross_equipment_ptr);
				}
			}

			cross_equipment_ptr = get_master_laux_ptr();
			send_the_tail_package_requirement_command(cross_equipment_ptr, equipment_ptr, pack_ptr->route_);
			start_the_end_package_time_delay(equipment_ptr, pack_ptr->route_);
		}
	}

	return true;
}

/*
�ú�����Ҫ����:
	1. �Ըý���վ�������������豸����β������������
	2. ���ӵ�ǰ����վ������
*/
bool proc_laux_tail_package(EQUIPMENT_ITEM_PTR equipment_ptr, THE_END_PACKAGE_INFO_PTR pack_ptr)
{
	bool is_zero_value = true;
	int route = pack_ptr->route_ & ROUTE_DIRECTION_VALUE_MASK;
	EQUIPMENT_ITEM_PTR	cross_equipment_ptr = NULL, 
						fdu_equipment_ptr = NULL;
	
	if(equipment_ptr->is_valid_equipment_) return true;
	cross_equipment_ptr = equipment_ptr;

	//��ʱʹ��, ��Ϊ�������Ҫ�Ըü�����-THE_END_PACKAGE_DES_COUNTER
	equipment_ptr->the_end_package_count_ += THE_END_PACKAGE_DES_COUNTER;

	while(cross_equipment_ptr){

		//left fdu
		is_zero_value = true;
		fdu_equipment_ptr = get_next_fdu_equipment_ptr(cross_equipment_ptr, ROUTE_LEFT);
		while(fdu_equipment_ptr){
			
			fdu_equipment_ptr->the_end_package_count_ -= THE_END_PACKAGE_DES_COUNTER;
			if(fdu_equipment_ptr->the_end_package_count_ <= 0)	fdu_equipment_ptr->the_end_package_count_ = 0x0;
			else												is_zero_value = false;																			

			fdu_equipment_ptr = get_next_fdu_equipment_ptr(fdu_equipment_ptr, ROUTE_LEFT);
		}

		if(is_zero_value){

			fdu_equipment_ptr = get_next_fdu_equipment_ptr(cross_equipment_ptr, ROUTE_LEFT);
			if(fdu_equipment_ptr != NULL){

				cross_equipment_ptr->left_ = NULL;
				fdu_equipment_ptr->right_ = NULL;
				if(!add_equipment_into_deletion_list(fdu_equipment_ptr))	return false;
			}
		}
		
		//right fdu
		is_zero_value = true;
		fdu_equipment_ptr = get_next_fdu_equipment_ptr(cross_equipment_ptr, ROUTE_RIGHT);
		while(fdu_equipment_ptr){

			fdu_equipment_ptr->the_end_package_count_ -= THE_END_PACKAGE_DES_COUNTER;
			if(fdu_equipment_ptr->the_end_package_count_ <= 0)	fdu_equipment_ptr->the_end_package_count_ = 0x0;
			else												is_zero_value = false;			

			fdu_equipment_ptr = get_next_fdu_equipment_ptr(fdu_equipment_ptr, ROUTE_RIGHT);
		}

		if(is_zero_value){
	
			fdu_equipment_ptr = get_next_fdu_equipment_ptr(cross_equipment_ptr, ROUTE_RIGHT);
			if(fdu_equipment_ptr != NULL){

				cross_equipment_ptr->right_ = NULL;
				fdu_equipment_ptr->left_ = NULL;
				if(!add_equipment_into_deletion_list(fdu_equipment_ptr))	return false;
			}
		}

		if(cross_equipment_ptr->the_end_package_count_ > 0)
			cross_equipment_ptr->the_end_package_count_ -= THE_END_PACKAGE_DES_COUNTER;

		if(cross_equipment_ptr->the_end_package_count_ < 0)	cross_equipment_ptr->the_end_package_count_ = 0x0;

		cross_equipment_ptr = get_prev_laux_equipment_ptr(cross_equipment_ptr, route);
	}

	return proc_laux_time_delay(equipment_ptr, pack_ptr);
}

//�ɼ�վ�͵�Դվ��β������
bool proc_fdu_laul_time_delay(EQUIPMENT_ITEM_PTR equipment_ptr, THE_END_PACKAGE_INFO_PTR pack_ptr)
{
	bool is_ok = true;
	EQUIPMENT_ITEM_PTR	cross_equipment_ptr = NULL;
	stdext_hash_map_iterator itr;

	if(is_time_delay_setting_of_the_cross_line_completed()){

		itr = __route_hash_map.find(pack_ptr->route_);
		if(itr != __route_hash_map.end()){

			cross_equipment_ptr = itr->second;
			send_the_tail_package_requirement_command(cross_equipment_ptr, equipment_ptr, pack_ptr->route_);
			start_the_end_package_time_delay(equipment_ptr, pack_ptr->route_);
		}
		else{
			SetLastError(NOT_FIND_ROUTE_ABOUT_THE_EQUIPMENT);
			is_ok = false;
		}
	}

	return is_ok;
}

/*
���ڴ����ϵĲɼ�վ�͵�Դվ����β������
	1.	����ǰ����豸β�����м���������,���ü�ȥTHE_END_PACKAGE_DES_COUNTER
	2.	�����豸��β�����ڳ����ȶ�״̬���Ҳ����յ��װ�,����ʱ�Ӵ�����豸����
*/
bool proc_fdu_laul_tail_package(EQUIPMENT_ITEM_PTR equipment_ptr, THE_END_PACKAGE_INFO_PTR pack_ptr)
{
	bool is_ok = true;
	bool be_found_it = false;
	int route = pack_ptr->route_ & ROUTE_DIRECTION_VALUE_MASK;
	EQUIPMENT_ITEM_PTR tmp_equipment_ptr = NULL;

	//����ǰ����豸β�����м���������,���ü�ȥTHE_END_PACKAGE_DES_COUNTER
	tmp_equipment_ptr = get_prev_fdu_equipment_ptr(equipment_ptr, route);
	while(tmp_equipment_ptr){

		tmp_equipment_ptr->the_end_package_count_ -= THE_END_PACKAGE_DES_COUNTER;
		if(tmp_equipment_ptr->the_end_package_count_ < 0) tmp_equipment_ptr->the_end_package_count_ = 0x0;
		tmp_equipment_ptr = get_prev_fdu_equipment_ptr(tmp_equipment_ptr, route);
	}

	//���㵱���豸��β�����ڳ����ȶ�״̬���Ҳ����յ��װ�
	if(__the_first_package_idled_counter >= THE_FIRST_PACKAGE_OPTR_COMPELETED_COUNTER){	
		if(equipment_ptr->the_end_package_count_ >= TIME_DELAY_SETTING_CONDITION){
			
			//�жϵ�ǰ�ڵ���Ƿ񻹴��ڼ�����������Ľڵ㣬��������ڽ�������Դ
			be_found_it = false;
			tmp_equipment_ptr = get_next_fdu_equipment_ptr(equipment_ptr, route);
			while(tmp_equipment_ptr){
			
				if(tmp_equipment_ptr->the_end_package_count_ > 0){ be_found_it = true;	break;}
				tmp_equipment_ptr = get_next_fdu_equipment_ptr(tmp_equipment_ptr, route);
			}
			
			if(!be_found_it){//���յ�β���ĵ�ǰ�豸֮ǰ, û���豸��β��������������,�����豸�����ն�����

				tmp_equipment_ptr = get_next_fdu_equipment_ptr(equipment_ptr, route);
				if(tmp_equipment_ptr != NULL){

					if(route == ROUTE_LEFT) equipment_ptr->left_ = tmp_equipment_ptr->right_ = NULL;
					else					equipment_ptr->right_ = tmp_equipment_ptr->left_ = NULL;

					add_equipment_into_deletion_list(tmp_equipment_ptr);
				}
			}

			//����ʱ�Ӵ���,��Ҫ��ָʱ�Ӳ�ѯ
			is_ok = proc_fdu_laul_time_delay(equipment_ptr, pack_ptr);
		}
	}

	return is_ok;
}

//	����β������
void proc_the_end_package()
{
	int recv_size = 0x0, 
		route_direction = 0x0,
		line_no = 0x0;
	char error_buf[MAX_INPUT_PACKAGE_SIZE * 6] = {0};
	char recv_buf[MAX_INPUT_PACKAGE_SIZE] = {0};
	THE_END_PACKAGE_INFO pack;
	EQUIPMENT_ITEM_PTR equipment_ptr = NULL;

	//��������
	SecureZeroMemory(recv_buf, sizeof(recv_buf));
	recv_size = recv(__the_end_package_socket.socket_, recv_buf, sizeof(recv_buf), 0);
	if(recv_size == SOCKET_ERROR){	

		output_log(IDS_STRING125, recv_size);
		return;
	}
	else if(recv_size < MAX_INPUT_PACKAGE_SIZE){
		SecureZeroMemory(error_buf, sizeof(error_buf));
		recv_size = bin_to_ansi((unsigned char*)recv_buf, recv_size, error_buf, sizeof(error_buf));
		output_log(IDS_STRING127, recv_size, MAX_INPUT_PACKAGE_SIZE);
		return;
	}

#ifdef __MATRIX_DEBUG__
	output_log(IDS_STRING173, __FILE__, __FUNCTION__, __MATRIX_TEXT("���β���Ϸ���,ͬʱ�ֽ����ݰ�"), __MATRIX_TEXT("NULL"));
#endif //__MATRIX_DEBUG__

	//���β���Ϸ���,ͬʱ�ֽ����ݰ�
	SecureZeroMemory(&pack, sizeof(pack));
	if(!check_the_end_package((unsigned char*)recv_buf, recv_size, &pack)){

		SecureZeroMemory(error_buf, sizeof(error_buf));
		recv_size = bin_to_ansi((unsigned char*)recv_buf, recv_size, error_buf, sizeof(error_buf));
		output_log(IDS_STRING128, error_buf, recv_size);
		return;
	}

	//����յ����ݰ��е�ipΪ��,��˵�����豸û�з���ip��ַ,ֱ�ӷ���,ֻ�е�IP��ַ������ϲŽ���β������

	if(pack.ip_ == 0x0){ 

#ifdef __MATRIX_DEBUG__
		output_log(IDS_STRING173, __FILE__, __FUNCTION__, __MATRIX_TEXT("����յ����ݰ��е�ipΪ��,��˵�����豸û�з���ip��ַ,ֱ�ӷ���,ֻ�е�IP��ַ������ϲŽ���β������"), __MATRIX_TEXT("NULL"));
#endif //__MATRIX_DEBUG__
		return;
	}

	//ÿ�λ���1���豸��ɾ��������,��Ҫ��timer��������ʱ�����
#ifdef __MATRIX_DEBUG__
	output_log(IDS_STRING173, __FILE__, __FUNCTION__, __MATRIX_TEXT("ÿ�λ���1���豸��ɾ��������,��Ҫ��timer��������ʱ�����"), __MATRIX_TEXT("NULL"));
#endif //__MATRIX_DEBUG__
	proc_deletion_equipment_list();

	//β��������SN,�����Ƿ��Ѿ�����IP��ַ,����SN,�ҵ��豸�ṹ��
#ifdef __MATRIX_DEBUG__
	output_log(IDS_STRING173, __FILE__, __FUNCTION__, __MATRIX_TEXT("β��������SN,�����Ƿ��Ѿ�����IP��ַ,����SN,�ҵ��豸�ṹ��"), __MATRIX_TEXT("NULL"));
#endif //__MATRIX_DEBUG__
	equipment_ptr = find_serial_no(pack.serial_no_);

	if(equipment_ptr == NULL){//û�ҵ�

		SecureZeroMemory(error_buf, sizeof(error_buf));
		recv_size = bin_to_ansi((unsigned char*)recv_buf, recv_size, error_buf, sizeof(error_buf));
		output_log(IDS_STRING129, pack.serial_no_, error_buf);
		return;
	}

	//���ý��ռ�����,�ü���������ܳ���TIME_DELAY_SETTING_CONDITION
	if(equipment_ptr->the_end_package_count_ < TIME_DELAY_SETTING_CONDITION)
		equipment_ptr->the_end_package_count_ += THE_END_PACKAGE_INC_COUNTER;


#ifdef __MATRIX_DEBUG__
	output_log(IDS_STRING148, equipment_ptr->serial_no_, equipment_ptr->ip_, 
				equipment_ptr->the_end_package_count_, equipment_ptr->type_);
#endif //__MATRIX_DEBUG__

	//�жϵ�ǰβ�������״̬,����в���ֹͣ����β��״̬�Ļ�,������,�ȴ���һ��β������
if(!is_stoppping_the_end_package()){

#ifdef __MATRIX_DEBUG__
		output_log(IDS_STRING173, __FILE__, __FUNCTION__, __MATRIX_TEXT("�ж��Ƿ���β��ʱ�Ӳ�ѯ����"), __MATRIX_TEXT("NULL"));
#endif //__MATRIX_DEBUG__
		if(is_starting_the_end_package_time_delay(equipment_ptr, pack.route_)){ 

			//����ʼ����β�������ʱ��, ����β��ʱ�Ӳ�ѯ��Ӧ��Ϣ
#ifdef __MATRIX_DEBUG__
			output_log(IDS_STRING173, __FILE__, __FUNCTION__, __MATRIX_TEXT("����ʼ����β�������ʱ��, ����β��ʱ�Ӳ�ѯ��Ӧ��Ϣ"), __MATRIX_TEXT("NULL"));
#endif //__MATRIX_DEBUG__
			proc_the_end_package_time_delay_resp(equipment_ptr, pack.route_);
			return;
		}
		else{
			output_log(IDS_STRING171, pack.ip_);
			return;	
		}
	}

	switch(equipment_ptr->type_){
		case SN_MAIN_LAUX:
#ifdef __MATRIX_DEBUG__
			output_log(IDS_STRING173, __FILE__, __FUNCTION__, __MATRIX_TEXT("������վβ������"), __MATRIX_TEXT("NULL"));
#endif //__MATRIX_DEBUG__
			proc_master_laux_tail_package(equipment_ptr, &pack);
			break;
		case LAUX:

			//�ж��Ƿ�ò��ߵ�β�������Ѿ����
#ifdef __MATRIX_DEBUG__
			output_log(IDS_STRING173, __FILE__, __FUNCTION__, __MATRIX_TEXT("�ж��Ƿ�ò��ߵ�β�������Ѿ����"), __MATRIX_TEXT("NULL"));
#endif //__MATRIX_DEBUG__
			route_direction = pack.route_ & ROUTE_DIRECTION_VALUE_MASK;
			if(route_direction == ROUTE_DOWN){ 

				if(__cross_line_array[0].the_end_station_item_down_ == equipment_ptr)
				{	if(__cross_line_array[0].be_the_following_line_time_delay_setting_completed_) return;	}
				else	return;
			}
			else{

				if(__cross_line_array[0].the_end_station_item_up_ == equipment_ptr)
				{	if(__cross_line_array[0].be_the_upper_line_time_delay_setting_completed_) return;}
				else	return;
			}
			
			//������վβ�����
#ifdef __MATRIX_DEBUG__
			output_log(IDS_STRING173, __FILE__, __FUNCTION__, __MATRIX_TEXT("������վβ�����"), __MATRIX_TEXT("NULL"));
#endif //__MATRIX_DEBUG__

			if(!proc_laux_tail_package(equipment_ptr, &pack)){
				SecureZeroMemory(error_buf, sizeof(error_buf));
				recv_size = bin_to_ansi((unsigned char*)recv_buf, recv_size, error_buf, sizeof(error_buf));
				output_log(IDS_STRING131, WSAGetLastError(), error_buf);
			}
			break;
		case FDU:
		case LAUL:
			//�ж��Ƿ�ò��ߵ�β�������Ѿ����
#ifdef __MATRIX_DEBUG__
			output_log(IDS_STRING173, __FILE__, __FUNCTION__, __MATRIX_TEXT("�ж��Ƿ�ò��ߵ�β�������Ѿ����"), __MATRIX_TEXT("NULL"));
#endif //__MATRIX_DEBUG__
			route_direction = pack.route_ & ROUTE_DIRECTION_VALUE_MASK;
			line_no = pack.route_ / ROUTE_BIG_LINE_BASE_NUMBER;

			if(route_direction == ROUTE_LEFT){ 

				if(__line_array[line_no - 1].the_end_station_item_left_ == equipment_ptr)
				{	if(__line_array[line_no - 1].be_the_left_line_time_delay_setting_completed_ ) return;}
			}
			else{

				if(__line_array[line_no - 1].the_end_station_item_right_ == equipment_ptr)
				{	if(__line_array[line_no - 1].be_the_right_line_time_delay_setting_completed_) return;}
			}			

#ifdef __MATRIX_DEBUG__
			output_log(IDS_STRING173, __FILE__, __FUNCTION__, __MATRIX_TEXT("����ɼ�վ���Դվβ�����"), __MATRIX_TEXT("NULL"));
#endif //__MATRIX_DEBUG__
			if(!proc_fdu_laul_tail_package(equipment_ptr, &pack)){

				SecureZeroMemory(error_buf, sizeof(error_buf));
				recv_size = bin_to_ansi((unsigned char*)recv_buf, recv_size, error_buf, sizeof(error_buf));
				output_log(IDS_STRING132, WSAGetLastError(), error_buf);
			}

			break;
		default:{
			output_log(IDS_STRING130, equipment_ptr->type_);
			break;
			}
	}	
}

/*
	����	����ʱ�Ӳ�ѯ����,�÷���ʹ���˹㲥�˿ڹ���
	ע��:	
		1. ����ǽ���վ�Ļ�,�����͵�����������վ�͹㲥��������վ���ڵĽ�����
		2. ����ǲɼ�վ�Ļ�,�����͵���������վ�͹㲥�����ɼ�վ�͵�Դվ���ڵĴ���
*/
void send_the_tail_package_requirement_command(EQUIPMENT_ITEM_PTR laux_ptr, EQUIPMENT_ITEM_PTR fdu_ptr, int route)
{
	int snd_size = 0x0;
	char error_buf[MAX_OUTPUT_PACKAGE_SIZE * 6] = {0};
	char buf[MAX_OUTPUT_PACKAGE_SIZE] = {0};
	SOCKADDR_IN remote_ip;
	
	SecureZeroMemory(&remote_ip, sizeof(remote_ip));
	remote_ip.sin_family = AF_INET;
	remote_ip.sin_port = htons(MATRIX_REQUIRE_TIME_DELAY_SEND_PORT);
	remote_ip.sin_addr.s_addr = htonl(INADDR_BROADCAST);

	//�㲥�����߻򽻲���
	make_require_delay_package(fdu_ptr, (unsigned char*)buf, sizeof(buf));
	snd_size = udp_send(&__the_end_package_socket, buf, sizeof(buf), (SOCKADDR *)&remote_ip);
	if(snd_size != sizeof(buf)){
		snd_size = bin_to_ansi((unsigned char*)buf, sizeof(buf), error_buf, sizeof(error_buf));
		output_log(IDS_STRING134, route, error_buf);
	}

	//����������վ��������վ
	make_require_delay_package_ptop(laux_ptr, (unsigned char*)buf, sizeof(buf));
	snd_size = udp_send(&__the_end_package_socket, buf, sizeof(buf), (SOCKADDR *)&remote_ip);
	if(snd_size != sizeof(buf)){
		snd_size = bin_to_ansi((unsigned char*)buf, sizeof(buf), error_buf, sizeof(error_buf));
		output_log(IDS_STRING134, route, error_buf);
	}
}
