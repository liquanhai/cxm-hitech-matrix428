
#ifndef _CommProtocol_H
#define _CommProtocol_H
/**
* @brief ��������
*/
/** ����SNλ��*/
#define InstrumentBytes						4
/** �����������С������SNΪ0���ʾ������*/
#define InstrumentTableWindowSize			169
/** ���Խ��λ��*/
#define TestResultBytes						1
/** ���紫�������λ��*/
#define TestDataBytes						4
/** ���ݱ������С*/
#define DataTableWindowSize					270
/** C/S���ջ�������С*/
#define ServerRecBufferSize					8192000
/** C/S���ͻ�������С*/
#define ServerSndBufferSize					8192000
/** ������ӵĿͻ��˸���*/
#define ListenClientMaxNum					5
/** ������ջ�������С*/
#define ServerRecBufSize					8192000
/** ������֡�ṹ����*/
#define FrameStructNumMax					5800
/** �̹߳رյĵȴ�ʱ��*/
#define CloseClientCommThreadTimes			800
/** �߳�ִ�еļ��ʱ��*/
#define ClientCommThreadWaitTime			50
/** �߳�ִ�еļ������*/
#define ClientCommThreadWaitTimes			10
/** ����֡��ʱ�ȴ�����*/
#define SndFrameWaitTimes					5
/** ����֡��෢�ʹ���*/
#define SndFrameMaxNum						5
/** �ͻ�����֤ʱ�����*/
#define ClientCheckCountNum					50
/** �ͻ��˻�Ծʱ��������*/
#define ClientActiveCountNum				50
/** ���ݴ���������С��20000վ*���ߺ�+���+����ָ���ַ����*/
#define ProcBufferSize						240000
/** ����FieldOnʱ����*/
#define FieldOnWaitForTime					120000
/** �Զ���رտͻ�����Ϣ*/
#define CloseClientMsg						(WM_USER + 100)
/**
* @brief �����ֺ�ͨѶЭ��/n
* ��ѯĳ������ͻ���ֻ�跢���кź������/n
* �������������ź��кź��ټ����������ԣ�SN��4���ֽ�)���IP��4���ֽڣ�)����ֵ����ֵ(4���ֽ�)������Խ����1���ֽڣ���/n
* ��ѯ�����б�ĳ������4���ֽڵ��кź�4���ֽڵ�������ţ�
*/

/** Ӧ������λ������Ӧ�𣬽���������б�*/
#define CmdReturnBit						(1 << 15)
/** ��������Ϊ��������*/
#define CmdTypeSet							0x01
/** ��������ΪӦ��*/
#define CmdTypeReturn						0x02
/** TCP/IP֡������*/
#define FrameSizeLimit						1400
/** ֡ͷ����*/
#define FrameHeadSize						4
/** ֡������*/
#define FrameLengthSize						2
/** ֡ͷ��Ϣ����*/
#define FrameHeadInfoSize					27
/** ֡β����*/
#define FrameTailSize						1
/** ֡��������*/
#define FrameInfoSizeLimit					(FrameSizeLimit-FrameHeadSize-FrameLengthSize-FrameHeadInfoSize-FrameTailSize)
/** ֡ͷ*/
#define FrameHead1							0xaa
/** ֡ͷ*/
#define FrameHead2							0xa5
/** ֡ͷ*/
#define FrameHead3							0x5a
/** ֡ͷ*/
#define FrameHead4							0x55
/** ֡β*/
#define FrameTail							0xff
/** ֡����ִ�н��-�ȴ�ִ��*/
#define CmdResultWait						0x00
/** ֡����ִ�н��-ִ�гɹ�*/
#define CmdResultSuccess					0x01
/** ֡����ִ�н��-ִ��ʧ��*/
#define CmdResultFail						0x02
/** ֡����ִ�н��-��Ҫ��ʱִ��*/
#define CmdResultDelay						0x03
/** ֡����ִ�н��-�������Ѿ�ִ��*/
#define CmdResultDone						0x04
/** ���Խ��-�ϸ�*/
#define TestResultQualified					0x01
/** ���Խ��-���ϸ�*/
#define TestResultFailure					0x02
/** ���Խ��-������*/
#define TestResultNull						0x03
/** �ͻ��������˷�����֤��*/
#define CommCheck							"���̩���Ƽ����޹�˾"

