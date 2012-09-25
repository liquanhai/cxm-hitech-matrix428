#include "stdafx.h"
#include "MatrixServerDll.h"

// ����·����Ϣ
void OnRoutReset(m_oRoutStruct* pRout)
{
	if (pRout == NULL)
	{
		return;
	}
	// �����Ƿ�ʹ����
	pRout->m_bInUsed = false;
	// ·�ɷ��� 1-�ϣ�2-�£�3-��4��
	pRout->m_iRoutDirection = 0;
	// ·��ͷ����
	pRout->m_pHead = NULL;
	// ·��β����
	pRout->m_pTail = NULL;
	// ·����������
	pRout->m_olsRoutInstrument.clear();
	// ·��ʱ��
	pRout->m_uiRoutTime = 0xFFFF0000;
	// ·���Ƿ�Ϊ������·��
	pRout->m_bRoutLaux = false;
	// ·���Ƿ���յ�ADC���ò���Ӧ��
	pRout->m_bADCSetReturn = false;
	// ·���Ƿ���ADC��������֡
	pRout->m_bADCSetRout = true;
	// ��·�ɷ����������ĸ���
	pRout->m_uiInstrumentNum = 0;
}
// ����·�ɶ����·��ʱ��
void UpdateRoutTime(unsigned int uiRoutIP, hash_map<unsigned int, m_oRoutStruct*>* pMap)
{
	if (pMap == NULL)
	{
		return;
	}
	m_oRoutStruct* pRout = NULL;
	unsigned int uiIP = 0;
	uiIP = uiRoutIP;
	while(1)
	{
		if (TRUE == IfIndexExistInRoutMap(uiIP, pMap))
		{
			pRout = GetRout(uiIP, pMap);
			// ·��ʱ��
			pRout->m_uiRoutTime = GetTickCount();
			if (pRout->m_uiRoutIP == 0)
			{
				break;
			}
			uiIP = pRout->m_pHead->m_uiRoutIP;
		}
		else
		{
			break;
		}
	}
}
// ·�ɵ�ַ�Ƿ��Ѽ���������
BOOL IfIndexExistInRoutMap(unsigned int uiRoutIP, 
	hash_map<unsigned int, m_oRoutStruct*>* pRoutMap)
{
	if (pRoutMap == NULL)
	{
		return FALSE;
	}
	BOOL bResult = FALSE;
	hash_map<unsigned int, m_oRoutStruct*>::iterator iter;
	iter = pRoutMap->find(uiRoutIP);
	if (iter != pRoutMap->end())
	{
		bResult = TRUE;
	}
	else
	{
		bResult = FALSE;
	}
	return bResult;
}
// ����һ��·��
void AddRout(unsigned int uiIndex, m_oRoutStruct* pRout, 
	hash_map<unsigned int, m_oRoutStruct*>* pRoutMap)
{
	if ((pRout == NULL) || (pRoutMap == NULL))
	{
		return;
	}
	if (false == IfIndexExistInRoutMap(uiIndex, pRoutMap))
	{
		pRoutMap->insert(hash_map<unsigned int, m_oRoutStruct*>::value_type (uiIndex, pRout));
	}
}
// �������������ţ���������õ�һ��·��ָ��
m_oRoutStruct* GetRout(unsigned int uiIndex, 
	hash_map<unsigned int, m_oRoutStruct*>* pRoutMap)
{
	if (pRoutMap == NULL)
	{
		return NULL;
	}
	hash_map<unsigned int, m_oRoutStruct*>::iterator iter;
	iter = pRoutMap->find(uiIndex);
	return iter->second;
}

// �������������ţ�����������ɾ��һ��·��
void DeleteRout(unsigned int uiIndex, 
	hash_map<unsigned int, m_oRoutStruct*>* pRoutMap)
{
	if (pRoutMap == NULL)
	{
		return;
	}
	if (pRoutMap->size() == 0)
	{
		return;
	}
	hash_map<unsigned int, m_oRoutStruct*>::iterator iter;
	iter = pRoutMap->find(uiIndex);
	if (iter != pRoutMap->end())
	{
		pRoutMap->erase(iter);
	}
}
// ��·��IP�õ�·�ɽṹ��ָ��
bool GetRoutByRoutIP(unsigned int uiRoutIP, 
	m_oRoutListStruct* pRoutList, m_oRoutStruct** ppRout)
{
	bool bReturn = false;
	// ��·���������ҵ���·��
	if (TRUE == IfIndexExistInRoutMap(uiRoutIP, &pRoutList->m_oRoutMap))
	{
		*ppRout = GetRout(uiRoutIP, &pRoutList->m_oRoutMap);
		bReturn = true;
	}
	return bReturn;
}