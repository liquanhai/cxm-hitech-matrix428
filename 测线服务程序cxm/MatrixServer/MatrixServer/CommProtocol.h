
#ifndef _CommProtocol_H
#define _CommProtocol_H
/************************************************************************/
/* ��������                                                             */
/************************************************************************/
// ����SNλ��
#define InstrumentBytes						4
// �����������С������SNΪ0���ʾ������
#define InstrumentTableWindowSize			338
// ���Խ��λ��
#define TestResultBytes						1
// ���紫�������λ��
#define DataBytes							3
// ���ݱ������С
#define DataTableWindowSize					338
// C/S���ջ�������С
#define ServerRecBufferSize					8192000
// C/S���ͻ�������С
#define ServerSndBufferSize					8192000
// ������ӵĿͻ��˸���
#define ListenClientMaxNum					5
// ������ջ�������С
#define ServerRecBufSize					8192000
// ������֡�ṹ����
#define FrameStructNumMax					5800
// �̹߳رյĵȴ�ʱ��
#define CloseClientCommThreadTimes			500
// �߳�ִ�еļ��ʱ��
#define RunClientCommThreadTimes			100

/************************************************************************/
/* �����ֺ�ͨѶЭ��                                                     */
/************************************************************************/
// ��ѯĳ������ͻ���ֻ�跢���кź������
// �������������ź��кź��ټ�����������ֵ
// ��ѯ�����б�ĳ������4���ֽڵ��кź�4���ֽڵ�������ţ�

// Ӧ������λ������Ӧ�𣬽���������б�
#define CmdReturnBit						(0x0001 << 15)
// ��������Ϊ��������
#define CmdTypeSet							0x01
// ��������ΪӦ��
#define CmdTypeReturn						0x02
// TCP/IP֡������
#define FrameSizeLimit						1400
// ֡ͷ����
#define FrameHeadSize						4
// ֡������
#define FrameLengthSize						2
// ֡ͷ��Ϣ����
#define FrameHeadInfoSize					27
// ֡β����
#define FrameTailSize						1
// ֡��������
#define FrameInfoSizeLimit					(FrameSizeLimit-FrameHeadSize-FrameLengthSize-FrameHeadInfoSize-FrameTailSize)
// ֡ͷ
#define FrameHead1							0xaa
// ֡ͷ
#define FrameHead2							0xa5
// ֡ͷ
#define FrameHead3							0x5a
// ֡ͷ
#define FrameHead4							0x55
// ֡β
#define FrameTail							0xff
// ֡����ִ�н��-ִ�гɹ�
#define CmdResultSuccess					0x01
// ֡����ִ�н��-ִ��ʧ��
#define CmdResultFail						0x02
// ֡����ִ�н��-��Ҫ��ʱִ��
#define CmdResultDelay						0x03
// ֡����ִ�н��-�������Ѿ�ִ��
#define CmdResultDone						0x04
// ���Խ��-�ϸ�
#define TestResultQualified					0x01
// ���Խ��-���ϸ�
#define TestResultFailure					0x02
// ���Խ��-������
#define TestResultNull						0x03
// �ͻ��������˷�����֤��
#define CommCheck							"���̩���Ƽ����޹�˾"

// �ͻ��˵�½��֤��֡����Ϊ��֤�룩
#define CmdClientConnect					0x0001
// �ͻ����������֡����Ϊ�գ�
#define CmdSetHeartBeat						0x0002
// ��ѯ����������֡����Ϊ�к�+�����+����SN��SN = 0������������
#define CmdQueryWholeTable					0x0003
// ����Update Table��֡����Ϊ�к�+�����+����SN��SN = 0������������
#define CmdSendUpdateTable					0x0004
// �ϵ磨�����ֺ�֡����Ϊ�գ�����ֵΪִ��FieldOnʣ��ʱ�䣬Ϊ0��ʾ����ȴ���
#define CmdSetFieldOn						0x0005
// �ϵ磨�����ֺ�֡����Ϊ�գ�
#define CmdSetFieldOff						0x0006
// ��ѯ��ѡ����ȫ����Ϣ��֡����Ϊ����SN��ÿ4���ֽ�һ��������
#define CmdQueryInstrumentInfo				0x0007
// ��ѯȫ��������ȫ����Ϣ��Ӧ��֡����Ϊ�����ṹ�壩
#define CmdQueryInstrumentInfoAll			0x0008

