/**
@brief	��ȡSPS�ļ�,��ȡSEG-Dʹ�ò���
@details	����Ӧ��sps�ļ�,Ȼ������Ӧ�Ĳ���д��SEG-D�����ļ���,
			sps�ļ�������׺Ϊx,r,s�������ļ��ֱ�����ж�ȡ�����Ϣ
			�����淶:
			//��¼��ʶ����H����1��ͷ�μ�¼���ͣ�2-3��ͷ�μ�¼�����޸ķ���4������������5-32���������ݣ�33-80��

			���	�����	��	��ʽ	��С�����	ȱʡ	��λ
			1	��¼��ʶ	1��1	A1	��R����S��	��	��
			2	������������룩	2��17	4A4	����	��	��
			3	��ţ��Ҷ��룩	18��25	2A4	����	��	��
			4	������	26��26	I1	1��9	1	��
			5	�����*	27��28	A2	�μ�����	��	��
			6	��̬У��	29��32	I4	-999��999	��	����
			7	�����	33��36	F4.1	0��99.9	��	��
			8	�����׼�� 	37��40	I4	-999��9999	��	��
			9	����ʱ��	41��42	I2	0��99	��	����
			10	ˮ��	43��46	F4.1#	0��99.9/999	��	��
			11	���������� 	47��55	F9.1		��	��
			12	����������� 	56��65	F10.1		��	��
			13	����߳�	66��71	F6.1	-999.9��9999.9	��	��
			14	һ������ۼ�	72��74	I3	1��999	��	��
			15	ʱ��hh mm ss��ʱ���룩	75��80	3I2	000000��235959	��	��

			���	�����	��	��ʽ	��С�����	ȱʡ	��λ
			1	��¼��ʶ	1��1	A1	��X��	��	��
			2	Ұ��Ŵ��ţ�����룩	2��7	3A2	����	��	��
			3	Ұ���¼��	8��11	I4	0��9999	��	��
			4	Ұ���¼����	12��12	I1	1��9	I	��
			5	��������	13��13	A1	1��9	I	��
			6	������������룩	14��29	4A4	û�ж���	��	��
			7	��ţ��Ҷ��룩	30��37	2A4	û�ж���	��	��
			8	������	38��38	I1	1��9	I	��
			9	��ʼ��¼����	39��42	I4	1��9999	��	�D
			10	��ֹ��¼����	43��46	I4	1��9999	��	��
			11	������	47��47	I1	1��9	I	��
			12	�����ߺţ�����룩	48��63	4A4	û�ж���	��	��
			13	��ʼ���յ�ţ��Ҷ��룩	64��71	2A4	û�ж���	��	��
			14	��ֹ���յ�ţ��Ҷ��룩	72��79	2A4	û�ж���	��	��
			15	���յ�����	80��80	I1	1��9	I	��

@file	proc.sps.file.cpp
@note	
@see	�й�SPS����,�μ�SPS�淶
@version	1.1.11.33.2011.09.26
@author	kuoxin	
@bug
	1.1.11.33.2011.09.26	��ʼ���汾
	1.1.12.40.2011.09.28	����sps֧��,��Ӧ��Դ��Ϣ���Բ�ѯ�����ܲ����Ϣ
*/

#include "segd.conv.h"
#include "proc.sps.file.h"

/**
@struct	__tagSPS_HEADER_RECORD_SPEC
@brief	sps�ļ�ͷ��¼��������Ϣ,����Ϣ���Գ������ļ���Ҳ���Ժ���,������r,x,s�ļ���,��������ͬ
@note	typedef struct __tagSPS_HEADER_RECORD_SPEC SPS_HEADER_RECORD_SPEC, *SPS_HEADER_RECORD_SPEC_PTR
*/
typedef struct __tagSPS_HEADER_RECORD_SPEC
{
	char id_;	//!< ��¼��ʶ����H��
	short type_;	//!< ͷ�μ�¼����
	int	 modifier_; //!< ͷ�μ�¼�����޸ķ�
	char param_descrip_[28 + 1]; //!< ��������
	char param_data_[48 + 1]; //!< ��������
}SPS_HEADER_RECORD_SPEC, *SPS_HEADER_RECORD_SPEC_PTR;

/**
@struct __tagSPS_POINT_RECORD_SPEC
@brief sps ���¼�ṹ��
@note
	typedef struct __tagSPS_POINT_RECORD_SPEC SPS_POINT_RECORD_SPEC, *SPS_POINT_RECORD_SPEC_PTR;
*/
typedef struct __tagSPS_POINT_RECORD_SPEC_PRIVATE
{
	char	id_[2];//!< ��¼��ʶ	1��1	A1	��R����S��	��	��
	char	line_name_[16 + 1];//!< ������������룩	2��17	4A4	����	��	��
	char	point_number_[8 + 1];//!< ��ţ��Ҷ��룩	18��25	2A4	����	��	��
	char	point_index_[1 + 1];//!< ������	26��26	I1	1��9	1	��
	char	point_code_[2 + 1];//!< �����*	27��28	A2	�μ�����	��	��
	int		static_correction_;//!< ��̬У��	29��32	I4	-999��999	��	����
	float	point_depth_;//!< �����	33��36	F4.1	0��99.9	��	��
	int		seismic_datum_;//!< �����׼�� 	37��40	I4	-999��9999	��	��
	short	uphole_time_;//!< ����ʱ��	41��42	I2	0��99	��	����
	float	water_depth_;//!< ˮ��	43��46	F4.1#	0��99.9/999	��	��
	double	map_grid_easting_;//!< ���������� 	47��55	F9.1		��	��
	double	map_grid_northing_;//!< ����������� 	56��65	F10.1		��	��
	float	surface_elevation_;//!< ����߳�	66��71	F6.1	-999.9��9999.9	��	��
	int		day_of_year_;//!< һ������ۼ�	72��74	I3	1��999	��	��
	short	time_[3];//!< ʱ��hh mm ss��ʱ���룩	75��80	3I2	000000��235959	��	��
}SPS_POINT_RECORD_SPEC_PRIVATE, *SPS_POINT_RECORD_SPEC_PRIVATE_PTR;

