
#include <list>
#include <hash_map>
#include "Instrument.h"
using std::list;
using stdext::hash_map;

#ifdef MATRIXSERVERDLL_EXPORTS
#define MATRIXSERVERDLL_API __declspec(dllexport)
#define MatrixServerDll_API extern "C" __declspec(dllexport)
#else
#define MATRIXSERVERDLL_API __declspec(dllimport)
#define MatrixServerDll_API extern "C" __declspec(dllimport)
#endif

#ifndef   _InstrumentList_H
#define   _InstrumentList_H
// ��������
typedef struct InstrumentList_Struct
{
	// ����������Դͬ������
	CRITICAL_SECTION m_oSecInstrumentList;
	/** ��������ָ��*/
	m_oInstrumentStruct* m_pArrayInstrument;
	/** ������������*/
	list<m_oInstrumentStruct*> m_olsInstrumentFree;
	/** ����IP��ַ����������*/
	hash_map<unsigned int, m_oInstrumentStruct*> m_oIPSetMap;
	// ����SN������
	hash_map<unsigned int, m_oInstrumentStruct*> m_oSNInstrumentMap;
	// ����IP��ַ������
	hash_map<unsigned int, m_oInstrumentStruct*> m_oIPInstrumentMap;
	// δ���ADC�������õ���������
	hash_map<unsigned int, m_oInstrumentStruct*> m_oADCSetInstrumentMap;
	// ����ϵͳ�����仯��ʱ��
	unsigned int m_uiLineChangeTime;
	// ����״̬�ɲ��ȶ���Ϊ�ȶ�
	bool m_bLineStableChange;
	/** ��������*/
	unsigned int m_uiCountAll;
	/** ������������*/
	unsigned int m_uiCountFree;
}m_oInstrumentListStruct;
#endif