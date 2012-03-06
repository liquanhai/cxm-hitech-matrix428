
#include "LogOutPut.h"
#ifdef MATRIXSERVERDLL_EXPORTS
#define MATRIXSERVERDLL_API __declspec(dllexport)
#define MatrixServerDll_API extern "C" __declspec(dllexport)
#else
#define MATRIXSERVERDLL_API __declspec(dllimport)
#define MatrixServerDll_API extern "C" __declspec(dllimport)
#endif

#ifndef    _ConstVar_H
#define    _ConstVar_H

// ini�����ļ����·��
#define INIFilePath					_T("..\\parameter\\MatrixServerDLL.ini")
// INI�ļ���ȡ�ؼ��ֻ�������С
#define INIFileStrBufSize			256
// ��INI�ļ��н����õ��ĳ���
typedef struct ConstVar_Struct
{
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
	int m_iIPBroadcastAddr;
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
	char* m_pFrameHeadCheck;
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
	char m_bySndFrameBufInit;
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
	char m_byCmdSn;
	// �װ�ʱ��
	char m_byCmdHeadFrameTime;
	// ����IP��ַ
	char m_byCmdLocalIPAddr;
	// ����ϵͳʱ��
	char m_byCmdLocalSysTime;
	// ����ʱ��������λ
	char m_byCmdLocalTimeFixedHigh;
	// ����ʱ��������λ
	char m_byCmdLocalTimeFixedLow;
	// �Զ����ݷ��ص�ַ
	char m_byCmdADCDataReturnAddr;
	// �Զ����ݷ��ض˿ں�����
	char m_byCmdADCDataReturnPort;
	// �˿ڵ������޺�����
	char m_byCmdADCDataReturnPortLimit;
	// ��������ȴ��˿ں�����
	char m_byCmdBroadCastPortSet;
	// ϵͳӲ��״̬����
	char m_byCmdFDUErrorCode;
	// TBʱ�̸�λ
	char m_byCmdTBHigh;
	// TBʱ�̵�λ
	char m_byCmdTbLow;
	// work_ctrl ����վ����
	char m_byCmdLAUXRoutOpenQuery;
	// ·�ɿ���
	char m_byCmdLAUXRoutOpenSet;
	// β������\����ʱ�̵�λ
	char m_byCmdTailRecSndTime;
	// �㲥����ȴ��˿�ƥ��
	char m_byCmdBroadCastPortSeted;
	// ����ADC��������������
	char m_byCmdADCSet;
	// ����ʱ��
	char m_byCmdNetTime;
	// ����վ����β������ʱ��
	char m_byCmdLineTailRecTimeLAUX;
	// ����վ������β������ʱ��
	char m_byCmdLAUTailRecTimeLAUX;
	// ����վ����1
	char m_byCmdLAUXErrorCode1;
	// ����վ����2
	char m_byCmdLAUXErrorCode2;
	// ����վ·�ɷ���
	char m_byCmdLAUXSetRout;
	// ����·��
	char m_byCmdReturnRout;
	// ���������������
	char m_byCmdEnd;

	//____ADC��������____
	// ADC�������Ҳ������С
	int m_iSetADCSetSineSize;
	// ADC�������Ҳ�����
	char* m_pSetADCSetSine;
	// ADC����ֹͣ���������С
	int m_iSetADCStopSampleSize;
	// ADC����ֹͣ��������
	char* m_pSetADCStopSample;
	// ADC���ô�TB��Դ��λ��С
	int m_iSetADCOpenTBPowerLowSize;
	// ADC���ô�TB��Դ��λ
	char* m_pSetADCOpenTBPowerLow;
	// ADC���ô�TB��Դ��λ��С
	int m_iSetADCOpenTBPowerHighSize;
	// ADC���ô�TB��Դ��λ
	char* m_pSetADCOpenTBPowerHigh;
	// ADC���ô�TB���ص�λ��С
	int m_iSetADCOpenSwitchTBLowSize;
	// ADC���ô�TB���ص�λ
	char* m_pSetADCOpenSwitchTBLow;
	// ADC���ô�TB���ظ�λ��С
	int m_iSetADCOpenSwitchTBHighSize;
	// ADC���ô�TB���ظ�λ
	char* m_pSetADCOpenSwitchTBHigh;
	// ADC���ö��Ĵ�����С
	int m_iSetADCRegisterReadSize;
	// ADC���ö��Ĵ���
	char* m_pSetADCRegisterRead;
	// ADC����д�Ĵ�����С
	int m_iSetADCRegisterWriteSize;
	// ADC����д�Ĵ���
	char* m_pSetADCRegisterWrite;
	// ADC���ô�TB���ش�С
	int m_iSetADCTBSwitchOpenSize;
	// ADC���ô�TB����
	char* m_pSetADCTBSwitchOpen;
	// ADC�������ô�С
	int m_iSetADCSampleSize;
	// ADC��������
	char* m_pSetADCSample;
	// ADC��������������С
	int m_iSetADCReadContinuousSize;
	// ADC������������
	char* m_pSetADCReadContinuous;
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

#endif