/**
@struct __tagSPS_POINT_RECORD_SPEC
@brief sps ��ϵ��¼�ṹ��
@note
	typedef struct __tagSPS_RELATION_RECORD_SPEC SPS_RELATION_RECORD_SPEC, *SPS_RELATION_RECORD_SPEC_PTR;
*/
typedef struct __tagSPS_RELATION_RECORD_SPEC_PRIVATE
{
	char	id_[1 + 1];//!< ��¼��ʶ	1��1	A1	��X��	��	��
	char	field_tape_number_[6 + 1];//!< Ұ��Ŵ��ţ�����룩	2��7	3A2	����	��	��
	int	field_record_number_;//!< Ұ���¼��	8��11	I4	0��9999	��	��
	int	field_record_increment_;//!< Ұ���¼����	12��12	I1	1��9	I	��
	int	instrument_code_;//!< ��������	13��13	A1	1��9	I	��
	char	source_line_name_[16 + 1];//!< ������������룩	14��29	4A4	û�ж���	��	��
	char	source_point_number_[8 + 1];//!< ��ţ��Ҷ��룩	30��37	2A4	û�ж���	��	��
	int	source_point_index_;//!< ������	38��38	I1	1��9	I	��
	int	from_channel_;//!< ��ʼ��¼����	39��42	I4	1��9999	��	�D
	int to_channel_;//!< ��ֹ��¼����	43��46	I4	1��9999	��	��
	int	channel_increment_;//!< ������	47��47	I1	1��9	I	��
	char	receiver_line_name_[16 + 1];//!< �����ߺţ�����룩	48��63	4A4	û�ж���	��	��
	char	from_receiver_[8 + 1];//!< ��ʼ���յ�ţ��Ҷ��룩	64��71	2A4	û�ж���	��	��
	char	to_receiver_[8 + 1];//!< ��ֹ���յ�ţ��Ҷ��룩	72��79	2A4	û�ж���	��	��
	int	receiver_index_;//!< ���յ�����	80��80	I1	1��9	I	��
}SPS_RELATION_RECORD_SPEC_PRIVATE, *SPS_RELATION_RECORD_SPEC_PRIVATE_PTR;

/**
@struct __tagFUNCTION_PARAM
@brief
@note typedef struct __tagFUNCTION_PARAM FUNCTION_PARAM, *FUNCTION_PARAM_PTR;
*/
typedef struct __tagFUNCTION_PARAM
{
	int								receiver_line_name_; //!< ���ܲ�����
	float							receive_point_num_;//!< ���ܵ��
	SPS_RELATION_RECORD_SPEC_PTR	relation_record_ptr_;//!< ��ϵ���ݽṹ��ָ��
}FUNCTION_PARAM, *FUNCTION_PARAM_PTR;

/**
@typedef bool (*ASSIGN_PARAM_CALLBACK)(__in__ char const* line, __in_out__ SPS_DATA_INFO_PTR sps_data_ptr)
@detail ����ص��������ڴ�������ļ��е�ÿһ����Ϣ
@param[in] line һ���ַ�������
@param[in/out] sps_data_ptr ������Ӧ������Ϣ
@return ����ɹ�����true, ���򷵻�false
@note	��ǰ������ļ�����char�ַ�
*/
typedef bool (*ASSIGN_PARAM_CALLBACK)(__in__ char const* line, __in_out__ void* data_ptr);

/**
@struct	__tagSPS_FILE_LINE
@brief	�����SPS�ļ���ȡ��ÿһ����Ϣ
@note	������Ҫ���ڱ����SPS��ȡ����Ϣ,���������ݽṹ�������ı��ļ���ʽ��SPS�ļ�(S,r,x��չ��)����Ȼ����Ϣ
		�ýṹֻ֧����ANSI��ʽ������ı��ļ�,�������һ�еĳ��Ȳ��ܳ���MAX_STRING_SIZE
*/
typedef struct __tagSPS_FILE_LINE
{
	char line_[MAX_STRING_SIZE];	//!< һ����Ϣ
	size_t size_;					//!< һ�д�С
	__tagSPS_FILE_LINE* next_;		//ָ����һ����Ϣ�ṹ��ָ��
}SPS_FILE_LINE, *SPS_FILE_LINE_PTR;

/**
@fn bool proc_lines(__in__ SPS_FILE_LINE_PTR sps_file_line_ptr, __in_out__ void* data_ptr, __in__ ASSIGN_PARAM_CALLBACK callback_function)
@detail ���ڴ򿪵��ļ����ж�ȡ,�������з�ʽ����callback����
@param[in]		sps_file_line_ptr	����sps�ļ�
@param[in/out]	data_ptr	������Ӧ������Ϣ
@param[in]		callback_function	�д���ص�����
@return ����ɹ�����true, ���򷵻�false
@note	��ǰ������ļ�����char�ַ�
*/
bool proc_lines(__in__ SPS_FILE_LINE_PTR sps_file_line_ptr, __in_out__ void* data_ptr, __in__ ASSIGN_PARAM_CALLBACK callback_function)
{
	_ASSERTE(sps_file_line_ptr != NULL);

	bool is_ok = true;
	SPS_FILE_LINE_PTR tmp_ptr = sps_file_line_ptr;

	while(tmp_ptr != NULL){
		//parse a option
		if(!(callback_function(tmp_ptr->line_, data_ptr))) break;
		tmp_ptr = tmp_ptr->next_;
	}

	return is_ok;
}

/**
@fn bool H402_function(__in__ SPS_HEADER_RECORD_SPEC_PTR header_record_spec, __in_out__ SPS_DATA_INFO_PTR sps_data_ptr)
@brief ����H402��ʶ
@param[in]	header_record_spec	spsͷ�μ�¼
@param[in/out]	sps_data_ptr	���浽sps���ݽṹ��
@return ����ɹ�����true, ���򷵻�false
@note
H402Sample int.,Record Len.     1,1MSEC,6SEC;                                   
*/
bool H402_function(__in__ SPS_HEADER_RECORD_SPEC_PTR header_record_spec, __in_out__ SPS_DATA_INFO_PTR sps_data_ptr)
{
	bool is_ok = true;
	char* context = NULL;
	char* token = NULL;
	char* tmp_ptr = NULL;
	
	token = strtok_s(header_record_spec->param_data_, ",", &context);
	while(token != NULL){
		
		tmp_ptr = StrStrA(token, "MSEC");
		if(tmp_ptr != NULL){
			
			token[tmp_ptr - token] = NULL;
			sps_data_ptr->sample_frequency_ = static_cast<int>(atof(token) * 1000);
			switch((int)(atof(token)*100)){
				case 25: {sps_data_ptr->base_scan_interval_ = 4; break;}
				case 50: {sps_data_ptr->base_scan_interval_ = 8; break;}
				case 100: {sps_data_ptr->base_scan_interval_ = 10; break;}
				case 200: {sps_data_ptr->base_scan_interval_ = 20; break;}
				case 400: {sps_data_ptr->base_scan_interval_ = 40; break;}
			}
		}
		else{
			tmp_ptr = StrStrA(token, "SEC");
			if(tmp_ptr != NULL){
				token[tmp_ptr - token] = NULL;
				sps_data_ptr->sample_length_ = atoi(token) * 1000;	
				sps_data_ptr->extended_record_length_ = sps_data_ptr->sample_length_;
				sps_data_ptr->listen_time_ = sps_data_ptr->extended_record_length_;
				sps_data_ptr->sample_number_in_trace_ = sps_data_ptr->sample_length_;
			}
		}

		token = strtok_s(NULL, ",", &context);
	}
	return is_ok; 
}

