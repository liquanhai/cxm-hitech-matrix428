// ���� ifdef ���Ǵ���ʹ�� DLL �������򵥵�
// ��ı�׼�������� DLL �е������ļ��������������϶���� MATRIXSERVERDLL_EXPORTS
// ���ű���ġ���ʹ�ô� DLL ��
// �κ�������Ŀ�ϲ�Ӧ����˷��š�������Դ�ļ��а������ļ����κ�������Ŀ���Ὣ
// MATRIXSERVERDLL_API ������Ϊ�Ǵ� DLL ����ģ����� DLL ���ô˺궨���
// ������Ϊ�Ǳ������ġ�

#include <list>
#include <hash_map>
#include "Resource.h"
using std::list;
using stdext::hash_map;
using std::string;
#ifdef MATRIXSERVERDLL_EXPORTS
#define MATRIXSERVERDLL_API __declspec(dllexport)
#define MatrixServerDll_API extern "C" __declspec(dllexport)
#else
#define MATRIXSERVERDLL_API __declspec(dllimport)
#define MatrixServerDll_API extern "C" __declspec(dllimport)
#endif

// �����Ǵ� MatrixServerDll.dll ������
class MATRIXSERVERDLL_API CMatrixServerDll {
public:
	CMatrixServerDll(void);
	// TODO: �ڴ�������ķ�����
};

extern MATRIXSERVERDLL_API int nMatrixServerDll;

MATRIXSERVERDLL_API int fnMatrixServerDll(void);
// ini�����ļ����·��
#define INIFilePath					_T("..\\parameter\\MatrixServerDLL.ini")
// ������������XML�ļ����·��
#define CommXMLFilePath				_T("..\\parameter\\MatrixLineApp.XML")
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
#define ADCDataLogFolderPath	_T("\\��������")

