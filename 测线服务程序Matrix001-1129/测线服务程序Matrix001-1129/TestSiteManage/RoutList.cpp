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
	// ·������
	m_uiCountAll = 2048;
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
		m_olsRoutFree.AddTail(&m_pArrayRout[i]);
	}
}

/**
* �ر�
* @param void
* @return void
*/
void CRoutList::OnClose()
{
	// ��տ���·�ɶ���
	m_olsRoutFree.RemoveAll();
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
	// ��տ���·�ɶ���
	m_olsRoutFree.RemoveAll();
	// ����·������
	m_uiCountFree = m_uiCountAll;
	// �������·�ɶ���
	for(unsigned int i = 0; i < m_uiCountAll; i++)
	{
		// ����·��
		m_pArrayRout[i].OnReset();
		// ·�ɼ��ڿ���·�ɶ���β��
		m_olsRoutFree.AddTail(&m_pArrayRout[i]);
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

	if(m_uiCountFree > 0)	//�п���·��
	{
		// �ӿ���·�ɶ���ͷ���õ�һ������·��
		pRout = m_olsRoutFree.RemoveHead();
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
	m_olsRoutFree.AddTail(pRout);
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