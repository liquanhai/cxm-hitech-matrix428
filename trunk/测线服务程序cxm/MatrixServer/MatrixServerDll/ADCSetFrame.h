#include "CommandInfo.h"

#ifdef MATRIXSERVERDLL_EXPORTS
#define MATRIXSERVERDLL_API __declspec(dllexport)
#define MatrixServerDll_API extern "C" __declspec(dllexport)
#else
#define MATRIXSERVERDLL_API __declspec(dllimport)
#define MatrixServerDll_API extern "C" __declspec(dllimport)
#endif

#ifndef   _ADCSetFrame_H
#define   _ADCSetFrame_H
// ADC��������
typedef struct ADCSetFrame_Struct
{
	// ADC��������֡��Դͬ������
	CRITICAL_SECTION m_oSecADCSetFrame;
	// ����˿ڽ��ջ�������С
	unsigned int m_uiRcvBufferSize;
	// ����֡������
	char* m_pcRcvFrameData;
	// ADC��������Ӧ��֡����
	m_oInstrumentCommandStruct* m_pCommandStructReturn;
	// ����˿ڷ��ͻ�������С
	unsigned int m_uiSndBufferSize;
	// ����֡������
	char* m_pcSndFrameData;
	// ADC�������������ּ���
	char* m_pcCommandWord;
	// ADC�������������ָ���
	unsigned short m_usCommandWordNum;
	// ADC�������÷���֡����
	m_oInstrumentCommandStruct* m_pCommandStructSet;
	// ADC��������Socket�׽���
	SOCKET m_oADCSetFrameSocket;
}m_oADCSetFrameStruct;
#endif