#include "StdAfx.h"
#include "ShotSpreads.h"

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////

/*
CShotSpreadEx::CShotSpreadEx(void) : CShotSpread()
{
}
CShotSpreadEx::~CShotSpreadEx(void) 
{
	m_arrSpreadDesc.RemoveAll();
}
*/
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
/**
 * @brief ���캯��
 */
CShotSpreads::CShotSpreads(void)
{
}
/**
 * @brief ��������
 */
CShotSpreads::~CShotSpreads(void)
{
	RemoveAll();
}
/**
 * @brief ɾ�����вɼ����ж����ͷ��ڴ�
 * @note  ɾ�����вɼ����ж����ͷ��ڴ�
 * @param void
 * @return void
 */
void CShotSpreads::RemoveAll()
{
	int i,nCount = m_AllSpread.GetCount();
	for (i=0;i<nCount;i++)
	{
		if(m_AllSpread[i])
		{
			delete m_AllSpread[i];
			m_AllSpread[i] = NULL;
		}		
	}
	m_AllSpread.RemoveAll();
}
/**
 * @brief ���ָ��λ�õĲɼ����ж���
 * @note  ���زɼ����б���ָ��λ�õ����ж���
 * @param int iIndex������ֵ��������0��ʼ
 * @return �ɹ�������Դָ�룬ʧ���򷵻�NULL
 */
CShotSpread* CShotSpreads::GetShotSpread(int iIndex)
{
	int nCount = GetCount();
	if(iIndex>=nCount)
		return NULL;

	return m_AllSpread[iIndex];
}
/**
 * @brief ��������
 * @note  ����ɼ����б��ж���Ĳɼ���������
 * @param void
 * @return �����ܵĲɼ�������
 */
int CShotSpreads::GetCount(void)
{
	return m_AllSpread.GetCount();
}

/**
 * @brief ����һ���ɼ�����
 * @note  ��ɼ����б��β������һ���ɼ����ж���
 * @param CShotSpread* pSrc���ɼ����ж���
 * @return �����������е�λ��
 */
int CShotSpreads::Add(CShotSpread* pSrc)
{
	return m_AllSpread.Add(pSrc);
}

/**
 * @brief ͨ���ɼ����б�Ų��Ҷ���
 * @note  ͨ���ɼ����б�Ų��Ҷ��󣬷��زɼ����ж���
 * @param DWORD dwNb���ɼ����б��
 * @return �ɹ��򷵻زɼ�����ָ�룬ʧ���򷵻�NULL
 */
CShotSpread* CShotSpreads::GetShotSpreadBySN(DWORD dwSN)
{
	CShotSpread* pSpread=NULL;
	int i,nCount = GetCount();
	for(i=0;i<nCount;i++)
	{
		pSpread = m_AllSpread[i];
		if(pSpread->m_dwNb == dwSN)
			return pSpread;
	}
	return NULL;
}