// ��ѯ SurveyXML �ļ���Ϣ��֡����Ϊ�գ�
#define CmdQuerySurveyXMLInfo				0x1001
// ���� SurveyXML �ļ���Ϣ��֡����Ϊ��Ϣ�ṹ�壩
#define CmdSetSurveyXMLInfo					0x1002
// ��ѯ PointCode XML�ļ���Ϣ��֡����Ϊ�գ�
#define CmdQueryPointCodeXMLInfo			0x1003
// ���� PointCode XML�ļ���Ϣ��֡����Ϊ��Ϣ�ṹ�壩
#define CmdSetPointCodeXMLInfo				0x1004
// ��ѯ Sensor XML�ļ���Ϣ��֡����Ϊ�գ�
#define CmdQuerySensorXMLInfo				0x1005
// ���� Sensor XML�ļ���Ϣ��֡����Ϊ��Ϣ�ṹ�壩
#define CmdSetSensorXMLInfo					0x1006
// ��ѯ Marker XML�ļ���Ϣ��֡����Ϊ�գ�
#define CmdQueryMarkerXMLInfo				0x1007
// ���� Marker XML�ļ���Ϣ��֡����Ϊ��Ϣ�ṹ�壩
#define CmdSetMarkerXMLInfo					0x1008
// ��ѯ Aux XML�ļ���Ϣ��֡����Ϊ�գ�
#define CmdQueryAuxXMLInfo					0x1009
// ���� Aux XML�ļ���Ϣ��֡����Ϊ��Ϣ�ṹ�壩
#define CmdSetAuxXMLInfo					0x100a
// ��ѯ Detour XML�ļ���Ϣ��֡����Ϊ�գ�
#define CmdQueryDetourXMLInfo				0x100b
// ���� Detour XML�ļ���Ϣ��֡����Ϊ��Ϣ�ṹ�壩
#define CmdSetDetourXMLInfo					0x100c
// ��ѯ Mute XML�ļ���Ϣ��֡����Ϊ�գ�
#define CmdQueryMuteXMLInfo					0x100d
// ���� Mute XML�ļ���Ϣ��֡����Ϊ��Ϣ�ṹ�壩
#define CmdSetMuteXMLInfo					0x100e
// ��ѯ BlastMachine XML�ļ���Ϣ��֡����Ϊ�գ�
#define CmdQueryBlastMachineXMLInfo			0x100f
// ���� BlastMachine XML�ļ���Ϣ��֡����Ϊ��Ϣ�ṹ�壩
#define CmdSetBlastMachineXMLInfo			0x1010
// ��ѯ Absolute XML�ļ���Ϣ��֡����Ϊ�գ�
#define CmdQueryAbsoluteXMLInfo				0x1011
// ���� Absolute XML�ļ���Ϣ��֡����Ϊ��Ϣ�ṹ�壩
#define CmdSetAbsoluteXMLInfo				0x1012
// ��ѯ Generic XML�ļ���Ϣ��֡����Ϊ�գ�
#define CmdQueryGenericXMLInfo				0x1013
// ���� Generic XML�ļ���Ϣ��֡����Ϊ��Ϣ�ṹ�壩
#define CmdSetGenericXMLInfo				0x1014
// ��ѯ Look XML�ļ���Ϣ��֡����Ϊ�գ�
#define CmdQueryLookXMLInfo					0x1015
// ���� Look XML�ļ���Ϣ��֡����Ϊ��Ϣ�ṹ�壩
#define CmdSetLookXMLInfo					0x1016
// ��ѯ InstrumentTestBase XML�ļ���Ϣ��֡����Ϊ�գ�
#define CmdQueryInstrumentTestBaseXMLInfo	0x1017
// ���� InstrumentTestBase XML�ļ���Ϣ��֡����Ϊ��Ϣ�ṹ�壩
#define CmdSetInstrumentTestBaseXMLInfo		0x1018
// ��ѯ SensorTestBase XML�ļ���Ϣ��֡����Ϊ�գ�
#define	CmdQuerySensorTestBaseXMLInfo		0x1019
// ���� SensorTestBase XML�ļ���Ϣ��֡����Ϊ��Ϣ�ṹ�壩
#define	CmdSetSensorTestBaseXMLInfo			0x101a
// ��ѯ InstrumentTestLimit XML�ļ���Ϣ��֡����Ϊ�գ�
#define CmdQueryInstrumentTestLimitXMLInfo	0x101b
// ���� InstrumentTestLimit XML�ļ���Ϣ��֡����Ϊ��Ϣ�ṹ�壩
#define CmdSetInstrumentTestLimitXMLInfo	0x101c
// ��ѯ SensorTestLimit XML�ļ���Ϣ��֡����Ϊ�գ�
#define CmdQuerySensorTestLimitXMLInfo		0x101d
// ���� SensorTestLimit XML�ļ���Ϣ��֡����Ϊ��Ϣ�ṹ�壩
#define CmdSetSensorTestLimitXMLInfo		0x101e
// ��ѯ InstrumentTest XML�ļ���Ϣ��֡����Ϊ�գ�
#define CmdQueryInstrumentTestXMLInfo		0x101f
// ���� InstrumentTest XML�ļ���Ϣ��֡����Ϊ��Ϣ�ṹ�壩
#define CmdSetInstrumentTestXMLInfo			0x1020
// ��ѯ SensorTest XML�ļ���Ϣ��֡����Ϊ�գ�
#define CmdQuerySensorTestXMLInfo			0x1021
// SensorTest XML�ļ���Ϣ��֡����Ϊ��Ϣ�ṹ�壩
#define CmdSetSensorTestXMLInfo				0x1022
// ��ѯ MultipleTest XML�ļ���Ϣ��֡����Ϊ�գ�
#define CmdQueryMultipleTestXMLInfo			0x1023
// ���� MultipleTest XML�ļ���Ϣ��֡����Ϊ��Ϣ�ṹ�壩
#define CmdSetMultipleTestXMLInfo			0x1024
// ��ѯ SeisMonitorTest XML�ļ���Ϣ��֡����Ϊ�գ�
#define CmdQuerySeisMonitorTestXMLInfo		0x1025
// ���� SeisMonitorTest XML�ļ���Ϣ��֡����Ϊ��Ϣ�ṹ�壩
#define CmdSetSeisMonitorTestXMLInfo		0x1026

