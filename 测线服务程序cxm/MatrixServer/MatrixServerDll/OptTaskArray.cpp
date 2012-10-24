#include "stdafx.h"
#include "MatrixServerDll.h"

// ����ʩ����������ṹ��
m_oOptTaskArrayStruct* OnCreateOptTaskArray(void)
{
	m_oOptTaskArrayStruct* pOptTaskArray = NULL;
	pOptTaskArray = new m_oOptTaskArrayStruct;
	pOptTaskArray->m_pArrayOptTask = NULL;
	InitializeCriticalSection(&pOptTaskArray->m_oSecOptTaskArray);
	return pOptTaskArray;
}
// ����ʩ����������ṹ��
void OnResetOptTaskArray(m_oOptTaskArrayStruct* pOptTaskArray)
{
	ASSERT(pOptTaskArray != NULL);
	EnterCriticalSection(&pOptTaskArray->m_oSecOptTaskArray);
	// ���ʩ����������
	pOptTaskArray->m_oOptTaskWorkMap.clear();
	// ��տ���ʩ���������
	pOptTaskArray->m_olsOptTaskFree.clear();
	// ����ʩ����������
	pOptTaskArray->m_uiCountFree = pOptTaskArray->m_uiCountAll;
	// �������ʩ���������
	for(unsigned int i = 0; i < pOptTaskArray->m_uiCountAll; i++)
	{
		// ����ʩ������
		OnOptTaskReset(&pOptTaskArray->m_pArrayOptTask[i]);
		// ʩ��������ڿ���ʩ���������β��
		pOptTaskArray->m_olsOptTaskFree.push_back(&pOptTaskArray->m_pArrayOptTask[i]);
	}
	LeaveCriticalSection(&pOptTaskArray->m_oSecOptTaskArray);
}
// ��ʼ��ʩ����������ṹ��
void OnInitOptTaskArray(m_oOptTaskArrayStruct* pOptTaskArray, m_oConstVarStruct* pConstVar)
{
	ASSERT(pOptTaskArray != NULL);
	ASSERT(pConstVar != NULL);
	EnterCriticalSection(&pOptTaskArray->m_oSecOptTaskArray);
	// ���ʩ����������
	pOptTaskArray->m_oOptTaskWorkMap.clear();
	// ��տ���ʩ���������
	pOptTaskArray->m_olsOptTaskFree.clear();

	// ʩ�����������·�ɸ���
	pOptTaskArray->m_uiCountAll = pConstVar->m_iOptTaskCountAll;
	// ����ʩ����������
	pOptTaskArray->m_uiCountFree = pOptTaskArray->m_uiCountAll;
	// ʩ���������ݴ洢�ļ��м���
	pOptTaskArray->m_uiOptTaskNb = 0;
	// ����ʩ����������
	if (pOptTaskArray->m_pArrayOptTask != NULL)
	{
		delete[] pOptTaskArray->m_pArrayOptTask;
		pOptTaskArray->m_pArrayOptTask = NULL;
	}
	pOptTaskArray->m_pArrayOptTask = new m_oOptTaskStruct[pOptTaskArray->m_uiCountAll];

	// �������ʩ���������
	for(unsigned int i = 0; i < pOptTaskArray->m_uiCountAll; i++)
	{
// 		// ʩ��������ʩ�����������е�λ��
// 		pOptTaskArray->m_pArrayOptTask[i].m_uiIndex = i;
		// ����ʩ������
		OnOptTaskReset(&pOptTaskArray->m_pArrayOptTask[i]);
		// ʩ��������ڿ���ʩ���������β��
		pOptTaskArray->m_olsOptTaskFree.push_back(&pOptTaskArray->m_pArrayOptTask[i]);
	}
	LeaveCriticalSection(&pOptTaskArray->m_oSecOptTaskArray);
}
// �ر�ʩ����������ṹ��
void OnCloseOptTaskArray(m_oOptTaskArrayStruct* pOptTaskArray)
{
	ASSERT(pOptTaskArray != NULL);
	EnterCriticalSection(&pOptTaskArray->m_oSecOptTaskArray);
	// ���ʩ����������
	pOptTaskArray->m_oOptTaskWorkMap.clear();
	// ��տ���ʩ���������
	pOptTaskArray->m_olsOptTaskFree.clear();
	// ɾ��ʩ����������
	if (pOptTaskArray->m_pArrayOptTask != NULL)
	{
		delete[] pOptTaskArray->m_pArrayOptTask;
		pOptTaskArray->m_pArrayOptTask = NULL;
	}
	LeaveCriticalSection(&pOptTaskArray->m_oSecOptTaskArray);
}
// �ͷ�ʩ����������ṹ��
void OnFreeOptTaskArray(m_oOptTaskArrayStruct* pOptTaskArray)
{
	ASSERT(pOptTaskArray != NULL);
	DeleteCriticalSection(&pOptTaskArray->m_oSecOptTaskArray);
	delete pOptTaskArray;
	pOptTaskArray = NULL;
}
// �õ�һ������ʩ������
m_oOptTaskStruct* GetFreeOptTask(m_oOptTaskArrayStruct* pOptTaskArray)
{
	ASSERT(pOptTaskArray != NULL);
	m_oOptTaskStruct* pOptTask = NULL;
	list <m_oOptTaskStruct*>::iterator iter;
	EnterCriticalSection(&pOptTaskArray->m_oSecOptTaskArray);
	if(pOptTaskArray->m_uiCountFree > 0)	//�п���ʩ������
	{
		// �ӿ���ʩ���������ͷ���õ�һ������ʩ������
		iter = pOptTaskArray->m_olsOptTaskFree.begin();
		pOptTask = *iter;
		pOptTaskArray->m_olsOptTaskFree.pop_front();
		// ʩ�������Ƿ�ʹ����
		pOptTask->m_bInUsed = true;
		// ����ʩ�����������1
		pOptTaskArray->m_uiCountFree--;
	}
	LeaveCriticalSection(&pOptTaskArray->m_oSecOptTaskArray);
	return pOptTask;
}
// ����һ������ʩ������
void AddFreeOptTask(m_oOptTaskStruct* pOptTask, m_oOptTaskArrayStruct* pOptTaskArray)
{
	ASSERT(pOptTask != NULL);
	ASSERT(pOptTaskArray != NULL);
	EnterCriticalSection(&pOptTaskArray->m_oSecOptTaskArray);
	//��ʼ��ʩ������
	OnOptTaskReset(pOptTask);
	//������ж���
	pOptTaskArray->m_olsOptTaskFree.push_back(pOptTask);
	// ����ʩ�����������1
	pOptTaskArray->m_uiCountFree++;
	LeaveCriticalSection(&pOptTaskArray->m_oSecOptTaskArray);
}
