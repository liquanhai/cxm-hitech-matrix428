/**
@brief	����ָ���Ĳ�����, FDU, ��������Ϣ����SEGD�ļ�
@details	
@file	make.segd.cpp
@note	
@see	
@version
@author	kuoxin	
@bug
*/
#include "segd.conv.h"
#include "proc.conf.file.h"
#include "..\segd.viewer\segd.file.format.h"
#include "proc.sps.file.h"
#include "proc.data.file.h"
#include "merge.config.info.h"
#include <time.h>
#include <complex>

extern APPLICATION_ENVIRONMENT __application_environment; //!< ����Ӧ�ó���ȫ�ֻ�������

/**
@func		void make_sin_data(float* * data, size_t& data_length)
@detail	������������
@param[in/out]	data	����sin����
@param[in/out]	data_length ���ݳ���
@return void
@remark �ú������������ݴ�С,ʹ�ú�����ͷ�	
*/
void make_sin_data(float** data, size_t& data_length)
{
	static const int count = 5;
	static const float max = 6.2832 * count;
	static const int freq = 80;
	float i = 0;
	int tmp_freq = freq/count;
	float tmp_val = 0x0;

	*data = new float[freq];
	data_length = 0x0;
	ZeroMemory(*data, sizeof(float) * freq);

	for(i = 0; i < tmp_freq; ++i )
		(*data)[data_length++] = std::sin(i);

	tmp_val = (*data)[data_length-1];
	for(i = 0; i < tmp_freq; ++i)
		(*data)[data_length++] = 2 * std::sin(i) + tmp_val;

	tmp_val = (*data)[data_length-1];
	for(i = 0; i < tmp_freq; ++i)
		(*data)[data_length++] = 3 * std::sin(i) + tmp_val;

	tmp_val = (*data)[data_length-1];
	for(i = 0; i < tmp_freq; ++i)
		(*data)[data_length++] = 2 * std::sin(i) + tmp_val;

	tmp_val = (*data)[data_length-1];
	for(i = 0; i < tmp_freq; ++i)
		(*data)[data_length++] = std::sin(i) + tmp_val;
}

int convert_float_to_int(float f_val)
{
	static const int min_freq = 0x7fffff / 2.5f;
	static const float max_freq = 0x800000/2.5f;
	int result = 0x0;

	if(f_val < 0){
		f_val = -f_val;
		result = (f_val * min_freq) + 0x800000;
	}
	else{
		result = max_freq * f_val;
	}
	return result;
}

