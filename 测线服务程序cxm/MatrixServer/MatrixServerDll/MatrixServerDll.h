// ���� ifdef ���Ǵ���ʹ�� DLL �������򵥵�
// ��ı�׼�������� DLL �е������ļ��������������϶���� MATRIXSERVERDLL_EXPORTS
// ���ű���ġ���ʹ�ô� DLL ��
// �κ�������Ŀ�ϲ�Ӧ����˷��š�������Դ�ļ��а������ļ����κ�������Ŀ���Ὣ
// MATRIXSERVERDLL_API ������Ϊ�Ǵ� DLL ����ģ����� DLL ���ô˺궨���
// ������Ϊ�Ǳ������ġ�

#include <list>
using std::list;
using std::string;
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
// ��INI�ļ��н����õ��ĳ���
typedef struct ConstVar_Struct
{
	//____֡��ʽ����____
	// ֡ͷ����
	int m_oFrameHeadSize;
	// ͬ��֡ͷ
	byte* m_pFrameHeadCheck;
	// �����ֳ���1�ֽ�
	int m_oFrameCmdSize1B;
	// ���������1�ֽ�
	int m_oFramePacketSize1B;
	// ���������2�ֽ�
	int m_oFramePacketSize2B;
	// ���������4�ֽ�
	int m_oFramePacketSize4B;
	// ADC������ռ�ֽ���
	int m_oADCDataSize3B;
	// �����ָ������ֵ
	int m_oCommandWordMaxNum;
	// 0x18�����������������ֽ���
	int m_oADCSetCommandMaxByte;
	// ����֡��������ֵ�趨
	byte m_oSndFrameBufInit;
	// ���յ���������֡֡����
	int m_oRcvFrameSize;
	// ���͵���������֡֡����
	int m_oSndFrameSize;
	//____���������豸����������____
	// ������������
	unsigned short m_oSendSetCmd;
	// ���Ͳ�ѯ����
	unsigned short m_oSendQueryCmd;
	// ����ADC���������ط�����
	unsigned short m_oSendADCCmd;
	// TB��ʼ�ɼ����ؿ�������(TB_L��8λ)
	unsigned int m_oCmdTBCtrl;
	// ����
	byte m_oCmdSn;
	// �װ�ʱ��
	byte m_oCmdHeadFrameTime;
	// ����IP��ַ
	byte m_oCmdLocalIPAddr;
	// ����ϵͳʱ��
	byte m_oCmdLocalSysTime;
	// ����ʱ��������λ
	byte m_oCmdLocalTimeFixedHigh;
	// ����ʱ��������λ
	byte m_oCmdLocalTimeFixedLow;
	// �Զ����ݷ��ص�ַ
	byte m_oCmdADCDataReturnAddr;
	// �Զ����ݷ��ض˿ں�����
	byte m_oCmdADCDataReturnPort;
	// �˿ڵ������޺�����
	byte m_oCmdADCDataReturnPortLimit;
	// ��������ȴ��˿ں�����
	byte m_oCmdSetBroadCastPort;
	// ϵͳӲ��״̬����
	byte m_oCmdFDUErrorCode;
	// TBʱ�̸�λ
	byte m_oCmdTBHigh;
	// TBʱ�̵�λ
	byte m_oCmdTbLow;
	// work_ctrl ����վ����
	byte m_oCmdLAUXRoutOpenQuery;
	// ·�ɿ���
	byte m_oCmdLAUXRoutOpenSet;
	// β������\����ʱ�̵�λ
	byte m_oCmdTailRecSndTimeLow;
	// �㲥����ȴ��˿�ƥ��
	byte m_oCmdBroadCastPortSet;
	// ����ADC��������������
	byte m_oCmdADCSet;
	// ����ʱ��
	byte m_oCmdNetTime;
	// ����վ����β������ʱ��
	byte m_oCmdLineTailRecTimeLAUX;
	// ����վ������β������ʱ��
	byte m_oCmdLAUTailRecTimeLAUX;
	// ����վ����1
	byte m_oCmdLAUXErrorCode1;
	// ����վ����2
	byte m_oCmdLAUXErrorCode2;
	// ����վ·�ɷ���
	byte m_oCmdLAUXSetRout;
	// ����·��
	byte m_oCmdReturnRout;
	// ���������������
	byte m_oCmdEnd;
}m_oConstVarStruct;
// ��XML�ļ��н����õ�����Ϣ
typedef struct InstrumentCommInfo_Struct
{
	/** XMLDOM�ļ�����*/
	CXMLDOMDocument m_oXMLDOMDocument;
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
	// �����豸����
	unsigned int m_uiInstrumentNum;
}m_oInstrumentCommInfoStruct;

