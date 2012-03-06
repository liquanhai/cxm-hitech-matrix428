#include "CommandInfo.h"
#ifdef MATRIXSERVERDLL_EXPORTS
#define MATRIXSERVERDLL_API __declspec(dllexport)
#define MatrixServerDll_API extern "C" __declspec(dllexport)
#else
#define MATRIXSERVERDLL_API __declspec(dllimport)
#define MatrixServerDll_API extern "C" __declspec(dllimport)
#endif

#ifndef   _HeartBeatFrame_H
#define   _HeartBeatFrame_H

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
}m_oHeartBeatFrameStruct;

#endif