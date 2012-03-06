#include "Thread.h"
#include "TailFrame.h"
#include "InstrumentList.h"
#include "RoutList.h"

#ifdef MATRIXSERVERDLL_EXPORTS
#define MATRIXSERVERDLL_API __declspec(dllexport)
#define MatrixServerDll_API extern "C" __declspec(dllexport)
#else
#define MATRIXSERVERDLL_API __declspec(dllimport)
#define MatrixServerDll_API extern "C" __declspec(dllimport)
#endif

#ifndef   _TailFrameThread_H
#define   _TailFrameThread_H

// β���߳�
typedef struct TailFrameThread_Struct
{
	// �߳̽ṹ��ָ��
	m_oThreadStruct* m_pThread;
	// β��ָ֡��
	m_oTailFrameStruct* m_pTailFrame;
	// �������нṹ��ָ��
	m_oInstrumentListStruct* m_pInstrumentList;
	// ·�ɶ��нṹ��ָ��
	m_oRoutListStruct* m_pRoutList;
}m_oTailFrameThreadStruct;

#endif
