// ���� ifdef ���Ǵ���ʹ�� DLL �������򵥵�
// ��ı�׼�������� DLL �е������ļ��������������϶���� MATRIXSERVERDLL_EXPORTS
// ���ű���ġ���ʹ�ô� DLL ��
// �κ�������Ŀ�ϲ�Ӧ����˷��š�������Դ�ļ��а������ļ����κ�������Ŀ���Ὣ
// MATRIXSERVERDLL_API ������Ϊ�Ǵ� DLL ����ģ����� DLL ���ô˺궨���
// ������Ϊ�Ǳ������ġ�
#pragma once
#ifndef _MatrixServerDll_H
#define _MatrixServerDll_H
#include "ConfigLineXml.h"
#include "ConfigOperationXml.h"
#include "ConfigPcapXml.h"
#include "Segd.h"
#include "Parameter.h"
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
/**
* @struct LogOutPut_Struct
* @brief ��־����ṹ
*/
typedef struct LogOutPut_Struct
{
	/** ��־�����Դͬ������*/
	CRITICAL_SECTION m_oSecLogFile;
	/** ��־����ļ�ָ��*/
	FILE* m_pFile;
	/** ��־����ṹ*/
	list<string> m_oLogOutputList;
	/** �������*/
	unsigned int m_uiErrorCount;
	/** ��־���·��*/
	string m_SaveLogFilePath;
	/** ��־�ļ����*/
	unsigned int m_uiLogFileNb;
	/** ��־�ļ��洢��Ϣ��������*/
	unsigned int m_uiLogInfoCount;
	/** ��־�ļ�����*/
	char m_cLogFileType;
}m_oLogOutPutStruct;

/**
* @struct ConstVar_Struct
* @brief ��INI�ļ��н����õ��ĳ���
* @note	�ýṹ���еı���ֵֻ����INI�ļ��б��޸�
* @note �ݲ�֧���ڳ������޸ģ����ܻ�����ڴ��ͻ�������
*/
typedef struct ConstVar_Struct
{
	/** INI�ļ�·��*/
	string m_strINIFilePath;
	/** �����豸����*/
	unsigned int m_iInstrumentNum;
	/** SEGD���ݻ���������*/
	int m_iSEGDDataBufCountAll;
	/** SEGD���ݻ�������С*/
	int m_iSEGDDataBufSize;
	/** �ж�SEGD���ݴ洢��ɵ�ʱ��*/
	int m_iSEGDCheckFinishTime;
	/** ʩ���������*/
	int m_iOptTaskCountAll;
	/** һ�����ߵ�ʱ��*/
	int m_iOneSleepTime;
	/** ��־����߳�д��־����ʱ����*/
	int m_iLogOutPutSleepTimes;
	/** �����̷߳�������֡��ʱ����*/
	int m_iHeartBeatSleepTimes;
	/** �װ��߳̽����װ���ʱ����*/
	int m_iHeadFrameSleepTimes;
	/** IP��ַ�����߳���ʱ����*/
	int m_iIPSetFrameSleepTimes;
	/** β���߳���ʱ����*/
	int m_iTailFrameSleepTimes;
	/** ·�ɼ����߳���ʱ����*/
	int m_iMonitorSleepTimes;
	/** ʱͳ�����߳���ʱ����*/
	int m_iTimeDelaySleepTimes;
	/** ADC���������߳���ʱ����*/
	int m_iADCSetSleepTimes;
	/** �����ѯ�߳���ʱ����*/
	int m_iErrorCodeSleepTimes;
	/** ADC���ݽ����߳���ʱ����*/
	int m_iADCDataRecSleepTimes;
	/** ADC���ݴ洢�߳���ʱ����*/
	int m_iADCDataSaveSleepTimes;
	/** �ȴ��̹߳رյ���ʱ����*/
	int m_iCloseThreadSleepTimes;
	/** �ɼ�վ���ɼ�վ��ʱͳ����ֵ*/
	int m_iTimeDelayFDUToFDU;
	/** LCI���ɼ�վ��ʱͳ����ֵ*/
	int m_iTimeDelayLCIToFDU;
	/** �ɼ�վ��LAUL��ʱͳ����ֵ*/
	int m_iTimeDelayFDUToLAUL;
	/** LAUL���ɼ�վ��ʱͳ����ֵ*/
	int m_iTimeDelayLAULToFDU;
	/** �װ��ȶ�����*/
	int m_iHeadFrameStableTimes;
	/** IP��ַ�������*/
	int m_iIPAddrResetTimes;
	/** β���ȶ�����*/
	int m_iTailFrameStableTimes;
	/** ·�ɼ����ȶ�ʱ��*/
	int m_iMonitorStableTime;
	/** ����ϵͳ״̬-link*/
	int m_iLineSysStatusLink;
	/** ����ϵͳ״̬-�ȶ�*/
	int m_iLineSysStatusStable;
	/** ����ϵͳ״̬-�����ɼ�*/
	int m_iLineSysStatusNoise;
	/** ����ϵͳ״̬-TB�ɼ�*/
	int m_iLineSysStatusSample;
	/** ����ϵͳ�ﵽ�ȶ�״̬ʱ��*/
	int m_iLineSysStableTime;
// 	/** ADC�������ò������*/
// 	int m_iADCSetOptNb;
// 	/** ADC��ʼ�ɼ��������*/
// 	int m_iADCStartSampleOptNb;
// 	/** ADCֹͣ�ɼ��������*/
// 	int m_iADCStopSampleOptNb;
	/** ADC��������������*/
	int m_iADCSetCmdNum;
	/** ADC����������ʼ�������*/
	int m_iADCSetCmdBeginNb;
	/** ADC��ʼ�ɼ�������*/
	int m_iADCStartSampleCmdNum;
	/** ADC��ʼ�ɼ���ʼ�������*/
	int m_iADCStartSampleBeginNb;
	/** ADCֹͣ�ɼ�������*/
	int m_iADCStopSampleCmdNum;
	/** ADCֹͣ�ɼ���ʼ�������*/
	int m_iADCStopSampleBeginNb;
// 	/** ��������-����վ*/
// 	int m_iInstrumentTypeLAUX;
// 	/** ��������-��Դվ*/
// 	int m_iInstrumentTypeLAUL;
// 	/** ��������-�ɼ�վ*/
// 	int m_iInstrumentTypeFDU;
// 	/** ��������-LCI*/
// 	int m_iInstrumentTypeLCI;
// 	/** �����Ϸ�*/
// 	int m_iDirectionTop;
// 	/** �����·�*/
// 	int m_iDirectionDown;
// 	/** ������*/
// 	int m_iDirectionLeft;
// 	/** �����ҷ�*/
// 	int m_iDirectionRight;
	/** ��������*/
	int m_iDirectionCenter;
	/** IP��ַ���õ���ʼ��ַ*/
	int m_iIPSetAddrStart;
	/** IP��ַ���õļ��*/
	int m_iIPSetAddrInterval;
	/** ·�ɵ�ַ���õ���ʼ��ַ*/
	int m_iRoutSetAddrStart;
	/** ·�ɵ�ַ���õļ��*/
	int m_iRoutSetAddrInterval;
	/** ���ù㲥�˿���ʼ��ַ*/
	int m_iBroadcastPortStart;
	/** ����Ϊ�㲥IP*/
	unsigned int m_uiIPBroadcastAddr;
// 	/** һ���ļ��ڴ洢�����豸ADC����֡��*/
// 	int m_iADCFrameSaveInOneFileNum;
	/** �洢ADC���ݵ��ļ�ͷ����*/
	int m_iADCSaveHeadLineNum;
	/** �洢ADC���ݵ����Ԥ����Ϣ�ֽ���*/
	int m_iADCSaveLeftInfoBytes;
	/** �洢ADC���ݵ��ֽ���*/
	int m_iADCSaveDataBytes;
	/** �洢ADC����֮��ļ���ֽ���*/
	int m_iADCSaveDataIntervalBytes;
	/** �豸ADC���ݻ�������С*/
	int m_iADCDataBufSize;
	/** �洢���ڲ��Լ�������ݸ���*/
	unsigned int m_uiSaveTestDataNum;

	/** ֡ͷ����*/
	int m_iFrameHeadSize;
	/** ͬ��֡ͷ*/
	char* m_cpFrameHeadCheck;
	/** �����ֳ���1�ֽ�*/
	int m_iFrameCmdSize1B;
	/** ���������1�ֽ�*/
	int m_iFramePacketSize1B;
	/** ���������2�ֽ�*/
	int m_iFramePacketSize2B;
	/** ���������4�ֽ�*/
	int m_iFramePacketSize4B;
	/** ADC������ռ�ֽ���*/
	int m_iADCDataSize3B;
	/** һ֡��ADC���ݸ���*/
	int m_iADCDataInOneFrameNum;
	/** ADC����ָ֡��ƫ��������*/
	unsigned short m_usADCFramePointLimit;
	/** �����ָ������ֵ*/
	int m_iCommandWordMaxNum;
	/** 0x18�����������������ֽ���*/
	int m_iADCSetCommandMaxByte;
	/** ����֡��������ֵ�趨*/
	char m_cSndFrameBufInit;
	/** ���յ���������֡֡����*/
	int m_iRcvFrameSize;
	/** ���͵���������֡֡����*/
	int m_iSndFrameSize;
	/**____���������豸����������____*/
	/** ������������*/
	unsigned short m_usSendSetCmd;
	/** ���Ͳ�ѯ����*/
	unsigned short m_usSendQueryCmd;
	/** ����ADC���������ط�����*/
	unsigned short m_usSendADCCmd;
	/** ����*/
	BYTE m_byCmdSn;
	/** �װ�ʱ��*/
	BYTE m_byCmdHeadFrameTime;
	/** ����IP��ַ*/
	BYTE m_byCmdLocalIPAddr;
	/** ����ϵͳʱ��*/
	BYTE m_byCmdLocalSysTime1;
	/** ����ϵͳʱ��*/
	BYTE m_byCmdLocalSysTime2;
	/** ����ϵͳʱ��*/
	BYTE m_byCmdLocalSysTime3;
	/** ����ʱ��������λ*/
	BYTE m_byCmdLocalTimeFixedHigh;
	/** ����ʱ��������λ*/
	BYTE m_byCmdLocalTimeFixedLow;
	/** �Զ����ݷ��ص�ַ*/
	BYTE m_byCmdADCDataReturnAddr;
	/** �Զ����ݷ��ض˿ں�����*/
	BYTE m_byCmdADCDataReturnPort;
	/** �˿ڵ������޺�����*/
	BYTE m_byCmdADCDataReturnPortLimit;
	/** ��������ȴ��˿ں�����*/
	BYTE m_byCmdBroadCastPortSet;
	/** ϵͳӲ��״̬����*/
	BYTE m_byCmdFDUErrorCode;
	/** TBʱ�̸�λ*/
	BYTE m_byCmdTBHigh;
	/** TBʱ�̵�λ*/
	BYTE m_byCmdTbLow;
	/** work_ctrl ����վ����*/
	BYTE m_byCmdLAUXRoutOpenQuery;
	/** ·�ɿ���*/
	BYTE m_byCmdLAUXRoutOpenSet;
	/** �����豸�汾*/
	BYTE m_byCmdVersion;
	/** β������\����ʱ�̵�λ*/
	BYTE m_byCmdTailRecSndTime1;
	/** β������\����ʱ�̵�λ*/
	BYTE m_byCmdTailRecSndTime2;
	/** β������\����ʱ�̵�λ*/
	BYTE m_byCmdTailRecSndTime3;
	/** �㲥����ȴ��˿�ƥ��*/
	BYTE m_byCmdBroadCastPortSeted;
	/** ����ADC��������������*/
	BYTE m_byCmdADCSet;
	/** ����ʱ��*/
	BYTE m_byCmdNetTime;
	/** ����վ����β������ʱ��*/
	BYTE m_byCmdLineTailRecTimeLAUX;
	/** ����վ������β������ʱ��*/
	BYTE m_byCmdLAUTailRecTimeLAUX;
	/** ����վ����1*/
	BYTE m_byCmdLAUXErrorCode1;
	/** ����վ����2*/
	BYTE m_byCmdLAUXErrorCode2;
	/** ����վ·�ɷ���*/
	BYTE m_byCmdLAUXSetRout;
	/** ����·��*/
	BYTE m_byCmdReturnRout;
	/** ���������������*/
	BYTE m_byCmdEnd;

	/** TB������ʱ��λ*/
	unsigned int m_uiTBSleepTimeHigh;
	/** TB������ʱ��λ*/
	unsigned short m_usTBSleepTimeLow;
	/** FieldOn����һ��FieldOff��ʱ����*/
	unsigned int m_uiFieldOnWaitTimeLimit;
	/** TB���ƣ�0x0001 ����TB����ADC���ݲɼ�*/
	unsigned short m_usCmdTBCtrlStartSample;
	/** 0x0002 ����TB���ؿ���ADC���ݲɼ�����*/
	unsigned short m_usCmdTBLoseCtrlStartSample;
	/** 0x0000 TB���ؿ���ADC����ֹͣ�ɼ�����*/
	unsigned short m_usCmdTBCtrlStopSample;
	/** LED����*/
	unsigned short m_usCmdCtrlCloseLed;
}m_oConstVarStruct;

/**
* @struct XMLIPSetupData_Struct
* @brief ��XML�ļ��н����õ�IP��ַ��������
*/
typedef struct XMLIPSetupData_Struct
{
	/** Դ��ַ*/
	unsigned int m_uiSrcIP;
	/** LCI��IP��ַ*/
	unsigned int m_uiAimIP;
	/** �Զ����ݷ��ص�ַ*/
	unsigned int m_uiADCDataReturnAddr;
}m_oXMLIPSetupDataStruct;

/**
* @struct XMLPortSetupData_Struct
* @brief ��XML�ļ��н����õ��˿���������
*/ 
typedef struct XMLPortSetupData_Struct
{
	/** LCI���յĶ˿ں�*/
	unsigned short m_usAimPort;
	/** ����֡���ض˿�*/
	unsigned short m_usHeartBeatReturnPort;
	/** �װ����ն˿�*/
	unsigned short m_usHeadFramePort;
	/** IP��ַ���÷��ض˿�*/
	unsigned short m_usIPSetReturnPort;
	/** β�����ն˿�*/
	unsigned short m_usTailFramePort;
	/** β��ʱ�̲�ѯ���ն˿�*/
	unsigned short m_usTailTimeReturnPort;
	/** ʱͳ����Ӧ��˿�*/
	unsigned short m_usTimeDelayReturnPort;
	/** ADC��������Ӧ��˿�*/
	unsigned short m_usADCSetReturnPort;
	/** �����ѯ���ض˿�*/
	unsigned short m_usErrorCodeReturnPort;
	/** ADC���ݷ��ض˿�*/
	unsigned short m_usADCDataReturnPort;
}m_oXMLPortSetupDataStruct;

