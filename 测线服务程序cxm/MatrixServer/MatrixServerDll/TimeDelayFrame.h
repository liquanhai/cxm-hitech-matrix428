#include "CommandInfo.h"

#ifdef MATRIXSERVERDLL_EXPORTS
#define MATRIXSERVERDLL_API __declspec(dllexport)
#define MatrixServerDll_API extern "C" __declspec(dllexport)
#else
#define MATRIXSERVERDLL_API __declspec(dllimport)
#define MatrixServerDll_API extern "C" __declspec(dllimport)
#endif

#ifndef   _TimeDelayFrame_H
#define   _TimeDelayFrame_H
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
}m_oTimeDelayFrameStruct;

#endif