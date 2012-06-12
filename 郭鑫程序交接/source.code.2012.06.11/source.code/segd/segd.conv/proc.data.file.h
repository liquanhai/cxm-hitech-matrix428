/**
@brief	���������д��������ļ�
@details	���--data-file��������ָ����ļ�,��ȡ�����ļ�ͷ��AD����,��ǰΪ.h�ļ�,����μ�ʵ���ļ�(cpp)
@file	proc.conf.file.h
@note	
@see	���������ļ��ο�args.conf
@version		1.1.13.45.2011.09.29
@author	kuoxin	
@bug
	1.1.12.40.2011.09.28	��ʼ���汾
	1.1.13.45.2011.09.29	������������ļ�ͷ���޸��޸������ļ�

*/
#ifndef __PROC_DATA_FILE_H__
#define	__PROC_DATA_FILE_H__

/*

@struct	__tagAD_DATA_FILE_HEAD_PRIVATE 
@brief	AD�����ļ�ͷ��Ϣ
@note	typedef struct ___tagAD_DATA_FILE_HEAD_PRIVATE  AD_DATA_FILE_HEAD_PRIVATE , *AD_DATA_FILE_HEAD_PRIVATE_PTR;

typedef struct __tagAD_DATA_FILE_HEAD
{
	char	config_path_[MAX_STRING_SIZE_LOCAL];//!< �����ļ�·��
	char	sps_path_[MAX_STRING_SIZE_LOCAL];//!< SPS�ļ�·��
	char	dat_path_[MAX_STRING_SIZE_LOCAL];//!< AD�����ļ�·��(���ļ�Ϊͨ���ļ�����)
	char	output_path_[MAX_STRING_SIZE_LOCAL];//!< ���SEG-D�ļ�·��
	char	remote_ip_[MAX_STRING_SIZE_LOCAL];	//!< ����ip��ַ
	unsigned	remote_port_; //!< �˿�

	int	shot_number_;			//!< �ں� 1 �� 9999
	int	FileNumber_;			//!< �ļ����  1 �� 9999

	float source_line_number_;	//!< ���ߺ�
	float source_point_number_;	//!< ��Դ���

	int scan_type_number_; //!< �����߻���������
	int source_type_;			//!< 29-32 XXXX bin ��Դ����0 = ����Դ 1 = ���� 2 = �ɿ���Դ

	int sample_frequency_;		//!< ������250��500��1000��2000��4000 ΢��
	int sample_length_;			//!< �ɼ�����1000��128000 ����
	int sample_number_in_trace_;	//!< 33-36 XXXX bin ��¼����������Ŀ1 �� 128000
	float tb_window_; //!< TB����ֵ
	time_t datetime_; //!< ��ʼʱ��
	int tb_time_;	  //�ڲ�TBʱ��=����ʱ�䣬�Ӹ�ʱ�����¼����
}AD_DATA_FILE_HEAD, *AD_DATA_FILE_HEAD_PTR;

@struct	__tagAD_DATA_FILE_HEAD_PRIVATE 
@brief	AD�����ļ�ͷ��Ϣ
@note	typedef struct ___tagAD_DATA_FILE_HEAD_PRIVATE  AD_DATA_FILE_HEAD_PRIVATE , *AD_DATA_FILE_HEAD_PRIVATE_PTR;

typedef struct __tagAD_DATA_SCAN_TYPE_INFO
{
	int trace_number_;	//!< ������
	int line_type_;//!< ������: 1		����������: 9

	float resistor_lower_limit_; //!< ��������
	float resistor_higher_limit_;//!< ��������
	float resistor_value_; //!< ����ֵ
	float tilt_limit_; //!< ��б�Ƚ���
	float tilt_value_; //!< ��б��ֵ
	bool resistor_deviation_; //!< �������
	bool tilt_deviation_; //!< ��б�����	
}AD_DATA_SCAN_TYPE_INFO, *AD_DATA_SCAN_TYPE_INFO_PTR;

*/

#define MAX_STRING_SIZE_LOCAL 128

/**
@struct	__tagAD_DATA_FILE_HEAD_PRIVATE 
@brief	AD�����ļ�ͷ��Ϣ
@note	typedef struct ___tagAD_DATA_FILE_HEAD_PRIVATE  AD_DATA_FILE_HEAD_PRIVATE , *AD_DATA_FILE_HEAD_PRIVATE_PTR;
*/
typedef struct __tagAD_DATA_FILE_HEAD_PRIVATE 
{
	char	config_path_[MAX_STRING_SIZE_LOCAL];//!< �����ļ�·��
	char	sps_path_[MAX_STRING_SIZE_LOCAL];//!< SPS�ļ�·��
	char	dat_path_[MAX_STRING_SIZE_LOCAL];//!< AD�����ļ�·��(���ļ�Ϊͨ���ļ�����)
	char	output_path_[MAX_STRING_SIZE_LOCAL];//!< ���SEG-D�ļ�·��
	char	remote_ip_[MAX_STRING_SIZE_LOCAL];	//!< ����ip��ַ
	unsigned	remote_port_; //!< �˿�

	int	shot_number_;			//!< �ں� 1 �� 9999
	int	FileNumber_;			//!< �ļ����  1 �� 9999

	float source_line_number_;	//!< ���ߺ�
	float source_point_number_;	//!< ��Դ���

	int sample_frequency_;		//!< ������250��500��1000��2000��4000 ΢��
	int sample_length_;			//!< �ɼ�����1000��128000 ����

	int receiver_line_number_; //!< ����������
	int	auxiliary_line_number_;		//!< ����������
	int	auxiliary_trace_number_;	//!< ������¼������	
	int trace_total_number_;	//!< ��¼������1��100000
	int source_type_;			//!< 29-32 XXXX bin ��Դ����0 = ����Դ 1 = ���� 2 = �ɿ���Դ
	int sample_number_in_trace_;	//!< 33-36 XXXX bin ��¼����������Ŀ1 �� 128000

	float tb_window_; //!< TB����ֵ
	time_t datetime_; //!< ��ʼʱ��
	int tb_time_;	  //�ڲ�TBʱ��=����ʱ�䣬�Ӹ�ʱ�����¼����

	float resistor_lower_limit_; //!< ��������
	float resistor_higher_limit_;//!< ��������
	float resistor_value_; //!< ����ֵ
	float tilt_limit_; //!< ��б�Ƚ���
	float tilt_value_; //!< ��б��ֵ
	bool resistor_deviation_; //!< �������
	bool tilt_deviation_; //!< ��б�����
}AD_DATA_FILE_HEAD_PRIVATE, *AD_DATA_FILE_HEAD__PRIVATE_PTR;