/**
* @struct XMLADCSetupData_Struct
* @brief ��XML�ļ��н����õ�ADC����������Ϣ
*/
typedef struct XMLADCSetupData_Struct
{
	/** ADC�������Ҳ������С*/
	int m_iSetADCSetSineSize;
	/** ADC�������Ҳ�����*/
	char* m_cpSetADCSetSine;
	/** ADC����ֹͣ���������С*/
	int m_iSetADCStopSampleSize;
	/** ADC����ֹͣ��������*/
	char* m_cpSetADCStopSample;
	/** ADC���ô�TB��Դ��λ��С*/
	int m_iSetADCOpenTBPowerLowSize;
	/** ADC���ô�TB��Դ��λ*/
	char* m_cpSetADCOpenTBPowerLow;
	/** ADC���ô�TB��Դ��λ��С*/
	int m_iSetADCOpenTBPowerHighSize;
	/** ADC���ô�TB��Դ��λ*/
	char* m_cpSetADCOpenTBPowerHigh;
	/** ADC���ô�TB���ص�λ��С*/
	int m_iSetADCOpenSwitchTBLowSize;
	/** ADC���ô�TB���ص�λ*/
	char* m_cpSetADCOpenSwitchTBLow;
	/** ADC���ô�TB���ظ�λ��С*/
	int m_iSetADCOpenSwitchTBHighSize;
	/** ADC���ô�TB���ظ�λ*/
	char* m_cpSetADCOpenSwitchTBHigh;
	/** ADC���ö��Ĵ�����С*/
	int m_iSetADCRegisterReadSize;
	/** ADC���ö��Ĵ���*/
	char* m_cpSetADCRegisterRead;
	/** ADC����д�Ĵ�����С*/
	int m_iSetADCRegisterWriteSize;
	/** ADC����д�Ĵ���*/
	char* m_cpSetADCRegisterWrite;
	/** ADC���ô�TB���ش�С*/
	int m_iSetADCTBSwitchOpenSize;
	/** ADC���ô�TB����*/
	char* m_cpSetADCTBSwitchOpen;
	/** ADC�������ô�С*/
	int m_iSetADCSampleSize;
	/** ADC��������*/
	char* m_cpSetADCSample;
	/** ADC��������������С*/
	int m_iSetADCReadContinuousSize;
	/** ADC������������*/
	char* m_cpSetADCReadContinuous;
	/** ����������*/
	int m_iSampleRate;
	/** ��ͨ�˲����Ƿ���*/
	bool m_bHPFOpen;
}m_oXMLADCSetupDataStruct;

/**
* @struct XMLParameterSetupData_Struct
* @brief ��XML�ļ��еõ��ķ���˲�����Ϣ
*/
typedef struct XMLParameterSetupData_Struct
{
	CTime m_oTimeFieldOff;
	/** �˿�ת��������ն˿�ƫ����*/
	unsigned short m_usNetRcvPortMove;
}m_oXMLParameterSetupDataStruct;
/** 
* @struct ServerSetupData_Struct
* @brief �ӷ������XML�ļ��н����õ�����Ϣ�ṹ��
*/
typedef struct ServerSetupData_Struct
{
	/** ��Դͬ������*/
	CRITICAL_SECTION m_oSecCommInfo;
	/** XMLDOM�ļ�����*/
	CXMLDOMDocument m_oXMLDOMDocument;
	/** Server��XML�����ļ�·��*/
	string m_strServerXMLFilePath;
	/** ��XML�ļ��н����õ�IP��ַ��������*/
	m_oXMLIPSetupDataStruct m_oXMLIPSetupData;
	/** ��XML�ļ��н����õ��˿���������*/
	m_oXMLPortSetupDataStruct m_oXMLPortSetupData;
	/** ��XML�ļ��н����õ�ADC����������Ϣ*/
	m_oXMLADCSetupDataStruct m_oXMLADCSetupData;
	/** ��XML�ļ��н����õ��ķ���˲�����Ϣ*/
	m_oXMLParameterSetupDataStruct m_oXMLParameterSetupData;
}m_oServerSetupDataStruct;
/**
* @struct InstrumentCommInfo_Struct
* @brief ��XML�ļ��н����õ�����Ϣ�ṹ��
*/
typedef struct InstrumentCommInfo_Struct
{
	/** �������Ϣ*/
	m_oServerSetupDataStruct* m_pServerSetupData;
	/** ���߿ͻ�����Ϣ*/
	m_oLineSetupDataStruct* m_pLineSetupData;
	/** ʩ���ͻ�����Ϣ*/
	m_oOptSetupDataStruct* m_pOptSetupData;
	/** Pcap������Ϣ*/
	m_oNetPcapSetupDataStruct* m_pPcapSetupData;
}m_oInstrumentCommInfoStruct;

/**
* @struct InstrumentCommand_Struct
* @brief ���豸ͨѶ���������ݽṹ��
*/
typedef struct InstrumentCommand_Struct
{
	/** LCI��IP��ַ*/
	unsigned int m_uiAimIP;
	/** LCI���յĶ˿ں�*/
	unsigned short m_usAimPort;
	/** Դ��ַ*/
	unsigned int m_uiSrcIP;
	/** Ŀ�ĵ�ַ*/
	unsigned int m_uiDstIP;
	/** Ӧ��˿�*/
	unsigned short m_usReturnPort;
	/** ���Ϊ1����������Ӧ��Ϊ2��ѯ����Ӧ��Ϊ3AD���������ط�*/
	unsigned short m_usCommand;
	/** SN����8λΪ�������ͣ�0x01Ϊ����վ��0x02Ϊ��Դվ��0x03Ϊ�ɼ�վ*/
	unsigned int m_uiSN;
	/** �װ�ʱ��*/
	unsigned int m_uiTimeHeadFrame;
	/** ����IP��ַ*/
	unsigned int m_uiInstrumentIP;
	/** ����ʱ��*/
	unsigned short m_usSysTimeNewLow;
	/** ����ʱ��*/
	unsigned int m_uiSysTimeNewHigh;
	/** ����ʱ��*/
	unsigned short m_usSysTimeOldLow;
	/** ����ʱ��*/
	unsigned int m_uiSysTimeOldHigh;
	/** ����ʱ��������λ*/
	unsigned int m_uiLocalTimeFixedHigh;
	/** ����ʱ��������λ*/
	unsigned int m_uiLocalTimeFixedLow;
	/** �Զ����ݷ��ص�ַ*/
	unsigned int m_uiADCDataReturnAddr;
	/** �Զ����ݷ��ض˿�*/
	unsigned short m_usADCDataReturnPort;
	/** �Զ����ݷ������ad_cmd(7)=1���˿ڵ�����=0���˿ڲ���*/
	unsigned short m_usADCDataReturnCmd;
	/** �����������λΪ1ʱ�����ض˿��Զ���1��������ʱ���ص��޶˿�*/
	/** �˿ڵ�������*/
	unsigned short m_usADCDataReturnPortLimitLow;
	/** �˿ڵ�������*/
	unsigned short m_usADCDataReturnPortLimitHigh;
	/** ��������ȴ��˿ڣ�ָ���ý�����λ���㲥����Ķ˿�*/
	unsigned int m_uiBroadCastPortSet;
	/** �������ݴ������*/
	char m_cFDUErrorCodeDataCount;
	/** ����������*/
	char m_cFDUErrorCodeCmdCount;
	/** ʱ�䱨��״̬*/
	char m_cTimeStatus;
	/** ����״̬*/
	char m_cCtrlStatus;
	/** TBʱ�̸�λ*/
	unsigned int m_uiTBHigh;
	/** TBʱ�̵�λ*/
	unsigned short m_usTBLow;
	/** TB���ƣ�0x05����TB��0x06��AD�ɼ�����TB��0x00ֹͣAD��ad_ctrl(2)=1��LED����*/
	unsigned short m_usTBCtrl;
	/** work_ctrl���ƽ���վ���պͷ�������ķ���*/
	/** �ɸߵ���λÿλ�ֱ���Ʒ��Ϳڽ�����A��B������A��B�����ն˽�����A��B������A��B*/
	/** =0Ϊ����=1Ϊ��*/
	char m_cLAUXRoutOpenQuery;
	/** ·�ɿ���*/
	/** �ɸ�λ����λ�ֱ���ƿ�������A����������B��������A��������B*/
	/** =0Ϊ����=1Ϊ��*/
	char m_cLAUXRoutOpenSet;
	/** Ӳ���豸����汾��*/
	unsigned int m_uiVersion;
	// @@@ʱ��48λ
// 	/** β������ʱ�̣���14λ��Ч*/
// 	unsigned short m_usTailRecTime;
// 	/** β������ʱ��/**����վβ������ʱ�̣���14λ��Ч*/
// 	unsigned short m_usTailSndTime;
// 	/** β������ʱ�̵�λ*/
// 	unsigned short m_usTailRecTimeLow;
	/** β������ʱ�̸�λ*/
	unsigned int m_uiTailRecTime;
// 	/** β������ʱ��/����վβ������ʱ�̵�λ*/
// 	unsigned short m_usTailSndTimeLow;
	/** β������ʱ��/����վβ������ʱ�̸�λ*/
	unsigned int m_uiTailSndTime;
	/** ��λ����ʱ��*/
	unsigned int m_uiLowTime;
	/** �㲥����ȴ��˿�ƥ�䣬������ڵ�һ��������λ�ã�����0x0a�����е�16λ�˿�ƥ����ܽ��չ㲥����*/
	unsigned int m_uiBroadCastPortSeted;
	/** ����ʱ��*/
	unsigned int m_uiNetTime;
	/** ����վ����Aβ������ʱ��*/
	unsigned short m_usLAUXTailRecTimeLineA;
	/** ����վ����Bβ������ʱ��*/
	unsigned short m_usLAUXTailRecTimeLineB;
	/** ����վ������Aβ������ʱ��*/
	unsigned short m_usLAUXTailRecTimeLAUXLineA;
	/** ����վ������Bβ������ʱ��*/
	unsigned short m_usLAUXTailRecTimeLAUXLineB;
	/** ����վ����A���ݹ���*/
	char m_cLAUXErrorCodeDataLineACount;
	/** ����վ����B���ݹ���*/
	char m_cLAUXErrorCodeDataLineBCount;
	/** ����վ������A���ݹ���*/
	char m_cLAUXErrorCodeDataLAUXLineACount;
	/** ����վ������B���ݹ���*/
	char m_cLAUXErrorCodeDataLAUXLineBCount;
	/** ����վ����ڹ���*/
	char m_cLAUXErrorCodeCmdCount;
	/** ����վ�Ϸ�·��IP*/
	unsigned int m_uiRoutIPTop;
	/** ����վ�·�·��IP*/
	unsigned int m_uiRoutIPDown;
	/** ����վ��·��IP*/
	unsigned int m_uiRoutIPLeft;
	/** ����վ�ҷ�·��IP*/
	unsigned int m_uiRoutIPRight;
	/** ·��IP��ַ*/
	unsigned int m_uiRoutIP;
	/** 0x18��������*/
	char* m_cpADCSet;
	/** 0x18�������ݸ���*/
	int m_iADCSetNum;
	/** ADC����ָ��ƫ����*/
	unsigned short m_usADCDataPoint;
	/** ADC���ݲɼ�ʱ��������ʱ���λ*/
	unsigned int m_uiADCSampleSysTimeHigh;
	/** ADC���ݲɼ�ʱ��������ʱ���λ*/
	unsigned short m_usADCSampleSysTimeLow;
	/** ADC�������ݻ�����ָ��*/
	char* m_pADCDataBuf;
}m_oInstrumentCommandStruct;

/**
* @struct HeartBeatFrame_Struct
* @brief ����֡�ṹ��
*/
typedef struct HeartBeatFrame_Struct
{
	/** ����֡��Դͬ������*/
	CRITICAL_SECTION m_oSecHeartBeat;
	/** ����֡������*/
	char* m_cpSndFrameData;
	/** ���������ּ���*/
	BYTE* m_pbyCommandWord;
	/** ���������ָ���*/
	unsigned short m_usCommandWordNum;
	/** ����֡����*/
	m_oInstrumentCommandStruct* m_pCommandStruct;
	/** ����Socket�׽���*/
	SOCKET m_oHeartBeatSocket;
	/** ���ն˿�ƫ����*/
	unsigned short m_usPortMove;
}m_oHeartBeatFrameStruct;

/**
* @struct HeadFrame_Struct
* @brief �װ�֡�ṹ��
*/
typedef struct HeadFrame_Struct
{
	/** �װ�֡��Դͬ������*/
	CRITICAL_SECTION m_oSecHeadFrame;
	/** ����˿ڽ��ջ�������С*/
	unsigned int m_uiRcvBufferSize;
	/** ����֡������*/
	char* m_cpRcvFrameData;
	/** �װ�֡����*/
	m_oInstrumentCommandStruct* m_pCommandStruct;
	/** �װ�Socket�׽���*/
	SOCKET m_oHeadFrameSocket;
	/** ���ն˿�ƫ����*/
	unsigned short m_usPortMove;
}m_oHeadFrameStruct;

/**
* @struct IPSetFrame_Struct
* @brief IP��ַ����֡�ṹ��
*/
typedef struct IPSetFrame_Struct
{
	/** IP��ַ����֡��Դͬ������*/
	CRITICAL_SECTION m_oSecIPSetFrame;
	/** ����˿ڷ��ͻ�������С*/
	unsigned int m_uiSndBufferSize;
	/** ����֡������*/
	char* m_cpSndFrameData;
	/** IP��ַ���������ּ���*/
	BYTE* m_pbyCommandWord;
	/** IP��ַ���������ָ���*/
	unsigned short m_usCommandWordNum;
	/** IP��ַ����֡����*/
	m_oInstrumentCommandStruct* m_pCommandStructSet;
	/** ����˿ڽ��ջ�������С*/
	unsigned int m_uiRcvBufferSize;
	/** ����֡������*/
	char* m_cpRcvFrameData;
	/** IP��ַ����Ӧ��֡����*/
	m_oInstrumentCommandStruct* m_pCommandStructReturn;
	/** IP��ַ����Socket�׽���*/
	SOCKET m_oIPSetFrameSocket;
	/** ���ն˿�ƫ����*/
	unsigned short m_usPortMove;
}m_oIPSetFrameStruct;

/**
* @struct TailFrame_Struct
* @brief β��֡�ṹ��
*/
typedef struct TailFrame_Struct
{
	/** β��֡��Դͬ������*/
	CRITICAL_SECTION m_oSecTailFrame;
	/** ����˿ڽ��ջ�������С*/
	unsigned int m_uiRcvBufferSize;
	/** ����֡������*/
	char* m_cpRcvFrameData;
	/** β��֡����*/
	m_oInstrumentCommandStruct* m_pCommandStruct;
	/** β��Socket�׽���*/
	SOCKET m_oTailFrameSocket;
	/** ���ն˿�ƫ����*/
	unsigned short m_usPortMove;
}m_oTailFrameStruct;

/**
* @struct TailTimeFrame_Struct
* @brief β��ʱ��֡�ṹ��
*/
typedef struct TailTimeFrame_Struct
{
	/** β��ʱ��֡��Դͬ������*/
	CRITICAL_SECTION m_oSecTailTimeFrame;
	/** ����˿ڽ��ջ�������С*/
	unsigned int m_uiRcvBufferSize;
	/** ����֡������*/
	char* m_cpRcvFrameData;
	/** β��ʱ��Ӧ��֡����*/
	m_oInstrumentCommandStruct* m_pCommandStructReturn;
	/** ����˿ڷ��ͻ�������С*/
	unsigned int m_uiSndBufferSize;
	/** ����֡������*/
	char* m_cpSndFrameData;
	/** β��ʱ�̲�ѯ�����ּ���*/
	BYTE* m_pbyCommandWord;
	/** β��ʱ�̲�ѯ�����ָ���*/
	unsigned short m_usCommandWordNum;
	/** β��ʱ�̷���֡����*/
	m_oInstrumentCommandStruct* m_pCommandStructSet;
	/** β��ʱ��Socket�׽���*/
	SOCKET m_oTailTimeFrameSocket;
	/** ���ն˿�ƫ����*/
	unsigned short m_usPortMove;
}m_oTailTimeFrameStruct;

/**
* @struct TimeDelayFrame_Struct
* @brief ʱͳ����֡�ṹ��
*/
typedef struct TimeDelayFrame_Struct
{
	/** ʱͳ����֡��Դͬ������*/
	CRITICAL_SECTION m_oSecTimeDelayFrame;
	/** ����˿ڽ��ջ�������С*/
	unsigned int m_uiRcvBufferSize;
	/** ����֡������*/
	char* m_cpRcvFrameData;
	/** ʱͳ����Ӧ��֡����*/
	m_oInstrumentCommandStruct* m_pCommandStructReturn;
	/** ����˿ڷ��ͻ�������С*/
	unsigned int m_uiSndBufferSize;
	/** ����֡������*/
	char* m_cpSndFrameData;
	/** ʱͳ���������ּ���*/
	BYTE* m_pbyCommandWord;
	/** ʱͳ���������ָ���*/
	unsigned short m_usCommandWordNum;
	/** ʱͳ���÷���֡����*/
	m_oInstrumentCommandStruct* m_pCommandStructSet;
	/** ʱͳ����Socket�׽���*/
	SOCKET m_oTimeDelayFrameSocket;
	/** ���ն˿�ƫ����*/
	unsigned short m_usPortMove;
}m_oTimeDelayFrameStruct;

