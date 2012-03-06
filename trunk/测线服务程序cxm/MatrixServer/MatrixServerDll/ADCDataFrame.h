#include "CommandInfo.h"

#ifdef MATRIXSERVERDLL_EXPORTS
#define MATRIXSERVERDLL_API __declspec(dllexport)
#define MatrixServerDll_API extern "C" __declspec(dllexport)
#else
#define MATRIXSERVERDLL_API __declspec(dllimport)
#define MatrixServerDll_API extern "C" __declspec(dllimport)
#endif

#ifndef   _ADCDataFrame_H
#define   _ADCDataFrame_H
// ADC���ݽ���
typedef struct ADCDataFrame_Struct
{
	// ADC���ݽ���֡��Դͬ������
	CRITICAL_SECTION m_oSecADCDataFrame;
	// ����˿ڽ��ջ�������С
	unsigned int m_uiRcvBufferSize;
	// ����֡������
	char* m_pcRcvFrameData;
	// Ӧ��֡����
	m_oInstrumentCommandStruct* m_pCommandStructReturn;
	// ����˿ڷ��ͻ�������С
	unsigned int m_uiSndBufferSize;
	// ����֡������
	char* m_pcSndFrameData;
	// ����֡����
	m_oInstrumentCommandStruct* m_pCommandStructSet;
	// ADC���ݽ��պ��ط�Socket�׽���
	SOCKET m_oADCDataFrameSocket;
}m_oADCDataFrameStruct;
#endif