/**
@fn	int make_virtual_data_file(SEGD_CONFIG_FILE_PTR segd_config_ptr, AD_DATA_FILE_INFO_PTR ad_data_ptr)
@details ����SEGD�����ļ���Ϣ,����AD�ɼ��ļ�
@param[in]	segd_config_ptr segd �����ļ���Ϣ
@param[in/out]	ad_data_ptr		AD �����ļ���Ϣ
@return	���ʧ�ܷ��ش�����Ϣ,���򷵻�APP_SUCCESS
@note	��ǰʹ��char_t
*/
int make_virtual_data_file(SEGD_CONFIG_FILE_PTR segd_config_ptr, AD_DATA_FILE_INFO_PTR ad_data_ptr)
{
	_ASSERTE(ad_data_ptr);
	_ASSERTE(segd_config_ptr);

	int is_ok = APP_SUCCESS;
	size_t mbcs_size = 0x0;

	__matrix_zero_Memory(ad_data_ptr, sizeof(AD_DATA_FILE_INFO));

	ad_data_ptr->manufacturer_code_ = segd_config_ptr->header_1_.manufacturer_code_;
	ad_data_ptr->file_header_.trace_total_number_ = segd_config_ptr->extended_header_.trace_total_number_;
	ad_data_ptr->frame_number_per_fdu_ = ad_data_ptr->data_size_.QuadPart / ((SAMPLE_DATA_PACKAGE_SIZE * 3 + TB_TIME_LENGTH) * ad_data_ptr->file_header_.trace_total_number_);

	//�õ���ʵ��Ч��sample_length & sample_number_in_trace -- ������Ϊtb_time��Ĳ������ݳ���
	ad_data_ptr->file_header_.sample_length_ = segd_config_ptr->extended_header_.sample_length_;
	ad_data_ptr->file_header_.sample_number_in_trace_ = segd_config_ptr->extended_header_.sample_number_in_trace_;

	wcstombs_s(&mbcs_size, ad_data_ptr->file_header_.config_path_, sizeof(ad_data_ptr->file_header_.config_path_), 
		segd_config_ptr->config_path_, sizeof(ad_data_ptr->file_header_.config_path_));
	ad_data_ptr->file_header_.config_path_[mbcs_size] = 0x0;

	wcstombs_s(&mbcs_size, ad_data_ptr->file_header_.sps_path_, sizeof(ad_data_ptr->file_header_.sps_path_), 
		segd_config_ptr->sps_path_, sizeof(ad_data_ptr->file_header_.sps_path_));
	ad_data_ptr->file_header_.sps_path_[mbcs_size] = 0x0;

	wcstombs_s(&mbcs_size, ad_data_ptr->file_header_.dat_path_, sizeof(ad_data_ptr->file_header_.dat_path_), 
		segd_config_ptr->dat_path_, sizeof(ad_data_ptr->file_header_.dat_path_));
	ad_data_ptr->file_header_.dat_path_[mbcs_size] = 0x0;

	wcstombs_s(&mbcs_size, ad_data_ptr->file_header_.output_path_, sizeof(ad_data_ptr->file_header_.output_path_), 
		segd_config_ptr->output_path_, sizeof(ad_data_ptr->file_header_.output_path_));
	ad_data_ptr->file_header_.output_path_[mbcs_size] = 0x0;

	ad_data_ptr->file_header_.remote_ip_;	//!< ����ip��ַ
	wcstombs_s(&mbcs_size, ad_data_ptr->file_header_.remote_ip_, sizeof(ad_data_ptr->file_header_.remote_ip_), 
		segd_config_ptr->remote_ip_, sizeof(ad_data_ptr->file_header_.remote_ip_));
	ad_data_ptr->file_header_.remote_ip_[mbcs_size] = 0x0;

	ad_data_ptr->file_header_.remote_port_ = segd_config_ptr->remote_port_; //!< �˿�

	ad_data_ptr->file_header_.shot_number_ = segd_config_ptr->extended_header_.shot_number_;			//!< �ں� 1 �� 9999
	ad_data_ptr->file_header_.FileNumber_ = segd_config_ptr->header_1_.file_number_;			//!< �ļ����  1 �� 9999

	ad_data_ptr->file_header_.source_line_number_ = segd_config_ptr->header_3_.source_line_number_;	//!< ���ߺ�
	ad_data_ptr->file_header_.source_point_number_ = segd_config_ptr->header_3_.source_point_number_;	//!< ��Դ���

	ad_data_ptr->file_header_.sample_frequency_ = segd_config_ptr->extended_header_.sample_frequency_;		//!< ������250��500��1000��2000��4000 ΢��

	ad_data_ptr->file_header_.receiver_line_number_ = segd_config_ptr->trace_header_.trace_header_extended_1_.receiver_line_number_; //!< ����������
	ad_data_ptr->file_header_.auxiliary_line_number_ = 2;		//!< ����������
	ad_data_ptr->file_header_.auxiliary_trace_number_ = 2;	//!< ������¼������

	ad_data_ptr->file_header_.source_type_ = segd_config_ptr->extended_header_.source_type_;
	ad_data_ptr->file_header_.tb_window_ = segd_config_ptr->extended_header_.tb_window_; //!< TB����ֵ
	time(&ad_data_ptr->file_header_.datetime_); //!< ��ʼʱ��
	ad_data_ptr->file_header_.tb_time_ = 0x0;	  //�ڲ�TBʱ��=����ʱ�䣬�Ӹ�ʱ�����¼����

	ad_data_ptr->file_header_.resistor_lower_limit_ = segd_config_ptr->trace_header_.trace_header_extended_3_.resistor_lower_limit_; //!< ��������
	ad_data_ptr->file_header_.resistor_higher_limit_ = segd_config_ptr->trace_header_.trace_header_extended_3_.resistor_higher_limit_;//!< ��������
	ad_data_ptr->file_header_.resistor_value_ = segd_config_ptr->trace_header_.trace_header_extended_3_.resistor_value_; //!< ����ֵ
	ad_data_ptr->file_header_.tilt_limit_ = segd_config_ptr->trace_header_.trace_header_extended_3_.tilt_limit_; //!< ��б�Ƚ���
	ad_data_ptr->file_header_.tilt_value_ = segd_config_ptr->trace_header_.trace_header_extended_3_.tilt_value_; //!< ��б��ֵ
	ad_data_ptr->file_header_.resistor_deviation_ = segd_config_ptr->trace_header_.trace_header_extended_3_.resistor_deviation_; //!< �������
	ad_data_ptr->file_header_.tilt_deviation_ = segd_config_ptr->trace_header_.trace_header_extended_3_.tilt_deviation_; //!< ��б�����

	return is_ok;
}

