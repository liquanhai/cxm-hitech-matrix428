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

typedef int (*INIT_MODULE)(wchar_t*);
typedef int (*SET_MODULE_OPTION)(wchar_t*, wchar_t const*);
typedef void (*RELEASE_MODULE)(void);
typedef const wchar_t* (*GET_ERROR_INFO)(int*);

extern "C"{

/**
@fn	int init_module(wchar_t* config_filename)
@details	��ʼ����ǰ����ģ��,���������ļ���Ϣ
@param[in]	config_filename ����segd����·����Ϣ,Ҫ��ʹ��ȫ·��
@return	�����ʼ����ȷ,������0,���򽫷��س������, ���Ե���scGetErrorInfo����ó�������
@note
*/
int init_module(WCHAR* config_filename);

/**
@fn	int set_module_option(wchar_t* option_name, wchar_t const* option_value)
@details �޸�ָ��option_name����,ʹ��option_value
@param[in]	option_name		ָ�������������
@param[in]	option_value	�޸�ֵ,��ֵ���ͽ�����ʹ�ò���,�ò���ʹ���ַ���,���۵Ĺؼ�������������
@return	�����ʼ����ȷ,������0,���򽫷��س������, ���Ե���get_error_info����ó�������
@note	������ַ���,��ôҪʹ��wchar_t
*/
int set_module_option(wchar_t* option_name, wchar_t const* option_value);

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
const wchar_t* get_error_info(int* error_code);
/**
@fn void __debug_hook()
@details ����һ�����Ժ���,Ŀǰ��δʹ��
@param
@return
@note
*/
int __debug_hook();
}
