#include "Thread.h"
#include "HeadFrame.h"
#include "InstrumentList.h"
#include "RoutList.h"
#ifdef MATRIXSERVERDLL_EXPORTS
#define MATRIXSERVERDLL_API __declspec(dllexport)
#define MatrixServerDll_API extern "C" __declspec(dllexport)
#else
#define MATRIXSERVERDLL_API __declspec(dllimport)
#define MatrixServerDll_API extern "C" __declspec(dllimport)
#endif

#ifndef   _HeadFrameThread_H
#define   _HeadFrameThread_H
// �װ��߳�
typedef struct HeadFrameThread_Struct
{
	// �߳̽ṹ��ָ��
	m_oThreadStruct* m_pThread;
	// �װ�ָ֡��
	m_oHeadFrameStruct* m_pHeadFrame;
	// �������нṹ��ָ��
	m_oInstrumentListStruct* m_pInstrumentList;
	// ·�ɶ��нṹ��ָ��
	m_oRoutListStruct* m_pRoutList;
}m_oHeadFrameThreadStruct;
#endif