// ��ѯ��ѡ�������������������ݺͲ��Խ����֡����Ϊ�к�+����ţ�
#define CmdQueryInstrNoiseTestArea			0x2001
// ��ѯȫ�����������������������ݺͲ��Խ����֡����Ϊ�գ�
#define CmdQueryInstrNoiseTestAll			0x2002
// ��ѯ��ѡ��������ʧ��������ݺͲ��Խ����֡����Ϊ�к�+����ţ�
#define CmdQueryInstrDistortionTestArea		0x2003
// ��ѯȫ������ʧ��������ݺͲ��Խ����֡����Ϊ�գ�
#define CmdQueryInstrDistortionTestAll		0x2004
// ��ѯ��ѡ�����������Ų������ݺͲ��Խ����֡����Ϊ�к�+����ţ�
#define CmdQueryInstrCrosstalkTestArea		0x2005
// ��ѯȫ���������Ų������ݺͲ��Խ����֡����Ϊ�գ�
#define CmdQueryInstrCrosstalkTestAll		0x2006
// ��ѯ��ѡ����������ģ���ƱȲ������ݺͲ��Խ����֡����Ϊ�к�+����ţ�
#define CmdQueryInstrCMRRTestArea			0x2007
// ��ѯȫ��������ģ���ƱȲ������ݺͲ��Խ����֡����Ϊ�գ�
#define CmdQueryInstrCMRRTestAll			0x2008
// ��ѯ��ѡ��������������λ�������ݺͲ��Խ����֡����Ϊ�к�+����ţ�
#define CmdQueryInstrGainPhaseTestArea		0x2009
// ��ѯȫ������������λ�������ݺͲ��Խ����֡����Ϊ�գ�
#define CmdQueryInstrGainPhaseTestAll		0x200a
// ��ѯ��ѡ����첨���迹�������ݺͲ��Խ����֡����Ϊ�к�+����ţ�
#define CmdQuerySensorResistanceTestArea	0x200b
// ��ѯȫ���첨���迹�������ݺͲ��Խ����֡����Ϊ�գ�
#define CmdQuerySensorResistanceTestAll		0x200c
// ��ѯ��ѡ����첨��©��������ݺͲ��Խ����֡����Ϊ�к�+����ţ�
#define CmdQuerySensorLeakageTestArea		0x200d
// ��ѯȫ���첨��©��������ݺͲ��Խ����֡����Ϊ�գ�
#define CmdQuerySensorLeakageTestAll		0x200e
// ��ѯ��ѡ����첨�������������ݺͲ��Խ����֡����Ϊ�к�+����ţ�
#define CmdQuerySensorNoiseTestArea			0x200f
// ��ѯȫ���첨�������������ݺͲ��Խ����֡����Ϊ�գ�
#define CmdQuerySensorNoiseTestAll			0x2010
// ��ѯ��ѡ����첨����б�Ȳ������ݺͲ��Խ����֡����Ϊ�к�+����ţ�
#define CmdQuerySensorTiltTestArea			0x2011
// ��ѯȫ���첨����б�Ȳ������ݺͲ��Խ����֡����Ϊ�գ�
#define CmdQuerySensorTiltTestAll			0x2012
// ��ѯ��ѡ����첨����б��ģʽ�������ݺͲ��Խ����֡����Ϊ�к�+����ţ�
#define CmdQuerySensorTiltModelTestArea		0x2013
// ��ѯȫ���첨����б��ģʽ�������ݺͲ��Խ����֡����Ϊ�գ�
#define CmdQuerySensorTiltModelTestAll		0x2014
// ��ѯ��ѡ���������������ݺͲ��Խ����֡����Ϊ�к�+����ţ�
#define CmdQuerySeisMonitorTestArea			0x2015
// ��ѯȫ��������������ݺͲ��Խ����֡����Ϊ�գ�
#define CmdQuerySeisMonitorTestAll			0x2016
			
