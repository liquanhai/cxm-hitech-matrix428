
#include <list>
#include <map>
using std::list;
using std::map;
/**
* @struct Survery_Struct
* @brief Survery SETUP�ṹ��
*/
typedef struct Survery_Struct
{
	/** ���ߺ�*/
	unsigned int m_uiLine;
	/** ����*/
	unsigned short m_usReceiverSectionSize;
	/** ��������+�첨�����ͣ���100-103p1*/
	char* m_pcReceiverSection;
}m_oSurveryStruct;

/**
* @struct PointCode_Struct
* @brief Point Code SETUP�ṹ��
*/
typedef struct PointCode_Struct
{
	/** �������*/
	unsigned int m_uiNb;
	/** ����*/
	unsigned short m_usLabelSize;
	/** ��ǩ����PointCode1*/
	char* m_pcLabel;
	/** ����*/
	unsigned short m_usSensorTypeSize;
	/** �첨�����ͣ���s1+cs*/
	char* m_pcSensorType;
}m_oPointCodeStruct;

/**
* @struct Sensor_Struct
* @brief Sensor SETUP�ṹ��
*/
typedef struct Sensor_Struct
{
	/** �첨����*/
	unsigned int m_uiNb;
	/** ����*/
	unsigned short m_usLabelSize;
	/** ��ǩ����Sensor1*/
	char* m_pcLabel;
	/** �첨���迹������*/
	float m_fContinuityMin;
	/** �첨���迹������*/
	float m_fContinuityMax;
	/** ���½�ϼ첨����б�Ȱٷֱ�*/
	float m_fTilt;
	/** ���RMS������ƽ*/
	float m_fNoise;
	/** ©����Բ�������������֮�������©�����*/
	float m_fLeakage;
	/** SEGD����*/
	unsigned int m_uiSEGDCode;
}m_oSensorStruct;

/**
* @struct Marker_Struct
* @brief Marker SETUP�ṹ��
*/
typedef struct Marker_Struct
{
	/** �������ͣ�1-����վ��2-��Դվ��3-�ɼ�վ*/
	unsigned int m_uiBoxType;
	/** ����SN*/
	unsigned int m_uiSN;
	/** ���ߺ�*/
	unsigned int m_uiLineName;
	/** ����*/
	unsigned int m_uiPointNb;
	/** �����*/
	unsigned int m_uiChannelNb;
	/** ��ǵ�����*/
	unsigned int m_uiMarkerIncr;
	/** ��ת��ǣ�0-����ת��1-��ת*/
	unsigned int m_uiReversed;
}m_oMarkerStruct;

/**
* @struct Aux_Struct
* @brief Aux SETUP�ṹ��
*/
typedef struct Aux_Struct
{
	/** �����ţ���Instrument�����е�Auxiliary Descr��Ӧ*/
	unsigned int m_uiNb;
	/** ����*/
	unsigned short m_usLabelSize;
	/** ��ǩ����pilot*/
	char* m_pcLabel;
	/** �������ͣ�1-����վ��2-��Դվ��3-�ɼ�վ*/
	unsigned int m_uiBoxType;
	/** ����SN*/
	unsigned int m_uiSN;
	/** �����*/
	unsigned int m_uiChannelNb;
	/** ���棬1600mv��400mv*/
	unsigned int m_uiGain;
	/** DPG���*/
	unsigned int m_uiDpgNb;
	/** ����*/
	unsigned short m_usCommentsSize;
	/** ע�ͣ���Comments1*/
	char* m_pcComments;
}m_oAuxStruct;

/**
* @struct Detour_Struct
* @brief Detour SETUP�ṹ��
*/
typedef struct Detour_Struct
{
	/** �Ͷ��������ͣ�1-����վ��2-��Դվ��3-�ɼ�վ*/
	unsigned int m_uiLowBoxType;
	/** �Ͷ�����SN*/
	unsigned int m_uiLowSN;
	/** �Ͷ˲����*/
	unsigned int m_uiLowChanNb;
	/** �߶��������ͣ�1-����վ��2-��Դվ��3-�ɼ�վ*/
	unsigned int m_uiHighBoxType;
	/** �߶�����SN*/
	unsigned int m_uiHighSN;
	/** �߶˲����*/
	unsigned int m_uiHighChanNb;
	/** ֹͣ��ǣ�0-������ǣ�1-ֹͣ���*/
	unsigned int m_uiStopMarking;
}m_oDetourStruct;

