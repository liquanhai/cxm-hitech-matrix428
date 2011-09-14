#include "StdAfx.h"
#include "PointList.h"

CPointList::CPointList()
{
}

CPointList::~CPointList()
{
}

/**
* ��ʼ��
* @param void
* @return void
*/
void CPointList::OnInit()
{
	// ���ɲ������
	m_pArrayPoint = new CPointSetupData[m_uiCountAll];
	// ʹ���в�������
	m_uiCountUsed = 0;
	// ���в������
	m_uiCountFree = m_uiCountAll;
	for(unsigned int i = 0; i < m_uiCountAll; i++)
	{
		// ����ڲ�������е�λ��
		m_pArrayPoint[i].m_uiIndex = i;
		// ���ò��
		m_pArrayPoint[i].OnReset();
	}
}

/**
* ���¼���
* @param void
* @return void
*/
void CPointList::OnReload()
{
	// ʹ���в�������
	m_uiCountUsed = 0;
	// ���в������
	m_uiCountFree = m_uiCountAll;
	for(unsigned int i = 0; i < m_uiCountAll; i++)
	{
		// ���ò��
		m_pArrayPoint[i].OnReset();
	}
	// ���������
	m_oPointMap.RemoveAll();
}

/**
* �ر�
* @param void
* @return void
*/
void CPointList::OnClose()
{
	// ɾ���������
	delete[] m_pArrayPoint;
	// ���������
	m_oPointMap.RemoveAll();
}

/**
* �õ�һ�����в��
* @param void
* @return CChannelSetupData* ���в�� NULL��û�п��в��
*/
CPointSetupData* CPointList::GetFreePoint()
{
	CPointSetupData* pPoint = NULL;

	if(m_uiCountFree > 0)	//�п��в��
	{
		pPoint = &m_pArrayPoint[m_uiCountUsed];
		pPoint->m_bInUsed = true;	// ���ò��Ϊʹ����
		m_uiCountFree--;	// ���в��������1
		m_uiCountUsed++;	// ʹ���в���������1
	}
	return pPoint;
}

/**
* ���������������
* @param unsigned int uiIndex ������
* @param CPointSetupData* pPoint ���ָ��
* @return void
*/
void CPointList::AddPointToMap(unsigned int uiIndex, CPointSetupData* pPoint)
{
	m_oPointMap.SetAt(uiIndex, pPoint);
}

/**
* ����������Ƿ��Ѽ���������
* @param unsigned int uiIndex ������
* @return BOOL TRUE���ǣ�FALSE����
*/
BOOL CPointList::IfIndexExistInMap(unsigned int uiIndex)
{
	CPointSetupData* pPoint = NULL;
	return m_oPointMap.Lookup(uiIndex, pPoint);
}

/**
* ��������õ�һ�����
* @param unsigned int uiIndex ������
* @param CPointSetupData* &pPoint ���ָ�룬���õ���
* @return BOOL TRUE���ɹ���FALSE��ʧ��
*/
BOOL CPointList::GetPointFromMap(unsigned int uiIndex, CPointSetupData* &pPoint)
{
	return m_oPointMap.Lookup(uiIndex, pPoint);
}

/**
* ���������������ڲ�������еõ�һ�����
* @param unsigned int uiIndex ����������
* @return CPointSetupData* ���
*/
CPointSetupData* CPointList::GetPointByIndex(unsigned int uiIndex)
{
	return &m_pArrayPoint[uiIndex];
}

/**
* ���ݲ��ߺš����ţ����������еõ����
* @param unsigned int uiNbLine ���ߺ�
* @param unsigned int uiNbPoint ����
* @return CPointSetupData* ��� NULL��û�в��
*/
CPointSetupData* CPointList::GetPoint(unsigned int uiNbLine, unsigned int uiNbPoint)
{
	CPointSetupData* pPoint = NULL;
	unsigned int m_uiIndexPoint = CPointSetupData::CreateIndexPoint(uiNbLine, uiNbPoint);
	if(TRUE == GetPointFromMap(m_uiIndexPoint, pPoint))
	{
		return pPoint;
	}
	return NULL;
}