// ���� ifdef ���Ǵ���ʹ�� DLL �������򵥵�
// ��ı�׼�������� DLL �е������ļ��������������϶���� MATRIXSERVERDLL_EXPORTS
// ���ű���ġ���ʹ�ô� DLL ��
// �κ�������Ŀ�ϲ�Ӧ����˷��š�������Դ�ļ��а������ļ����κ�������Ŀ���Ὣ
// MATRIXSERVERDLL_API ������Ϊ�Ǵ� DLL ����ģ����� DLL ���ô˺궨���
// ������Ϊ�Ǳ������ġ�

#ifndef _MatrixServerDll_H
#define _MatrixServerDll_H

#include <list>
#include <map>
#include <hash_map>

using std::list;
using std::string;
using std::wstring;
using std::map;
using stdext::hash_map;

/*
*	if using C++ Compiler to compile the file, adopting C linkage mode
	*/
#ifdef __cplusplus
	extern "C" {
#endif

	// according to the control macro, deciding whether export or import functions
#ifdef MATRIXSERVERDLL_EXPORTS
#define MatrixServerDll_API __declspec(dllexport)
#else
#define MatrixServerDll_API __declspec(dllimport)
#endif

	// Macro definitions declarations
	// ��־�ļ���
#define LogFolderPath				_T("..\\Log")
	// ϵͳ��־�ļ��У��������������桢����
#define SysOptLogFolderPath			_T("\\ϵͳ������־")
	// ʱͳ��־�ļ��У�����β��ʱ�̲�ѯ��ʱͳ����Ӧ�𼰽��ͳ�ƣ�
#define TimeDelayLogFolderPath		_T("\\ʱͳ��־")
	// �����ѯ��־�ļ��У����������ѯӦ�𼰽��ͳ�ƣ�
#define ErrorCodeLogFolderPath		_T("\\�����ѯ��־")
	// ֡ʱ���ƫ������־��������֡���ط�֡��ʧЧ֡���ͳ�ƣ�
#define ADCFrameTimeLogFolderPath	_T("\\��������֡ʱ�估ƫ����")
	// ADC����֡
#define ADCDataLogFolderPath		_T("\\��������")

	// ���ѡ��:Debug�����Ϊ0��Release�����Ϊ1
#define OutPutSelect				0
	// ���������־����
#define OutPutLogErrorLimit			100
	// ��־�ļ������ļ������Ϣ����
#define OutPutLogFileInfoNumLimit	5000
	// ��־�������
	enum{LogType, WarningType, ErrorType, ExpandType};
	// ��־�ļ�����
	enum{OptLogType, TimeDelayLogType, ErrorCodeLogType, ADCFrameTimeLogType};
// INI�ļ���ȡ�ؼ��ֻ�������С
#define INIFileStrBufSize			256
typedef int (WINAPI *PFCALLBACK)(int Param1,int Param2) ;
typedef void (CALLBACK* ProSampleDateCallBack)(int _iLineIndex, int _iPointIndex, int *_piData,
	int _iSize, unsigned int _uiSN);

// Resources declarations
// ��־����ṹ
typedef struct LogOutPut_Struct
{
	// ��־�����Դͬ������
	CRITICAL_SECTION m_oSecLogFile;
	// ��־����ļ�ָ��
	FILE* m_pFile;
	// ��־����ṹ
	list<string> m_oLogOutputList;
	// �������
	unsigned int m_uiErrorCount;
	// ��־���·��
	string m_SaveLogFilePath;
	// ��־�ļ����
	unsigned int m_uiLogFileNb;
	// ��־�ļ��洢��Ϣ��������
	unsigned int m_uiLogInfoCount;
	// ��־�ļ�����
	char m_cLogFileType;
}m_oLogOutPutStruct;

// ��INI�ļ��н����õ��ĳ���
// �ýṹ���еı���ֵֻ����INI�ļ��б��޸�
// �ݲ�֧���ڳ������޸ģ����ܻ�����ڴ��ͻ�������
typedef struct ConstVar_Struct
{
	// INI�ļ�·��
	string m_strINIFilePath;
	//____��������____
	// �����豸����
	unsigned int m_iInstrumentNum;
	// ADC���ݻ���������
	int m_iADCDataCountAll;
	// ʩ���������
	int m_iOptTaskCountAll;
	// һ�����ߵ�ʱ��
	int m_iOneSleepTime;
	// ��־����߳�д��־����ʱ����
	int m_iLogOutPutSleepTimes;
	// �����̷߳�������֡��ʱ����
	int m_iHeartBeatSleepTimes;
	// �װ��߳̽����װ���ʱ����
	int m_iHeadFrameSleepTimes;
	// IP��ַ�����߳���ʱ����
	int m_iIPSetFrameSleepTimes;
	// β���߳���ʱ����
	int m_iTailFrameSleepTimes;
	// ·�ɼ����߳���ʱ����
	int m_iMonitorSleepTimes;
	// ʱͳ�����߳���ʱ����
	int m_iTimeDelaySleepTimes;
	// ADC���������߳���ʱ����
	int m_iADCSetSleepTimes;
	// �����ѯ�߳���ʱ����
	int m_iErrorCodeSleepTimes;
	// ADC���ݽ����߳���ʱ����
	int m_iADCDataRecSleepTimes;
	// ADC���ݴ洢�߳���ʱ����
	int m_iADCDataSaveSleepTimes;
	// �ȴ��̹߳رյ���ʱ����
	int m_iCloseThreadSleepTimes;

	// �װ��ȶ�����
	int m_iHeadFrameStableTimes;
	// IP��ַ�������
	int m_iIPAddrResetTimes;
	// β���ȶ�����
	int m_iTailFrameStableTimes;
	// ·�ɼ����ȶ�ʱ��
	int m_iMonitorStableTime;
	// ����ϵͳ״̬-link
	int m_iLineSysStatusLink;
	// ����ϵͳ״̬-�ȶ�
	int m_iLineSysStatusStable;
	// ����ϵͳ״̬-�����ɼ�
	int m_iLineSysStatusNoise;
	// ����ϵͳ״̬-TB�ɼ�
	int m_iLineSysStatusSample;
	// ����ϵͳ�ﵽ�ȶ�״̬ʱ��
	int m_iLineSysStableTime;
	// ADC�������ò������
	int m_iADCSetOptNb;
	// ADC��ʼ�ɼ��������
	int m_iADCStartSampleOptNb;
	// ADCֹͣ�ɼ��������
	int m_iADCStopSampleOptNb;
	// ��������-����վ
	int m_iInstrumentTypeLAUX;
	// ��������-��Դվ
	int m_iInstrumentTypeLAUL;
	// ��������-�ɼ�վ
	int m_iInstrumentTypeFDU;
	// ��������-LCI
	int m_iInstrumentTypeLCI;
	// �����Ϸ�
	int m_iDirectionTop;
	// �����·�
	int m_iDirectionDown;
	// ������
	int m_iDirectionLeft;
	// �����ҷ�
	int m_iDirectionRight;
	// ��������
	int m_iDirectionCenter;
	// IP��ַ���õ���ʼ��ַ
	int m_iIPSetAddrStart;
	// IP��ַ���õļ��
	int m_iIPSetAddrInterval;
	// ·�ɵ�ַ���õ���ʼ��ַ
	int m_iRoutSetAddrStart;
	// ·�ɵ�ַ���õļ��
	int m_iRoutSetAddrInterval;
	// ���ù㲥�˿���ʼ��ַ
	int m_iBroadcastPortStart;
	// ����Ϊ�㲥IP
	unsigned int m_uiIPBroadcastAddr;
	// һ���ļ��ڴ洢�����豸ADC����֡��
	int m_iADCFrameSaveInOneFileNum;
	// �洢ADC���ݵ��ļ�ͷ����
	int m_iADCSaveHeadLineNum;
	// �洢ADC���ݵ����Ԥ����Ϣ�ֽ���
	int m_iADCSaveLeftInfoBytes;
	// �洢ADC���ݵ��ֽ���
	int m_iADCSaveDataBytes;
	// �洢ADC����֮��ļ���ֽ���
	int m_iADCSaveDataIntervalBytes;
	// �豸ADC���ݻ�������С
	int m_iADCDataBufSize;

	//____֡��ʽ����____
	// ֡ͷ����
	int m_iFrameHeadSize;
	// ͬ��֡ͷ
	char* m_cpFrameHeadCheck;
	// �����ֳ���1�ֽ�
	int m_iFrameCmdSize1B;
	// ���������1�ֽ�
	int m_iFramePacketSize1B;
	// ���������2�ֽ�
	int m_iFramePacketSize2B;
	// ���������4�ֽ�
	int m_iFramePacketSize4B;
	// ADC������ռ�ֽ���
	int m_iADCDataSize3B;
	// һ֡��ADC���ݸ���
	int m_iADCDataInOneFrameNum;
	// ADC����ָ֡��ƫ��������
	unsigned short m_usADCFramePointLimit;
	// �����ָ������ֵ
	int m_iCommandWordMaxNum;
	// 0x18�����������������ֽ���
	int m_iADCSetCommandMaxByte;
	// ����֡��������ֵ�趨
	char m_cSndFrameBufInit;
	// ���յ���������֡֡����
	int m_iRcvFrameSize;
	// ���͵���������֡֡����
	int m_iSndFrameSize;
	//____���������豸����������____
	// ������������
	unsigned short m_usSendSetCmd;
	// ���Ͳ�ѯ����
	unsigned short m_usSendQueryCmd;
	// ����ADC���������ط�����
	unsigned short m_usSendADCCmd;
	// ����
	char m_cCmdSn;
	// �װ�ʱ��
	char m_cCmdHeadFrameTime;
	// ����IP��ַ
	char m_cCmdLocalIPAddr;
	// ����ϵͳʱ��
	char m_cCmdLocalSysTime;
	// ����ʱ��������λ
	char m_cCmdLocalTimeFixedHigh;
	// ����ʱ��������λ
	char m_cCmdLocalTimeFixedLow;
	// �Զ����ݷ��ص�ַ
	char m_cCmdADCDataReturnAddr;
	// �Զ����ݷ��ض˿ں�����
	char m_cCmdADCDataReturnPort;
	// �˿ڵ������޺�����
	char m_cCmdADCDataReturnPortLimit;
	// ��������ȴ��˿ں�����
	char m_cCmdBroadCastPortSet;
	// ϵͳӲ��״̬����
	char m_cCmdFDUErrorCode;
	// TBʱ�̸�λ
	char m_cCmdTBHigh;
	// TBʱ�̵�λ
	char m_cCmdTbLow;
	// work_ctrl ����վ����
	char m_cCmdLAUXRoutOpenQuery;
	// ·�ɿ���
	char m_cCmdLAUXRoutOpenSet;
	// β������\����ʱ�̵�λ
	char m_cCmdTailRecSndTime;
	// �㲥����ȴ��˿�ƥ��
	char m_cCmdBroadCastPortSeted;
	// ����ADC��������������
	char m_cCmdADCSet;
	// ����ʱ��
	char m_cCmdNetTime;
	// ����վ����β������ʱ��
	char m_cCmdLineTailRecTimeLAUX;
	// ����վ������β������ʱ��
	char m_cCmdLAUTailRecTimeLAUX;
	// ����վ����1
	char m_cCmdLAUXErrorCode1;
	// ����վ����2
	char m_cCmdLAUXErrorCode2;
	// ����վ·�ɷ���
	char m_cCmdLAUXSetRout;
	// ����·��
	char m_cCmdReturnRout;
	// ���������������
	char m_cCmdEnd;

	// TB������ʱ��λ
	unsigned int m_uiTBSleepTimeHigh;
	// TB������ʱ��λ
	unsigned short m_usTBSleepTimeLow;
	// TB���ƣ�0x0001 ����TB����ADC���ݲɼ�
	unsigned short m_usCmdTBCtrlStartSample;
	// 0x0002 ����TB���ؿ���ADC���ݲɼ�����
	unsigned short m_usCmdTBLoseCtrlStartSample;
	// 0x0000 TB���ؿ���ADC����ֹͣ�ɼ�����
	unsigned short m_usCmdTBCtrlStopSample;
	// LED����
	unsigned short m_usCmdCtrlCloseLed;
	// �����־ָ��
	m_oLogOutPutStruct* m_pLogOutPut;
}m_oConstVarStruct;

// ��XML�ļ��н����õ�IP��ַ��������
typedef struct XMLIPSetupData_Struct
{
	// Դ��ַ
	unsigned int m_uiSrcIP;
	// LCI��IP��ַ
	unsigned int m_uiAimIP;
	// �Զ����ݷ��ص�ַ
	unsigned int m_uiADCDataReturnAddr;
}m_oXMLIPSetupDataStruct;
// ��XML�ļ��н����õ��˿���������
typedef struct XMLPortSetupData_Struct
{
	// LCI���յĶ˿ں�
	unsigned short m_usAimPort;
	// ����֡���ض˿�
	unsigned short m_usHeartBeatReturnPort;
	// �װ����ն˿�
	unsigned short m_usHeadFramePort;
	// IP��ַ���÷��ض˿�
	unsigned short m_usIPSetReturnPort;
	// β�����ն˿�
	unsigned short m_usTailFramePort;
	// β��ʱ�̲�ѯ���ն˿�
	unsigned short m_usTailTimeReturnPort;
	// ʱͳ����Ӧ��˿�
	unsigned short m_usTimeDelayReturnPort;
	// ADC��������Ӧ��˿�
	unsigned short m_usADCSetReturnPort;
	// �����ѯ���ض˿�
	unsigned short m_usErrorCodeReturnPort;
	// ADC���ݷ��ض˿�
	unsigned short m_usADCDataReturnPort;
}m_oXMLPortSetupDataStruct;
// ��XML�ļ��н����õ�ADC����������Ϣ
typedef struct XMLADCSetupData_Struct
{
	// ADC�������Ҳ������С
	int m_iSetADCSetSineSize;
	// ADC�������Ҳ�����
	char* m_cpSetADCSetSine;
	// ADC����ֹͣ���������С
	int m_iSetADCStopSampleSize;
	// ADC����ֹͣ��������
	char* m_cpSetADCStopSample;
	// ADC���ô�TB��Դ��λ��С
	int m_iSetADCOpenTBPowerLowSize;
	// ADC���ô�TB��Դ��λ
	char* m_cpSetADCOpenTBPowerLow;
	// ADC���ô�TB��Դ��λ��С
	int m_iSetADCOpenTBPowerHighSize;
	// ADC���ô�TB��Դ��λ
	char* m_cpSetADCOpenTBPowerHigh;
	// ADC���ô�TB���ص�λ��С
	int m_iSetADCOpenSwitchTBLowSize;
	// ADC���ô�TB���ص�λ
	char* m_cpSetADCOpenSwitchTBLow;
	// ADC���ô�TB���ظ�λ��С
	int m_iSetADCOpenSwitchTBHighSize;
	// ADC���ô�TB���ظ�λ
	char* m_cpSetADCOpenSwitchTBHigh;
	// ADC���ö��Ĵ�����С
	int m_iSetADCRegisterReadSize;
	// ADC���ö��Ĵ���
	char* m_cpSetADCRegisterRead;
	// ADC����д�Ĵ�����С
	int m_iSetADCRegisterWriteSize;
	// ADC����д�Ĵ���
	char* m_cpSetADCRegisterWrite;
	// ADC���ô�TB���ش�С
	int m_iSetADCTBSwitchOpenSize;
	// ADC���ô�TB����
	char* m_cpSetADCTBSwitchOpen;
	// ADC�������ô�С
	int m_iSetADCSampleSize;
	// ADC��������
	char* m_cpSetADCSample;
	// ADC��������������С
	int m_iSetADCReadContinuousSize;
	// ADC������������
	char* m_cpSetADCReadContinuous;
}m_oXMLADCSetupDataStruct;

// Survery SETUP�ṹ��
// Survery
typedef struct Survery_Struct
{
	// ���ߺ�
	unsigned int m_uiLine;
	// ����
	unsigned short m_usReceiverSectionSize;
	// ��������+�첨�����ͣ���100-103p1
	char* m_pcReceiverSection;
}m_oSurveryStruct;
// Point Code
typedef struct PointCode_Struct
{
	// �������
	unsigned int m_uiNb;
	// ����
	unsigned short m_usLabelSize;
	// ��ǩ����PointCode1
	char* m_pcLabel;
	// ����
	unsigned short m_usSensorTypeSize;
	// �첨�����ͣ���s1+cs
	char* m_pcSensorType;
}m_oPointCodeStruct;
// Sensor
typedef struct Sensor_Struct
{
	// �첨����
	unsigned int m_uiNb;
	// ����
	unsigned short m_usLabelSize;
	// ��ǩ����Sensor1
	char* m_pcLabel;
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
}m_oMarkerStruct;
// Aux
typedef struct Aux_Struct
{
	// �����ţ���Instrument�����е�Auxiliary Descr��Ӧ
	unsigned int m_uiNb;
	// ����
	unsigned short m_usLabelSize;
	// ��ǩ����pilot
	char* m_pcLabel;
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
	// ����
	unsigned short m_usCommentsSize;
	// ע�ͣ���Comments1
	char* m_pcComments;
}m_oAuxStruct;
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
	// ����
	unsigned short m_usLabelSize;
	// ��ǩ����pilot
	char* m_pcLabel;
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
	// ����
	unsigned short m_usCommentsSize;
	// ע�ͣ���Comments1
	char* m_pcComments;
}m_oBlastMachineStruct;
// Spread Type Setup
// Absolute
typedef struct Absolute_Struct
{
	// ������
	unsigned int m_uiNb;
	// ����
	unsigned short m_usLabelSize;
	// ��ǩ����Absolute1
	char* m_pcLabel;
	// ����
	unsigned short m_usAbsoluteSpreadSize;
	// �������У���1:1-127������������ʼ����-��ֹ���ţ�
	char* m_pcAbsoluteSpread;
}m_oAbsoluteStruct;
// Generic
typedef struct Generic_Struct
{
	// ������
	unsigned int m_uiNb;
	// ����
	unsigned short m_usLabelSize;
	// ��ǩ����Generic1
	char* m_pcLabel;
	// ����
	unsigned short m_usLineSize;
	// ��ͨ�������ͣ���50��g1+g2����50�Ե��������һ�����������Ϊ0Db,�ڶ���Ϊ12dB��
	char* m_pcLine;
	// ����
	unsigned short m_usSpreadSize;
	// ��ͨ���У���10(l1+ls)��10�Բ��ߣ���һ������ΪLine�ж����l1���ͣ��ڶ�����������
	char* m_pcSpread;
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
// LAULeakage
typedef struct LAULeakage_Struct
{
	// ����ֵ
	unsigned int m_uiLimit;
}m_oLAULeakageStruct;
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
	unsigned int m_uiFilter;//�˲������ͣ�1-0.8LIN��2-0.8MIN
	unsigned int m_uiSamplingRate; //��us��������
	unsigned int m_uiSamplingLength;//��ms����������
}m_oInstrumentTestBaseStruct, m_oSensorTestBaseStruct;
//Instrument Limit
typedef struct Instrument_SensorTestLimit_Struct
{
	unsigned int m_uiNb; //�����ţ�ֻ����
	unsigned short m_usDescrSize; //m_pcDescr ��С
	char* m_pcDescr; //����������������INSTRUMENT NOISE��ֻ����
	unsigned short m_usUnitSize; //	��λ size
	char* m_pcUnit;//	��λ��ֻ��������%
	unsigned int m_uiTestAim;
	unsigned int m_uiTestType;//�������ʹ��루ֻ����
	float m_fLimit;//����ֵ
}m_oInstrumentTestLimitStruct, m_oSensorTestLimitStruct;
// Instrument Test
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
// Sensor Test
typedef struct SensorTest_Struct
{
	unsigned int m_uiNb; //�����ţ�ֻ����
	unsigned int m_uiTestType;//�������ʹ��루ֻ����
	unsigned m_uiRecorded; //�Ƿ��¼�������ݣ�0-����¼��1-��¼
	unsigned short m_usAbsoluteSpreadSize; //�������� ��С
	char* m_pcAbsoluteSpread; //�������У���1:10-20
}m_oSensorTestStruct;
// Multiple Test
typedef struct MultipleTestKey_Struct
{
	unsigned int m_uiNb; //�����ţ�ֻ����
	unsigned short m_usTestNameSize;
	char* m_pcTestName;//������Ŀ���ƣ���Test1
	unsigned short m_usAuxiliaryDescrSize; //���������� ��С
	char* m_pcAuxiliaryDescr; //��������������a1-a3
	unsigned short m_usAbsoluteSpreadSize; //�������� ��С
	char* m_pcAbsoluteSpread; //�������У���1:10-20
	unsigned int m_uiDelayBetweenTest;//(ms)ÿ�β���֮��ļ��
	unsigned int m_uiRecordResults;//	�Ƿ��¼�������ݣ�0-����¼��1-��¼
	unsigned int m_uiRecordLength; //(ms)���Լ�¼ʱ��
	unsigned int m_uiTestFileNb;//�ļ����
	bool operator < (const MultipleTestKey_Struct& rhs) const
	{
		return (m_uiNb < rhs.m_uiNb);
	}
}m_oMultipleTestKeyStruct;
// Test Task
typedef struct MultipleTestTask_Struct
{
	unsigned int m_uiLineNb;//���ߺ�
	unsigned int m_uiTestType;//�������ʹ���
	unsigned int m_uiGain;//���棬1600mv��400mv
	unsigned int m_uiLoopLineNb;//��Ҫ�ظ����еĲ���������
	unsigned int m_uiNbLoops;//����ѭ������
}m_oMultipleTestTaskStruct;
// SeisMonitor
typedef struct SeisMonitorTest_Struct
{
	unsigned short m_usAbsoluteSpreadSize; //�������� ��С
	char* m_pcAbsoluteSpread; //�������У���1:10-20
}m_oSeisMonitorStruct;
// ���߿ͻ�����Ϣ
typedef struct LineSetupData_Struct
{
	// ��Line�������ļ��н����õ�����Ϣ����
	// Survery
	list<m_oSurveryStruct> m_olsSurveryStruct;
	// Point Code
	list<m_oPointCodeStruct> m_olsPointCodeStruct;
	// Sensor
	list<m_oSensorStruct> m_olsSensorStruct;
	// LAYOUT SETUP
	// Marker
	list<m_oMarkerStruct> m_olsMarkerStruct;
	// Aux
	list<m_oAuxStruct> m_olsAuxStruct;
	// Detour
	list<m_oDetourStruct> m_olsDetourStruct;
	// Mute
	list<m_oMuteStruct> m_olsMuteStruct;
	// BlastMachine
	list<m_oBlastMachineStruct> m_olsBlastMachineStruct;
	// Spread Type Setup
	// �������к��ڵ������
	map<unsigned int, list<m_oAbsoluteStruct>> m_oAbsoluteStructMap;
	// Generic
	list<m_oGenericStruct> m_olsGenericStruct;
	// Look
	m_oLookStruct m_oLook;
	// LAULeakage
	m_oLAULeakageStruct m_oLAULeakage;
	// Form Line
	list<m_oFormLineStruct> m_olsFormLineStruct;
	// Instrument Test base
	list<m_oInstrumentTestBaseStruct> m_olsInstrumentTestBaseStruct;
	// Sensor Test base
	list<m_oSensorTestBaseStruct> m_olsSensorTestBaseStruct;
	// Instrument Limit
	list<m_oInstrumentTestLimitStruct> m_olsInstrumentTestLimitStruct;
	// Sensor Limit
	list<m_oSensorTestLimitStruct> m_olsSensorTestLimitStruct;
	// Instrument Test
	list<m_oInstrumentTestStruct> m_olsInstrumentTestStruct;
	// Sensor Test
	list<m_oSensorTestStruct> m_olsSensorTestStruct;
	// Multiple Test
	map<m_oMultipleTestKeyStruct, list<m_oMultipleTestTaskStruct>> m_oMultpleTestStructMap;
	// SeisMonitor
	m_oSeisMonitorStruct m_oSeisMonitor;
}m_oLineSetupDataStruct;
// ��XML�ļ��н����õ�����Ϣ
typedef struct InstrumentCommInfo_Struct
{
	// ��Դͬ������
	CRITICAL_SECTION m_oSecCommInfo;
	/** XMLDOM�ļ�����*/
	CXMLDOMDocument m_oXMLDOMDocument;
	// ��XML�ļ��н����õ�IP��ַ��������
	m_oXMLIPSetupDataStruct m_oXMLIPSetupData;
	// ��XML�ļ��н����õ��˿���������
	m_oXMLPortSetupDataStruct m_oXMLPortSetupData;
	// ��XML�ļ��н����õ�ADC����������Ϣ
	m_oXMLADCSetupDataStruct m_oXMLADCSetupData;
	// ���߿ͻ�����Ϣ
	m_oLineSetupDataStruct m_oLineSetupData;
	// Dll��XML�����ļ�·��
	string m_strDllXMLFilePath;
	// ����XML�����ļ�·��
	string m_strLineXMLFilePath;
	// ʩ��XML�����ļ�·��
	string m_strOptXMLFilePath;
	// �����־ָ��
	m_oLogOutPutStruct* m_pLogOutPut;
}m_oInstrumentCommInfoStruct;

