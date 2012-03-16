#include "stdafx.h"
#include "MatrixServerDll.h"

// �ж��������Ƿ��Ѽ���������
BOOL IfIndexExistInADCFrameLostMap(m_oADCLostFrameKeyStruct Key, 
	map<m_oADCLostFrameKeyStruct, m_oADCLostFrameStruct>* pMap)
{
	if (pMap == NULL)
	{
		return FALSE;
	}
	BOOL bResult = FALSE;
	map<m_oADCLostFrameKeyStruct, m_oADCLostFrameStruct>::iterator iter;
	iter = pMap->find(Key);
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
// ���ӵ�����
void AddToADCFrameLostMap(m_oADCLostFrameKeyStruct Key, 
	m_oADCLostFrameStruct oLostFrame, map<m_oADCLostFrameKeyStruct, m_oADCLostFrameStruct>* pMap)
{
	if (pMap == NULL)
	{
		return;
	}
	if (false == IfIndexExistInADCFrameLostMap(Key, pMap))
	{
		pMap->insert(map<m_oADCLostFrameKeyStruct, m_oADCLostFrameStruct>::value_type (Key, oLostFrame));
	}
}
// �������������ţ���������õ�����ָ��
ADCLostFrame_Struct* GetFromADCFrameLostMap(m_oADCLostFrameKeyStruct Key, 
	map<m_oADCLostFrameKeyStruct, m_oADCLostFrameStruct>* pMap)
{
	if (pMap == NULL)
	{
		return NULL;
	}
	map<m_oADCLostFrameKeyStruct, m_oADCLostFrameStruct>::iterator iter;
	iter = pMap->find(Key);
	return &iter->second;
}
