#include "StdAfx.h"
#include "PointCodeData.h"

CPointCodeData::CPointCodeData(void)
{
}

CPointCodeData::~CPointCodeData(void)
{
}

/**
* ����XML
* @param void
* @return void
*/
void CPointCodeData::ParseXML(CXMLDOMElement* pElement)
{
	CString strKey;
	strKey = "Nb";
	m_uiNb = CXMLDOMTool::GetElementAttributeInt(pElement, strKey);
	strKey = "Label";
	m_strLabel = CXMLDOMTool::GetElementAttributeString(pElement, strKey);
	strKey = "SensorType";
	m_strSensorType = CXMLDOMTool::GetElementAttributeString(pElement, strKey);
}

/**
* ����XML
* @param CXMLDOMElement* pElement XML�ĵ��ڵ�ָ��
* @return void
*/
void CPointCodeData::AddToXML(CXMLDOMElement* pElement)
{
	CString strKey;	// ����
	COleVariant oVariant;
	strKey = "Nb";
	oVariant = (long)m_uiNb;
	pElement->setAttribute(strKey, oVariant);
	strKey = "Label";
	oVariant = m_strLabel;
	pElement->setAttribute(strKey, oVariant);
	strKey = "SensorType";
	oVariant = m_strSensorType;
	pElement->setAttribute(strKey, oVariant);
}