/**
@fn bool H403_function(__in__ SPS_HEADER_RECORD_SPEC_PTR header_record_spec, __in_out__ SPS_DATA_INFO_PTR sps_data_ptr)
@brief ����H403��ʶ
@param[in]	header_record_spec	spsͷ�μ�¼
@param[in/out]	sps_data_ptr	���浽sps���ݽṹ��
@return ����ɹ�����true, ���򷵻�false
@note
H403Number of channels          1,200;                                          
*/
bool H403_function(__in__ SPS_HEADER_RECORD_SPEC_PTR header_record_spec, __in_out__ SPS_DATA_INFO_PTR sps_data_ptr)
{
	header_record_spec = header_record_spec;
	sps_data_ptr = sps_data_ptr;
	return true; 
}

/**
@fn bool H404_function(__in__ SPS_HEADER_RECORD_SPEC_PTR header_record_spec, __in_out__ SPS_DATA_INFO_PTR sps_data_ptr)
@brief ����H404��ʶ
@param[in]	header_record_spec	spsͷ�μ�¼
@param[in/out]	sps_data_ptr	���浽sps���ݽṹ��
@return ����ɹ�����true, ���򷵻�false
@note
H404Tape type,format,density    1,Cartridge,SEGD,5745171;                       
*/
bool H404_function(__in__ SPS_HEADER_RECORD_SPEC_PTR header_record_spec, __in_out__ SPS_DATA_INFO_PTR sps_data_ptr)
{
	header_record_spec = header_record_spec;
	sps_data_ptr = sps_data_ptr;
	return true; 
}

/**
@fn bool H405_function(__in__ SPS_HEADER_RECORD_SPEC_PTR header_record_spec, __in_out__ SPS_DATA_INFO_PTR sps_data_ptr)
@brief ����H405��ʶ
@param[in]	header_record_spec	spsͷ�μ�¼
@param[in/out]	sps_data_ptr	���浽sps���ݽṹ��
@return ����ɹ�����true, ���򷵻�false
@note
H405Filter_alias Hz,dB pnt,slope1,None;                                         
*/
bool H405_function(__in__ SPS_HEADER_RECORD_SPEC_PTR header_record_spec, __in_out__ SPS_DATA_INFO_PTR sps_data_ptr)
{
	bool is_ok = true;
	char* context = NULL;
	char* token = NULL;
	int num = 0x0;
	double tmp_value = 0x0;

	token = strtok_s(header_record_spec->param_data_, ",", &context);
	while(token != NULL){

		if(num == 0){ ++num;}
		else{
			StrTrimA(token, " ;");
			if(num == 1){
				if(StrCmpA(token, "None") == 0){ break;}
				else{
					tmp_value = atof(token);
				}
			}
			else{ //2,3...
				if(num == 2){
					if(StrCmpA(token, "3DB") == 0){
						switch((int)tmp_value * 100){
						case 25:	sps_data_ptr->alias_filter_frequency_ = 1600;	break;
						case 50:	sps_data_ptr->alias_filter_frequency_ = 800;	break;
						case 100:	sps_data_ptr->alias_filter_frequency_ = 400;	break;
						case 200:	sps_data_ptr->alias_filter_frequency_ = 200;	break;
						case 400:	sps_data_ptr->alias_filter_frequency_ = 100;	break;
						}
					}
				}
			}
		}
		token = strtok_s(NULL, ",", &context);
	}
	return is_ok; 
}

/**
@fn bool H406_function(__in__ SPS_HEADER_RECORD_SPEC_PTR header_record_spec, __in_out__ SPS_DATA_INFO_PTR sps_data_ptr)
@brief ����H406��ʶ
@param[in]	header_record_spec	spsͷ�μ�¼
@param[in/out]	sps_data_ptr	���浽sps���ݽṹ��
@return ����ɹ�����true, ���򷵻�false
@note
H406Filter_notch Hz,-3dB points 1,None;                                         
*/
bool H406_function(__in__ SPS_HEADER_RECORD_SPEC_PTR header_record_spec, __in_out__ SPS_DATA_INFO_PTR sps_data_ptr)
{
	header_record_spec = header_record_spec;
	sps_data_ptr = sps_data_ptr;
	return true; 
}

/**
@fn bool H407_function(__in__ SPS_HEADER_RECORD_SPEC_PTR header_record_spec, __in_out__ SPS_DATA_INFO_PTR sps_data_ptr)
@brief ����H407��ʶ
@param[in]	header_record_spec	spsͷ�μ�¼
@param[in/out]	sps_data_ptr	���浽sps���ݽṹ��
@return ����ɹ�����true, ���򷵻�false
@note
H407Filter_low Hz,dB pnt,slope  1,0.0Hz,0.0DB,0.0DB/OCT;   
*/
bool H407_function(__in__ SPS_HEADER_RECORD_SPEC_PTR header_record_spec, __in_out__ SPS_DATA_INFO_PTR sps_data_ptr)
{
	bool is_ok = true;
	char* context = NULL;
	char* token = NULL;
	char* tmp_ptr = NULL;
	int num = 0x0;

	token = strtok_s(header_record_spec->param_data_, ",", &context);
	while(token != NULL){
		if(num == 0){ ++num;}
		else{
			StrTrimA(token, " ;");
			tmp_ptr = StrStrA(token, "Hz");
			if(tmp_ptr != NULL){
				token[tmp_ptr-token] = NULL;
				sps_data_ptr->low_cut_filter_ = atoi(token);
			}
			else{
				tmp_ptr = StrStrA(token, "DB/OCT");
				if(tmp_ptr != NULL){
					token[tmp_ptr-token] = NULL;
					sps_data_ptr->low_cut_filter_slope_ = atoi(token);				
				}
			}			
		}
		token = strtok_s(NULL, ",", &context);
	}
	return is_ok; 
}

