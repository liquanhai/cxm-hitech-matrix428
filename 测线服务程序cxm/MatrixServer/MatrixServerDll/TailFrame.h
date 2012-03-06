#include "CommandInfo.h"
#ifdef MATRIXSERVERDLL_EXPORTS
#define MATRIXSERVERDLL_API __declspec(dllexport)
#define MatrixServerDll_API extern "C" __declspec(dllexport)
#else
#define MATRIXSERVERDLL_API __declspec(dllimport)
#define MatrixServerDll_API extern "C" __declspec(dllimport)
#endif

#ifndef   _TailFrame_H
#define   _TailFrame_H

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
}m_oTailFrameStruct;
#endif