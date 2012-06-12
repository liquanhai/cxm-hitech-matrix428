/**
@brief	��ģ������ļ�����ӿ�
@details	��ͷ�ļ����ṩ�˲����ļ������ӿں���˵��,���а���config, export, line. log, operation, 
			plotter, positioning, vibrator
@file	params.io.h
@note	
@see	
@version	1.0.0.1.2011.11.16
@author	kuoxin	
@bug
*/

#ifndef __PARAMS_IO_H__
#define __PARAMS_IO_H__

#include "params.header.h"

/**
@enum __enuPARAMS_STATUS
@brief �ӿں�������״̬
*/
enum __enuPARAMS_IO_STATUS
{
	PARAMS_IO_SUCCESS = 0, //!< �ɹ�
	PARAMS_IO_FAULT = -1, //!< ʧ��
};

/**
@enum __enuPARAMS_IO_SET_TYPE
@brief ������������
*/
enum __enuPARAMS_IO_SET_TYPE
{
	LOG_PARAMS_IO_SET_TYPE = 1, //!< log��������
	CONFIG_PARAMS_IO_SET_TYPE, //!< config��������
	LINE_PARAMS_IO_SET_TYPE, //!< line��������
	EXPORT_PARAMS_IO_SET_TYPE, //!< export��������
	OPTERATION_PARAMS_IO_SET_TYPE, //!< operation��������
	PLOTTER_PARAMS_IO_SET_TYPE, //!< plotter��������
	POSITIONING_PARAMS_IO_SET_TYPE, //!< positioning��������
	VIBRATOR_PARAMS_IO_SET_TYPE, //!< vibrator��������
};

/**
@typedef int (*INIT_PARAMS_IO)()
@brief ����params import ��ʼ������
@see 
*/
typedef int (*INIT_PARAMS_IO)();

/**
@typedef int (*RELEASE_PARAMS_IO)()
@brief ����params import �ͷź���
@see int release_params_io()
*/
typedef int (*RELEASE_PARAMS_IO)();

/**
@typedef int (*PARAMS_GET_LAST_ERROR_PROC)(char*, int*)
@brief ����params import ����
@see int get_last_error(char*, int*)
*/
typedef int (*PARAMS_GET_LAST_ERROR_PROC)(char*, int*);

/**
@typedef int (*IMPORT_PARAMS_PROC)(char const*, enum __enuPARAMS_IO_SET_TYPE, void*) 
@brief ����params import ���뺯��
@see int import_params(char const* param_path, enum __enuPARAMS_IO_SET_TYPE type, void* params)
*/
typedef int (*IMPORT_PARAMS_PROC)(char const*, enum __enuPARAMS_IO_SET_TYPE, void*);

/**
@typedef typedef int (EXPORT_PARAMS_PROC)(char const*, enum __enuPARAMS_IO_SET_TYPE, void const*)
@brief ����params import ���뺯��
@see int export_params(char const* params_path, enum __enuPARAMS_IO_SET_TYPE type, void const* params)
*/
typedef int (*EXPORT_PARAMS_PROC)(char const*, enum __enuPARAMS_IO_SET_TYPE, void const*);

/**
 @fn int init_params_io();
 @brief SPS import/extport ��ʼ������
 @return ����ɹ�����PARAMS_IO_SUCCESS,���򷵻�PARAMS_IO_FAULT, ͨ������get_last_error()���ش�����Ϣ
 @remark
*/
int init_params_io();

/**
 @fn int import_params(char const* params_path, enum __enuPARAMS_IO_SET_TYPE type, void* params_list)
 @brief ����ָ�������Ͳ����ļ��Ĳ����б�
 @param[in] params_path ����·��
 @param[in] type ������������,�μ�enum __enuPARAMS_IO_SET_TYPE
 @param[in/out] params ���ݼ�����Ϣ
 @return ����ɹ�����PARAMS_IO_SUCCESS,���򷵻�PARAMS_IO_FAULT, ͨ������get_last_error()���ش�����Ϣ
 @remark
*/
int import_params(char const* params_path, enum __enuPARAMS_IO_SET_TYPE type, void* params);

/**
 @fn int export_params(char const* params_path, enum __enuPARAMS_IO_SET_TYPE type, void const* params_list)
 @brief ����ָ�������Ͳ����ļ��Ĳ����б�
 @param[in] params_path ����·��
 @param[in] type ������������,�μ�enum __enuPARAMS_IO_SET_TYPE
 @param[in] params ���ݼ�����Ϣ
 @return ����ɹ�����PARAMS_IO_SUCCESS,���򷵻�PARAMS_IO_FAULT, ͨ������get_last_error()���ش�����Ϣ
 @remark
*/
int export_params(char const* params_path, enum __enuPARAMS_IO_SET_TYPE type, void const* params);

/**
 @fn int release_params_io()
 @brief �ͷ�ģ��
 @return ����ɹ�����PARAMS_IO_SUCCESS,���򷵻�PARAMS_IO_FAULT, ͨ������get_last_error()���ش�����Ϣ
 @remark
*/
int release_params_io();

/**
 @fn int get_last_error(char* error_info, int* error_info_size)
 @brief �õ���ǰ����ģ�������Ϣ
 @param[in/out] error_info ������Ч������,���ص�ǰ���󻺳�
 @param[in/out] error_info_size ����error_info��С,���ػ���ʵ������С
 @return ���ص�ǰ�Ĵ�����,�������PARAMS_IO_SUCCESS˵��û�д���
 @remark
*/
int get_last_error(char* error_info, int* error_info_size);

#endif /*__PARAMS_IO_H__*/

