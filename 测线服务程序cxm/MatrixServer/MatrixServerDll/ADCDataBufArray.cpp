#include "stdafx.h"
#include "MatrixServerDll.h"

// �������ݴ洢�������ṹ��
m_oADCDataBufArrayStruct* OnCreateADCDataBufArray(void)
{
	m_oADCDataBufArrayStruct* pADCDataBufArray = NULL;
	pADCDataBufArray = new m_oADCDataBufArrayStruct;
	InitializeCriticalSection(&pADCDataBufArray->m_oSecADCDataBufArray);
	pADCDataBufArray->m_pArrayADCDataBuf = NULL;
	return pADCDataBufArray;
}
// �������ݴ洢�������ṹ��
void OnResetADCDataBufArray(m_oADCDataBufArrayStruct* pADCDataBufArray)
{
	ASSERT(pADCDataBufArray != NULL);
	EnterCriticalSection(&pADCDataBufArray->m_oSecADCDataBufArray);
	// ������ݻ���������
	pADCDataBufArray->m_oADCDataBufWorkMap.clear();
	// ��տ������ݻ���������
	pADCDataBufArray->m_olsADCDataBufFree.clear();
	// �������ݻ���������
	pADCDataBufArray->m_uiCountFree = pADCDataBufArray->m_uiCountAll;
	// ����������ݻ���������
	for(unsigned int i = 0; i < pADCDataBufArray->m_uiCountAll; i++)
	{
		// �������ݻ�����
		OnADCDataBufReset(&pADCDataBufArray->m_pArrayADCDataBuf[i]);
		// ���ݻ��������ڿ������ݻ���������β��
		pADCDataBufArray->m_olsADCDataBufFree.push_back(&pADCDataBufArray->m_pArrayADCDataBuf[i]);
	}
	LeaveCriticalSection(&pADCDataBufArray->m_oSecADCDataBufArray);
}
// ��ʼ�����ݴ洢�������ṹ��
void OnInitADCDataBufArray(m_oADCDataBufArrayStruct* pADCDataBufArray, m_oConstVarStruct* pConstVar)
{
	ASSERT(pADCDataBufArray != NULL);
	ASSERT(pConstVar != NULL);
	EnterCriticalSection(&pADCDataBufArray->m_oSecADCDataBufArray);
	// ������ݻ���������
	pADCDataBufArray->m_oADCDataBufWorkMap.clear();
	// ��տ������ݻ���������
	pADCDataBufArray->m_olsADCDataBufFree.clear();

	// ���ݻ�����������·�ɸ���
	pADCDataBufArray->m_uiCountAll = pConstVar->m_iSEGDDataBufCountAll;
	// �������ݻ���������
	pADCDataBufArray->m_uiCountFree = pADCDataBufArray->m_uiCountAll;
	// �������ݻ���������
	if (pADCDataBufArray->m_pArrayADCDataBuf != NULL)
	{
		for(unsigned int i = 0; i < pADCDataBufArray->m_uiCountAll; i++)
		{
			delete[] pADCDataBufArray->m_pArrayADCDataBuf[i].m_pADCDataBuf;
			pADCDataBufArray->m_pArrayADCDataBuf[i].m_pADCDataBuf = NULL;
		}
		delete[] pADCDataBufArray->m_pArrayADCDataBuf;
		pADCDataBufArray->m_pArrayADCDataBuf = NULL;
	}
	pADCDataBufArray->m_pArrayADCDataBuf = new m_oADCDataBufStruct[pADCDataBufArray->m_uiCountAll];

	// ����������ݻ���������
	for(unsigned int i = 0; i < pADCDataBufArray->m_uiCountAll; i++)
	{
		// �������ڻ����������е�λ��
		pADCDataBufArray->m_pArrayADCDataBuf[i].m_uiIndex = i;
		pADCDataBufArray->m_pArrayADCDataBuf[i].m_pADCDataBuf = new char[pConstVar->m_iSEGDDataBufSize];
		pADCDataBufArray->m_pArrayADCDataBuf[i].m_uiBufLength = pConstVar->m_iSEGDDataBufSize;
		// �������ݻ�����
		OnADCDataBufReset(&pADCDataBufArray->m_pArrayADCDataBuf[i]);
		// ���ݻ��������ڿ������ݻ���������β��
		pADCDataBufArray->m_olsADCDataBufFree.push_back(&pADCDataBufArray->m_pArrayADCDataBuf[i]);
	}
	LeaveCriticalSection(&pADCDataBufArray->m_oSecADCDataBufArray);
}
// �ر����ݴ洢�������ṹ��
void OnCloseADCDataBufArray(m_oADCDataBufArrayStruct* pADCDataBufArray)
{
	ASSERT(pADCDataBufArray != NULL);
	EnterCriticalSection(&pADCDataBufArray->m_oSecADCDataBufArray);
	// ������ݻ���������
	pADCDataBufArray->m_oADCDataBufWorkMap.clear();
	// ��տ������ݻ���������
	pADCDataBufArray->m_olsADCDataBufFree.clear();
	// ɾ�����ݻ���������
	if (pADCDataBufArray->m_pArrayADCDataBuf != NULL)
	{
		for(unsigned int i = 0; i < pADCDataBufArray->m_uiCountAll; i++)
		{
			if (pADCDataBufArray->m_pArrayADCDataBuf[i].m_pADCDataBuf != NULL)
			{
				delete[] pADCDataBufArray->m_pArrayADCDataBuf[i].m_pADCDataBuf;
				pADCDataBufArray->m_pArrayADCDataBuf[i].m_pADCDataBuf = NULL;
			}
		}
		delete[] pADCDataBufArray->m_pArrayADCDataBuf;
		pADCDataBufArray->m_pArrayADCDataBuf = NULL;
	}
	LeaveCriticalSection(&pADCDataBufArray->m_oSecADCDataBufArray);
}
// �ͷ����ݴ洢�������ṹ��
void OnFreeADCDataBufArray(m_oADCDataBufArrayStruct* pADCDataBufArray)
{
	ASSERT(pADCDataBufArray != NULL);
	DeleteCriticalSection(&pADCDataBufArray->m_oSecADCDataBufArray);
	delete pADCDataBufArray;
	pADCDataBufArray = NULL;
}
// �õ�һ���������ݴ洢������
m_oADCDataBufStruct* GetFreeADCDataBuf(m_oADCDataBufArrayStruct* pADCDataBufArray)
{
	ASSERT(pADCDataBufArray != NULL);
	m_oADCDataBufStruct* pADCDataBuf = NULL;
	EnterCriticalSection(&pADCDataBufArray->m_oSecADCDataBufArray);
	if(pADCDataBufArray->m_uiCountFree > 0)	//�п������ݴ洢������
	{
		// �ӿ������ݴ洢����������ͷ���õ�һ���������ݴ洢������
		pADCDataBuf = *pADCDataBufArray->m_olsADCDataBufFree.begin();
		// ���ݴ洢�������Ƿ�ʹ����
		pADCDataBuf->m_bInUsed = true;
		pADCDataBufArray->m_olsADCDataBufFree.pop_front();
		// �������ݴ洢������������1
		pADCDataBufArray->m_uiCountFree--;
	}
	LeaveCriticalSection(&pADCDataBufArray->m_oSecADCDataBufArray);
	return pADCDataBuf;
}
// ����һ���������ݴ洢������
void AddFreeADCDataBuf(m_oADCDataBufStruct* pADCDataBuf, 
	m_oADCDataBufArrayStruct* pADCDataBufArray)
{
	ASSERT(pADCDataBuf != NULL);
	ASSERT(pADCDataBufArray != NULL);
	EnterCriticalSection(&pADCDataBufArray->m_oSecADCDataBufArray);
	//��ʼ�����ݴ洢������
	OnADCDataBufReset(pADCDataBuf);
	//������ж���
	pADCDataBufArray->m_olsADCDataBufFree.push_back(pADCDataBuf);
	// �������ݴ洢������������1
	pADCDataBufArray->m_uiCountFree++;
	LeaveCriticalSection(&pADCDataBufArray->m_oSecADCDataBufArray);
}
// �ж��������Ƿ��Ѽ������ݴ洢����������
BOOL IfIndexExistInADCDataBufMap(unsigned int uiIndex, 
	hash_map<unsigned int, m_oADCDataBufStruct*>* pMap)
{
	ASSERT(pMap != NULL);
	BOOL bResult = FALSE;
	hash_map<unsigned int, m_oADCDataBufStruct*>::iterator iter;
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
// �����ݴ洢�������������м��뻺����ָ��
void AddToADCDataBufMap(unsigned int uiIndex, m_oADCDataBufStruct* pADCDataBuf,
	hash_map<unsigned int, m_oADCDataBufStruct*>* pMap)
{
	ASSERT(pMap != NULL);
	if (FALSE == IfIndexExistInADCDataBufMap(uiIndex, pMap))
	{
		pMap->insert(hash_map<unsigned int, m_oADCDataBufStruct*>::value_type (uiIndex, pADCDataBuf));
	}
}
// �������������ţ���������õ����ݴ洢������ָ��
m_oADCDataBufStruct* GetADCDataBufFromMap(unsigned int uiIndex, 
	hash_map<unsigned int, m_oADCDataBufStruct*>* pMap)
{
	ASSERT(pMap != NULL);
	hash_map<unsigned int, m_oADCDataBufStruct*>::iterator iter;
	iter = pMap->find(uiIndex);
	if (iter == pMap->end())
	{
		return NULL;
	}
	return iter->second;
}
// ��������ɾ��������ָ������ݴ洢������ָ��
BOOL DeleteADCDataBufFromMap(unsigned int uiIndex, 
	hash_map<unsigned int, m_oADCDataBufStruct*>* pMap)
{
	ASSERT(pMap != NULL);
	BOOL bResult = FALSE;
	hash_map<unsigned int, m_oADCDataBufStruct*>::iterator iter;
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