#include "StdAfx.h"

#include "RoutList.h"

CRoutList::CRoutList()
{
}

CRoutList::~CRoutList()
{
}

/**
* ��ʼ��
* @param void
* @return void
*/
void CRoutList::OnInit()
{
	// ���·�ɵ�ַ����
	m_oRoutMap.clear();
	// ��տ���·�ɶ���
	m_olsRoutFree.clear();
	// ����·������
	m_uiCountFree = m_uiCountAll;
	// ����·������
	m_pArrayRout = new CRout[m_uiCountAll];
	// ����·�����飬Ϊ�ֳ��������׼��
	m_pArrayRoutOutput = new CRout[m_uiCountAll];

	// �������·�ɶ���
	for(unsigned int i = 0; i < m_uiCountAll; i++)
	{
		// ����·��IP��ַ
		m_pArrayRout[i].m_uiRoutIP = i + 1;
		// ·����·�������е�λ��
		m_pArrayRout[i].m_uiIndex = i;
		// ����·��
		m_pArrayRout[i].OnReset();
		// ·�ɼ��ڿ���·�ɶ���β��
		m_olsRoutFree.push_back(&m_pArrayRout[i]);
	}
}

/**
* �ر�
* @param void
* @return void
*/
void CRoutList::OnClose()
{
	// ���·�ɵ�ַ����
	m_oRoutMap.clear();
	// ��տ���·�ɶ���
	m_olsRoutFree.clear();
	// ɾ��·������
	delete[] m_pArrayRout;
	// ɾ��·�����飬Ϊ�ֳ��������׼��
	delete[] m_pArrayRoutOutput;
}

/**
* ����
* @param void
* @return void
*/
void CRoutList::OnReset()
{
	// ���·�ɵ�ַ����
	m_oRoutMap.clear();
	// ��տ���·�ɶ���
	m_olsRoutFree.clear();
	// ����·������
	m_uiCountFree = m_uiCountAll;
	// �������·�ɶ���
	for(unsigned int i = 0; i < m_uiCountAll; i++)
	{
		// ����·��
		m_pArrayRout[i].OnReset();
		// ·�ɼ��ڿ���·�ɶ���β��
		m_olsRoutFree.push_back(&m_pArrayRout[i]);
	}
}

/**
* �õ�һ������·��
* @param void
* @return CRout* ����·�� NULL��û�п���·��
*/
CRout* CRoutList::GetFreeRout()
{
	CRout* pRout = NULL;
	list <CRout*>::iterator iter;
	if(m_uiCountFree > 0)	//�п���·��
	{
		// �ӿ���·�ɶ���ͷ���õ�һ������·��
		iter = m_olsRoutFree.begin();
		pRout = *iter;
		m_olsRoutFree.pop_front();	
		// ·���Ƿ�ʹ����
		pRout->m_bInUsed = true;	
		// ����·�ɼ�����1
		m_uiCountFree--;
	}
	return pRout;
}

/**
* ����һ������·��
* @param CRout* pRout ·��ָ��
* @return void
*/
void CRoutList::AddFreeRout(CRout* pRout)
{
	//��ʼ��·��
	pRout->OnReset();
	//������ж���
	m_olsRoutFree.push_back(pRout);
	// ����·�ɼ�����1
	m_uiCountFree++;
}

/**
* �����������鵽�������
* @param void
* @return void
*/
void CRoutList::CopyRoutArrayForOutput()
{
	memcpy(m_pArrayRoutOutput, m_pArrayRout, sizeof(CRout) * m_uiCountAll);
}

/**
* ����һ��·��
* @param unsigned int uiIndex ������
* @param CRout* pRout	·��ָ��
* @return void
*/
// 
void CRoutList::AddRout(unsigned int uiIndex, CRout* pRout)
{
	m_oRoutMap.insert(hash_map<unsigned int, CRout*>::value_type (uiIndex, pRout));
}

/**
* �������������ţ���������õ�һ��·��ָ��
* @param unsigned int uiIndex ������
* @param CRout* &pRout	·��ָ�룬���õ���
* @return BOOL TRUE���ɹ���FALSE��ʧ��
*/
BOOL CRoutList::GetRout(unsigned int uiIndex, CRout* &pRout)
{
	BOOL bResult = FALSE;
	hash_map<unsigned int, CRout*>::iterator iter;
	iter = m_oRoutMap.find(uiIndex);
	if (iter != m_oRoutMap.end())
	{
		pRout = iter->second;
		bResult = TRUE;
	}
	else
	{
		bResult = FALSE;
	}
	return bResult;
}

/**
* �������������ţ�����������ɾ��һ��·��
* @param unsigned int uiIndex ������
* @return void
*/
void CRoutList::DeleteRout(unsigned int uiIndex)
{
	hash_map<unsigned int, CRout*>::iterator iter;
	iter = m_oRoutMap.find(uiIndex);
	if (iter != m_oRoutMap.end())
	{
		m_oRoutMap.erase(iter);
	}
}
/**
* ·�ɵ�ַ�Ƿ��Ѽ���������
* @param unsigned int uiRoutIP ·�ɵ�ַ
* @return BOOL TRUE���ǣ�FALSE����
*/
BOOL CRoutList::IfIndexExistInMap(unsigned int uiRoutIP)
{
	BOOL bResult = FALSE;
	hash_map<unsigned int, CRout*>::iterator iter;
	iter = m_oRoutMap.find(uiRoutIP);
	if (iter != m_oRoutMap.end())
	{
		bResult = TRUE;
	}
	else
	{
		bResult = FALSE;
	}
	return bResult;
}