/**
* @struct ADCSetFrame_Struct
* @brief ADC��������֡�ṹ��
*/
typedef struct ADCSetFrame_Struct
{
	/** ADC��������֡��Դͬ������*/
	CRITICAL_SECTION m_oSecADCSetFrame;
	/** ����˿ڽ��ջ�������С*/
	unsigned int m_uiRcvBufferSize;
	/** ����֡������*/
	char* m_cpRcvFrameData;
	/** ADC��������Ӧ��֡����*/
	m_oInstrumentCommandStruct* m_pCommandStructReturn;
	/** ����˿ڷ��ͻ�������С*/
	unsigned int m_uiSndBufferSize;
	/** ����֡������*/
	char* m_cpSndFrameData;
	/** ADC�������������ּ���*/
	BYTE* m_pbyCommandWord;
	/** ADC�������������ָ���*/
	unsigned short m_usCommandWordNum;
	/** ADC�������÷���֡����*/
	m_oInstrumentCommandStruct* m_pCommandStructSet;
	/** ADC��������Socket�׽���*/
	SOCKET m_oADCSetFrameSocket;
	/** ���ն˿�ƫ����*/
	unsigned short m_usPortMove;
}m_oADCSetFrameStruct;

/**
* @struct ErrorCodeFrame_Struct
* @brief �����ѯ֡�ṹ��
*/
typedef struct ErrorCodeFrame_Struct
{
	/** ADC��������֡��Դͬ������*/
	CRITICAL_SECTION m_oSecErrorCodeFrame;
	/** ����˿ڽ��ջ�������С*/
	unsigned int m_uiRcvBufferSize;
	/** ����֡������*/
	char* m_cpRcvFrameData;
	/** Ӧ��֡����*/
	m_oInstrumentCommandStruct* m_pCommandStructReturn;
	/** ����˿ڷ��ͻ�������С*/
	unsigned int m_uiSndBufferSize;
	/** ����֡������*/
	char* m_cpSndFrameData;
	/** �����ѯ�����ּ���*/
	BYTE* m_pbyCommandWord;
	/** �����ѯ�����ָ���*/
	unsigned short m_usCommandWordNum;
	/** ����֡����*/
	m_oInstrumentCommandStruct* m_pCommandStructSet;
	/** �����ѯSocket�׽���*/
	SOCKET m_oErrorCodeFrameSocket;
	/** ���ն˿�ƫ����*/
	unsigned short m_usPortMove;
}m_oErrorCodeFrameStruct;

/**
* @struct ADCDataFrame_Struct
* @brief ADC���ݽ���֡�ṹ��
*/
typedef struct ADCDataFrame_Struct
{
	/** ADC���ݽ���֡��Դͬ������*/
	CRITICAL_SECTION m_oSecADCDataFrame;
	/** ����˿ڽ��ջ�������С*/
	unsigned int m_uiRcvBufferSize;
	/** ����֡������*/
	char* m_cpRcvFrameData;
	/** Ӧ��֡����*/
	m_oInstrumentCommandStruct* m_pCommandStructReturn;
	/** ����˿ڷ��ͻ�������С*/
	unsigned int m_uiSndBufferSize;
	/** ����֡������*/
	char* m_cpSndFrameData;
	/** ����֡����*/
	m_oInstrumentCommandStruct* m_pCommandStructSet;
	/** ADC���ݽ��պ��ط�Socket�׽���*/
	SOCKET m_oADCDataFrameSocket;
	/** ���ն˿�ƫ����*/
	unsigned short m_usPortMove;
}m_oADCDataFrameStruct;

/**
* @struct Instrument_Struct
* @brief �������Խṹ��
*/
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
	/** ��������汾��*/
	unsigned int m_uiVersion;
	/** β������*/
	int m_iTailFrameCount;
	/** ����ʱ��*/
	unsigned int m_uiDelayTime;
	// @@@ʱ��48λ
// 	/** ��������ϵͳʱ��*/
// 	unsigned int m_uiSystemTime;
// 	/** ��������ʱ��*/
// 	unsigned int m_uiNetTime;
	/** ��������״̬*/
	unsigned int m_uiNetState;
	/** ������������1*/
	unsigned int m_uiNetOrder;
// 	/** 16bitsʱ�䣬����ʱ�̵�λ*/
// 	unsigned short m_usReceiveTime;	
// 	/** 16bitsʱ�䣬����ʱ�̵�λ*/
// 	unsigned short m_usSendTime;
// 	/** 16bitsʱ�䣬����ʱ�̵�λ*/
// 	unsigned short m_usReceiveTimeLow;
	/** 32bitsʱ�䣬����ʱ�̸�λ*/
	unsigned int m_uiReceiveTime;
// 	/** 16bitsʱ�䣬����ʱ�̵�λ*/
// 	unsigned short m_usSendTimeLow;
	/** 32bitsʱ�䣬����ʱ�̸�λ*/
	unsigned int m_uiSendTime;
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
	/** �װ�λ���ȶ�����*/
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
	/** ADC���������Ƿ�Ӧ��*/
	bool m_bADCSetReturn;
	/** �����Ƿ������ADC��������*/
	bool m_bADCSet;
	/** ������ʼADC���ݲɼ����óɹ�*/
	bool m_bADCStartSample;
	/** ����ֹͣADC���ݲɼ����óɹ�*/
	bool m_bADCStopSample;
	/** �����ѯ����֡��*/
	unsigned int m_uiErrorCodeQueryNum;
	/** �����ѯӦ��֡��*/
	unsigned int m_uiErrorCodeReturnNum;
	/** �ɼ�վ�͵�Դվ�������ݴ������*/
	int m_iFDUErrorCodeDataCount;
	/** �ɼ�վ�͵�Դվ����������*/
	int m_iFDUErrorCodeCmdCount;
	/** �ɼ�վ�͵�Դվ�������ݴ������*/
	char m_cFDUErrorCodeDataCountOld;
	/** �ɼ�վ�͵�Դվ����������*/
	char m_cFDUErrorCodeCmdCountOld;

	/** ����վ����A���ݹ���*/
	int m_iLAUXErrorCodeDataLineACount;
	/** ����վ����B���ݹ���*/
	int m_iLAUXErrorCodeDataLineBCount;
	/** ����վ������A���ݹ���*/
	int m_iLAUXErrorCodeDataLAUXLineACount;
	/** ����վ������B���ݹ���*/
	int m_iLAUXErrorCodeDataLAUXLineBCount;
	/** ����վ����ڹ���*/
	int m_iLAUXErrorCodeCmdCount;

	/** ����վ����A���ݹ���*/
	char m_cLAUXErrorCodeDataLineACountOld;
	/** ����վ����B���ݹ���*/
	char m_cLAUXErrorCodeDataLineBCountOld;
	/** ����վ������A���ݹ���*/
	char m_cLAUXErrorCodeDataLAUXLineACountOld;
	/** ����վ������B���ݹ���*/
	char m_cLAUXErrorCodeDataLAUXLineBCountOld;
	/** ����վ����ڹ���*/
	char m_cLAUXErrorCodeCmdCountOld;

	/** ʵ�ʽ���ADC����֡�������ط�֡��*/
	unsigned int m_uiADCDataActualRecFrameNum;
	/** �ط���ѯ֡�õ���Ӧ��֡��*/
	unsigned int m_uiADCDataRetransmissionFrameNum;
	/** Ӧ�ý���ADC����֡��������֡��*/
	unsigned int m_uiADCDataShouldRecFrameNum;
	/** ADC�������ݣ�ȡÿ֡�ĵ�һ���������ڼ��㣩*/
	list<int> m_olsADCDataSave;
	/** ADC����֡��ָ��ƫ����*/
	unsigned short m_usADCDataFramePointNow;
	/** ADC����֡����ʱ�ı���ʱ��*/
	unsigned int m_uiADCDataFrameSysTimeNow;
	/** ADC����֡��ָ��ƫ����*/
	unsigned short m_usADCDataFramePointOld;
	/** ADC����֡����ʱ�ı���ʱ��*/
	unsigned int m_uiADCDataFrameSysTimeOld;
	/** ������ʼ������TBʱ�̸�λ*/
	unsigned int m_uiTBHigh;
	/** ����Ƿ������û���յ�ADC����֡*/
	bool m_bCheckADCFrameLate;
	/** �������ʱ��*/
	unsigned int m_uiActiveTime;
	/** ����ϵͳʱ���λ*/
	unsigned int m_uiSysTimeHigh;
	/** ����ϵͳʱ���λ*/
	unsigned short m_usSysTimeLow;
}m_oInstrumentStruct;

/**
* @struct InstrumentLocation_Struct
* @brief ����λ�õ�ṹ��
*/
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
	/** �ߺ�*/
	int m_iLineIndex;
	/** ���*/
	int m_iPointIndex;
}m_oInstrumentLocationStruct;

/**
* @struct ADCLostFrameKey_Struct
* @brief ��ʧ֡IP��ַ��ƫ�����ṹ��
*/
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
	/** ��֡��ָ��ƫ����*/
	unsigned short m_usADCFramePointNb;
	/** ��֡��IP��ַ*/
	unsigned int m_uiIP;
}m_oADCLostFrameKeyStruct;

/**
* @struct ADCLostFrame_Struct
* @brief ��ʧ֡�ṹ��
*/
typedef struct ADCLostFrame_Struct
{
	/** ��ʧ֡�ط�����*/
	unsigned int m_uiCount;
// 	/** ��֡���ļ��ڵ�֡��ţ���0��ʼ*/
// 	unsigned int m_uiFrameNb;
	/** ��ʧ֡�ı���ʱ��*/
	unsigned int m_uiSysTime;
	/** �Ƿ��Ѿ��յ�Ӧ��*/
	bool m_bReturnOk;
}m_oADCLostFrameStruct;

/**
* @struct InstrumentList_Struct
* @brief �������нṹ��
*/
typedef struct InstrumentList_Struct
{
	/** ��������ָ��*/
	m_oInstrumentStruct* m_pArrayInstrument;
	/** ������������*/
	list<m_oInstrumentStruct*> m_olsInstrumentFree;
	/** ����IP��ַ����������*/
	hash_map<unsigned int, m_oInstrumentStruct*> m_oIPSetInstrumentMap;
	/** ����SN������*/
	hash_map<unsigned int, m_oInstrumentStruct*> m_oSNInstrumentMap;
	/** ����IP��ַ������*/
	hash_map<unsigned int, m_oInstrumentStruct*> m_oIPInstrumentMap;
	/** δ���ADC�������õ���������*/
	hash_map<unsigned int, m_oInstrumentStruct*> m_oADCSetInstrumentMap;
	/** ����λ��������*/
	map<m_oInstrumentLocationStruct, m_oInstrumentStruct*> m_oInstrumentLocationMap;
	/** ����ʩ���ɼ�������������*/
	// @@@��δʹ��
	hash_map<unsigned int, m_oInstrumentStruct*> m_oOptInstrumentMap;
	/** ������֡������*/
	map<m_oADCLostFrameKeyStruct, m_oADCLostFrameStruct> m_oADCLostFrameMap;
	/** ��������*/
	unsigned int m_uiCountAll;
	/** ������������*/
	unsigned int m_uiCountFree;
	/** �Ƿ���·��IP�ֶ�����ADC����*/
	bool m_bSetByHand;
}m_oInstrumentListStruct;

/**
* @struct Rout_Struct
* @brief ·�����Խṹ��
*/
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
	/** ·���Ƿ�Ϊ������·��*/
	bool m_bRoutLaux;
	/** ·���Ƿ���յ�ADC���ò���Ӧ��*/
	bool m_bADCSetReturn;
	/** ·���Ƿ���ADC��������֡*/
	bool m_bADCSetRout;
	/** ��·�ɷ����������ĸ���*/
	unsigned int m_uiInstrumentNum;
}m_oRoutStruct;

/**
* @struct RoutList_Struct
* @brief ·�ɶ��нṹ��
*/
typedef struct RoutList_Struct
{
	/** ·������ָ��*/
	m_oRoutStruct* m_pArrayRout;
	/** ����·�ɶ���*/
	list<m_oRoutStruct*> m_olsRoutFree;
	/** ����·�ɵ�ַ������*/
	hash_map<unsigned int, m_oRoutStruct*> m_oRoutMap;
	/** ��Ҫɾ��·��������·��������*/
	hash_map<unsigned int, m_oRoutStruct*> m_oRoutDeleteMap;
// 	/** ����ʱͳ��������У���ԱΪ·��IP*/
// 	list<unsigned int> m_olsTimeDelayTaskQueue;
// 	/** ����ʱͳ��������ת����*/
// 	list<unsigned int> m_olsTimeDelayTemp;
	/** ADC����������������*/
	hash_map<unsigned int, m_oRoutStruct*> m_oADCSetRoutMap;
	/** ·������*/
	unsigned int m_uiCountAll;
	/** ����·������*/
	unsigned int m_uiCountFree;
}m_oRoutListStruct;

/**
* @struct LineList_Struct
* @brief ���߶��нṹ��
*/
typedef struct LineList_Struct
{
	/** ���߶�����Դͬ������*/
	CRITICAL_SECTION m_oSecLineList;
	/** �������нṹ��ָ��*/
	m_oInstrumentListStruct* m_pInstrumentList;
	/** ·�ɶ��нṹ��*/
	m_oRoutListStruct* m_pRoutList;
	/** ����״̬�ɲ��ȶ���Ϊ�ȶ�*/
	bool m_bLineStableChange;
	/** ����ϵͳ�����仯��ʱ��*/
	unsigned int m_uiLineChangeTime;
	/** TBʱ���λ*/
	unsigned int m_uiTBHigh;
	/** LCI�ı���ϵͳʱ��*/
	unsigned int m_uiLocalSysTime;
}m_oLineListStruct;

/**
* @struct OptInstrument_Struct
* @brief ����ʩ���������ṹ��
*/
typedef struct OptInstrument_Struct
{
	/** ��������IP*/
	unsigned int m_uiIP;
	/** ����ߺ�*/
	int m_iLineIndex;
	/** ��ǵ��*/
	int m_iPointIndex;
	/** �ɼ�վ�����Ƿ�����������*/
	bool m_bAuxiliary;
	/** �����洢��SEGD��λ�ú�*/
	unsigned int m_uiLocation;
}m_oOptInstrumentStruct;

/**
* @struct OptTask_Struct
* @brief ʩ������ṹ��
*/
typedef struct OptTask_Struct
{
	/** �����Ƿ�ʹ����*/
	bool m_bInUsed;
	/** ʩ���ں�*/
	unsigned int m_uiOptNo;
	/** ʩ������ʼ��¼��ʱ��*/
	unsigned int m_uiTB;
	/** ʩ������ֹͣ��¼��ʱ��*/
	unsigned int m_uiTS;
	/** ������*/
	int m_iSampleRate;
// 	/** �洢һ֡����ʱ��*/
// 	unsigned int m_uiOneFrameTime;
	/** ʩ����������ļ�ָ��*/
	FILE* m_pFile;
// 	/** ʩ���������ǰһ���ļ����ļ�ָ��*/
// 	FILE* m_pPreviousFile;
// 	/** ���µ��ļ��洢���*/
// 	unsigned int m_uiFileSaveNb;
	/** ʩ�����ݴ洢�ļ�·��*/
	string m_SaveFilePath;
	/** ʩ�������������ؼ���ΪIP������Ϊ����ʩ���������ṹ��*/
	hash_map<unsigned int, m_oOptInstrumentStruct*> m_oIPMap;
	/** ����洢��Ԫ��־λ*/
	bool m_bSaveBuf;
	/** ����洢��Ԫ���*/
	unsigned int m_uiSaveBufNo;
// 	/** ����ʩ������������*/
// 	list<m_oOptInstrumentStruct> m_olsOptInstrument;
}m_oOptTaskStruct;

