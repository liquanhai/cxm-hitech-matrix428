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

// ���豸ͨѶ����������
typedef struct Instrument_Command
{
	// ����֡������
	byte m_byRcvFrameData[RcvFrameSize];
	// ����֡������
	byte m_bySndFrameData[SndFrameSize];
	// Դ��ַ
	unsigned int m_uiSrcIP;
	// Ŀ�ĵ�ַ
	unsigned int m_uiDstIP;
	// �˿�
	unsigned short m_usAimPort;
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
}m_oInstrumentCommand;
// �װ�
typedef struct HeadFrame
{
	// Դ��ַ
	CString m_csSrcIP;
	// �װ�֡����
	m_oInstrumentCommand m_oHeadFrameCommand;
}m_oHeadFrame;
// IP��ַ����
typedef struct IPSetFrame
{
	// Դ��ַ
	CString m_csSrcIP;
	// Ŀ�ĵ�ַ
	CString m_csDstIP;
	// IP��ַ����֡����
	m_oInstrumentCommand m_oIPSetFrameCommand;
}m_oIPSetFrame;
// IP��ַ����Ӧ��
typedef struct IPSetReturnFrame
{
	// Դ��ַ
	CString m_csSrcIP;
	// IP��ַ����֡����
	m_oInstrumentCommand m_oIPSetReturnFrameCommand;
}m_oIPSetReturnFrame;
// У�����豸ͨѶ֡��ͬ����
typedef bool (*pCheckInstrumentFrameHead)(byte* pFrameData);
// ����֡���ݽ�������
typedef void (*pResetInstrumentFrame)(m_oInstrumentCommand* pCommand);
// �������豸ͨѶ����֡����
typedef bool (*pParseInstrumentFrame)(m_oInstrumentCommand* pCommand);