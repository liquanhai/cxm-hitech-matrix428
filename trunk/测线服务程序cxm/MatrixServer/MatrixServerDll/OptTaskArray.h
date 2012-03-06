#include <list>
#include <hash_map>
#include "OptTask.h"
using std::list;
using stdext::hash_map;

#ifdef MATRIXSERVERDLL_EXPORTS
#define MATRIXSERVERDLL_API __declspec(dllexport)
#define MatrixServerDll_API extern "C" __declspec(dllexport)
#else
#define MATRIXSERVERDLL_API __declspec(dllimport)
#define MatrixServerDll_API extern "C" __declspec(dllimport)
#endif

#ifndef   _OptTaskArray_H
#define   _OptTaskArray_H

// ʩ������ṹ������
typedef struct OptTaskArray_Struct
{
	// ��Դͬ������
	CRITICAL_SECTION m_oSecOptTaskArray;
	/** ʩ����������ָ��*/
	m_oOptTaskStruct* m_pArrayOptTask;
	// ���е�ʩ���������
	list<m_oOptTaskStruct*> m_olsOptTaskFree;
	// ���ڽ��е�ʩ����������
	hash_map<unsigned int, m_oOptTaskStruct*> m_oOptTaskWorkMap;
	/** ʩ����������*/
	unsigned int m_uiCountAll;
	/** ������������*/
	unsigned int m_uiCountFree;
	// ʩ���������ݴ洢�ļ��м���
	unsigned int m_uiADCDataFolderNb;
	// ʩ�����ݴ洢�ļ���·��
	string m_SaveLogFolderPath;
}m_oOptTaskArrayStruct;
#endif