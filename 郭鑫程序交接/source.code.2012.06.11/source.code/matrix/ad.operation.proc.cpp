/*
*	����:	���ļ�ʵ�ֲɼ��豸��AD������������
*	�ļ�:	ad.operation.proc.cpp
*	ע��:	���������͵��ü�ad.operation.proc.h
*			�ò���ʵ�ַ������������AD���������е�ÿһ������,���ݵȴ�ʱ��������TIMER, 
*			���н����ÿһ���������ִ��,ֱ�����д��߶�ִ�����.
*	�汾:	1.0.2.30.2011.7.29.BASE
*	�����:	kuoxin
*	�ο�����:	
*	�޸�:	
*			1.0.8.42.2011.8.18	�޸�proc_ad_operation ��������,��ǰ�����������
*/

#include "../common/config.h"
#include "../common/typedef.h"
#include "../common/sockimpl.h"
#include "matrix.h"
#include "common.functions.h"
#include "equipment.comm.order.h"
#include "ad.operation.resp.h"

#define __MATRIX_DEBUG__

enum
{
	MAX_AD_OPERATION_EQUIPMENTS_SIZE = 0x100,
};

//����ýṹ��Ҫ�������A,B�Ͻ���վ��ĵ�һ���ɼ�վ
typedef struct __tagAD_OPERATION_EQUIPMENTS
{
	EQUIPMENT_ITEM_PTR	equipment_ptr_;
	int					route_;
}AD_OPERATION_EQUIPMENTS, *AD_OPERATION_EQUIPMENTS_PTR;

//extern global variable
extern stdext_hash_map __route_hash_map;
extern stdext_hash_map __ip_hash_map;
extern APPLICATION_ENVIRONMENT	__application_environment;
extern THE_HEART_BEAT_PACKAGE_INFO __heartbeat_data;
extern LING_ARRAY_ITEM __line_array[MAX_BIG_LINE_SIZE]; //�������飬��־ÿ���������豸

//local global variable
unsigned int __current_command_index;//ָ����ǰAD����������������е��±�
unsigned int __current_ad_operation_equipments_array_index; //��ǰ__ad_operation_equipments_array���±�����
unsigned int __current_ad_operation_equipments_array_size; //��ǰ__ad_operation_equipments_array��С
bool __be_ad_operation_proc_completed; //����AD�����Ƿ����
AD_OPERATION_EQUIPMENTS __ad_operation_equipments_array[MAX_AD_OPERATION_EQUIPMENTS_SIZE]; // ���AD���ô���A,B�ĵ�һ���ɼ�վ

bool init_ad_operation_proc()
{
	bool is_ok = true;
	int i = 0;
	int size = sizeof(__line_array) / sizeof(__line_array[0]);
	AD_OPERATION_EQUIPMENTS_PTR ptr = NULL;

	SecureZeroMemory(__ad_operation_equipments_array, sizeof(__ad_operation_equipments_array));
	__current_command_index = 0;
	__current_ad_operation_equipments_array_index = 0;
	__current_ad_operation_equipments_array_size = 0;
	__be_ad_operation_proc_completed = false;

	for(i = 0; i < size; ++i){
		
		ptr = __ad_operation_equipments_array + __current_ad_operation_equipments_array_size;
		ptr->equipment_ptr_ = __line_array[i].the_first_station_item_left_;
		if(ptr->equipment_ptr_){	ptr->route_ = ROUTE_LEFT;	++__current_ad_operation_equipments_array_size;}

		ptr = __ad_operation_equipments_array + __current_ad_operation_equipments_array_size;
		ptr->equipment_ptr_ = __line_array[i].the_first_station_item_right_;
		if(ptr->equipment_ptr_){	ptr->route_ = ROUTE_RIGHT;	++__current_ad_operation_equipments_array_size;}
	}

	size = sizeof(__ad_operation_equipments_array)/sizeof(__ad_operation_equipments_array[0]);
	if(__current_ad_operation_equipments_array_size > size)	{
		output_log(IDS_STRING178, size, __current_ad_operation_equipments_array_size);	
		return is_ok = false;
	}

	init_ad_operation_resp();

	return is_ok;
}

void release_ad_operation_proc(){	release_ad_operation_resp();}