/**
@fn bool H600_function(__in__ SPS_HEADER_RECORD_SPEC_PTR header_record_spec, __in_out__ SPS_DATA_INFO_PTR sps_data_ptr)
@brief ����H402��ʶ
@param[in]	header_record_spec	spsͷ�μ�¼
@param[in/out]	sps_data_ptr	���浽sps���ݽṹ��
@return ����ɹ�����true, ���򷵻�false
@note
H600Type,model,polarity         G1,G_Land,SN7C-10Hz,SEG;                        
*/
bool H600_function(__in__ SPS_HEADER_RECORD_SPEC_PTR header_record_spec, __in_out__ SPS_DATA_INFO_PTR sps_data_ptr)
{
	header_record_spec = header_record_spec;
	sps_data_ptr = sps_data_ptr;
	return true; 
}

/**
@fn bool proc_header_record_callback(char * line, __SPS_DATA_INFO_PTR sps_data_ptr)
@detail callback����
@note	ASSIGN_PARAM_CALLBACK
*/
bool proc_header_record_callback(__in__ char const* line, __in__ void* data_ptr)
{
	bool is_ok = true;
	SPS_DATA_INFO_PTR sps_data_ptr = (SPS_DATA_INFO_PTR)data_ptr;
	char tmp_buff[MAX_STRING_SIZE] = {0};
	SPS_HEADER_RECORD_SPEC header_rec;

	__matrix_zero_Memory(&header_rec, sizeof(header_rec));

	header_rec.id_ = line[0];

	__matrix_zero_Memory(tmp_buff, sizeof(tmp_buff));
	CopyMemory(tmp_buff, line+1, 2);
	header_rec.type_ = atoi(tmp_buff);

	__matrix_zero_Memory(tmp_buff, sizeof(tmp_buff));
	tmp_buff[0] = line[3];
	header_rec.modifier_ = atoi(tmp_buff);

	CopyMemory(header_rec.param_descrip_, line + 4, 28);
	CopyMemory(header_rec.param_data_, line + 32, 48);

	if(header_rec.type_ == 40){
		switch(header_rec.modifier_){
		case 2: H402_function(&header_rec, sps_data_ptr); break;
		case 3: H403_function(&header_rec, sps_data_ptr); break;
		case 4: H404_function(&header_rec, sps_data_ptr); break;
		case 5: H405_function(&header_rec, sps_data_ptr); break;
		case 6: H406_function(&header_rec, sps_data_ptr); break;
		case 7: H407_function(&header_rec, sps_data_ptr); break;
		}
	}
	else if(header_rec.type_ == 60){
		if(header_rec.modifier_ == 0) H600_function(&header_rec, sps_data_ptr);
	}

	return is_ok; 
}


/**
@fn	int read_hxxx_option(__in__ SPS_FILE_LINE_PTR sps_file_line_ptr, __in_out__ void* data_ptr)
@details	��ȡHxxx��Ϣ
@param[in]		sps_file_line_ptr	sps����Ϣ����
@param[in/out]	sps_data_ptr	��sps�ļ��еõ������ݽṹ
@return	����ɹ�����APP_SUCCESS, ���򷵻�APP_FAULT
@note
	����ȡ:
	H402Sample int.,Record Len.     1,1MSEC,6SEC;                                   
	H403Number of channels          1,200;                                          
	H404Tape type,format,density    1,Cartridge,SEGD,5745171;                       
	H405Filter_alias Hz,dB pnt,slope1,None;                                         
	H406Filter_notch Hz,-3dB points 1,None;                                         
	H407Filter_low Hz,dB pnt,slope  1,0.0Hz,0.0DB,0.0DB/OCT;   
	H600Type,model,polarity         G1,G_Land,SN7C-10Hz,SEG;                        
*/
int read_hxxx_option(__in__ SPS_FILE_LINE_PTR sps_file_line_ptr, __in_out__ void* data_ptr)
{
	int is_ok = APP_SUCCESS;

	if(!proc_lines(sps_file_line_ptr, data_ptr, proc_header_record_callback))	is_ok = APP_FAULT;

	return is_ok;
}

bool s_function(__in__ char const* line, __in_out__ void* data_ptr)
{
	bool is_ok = true;
	SPS_POINT_RECORD_SPEC_PRIVATE point_record;
	SPS_DATA_INFO_PTR sps_data_ptr = (SPS_DATA_INFO_PTR)data_ptr;
	float tmp_value = 0x0;
	char tmp_buf[80 + 1] = {0};

	__matrix_zero_Memory(&point_record, sizeof(point_record));

	point_record.id_[0] = line[0];

	CopyMemory(point_record.line_name_, line+1, sizeof(point_record.line_name_) - 1);
//	StrTrimA(point_record.line_name_, " ");

	tmp_value = atof(point_record.line_name_);
	if(tmp_value != sps_data_ptr->source_line_number_) goto GOTO;

	CopyMemory(point_record.point_number_, line + 17, sizeof(point_record.point_number_) - 1);
//	StrTrimA(point_record.point_number_, " ");
	tmp_value = atof(point_record.point_number_);
	if(tmp_value != sps_data_ptr->source_point_number_) goto GOTO;

	point_record.point_index_[0] = line[25];
	CopyMemory(point_record.point_code_, line + 26, sizeof(point_record.point_code_) - 1);

		
	CopyMemory(tmp_buf, line + 28, sizeof(point_record.static_correction_));
//	StrTrimA(tmp_buf, " ");
	point_record.static_correction_ = atoi(tmp_buf);

	__matrix_zero_Memory(tmp_buf, sizeof(tmp_buf));
	CopyMemory(tmp_buf, line + 32, sizeof(point_record.point_depth_));
//	StrTrimA(tmp_buf, " ");
	point_record.point_depth_ = atof(tmp_buf);

	__matrix_zero_Memory(tmp_buf, sizeof(tmp_buf));
	CopyMemory(tmp_buf, line + 36, sizeof(point_record.seismic_datum_));
//	StrTrimA(tmp_buf, " ");
	point_record.seismic_datum_ = atoi(tmp_buf);

	__matrix_zero_Memory(tmp_buf, sizeof(tmp_buf));
	CopyMemory(tmp_buf, line + 40, sizeof(point_record.uphole_time_));
//	StrTrimA(tmp_buf, " ");
	point_record.uphole_time_ = atoi(tmp_buf);

	__matrix_zero_Memory(tmp_buf, sizeof(tmp_buf));
	CopyMemory(tmp_buf, line + 42, sizeof(point_record.water_depth_));
//	StrTrimA(tmp_buf, " ");
	point_record.water_depth_ = atof(tmp_buf);

	__matrix_zero_Memory(tmp_buf, sizeof(tmp_buf));
	CopyMemory(tmp_buf, line + 46, 9);
//	StrTrimA(tmp_buf, " ");
	point_record.map_grid_easting_ = atof(tmp_buf);

	__matrix_zero_Memory(tmp_buf, sizeof(tmp_buf));
	CopyMemory(tmp_buf, line + 55, 10);
//	StrTrimA(tmp_buf, " ");
	point_record.map_grid_northing_ = atof(tmp_buf);

	__matrix_zero_Memory(tmp_buf, sizeof(tmp_buf));
	CopyMemory(tmp_buf, line + 65, 6);
//	StrTrimA(tmp_buf, " ");
	point_record.surface_elevation_ = atof(tmp_buf);

	__matrix_zero_Memory(tmp_buf, sizeof(tmp_buf));
	CopyMemory(tmp_buf, line + 71, 3);
//	StrTrimA(tmp_buf, " ");
	point_record.day_of_year_ = atof(tmp_buf);

	sps_data_ptr->shot_point_.index_ = atoi(point_record.point_index_);
	sps_data_ptr->shot_point_.uphole_time_ = point_record.uphole_time_;
	sps_data_ptr->shot_point_.easting_ = point_record.map_grid_easting_;
	sps_data_ptr->shot_point_.northing_ = point_record.map_grid_northing_;
	sps_data_ptr->shot_point_.elevation_ = point_record.surface_elevation_;
	sps_data_ptr->shot_point_.seismic_datum_ = point_record.seismic_datum_;
	sps_data_ptr->shot_point_.point_number_ = atoi(point_record.point_number_);
	sps_data_ptr->shot_point_.line_name_ = atoi(point_record.line_name_);
GOTO:
	return is_ok; 
}

