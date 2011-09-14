#include "StdAfx.h"

#include "IndexInstrumentMap.h"

CIndexInstrumentMap::CIndexInstrumentMap()
{
}

CIndexInstrumentMap::~CIndexInstrumentMap()
{
}

/**
* ��ʼ��
* @param void
* @return void
*/
void CIndexInstrumentMap::OnInit()
{

}

/**
* �ر�
* @param void
* @return void
*/
void CIndexInstrumentMap::OnClose()
{
	// ɾ����������
	DeleteInstrumentAll();
}

/**
* ����
* @param void
* @return void
*/
void CIndexInstrumentMap::OnReset()
{
	// ɾ����������
	DeleteInstrumentAll();
}

/**
* ����һ������
* @param unsigned int uiIndex ������
* @param CInstrument* pInstrument	����ָ��
* @return void
*/
void CIndexInstrumentMap::AddInstrument(unsigned int uiIndex, CInstrument* pInstrument)
{
	m_oInstrumentMap.SetAt(uiIndex, pInstrument);
}

/**
* �����������Ƿ��Ѽ���������
* @param unsigned int uiIndex ������
* @return BOOL TRUE���ǣ�FALSE����
*/
BOOL CIndexInstrumentMap::IfIndexExistInMap(unsigned int uiIndex)
{
	CInstrument* pInstrument = NULL;
	return m_oInstrumentMap.Lookup(uiIndex, pInstrument);
}

/**
* �������������ţ���������õ�һ������ָ��
* @param unsigned int uiIndex ������
* @param CInstrument* pInstrument	����ָ�룬���õ���
* @return BOOL TRUE���ɹ���FALSE��ʧ��
*/
BOOL CIndexInstrumentMap::GetInstrument(unsigned int uiIndex, CInstrument* &pInstrument)
{
	return m_oInstrumentMap.Lookup(uiIndex, pInstrument);
}

/**
* �������������ţ�����������ɾ��һ������
* @param unsigned int uiIndex ������
* @return void
*/
void CIndexInstrumentMap::DeleteInstrument(unsigned int uiIndex)
{
	m_oInstrumentMap.RemoveKey(uiIndex);
}

/**
* ɾ������������������
* @param void
* @return void
*/
void CIndexInstrumentMap::DeleteInstrumentAll()
{
	m_oInstrumentMap.RemoveAll();
}