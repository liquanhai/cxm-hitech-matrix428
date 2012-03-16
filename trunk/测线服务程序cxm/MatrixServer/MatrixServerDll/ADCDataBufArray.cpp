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
	if (pADCDataBufArray == NULL)
	{
		return;
	}
	EnterCriticalSection(&pADCDataBufArray->m_oSecADCDataBufArray);
	// ������ݻ���������
	pADCDataBufArray->m_olsADCDataToWrite.clear();
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
void OnInitADCDataBufArray(m_oADCDataBufArrayStruct* pADCDataBufArray,
	m_oConstVarStruct* pConstVar)
{
	if (pConstVar == NULL)
	{
		return;
	}
	if (pADCDataBufArray == NULL)
	{
		AddMsgToLogOutPutList(pConstVar->m_pLogOutPut, "OnInitADCDataBufArray", "", 
			ErrorType, IDS_ERR_PTRISNULL);
		return;
	}
	EnterCriticalSection(&pADCDataBufArray->m_oSecADCDataBufArray);
	// ������ݻ���������
	pADCDataBufArray->m_olsADCDataToWrite.clear();
	// ��տ������ݻ���������
	pADCDataBufArray->m_olsADCDataBufFree.clear();

	// ���ݻ�����������·�ɸ���
	pADCDataBufArray->m_uiCountAll = pConstVar->m_iADCDataCountAll;
	// �������ݻ���������
	pADCDataBufArray->m_uiCountFree = pADCDataBufArray->m_uiCountAll;
	// �������ݻ���������
	if (pADCDataBufArray->m_pArrayADCDataBuf != NULL)
	{
		for(unsigned int i = 0; i < pADCDataBufArray->m_uiCountAll; i++)
		{
			delete[] pADCDataBufArray->m_pArrayADCDataBuf[i].m_pADCDataBuf;
		}
		delete[] pADCDataBufArray->m_pArrayADCDataBuf;
	}
	pADCDataBufArray->m_pArrayADCDataBuf = new m_oADCDataBufStruct[pADCDataBufArray->m_uiCountAll];

	// ����������ݻ���������
	for(unsigned int i = 0; i < pADCDataBufArray->m_uiCountAll; i++)
	{
		// �������ڻ����������е�λ��
		pADCDataBufArray->m_pArrayADCDataBuf[i].m_uiIndex = i;
		pADCDataBufArray->m_pArrayADCDataBuf[i].m_pADCDataBuf = new int[pConstVar->m_iADCDataInOneFrameNum];
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
	if (pADCDataBufArray == NULL)
	{
		return;
	}
	EnterCriticalSection(&pADCDataBufArray->m_oSecADCDataBufArray);
	// ������ݻ���������
	pADCDataBufArray->m_olsADCDataToWrite.clear();
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
	if (pADCDataBufArray == NULL)
	{
		return;
	}
	DeleteCriticalSection(&pADCDataBufArray->m_oSecADCDataBufArray);
	delete pADCDataBufArray;
}
// �õ�һ���������ݴ洢������
m_oADCDataBufStruct* GetFreeADCDataBuf(m_oADCDataBufArrayStruct* pADCDataBufArray)
{
	if (pADCDataBufArray == NULL)
	{
		return NULL;
	}
	m_oADCDataBufStruct* pADCDataBuf = NULL;
	list <m_oADCDataBufStruct*>::iterator iter;
	if(pADCDataBufArray->m_uiCountFree > 0)	//�п������ݴ洢������
	{
		// �ӿ������ݴ洢����������ͷ���õ�һ���������ݴ洢������
		iter = pADCDataBufArray->m_olsADCDataBufFree.begin();
		pADCDataBuf = *iter;
		pADCDataBufArray->m_olsADCDataBufFree.pop_front();	
		// ���ݴ洢�������Ƿ�ʹ����
		pADCDataBuf->m_bInUsed = true;	
		// �������ݴ洢������������1
		pADCDataBufArray->m_uiCountFree--;
	}
	return pADCDataBuf;
}
// ����һ���������ݴ洢������
void AddFreeADCDataBuf(m_oADCDataBufStruct* pADCDataBuf, 
	m_oADCDataBufArrayStruct* pADCDataBufArray)
{
	if ((pADCDataBuf == NULL) || (pADCDataBufArray == NULL))
	{
		return;
	}
	//��ʼ�����ݴ洢������
	OnADCDataBufReset(pADCDataBuf);
	//������ж���
	pADCDataBufArray->m_olsADCDataBufFree.push_back(pADCDataBuf);
	// �������ݴ洢������������1
	pADCDataBufArray->m_uiCountFree++;
}