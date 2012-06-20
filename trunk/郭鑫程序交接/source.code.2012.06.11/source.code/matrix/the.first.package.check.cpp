/**
*	���������ļ�ʵ�ֶ�ʱ����ʱ�������߽����˻�����, ��ʱΪCHECK_THE_FIRST_PACKAGE_TIMEOUT_VALUE
*	�ļ���the.first.package.check.cpp
*	ע�ͣ�ͨ���������ڶ�ʱ���е���,��ʱ���´�����IP��ַ��Ч���豸,������ɾ��
*	�ο����ף�
*	�汾��1.0.5.37.2011.8.12
*	ע�ͣ�
*	�޸ģ�
*		1.0.7.39.2011.8.12	�޸�check_the_first_package�еĴ���
*		
*/

#include "..\common\config.h"
#include "..\common\typedef.h"
#include "common.functions.h"
#include "the.first.package.check.h"
#include "matrix.h"

extern LING_ARRAY_ITEM __line_array[MAX_BIG_LINE_SIZE]; //�������飬��־ÿ���������豸

/*
	֧���˻�����,������ֲɼ�վ�͵�Դվ���װ�������С��0ʱ,������豸ɾ��
*/
void check_the_first_package()
{
	int i = 0;
	EQUIPMENT_ITEM_PTR equipment_ptr = NULL;

#ifdef __MATRIX_DEBUG__
	char dbuf[MAX_STRING_SIZE * 4] = {0};
	output_log(IDS_STRING172, __FILE__, __LINE__, __MATRIX_TEXT("�˻�����,������ֲɼ�վ�͵�Դվ���װ�������С��0ʱ,������豸ɾ��"));
#endif //__MATRIX_DEBUG__

	for(i = 0; i < MAX_BIG_LINE_SIZE; ++i){
		
		equipment_ptr = __line_array[i].the_first_station_item_left_;
		while(equipment_ptr){

			if(!equipment_ptr->is_valid_ip_){

				--equipment_ptr->the_first_package_count_;
				if(equipment_ptr->the_first_package_count_ < 0){
#ifdef __MATRIX_DEBUG__
					sprintf_s(dbuf, sizeof(dbuf), "��ɾ���ڵ�%d����A�ϵ�SN:%X���豸", i, equipment_ptr->serial_no_);
					output_log(IDS_STRING172, __FILE__, __LINE__, dbuf);
#endif //__MATRIX_DEBUG__
					delete_serial_no(equipment_ptr->serial_no_);
					equipment_ptr =  delete_equipment(equipment_ptr);
					continue;
				}
			}

			equipment_ptr = get_next_fdu_equipment_ptr(equipment_ptr, ROUTE_LEFT);
		}

		equipment_ptr = __line_array[i].the_first_station_item_right_;
		while(equipment_ptr){

			if(!equipment_ptr->is_valid_ip_){

				--equipment_ptr->the_first_package_count_;
				if(equipment_ptr->the_first_package_count_ < 0){

#ifdef __MATRIX_DEBUG__
					sprintf_s(dbuf, sizeof(dbuf), "��ɾ���ڵ�%d����B�ϵ�SN:%X���豸", i, equipment_ptr->serial_no_);
					output_log(IDS_STRING172, __FILE__, __LINE__, dbuf);
#endif //__MATRIX_DEBUG__

					delete_serial_no(equipment_ptr->serial_no_);
					equipment_ptr =  delete_equipment(equipment_ptr);
					continue;
				}
			}

			equipment_ptr = get_next_fdu_equipment_ptr(equipment_ptr, ROUTE_RIGHT);
		}
	}
}

