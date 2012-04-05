#include "stdafx.h"
#include "MatrixServerDll.h"

// ����·�ɶ��нṹ��
m_oRoutListStruct* OnCreateRoutList(void)
{
	m_oRoutListStruct* pRoutList = NULL;
	pRoutList = new m_oRoutListStruct;
	InitializeCriticalSection(&pRoutList->m_oSecRoutList);
	pRoutList->m_pArrayRout = NULL;
	return pRoutList;
}
// ����·�ɶ��нṹ��
void OnResetRoutList(m_oRoutListStruct* pRoutList)
{
	if (pRoutList == NULL)
	{
		return;
	}
	EnterCriticalSection(&pRoutList->m_oSecRoutList);
	// ���·�ɵ�ַ����
	pRoutList->m_oRoutMap.clear();
	// �����Ҫɾ����·�ɵ�ַ����
	pRoutList->m_oRoutDeleteMap.clear();
	// ���ADC����������������
	pRoutList->m_oADCSetRoutMap.clear();
	// ��տ���·�ɶ���
	pRoutList->m_olsRoutFree.clear();
	// �������ʱͳ���������
	pRoutList->m_olsTimeDelayTaskQueue.clear();
	pRoutList->m_olsTimeDelayTemp.clear();
	// ����·������
	pRoutList->m_uiCountFree = pRoutList->m_uiCountAll;
	// �������·�ɶ���
	for(unsigned int i = 0; i < pRoutList->m_uiCountAll; i++)
	{
		// ����·��
		OnRoutReset(&pRoutList->m_pArrayRout[i]);
		// ·�ɼ��ڿ���·�ɶ���β��
		pRoutList->m_olsRoutFree.push_back(&pRoutList->m_pArrayRout[i]);
	}
	LeaveCriticalSection(&pRoutList->m_oSecRoutList);
}
// ��ʼ��·�ɶ��нṹ��
void OnInitRoutList(m_oRoutListStruct* pRoutList, m_oConstVarStruct* pConstVar)
{
	if (pConstVar == NULL)
	{
		return;
	}
	if (pRoutList == NULL)
	{
		AddMsgToLogOutPutList(pConstVar->m_pLogOutPut, "OnInitRoutList", "",
			ErrorType, IDS_ERR_PTRISNULL);
		return;
	}
	EnterCriticalSection(&pRoutList->m_oSecRoutList);
	// ���·�ɵ�ַ����
	pRoutList->m_oRoutMap.clear();
	// �����Ҫɾ����·�ɵ�ַ����
	pRoutList->m_oRoutDeleteMap.clear();
	// ���ADC����������������
	pRoutList->m_oADCSetRoutMap.clear();
	// ��տ���·�ɶ���
	pRoutList->m_olsRoutFree.clear();
	// �������ʱͳ���������
	pRoutList->m_olsTimeDelayTaskQueue.clear();
	pRoutList->m_olsTimeDelayTemp.clear();
	// ·�ɶ�����·�ɸ���
	pRoutList->m_uiCountAll = pConstVar->m_iInstrumentNum;
	// ����·������
	pRoutList->m_uiCountFree = pRoutList->m_uiCountAll;
	// ����·������
	if (pRoutList->m_pArrayRout != NULL)
	{
		delete[] pRoutList->m_pArrayRout;
	}
	pRoutList->m_pArrayRout = new m_oRoutStruct[pRoutList->m_uiCountAll];

	// �������·�ɶ���
	for(unsigned int i = 0; i < pRoutList->m_uiCountAll; i++)
	{
		// ����·��IP��ַ
		pRoutList->m_pArrayRout[i].m_uiRoutIP = pConstVar->m_iRoutSetAddrStart 
			+ i * pConstVar->m_iRoutSetAddrInterval;
		// ·����·�������е�λ��
		pRoutList->m_pArrayRout[i].m_uiIndex = i;
		// ����·��
		OnRoutReset(&pRoutList->m_pArrayRout[i]);
		// ·�ɼ��ڿ���·�ɶ���β��
		pRoutList->m_olsRoutFree.push_back(&pRoutList->m_pArrayRout[i]);
	}
	LeaveCriticalSection(&pRoutList->m_oSecRoutList);
}
// �ر�·�ɶ��нṹ��
void OnCloseRoutList(m_oRoutListStruct* pRoutList)
{
	if (pRoutList == NULL)
	{
		return;
	}
	EnterCriticalSection(&pRoutList->m_oSecRoutList);
	// ���·�ɵ�ַ����
	pRoutList->m_oRoutMap.clear();
	// �����Ҫɾ����·�ɵ�ַ����
	pRoutList->m_oRoutDeleteMap.clear();
	// ���ADC����������������
	pRoutList->m_oADCSetRoutMap.clear();
	// ��տ���·�ɶ���
	pRoutList->m_olsRoutFree.clear();
	// �������ʱͳ���������
	pRoutList->m_olsTimeDelayTaskQueue.clear();
	pRoutList->m_olsTimeDelayTemp.clear();
	// ɾ��·������
	if (pRoutList->m_pArrayRout != NULL)
	{
		delete[] pRoutList->m_pArrayRout;
		pRoutList->m_pArrayRout = NULL;
	}
	LeaveCriticalSection(&pRoutList->m_oSecRoutList);
}
// �ͷ�·�ɶ��нṹ��
void OnFreeRoutList(m_oRoutListStruct* pRoutList)
{
	if (pRoutList == NULL)
	{
		return;
	}
	DeleteCriticalSection(&pRoutList->m_oSecRoutList);
	delete pRoutList;
}

// �õ�һ������·��
m_oRoutStruct* GetFreeRout(m_oRoutListStruct* pRoutList)
{
	if (pRoutList == NULL)
	{
		return NULL;
	}
	m_oRoutStruct* pRout = NULL;
	list <m_oRoutStruct*>::iterator iter;
	if(pRoutList->m_uiCountFree > 0)	//�п���·��
	{
		// �ӿ���·�ɶ���ͷ���õ�һ������·��
		iter = pRoutList->m_olsRoutFree.begin();
		pRout = *iter;
		pRoutList->m_olsRoutFree.pop_front();	
		// ·���Ƿ�ʹ����
		pRout->m_bInUsed = true;	
		// ����·�ɼ�����1
		pRoutList->m_uiCountFree--;
	}
	return pRout;
}
// ����һ������·��
void AddFreeRout(m_oRoutStruct* pRout, m_oRoutListStruct* pRoutList)
{
	if ((pRout == NULL) || (pRoutList == NULL))
	{
		return;
	}
	//��ʼ��·��
	OnRoutReset(pRout);
	//������ж���
	pRoutList->m_olsRoutFree.push_back(pRout);
	// ����·�ɼ�����1
	pRoutList->m_uiCountFree++;
}