/**
* @struct Mute_Struct
* @brief Mute SETUP�ṹ��
*/
typedef struct Mute_Struct
{
	/** ���ߺ�*/
	unsigned int m_uiLineName;
	/** ����*/
	unsigned int m_uiPointNb;
}m_oMuteStruct;

/**
* @struct BlastMachine_Struct
* @brief BlastMachine SETUP�ṹ��
*/
typedef struct BlastMachine_Struct
{
	/** ������*/
	unsigned int m_uiNb;
	/** ����*/
	unsigned short m_usLabelSize;
	/** ��ǩ����pilot*/
	char* m_pcLabel;
	/** �������ͣ�1-����վ��2-��Դվ��3-�ɼ�վ*/
	unsigned int m_uiBoxType;
	/** ����SN*/
	unsigned int m_uiSN;
	/** �����*/
	unsigned int m_uiChannelNb;
	/** ���棬1600mv��400mv*/
	unsigned int m_uiGain;
	/** DPG���*/
	unsigned int m_uiDpgNb;
	/** ����*/
	unsigned short m_usCommentsSize;
	/** ע�ͣ���Comments1*/
	char* m_pcComments;
}m_oBlastMachineStruct;

/**
* @struct Absolute_Struct
* @brief Absolute Spread SETUP�ṹ��
*/
typedef struct Absolute_Struct
{
	/** ������*/
	unsigned int m_uiNb;
	/** ����*/
	unsigned short m_usLabelSize;
	/** ��ǩ����Absolute1*/
	char* m_pcLabel;
	/** ����*/
	unsigned short m_usAbsoluteSpreadSize;
	/** �������У���1:1-127������������ʼ����-��ֹ���ţ�*/
	char* m_pcAbsoluteSpread;
}m_oAbsoluteStruct;

/**
* @struct Generic_Struct
* @brief Generic Spread SETUP�ṹ��
*/
typedef struct Generic_Struct
{
	/** ������*/
	unsigned int m_uiNb;
	/** ����*/
	unsigned short m_usLabelSize;
	/** ��ǩ����Generic1*/
	char* m_pcLabel;
	/** ����*/
	unsigned short m_usLineSize;
	/** ��ͨ�������ͣ���50��g1+g2����50�Ե��������һ�����������Ϊ0Db,�ڶ���Ϊ12dB��*/
	char* m_pcLine;
	/** ����*/
	unsigned short m_usSpreadSize;
	/** ��ͨ���У���10(l1+ls)��10�Բ��ߣ���һ������ΪLine�ж����l1���ͣ��ڶ�����������*/
	char* m_pcSpread;
}m_oGenericStruct;

/**
* @struct Look_Struct
* @brief Look SETUP�ṹ��
*/
typedef struct Look_Struct
{
	/** �Զ��鿴�Ƿ����������豸��1-�Զ��鿴��2-�ֶ��鿴*/
	unsigned int m_uiAutoLook;
	/** �첨��������ԣ�1-���ԣ�2-������*/
	unsigned int m_uiResistance;
	/** �첨����б�Ȳ��ԣ�1-���ԣ�2-������*/
	unsigned int m_uiTilt;
	/** �첨��©����ԣ�1-���ԣ�2-������*/
	unsigned int m_uiLeakage;
}m_oLookStruct;

/**
* @struct LAULeakage_Struct
* @brief LAULeakage SETUP�ṹ��
*/
typedef struct LAULeakage_Struct
{
	/** ����ֵ*/
	unsigned int m_uiLimit;
}m_oLAULeakageStruct;

/**
* @struct FormLine_Struct
* @brief Form Line SETUP�ṹ��
*/
typedef struct FormLine_Struct
{
	/** ������*/
	unsigned int m_uiNb;
	/** �������ͣ�1-����վ��2-��Դվ��3-�ɼ�վ*/
	unsigned int m_uiBoxType;
	/** ����SN*/
	unsigned int m_uiSN;
}m_oFormLineStruct;