/**
* @struct OptTaskArray_Struct
* @brief ʩ������ṹ������
*/
typedef struct OptTaskArray_Struct
{
	/** ��Դͬ������*/
	CRITICAL_SECTION m_oSecOptTaskArray;
	/** ʩ����������ָ��*/
	m_oOptTaskStruct* m_pArrayOptTask;
	/** ���е�ʩ���������*/
	list<m_oOptTaskStruct*> m_olsOptTaskFree;
	/** ���ڽ��е�ʩ����������*/
	hash_map<unsigned int, m_oOptTaskStruct*> m_oOptTaskWorkMap;
	/** ʩ����������*/
	unsigned int m_uiCountAll;
	/** ������������*/
	unsigned int m_uiCountFree;
	/** ʩ���������ݴ洢�ļ��м���*/
	unsigned int m_uiOptTaskNb;
	/** ʩ�����ݴ洢�ļ���·��*/
	string m_SaveFolderPath;
}m_oOptTaskArrayStruct;
/**
* @struct ADCDataBuf_Struct
* @brief ���ݴ洢�������ṹ��
*/
typedef struct ADCDataBuf_Struct
{
	/** �������Ƿ�ʹ����*/
	bool m_bInUsed;
	/** ADC���ݴ洢������*/
	char* m_pADCDataBuf;
	/** ����������*/
	unsigned int m_uiBufLength;
	/** ÿ��վ�洢�����ݵ���*/
	unsigned int m_uiSavePointNum;
	/** ����ʱ��*/
	unsigned int m_uiSampleTime;
	/** �ж��Ƿ�д��SEGD�ļ���־λ*/
	bool m_bSaveInSegd;
	/** ����ʩ���Ĳɼ�վ����*/
	unsigned int m_uiAcqTraceNum;
	/** ��������Ŀ*/
	unsigned int m_uiAuxTraceNum;
	/** ʩ���ں�*/
	unsigned int m_uiOptNo;
	/** ʩ�����ݴ洢�ļ�·��*/
	string m_SaveFilePath;
	/** ������*/
	int m_iSampleRate;
	// 	/** ÿ���ɼ�վ���ݴ洢֡��*/
	// 	unsigned int m_uiFrameNb;
	// 	/** SEGDЭ��ͷ����*/
	// 	unsigned int m_uiSEGDHeaderLen;
	// 	/** �ɼ�վ����ͷ����*/
	// 	unsigned int m_uiDataHeaderLen;
	/** ʩ������������ָ�룬�ؼ���ΪIP������Ϊ����ʩ����Segd����ͷ�ṹ��*/
	list<m_oSegdDataHeaderStruct*> m_olsSegdDataHeader;
	/** ���������*/
	unsigned int m_uiIndex;
}m_oADCDataBufStruct;

/**
* @struct ADCDataBufArray_Struct
* @brief ���ݴ洢�������ṹ��
*/
typedef struct ADCDataBufArray_Struct
{
	/** ��������Դͬ������*/
	CRITICAL_SECTION m_oSecADCDataBufArray;
	/** ����������ָ��*/
	m_oADCDataBufStruct* m_pArrayADCDataBuf;
	/** ����������*/
	list<m_oADCDataBufStruct*> m_olsADCDataBufFree;
	/** д���ļ������ݻ���������*/
	hash_map<unsigned int, m_oADCDataBufStruct*> m_oADCDataBufWorkMap;
	/** ����������*/
	unsigned int m_uiCountAll;
	/** ���л���������*/
	unsigned int m_uiCountFree;
}m_oADCDataBufArrayStruct;

/**
* @struct Thread_Struct
* @brief �߳̽ṹ��
*/
typedef struct Thread_Struct
{
	/** �߳̾��*/
	HANDLE m_hThread;
	/** �̺߳�*/
	DWORD m_dwThreadID;
	/**�Ƿ���״̬*/
	bool m_bWork;
	/** �Ƿ�ر��߳�*/
	bool m_bClose;
	/** �߳̽����¼�*/
	HANDLE m_hThreadClose;
	/** ����ָ��*/
	m_oConstVarStruct* m_pConstVar;
	/** �����־ָ��*/
	m_oLogOutPutStruct* m_pLogOutPut;
}m_oThreadStruct;

/**
* @struct LogOutPutThread_Struct
* @brief ��־����߳̽ṹ��
*/
typedef struct LogOutPutThread_Struct
{
	/** ��Դͬ������*/
	CRITICAL_SECTION m_oSecLogOutPutThread;
	/** �߳̽ṹ��ָ��*/
	m_oThreadStruct* m_pThread;
	/** �����־ָ��*/
	m_oLogOutPutStruct* m_pLogOutPutTimeDelay;
	/** �����־ָ��*/
	m_oLogOutPutStruct* m_pLogOutPutErrorCode;
	/** �����־ָ��*/
	m_oLogOutPutStruct* m_pLogOutPutADCFrameTime;
}m_oLogOutPutThreadStruct;

/**
* @struct HeartBeatThread_Struct
* @brief �����߳̽ṹ��
*/
typedef struct HeartBeatThread_Struct
{
	/** ��Դͬ������*/
	CRITICAL_SECTION m_oSecHeartBeatThread;
	/** �߳̽ṹ��ָ��*/
	m_oThreadStruct* m_pThread;
	/** ����ָ֡��*/
	m_oHeartBeatFrameStruct* m_pHeartBeatFrame;
}m_oHeartBeatThreadStruct;

/**
* @struct HeadFrameThread_Struct
* @brief �װ��߳̽ṹ��
*/
typedef struct HeadFrameThread_Struct
{
	/** ��Դͬ������*/
	CRITICAL_SECTION m_oSecHeadFrameThread;
	/** �߳̽ṹ��ָ��*/
	m_oThreadStruct* m_pThread;
	/** �װ�ָ֡��*/
	m_oHeadFrameStruct* m_pHeadFrame;
	/** ���߶��нṹ��ָ��*/
	m_oLineListStruct* m_pLineList;
	/** �װ�����*/
	unsigned int m_uiHeadFrameCount;
}m_oHeadFrameThreadStruct;

/**
* @struct IPSetFrameThread_Struct
* @brief IP��ַ�����߳̽ṹ��
*/
typedef struct IPSetFrameThread_Struct
{
	/** ��Դͬ������*/
	CRITICAL_SECTION m_oSecIPSetFrameThread;
	/** �߳̽ṹ��ָ��*/
	m_oThreadStruct* m_pThread;
	/** IP��ַ����ָ֡��*/
	m_oIPSetFrameStruct* m_pIPSetFrame;
	/** ���߶��нṹ��ָ��*/
	m_oLineListStruct* m_pLineList;
}m_oIPSetFrameThreadStruct;

/**
* @struct TimeDelayThread_Struct
* @brief ʱͳ�߳̽ṹ��
*/
typedef struct TimeDelayThread_Struct
{
	/** ��Դͬ������*/
	CRITICAL_SECTION m_oSecTimeDelayThread;
	/** �߳̽ṹ��ָ��*/
	m_oThreadStruct* m_pThread;
	/** β��ʱ��ָ֡��*/
	m_oTailTimeFrameStruct* m_pTailTimeFrame;
	/** ʱͳ����ָ֡��*/
	m_oTimeDelayFrameStruct* m_pTimeDelayFrame;
	/** ���߶��нṹ��ָ��*/
	m_oLineListStruct* m_pLineList;
	/** ADC��ʼ���ݲɼ���־λ*/
	bool m_bADCStartSample;
	/** ������*/
//	unsigned int m_uiCounter;
	/** �����־ָ��*/
	m_oLogOutPutStruct* m_pLogOutPutTimeDelay;
}m_oTimeDelayThreadStruct;

/**
* @struct TailFrameThread_Struct
* @brief β���߳̽ṹ��
*/
typedef struct TailFrameThread_Struct
{
	/** ��Դͬ������*/
	CRITICAL_SECTION m_oSecTailFrameThread;
	/** �߳̽ṹ��ָ��*/
	m_oThreadStruct* m_pThread;
	/** β��ָ֡��*/
	m_oTailFrameStruct* m_pTailFrame;
	/** �������нṹ��ָ��*/
	m_oLineListStruct* m_pLineList;
	/** β������*/
	unsigned int m_uiTailFrameCount;
	/** ʱͳ�߳�ָ��*/
	m_oTimeDelayThreadStruct* m_pTimeDelayThread;
}m_oTailFrameThreadStruct;
/**
* @struct ADCSetThread_Struct
* @brief ADC���������߳̽ṹ��
*/
typedef struct ADCSetThread_Struct
{
	/** ��Դͬ������*/
	CRITICAL_SECTION m_oSecADCSetThread;
	/** �߳̽ṹ��ָ��*/
	m_oThreadStruct* m_pThread;
	/** ADC��������ָ֡��*/
	m_oADCSetFrameStruct* m_pADCSetFrame;
	/** ���߶��нṹ��ָ��*/
	m_oLineListStruct* m_pLineList;
	/** ADC�����������*/
	int m_iADCSetOperationNb;
	/** ������*/
	unsigned int m_uiCounter;
	/** ADC��ʼ���ݲɼ���־λ*/
	bool m_bADCStartSample;
	/** ADCֹͣ���ݲɼ���־λ*/
	bool m_bADCStopSample;
// 	/** ��һ�ο�ʼ�����Ĳ���ʱ��*/
// 	unsigned int m_uiLocalSysTimeOld;
	/** ��XML�ļ��н����õ�����Ϣ*/
	m_oInstrumentCommInfoStruct* m_pCommInfo;
	/** �����־ָ��*/
	m_oLogOutPutStruct* m_pLogOutPutADCFrameTime;
}m_oADCSetThreadStruct;

/**
* @struct ErrorCodeThread_Struct
* @brief �����ѯ�߳̽ṹ��
*/
typedef struct ErrorCodeThread_Struct
{
	/** ��Դͬ������*/
	CRITICAL_SECTION m_oSecErrorCodeThread;
	/** �߳̽ṹ��ָ��*/
	m_oThreadStruct* m_pThread;
	/** �����ѯָ֡��*/
	m_oErrorCodeFrameStruct* m_pErrorCodeFrame;
	/** ���߶��нṹ��ָ��*/
	m_oLineListStruct* m_pLineList;
	/** �����ѯ��־ָ��*/
	m_oLogOutPutStruct* m_pLogOutPutErrorCode;
}m_oErrorCodeThreadStruct;

/**
* @struct MonitorThread_Struct
* @brief ·�ɼ����߳̽ṹ��
*/
typedef struct MonitorThread_Struct
{
	/** ��Դͬ������*/
	CRITICAL_SECTION m_oSecMonitorThread;
	/** �߳̽ṹ��ָ��*/
	m_oThreadStruct* m_pThread;
	/** ���߶��нṹ��ָ��*/
	m_oLineListStruct* m_pLineList;
	/** ʱͳ�߳�ָ��*/
	m_oTimeDelayThreadStruct* m_pTimeDelayThread;
	/** ADC���������߳�*/
	m_oADCSetThreadStruct* m_pADCSetThread;
	/** �����ѯ�߳�*/
	m_oErrorCodeThreadStruct* m_pErrorCodeThread;
	/** IP��ַ����֡�ṹ*/
	m_oIPSetFrameStruct* m_pIPSetFrame;
}m_oMonitorThreadStruct;

/**
* @struct ADCDataRecThread_Struct
* @brief ADC���ݽ����߳̽ṹ��
*/
typedef struct ADCDataRecThread_Struct
{
	/** ��Դͬ������*/
	CRITICAL_SECTION m_oSecADCDataRecThread;
	/** �߳̽ṹ��ָ��*/
	m_oThreadStruct* m_pThread;
	/** �����ѯָ֡��*/
	m_oADCDataFrameStruct* m_pADCDataFrame;
	/** ���߶��нṹ��ָ��*/
	m_oLineListStruct* m_pLineList;
	/** �����ѯ��־ָ��*/
	m_oLogOutPutStruct* m_pLogOutPutADCFrameTime;
	/** ���ݴ洢����������ṹ��ָ��*/
	m_oADCDataBufArrayStruct* m_pADCDataBufArray;
	/** ʩ����������ṹ��ָ��*/
	m_oOptTaskArrayStruct* m_pOptTaskArray;
	/** ����������*/
	int m_iADCSampleRate;
//	/** ��һ֡�ı���ʱ��*/
//	unsigned int m_uiADCDataFrameSysTime;
//	/** ���ļ�����֡������*/
//	int m_iADCFrameCount;
// 	/** �������ݻص�����*/
// 	ProSampleDateCallBack m_oProSampleDataCallBack;
}m_oADCDataRecThreadStruct;

/**
* @struct ADCDataSaveThread_Struct
* @brief ʩ���������ݴ洢�߳̽ṹ��
*/
typedef struct ADCDataSaveThread_Struct
{
	/** ��Դͬ������*/
	CRITICAL_SECTION m_oSecADCDataSaveThread;
	/** �߳̽ṹ��ָ��*/
	m_oThreadStruct* m_pThread;
	/** ���ݴ洢�������ṹ��ָ��*/
	m_oADCDataBufArrayStruct* m_pADCDataBufArray;
}m_oADCDataSaveThreadStruct;
/**
* @struct Environment_Struct
* @brief ��Դ�����ṹ��
*/
typedef struct Environment_Struct
{
	/** ��INI�ļ��õ��ĳ�����Ϣ*/
	m_oConstVarStruct* m_pConstVar;
	/** ��XML�ļ��õ���������ͨѶ��Ϣ�ṹ*/
	m_oInstrumentCommInfoStruct* m_pInstrumentCommInfo;
	/** ����֡�ṹ*/
	m_oHeartBeatFrameStruct* m_pHeartBeatFrame;
	/** �װ�֡�ṹ*/
	m_oHeadFrameStruct* m_pHeadFrame;
	/** IP��ַ����֡�ṹ*/
	m_oIPSetFrameStruct* m_pIPSetFrame;
	/** β��֡�ṹ*/
	m_oTailFrameStruct* m_pTailFrame;
	/** β��ʱ��֡�ṹ*/
	m_oTailTimeFrameStruct* m_pTailTimeFrame;
	/** ʱͳ����֡�ṹ*/
	m_oTimeDelayFrameStruct* m_pTimeDelayFrame;
	/** ADC��������֡�ṹ*/
	m_oADCSetFrameStruct* m_pADCSetFrame;
	/** �����ѯ֡�ṹ*/
	m_oErrorCodeFrameStruct* m_pErrorCodeFrame;
	/** ADC����֡�ṹ*/
	m_oADCDataFrameStruct* m_pADCDataFrame;
	/** ������־����ṹ*/
	m_oLogOutPutStruct* m_pLogOutPutOpt;
	/** ʱͳ��־����ṹ*/
	m_oLogOutPutStruct* m_pLogOutPutTimeDelay;
	/** �����ѯ��־����ṹ*/
	m_oLogOutPutStruct* m_pLogOutPutErrorCode;
	/** ֡ʱ���ƫ������־����ṹ*/
	m_oLogOutPutStruct* m_pLogOutPutADCFrameTime;
	/** ���߶��нṹ��*/
	m_oLineListStruct* m_pLineList;
	/** ���ݴ洢�������ṹ��ָ��*/
	m_oADCDataBufArrayStruct* m_pADCDataBufArray;
	/** ʩ����������ṹ��ָ��*/
	m_oOptTaskArrayStruct* m_pOptTaskArray;

	/** ��־����߳�*/
	m_oLogOutPutThreadStruct* m_pLogOutPutThread;
	/** �����߳�*/
	m_oHeartBeatThreadStruct* m_pHeartBeatThread;
	/** �װ������߳�*/
	m_oHeadFrameThreadStruct* m_pHeadFrameThread;
	/** IP��ַ�����߳�*/
	m_oIPSetFrameThreadStruct* m_pIPSetFrameThread;
	/** β�������߳�*/
	m_oTailFrameThreadStruct* m_pTailFrameThread;
	/** ·�ɼ����߳�*/
	m_oMonitorThreadStruct* m_pMonitorThread;
	/** ʱͳ�߳�*/
	m_oTimeDelayThreadStruct* m_pTimeDelayThread;
	/** ADC���������߳�*/
	m_oADCSetThreadStruct* m_pADCSetThread;
	/** �����ѯ�߳�*/
	m_oErrorCodeThreadStruct* m_pErrorCodeThread;
	/** ADC���ݽ����߳�*/
	m_oADCDataRecThreadStruct* m_pADCDataRecThread;
	/** ʩ���������ݴ洢�߳�*/
	m_oADCDataSaveThreadStruct* m_pADCDataSaveThread;
	/** Field On*/
	bool m_bFieldOn;
	/** Field Off*/
	bool m_bFieldOff;
	/** Netd����Ľ�����Ϣ*/
	PROCESS_INFORMATION m_piNetd;
}m_oEnvironmentStruct;

