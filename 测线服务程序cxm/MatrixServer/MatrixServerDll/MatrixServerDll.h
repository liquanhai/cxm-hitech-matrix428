// ���� ifdef ���Ǵ���ʹ�� DLL �������򵥵�
// ��ı�׼�������� DLL �е������ļ��������������϶���� MATRIXSERVERDLL_EXPORTS
// ���ű���ġ���ʹ�ô� DLL ��
// �κ�������Ŀ�ϲ�Ӧ����˷��š�������Դ�ļ��а������ļ����κ�������Ŀ���Ὣ
// MATRIXSERVERDLL_API ������Ϊ�Ǵ� DLL ����ģ����� DLL ���ô˺궨���
// ������Ϊ�Ǳ������ġ�
#include "..\\parameter\\Parameter.h"
#ifdef MATRIXSERVERDLL_EXPORTS
#define MATRIXSERVERDLL_API __declspec(dllexport)
#else
#define MATRIXSERVERDLL_API __declspec(dllimport)
#endif

#define MatrixServerDll_API extern "C" __declspec(dllexport)
// �����Ǵ� MatrixServerDll.dll ������
class MATRIXSERVERDLL_API CMatrixServerDll {
public:
	CMatrixServerDll(void);
	// TODO: �ڴ�������ķ�����
};

extern MATRIXSERVERDLL_API int nMatrixServerDll;

MATRIXSERVERDLL_API int fnMatrixServerDll(void);

// ��XML�ļ��н����õ�����Ϣ
typedef struct XML_InfoStruct
{
	// ��XML�еõ�����Ϣ���߳�ͬ������
	CCriticalSection m_oSecXML;
	// Դ��ַ
	CString m_csSrcIP;
	// Ŀ�ĵ�ַ,LCI��IP��ַ
	CString m_csDstIP;
	// Դ��ַ
	unsigned int m_uiSrcIP;
	// Ŀ�ĵ�ַ
	unsigned int m_uiDstIP;
	// Ŀ��IP��ַ�˿ں�
	unsigned int m_uiAimPort;
	// ����֡���ض˿�
	unsigned short m_usHeartBeatReturnPort;
	// �װ����ն˿�
	unsigned short m_usHeadFramePort;
	// IP��ַ���÷��ض˿�
	unsigned short m_usIPSetReturnPort;
}m_oXMLInfoStruct;

// �̴߳����־λ�ṹ
typedef struct ThreadProc_FlagStruct
{
	// ��־λ���߳�ͬ������
	CCriticalSection m_oSecFlag;
	// ���������߳�ֹͣ��־λ
	bool m_bProcHeartBeatStop;
	// �װ������߳�ֹͣ��־λ
	bool m_bProcHeadFrameStop;
	// ����IP��ַ�����߳�ֹͣ��־λ
	bool m_bProcIPSetStop;
}m_oThreadProcFlagStruct;

// ���豸ͨѶ����������
typedef struct Instrument_CommandStruct
{
	// Դ��ַ
	CString m_csSrcIP;
	// Ŀ�ĵ�ַ,LCI��IP��ַ
	CString m_csDstIP;
	// Դ��ַ
	unsigned int m_uiSrcIP;
	// Ŀ�ĵ�ַ
	unsigned int m_uiDstIP;
	// Ŀ��IP��ַ�˿ں�
	unsigned int m_uiAimPort;
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
	unsigned short m_usLocalTimeFixedLow;
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
	unsigned short m_usSetBroadCastPort;
	// �������ݴ������
	byte m_byFDUErrorCodeDataCount;
	// ����������
	byte m_byFDUErrorCodeCmdCount;
	// ʱ�䱨��״̬
	byte m_byTimeStatus;
	// ����״̬
	byte m_byCtrlStatus;
	// TBʱ�̸�λ
	unsigned int m_uiTBHigh;
	// TBʱ�̵�λ
	unsigned short m_usTBLow;
	// TB���ƣ�0x05����TB��0x06��AD�ɼ�����TB��0x00ֹͣAD��ad_ctrl(2)=1��LED����
	unsigned short m_usTBCtrl;
	// work_ctrl���ƽ���վ���պͷ�������ķ���
	// �ɸߵ���λÿλ�ֱ���Ʒ��Ϳڽ�����A��B������A��B�����ն˽�����A��B������A��B
	// =0Ϊ����=1Ϊ��
	byte m_byLAUXRoutOpenQuery;
	// ·�ɿ���
	// �ɸ�λ����λ�ֱ���ƿ�������A����������B��������A��������B
	// =0Ϊ����=1Ϊ��
	byte m_byLAUXRoutOpenSet;
	// β������\����ʱ�̵�λ//����վβ������ʱ�̣���14λ��Ч
	unsigned short m_usTailRecSndTimeLow;
	// �㲥����ȴ��˿�ƥ�䣬������ڵ�һ��������λ�ã�����0x0a�����е�16λ�˿�ƥ����ܽ��չ㲥����
	unsigned short m_usBroadCastPortSet;
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
	byte m_byLAUXErrorCodeDataLineACount;
	// ����վ����B���ݹ���
	byte m_byLAUXErrorCodeDataLineBCount;
	// ����վ������A���ݹ���
	byte m_byLAUXErrorCodeDataLAUXLineACount;
	// ����վ������B���ݹ���
	byte m_byLAUXErrorCodeDataLAUXLineBCount;
	// ����վ����ڹ���
	byte m_byLAUXErrorCodeCmdCount;
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
	byte m_byADCSet[ADCSetCommandMaxByte];
	// 0x18�������ݸ���
	unsigned short m_usADCSetNum;
}m_oInstrumentCommandStruct;
// ����
typedef struct HeartBeatFrameStruct
{
	// �����߳�ͬ������
	CCriticalSection m_oSecHeartBeat;
	// ����֡������
	byte m_bySndFrameData[SndFrameSize];
	// ���������ּ���
	byte m_byCommandWord[CommandWordMaxNum];
	// ���������ָ���
	unsigned short m_usCommandWordNum;
	// IP��ַ����֡����
	m_oInstrumentCommandStruct m_oCommandStruct;
}m_oHeartBeatFrameStruct;
// �װ�
typedef struct HeadFrameStruct
{
	// �װ��߳�ͬ������
	CCriticalSection m_oSecHeadFrame;
	// ����֡������
	byte m_byRcvFrameData[RcvFrameSize];
	// �װ�֡����
	m_oInstrumentCommandStruct m_oCommandStruct;
}m_oHeadFrameStruct;
// IP��ַ����
typedef struct IPSetFrameStruct
{
	// IP��ַ�����߳�ͬ������
	CCriticalSection m_oSecIPSetFrame;
	// ����֡������
	byte m_bySndFrameData[SndFrameSize];
	// IP��ַ���������ּ���
	byte m_byCommandWord[CommandWordMaxNum];
	// IP��ַ���������ָ���
	unsigned short m_usCommandWordNum;
	// IP��ַ����֡����
	m_oInstrumentCommandStruct m_oCommandStructSet;
	// ����֡������
	byte m_byRcvFrameData[RcvFrameSize];
	// IP��ַ����Ӧ��֡����
	m_oInstrumentCommandStruct m_oCommandStructReturn;
}m_oIPSetFrameStruct;
// �����ṹ��
typedef struct EnvironmentStruct
{
	// XML��Ϣ�ṹ
	m_oXMLInfoStruct m_oXMLInfo;
	// ����֡�ṹ
	m_oHeartBeatFrameStruct m_oHeartBeatFrame;
	// �װ�֡�ṹ
	m_oHeadFrameStruct m_oHeadFrame;
	// IP��ַ����֡�ṹ
	m_oIPSetFrameStruct m_oIPSetFrame;
	// �̴߳����־λ�ṹ
	m_oThreadProcFlagStruct m_oThreadProcFlag;


}m_oEnvironmentStruct;


