#include "stdafx.h"
#include "MatrixServerDll.h"

// ����ʩ������
void OnOptTaskReset(m_oOptTaskStruct* pOptTask)
{
	if (pOptTask == NULL)
	{
		return;
	}
	// �����Ƿ�ʹ����
	pOptTask->m_bInUsed = false;
	// ʩ������ʼ��¼������֡��
	pOptTask->m_uiStartFrame = 0;
	// ʩ����������ļ�ָ��
	pOptTask->m_pFile = NULL;
	// ʩ���������ǰһ���ļ����ļ�ָ��
	pOptTask->m_pPreviousFile = NULL;
	// ���µ��ļ��洢���
	pOptTask->m_uiFileSaveNb = 0;
	// ʩ�������������ؼ���ΪSN������Ϊ�к�
	pOptTask->m_oSNMap.clear();
	// ����ʩ������������
	pOptTask->m_olsOptInstrument.clear();
}

// �ж��������Ƿ��Ѽ���ʩ������������
BOOL IfIndexExistInOptTaskMap(unsigned int uiIndex, 
	hash_map<unsigned int, m_oOptTaskStruct*>* pMap)
{
	if (pMap == NULL)
	{
		return FALSE;
	}
	BOOL bResult = FALSE;
	hash_map<unsigned int, m_oOptTaskStruct*>::iterator iter;
	iter = pMap->find(uiIndex);
	if (iter != pMap->end())
	{
		bResult = TRUE;
	}
	else
	{
		bResult = FALSE;
	}
	return bResult;
}
// �ж�����SN���Ƿ��Ѽ���ʩ����������������
BOOL IfIndexExistInOptTaskSNMap(unsigned int uiIndex,
	hash_map<unsigned int, unsigned int>* pMap)
{
	if (pMap == NULL)
	{
		return FALSE;
	}
	BOOL bResult = FALSE;
	hash_map<unsigned int, unsigned int>::iterator iter;
	iter = pMap->find(uiIndex);
	if (iter != pMap->end())
	{
		bResult = TRUE;
	}
	else
	{
		bResult = FALSE;
	}
	return bResult;
}
// ��ʩ�����������������еõ��������к�
unsigned int GetLineNbFromOptTaskSNMap(unsigned int uiIndex,
	hash_map<unsigned int, unsigned int>* pMap)
{
	if (pMap == NULL)
	{
		return 0;
	}
	hash_map<unsigned int, unsigned int>::iterator iter;
	iter = pMap->find(uiIndex);
	return iter->second;
}
// ��ʩ�����������������м�������
void AddToOptTaskSNMap(unsigned int uiIndex, unsigned int uiLineNb,
	hash_map<unsigned int, unsigned int>* pMap)
{
	if (pMap == NULL)
	{
		return;
	}
	if (FALSE == IfIndexExistInOptTaskSNMap(uiIndex, pMap))
	{
		pMap->insert(hash_map<unsigned int, unsigned int>::value_type (uiIndex, uiLineNb));
	}
}
// ����һ��ʩ������
void AddOptTaskToMap(unsigned int uiIndex, m_oOptTaskStruct* pOptTask, 
	hash_map<unsigned int, m_oOptTaskStruct*>* pMap)
{
	if ((pOptTask == NULL) || (pMap == NULL))
	{
		return;
	}
	if (FALSE == IfIndexExistInOptTaskMap(uiIndex, pMap))
	{
		pMap->insert(hash_map<unsigned int, m_oOptTaskStruct*>::value_type (uiIndex, pOptTask));
	}
}
// �������������ţ���������õ�ʩ������ָ��
m_oOptTaskStruct* GetOptTaskFromMap(unsigned int uiIndex, 
	hash_map<unsigned int, m_oOptTaskStruct*>* pMap)
{
	if (pMap == NULL)
	{
		return NULL;
	}
	hash_map<unsigned int, m_oOptTaskStruct*>::iterator iter;
	iter = pMap->find(uiIndex);
	return iter->second;
}
// ��������ɾ��������ָ���ʩ������ָ��
BOOL DeleteOptTaskFromMap(unsigned int uiIndex, 
	hash_map<unsigned int, m_oOptTaskStruct*>* pMap)
{
	if (pMap == NULL)
	{
		return FALSE;
	}
	BOOL bResult = FALSE;
	hash_map<unsigned int, m_oOptTaskStruct*>::iterator iter;
	iter = pMap->find(uiIndex);
	if (iter != pMap->end())
	{
		pMap->erase(iter);
		bResult = TRUE;
	}
	else
	{
		bResult = FALSE;
	}
	return bResult;
}