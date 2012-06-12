/**
@brief	��ȡSPS�ļ�,��ȡSEG-Dʹ�ò���
@details ����Ӧ��sps�ļ�,Ȼ������Ӧ�Ĳ���д��SEG-D������
@file	proc.sps.file.h
@note	ʵ�ּ�proc.sps.file.cpp
@see	�й�SPS����,�μ�SPS��׼
@version	1.1.6.20.2011.09.14
@author	kuoxin	
@bug
*/

/**
@struct __tagSPS_POINT_RECORD_SPEC
@brief sps ���¼�ṹ��
@note
	typedef struct __tagSPS_POINT_RECORD_SPEC SPS_POINT_RECORD_SPEC, *SPS_POINT_RECORD_SPEC_PTR;
*/
typedef struct __tagSPS_POINT_RECORD_SPEC
{
	unsigned	line_name_; //!< ������
	float		point_number_;//!< ����
	unsigned	index_;	//!< ��Դ������
	double		easting_;	//!< ��Դƫ����	Ĭ��Ϊ GUI ���ã����ɷ��ڻ򵼺�ϵͳ����
	double		northing_;	//!< ��Դ����γ�Ȳ�	Ĭ��Ϊ GUI ���ã����ɷ��ڻ򵼺�ϵͳ����
	float		elevation_;	//!< ��Դ�߳�	Ĭ��Ϊ GUI ���ã����ɷ��ڻ򵼺�ϵͳ����
	int			seismic_datum_;//!< �����׼��
	short		uphole_time_;//!< ����ʱ��
	__tagSPS_POINT_RECORD_SPEC* next_; //!< ��һ���ṹ��ָ��,����ʹ������
}SPS_POINT_RECORD_SPEC, *SPS_POINT_RECORD_SPEC_PTR;

/**
@struct __tagSPS_POINT_RECORD_SPEC
@brief sps ��ϵ��¼�ṹ��
@note
	typedef struct __tagSPS_RELATION_RECORD_SPEC SPS_RELATION_RECORD_SPEC, *SPS_RELATION_RECORD_SPEC_PTR;
*/
typedef struct __tagSPS_RELATION_RECORD_SPEC
{
	int	field_record_number_;//!< Ұ���¼��
	int	field_record_increment_;//!< Ұ���¼����
	int	instrument_code_;//!< ��������
	int	from_channel_;//!< ��ʼ��¼����
	int to_channel_;//!< ��ֹ��¼����
	int	channel_increment_;//!< ������
	int	receiver_line_name_;//!< �����ߺţ�����룩
	int	from_receiver_;//!< ��ʼ���յ�ţ��Ҷ��룩
	int	to_receiver_;//!< ��ֹ���յ�ţ��Ҷ��룩
	int	receiver_index_;//!< ���յ�����
	int	receiver_point_size_;//!< �������ݴ�С
	SPS_POINT_RECORD_SPEC_PTR	head_receiver_point_ptr_;//!< ���ܵ�������Ϣ,��ֵΪָ��,�ڴ�ķ�����Ҫ���ɷ��������,ʹ�ú�,��Ҫɾ��
	SPS_POINT_RECORD_SPEC_PTR	tail_receiver_point_ptr_;//!< ���ܵ�������Ϣ,��ֵΪָ��,�ڴ�ķ�����Ҫ���ɷ��������,ʹ�ú�,��Ҫɾ��
	__tagSPS_RELATION_RECORD_SPEC* next_; //!< ��һ���ṹ��ָ��,����ʹ������
}SPS_RELATION_RECORD_SPEC, *SPS_RELATION_RECORD_SPEC_PTR;