/** �ͻ��˵�½��֤��֡����Ϊ��֤��*/
#define CmdClientConnect					0x0001
/** ��ѯ��������֡����Ϊ������4���ֽڣ�+������4���ֽڣ���*/
#define CmdQueryRevSection					0x0002
/** �ͻ����������֡����Ϊ�գ�*/
#define CmdSetHeartBeat						0x0003
/** ��ѯWhole Table��֡����Ϊ�к�+�����+ ����SN+����IP��SN = 0������������*/
#define CmdQueryWholeTable					0x0004
/** ��ѯUpdate Table��֡����Ϊ�к�+�����+ ����SN+����IP��SN = 0������������*/
#define CmdQueryUpdateTable					0x0005
/** �ϵ磨�����ֺ�֡����Ϊ�գ�*/
#define CmdSetFieldOn						0x0006
/** �ϵ磨�����ֺ�֡����Ϊ�գ�*/
#define CmdSetFieldOff						0x0007
/** ��ѯ��ѡ����ȫ����Ϣ��֡����Ϊ�к�+����ţ�*/
#define CmdQueryInstrumentInfo				0x0008
/** ��ѯȫ��������ȫ����Ϣ��֡����Ϊ�����ṹ�壩*/
#define CmdQueryInstrumentInfoAll			0x0009
/** Field On��Ҫ�ȴ���ʱ�䣨֡����Ϊִ��FieldOnʣ��ʱ�䣬Ϊ0��ʾ����ȴ���*/
#define CmdFieldOnWaitTime					0x000a

