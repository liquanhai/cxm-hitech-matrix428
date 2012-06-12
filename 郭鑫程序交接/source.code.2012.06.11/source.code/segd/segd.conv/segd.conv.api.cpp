/**
@brief	���ļ���Ҫʵ�ֵ��������ļ����ù���
@details ���������º���:
			init_module
			release_module
			set_module_option
			get_error_info
			__debug_hook
		����ο�ÿ������˵��
@file	segd.conv.api.cpp
@note	
@see	
@version	1.1.2.8.2011.09.05
@author	kuoxin	
@bug
*/
#include <shlwapi.h>
#include "segd.conv.h"
#include "segd.conv.api.h"
#include "proc.conf.file.h"

char_t __config_file_path[MAX_STRING_SIZE];
int __last_error_code = 0x0;
char_t __last_error_info[MAX_STRING_SIZE];


/**
@fn	int init_module(wchar_t* config_filename)
@details	��ʼ����ǰ����ģ��,���������ļ���Ϣ
@param[in]	config_filename ����segd����·����Ϣ,Ҫ��ʹ��ȫ·��
@return	�����ʼ����ȷ,������0,���򽫷��س������, ���Ե���scGetErrorInfo����ó�������
@note
*/
int init_module(WCHAR* config_filename)
{
	int error_code = 0x0;

	SecureZeroMemory(__config_file_path, sizeof(__config_file_path));
#if defined(UNICODE) || defined(_UNICODE)
	StrCpy(__config_file_path, config_filename);
#else
	size_t size = 0x0;
	wcstombs_s(&size, __config_file_path, sizeof(__config_file_path)-1, config_filename, sizeof(__config_file_path)-1);
	__config_file_path[size] = 0x0;
#endif //defined(UNICODE) || defined(_UNICODE)
	error_code = check_config_file(__config_file_path);
	if(error_code == APP_FAULT){__last_error_code = get_last_error();}

	return error_code;
}

/**
@fn	int set_module_option(wchar_t* option_name, wchar_t const* option_value)
@details �޸�ָ��option_name����,ʹ��option_value
@param[in]	option_name		ָ�������������
@param[in]	option_value	�޸�ֵ,��ֵ���ͽ�����ʹ�ò���,�ò���ʹ���ַ���,���۵Ĺؼ�������������
@return	�����ʼ����ȷ,������0,���򽫷��س������, ���Ե���get_error_info����ó�������
@note	������ַ���,��ôҪʹ��wchar_t
*/
int set_module_option(wchar_t* option_name, wchar_t const* option_value)
{
	char tmp_option_value[MAX_STRING_SIZE * 2] = {0};
	int error_code =0x0;
	size_t size = 0x0;

	error_code = load_config_file(__config_file_path);
	if(error_code == APP_FAULT){	__last_error_code = get_last_error();	goto GOTO;}

	error_code = check_segd_option(option_name);
	if(error_code == APP_FAULT){	__last_error_code = get_last_error();	goto GOTO;}

	size = wcstombs_s(&size, tmp_option_value, sizeof(tmp_option_value), option_value, sizeof(tmp_option_value));
	tmp_option_value[size] = 0x0;
	error_code = modify_segd_option(option_name, tmp_option_value);
	if(error_code == APP_FAULT){	__last_error_code = get_last_error();	goto GOTO;}

	error_code = save_config_file(__config_file_path);
	if(error_code == APP_FAULT){	__last_error_code = get_last_error();}

GOTO:
	return error_code;
}

/**
@fn	void release_module();
@details	�ͷŵ�ǰģ��
@return void
@note
*/
void release_module()
{
	SecureZeroMemory(__config_file_path, sizeof(__config_file_path));
	__last_error_code = 0x0;
}

/**
@fn	const wchar_t* get_error_info(int* error_code)
@details ���س�����Ϣ����
@param[in/out]	error_code		������Ϣ����
@return	�õ����ص��ַ���,���û�з��򽫷���NULL
@note	
*/
const wchar_t* get_error_info(int* error_code)
{
	*error_code = __last_error_code;
	SecureZeroMemory(__last_error_info, sizeof(__last_error_info));
	get_string(__last_error_code, __last_error_info, sizeof(__last_error_info) / sizeof(__last_error_info));
	return __last_error_info;
}

/**
@fn void __debug_hook()
@details ����һ�����Ժ���,Ŀǰ��δʹ��
@param
@return
@note
*/
int __debug_hook()
{
	int error_code = 0;

	return error_code;
}


