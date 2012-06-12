#pragma once

// ��������
#define InstrumentNoiseTestType			0x00000001
#define InstrumentDistortionTestType	(InstrumentNoiseTestType << 1)
#define InstrumentCrosstalkTestType		(InstrumentNoiseTestType << 2)
#define InstrumentCMRRTestType			(InstrumentNoiseTestType << 3)
#define InstrumentGainPhaseTestType		(InstrumentNoiseTestType << 4)
#define SensorResistanceTestType		(InstrumentNoiseTestType << 5)
#define SensorLeakageTestType			(InstrumentNoiseTestType << 6)
#define SensorNoiseTestType				(InstrumentNoiseTestType << 7)
#define SensorTiltTestType				(InstrumentNoiseTestType << 8)
#define SensorTiltModelTestType			(InstrumentNoiseTestType << 9)
#define SeisMonitorTestType				(InstrumentNoiseTestType << 10)

// ������
// �ϵ�
#define CmdFieldOn					0x0001
// �ϵ�
#define CmdFieldOff					0x0002
// ������������������ṹ�壩
#define CmdAddInstrument			0x0003
// �޸��������ԣ���������ṹ�壩
#define CmdChangeInstrument			0x0004
// ɾ���������������SN+IP��
#define CmdDeleteInstrument			0x0005
// �õ���������ȫ����Ϣ���������SN+IP��
#define CmdGetInstrumentInfo		0x0006
// �õ�ȫ��������ȫ����Ϣ
#define CmdGetInstrumentInfoAll		0x0007
// ȫ��������ʼ���ԣ�����������ͣ���������ռ4���ֽڣ�
#define CmdStartTestAll				0x0008
// ����������ʼ���ԣ���������+���в���ɼ�������SN+IP��
#define CmdStarTestSelect			0x0009
// ȫ������ֹͣ���ԣ�����������ͣ���������ռ4���ֽڣ�
#define CmdStopTestAll				0x000a
// ��������ֹͣ���ԣ���������+����ֹͣ�ɼ�������SN+IP��
#define	CmdStopTestSelect			0x000b

// SurveyXML �ļ���Ϣ�������Ϣ�ṹ�壩
#define CmdSurveyXMLInfo			0x1001
// PointCode XML�ļ���Ϣ�������Ϣ�ṹ�壩
#define CmdPointCodeXMLInfo			0x1002
// Sensor XML�ļ���Ϣ�������Ϣ�ṹ�壩
#define CmdSensorXMLInfo			0x1003
// Marker XML�ļ���Ϣ�������Ϣ�ṹ�壩
#define CmdMarkerXMLInfo			0x1004
// Aux XML�ļ���Ϣ�������Ϣ�ṹ�壩
#define CmdAuxXMLInfo				0x1005
// Detour XML�ļ���Ϣ�������Ϣ�ṹ�壩
#define CmdDetourXMLInfo			0x1006
// Mute XML�ļ���Ϣ�������Ϣ�ṹ�壩
#define CmdMuteXMLInfo				0x1007
// BlastMachine XML�ļ���Ϣ�������Ϣ�ṹ�壩
#define CmdBlastMachineXMLInfo		0x1008
// Absolute XML�ļ���Ϣ�������Ϣ�ṹ�壩
#define CmdAbsoluteXMLInfo			0x1009
// Generic XML�ļ���Ϣ�������Ϣ�ṹ�壩
#define CmdGenericXMLInfo			0x100a
// Look XML�ļ���Ϣ�������Ϣ�ṹ�壩
#define CmdLookXMLInfo				0x100b
// InstrumentTestBase XML�ļ���Ϣ�������Ϣ�ṹ�壩
#define CmdInstrumentTestBaseXMLInfo	0x100c
// SensorTestBase XML�ļ���Ϣ�������Ϣ�ṹ�壩
#define	CmdSensorTestBaseXMLInfo		0x100d
// InstrumentTestLimit XML�ļ���Ϣ�������Ϣ�ṹ�壩
#define CmdInstrumentTestLimitXMLInfo	0x100e
// SensorTestLimit XML�ļ���Ϣ�������Ϣ�ṹ�壩
#define CmdSensorTestLimitXMLInfo		0x100f
// InstrumentTest XML�ļ���Ϣ�������Ϣ�ṹ�壩
#define CmdInstrumentTestXMLInfo		0x1010
// SensorTest XML�ļ���Ϣ�������Ϣ�ṹ�壩
#define CmdSensorTestXMLInfo			0x1011
// MultipleTest XML�ļ���Ϣ�������Ϣ�ṹ�壩
#define CmdMultipleTestXMLInfo			0x1012
// SeisMonitorTest XML�ļ���Ϣ�������Ϣ�ṹ�壩
#define CmdSeisMonitorTestXMLInfo		0x1013

