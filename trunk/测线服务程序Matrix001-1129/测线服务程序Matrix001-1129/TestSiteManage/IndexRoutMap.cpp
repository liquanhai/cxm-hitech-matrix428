#include "StdAfx.h"

#include "IndexRoutMap.h"

CIndexRoutMap::CIndexRoutMap()
{
}

CIndexRoutMap::~CIndexRoutMap()
{
}

/**
* ��ʼ��
* @param void
* @return void
*/
void CIndexRoutMap::OnInit()
{

}

/**
* �ر�
* @param void
* @return void
*/
void CIndexRoutMap::OnClose()
{
	// ɾ������·��
	DeleteRoutAll();
}

/**
* ����
* @param void
* @return void
*/
void CIndexRoutMap::OnReset()
{
	// ɾ������·��
	DeleteRoutAll();
}

/**
* ����һ��·��
* @param unsigned int uiIndex ������
* @param CRout* pRout	·��ָ��
* @return void
*/
// 
void CIndexRoutMap::AddRout(unsigned int uiIndex, CRout* pRout)
{
	m_oRoutMap.SetAt(uiIndex, pRout);
}

/**
* �������������ţ���������õ�һ��·��ָ��
* @param unsigned int uiIndex ������
* @param CRout* &pRout	·��ָ�룬���õ���
* @return BOOL TRUE���ɹ���FALSE��ʧ��
*/
BOOL CIndexRoutMap::GetRout(unsigned int uiIndex, CRout* &pRout)
{
	return m_oRoutMap.Lookup(uiIndex, pRout);
}

/**
* �������������ţ�����������ɾ��һ��·��
* @param unsigned int uiIndex ������
* @return void
*/
void CIndexRoutMap::DeleteRout(unsigned int uiIndex)
{
	m_oRoutMap.RemoveKey(uiIndex);
}

/**
* ɾ��������������·��
* @param void
* @return void
*/
void CIndexRoutMap::DeleteRoutAll()
{
	m_oRoutMap.RemoveAll();
}

/**
* ·�ɵ�ַ�Ƿ��Ѽ���������
* @param unsigned int uiRoutIP ·�ɵ�ַ
* @return BOOL TRUE���ǣ�FALSE����
*/
BOOL CIndexRoutMap::IfIndexExistInMap(unsigned int uiRoutIP)
{
	CRout* pRout = NULL;
	return m_oRoutMap.Lookup(uiRoutIP, pRout);
}

/**
* �ж�·���Ƿ������û��ʱ��������·��
* @param CRout* &pRout	·��ָ��
* @return BOOL TRUE���ǣ�FALSE����
*/
bool CIndexRoutMap::JudgeRoutIsLongestTime(CRout* pRout)
{
	if(0 == pRout->m_uiDelayProcTime)
	{
		return true;
	}

	CRout* pRoutFind = NULL;	// ·�ɶ���ָ��
	POSITION pos = NULL;	// λ��	
	unsigned int uiKey;	// ������	
	pos = m_oRoutMap.GetStartPosition();	// �õ���������ʼ·��λ��
	while(NULL != pos)
	{
		pRoutFind = NULL;		
		m_oRoutMap.GetNextAssoc(pos, uiKey, pRoutFind);	// �õ�·�ɶ���
		if(NULL != pRoutFind)	// �õ�·�ɶ���
		{
			if(NULL != pRoutFind->m_pTail)	// ����������
			{
				if(0 != pRoutFind->m_pTail->m_uiIP)	// β�����ѷ���IP��ַ
				{
					if(pRout->m_uiDelayProcTime > pRoutFind->m_uiDelayProcTime)
					{
						return false;
					}
				}
			}
		}
	}
	return true;
}