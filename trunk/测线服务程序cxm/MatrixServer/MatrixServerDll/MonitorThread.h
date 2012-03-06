#include "Thread.h"
#include "InstrumentList.h"
#include "RoutList.h"
#include "ADCSetThread.h"
#include "TimeDelayThread.h"
#include "ErrorCodeThread.h"

#ifdef MATRIXSERVERDLL_EXPORTS
#define MATRIXSERVERDLL_API __declspec(dllexport)
#define MatrixServerDll_API extern "C" __declspec(dllexport)
#else
#define MATRIXSERVERDLL_API __declspec(dllimport)
#define MatrixServerDll_API extern "C" __declspec(dllimport)
#endif

#ifndef   _MonitorThread_H
#define   _MonitorThread_H
// ·�ɼ����߳�
typedef struct MonitorThread_Struct
{
	// �߳̽ṹ��ָ��
	m_oThreadStruct* m_pThread;
	// �������нṹ��ָ��
	m_oInstrumentListStruct* m_pInstrumentList;
	// ·�ɶ��нṹ��ָ��
	m_oRoutListStruct* m_pRoutList;
	// ʱͳ�߳�ָ��
	m_oTimeDelayThreadStruct* m_pTimeDelayThread;
	// ADC���������߳�
	m_oADCSetThreadStruct* m_pADCSetThread;
	// �����ѯ�߳�
	m_oErrorCodeThreadStruct* m_pErrorCodeThread;
}m_oMonitorThreadStruct;
#endif