// ���豸ͨѶ����������
typedef struct InstrumentCommand_Struct
{
	// LCI��IP��ַ
	unsigned int m_uiAimIP;
	// LCI���յĶ˿ں�
	unsigned short m_usAimPort;
	// Դ��ַ
	unsigned int m_uiSrcIP;
	// Ŀ�ĵ�ַ
	unsigned int m_uiDstIP;
	// Ӧ��˿�
	unsigned short m_usReturnPort;
	// ���Ϊ1����������Ӧ��Ϊ2��ѯ����Ӧ��Ϊ3AD���������ط�
	unsigned short m_usCommand;
	// SN����8λΪ�������ͣ�0x01Ϊ����վ��0x02Ϊ��Դվ��0x03Ϊ�ɼ�վ
	unsigned int m_uiSN;
	// �װ�ʱ��
	unsigned int m_uiTimeHeadFrame;
	// ����IP��ַ
	unsigned int m_uiInstrumentIP;
	// ����ʱ��
	unsigned int m_uiSysTime;
	// ����ʱ��������λ
	unsigned int m_uiLocalTimeFixedHigh;
	// ����ʱ��������λ
	unsigned int m_uiLocalTimeFixedLow;
	// �Զ����ݷ��ص�ַ
	unsigned int m_uiADCDataReturnAddr;
	// �Զ����ݷ��ض˿�
	unsigned short m_usADCDataReturnPort;
	// �Զ����ݷ������ad_cmd(7)=1���˿ڵ�����=0���˿ڲ���
	unsigned short m_usADCDataReturnCmd;
	// �����������λΪ1ʱ�����ض˿��Զ���1��������ʱ���ص��޶˿�
	// �˿ڵ�������
	unsigned short m_usADCDataReturnPortLimitLow;
	// �˿ڵ�������
	unsigned short m_usADCDataReturnPortLimitHigh;
	// ��������ȴ��˿ڣ�ָ���ý�����λ���㲥����Ķ˿�
	unsigned int m_uiBroadCastPortSet;
	// �������ݴ������
	char m_cFDUErrorCodeDataCount;
	// ����������
	char m_cFDUErrorCodeCmdCount;
	// ʱ�䱨��״̬
	char m_cTimeStatus;
	// ����״̬
	char m_cCtrlStatus;
	// TBʱ�̸�λ
	unsigned int m_uiTBHigh;
	// TBʱ�̵�λ
	unsigned short m_usTBLow;
	// TB���ƣ�0x05����TB��0x06��AD�ɼ�����TB��0x00ֹͣAD��ad_ctrl(2)=1��LED����
	unsigned short m_usTBCtrl;
	// work_ctrl���ƽ���վ���պͷ�������ķ���
	// �ɸߵ���λÿλ�ֱ���Ʒ��Ϳڽ�����A��B������A��B�����ն˽�����A��B������A��B
	// =0Ϊ����=1Ϊ��
	char m_cLAUXRoutOpenQuery;
	// ·�ɿ���
	// �ɸ�λ����λ�ֱ���ƿ�������A����������B��������A��������B
	// =0Ϊ����=1Ϊ��
	char m_cLAUXRoutOpenSet;
	// β������ʱ�̣���14λ��Ч
	unsigned short m_usTailRecTime;
	// β������ʱ��//����վβ������ʱ�̣���14λ��Ч
	unsigned short m_usTailSndTime;
	// �㲥����ȴ��˿�ƥ�䣬������ڵ�һ��������λ�ã�����0x0a�����е�16λ�˿�ƥ����ܽ��չ㲥����
	unsigned int m_uiBroadCastPortSeted;
	// ����ʱ��
	unsigned int m_uiNetTime;
	// ����վ����Aβ������ʱ��
	unsigned short m_usLAUXTailRecTimeLineA;
	// ����վ����Bβ������ʱ��
	unsigned short m_usLAUXTailRecTimeLineB;
	// ����վ������Aβ������ʱ��
	unsigned short m_usLAUXTailRecTimeLAUXLineA;
	// ����վ������Bβ������ʱ��
	unsigned short m_usLAUXTailRecTimeLAUXLineB;
	// ����վ����A���ݹ���
	char m_cLAUXErrorCodeDataLineACount;
	// ����վ����B���ݹ���
	char m_cLAUXErrorCodeDataLineBCount;
	// ����վ������A���ݹ���
	char m_cLAUXErrorCodeDataLAUXLineACount;
	// ����վ������B���ݹ���
	char m_cLAUXErrorCodeDataLAUXLineBCount;
	// ����վ����ڹ���
	char m_cLAUXErrorCodeCmdCount;
	// ����վ�Ϸ�·��IP
	unsigned int m_uiRoutIPTop;
	// ����վ�·�·��IP
	unsigned int m_uiRoutIPDown;
	// ����վ��·��IP
	unsigned int m_uiRoutIPLeft;
	// ����վ�ҷ�·��IP
	unsigned int m_uiRoutIPRight;
	// ·��IP��ַ
	unsigned int m_uiRoutIP;
	// 0x18��������
	char* m_cpADCSet;
	// 0x18�������ݸ���
	int m_iADCSetNum;
	// ADC����ָ��ƫ����
	unsigned short m_usADCDataPoint;
	// ADC���ݲɼ�ʱ��������ʱ��
	unsigned int m_uiADCSampleSysTime;
	// ADC�������ݻ�����ָ��
	int* m_pADCData;
}m_oInstrumentCommandStruct;

// ����
typedef struct HeartBeatFrame_Struct
{
	// ����֡��Դͬ������
	CRITICAL_SECTION m_oSecHeartBeat;
	// ����֡������
	char* m_cpSndFrameData;
	// ���������ּ���
	char* m_cpCommandWord;
	// ���������ָ���
	unsigned short m_usCommandWordNum;
	// ����֡����
	m_oInstrumentCommandStruct* m_pCommandStruct;
	// ����Socket�׽���
	SOCKET m_oHeartBeatSocket;
}m_oHeartBeatFrameStruct;

// �װ�
typedef struct HeadFrame_Struct
{
	// �װ�֡��Դͬ������
	CRITICAL_SECTION m_oSecHeadFrame;
	// ����˿ڽ��ջ�������С
	unsigned int m_uiRcvBufferSize;
	// ����֡������
	char* m_cpRcvFrameData;
	// �װ�֡����
	m_oInstrumentCommandStruct* m_pCommandStruct;
	// �װ�Socket�׽���
	SOCKET m_oHeadFrameSocket;
}m_oHeadFrameStruct;

// IP��ַ����
typedef struct IPSetFrame_Struct
{
	// IP��ַ����֡��Դͬ������
	CRITICAL_SECTION m_oSecIPSetFrame;
	// ����˿ڷ��ͻ�������С
	unsigned int m_uiSndBufferSize;
	// ����֡������
	char* m_cpSndFrameData;
	// IP��ַ���������ּ���
	char* m_cpCommandWord;
	// IP��ַ���������ָ���
	unsigned short m_usCommandWordNum;
	// IP��ַ����֡����
	m_oInstrumentCommandStruct* m_pCommandStructSet;
	// ����˿ڽ��ջ�������С
	unsigned int m_uiRcvBufferSize;
	// ����֡������
	char* m_cpRcvFrameData;
	// IP��ַ����Ӧ��֡����
	m_oInstrumentCommandStruct* m_pCommandStructReturn;
	// IP��ַ����Socket�׽���
	SOCKET m_oIPSetFrameSocket;
}m_oIPSetFrameStruct;

// β��
typedef struct TailFrame_Struct
{
	// β��֡��Դͬ������
	CRITICAL_SECTION m_oSecTailFrame;
	// ����˿ڽ��ջ�������С
	unsigned int m_uiRcvBufferSize;
	// ����֡������
	char* m_cpRcvFrameData;
	// β��֡����
	m_oInstrumentCommandStruct* m_pCommandStruct;
	// β��Socket�׽���
	SOCKET m_oTailFrameSocket;
}m_oTailFrameStruct;

// β��ʱ��
typedef struct TailTimeFrame_Struct
{
	// β��ʱ��֡��Դͬ������
	CRITICAL_SECTION m_oSecTailTimeFrame;
	// ����˿ڽ��ջ�������С
	unsigned int m_uiRcvBufferSize;
	// ����֡������
	char* m_cpRcvFrameData;
	// β��ʱ��Ӧ��֡����
	m_oInstrumentCommandStruct* m_pCommandStructReturn;
	// ����˿ڷ��ͻ�������С
	unsigned int m_uiSndBufferSize;
	// ����֡������
	char* m_cpSndFrameData;
	// β��ʱ�̲�ѯ�����ּ���
	char* m_cpCommandWord;
	// β��ʱ�̲�ѯ�����ָ���
	unsigned short m_usCommandWordNum;
	// β��ʱ�̷���֡����
	m_oInstrumentCommandStruct* m_pCommandStructSet;
	// β��ʱ��Socket�׽���
	SOCKET m_oTailTimeFrameSocket;
}m_oTailTimeFrameStruct;

// ʱͳ����
typedef struct TimeDelayFrame_Struct
{
	// ʱͳ����֡��Դͬ������
	CRITICAL_SECTION m_oSecTimeDelayFrame;
	// ����˿ڽ��ջ�������С
	unsigned int m_uiRcvBufferSize;
	// ����֡������
	char* m_cpRcvFrameData;
	// ʱͳ����Ӧ��֡����
	m_oInstrumentCommandStruct* m_pCommandStructReturn;
	// ����˿ڷ��ͻ�������С
	unsigned int m_uiSndBufferSize;
	// ����֡������
	char* m_cpSndFrameData;
	// ʱͳ���������ּ���
	char* m_cpCommandWord;
	// ʱͳ���������ָ���
	unsigned short m_usCommandWordNum;
	// ʱͳ���÷���֡����
	m_oInstrumentCommandStruct* m_pCommandStructSet;
	// ʱͳ����Socket�׽���
	SOCKET m_oTimeDelayFrameSocket;
}m_oTimeDelayFrameStruct;