/** ��ѯ SurveyXML �ļ���Ϣ��֡����Ϊ�գ�*/
#define CmdQuerySurveyXMLInfo				0x1001
/** ���� SurveyXML �ļ���Ϣ��֡����Ϊ��Ϣ�ṹ�壩*/
#define CmdSetSurveyXMLInfo					0x1002
/** ��ѯ PointCode XML�ļ���Ϣ��֡����Ϊ�գ�*/
#define CmdQueryPointCodeXMLInfo			0x1003
/** ���� PointCode XML�ļ���Ϣ��֡����Ϊ��Ϣ�ṹ�壩*/
#define CmdSetPointCodeXMLInfo				0x1004
/** ��ѯ Sensor XML�ļ���Ϣ��֡����Ϊ�գ�*/
#define CmdQuerySensorXMLInfo				0x1005
/** ���� Sensor XML�ļ���Ϣ��֡����Ϊ��Ϣ�ṹ�壩*/
#define CmdSetSensorXMLInfo					0x1006
/** ��ѯ Marker XML�ļ���Ϣ��֡����Ϊ�գ�*/
#define CmdQueryMarkerXMLInfo				0x1007
/** ���� Marker XML�ļ���Ϣ��֡����Ϊ��Ϣ�ṹ�壩*/
#define CmdSetMarkerXMLInfo					0x1008
/** ��ѯ Aux XML�ļ���Ϣ��֡����Ϊ�գ�*/
#define CmdQueryAuxXMLInfo					0x1009
/** ���� Aux XML�ļ���Ϣ��֡����Ϊ��Ϣ�ṹ�壩*/
#define CmdSetAuxXMLInfo					0x100a
/** ��ѯ Detour XML�ļ���Ϣ��֡����Ϊ�գ�*/
#define CmdQueryDetourXMLInfo				0x100b
/** ���� Detour XML�ļ���Ϣ��֡����Ϊ��Ϣ�ṹ�壩*/
#define CmdSetDetourXMLInfo					0x100c
/** ��ѯ Mute XML�ļ���Ϣ��֡����Ϊ�գ�*/
#define CmdQueryMuteXMLInfo					0x100d
/** ���� Mute XML�ļ���Ϣ��֡����Ϊ��Ϣ�ṹ�壩*/
#define CmdSetMuteXMLInfo					0x100e
/** ��ѯ BlastMachine XML�ļ���Ϣ��֡����Ϊ�գ�*/
#define CmdQueryBlastMachineXMLInfo			0x100f
/** ���� BlastMachine XML�ļ���Ϣ��֡����Ϊ��Ϣ�ṹ�壩*/
#define CmdSetBlastMachineXMLInfo			0x1010
/** ��ѯ Absolute XML�ļ���Ϣ��֡����Ϊ�գ�*/
#define CmdQueryAbsoluteXMLInfo				0x1011
/** ���� Absolute XML�ļ���Ϣ��֡����Ϊ��Ϣ�ṹ�壩*/
#define CmdSetAbsoluteXMLInfo				0x1012
/** ��ѯ Generic XML�ļ���Ϣ��֡����Ϊ�գ�*/
#define CmdQueryGenericXMLInfo				0x1013
/** ���� Generic XML�ļ���Ϣ��֡����Ϊ��Ϣ�ṹ�壩*/
#define CmdSetGenericXMLInfo				0x1014
/** ��ѯ Look XML�ļ���Ϣ��֡����Ϊ�գ�*/
#define CmdQueryLookXMLInfo					0x1015
/** ���� Look XML�ļ���Ϣ��֡����Ϊ��Ϣ�ṹ�壩*/
#define CmdSetLookXMLInfo					0x1016
/** ��ѯ InstrumentTestBase XML�ļ���Ϣ��֡����Ϊ�գ�*/
#define CmdQueryInstrumentTestBaseXMLInfo	0x1017
/** ���� InstrumentTestBase XML�ļ���Ϣ��֡����Ϊ��Ϣ�ṹ�壩*/
#define CmdSetInstrumentTestBaseXMLInfo		0x1018
/** ��ѯ SensorTestBase XML�ļ���Ϣ��֡����Ϊ�գ�*/
#define	CmdQuerySensorTestBaseXMLInfo		0x1019
/** ���� SensorTestBase XML�ļ���Ϣ��֡����Ϊ��Ϣ�ṹ�壩*/
#define	CmdSetSensorTestBaseXMLInfo			0x101a
/** ��ѯ InstrumentTestLimit XML�ļ���Ϣ��֡����Ϊ�գ�*/
#define CmdQueryInstrumentTestLimitXMLInfo	0x101b
/** ���� InstrumentTestLimit XML�ļ���Ϣ��֡����Ϊ��Ϣ�ṹ�壩*/
#define CmdSetInstrumentTestLimitXMLInfo	0x101c
/** ��ѯ SensorTestLimit XML�ļ���Ϣ��֡����Ϊ�գ�*/
#define CmdQuerySensorTestLimitXMLInfo		0x101d
/** ���� SensorTestLimit XML�ļ���Ϣ��֡����Ϊ��Ϣ�ṹ�壩*/
#define CmdSetSensorTestLimitXMLInfo		0x101e
/** ��ѯ InstrumentTest XML�ļ���Ϣ��֡����Ϊ�գ�*/
#define CmdQueryInstrumentTestXMLInfo		0x101f
/** ���� InstrumentTest XML�ļ���Ϣ��֡����Ϊ��Ϣ�ṹ�壩*/
#define CmdSetInstrumentTestXMLInfo			0x1020
/** ��ѯ SensorTest XML�ļ���Ϣ��֡����Ϊ�գ�*/
#define CmdQuerySensorTestXMLInfo			0x1021
/** SensorTest XML�ļ���Ϣ��֡����Ϊ��Ϣ�ṹ�壩*/
#define CmdSetSensorTestXMLInfo				0x1022
/** ��ѯ MultipleTest XML�ļ���Ϣ��֡����Ϊ�գ�*/
#define CmdQueryMultipleTestXMLInfo			0x1023
/** ���� MultipleTest XML�ļ���Ϣ��֡����Ϊ��Ϣ�ṹ�壩*/
#define CmdSetMultipleTestXMLInfo			0x1024
/** ��ѯ SeisMonitorTest XML�ļ���Ϣ��֡����Ϊ�գ�*/
#define CmdQuerySeisMonitorTestXMLInfo		0x1025
/** ���� SeisMonitorTest XML�ļ���Ϣ��֡����Ϊ��Ϣ�ṹ�壩*/
#define CmdSetSeisMonitorTestXMLInfo		0x1026
/** ��ѯ LAULeakage XML�ļ���Ϣ��֡����Ϊ�գ�*/
#define CmdQueryLAULeakageXMLInfo			0x1027
/** ���� LAULeakage XML�ļ���Ϣ��֡����Ϊ��Ϣ�ṹ�壩*/
#define CmdSetLAULeakageXMLInfo				0x1028
/** ��ѯ FormLine XML�ļ���Ϣ��֡����Ϊ�գ�*/
#define CmdQueryFormLineXMLInfo				0x1029
/** ���� FormLine XML�ļ���Ϣ��֡����Ϊ��Ϣ�ṹ�壩*/
#define CmdSetFormLineXMLInfo				0x102a

