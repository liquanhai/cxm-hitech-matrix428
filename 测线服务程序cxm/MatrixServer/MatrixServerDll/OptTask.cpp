#include "stdafx.h"
#include "MatrixServerDll.h"

// ����ʩ������
void OnOptTaskReset(m_oOptTaskStruct* pOptTask)
{
	ASSERT(pOptTask != NULL);
	hash_map<unsigned int, m_oOptInstrumentStruct*>::iterator iter;
	// �����Ƿ�ʹ����
	pOptTask->m_bInUsed = false;
	// ʩ������ʼ��¼��ʱ��
	pOptTask->m_uiTB = 0;
	// ʩ������ֹͣ��¼��ʱ��
	pOptTask->m_uiTS = 0;
	// ʩ����������ļ�ָ��
	pOptTask->m_pFile = NULL;
	// ʩ���������ǰһ���ļ����ļ�ָ��
	pOptTask->m_pPreviousFile = NULL;
	// ���µ��ļ��洢���
	pOptTask->m_uiFileSaveNb = 0;
	// ʩ�������������ؼ���ΪSN������Ϊ�к�
	for (iter = pOptTask->m_oIPMap.begin(); iter != pOptTask->m_oIPMap.end(); iter++);
	{
		delete iter->second;
		iter->second = NULL;
	}
	pOptTask->m_oIPMap.clear();
	// ����洢��Ԫ��־λ
	pOptTask->m_bSaveBuf = false;
	// ����洢��Ԫ���
	pOptTask->m_uiSaveBufNo = 0;
// 	// ����ʩ������������
// 	pOptTask->m_olsOptInstrument.clear();
}

// �ж��������Ƿ��Ѽ���ʩ������������
BOOL IfIndexExistInOptTaskMap(unsigned int uiIndex, 
	hash_map<unsigned int, m_oOptTaskStruct*>* pMap)
{
	ASSERT(pMap != NULL);
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
BOOL IfIndexExistInOptTaskIPMap(unsigned int uiIndex,
	hash_map<unsigned int, m_oOptInstrumentStruct*>* pMap)
{
	ASSERT(pMap != NULL);
	BOOL bResult = FALSE;
	hash_map<unsigned int, m_oOptInstrumentStruct*>::iterator iter;
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
	ASSERT(pMap != NULL);
	hash_map<unsigned int, unsigned int>::iterator iter;
	iter = pMap->find(uiIndex);
	return iter->second;
}
// ��ʩ�����������������м�������
void AddToOptTaskIPMap(unsigned int uiIndex, m_oOptInstrumentStruct* pOptInstr,
	hash_map<unsigned int, m_oOptInstrumentStruct*>* pMap)
{
	ASSERT(pMap != NULL);
	if (FALSE == IfIndexExistInOptTaskIPMap(uiIndex, pMap))
	{
		pMap->insert(hash_map<unsigned int, m_oOptInstrumentStruct*>::value_type (uiIndex, pOptInstr));
	}
}
// ����һ��ʩ������
void AddOptTaskToMap(unsigned int uiIndex, m_oOptTaskStruct* pOptTask, 
	hash_map<unsigned int, m_oOptTaskStruct*>* pMap)
{
	ASSERT(pOptTask != NULL);
	ASSERT(pMap != NULL);
	if (FALSE == IfIndexExistInOptTaskMap(uiIndex, pMap))
	{
		pMap->insert(hash_map<unsigned int, m_oOptTaskStruct*>::value_type (uiIndex, pOptTask));
	}
}
// �������������ţ���������õ�ʩ������ָ��
m_oOptTaskStruct* GetOptTaskFromMap(unsigned int uiIndex, 
	hash_map<unsigned int, m_oOptTaskStruct*>* pMap)
{
	ASSERT(pMap != NULL);
	hash_map<unsigned int, m_oOptTaskStruct*>::iterator iter;
	iter = pMap->find(uiIndex);
	return iter->second;
}
// ��������ɾ��������ָ���ʩ������ָ��
BOOL DeleteOptTaskFromMap(unsigned int uiIndex, 
	hash_map<unsigned int, m_oOptTaskStruct*>* pMap)
{
	ASSERT(pMap != NULL);
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