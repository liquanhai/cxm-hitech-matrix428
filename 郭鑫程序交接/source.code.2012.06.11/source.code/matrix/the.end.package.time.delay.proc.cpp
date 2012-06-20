/*
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
#include "the.end.package.time.delay.setting.proc.h"
#include "common.functions.h"

enum __enuTHE_END_PACKAGE_TIME_DELAY_PROC_IMPL_ERROR
{

};

enum __enuMATRIX_THE_END_PACKAGE_TIME_DELAY_PROC_VALUE
{
	THE_END_PACKAGE_TIME_DELAY_RESP_PORT = PORT_REQUIRE_DELAY,
};

//global variable
extern stdext_hash_map __serial_no_hash_map;
extern stdext_hash_map __route_hash_map;
extern int __work_items_size;	//ʹ���豸����
extern EQUIPMENT_ITEM_PTR __free_items; //û��ʹ���豸
extern EQUIPMENT_ITEM_PTR __work_items;
extern APPLICATION_ENVIRONMENT __application_environment; 
SOCKET_IMPL __the_end_package_time_delay_socket;

void proc_the_end_package_time_delay();

bool init_the_end_package_time_delay_proc(TCHAR const* remote_ip)
{
	bool is_ok = true;

	if(__the_end_package_time_delay_socket.socket_)	close_udp_socket(&__the_end_package_time_delay_socket);

	SecureZeroMemory(&__the_end_package_time_delay_socket, sizeof(__the_end_package_time_delay_socket)); 

	__the_end_package_time_delay_socket.listen_port_ = THE_END_PACKAGE_TIME_DELAY_RESP_PORT;

	is_ok = create_udp_socket(&__the_end_package_time_delay_socket, remote_ip);
	if(!is_ok) return is_ok;

	is_ok = async_select(&__the_end_package_time_delay_socket, __application_environment.main_window_,
						WM_THE_END_PACKAGE_TIME_DELAY_RECV_MESSAGE, FD_READ);
	return is_ok;	
}

void release_the_end_package_time_delay_proc()
{
	if(__the_end_package_time_delay_socket.socket_){

		async_select(&__the_end_package_time_delay_socket, __application_environment.main_window_, 0, 0);
		close_udp_socket(&__the_end_package_time_delay_socket);
	}

	KillTimer(__application_environment.main_window_, TIME_DELAY_SETTING_RESP_EVENT_ID);
}

//	����	β��ʱ�Ӳ�ѯ��Ҫ����Windows Message��ʽ��OnReceiver��ʽʵ��
BOOL on_receive_the_end_time_delay_package(WPARAM wparam, LPARAM lparam)
{
	UNREFERENCED_PARAMETER(wparam);
	int error_code = WSAGETSELECTERROR(lparam);
	fd_set fds;
	int ready;
	timeval timeout = {0};

	if(WSAGETSELECTEVENT(lparam) == FD_READ){

		FD_ZERO(&fds);
		FD_SET(__the_end_package_time_delay_socket.socket_, &fds);
		ready = select(0, &fds, NULL, NULL, &timeout);
		if(ready == SOCKET_ERROR)	error_code = WSAGetLastError();

		if(ready == 1)	proc_the_end_package_time_delay();
		else			output_log(IDS_STRING133, error_code);
	}

	return TRUE;	
}

//����յ����ݰ���Ч�Ժͷֽ�
bool check_require_delay_rec_package(unsigned char* buf, int buf_size, THE_REQUIRE_DELAY_PACKAGE_INFO_PTR require_delay_pack_info)
{
	buf_size = buf_size;

	unsigned boardcast_cmd = 0;
	unsigned end = 0;
	unsigned end_ptop = 0;
	memcpy(&boardcast_cmd, &buf[0x1c],1);
	memcpy(&end, &buf[0x26], 1);
	memcpy(&end_ptop, &buf[0x21],1);
	memcpy(&require_delay_pack_info->ip_, &buf[0x10],4);
	memcpy(&require_delay_pack_info->cmd_word_, &buf[0x1a], 2);

	if (require_delay_pack_info->cmd_word_ == CMD_SEARCH && end == CMD_END && boardcast_cmd == CMD_BOARDCAST_PORT_R){

		memcpy(&require_delay_pack_info->require_delay_cmd_, &buf[0x21],1);
		memcpy(&require_delay_pack_info->send_time_, &buf[0x24], 2);
		memcpy(&require_delay_pack_info->rec_time_, &buf[0x22], 2);
	}
	else if (require_delay_pack_info->cmd_word_ == CMD_SEARCH && end_ptop == CMD_END){

		memcpy(&require_delay_pack_info->require_delay_cmd_, &buf[0x1c],1);
		memcpy(&require_delay_pack_info->send_time_, &buf[0x1f], 2);
		memcpy(&require_delay_pack_info->rec_time_, &buf[0x1d], 2);
	}
	else{		return false;}

	return true;
}

//�����յ����ݰ����д���
void proc_the_end_package_time_delay()
{
	int recv_size = 0x0;
	char error_buf[MAX_INPUT_PACKAGE_SIZE * 6] = {0};
	char recv_buf[MAX_INPUT_PACKAGE_SIZE] = {0};
	EQUIPMENT_ITEM_PTR equipment_ptr = NULL;
	THE_REQUIRE_DELAY_PACKAGE_INFO pack;

#ifdef __MATRIX_DEBUG__
	char dbuf[MAX_STRING_SIZE] = {0};
#endif //__MATRIX_DEBUG__

	SecureZeroMemory(recv_buf, sizeof(recv_buf));
	recv_size = recv(__the_end_package_time_delay_socket.socket_, recv_buf, sizeof(recv_buf), 0);
	if(recv_size == SOCKET_ERROR){	

		output_log(IDS_STRING135, recv_size);
		return;
	}
	else if(recv_size < MAX_INPUT_PACKAGE_SIZE){
		SecureZeroMemory(error_buf, sizeof(error_buf));
		recv_size = bin_to_ansi((unsigned char*)recv_buf, recv_size, error_buf, sizeof(error_buf));
		output_log(IDS_STRING136, recv_size, MAX_INPUT_PACKAGE_SIZE);
		return;
	}

	//���β��
	SecureZeroMemory(&pack, sizeof(pack));
	if(!check_require_delay_rec_package((unsigned char*)recv_buf, recv_size, &pack)){

		SecureZeroMemory(error_buf, sizeof(error_buf));
		recv_size = bin_to_ansi((unsigned char*)recv_buf, recv_size, error_buf, sizeof(error_buf));
		output_log(IDS_STRING137, error_buf, recv_size);
		return;
	}

	//������иð����豸�Ƿ����, ʹ��IP��ѯ
	equipment_ptr = find_ip(pack.ip_);
	if(equipment_ptr == NULL){

		SecureZeroMemory(error_buf, sizeof(error_buf));
		recv_size = bin_to_ansi((unsigned char*)recv_buf, recv_size, error_buf, sizeof(error_buf));
		output_log(IDS_STRING138, pack.ip_, error_buf);
		return;
	}

	equipment_ptr->the_end_package_recv_time_ = pack.rec_time_;
	equipment_ptr->the_end_package_send_time_ = pack.send_time_;
	equipment_ptr->is_valid_the_end_package_time_delay_resp_ = true;

#ifdef __MATRIX_DEBUG__
	sprintf_s(dbuf, sizeof(dbuf), __MATRIX_TEXT("IP %08X; recv_time %X; snd_time %X"), pack.ip_, pack.rec_time_, pack.send_time_);
	output_log(IDS_STRING173, __FILE__, __FUNCTION__, __MATRIX_TEXT("����ʱ�Ӳ�ѯ��Ӧ���ݰ�"), dbuf);
#endif //__MATRIX_DEBUG__

}

EQUIPMENT_ITEM_PTR get_prev_equipment_ptr(EQUIPMENT_ITEM_PTR equipment_ptr, int route)
{
	EQUIPMENT_ITEM_PTR tmp_equipment_ptr = NULL;
	switch(equipment_ptr->type_){
		case FDU:
		case LAUL:
			tmp_equipment_ptr = get_prev_fdu_equipment_ptr(equipment_ptr, route);
			if(tmp_equipment_ptr == NULL){

				if(route == ROUTE_LEFT)			tmp_equipment_ptr = equipment_ptr->right_;
				else if(route == ROUTE_RIGHT)	tmp_equipment_ptr = equipment_ptr->left_;
			}
			break;
		case LAUX:
			tmp_equipment_ptr = get_prev_laux_equipment_ptr(equipment_ptr, route);
			break;
		default:
			break;
	}

	return tmp_equipment_ptr;
}

//ֻ�ܴ���ǰ�����β�����ڵĴ��߻򽻲���A,B�Ƿ��Ѿ����ʱ�Ӳ�ѯ
bool is_the_end_package_time_delay_ok(EQUIPMENT_ITEM_PTR equipment_ptr/*����β�����豸��Ϣ*/, int route)
{
	bool is_ok = true;
	EQUIPMENT_ITEM_PTR tmp_equipment_ptr = NULL;

	tmp_equipment_ptr = get_prev_equipment_ptr(equipment_ptr, route);
	while(tmp_equipment_ptr){

		if(!tmp_equipment_ptr->is_valid_the_end_package_time_delay_resp_){	is_ok = false; 	break;}
		tmp_equipment_ptr = get_prev_equipment_ptr(tmp_equipment_ptr, route);
	}

	return is_ok;
}