// ���ѡ��:Debug�����Ϊ0��Release�����Ϊ1
#define OutPutSelect				0
// ���������־����
#define OutPutLogErrorLimit			100
// ��־�ļ������ļ������Ϣ����
#define OutPutLogFileInfoNumLimit	5000
// ��־�������
enum{LogType, WarningType, ErrorType, ExpandType};
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
	CString m_csSaveLogFilePath;
	// ��־�ļ����
	unsigned int m_uiLogFileNb;
	// ��־�ļ��洢��Ϣ��������
	unsigned int m_uiLogInfoCount;
}m_oLogOutPutStruct;
// ��INI�ļ��н����õ��ĳ���
typedef struct ConstVar_Struct
{
	//____��������____
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
// ��XML�ļ��н����õ�����Ϣ
typedef struct InstrumentCommInfo_Struct
{
	/** XMLDOM�ļ�����*/
	CXMLDOMDocument m_oXMLDOMDocument;
	// Դ��ַ
	unsigned int m_uiSrcIP;
	// LCI��IP��ַ
	unsigned int m_uiAimIP;
	// �Զ����ݷ��ص�ַ
	unsigned int m_uiADCDataReturnAddr;
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
	// �����豸����
	unsigned int m_uiInstrumentNum;
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
	char m_byFDUErrorCodeDataCount;
	// ����������
	char m_byFDUErrorCodeCmdCount;
	// ʱ�䱨��״̬
	char m_byTimeStatus;
	// ����״̬
	char m_byCtrlStatus;
	// TBʱ�̸�λ
	unsigned int m_uiTBHigh;
	// TBʱ�̵�λ
	unsigned short m_usTBLow;
	// TB���ƣ�0x05����TB��0x06��AD�ɼ�����TB��0x00ֹͣAD��ad_ctrl(2)=1��LED����
	unsigned short m_usTBCtrl;
	// work_ctrl���ƽ���վ���պͷ�������ķ���
	// �ɸߵ���λÿλ�ֱ���Ʒ��Ϳڽ�����A��B������A��B�����ն˽�����A��B������A��B
	// =0Ϊ����=1Ϊ��
	char m_byLAUXRoutOpenQuery;
	// ·�ɿ���
	// �ɸ�λ����λ�ֱ���ƿ�������A����������B��������A��������B
	// =0Ϊ����=1Ϊ��
	char m_byLAUXRoutOpenSet;
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
	char m_byLAUXErrorCodeDataLineACount;
	// ����վ����B���ݹ���
	char m_byLAUXErrorCodeDataLineBCount;
	// ����վ������A���ݹ���
	char m_byLAUXErrorCodeDataLAUXLineACount;
	// ����վ������B���ݹ���
	char m_byLAUXErrorCodeDataLAUXLineBCount;
	// ����վ����ڹ���
	char m_byLAUXErrorCodeCmdCount;
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
	char* m_pcADCSet;
	// 0x18�������ݸ���
	int m_iADCSetNum;
}m_oInstrumentCommandStruct;

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
	byte m_byLAUXRoutOpenSet;
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
// 	/** β��ʱ��*/
// 	unsigned int m_uiTailSysTime;
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
	int m_iLineNb;
	/** ����*/
	int m_iPointIndex;
	/** ��ǵ��*/
	unsigned int m_uiPointNb;
	// 	/** ���*/
	// 	unsigned int m_uiChannelNb;
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
	// �װ�λ���ȶ�����
	int m_iHeadFrameStableNum;
	/** �ڼ�������IP��ַ*/
	int m_iIPSetCount;
	/** IP��ַ�����Ƿ�ɹ�*/
	bool m_bIPSetOK;
	// 	/** �ڼ���β��ʱ�̲�ѯ*/
	// 	int m_iTailTimeQueryCount;
	/** β��ʱ�̲�ѯ�Ƿ�ɹ�*/
	bool m_bTailTimeQueryOK;
	/** ����ʱ��������λ*/
	unsigned int m_uiTimeHigh;
	/** ����ʱ��������λ*/
	unsigned int m_uiTimeLow;
	/** �ڼ�����������ʱ��*/
	int m_iTimeSetCount;
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
}m_oInstrumentStruct;
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
	// ����ϵͳ�����仯��ʱ��
	ULONGLONG m_ullLineChangeTime;
	// ����״̬�ɲ��ȶ���Ϊ�ȶ�
	bool m_bLineStableChange;
	/** ��������*/
	unsigned int m_uiCountAll;
	/** ������������*/
	unsigned int m_uiCountFree;
	// �����־ָ��
	m_oLogOutPutStruct* m_pLogOutPut;
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
	Instrument_Struct* m_pHead;
	/** ·��β����*/
	Instrument_Struct* m_pTail;
	/** ·��ʱ��*/
	ULONGLONG m_ullRoutTime;
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
	// �����־ָ��
	m_oLogOutPutStruct* m_pLogOutPut;
}m_oRoutListStruct;
// ����
typedef struct HeartBeatFrame_Struct
{
	// ����֡��Դͬ������
	CRITICAL_SECTION m_oSecHeartBeat;
	// ����֡������
	char* m_pcSndFrameData;
	// ���������ּ���
	char* m_pcCommandWord;
	// ���������ָ���
	unsigned short m_usCommandWordNum;
	// ����֡����
	m_oInstrumentCommandStruct* m_pCommandStruct;
	// ����Socket�׽���
	SOCKET m_oHeartBeatSocket;
	// �����־ָ��
	m_oLogOutPutStruct* m_pLogOutPut;
}m_oHeartBeatFrameStruct;

// �װ�
typedef struct HeadFrame_Struct
{
	// �װ�֡��Դͬ������
	CRITICAL_SECTION m_oSecHeadFrame;
	// ����˿ڽ��ջ�������С
	unsigned int m_uiRcvBufferSize;
	// ����֡������
	char* m_pcRcvFrameData;
	// �װ�֡����
	m_oInstrumentCommandStruct* m_pCommandStruct;
	// �װ�Socket�׽���
	SOCKET m_oHeadFrameSocket;
	// �����־ָ��
	m_oLogOutPutStruct* m_pLogOutPut;
}m_oHeadFrameStruct;

