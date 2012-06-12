/**
@brief	���ļ�Ϊ����ȫ�����ݴ�����ʵ���ļ�
@details	
@file	data.base.cpp
@note	
@see	
@version	
@author	kuoxin	
@bug
*/
#pragma once

#include <vector>
#include <map>

namespace matrix_data{

#define ZOOM_IN_RATE	2.0f
#define ZOOM_OUT_RATE	0.5f

enum __enuCONST_VALUE
{
	MAX_DESCRIPTION_STRING_SIZE = 260,
};

//device Limit(instrument & sensor)
class  device_limit
{
public:
	device_limit()	{ clear();	};
	~device_limit(){};

	void clear(){
		m_uiNb = 0x0;
		m_fLimit = 0.0;
		m_uiTestType = 0x0;
		m_uiTestAim = 0x0;
		ZeroMemory(m_pcUnit, sizeof(m_pcUnit));
		ZeroMemory(m_pcDescr, sizeof(m_pcDescr));
	}

public:
	unsigned int m_uiNb; //!<�����ţ�ֻ����
	char m_pcDescr[MAX_DESCRIPTION_STRING_SIZE]; //!<����������������INSTRUMENT NOISE��ֻ����
	char m_pcUnit[MAX_DESCRIPTION_STRING_SIZE];//!<	��λ��ֻ��������%
	unsigned int m_uiTestAim;
	unsigned int m_uiTestType;//!<�������ʹ��루ֻ����
	float m_fLimit;//!<����ֵ

public: // operator function
	device_limit& operator=(device_limit const& dl){
		if(this == &dl) return *this;
		m_fLimit = dl.m_fLimit;
		CopyMemory(m_pcDescr, dl.m_pcDescr, sizeof(m_pcDescr));
		CopyMemory(m_pcUnit, dl.m_pcUnit, sizeof(m_pcUnit));
		m_uiNb = dl.m_uiNb;
		m_uiTestAim = dl.m_uiTestAim;
		m_uiTestType = dl.m_uiTestType;
		return *this;
	};

public: //friend function
	friend bool operator==(const device_limit& left,	const device_limit& right);
};

//�첨����Ϣ
class  sensor_info
{
public:
	sensor_info(){clear();};
	sensor_info(sensor_info const& si){*this = si;};
	~sensor_info(){};
	void clear(){
		type_ = 0x0;
		resistance_ = 0x0;
		resistance_check_ = 0x0;
		tilt_ = 0x0;
		tilt_check_ = 0x0;
		tilt_model_ = 0x0;
		tilt_model_check_ = 0x0;
		noise_ = 0x0;
		noise_check_ = 0x0;
		leakage_ = 0x0;
		leakage_check_ = 0x0;
		field_check_ = 0x0;
		noise_monitor_check_ = 0x0;
		noise_monitor_ = 0x0;
		check_all_ = 0x0;
	};
public://operator function
	sensor_info& operator=(sensor_info const& si){
		if(this == &si) return *this;
		type_ = si.type_;
		resistance_ = si.resistance_;
		resistance_check_ = si.resistance_check_;
		tilt_ = si.tilt_;
		tilt_check_ = si.tilt_check_;
		noise_ = si.noise_;
		noise_check_ = si.noise_check_;
		leakage_ = si.leakage_;
		leakage_check_ = si.leakage_check_;
		tilt_model_ = si.tilt_model_;
		tilt_model_check_ = si.tilt_model_check_;
		field_check_ = si.field_check_;
		noise_monitor_check_ = si.noise_monitor_check_;
		noise_monitor_ = si.noise_monitor_;
		check_all_ = 0x0;
		return *this;
	};
public: //friend function
	friend bool operator==(const sensor_info& left,	const sensor_info& right);
public:
	//�첨������(�첨����)
	unsigned int type_;
	// �첨���迹
	float resistance_;
	byte resistance_check_;
	// ���½�ϼ첨����б�Ȱٷֱ�
	float tilt_;
	byte tilt_check_;
	// ���RMS������ƽ
	float noise_;
	byte noise_check_;
	// ©����Բ�������������֮�������©�����
	float leakage_;
	byte leakage_check_;
	float tilt_model_;
	byte tilt_model_check_;
	byte field_check_;
	byte noise_monitor_check_;
	float noise_monitor_;
	byte check_all_;
};

//�첨������
class  sensor_type
{
public:
	sensor_type(){clear();};
	~sensor_type(){};
	void clear(){
		nb_ = 0x0;
		continuity_max = 0x0;
		continuity_min_ = 0x0;
		tilt_ = 0x0;
		noise_ = 0x0;
		leakage_ = 0x0;
		ZeroMemory(label_, sizeof(label_));
		segd_code_ = 0x0;
	};
public://operator function
	sensor_type& operator=(sensor_type const& si){
		if(this == &si) return *this;
		nb_ = si.nb_;
		CopyMemory(label_, si.label_, sizeof(label_));
		continuity_min_ = si.continuity_min_;
		continuity_max = si.continuity_max;
		tilt_ = si.tilt_;
		noise_ = si.noise_;
		leakage_ = si.leakage_;
		segd_code_ = si.segd_code_;
		return *this;
	};
public: //friend function
	friend bool operator==(const sensor_type& left,	const sensor_type& right);
public:
	// �첨����
	unsigned int nb_;
	// ��ǩ����Sensor1
	char label_[MAX_DESCRIPTION_STRING_SIZE];
	// �첨���迹������
	float continuity_min_;
	// �첨���迹������
	float continuity_max;
	// ���½�ϼ첨����б�Ȱٷֱ�
	float tilt_;
	// ���RMS������ƽ
	float noise_;
	// ©����Բ�������������֮�������©�����
	float leakage_;
	// SEGD����
	unsigned int segd_code_;
};

//device info for fdu, aux, lci
class device_info
{
public:
	typedef std::vector<sensor_info> sensor_info_vector;
	typedef const std::vector<sensor_info> cosnt_sensor_info_vector;
public:
	device_info(){clear();};
	device_info(device_info const& di){*this = di;};
	~device_info(){};
	void clear(){
		sn_ =0x0;
		line_index_ = 0x0;
		section_index_ = 0x0;
		m_iPointIndex = 0x0;
		m_uiLineNb = 0x0;
		m_uiPointNb = 0x0;
		ip_ = 0x0;
		m_bJumpedChannel = false;
		m_bSensor = false;
		m_bAux = false;
		m_bBlastMachine = false;
		m_bDetour = false;
		m_bDetourMarkerLow = false;
		m_bDetourMarkerHigh = false;
		m_bStopMarking = false;
		m_bMarker = false;
		m_bMute = false;
		m_uiSNCrossDown = 0x0;
		m_uiSNCrossTop = 0x0;
		m_uiSNInstrumentLeft = 0x0;
		m_uiSNInstrumentRight = 0x0;
		m_fNoiseValue = 0x0;
		m_byNoiseCheck = 0;
		m_fDistortionValue = 0x0;
		m_byDistortionCheck = 0;
		m_fCrosstalkValue = 0x0;
		m_byCrosstalkCheck = 0;
		m_fGainValue = 0x0f;
		m_byGainCheck = 0;
		m_fPhaseValue = 0x0;
		m_byPhaseCheck = 0x0;
		m_fCMRRValue = 0x0;
		m_byCMRRCheck = 0;
		m_byCheck = 0;
		sensors_.clear();
	};
public: // operator function
	device_info& operator=(device_info const& di){
		if(this == &di) return *this;
		sn_ = di.sn_;
		line_index_ = di.line_index_;
		section_index_ = di.section_index_;
		m_iPointIndex = di.m_iPointIndex;
		m_uiLineNb = di.m_uiLineNb;
		m_uiPointNb = di.m_uiPointNb;
		ip_ = di.ip_;
		m_bJumpedChannel = di.m_bJumpedChannel;
		m_bSensor = di.m_bSensor;
		m_bAux = di.m_bAux;
		m_bBlastMachine = di.m_bBlastMachine;
		m_bDetour = di.m_bDetour;
		m_bDetourMarkerLow = di.m_bDetourMarkerLow;
		m_bDetourMarkerHigh = di.m_bDetourMarkerHigh;
		m_bStopMarking = di.m_bStopMarking;
		m_bMarker = di.m_bMarker;
		m_bMute = di.m_bMute;
		m_uiSNCrossDown = di.m_uiSNCrossDown;
		m_uiSNCrossTop = di.m_uiSNCrossTop;
		m_uiSNInstrumentLeft = di.m_uiSNInstrumentLeft;
		m_uiSNInstrumentRight = di.m_uiSNInstrumentRight;
		m_fNoiseValue = di.m_fNoiseValue;
		m_byNoiseCheck = di.m_byNoiseCheck;
		m_fDistortionValue = di.m_fDistortionValue;
		m_byDistortionCheck = di.m_byDistortionCheck;
		m_fCrosstalkValue = di.m_fCrosstalkValue;
		m_byCrosstalkCheck = di.m_byCrosstalkCheck;
		m_fGainValue = di.m_fGainValue;
		m_byGainCheck = di.m_byGainCheck;
		m_fPhaseValue = di.m_fPhaseValue;
		m_byPhaseCheck = di.m_byPhaseCheck;
		m_fCMRRValue = di.m_fCMRRValue;
		m_byCMRRCheck = di.m_byCMRRCheck;
		m_byCheck = di.m_byCheck;
		sensors_ = di.sensors_;
		return *this;
	};
public: //friend function
	friend bool operator==(const device_info& left,	const device_info& right);
public:
	int sn_; //!<�豸SN
	int line_index_;//!<�к�
	int section_index_;//!<�����
	/** ����*/
	int m_iPointIndex;
	/** ����ߺ�*/
	unsigned int m_uiLineNb;
	/** ��ǵ��*/
	int m_uiPointNb;
	int ip_;//!<IP��ַ
	/** �Ƿ�������*/
	bool m_bJumpedChannel;
	/** �Ƿ����Ӽ첨��*/
	bool m_bSensor;
	/** �Ƿ�����*/
	bool m_bAux;
	/** �Ƿ����ӱ�ը��*/
	bool m_bBlastMachine;
	/** �Ƿ��ػص�*/
	bool m_bDetour;
	/** �Ƿ��ػص��Ͷ˱�ǵ�*/
	bool m_bDetourMarkerLow;
	/** �Ƿ��ػص��߶˱�ǵ�*/
	bool m_bDetourMarkerHigh;
	/** �Ƿ��ػص�ֹͣ���*/
	bool m_bStopMarking;
	/** �Ƿ��ǵ�*/
	bool m_bMarker;
	/** �Ƿ��Ƶ�*/
	bool m_bMute;
	/** ���ӵĽ���վ �Ϸ�*/
	unsigned int m_uiSNCrossTop;
	/** ���ӵĽ���վ �·�*/
	unsigned int m_uiSNCrossDown;
	/** ���ӵ����� ��*/
	unsigned int m_uiSNInstrumentLeft;
	/** ���ӵ����� �ҷ�*/
	unsigned int m_uiSNInstrumentRight;
	/** ������������ֵ*/
	float m_fNoiseValue;
	/** �����������Խ�� 0��δ���ԣ�1�����Ժϸ�2�����Բ��ϸ�3�����ź�*/
	byte m_byNoiseCheck;
	/** �����������ֵ*/
	float m_fDistortionValue;
	/** ����������Խ�� 0��δ���ԣ�1�����Ժϸ�2�����Բ��ϸ�3�����ź�*/
	byte m_byDistortionCheck;
	/** ������������ֵ*/
	float m_fCrosstalkValue;
	/** �����������Խ�� 0��δ���ԣ�1�����Ժϸ�2�����Բ��ϸ�3�����ź�*/
	byte m_byCrosstalkCheck;
	/** �����������ֵ*/
	float m_fGainValue;
	/** ����������Խ�� 0��δ���ԣ�1�����Ժϸ�2�����Բ��ϸ�3�����ź�*/
	byte m_byGainCheck;
	/** ������λ����ֵ*/
	float m_fPhaseValue;
	/** ������λ���Խ�� 0��δ���ԣ�1�����Ժϸ�2�����Բ��ϸ�3�����ź�*/
	byte m_byPhaseCheck;
	/** ������ģ����ֵ*/
	float m_fCMRRValue;
	/** ������ģ���Խ�� 0��δ���ԣ�1�����Ժϸ�2�����Բ��ϸ�3�����ź�*/
	byte m_byCMRRCheck;
	/** �������Խ�� 0��δ���ԣ�1�����Ժϸ�2�����Բ��ϸ�3�����ź�*/
	byte m_byCheck;
	sensor_info_vector sensors_;
};

//data center
class data_base
{
public:
	typedef sensor_info	sensor;
	typedef device_info::sensor_info_vector	sensor_vector;	
	typedef device_limit instrument_limit;
	typedef device_limit sensor_limit;
	typedef std::vector<instrument_limit> instrument_limit_vector;
	typedef std::vector<sensor_limit> sensor_limit_vector;
	typedef std::map<int, device_info> device_info_map;
	typedef std::map<int /*nPointNB * 10000 + line_num*/, int /*SN*/> point_nb_to_sn_map;
	typedef std::map<int /*ip*/, int /*sn*/> ip_to_sn_map;
	typedef sensor_type sensor_type;
	typedef std::vector<sensor_type> sensor_type_vector;
public:
	data_base(void);
	virtual ~data_base(void);

private:
	data_base(data_base const& db){*this = db;};
	data_base& operator=(data_base const& db){
		if(this == &db) return *this;
		devices_info_ = db.devices_info_;
		sensor_limits_ = db.sensor_limits_;
		instrument_limits_ = db.instrument_limits_;
		point_nb_to_sn_map_ = db.point_nb_to_sn_map_;
		sensor_type_vector_ = db.sensor_type_vector_;
		return *this;
	}

private:
	instrument_limit_vector instrument_limits_; //!<instrument test base limit
	sensor_limit_vector sensor_limits_;//!< sensor test base limit
	device_info_map devices_info_;//!<device info map for fdu, lci, aux
	unsigned int line_number_; //!< ����������
	unsigned int section_number_;//!< ��������������
	point_nb_to_sn_map point_nb_to_sn_map_;//!< �ߺ�+ ���* 1000��SN��Ӧ��ϵ
	ip_to_sn_map ip_to_sn_map_;//����IP��ַ����sn
	sensor_type_vector sensor_type_vector_;//�첨������
	friend class data_base_helper;
};
}; //namespace matrix_data