void refresh_equipments_status(EQUIPMENT_ITEM_PTR equipment_ptr/*����β�����豸��Ϣ*/, int route)
{
	EQUIPMENT_ITEM_PTR tmp_equipment_ptr = NULL;

	equipment_ptr->is_valid_the_end_package_time_delay_resp_ = false;
	tmp_equipment_ptr = get_prev_equipment_ptr(equipment_ptr, route);
	while(tmp_equipment_ptr){

		tmp_equipment_ptr->is_valid_the_end_package_time_delay_resp_ = false;
		tmp_equipment_ptr = get_prev_equipment_ptr(tmp_equipment_ptr, route);
	}
}

unsigned calculate_delay(EQUIPMENT_ITEM_PTR equipment_ptr,EQUIPMENT_ITEM_PTR next_equipment_ptr/*ָ���з������һ������*/)
{
	unsigned i = 0;
	unsigned del = 0;
	i = equipment_ptr->the_end_package_recv_time_ - next_equipment_ptr->the_end_package_send_time_;
	i = i&0x0ff;
	del = i/2 + 10;
	return del;   
}

//�ڿ�ʼβ����ѯ��,�ú�������Ƿ��Ѿ��յ�ȫ�����豸��Ӧ��Ϣ,����Ѿ��յ�ȫ��ʱ�Ӻ�,���м��㷢��ʱ����������
bool proc_the_end_package_time_delay_resp(EQUIPMENT_ITEM_PTR equipment_ptr/*����β�����豸��Ϣ*/, int route)
{
	EQUIPMENT_ITEM_PTR laux_ptr = NULL;
	EQUIPMENT_ITEM_PTR next_laux_ptr = NULL;
	EQUIPMENT_ITEM_PTR fdu_ptr = NULL, next_fdu_ptr = NULL;
	stdext_hash_map_iterator itr;
	int route_direction = route & ROUTE_DIRECTION_VALUE_MASK;

	if(is_the_end_package_time_delay_ok(equipment_ptr, route_direction)){
		
		//����ʱ�Ӳ��ҷ�������ʱ������
		if(equipment_ptr->type_ == SN_MAIN_LAUX){
			equipment_ptr->the_end_package_delay_time_low_ = 0x0;
			equipment_ptr->the_end_package_delay_time_high_ = 0x0;
			return true;
		}
		if(equipment_ptr->type_ == LAUX){

			laux_ptr = get_master_laux_ptr(); //�÷���ֻ�ʺ�һ��������
			while(laux_ptr){ //����������վ������,ʱ����������,����Ҫ�����ۼ�

				next_laux_ptr = get_next_laux_equipment_ptr(laux_ptr, route_direction);
				if(next_laux_ptr){

					next_laux_ptr->the_end_package_delay_time_low_ = calculate_delay(laux_ptr, next_laux_ptr);
					next_laux_ptr->the_end_package_delay_time_low_ += laux_ptr->the_end_package_delay_time_low_;

					//send cmd
					if(!insert_into_time_delay_setting_resp_list(next_fdu_ptr))	return false;
				}
				laux_ptr = next_laux_ptr;
			}
#ifdef __MATRIX_DEBUG__
			output_log(IDS_STRING173, __FILE__, __FUNCTION__, __MATRIX_TEXT("�յ�ȫ�����������豸ʱ�Ӳ�ѯ��Ӧ��Ϣ, ����������ݰ���ʱ�Ӷ�����"), __MATRIX_TEXT("NULL"));
#endif //__MATRIX_DEBUG__
		}
		else if(equipment_ptr->type_ == FDU || equipment_ptr->type_ == LAUL){
			
			itr = __route_hash_map.find(route);
			fdu_ptr = itr->second;
			next_fdu_ptr = get_next_fdu_equipment_ptr(fdu_ptr, route_direction);
			while(next_fdu_ptr){

				next_fdu_ptr->the_end_package_delay_time_low_ = calculate_delay(fdu_ptr, next_fdu_ptr);
				next_fdu_ptr->the_end_package_delay_time_low_ += fdu_ptr->the_end_package_delay_time_low_;

				//send cmd
				if(!insert_into_time_delay_setting_resp_list(next_fdu_ptr))	return false;

				fdu_ptr = next_fdu_ptr;
				next_fdu_ptr = get_next_fdu_equipment_ptr(fdu_ptr, route_direction);
			}

#ifdef __MATRIX_DEBUG__
			output_log(IDS_STRING173, __FILE__, __FUNCTION__, __MATRIX_TEXT("�յ�������ȫ���豸ʱ�Ӳ�ѯ��Ӧ��Ϣ, ����������ݰ���ʱ�Ӷ�����"), __MATRIX_TEXT("NULL"));
#endif //__MATRIX_DEBUG__
		}

		//��ʼ����ʱ������, �򿪶�ʱ�����ڴ���
#ifdef __MATRIX_DEBUG__
		output_log(IDS_STRING173, __FILE__, __FUNCTION__, __MATRIX_TEXT("��ʼʱ������,��ʱ��������Ӧ����ʱ��"), __MATRIX_TEXT("NULL"));
#endif //__MATRIX_DEBUG__
		start_the_end_package_time_delay_setting();
		SetTimer(__application_environment.main_window_, TIME_DELAY_SETTING_RESP_EVENT_ID,
			TIME_DELAY_SETTING_RESP_TIMEOUT_VALUE, proc_time_delay_setting_resp);
	}
	else{//�ȴ��´�����
		

#ifdef __MATRIX_DEBUG__
		output_log(IDS_STRING173, __FILE__, __FUNCTION__, __MATRIX_TEXT("û���յ�ȫ���豸ʱ�Ӳ�ѯ��Ӧ��Ϣ,�ù��̽����¿�ʼ"), __MATRIX_TEXT("NULL"));
#endif //__MATRIX_DEBUG__
		refresh_equipments_status(equipment_ptr, route_direction);
		stop_the_end_package();
	}

	return true;
}
