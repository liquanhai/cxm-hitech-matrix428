/**
@brief	SPS�ļ����ݽṹ
@details ���ļ����������й�SPS�����ݽṹ��Ϣ
@file	sps.header.h
@note	
@see	�й�SPS����,�μ�SPS��׼(Transcriber 2 SPS Format; e428XL V4.0 VOL.2, 
@version	1.0.0.1.2011.11.16
@author	kuoxin	
@bug
*/

/**
@struct __tagSPS_POINT_RECORD_SPEC
@brief SPS���¼�ṹ����д��SPS�е�S��R�ļ�,������ΪԪ���ݽṹ
*/
typedef __tagSPS_POINT_RECORD_SPEC_PRIVATE
{
	char	record_id_;			//!< 1 Record identification 1 A1 'R' or 'S' None
	char	line_name_[16 + 1];		//!< 2 Line name (left adj) 2-17 16A1 Free None
	char	point_number_[8 + 1];	//!< 3 Point number (right adj)18-25 8A1 Free None -
	char	point_index_;		//!< 4 Point index 26 A1 '1' to 'A' '1' -
	char	point_code_[2 + 1];		//!< 5 Point code 27-28 A2 see below * None -
	char	static_correction_[4 + 1];	//!< 6 Static correction 29-32 I4 -999 - 999 Blank Msec
	char	point_depth_[4 + 1];		//!< 7 Point depth 33-36 F4.1 0 - 99.9 None Meter
	char	seismic_datum_[4 + 1];		//!< 8 Seismic datum 37-40 I4 -999 - 9999 None Meter
	char	uphole_[2 + 1];				//!< 9 Uphole time 41-42 I2 0 - 99 Blank Msec
	char	water_depth_[5 + 1];		//!< 10 Water depth 43-46 F4.1# 0 - 99.9/999 Blank Meter
	char	map_grid_easting_[9 + 1]	//!< 11 Map grid easting 47-55 F9.1 None -
	char	map_grid_northing_[10 + 1];	//!< 12 Map grid northing 56-65 F10.1 None -
	char	surface_elevation_[6 + 1];	//!< 13 Surface elevation 66-71 F6.1 -999.9 -9999.9 None Meter
	char	day_of_year_[3 + 1];		//!< 14 Day of year 72-74 I3 1 - 999 None -
	char	time_[6 + 1];				//!< 15 Time (hhmmss) 75-80 3I2 000000 - 235959 None
}SPS_POINT_RECORD_SPEC_PRIVATE, *SPS_POINT_RECORD_SPEC_PRIVATE_PTR;

/**
 * @typedef struct __tagSPS_POINT_RECORD_SPEC_PRIVATE SPS_POINT_RECORD_SPEC_PRIVATE, *SPS_POINT_RECORD_SPEC_PRIVATE_PTR;
 * @brief ������¼��ԭʼ���ݽṹ
*/

/**
@struct __tagSPS_POINT_RECORD_SPEC
@brief sps ���¼�ṹ��,�ýṹ������__tagSPS_POINT_RECORD_SPEC_PRIVATE�ķ���
*/
typedef struct __tagSPS_POINT_RECORD_SPEC
{
	unsigned		line_name_; //!< ������
	float			point_number_;//!< ����
	unsigned char	index_;	//!< ��Դ������
	char			point_code_[3]; //!< �����
	int				static_correction_; //!< ��̬����
	float			point_depth_; //!< �����
	int				seismic_datum_;//!< ��������
	unsigned short	uphole_time; //!< ����ʱ��
	float			water_depth_; //!< ˮ��
	double			easting_;	//!< ��Դƫ����	Ĭ��Ϊ GUI ���ã����ɷ��ڻ򵼺�ϵͳ����
	double			northing_;	//!< ��Դ����γ�Ȳ�	Ĭ��Ϊ GUI ���ã����ɷ��ڻ򵼺�ϵͳ����
	float			elevation_;	//!< ��Դ�߳�	Ĭ��Ϊ GUI ���ã����ɷ��ڻ򵼺�ϵͳ����
	int				day_of_year; //!< ������ ��ʽ: I3
	unsigned short	time_[3]; //!< ʱ��,��ʽ: hhmmss
//	__tagSPS_POINT_RECORD_SPEC* next_; //!< ��һ���ṹ��ָ��,����ʹ������
}SPS_POINT_RECORD_SPEC, *SPS_POINT_RECORD_SPEC_PTR;

/**
 * @typedef struct __tagSPS_POINT_RECORD_SPEC SPS_POINT_RECORD_SPEC, *SPS_POINT_RECORD_SPEC_PTR;
 * @brief ������¼
*/