/** functions declarations*/
/************************************************************************/
/* ���ܺ���                                                             */
/************************************************************************/
/**
* @fn void OnInitSocketLib(void)
* @detail ��ʼ���׽��ֿ�
*/
MatrixServerDll_API	void OnInitSocketLib(void);
/**
* @fn void OnCloseSocketLib(void)
* @detail �ͷ��׽��ֿ�
*/
MatrixServerDll_API	void OnCloseSocketLib(void);
// �õ�֡��֡����
MatrixServerDll_API void GetFrameInfo(char* pFrameData, int iSize, string* strFrameData);
// ��CStringת��Ϊchar����
MatrixServerDll_API void ParseCStringToArray(char** pData, int iSize, CString str);
// �ж��ļ��Ƿ����
MatrixServerDll_API bool IfFileExist(CString str);
// У��֡��ͬ����
MatrixServerDll_API bool CheckInstrFrameHead(char* pFrameData, char* pFrameHeadCheck, int iCheckSize);
// ����֡��ͬ����
MatrixServerDll_API bool MakeInstrFrameHead(char* pFrameData, char* pFrameHeadCheck, int iCheckSize);
// ����֡���ݽ�������
MatrixServerDll_API bool ResetInstrFramePacket(m_oInstrumentCommandStruct* pCommand);
// �������豸ͨѶ����֡����
MatrixServerDll_API bool ParseInstrFrame(m_oInstrumentCommandStruct* pCommand, 
	char* pFrameData, m_oConstVarStruct* pConstVar, m_oLogOutPutStruct* pLogOutPut);
// �������豸ͨѶ֡
MatrixServerDll_API bool MakeInstrFrame(m_oInstrumentCommandStruct* pCommand, 
	m_oConstVarStruct* pConstVar, char* pFrameData, BYTE* pCommandWord = NULL, 
	unsigned short usCommandWordNum = 0);
// ����CSocket���ն˿ڲ��󶨶˿ں�IP��ַ
MatrixServerDll_API SOCKET CreateInstrSocket(unsigned short usPort, 
	unsigned int uiIP, m_oLogOutPutStruct* pLogOutPut = NULL);
