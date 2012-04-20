#include "stdafx.h"
#include "MatrixServerDll.h"

// �����������нṹ��
m_oInstrumentListStruct* OnCreateInstrumentList(void)
{
	m_oInstrumentListStruct* pInstrumentList = NULL;
	pInstrumentList = new m_oInstrumentListStruct;
	InitializeCriticalSection(&pInstrumentList->m_oSecInstrumentList);
	pInstrumentList->m_pArrayInstrument = NULL;
	pInstrumentList->m_bSetByHand = false;
	return pInstrumentList;
}
// �����������нṹ��
void OnResetInstrumentList(m_oInstrumentListStruct* pInstrumentList)
{
	if (pInstrumentList == NULL)
	{
		return;
	}
	EnterCriticalSection(&pInstrumentList->m_oSecInstrumentList);
	// ���SN����������
	pInstrumentList->m_oSNInstrumentMap.clear();
	// ���IP��ַ����������
	pInstrumentList->m_oIPInstrumentMap.clear();
	// ��տ�����������
	pInstrumentList->m_olsInstrumentFree.clear();
	// ���IP��ַ��������������
	pInstrumentList->m_oIPSetMap.clear();
	// ���δ���ADC�������õ���������
	pInstrumentList->m_oADCSetInstrumentMap.clear();
	// �������λ��������
	pInstrumentList->m_oInstrumentLocationMap.clear();
	// ����ϵͳ�����仯��ʱ��
	pInstrumentList->m_uiLineChangeTime = 0;
	// ����״̬Ϊ���ȶ�
	pInstrumentList->m_bLineStableChange = false;

	// ������������
	pInstrumentList->m_uiCountFree = pInstrumentList->m_uiCountAll;
	for(unsigned int i = 0; i < pInstrumentList->m_uiCountAll; i++)
	{
		// ��������
		OnInstrumentReset(&pInstrumentList->m_pArrayInstrument[i], pInstrumentList->m_bSetByHand);
		// �������ڿ�����������β��
		pInstrumentList->m_olsInstrumentFree.push_back(&pInstrumentList->m_pArrayInstrument[i]);
	}
	LeaveCriticalSection(&pInstrumentList->m_oSecInstrumentList);
}
// ADC�������ø�Ϊ�ֶ�����
void OnSetADCSetByHand(m_oInstrumentListStruct* pInstrumentList)
{
	if (pInstrumentList == NULL)
	{
		return;
	}
	pInstrumentList->m_bSetByHand = true;
}
// ��ʼ���������нṹ��
void OnInitInstrumentList(m_oInstrumentListStruct* pInstrumentList, m_oConstVarStruct* pConstVar)
{
	if (pConstVar == NULL)
	{
		return;
	}
	if (pInstrumentList == NULL)
	{
		AddMsgToLogOutPutList(pConstVar->m_pLogOutPut, "InitInstrumentList", "",
			ErrorType, IDS_ERR_PTRISNULL);
		return;
	}
	EnterCriticalSection(&pInstrumentList->m_oSecInstrumentList);
	// ���SN����������
	pInstrumentList->m_oSNInstrumentMap.clear();
	// ���IP��ַ����������
	pInstrumentList->m_oIPInstrumentMap.clear();
	// ��տ�����������
	pInstrumentList->m_olsInstrumentFree.clear();
	// ���IP��ַ��������������
	pInstrumentList->m_oIPSetMap.clear();
	// ���δ���ADC�������õ���������
	pInstrumentList->m_oADCSetInstrumentMap.clear();
	// �������λ��������
	pInstrumentList->m_oInstrumentLocationMap.clear();

	// ����ϵͳ�����仯��ʱ��
	pInstrumentList->m_uiLineChangeTime = 0;
	// ����״̬Ϊ���ȶ�
	pInstrumentList->m_bLineStableChange = false;
	// ������������������
	pInstrumentList->m_uiCountAll = pConstVar->m_iInstrumentNum;
	// ������������
	if (pInstrumentList->m_pArrayInstrument != NULL)
	{
		delete[] pInstrumentList->m_pArrayInstrument;
	}
	pInstrumentList->m_pArrayInstrument = new m_oInstrumentStruct[pInstrumentList->m_uiCountAll];
	// ������������
	pInstrumentList->m_uiCountFree = pInstrumentList->m_uiCountAll;
	for(unsigned int i = 0; i < pInstrumentList->m_uiCountAll; i++)
	{
		// ���������������е�λ��
		pInstrumentList->m_pArrayInstrument[i].m_uiIndex = i;
		pInstrumentList->m_pArrayInstrument[i].m_uiIP = pConstVar->m_iIPSetAddrStart 
			+ i * pConstVar->m_iIPSetAddrInterval;
		// ��������
		OnInstrumentReset(&pInstrumentList->m_pArrayInstrument[i], pInstrumentList->m_bSetByHand);
		// �������ڿ�����������β��
		pInstrumentList->m_olsInstrumentFree.push_back(&pInstrumentList->m_pArrayInstrument[i]);
	}
	LeaveCriticalSection(&pInstrumentList->m_oSecInstrumentList);
}
// �ر��������нṹ��
void OnCloseInstrumentList(m_oInstrumentListStruct* pInstrumentList)
{
	if (pInstrumentList == NULL)
	{
		return;
	}
	EnterCriticalSection(&pInstrumentList->m_oSecInstrumentList);
	// ���SN����������
	pInstrumentList->m_oSNInstrumentMap.clear();
	// ���IP��ַ����������
	pInstrumentList->m_oIPInstrumentMap.clear();
	// ��տ�����������
	pInstrumentList->m_olsInstrumentFree.clear();
	// ���IP��ַ��������������
	pInstrumentList->m_oIPSetMap.clear();
	// ���δ���ADC�������õ���������
	pInstrumentList->m_oADCSetInstrumentMap.clear();
	// �������λ��������
	pInstrumentList->m_oInstrumentLocationMap.clear();
	// ɾ����������
	if (pInstrumentList->m_pArrayInstrument != NULL)
	{
		delete[] pInstrumentList->m_pArrayInstrument;
		pInstrumentList->m_pArrayInstrument = NULL;
	}
	LeaveCriticalSection(&pInstrumentList->m_oSecInstrumentList);
}
// �ͷ��������нṹ��
void OnFreeInstrumentList(m_oInstrumentListStruct* pInstrumentList)
{
	if (pInstrumentList == NULL)
	{
		return;
	}
	DeleteCriticalSection(&pInstrumentList->m_oSecInstrumentList);
	delete pInstrumentList;
}
// �õ�һ����������
m_oInstrumentStruct* GetFreeInstrument(m_oInstrumentListStruct* pInstrumentList)
{
	if (pInstrumentList == NULL)
	{
		return NULL;
	}
	m_oInstrumentStruct* pInstrument = NULL;
	list <m_oInstrumentStruct*>::iterator iter;
	if(pInstrumentList->m_uiCountFree > 0)	//�п�������
	{
		// �ӿ��ж����еõ�һ������
		iter = pInstrumentList->m_olsInstrumentFree.begin();
		pInstrument = *iter;
		pInstrumentList->m_olsInstrumentFree.pop_front();	
		pInstrument->m_bInUsed = true;	// ��������Ϊʹ����
		pInstrumentList->m_uiCountFree--;	// ��������������1
	}
	return pInstrument;
}
// ����һ����������
void AddFreeInstrument(m_oInstrumentStruct* pInstrument, m_oInstrumentListStruct* pInstrumentList)
{
	if ((pInstrument == NULL) || (pInstrumentList == NULL))
	{
		return;
	}
	//��ʼ������
	OnInstrumentReset(pInstrument, pInstrumentList->m_bSetByHand);
	//������ж���
	pInstrumentList->m_olsInstrumentFree.push_back(pInstrument);
	pInstrumentList->m_uiCountFree++;	// ��������������1
}
// �����ϴβ���ϵͳ�仯ʱ��
void UpdateLineChangeTime(m_oInstrumentListStruct* pInstrumentList)
{
	if (pInstrumentList == NULL)
	{
		return;
	}
	// �ϴβ���ϵͳ�仯ʱ��
	pInstrumentList->m_uiLineChangeTime = GetTickCount();
}