// �������ͻ���ͨѶ֡�ṹ
/************************************************************************/
/* ҵ���߼������ҵ�֡ͷ��֡ͷУ�飬�ɹ��������ʧ����������֡ͷ����ȡ֡��
   ���ܳ��ȣ���֤������ԣ���������������֡ͷ�����ҵ�֡β������������Ȳ�
   ������֤֡β����ȷ���֡���ݽ���ҵ����������������֡ͷ         */
/************************************************************************/
typedef struct CommFrame_Struct
{
// 	// ֡ͷ
// 	char m_cFrameHead[4];
// 	// ��֡��֮��֡β������֡β��Ϊ֡�����ܳ��ȣ���ҪС��֡������
// 	unsigned short m_usFrameLength;
	/** ֡�����֡�ʱ���������ˮ�ž���ͬ��
	����Ϊ��ͬһ֡*/
	// ֡�������ͣ�Ϊ1��Ϊ���Ϊ3��ΪӦ��
	char m_cCmdType;
	// ֡�����֣�����֡�Ĺ���
	unsigned short m_usCmd;
	// �����ʱ���
	unsigned int m_uiServerTimeStep;
	// �ͻ���ʱ���
	unsigned int m_uiClientTimeStep;
	// ����ˮ��
	unsigned int m_uiPacketIndex;
	// ������ˮ��
	unsigned int m_uiCmdIndex;
	// ��֡��
	unsigned int m_uiFrameNum;
	// ֡���
	unsigned int m_uiFrameIndex;
	// ֡����ִ�н��
	char m_cResult;
	// ֡���ݳ��� = ֡�����ܳ��� �C 2 �C 4 �C 4 �C 4 - 1��
	/** FieldOn�����Ӧ��4���ֽڱ����ͻ���FieldOn��Ҫ�ȴ���ʱ�䣬
	����Ϊ��λΪ0��ִ�У�����ȴ�)��*/
	unsigned short m_usFrameInfoSize;
	// ֡����ָ�룬���Ϊ��ѯ������֡���ݵ�ǰ�����ֽڷֱ����кź������
	char m_pcFrameInfo[FrameInfoSizeLimit];
// 	// ֡β
// 	char m_cFrameTail;
}m_oCommFrameStruct, *m_oCommFrameStructPtr;
// SURVEY SETUP�ṹ��
// Survey
typedef struct Survey_Struct
{
	// ���ߺ�
	unsigned int m_uiLine;
	// ��������+�첨�����ͣ���100-103p1
	char* m_pcReceiverSection;
	// ����
	unsigned short m_usReceiverSectionSize;
}m_oSurveyStruct;
// Point Code
typedef struct PointCode_Struct
{
	// �������
	unsigned int m_uiNb;
	// ��ǩ����PointCode1
	char* m_pcLabel;
	// ����
	unsigned short m_usLabelSize;
	// �첨�����ͣ���s1+cs
	char* m_pcSensorType;
	// ����
	unsigned short m_usSensorTypeSize;
}m_oPointCodeStruct;
// Sensor
typedef struct Sensor_Struct
{
	// �첨����
	unsigned int m_uiNb;
	// ��ǩ����Sensor1
	char* m_pcLabel;
	// ����
	unsigned short m_usLabelSize;
	// �첨���迹������
	float m_fContinuityMin;
	// �첨���迹������
	float m_fContinuityMax;
	// ���½�ϼ첨����б�Ȱٷֱ�
	float m_fTilt;
	// ���RMS������ƽ
	float m_fNoise;
	// ©����Բ�������������֮�������©�����
	float m_fLeakage;
	// SEGD����
	unsigned int m_uiSEGDCode;
}m_oSensorStruct;
// LAYOUT SETUP
// Marker
typedef struct Marker_Struct
{
	// �������ͣ�1-����վ��2-��Դվ��3-�ɼ�վ
	unsigned int m_uiBoxType;
	// ����SN
	unsigned int m_uiSN;
	// ���ߺ�
	unsigned int m_uiLineName;
	// ����
	unsigned int m_uiPointNb;
	// �����
	unsigned int m_uiChannelNb;
	// ��ǵ�����
	unsigned int m_uiMarkerIncr;
	// ��ת��ǣ�0-����ת��1-��ת
	unsigned int m_uiReversed;
}m_oMarker_Struct;
// Aux
typedef struct Aux_Struct
{
	// �����ţ���Instrument�����е�Auxiliary Descr��Ӧ
	unsigned int m_uiNb;
	// ��ǩ����pilot
	char* m_pcLabel;
	// ����
	unsigned short m_usLabelSize;
	// �������ͣ�1-����վ��2-��Դվ��3-�ɼ�վ
	unsigned int m_uiBoxType;
	// ����SN
	unsigned int m_uiSN;
	// �����
	unsigned int m_uiChannelNb;
	// ���棬1600mv��400mv
	unsigned int m_uiGain;
	// DPG���
	unsigned int m_uiDpgNb;
	// ע�ͣ���Comments1
	char* m_pcComments;
	// ����
	unsigned short m_usCommentsSize;
}m_oAux_Struct;
// Detour
typedef struct Detour_Struct
{
	// �Ͷ��������ͣ�1-����վ��2-��Դվ��3-�ɼ�վ
	unsigned int m_uiLowBoxType;
	// �Ͷ�����SN
	unsigned int m_uiLowSN;
	// �Ͷ˲����
	unsigned int m_uiLowChanNb;
	// �߶��������ͣ�1-����վ��2-��Դվ��3-�ɼ�վ
	unsigned int m_uiHighBoxType;
	// �߶�����SN
	unsigned int m_uiHighSN;
	// �߶˲����
	unsigned int m_uiHighChanNb;
	// ֹͣ��ǣ�0-������ǣ�1-ֹͣ���
	unsigned int m_uiStopMarking;
}m_oDetourStruct;
// Mute
typedef struct Mute_Struct
{
	// ���ߺ�
	unsigned int m_uiLineName;
	// ����
	unsigned int m_uiPointNb;
}m_oMuteStruct;
// BlastMachine
typedef struct BlastMachine_Struct
{
	// ������
	unsigned int m_uiNb;
	// ��ǩ����pilot
	char* m_pcLabel;
	// ����
	unsigned short m_usLabelSize;
	// �������ͣ�1-����վ��2-��Դվ��3-�ɼ�վ
	unsigned int m_uiBoxType;
	// ����SN
	unsigned int m_uiSN;
	// �����
	unsigned int m_uiChannelNb;
	// ���棬1600mv��400mv
	unsigned int m_uiGain;
	// DPG���
	unsigned int m_uiDpgNb;
	// ע�ͣ���Comments1
	char* m_pcComments;
	// ����
	unsigned short m_usCommentsSize;
}m_oBlastMachineStruct;
// Spread Type Setup
// Absolute
typedef struct Absolute_Struct
{
	// ������
	unsigned int m_uiNb;
	// ��ǩ����Absolute1
	char* m_pcLabel;
	// ����
	unsigned short m_usLabelSize;
	// �������У���1:1-127������������ʼ����-��ֹ���ţ�
	char* m_pcAbsoluteSpread;
	// ����
	unsigned short m_usAbsoluteSpreadSize;
}m_oAbsoluteStruct;
// Generic
typedef struct Generic_Struct
{
	// ������
	unsigned int m_uiNb;
	// ��ǩ����Generic1
	char* m_pcLabel;
	// ����
	unsigned short m_usLabelSize;
	// ��ͨ�������ͣ���50��g1+g2����50�Ե��������һ�����������Ϊ0Db,�ڶ���Ϊ12dB��
	char* m_pcLine;
	// ����
	unsigned short m_usLineSize;
	// ��ͨ���У���10(l1+ls)��10�Բ��ߣ���һ������ΪLine�ж����l1���ͣ��ڶ�����������
	char* m_pcSpread;
	// ����
	unsigned short m_usSpreadSize;
}m_oGenericStruct;
// Look
typedef struct Look_Struct
{
	// �Զ��鿴�Ƿ����������豸��1-�Զ��鿴��2-�ֶ��鿴
	unsigned int m_uiAutoLook;
	// �첨��������ԣ�1-���ԣ�2-������
	unsigned int m_uiResistance;
	// �첨����б�Ȳ��ԣ�1-���ԣ�2-������
	unsigned int m_uiTilt;
	// �첨��©����ԣ�1-���ԣ�2-������
	unsigned int m_uiLeakage;
}m_oLookStruct;
// Form Line
typedef struct FormLine_Struct
{
	// ������
	unsigned int m_uiNb;
	// �������ͣ�1-����վ��2-��Դվ��3-�ɼ�վ
	unsigned int m_uiBoxType;
	// ����SN
	unsigned int m_uiSN;
}m_oFormLineStruct;