/**
@fn	int write_segd_data_private2(SEGD_CONFIG_FILE_PTR segd_config_ptr,
								SEGD_FILE_PTR outp_file_ptr,
								SPS_DATA_INFO_PTR sps_data_info_ptr,
								)
@details ���ݴ����������segd�������ļ�����
@param[in]	segd_config_ptr	segd���ýṹ��
@param[in]	outp_file_ptr		����ļ��ṹ��
@param[in]	sps_data_info_ptr	sps���ݽṹ��
@param[in]	ad_data_ptr			AD���ݽṹ��
@return	���ʧ�ܷ��ش�����Ϣ,���򷵻�APP_SUCCESS
@note	��ǰʹ��char_t
*/
int make_segd_data_private(SEGD_CONFIG_FILE_PTR segd_config_ptr,
							SEGD_FILE_PTR outp_file_ptr,
							SPS_DATA_INFO_PTR sps_data_info_ptr,
							AD_DATA_FILE_INFO_PTR ad_data_ptr)
{
	int is_ok = APP_SUCCESS;

	float * data = NULL;
	size_t data_length = 0x0;
	int size = 0, i = 0, j =0, k =0, tmp_val = 0x0;
	int trace_number = get_total_trace_size(ad_data_ptr);
	int aut_trace_number = get_aux_trace_size(ad_data_ptr);
	int valid_segd_data_size = get_data_size(ad_data_ptr);
	int fdu_index = 0x0;
	int step_length = 0x0;

	float* outp_data = NULL;
	size_t outp_data_size = segd_config_ptr->extended_header_.trace_total_number_;

	SPS_RELATION_RECORD_SPEC_PTR relation_record_ptr = NULL;
	SPS_POINT_RECORD_SPEC_PTR point_record_ptr = NULL;
	SEGD_FILE_TRACE_HEADER trace_header;

	size = segd_file_get_trace_data_size_base(segd_config_ptr->header_1_.manufacturer_code_, 
												segd_config_ptr->extended_header_.sample_number_in_trace_,
												segd_config_ptr->extended_header_.sample_length_,
												segd_config_ptr->extended_header_.sample_frequency_);


	step_length = ((size/CURRENT_SEGD_MINI_DATA_LENGTH)*2)/segd_config_ptr->extended_header_.trace_total_number_;
	outp_data_size *= size;
	outp_data = (float*)malloc(outp_data_size);
	ZeroMemory(outp_data, outp_data_size);

	//������������
	make_sin_data(&data, data_length);
	data_length = data_length < step_length ? data_length : step_length;
	for(i = segd_config_ptr->extended_header_.trace_total_number_/2, k = 0; i >=0 ; --i, k += step_length)
		for(j = 0; j < data_length; ++j)
			outp_data[i* size/CURRENT_SEGD_MINI_DATA_LENGTH + k + j] = data[j];

	for(i = segd_config_ptr->extended_header_.trace_total_number_/2 + 1, k = 0;
		i < segd_config_ptr->extended_header_.trace_total_number_ ; ++i, k += step_length)
		for(j = 0; j < data_length; ++j)
			outp_data[i * size/CURRENT_SEGD_MINI_DATA_LENGTH + k + j] = data[j];

	
	for(k = 0, j = 0, i = 0; i < ad_data_ptr->file_header_.receiver_line_number_; ++i, j = 0){

		relation_record_ptr = sps_data_info_ptr->head_relation_records_ptr_;
		//�õ���������Ϣ
		while(relation_record_ptr != NULL){	
			if(j == i){	break;}
			else{relation_record_ptr = relation_record_ptr->next_; ++j;}
		}

		if(relation_record_ptr == NULL){	set_last_error(IDS_STRING5031); output_log(IDS_STRING5031); goto GOTO;}

		//����SPSͨ�������Ƿ���ڲ������,������ڲ������,���򽫱���,���ҽ�������
		j = (relation_record_ptr->to_channel_ -  relation_record_ptr->from_channel_) / relation_record_ptr->channel_increment_;
		if(j < (ad_data_ptr->file_header_.trace_total_number_ - 
			(ad_data_ptr->file_header_.auxiliary_line_number_ * 
			ad_data_ptr->file_header_.auxiliary_trace_number_))){

				set_last_error(IDS_STRING5045);
				output_log(get_last_error());
				is_ok = APP_FAULT;
				goto GOTO;
		}

		for(j = relation_record_ptr->from_channel_; j < relation_record_ptr->to_channel_; 
			j += relation_record_ptr->channel_increment_, k = 0){

				fdu_index = tmp_val = (j - relation_record_ptr->from_channel_)/relation_record_ptr->channel_increment_;
				if(tmp_val == (trace_number - aut_trace_number)) break;

				//write trace header
				__matrix_zero_Memory(&trace_header, sizeof(trace_header));
				CopyMemory(&trace_header, &segd_config_ptr->trace_header_, sizeof(trace_header));

				point_record_ptr = relation_record_ptr->head_receiver_point_ptr_;
				while(point_record_ptr != NULL){
					if(k == tmp_val) break;
					else{point_record_ptr = point_record_ptr->next_; ++k;}	
				}

				if(point_record_ptr == NULL){	
					set_last_error(IDS_STRING5041); 
					output_log(IDS_STRING5041); 
					goto GOTO;
				}

				trace_header.demux_trace_header_.trace_number_ = j;
				trace_header.demux_trace_header_.channel_set_number_ = i + 1;
				trace_header.trace_header_extended_1_.receiver_line_number_ = point_record_ptr->line_name_;
				trace_header.trace_header_extended_1_.receiver_point_number_ = point_record_ptr->point_number_;
				trace_header.trace_header_extended_2_.receiver_point_east_ = point_record_ptr->easting_;
				trace_header.trace_header_extended_2_.receiver_point_high_ = point_record_ptr->elevation_;
				trace_header.trace_header_extended_2_.receiver_point_north_ = point_record_ptr->northing_;
				trace_header.trace_header_extended_2_.extended_trace_number_ = j;

				is_ok = segd_file_write_trace_header(outp_file_ptr, &trace_header);
				if(!is_ok){
					set_last_error(GetLastError());
					output_log(get_last_error());
					is_ok = APP_FAULT;
					goto GOTO;
				}			

				//�õ�ÿ���ɼ�������
				segd_file_write_trace_data(outp_file_ptr, (SEGD_UCHAR*)(outp_data + (fdu_index * valid_segd_data_size) / 4), valid_segd_data_size);
		}
	}

	//12. д��SEG-D�ļ�β
	for(k = get_trace_size(ad_data_ptr), 
		i = 0; i < ad_data_ptr->file_header_.auxiliary_line_number_; ++i){

			for(j = 0; j < ad_data_ptr->file_header_.auxiliary_trace_number_; ++j, ++k, ++fdu_index){

				segd_config_ptr->extended_header_.auxiliary_trace_number_ = 1;
				__matrix_zero_Memory(&trace_header, sizeof(trace_header));
				CopyMemory(&trace_header, &segd_config_ptr->trace_header_, sizeof(trace_header));
				trace_header.demux_trace_header_.channel_set_number_ = ad_data_ptr->file_header_.receiver_line_number_ + i + 1;
				trace_header.demux_trace_header_.trace_number_ = j + 1;
				trace_header.trace_header_extended_2_.extended_trace_number_ = j + 1;
				trace_header.trace_header_extended_1_.receiver_line_number_ = 0xffffff;
				trace_header.trace_header_extended_1_.receiver_point_number_ = 0xffffff;
				is_ok = segd_file_write_trace_header(outp_file_ptr, &trace_header);

				if(!is_ok){	
					set_last_error(GetLastError());	
					output_log(get_last_error()); 
					is_ok = APP_FAULT;
					goto GOTO;
				}
				else{ 
					is_ok = APP_SUCCESS;
				}

				//�õ�ÿ���ɼ�������
				segd_file_write_trace_data(outp_file_ptr, (SEGD_UCHAR*)(outp_data + (fdu_index * valid_segd_data_size) / 4), valid_segd_data_size);
			}
	}

GOTO:
	if(outp_data) free(outp_data);
	if(data)	free(data);

	return is_ok;
}

