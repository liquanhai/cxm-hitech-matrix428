#include "StdAfx.h"
#include "SpreadGenericData.h"

CSpreadGenericData::CSpreadGenericData(void)
{
}

CSpreadGenericData::~CSpreadGenericData(void)
{
}

/**
* ����XML
* @param CXMLDOMElement* pElement XML�ĵ��ڵ�ָ��
* @return void
*/
void CSpreadGenericData::ParseXML(CXMLDOMElement* pElement)
{
	CString strKey;
	strKey = "Nb";
	m_uiNb = CXMLDOMTool::GetElementAttributeInt(pElement, strKey);
	strKey = "Label";
	m_strLabel = CXMLDOMTool::GetElementAttributeString(pElement, strKey);
	strKey = "Line";
	m_strLine = CXMLDOMTool::GetElementAttributeString(pElement, strKey);
	strKey = "Spread";
	m_strSpread = CXMLDOMTool::GetElementAttributeString(pElement, strKey);
}

/**
* ����XML
* @param CXMLDOMElement* pElement XML�ĵ��ڵ�ָ��
* @return void
*/
void CSpreadGenericData::AddToXML(CXMLDOMElement* pElement)
{
	CString strKey;	// ����
	COleVariant oVariant;

	strKey = "Nb";
	oVariant = (long)m_uiNb;
	pElement->setAttribute(strKey, oVariant);

	strKey = "Label";
	oVariant = m_strLabel;
	pElement->setAttribute(strKey, oVariant);

	strKey = "Line";
	oVariant = m_strLine;
	pElement->setAttribute(strKey, oVariant);

	strKey = "Spread";
	oVariant = m_strSpread;
	pElement->setAttribute(strKey, oVariant);
}