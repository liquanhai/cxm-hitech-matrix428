#include "CommandInfo.h"
#ifdef MATRIXSERVERDLL_EXPORTS
#define MATRIXSERVERDLL_API __declspec(dllexport)
#define MatrixServerDll_API extern "C" __declspec(dllexport)
#else
#define MATRIXSERVERDLL_API __declspec(dllimport)
#define MatrixServerDll_API extern "C" __declspec(dllimport)
#endif

#ifndef   _HeadFrame_H
#define   _HeadFrame_H
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
}m_oHeadFrameStruct;
#endif