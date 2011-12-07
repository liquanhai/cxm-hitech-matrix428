#include "StdAfx.h"
#include "LineList.h"

CLineList::CLineList()
{
}

CLineList::~CLineList()
{
}

/**
* ��ʼ��
* @param void
* @return void
*/
void CLineList::OnInit()
{
	// ���ɲ�������
	m_pArrayLine = new CLineSetupData[m_uiCountAll];
	// ʹ���в�������
	m_uiCountUsed = 0;
	// ���в�������
	m_uiCountFree = m_uiCountAll;
	for(unsigned int i = 0; i < m_uiCountAll; i++)
	{
		// �����ڲ��������е�λ��
		m_pArrayLine[i].m_uiIndex = i;
		// ���ò���
		m_pArrayLine[i].OnReset();
	}
}

/**
* ���¼���
* @param void
* @return void
*/
void CLineList::OnReload()
{
	// ʹ���в�������
	m_uiCountUsed = 0;
	// ���в�������
	m_uiCountFree = m_uiCountAll;
	for(unsigned int i = 0; i < m_uiCountAll; i++)
	{
		// ���ò���
		m_pArrayLine[i].OnReset();
	}
	// ���������
	m_oLineMap.RemoveAll();
}

/**
* �ر�
* @param void
* @return void
*/
void CLineList::OnClose()
{
	// ɾ����������
	delete[] m_pArrayLine;
	// ���������
	m_oLineMap.RemoveAll();
}

/**
* �õ�һ�����в���
* @param void
* @return CLineSetupData* ���в��� NULL��ʧ��
*/
CLineSetupData* CLineList::GetFreeLine()
{
	CLineSetupData* pLine = NULL;

	if(m_uiCountFree > 0)	//�п��в���
	{
		pLine = &m_pArrayLine[m_uiCountUsed];
		pLine->m_bInUsed = true;	// ���ò���Ϊʹ����
		m_uiCountFree--;	// ���в���������1
		m_uiCountUsed++;	// ʹ���в���������1
	}
	return pLine;
}

/**
* ����һ�����ߵ�������
* @param unsigned int uiIndex ���߱�ʶ��
* @param CLineSetupData* pLine ����ָ��
* @return void
*/
void CLineList::AddLineToMap(unsigned int uiIndex, CLineSetupData* pLine)
{
	m_oLineMap.SetAt(uiIndex, pLine);
}

/**
* �����������Ƿ��Ѽ���������
* @param unsigned int uiIndex ������
* @return BOOL TRUE���ǣ�FALSE����
*/
BOOL CLineList::IfIndexExistInMap(unsigned int uiIndex)
{
	CLineSetupData* pLine = NULL;
	return m_oLineMap.Lookup(uiIndex, pLine);
}

/**
* ��������õ�һ������
* @param unsigned int uiIndex ������
* @param CLineSetupData* &pLine ����ָ�룬���õ���
* @return BOOL TRUE���ɹ���FALSE��ʧ��
*/
BOOL CLineList::GetLineFromMap(unsigned int uiIndex, CLineSetupData* &pLine)
{
	return m_oLineMap.Lookup(uiIndex, pLine);
}

/**
* ���������������ڲ��������еõ�һ������
* @param unsigned int uiIndex ����������
* @return CLineSetupData* ����
*/
CLineSetupData* CLineList::GetLineByIndex(unsigned int uiIndex)
{
	return &m_pArrayLine[uiIndex];
}

/**
* ��������õ�һ������
* @param unsigned int uiNbLine ���ߺ�
* @return CLineSetupData* ���� NULL��ʧ��
*/
CLineSetupData* CLineList::GetLine(unsigned int uiNbLine)
{
	CLineSetupData* pLine = NULL;
	if(TRUE == GetLineFromMap(uiNbLine, pLine))
	{
		return pLine;
	}
	return NULL;
}