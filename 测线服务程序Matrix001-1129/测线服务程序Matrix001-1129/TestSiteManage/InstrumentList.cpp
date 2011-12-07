#include "StdAfx.h"

#include "InstrumentList.h"


CInstrumentList::CInstrumentList()
{
}

CInstrumentList::~CInstrumentList()
{
}

/**
* ��ʼ��
* @param void
* @return void
*/
void CInstrumentList::OnInit()
{
	// ������������
	m_pArrayInstrument = new CInstrument[m_uiCountAll];
	// �����������飬Ϊ�ֳ��������׼��
	m_pArrayInstrumentOutput = new CInstrument[m_uiCountAll];
	// ������������
	m_uiCountFree = m_uiCountAll;
	for(unsigned int i = 0; i < m_uiCountAll; i++)
	{
		// ���������������е�λ��
		m_pArrayInstrument[i].m_uiIndex = i;
		// ��������
		m_pArrayInstrument[i].OnReset();
		// �������ڿ�����������β��
		m_olsInstrumentFree.AddTail(&m_pArrayInstrument[i]);
	}
}

/**
* �ر�
* @param void
* @return void
*/
void CInstrumentList::OnClose()
{
	// ��տ�����������
	m_olsInstrumentFree.RemoveAll();
	// ɾ����������
	delete[] m_pArrayInstrument;
	// ɾ���������飬Ϊ�ֳ��������׼��
	delete[] m_pArrayInstrumentOutput;
}

/**
* ����
* @param void
* @return void
*/
void CInstrumentList::OnReset()
{
	// ��տ�����������
	m_olsInstrumentFree.RemoveAll();
	// ������������
	m_uiCountFree = m_uiCountAll;
	for(unsigned int i = 0; i < m_uiCountAll; i++)
	{
		// ��������
		m_pArrayInstrument[i].OnReset();
		// �������ڿ�����������β��
		m_olsInstrumentFree.AddTail(&m_pArrayInstrument[i]);
	}
}

/**
* �õ�һ����������
* @param void
* @return CInstrument* �������� NULL��û�п�������
*/
CInstrument* CInstrumentList::GetFreeInstrument()
{
	CInstrument* pInstrument = NULL;

	if(m_uiCountFree > 0)	//�п�������
	{
		pInstrument = m_olsInstrumentFree.RemoveHead();	// �ӿ��ж����еõ�һ������
		pInstrument->m_bInUsed = true;	// ��������Ϊʹ����
		m_uiCountFree--;	// ��������������1
	}
	return pInstrument;
}

/**
* ����һ����������
* @param CInstrument* pInstrument ����ָ��
* @return void
*/
void CInstrumentList::AddFreeInstrument(CInstrument* pInstrument)
{
	//��ʼ������
	pInstrument->OnReset();
	//������ж���
	m_olsInstrumentFree.AddTail(pInstrument);
	m_uiCountFree++;	// ��������������1
}

/**
* �����������鵽�������
* @param void
* @return void
*/
void CInstrumentList::CopyInstrumentArrayForOutput()
{
	memcpy(m_pArrayInstrumentOutput, m_pArrayInstrument, sizeof(CInstrument) * m_uiCountAll);
}