// ADC��������
typedef struct ADCSetFrame_Struct
{
	// ADC��������֡��Դͬ������
	CRITICAL_SECTION m_oSecADCSetFrame;
	// ����˿ڽ��ջ�������С
	unsigned int m_uiRcvBufferSize;
	// ����֡������
	char* m_cpRcvFrameData;
	// ADC��������Ӧ��֡����
	m_oInstrumentCommandStruct* m_pCommandStructReturn;
	// ����˿ڷ��ͻ�������С
	unsigned int m_uiSndBufferSize;
	// ����֡������
	char* m_cpSndFrameData;
	// ADC�������������ּ���
	char* m_cpCommandWord;
	// ADC�������������ָ���
	unsigned short m_usCommandWordNum;
	// ADC�������÷���֡����
	m_oInstrumentCommandStruct* m_pCommandStructSet;
	// ADC��������Socket�׽���
	SOCKET m_oADCSetFrameSocket;
}m_oADCSetFrameStruct;

// �����ѯ
typedef struct ErrorCodeFrame_Struct
{
	// ADC��������֡��Դͬ������
	CRITICAL_SECTION m_oSecErrorCodeFrame;
	// ����˿ڽ��ջ�������С
	unsigned int m_uiRcvBufferSize;
	// ����֡������
	char* m_cpRcvFrameData;
	// Ӧ��֡����
	m_oInstrumentCommandStruct* m_pCommandStructReturn;
	// ����˿ڷ��ͻ�������С
	unsigned int m_uiSndBufferSize;
	// ����֡������
	char* m_cpSndFrameData;
	// �����ѯ�����ּ���
	char* m_cpCommandWord;
	// �����ѯ�����ָ���
	unsigned short m_usCommandWordNum;
	// ����֡����
	m_oInstrumentCommandStruct* m_pCommandStructSet;
	// �����ѯSocket�׽���
	SOCKET m_oErrorCodeFrameSocket;
}m_oErrorCodeFrameStruct;

// ADC���ݽ���
typedef struct ADCDataFrame_Struct
{
	// ADC���ݽ���֡��Դͬ������
	CRITICAL_SECTION m_oSecADCDataFrame;
	// ����˿ڽ��ջ�������С
	unsigned int m_uiRcvBufferSize;
	// ����֡������
	char* m_cpRcvFrameData;
	// Ӧ��֡����
	m_oInstrumentCommandStruct* m_pCommandStructReturn;
	// ����˿ڷ��ͻ�������С
	unsigned int m_uiSndBufferSize;
	// ����֡������
	char* m_cpSndFrameData;
	// ����֡����
	m_oInstrumentCommandStruct* m_pCommandStructSet;
	// ADC���ݽ��պ��ط�Socket�׽���
	SOCKET m_oADCDataFrameSocket;
}m_oADCDataFrameStruct;

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
	unsigned char m_ucLAUXRoutOpenSet;
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
	bool m_bStopMarking;
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

// ����λ�õ�ṹ��
typedef struct InstrumentLocation_Struct
{
	InstrumentLocation_Struct(int iLineIndex, int iPointIndex)
	{
		this->m_iLineIndex = iLineIndex;
		this->m_iPointIndex = iPointIndex;
	}
	~InstrumentLocation_Struct()
	{
	}
	bool operator == (const InstrumentLocation_Struct& rhs) const
	{
		return ((m_iLineIndex == rhs.m_iLineIndex) && (m_iPointIndex == rhs.m_iPointIndex));
	}
	bool operator < (const InstrumentLocation_Struct& rhs) const
	{
		if (m_iLineIndex == rhs.m_iLineIndex)
		{
			return (m_iPointIndex < rhs.m_iPointIndex);
		}
		else
		{
			return (m_iLineIndex < rhs.m_iLineIndex);
		}
	}
	// �ߺ�
	int m_iLineIndex;
	// ���
	int m_iPointIndex;
}m_oInstrumentLocationStruct;

// ��������
typedef struct InstrumentList_Struct
{
	// ����������Դͬ������
	CRITICAL_SECTION m_oSecInstrumentList;
	/** ��������ָ��*/
	m_oInstrumentStruct* m_pArrayInstrument;
	/** ������������*/
	list<m_oInstrumentStruct*> m_olsInstrumentFree;
	/** ����IP��ַ����������*/
	hash_map<unsigned int, m_oInstrumentStruct*> m_oIPSetMap;
	// ����SN������
	hash_map<unsigned int, m_oInstrumentStruct*> m_oSNInstrumentMap;
	// ����IP��ַ������
	hash_map<unsigned int, m_oInstrumentStruct*> m_oIPInstrumentMap;
	// δ���ADC�������õ���������
	hash_map<unsigned int, m_oInstrumentStruct*> m_oADCSetInstrumentMap;
	// ����λ��������
	map<m_oInstrumentLocationStruct, m_oInstrumentStruct*> m_oInstrumentLocationMap;
	// ����ϵͳ�����仯��ʱ��
	unsigned int m_uiLineChangeTime;
	// ����״̬�ɲ��ȶ���Ϊ�ȶ�
	bool m_bLineStableChange;
	/** ��������*/
	unsigned int m_uiCountAll;
	/** ������������*/
	unsigned int m_uiCountFree;
	// �Ƿ���·��IP�ֶ�����ADC����
	bool m_bSetByHand;
}m_oInstrumentListStruct;

// ·�����Խṹ��
typedef struct Rout_Struct
{
	/** ��·�������е�λ��*/
	unsigned int m_uiIndex;
	/** ·���Ƿ�ʹ����*/
	bool m_bInUsed;
	/** ·��IP��ַ*/
	unsigned int m_uiRoutIP;
	/** ·�ɷ��� 1-�ϣ�2-�£�3-��4��*/
	int m_iRoutDirection;
	/** ·��ͷ����*/
	m_oInstrumentStruct* m_pHead;
	/** ·��β����*/
	m_oInstrumentStruct* m_pTail;
	/** ·����������*/
	list<m_oInstrumentStruct*> m_olsRoutInstrument;
	/** ·��ʱ��*/
	unsigned int m_uiRoutTime;
	/** ·���Ƿ�Ϊ������·��*/
	bool m_bRoutLaux;
	/** ·���Ƿ���յ�ADC���ò���Ӧ��*/
	bool m_bADCSetReturn;
	// ·���Ƿ���ADC��������֡
	bool m_bADCSetRout;
	// ��·�ɷ����������ĸ���
	unsigned int m_uiInstrumentNum;
}m_oRoutStruct;

// ·�ɶ��нṹ��
typedef struct RoutList_Struct
{
	// ·�ɶ�����Դͬ������
	CRITICAL_SECTION m_oSecRoutList;
	/** ·������ָ��*/
	m_oRoutStruct* m_pArrayRout;
	/** ����·�ɶ���*/
	list<m_oRoutStruct*> m_olsRoutFree;
	// ����·�ɵ�ַ������
	hash_map<unsigned int, m_oRoutStruct*> m_oRoutMap;
	// ��Ҫɾ��·��������·��������
	hash_map<unsigned int, m_oRoutStruct*> m_oRoutDeleteMap;
	// ����ʱͳ��������У���ԱΪ·��IP
	list<unsigned int> m_olsTimeDelayTaskQueue;
	// ����ʱͳ��������ת����
	list<unsigned int> m_olsTimeDelayTemp;
	// ADC����������������
	hash_map<unsigned int, m_oRoutStruct*> m_oADCSetRoutMap;
	/** ·������*/
	unsigned int m_uiCountAll;
	/** ����·������*/
	unsigned int m_uiCountFree;
}m_oRoutListStruct;

// ���ݴ洢�������ṹ��
typedef struct ADCDataBuf_Struct
{
	// �������Ƿ�ʹ����
	bool m_bInUsed;
	// ADC���ݴ洢������
	int* m_pADCDataBuf;
	// ���ݴ洢֡��ţ���0��ʼ
	unsigned int m_uiFrameNb;
	// ��������SN
	unsigned int m_uiSN;
	// ֡�ı���ʱ��
	unsigned int m_uiSysTime;
	// ���������
	unsigned int m_uiIndex;
}m_oADCDataBufStruct;

// ���ݴ洢�������ṹ��
typedef struct ADCDataBufArray_Struct
{
	// ��������Դͬ������
	CRITICAL_SECTION m_oSecADCDataBufArray;
	/** ����������ָ��*/
	m_oADCDataBufStruct* m_pArrayADCDataBuf;
	/** ����������*/
	list<m_oADCDataBufStruct*> m_olsADCDataBufFree;
	// д���ļ������ݻ���������
	list<m_oADCDataBufStruct*> m_olsADCDataToWrite;
	/** ����������*/
	unsigned int m_uiCountAll;
	/** ���л���������*/
	unsigned int m_uiCountFree;
}m_oADCDataBufArrayStruct;

// ��ʧ֡IP��ַ��ƫ�����ṹ��
typedef struct ADCLostFrameKey_Struct
{
	ADCLostFrameKey_Struct(unsigned int uiIP, unsigned short usADCFramePointNb)
	{
		this->m_uiIP = uiIP;
		this->m_usADCFramePointNb = usADCFramePointNb;
	}
	~ADCLostFrameKey_Struct()
	{
	}
	bool operator == (const ADCLostFrameKey_Struct& rhs) const
	{
		return ((m_uiIP == rhs.m_uiIP) && (m_usADCFramePointNb == rhs.m_usADCFramePointNb));
	}
	bool operator < (const ADCLostFrameKey_Struct& rhs) const
	{
		if (m_uiIP == rhs.m_uiIP)
		{
			return (m_usADCFramePointNb < rhs.m_usADCFramePointNb);
		}
		else
		{
			return (m_uiIP < rhs.m_uiIP);
		}
	}
	// ��֡��ָ��ƫ����
	unsigned short m_usADCFramePointNb;
	// ��֡��IP��ַ
	unsigned int m_uiIP;
}m_oADCLostFrameKeyStruct;

// ��ʧ֡�ṹ��
typedef struct ADCLostFrame_Struct
{
	// ��ʧ֡�ط�����
	unsigned int m_uiCount;
	// ��֡���ļ��ڵ�֡��ţ���0��ʼ
	unsigned int m_uiFrameNb;
	// ��ʧ֡�ı���ʱ��
	unsigned int m_uiSysTime;
	// �Ƿ��Ѿ��յ�Ӧ��
	bool m_bReturnOk;
}m_oADCLostFrameStruct;

// ����ʩ���������ṹ��
typedef struct OptInstrument_Struct
{
	// SN
	unsigned int m_uiSN;
	/** ���ߺ�*/
	int m_iLineIndex;
	/** ����*/
	int m_iPointIndex;
	bool operator < (const OptInstrument_Struct& rhs) const
	{
		if (m_iLineIndex == rhs.m_iLineIndex)
		{
			return (m_iPointIndex < rhs.m_iPointIndex);
		}
		else
		{
			return (m_iLineIndex < rhs.m_iLineIndex);
		}
	}
}m_oOptInstrumentStruct;

// ʩ������ṹ��
typedef struct OptTask_Struct
{
	// �����Ƿ�ʹ����
	bool m_bInUsed;
	// �������
	unsigned int m_uiIndex;
	// ʩ������ʼ��¼������֡��
	unsigned int m_uiStartFrame;
	// ʩ����������ļ�ָ��
	FILE* m_pFile;
	// ʩ���������ǰһ���ļ����ļ�ָ��
	FILE* m_pPreviousFile;
	// ���µ��ļ��洢���
	unsigned int m_uiFileSaveNb;
	// ʩ�����ݴ洢�ļ�·��
	string m_SaveLogFilePath;
	// ʩ�������������ؼ���ΪSN������Ϊ�к�
	hash_map<unsigned int, unsigned int> m_oSNMap;
	// ����ʩ������������
	list<m_oOptInstrumentStruct> m_olsOptInstrument;
}m_oOptTaskStruct;

// ʩ������ṹ������
typedef struct OptTaskArray_Struct
{
	// ��Դͬ������
	CRITICAL_SECTION m_oSecOptTaskArray;
	/** ʩ����������ָ��*/
	m_oOptTaskStruct* m_pArrayOptTask;
	// ���е�ʩ���������
	list<m_oOptTaskStruct*> m_olsOptTaskFree;
	// ���ڽ��е�ʩ����������
	hash_map<unsigned int, m_oOptTaskStruct*> m_oOptTaskWorkMap;
	/** ʩ����������*/
	unsigned int m_uiCountAll;
	/** ������������*/
	unsigned int m_uiCountFree;
	// ʩ���������ݴ洢�ļ��м���
	unsigned int m_uiADCDataFolderNb;
	// ʩ�����ݴ洢�ļ���·��
	string m_SaveLogFolderPath;
}m_oOptTaskArrayStruct;

// �߳̽ṹ��
typedef struct Thread_Struct
{
	// �߳̾��
	HANDLE m_hThread;
	// �̺߳�
	DWORD m_dwThreadID;
	//�Ƿ���״̬
	bool m_bWork;
	// �Ƿ�ر��߳�
	bool m_bClose;
	// �߳̽����¼�
	HANDLE m_hThreadClose;
	// ����ָ��
	m_oConstVarStruct* m_pConstVar;
	// �����־ָ��
	m_oLogOutPutStruct* m_pLogOutPut;
}m_oThreadStruct;

// ��־����߳�
typedef struct LogOutPutThread_Struct
{
	// ��Դͬ������
	CRITICAL_SECTION m_oSecLogOutPutThread;
	// �߳̽ṹ��ָ��
	m_oThreadStruct* m_pThread;
	// �����־ָ��
	m_oLogOutPutStruct* m_pLogOutPutTimeDelay;
	// �����־ָ��
	m_oLogOutPutStruct* m_pLogOutPutErrorCode;
	// �����־ָ��
	m_oLogOutPutStruct* m_pLogOutPutADCFrameTime;
}m_oLogOutPutThreadStruct;

// �����߳�
typedef struct HeartBeatThread_Struct
{
	// ��Դͬ������
	CRITICAL_SECTION m_oSecHeartBeatThread;
	// �߳̽ṹ��ָ��
	m_oThreadStruct* m_pThread;
	// ����ָ֡��
	m_oHeartBeatFrameStruct* m_pHeartBeatFrame;
}m_oHeartBeatThreadStruct;

// �װ��߳�
typedef struct HeadFrameThread_Struct
{
	// ��Դͬ������
	CRITICAL_SECTION m_oSecHeadFrameThread;
	// �߳̽ṹ��ָ��
	m_oThreadStruct* m_pThread;
	// �װ�ָ֡��
	m_oHeadFrameStruct* m_pHeadFrame;
	// �������нṹ��ָ��
	m_oInstrumentListStruct* m_pInstrumentList;
	// ·�ɶ��нṹ��ָ��
	m_oRoutListStruct* m_pRoutList;
}m_oHeadFrameThreadStruct;

// IP��ַ�����߳�
typedef struct IPSetFrameThread_Struct
{
	// ��Դͬ������
	CRITICAL_SECTION m_oSecIPSetFrameThread;
	// �߳̽ṹ��ָ��
	m_oThreadStruct* m_pThread;
	// IP��ַ����ָ֡��
	m_oIPSetFrameStruct* m_pIPSetFrame;
	// �������нṹ��ָ��
	m_oInstrumentListStruct* m_pInstrumentList;
	// ·�ɶ��нṹ��ָ��
	m_oRoutListStruct* m_pRoutList;
}m_oIPSetFrameThreadStruct;

// β���߳�
typedef struct TailFrameThread_Struct
{
	// ��Դͬ������
	CRITICAL_SECTION m_oSecTailFrameThread;
	// �߳̽ṹ��ָ��
	m_oThreadStruct* m_pThread;
	// β��ָ֡��
	m_oTailFrameStruct* m_pTailFrame;
	// �������нṹ��ָ��
	m_oInstrumentListStruct* m_pInstrumentList;
	// ·�ɶ��нṹ��ָ��
	m_oRoutListStruct* m_pRoutList;
}m_oTailFrameThreadStruct;

// ʱͳ�߳�
typedef struct TimeDelayThread_Struct
{
	// ��Դͬ������
	CRITICAL_SECTION m_oSecTimeDelayThread;
	// �߳̽ṹ��ָ��
	m_oThreadStruct* m_pThread;
	// β��ʱ��ָ֡��
	m_oTailTimeFrameStruct* m_pTailTimeFrame;
	// ʱͳ����ָ֡��
	m_oTimeDelayFrameStruct* m_pTimeDelayFrame;
	// �������нṹ��ָ��
	m_oInstrumentListStruct* m_pInstrumentList;
	// ·�ɶ��нṹ��ָ��
	m_oRoutListStruct* m_pRoutList;
	// ADC��ʼ���ݲɼ���־λ
	bool m_bADCStartSample;
	// ������
	unsigned int m_uiCounter;
	// �����־ָ��
	m_oLogOutPutStruct* m_pLogOutPutTimeDelay;
}m_oTimeDelayThreadStruct;

// ADC���������߳�
typedef struct ADCSetThread_Struct
{
	// ��Դͬ������
	CRITICAL_SECTION m_oSecADCSetThread;
	// �߳̽ṹ��ָ��
	m_oThreadStruct* m_pThread;
	// ADC��������ָ֡��
	m_oADCSetFrameStruct* m_pADCSetFrame;
	// �������нṹ��ָ��
	m_oInstrumentListStruct* m_pInstrumentList;
	// ·�ɶ��нṹ��ָ��
	m_oRoutListStruct* m_pRoutList;
	// ADC�����������
	unsigned int m_uiADCSetOperationNb;
	// ������
	unsigned int m_uiCounter;
	// ADC��ʼ���ݲɼ���־λ
	bool m_bADCStartSample;
	// ADCֹͣ���ݲɼ���־λ
	bool m_bADCStopSample;
	// ������ϵͳʱ��
	unsigned int m_uiLocalSysTime;
	// ��һ�ο�ʼ�����Ĳ���ʱ��
	unsigned int m_uiTBTimeOld;
	// ��XML�ļ��н����õ�����Ϣ
	m_oInstrumentCommInfoStruct* m_pCommInfo;
	// �����־ָ��
	m_oLogOutPutStruct* m_pLogOutPutADCFrameTime;
}m_oADCSetThreadStruct;

