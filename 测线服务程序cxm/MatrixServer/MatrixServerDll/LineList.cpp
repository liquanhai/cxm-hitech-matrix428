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
	// ����״̬Ϊ���ȶ�
	pLineList->m_bLineStableChange = false;
	// ����ϵͳ�����仯��ʱ��
	pLineList->m_uiLineChangeTime = 0;
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
	// ����״̬Ϊ���ȶ�
	pLineList->m_bLineStableChange = false;
	// ����ϵͳ�����仯��ʱ��
	pLineList->m_uiLineChangeTime = 0;
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
	pLineList = NULL;
}

// �õ���������λ��
void QueryInstrumentLocation(char* pChar, int& iPos, m_oLineListStruct* pLineList)
{
	map<m_oInstrumentLocationStruct, m_oInstrumentStruct*>::iterator iterLocation;
	// ��SN��������ͻ��˵�����λ�������������
	EnterCriticalSection(&pLineList->m_oSecLineList);
	for (iterLocation = pLineList->m_pInstrumentList->m_oInstrumentLocationMap.begin();
		iterLocation != pLineList->m_pInstrumentList->m_oInstrumentLocationMap.end(); iterLocation++)
	{
		memcpy(&pChar[iPos], &iterLocation->first.m_iLineIndex, 4);
		iPos += 4;
		memcpy(&pChar[iPos], &iterLocation->first.m_iPointIndex, 4);
		iPos += 4;
		memcpy(&pChar[iPos], &iterLocation->second->m_uiSN, 4);
		iPos += 4;
	}
	LeaveCriticalSection(&pLineList->m_oSecLineList);
}