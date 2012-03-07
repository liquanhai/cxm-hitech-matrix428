#include "StdAfx.h"
#include "ProcessTypes.h"
/**
 * @brief ���캯��
 */
CProcessTypes::CProcessTypes(void)
{
}
/**
 * @brief ��������
 */
CProcessTypes::~CProcessTypes(void)
{
	int i,nCount = m_AllProcess.GetCount();
	for (i=0;i<nCount;i++)
	{
		if(m_AllProcess[i])
		{
			delete m_AllProcess[i];
			m_AllProcess[i] = NULL;
		}	
	}
	m_AllProcess.RemoveAll();
}
/**
 * @brief ɾ�����еĴ������Ͷ���
 * @note  ɾ���ö����б���Ĵ������Ͷ��󣬲���ն���ָ�����顣
 * @param void
 * @return void
 */
void CProcessTypes:: RemoveAll(void)
{
	int i,nCount = m_AllProcess.GetCount();
	for (i=0;i<nCount;i++)
	{
		if(m_AllProcess[i])
		{
			delete m_AllProcess[i];
			m_AllProcess[i] = NULL;
		}	
	}
	m_AllProcess.RemoveAll();
}

/**
 * @brief ��ô������Ͷ���
 * @note  ���ش������ͱ���ָ��λ�õĴ������Ͷ���
 * @param int iIndex������ֵ��������0��ʼ
 * @return �ɹ����ش������Ͷ���ָ�룬ʧ���򷵻�NULL
 */
CProcessType* CProcessTypes::GetProcessType(int iIndex)
{
	int nCount = GetCount();
	if(iIndex>=nCount)
		return NULL;
	return m_AllProcess[iIndex];
}
/**
 * @brief ��������
 * @note  ���㴦�����Ͷ��������
 * @param void
 * @return �������Ͷ��������
 */
int CProcessTypes::GetCount(void)
{
	return m_AllProcess.GetCount();
}
/**
 * @brief ����һ���������Ͷ���
 * @note  �������Ͷ�����β������һ���������Ͷ���
 * @param CProcessType* pProcess���������Ͷ���
 * @return �����������е�λ��
 */
int CProcessTypes::Add(CProcessType* pProcess)
{
	return m_AllProcess.Add(pProcess);
}

/**
 * @brief ͨ���������ͱ�Ų��Ҷ���
 * @note  ͨ���������ͱ�Ų��Ҷ��󣬷��ش������Ͷ���
 * @param DWORD dwNb���������ͱ��
 * @return �ɹ��򷵻ش�������ָ�룬ʧ���򷵻�NULL
 */
CProcessType* CProcessTypes::GetProcessTypeByNb(DWORD dwNb)
{
	int i,nCount = m_AllProcess.GetCount();
	for (i=0;i<nCount;i++)
	{
		if(m_AllProcess[i]->m_dwProcessNb == dwNb)
		{			
			return m_AllProcess[i];
		}	
	}
	return NULL;
}
/**
 * @brief ͨ���������ͱ�Ų��Ҷ���
 * @note  ͨ���������ͱ�Ų��Ҷ��󣬷��ش������Ͷ����λ��
 * @param DWORD dwNb���������ͱ��
 * @return �����е�����λ�ã�ʧ���򷵻�-1
 */
int  CProcessTypes::GetProcessIndexByNb(DWORD dwNb)
{
	int i,nCount = m_AllProcess.GetCount();
	for (i=0;i<nCount;i++)
	{
		if(m_AllProcess[i]->m_dwProcessNb == dwNb)
		{			
			return i;
		}	
	}
	return -1;
}