// �����ѯ�߳�
typedef struct ErrorCodeThread_Struct
{
	// ��Դͬ������
	CRITICAL_SECTION m_oSecErrorCodeThread;
	// �߳̽ṹ��ָ��
	m_oThreadStruct* m_pThread;
	// �����ѯָ֡��
	m_oErrorCodeFrameStruct* m_pErrorCodeFrame;
	// �������нṹ��ָ��
	m_oInstrumentListStruct* m_pInstrumentList;
	// ·�ɶ��нṹ��ָ��
	m_oRoutListStruct* m_pRoutList;
	// �����ѯ��־ָ��
	m_oLogOutPutStruct* m_pLogOutPutErrorCode;
}m_oErrorCodeThreadStruct;

// ·�ɼ����߳�
typedef struct MonitorThread_Struct
{
	// ��Դͬ������
	CRITICAL_SECTION m_oSecMonitorThread;
	// �߳̽ṹ��ָ��
	m_oThreadStruct* m_pThread;
	// �������нṹ��ָ��
	m_oInstrumentListStruct* m_pInstrumentList;
	// ·�ɶ��нṹ��ָ��
	m_oRoutListStruct* m_pRoutList;
	// ʱͳ�߳�ָ��
	m_oTimeDelayThreadStruct* m_pTimeDelayThread;
	// ADC���������߳�
	m_oADCSetThreadStruct* m_pADCSetThread;
	// �����ѯ�߳�
	m_oErrorCodeThreadStruct* m_pErrorCodeThread;
}m_oMonitorThreadStruct;

// ADC���ݽ����߳�
typedef struct ADCDataRecThread_Struct
{
	// ��Դͬ������
	CRITICAL_SECTION m_oSecADCDataRecThread;
	// �߳̽ṹ��ָ��
	m_oThreadStruct* m_pThread;
	// �����ѯָ֡��
	m_oADCDataFrameStruct* m_pADCDataFrame;
	// �������нṹ��ָ��
	m_oInstrumentListStruct* m_pInstrumentList;
	// �����ѯ��־ָ��
	m_oLogOutPutStruct* m_pLogOutPutADCFrameTime;
	// ���ݴ洢�������ṹ��ָ��
	m_oADCDataBufArrayStruct* m_pADCDataBufArray;
	// ��һ֡�ı���ʱ��
	unsigned int m_uiADCDataFrameSysTime;
	// ���ļ�����֡������
	int m_iADCFrameCount;
	// ��֡������
	map<m_oADCLostFrameKeyStruct, m_oADCLostFrameStruct> m_oADCLostFrameMap;
	// �������ݻص�����
	ProSampleDateCallBack m_oProSampleDataCallBack;
}m_oADCDataRecThreadStruct;

// ʩ���������ݴ洢�߳�
typedef struct ADCDataSaveThread_Struct
{
	// ��Դͬ������
	CRITICAL_SECTION m_oSecADCDataSaveThread;
	// �߳̽ṹ��ָ��
	m_oThreadStruct* m_pThread;
	// ���ݴ洢�������ṹ��ָ��
	m_oADCDataBufArrayStruct* m_pADCDataBufArray;
	// ʩ����������ṹ��ָ��
	m_oOptTaskArrayStruct* m_pOptTaskArray;
}m_oADCDataSaveThreadStruct;

// �����ṹ��
typedef struct Environment_Struct
{
	// ��INI�ļ��õ��ĳ�����Ϣ
	m_oConstVarStruct* m_pConstVar;
	// ��XML�ļ��õ���������ͨѶ��Ϣ�ṹ
	m_oInstrumentCommInfoStruct* m_pInstrumentCommInfo;
	// ����֡�ṹ
	m_oHeartBeatFrameStruct* m_pHeartBeatFrame;
	// �װ�֡�ṹ
	m_oHeadFrameStruct* m_pHeadFrame;
	// IP��ַ����֡�ṹ
	m_oIPSetFrameStruct* m_pIPSetFrame;
	// β��֡�ṹ
	m_oTailFrameStruct* m_pTailFrame;
	// β��ʱ��֡�ṹ
	m_oTailTimeFrameStruct* m_pTailTimeFrame;
	// ʱͳ����֡�ṹ
	m_oTimeDelayFrameStruct* m_pTimeDelayFrame;
	// ADC��������֡�ṹ
	m_oADCSetFrameStruct* m_pADCSetFrame;
	// �����ѯ֡�ṹ
	m_oErrorCodeFrameStruct* m_pErrorCodeFrame;
	// ADC����֡�ṹ
	m_oADCDataFrameStruct* m_pADCDataFrame;
	// ������־����ṹ
	m_oLogOutPutStruct* m_pLogOutPutOpt;
	// ʱͳ��־����ṹ
	m_oLogOutPutStruct* m_pLogOutPutTimeDelay;
	// �����ѯ��־����ṹ
	m_oLogOutPutStruct* m_pLogOutPutErrorCode;
	// ֡ʱ���ƫ������־����ṹ
	m_oLogOutPutStruct* m_pLogOutPutADCFrameTime;
	// �������нṹ
	m_oInstrumentListStruct* m_pInstrumentList;
	// ·�ɶ��нṹ
	m_oRoutListStruct* m_pRoutList;
	// ���ݴ洢�������ṹ��ָ��
	m_oADCDataBufArrayStruct* m_pADCDataBufArray;
	// ʩ����������ṹ��ָ��
	m_oOptTaskArrayStruct* m_pOptTaskArray;

	// ��־����߳�
	m_oLogOutPutThreadStruct* m_pLogOutPutThread;
	// �����߳�
	m_oHeartBeatThreadStruct* m_pHeartBeatThread;
	// �װ������߳�
	m_oHeadFrameThreadStruct* m_pHeadFrameThread;
	// IP��ַ�����߳�
	m_oIPSetFrameThreadStruct* m_pIPSetFrameThread;
	// β�������߳�
	m_oTailFrameThreadStruct* m_pTailFrameThread;
	// ·�ɼ����߳�
	m_oMonitorThreadStruct* m_pMonitorThread;
	// ʱͳ�߳�
	m_oTimeDelayThreadStruct* m_pTimeDelayThread;
	// ADC���������߳�
	m_oADCSetThreadStruct* m_pADCSetThread;
	// �����ѯ�߳�
	m_oErrorCodeThreadStruct* m_pErrorCodeThread;
	// ADC���ݽ����߳�
	m_oADCDataRecThreadStruct* m_pADCDataRecThread;
	// ʩ���������ݴ洢�߳�
	m_oADCDataSaveThreadStruct* m_pADCDataSaveThread;
}m_oEnvironmentStruct;

// functions declarations
/************************************************************************/
/* ���ܺ���                                                             */
/************************************************************************/
// �õ�֡��֡����
MatrixServerDll_API void GetFrameInfo(char* pFrameData, int iSize, string* strFrameData);
// ��CStringת��Ϊchar����
MatrixServerDll_API void ParseCStringToArray(char** pData, int iSize, CString str);
// �ж��ļ��Ƿ����
MatrixServerDll_API bool IfFileExist(CString str);
// У��֡��ͬ����
MatrixServerDll_API bool CheckInstrumentFrameHead(char* pFrameData, char* pFrameHeadCheck, int iCheckSize);
// ����֡��ͬ����
MatrixServerDll_API bool MakeInstrumentFrameHead(char* pFrameData, char* pFrameHeadCheck, int iCheckSize);
// ����֡���ݽ�������
MatrixServerDll_API bool ResetInstrumentFramePacket(m_oInstrumentCommandStruct* pCommand);
// �������豸ͨѶ����֡����
MatrixServerDll_API bool ParseInstrumentFrame(m_oInstrumentCommandStruct* pCommand, 
	char* pFrameData, m_oConstVarStruct* pConstVar);
// �������豸ͨѶ֡
MatrixServerDll_API bool MakeInstrumentFrame(m_oInstrumentCommandStruct* pCommand, 
	m_oConstVarStruct* pConstVar,char* pFrameData, char* pCommandWord = NULL, 
	unsigned short usCommandWordNum = 0);
// ����CSocket���ն˿ڲ��󶨶˿ں�IP��ַ
MatrixServerDll_API SOCKET CreateInstrumentSocket(unsigned short usPort, 
	unsigned int uiIP, m_oLogOutPutStruct* pLogOutPut = NULL);
// ���ù㲥ģʽ
MatrixServerDll_API void SetInstrumentSocketBroadCast(SOCKET oSocket, 
	m_oLogOutPutStruct* pLogOutPut = NULL);
// ���ö˿ڽ��ջ���������֡����
MatrixServerDll_API void SetRcvBufferSize(SOCKET oSocket, int iRcvBufferSize, 
	m_oLogOutPutStruct* pLogOutPut = NULL);
// ���ö˿ڷ��ͻ���������֡����
MatrixServerDll_API void SetSndBufferSize(SOCKET oSocket, int iSndBufferSize, 
	m_oLogOutPutStruct* pLogOutPut = NULL);
// �õ�������ջ������յ���֡����
MatrixServerDll_API DWORD GetFrameCount(SOCKET oSocket, int iRcvFrameSize, 
	m_oLogOutPutStruct* pLogOutPut = NULL);
// �õ�֡����
MatrixServerDll_API bool GetFrameData(SOCKET oSocket, char* pFrameData, 
	int iRcvFrameSize, m_oLogOutPutStruct* pLogOutPut = NULL);
// ��ս���֡������
MatrixServerDll_API void ClearRcvFrameBuf(SOCKET oSocket, char* pFrameData, 
	int iRcvFrameSize, m_oLogOutPutStruct* pLogOutPut = NULL);
// ����֡
MatrixServerDll_API bool SendFrame(SOCKET oSocket, char* pFrameData,int iSndFrameSize, 
	unsigned short usPort, unsigned int uiIP, m_oLogOutPutStruct* pLogOutPut = NULL);
// ��ʼ���׽��ֿ�
MatrixServerDll_API void OnInitSocketLib(m_oLogOutPutStruct* pLogOutPut = NULL);
// �ͷ��׽��ֿ�
MatrixServerDll_API void OnCloseSocketLib(m_oLogOutPutStruct* pLogOutPut = NULL);
// �ر�Socket�׽���
MatrixServerDll_API void OnCloseSocket(SOCKET oSocket);
// ��ս��ջ�����
MatrixServerDll_API void OnClearSocketRcvBuf(SOCKET oSocket, int iRcvFrameSize);
// �õ�·�ɷ�������������
MatrixServerDll_API bool OnGetRoutInstrumentNum(int iLineIndex, int iPointIndex, int iDirection, 
	m_oEnvironmentStruct* pEnv, unsigned int& uiInstrumentNum);

/************************************************************************/
/* ��־���                                                             */
/************************************************************************/
// ������־����ṹ��
MatrixServerDll_API m_oLogOutPutStruct* OnCreateLogOutPut();
// ����־����ļ�
MatrixServerDll_API int OpenLogOutPutFile(m_oLogOutPutStruct* pLogOutPut);
// ���뵽��־�������
MatrixServerDll_API void AddMsgToLogOutPutList(m_oLogOutPutStruct* pLogOutPut, 
	string pFuncName = "", string pVarName = "", byte byErrorType = LogType, 
	unsigned int uiErrorCode = 0);
// ��־���д���ļ�
MatrixServerDll_API void LogOutPutWriteInFile(FILE* pFile, string str, 
	bool bFlush = false);
// д����־����ļ�
MatrixServerDll_API void WriteLogOutPutListToFile(m_oLogOutPutStruct* pLogOutPut);
// �ر���־����ļ�
MatrixServerDll_API void CloseLogOutPutFile(m_oLogOutPutStruct* pLogOutPut);
// ��ʼ����־����ṹ��
MatrixServerDll_API void OnInitLogOutPut(m_oLogOutPutStruct* pLogOutPut);
// �ر���־����ṹ��
MatrixServerDll_API void OnCloseLogOutPut(m_oLogOutPutStruct* pLogOutPut);
// �ͷ���־����ṹ��
MatrixServerDll_API void OnFreeLogOutPut(m_oLogOutPutStruct* pLogOutPut);

/************************************************************************/
/* ������Ϣ                                                             */
/************************************************************************/
// ����������Ϣ�ṹ��
MatrixServerDll_API m_oConstVarStruct* OnCreateConstVar(void);
// ����INI�ļ�
MatrixServerDll_API void LoadIniFile(m_oConstVarStruct* pConstVar);
// ��ʼ��������Ϣ�ṹ��
MatrixServerDll_API void OnInitConstVar(m_oConstVarStruct* pConstVar, 
	m_oLogOutPutStruct* pLogOutPut = NULL);
// �رճ�����Ϣ�ṹ��
MatrixServerDll_API void OnCloseConstVar(m_oConstVarStruct* pConstVar);
// �ͷų�����Ϣ�ṹ��
MatrixServerDll_API void OnFreeConstVar(m_oConstVarStruct* pConstVar);

/************************************************************************/
/* xml����                                                              */
/************************************************************************/
// ��������ͨѶ��Ϣ�ṹ��
MatrixServerDll_API m_oInstrumentCommInfoStruct* OnCreateInstrumentCommInfo(void);
// ��ʼ���������������Ϣ
MatrixServerDll_API void OnInitServerXMLSetupData(m_oInstrumentCommInfoStruct* pCommInfo);
// ��ʼ�����߿ͻ�����������Ϣ
MatrixServerDll_API void OnInitLineClientXMLSetupData(m_oInstrumentCommInfoStruct* pCommInfo);
// ����Survery
MatrixServerDll_API void OnResetSurveryList(m_oInstrumentCommInfoStruct* pCommInfo);
// ����Point Code
MatrixServerDll_API void OnResetPointCodeList(m_oInstrumentCommInfoStruct* pCommInfo);
// ����Sensor
MatrixServerDll_API void OnResetSensorList(m_oInstrumentCommInfoStruct* pCommInfo);
// ����Marker
MatrixServerDll_API void OnResetMarkerList(m_oInstrumentCommInfoStruct* pCommInfo);
// ����Aux
MatrixServerDll_API void OnResetAuxList(m_oInstrumentCommInfoStruct* pCommInfo);
// ����Detour
MatrixServerDll_API void OnResetDetourList(m_oInstrumentCommInfoStruct* pCommInfo);
// ����Mute
MatrixServerDll_API void OnResetMuteList(m_oInstrumentCommInfoStruct* pCommInfo);
// ����BlastMachine
MatrixServerDll_API void OnResetBlastMachineList(m_oInstrumentCommInfoStruct* pCommInfo);
// ����Absolute
MatrixServerDll_API void OnResetAbsoluteMap(m_oInstrumentCommInfoStruct* pCommInfo);
// ����Generic
MatrixServerDll_API void OnResetGenericList(m_oInstrumentCommInfoStruct* pCommInfo);
// ����FormLine
MatrixServerDll_API void OnResetFormLineList(m_oInstrumentCommInfoStruct* pCommInfo);
// ����Instrument_SensorTestBase
MatrixServerDll_API void OnResetInstrument_SensorTestBaseList(bool bInstrument, m_oInstrumentCommInfoStruct* pCommInfo);
// ����Instrument_SensorTestLimit
MatrixServerDll_API void OnResetInstrument_SensorTestLimitList(bool bInstrument, m_oInstrumentCommInfoStruct* pCommInfo);
// ����Instrument Test
MatrixServerDll_API void OnResetInstrumentTestList(m_oInstrumentCommInfoStruct* pCommInfo);
// ����Sensor Test
MatrixServerDll_API void OnResetSensorTestList(m_oInstrumentCommInfoStruct* pCommInfo);
// ����Multiple Test
MatrixServerDll_API void OnResetMultipleTestMap(m_oInstrumentCommInfoStruct* pCommInfo);
// ����SeisMonitor
MatrixServerDll_API void OnResetSeisMonitor(m_oInstrumentCommInfoStruct* pCommInfo);
// ���ò��߿ͻ�����Ϣ
MatrixServerDll_API void OnResetLineClientXMLSetupData(m_oInstrumentCommInfoStruct* pCommInfo);
// �򿪳��������ļ�
MatrixServerDll_API BOOL OpenAppXMLFile(m_oInstrumentCommInfoStruct* pCommInfo,
	string strXMLFilePath);