// IP��ַ����
typedef struct IPSetFrame_Struct
{
	// IP��ַ����֡��Դͬ������
	CRITICAL_SECTION m_oSecIPSetFrame;
	// ����˿ڷ��ͻ�������С
	unsigned int m_uiSndBufferSize;
	// ����֡������
	char* m_pcSndFrameData;
	// IP��ַ���������ּ���
	char* m_pcCommandWord;
	// IP��ַ���������ָ���
	unsigned short m_usCommandWordNum;
	// IP��ַ����֡����
	m_oInstrumentCommandStruct* m_pCommandStructSet;
	// ����˿ڽ��ջ�������С
	unsigned int m_uiRcvBufferSize;
	// ����֡������
	char* m_pcRcvFrameData;
	// IP��ַ����Ӧ��֡����
	m_oInstrumentCommandStruct* m_pCommandStructReturn;
	// IP��ַ����Socket�׽���
	SOCKET m_oIPSetFrameSocket;
	// �����־ָ��
	m_oLogOutPutStruct* m_pLogOutPut;
}m_oIPSetFrameStruct;
// β��
typedef struct TailFrame_Struct
{
	// β��֡��Դͬ������
	CRITICAL_SECTION m_oSecTailFrame;
	// ����˿ڽ��ջ�������С
	unsigned int m_uiRcvBufferSize;
	// ����֡������
	char* m_pcRcvFrameData;
	// β��֡����
	m_oInstrumentCommandStruct* m_pCommandStruct;
	// β��Socket�׽���
	SOCKET m_oTailFrameSocket;
	// �����־ָ��
	m_oLogOutPutStruct* m_pLogOutPut;
}m_oTailFrameStruct;
// β��ʱ��
typedef struct TailTimeFrame_Struct
{
	// β��ʱ��֡��Դͬ������
	CRITICAL_SECTION m_oSecTailTimeFrame;
	// ����˿ڽ��ջ�������С
	unsigned int m_uiRcvBufferSize;
	// ����֡������
	char* m_pcRcvFrameData;
	// β��ʱ��Ӧ��֡����
	m_oInstrumentCommandStruct* m_pCommandStructReturn;
	// ����˿ڷ��ͻ�������С
	unsigned int m_uiSndBufferSize;
	// ����֡������
	char* m_pcSndFrameData;
	// β��ʱ�̲�ѯ�����ּ���
	char* m_pcCommandWord;
	// β��ʱ�̲�ѯ�����ָ���
	unsigned short m_usCommandWordNum;
	// β��ʱ�̷���֡����
	m_oInstrumentCommandStruct* m_pCommandStructSet;
	// β��ʱ��Socket�׽���
	SOCKET m_oTailTimeFrameSocket;
	// �����־ָ��
	m_oLogOutPutStruct* m_pLogOutPut;
}m_oTailTimeFrameStruct;

