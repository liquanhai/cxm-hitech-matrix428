#include "CommandInfo.h"
#ifdef MATRIXSERVERDLL_EXPORTS
#define MATRIXSERVERDLL_API __declspec(dllexport)
#define MatrixServerDll_API extern "C" __declspec(dllexport)
#else
#define MATRIXSERVERDLL_API __declspec(dllimport)
#define MatrixServerDll_API extern "C" __declspec(dllimport)
#endif

#ifndef   _IPSetFrame_H
#define   _IPSetFrame_H

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
}m_oIPSetFrameStruct;
#endif