// ����IP��ַ��������
MatrixServerDll_API void LoadServerIP(m_oInstrumentCommInfoStruct* pCommInfo);
// ����IP��ַ��������
MatrixServerDll_API void LoadServerIPSetupData(m_oInstrumentCommInfoStruct* pCommInfo);
// ���ض˿���������
MatrixServerDll_API void LoadServerPort(m_oInstrumentCommInfoStruct* pCommInfo);
// ���ض˿���������
MatrixServerDll_API void LoadServerPortSetupData(m_oInstrumentCommInfoStruct* pCommInfo);
// ����ADC������������
MatrixServerDll_API void LoadServerADCSet(m_oInstrumentCommInfoStruct* pCommInfo);
// ����ADC������������
MatrixServerDll_API void LoadServerADCSetSetupData(m_oInstrumentCommInfoStruct* pCommInfo);
// ���ط���˳�����������
MatrixServerDll_API void LoadServerAppSetupData(m_oInstrumentCommInfoStruct* pCommInfo);
// ����Survery��������
MatrixServerDll_API void LoadSurvery(m_oSurveryStruct* pSurveryStruct,CXMLDOMElement* pElement);
// ����Survery���ö�������
MatrixServerDll_API void LoadSurveryList(m_oInstrumentCommInfoStruct* pCommInfo);
// ����Survery��������
MatrixServerDll_API void LoadSurverySetupData(m_oInstrumentCommInfoStruct* pCommInfo);
// ����Survery��������
MatrixServerDll_API void SaveSurvery(m_oSurveryStruct* pSurveryStruct,CXMLDOMElement* pElement);
// ����Survery���ö�������
MatrixServerDll_API void SaveSurveryList(m_oInstrumentCommInfoStruct* pCommInfo);
// ����Survery��������
MatrixServerDll_API void SaveSurverySetupData(m_oInstrumentCommInfoStruct* pCommInfo);
// ����Point Code��������
MatrixServerDll_API void LoadPointCode(m_oPointCodeStruct* pPointCodeStruct,CXMLDOMElement* pElement);
// ����Point Code���ö�������
MatrixServerDll_API void LoadPointCodeList(m_oInstrumentCommInfoStruct* pCommInfo);
// ����Point Code��������
MatrixServerDll_API void LoadPointCodeSetupData(m_oInstrumentCommInfoStruct* pCommInfo);
// ����Point Code��������
MatrixServerDll_API void SavePointCode(m_oPointCodeStruct* pPointCodeStruct,CXMLDOMElement* pElement);
// ����Point Code���ö�������
MatrixServerDll_API void SavePointCodeList(m_oInstrumentCommInfoStruct* pCommInfo);
// ����Point Code��������
MatrixServerDll_API void SavePointCodeSetupData(m_oInstrumentCommInfoStruct* pCommInfo);
// ����Sensor��������
MatrixServerDll_API void LoadSensor(m_oSensorStruct* pSensorStruct,CXMLDOMElement* pElement);
// ����Sensor���ö�������
MatrixServerDll_API void LoadSensorList(m_oInstrumentCommInfoStruct* pCommInfo);
// ����Sensor��������
MatrixServerDll_API void LoadSensorSetupData(m_oInstrumentCommInfoStruct* pCommInfo);
// ����Sensor��������
MatrixServerDll_API void SaveSensor(m_oSensorStruct* pSensorStruct,CXMLDOMElement* pElement);
// ����Sensor���ö�������
MatrixServerDll_API void SaveSensorList(m_oInstrumentCommInfoStruct* pCommInfo);
// ����Sensor��������
MatrixServerDll_API void SaveSensorSetupData(m_oInstrumentCommInfoStruct* pCommInfo);
// ����Marker��������
MatrixServerDll_API void LoadMarker(m_oMarkerStruct* pMarkerStruct,CXMLDOMElement* pElement);
// ����Marker���ö�������
MatrixServerDll_API void LoadMarkerList(m_oInstrumentCommInfoStruct* pCommInfo);
// ����Marker��������
MatrixServerDll_API void LoadMarkerSetupData(m_oInstrumentCommInfoStruct* pCommInfo);
// ����Marker��������
MatrixServerDll_API void SaveMarker(m_oMarkerStruct* pMarkerStruct,CXMLDOMElement* pElement);
// ����Marker���ö�������
MatrixServerDll_API void SaveMarkerList(m_oInstrumentCommInfoStruct* pCommInfo);
// ����Marker��������
MatrixServerDll_API void SaveMarkerSetupData(m_oInstrumentCommInfoStruct* pCommInfo);
// ����Aux��������
MatrixServerDll_API void LoadAux(m_oAuxStruct* pAuxStruct,CXMLDOMElement* pElement);
// ����Aux���ö�������
MatrixServerDll_API void LoadAuxList(m_oInstrumentCommInfoStruct* pCommInfo);
// ����Aux��������
MatrixServerDll_API void LoadAuxSetupData(m_oInstrumentCommInfoStruct* pCommInfo);
// ����Aux��������
MatrixServerDll_API void SaveAux(m_oAuxStruct* pAuxStruct,CXMLDOMElement* pElement);
// ����Aux���ö�������
MatrixServerDll_API void SaveAuxList(m_oInstrumentCommInfoStruct* pCommInfo);
// ����Aux��������
MatrixServerDll_API void SaveAuxSetupData(m_oInstrumentCommInfoStruct* pCommInfo);
// ����Detour��������
MatrixServerDll_API void LoadDetour(m_oDetourStruct* pDetourStruct,CXMLDOMElement* pElement);
// ����Detour���ö�������
MatrixServerDll_API void LoadDetourList(m_oInstrumentCommInfoStruct* pCommInfo);
// ����Detour��������
MatrixServerDll_API void LoadDetourSetupData(m_oInstrumentCommInfoStruct* pCommInfo);
// ����Detour��������
MatrixServerDll_API void SaveDetour(m_oDetourStruct* pDetourStruct,CXMLDOMElement* pElement);
// ����Detour���ö�������
MatrixServerDll_API void SaveDetourList(m_oInstrumentCommInfoStruct* pCommInfo);
// ����Detour��������
MatrixServerDll_API void SaveDetourSetupData(m_oInstrumentCommInfoStruct* pCommInfo);
// ����Mute��������
MatrixServerDll_API void LoadMute(m_oMuteStruct* pMuteStruct,CXMLDOMElement* pElement);
// ����Mute���ö�������
MatrixServerDll_API void LoadMuteList(m_oInstrumentCommInfoStruct* pCommInfo);
// ����Mute��������
MatrixServerDll_API void LoadMuteSetupData(m_oInstrumentCommInfoStruct* pCommInfo);
// ����Mute��������
MatrixServerDll_API void SaveMute(m_oMuteStruct* pMuteStruct,CXMLDOMElement* pElement);
// ����Mute���ö�������
MatrixServerDll_API void SaveMuteList(m_oInstrumentCommInfoStruct* pCommInfo);
// ����Mute��������
MatrixServerDll_API void SaveMuteSetupData(m_oInstrumentCommInfoStruct* pCommInfo);
// ����BlastMachine��������
MatrixServerDll_API void LoadBlastMachine(m_oBlastMachineStruct* pBlastMachineStruct,CXMLDOMElement* pElement);
// ����BlastMachine���ö�������
MatrixServerDll_API void LoadBlastMachineList(m_oInstrumentCommInfoStruct* pCommInfo);
// ����BlastMachine��������
MatrixServerDll_API void LoadBlastMachineSetupData(m_oInstrumentCommInfoStruct* pCommInfo);
// ����BlastMachine��������
MatrixServerDll_API void SaveBlastMachine(m_oBlastMachineStruct* pBlastMachineStruct,CXMLDOMElement* pElement);
// ����BlastMachine���ö�������
MatrixServerDll_API void SaveBlastMachineList(m_oInstrumentCommInfoStruct* pCommInfo);
// ����BlastMachine��������
MatrixServerDll_API void SaveBlastMachineSetupData(m_oInstrumentCommInfoStruct* pCommInfo);
// ����Absolute��������
MatrixServerDll_API void LoadAbsolute(m_oAbsoluteStruct* pAbsoluteStruct,CXMLDOMElement* pElement);
// ����Absolute���ö�������
MatrixServerDll_API void LoadAbsoluteList(m_oInstrumentCommInfoStruct* pCommInfo, CXMLDOMElement* pElement);
// ����Absolute������������
MatrixServerDll_API void LoadAbsoluteMap(m_oInstrumentCommInfoStruct* pCommInfo);
// ����Absolute��������
MatrixServerDll_API void LoadAbsoluteSetupData(m_oInstrumentCommInfoStruct* pCommInfo);
// ����Generic��������
MatrixServerDll_API void LoadGeneric(m_oGenericStruct* pGenericStruct,CXMLDOMElement* pElement);
// ����Generic���ö�������
MatrixServerDll_API void LoadGenericList(m_oInstrumentCommInfoStruct* pCommInfo);
// ����Generic��������
MatrixServerDll_API void LoadGenericSetupData(m_oInstrumentCommInfoStruct* pCommInfo);
// ����Generic��������
MatrixServerDll_API void SaveGeneric(m_oGenericStruct* pGenericStruct,CXMLDOMElement* pElement);
// ����Generic���ö�������
MatrixServerDll_API void SaveGenericList(m_oInstrumentCommInfoStruct* pCommInfo);
// ����Generic��������
MatrixServerDll_API void SaveGenericSetupData(m_oInstrumentCommInfoStruct* pCommInfo);
// ����Look��������
MatrixServerDll_API void LoadLook(m_oInstrumentCommInfoStruct* pCommInfo);
// ����Look��������
MatrixServerDll_API void LoadLookSetupData(m_oInstrumentCommInfoStruct* pCommInfo);
// ����Look��������
MatrixServerDll_API void SaveLook(m_oInstrumentCommInfoStruct* pCommInfo);
// ����Look��������
MatrixServerDll_API void SaveLookSetupData(m_oInstrumentCommInfoStruct* pCommInfo);
// ����LAULeakage��������
MatrixServerDll_API void LoadLAULeakage(m_oInstrumentCommInfoStruct* pCommInfo);
// ����LAULeakage��������
MatrixServerDll_API void LoadLAULeakageSetupData(m_oInstrumentCommInfoStruct* pCommInfo);
// ����LAULeakage��������
MatrixServerDll_API void SaveLAULeakage(m_oInstrumentCommInfoStruct* pCommInfo);
// ����LAULeakage��������
MatrixServerDll_API void SaveLAULeakageSetupData(m_oInstrumentCommInfoStruct* pCommInfo);
// ����FormLine��������
MatrixServerDll_API void LoadFormLine(m_oFormLineStruct* pFormLineStruct,CXMLDOMElement* pElement);
// ����FormLine���ö�������
MatrixServerDll_API void LoadFormLineList(m_oInstrumentCommInfoStruct* pCommInfo);
// ����FormLine��������
MatrixServerDll_API void LoadFormLineSetupData(m_oInstrumentCommInfoStruct* pCommInfo);
// ����FormLine��������
MatrixServerDll_API void SaveFormLine(m_oFormLineStruct* pFormLineStruct,CXMLDOMElement* pElement);
// ����FormLine���ö�������
MatrixServerDll_API void SaveFormLineList(m_oInstrumentCommInfoStruct* pCommInfo);
// ����FormLine��������
MatrixServerDll_API void SaveFormLineSetupData(m_oInstrumentCommInfoStruct* pCommInfo);
// ����Instrument_SensorTestBase��������
MatrixServerDll_API void LoadInstrument_SensorTestBase(Instrument_SensorTestBase_Struct* pInstrument_SensorTestBaseStruct,CXMLDOMElement* pElement);
// ����Instrument_SensorTestBase���ö�������
MatrixServerDll_API void LoadInstrument_SensorTestBaseList(bool bInstrument, m_oInstrumentCommInfoStruct* pCommInfo);
// ����Instrument_SensorTestBase��������
MatrixServerDll_API void LoadInstrument_SensorTestBaseSetupData(bool bInstrument, m_oInstrumentCommInfoStruct* pCommInfo);
// ����Instrument_SensorTestLimit��������
MatrixServerDll_API void LoadInstrument_SensorTestLimit(Instrument_SensorTestLimit_Struct* pInstrument_SensorTestLimitStruct,CXMLDOMElement* pElement);
// ����Instrument_SensorTestLimit���ö�������
MatrixServerDll_API void LoadInstrument_SensorTestLimitList(bool bInstrument, m_oInstrumentCommInfoStruct* pCommInfo);
// ����Instrument_SensorTestLimit��������
MatrixServerDll_API void LoadInstrument_SensorTestLimitSetupData(bool bInstrument, m_oInstrumentCommInfoStruct* pCommInfo);
// ����Instrument Test��������
MatrixServerDll_API void LoadInstrumentTest(m_oInstrumentTestStruct* pInstrumentTestStruct, CXMLDOMElement* pElement);
// ����Instrument Test���ö�������
MatrixServerDll_API void LoadInstrumentTestList(m_oInstrumentCommInfoStruct* pCommInfo);
// ����Instrument Test��������
MatrixServerDll_API void LoadInstrumentTestSetupData(m_oInstrumentCommInfoStruct* pCommInfo);
// ����Sensor Test��������
MatrixServerDll_API void LoadSensorTest(m_oSensorTestStruct* pSensorTestStruct, CXMLDOMElement* pElement);
// ����Sensor Test���ö�������
MatrixServerDll_API void LoadSensorTestList(m_oInstrumentCommInfoStruct* pCommInfo);
// ����Sensor Test��������
MatrixServerDll_API void LoadSensorTestSetupData(m_oInstrumentCommInfoStruct* pCommInfo);
// ����Multiple Test��������
MatrixServerDll_API void LoadMultipleTest(m_oMultipleTestTaskStruct* pMultipleTestTaskStruct, CXMLDOMElement* pElement);
// ����Multiple Test���ö�������
MatrixServerDll_API void LoadMultipleTestList(m_oInstrumentCommInfoStruct* pCommInfo, CXMLDOMElement* pElement);
// ����Multiple Test������������
MatrixServerDll_API void LoadMultipleTestMap(m_oInstrumentCommInfoStruct* pCommInfo);
// ����Multiple Test��������
MatrixServerDll_API void LoadMultipleTestSetupData(m_oInstrumentCommInfoStruct* pCommInfo);
// ����SeisMonitor��������
MatrixServerDll_API void LoadSeisMonitor(m_oInstrumentCommInfoStruct* pCommInfo);
// ����SeisMonitor��������
MatrixServerDll_API void LoadSeisMonitorSetupData(m_oInstrumentCommInfoStruct* pCommInfo);

// ���ز��߿ͻ��˳�����������
MatrixServerDll_API void LoadLineAppSetupData(m_oInstrumentCommInfoStruct* pCommInfo);
// ������߿ͻ��˳�����������
MatrixServerDll_API void SaveLineAppSetupData(m_oInstrumentCommInfoStruct* pCommInfo);
// ��ʼ������ͨѶ��Ϣ�ṹ��
MatrixServerDll_API void OnInitInstrumentCommInfo(m_oInstrumentCommInfoStruct* pCommInfo, 
	m_oLogOutPutStruct* pLogOutPut = NULL);
// �رճ��������ļ�
MatrixServerDll_API void CloseAppXMLFile(m_oInstrumentCommInfoStruct* pCommInfo);
// �ͷŷ���˲���������Ϣ�ṹ�建����
MatrixServerDll_API void OnFreeServerXMLSetupData(m_oInstrumentCommInfoStruct* pCommInfo);
// �ͷ�����ͨѶ��Ϣ�ṹ��
MatrixServerDll_API void OnFreeInstrumentCommInfo(m_oInstrumentCommInfoStruct* pCommInfo);

/************************************************************************/
/* ����֡                                                               */
/************************************************************************/
// ��������֡��Ϣ�ṹ��
MatrixServerDll_API m_oHeartBeatFrameStruct* OnCreateInstrumentHeartBeat(void);
// ��ʼ������
MatrixServerDll_API void OnInitInstrumentHeartBeat(m_oHeartBeatFrameStruct* pHeartBeatFrame, 
	m_oInstrumentCommInfoStruct* pCommInfo, m_oConstVarStruct* pConstVar);
// �ر�����֡��Ϣ�ṹ��
MatrixServerDll_API void OnCloseInstrumentHeartBeat(m_oHeartBeatFrameStruct* pHeartBeatFrame);
// �ͷ�����֡��Ϣ�ṹ��
MatrixServerDll_API void OnFreeInstrumentHeartBeat(m_oHeartBeatFrameStruct* pHeartBeatFrame);
// ���������������˿�
MatrixServerDll_API void OnCreateAndSetHeartBeatSocket(m_oHeartBeatFrameStruct* pHeartBeatFrame, 
	m_oLogOutPutStruct* pLogOutPut = NULL);
// ��������֡
MatrixServerDll_API void MakeInstrumentHeartBeatFrame(m_oHeartBeatFrameStruct* pHeartBeatFrame, 
	m_oConstVarStruct* pConstVar);
// ��������֡
MatrixServerDll_API void SendInstrumentHeartBeatFrame(m_oHeartBeatFrameStruct* pHeartBeatFrame, 
	m_oConstVarStruct* pConstVar);

/************************************************************************/
/* �װ�֡                                                               */
/************************************************************************/
// �����װ�֡��Ϣ�ṹ��
MatrixServerDll_API m_oHeadFrameStruct* OnCreateInstrumentHeadFrame(void);
// ��ʼ���װ�
MatrixServerDll_API void OnInitInstrumentHeadFrame(m_oHeadFrameStruct* pHeadFrame, 
	m_oInstrumentCommInfoStruct* pCommInfo, m_oConstVarStruct* pConstVar);
// �ر��װ�֡��Ϣ�ṹ��
MatrixServerDll_API void OnCloseInstrumentHeadFrame(m_oHeadFrameStruct* pHeadFrame);
// �ͷ��װ�֡��Ϣ�ṹ��
MatrixServerDll_API void OnFreeInstrumentHeadFrame(m_oHeadFrameStruct* pHeadFrame);
// �����������װ��˿�
MatrixServerDll_API void OnCreateAndSetHeadFrameSocket(m_oHeadFrameStruct* pHeadFrame, 
		m_oLogOutPutStruct* pLogOutPut = NULL);
// �����װ�֡
MatrixServerDll_API bool ParseInstrumentHeadFrame(m_oHeadFrameStruct* pHeadFrame, 
	m_oConstVarStruct* pConstVar);

/************************************************************************/
/* IP��ַ����֡                                                         */
	/************************************************************************/
// ����IP��ַ����֡��Ϣ�ṹ��
MatrixServerDll_API m_oIPSetFrameStruct* OnCreateInstrumentIPSetFrame(void);
// ��ʼ��IP��ַ����
MatrixServerDll_API void OnInitInstrumentIPSetFrame(m_oIPSetFrameStruct* pIPSetFrame,
	m_oInstrumentCommInfoStruct* pCommInfo, m_oConstVarStruct* pConstVar);