/**
@fn	int run_making_segd_file_arg_private(APPLICATION_COMMAND_ARG_PTR arg)
@details ���ݴ���������ļ�������Ӧ��SEGD�ļ�
@param[in]	argc	��������
@param[in]	argv	��������
@return	���ʧ�ܷ���false,���򷵻�true
@note	��ǰʹ��char_t
*/
int run_making_segd_file_arg_private(APPLICATION_COMMAND_ARG_PTR arg)
{
	int error_code = APP_SUCCESS, i = 0x0, trace_group_value = 0x0;
	SEGD_CONFIG_FILE_PTR segd_config_info_ptr = NULL;
	SEGD_FILE_PTR outp_file_ptr = NULL;
	SPS_DATA_INFO sps_data_info;
	AD_DATA_FILE_INFO ad_data;

	__matrix_zero_Memory(&sps_data_info, sizeof(sps_data_info));

	__matrix_strcpy_s(__application_environment.config_file_path_, 
		sizeof(__application_environment.config_file_path_)/sizeof(__application_environment.config_file_path_[0]), arg->value_);

	//1. ��ȡ�����ļ�
	if(load_config_file(__application_environment.config_file_path_) != APP_SUCCESS){	error_code = APP_FAULT;	goto GOTO;}

	//2. �õ�������Ϣ & ����socket
	segd_config_info_ptr = get_segd_config_info_ptr();

	//3. ��������AD�����ļ�
	if(make_virtual_data_file(segd_config_info_ptr, &ad_data) != APP_SUCCESS){	error_code = APP_FAULT;	goto GOTO;}

	//4. ��ȡSPS������Ϣ
	sps_data_info.sps_path_ptr_ = segd_config_info_ptr->sps_path_;
	sps_data_info.source_line_number_ = ad_data.file_header_.source_line_number_;
	sps_data_info.source_point_number_ = ad_data.file_header_.source_point_number_;
	load_sps_file(&sps_data_info);

	//5. ����SEG-D�ļ�
	outp_file_ptr = segd_file_create(segd_config_info_ptr->output_path_, SEGD_FILE_CREATE | SEGD_FILE_IO_NON_OVERLAPPED);
	if(outp_file_ptr == NULL){
		set_last_error(IDS_STRING5014);
		output_log(IDS_STRING5014, segd_config_info_ptr->output_path_);
		error_code = APP_FAULT;
		goto GOTO;
	}

	//6. д����ͨͷ�����ݿ�1
	merge_segd_header_1(&sps_data_info, &segd_config_info_ptr->header_1_);
	memcpy_s(&outp_file_ptr->header_1_, sizeof(outp_file_ptr->header_1_), &segd_config_info_ptr->header_1_, sizeof(segd_config_info_ptr->header_1_));
	if(!segd_file_write_genernal_header_1(outp_file_ptr, &outp_file_ptr->header_1_)){

		set_last_error(GetLastError());
		output_log(get_last_error());
		error_code = APP_FAULT;
		goto GOTO;
	}

	//7. д����ͨͷ�����ݿ�2
	merge_segd_header_2(&sps_data_info, &segd_config_info_ptr->header_2_);
	memcpy_s(&outp_file_ptr->header_2_, sizeof(outp_file_ptr->header_2_), &segd_config_info_ptr->header_2_, sizeof(segd_config_info_ptr->header_2_));
	if(!segd_file_write_genernal_header_2(outp_file_ptr, &outp_file_ptr->header_2_)){

		set_last_error(GetLastError());
		output_log(get_last_error());
		error_code = APP_FAULT;
		goto GOTO;
	}

	//8. д����ͨͷ�����ݿ�3
	merge_segd_header_3(&sps_data_info, &segd_config_info_ptr->header_3_);
	memcpy_s(&outp_file_ptr->header_3_, sizeof(outp_file_ptr->header_3_), &segd_config_info_ptr->header_3_, sizeof(segd_config_info_ptr->header_3_));
	if(segd_config_info_ptr->header_1_.additional_blocks_in_general_header_ == 2){

		if(!segd_file_write_genernal_header_3(outp_file_ptr, &outp_file_ptr->header_3_)){

			set_last_error(GetLastError());
			output_log(get_last_error());
			error_code = APP_FAULT;
			goto GOTO;
		}
	}

	//9. д��ɨ������ͷ��
	if((ad_data.file_header_.receiver_line_number_ + ad_data.file_header_.auxiliary_line_number_) 
			> segd_config_info_ptr->header_1_.channal_sets_scan_type_){	

				set_last_error(IDS_STRING5044); output_log(get_last_error());error_code = APP_FAULT; goto GOTO;
	}
	else{
		i = sizeof(SEGD_SCAN_TYPE_HEADER) * segd_config_info_ptr->header_1_.channal_sets_scan_type_;
		outp_file_ptr->scan_type_header_ = (SEGD_SCAN_TYPE_HEADER_PTR)malloc(i);
		__matrix_zero_Memory(outp_file_ptr->scan_type_header_, i);
	}

	//9.1д���¼������Ϣ
	for(trace_group_value = 1, i = 0; i< ad_data.file_header_.receiver_line_number_; ++i, ++trace_group_value){

		//__matrix_zero_Memory(&segd_scan_type_header, sizeof(segd_scan_type_header));
		if(i < sps_data_info.relation_records_size_){

			merge_segd_scan_type_header(&sps_data_info, &segd_config_info_ptr->scan_type_header_);
			memcpy(outp_file_ptr->scan_type_header_ + (trace_group_value - 1), 
				&segd_config_info_ptr->scan_type_header_, sizeof(SEGD_SCAN_TYPE_HEADER));

		}
		outp_file_ptr->scan_type_header_[trace_group_value - 1].channel_set_number_ = trace_group_value;
		outp_file_ptr->scan_type_header_[trace_group_value - 1].channels_number_ = 
			ad_data.file_header_.trace_total_number_ - ad_data.file_header_.auxiliary_trace_number_ * ad_data.file_header_.auxiliary_line_number_;

		if(!segd_file_write_scan_type_header(outp_file_ptr, &outp_file_ptr->scan_type_header_[trace_group_value - 1])){
			set_last_error(GetLastError());	output_log(get_last_error()); error_code = APP_FAULT; goto GOTO;}
	}

	//9.2д�븨��������Ϣ
	for(i = 0; i< ad_data.file_header_.auxiliary_line_number_; ++i, ++trace_group_value){

		memcpy(outp_file_ptr->scan_type_header_ + trace_group_value - 1, outp_file_ptr->scan_type_header_, sizeof(SEGD_SCAN_TYPE_HEADER));
		outp_file_ptr->scan_type_header_[trace_group_value - 1].channels_number_ = ad_data.file_header_.auxiliary_trace_number_;
		outp_file_ptr->scan_type_header_[trace_group_value - 1].channel_type_identification_ = 9;
		outp_file_ptr->scan_type_header_[trace_group_value - 1].channel_set_number_ = trace_group_value;
		if(!segd_file_write_scan_type_header(outp_file_ptr, &outp_file_ptr->scan_type_header_[trace_group_value - 1])){
			set_last_error(GetLastError());	output_log(get_last_error()); error_code = APP_FAULT; goto GOTO;}
	}

	trace_group_value = ad_data.file_header_.receiver_line_number_ + ad_data.file_header_.auxiliary_line_number_;
	for(i = trace_group_value; i < segd_config_info_ptr->header_1_.channal_sets_scan_type_; ++i){

		__matrix_zero_Memory(outp_file_ptr->scan_type_header_ + i, sizeof(SEGD_SCAN_TYPE_HEADER));
		if(!segd_file_write_scan_type_header(outp_file_ptr, &outp_file_ptr->scan_type_header_[i])){
			set_last_error(GetLastError());	output_log(get_last_error()); error_code = APP_FAULT; goto GOTO;}
	}

	//10. д����չͷ��
	if(segd_config_info_ptr->header_1_.extended_header_block_ == 32){

		merge_segd_extend_header(&sps_data_info, &segd_config_info_ptr->extended_header_);
		memcpy_s(&outp_file_ptr->extended_header_, sizeof(outp_file_ptr->extended_header_), &segd_config_info_ptr->extended_header_, sizeof(segd_config_info_ptr->extended_header_));
		if(!segd_file_write_extended_header(outp_file_ptr, &outp_file_ptr->extended_header_)){

			set_last_error(GetLastError());
			output_log(get_last_error());
			error_code = APP_FAULT;
			goto GOTO;
		}
	}

	//11. д���¼�����ݿ� + д��AD����
	make_segd_data_private(segd_config_info_ptr, outp_file_ptr, &sps_data_info, &ad_data);
GOTO:
	free_sps_data_memory(&sps_data_info);
	CloseHandle(ad_data.file_handle_);
	segd_file_close(outp_file_ptr);
	return error_code;
}