// �̴߳����־λ�ṹ
typedef struct ThreadProcFlag_Struct
{
	// ��־λ����Դͬ������
	CRITICAL_SECTION m_oSecFlag;
	// ���������߳�ֹͣ��־λ
	bool m_bProcHeartBeatStop;
	// �װ������߳�ֹͣ��־λ
	bool m_bProcHeadFrameStop;
	// ����IP��ַ�����߳�ֹͣ��־λ
	bool m_bProcIPSetStop;
}m_oThreadProcFlagStruct;

// ���豸ͨѶ����������
typedef struct InstrumentCommand_Struct
{
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
	byte* m_pbyADCSet;
	// 0x18�������ݸ���
	unsigned short m_usADCSetNum;
}m_oInstrumentCommandStruct;
// ����
typedef struct HeartBeatFrame_Struct
{
	// ����֡��Դͬ������
	CRITICAL_SECTION m_oSecHeartBeat;
	// ����֡������
	byte* m_pbySndFrameData;
	// ���������ּ���
	byte* m_pbyCommandWord;
	// ���������ָ���
	unsigned short m_usCommandWordNum;
	// ����֡����
	m_oInstrumentCommandStruct m_oCommandStruct;
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
	byte* m_pbyRcvFrameData;
	// �װ�֡����
	m_oInstrumentCommandStruct m_oCommandStruct;
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
	byte* m_pbySndFrameData;
	// IP��ַ���������ּ���
	byte* m_pbyCommandWord;
	// IP��ַ���������ָ���
	unsigned short m_usCommandWordNum;
	// IP��ַ����֡����
	m_oInstrumentCommandStruct m_oCommandStructSet;
	// ����˿ڽ��ջ�������С
	unsigned int m_uiRcvBufferSize;
	// ����֡������
	byte* m_pbyRcvFrameData;
	// IP��ַ����Ӧ��֡����
	m_oInstrumentCommandStruct m_oCommandStructReturn;
	// IP��ַ����Socket�׽���
	SOCKET m_oIPSetFrameSocket;
}m_oIPSetFrameStruct;
// ��־����ṹ
typedef struct LogOutPut_Struct
{
	// ��־�����Դͬ������
	CRITICAL_SECTION m_oSecLogFile;
	// ��־����ļ�ָ��
	FILE* m_pFile;
	// ��־����ṹ
	list<string> m_oLogOutputList;
}m_oLogOutPutStruct;
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
	// �̴߳����־λ�ṹ
	m_oThreadProcFlagStruct* m_pThreadProcFlag;
	// ��־����ṹ
	m_oLogOutPutStruct* m_pLogOutPut;
}m_oEnvironmentStruct;


// ����ʵ����������ʵ��ָ��
typedef m_oEnvironmentStruct* (*Create_Instance)(void);
// �ͷ�ʵ����Դ
typedef void (*Free_Instance)(m_oEnvironmentStruct* pEnv);
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
typedef bool (*Get_FrameData)(SOCKET oSocket, byte* pFrameData);
// ����֡
typedef void (*Send_Frame)(SOCKET oSocket, byte* pFrameData, unsigned short usPort, unsigned int uiIP);

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