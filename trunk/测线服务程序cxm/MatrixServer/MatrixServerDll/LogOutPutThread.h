#include "Thread.h"
#include "LogOutPut.h"
#ifdef MATRIXSERVERDLL_EXPORTS
#define MATRIXSERVERDLL_API __declspec(dllexport)
#define MatrixServerDll_API extern "C" __declspec(dllexport)
#else
#define MATRIXSERVERDLL_API __declspec(dllimport)
#define MatrixServerDll_API extern "C" __declspec(dllimport)
#endif

#ifndef   _LogOutPutThread_H
#define   _LogOutPutThread_H
// ��־����߳�
typedef struct LogOutPutThread_Struct
{
	// �߳̽ṹ��ָ��
	m_oThreadStruct* m_pThread;
	// �����־ָ��
	m_oLogOutPutStruct* m_pLogOutPutTimeDelay;
	// �����־ָ��
	m_oLogOutPutStruct* m_pLogOutPutErrorCode;
	// �����־ָ��
	m_oLogOutPutStruct* m_pLogOutPutADCFrameTime;
}m_oLogOutPutThreadStruct;
#endif