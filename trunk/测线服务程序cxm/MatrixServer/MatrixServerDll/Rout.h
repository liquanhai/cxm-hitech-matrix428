#include "Instrument.h"

#ifdef MATRIXSERVERDLL_EXPORTS
#define MATRIXSERVERDLL_API __declspec(dllexport)
#define MatrixServerDll_API extern "C" __declspec(dllexport)
#else
#define MATRIXSERVERDLL_API __declspec(dllimport)
#define MatrixServerDll_API extern "C" __declspec(dllimport)
#endif

#ifndef   _Rout_H
#define   _Rout_H
// ·�����Խṹ��
typedef struct Rout_Struct
{
	/** ��·�������е�λ��*/
	unsigned int m_uiIndex;
	/** ·���Ƿ�ʹ����*/
	bool m_bInUsed;
	/** ·��IP��ַ*/
	unsigned int m_uiRoutIP;
	/** ·�ɷ��� 1-�ϣ�2-�£�3-��4��*/
	int m_iRoutDirection;
	/** ·��ͷ����*/
	Instrument_Struct* m_pHead;
	/** ·��β����*/
	Instrument_Struct* m_pTail;
	/** ·��ʱ��*/
	unsigned int m_uiRoutTime;
	/** ·���Ƿ�Ϊ������·��*/
	bool m_bRoutLaux;
	/** ·���Ƿ���յ�ADC���ò���Ӧ��*/
	bool m_bADCSetReturn;
	// ·���Ƿ���ADC��������֡
	bool m_bADCSetRout;
	// ��·�ɷ����������ĸ���
	unsigned int m_uiInstrumentNum;
}m_oRoutStruct;
#endif