// �ͻ��˵�½��֤
#define CmdClientConnect				0x2001

// TCP/IP֡������
#define FrameSizeLimit					1460
// ֡ͷ
#define FrameHead1						0x11
// ֡ͷ
#define FrameHead2						0x22
// ֡ͷ
#define FrameHead3						0x33
// ֡ͷ
#define FrameHead4						0x44
// ֡β
#define FrameTail						0xaa
// �ͻ��������˷�����֤��
#define CommCheck						_T("���̩���Ƽ����޹�˾")

// �������ͻ���ͨѶ֡�ṹ
/************************************************************************/
/* ҵ���߼������ҵ�֡ͷ��֡ͷУ�飬�ɹ��������ʧ����������֡ͷ����ȡ֡��
   ���ܳ��ȣ���֤������ԣ���������������֡ͷ�����ҵ�֡β������������Ȳ�
   ������֤֡β����ȷ���֡���ݽ���ҵ����������������֡ͷ         */
/************************************************************************/
typedef struct CommFrame_Struct
{
	// ֡ͷ
	char m_cFrameHead[4];
	// ֡�����ܳ��ȣ�С��֡������
	unsigned short m_usFrameLength;
	// ֡�����֣�����֡�Ĺ���
	unsigned short m_usCmd;
	// ��֡��
	unsigned int m_uiFrameNum;
	// ֡���
	unsigned int m_uiFrameIndex;
	// ֡���Ϊ1��Ϊ�������Ϊ2��Ϊ��ѯ���Ϊ3��ΪӦ������
	char m_cCommand;
	// Ӧ�����úͲ�ѯ�����Ƿ�ɹ�
	char m_cResult;
	// ֡���ݳ��� = ֡�����ܳ��� �C 2 �C 4 �C 4 �C 1 - 1��
	/** FieldOn�����Ӧ��4���ֽڱ����ͻ���FieldOn��Ҫ�ȴ���ʱ�䣬
	����Ϊ��λΪ0��ִ�У�����ȴ�)��*/
	unsigned short m_usFrameInfoSize;
	// ֡����ָ��
	char* m_pcFrameInfo;
	// ֡β
	char m_cFrameTail;
}m_oCommFrameStruct;
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
typedef struct Instrument_Struct 
{
	/** �����������е�λ��*/
	unsigned int m_uiIndex;
	/** �����Ƿ�ʹ����*/
	bool m_bInUsed;
	/** �����豸��*/
	unsigned int m_uiSN;
	/** �������� 1-����վ��2-��Դվ��3-�ɼ�վ��4-LCI*/
	int m_iInstrumentType;
	/** ����IP��ַ*/
	unsigned int m_uiIP;
	/** ����·��IP��ַ*/
	unsigned int m_uiRoutIP;
	/** ·�ɷ��� 1-�ϣ�2-�£�3-��4��*/
	int m_iRoutDirection;
	/** ·�ɵ�ַ �����߷��� �Ϸ�*/
	unsigned int m_uiRoutIPTop;
	/** ·�ɵ�ַ �����߷��� �·�*/
	unsigned int m_uiRoutIPDown;
	/** ·�ɵ�ַ �����߷��� ��*/
	unsigned int m_uiRoutIPLeft;
	/** ·�ɵ�ַ �����߷��� �ҷ�*/
	unsigned int m_uiRoutIPRight;
	/** ·�ɿ���*/
	char m_cLAUXRoutOpenSet;
	/** ���ӵ����� �Ϸ�*/
	Instrument_Struct* m_pInstrumentTop;
	/** ���ӵ����� �·�*/
	Instrument_Struct* m_pInstrumentDown;
	/** ���ӵ����� ��*/
	Instrument_Struct* m_pInstrumentLeft;
	/** ���ӵ����� �ҷ�*/
	Instrument_Struct* m_pInstrumentRight;
	/** �װ�ʱ��*/
	unsigned int m_uiTimeHeadFrame;
	/** β������*/
	int m_iTailFrameCount;
	/** ����ʱ��*/
	unsigned int m_uiDelayTime;
	/** ��������ϵͳʱ��*/
	unsigned int m_uiSystemTime;
	/** ��������ʱ��*/
	unsigned int m_uiNetTime;
	/** ��������״̬*/
	unsigned int m_uiNetState;
	/** ������������1*/
	unsigned int m_uiNetOrder;
	/** 16bitsʱ�䣬����ʱ�̵�λ*/
	unsigned short m_usReceiveTime;	
	/** 16bitsʱ�䣬����ʱ�̵�λ*/
	unsigned short m_usSendTime;
	/** 16bits ���߷�������β������ʱ��*/
	unsigned short m_usLineLeftReceiveTime;	
	/** 16bits ���߷�������β������ʱ��*/
	unsigned short m_usLineRightReceiveTime;	
	/** 16bits �����߷�������β������ʱ��*/
	unsigned short m_usCrossTopReceiveTime;	
	/** 16bits �����߷�����β������ʱ��*/
	unsigned short m_usCrossDownReceiveTime;	
	/** �ɼ�վ���Դվ�Ĺ㲥�˿�*/
	unsigned int m_uiBroadCastPort;
	/** ����*/
	int m_iLineIndex;
	/** ����*/
	int m_iPointIndex;
	/** ����ߺ�*/
	unsigned int m_uiLineNb;
	/** ��ǵ��*/
	unsigned int m_uiPointNb;
	/** �����*/
	unsigned int m_uiChannelNb;
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
	unsigned int m_uiStopMarking;
	/** �Ƿ��ǵ�*/
	bool m_bMarker;
	/** �Ƿ��Ƶ�*/
	bool m_bMute;
	// �װ�λ���ȶ�����
	int m_iHeadFrameStableNum;
	/** �ڼ�������IP��ַ*/
	int m_iIPSetCount;
	/** IP��ַ�����Ƿ�ɹ�*/
	bool m_bIPSetOK;
	/** �ڼ���β��ʱ�̲�ѯ*/
	int m_iTailTimeQueryCount;
	/** β��ʱ�̲�ѯӦ�����*/
	int m_iTailTimeReturnCount;
	/** β��ʱ�̲�ѯ�Ƿ�ɹ�*/
	bool m_bTailTimeQueryOK;
	/** ����ʱ��������λ*/
	unsigned int m_uiTimeHigh;
	/** ����ʱ��������λ*/
	unsigned int m_uiTimeLow;
	/** �ڼ�����������ʱ��*/
	int m_iTimeSetCount;
	/** ����ʱͳ�ɹ�����*/
	int m_iTimeSetReturnCount;
	/** ����ʱ�������Ƿ�ɹ�*/
	bool m_bTimeSetOK;
	// ADC���������Ƿ�Ӧ��
	bool m_bADCSetReturn;
	// �����Ƿ������ADC��������
	bool m_bADCSet;
	// ������ʼADC���ݲɼ����óɹ�
	bool m_bADCStartSample;
	// ����ֹͣADC���ݲɼ����óɹ�
	bool m_bADCStopSample;
	// �����ѯ����֡��
	unsigned int m_uiErrorCodeQueryNum;
	// �����ѯӦ��֡��
	unsigned int m_uiErrorCodeReturnNum;
	// �ɼ�վ�͵�Դվ�������ݴ������
	int m_iFDUErrorCodeDataCount;
	// �ɼ�վ�͵�Դվ����������
	int m_iFDUErrorCodeCmdCount;
	// �ɼ�վ�͵�Դվ�������ݴ������
	char m_cFDUErrorCodeDataCountOld;
	// �ɼ�վ�͵�Դվ����������
	char m_cFDUErrorCodeCmdCountOld;

	// ����վ����A���ݹ���
	int m_iLAUXErrorCodeDataLineACount;
	// ����վ����B���ݹ���
	int m_iLAUXErrorCodeDataLineBCount;
	// ����վ������A���ݹ���
	int m_iLAUXErrorCodeDataLAUXLineACount;
	// ����վ������B���ݹ���
	int m_iLAUXErrorCodeDataLAUXLineBCount;
	// ����վ����ڹ���
	int m_iLAUXErrorCodeCmdCount;

	// ����վ����A���ݹ���
	char m_cLAUXErrorCodeDataLineACountOld;
	// ����վ����B���ݹ���
	char m_cLAUXErrorCodeDataLineBCountOld;
	// ����վ������A���ݹ���
	char m_cLAUXErrorCodeDataLAUXLineACountOld;
	// ����վ������B���ݹ���
	char m_cLAUXErrorCodeDataLAUXLineBCountOld;
	// ����վ����ڹ���
	char m_cLAUXErrorCodeCmdCountOld;

	// ʵ�ʽ���ADC����֡�������ط�֡��
	unsigned int m_uiADCDataActualRecFrameNum;
	// �ط���ѯ֡�õ���Ӧ��֡��
	unsigned int m_uiADCDataRetransmissionFrameNum;
	// Ӧ�ý���ADC����֡��������֡��
	unsigned int m_uiADCDataShouldRecFrameNum;
	// ADC����֡��ָ��ƫ����
	unsigned short m_usADCDataFramePoint;
	// ADC����֡����ʱ�ı���ʱ��
	unsigned int m_uiADCDataFrameSysTime;
	// ADC����֡��ʼ֡��
	int m_iADCDataFrameStartNum;
}m_oInstrumentStruct;