/**
* @struct Instrument_SensorTestBase_Struct
* @brief Instrument Sensor Test base SETUP�ṹ��
*/
typedef struct Instrument_SensorTestBase_Struct
{
	unsigned int m_uiTestAim;
	unsigned int m_uiNb;	/**�����ţ�ֻ����*/
	unsigned short m_usDescrSize; /**m_pcDescr ��С*/
	char* m_pcDescr; /**����������������INSTRUMENT NOISE��ֻ����*/
	unsigned int m_uiTestType;/**�������ʹ��루ֻ����*/
	unsigned int m_uiADC;/**0-Close��1-Inner��2-Out	*/
	unsigned int m_uiGain;/**���棬1600mv��400mv*/
	unsigned int m_uiDAC;/**0-Close���رգ���1-Inner�����ӵ��ڲ��������磩��2-Out�����ӵ��첨���ĵ�·����ˣ�*/	
	unsigned int m_uiFilter;/**�˲������ͣ�1-0.8LIN��2-0.8MIN*/
	unsigned int m_uiSamplingRate; /**��us��������*/
	unsigned int m_uiSamplingLength;/**��ms����������*/
}m_oInstrumentTestBaseStruct, m_oSensorTestBaseStruct;

/**
* @struct Instrument_SensorTestLimit_Struct
* @brief Instrument Sensor Test Limit SETUP�ṹ��
*/
typedef struct Instrument_SensorTestLimit_Struct
{
	unsigned int m_uiNb; /**�����ţ�ֻ����*/
	unsigned short m_usDescrSize; /**m_pcDescr ��С*/
	char* m_pcDescr; /**����������������INSTRUMENT NOISE��ֻ����*/
	unsigned short m_usUnitSize; /**	��λ size*/
	char* m_pcUnit;/**	��λ��ֻ��������%*/
	unsigned int m_uiTestAim;
	unsigned int m_uiTestType;/**�������ʹ��루ֻ����*/
	float m_fLimit;/**����ֵ*/
}m_oInstrumentTestLimitStruct, m_oSensorTestLimitStruct;

/**
* @struct InstrumentTest_Struct
* @brief Instrument Test SETUP�ṹ��
*/
typedef struct InstrumentTest_Struct
{
	unsigned int m_uiNb; /**�����ţ�ֻ����*/
	unsigned int m_uiTestType;/**�������ʹ��루ֻ����*/
	unsigned int m_uiGain;/**���棬1600mv��400mv*/
	unsigned m_uiRecordLength; /**��¼ʱ��*/
	unsigned m_uiRecorded; /**�Ƿ��¼�������ݣ�0-����¼��1-��¼*/
	unsigned short m_usAuxiliaryDescrSize; /**���������� ��С*/
	char* m_pcAuxiliaryDescr; /**��������������a1-a3*/
	unsigned short m_usAbsoluteSpreadSize; /**�������� ��С*/
	char* m_pcAbsoluteSpread; /**�������У���1:10-20*/
}m_oInstrumentTestStruct;

/**
* @struct SensorTest_Struct
* @brief Sensor Test SETUP�ṹ��
*/
typedef struct SensorTest_Struct
{
	unsigned int m_uiNb; /**�����ţ�ֻ����*/
	unsigned int m_uiTestType;/**�������ʹ��루ֻ����*/
	unsigned m_uiRecorded; /**�Ƿ��¼�������ݣ�0-����¼��1-��¼*/
	unsigned short m_usAbsoluteSpreadSize; /**�������� ��С*/
	char* m_pcAbsoluteSpread; /**�������У���1:10-20*/
}m_oSensorTestStruct;