/**
@fn	int read_shot_option(__in__ SPS_FILE_LINE_PTR sps_file_line_ptr, __in_out__ void* data_ptr)
@details	��ȡHxxx��Ϣ
@param[in]		sps_file_line_ptr	sps����Ϣ����
@param[in/out]	sps_data_ptr	��sps�ļ��еõ������ݽṹ
@return	����ɹ�����APP_SUCCESS, ���򷵻�APP_FAULT
@note
	s�ļ��еĵ���Ϣ:
	S691              23329.51V1                   509494.8 4782327.81269.9
*/
int read_shot_option(__in__ SPS_FILE_LINE_PTR sps_file_line_ptr, __in_out__ void* data_ptr)
{
	int is_ok = APP_SUCCESS;

	if(!proc_lines(sps_file_line_ptr, data_ptr, s_function))	is_ok = APP_FAULT;
	return is_ok;
}

bool r_function(__in__ char const* line, __in_out__ void* data_ptr)
{
	bool is_ok = true;
	SPS_POINT_RECORD_SPEC_PRIVATE point_record;
	FUNCTION_PARAM_PTR param_ptr = (FUNCTION_PARAM_PTR)data_ptr;
	SPS_RELATION_RECORD_SPEC_PTR relation_record_ptr = param_ptr->relation_record_ptr_;
	float tmp_value = 0x0;
	char tmp_buf[80 + 1];
	SPS_POINT_RECORD_SPEC_PTR receive_record_ptr = NULL;

	memset(&point_record, 0x0, sizeof(point_record));

	point_record.id_[0] = line[0];

	CopyMemory(point_record.line_name_, line+1, sizeof(point_record.line_name_) - 1);

//	StrTrimA(point_record.line_name_, " ");

	tmp_value = atof(point_record.line_name_);
	if(tmp_value != param_ptr->receiver_line_name_) goto GOTO;

	CopyMemory(point_record.point_number_, line + 17, sizeof(point_record.point_number_) - 1);
	//StrTrimA(point_record.point_number_, " ");
	tmp_value = atof(point_record.point_number_);
	if(tmp_value != param_ptr->receive_point_num_) goto GOTO;

	point_record.point_index_[0] = line[25];
	CopyMemory(point_record.point_code_, line + 26, sizeof(point_record.point_code_) - 1);

	__matrix_zero_Memory(tmp_buf, sizeof(tmp_buf));
	CopyMemory(tmp_buf, line + 28, sizeof(point_record.static_correction_));
	//StrTrimA(tmp_buf, " ");
	point_record.static_correction_ = atoi(tmp_buf);

	__matrix_zero_Memory(tmp_buf, sizeof(tmp_buf));
	CopyMemory(tmp_buf, line + 32, sizeof(point_record.point_depth_));
	//StrTrimA(tmp_buf, " ");
	point_record.point_depth_ = atof(tmp_buf);

	__matrix_zero_Memory(tmp_buf, sizeof(tmp_buf));
	CopyMemory(tmp_buf, line + 36, sizeof(point_record.seismic_datum_));
	//StrTrimA(tmp_buf, " ");
	point_record.seismic_datum_ = atoi(tmp_buf);

	__matrix_zero_Memory(tmp_buf, sizeof(tmp_buf));
	CopyMemory(tmp_buf, line + 40, sizeof(point_record.uphole_time_));
	//StrTrimA(tmp_buf, " ");
	point_record.uphole_time_ = atoi(tmp_buf);

	__matrix_zero_Memory(tmp_buf, sizeof(tmp_buf));
	CopyMemory(tmp_buf, line + 42, sizeof(point_record.water_depth_));
	//StrTrimA(tmp_buf, " ");
	point_record.water_depth_ = atof(tmp_buf);

	__matrix_zero_Memory(tmp_buf, sizeof(tmp_buf));
	CopyMemory(tmp_buf, line + 46, 9);
	//StrTrimA(tmp_buf, " ");
	point_record.map_grid_easting_ = atof(tmp_buf);

	__matrix_zero_Memory(tmp_buf, sizeof(tmp_buf));
	CopyMemory(tmp_buf, line + 55, 10);
	//StrTrimA(tmp_buf, " ");
	point_record.map_grid_northing_ = atof(tmp_buf);

	__matrix_zero_Memory(tmp_buf, sizeof(tmp_buf));
	CopyMemory(tmp_buf, line + 65, 6);
	//StrTrimA(tmp_buf, " ");
	point_record.surface_elevation_ = atof(tmp_buf);

	__matrix_zero_Memory(tmp_buf, sizeof(tmp_buf));
	CopyMemory(tmp_buf, line + 71, 3);
	//StrTrimA(tmp_buf, " ");
	point_record.day_of_year_ = atof(tmp_buf);

	receive_record_ptr = (SPS_POINT_RECORD_SPEC_PTR)malloc(sizeof(SPS_POINT_RECORD_SPEC));
	if(receive_record_ptr == NULL) {is_ok = false; goto GOTO;}
	__matrix_zero_Memory(receive_record_ptr, sizeof(SPS_POINT_RECORD_SPEC));

	if(relation_record_ptr->head_receiver_point_ptr_ == NULL)	relation_record_ptr->head_receiver_point_ptr_ = receive_record_ptr;
	
	if(relation_record_ptr->tail_receiver_point_ptr_ != NULL){	relation_record_ptr->tail_receiver_point_ptr_->next_ = receive_record_ptr;}
	relation_record_ptr->tail_receiver_point_ptr_ = receive_record_ptr;
	++relation_record_ptr->receiver_point_size_;

	receive_record_ptr->easting_ = point_record.map_grid_easting_;
	receive_record_ptr->elevation_ = point_record.surface_elevation_;
	receive_record_ptr->index_ = atoi(point_record.point_index_);
	receive_record_ptr->line_name_ = atoi(point_record.line_name_);
	receive_record_ptr->northing_ = point_record.map_grid_northing_;
	receive_record_ptr->point_number_ = atoi(point_record.point_number_);
	receive_record_ptr->seismic_datum_ = point_record.seismic_datum_;
	receive_record_ptr->uphole_time_ = point_record.uphole_time_;
GOTO:
	return is_ok; 
}