// �ر�IP��ַ����֡��Ϣ�ṹ��
MatrixServerDll_API void OnCloseInstrumentIPSetFrame(m_oIPSetFrameStruct* pIPSetFrame);
// �ͷ�IP��ַ����֡��Ϣ�ṹ��
MatrixServerDll_API void OnFreeInstrumentIPSetFrame(m_oIPSetFrameStruct* pIPSetFrame);
// ����������IP��ַ���ö˿�
MatrixServerDll_API void OnCreateAndSetIPSetFrameSocket(m_oIPSetFrameStruct* pIPSetFrame, 
	m_oLogOutPutStruct* pLogOutPut = NULL);
// ����IP��ַ����Ӧ��֡
MatrixServerDll_API bool ParseInstrumentIPSetReturnFrame(m_oIPSetFrameStruct* pIPSetFrame, 
	m_oConstVarStruct* pConstVar);
// �򿪽���վĳһ·�ɷ���ĵ�Դ
MatrixServerDll_API bool OpenLAUXRoutPower(int iLineIndex, int iPointIndex, unsigned char ucLAUXRoutOpenSet, 
	m_oEnvironmentStruct* pEnv);
// ����IP��ַ��ѯ֡
MatrixServerDll_API void MakeInstrumentIPQueryFrame(m_oIPSetFrameStruct* pIPSetFrame, 
	m_oConstVarStruct* pConstVar, unsigned int uiInstrumentIP);
// ����IP��ַ����֡
MatrixServerDll_API void MakeInstrumentIPSetFrame(m_oIPSetFrameStruct* pIPSetFrame, 
	m_oConstVarStruct* pConstVar, m_oInstrumentStruct* pInstrument);
// ����IP��ַ����֡
MatrixServerDll_API void SendInstrumentIPSetFrame(m_oIPSetFrameStruct* pIPSetFrame, 
	m_oConstVarStruct* pConstVar);

/************************************************************************/
/* β��֡                                                               */
/************************************************************************/
// ����β��֡��Ϣ�ṹ��
MatrixServerDll_API m_oTailFrameStruct* OnCreateInstrumentTailFrame(void);
// ��ʼ��β��
MatrixServerDll_API void OnInitInstrumentTailFrame(m_oTailFrameStruct* pTailFrame, 
	m_oInstrumentCommInfoStruct* pCommInfo, m_oConstVarStruct* pConstVar);
// �ر�β��֡��Ϣ�ṹ��
MatrixServerDll_API void OnCloseInstrumentTailFrame(m_oTailFrameStruct* pTailFrame);
// �ͷ�β��֡��Ϣ�ṹ��
MatrixServerDll_API void OnFreeInstrumentTailFrame(m_oTailFrameStruct* pTailFrame);
// ����������β���˿�
MatrixServerDll_API void OnCreateAndSetTailFrameSocket(m_oTailFrameStruct* pTailFrame, 
	m_oLogOutPutStruct* pLogOutPut = NULL);
// ����β��֡
MatrixServerDll_API bool ParseInstrumentTailFrame(m_oTailFrameStruct* pTailFrame, 
	m_oConstVarStruct* pConstVar);


/************************************************************************/
/* β��ʱ��֡                                                           */
/************************************************************************/
// ����β��ʱ��֡��Ϣ�ṹ��
MatrixServerDll_API m_oTailTimeFrameStruct* OnCreateInstrumentTailTimeFrame(void);
// ��ʼ��β��ʱ��֡
MatrixServerDll_API void OnInitInstrumentTailTimeFrame(m_oTailTimeFrameStruct* pTailTimeFrame,
	m_oInstrumentCommInfoStruct* pCommInfo, m_oConstVarStruct* pConstVar);
// �ر�β��ʱ��֡��Ϣ�ṹ��
MatrixServerDll_API void OnCloseInstrumentTailTimeFrame(m_oTailTimeFrameStruct* pTailTimeFrame);
// �ͷ�β��ʱ��֡��Ϣ�ṹ��
MatrixServerDll_API void OnFreeInstrumentTailTimeFrame(m_oTailTimeFrameStruct* pTailTimeFrame);
// ����������β��ʱ�̶˿�
MatrixServerDll_API void OnCreateAndSetTailTimeFrameSocket(m_oTailTimeFrameStruct* pTailTimeFrame, 
	m_oLogOutPutStruct* pLogOutPut = NULL);
// ����β��ʱ�̲�ѯ֡
MatrixServerDll_API bool ParseInstrumentTailTimeReturnFrame(m_oTailTimeFrameStruct* pTailTimeFrame, 
	m_oConstVarStruct* pConstVar);
// ��IP��ַ��ѯβ��ʱ��֡
MatrixServerDll_API void MakeInstrumentTailTimeQueryFramebyIP(m_oTailTimeFrameStruct* pTailTimeFrame, 
	m_oConstVarStruct* pConstVar, unsigned int uiInstrumentIP);
// �㲥��ѯβ��ʱ��֡
MatrixServerDll_API void MakeInstrumentTailTimeQueryFramebyBroadCast(m_oTailTimeFrameStruct* pTailTimeFrame, 
	m_oConstVarStruct* pConstVar, unsigned int uiBroadCastPort);
// ����β��ʱ�̲�ѯ֡
MatrixServerDll_API void SendInstrumentTailTimeQueryFrame(m_oTailTimeFrameStruct* pTailTimeFrame, 
	m_oConstVarStruct* pConstVar);

/************************************************************************/
/* ʱͳ֡                                                               */
/************************************************************************/
// ����ʱͳ����֡��Ϣ�ṹ��
MatrixServerDll_API m_oTimeDelayFrameStruct* OnCreateInstrumentTimeDelayFrame(void);
// ��ʼ��ʱͳ����֡
MatrixServerDll_API void OnInitInstrumentTimeDelayFrame(m_oTimeDelayFrameStruct* pTimeDelayFrame,
	m_oInstrumentCommInfoStruct* pCommInfo, m_oConstVarStruct* pConstVar);
// �ر�ʱͳ����֡��Ϣ�ṹ��
MatrixServerDll_API void OnCloseInstrumentTimeDelayFrame(m_oTimeDelayFrameStruct* pTimeDelayFrame);
// �ͷ�ʱͳ����֡��Ϣ�ṹ��
MatrixServerDll_API void OnFreeInstrumentTimeDelayFrame(m_oTimeDelayFrameStruct* pTimeDelayFrame);
// ����������ʱͳ���ö˿�
MatrixServerDll_API void OnCreateAndSetTimeDelayFrameSocket(m_oTimeDelayFrameStruct* pTimeDelayFrame, 
	m_oLogOutPutStruct* pLogOutPut = NULL);
// ����ʱͳ����Ӧ��֡
MatrixServerDll_API bool ParseInstrumentTimeDelayReturnFrame(m_oTimeDelayFrameStruct* pTimeDelayFrame, 
	m_oConstVarStruct* pConstVar);
// ����ʱͳ����֡
MatrixServerDll_API void MakeInstrumentDelayTimeFrame(m_oTimeDelayFrameStruct* pTimeDelayFrame, 
	m_oConstVarStruct* pConstVar, m_oInstrumentStruct* pInstrument);
// ����ʱͳ����֡
MatrixServerDll_API void SendInstrumentDelayTimeFrame(m_oTimeDelayFrameStruct* pTimeDelayFrame, 
	m_oConstVarStruct* pConstVar);

/************************************************************************/
/* ADC��������֡                                                        */
/************************************************************************/
// ����ADC��������֡��Ϣ�ṹ��
MatrixServerDll_API m_oADCSetFrameStruct* OnCreateInstrumentADCSetFrame(void);
// ��ʼ��ADC��������֡
MatrixServerDll_API void OnInitInstrumentADCSetFrame(m_oADCSetFrameStruct* pADCSetFrame,
	m_oInstrumentCommInfoStruct* pCommInfo, m_oConstVarStruct* pConstVar);
// �ر�ADC��������֡��Ϣ�ṹ��
MatrixServerDll_API void OnCloseInstrumentADCSetFrame(m_oADCSetFrameStruct* pADCSetFrame);
// �ͷ�ADC��������֡��Ϣ�ṹ��
MatrixServerDll_API void OnFreeInstrumentADCSetFrame(m_oADCSetFrameStruct* pADCSetFrame);
// ����������ADC�������ö˿�
MatrixServerDll_API void OnCreateAndSetADCSetFrameSocket(m_oADCSetFrameStruct* pADCSetFrame, 
	m_oLogOutPutStruct* pLogOutPut = NULL);
// ����ADC��������Ӧ��֡
MatrixServerDll_API bool ParseInstrumentADCSetReturnFrame(m_oADCSetFrameStruct* pADCSetFrame,
	m_oConstVarStruct* pConstVar);
// ����ADC��������֡
MatrixServerDll_API void SendInstrumentADCSetFrame(m_oADCSetFrameStruct* pADCSetFrame, 
	m_oConstVarStruct* pConstVar);

/************************************************************************/
/* �����ѯ֡                                                           */
/************************************************************************/
// ���������ѯ֡��Ϣ�ṹ��
MatrixServerDll_API m_oErrorCodeFrameStruct* OnCreateInstrumentErrorCodeFrame(void);
// ��ʼ�������ѯ֡
MatrixServerDll_API void OnInitInstrumentErrorCodeFrame(m_oErrorCodeFrameStruct* pErrorCodeFrame,
	m_oInstrumentCommInfoStruct* pCommInfo, m_oConstVarStruct* pConstVar);
// �ر������ѯ֡��Ϣ�ṹ��
MatrixServerDll_API void OnCloseInstrumentErrorCodeFrame(m_oErrorCodeFrameStruct* pErrorCodeFrame);
// �ͷ������ѯ֡��Ϣ�ṹ��
MatrixServerDll_API void OnFreeInstrumentErrorCodeFrame(m_oErrorCodeFrameStruct* pErrorCodeFrame);
// ���������������ѯ�˿�
MatrixServerDll_API void OnCreateAndSetErrorCodeFrameSocket(m_oErrorCodeFrameStruct* pErrorCodeFrame, 
	m_oLogOutPutStruct* pLogOutPut = NULL);
// ���������ѯӦ��֡
MatrixServerDll_API bool ParseInstrumentErrorCodeReturnFrame(m_oErrorCodeFrameStruct* pErrorCodeFrame, 
	m_oConstVarStruct* pConstVar);
// �㲥��ѯ����
MatrixServerDll_API void MakeInstrumentErrorCodeQueryFrame(m_oErrorCodeFrameStruct* pErrorCodeFrame, 
	m_oConstVarStruct* pConstVar, unsigned int uiBroadCastPort);
// ���������ѯ֡
MatrixServerDll_API void SendInstrumentErrorCodeFrame(m_oErrorCodeFrameStruct* pErrorCodeFrame, 
	m_oConstVarStruct* pConstVar);

/************************************************************************/
/* ADC����֡                                                            */
/************************************************************************/
// ����ADC����֡��Ϣ�ṹ��
MatrixServerDll_API m_oADCDataFrameStruct* OnCreateInstrumentADCDataFrame(void);
// ��ʼ��ADC����֡
MatrixServerDll_API void OnInitInstrumentADCDataFrame(m_oADCDataFrameStruct* pADCDataFrame,
	m_oInstrumentCommInfoStruct* pCommInfo, m_oConstVarStruct* pConstVar);
// �ر�ADC����֡��Ϣ�ṹ��
MatrixServerDll_API void OnCloseInstrumentADCDataFrame(m_oADCDataFrameStruct* pADCDataFrame);
// �ͷ�ADC����֡��Ϣ�ṹ��
MatrixServerDll_API void OnFreeInstrumentADCDataFrame(m_oADCDataFrameStruct* pADCDataFrame);
// ����������ADC����֡�˿�
MatrixServerDll_API void OnCreateAndSetADCDataFrameSocket(m_oADCDataFrameStruct* pADCDataFrame, 
	m_oLogOutPutStruct* pLogOutPut = NULL);
// ����ADC���ݽ���֡
MatrixServerDll_API bool ParseInstrumentADCDataRecFrame(m_oADCDataFrameStruct* pADCDataFrame, 
	m_oConstVarStruct* pConstVar);
// ����ADC���ݲ�ѯ֡
MatrixServerDll_API void MakeInstrumentADCDataFrame(m_oADCDataFrameStruct* pADCDataFrame, 
	m_oConstVarStruct* pConstVar, unsigned int uiIP, unsigned short usDataPoint);
// ����ADC���ݲ�ѯ֡
MatrixServerDll_API void SendInstrumentADCDataFrame(m_oADCDataFrameStruct* pADCDataFrame, 
	m_oConstVarStruct* pConstVar);

/************************************************************************/
/* �����ṹ��                                                           */
/************************************************************************/
// ������Ϣ����
MatrixServerDll_API void OnInstrumentReset(m_oInstrumentStruct* pInstrument, bool bSetByHand);
// �ж������������Ƿ��Ѽ���������
MatrixServerDll_API BOOL IfIndexExistInMap(unsigned int uiIndex, 
	hash_map<unsigned int, m_oInstrumentStruct*>* pMap);
// ����һ��IP��ַ��������
MatrixServerDll_API void AddInstrumentToMap(unsigned int uiIndex, m_oInstrumentStruct* pInstrument, 
	hash_map<unsigned int, m_oInstrumentStruct*>* pMap);
// �������������ţ���������õ�����ָ��
MatrixServerDll_API m_oInstrumentStruct* GetInstrumentFromMap(unsigned int uiIndex, 
	hash_map<unsigned int, m_oInstrumentStruct*>* pMap);
// ��������ɾ��������ָ�������ָ��
MatrixServerDll_API BOOL DeleteInstrumentFromMap(unsigned int uiIndex, 
	hash_map<unsigned int, m_oInstrumentStruct*>* pMap);
// �ж�����λ���������Ƿ��Ѽ���������
MatrixServerDll_API BOOL IfLocationExistInMap(int iLineIndex, int iPointIndex, 
	map<m_oInstrumentLocationStruct, m_oInstrumentStruct*>* pMap);
// ���Ӷ���������
MatrixServerDll_API void AddLocationToMap(int iLineIndex, int iPointIndex, 
	m_oInstrumentStruct* pInstrument, map<m_oInstrumentLocationStruct, 
	m_oInstrumentStruct*>* pMap);
// �������������ţ���������õ�����ָ��
MatrixServerDll_API m_oInstrumentStruct* GetInstrumentFromLocationMap(int iLineIndex, int iPointIndex, 
	map<m_oInstrumentLocationStruct, m_oInstrumentStruct*>* pMap);
// ����������λ�õõ�������SN��
MatrixServerDll_API unsigned int GetInstrumentSnFromLocationMap(int iLineIndex, int iPointIndex, 
	m_oInstrumentListStruct* pInstrumentList);
// ��������ɾ��������ָ�������ָ��
MatrixServerDll_API BOOL DeleteInstrumentFromLocationMap(int iLineIndex, int iPointIndex, 
	map<m_oInstrumentLocationStruct, m_oInstrumentStruct*>* pMap);
// �õ�������ĳһ�����ϵ�·��IP
MatrixServerDll_API bool GetRoutIPBySn(unsigned int uiSN, int iDirection, 
	m_oInstrumentListStruct* pInstrumentList, m_oConstVarStruct* pConstVar, 
	unsigned int& uiRoutIP);

/**
* �������ӷ��򣬵õ����ӵ���һ������
* @param unsigned int uiRoutDirection ���� 1-�ϣ�2-�£�3-��4��
	* @return CInstrument* ����ָ�� NLLL�����ӵ���һ������������
*/
MatrixServerDll_API m_oInstrumentStruct* GetNextInstrument(int iRoutDirection, 
m_oInstrumentStruct* pInstrument, m_oConstVarStruct* pConstVar);
/**
* �������ӷ��򣬵õ����ӵ�ǰһ������
* @param unsigned int uiRoutDirection ���� 1-�ϣ�2-�£�3-��4��
* @return CInstrument* ����ָ�� NLLL�����ӵ�ǰһ������������
*/
MatrixServerDll_API m_oInstrumentStruct* GetPreviousInstrument(int iRoutDirection, 
m_oInstrumentStruct* pInstrument, m_oConstVarStruct* pConstVar);



/************************************************************************/
/* ��������                                                             */
/************************************************************************/
// �����������нṹ��
MatrixServerDll_API m_oInstrumentListStruct* OnCreateInstrumentList(void);
// �����������нṹ��
MatrixServerDll_API void OnResetInstrumentList(m_oInstrumentListStruct* pInstrumentList);
// ��ʼ���������нṹ��
MatrixServerDll_API void OnInitInstrumentList(m_oInstrumentListStruct* pInstrumentList,
	m_oConstVarStruct* pConstVar);
// ADC�������ø�Ϊ�ֶ�����
MatrixServerDll_API void OnSetADCSetByHand(m_oInstrumentListStruct* pInstrumentList);
// �ر��������нṹ��
MatrixServerDll_API void OnCloseInstrumentList(m_oInstrumentListStruct* pInstrumentList);
// �ͷ��������нṹ��
MatrixServerDll_API void OnFreeInstrumentList(m_oInstrumentListStruct* pInstrumentList);
// �õ�һ����������
MatrixServerDll_API m_oInstrumentStruct* GetFreeInstrument(m_oInstrumentListStruct* pInstrumentList);
// ����һ����������
MatrixServerDll_API void AddFreeInstrument(m_oInstrumentStruct* pInstrument, 
	m_oInstrumentListStruct* pInstrumentList);
// �����ϴβ���ϵͳ�仯ʱ��
MatrixServerDll_API void UpdateLineChangeTime(m_oInstrumentListStruct* pInstrumentList);