/** ��ѯ��ѡ�������������������ݺͲ��Խ����֡����Ϊ�к�+����ţ�*/
#define CmdQueryInstrNoiseTestArea			0x2001
/** ��ѯȫ�����������������������ݺͲ��Խ����֡����Ϊ�գ�*/
#define CmdQueryInstrNoiseTestAll			0x2002
/** ��ѯ��ѡ��������ʧ��������ݺͲ��Խ����֡����Ϊ�к�+����ţ�*/
#define CmdQueryInstrDistortionTestArea		0x2003
/** ��ѯȫ������ʧ��������ݺͲ��Խ����֡����Ϊ�գ�*/
#define CmdQueryInstrDistortionTestAll		0x2004
/** ��ѯ��ѡ�����������Ų������ݺͲ��Խ����֡����Ϊ�к�+����ţ�*/
#define CmdQueryInstrCrosstalkTestArea		0x2005
/** ��ѯȫ���������Ų������ݺͲ��Խ����֡����Ϊ�գ�*/
#define CmdQueryInstrCrosstalkTestAll		0x2006
/** ��ѯ��ѡ����������ģ���ƱȲ������ݺͲ��Խ����֡����Ϊ�к�+����ţ�*/
#define CmdQueryInstrCMRRTestArea			0x2007
/** ��ѯȫ��������ģ���ƱȲ������ݺͲ��Խ����֡����Ϊ�գ�*/
#define CmdQueryInstrCMRRTestAll			0x2008
/** ��ѯ��ѡ��������������λ�������ݺͲ��Խ����֡����Ϊ�к�+����ţ�*/
#define CmdQueryInstrGainPhaseTestArea		0x2009
/** ��ѯȫ������������λ�������ݺͲ��Խ����֡����Ϊ�գ�*/
#define CmdQueryInstrGainPhaseTestAll		0x200a
/** ��ѯ��ѡ����첨���迹�������ݺͲ��Խ����֡����Ϊ�к�+����ţ�*/
#define CmdQuerySensorResistanceTestArea	0x200b
/** ��ѯȫ���첨���迹�������ݺͲ��Խ����֡����Ϊ�գ�*/
#define CmdQuerySensorResistanceTestAll		0x200c
/** ��ѯ��ѡ����첨��©��������ݺͲ��Խ����֡����Ϊ�к�+����ţ�*/
#define CmdQuerySensorLeakageTestArea		0x200d
/** ��ѯȫ���첨��©��������ݺͲ��Խ����֡����Ϊ�գ�*/
#define CmdQuerySensorLeakageTestAll		0x200e
/** ��ѯ��ѡ����첨�������������ݺͲ��Խ����֡����Ϊ�к�+����ţ�*/
#define CmdQuerySensorNoiseTestArea			0x200f
/** ��ѯȫ���첨�������������ݺͲ��Խ����֡����Ϊ�գ�*/
#define CmdQuerySensorNoiseTestAll			0x2010
/** ��ѯ��ѡ����첨����б�Ȳ������ݺͲ��Խ����֡����Ϊ�к�+����ţ�*/
#define CmdQuerySensorTiltTestArea			0x2011
/** ��ѯȫ���첨����б�Ȳ������ݺͲ��Խ����֡����Ϊ�գ�*/
#define CmdQuerySensorTiltTestAll			0x2012
/** ��ѯ��ѡ����첨����б��ģʽ�������ݺͲ��Խ����֡����Ϊ�к�+����ţ�*/
#define CmdQuerySensorTiltModelTestArea		0x2013
/** ��ѯȫ���첨����б��ģʽ�������ݺͲ��Խ����֡����Ϊ�գ�*/
#define CmdQuerySensorTiltModelTestAll		0x2014
/** ��ѯ��ѡ���������������ݺͲ��Խ����֡����Ϊ�к�+����ţ�*/
#define CmdQuerySeisMonitorTestArea			0x2015
/** ��ѯȫ��������������ݺͲ��Խ����֡����Ϊ�գ�*/
#define CmdQuerySeisMonitorTestAll			0x2016