/**
@fn	int read_receiver_option(__in__ SPS_FILE_LINE_PTR sps_file_line_ptr, __in_out__ void* data_ptr)
@details	��ȡHxxx��Ϣ
@param[in]		sps_file_line_ptr	sps����Ϣ����
@param[in/out]	sps_data_ptr		��sps�ļ��еõ������ݽṹ
@return	����ɹ�����APP_SUCCESS, ���򷵻�APP_FAULT
@note
	r�ļ��еĵ���Ϣ:
	R691                233291G1                   509481.8 4782309.61269.4
*/
int read_receiver_option(__in__ SPS_FILE_LINE_PTR sps_file_line_ptr, __in_out__ void* data_ptr)
{
	int is_ok = APP_SUCCESS;

	if(!proc_lines(sps_file_line_ptr, data_ptr, r_function))	is_ok = APP_FAULT;
	return is_ok;
}

bool x_function(__in__ char const* line, __in_out__ void* data_ptr)
{
	bool is_ok = true;
	SPS_DATA_INFO_PTR sps_data_ptr = (SPS_DATA_INFO_PTR)data_ptr;
	char tmp_buf[80 + 1] = {0};
	int tmp_value = 0x0;
	float tmp_float_value = 0x0;
	SPS_RELATION_RECORD_SPEC_PRIVATE relation_record;
	SPS_RELATION_RECORD_SPEC_PTR relation_record_ptr = NULL;

	__matrix_zero_Memory(&relation_record, sizeof(relation_record));

	relation_record.id_[0] = line[0];

	CopyMemory(relation_record.field_tape_number_, line + 1, sizeof(relation_record.field_tape_number_) - 1);
	CopyMemory(tmp_buf, line + 7, sizeof(relation_record.field_record_number_));
//	StrTrimA(tmp_buf, " ");
	relation_record.field_record_number_ = atoi(tmp_buf);
	
	__matrix_zero_Memory(tmp_buf, sizeof(tmp_buf));
	tmp_buf[0] = line[11];
	relation_record.field_record_increment_ = atoi(tmp_buf);

	__matrix_zero_Memory(tmp_buf, sizeof(tmp_buf));
	tmp_buf[0] = line[12];
	relation_record.instrument_code_ = atoi(tmp_buf);

	CopyMemory(relation_record.source_line_name_, line + 13, sizeof(relation_record.source_line_name_) - 1);
//	StrTrimA(relation_record.source_line_name_, " ");
	tmp_value = atoi(relation_record.source_line_name_);
	if(tmp_value != sps_data_ptr->source_line_number_) goto GOTO;

	CopyMemory(relation_record.source_point_number_, line + 29, sizeof(relation_record.source_point_number_) - 1);
//	StrTrimA(relation_record.source_point_number_, " ");
	tmp_float_value = atof(relation_record.source_point_number_);
	if(tmp_float_value != sps_data_ptr->source_point_number_) goto GOTO;

	__matrix_zero_Memory(tmp_buf, sizeof(tmp_buf));
	tmp_buf[0] = line[37];
	relation_record.source_point_index_ = atoi(tmp_buf);

	__matrix_zero_Memory(tmp_buf, sizeof(tmp_buf));
	CopyMemory(tmp_buf, line + 38, sizeof(int));
	relation_record.from_channel_ = atoi(tmp_buf);

	__matrix_zero_Memory(tmp_buf, sizeof(tmp_buf));
	CopyMemory(tmp_buf, line + 42, sizeof(int));
	relation_record.to_channel_ = atoi(tmp_buf);

	__matrix_zero_Memory(tmp_buf, sizeof(tmp_buf));
	tmp_buf[0] = line[46];
	relation_record.channel_increment_ = atoi(tmp_buf);

	CopyMemory(relation_record.receiver_line_name_, line + 47, sizeof(relation_record.receiver_line_name_) - 1);
//	StrTrimA(relation_record.receiver_line_name_, " ");

	CopyMemory(relation_record.from_receiver_, line + 63, sizeof(relation_record.from_receiver_) - 1);
//	StrTrimA(relation_record.from_receiver_, " ");

	CopyMemory(relation_record.to_receiver_, line + 71, sizeof(relation_record.to_receiver_) - 1);
//	StrTrimA(relation_record.to_receiver_, " ");

	__matrix_zero_Memory(tmp_buf, sizeof(tmp_buf));
	tmp_buf[0] = line[79];
	relation_record.receiver_index_ = atoi(tmp_buf);

	relation_record_ptr = (SPS_RELATION_RECORD_SPEC_PTR)malloc(sizeof(SPS_RELATION_RECORD_SPEC));
	if(!relation_record_ptr) {is_ok = false; goto GOTO;}
	__matrix_zero_Memory(relation_record_ptr, sizeof(SPS_RELATION_RECORD_SPEC));

	if(sps_data_ptr->head_relation_records_ptr_ == NULL)	sps_data_ptr->head_relation_records_ptr_ = relation_record_ptr;

	if(sps_data_ptr->tail_relation_records_ptr_ == NULL){
		sps_data_ptr->tail_relation_records_ptr_ = relation_record_ptr;
	}
	else{
		sps_data_ptr->tail_relation_records_ptr_->next_ = relation_record_ptr;
		sps_data_ptr->tail_relation_records_ptr_ = relation_record_ptr;
	}

	++sps_data_ptr->relation_records_size_;

	relation_record_ptr->channel_increment_ = relation_record.channel_increment_;
	relation_record_ptr->field_record_increment_ = relation_record.field_record_increment_;
	relation_record_ptr->field_record_number_ = relation_record.field_record_number_;
	relation_record_ptr->from_channel_ = relation_record.from_channel_;
	relation_record_ptr->from_receiver_ = atoi(relation_record.from_receiver_);
	relation_record_ptr->instrument_code_ = relation_record.instrument_code_;
	relation_record_ptr->receiver_index_ = relation_record.receiver_index_;
	relation_record_ptr->receiver_line_name_ = atoi(relation_record.receiver_line_name_);
	relation_record_ptr->receiver_point_size_ = 0;
	relation_record_ptr->to_channel_ = relation_record.to_channel_;
	relation_record_ptr->to_receiver_ = atoi(relation_record.to_receiver_);

GOTO:
	return is_ok; 
}