/************************************************************************/
/* ·�ɽṹ��                                                           */
/************************************************************************/
// ����·����Ϣ
MatrixServerDll_API void OnRoutReset(m_oRoutStruct* pRout);
// ����·�ɶ����·��ʱ��
MatrixServerDll_API void UpdateRoutTime(m_oRoutStruct* pRout);
// ·�ɵ�ַ�Ƿ��Ѽ���������
MatrixServerDll_API BOOL IfIndexExistInRoutMap(unsigned int uiRoutIP, 
	hash_map<unsigned int, m_oRoutStruct*>* pRoutMap);
// ����һ��·��
MatrixServerDll_API void AddRout(unsigned int uiIndex, m_oRoutStruct* pRout, 
	hash_map<unsigned int, m_oRoutStruct*>* pRoutMap);
// �������������ţ���������õ�һ��·��ָ��
MatrixServerDll_API m_oRoutStruct* GetRout(unsigned int uiIndex, 
	hash_map<unsigned int, m_oRoutStruct*>* pRoutMap);
// �������������ţ�����������ɾ��һ��·��
MatrixServerDll_API void DeleteRout(unsigned int uiIndex, 
	hash_map<unsigned int, m_oRoutStruct*>* pRoutMap);
// ��·��IP�õ�·�ɽṹ��ָ��
MatrixServerDll_API bool GetRoutByRoutIP(unsigned int uiRoutIP, 
	m_oRoutListStruct* pRoutList, m_oRoutStruct** ppRout);

/************************************************************************/
/* ·�ɶ���                                                             */
/************************************************************************/
// ����·�ɶ��нṹ��
MatrixServerDll_API m_oRoutListStruct* OnCreateRoutList(void);
// ����·�ɶ��нṹ��
MatrixServerDll_API void OnResetRoutList(m_oRoutListStruct* pRoutList);
// ��ʼ��·�ɶ��нṹ��
MatrixServerDll_API void OnInitRoutList(m_oRoutListStruct* pRoutList,
	m_oConstVarStruct* pConstVar);
// �ر�·�ɶ��нṹ��
MatrixServerDll_API void OnCloseRoutList(m_oRoutListStruct* pRoutList);
// �ͷ�·�ɶ��нṹ��
MatrixServerDll_API void OnFreeRoutList(m_oRoutListStruct* pRoutList);
// �õ�һ������·��
MatrixServerDll_API m_oRoutStruct* GetFreeRout(m_oRoutListStruct* pRoutList);
// ����һ������·��
MatrixServerDll_API void AddFreeRout(m_oRoutStruct* pRout, m_oRoutListStruct* pRoutList);

/************************************************************************/
/* ADC���ݴ洢����                                                      */
/************************************************************************/
// �������ݴ洢��������Ϣ
MatrixServerDll_API void OnADCDataBufReset(m_oADCDataBufStruct* pADCDataBuf);

/************************************************************************/
/* ADC���ݴ洢����������                                                */
/************************************************************************/
// �������ݴ洢�������ṹ��
MatrixServerDll_API m_oADCDataBufArrayStruct* OnCreateADCDataBufArray(void);
// �������ݴ洢�������ṹ��
MatrixServerDll_API void OnResetADCDataBufArray(m_oADCDataBufArrayStruct* pADCDataBufArray);
// ��ʼ�����ݴ洢�������ṹ��
MatrixServerDll_API void OnInitADCDataBufArray(m_oADCDataBufArrayStruct* pADCDataBufArray,
	m_oConstVarStruct* pConstVar);
// �ر����ݴ洢�������ṹ��
MatrixServerDll_API void OnCloseADCDataBufArray(m_oADCDataBufArrayStruct* pADCDataBufArray);
// �ͷ����ݴ洢�������ṹ��
MatrixServerDll_API void OnFreeADCDataBufArray(m_oADCDataBufArrayStruct* pADCDataBufArray);
// �õ�һ���������ݴ洢������
MatrixServerDll_API m_oADCDataBufStruct* GetFreeADCDataBuf(m_oADCDataBufArrayStruct* pADCDataBufArray);
// ����һ���������ݴ洢������
MatrixServerDll_API void AddFreeADCDataBuf(m_oADCDataBufStruct* pADCDataBuf, 
	m_oADCDataBufArrayStruct* pADCDataBufArray);

/************************************************************************/
/* ��ʧ֡�ṹ��                                                         */
/************************************************************************/
// �ж��������Ƿ��Ѽ���������
MatrixServerDll_API BOOL IfIndexExistInADCFrameLostMap(unsigned int uiIP, unsigned short usFramePointNb,
	map<m_oADCLostFrameKeyStruct, m_oADCLostFrameStruct>* pMap);
// ���ӵ�����
MatrixServerDll_API void AddToADCFrameLostMap(unsigned int uiIP, unsigned short usFramePointNb, 
	m_oADCLostFrameStruct oLostFrame, map<m_oADCLostFrameKeyStruct, m_oADCLostFrameStruct>* pMap);
// �������������ţ���������õ�����ָ��
MatrixServerDll_API m_oADCLostFrameStruct* GetFromADCFrameLostMap(unsigned int uiIP, unsigned short usFramePointNb, 
	map<m_oADCLostFrameKeyStruct, m_oADCLostFrameStruct>* pMap);

/************************************************************************/
/* ʩ������                                                             */
/************************************************************************/
// ����ʩ������
MatrixServerDll_API void OnOptTaskReset(m_oOptTaskStruct* pOptTask);
// �ж��������Ƿ��Ѽ���ʩ������������
MatrixServerDll_API BOOL IfIndexExistInOptTaskMap(unsigned int uiIndex, 
	hash_map<unsigned int, m_oOptTaskStruct*>* pMap);
// �ж�����SN���Ƿ��Ѽ���ʩ����������������
MatrixServerDll_API BOOL IfIndexExistInOptTaskSNMap(unsigned int uiIndex,
	hash_map<unsigned int, unsigned int>* pMap);
// ��ʩ�����������������еõ��������к�
MatrixServerDll_API unsigned int GetLineNbFromOptTaskSNMap(unsigned int uiIndex,
	hash_map<unsigned int, unsigned int>* pMap);
// ��ʩ�����������������м�������
MatrixServerDll_API void AddToOptTaskSNMap(unsigned int uiIndex, unsigned int uiLineNb,
	hash_map<unsigned int, unsigned int>* pMap);
// ����һ��ʩ������
MatrixServerDll_API void AddOptTaskToMap(unsigned int uiIndex, m_oOptTaskStruct* pOptTask, 
	hash_map<unsigned int, m_oOptTaskStruct*>* pMap);
// �������������ţ���������õ�ʩ������ָ��
MatrixServerDll_API m_oOptTaskStruct* GetOptTaskFromMap(unsigned int uiIndex, 
	hash_map<unsigned int, m_oOptTaskStruct*>* pMap);
// ��������ɾ��������ָ���ʩ������ָ��
MatrixServerDll_API BOOL DeleteOptTaskFromMap(unsigned int uiIndex, 
	hash_map<unsigned int, m_oOptTaskStruct*>* pMap);

/************************************************************************/
/* ʩ����������                                                         */
/************************************************************************/
// ����ʩ����������ṹ��
MatrixServerDll_API m_oOptTaskArrayStruct* OnCreateOptTaskArray(void);
// ����ʩ����������ṹ��
MatrixServerDll_API void OnResetOptTaskArray(m_oOptTaskArrayStruct* pOptTaskArray);
// ��ʼ��ʩ����������ṹ��
MatrixServerDll_API void OnInitOptTaskArray(m_oOptTaskArrayStruct* pOptTaskArray,
	m_oConstVarStruct* pConstVar);
// �ر�ʩ����������ṹ��
MatrixServerDll_API void OnCloseOptTaskArray(m_oOptTaskArrayStruct* pOptTaskArray);
// �ͷ�ʩ����������ṹ��
MatrixServerDll_API void OnFreeOptTaskArray(m_oOptTaskArrayStruct* pOptTaskArray);
// �õ�һ������ʩ������
MatrixServerDll_API m_oOptTaskStruct* GetFreeOptTask(m_oOptTaskArrayStruct* pOptTaskArray);
// ����һ������ʩ������
MatrixServerDll_API void AddFreeOptTask(m_oOptTaskStruct* pOptTask, m_oOptTaskArrayStruct* pOptTaskArray);

/************************************************************************/
/* �߳̽ṹ��                                                           */
/************************************************************************/
// ��ʼ���̺߳���
MatrixServerDll_API bool OnInitThread(m_oThreadStruct* pThread, 
	m_oLogOutPutStruct* pLogOutPut = NULL, m_oConstVarStruct* pConstVar = NULL);
// �ر��̺߳����ľ��
MatrixServerDll_API void OnCloseThreadHandle(m_oThreadStruct* pThread);
// �ر��̺߳���
MatrixServerDll_API bool OnCloseThread(m_oThreadStruct* pThread);

/************************************************************************/
/* ��־����߳�                                                         */
/************************************************************************/
// ������־����߳�
MatrixServerDll_API m_oLogOutPutThreadStruct* OnCreateLogOutPutThread(void);
// �̵߳ȴ�����
MatrixServerDll_API void WaitLogOutPutThread(m_oLogOutPutThreadStruct* pLogOutPutThread);
// ��ʼ����־����߳�
MatrixServerDll_API bool OnInitLogOutPutThread(m_oLogOutPutThreadStruct* pLogOutPutThread, 
	m_oLogOutPutStruct* pLogOutPut = NULL, m_oConstVarStruct* pConstVar = NULL);
// ��ʼ����־����߳�
MatrixServerDll_API bool OnInit_LogOutPutThread(m_oEnvironmentStruct* pEnv);
// �ر���־����߳�
MatrixServerDll_API bool OnCloseLogOutPutThread(m_oLogOutPutThreadStruct* pLogOutPutThread);
// �ͷ���־����߳�
MatrixServerDll_API void OnFreeLogOutPutThread(m_oLogOutPutThreadStruct* pLogOutPutThread);

/************************************************************************/
/* �����߳�                                                             */
/************************************************************************/
// ���������߳�
MatrixServerDll_API m_oHeartBeatThreadStruct* OnCreateHeartBeatThread(void);
// �̵߳ȴ�����
MatrixServerDll_API void WaitHeartBeatThread(m_oHeartBeatThreadStruct* pHeartBeatThread);
// ��ʼ�������߳�
MatrixServerDll_API bool OnInitHeartBeatThread(m_oHeartBeatThreadStruct* pHeartBeatThread, 
	m_oLogOutPutStruct* pLogOutPut = NULL, m_oConstVarStruct* pConstVar = NULL);
// ��ʼ�������߳�
MatrixServerDll_API bool OnInit_HeartBeatThread(m_oEnvironmentStruct* pEnv);
// �ر������߳�
MatrixServerDll_API bool OnCloseHeartBeatThread(m_oHeartBeatThreadStruct* pHeartBeatThread);
// �ͷ������߳�
MatrixServerDll_API void OnFreeHeartBeatThread(m_oHeartBeatThreadStruct* pHeartBeatThread);

/************************************************************************/
/* �װ��߳�                                                             */
/************************************************************************/
// �����װ������߳�
MatrixServerDll_API m_oHeadFrameThreadStruct* OnCreateHeadFrameThread(void);
// ����λ�ð����װ�ʱ������
MatrixServerDll_API void InstrumentLocationSort(m_oInstrumentStruct* pInstrument, 
	m_oRoutStruct* pRout, m_oConstVarStruct* pConstVar);
/**
* ���ý���վĳ�������·��
	* @param CInstrument* &pInstrument ����ָ��
* @param unsigned int uiRoutDirection ·�ɷ���
* @return void
*/
MatrixServerDll_API void SetCrossRout(m_oInstrumentStruct* pInstrument, int iRoutDirection, 
m_oConstVarStruct* pConstVar, m_oRoutListStruct* pRoutList);
// �������װ�֡
MatrixServerDll_API void ProcHeadFrameOne(m_oHeadFrameThreadStruct* pHeadFrameThread);
// �����װ�֡
MatrixServerDll_API void ProcHeadFrame(m_oHeadFrameThreadStruct* pHeadFrameThread);
// �̵߳ȴ�����
MatrixServerDll_API void WaitHeadFrameThread(m_oHeadFrameThreadStruct* pHeadFrameThread);
// ��ʼ���װ������߳�
MatrixServerDll_API bool OnInitHeadFrameThread(m_oHeadFrameThreadStruct* pHeadFrameThread, 
	m_oLogOutPutStruct* pLogOutPut = NULL, m_oConstVarStruct* pConstVar = NULL);
// ��ʼ���װ������߳�
MatrixServerDll_API bool OnInit_HeadFrameThread(m_oEnvironmentStruct* pEnv);
// �ر��װ������߳�
MatrixServerDll_API bool OnCloseHeadFrameThread(m_oHeadFrameThreadStruct* pHeadFrameThread);
// �ͷ��װ������߳�
MatrixServerDll_API void OnFreeHeadFrameThread(m_oHeadFrameThreadStruct* pHeadFrameThread);

/************************************************************************/
/* IP��ַ�����߳�                                                       */
/************************************************************************/
// ����IP��ַ�����߳�
MatrixServerDll_API m_oIPSetFrameThreadStruct* OnCreateIPSetFrameThread(void);
// ������IP��ַ����Ӧ��֡
MatrixServerDll_API void  ProcIPSetReturnFrameOne(m_oIPSetFrameThreadStruct* pIPSetFrameThread);
// ����IP��ַ����Ӧ��֡
MatrixServerDll_API void ProcIPSetReturnFrame(m_oIPSetFrameThreadStruct* pIPSetFrameThread);
// ����IP��ַ������������IP��ַ����֡
MatrixServerDll_API void ProcIPSetFrame(m_oIPSetFrameThreadStruct* pIPSetFrameThread);
// �̵߳ȴ�����
MatrixServerDll_API void WaitIPSetFrameThread(m_oIPSetFrameThreadStruct* pIPSetFrameThread);
// ��ʼ��IP��ַ�����߳�
MatrixServerDll_API bool OnInitIPSetFrameThread(m_oIPSetFrameThreadStruct* pIPSetFrameThread, 
	m_oLogOutPutStruct* pLogOutPut = NULL, m_oConstVarStruct* pConstVar = NULL);
// ��ʼ��IP��ַ�����߳�
MatrixServerDll_API bool OnInit_IPSetFrameThread(m_oEnvironmentStruct* pEnv);
// �ر�IP��ַ�����߳�
MatrixServerDll_API bool OnCloseIPSetFrameThread(m_oIPSetFrameThreadStruct* pIPSetFrameThread);
// �ͷ�IP��ַ�����߳�
MatrixServerDll_API void OnFreeIPSetFrameThread(m_oIPSetFrameThreadStruct* pIPSetFrameThread);

/************************************************************************/
/* β���߳�                                                             */
/************************************************************************/
// ����β�������߳�
MatrixServerDll_API m_oTailFrameThreadStruct* OnCreateTailFrameThread(void);
// �̵߳ȴ�����
MatrixServerDll_API void WaitTailFrameThread(m_oTailFrameThreadStruct* pTailFrameThread);
// ����������·�ɷ�����ͬ��֮ǰ������β������
MatrixServerDll_API void OnClearSameRoutTailCount(m_oInstrumentStruct* pInstrument, 
	m_oRoutStruct* pRout, m_oConstVarStruct* pConstVar);
// ����һ��·��
MatrixServerDll_API void FreeRoutFromMap(unsigned int uiRoutIP, m_oRoutListStruct* pRoutList);
// ����һ������
MatrixServerDll_API void FreeInstrumentFromMap(m_oInstrumentStruct* pInstrument, 
	m_oInstrumentListStruct* pInstrumentList, m_oRoutListStruct* pRoutList, m_oConstVarStruct* pConstVar);
// ɾ����·�ɷ���ָ������֮�������
MatrixServerDll_API void DeleteInstrumentAlongRout(m_oInstrumentStruct* pInstrument, m_oRoutStruct* pRout, 
	m_oInstrumentListStruct* pInstrumentList, m_oRoutListStruct* pRoutList, m_oConstVarStruct* pConstVar);
// ��·�ɷ�����ɾ��������֮���ȫ������
MatrixServerDll_API void DeleteAllInstrumentAlongRout(m_oInstrumentStruct* pInstrument, m_oRoutStruct* pRout, 
	m_oInstrumentListStruct* pInstrumentList, m_oRoutListStruct* pRoutList, m_oConstVarStruct* pConstVar,
	m_oLogOutPutStruct* pLogOutPut);
// ������β��֡
MatrixServerDll_API void ProcTailFrameOne(m_oTailFrameThreadStruct* pTailFrameThread);
// ����β��֡
MatrixServerDll_API void ProcTailFrame(m_oTailFrameThreadStruct* pTailFrameThread);
// ��ʼ��β�������߳�
MatrixServerDll_API bool OnInitTailFrameThread(m_oTailFrameThreadStruct* pTailFrameThread, 
	m_oLogOutPutStruct* pLogOutPut = NULL, m_oConstVarStruct* pConstVar = NULL);
// ��ʼ��β�������߳�
MatrixServerDll_API bool OnInit_TailFrameThread(m_oEnvironmentStruct* pEnv);
// �ر�β�������߳�
MatrixServerDll_API bool OnCloseTailFrameThread(m_oTailFrameThreadStruct* pTailFrameThread);
// �ͷ�β�������߳�
MatrixServerDll_API void OnFreeTailFrameThread(m_oTailFrameThreadStruct* pTailFrameThread);

