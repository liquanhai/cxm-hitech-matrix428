/**
@brief	sps�ļ�,Ĭ�������ļ���Ϣд��segd��
@details	���ļ���Ҫ������sps�ļ�,Ĭ�������ļ��г�ȡѡ�ͺϲ���д�뵽segd����ͷ��,���ļ�Ϊ.h,����ʵ�ּ�cpp
@file	merge.config.info.cpp
@note	���ļ���ʹ��wchar_t��char��ϵ��ַ�����ʽ
@see	proc.conf.file.h, proc.sps.file.h, proc.data.file.h
@version	1.1.13.45.2011.09.29
@author	kuoxin	
@bug
		1.1.13.45.2011.09.29	��ʼ���汾
*/

#ifndef __MERGE_CONFIG_INFO_CPP__
#define __MERGE_CONFIG_INFO_CPP__

/**
@fn int merge_segd_header_1(__in__ const SPS_DATA_INFO_PTR sps_data_ptr, __in_out__ SEGD_GENERAL_HEADER_1_PTR header_ptr);
@brief �ϲ�sps��Ϣ
@param[in]	sps_data_ptr	sps����
@param[in/out]	header_ptr	�ϲ����ͨ��ͷ��1����
@return ����ɹ�����APP_SUCCESS, ���򷵻�APP_FAULT
@note
*/
int merge_segd_header_1(__in__ const SPS_DATA_INFO_PTR sps_data_ptr, 
						__in_out__ SEGD_GENERAL_HEADER_1_PTR header_ptr);

/**
@fn int merge_segd_header_2(__in__ const SPS_DATA_INFO_PTR sps_data_ptr, __in_out__ SEGD_GENERAL_HEADER_2_PTR header_ptr);
@brief �ϲ�sps��Ϣ
@param[in]	sps_data_ptr	sps����
@param[in/out]	header_ptr	�ϲ����ͨ��ͷ��2����
@return ����ɹ�����APP_SUCCESS, ���򷵻�APP_FAULT
@note
*/
int merge_segd_header_2(__in__ const SPS_DATA_INFO_PTR sps_data_ptr, 
						__in_out__ SEGD_GENERAL_HEADER_2_PTR header_ptr);

/**
@fn int merge_segd_header_3(__in__ const SPS_DATA_INFO_PTR sps_data_ptr, __in_out__ SEGD_GENERAL_HEADER_3_PTR header_ptr);
@brief �ϲ�sps��Ϣ
@param[in]	sps_data_ptr	sps����
@param[in/out]	header_ptr	�ϲ����ͨ��ͷ��3����
@return ����ɹ�����APP_SUCCESS, ���򷵻�APP_FAULT
@note
*/
int merge_segd_header_3(__in__ const SPS_DATA_INFO_PTR sps_data_ptr, 
						__in_out__ SEGD_GENERAL_HEADER_3_PTR header_ptr);

/**
@fn int merge_segd_scan_type_header(__in__ const SPS_DATA_INFO_PTR sps_data_ptr, __in_out__ SEGD_SCAN_TYPE_HEADER_PTR header_ptr);
@brief �ϲ�sps��Ϣ
@param[in]	sps_data_ptr	sps����
@param[in/out]	header_ptr	�ϲ����ɨ������ͷ������
@return ����ɹ�����APP_SUCCESS, ���򷵻�APP_FAULT
@note
*/
int merge_segd_scan_type_header(__in__ const SPS_DATA_INFO_PTR sps_data_ptr, __in_out__ SEGD_SCAN_TYPE_HEADER_PTR header_ptr);

/**
@fn int merge_segd_extend_header(__in__ const SPS_DATA_INFO_PTR sps_data_ptr, __in_out__ SEGD_EXTENDED_HEADER_PTR header_ptr);
@brief �ϲ�sps��Ϣ
@param[in]	sps_data_ptr	sps����
@param[in/out]	header_ptr	�ϲ������չ����ͷ������
@return ����ɹ�����APP_SUCCESS, ���򷵻�APP_FAULT
@note
*/
int merge_segd_extend_header(__in__ const SPS_DATA_INFO_PTR sps_data_ptr, __in_out__ SEGD_EXTENDED_HEADER_PTR header_ptr);

#endif //__MERGE_CONFIG_INFO_CPP__