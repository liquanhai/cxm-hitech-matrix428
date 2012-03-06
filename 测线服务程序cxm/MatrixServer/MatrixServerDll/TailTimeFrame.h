#include "CommandInfo.h"

#ifdef MATRIXSERVERDLL_EXPORTS
#define MATRIXSERVERDLL_API __declspec(dllexport)
#define MatrixServerDll_API extern "C" __declspec(dllexport)
#else
#define MATRIXSERVERDLL_API __declspec(dllimport)
#define MatrixServerDll_API extern "C" __declspec(dllimport)
#endif

#ifndef   _TailTimeFrame_H
#define   _TailTimeFrame_H
// β��ʱ��
typedef struct TailTimeFrame_Struct
{
	// β��ʱ��֡��Դͬ������
	CRITICAL_SECTION m_oSecTailTimeFrame;
	// ����˿ڽ��ջ�������С
	unsigned int m_uiRcvBufferSize;
	// ����֡������
	char* m_pcRcvFrameData;
	// β��ʱ��Ӧ��֡����
	m_oInstrumentCommandStruct* m_pCommandStructReturn;
	// ����˿ڷ��ͻ�������С
	unsigned int m_uiSndBufferSize;
	// ����֡������
	char* m_pcSndFrameData;
	// β��ʱ�̲�ѯ�����ּ���
	char* m_pcCommandWord;
	// β��ʱ�̲�ѯ�����ָ���
	unsigned short m_usCommandWordNum;
	// β��ʱ�̷���֡����
	m_oInstrumentCommandStruct* m_pCommandStructSet;
	// β��ʱ��Socket�׽���
	SOCKET m_oTailTimeFrameSocket;
}m_oTailTimeFrameStruct;
#endif