// Instrument Sensor Test base
typedef struct Instrument_SensorTestBase_Struct
{
	unsigned int m_uiNb;	//�����ţ�ֻ����
	unsigned short m_usDescrSize; //m_pcDescr ��С
	char* m_pcDescr; //����������������INSTRUMENT NOISE��ֻ����
	unsigned int m_uiTestType;//�������ʹ��루ֻ����
	unsigned int m_uiADC;//0-Close��1-Inner��2-Out	
	unsigned int m_uiGain;//���棬1600mv��400mv
	unsigned int m_uiDAC;//0-Close���رգ���1-Inner�����ӵ��ڲ��������磩��2-Out�����ӵ��첨���ĵ�·����ˣ�	
	unsigned int m_uifilter;//�˲������ͣ�1-0.8LIN��2-0.8MIN
	unsigned int m_uiSampingRate; //��us��������
	unsigned int m_uiSampingLength;//��ms����������
}m_oInstrumentTestBaseStruct, m_oSensorTestBaseStruct;

//Instrument Limit
typedef struct Instrument_SensorTestLimit_Struct
{
	unsigned int m_uiNb; //�����ţ�ֻ����
	unsigned short m_usDescrSize; //m_pcDescr ��С
	char* m_pcDescr; //����������������INSTRUMENT NOISE��ֻ����
	unsigned int m_uiUnitSize; //	��λ size
	char* m_pcUnit;//	��λ��ֻ��������%
	unsigned int m_uiTestType;//�������ʹ��루ֻ����
	float m_fLimit;//����ֵ
}m_oInstrumentTestLimitStruct, m_oSensorTestLimitStruct;

