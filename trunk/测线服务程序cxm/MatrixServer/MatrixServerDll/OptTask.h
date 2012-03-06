#include <list>
#include <hash_map>
#include "OptInstrument.h"
using std::list;
using stdext::hash_map;
using std::string;
#ifdef MATRIXSERVERDLL_EXPORTS
#define MATRIXSERVERDLL_API __declspec(dllexport)
#define MatrixServerDll_API extern "C" __declspec(dllexport)
#else
#define MATRIXSERVERDLL_API __declspec(dllimport)
#define MatrixServerDll_API extern "C" __declspec(dllimport)
#endif

#ifndef   _OptTask_H
#define   _OptTask_H
// ʩ������ṹ��
typedef struct OptTask_Struct
{
	// �����Ƿ�ʹ����
	bool m_bInUsed;
	// �������
	unsigned int m_uiIndex;
	// ʩ������ʼ��¼������֡��
	unsigned int m_uiStartFrame;
	// ʩ����������ļ�ָ��
	FILE* m_pFile;
	// ʩ���������ǰһ���ļ����ļ�ָ��
	FILE* m_pPreviousFile;
	// ���µ��ļ��洢���
	unsigned int m_uiFileSaveNb;
	// ʩ�����ݴ洢�ļ�·��
	string m_SaveLogFilePath;
	// ʩ�������������ؼ���ΪSN������Ϊ�к�
	hash_map<unsigned int, unsigned int> m_oSNMap;
	// ����ʩ������������
	list<m_oOptInstrumentStruct> m_olsOptInstrument;
}m_oOptTaskStruct;
#endif