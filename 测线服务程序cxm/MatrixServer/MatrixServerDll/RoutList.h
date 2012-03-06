#include <list>
#include <hash_map>
#include "Rout.h"
using std::list;
using stdext::hash_map;

#ifdef MATRIXSERVERDLL_EXPORTS
#define MATRIXSERVERDLL_API __declspec(dllexport)
#define MatrixServerDll_API extern "C" __declspec(dllexport)
#else
#define MATRIXSERVERDLL_API __declspec(dllimport)
#define MatrixServerDll_API extern "C" __declspec(dllimport)
#endif

#ifndef   _RoutList_H
#define   _RoutList_H

// ·�ɶ��нṹ��
typedef struct RoutList_Struct
{
	// ·�ɶ�����Դͬ������
	CRITICAL_SECTION m_oSecRoutList;
	/** ·������ָ��*/
	m_oRoutStruct* m_pArrayRout;
	/** ����·�ɶ���*/
	list<m_oRoutStruct*> m_olsRoutFree;
	// ����·�ɵ�ַ������
	hash_map<unsigned int, m_oRoutStruct*> m_oRoutMap;
	// ��Ҫɾ��·��������·��������
	hash_map<unsigned int, m_oRoutStruct*> m_oRoutDeleteMap;
	// ����ʱͳ��������У���ԱΪ·��IP
	list<unsigned int> m_olsTimeDelayTaskQueue;
	// ����ʱͳ��������ת����
	list<unsigned int> m_olsTimeDelayTemp;
	// ADC����������������
	hash_map<unsigned int, m_oRoutStruct*> m_oADCSetRoutMap;
	/** ·������*/
	unsigned int m_uiCountAll;
	/** ����·������*/
	unsigned int m_uiCountFree;
}m_oRoutListStruct;

#endif