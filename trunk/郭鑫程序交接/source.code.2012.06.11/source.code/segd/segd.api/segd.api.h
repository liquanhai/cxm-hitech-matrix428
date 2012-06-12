/**
@brief		�޸�segd�����ļ����ܵ�������
@details	��Щ��������,�����ڸý�����,��Ҫ������ʹ�ö�̬���ظ�ִ���ļ�,Ȼ�������Ӧ�ĺ�����ַ
@file	segd.conv.cpp
@note	��ͷ�ļ���ʹ��unicode����,�����߿���
@see
@code
@endcode
@version	1.1.1.5.2011.09.02
@author	kuoxin	
@bug
*/

#pragma once

#include "targetver.h"

#define __in__
#define __out__
#define __in_out__
#define __in_opt__
#define __out_opt__
#define __in_out_opt__

#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers
#include <windows.h>

/**
@struct SEGD_WRITING_PROGRESS_INFO
@detail	UDP���ܵ���SEG-Dд�����֪ͨ��Ϣ�ṹ��
*/
typedef struct __tagSEGD_WRITING_PROGRESS_INFO
{
	int step_position_; //!< ����,��ֵ����λ��
	int range_;			//!< ���Χ
	int descrip_size_; //!< descrip_������Ϣ�Ĵ�С
	wchar_t*	descrip_; //!< ������Ϣ,������ָ�����ڶ�ȡ�Ǹ��ļ���������Ϣ
}SEGD_WRITING_PROGRESS_INFO, *SEGD_WRITING_PROGRESS_INFO_PTR;

/**
@struct	__tagSEGD_API_INFO
@detail	���崫���ģ���ʼ������
*/
typedef struct __tagSEGD_API_INFO
{
	wchar_t* config_path_; //!< ,Ҫ��ʹ��ȫ·��
	unsigned short listen_port_; //!< ����socket �����˿�
}SEGD_API_INFO, *SEGD_API_INFO_PTR;

typedef int (*INIT_MODULE)(SEGD_API_INFO_PTR);
typedef int (*SET_MODULE_OPTION)(wchar_t*, wchar_t const*);
typedef void (*RELEASE_MODULE)(void);
typedef const wchar_t* (*GET_ERROR_INFO)(int*);
typedef int (*SHOW_WRITING_PROGRESS)(HWND, wchar_t const*);

extern "C"{

/**
@fn	int init_module(__in__ SEGD_API_INFO_PTR config_info_ptr)
@details	��ʼ����ǰ����ģ��,���������ļ���Ϣ
@param[in]	config_info ����segd������Ϣ
@return	�����ʼ����ȷ,������APP_SUCCESS,���򽫷���APP_FAULT, ���Ե���get_error_info����ó�������
@note
*/
int init_module(__in__ SEGD_API_INFO_PTR config_info_ptr);

/**
@fn	int set_module_option(wchar_t const* option_name, wchar_t const* option_value)
@details �޸�ָ��option_name����,ʹ��option_value
@param[in]	option_name		ָ�������������
@param[in]	option_value	�޸�ֵ,��ֵ���ͽ�����ʹ�ò���,�ò���ʹ���ַ���,���۵Ĺؼ�������������
@return	�����ʼ����ȷ,������0,���򽫷��س������, ���Ե���get_error_info����ó�������
@note	������ַ���,��ôҪʹ��wchar_t
*/
int set_module_option(__in__ wchar_t const* option_name, __in__ wchar_t const* option_value);

/**
@fn	void release_module();
@details	�ͷŵ�ǰģ��
@return void
@note
*/
void release_module();

/**
@fn	const wchar_t* get_error_info(int* error_code)
@details ���س�����Ϣ����
@param[in/out]	error_code		������Ϣ����
@return	�õ����ص��ַ���,���û�з��򽫷���NULL
@note	
*/
__out__ const wchar_t* get_error_info(__in_out__ int* error_code);
/**
@fn void __debug_hook()
@details ����һ�����Ժ���,Ŀǰ��δʹ��
@return
@note
*/
int __debug_hook();

/**
@fn __out__ int show_writing_progress(__in_opt__ HWND parent_window_handler, __in_opt__ wchar_t const* window_title)
@details ����һ���Ի���������ʾ��ǰSEGD�ļ���д��������
@param[in]	parent_window_handler	��ѡʹ��,ָ����ǰ�ĵ����Ի���ĸ�����
@param[in]	window_title			��ѡʹ��,ָ����ǰ�ĵ����Ի���ı���		
@return	�����������ɹ�����APP_SUCCESS,���򷵻�APP_FAULT,����ͨ��get_error_info�õ�������Ϣ
@note
*/
__out__ int show_writing_progress(__in_opt__ HWND parent_window_handler, __in_opt__ wchar_t const* window_title);
}

/**
@fn	void output_log(char_t const* info)
@details ʵ����־�������
@param[in]	info	��־�ַ���
@return	void
@note	Ҫʹ��char_t
*/
void output_log(wchar_t const* info);

/**
@fn	void output_log(unsigned int id, ...)
@details ʵ�ֶ������־�������
@param[in]	id	��Դ���ַ������б��
@param[in]	...	������Դ���ַ������ַ����Ĳ�����ȷ��
@return	void
@note	Ҫʹ��char_t, �ú�����������鴫������
*/
void output_log(unsigned int id, ...);

/**
@fn	int get_last_error()
@details �õ���ǰ���������
@return	int ���ش�����Ϣ
@note	
*/
int get_last_error();

/**
@fn	void set_last_error(int error_code)
@details	���õ�ǰ���Ĵ�������� 
@param[in]	error_code	��������� 
@return	void
@note	
*/
void set_last_error(int error_code);

/**
@fn	int get_string(UINT id, char_t* buf, unsigned size)
@details	������ԴID�õ����ַ���
@param[in]		id		��ԴID
@param[in/out]	buf		�õ����ַ���
@param[in]		size	buf��С
@return	����ֵ�ο�LoadString (Win32 API)
@note	
*/
int get_string(UINT id, wchar_t* buf, unsigned size);