// ���ù㲥ģʽ
MatrixServerDll_API void SetInstrSocketBroadCast(SOCKET oSocket, 
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
// �ر�Socket�׽���
MatrixServerDll_API void OnCloseSocket(SOCKET oSocket);
// ��ս��ջ�����
MatrixServerDll_API void OnClearSocketRcvBuf(SOCKET oSocket, int iRcvFrameSize);
// �õ�·�ɷ�������������
MatrixServerDll_API bool OnGetRoutInstrNum(int iLineIndex, int iPointIndex, int iDirection, 
	m_oEnvironmentStruct* pEnv, unsigned int& uiInstrumentNum);
// ����������ݵ�����������
MatrixServerDll_API double CalMeanSquare(m_oInstrumentStruct* pInstrument);

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
MatrixServerDll_API bool LoadIniFile(m_oConstVarStruct* pConstVar);
// ��ʼ��������Ϣ�ṹ��
MatrixServerDll_API bool OnInitConstVar(m_oConstVarStruct* pConstVar);
// �رճ�����Ϣ�ṹ��
MatrixServerDll_API void OnCloseConstVar(m_oConstVarStruct* pConstVar);
// �ͷų�����Ϣ�ṹ��
MatrixServerDll_API void OnFreeConstVar(m_oConstVarStruct* pConstVar);

/************************************************************************/
/* xml����                                                              */
/************************************************************************/
// ��������ͨѶ��Ϣ�ṹ��
MatrixServerDll_API m_oInstrumentCommInfoStruct* OnCreateInstrumentCommInfo(void);
// ��ʼ������ͨѶ��Ϣ�ṹ��
MatrixServerDll_API void OnInitInstrumentCommInfo(m_oInstrumentCommInfoStruct* pCommInfo);
// �ͷ�����ͨѶ��Ϣ�ṹ��
MatrixServerDll_API void OnFreeInstrumentCommInfo(m_oInstrumentCommInfoStruct* pCommInfo);

// ��ʼ�����߿ͻ�����������Ϣ
MatrixServerDll_API void OnInitLineClientXMLSetupData(m_oLineSetupDataStruct* pLineSetupData);
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
MatrixServerDll_API void OnResetLineClientXMLSetupData(m_oLineSetupDataStruct* pLineSetupData);
// �򿪲��߿ͻ��˳��������ļ�
MatrixServerDll_API BOOL OpenLineClientXMLFile(m_oLineSetupDataStruct* pLineSetupData);
// �رղ��߿ͻ��˳��������ļ�
MatrixServerDll_API void CloseLineClientXMLFile(m_oLineSetupDataStruct* pLineSetupData);
// ����Survery��������
MatrixServerDll_API void LoadSurverySetupData(m_oLineSetupDataStruct* pLineSetupData);
// ����Survery��������
MatrixServerDll_API void SaveSurverySetupData(m_oLineSetupDataStruct* pLineSetupData);
// ����Survery��������
MatrixServerDll_API void SetSurverySetupData(char* pChar, unsigned int uiSize, m_oLineSetupDataStruct* pLineSetupData, bool bSave = true);
// ��ѯ SurveyXML �ļ���Ϣ
MatrixServerDll_API void QuerySurverySetupData(char* cProcBuf, int& iPos, m_oLineSetupDataStruct* pLineSetupData);
// ����Point Code��������
MatrixServerDll_API void LoadPointCodeSetupData(m_oLineSetupDataStruct* pLineSetupData);
// ����Point Code��������
MatrixServerDll_API void SavePointCodeSetupData(m_oLineSetupDataStruct* pLineSetupData);
// ����Point Code��������
MatrixServerDll_API void SetPointCodeSetupData(char* pChar, unsigned int uiSize, m_oLineSetupDataStruct* pLineSetupData, bool bSave = true);
// ��ѯ PointCode XML�ļ���Ϣ
MatrixServerDll_API void QueryPointCodeSetupData(char* cProcBuf, int& iPos, m_oLineSetupDataStruct* pLineSetupData);
// ����Sensor��������
MatrixServerDll_API void LoadSensorSetupData(m_oLineSetupDataStruct* pLineSetupData);
// ����Sensor��������
MatrixServerDll_API void SaveSensorSetupData(m_oLineSetupDataStruct* pLineSetupData);
// ����Sensor��������
MatrixServerDll_API void SetSensorSetupData(char* pChar, unsigned int uiSize, m_oLineSetupDataStruct* pLineSetupData, bool bSave = true);
// ��ѯ Sensor XML�ļ���Ϣ
MatrixServerDll_API void QuerySensorSetupData(char* cProcBuf, int& iPos, m_oLineSetupDataStruct* pLineSetupData);
// ����Marker��������
MatrixServerDll_API void LoadMarkerSetupData(m_oLineSetupDataStruct* pLineSetupData);
// ����Marker��������
MatrixServerDll_API void SaveMarkerSetupData(m_oLineSetupDataStruct* pLineSetupData);
// ����Marker��������
MatrixServerDll_API void SetMarkerSetupData(char* pChar, unsigned int uiSize, m_oLineSetupDataStruct* pLineSetupData, bool bSave = true);
// ��ѯ Marker XML�ļ���Ϣ
MatrixServerDll_API void QueryMarkerSetupData(char* cProcBuf, int& iPos, m_oLineSetupDataStruct* pLineSetupData);
// ����Aux��������
MatrixServerDll_API void LoadAuxSetupData(m_oLineSetupDataStruct* pLineSetupData);
// ����Aux��������
MatrixServerDll_API void SaveAuxSetupData(m_oLineSetupDataStruct* pLineSetupData);
// ����Aux��������
MatrixServerDll_API void SetAuxSetupData(char* pChar, unsigned int uiSize, m_oLineSetupDataStruct* pLineSetupData, bool bSave = true);
// ��ѯ Aux XML�ļ���Ϣ
MatrixServerDll_API void QueryAuxSetupData(char* cProcBuf, int& iPos, m_oLineSetupDataStruct* pLineSetupData);
// ����Detour��������
MatrixServerDll_API void LoadDetourSetupData(m_oLineSetupDataStruct* pLineSetupData);
// ����Detour��������
MatrixServerDll_API void SaveDetourSetupData(m_oLineSetupDataStruct* pLineSetupData);
// ����Detour��������
MatrixServerDll_API void SetDetourSetupData(char* pChar, unsigned int uiSize, m_oLineSetupDataStruct* pLineSetupData, bool bSave = true);
// ��ѯ Detour XML�ļ���Ϣ
MatrixServerDll_API void QueryDetourSetupData(char* cProcBuf, int& iPos, m_oLineSetupDataStruct* pLineSetupData);
// ����Mute��������
MatrixServerDll_API void LoadMuteSetupData(m_oLineSetupDataStruct* pLineSetupData);
// ����Mute��������
MatrixServerDll_API void SaveMuteSetupData(m_oLineSetupDataStruct* pLineSetupData);
// ����Mute��������
MatrixServerDll_API void SetMuteSetupData(char* pChar, unsigned int uiSize, m_oLineSetupDataStruct* pLineSetupData, bool bSave = true);
// ��ѯ Mute XML�ļ���Ϣ
MatrixServerDll_API void QueryMuteSetupData(char* cProcBuf, int& iPos, m_oLineSetupDataStruct* pLineSetupData);
// ����BlastMachine��������
MatrixServerDll_API void LoadBlastMachineSetupData(m_oLineSetupDataStruct* pLineSetupData);
// ����BlastMachine��������
MatrixServerDll_API void SaveBlastMachineSetupData(m_oLineSetupDataStruct* pLineSetupData);
// ����BlastMachine��������
MatrixServerDll_API void SetBlastMachineSetupData(char* pChar, unsigned int uiSize, m_oLineSetupDataStruct* pLineSetupData, bool bSave = true);
// ��ѯ BlastMachine XML�ļ���Ϣ
MatrixServerDll_API void QueryBlastMachineSetupData(char* cProcBuf, int& iPos, m_oLineSetupDataStruct* pLineSetupData);
// ����Absolute��������
MatrixServerDll_API void LoadAbsoluteSetupData(m_oLineSetupDataStruct* pLineSetupData);
// ����Absolute��������
MatrixServerDll_API void SaveAbsoluteSetupData(m_oLineSetupDataStruct* pLineSetupData);
// ����Absolute��������
MatrixServerDll_API void SetAbsoluteSetupData(char* pChar, unsigned int uiSize, m_oLineSetupDataStruct* pLineSetupData, bool bSave = true);
// ��ѯ Absolute XML�ļ���Ϣ
MatrixServerDll_API void QueryAbsoluteSetupData(char* cProcBuf, int& iPos, m_oLineSetupDataStruct* pLineSetupData);
// ����Generic��������
MatrixServerDll_API void LoadGenericSetupData(m_oLineSetupDataStruct* pLineSetupData);
// ����Generic��������
MatrixServerDll_API void SaveGenericSetupData(m_oLineSetupDataStruct* pLineSetupData);
// ����Generic��������
MatrixServerDll_API void SetGenericSetupData(char* pChar, unsigned int uiSize, m_oLineSetupDataStruct* pLineSetupData, bool bSave = true);
// ��ѯ Generic XML�ļ���Ϣ
MatrixServerDll_API void QueryGenericSetupData(char* cProcBuf, int& iPos, m_oLineSetupDataStruct* pLineSetupData);
// ����Look��������
MatrixServerDll_API void LoadLookSetupData(m_oLineSetupDataStruct* pLineSetupData);
// ����Look��������
MatrixServerDll_API void SaveLookSetupData(m_oLineSetupDataStruct* pLineSetupData);
// ����Look��������
MatrixServerDll_API void SetLookSetupData(char* pChar, unsigned int uiSize, m_oLineSetupDataStruct* pLineSetupData, bool bSave = true);
// ��ѯ Look XML�ļ���Ϣ
MatrixServerDll_API void QueryLookSetupData(char* cProcBuf, int& iPos, m_oLineSetupDataStruct* pLineSetupData);
// ����LAULeakage��������
MatrixServerDll_API void LoadLAULeakageSetupData(m_oLineSetupDataStruct* pLineSetupData);
// ����LAULeakage��������
MatrixServerDll_API void SaveLAULeakageSetupData(m_oLineSetupDataStruct* pLineSetupData);
// ����LAULeakage��������
MatrixServerDll_API void SetLAULeakageSetupData(char* pChar, unsigned int uiSize, m_oLineSetupDataStruct* pLineSetupData, bool bSave = true);
// ��ѯ LAULeakage XML�ļ���Ϣ
MatrixServerDll_API void QueryLAULeakageSetupData(char* cProcBuf, int& iPos, m_oLineSetupDataStruct* pLineSetupData);
// ����FormLine��������
MatrixServerDll_API void LoadFormLineSetupData(m_oLineSetupDataStruct* pLineSetupData);
// ����FormLine��������
MatrixServerDll_API void SaveFormLineSetupData(m_oLineSetupDataStruct* pLineSetupData);
// ����FormLine��������
MatrixServerDll_API void SetFormLineSetupData(char* pChar, unsigned int uiSize, m_oLineSetupDataStruct* pLineSetupData, bool bSave = true);
// ��ѯ FormLine XML�ļ���Ϣ
MatrixServerDll_API void QueryFormLineSetupData(char* cProcBuf, int& iPos, m_oLineSetupDataStruct* pLineSetupData);
// ����Instrument_SensorTestBase��������
MatrixServerDll_API void LoadInstrument_SensorTestBaseSetupData(bool bInstrument, m_oLineSetupDataStruct* pLineSetupData);
// ����Instrument_SensorTestBase��������
MatrixServerDll_API void SaveInstrument_SensorTestBaseSetupData(bool bInstrument, m_oLineSetupDataStruct* pLineSetupData);
// ����Instrument_SensorTestBase��������
MatrixServerDll_API void SetInstrument_SensorTestBaseSetupData(char* pChar, unsigned int uiSize, bool bInstrument, m_oLineSetupDataStruct* pLineSetupData, bool bSave = true);
// ��ѯ Instrument_SensorTestBase XML�ļ���Ϣ
MatrixServerDll_API void QueryInstrument_SensorTestBaseSetupData(char* cProcBuf, int& iPos, bool bInstrument, m_oLineSetupDataStruct* pLineSetupData);
// ����Instrument_SensorTestLimit��������
MatrixServerDll_API void LoadInstrument_SensorTestLimitSetupData(bool bInstrument, m_oLineSetupDataStruct* pLineSetupData);
// ����Instrument_SensorTestLimit��������
MatrixServerDll_API void SaveInstrument_SensorTestLimitSetupData(bool bInstrument, m_oLineSetupDataStruct* pLineSetupData);
// ����Instrument_SensorTestLimit��������
MatrixServerDll_API void SetInstrument_SensorTestLimitSetupData(char* pChar, unsigned int uiSize, bool bInstrument, m_oLineSetupDataStruct* pLineSetupData, bool bSave = true);
// ��ѯ InstrumentTestLimit XML�ļ���Ϣ
MatrixServerDll_API void QueryInstrument_SensorTestLimitSetupData(char* cProcBuf, int& iPos, bool bInstrument, m_oLineSetupDataStruct* pLineSetupData);
// ����Instrument Test��������
MatrixServerDll_API void LoadInstrumentTestSetupData(m_oLineSetupDataStruct* pLineSetupData);
// ����Instrument Test��������
MatrixServerDll_API void SaveInstrumentTestSetupData(m_oLineSetupDataStruct* pLineSetupData);
// ����Instrument Test��������
MatrixServerDll_API void SetInstrumentTestSetupData(char* pChar, unsigned int uiSize, m_oLineSetupDataStruct* pLineSetupData, bool bSave = true);
// ��ѯ InstrumentTest XML�ļ���Ϣ
MatrixServerDll_API void QueryInstrumentTestSetupData(char* cProcBuf, int& iPos, m_oLineSetupDataStruct* pLineSetupData);
// ����Sensor Test��������
MatrixServerDll_API void LoadSensorTestSetupData(m_oLineSetupDataStruct* pLineSetupData);
// ����Sensor Test��������
MatrixServerDll_API void SaveSensorTestSetupData(m_oLineSetupDataStruct* pLineSetupData);
// ����Sensor Test��������
MatrixServerDll_API void SetSensorTestSetupData(char* pChar, unsigned int uiSize, m_oLineSetupDataStruct* pLineSetupData, bool bSave = true);
// ��ѯ SensorTest XML�ļ���Ϣ
MatrixServerDll_API void QuerySensorTestSetupData(char* cProcBuf, int& iPos, m_oLineSetupDataStruct* pLineSetupData);
// ����Multiple Test��������
MatrixServerDll_API void LoadMultipleTestSetupData(m_oLineSetupDataStruct* pLineSetupData);
// ����Multiple Test��������
MatrixServerDll_API void SaveMultipleTestSetupData(m_oLineSetupDataStruct* pLineSetupData);
// ����Multiple Test��������
MatrixServerDll_API void SetMultipleTestSetupData(char* pChar, unsigned int uiSize, m_oLineSetupDataStruct* pLineSetupData, bool bSave = true);
// ��ѯ MultipleTest XML�ļ���Ϣ
MatrixServerDll_API void QueryMultipleTestSetupData(char* cProcBuf, int& iPos, m_oLineSetupDataStruct* pLineSetupData);
// ����SeisMonitor��������
MatrixServerDll_API void LoadSeisMonitorSetupData(m_oLineSetupDataStruct* pLineSetupData);
// ����SeisMonitor��������
MatrixServerDll_API void SaveSeisMonitorSetupData(m_oLineSetupDataStruct* pLineSetupData);
// ����SeisMonitor��������
MatrixServerDll_API void SetSeisMonitorSetupData(char* pChar, unsigned int uiSize, m_oLineSetupDataStruct* pLineSetupData, bool bSave = true);
// ��ѯ SeisMonitorTest XML�ļ���Ϣ
MatrixServerDll_API void QuerySeisMonitorSetupData(char* cProcBuf, int& iPos, m_oLineSetupDataStruct* pLineSetupData);
// ��XML�����ļ��õ�������������ֵ
MatrixServerDll_API float QueryTestDataLimit(bool bInstrument, string str, m_oLineSetupDataStruct* pLineSetupData);
// �������߿ͻ���ͨѶ��Ϣ�ṹ��
MatrixServerDll_API m_oLineSetupDataStruct* OnCreateLineAppSetupData(void);
// ���ز��߿ͻ��˳�����������
MatrixServerDll_API void LoadLineAppSetupData(m_oLineSetupDataStruct* pLineSetupData);
// ������߿ͻ��˳�����������
MatrixServerDll_API void SaveLineAppSetupData(m_oLineSetupDataStruct* pLineSetupData);
// �ͷŲ��߿ͻ��˲���������Ϣ�ṹ�建����
MatrixServerDll_API void OnFreeLineXMLSetupData(m_oLineSetupDataStruct* pLineSetupData);

// ��ʼ��ʩ���ͻ�����������Ϣ
MatrixServerDll_API void OnInitOptClientXMLSetupData(m_oOptSetupDataStruct* pOptSetupData);
// �����ڵ����
MatrixServerDll_API void OnResetOptSourceShotList(m_oInstrumentCommInfoStruct* pCommInfo);
// ����Explo��Դ���Ͷ���
MatrixServerDll_API void OnResetOptExploList(m_oInstrumentCommInfoStruct* pCommInfo);
// ����Vibro��Դ���Ͷ���
MatrixServerDll_API void OnResetOptVibroList(m_oInstrumentCommInfoStruct* pCommInfo);
// ���ô�������Aux����
MatrixServerDll_API void OnResetOptProcessAuxList(m_oInstrumentCommInfoStruct* pCommInfo);
// ���ô�������Acq����
MatrixServerDll_API void OnResetOptProcessAcqList(m_oInstrumentCommInfoStruct* pCommInfo);
// ���ô������Ͷ���
MatrixServerDll_API void OnResetOptProcessTypeList(m_oInstrumentCommInfoStruct* pCommInfo);
// ����ע�Ͷ���
MatrixServerDll_API void OnResetOptCommentList(m_oInstrumentCommInfoStruct* pCommInfo);
// ����ʩ���ͻ�����Ϣ
MatrixServerDll_API void OnResetOptClientXMLSetupData(m_oOptSetupDataStruct* pOptSetupData);
// ��ʩ���ͻ��˳��������ļ�
MatrixServerDll_API BOOL OpenOptClientXMLFile(m_oOptSetupDataStruct* pOptSetupData);
// �ر�ʩ���ͻ��˳��������ļ�
MatrixServerDll_API void CloseOptClientXMLFile(m_oOptSetupDataStruct* pOptSetupData);
// ����Delay��������
MatrixServerDll_API void LoadOptDelaySetupData(m_oOptSetupDataStruct* pOptSetupData);
// ����Delay��������
MatrixServerDll_API void SaveDelaySetupData(m_oOptSetupDataStruct* pOptSetupData);
// ����Delay��������
MatrixServerDll_API void SetDelaySetupData(char* pChar, unsigned int uiSize, m_oOptSetupDataStruct* pOptSetupData, bool bSave = true);
// ��ѯ Delay XML�ļ���Ϣ
MatrixServerDll_API void QueryDelaySetupData(char* cProcBuf, int& iPos, m_oOptSetupDataStruct* pOptSetupData);
// ����SourceShot��������
MatrixServerDll_API void LoadSourceShotSetupData(m_oOptSetupDataStruct* pOptSetupData);
// ����SourceShot��������
MatrixServerDll_API void SaveSourceShotSetupData(m_oOptSetupDataStruct* pOptSetupData);
// ����SourceShot��������
MatrixServerDll_API void SetSourceShotSetupData(char* pChar, unsigned int uiSize, m_oOptSetupDataStruct* pOptSetupData, bool bSave = true);
// ��ѯ SourceShot XML�ļ���Ϣ
MatrixServerDll_API void QuerySourceShotSetupData(char* cProcBuf, int& iPos, m_oOptSetupDataStruct* pOptSetupData);
// ����Explo��������
MatrixServerDll_API void LoadExploSetupData(m_oOptSetupDataStruct* pOptSetupData);
// ����Explo��������
MatrixServerDll_API void SaveExploSetupData(m_oOptSetupDataStruct* pOptSetupData);
// ����Explo��������
MatrixServerDll_API void SetExploSetupData(char* pChar, unsigned int uiSize, m_oOptSetupDataStruct* pOptSetupData, bool bSave = true);
// ��ѯ Explo XML�ļ���Ϣ
MatrixServerDll_API void QueryExploSetupData(char* cProcBuf, int& iPos, m_oOptSetupDataStruct* pOptSetupData);
// ����Vibro��������
MatrixServerDll_API void LoadVibroSetupData(m_oOptSetupDataStruct* pOptSetupData);
// ����Vibro��������
MatrixServerDll_API void SaveVibroSetupData(m_oOptSetupDataStruct* pOptSetupData);
// ����Vibro��������
MatrixServerDll_API void SetVibroSetupData(char* pChar, unsigned int uiSize, m_oOptSetupDataStruct* pOptSetupData, bool bSave = true);
// ��ѯ Vibro XML�ļ���Ϣ
MatrixServerDll_API void QueryVibroSetupData(char* cProcBuf, int& iPos, m_oOptSetupDataStruct* pOptSetupData);
// ����ProcessRecord��������
MatrixServerDll_API void LoadOptProcessRecordSetupData(m_oOptSetupDataStruct* pOptSetupData);
// ����ProcessRecord��������
MatrixServerDll_API void SaveProcessRecordSetupData(m_oOptSetupDataStruct* pOptSetupData);
// ����ProcessRecord��������
MatrixServerDll_API void SetProcessRecordSetupData(char* pChar, unsigned int uiSize, m_oOptSetupDataStruct* pOptSetupData, bool bSave = true);
// ��ѯ ProcessRecord XML�ļ���Ϣ
MatrixServerDll_API void QueryProcessRecordSetupData(char* cProcBuf, int& iPos, m_oOptSetupDataStruct* pOptSetupData);
// ����ProcessAux��������
MatrixServerDll_API void LoadProcessAuxSetupData(m_oOptSetupDataStruct* pOptSetupData);
// ����ProcessAux��������
MatrixServerDll_API void SaveProcessAuxSetupData(m_oOptSetupDataStruct* pOptSetupData);
// ����ProcessAux��������
MatrixServerDll_API void SetProcessAuxSetupData(char* pChar, unsigned int uiSize, m_oOptSetupDataStruct* pOptSetupData, bool bSave = true);
// ��ѯ ProcessAux XML�ļ���Ϣ
MatrixServerDll_API void QueryProcessAuxSetupData(char* cProcBuf, int& iPos, m_oOptSetupDataStruct* pOptSetupData);
// ����ProcessAcq��������
MatrixServerDll_API void LoadProcessAcqSetupData(m_oOptSetupDataStruct* pOptSetupData);
// ����ProcessAcq��������
MatrixServerDll_API void SaveProcessAcqSetupData(m_oOptSetupDataStruct* pOptSetupData);
// ����ProcessAcq��������
MatrixServerDll_API void SetProcessAcqSetupData(char* pChar, unsigned int uiSize, m_oOptSetupDataStruct* pOptSetupData, bool bSave = true);
// ��ѯ ProcessAcq XML�ļ���Ϣ
MatrixServerDll_API void QueryProcessAcqSetupData(char* cProcBuf, int& iPos, m_oOptSetupDataStruct* pOptSetupData);
// ����ProcessType��������
MatrixServerDll_API void LoadProcessTypeSetupData(m_oOptSetupDataStruct* pOptSetupData);
// ����ProcessType��������
MatrixServerDll_API void SaveProcessTypeSetupData(m_oOptSetupDataStruct* pOptSetupData);
// ����ProcessType��������
MatrixServerDll_API void SetProcessTypeSetupData(char* pChar, unsigned int uiSize, m_oOptSetupDataStruct* pOptSetupData, bool bSave = true);
// ��ѯ ProcessType XML�ļ���Ϣ
MatrixServerDll_API void QueryProcessTypeSetupData(char* cProcBuf, int& iPos, m_oOptSetupDataStruct* pOptSetupData);
// ����ProcessComments��������
MatrixServerDll_API void LoadProcessCommentsSetupData(m_oOptSetupDataStruct* pOptSetupData);
// ����ProcessComments��������
MatrixServerDll_API void SaveProcessCommentsSetupData(m_oOptSetupDataStruct* pOptSetupData);
// ����ProcessComments��������
MatrixServerDll_API void SetProcessCommentsSetupData(char* pChar, unsigned int uiSize, m_oOptSetupDataStruct* pOptSetupData, bool bSave = true);
// ��ѯ ProcessComments XML�ļ���Ϣ
MatrixServerDll_API void QueryProcessCommentsSetupData(char* cProcBuf, int& iPos, m_oOptSetupDataStruct* pOptSetupData);
// ����ʩ���ͻ���ͨѶ��Ϣ�ṹ��
MatrixServerDll_API m_oOptSetupDataStruct* OnCreateOptAppSetupData(void);
// ����ʩ���ͻ��˳�����������
MatrixServerDll_API void LoadOptAppSetupData(m_oOptSetupDataStruct* pOptSetupData);
// ����ʩ���ͻ��˳�����������
MatrixServerDll_API void SaveOptAppSetupData(m_oOptSetupDataStruct* pOptSetupData);
// �ͷ�ʩ���ͻ��˲���������Ϣ�ṹ�建����
MatrixServerDll_API void OnFreeOptXMLSetupData(m_oOptSetupDataStruct* pOptSetupData);

// ��ʼ���������������Ϣ
MatrixServerDll_API void OnInitServerXMLSetupData(m_oServerSetupDataStruct* pServerSetupData);
// �򿪷�����������ļ�
MatrixServerDll_API BOOL OpenServerXMLFile(m_oServerSetupDataStruct* pServerSetupData);
// �رշ�����������ļ�
MatrixServerDll_API void CloseServerXMLFile(m_oServerSetupDataStruct* pServerSetupData);
// ����IP��ַ��������
MatrixServerDll_API void LoadServerIPSetupData(m_oServerSetupDataStruct* pServerSetupData);
// ���ض˿���������
MatrixServerDll_API void LoadServerPortSetupData(m_oServerSetupDataStruct* pServerSetupData);
// ����ADC������������
MatrixServerDll_API void LoadServerADCSetSetupData(m_oServerSetupDataStruct* pServerSetupData);
// ���ط������˲�����������
MatrixServerDll_API void LoadServerParameterSetupData(m_oServerSetupDataStruct* pServerSetupData);
// ����������˲�����������
MatrixServerDll_API void SaveServerParameterSetupData(m_oServerSetupDataStruct* pServerSetupData);
// ���������ͨѶ��Ϣ�ṹ��
MatrixServerDll_API m_oServerSetupDataStruct* OnCreateServerAppSetupData(void);
// ���ط���˳�����������
MatrixServerDll_API void LoadServerAppSetupData(m_oServerSetupDataStruct* pServerSetupData);
// ��ʼ��Pcap����������Ϣ�ṹ��
MatrixServerDll_API void OnInitPcapXMLSetupData(m_oNetPcapSetupDataStruct* pPcapSetupData);
// ����Pcap������Ϣ�ṹ��
MatrixServerDll_API m_oNetPcapSetupDataStruct* OnCreatePcapAppSetupData(void);
// ��Pcap���������ļ�
MatrixServerDll_API BOOL OpenPcapXMLFile(m_oNetPcapSetupDataStruct* pPcapSetupData);
// �ر�Pcap���������ļ�
MatrixServerDll_API void ClosePcapXMLFile(m_oNetPcapSetupDataStruct* pPcapSetupData);
// ����PcapIP��������
MatrixServerDll_API void LoadPcapIPSetupData(m_oNetPcapSetupDataStruct* pPcapSetupData);
// ����Pcap�˿���������
MatrixServerDll_API void LoadPcapPortSetupData(m_oNetPcapSetupDataStruct* pPcapSetupData);
// ����Pcap������������
MatrixServerDll_API void LoadPcapParamSetupData(m_oNetPcapSetupDataStruct* pPcapSetupData);
// ����Pcap����������Ϣ
MatrixServerDll_API void LoadPcapAppSetupData(m_oNetPcapSetupDataStruct* pPcapSetupData);
// �ͷ�Pcap����������Ϣ�ṹ�建����
MatrixServerDll_API void OnFreePcapXMLSetupData(m_oNetPcapSetupDataStruct* pPcapSetupData);
// �ͷŷ���˲���������Ϣ�ṹ�建����
MatrixServerDll_API void OnFreeServerXMLSetupData(m_oServerSetupDataStruct* pServerSetupData);

// �õ����߽�������
MatrixServerDll_API void GetLineRevSection(unsigned int& uiLineNum, unsigned int& uiColumnNum, m_oLineSetupDataStruct* pLineSetupData);
/************************************************************************/
/* ����֡                                                               */
/************************************************************************/
// ��������֡��Ϣ�ṹ��
MatrixServerDll_API m_oHeartBeatFrameStruct* OnCreateInstrHeartBeat(void);
// ��ʼ������
MatrixServerDll_API void OnInitInstrHeartBeat(m_oHeartBeatFrameStruct* pHeartBeatFrame, 
	m_oInstrumentCommInfoStruct* pCommInfo, m_oConstVarStruct* pConstVar);
// �ر�����֡��Ϣ�ṹ��
MatrixServerDll_API void OnCloseInstrHeartBeat(m_oHeartBeatFrameStruct* pHeartBeatFrame);
// �ͷ�����֡��Ϣ�ṹ��
MatrixServerDll_API void OnFreeInstrHeartBeat(m_oHeartBeatFrameStruct* pHeartBeatFrame);
// ���������������˿�
MatrixServerDll_API void OnCreateAndSetHeartBeatSocket(m_oHeartBeatFrameStruct* pHeartBeatFrame, 
	m_oLogOutPutStruct* pLogOutPut = NULL);
// ��������֡
MatrixServerDll_API void MakeInstrHeartBeatFrame(m_oHeartBeatFrameStruct* pHeartBeatFrame, 
	m_oConstVarStruct* pConstVar, m_oLogOutPutStruct* pLogOutPut);

/************************************************************************/
/* �װ�֡                                                               */
/************************************************************************/
// �����װ�֡��Ϣ�ṹ��
MatrixServerDll_API m_oHeadFrameStruct* OnCreateInstrHeadFrame(void);
// ��ʼ���װ�
MatrixServerDll_API void OnInitInstrHeadFrame(m_oHeadFrameStruct* pHeadFrame, 
	m_oInstrumentCommInfoStruct* pCommInfo, m_oConstVarStruct* pConstVar);
// �ر��װ�֡��Ϣ�ṹ��
MatrixServerDll_API void OnCloseInstrHeadFrame(m_oHeadFrameStruct* pHeadFrame);
// �ͷ��װ�֡��Ϣ�ṹ��
MatrixServerDll_API void OnFreeInstrHeadFrame(m_oHeadFrameStruct* pHeadFrame);
// �����������װ��˿�
MatrixServerDll_API void OnCreateAndSetHeadFrameSocket(m_oHeadFrameStruct* pHeadFrame, 
	m_oLogOutPutStruct* pLogOutPut = NULL);
// �����װ�֡
MatrixServerDll_API bool ParseInstrHeadFrame(m_oHeadFrameStruct* pHeadFrame, 
	m_oConstVarStruct* pConstVar, m_oLogOutPutStruct* pLogOutPut);

/************************************************************************/
/* IP��ַ����֡                                                         */
/************************************************************************/
// ����IP��ַ����֡��Ϣ�ṹ��
MatrixServerDll_API m_oIPSetFrameStruct* OnCreateInstrIPSetFrame(void);
// ��ʼ��IP��ַ����
MatrixServerDll_API void OnInitInstrIPSetFrame(m_oIPSetFrameStruct* pIPSetFrame,
	m_oInstrumentCommInfoStruct* pCommInfo, m_oConstVarStruct* pConstVar);
// �ر�IP��ַ����֡��Ϣ�ṹ��
MatrixServerDll_API void OnCloseInstrIPSetFrame(m_oIPSetFrameStruct* pIPSetFrame);
// �ͷ�IP��ַ����֡��Ϣ�ṹ��
MatrixServerDll_API void OnFreeInstrIPSetFrame(m_oIPSetFrameStruct* pIPSetFrame);
// ����������IP��ַ���ö˿�
MatrixServerDll_API void OnCreateAndSetIPSetFrameSocket(m_oIPSetFrameStruct* pIPSetFrame, 
	m_oLogOutPutStruct* pLogOutPut = NULL);
// ����IP��ַ����Ӧ��֡
MatrixServerDll_API bool ParseInstrIPSetReturnFrame(m_oIPSetFrameStruct* pIPSetFrame, 
	m_oConstVarStruct* pConstVar, m_oLogOutPutStruct* pLogOutPut);
// �򿪽���վĳһ·�ɷ���ĵ�Դ
MatrixServerDll_API bool OpenLAUXRoutPower(int iLineIndex, int iPointIndex, unsigned char ucLAUXRoutOpenSet, 
	m_oEnvironmentStruct* pEnv);
// ����IP��ַ��ѯ֡
MatrixServerDll_API void MakeInstrIPQueryFrame(m_oIPSetFrameStruct* pIPSetFrame, 
	m_oConstVarStruct* pConstVar, unsigned int uiInstrumentIP, m_oLogOutPutStruct* pLogOutPut);
// ����IP��ַ����֡
MatrixServerDll_API void MakeInstrIPSetFrame(m_oIPSetFrameStruct* pIPSetFrame, 
	m_oConstVarStruct* pConstVar, m_oInstrumentStruct* pInstrument, m_oLogOutPutStruct* pLogOutPut);

/************************************************************************/
/* β��֡                                                               */
/************************************************************************/
// ����β��֡��Ϣ�ṹ��
MatrixServerDll_API m_oTailFrameStruct* OnCreateInstrTailFrame(void);
// ��ʼ��β��
MatrixServerDll_API void OnInitInstrTailFrame(m_oTailFrameStruct* pTailFrame, 
	m_oInstrumentCommInfoStruct* pCommInfo, m_oConstVarStruct* pConstVar);
// �ر�β��֡��Ϣ�ṹ��
MatrixServerDll_API void OnCloseInstrTailFrame(m_oTailFrameStruct* pTailFrame);
// �ͷ�β��֡��Ϣ�ṹ��
MatrixServerDll_API void OnFreeInstrTailFrame(m_oTailFrameStruct* pTailFrame);
// ����������β���˿�
MatrixServerDll_API void OnCreateAndSetTailFrameSocket(m_oTailFrameStruct* pTailFrame, 
	m_oLogOutPutStruct* pLogOutPut = NULL);
// ����β��֡
MatrixServerDll_API bool ParseInstrTailFrame(m_oTailFrameStruct* pTailFrame, 
	m_oConstVarStruct* pConstVar, m_oLogOutPutStruct* pLogOutPut);


/************************************************************************/
/* β��ʱ��֡                                                           */
/************************************************************************/
// ����β��ʱ��֡��Ϣ�ṹ��
MatrixServerDll_API m_oTailTimeFrameStruct* OnCreateInstrTailTimeFrame(void);
// ��ʼ��β��ʱ��֡
MatrixServerDll_API void OnInitInstrTailTimeFrame(m_oTailTimeFrameStruct* pTailTimeFrame,
	m_oInstrumentCommInfoStruct* pCommInfo, m_oConstVarStruct* pConstVar);
// �ر�β��ʱ��֡��Ϣ�ṹ��
MatrixServerDll_API void OnCloseInstrTailTimeFrame(m_oTailTimeFrameStruct* pTailTimeFrame);
// �ͷ�β��ʱ��֡��Ϣ�ṹ��
MatrixServerDll_API void OnFreeInstrTailTimeFrame(m_oTailTimeFrameStruct* pTailTimeFrame);
// ����������β��ʱ�̶˿�
MatrixServerDll_API void OnCreateAndSetTailTimeFrameSocket(m_oTailTimeFrameStruct* pTailTimeFrame, 
	m_oLogOutPutStruct* pLogOutPut = NULL);
// ����β��ʱ�̲�ѯ֡
MatrixServerDll_API bool ParseInstrTailTimeReturnFrame(m_oTailTimeFrameStruct* pTailTimeFrame, 
	m_oConstVarStruct* pConstVar, m_oLogOutPutStruct* pLogOutPut);
// ��IP��ַ��ѯβ��ʱ��֡
MatrixServerDll_API void MakeInstrTailTimeQueryFramebyIP(m_oTailTimeFrameStruct* pTailTimeFrame, 
	m_oConstVarStruct* pConstVar, unsigned int uiInstrumentIP, m_oLogOutPutStruct* pLogOutPut);
// �㲥��ѯβ��ʱ��֡
MatrixServerDll_API void MakeInstrTailTimeQueryFramebyBroadCast(m_oTailTimeFrameStruct* pTailTimeFrame, 
	m_oConstVarStruct* pConstVar, unsigned int uiBroadCastPort, m_oLogOutPutStruct* pLogOutPut);

/************************************************************************/
/* ʱͳ֡                                                               */
/************************************************************************/
// ����ʱͳ����֡��Ϣ�ṹ��
MatrixServerDll_API m_oTimeDelayFrameStruct* OnCreateInstrTimeDelayFrame(void);
// ��ʼ��ʱͳ����֡
MatrixServerDll_API void OnInitInstrTimeDelayFrame(m_oTimeDelayFrameStruct* pTimeDelayFrame,
	m_oInstrumentCommInfoStruct* pCommInfo, m_oConstVarStruct* pConstVar);
// �ر�ʱͳ����֡��Ϣ�ṹ��
MatrixServerDll_API void OnCloseInstrTimeDelayFrame(m_oTimeDelayFrameStruct* pTimeDelayFrame);
// �ͷ�ʱͳ����֡��Ϣ�ṹ��
MatrixServerDll_API void OnFreeInstrTimeDelayFrame(m_oTimeDelayFrameStruct* pTimeDelayFrame);
// ����������ʱͳ���ö˿�
MatrixServerDll_API void OnCreateAndSetTimeDelayFrameSocket(m_oTimeDelayFrameStruct* pTimeDelayFrame, 
	m_oLogOutPutStruct* pLogOutPut = NULL);
// ����ʱͳ����Ӧ��֡
MatrixServerDll_API bool ParseInstrTimeDelayReturnFrame(m_oTimeDelayFrameStruct* pTimeDelayFrame, 
	m_oConstVarStruct* pConstVar, m_oLogOutPutStruct* pLogOutPut);
// ����ʱͳ����֡
MatrixServerDll_API void MakeInstrDelayTimeFrame(m_oTimeDelayFrameStruct* pTimeDelayFrame, 
	m_oConstVarStruct* pConstVar, m_oInstrumentStruct* pInstrument, m_oLogOutPutStruct* pLogOutPut);

/************************************************************************/
/* ADC��������֡                                                        */
/************************************************************************/
// ����ADC��������֡��Ϣ�ṹ��
MatrixServerDll_API m_oADCSetFrameStruct* OnCreateInstrADCSetFrame(void);
// ��ʼ��ADC��������֡
MatrixServerDll_API void OnInitInstrADCSetFrame(m_oADCSetFrameStruct* pADCSetFrame,
	m_oInstrumentCommInfoStruct* pCommInfo, m_oConstVarStruct* pConstVar);
// �ر�ADC��������֡��Ϣ�ṹ��
MatrixServerDll_API void OnCloseInstrADCSetFrame(m_oADCSetFrameStruct* pADCSetFrame);
// �ͷ�ADC��������֡��Ϣ�ṹ��
MatrixServerDll_API void OnFreeInstrADCSetFrame(m_oADCSetFrameStruct* pADCSetFrame);
// ����������ADC�������ö˿�
MatrixServerDll_API void OnCreateAndSetADCSetFrameSocket(m_oADCSetFrameStruct* pADCSetFrame, 
	m_oLogOutPutStruct* pLogOutPut = NULL);
// ����ADC��������Ӧ��֡
MatrixServerDll_API bool ParseInstrADCSetReturnFrame(m_oADCSetFrameStruct* pADCSetFrame,
	m_oConstVarStruct* pConstVar, m_oLogOutPutStruct* pLogOutPut);

/************************************************************************/
/* �����ѯ֡                                                           */
/************************************************************************/
// ���������ѯ֡��Ϣ�ṹ��
MatrixServerDll_API m_oErrorCodeFrameStruct* OnCreateInstrErrorCodeFrame(void);
// ��ʼ�������ѯ֡
MatrixServerDll_API void OnInitInstrErrorCodeFrame(m_oErrorCodeFrameStruct* pErrorCodeFrame,
	m_oInstrumentCommInfoStruct* pCommInfo, m_oConstVarStruct* pConstVar);
// �ر������ѯ֡��Ϣ�ṹ��
MatrixServerDll_API void OnCloseInstrErrorCodeFrame(m_oErrorCodeFrameStruct* pErrorCodeFrame);
// �ͷ������ѯ֡��Ϣ�ṹ��
MatrixServerDll_API void OnFreeInstrErrorCodeFrame(m_oErrorCodeFrameStruct* pErrorCodeFrame);
// ���������������ѯ�˿�
MatrixServerDll_API void OnCreateAndSetErrorCodeFrameSocket(m_oErrorCodeFrameStruct* pErrorCodeFrame, 
	m_oLogOutPutStruct* pLogOutPut = NULL);
// ���������ѯӦ��֡
MatrixServerDll_API bool ParseInstrErrorCodeReturnFrame(m_oErrorCodeFrameStruct* pErrorCodeFrame, 
	m_oConstVarStruct* pConstVar, m_oLogOutPutStruct* pLogOutPut);
// �㲥��ѯ����
MatrixServerDll_API void MakeInstrErrorCodeQueryFrame(m_oErrorCodeFrameStruct* pErrorCodeFrame, 
	m_oConstVarStruct* pConstVar, unsigned int uiBroadCastPort, m_oLogOutPutStruct* pLogOutPut);

/************************************************************************/
/* ADC����֡                                                            */
/************************************************************************/
// ����ADC����֡��Ϣ�ṹ��
MatrixServerDll_API m_oADCDataFrameStruct* OnCreateInstrADCDataFrame(void);
// ��ʼ��ADC����֡
MatrixServerDll_API void OnInitInstrADCDataFrame(m_oADCDataFrameStruct* pADCDataFrame,
	m_oInstrumentCommInfoStruct* pCommInfo, m_oConstVarStruct* pConstVar);
// �ر�ADC����֡��Ϣ�ṹ��
MatrixServerDll_API void OnCloseInstrADCDataFrame(m_oADCDataFrameStruct* pADCDataFrame);
// �ͷ�ADC����֡��Ϣ�ṹ��
MatrixServerDll_API void OnFreeInstrADCDataFrame(m_oADCDataFrameStruct* pADCDataFrame);
// ����������ADC����֡�˿�
MatrixServerDll_API void OnCreateAndSetADCDataFrameSocket(m_oADCDataFrameStruct* pADCDataFrame, 
	m_oLogOutPutStruct* pLogOutPut = NULL);
// ����ADC���ݽ���֡
MatrixServerDll_API bool ParseInstrADCDataRecFrame(m_oADCDataFrameStruct* pADCDataFrame, 
	m_oConstVarStruct* pConstVar, m_oLogOutPutStruct* pLogOutPut);
// ����ADC���ݲ�ѯ֡
MatrixServerDll_API void MakeInstrADCDataFrame(m_oADCDataFrameStruct* pADCDataFrame, 
	m_oConstVarStruct* pConstVar, unsigned int uiIP, unsigned short usDataPoint, 
	m_oLogOutPutStruct* pLogOutPut);

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
// ��������ɾ��������ָ�������ָ��
MatrixServerDll_API BOOL DeleteInstrumentFromLocationMap(int iLineIndex, int iPointIndex, 
	map<m_oInstrumentLocationStruct, m_oInstrumentStruct*>* pMap);
// �õ�������ĳһ�����ϵ�·��IP
MatrixServerDll_API bool GetRoutIPBySn(unsigned int uiSN, int iDirection, 
	m_oInstrumentListStruct* pInstrumentList, unsigned int& uiRoutIP);
// ���������Ĵ��ʱ��
MatrixServerDll_API void UpdateInstrActiveTime(m_oInstrumentStruct* pInstrument);
/**
* �������ӷ��򣬵õ����ӵ���һ������
	* @param unsigned int uiRoutDirection ���� 1-�ϣ�2-�£�3-��4��
* @return CInstrument* ����ָ�� NLLL�����ӵ���һ������������
	*/
MatrixServerDll_API m_oInstrumentStruct* GetNextInstrAlongRout(m_oInstrumentStruct* pInstrument, int iRoutDirection);
/**
* �������ӷ��򣬵õ����ӵ�ǰһ������
* @return CInstrument* ����ָ�� NLLL�����ӵ�ǰһ������������
*/
MatrixServerDll_API m_oInstrumentStruct* GetPreviousInstr(m_oInstrumentStruct* pInstrument);



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
MatrixServerDll_API void UpdateLineChangeTime(m_oLineListStruct* pLineList);

/************************************************************************/
/* ·�ɽṹ��                                                           */
/************************************************************************/
// ����·����Ϣ
MatrixServerDll_API void OnRoutReset(m_oRoutStruct* pRout);
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
MatrixServerDll_API void OnInitRoutList(m_oRoutListStruct* pRoutList, m_oConstVarStruct* pConstVar);
// �ر�·�ɶ��нṹ��
MatrixServerDll_API void OnCloseRoutList(m_oRoutListStruct* pRoutList);
// �ͷ�·�ɶ��нṹ��
MatrixServerDll_API void OnFreeRoutList(m_oRoutListStruct* pRoutList);
// �õ�һ������·��
MatrixServerDll_API m_oRoutStruct* GetFreeRout(m_oRoutListStruct* pRoutList);
// ����һ������·��
MatrixServerDll_API void AddFreeRout(m_oRoutStruct* pRout, m_oRoutListStruct* pRoutList);

/************************************************************************/
/* ���߶���                                                             */
/************************************************************************/
// �������߶��нṹ��
MatrixServerDll_API m_oLineListStruct* OnCreateLineList(void);
// ���ò��߶��нṹ��
MatrixServerDll_API void OnResetLineList(m_oLineListStruct* pLineList);
// ��ʼ�����߶��нṹ��
MatrixServerDll_API void OnInitLineList(m_oLineListStruct* pLineList, m_oConstVarStruct* pConstVar);
// �رղ��߶��нṹ��
MatrixServerDll_API void OnCloseLineList(m_oLineListStruct* pLineList);
// �ͷŲ��߶��нṹ��
MatrixServerDll_API void OnFreeLineList(m_oLineListStruct* pLineList);
// �õ���������λ��
MatrixServerDll_API void QueryInstrumentLocation(char* pChar, int& iPos, m_oLineListStruct* pLineList);
// ���µײ������ı���ϵͳʱ��
MatrixServerDll_API void UpdateLocalSysTime(unsigned int uiSysTime, m_oLineListStruct* pLineList);
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
// �ж��������Ƿ��Ѽ������ݴ洢����������
MatrixServerDll_API BOOL IfIndexExistInADCDataBufMap(unsigned int uiIndex, hash_map<unsigned int, m_oADCDataBufStruct*>* pMap);
// �����ݴ洢�������������м��뻺����ָ��
MatrixServerDll_API void AddToADCDataBufMap(unsigned int uiIndex, m_oADCDataBufStruct* pADCDataBuf,
	hash_map<unsigned int, m_oADCDataBufStruct*>* pMap);
// �������������ţ���������õ����ݴ洢������ָ��
MatrixServerDll_API m_oADCDataBufStruct* GetADCDataBufFromMap(unsigned int uiIndex, 
	hash_map<unsigned int, m_oADCDataBufStruct*>* pMap);
// ��������ɾ��������ָ������ݴ洢������ָ��
MatrixServerDll_API BOOL DeleteADCDataBufFromMap(unsigned int uiIndex, 
	hash_map<unsigned int, m_oADCDataBufStruct*>* pMap);
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
MatrixServerDll_API BOOL IfIndexExistInOptTaskIPMap(unsigned int uiIndex,
	hash_map<unsigned int, m_oOptInstrumentStruct*>* pMap);
// ��ʩ�����������������еõ��������к�
// MatrixServerDll_API m_oOptInstrumentStruct GetLineNbFromOptTaskSNMap(unsigned int uiIndex,
// 	hash_map<unsigned int, m_oOptInstrumentStruct>* pMap);
// ��ʩ�����������������м�������
MatrixServerDll_API void AddToOptTaskIPMap(unsigned int uiIndex, m_oOptInstrumentStruct* pOptInstr,
	hash_map<unsigned int, m_oOptInstrumentStruct*>* pMap);
// ����һ��ʩ������
MatrixServerDll_API void AddOptTaskToMap(unsigned int uiIndex, m_oOptTaskStruct* pOptTask, 
	hash_map<unsigned int, m_oOptTaskStruct*>* pMap);
// �������������ţ���������õ�ʩ������ָ��
MatrixServerDll_API m_oOptTaskStruct* GetOptTaskFromMap(unsigned int uiIndex, 
	hash_map<unsigned int, m_oOptTaskStruct*>* pMap);
// �������������ţ���������õ�ʩ������ָ��
MatrixServerDll_API m_oOptInstrumentStruct* GetOptTaskFromIPMap(unsigned int uiIndex, 
	hash_map<unsigned int, m_oOptInstrumentStruct*>* pMap);
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
MatrixServerDll_API void InstrumentLocationSort(m_oInstrumentStruct* pInstrument, m_oRoutStruct* pRout);
/**
* ���ý���վĳ�������·��
	* @param CInstrument* &pInstrument ����ָ��
	* @param unsigned int uiRoutDirection ·�ɷ���
* @return void
*/
MatrixServerDll_API void SetCrossRout(m_oInstrumentStruct* pInstrument, int iRoutDirection, m_oRoutListStruct* pRoutList);
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
// ����һ��·��
MatrixServerDll_API void FreeRoutFromMap(unsigned int uiRoutIP, m_oRoutListStruct* pRoutList);
// ����һ������
MatrixServerDll_API void FreeInstrumentFromMap(m_oInstrumentStruct* pInstrument, 
	m_oLineListStruct* pLineList, m_oLogOutPutStruct* pLogOutPut);
// ɾ����·�ɷ���ָ������֮�������
MatrixServerDll_API void DeleteInstrumentAlongRout(m_oInstrumentStruct* pInstrument, m_oRoutStruct* pRout, 
	m_oLineListStruct* pLineList, m_oLogOutPutStruct* pLogOutPut);
// ��·�ɷ�����ɾ��������֮���ȫ������
MatrixServerDll_API void DeleteAllInstrumentAlongRout(m_oInstrumentStruct* pInstrument, m_oRoutStruct* pRout, 
	m_oLineListStruct* pLineList, m_oLogOutPutStruct* pLogOutPut);
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
MatrixServerDll_API void PrepareTailTimeFrame(m_oRoutStruct* pRout);
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
	unsigned int uiDstIP, unsigned int uiTBHigh);
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
// MatrixServerDll_API void GetTimeDelayTaskAlongRout(m_oRoutStruct* pRout, m_oRoutListStruct* pRoutList);
// �õ�ʱͳ����
// MatrixServerDll_API void GetTimeDelayTask(m_oRoutListStruct* pRoutList, m_oLogOutPutStruct* pLogOutPut);
// ����ʱͳ�������
// MatrixServerDll_API void GenTimeDelayTaskQueue(m_oRoutListStruct* pRoutList, m_oLogOutPutStruct* pLogOutPut);
// ADC���������߳̿�ʼ����
MatrixServerDll_API void OnADCSetThreadWork(int iOpt, m_oADCSetThreadStruct* pADCSetThread);
// ���ADC����������������
MatrixServerDll_API void OnClearADCSetMap(m_oLineListStruct* pLineList);
// ����������ADC��������������
MatrixServerDll_API void GetADCTaskQueueBySN(bool bADCStartSample, bool bADCStopSample, 
	m_oLineListStruct* pLineList, m_oLogOutPutStruct* pLogOutPut, m_oInstrumentStruct* pInstrument, int iOpt);