// ʱͳ����
typedef struct TimeDelayFrame_Struct
{
	// ʱͳ����֡��Դͬ������
	CRITICAL_SECTION m_oSecTimeDelayFrame;
	// ����˿ڽ��ջ�������С
	unsigned int m_uiRcvBufferSize;
	// ����֡������
	char* m_pcRcvFrameData;
	// ʱͳ����Ӧ��֡����
	m_oInstrumentCommandStruct* m_pCommandStructReturn;
	// ����˿ڷ��ͻ�������С
	unsigned int m_uiSndBufferSize;
	// ����֡������
	char* m_pcSndFrameData;
	// ʱͳ���������ּ���
	char* m_pcCommandWord;
	// ʱͳ���������ָ���
	unsigned short m_usCommandWordNum;
	// ʱͳ���÷���֡����
	m_oInstrumentCommandStruct* m_pCommandStructSet;
	// ʱͳ����Socket�׽���
	SOCKET m_oTimeDelayFrameSocket;
	// �����־ָ��
	m_oLogOutPutStruct* m_pLogOutPut;
}m_oTimeDelayFrameStruct;
// ADC��������
typedef struct ADCSetFrame_Struct
{
	// ADC��������֡��Դͬ������
	CRITICAL_SECTION m_oSecADCSetFrame;
	// ����˿ڽ��ջ�������С
	unsigned int m_uiRcvBufferSize;
	// ����֡������
	char* m_pcRcvFrameData;
	// ADC��������Ӧ��֡����
	m_oInstrumentCommandStruct* m_pCommandStructReturn;
	// ����˿ڷ��ͻ�������С
	unsigned int m_uiSndBufferSize;
	// ����֡������
	char* m_pcSndFrameData;
	// ADC�������������ּ���
	char* m_pcCommandWord;
	// ADC�������������ָ���
	unsigned short m_usCommandWordNum;
	// ADC�������÷���֡����
	m_oInstrumentCommandStruct* m_pCommandStructSet;
	// ADC��������Socket�׽���
	SOCKET m_oADCSetFrameSocket;
	// �����־ָ��
	m_oLogOutPutStruct* m_pLogOutPut;
}m_oADCSetFrameStruct;
// �����ѯ
typedef struct ErrorCodeFrame_Struct
{
	// ADC��������֡��Դͬ������
	CRITICAL_SECTION m_oSecErrorCodeFrame;
	// ����˿ڽ��ջ�������С
	unsigned int m_uiRcvBufferSize;
	// ����֡������
	char* m_pcRcvFrameData;
	// Ӧ��֡����
	m_oInstrumentCommandStruct* m_pCommandStructReturn;
	// ����˿ڷ��ͻ�������С
	unsigned int m_uiSndBufferSize;
	// ����֡������
	char* m_pcSndFrameData;
	// �����ѯ�����ּ���
	char* m_pcCommandWord;
	// �����ѯ�����ָ���
	unsigned short m_usCommandWordNum;
	// ����֡����
	m_oInstrumentCommandStruct* m_pCommandStructSet;
	// �����ѯSocket�׽���
	SOCKET m_oErrorCodeFrameSocket;
	// �����־ָ��
	m_oLogOutPutStruct* m_pLogOutPut;
}m_oErrorCodeFrameStruct;
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
	// �߳̽ṹ��ָ��
	m_oThreadStruct* m_pThread;
	// ����ָ֡��
	m_oHeartBeatFrameStruct* m_pHeartBeatFrame;
}m_oHeartBeatThreadStruct;
// �װ��߳�
typedef struct HeadFrameThread_Struct
{
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
	// �߳̽ṹ��ָ��
	m_oThreadStruct* m_pThread;
	// IP��ַ����ָ֡��
	m_oIPSetFrameStruct* m_pIPSetFrame;
	// �������нṹ��ָ��
	m_oInstrumentListStruct* m_pInstrumentList;
}m_oIPSetFrameThreadStruct;
// β���߳�
typedef struct TailFrameThread_Struct
{
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
	// β����ѯ֡��ѯ����������
	unsigned int m_uiTailTimeQueryNum;
	// β����ѯ֡Ӧ�����
	unsigned int m_uiTailTimeReturnNum;
	// ʱͳ����֡����
	unsigned int m_uiTimeDelaySetNum;
	// ʱͳ����Ӧ��֡����
	unsigned int m_uiTimeDelayReturnNum;
	// �����־ָ��
	m_oLogOutPutStruct* m_pLogOutPutTimeDelay;
}m_oTimeDelayThreadStruct;
// ADC���������߳�
typedef struct ADCSetThread_Struct
{
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
	// ADC����������������
	unsigned int m_uiADCSetNum;
	// ADC��������Ӧ����������
	unsigned int m_uiADCSetReturnNum;
}m_oADCSetThreadStruct;
// �����ѯ�߳�
typedef struct ErrorCodeThread_Struct
{
	// �߳̽ṹ��ָ��
	m_oThreadStruct* m_pThread;
	// �����ѯָ֡��
	m_oErrorCodeFrameStruct* m_pErrorCodeFrame;
	// ·�ɶ��нṹ��ָ��
	m_oRoutListStruct* m_pRoutList;
	// ������
	unsigned int m_uiCounter;
	// �����ѯ��־ָ��
	m_oLogOutPutStruct* m_pLogOutPutErrorCode;
}m_oErrorCodeThreadStruct;
// ·�ɼ����߳�
typedef struct MonitorThread_Struct
{
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
}m_oEnvironmentStruct;