bool proc_ad_operation(AD_COMMAND_ITEM_PTR ad_commands, unsigned int ad_commands_size)
{
	int route = 0x0;
	EQUIPMENT_ITEM_PTR equipment_ptr = NULL;
#ifdef __MATRIX_DEBUG__
	char dbuf[MAX_STRING_SIZE * 4] = {0};
#endif //__MATRIX_DEBUG__

	if(__current_ad_operation_equipments_array_index < __current_ad_operation_equipments_array_size){

		if(__current_command_index < ad_commands_size){

#ifdef __MATRIX_DEBUG__
			sprintf_s(dbuf, sizeof(dbuf), __MATRIX_TEXT("ln-idx %X; ln-sz %X; cmd-idx %X; cmd-sz %X"), 
					__current_ad_operation_equipments_array_index, __current_ad_operation_equipments_array_size,
					__current_command_index, ad_commands_size);
			output_log(IDS_STRING173, __FILE__, __FUNCTION__, __MATRIX_TEXT("AD�����е�ǰ��������С��AD��������"), dbuf);
#endif //__MATRIX_DEBUG__
			if(is_ad_operation_running()){

#ifdef __MATRIX_DEBUG__
				output_log(IDS_STRING173, __FILE__, __FUNCTION__, __MATRIX_TEXT("AD�������������������"), __MATRIX_TEXT("NULL"));
#endif //__MATRIX_DEBUG__
				if(be_ad_operation_completed()){

#ifdef __MATRIX_DEBUG__
					output_log(IDS_STRING173, __FILE__, __FUNCTION__, __MATRIX_TEXT("AD��������Ѿ����,���ر�Ӧ��TIMER"), __MATRIX_TEXT("NULL"));
#endif //__MATRIX_DEBUG__
					stop_ad_operation();
					if(++__current_command_index == ad_commands_size) goto GOTO;

					equipment_ptr = __ad_operation_equipments_array[__current_ad_operation_equipments_array_index].equipment_ptr_;
					route = __ad_operation_equipments_array[__current_ad_operation_equipments_array_index].route_ & ROUTE_DIRECTION_VALUE_MASK;
					while(equipment_ptr){

						if(equipment_ptr->is_valid_equipment_)
							insert_into_ad_operation_list(equipment_ptr, (ad_commands + __current_command_index)->function_ptr_, &__heartbeat_data);
						else
							output_log(IDS_STRING176, equipment_ptr->serial_no_, equipment_ptr->ip_);

						equipment_ptr = get_next_fdu_equipment_ptr(equipment_ptr, route);
					}

#ifdef __MATRIX_DEBUG__
					sprintf_s(dbuf, sizeof(dbuf), __MATRIX_TEXT("AD-CMD index %X; elapsed-time %X"), __current_command_index, 
						(ad_commands+__current_command_index)->elapsed_time_);
					output_log(IDS_STRING173, __FILE__, __FUNCTION__, __MATRIX_TEXT("��AD�������Ӧ��TIMER"), dbuf);
#endif //__MATRIX_DEBUG__
					start_ad_operation((ad_commands + __current_command_index)->elapsed_time_);
				}
#ifdef __MATRIX_DEBUG__
				else{
					output_log(IDS_STRING173, __FILE__, __FUNCTION__, __MATRIX_TEXT("��ǰAD����������ڽ�����"), __MATRIX_TEXT("NULL"));
				}
#endif //__MATRIX_DEBUG__
			}
			else{

				stop_ad_operation();
				equipment_ptr = __ad_operation_equipments_array[__current_ad_operation_equipments_array_index].equipment_ptr_;
				route = __ad_operation_equipments_array[__current_ad_operation_equipments_array_index].route_ & ROUTE_DIRECTION_VALUE_MASK;
				while(equipment_ptr){

					if(equipment_ptr->is_valid_equipment_)
						insert_into_ad_operation_list(equipment_ptr, (ad_commands+__current_command_index)->function_ptr_, &__heartbeat_data);
					else
						output_log(IDS_STRING176, equipment_ptr->serial_no_, equipment_ptr->ip_);

					equipment_ptr = get_next_fdu_equipment_ptr(equipment_ptr, route);
				}
#ifdef __MATRIX_DEBUG__
				output_log(IDS_STRING173, __FILE__, __FUNCTION__, __MATRIX_TEXT("���ô����е������豸�����뵽AD����Ӧ�������"), __MATRIX_TEXT("NULL"));
				sprintf_s(dbuf, sizeof(dbuf), __MATRIX_TEXT("AD-CMD index %X; elapsed-time %X"), __current_command_index, 
					(ad_commands+__current_command_index)->elapsed_time_);
				output_log(IDS_STRING173, __FILE__, __FUNCTION__, __MATRIX_TEXT("��AD�������Ӧ��TIMER"), dbuf);
#endif //__MATRIX_DEBUG__			
				start_ad_operation((ad_commands+__current_command_index)->elapsed_time_);
			}
		}
		else{
GOTO:
#ifdef __MATRIX_DEBUG__
			sprintf_s(dbuf, sizeof(dbuf), __MATRIX_TEXT("line-index %X"), __current_ad_operation_equipments_array_index);
			output_log(IDS_STRING173, __FILE__, __FUNCTION__, __MATRIX_TEXT("����AD��������ڴ������������"), __MATRIX_TEXT("NULL"));
#endif //__MATRIX_DEBUG__
			++__current_ad_operation_equipments_array_index;
			__current_command_index = 0;
		}
	}
	else{ 
		output_log(IDS_STRING173, __FILE__, __FUNCTION__, __MATRIX_TEXT("����AD������������д������������"), __MATRIX_TEXT("NULL"));
		__be_ad_operation_proc_completed = true;
	}

	return __be_ad_operation_proc_completed;
}

