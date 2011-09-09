#include "StdAfx.h"
#include "ShotPoints.h"
#include <math.h>
/**
 * @brief CShotPoints���캯��
 */
CShotPoints::CShotPoints(void)
{
}
/**
 * @brief CShotPoints��������
 *
 * ���ͷ�ÿ���ںŶ�������շ��ڱ�
 */
CShotPoints::~CShotPoints(void)
{
	RemoveAll();
}
/**
 * @brief ɾ�����з��ڶ���
 * @note  ɾ�����з��ڶ���
 * @param void
 * @return void
 */
void   CShotPoints::RemoveAll(void)
{
	int i,nCount = m_AllVP.GetCount();
	for (i=0;i<nCount;i++)
	{
		if(m_AllVP[i])
		{
			delete m_AllVP[i];
			m_AllVP[i] = NULL;
		}	
	}
	m_AllVP.RemoveAll();
}
/**
 * @brief �������ڱ�
 * @note  ��һ�������п���ȫ�����ڱ������ǿ����ڴ��з��ڱ�ָ�����飬
 �����ǽ����ڱ����ݿ������ö����С����øú����󣬱��ض����pPoints����ָ���ڴ�
 ��ͬһ��ķ��ڱ�����
 * @param CShotPoints* pPoints-���ڱ�
 * @return void
 */
void   CShotPoints::OnlyCopyObjectPointer(CShotPoints*  pPoints)
{
	m_AllVP.Copy(pPoints->m_AllVP);
}
/**
 * @brief ����һ���ں�
 * @note  ����ڱ��β������һ���ںŶ���
 * @param CShotPoint* pVP���ںŶ���
 * @return �����������е�λ��
 */
int CShotPoints::Add(CShotPoint* pVP)
{
	return m_AllVP.Add(pVP);
}
/**
 * @brief ��������
 * @note  ������ڱ����ܵ��ں���
 * @param void
 * @return �����ܵ��ں���
 */
int CShotPoints::GetCount(void)
{
	return m_AllVP.GetCount();
}

/**
 * @brief ���ָ��λ�õ��ںŶ���
 * @note  ���ط��ڱ���ָ��λ�õ��ںŶ���
 * @param int iIndex������ֵ��������0��ʼ
 * @return �ɹ������ں�ָ�룬ʧ���򷵻�NULL
 */
CShotPoint* CShotPoints::GetShotPoint(int iIndex)
{
	int nCount = GetCount();
	if(iIndex>=nCount)
		return NULL;

	return m_AllVP[iIndex];

}
/**
 * @brief ͨ���ڵ��Ų��Ҷ���
 * @note  ͨ���ڵ��Ų��Ҷ��󣬷����ںŶ���
 * @param DWORD dwNb���ڵ���
 * @return �ɹ��򷵻��ں�ָ�룬ʧ���򷵻�NULL
 */
CShotPoint* CShotPoints::GetShotPointByNb(DWORD dwNb)
{
	int i,nCount = m_AllVP.GetCount();
	for (i=0;i<nCount;i++)
	{
		if(m_AllVP[i]->m_dwShotNb == dwNb)
		{			
			return m_AllVP[i];
		}	
	}
	return NULL;
}
/**
 * @brief ͨ��SPL ����Դ����ߣ� �� SPN ����Դ��ţ����Ҷ���
 * @note  ͨ��SPL ����Դ����ߣ� �� SPN ����Դ��ţ����Ҷ��󣬷����ںŶ���
 * @param float fSPL,��Դ�����
 * @param float fSPN����Դ���
 * @return �ɹ��򷵻��ں�ָ�룬ʧ���򷵻�NULL
 */
CShotPoint* CShotPoints::GetShotPointBySPLSPN(float fSPL,float fSPN)
{
	int i,nCount = m_AllVP.GetCount();
	for (i=0;i<nCount;i++)
	{	// �ж�SPL��SPN�Ƿ����
		if(    abs(m_AllVP[i]->m_fSourceLine-fSPL)<0.00001 
			&& abs(m_AllVP[i]->m_fSourceNb  -fSPN)<0.00001) 
		{			
			return m_AllVP[i];
		}	
	}
	return NULL;
}