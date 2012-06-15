#include <stdio.h>
#include <stdlib.h>
#include <tchar.h>
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include "../../common/config.h"
#include "../../common/typedef.h"
#include "../../common/log.h"
#include "..\..\common\sockimpl.h"
#include "resource.h"
#include <shlwapi.h>

#pragma comment(lib, "shlwapi")
#pragma comment(lib, "User32")

#define CONF_FILE_NAME	__TEXT("args.conf")

/**
@enum	__enuAPPLICATION_CONST_VALUE
@details	����ȫ�ֳ���
*/
enum __enuAPPLICATION_CONST_VALUE
{
	APP_CONSOLE_SCREEN_BUFFER_X = 150,	//!< console��Ļ�����СX�� 	
	APP_CONSOLE_SCREEN_BUFFER_Y = 9999,	//!< console��Ļ�����СY��
	APP_CONSOLE_WINDOWS_SIZE_Y = 40,	//!< console window��СY��
	MAX_COMMAND_SIZE = 0x19,	//!< �����в����������
};

struct __tagAPPLICATION_COMMAND_ARG;
/**
@fn	int (*APP_CMD_FUNC_PTR)(APPLICATION_COMMAND_ARG_PTR); 
@param[in]	�ƶ����в���
@brief	���嵱ǰ�����д�����������к���
*/
typedef int (*APP_CMD_FUNC_PTR)(__tagAPPLICATION_COMMAND_ARG*); 

/**
@struct	__tagAPPLICATION_COMMAND_ARG
@details	���������д������
@note	�����ݽṹֻ����Բ���1���Ĳ�����Ч
*/
typedef struct __tagAPPLICATION_COMMAND_ARG
{
	char_t	arg_name_[MAX_STRING_SIZE];//!< �����ؼ���
	APP_CMD_FUNC_PTR	function_ptr; //!<�ò��������к���
	char_t	value_[MAX_STRING_SIZE];//!< ��Ӧ��������Ĳ���
	int value_size_; //!< ��Ӧ���������������
	int priority_;//!< ���������ȼ�
}APPLICATION_COMMAND_ARG, *APPLICATION_COMMAND_ARG_PTR;

/**
@struct	__tagSEGD_WRITING_PROGRESS_INFO
@brief	���ͽ�����Ϣ���ݽṹ
*/
typedef struct __tagSEGD_WRITING_PROGRESS_INFO_PRIVATE
{
	SOCKET_IMPL sock_impl_; //!< ʹ�õ�socket����
	int step_position_; //!< ��ǰ����λ��
	int range_;	//!< ������󳤶�
	char_t descrip_[MAX_STRING_SIZE]; //!< ������Ϣ
}SEGD_WRITING_PROGRESS_INFO_PRIVATE, *SEGD_WRITING_PROGRESS_INFO_PRIVATE_PTR;

/**
@struct	__tagAPPLICATION_ENVIRONMENT
@details	����ȫ�ֽṹ����ȫ�ֱ���
*/
typedef struct __tagAPPLICATION_ENVIRONMENT
{
	segd::log*	log_; //!< ��־�����
	HANDLE	instance_; //!< ��ǰ����ʵ�����
	int		last_error_code_; //!< ���һ��������,����ͨ���ñ�Ų�ѯ���ض��ַ���
	bool	is_verbose_;//!< ��ʾ�����Ϣ
	char_t	config_file_path_[MAX_STRING_SIZE];//!<���ʹ�������ļ��Ļ�,��ǰ�ļ���·��
	int		args_[MAX_COMMAND_SIZE];//��������,��__app_cmd�����±�
	int		arg_size_;//!<��������
	const char_t* version_; //!< ��ǰ�汾��Ϣ
	unsigned int tb_time_;//!< ��ǰtb_time��Ϣ
	unsigned char manufacturer_code_;//!< ָ�������̴���,sercelΪ13, ��ע��ʱ,ͨ��ʹ��0
	char_t output_log_[MAX_STRING_SIZE]; //!< ����ļ�,���ļ�������ʹ�ò�ͬ��������,�궨����ļ�����
}APPLICATION_ENVIRONMENT, *APPLICATION_ENVIRONMENT_PTR;

/**
@fn	int main_private(int argc, char_t* argv[],  const char_t* app_version)
@details ʵ��wmain��������
@param[in]	argc	��������			
@param[in]	argv	���������б�		
@param[in]	app_version	��ǰ�汾��Ϣ
@return	�����ʼ����ȷ,������0,���򽫷��س������, ֱ�ӷ��ظ�wmain����,���ó������
		ͨ��CreateProcess�õ�������Ϣ
@note	������ַ���,��ôҪʹ��wchar_t
*/
int main_private(int argc, char_t* argv[], char_t const* app_version);

/**
@fn	void output_log(char_t const* info)
@details ʵ����־�������
@param[in]	info	��־�ַ���
@return	void
@note	Ҫʹ��char_t
*/
void output_log(char_t const* info);

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
int get_string(UINT id, char_t* buf, unsigned size);

/**
@fn	void send_progress_info(const SEGD_WRITING_PROGRESS_INFO_PTR info_ptr)
@details ����SEGD�ļ����ɽ���
@param[in]	info_ptr	���ݽṹ
@return	
@note	
*/
void send_progress_info(const SEGD_WRITING_PROGRESS_INFO_PRIVATE_PTR info_ptr);