/**
@fn	int read_cross_option(__in__ SPS_FILE_LINE_PTR sps_file_line_ptr, SPS_DATA_INFO_PTR sps_data_ptr)
@details	��ȡHxxx��Ϣ
@param[in]		sps_file_line_ptr	sps����Ϣ����
@param[in/out]	sps_data_ptr	��sps�ļ��еõ������ݽṹ
@return	����ɹ�����APP_SUCCESS, ���򷵻�APP_FAULT
@note
	x�ļ��еĵ���Ϣ:
	X          11691              23329.51   1 6001691                23030   236291
*/
int read_cross_option(__in__ SPS_FILE_LINE_PTR sps_file_line_ptr, __in_out__ void* data_ptr)
{
	int is_ok = APP_SUCCESS;

	if(!proc_lines(sps_file_line_ptr, data_ptr, x_function))	is_ok = APP_FAULT;
	return is_ok;
}

/**
@fn	void free_sps_line_list(__in__ SPS_FILE_LINE_PTR sps_file_line_ptr)
@details	�ͷŶ�ȡ��sps��Ϣ����
@param[in]	sps_file_line_ptr	������������ڵ㿪ʼ�ͷ�������Ϣ
@return	����ɹ�����APP_SUCCESS, ���򷵻�APP_FAULT
@note
*/
void free_sps_line_list(__in__ SPS_FILE_LINE_PTR sps_file_line_ptr)
{
	if(sps_file_line_ptr == NULL) return;
	SPS_FILE_LINE_PTR tmp_ptr = sps_file_line_ptr;
	SPS_FILE_LINE_PTR tmp_ptr2 = NULL;

	while(tmp_ptr != NULL){
		tmp_ptr2 = tmp_ptr->next_;
		tmp_ptr->next_ = NULL;
		free(tmp_ptr);
		tmp_ptr = tmp_ptr2;
	}
}

/**
@fn	int read_lines(__in__ HANDLE file_handle, __in_out__ SPS_FILE_LINE_PTR sps_file_line_ptr)
@details	���ж�ȡ�Ѿ��򿪵�SPS�ļ�,������Ϣ���浽������
@param[in]	file_handle	�򿪵��ļ����,�ļ�������X,R,S�ļ�
@param[in/out]	sps_file_line_ptr	�����ڸ�������
@return	����ɹ�����APP_SUCCESS, ���򷵻�APP_FAULT
@note	��ǰʹ�ñ���ΪANSI��ʽ
*/
int read_lines(__in__ HANDLE file_handle, __in_out__ SPS_FILE_LINE_PTR sps_file_line_ptr)
{
	int is_ok = APP_SUCCESS;
	char buf[MAX_STRING_SIZE] = {0};
	char line[MAX_STRING_SIZE] = {0};
	DWORD size = 0x0, i = 0, cur_line_size = 0x0;
	SPS_FILE_LINE_PTR tmp_ptr = sps_file_line_ptr;
	SPS_FILE_LINE_PTR tmp_ptr2 = NULL;

	if(sps_file_line_ptr == NULL){	set_last_error(IDS_STRING5043);	output_log(IDS_STRING5043);	is_ok = APP_FAULT; 	goto GOTO;}

	SetFilePointer(file_handle, 0, NULL, FILE_BEGIN);
	while(ReadFile(file_handle, buf, sizeof(buf), &size,NULL)){

		if(size == 0) break;
		for(i = 0; i < size; ++i){
			if(buf[i] == 0x0d){

				if(cur_line_size == 0) continue;
				StrTrimA(line, " 	");
				cur_line_size = strlen(line);
				if(cur_line_size == 0) continue;

				//save this line
				StrCpyA(tmp_ptr->line_, line);
				tmp_ptr->size_ = cur_line_size;
				tmp_ptr->line_[cur_line_size] = NULL;
				if(tmp_ptr->next_ == NULL){
					tmp_ptr->next_ = (SPS_FILE_LINE_PTR)malloc(sizeof(SPS_FILE_LINE));
					if(tmp_ptr->next_ == NULL){
						set_last_error(IDS_STRING5042); 
						is_ok = APP_FAULT;	goto GOTO;
					}
					__matrix_zero_Memory(tmp_ptr->next_, sizeof(SPS_FILE_LINE));
				}

				cur_line_size = 0x0;
				__matrix_zero_Memory(line, sizeof(line));
				tmp_ptr2 = tmp_ptr;
				tmp_ptr = tmp_ptr->next_;
			}
			else{
				if(buf[i] != 0xa){	line[cur_line_size++] = buf[i];}
			}
		}
	}

	//�ͷŶ�����нṹ��Ϣ
	if(tmp_ptr != NULL){	if(tmp_ptr2)	tmp_ptr2->next_ = NULL;}
	free_sps_line_list(tmp_ptr);
GOTO:
	return is_ok;
}