/**
@struct	__tagSPS_DATA_INFO
@brief	����SPS��Ϣ
@note
	ʹ�õ�h��Ϣ:
	H402Sample int.,Record Len.     1,1MSEC,6SEC;                                   
	H403Number of channels          1,200;                                          
	H404Tape type,format,density    1,Cartridge,SEGD,5745171;                       
	H405Filter_alias Hz,dB pnt,slope1,None;                                         
	H406Filter_notch Hz,-3dB points 1,None;                                         
	H407Filter_low Hz,dB pnt,slope  1,0.0Hz,0.0DB,0.0DB/OCT;   
	H600Type,model,polarity         G1,G_Land,SN7C-10Hz,SEG;                        

	s�ļ��еĵ���Ϣ:
	S691              23329.51V1                   509494.8 4782327.81269.9
	
	r�ļ��еĵ���Ϣ:
	R691                233291G1                   509481.8 4782309.61269.4

	x�ļ��еĵ���Ϣ:
	X          11691              23329.51   1 6001691                23030   236291
*/
typedef struct __tagSPS_DATA_INFO
{
	__in__ char_t const* sps_path_ptr_; //!< sps�ļ�·��
	__in__ float source_line_number_;	//!< ���ߺ�
	__in__ float source_point_number_;	//!< ��Դ���

	//����Hxxx��Ϣ
	__out__ unsigned	base_scan_interval_; //!< ����ɨ����
	__out__ unsigned	extended_record_length_;//!< ��չ��¼����
	__out__ unsigned	alias_filter_frequency_; //!< ����˲���Ƶ�� 
	__out__ unsigned	alias_filter_slope_; //!< ����˲���б�� 
	__out__ unsigned	low_cut_filter_;  //!< �ͽ��˲���Ƶ��
	__out__ unsigned	low_cut_filter_slope_;  //!< �ͽ��˲���б��
	__out__ unsigned	sample_length_;			//!< �ɼ�����1000 �� 128000����
	__out__ unsigned	sample_frequency_;		//!< ������250��500��1000��2000��4000 ΢��
	__out__ unsigned	sample_number_in_trace_;//!< ��¼����������Ŀ1 �� 128000
	__out__ unsigned	listen_time_;			//!< ����ʱ��	100 �� 128000 ����
	__out__ unsigned	scan_length_;			//!< ɨ�賤��	1000 �� 128000 ����
	__out__ unsigned	trace_total_number_;	//!< ��¼������1 �� 100000
	__out__ unsigned	auxiliary_trace_number_;//!< ��������Ŀ1 �� 100000
	__out__ unsigned	trace_number_;			//!< �����¼����Ŀ1 �� 100000

	__out__ SPS_POINT_RECORD_SPEC shot_point_;//!< ��Դ��Ϣ
	__out__ unsigned relation_records_size_; //!< ���߹�ϵ��¼��С
	__out__ SPS_RELATION_RECORD_SPEC_PTR head_relation_records_ptr_; //!< ��һ�����߹�ϵ��¼ָ��
	__out__ SPS_RELATION_RECORD_SPEC_PTR tail_relation_records_ptr_; //!< ���һ�����߹�ϵ��¼ָ��
}SPS_DATA_INFO, *SPS_DATA_INFO_PTR;

/**
@fn	int load_sps_file(__in_out__ SPS_DATA_INFO_PTR sps_data_ptr);
@brief	��鲢���������ļ���Ϣ��Ӧ�û�����
@param[in/out]	sps_data_ptr		��sps�ļ��еõ������ݽṹ
@return	����ɹ�����APP_SUCCESS, ���򷵻�APP_FAULT
@note
*/
int load_sps_file(__in_out__ SPS_DATA_INFO_PTR sps_data_ptr);


/**
@fn	int free_sps_data_memory(__in__ SPS_DATA_INFO_PTR sps_data_ptr)
@brief �ͷ�SPS_DATA_INFO���ݽṹ������ڴ� 	
@param[in/out]	sps_data_ptr	��sps�ļ��еõ������ݽṹ
@return	����ɹ�����APP_SUCCESS, ���򷵻�APP_FAULT
@note
*/
int free_sps_data_memory(__in__ SPS_DATA_INFO_PTR sps_data_ptr);