/**
@struct	__tagAD_DATA_FILE_INFO
@brief	AD�����ļ�ͷ��Ϣ
@note	typedef struct __tagAD_DATA_FILE_INFO AD_DATA_FILE_INFO, *AD_DATA_FILE_INFO_PTR;
*/
typedef struct __tagAD_DATA_FILE_INFO
{
	HANDLE	file_handle_; //!< �����ļ����
	LARGE_INTEGER data_size_; //!< ���ݴ�С;
	ULONG	frame_number_per_fdu_; //!< ÿ���豸�ɼ�֡����������DAT�ļ�
	UCHAR	manufacturer_code_;//!< ָ���������,sercelΪ13, ��ע��ʱ,ͨ��ʹ��0
	AD_DATA_FILE_HEAD_PRIVATE file_header_;
}AD_DATA_FILE_INFO, *AD_DATA_FILE_INFO_PTR;


/**
@fn int load_data_file(char_t const* data_path, AD_DATA_FILE_INFO_PTR ad_data_ptr);
@brief ��ȡ�����ļ�
@param[in]		data_path	�����ļ�·��
@param[in/out]	ad_data_ptr	����ͷ�ļ��ṹ
@return ����ɹ�����APP_SUCCESS, ���򷵻�APP_FAULT
@note
*/
int load_data_file(char_t const* data_path, AD_DATA_FILE_INFO_PTR ad_data_ptr);

/**
@fn	int modify_config_info(__in__ char_t const* config_path, const AD_DATA_FILE_INFO_PTR ad_data_ptr)
@details ͨ�������ļ���Ϣ�޸������ļ�
@param[in]	config_path	�����ļ�Ŀ¼
@param[in]	ad_data_ptr	�����ļ��е�������Ϣ
@return	���ʧ�ܷ���APP_FAULT,���򷵻�APP_SUCCESS
@note	
*/
int modify_config_info(__in__ char_t const* config_path, __in__ const AD_DATA_FILE_INFO_PTR ad_data_ptr);
int modify_config_info(__in__ const AD_DATA_FILE_INFO_PTR ad_data_ptr, __in_out__ VOID* segd_config_info_ptr);
/**
@fn	int get_trace_size(__in__ const AD_DATA_FILE_INFO_PTR ad_data_ptr);
@details �õ����ٵ�����,��ֵΪtrace_total_number - 1
@param[in]	ad_data_ptr	�����ļ��е�������Ϣ
@return	���ظ��ٵ�����
@note	
*/
inline int get_total_trace_size(__in__ const AD_DATA_FILE_INFO_PTR ad_data_ptr){return ad_data_ptr->file_header_.trace_total_number_;};
inline int get_aux_trace_size(__in__ const AD_DATA_FILE_INFO_PTR ad_data_ptr)
	{return ad_data_ptr->file_header_.auxiliary_trace_number_ * ad_data_ptr->file_header_.auxiliary_line_number_;};
inline int get_trace_size(__in__ const AD_DATA_FILE_INFO_PTR ad_data_ptr)
	{return get_total_trace_size(ad_data_ptr) - get_aux_trace_size(ad_data_ptr);};

/**
@fn	int get_data_frame_size(__in__ const AD_DATA_FILE_INFO_PTR ad_data_ptr);
@details ���ݲɼ��ļ��е�����֡����
@param[in]	ad_data_ptr	�����ļ��е�������Ϣ
@return	���ص�ǰ����֡����
@note	
*/
inline int get_data_frame_size(__in__ const AD_DATA_FILE_INFO_PTR ad_data_ptr){	return ad_data_ptr->frame_number_per_fdu_; };

/**
@fn	int get_data_size(__in__ const AD_DATA_FILE_INFO_PTR ad_data_ptr);
@details ÿ��FDU�ɼ��������ܷ���SEGD�ļ��е����ݴ�С
@param[in]	ad_data_ptr	�����ļ��е�������Ϣ
@return	����ÿ��FDU�ɼ��������ܷ���SEGD�ļ��е����ݴ�С
@note	
*/
int get_data_size(__in__ const AD_DATA_FILE_INFO_PTR ad_data_ptr);

/**
@fn	int get_file_header_size()
@details 
@return	���ص�ǰ����֡����
@note	
*/
int get_file_header_size();

#endif //__PROC_DATA_FILE_H__