/************************************************************************/
/* ʱͳ�߳�                                                             */
/************************************************************************/
// ����ʱͳ�߳�
MatrixServerDll_API m_oTimeDelayThreadStruct* OnCreateTimeDelayThread(void);
// �̵߳ȴ�����
MatrixServerDll_API void WaitTimeDelayThread(m_oTimeDelayThreadStruct* pTimeDelayThread);
// β��ʱ�̲�ѯ׼������
MatrixServerDll_API void PrepareTailTimeFrame(m_oRoutStruct* pRout, m_oConstVarStruct* pConstVar);
// ����β��ʱ�̲�ѯ
MatrixServerDll_API void ProcTailTimeFrame(m_oRoutStruct* pRout, m_oTimeDelayThreadStruct* pTimeDelayThread);
// ������β��ʱ�̲�ѯӦ��֡
MatrixServerDll_API void ProcTailTimeReturnFrameOne(m_oRoutStruct* pRout, 
	m_oTimeDelayThreadStruct* pTimeDelayThread);
// ����β��ʱ�̲�ѯӦ��
MatrixServerDll_API void ProcTailTimeReturnFrame(m_oRoutStruct* pRout, 
	m_oTimeDelayThreadStruct* pTimeDelayThread);
// ���β��ʱ�̲�ѯ����Ƿ������ȫ
MatrixServerDll_API bool CheckTailTimeReturn(m_oRoutStruct* pRout, m_oTimeDelayThreadStruct* pTimeDelayThread);
// ����ʱͳ����
MatrixServerDll_API void ProcTimeDelayFrame(m_oRoutStruct* pRout, m_oTimeDelayThreadStruct* pTimeDelayThread);
// ������ʱͳ����Ӧ��
MatrixServerDll_API void ProcTimeDelayReturnFrameOne(m_oTimeDelayThreadStruct* pTimeDelayThread);
// ����ʱͳ����Ӧ��
MatrixServerDll_API void ProcTimeDelayReturnFrame(m_oTimeDelayThreadStruct* pTimeDelayThread);
// ��ʼ��ʱͳ�����߳�
MatrixServerDll_API bool OnInitTimeDelayThread(m_oTimeDelayThreadStruct* pTimeDelayThread, 
	m_oLogOutPutStruct* pLogOutPut = NULL, m_oConstVarStruct* pConstVar = NULL);
// ��ʼ��ʱͳ�����߳�
MatrixServerDll_API bool OnInit_TimeDelayThread(m_oEnvironmentStruct* pEnv);
// �ر�ʱͳ�����߳�
MatrixServerDll_API bool OnCloseTimeDelayThread(m_oTimeDelayThreadStruct* pTimeDelayThread);
// �ͷ�ʱͳ�����߳�
MatrixServerDll_API void OnFreeTimeDelayThread(m_oTimeDelayThreadStruct* pTimeDelayThread);

/************************************************************************/
/* ADC���������߳�                                                      */
/************************************************************************/
// ����ADC���������߳�
MatrixServerDll_API m_oADCSetThreadStruct* OnCreateADCSetThread(void);
// ����ADC��������֡
MatrixServerDll_API void OnSelectADCSetCmd(m_oADCSetThreadStruct* pADCSetThread, bool bRout, 
	unsigned int uiDstIP);
// �ֶ�����ADC��������֡
MatrixServerDll_API bool OnSetADCSetFrameByHand(int iLineIndex, int iPointIndex, int iDirection, bool bRout, 
	char* cpADCSet, int iADCSetNum, m_oEnvironmentStruct* pEnv);
// ����ADC��������֡
MatrixServerDll_API void OnSendADCSetCmd(m_oADCSetThreadStruct* pADCSetThread);
// ����ADC��������Ӧ��֡
MatrixServerDll_API void ProcADCSetReturnFrameOne(m_oADCSetThreadStruct* pADCSetThread);
// ������պͷ���֡��ͳ�ƽ��
MatrixServerDll_API void OnOutPutADCDataRecResult(m_oADCSetThreadStruct* pADCSetThread);
// ����Ӧ�������ȫ��Ĳ���
MatrixServerDll_API void OnADCSetNextOpt(m_oADCSetThreadStruct* pADCSetThread);
// �ж�ADC��������Ӧ���Ƿ������ȫ
MatrixServerDll_API bool CheckADCSetReturnFrame(m_oADCSetThreadStruct* pADCSetThread);
// ����ADC��������Ӧ��֡
MatrixServerDll_API void ProcADCSetReturnFrame(m_oADCSetThreadStruct* pADCSetThread);
// �̵߳ȴ�����
MatrixServerDll_API void WaitADCSetThread(m_oADCSetThreadStruct* pADCSetThread);
// ��ʼ��ADC���������߳�
MatrixServerDll_API bool OnInitADCSetThread(m_oADCSetThreadStruct* pADCSetThread, 
	m_oLogOutPutStruct* pLogOutPut = NULL, m_oConstVarStruct* pConstVar = NULL);
// ��ʼ��ADC���������߳�
MatrixServerDll_API bool OnInit_ADCSetThread(m_oEnvironmentStruct* pEnv);
// �ر�ADC���������߳�
MatrixServerDll_API bool OnCloseADCSetThread(m_oADCSetThreadStruct* pADCSetThread);
// �ͷ�ADC���������߳�
MatrixServerDll_API void OnFreeADCSetThread(m_oADCSetThreadStruct* pADCSetThread);

/************************************************************************/
/* �����ѯ�߳�                                                         */
/************************************************************************/
// ���������ѯ�߳�
MatrixServerDll_API m_oErrorCodeThreadStruct* OnCreateErrorCodeThread(void);
// �̵߳ȴ�����
MatrixServerDll_API void WaitErrorCodeThread(m_oErrorCodeThreadStruct* pErrorCodeThread);
// �����������ѯӦ��֡
MatrixServerDll_API void ProcErrorCodeReturnFrameOne(m_oErrorCodeThreadStruct* pErrorCodeThread);
// ���������ѯӦ��֡
MatrixServerDll_API void ProcErrorCodeReturnFrame(m_oErrorCodeThreadStruct* pErrorCodeThread);
// ���������ѯ֡
MatrixServerDll_API void ProcErrorCodeQueryFrame(m_oErrorCodeThreadStruct* pErrorCodeThread);
// ��ʼ�������ѯ�߳�
MatrixServerDll_API bool OnInitErrorCodeThread(m_oErrorCodeThreadStruct* pErrorCodeThread, 
	m_oLogOutPutStruct* pLogOutPut = NULL, m_oConstVarStruct* pConstVar = NULL);
// ��ʼ�������ѯ�߳�
MatrixServerDll_API bool OnInit_ErrorCodeThread(m_oEnvironmentStruct* pEnv);
// �ر������ѯ�߳�
MatrixServerDll_API bool OnCloseErrorCodeThread(m_oErrorCodeThreadStruct* pErrorCodeThread);
// �ͷ������ѯ�߳�
MatrixServerDll_API void OnFreeErrorCodeThread(m_oErrorCodeThreadStruct* pErrorCodeThread);

/************************************************************************/
/* �����߳�                                                             */
/************************************************************************/
// ����·�ɼ����߳�
MatrixServerDll_API m_oMonitorThreadStruct* OnCreateMonitorThread(void);
// �̵߳ȴ�����
MatrixServerDll_API void WaitMonitorThread(m_oMonitorThreadStruct* pMonitorThread);
// ����·�ɷ���õ�ʱͳ����
MatrixServerDll_API void GetTimeDelayTaskAlongRout(m_oRoutStruct* pRout, 
	m_oRoutListStruct* pRoutList, m_oConstVarStruct* pConstVar);
// �õ�ʱͳ����
MatrixServerDll_API void GetTimeDelayTask(m_oRoutListStruct* pRoutList, m_oConstVarStruct* pConstVar);
// ����ʱͳ�������
MatrixServerDll_API void GenTimeDelayTaskQueue(m_oRoutListStruct* pRoutList, m_oConstVarStruct* pConstVar);
// ADC���������߳̿�ʼ����
MatrixServerDll_API void OnADCSetThreadWork(int iOpt, m_oADCSetThreadStruct* pADCSetThread);
// ���ADC����������������
MatrixServerDll_API void OnClearADCSetMap(m_oADCSetThreadStruct* pADCSetThread);
// ����������ADC��������������
MatrixServerDll_API void GetADCTaskQueueBySN(m_oADCSetThreadStruct* pADCSetThread, 
	m_oInstrumentStruct* pInstrument, int iOpt);
// �ж�·�ɷ������Ƿ��вɼ�վ
MatrixServerDll_API void GetADCTaskQueueByRout(m_oADCSetThreadStruct* pADCSetThread, 
	m_oRoutStruct* pRout, int iOpt);
// ����ADC���������������
MatrixServerDll_API void GetADCTaskQueue(m_oADCSetThreadStruct* pADCSetThread, int iOpt);
// �Զ���ʼADC��������
MatrixServerDll_API void OnADCCmdAuto(m_oADCSetThreadStruct* pADCSetThread, int iOpt);
// ADC��������
MatrixServerDll_API void OnADCSetAuto(m_oADCSetThreadStruct* pADCSetThread);
// ADC��ʼ�ɼ�����
MatrixServerDll_API void OnADCStartSampleAuto(m_oADCSetThreadStruct* pADCSetThread);
// ADCֹͣ�ɼ�����
MatrixServerDll_API void OnADCStopSampleAuto(m_oADCSetThreadStruct* pADCSetThread);
// ���ӹ���·�ɼ�����
MatrixServerDll_API void MonitorRoutAndInstrument(m_oMonitorThreadStruct* pMonitorThread);
// ���ʱͳ����Ӧ���Ƿ������ȫ
MatrixServerDll_API bool CheckTimeDelayReturnByRout(m_oRoutStruct* pRout, 
	m_oTimeDelayThreadStruct* pTimeDelayThread, bool bSample);
// ��������Ƿ������ʱͳ
MatrixServerDll_API bool CheckTimeDelayReturn(m_oTimeDelayThreadStruct* pTimeDelayThread);
// ����ʱͳ
MatrixServerDll_API void MonitorTimeDelay(m_oTimeDelayThreadStruct* pTimeDelayThread);
// ����������ADC��������
MatrixServerDll_API void MonitorADCSet(m_oADCSetThreadStruct* pADCSetThread);
// ��������������
MatrixServerDll_API void MonitorErrorCode(m_oErrorCodeThreadStruct* pErrorCodeThread);
// ����·�ɼ���
MatrixServerDll_API void ProcMonitor(m_oMonitorThreadStruct* pMonitorThread);
// ��ʼ��·�ɼ����߳�
MatrixServerDll_API bool OnInitMonitorThread(m_oMonitorThreadStruct* pMonitorThread, 
	m_oLogOutPutStruct* pLogOutPut = NULL, m_oConstVarStruct* pConstVar = NULL);
// ��ʼ��·�ɼ����߳�
MatrixServerDll_API bool OnInit_MonitorThread(m_oEnvironmentStruct* pEnv);
// �ر�·�ɼ����߳�
MatrixServerDll_API bool OnCloseMonitorThread(m_oMonitorThreadStruct* pMonitorThread);
// �ͷ�·�ɼ����߳�
MatrixServerDll_API void OnFreeMonitorThread(m_oMonitorThreadStruct* pMonitorThread);

/************************************************************************/
/* ADC���ݽ����߳�                                                      */
/************************************************************************/
// ����ADC���ݽ����߳�
MatrixServerDll_API m_oADCDataRecThreadStruct* OnCreateADCDataRecThread(void);
// �̵߳ȴ�����
MatrixServerDll_API void WaitADCDataRecThread(m_oADCDataRecThreadStruct* pADCDataRecThread);
// ��ADC���ݼ��뵽�����б�
MatrixServerDll_API void AddToADCDataWriteFileList(int iLineIndex, int iPointIndex, 
	unsigned int uiFrameNb, unsigned int uiSN, unsigned int uiSysTime, 
	m_oADCDataRecThreadStruct* pADCDataRecThread);
// �������ݻص�����
MatrixServerDll_API void GetProSampleDateCallBack(m_oADCDataRecThreadStruct* pADCDataRecThread, 
	ProSampleDateCallBack pCallBack);
// ������ADC����֡
MatrixServerDll_API void ProcADCDataRecFrameOne(m_oADCDataRecThreadStruct* pADCDataRecThread);
// ����ADC���ݽ���֡
MatrixServerDll_API void ProcADCDataRecFrame(m_oADCDataRecThreadStruct* pADCDataRecThread);
// ����ADC�����ط�
MatrixServerDll_API void ProcADCRetransmission(m_oADCDataRecThreadStruct* pADCDataRecThread);
// ��ʼ��ADC���ݽ����߳�
MatrixServerDll_API bool OnInitADCDataRecThread(m_oADCDataRecThreadStruct* pADCDataRecThread, 
	m_oLogOutPutStruct* pLogOutPut = NULL, m_oConstVarStruct* pConstVar = NULL);
// ��ʼ��ADC���ݽ����߳�
MatrixServerDll_API bool OnInit_ADCDataRecThread(m_oEnvironmentStruct* pEnv);
// �ر�ADC���ݽ����߳�
MatrixServerDll_API bool OnCloseADCDataRecThread(m_oADCDataRecThreadStruct* pADCDataRecThread);
// �ͷ�ADC���ݽ����߳�
MatrixServerDll_API void OnFreeADCDataRecThread(m_oADCDataRecThreadStruct* pADCDataRecThread);
/************************************************************************/
/* ʩ���������ݴ洢�߳�                                                 */
/************************************************************************/
// ����ʩ���������ݴ洢�߳�
MatrixServerDll_API m_oADCDataSaveThreadStruct* OnCreateADCDataSaveThread(void);
// �̵߳ȴ�����
MatrixServerDll_API void WaitADCDataSaveThread(m_oADCDataSaveThreadStruct* pADCDataSaveThread);
// ����ADC���ݵ�ʩ���ļ�
MatrixServerDll_API void WriteADCDataInOptTaskFile(m_oADCDataBufStruct* pADCDataBuf, 
	m_oOptTaskStruct* pOptTask, unsigned int uiLineIndex, m_oConstVarStruct* pConstVar);
// �ر����е�ʩ���ļ�
MatrixServerDll_API void CloseAllADCDataSaveInFile(m_oOptTaskArrayStruct* pOptTaskArray);
// ����ADC���ݵ�ʩ���ļ�
MatrixServerDll_API void ProcADCDataSaveInFile(m_oADCDataSaveThreadStruct* pADCDataSaveThread);
// ��ʼ��ʩ���������ݴ洢�߳�
MatrixServerDll_API bool OnInitADCDataSaveThread(m_oADCDataSaveThreadStruct* pADCDataSaveThread, 
	m_oLogOutPutStruct* pLogOutPut = NULL, m_oConstVarStruct* pConstVar = NULL);
// ��ʼ��ʩ���������ݴ洢�߳�
MatrixServerDll_API bool OnInit_ADCDataSaveThread(m_oEnvironmentStruct* pEnv);
// �ر�ʩ���������ݴ洢�߳�
MatrixServerDll_API bool OnCloseADCDataSaveThread(m_oADCDataSaveThreadStruct* pADCDataSaveThread);
// �ͷ�ʩ���������ݴ洢�߳�
MatrixServerDll_API void OnFreeADCDataSaveThread(m_oADCDataSaveThreadStruct* pADCDataSaveThread);

/************************************************************************/
/* �������                                                             */
/************************************************************************/
// ����һ��ʩ������
MatrixServerDll_API void GenOneOptTask(unsigned int uiIndex, unsigned int uiStartFrame, 
	m_oOptTaskArrayStruct* pOptTaskArray, m_oInstrumentListStruct* pInstrumentList,
	m_oConstVarStruct* pConstVar);
// �ͷ�һ��ʩ������
MatrixServerDll_API void FreeOneOptTask(unsigned int uiIndex, 
	m_oOptTaskArrayStruct* pOptTaskArray);
// ��SN����ADC�������ñ�־λ
MatrixServerDll_API void OnResetADCSetLableBySN(m_oInstrumentStruct* pInstrument, int iOpt, 
	m_oInstrumentListStruct* pInstrumentList, m_oConstVarStruct* pConstVar);
// ��·������ADC�������ñ�־λ
MatrixServerDll_API void OnResetADCSetLableByRout(m_oRoutStruct* pRout, int iOpt, 
	m_oConstVarStruct* pConstVar);
// ����·�ɵ�ַ����ADC�������ñ�־λ
MatrixServerDll_API void OnSetADCByLAUXSN(int iLineIndex, int iPointIndex, int iDirection, int iOpt, 
	m_oEnvironmentStruct* pEnv, bool bOnly = true, bool bRout = true);
// ����ADC�������ñ�־λ
MatrixServerDll_API void OnResetADCSetLable(m_oRoutListStruct* pRoutList, int iOpt, 
	m_oConstVarStruct* pConstVar);
// ADC��������
MatrixServerDll_API void OnADCSet(m_oEnvironmentStruct* pEnv);
// ADC��ʼ�ɼ�����
MatrixServerDll_API void OnADCStartSample(m_oEnvironmentStruct* pEnv);
// ADCֹͣ�ɼ�����
MatrixServerDll_API void OnADCStopSample(m_oEnvironmentStruct* pEnv);
// ������պͷ���֡��ͳ�ƽ��
MatrixServerDll_API void OnOutPutResult(m_oEnvironmentStruct* pEnv);
// ����ʵ����������ʵ��ָ��
MatrixServerDll_API m_oEnvironmentStruct* OnCreateInstance(void);
// ��ʼ��ʵ��
MatrixServerDll_API void OnInit(m_oEnvironmentStruct* pEnv);
// �ر�
MatrixServerDll_API void OnClose(m_oEnvironmentStruct* pEnv);
// ����
MatrixServerDll_API void OnWork(m_oEnvironmentStruct* pEnv);
// ֹͣ
MatrixServerDll_API void OnStop(m_oEnvironmentStruct* pEnv);
// �ͷ�ʵ����Դ
MatrixServerDll_API void OnFreeInstance(m_oEnvironmentStruct* pEnv);



#undef MatrixServerDll_API
#ifdef __cplusplus
}
#endif

#endif