/**
@struct __tagSPS_RELATION_RECORD_SPEC_PRIVATE
@brief sps ��ϵ��¼�ṹ���ԭʼ���ݽṹ
*/
typedef struct __tagSPS_RELATION_RECORD_SPEC_PRIVATE
{
	char	record_id_;							//!< 1 Record identification 1 A1 'X' None -
	char	field_tape_number_[6 + 1];			//!< 2 Field tape number 2-7 6A1 Free None -
	char	field_record_number_[4 + 1];		//!< 3 Field record number 8-11 I4 0 - 9999 None -
	unsigned char	field_record_increment_;	//4 Field record increment 12 A1 '1' to 'Z' '1' -
	unsigned char	instrument_code_;			//!< 5 Instrument code 13 A1 '1' to 'A' '1' -
	char	shot_line_name_[16 + 1];			//!< 6 Line name (left adj) 14-29 16A1 Free None -
	char	point_number_[8 + 1];				//!< 7 Point number (right adj) 30-37 8A1 Free None -
	char	point_index_;						//!< 8 Point index 38 A1 '1' to 'Z' '1' -
	char	from_channel_[4 + 1];				//!< 9 From channel 39-42 I4 0 - 9999 None -
	char	to_channel_[4 + 1];					//!< 10 To channel 43-46 I4 0 - 9999 None -
	char	channel_increment_;					//!< 11 Channel increment 47 I1 1-9 1 -
	char	receiver_line_name_[16 + 1];		//!< 12 Line name (left adj) 48-63 16A1 Free None -
	char	from_receiver_[8 + 1];				//!< 13 From receiver (right adj) 64-71 8A1 Free None -
	char	to_receiver_[8 + 1];				//!< 14 To receiver (right adj) 72-79 8A1 Free None -
	char	receiver_index_;					//!< 15 Receiver index 80 A1 '1' to 'A' '1' -
}SPS_RELATION_RECORD_SPEC_PRIVATE, *SPS_RELATION_RECORD_SPEC_PRIVATE_PTR;

/**
 * @typedef struct __tagSPS_RELATION_RECORD_SPEC_PRIVATE SPS_RELATION_RECORD_SPEC_PRIVATE, *SPS_RELATION_RECORD_SPEC_PRIVATE_PTR
 * @brief ����sps��ϵ��¼Ԫ���ݽṹ
*/

/**
@struct __tagSPS_RELATION_RECORD_SPEC
@brief sps��ϵ��¼�ṹ��
*/
typedef struct __tagSPS_RELATION_RECORD_SPEC
{
	char	field_tape_number_[6 + 1]; //!< ����Ŵ���
	int	field_record_number_;//!< Ұ���¼��
	int	field_record_increment_;//!< Ұ���¼����
	int	instrument_code_;//!< ��������
	char	shot_line_name_[16 + 1]; //!< �ڵ��ߺ�����	
	char	point_number_[8 + 1];	//!< �ڵ��
	int	point_index_;				//!< �ڵ�����
	int	from_channel_;				//!< ��ʼ��¼����
	int to_channel_;				//!< ��ֹ��¼����
	int	channel_increment_;			//!< ������
	char	receiver_line_name_[16 + 1];//!< �����ߺţ�����룩
	int	from_receiver_;//!< ��ʼ���յ�ţ��Ҷ��룩
	int	to_receiver_;//!< ��ֹ���յ�ţ��Ҷ��룩
	int	receiver_index_;//!< ���յ�����
//	int	receiver_point_size_;//!< �������ݴ�С
//	SPS_POINT_RECORD_SPEC_PTR	head_receiver_point_ptr_;//!< ���ܵ�������Ϣ,��ֵΪָ��,�ڴ�ķ�����Ҫ���ɷ��������,ʹ�ú�,��Ҫɾ��
//	SPS_POINT_RECORD_SPEC_PTR	tail_receiver_point_ptr_;//!< ���ܵ�������Ϣ,��ֵΪָ��,�ڴ�ķ�����Ҫ���ɷ��������,ʹ�ú�,��Ҫɾ��
//	__tagSPS_RELATION_RECORD_SPEC* next_; //!< ��һ���ṹ��ָ��,����ʹ������
}SPS_RELATION_RECORD_SPEC, *SPS_RELATION_RECORD_SPEC_PTR;

/**
 * @typedef struct __tagSPS_RELATION_RECORD_SPEC SPS_RELATION_RECORD_SPEC, *SPS_RELATION_RECORD_SPEC_PTR
 * @brief ����sps��ϵ��¼�ṹ��
*/

