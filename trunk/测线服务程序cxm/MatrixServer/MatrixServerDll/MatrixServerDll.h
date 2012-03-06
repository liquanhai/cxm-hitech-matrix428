// ���� ifdef ���Ǵ���ʹ�� DLL �������򵥵�
// ��ı�׼�������� DLL �е������ļ��������������϶���� MATRIXSERVERDLL_EXPORTS
// ���ű���ġ���ʹ�ô� DLL ��
// �κ�������Ŀ�ϲ�Ӧ����˷��š�������Դ�ļ��а������ļ����κ�������Ŀ���Ὣ
// MATRIXSERVERDLL_API ������Ϊ�Ǵ� DLL ����ģ����� DLL ���ô˺궨���
// ������Ϊ�Ǳ������ġ�

#include <list>
#include <hash_map>
#include <map>
#include "Resource.h"

#include "LogOutPut.h"
#include "ConstVar.h"
#include "xml.h"
#include "InstrumentList.h"
#include "RoutList.h"
#include "HeartBeatFrame.h"
#include "HeadFrame.h"
#include "IPSetFrame.h"
#include "TailFrame.h"
#include "TailTimeFrame.h"
#include "TimeDelayFrame.h"
#include "ADCSetFrame.h"
#include "ErrorCodeFrame.h"
#include "ADCDataFrame.h"
#include "LogOutPutThread.h"
#include "HeartBeatThread.h"
#include "HeadFrameThread.h"
#include "IPSetFrameThread.h"
#include "TailFrameThread.h"
#include "TimeDelayThread.h"
#include "ADCSetThread.h"
#include "ErrorCodeThread.h"
#include "ADCDataRecThread.h"
#include "MonitorThread.h"
#include "ADCDataSaveThread.h"
using std::list;
using stdext::hash_map;
using std::map;
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