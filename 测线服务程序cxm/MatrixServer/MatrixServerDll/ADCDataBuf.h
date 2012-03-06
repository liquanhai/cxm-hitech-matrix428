
#ifdef MATRIXSERVERDLL_EXPORTS
#define MATRIXSERVERDLL_API __declspec(dllexport)
#define MatrixServerDll_API extern "C" __declspec(dllexport)
#else
#define MATRIXSERVERDLL_API __declspec(dllimport)
#define MatrixServerDll_API extern "C" __declspec(dllimport)
#endif

#ifndef   _ADCDataBuf_H
#define   _ADCDataBuf_H

// ���ݴ洢�������ṹ��
typedef struct ADCDataBuf_Struct
{
	// �������Ƿ�ʹ����
	bool m_bInUsed;
	// ADC���ݴ洢������
	int* m_pADCDataBuf;
	// ���ݴ洢֡��ţ���0��ʼ
	unsigned int m_uiFrameNb;
	// ��������SN
	unsigned int m_uiSN;
	// ֡�ı���ʱ��
	unsigned int m_uiSysTime;
	// ���������
	unsigned int m_uiIndex;
}m_oADCDataBufStruct;
#endif