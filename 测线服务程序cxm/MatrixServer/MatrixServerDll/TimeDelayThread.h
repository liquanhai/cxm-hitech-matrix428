#include "Thread.h"
#include "TailTimeFrame.h"
#include "TimeDelayFrame.h"
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

#ifndef   _TimeDelayThread_H
#define   _TimeDelayThread_H
// ʱͳ�߳�
typedef struct TimeDelayThread_Struct
{
	// �߳̽ṹ��ָ��
	m_oThreadStruct* m_pThread;
	// β��ʱ��ָ֡��
	m_oTailTimeFrameStruct* m_pTailTimeFrame;
	// ʱͳ����ָ֡��
	m_oTimeDelayFrameStruct* m_pTimeDelayFrame;
	// �������нṹ��ָ��
	m_oInstrumentListStruct* m_pInstrumentList;
	// ·�ɶ��нṹ��ָ��
	m_oRoutListStruct* m_pRoutList;
	// ADC��ʼ���ݲɼ���־λ
	bool m_bADCStartSample;
	// ������
	unsigned int m_uiCounter;
	// �����־ָ��
	m_oLogOutPutStruct* m_pLogOutPutTimeDelay;
}m_oTimeDelayThreadStruct;
#endif