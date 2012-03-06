#include "Thread.h"
#include "ADCDataBufArray.h"
#include "OptTaskArray.h"
#ifdef MATRIXSERVERDLL_EXPORTS
#define MATRIXSERVERDLL_API __declspec(dllexport)
#define MatrixServerDll_API extern "C" __declspec(dllexport)
#else
#define MATRIXSERVERDLL_API __declspec(dllimport)
#define MatrixServerDll_API extern "C" __declspec(dllimport)
#endif

#ifndef   _ADCDataSaveThread_H
#define   _ADCDataSaveThread_H

// ʩ���������ݴ洢�߳�
typedef struct ADCDataSaveThread_Struct
{
	// �߳̽ṹ��ָ��
	m_oThreadStruct* m_pThread;
	// ���ݴ洢�������ṹ��ָ��
	m_oADCDataBufArrayStruct* m_pADCDataBufArray;
	// ʩ����������ṹ��ָ��
	m_oOptTaskArrayStruct* m_pOptTaskArray;
}m_oADCDataSaveThreadStruct;
#endif