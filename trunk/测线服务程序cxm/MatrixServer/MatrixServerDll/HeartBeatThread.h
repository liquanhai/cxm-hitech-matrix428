#include "Thread.h"
#include "HeartBeatFrame.h"
#ifdef MATRIXSERVERDLL_EXPORTS
#define MATRIXSERVERDLL_API __declspec(dllexport)
#define MatrixServerDll_API extern "C" __declspec(dllexport)
#else
#define MATRIXSERVERDLL_API __declspec(dllimport)
#define MatrixServerDll_API extern "C" __declspec(dllimport)
#endif

#ifndef   _HeartBeatThread_H
#define   _HeartBeatThread_H
// �����߳�
typedef struct HeartBeatThread_Struct
{
	// �߳̽ṹ��ָ��
	m_oThreadStruct* m_pThread;
	// ����ָ֡��
	m_oHeartBeatFrameStruct* m_pHeartBeatFrame;
}m_oHeartBeatThreadStruct;
#endif