#include "Thread.h"
#include "ADCSetFrame.h"
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

#ifndef   _ADCSetThread_H
#define   _ADCSetThread_H

// ADC���������߳�
typedef struct ADCSetThread_Struct
{
	// �߳̽ṹ��ָ��
	m_oThreadStruct* m_pThread;
	// ADC��������ָ֡��
	m_oADCSetFrameStruct* m_pADCSetFrame;
	// �������нṹ��ָ��
	m_oInstrumentListStruct* m_pInstrumentList;
	// ·�ɶ��нṹ��ָ��
	m_oRoutListStruct* m_pRoutList;
	// ADC�����������
	unsigned int m_uiADCSetOperationNb;
	// ������
	unsigned int m_uiCounter;
	// ADC��ʼ���ݲɼ���־λ
	bool m_bADCStartSample;
	// ADCֹͣ���ݲɼ���־λ
	bool m_bADCStopSample;
	// ������ϵͳʱ��
	unsigned int m_uiLocalSysTime;
	// ��һ�ο�ʼ�����Ĳ���ʱ��
	unsigned int m_uiTBTimeOld;
	// ADC����������������
	unsigned int m_uiADCSetNum;
	// ADC��������Ӧ����������
	unsigned int m_uiADCSetReturnNum;
	// �����־ָ��
	m_oLogOutPutStruct* m_pLogOutPutADCFrameTime;
}m_oADCSetThreadStruct;
#endif