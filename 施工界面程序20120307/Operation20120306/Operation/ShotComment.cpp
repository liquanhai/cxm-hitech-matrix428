#include "StdAfx.h"
#include "ShotComment.h"

CShotComment::CShotComment(void)
: m_dwCommentNb(0)
, m_strLabel(_T(""))
, m_strComment(_T(""))
{
}

CShotComment::~CShotComment(void)
{
}

/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////

CShotComments::CShotComments(void)
{

}

CShotComments::~CShotComments(void)
{
	RemoveAll();
}
/**
 * @brief ɾ������ע�Ͷ���
 * @note  ɾ������ע�Ͷ���
 * @param void
 * @return void
 */
void   CShotComments::RemoveAll(void)
{
	int i,nCount = m_AllComments.GetCount();
	for (i=0;i<nCount;i++)
	{
		if(m_AllComments[i])
		{
			delete m_AllComments[i];
			m_AllComments[i] = NULL;
		}	
	}
	m_AllComments.RemoveAll();
}
/**
 * @brief ���ָ��λ�õĶ���
 * @note  ����ע�ͱ����ָ��λ�õ�ע�Ͷ���
 * @param int iIndex������ֵ��������0��ʼ
 * @return �ɹ�����ָ�룬ʧ���򷵻�NULL
 */
CShotComment* CShotComments::GetShotComment(int nIndex)
{
	int nCount = GetCount();
	if(nIndex>=nCount)
		return NULL;
	
	return m_AllComments[nIndex];
}

