#include "StdAfx.h"

#include "IndexInstrumentMap.h"

CIndexInstrumentMap::CIndexInstrumentMap(void)
{
}

CIndexInstrumentMap::~CIndexInstrumentMap(void)
{
}

// ��ʼ��
void CIndexInstrumentMap::OnInit()
{

}

// �ر�
void CIndexInstrumentMap::OnClose()
{
	// ɾ����������
	DeleteInstrumentAll();
}

// ����
void CIndexInstrumentMap::OnReset()
{
	// ɾ����������
	DeleteInstrumentAll();
}

// ����һ������
void CIndexInstrumentMap::AddInstrument(unsigned int uiIndex, CInstrument* pInstrument)
{
	m_oInstrumentMap.SetAt(uiIndex, pInstrument);
}

// �����������Ƿ��Ѽ���������
BOOL CIndexInstrumentMap::IfIndexExistInMap(unsigned int uiIndex)
{
	CInstrument* pInstrument = NULL;
	return m_oInstrumentMap.Lookup(uiIndex, pInstrument);
}

// �õ�һ������
BOOL CIndexInstrumentMap::GetInstrument(unsigned int uiIndex, CInstrument* &pInstrument)
{
	return m_oInstrumentMap.Lookup(uiIndex, pInstrument);
}

// ɾ��һ������
void CIndexInstrumentMap::DeleteInstrument(unsigned int uiIndex)
{
	m_oInstrumentMap.RemoveKey(uiIndex);
}

// ɾ����������
void CIndexInstrumentMap::DeleteInstrumentAll(void)
{
	m_oInstrumentMap.RemoveAll();
}

// �õ��׸�����λ��
POSITION CIndexInstrumentMap::GetFirstInstrumentPosition()
{
	POSITION pos = m_oInstrumentMap.GetStartPosition();
	return pos;
}

// �õ���һ������
void CIndexInstrumentMap::GetNextInstrumentByPosition(POSITION &pos, CInstrument* &pInstrument)
{
	unsigned int uiIP;
	return m_oInstrumentMap.GetNextAssoc(pos, uiIP, pInstrument);
}