/**
* @struct MultipleTestKey_Struct
* @brief Multiple Test SETUP�ṹ��
*/
typedef struct MultipleTestKey_Struct
{
	unsigned int m_uiNb; /**�����ţ�ֻ����*/
	unsigned short m_usTestNameSize;
	char* m_pcTestName;/**������Ŀ���ƣ���Test1*/
	unsigned short m_usAuxiliaryDescrSize; /**���������� ��С*/
	char* m_pcAuxiliaryDescr; /**��������������a1-a3*/
	unsigned short m_usAbsoluteSpreadSize; /**�������� ��С*/
	char* m_pcAbsoluteSpread; /**�������У���1:10-20*/
	unsigned int m_uiDelayBetweenTest;/**(ms)ÿ�β���֮��ļ��*/
	unsigned int m_uiRecordResults;/**	�Ƿ��¼�������ݣ�0-����¼��1-��¼*/
	unsigned int m_uiRecordLength; /**(ms)���Լ�¼ʱ��*/
	unsigned int m_uiTestFileNb;/**�ļ����*/
	bool operator < (const MultipleTestKey_Struct& rhs) const
	{
		return (m_uiNb < rhs.m_uiNb);
	}
}m_oMultipleTestKeyStruct;

/**
* @struct MultipleTestTask_Struct
* @brief Multiple Test Task�ṹ��
*/
typedef struct MultipleTestTask_Struct
{
	unsigned int m_uiLineNb;/**���ߺ�*/
	unsigned int m_uiTestType;/**�������ʹ���*/
	unsigned int m_uiGain;/**���棬1600mv��400mv*/
	unsigned int m_uiLoopLineNb;/**��Ҫ�ظ����еĲ���������*/
	unsigned int m_uiNbLoops;/**����ѭ������*/
}m_oMultipleTestTaskStruct;

/**
* @struct SeisMonitorTest_Struct
* @brief SeisMonitor Test�ṹ��
*/
typedef struct SeisMonitorTest_Struct
{
	unsigned short m_usAbsoluteSpreadSize; /**�������� ��С*/
	char* m_pcAbsoluteSpread; /**�������У���1:10-20*/
}m_oSeisMonitorStruct;

/**
* @struct LineSetupData_Struct
* @brief ���߿ͻ�����Ϣ�ṹ��
*/
typedef struct LineSetupData_Struct
{
	/** Survery*/
	list<m_oSurveryStruct> m_olsSurveryStruct;
	/** Point Code*/
	list<m_oPointCodeStruct> m_olsPointCodeStruct;
	/** Sensor*/
	list<m_oSensorStruct> m_olsSensorStruct;
	/** LAYOUT SETUP*/
	/** Marker*/
	list<m_oMarkerStruct> m_olsMarkerStruct;
	/** Aux*/
	list<m_oAuxStruct> m_olsAuxStruct;
	/** Detour*/
	list<m_oDetourStruct> m_olsDetourStruct;
	/** Mute*/
	list<m_oMuteStruct> m_olsMuteStruct;
	/** BlastMachine*/
	list<m_oBlastMachineStruct> m_olsBlastMachineStruct;
	/** �������к��ڵ������*/
	map<unsigned int, list<m_oAbsoluteStruct>> m_oAbsoluteStructMap;
	/** Generic*/
	list<m_oGenericStruct> m_olsGenericStruct;
	/** Look*/
	m_oLookStruct m_oLook;
	/** LAULeakage*/
	m_oLAULeakageStruct m_oLAULeakage;
	/** Form Line*/
	list<m_oFormLineStruct> m_olsFormLineStruct;
	/** Instrument Test base*/
	list<m_oInstrumentTestBaseStruct> m_olsInstrumentTestBaseStruct;
	/** Sensor Test base*/
	list<m_oSensorTestBaseStruct> m_olsSensorTestBaseStruct;
	/** Instrument Limit*/
	list<m_oInstrumentTestLimitStruct> m_olsInstrumentTestLimitStruct;
	/** Sensor Limit*/
	list<m_oSensorTestLimitStruct> m_olsSensorTestLimitStruct;
	/** Instrument Test*/
	list<m_oInstrumentTestStruct> m_olsInstrumentTestStruct;
	/** Sensor Test*/
	list<m_oSensorTestStruct> m_olsSensorTestStruct;
	/** Multiple Test*/
	map<m_oMultipleTestKeyStruct, list<m_oMultipleTestTaskStruct>> m_oMultpleTestStructMap;
	/** SeisMonitor*/
	m_oSeisMonitorStruct m_oSeisMonitor;
}m_oLineSetupDataStruct;
