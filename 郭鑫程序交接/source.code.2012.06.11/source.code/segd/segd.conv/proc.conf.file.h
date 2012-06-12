/**
@brief	���������д��������ļ�
@details	���--file��������ָ����ļ�,�����������µ�SEGD�ļ�,��ǰΪ.h�ļ�,����μ�ʵ���ļ�(cpp)
@file	proc.conf.file.h
@note	
@see	���������ļ��ο�args.conf
@version	1.1.30.80.2011.10.26	
@author	kuoxin	
@bug
	1.1.5.12.2011.09.07		��ʼ���汾	
	1.1.30.80.2011.10.26	�޸Ķ���MAX_CONFIG_FILE_LINE_SIZE������0x200��Ϊ0x104,
							���޸Ľṹ��__tagSEGD_OPTION_ITEM�� __tagCONFIG_FILE_LINE_INFO�е�key_name��С
							ΪMAX_STRING_SIZE/4
*/

#include "../segd.viewer/segd.file.format.h"

/**
@enum __enuPROC_CONF_FILE_VALUE
@brief ���屾ģ��ʹ�õĳ���
*/
enum __enuPROC_CONF_FILE_VALUE
{
	MAX_CONFIG_FILE_LINE_SIZE = 0x104,
};

/**
@typedef int (*ASSIGN_VALUE_FUNCTION)(void* value_ptr, const char* value_string)
@brief	����ASSIGN_VALUE_FUNCTION����ת��������Ϣ��SEGD_FILE�ṹ���в���������SEGD�ļ�
@param[in]	value_ptr	SEGD_FILE�ṹ����,����ָ��
@param[in]	value_string	�����ļ��е��ַ���ֵ
@return	���سɹ�APP_SUCCESS, ʧ�ܷ���APP_FAULT
*/
typedef int (*ASSIGN_VALUE_FUNCTION)(void* value_ptr, const char* value_string);

/**
@struct	__tagCONFIG_FILE_LINE_INFO
@details	���������ļ�����
@note	��ǰʹ��char
*/
typedef struct __tagSEGD_OPTION_ITEM
{
	char	key_name_[MAX_STRING_SIZE/4];//!< �����ؼ���
	void*	value_ptr_; //!< ����ָ��
	ASSIGN_VALUE_FUNCTION	function_ptr_;//!< ������ֵ����
}SEGD_OPTION_ITEM, SEGD_OPTION_ITEM_PTR;

/**
@struct	__tagCONFIG_FILE_LINE_INFO
@details	���������ļ�����
@note	��ǰʹ��char
*/
typedef struct __tagCONFIG_FILE_LINE_INFO
{
	char	key_name_[MAX_STRING_SIZE/4];//!< �����ؼ���
	char	value_[MAX_STRING_SIZE];//!< ��Ӧ��������Ĳ���
	char	line_[MAX_STRING_SIZE]; //!< ��ǰ����Ϣ
}CONFIG_FILE_LINE_INFO, *CONFIG_FILE_LINE_INFO_PTR;

/**
@struct	__tagSEGD_CONFIG_FILE
@details	SEGD�����ļ����ݽṹ
@note	��ǰʹ��char_t
*/
typedef struct __tagSEGD_CONFIG_FILE
{
	char_t					config_path_[MAX_STRING_SIZE];//!< �����ļ�·��
	char_t					sps_path_[MAX_STRING_SIZE];//!< SPS�ļ�·��
	char_t					dat_path_[MAX_STRING_SIZE];//!< AD�����ļ�·��(���ļ�Ϊͨ���ļ�����)
	char_t					output_path_[MAX_STRING_SIZE];//!< ���SEG-D�ļ�·��
	char_t					remote_ip_[MAX_STRING_SIZE];	//!< ����ip��ַ
	unsigned short			remote_port_; //!< �˿�

	SEGD_GENERAL_HEADER_1	header_1_;//!< SEG-Dͷ1
	SEGD_GENERAL_HEADER_2	header_2_;//!< SEG-Dͷ2
	SEGD_GENERAL_HEADER_3	header_3_;//!< SEG-Dͷ3
	SEGD_SCAN_TYPE_HEADER	scan_type_header_; //!< SEG-D ɨ��ͷ
	SEGD_EXTENDED_HEADER	extended_header_; //!< SEG-D��չͷ

	SEGD_FILE_TRACE_HEADER	trace_header_;//!< SEG-D��ͷ
	SEGD_FILE_TRACE_HEADER	aux_trace_header_;//!< SEG-D���ӵ�ͷ
}SEGD_CONFIG_FILE, *SEGD_CONFIG_FILE_PTR;


/**
@fn	int load_config_file(char_t const* config_path, APPLICATION_ENVIRONMENT_PTR app_env_ptr)
@details	��鲢���������ļ���Ϣ��Ӧ�û�����
@param[in]		config_path	�����ļ�
@return	����ɹ�����APP_SUCCESS, ���򷵻�APP_FAULT
@note
*/
int load_config_file(char_t const* config_path);

/**
@fn	const SEGD_CONFIG_FILE_PTR get_config_info_ptr()
@details	���ص�ǰSEG-D�����ļ���Ϣ
@return	���������ļ��ṹ��ָ��,��ָ�벻�ܱ��޸�
@note
*/
const SEGD_CONFIG_FILE_PTR get_segd_config_info_ptr();

/**
@fn	int check_config_file(char_t const* config_path)
@details	��鲢�����ļ���Ϣ
@param[in]		config_path	�����ļ�
@return	����ɹ�����APP_SUCCESS, ���򷵻�APP_FAULT
@note
*/
int check_config_file(char_t const* config_path);

/**
@fn	int check_segd_option(char_t const* option, char const* option_value, unsigned option_value_size)
@details	���ָ�������������Ƿ���ȷ
@param[in]	option	����ָ��
@return	����ɹ�����APP_SUCCESS, ���򷵻�APP_FAULT
@note
*/
int check_segd_option(char_t const* option/*, char const* option_value, unsigned option_value_size*/);

/**
@fn	int modify_segd_option(char_t const* option, char const* option_value, unsigned option_value_size)
@details	�޸�ָ������������
@param[in]	option	����ָ��
@param[in]	option_value	����ָ����ֵ,���еĴ������,������ת�����ַ���,�����ַ�����˵Ҫ����˫���ŵ�
@return	����ɹ�����APP_SUCCESS, ���򷵻�APP_FAULT
@note
	����: 	sample_error_explaination "this is a demo"	#605-764 	XXXX 	asc	�ɼ�����˵��	ASCII �ı���160 ���ַ�
*/
int modify_segd_option(char_t const* option, char const* option_value/*, unsigned option_value_size*/);

/**
@fn	int save_config_file(char_t const* config_path)
@details	����Ӧ�û��������ݵ������ļ�
@param[in]		config_path	�����ļ�
@return	����ɹ�����APP_SUCCESS, ���򷵻�APP_FAULT
@note
*/
int save_config_file(char_t const* config_path);



