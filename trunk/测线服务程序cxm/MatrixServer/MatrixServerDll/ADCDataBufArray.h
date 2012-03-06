#include <list>
#include "ADCDataBuf.h"
using std::list;
#ifdef MATRIXSERVERDLL_EXPORTS
#define MATRIXSERVERDLL_API __declspec(dllexport)
#define MatrixServerDll_API extern "C" __declspec(dllexport)
#else
#define MATRIXSERVERDLL_API __declspec(dllimport)
#define MatrixServerDll_API extern "C" __declspec(dllimport)
#endif

#ifndef   _ADCDataBufArray_H
#define   _ADCDataBufArray_H

// ���ݴ洢�������ṹ��
typedef struct ADCDataBufArray_Struct
{
	// ��������Դͬ������
	CRITICAL_SECTION m_oSecADCDataBufArray;
	/** ����������ָ��*/
	m_oADCDataBufStruct* m_pArrayADCDataBuf;
	/** ����������*/
	list<m_oADCDataBufStruct*> m_olsADCDataBufFree;
	// д���ļ������ݻ���������
	list<m_oADCDataBufStruct*> m_olsADCDataToWrite;
	/** ����������*/
	unsigned int m_uiCountAll;
	/** ���л���������*/
	unsigned int m_uiCountFree;
}m_oADCDataBufArrayStruct;
#endif