// ����ʵ����������ʵ��ָ��
typedef m_oEnvironmentStruct* (*Create_Instance)(void);
// �ͷ�ʵ����Դ
typedef void (*Free_Instance)(m_oEnvironmentStruct* pEnv);
// У�����豸ͨѶ֡��ͬ����
typedef bool (*Instrument_CheckFrameHead)(char* pFrameData);
// ����֡��ͬ����
typedef void (*Instrument_MakeFrameHead)(char* pFrameData);
// ����֡���ݽ�������
typedef void (*Instrument_ResetFramePacket)(m_oInstrumentCommandStruct* pCommand);
// �������豸ͨѶ����֡����
typedef bool (*Instrument_ParseFrame)(m_oInstrumentCommandStruct* pCommand, char* pFrameData);
// �������豸ͨѶ֡
typedef void (*Instrument_MakeFrame)(m_oInstrumentCommandStruct* pCommand, char* pFrameData);
// ����CSocket���ն˿ڲ��󶨶˿ں�IP��ַ,������ִ�г�ʼ����ģ�����ܴ�����ģ��˿�
typedef SOCKET (*Instrument_CreateSocket)(unsigned short usPort, unsigned int uiIP);
// ���ù㲥ģʽ
typedef void (*Instrument_SetSocketBroadCast)(SOCKET oSocket);
// ���ö˿ڽ��ջ���������֡����
typedef void (*Set_RcvBufferSize)(SOCKET oSocket, int iFrameCount);
// ���ö˿ڷ��ͻ���������֡����
typedef void (*Set_SndBufferSize)(SOCKET oSocket, int iFrameCount);
// �õ�������ջ������յ���֡����
typedef DWORD (*Get_FrameCount)(SOCKET oSocket);
// �õ�֡����
typedef bool (*Get_FrameData)(SOCKET oSocket, char* pFrameData);
// ����֡
typedef void (*Send_Frame)(SOCKET oSocket, char* pFrameData, unsigned short usPort, unsigned int uiIP);

