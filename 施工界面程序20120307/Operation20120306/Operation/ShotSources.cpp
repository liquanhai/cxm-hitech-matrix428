#include "StdAfx.h"
#include "ShotSources.h"
/**
 * @brief ���캯��
 */
CShotSources::CShotSources(void)
{
}
/**
 * @brief ��������
 */
CShotSources::~CShotSources(void)
{
	int i,nCount = GetCount();
	for (i=0;i<nCount;i++)
	{
		if(m_AllSrc[i])
		{
			delete m_AllSrc[i];
			m_AllSrc[i] = NULL;
		}		
	}
	m_AllSrc.RemoveAll();
}
/**
 * @brief ɾ��������Դ����
 * @note  ɾ��������Դ����
 * @param void
 * @return void
 */
void CShotSources::RemoveAll(void)
{
	int i,nCount = GetCount();
	for (i=0;i<nCount;i++)
	{
		if(m_AllSrc[i])
		{
			delete m_AllSrc[i];
			m_AllSrc[i] = NULL;
		}		
	}
	m_AllSrc.RemoveAll();
}

/**
 * @brief ������Դ������
 * @note  ��һ�������п���ȫ����Դ�������ǿ����ڴ�����Դ��ָ�����飬
 �����ǽ���Դ�����ݿ������ö����С����øú����󣬱��ض����pShotSrcs����ָ���ڴ�
 ��ͬһ�����Դ������
 * @param CShotPoints* pPoints-���ڱ�
 * @return void
 */
void CShotSources::Copy(CShotSources* pShotSrcs)
{
	m_AllSrc.Copy(pShotSrcs->m_AllSrc);
}
/**
 * @brief ���ָ��λ�õ���Դ����
 * @note  ������Դ����ָ��λ�õ���Դ����
 * @param int iIndex������ֵ��������0��ʼ
 * @return �ɹ�������Դָ�룬ʧ���򷵻�NULL
 */
CShotSource* CShotSources::GetShotSource(int iIndex)
{
	int nCount = GetCount();
	if(iIndex>=nCount)
		return NULL;

	return m_AllSrc[iIndex];
}

/**
 * @brief ��������
 * @note  ������Դ�����ܵ���Դ��
 * @param void
 * @return �����ܵ���Դ��
 */
int CShotSources::GetCount(void)
{
	return (int)m_AllSrc.GetCount();
}
/**
 * @brief ����������Դ������
 * @note  ������Դ�����ܵ�������Դ��
 * @param void
 * @return �����ܵ�������Դ��
 */
int CShotSources::GetExploCount(void)
{
	int nExploCount=0;
	int i,nCount = GetCount();
	for (i=0;i<nCount;i++)
	{
		if(m_AllSrc[i]->m_dwSourceType == SHOTTYPE_EXPLO)
		{
			nExploCount++;
		}		
	}
	return nExploCount;
}
/**
 * @brief ����ɿ���Դ������
 * @note  ������Դ�����ܵĿɿ���Դ��
 * @param void
 * @return �����ܵĿɿ���Դ��
 */
int CShotSources::GetVibroCount(void)
{
	int nVibroCount=0;
	int i,nCount = GetCount();
	for (i=0;i<nCount;i++)
	{
		if(m_AllSrc[i]->m_dwSourceType == SHOTTYPE_VIBRO)
		{
			nVibroCount++;
		}		
	}
	return nVibroCount;
}
/**
 * @brief ����һ����Դ
 * @note  ����Դ���β������һ����Դ����
 * @param CShotSource* pSrc����Դ����
 * @return �����������е�λ��
 */
int CShotSources::Add(CShotSource* pSrc)
{
	return (int)m_AllSrc.Add(pSrc);
}

/**
 * @brief ͨ����Դ��Ų��Ҷ���
 * @note  ͨ����Դ��Ų��Ҷ��󣬷�����Դ����
 * @param DWORD dwNb����Դ���
 * @return �ɹ��򷵻���Դָ�룬ʧ���򷵻�NULL
 */
CShotSource* CShotSources::GetShotSourceByNb(DWORD dwNb)
{
	int i,nCount = GetCount();
	for (i=0;i<nCount;i++)
	{
		if(m_AllSrc[i]->m_dwSourceNb == dwNb)
		{			
			return m_AllSrc[i];
		}	
	}
	return NULL;
}
/**
 * @brief ����ָ��λ�õĶ���
 * @note  ����ָ������λ�õĶ�����������Ѿ����ڣ���ɾ������Ȼ������ӣ�
 ���λ�ó�������ķ�Χ����̬�������飬������ָ��λ�õ�ֵ��
 * @param DWORD dwNb����Դ���
 * @return �ɹ��򷵻���Դָ�룬ʧ���򷵻�NULL
 */
void CShotSources::SetAt(int nIndex,CShotSource* pShotSrc)
{
	int nCount = GetCount();
	if(nIndex<nCount)
	{
		delete m_AllSrc[nIndex];
		m_AllSrc[nIndex] = pShotSrc;
	}
	else
	{
		m_AllSrc.SetAtGrow(nIndex,pShotSrc);
	}

}