//instrument
typedef struct InstrumentTest_Struct
{
	unsigned int m_uiNb; //�����ţ�ֻ����
	unsigned int m_uiTestType;//�������ʹ��루ֻ����
	unsigned int m_uiGain;//���棬1600mv��400mv
	unsigned m_uiRecordLength; //��¼ʱ��
	unsigned m_uiRecorded; //�Ƿ��¼�������ݣ�0-����¼��1-��¼
	unsigned short m_usAuxiliaryDescrSize; //���������� ��С
	char* m_pcAuxiliaryDescr; //��������������a1-a3
	unsigned short m_usAbsoluteSpreadSize; //�������� ��С
	char* m_pcAbsoluteSpread; //�������У���1:10-20
}m_oInstrumentTestStruct;

//Sensor
typedef struct SensorTest_Struct
{
	unsigned int m_uiNb; //�����ţ�ֻ����
	unsigned int m_uiTestType;//�������ʹ��루ֻ����
	unsigned m_uiRecorded; //�Ƿ��¼�������ݣ�0-����¼��1-��¼
	unsigned short m_usAbsoluteSpreadSize; //�������� ��С
	char* m_pcAbsoluteSpread; //�������У���1:10-20
}m_oSensorTestStruct;

//Multple
typedef struct MultpleTest_Struct
{
	unsigned int m_uiNb; //�����ţ�ֻ����
	unsigned m_uiTestNameSize;
	char* m_pcTestName;//������Ŀ���ƣ���Test1
	unsigned short m_usAuxiliaryDescrSize; //���������� ��С
	char* m_pcAuxiliaryDescr; //��������������a1-a3
	unsigned short m_usAbsoluteSpreadSize; //�������� ��С
	char* m_pcAbsoluteSpread; //�������У���1:10-20

	unsigned int m_uiDelayBetweenTest;//(ms)ÿ�β���֮��ļ��
	unsigned int m_uiRecordResults;//	�Ƿ��¼�������ݣ�0-����¼��1-��¼
	unsigned int m_uiRecordLength; //(ms)���Լ�¼ʱ��
	unsigned int m_uiTestFileNb;//�ļ����
	unsigned int m_uiLineNb;//���ߺ�
	unsigned int m_uiTestType;//�������ʹ���
	unsigned int m_uiGain;//���棬1600mv��400mv
	unsigned int m_uiLoopLineNb;//��Ҫ�ظ����еĲ���������
	unsigned int m_uiNbLoops;//����ѭ������
}m_oMultpleTestStruct;

//SeisMonitor
typedef struct SeisMonitorTest_Struct
{
	unsigned short m_usAbsoluteSpreadSize; //�������� ��С
	char* m_pcAbsoluteSpread; //�������У���1:10-20
}m_oSeisMonitorStruct;

// �������Խṹ��
typedef struct InstrumentNet_Struct 
{
	/** �����豸��*/
	unsigned int m_uiSN;
	/** ����*/
	int m_iLineIndex;
	/** ����*/
	int m_iPointIndex;
	/** ����ߺ�*/
	unsigned int m_uiLineNb;
	/** ��ǵ��*/
	unsigned int m_uiPointNb;
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
}m_oInstrumentNetStruct;

#endif