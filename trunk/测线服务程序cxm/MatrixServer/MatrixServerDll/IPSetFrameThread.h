#include "Thread.h"
#include "IPSetFrame.h"
#include "InstrumentList.h"
#ifdef MATRIXSERVERDLL_EXPORTS
#define MATRIXSERVERDLL_API __declspec(dllexport)
#define MatrixServerDll_API extern "C" __declspec(dllexport)
#else
#define MATRIXSERVERDLL_API __declspec(dllimport)
#define MatrixServerDll_API extern "C" __declspec(dllimport)
#endif

#ifndef   _IPSetFrameThread_H
#define   _IPSetFrameThread_H

// IP��ַ�����߳�
typedef struct IPSetFrameThread_Struct
{
	// �߳̽ṹ��ָ��
	m_oThreadStruct* m_pThread;
	// IP��ַ����ָ֡��
	m_oIPSetFrameStruct* m_pIPSetFrame;
	// �������нṹ��ָ��
	m_oInstrumentListStruct* m_pInstrumentList;
}m_oIPSetFrameThreadStruct;
#endif