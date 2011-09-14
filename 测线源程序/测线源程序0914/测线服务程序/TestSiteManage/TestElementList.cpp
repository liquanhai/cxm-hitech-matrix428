#include "StdAfx.h"
#include "TestElementList.h"

CTestElementList::CTestElementList()
{
	// ÿ���β�����������ݸ���
	m_uiBatchDataCountMax = 50;
}

CTestElementList::~CTestElementList()
{
}

/**
* ��ʼ��
* @param void
* @return void
*/
void CTestElementList::OnInit()
{
	// ���ɵ�Ԫ����
	m_pArrayTestElementData = new CTestElementData[m_uiCountAll];
	// ʹ��������
	m_uiCountUsed = 0;
	// ��������
	m_uiCountFree = m_uiCountAll;
	for(unsigned int i = 0; i < m_uiCountAll; i++)
	{
		// ��Ԫ�ڵ�Ԫ�����е�λ��
		m_pArrayTestElementData[i].m_uiIndex = i;
		// ���õ�Ԫ
		m_pArrayTestElementData[i].Reset();
	}
}

/**
* ����
* @param void
* @return void
*/
void CTestElementList::OnReset()
{
	// ʹ���е�Ԫ����
	m_uiCountUsed = 0;
	// ���е�Ԫ����
	m_uiCountFree = m_uiCountAll;
	for(unsigned int i = 0; i < m_uiCountUsed; i++)
	{
		// ���õ�Ԫ
		m_pArrayTestElementData[i].Reset();
	}
	// ���������
	m_oTestElementDataMap.RemoveAll();
}

/**
* �ر�
* @param void
* @return void
*/
void CTestElementList::OnClose()
{
	// ɾ����Ԫ����
	delete[] m_pArrayTestElementData;
	// ���������
	m_oTestElementDataMap.RemoveAll();
}

/**
* ���ã�Ϊһ���µĲ�������
* @param void
* @return void
*/
void CTestElementList::ResetForNewTestRequest()
{
	for(unsigned int i = 0; i < m_uiCountUsed; i++)
	{
		// ���õ�Ԫ��Ϊһ���µĲ�������
		m_pArrayTestElementData[i].ResetForNewTestRequest();
	}
}

/**
* ����һ����Ԫ��������
* @param unsigned int uiIndex ��Ԫ����
* @param CTestElementData* pTestElementData ��Ԫָ��
* @return void
*/
void CTestElementList::AddTestElementDataToMap(unsigned int uiIndex, CTestElementData* pTestElementData)
{
	m_oTestElementDataMap.SetAt(uiIndex, pTestElementData);
}

/**
* ��Ԫ�������Ƿ��Ѽ���������
* @param unsigned int uiIndex ��Ԫ����
* @return BOOL TRUE���ǣ�FALSE����
*/
BOOL CTestElementList::IfIndexExistInMap(unsigned int uiIndex)
{
	CTestElementData* pTestElementData = NULL;
	return m_oTestElementDataMap.Lookup(uiIndex, pTestElementData);
}

/**
* �������������ţ���������õ���Ԫָ��
* @param unsigned int uiIndex ������
* @param CTestElementData* &pTestElementData	��Ԫָ�룬���õ���
* @return BOOL TRUE���ɹ���FALSE��ʧ��
*/
BOOL CTestElementList::GetTestElementDataFromMap(unsigned int uiIndex, CTestElementData* &pTestElementData)
{
	return m_oTestElementDataMap.Lookup(uiIndex, pTestElementData);
}

/**
* ���ݵ�Ԫ�����������ţ��õ���Ԫָ��
* @param unsigned int uiIndex ��Ԫ������������
* @return CTestElementData* ��Ԫָ��
*/
CTestElementData* CTestElementList::GetTestElementDataByIndex(unsigned int uiIndex)
{
	return &m_pArrayTestElementData[uiIndex];
}

/**
* �����μ��㣬��������������
* @param void
* @return unsigned int ��������������
*/
unsigned int CTestElementList::GetTestDataBatchCount()
{
	unsigned int uiBatchCount = 0;
	uiBatchCount = m_uiCountUsed / m_uiBatchDataCountMax;
	if((m_uiCountUsed % m_uiBatchDataCountMax) > 0)
	{
		uiBatchCount++;
	}
	return uiBatchCount;
}

/**
* �����μ��㣬��������������
* @param unsigned int uiTestType ��������
* @param unsigned int uiBatchIndex ����������������
* @param unsigned unsigned int uiDataSize ÿ����������ռ���ֽ��������ô�ֵ
* @paramunsigned short usDataCount �������ݸ��������ô�ֵ
* @return bool true���ɹ���false��ʧ��
*/
bool CTestElementList::GetTestDataByBatchIndex(unsigned int uiTestType, unsigned int uiBatchIndex, unsigned int& uiDataSize, unsigned short& usDataCount)
{
	bool bReturn = true;
	unsigned int uiBatchCount = 0;
	usDataCount = m_uiBatchDataCountMax;
	uiBatchCount = m_uiCountUsed / m_uiBatchDataCountMax;
	if((m_uiCountUsed % m_uiBatchDataCountMax) > 0)
	{
		uiBatchCount++;
		if((uiBatchIndex + 1) == uiBatchCount)
		{
			usDataCount = m_uiCountUsed % m_uiBatchDataCountMax;
		}
	}
	int iPosition = 0;
	for(unsigned int i = uiBatchIndex * m_uiBatchDataCountMax; i < uiBatchIndex * m_uiBatchDataCountMax + ((unsigned int)usDataCount); i++)
	{
		uiDataSize = m_pArrayTestElementData[i].GetTestResult(uiTestType, &m_pTestData[iPosition]);
		iPosition = iPosition + uiDataSize;
	}
	return bReturn;
}