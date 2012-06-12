/**
@brief	SPS�ļ����뵼���ӿ�
@details ��ͷ�ļ����ṩ��SPS�ļ������ӿں���˵��
@file	sps.io.h
@note	
@see	�й�SPS����,�μ�SPS��׼(Transcriber 2 SPS Format; e428XL V4.0 VOL.2, 
		�������ݽṹ�ο�sps.header.h
@version	1.0.0.1.2011.11.16
@author	kuoxin	
@bug
*/

#ifndef __SPS_IO_H__
#define __SPS_IO_H__

#include "sps.header.h"

enum 
{
	SPS_SUCCESS = 0,
	SPS_FAULT = -1,
};

typedef struct __tagSHOT_POINT_DATA
{
	SPS_POINT_RECORD_SPEC data_;	//!< ���¼��Ϣ
	SPS_POINT_RECORD_SPEC_PTR next_;//!< ���¼��Ϣָ������
}SHOT_POINT_DATA, *SHOT_POINT_DATA_PTR, RECEIVER_POINT_DATA, *RECEIVER_POINT_DATA_PTR;

typedef struct __tagRELATION_RECORD_SPEC
{
	SPS_RELATION_RECORD_SPEC data_;	//!< ���¼��Ϣ
	int	receiver_point_size_;//!< �������ݴ�С
	RECEIVER_POINT_DATA_PTR	head_receiver_point_ptr_;//!< ���ܵ�������Ϣ,��ֵΪָ��,�ڴ�ķ�����Ҫ���ɷ��������,ʹ�ú�,��Ҫɾ��
	RECEIVER_POINT_DATA_PTR	tail_receiver_point_ptr_;//!< ���ܵ�������Ϣ,��ֵΪָ��,�ڴ�ķ�����Ҫ���ɷ��������,ʹ�ú�,��Ҫɾ��
	RELATION_RECORD_SPEC_PTR next_; //!< ��һ���ṹ��ָ��,����ʹ������
}RELATION_RECORD_SPEC, *RELATION_RECORD_SPEC_PTR;

/**
@struct __tagSPS_DATA
@brief ����s,x,r�ļ���Ϣ���ݽṹ
@see sps.header.h
*/
typedef struct __tagSPS_DATA
{
	SHOT_POINT_DATA	shot_pointers_;			//!< �ڵ���������
	RECEIVER_POINT_DATA	receiver_pointers_;	//!< ���ܵ���������
	RELATION_RECORD_SPEC relation_records_;	//!< ��ϵ��������
}SPS_DATA, *SPS_DATA_PTR;

/**
@typedef int (*INIT_SPS_IO_PROC)();
@brief ����SPS import/export ��ʼ������
@see int init_sps_io()
*/
typedef int (*INIT_SPS_IO_PROC)();

/**
@typedef int (*RELEASE_SPS_IO_PROC)();
@brief ����SPS import/export �ͷź���
@see int release_sps_io()
*/
typedef int (*RELEASE_SPS_IO_PROC)();

/**
@typedef int (*SPS_GET_LAST_ERROR_PROC)(char*, int*)
@brief ����SPS import/export ����
@see int get_last_error(char*, int*)
*/
typedef int (*SPS_GET_LAST_ERROR_PROC)(char*, int*);

/**
@typedef int (SPS_IMPORT)(char const*, SPS_DATA_PTR)
@brief ����SPS import/export ���뺯��
@see int import_sps(char const* sps_path, SPS_DATA_PTR sps_data);
*/
typedef int (SPS_IMPORT)(char const*, SPS_DATA_PTR);

/**
@typedef int (SPS_EXPORT)(char const*, SPS_DATA_PTR)
@brief ����SPS import/export ���뺯��
@see int export_sps(char const* sps_path, SPS_DATA_PTR sps_data);
*/
typedef int (SPS_EXPORT)(char const*, SPS_DATA_PTR);

/**
 @fn int init_sps_io()
 @brief SPS import/extport ��ʼ������
 @return ����ɹ�����SPS_SUCCESS,���򷵻�SPS_FAULT, ͨ������get_last_error()���ش�����Ϣ
 @remark
*/
int init_sps_io();

/**
 @fn int import_sps(char const* sps_path, SPS_DATA_PTR sps_data)
 @brief ����sps�ļ�,�õ�SPS����
 @param[in] sps_path ����·��,���򿪺�׺s, x, r �ļ�
 @param[in/out] sps_data ������Ϣ
 @return ����ɹ�����SPS_SUCCESS,���򷵻�SPS_FAULT, ͨ������get_last_error()���ش�����Ϣ
 @remark
*/
int import_sps(char const* sps_path, SPS_DATA_PTR sps_data);

/**
 @fn int export_sps(char const* sps_path, const SPS_DATA_PTR sps_data)
 @brief ���SPS�ļ�
 @param[in] sps_path ����·��,���ļ���׺����s, x, r 
 @param[in] sps_data ������Ϣ
 @return ����ɹ�����SPS_SUCCESS,���򷵻�SPS_FAULT, ͨ������get_last_error()���ش�����Ϣ
 @remark
*/
int export_sps(char const* sps_path, const SPS_DATA_PTR sps_data);

/**
 @fn int release_sps_io()
 @brief �ͷ�ģ��
 @return ����ɹ�����SPS_SUCCESS,���򷵻�SPS_FAULT, ͨ������get_last_error()���ش�����Ϣ
 @remark
*/
int release_sps_io();

/**
 @fn int get_last_error(char* error_info, int* error_info_size)
 @brief �õ���ǰ����ģ�������Ϣ
 @param[in/out] error_info ������Ч������,���ص�ǰ���󻺳�
 @param[in/out] error_info_size ����error_info��С,���ػ���ʵ������С
 @return ���ص�ǰ�Ĵ�����,�������SPS_SUCCESS˵��û�д���
 @remark
*/
int get_last_error(char* error_info, int* error_info_size);

#endif /*__SPS_IO_H__*/