int load_sps_file(__in_out__ SPS_DATA_INFO_PTR sps_data_ptr)
{
	int is_ok = APP_SUCCESS;
	int i = 0, loop = 0x0;
	size_t size = 0;
	HANDLE file_handle = INVALID_HANDLE_VALUE;
	char_t* tmp_ptr = NULL;
	errno_t err_no = 0;
	char_t tmp_value[MAX_STRING_SIZE] = {0};
	char_t path[MAX_STRING_SIZE] = {0};
	SPS_RELATION_RECORD_SPEC_PTR relation_record_ptr = NULL;
	FUNCTION_PARAM param;
	SPS_FILE_LINE_PTR sps_file_line_ptr = NULL;

	size = __matrix_strnlen_s(sps_data_ptr->sps_path_ptr_, MAX_STRING_SIZE);
	if(size == 0){
		set_last_error(IDS_STRING5024);	output_log(IDS_STRING5024);	
		is_ok = APP_FAULT; 	goto GOTO;
	}

	CopyMemory(path, sps_data_ptr->sps_path_ptr_, size * sizeof(path[0]));

	tmp_ptr = StrStr(path, __TEXT("."));
	if(tmp_ptr != NULL){//�ڴ���·���з����п��ܴ����ļ���׺
		__matrix_zero_Memory(tmp_value, sizeof(tmp_value));
		err_no = __matrix_splitpath_s(sps_data_ptr->sps_path_ptr_, NULL, 0, NULL,0,
									NULL, 0, tmp_value, sizeof(tmp_value)/sizeof(tmp_value[0]));
		if(err_no != 0){
			set_last_error(IDS_STRING5025);	output_log(IDS_STRING5025);
			is_ok = APP_FAULT; 	goto GOTO;			
		}
		
		size = __matrix_strnlen_s(tmp_value, sizeof(tmp_value)/sizeof(tmp_value[0]));
		if(size != 0){//ȥ���ļ���׺
			tmp_ptr = StrStr(path, tmp_value);
			size = tmp_ptr - tmp_value + 1;
			path[size] = NULL;
		}
	}

	//��s�ļ�
	__matrix_zero_Memory(tmp_value, sizeof(tmp_value));
	size = __matrix_sprintf_s(tmp_value, __TEXT("%s.s"), path);
	tmp_value[size] = 0x0; 
	file_handle = CreateFile(tmp_value, GENERIC_READ, FILE_SHARE_READ, NULL,
							OPEN_EXISTING, FILE_ATTRIBUTE_READONLY, NULL);
	if(file_handle == INVALID_HANDLE_VALUE)
	{	set_last_error(IDS_STRING5026); output_log(IDS_STRING5026, tmp_value);	is_ok = APP_FAULT;	goto GOTO;}
	else{	
		sps_file_line_ptr = (SPS_FILE_LINE_PTR)malloc(sizeof(SPS_FILE_LINE)); 
		if(sps_file_line_ptr == NULL){
			set_last_error(IDS_STRING5042); 
			output_log(IDS_STRING5042, tmp_value);	
			is_ok = APP_FAULT;	goto GOTO;
		}
		__matrix_zero_Memory(sps_file_line_ptr, sizeof(SPS_FILE_LINE));
		is_ok = read_lines(file_handle, sps_file_line_ptr);
		if(is_ok == APP_FAULT) goto GOTO;
	}	

	CloseHandle(file_handle);//�ر�s�ļ�
	is_ok = read_hxxx_option(sps_file_line_ptr, sps_data_ptr);
	if(is_ok == APP_FAULT){	
		if(get_last_error() == IDS_STRING5042)	output_log(IDS_STRING5042, tmp_value);
		goto GOTO;
	}

	is_ok = read_shot_option(sps_file_line_ptr, sps_data_ptr);
	if(is_ok == APP_FAULT){
		if(get_last_error() == IDS_STRING5042)	output_log(IDS_STRING5042, tmp_value);
		goto GOTO;
	}

	//��x�ļ�
	__matrix_zero_Memory(tmp_value, sizeof(tmp_value));
	size = __matrix_sprintf_s(tmp_value, __TEXT("%s.x"), path);
	tmp_value[size] = 0x0; 
	file_handle = CreateFile(tmp_value, GENERIC_READ, FILE_SHARE_READ, NULL, 
							OPEN_EXISTING, FILE_ATTRIBUTE_READONLY, NULL);
	if(file_handle == INVALID_HANDLE_VALUE)
	{	set_last_error(IDS_STRING5026); output_log(IDS_STRING5026, tmp_value);	is_ok = APP_FAULT;	goto GOTO;}
	else{
		is_ok = read_lines(file_handle, sps_file_line_ptr);
		if(is_ok == APP_FAULT) goto GOTO;
	}

	CloseHandle(file_handle);//�ر�x�ļ�
	is_ok = read_cross_option(sps_file_line_ptr, sps_data_ptr);
	if(is_ok == APP_FAULT){	
		if(get_last_error() == IDS_STRING5042)	output_log(IDS_STRING5042, tmp_value);
		goto GOTO;
	}

	//��r�ļ�
	__matrix_zero_Memory(tmp_value, sizeof(tmp_value));
	size = __matrix_sprintf_s(tmp_value, __TEXT("%s.r"), path);
	tmp_value[size] = 0x0; 
	file_handle = CreateFile(tmp_value, GENERIC_READ, FILE_SHARE_READ, NULL, 
							OPEN_EXISTING, FILE_ATTRIBUTE_READONLY, NULL);
	if(file_handle == INVALID_HANDLE_VALUE)
	{	set_last_error(IDS_STRING5026); output_log(IDS_STRING5026, tmp_value);	is_ok = APP_FAULT;	goto GOTO;}
	else{	is_ok = read_lines(file_handle, sps_file_line_ptr);	if(is_ok == APP_FAULT) goto GOTO;}
	
	relation_record_ptr = sps_data_ptr->head_relation_records_ptr_;
	while(relation_record_ptr != NULL){
		
		loop = (relation_record_ptr->to_receiver_ - relation_record_ptr->from_receiver_) / 
				(relation_record_ptr->to_channel_ - relation_record_ptr->from_channel_ -1);
		for(i = relation_record_ptr->from_receiver_; i <= relation_record_ptr->to_receiver_; i += loop){

			param.receiver_line_name_ = relation_record_ptr->receiver_line_name_;
			param.receive_point_num_ = i;
			param.relation_record_ptr_ = relation_record_ptr;
			is_ok = read_receiver_option(sps_file_line_ptr, &param);
			if(is_ok == APP_FAULT)	goto GOTO;
		}
		relation_record_ptr = relation_record_ptr->next_;
	}

GOTO:
	free_sps_line_list(sps_file_line_ptr);
	if(file_handle != INVALID_HANDLE_VALUE)	CloseHandle(file_handle);

	return is_ok;
}

int free_sps_data_memory(__in__ SPS_DATA_INFO_PTR sps_data_ptr)
{
	int is_ok = APP_SUCCESS;
	SPS_RELATION_RECORD_SPEC_PTR	relation_record_ptr = NULL,
									tmp_relation_record_ptr = NULL;

	SPS_POINT_RECORD_SPEC_PTR		point_record_ptr = NULL,
									tmp_point_record_ptr = NULL;

	relation_record_ptr = sps_data_ptr->head_relation_records_ptr_;
	while(relation_record_ptr != NULL){

		tmp_relation_record_ptr = relation_record_ptr;
		point_record_ptr = relation_record_ptr->head_receiver_point_ptr_;
		while(point_record_ptr != NULL){
			tmp_point_record_ptr = point_record_ptr;
			point_record_ptr = point_record_ptr->next_;
			free(tmp_point_record_ptr);
		}

		relation_record_ptr = relation_record_ptr->next_;
		free(tmp_relation_record_ptr);
	}	

	return is_ok;
}