// ����������Ϣ�ṹ��
typedef void (*Create_ConstVar)(m_oEnvironmentStruct* pEnv);
// ��ʼ��������Ϣ�ṹ��
typedef void (*Init_ConstVar)(m_oEnvironmentStruct* pEnv);
// �ͷų�����Ϣ�ṹ��
typedef void (*Free_ConstVar)(m_oEnvironmentStruct* pEnv);
// ��������ͨѶ��Ϣ�ṹ��
typedef void (*Instrument_CreateCommInfo)(m_oEnvironmentStruct* pEnv);
// ��ʼ������ͨѶ��Ϣ�ṹ��
typedef void (*Instrument_InitCommInfo)(m_oEnvironmentStruct* pEnv);
// �ͷ�����ͨѶ��Ϣ�ṹ��
typedef void (*Instrument_FreeCommInfo)(m_oEnvironmentStruct* pEnv);
// ��������֡��Ϣ�ṹ��
typedef void (*Instrument_CreateHeartBeat)(m_oEnvironmentStruct* pEnv);
// ��ʼ������
typedef void (*Instrument_InitHeartBeat)(m_oEnvironmentStruct* pEnv);
// �ͷ�����֡��Ϣ�ṹ��
typedef void (*Instrument_FreeHeartBeat)(m_oEnvironmentStruct* pEnv);
// �����װ�֡��Ϣ�ṹ��
typedef void (*Instrument_CreateHeadFrame)(m_oEnvironmentStruct* pEnv);
// ��ʼ���װ�
typedef void (*Instrument_InitHeadFrame)(m_oEnvironmentStruct* pEnv);
// �ͷ��װ�֡��Ϣ�ṹ��
typedef void (*Instrument_FreeHeadFrame)(m_oEnvironmentStruct* pEnv);
// ����IP��ַ����֡��Ϣ�ṹ��
typedef void (*Instrument_CreateIPSetFrame)(m_oEnvironmentStruct* pEnv);
// ��ʼ��IP��ַ����
typedef void (*Instrument_InitIPSetFrame)(m_oEnvironmentStruct* pEnv);
// �ͷ�IP��ַ����֡��Ϣ�ṹ��
typedef void (*Instrument_FreeIPSetFrame)(m_oEnvironmentStruct* pEnv);
// �����̴߳����־λ��Ϣ�ṹ��
typedef void (*Create_ThreadProcFlag)(m_oEnvironmentStruct* pEnv);
// ��ʼ���̴߳����־λ
typedef void (*Init_ThreadProcFlag)(m_oEnvironmentStruct* pEnv);
// �ͷ��̴߳����־λ��Ϣ�ṹ��
typedef void (*Free_ThreadProcFlag)(m_oEnvironmentStruct* pEnv);
// ���������������˿�
typedef void (*CreateAndSet_HeartBeatSocket)(m_oEnvironmentStruct* pEnv);
// �����������װ��˿�
typedef void (*CreateAndSet_HeadFrameSocket)(m_oEnvironmentStruct* pEnv);
// ����������IP��ַ���ö˿�
typedef void (*CreateAndSet_IPSetFrameSocket)(m_oEnvironmentStruct* pEnv);

// ��ʼ��ʵ��
// ������
// ��������ʼ������ͨѶ��Ϣ�ṹ��
// ��������ʼ������֡��Ϣ�ṹ��
// ��������ʼ���װ�֡��Ϣ�ṹ��
// ��������ʼ��IP��ַ����֡��Ϣ�ṹ��
// ��������ʼ���̴߳����־λ��Ϣ�ṹ��
// ���������������˿�
// �����������װ��˿�
// ����������IP��ַ���ö˿�
typedef void (*Init_Instance)(m_oEnvironmentStruct* pEnv);
typedef void (*On_Init)(m_oEnvironmentStruct* pEnv);
typedef void (*On_Work)(m_oEnvironmentStruct* pEnv);
typedef void (*On_Stop)(m_oEnvironmentStruct* pEnv);
typedef void (*On_Close)(m_oEnvironmentStruct* pEnv);
typedef void (*On_StartSample)(m_oEnvironmentStruct* pEnv);
typedef void (*On_StopSample)(m_oEnvironmentStruct* pEnv);
// �����װ�֡
typedef bool (*Instrument_ParseHeadFrame)(m_oEnvironmentStruct* pEnv);
// ����IP��ַ����Ӧ��֡
typedef bool (*Instrument_ParseIPSetReturnFrame)(m_oEnvironmentStruct* pEnv);
// ��������֡
typedef void (*Instrument_MakeHeartBeatFrame)(m_oEnvironmentStruct* pEnv);
// ����IP��ַ����֡
typedef void (*Instrument_MakeIPSetFrame)(m_oEnvironmentStruct* pEnv);

// ����־��Ϣ���뵽��־�ļ��������
typedef void (*Add_LogFileOutPutList)(int iType, unsigned int uiErrorCodeNb, string strFuncName, string strLogInfo);