// ����ͨѶ�е��������Խṹ��
typedef struct InstrumentNet_Struct 
{
	/** �����豸��*/
	unsigned int m_uiSN;
	/** �������� 1-����վ��2-��Դվ��3-�ɼ�վ��4-LCI*/
	int m_iInstrumentType;
	/** ����IP��ַ*/
	unsigned int m_uiIP;
	/** ����·��IP��ַ*/
	unsigned int m_uiRoutIP;
	/** ·�ɷ��� 1-�ϣ�2-�£�3-��4��*/
	int m_iRoutDirection;
	/** ����*/
	int m_iLineIndex;
	/** ����*/
	int m_iPointIndex;
	/** ����ߺ�*/
	unsigned int m_uiLineNb;
	/** ��ǵ��*/
	unsigned int m_uiPointNb;
	/** �����*/
	unsigned int m_uiChannelNb;
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
	unsigned int m_uiStopMarking;
	/** �Ƿ��ǵ�*/
	bool m_bMarker;
	/** �Ƿ��Ƶ�*/
	bool m_bMute;
	/** IP��ַ�����Ƿ�ɹ�*/
	bool m_bIPSetOK;
	/** ����ʱ�������Ƿ�ɹ�*/
	bool m_bTimeSetOK;
	// �����Ƿ������ADC��������
	bool m_bADCSet;
}m_oInstrumentNetStruct;
/**	test type
INSTRUMENT:
	INSTRUMENT NOISE
	INSTRUMENT DISTORTION
	INSTRUMENT CROSSTALK
	INSTRUMENT CMRR
	INSTRUMENT GAIN/PHASE

SENSOR:
	SENSOR RESISTANCE
	SENSOR LEAKAGE
	SENSOR NOISE
	SENSOR TILT
	SENSOR TILT MODEL

MONITOR:
	SENSOR MONITOR	
*/
//common instrument/sensor test
typedef struct CommonDevice_Struct
{
	unsigned int m_uiSN;// �����豸��
	unsigned int m_uiIP;// ����IP��ַ
}m_oCommonDeviceStruct;

//common test result
typedef struct CommonDeviceTestResult_Struct
{
	m_oCommonDeviceStruct m_oDevice;
	unsigned int m_uiTestType; //��������
	float m_fTestValue;//���Խ��
	char m_cTestCheck; //���Լ��λ
}m_oCommonDeviceTestResultStruct;