// �ж�·�ɷ������Ƿ��вɼ�վ
MatrixServerDll_API void GetADCTaskQueueByRout(bool bADCStartSample, bool bADCStopSample, 
	m_oLineListStruct* pLineList, m_oLogOutPutStruct* pLogOutPut, m_oRoutStruct* pRout, int iOpt);
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
// ��ADC���ݼ��뵽���񻺳���
MatrixServerDll_API void AddToADCDataBuf(unsigned int uiIP, unsigned int uiTime, double dPointTime, char* pBuf, 
	unsigned int uiLen, m_oADCDataRecThreadStruct* pADCDataRecThread);
// �������ݻص�����
// MatrixServerDll_API void GetProSampleDateCallBack(m_oADCDataRecThreadStruct* pADCDataRecThread, 
// 	ProSampleDateCallBack pCallBack);
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
// ��ʼ��SEGD�ļ���׼ͷ
MatrixServerDll_API void OnInitSegdSH(m_oSegdStandardHeaderStruct* pSegdSH);
// ��ʼ��SEGD�ļ����ݵ�ͷ
MatrixServerDll_API void OnInitSegdTH(m_oSegdTraceHeaderStruct* pSegdTH);
// ���浽Segd�ļ����ɹ�����true��ʧ�ܷ���false
MatrixServerDll_API bool SaveSegdFile(m_oSegdFileStruct* pSegdFileStruct);
MatrixServerDll_API void ProcessGeneralHeaderBlock1BackNew(FILE* pFile, m_oSegdFileStruct* pSegdFileStruct);
MatrixServerDll_API void ProcessGeneralHeaderBlock2BackNew(FILE* pFile, m_oSegdFileStruct* pSegdFileStruct);
MatrixServerDll_API void ProcessGeneralHeaderBlock3BackNew(FILE* pFile, m_oSegdFileStruct* pSegdFileStruct);
MatrixServerDll_API void ProcessScanTypeHeaderBackNew(FILE* pFile, int iChannel, m_oSegdFileStruct* pSegdFileStruct);
MatrixServerDll_API void ProcessExtendedHeaderBackNew(FILE* pFile, m_oSegdFileStruct* pSegdFileStruct);
MatrixServerDll_API void ProcessExternalHeaderBackNew(FILE* pFile, m_oSegdFileStruct* pSegdFileStruct);
MatrixServerDll_API void ProcessTraceHeaderBackNew(FILE* pFile, int iChannel, m_oSegdFileStruct* pSegdFileStruct);
MatrixServerDll_API void ProcessTraceHeaderExtensionBlock1BackNew(FILE* pFile, int iChannel, m_oSegdFileStruct* pSegdFileStruct);
MatrixServerDll_API void ProcessTraceHeaderExtensionBlock2BackNew(FILE* pFile, int iChannel, m_oSegdFileStruct* pSegdFileStruct);
MatrixServerDll_API void ProcessTraceHeaderExtensionBlock3BackNew(FILE* pFile, m_oSegdFileStruct* pSegdFileStruct);
MatrixServerDll_API void ProcessTraceHeaderExtensionBlock4BackNew(FILE* pFile, m_oSegdFileStruct* pSegdFileStruct);
MatrixServerDll_API void ProcessTraceHeaderExtensionBlock5BackNew(FILE* pFile, m_oSegdFileStruct* pSegdFileStruct);
MatrixServerDll_API void ProcessTraceHeaderExtensionBlock6BackNew(FILE* pFile, m_oSegdFileStruct* pSegdFileStruct);
MatrixServerDll_API void ProcessTraceHeaderExtensionBlock7BackNew(FILE* pFile, m_oSegdFileStruct* pSegdFileStruct);
MatrixServerDll_API void ProcessTraceDataBackNew(FILE* pFile, int iInstrNo, m_oSegdFileStruct* pSegdFileStruct);
MatrixServerDll_API int ReadInitToWriteSegdNew_BCD(FILE* pFile, int iCountByte, const char* pParameter);
MatrixServerDll_API int ReadInitToWriteSegdNew_BIN(FILE* pFile, int iCountByte, const char* pParameter);
MatrixServerDll_API void ReadInitToWriteSegdNew_BCD_addLow(FILE* pFile, int iCountByte, const char* pParameter, string strHigh);
MatrixServerDll_API void ReadInitToWriteSegdNew_BCD_addHigh(const char* pParameter, string* pstr);
MatrixServerDll_API void ReadInitToWriteSegdNew_FLOAT(FILE* pFile, int iCountByte, const char* pParameter);
MatrixServerDll_API void ReadInitToWriteSegdNew_DOUBLE(FILE* pFile, int iCountByte, const char* pParameter);
MatrixServerDll_API void ReadInitToWriteSegdNew_ASC(FILE* pFile, int iCountByte, const char* pParameter);
MatrixServerDll_API void ReadArrayToWriteSegdData_FLOAT(FILE* pFile, int iInstrNo, int iDataNo, m_oSegdFileStruct* pSegdFileStruct);
MatrixServerDll_API void ReadParameterToSegd_BIN(FILE* pFile, int iCountByte, int iValue);
MatrixServerDll_API void ReadParameterToSegd_BCD(FILE* pFile, int iCountByte, int iValue);
// �ر����е�ʩ���ļ�
// MatrixServerDll_API void CloseAllADCDataSaveInFile(m_oOptTaskArrayStruct* pOptTaskArray);
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
// ��������ʩ������������
MatrixServerDll_API void GenOptInstrMap(m_oLineListStruct* pLineList, m_oOptTaskArrayStruct* pOptTaskArray);
// ����һ��ʩ������
MatrixServerDll_API void GenOptTaskList(unsigned int uiStartOptNo, unsigned int uiOptNoInterval, unsigned int uiOptNum, 
	unsigned int uiTBWindow, unsigned int uiTSample, int iSampleRate, m_oOptTaskArrayStruct* pOptTaskArray, 
	m_oLineListStruct* pLineList, m_oConstVarStruct* pConstVar);