// ����ʵ����������ʵ��ָ��
typedef m_oEnvironmentStruct* (*Create_Instance)(void);
// �ͷ�ʵ����Դ
typedef void (*Free_Instance)(m_oEnvironmentStruct* ptr);
// У�����豸ͨѶ֡��ͬ����
typedef bool (*Instrument_CheckFrameHead)(byte* pFrameData);
// ����֡��ͬ����
typedef void (*Instrument_MakeFrameHead)(byte* pFrameData);
// ����֡���ݽ�������
typedef void (*Instrument_ResetFramePacket)(m_oInstrumentCommandStruct* pCommand);
// �������豸ͨѶ����֡����
typedef bool (*Instrument_ParseFrame)(m_oInstrumentCommandStruct* pCommand, byte* pFrameData);
// �������豸ͨѶ֡
typedef void (*Instrument_MakeFrame)(m_oInstrumentCommandStruct* pCommand, byte* pFrameData);
// ����CSocket���ն˿ڲ��󶨶˿ں�IP��ַ,������ִ�г�ʼ����ģ�����ܴ�����ģ��˿�
typedef BOOL (*Instrument_CreateSocket)(m_oInstrumentCommandStruct* pCommand, CSocket* pCSocket);
// ���ù㲥ģʽ
typedef BOOL (*Instrument_SetSocketBroadCast)(CSocket* pCSocket);
// ���ö˿ڽ��ջ���������֡����
typedef BOOL (*Set_RcvBufferSize)(CSocket* pCSocket, int iFrameCount);
// ���ö˿ڷ��ͻ���������֡����
typedef BOOL (*Set_SndBufferSize)(CSocket* pCSocket, int iFrameCount);
// �õ�������ջ������յ���֡����
typedef DWORD (*Get_FrameCount)(CSocket* pCSocket);
// �õ�֡����
typedef BOOL (*Get_FrameData)(CSocket* pCSocket, byte* pFrameData);
// ����֡
typedef BOOL (*Send_Frame)(CSocket* pCSocket, byte* pFrameData, unsigned int uiPort, CString strIP);

// ��ʼ������
typedef void (*Instrument_InitHeartBeat)(m_oEnvironmentStruct* pEnv);
// ��ʼ���װ�
typedef void (*Instrument_InitHeadFrame)(m_oEnvironmentStruct* pEnv);
// ��ʼ��IP��ַ����
typedef void (*Instrument_InitIPSetFrame)(m_oEnvironmentStruct* pEnv);
// ��ʼ���̴߳����־λ
typedef void (*Init_ThreadProcFlag)(m_oEnvironmentStruct* pEnv);
// ��ʼ��ʵ��
typedef void (*Init_Instance)(m_oEnvironmentStruct* pEnv);

// �����װ�֡
typedef bool (*Instrument_ParseHeadFrame)(m_oEnvironmentStruct* pEnv);
// ����IP��ַ����Ӧ��֡
typedef bool (*Instrument_ParseIPSetReturnFrame)(m_oEnvironmentStruct* pEnv);
// ��������֡
typedef void (*Instrument_MakeHeartBeatFrame)(m_oEnvironmentStruct* pEnv);
// ����IP��ַ����֡
typedef void (*Instrument_MakeIPSetFrame)(m_oEnvironmentStruct* pEnv);