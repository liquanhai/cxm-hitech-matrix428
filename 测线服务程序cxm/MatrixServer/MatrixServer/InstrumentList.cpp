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
	// ���SN����������
	m_oSNInstrumentMap.clear();
	// ���IP��ַ����������
	m_oIPInstrumentMap.clear();
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
	// ���SN����������
	m_oSNInstrumentMap.clear();
	// ���IP��ַ����������
	m_oIPInstrumentMap.clear();
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
	// ���SN����������
	m_oSNInstrumentMap.clear();
	// ���IP��ַ����������
	m_oIPInstrumentMap.clear();
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
void CInstrumentList::AddInstrumentToSNMap(unsigned int uiIndex, CInstrument* pInstrument)
{
	m_oSNInstrumentMap.insert(hash_map<unsigned int, CInstrument*>::value_type (uiIndex, pInstrument));
}

// �ж������������Ƿ��Ѽ���������
//************************************
// Method:    IfIndexExistInMap
// FullName:  CInstrumentList::IfIndexExistInMap
// Access:    public 
// Returns:   BOOL
// Qualifier:
// Parameter: unsigned int uiIndex
//************************************
BOOL CInstrumentList::IfIndexExistInSNMap(unsigned int uiIndex)
{
	BOOL bResult = FALSE;
	hash_map<unsigned int, CInstrument*>::iterator iter;
	iter = m_oSNInstrumentMap.find(uiIndex);
	if (iter != m_oSNInstrumentMap.end())
	{
		bResult = TRUE;
	}
	else
	{
		bResult = FALSE;
	}
	return bResult;
}

// �������������ţ���������õ�����ָ��
//************************************
// Method:    GetInstrumentFromMap
// FullName:  CInstrumentList::GetInstrumentFromMap
// Access:    public 
// Returns:   BOOL
// Qualifier:
// Parameter: unsigned int uiIndex
// Parameter: CInstrument *  & pInstrument
//************************************
BOOL CInstrumentList::GetInstrumentFromSNMap(unsigned int uiIndex, CInstrument* &pInstrument)
{
	BOOL bResult = FALSE;
	hash_map<unsigned int, CInstrument*>::iterator iter;
	iter = m_oSNInstrumentMap.find(uiIndex);
	if (iter != m_oSNInstrumentMap.end())
	{
		pInstrument = iter->second;
		bResult = TRUE;
	}
	else
	{
		bResult = FALSE;
	}
	return bResult;
}

// ��һ����������IP��ַ������
//************************************
// Method:    AddInstrumentToIPMap
// FullName:  CInstrumentList::AddInstrumentToIPMap
// Access:    public 
// Returns:   void
// Qualifier:
// Parameter: unsigned int uiIndex
// Parameter: CInstrument * pInstrument
//************************************
void CInstrumentList::AddInstrumentToIPMap(unsigned int uiIndex, CInstrument* pInstrument)
{
	m_oIPInstrumentMap.insert(hash_map<unsigned int, CInstrument*>::value_type (uiIndex, pInstrument));
}

// �ж������������Ƿ��Ѽ���IP��ַ������
//************************************
// Method:    IfIndexExistInIPMap
// FullName:  CInstrumentList::IfIndexExistInIPMap
// Access:    public 
// Returns:   BOOL
// Qualifier:
// Parameter: unsigned int uiIndex
//************************************
BOOL CInstrumentList::IfIndexExistInIPMap(unsigned int uiIndex)
{
	BOOL bResult = FALSE;
	hash_map<unsigned int, CInstrument*>::iterator iter;
	iter = m_oIPInstrumentMap.find(uiIndex);
	if (iter != m_oIPInstrumentMap.end())
	{
		bResult = TRUE;
	}
	else
	{
		bResult = FALSE;
	}
	return bResult;
}

// ��������IP��ַ�����ţ���IP��ַ������õ�����ָ��
//************************************
// Method:    GetInstrumentFromIPMap
// FullName:  CInstrumentList::GetInstrumentFromIPMap
// Access:    public 
// Returns:   BOOL
// Qualifier:
// Parameter: unsigned int uiIndex
// Parameter: CInstrument *  & pInstrument
//************************************
BOOL CInstrumentList::GetInstrumentFromIPMap(unsigned int uiIndex, CInstrument* &pInstrument)
{
	BOOL bResult = FALSE;
	hash_map<unsigned int, CInstrument*>::iterator iter;
	iter = m_oIPInstrumentMap.find(uiIndex);
	if (iter != m_oIPInstrumentMap.end())
	{
		pInstrument = iter->second;
		bResult = TRUE;
	}
	else
	{
		bResult = FALSE;
	}
	return bResult;
}