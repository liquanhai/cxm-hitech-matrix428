#include "CommandInfo.h"

#ifdef MATRIXSERVERDLL_EXPORTS
#define MATRIXSERVERDLL_API __declspec(dllexport)
#define MatrixServerDll_API extern "C" __declspec(dllexport)
#else
#define MATRIXSERVERDLL_API __declspec(dllimport)
#define MatrixServerDll_API extern "C" __declspec(dllimport)
#endif

#ifndef   _ErrorCodeFrame_H
#define   _ErrorCodeFrame_H
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
}m_oErrorCodeFrameStruct;

#endif