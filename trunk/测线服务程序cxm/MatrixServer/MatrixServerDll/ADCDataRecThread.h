#include <map>
#include "Thread.h"
#include "ADCDataFrame.h"
#include "InstrumentList.h"
#include "LogOutPut.h"
#include "ADCDataBufArray.h"
#include "ADCLostFrame.h"
using std::map;

#ifdef MATRIXSERVERDLL_EXPORTS
#define MATRIXSERVERDLL_API __declspec(dllexport)
#define MatrixServerDll_API extern "C" __declspec(dllexport)
#else
#define MATRIXSERVERDLL_API __declspec(dllimport)
#define MatrixServerDll_API extern "C" __declspec(dllimport)
#endif

#ifndef   _ADCDataRecThread_H
#define   _ADCDataRecThread_H

// ADC���ݽ����߳�
typedef struct ADCDataRecThread_Struct
{
	// �߳̽ṹ��ָ��
	m_oThreadStruct* m_pThread;
	// �����ѯָ֡��
	m_oADCDataFrameStruct* m_pADCDataFrame;
	// �������нṹ��ָ��
	m_oInstrumentListStruct* m_pInstrumentList;
	// �����ѯ��־ָ��
	m_oLogOutPutStruct* m_pLogOutPutADCFrameTime;
	// ���ݴ洢�������ṹ��ָ��
	m_oADCDataBufArrayStruct* m_pADCDataBufArray;
	// ��һ֡�ı���ʱ��
	unsigned int m_uiADCDataFrameSysTime;
	// ���ļ�����֡������
	int m_iADCFrameCount;
	// ��֡������
	map<m_oADCLostFrameKeyStruct, m_oADCLostFrameStruct> m_oADCLostFrameMap;
}m_oADCDataRecThreadStruct;
#endif