// �ͷ�һ��ʩ������
// MatrixServerDll_API void FreeOneOptTask(unsigned int uiIndex, m_oOptTaskArrayStruct* pOptTaskArray, m_oADCDataBufArrayStruct* pADCDataBufArray);
// ��SN����ADC�������ñ�־λ
MatrixServerDll_API void OnResetADCSetLableBySN(m_oInstrumentStruct* pInstrument, int iOpt);
// ��·������ADC�������ñ�־λ
MatrixServerDll_API void OnResetADCSetLableByRout(m_oRoutStruct* pRout, int iOpt);
// ����·�ɵ�ַ����ADC�������ñ�־λ
MatrixServerDll_API void OnSetADCByLAUXSN(int iLineIndex, int iPointIndex, int iDirection, int iOpt, 
	m_oEnvironmentStruct* pEnv, bool bOnly = true, bool bRout = true);
// ����ADC�������ñ�־λ
MatrixServerDll_API void OnResetADCSetLable(m_oRoutListStruct* pRoutList, int iOpt);
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
MatrixServerDll_API unsigned int OnWork(m_oEnvironmentStruct* pEnv);
// ֹͣ
MatrixServerDll_API void OnStop(m_oEnvironmentStruct* pEnv);
// �ͷ�ʵ����Դ
MatrixServerDll_API void OnFreeInstance(m_oEnvironmentStruct* pEnv);



#undef MatrixServerDll_API
#ifdef __cplusplus
}
#endif

#endif
