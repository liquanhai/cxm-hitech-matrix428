#include "stdafx.h"
#include "MatrixServerDll.h"

// �������߶��нṹ��
m_oLineListStruct* OnCreateLineList(void)
{
	m_oLineListStruct* pLineList = NULL;
	pLineList = new m_oLineListStruct;
	pLineList->m_pInstrumentList = OnCreateInstrumentList();
	pLineList->m_pRoutList = OnCreateRoutList();
	InitializeCriticalSection(&pLineList->m_oSecLineList);
	return pLineList;
}
// ���ò��߶��нṹ��
void OnResetLineList(m_oLineListStruct* pLineList)
{
	if (pLineList == NULL)
	{
		return;
	}
	EnterCriticalSection(&pLineList->m_oSecLineList);
	// ������������
	OnResetInstrumentList(pLineList->m_pInstrumentList);
	// ����·�ɶ���
	OnResetRoutList(pLineList->m_pRoutList);
	LeaveCriticalSection(&pLineList->m_oSecLineList);
}
// ��ʼ�����߶��нṹ��
void OnInitLineList(m_oLineListStruct* pLineList, m_oConstVarStruct* pConstVar)
{
	if (pConstVar == NULL)
	{
		return;
	}
	if (pLineList == NULL)
	{
		AddMsgToLogOutPutList(pConstVar->m_pLogOutPut, "OnInitLineList", "",
			ErrorType, IDS_ERR_PTRISNULL);
		return;
	}
	EnterCriticalSection(&pLineList->m_oSecLineList);
	// ��ʼ���������нṹ��
	OnInitInstrumentList(pLineList->m_pInstrumentList, pConstVar);
	// ��ʼ��·�ɶ��нṹ��
	OnInitRoutList(pLineList->m_pRoutList, pConstVar);
	LeaveCriticalSection(&pLineList->m_oSecLineList);
}
// �رղ��߶��нṹ��
void OnCloseLineList(m_oLineListStruct* pLineList)
{
	if (pLineList == NULL)
	{
		return;
	}
	EnterCriticalSection(&pLineList->m_oSecLineList);
	// �ͷ�����������Դ
	OnCloseInstrumentList(pLineList->m_pInstrumentList);
	// �ͷ�·�ɶ�����Դ
	OnCloseRoutList(pLineList->m_pRoutList);
	LeaveCriticalSection(&pLineList->m_oSecLineList);
}
// �ͷŲ��߶��нṹ��
void OnFreeLineList(m_oLineListStruct* pLineList)
{
	if (pLineList == NULL)
	{
		return;
	}
	EnterCriticalSection(&pLineList->m_oSecLineList);
	// �ͷ��������нṹ����Դ
	OnFreeInstrumentList(pLineList->m_pInstrumentList);
	// �ͷ�·�ɶ��нṹ����Դ
	OnFreeRoutList(pLineList->m_pRoutList);
	LeaveCriticalSection(&pLineList->m_oSecLineList);
	DeleteCriticalSection(&pLineList->m_oSecLineList);
	delete pLineList;
}