/**
* @brief �������ͻ���ͨѶ֡�ṹ\n
* ҵ���߼������ҵ�֡ͷ��֡ͷУ�飬�ɹ��������ʧ����������֡ͷ����ȡ֡��\n
* ���ܳ��ȣ���֤������ԣ���������������֡ͷ�����ҵ�֡β������������Ȳ�\n
* ������֤֡β����ȷ���֡���ݽ���ҵ����������������֡ͷ��
*/
typedef struct CommFrame_Struct
{
// 	/** ֡ͷ*/
// 	char m_cFrameHead[4];
// 	/** ��֡��֮��֡β������֡β��Ϊ֡�����ܳ��ȣ���ҪС��֡������*/
// 	unsigned short m_usFrameLength;
	/** ֡�����֡�ʱ���������ˮ�ž���ͬ������Ϊ��ͬһ֡*/
	/** ֡�������ͣ�Ϊ1��Ϊ���Ϊ3��ΪӦ��*/
	char m_cCmdType;
	/** ֡�����֣�����֡�Ĺ���*/
	unsigned short m_usCmd;
	/** �����ʱ���*/
	unsigned int m_uiServerTimeStep;
	/** �ͻ���ʱ���*/
	unsigned int m_uiClientTimeStep;
	/** ����ˮ��*/
	unsigned int m_uiPacketIndex;
	/** ������ˮ��*/
	unsigned int m_uiCmdIndex;
	/** ��֡��*/
	unsigned int m_uiFrameNum;
	/** ֡��ţ���1��ʼ��*/
	unsigned int m_uiFrameIndex;
	/** ֡����ִ�н��*/
	char m_cResult;
	/** ֡���ݳ��� = ֡�����ܳ��� �C 2 �C 4 �C 4 �C 4 - 1��*/
	/** FieldOn�����Ӧ��4���ֽڱ����ͻ���FieldOn��Ҫ�ȴ���ʱ�䣬
	����Ϊ��λΪ0��ִ�У�����ȴ�)��*/
	unsigned short m_usFrameInfoSize;
	/** ֡����ָ�룬���Ϊ��ѯ������֡���ݵ�ǰ�����ֽڷֱ����кź������*/
	char m_pcFrameInfo[FrameInfoSizeLimit];
// 	/** ֡β*/
// 	char m_cFrameTail;
	/** ��ʱ����*/
	unsigned int m_uiTimeOutCount;
	/** ���ʹ�������*/
	unsigned int m_uiSndCount;
}m_oCommFrameStruct, *m_oCommFrameStructPtr;

/**
* @brief �������Խṹ��
*/
typedef struct InstrumentNet_Struct 
{
	/** �����豸��*/
	unsigned int m_uiSN;
	/** ����IP*/
	unsigned int m_uiIP;
}m_oInstrumentNetStruct;

#endif