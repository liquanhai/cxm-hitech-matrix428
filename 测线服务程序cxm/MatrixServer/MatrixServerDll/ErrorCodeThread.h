#include "Thread.h"
#include "ErrorCodeFrame.h"
#include "InstrumentList.h"
#include "RoutList.h"
#include "LogOutPut.h"

#ifdef MATRIXSERVERDLL_EXPORTS
#define MATRIXSERVERDLL_API __declspec(dllexport)
#define MatrixServerDll_API extern "C" __declspec(dllexport)
#else
#define MATRIXSERVERDLL_API __declspec(dllimport)
#define MatrixServerDll_API extern "C" __declspec(dllimport)
#endif

#ifndef   _ErrorCodeThread_H
#define   _ErrorCodeThread_H

// �����ѯ�߳�
typedef struct ErrorCodeThread_Struct
{
	// �߳̽ṹ��ָ��
	m_oThreadStruct* m_pThread;
	// �����ѯָ֡��
	m_oErrorCodeFrameStruct* m_pErrorCodeFrame;
	// �������нṹ��ָ��
	m_oInstrumentListStruct* m_pInstrumentList;
	// ·�ɶ��нṹ��ָ��
	m_oRoutListStruct* m_pRoutList;
	// �����ѯ��־ָ��
	m_oLogOutPutStruct* m_pLogOutPutErrorCode;
}m_oErrorCodeThreadStruct;
#endif