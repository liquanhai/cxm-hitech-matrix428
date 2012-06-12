#include "StdAfx.h"
#include "LineSetupData.h"

CLineSetupData::CLineSetupData(void)
{
}

CLineSetupData::~CLineSetupData(void)
{
}

/**
* ����XML
* @param void
* @return void
*/
void CLineSetupData::ParseXML(CXMLDOMElement* pElement)
{
	CString strKey;	// ����	
	// �õ����ߺ�
	strKey = "LineName";
	m_uiNbLine = CXMLDOMTool::GetElementAttributeInt(pElement, strKey);
	// �õ����ߵĲ�㶨��
	strKey = "ReceiverSection";
	m_strReceiverSection = CXMLDOMTool::GetElementAttributeString(pElement, strKey);
}

/**
* ����XML
* @param CXMLDOMElement* pElement XML�ĵ��ڵ�ָ��
* @return void
*/
void CLineSetupData::AddToXML(CXMLDOMElement* pElement)
{
	CString strKey;	// ����
	COleVariant oVariant;
	// �õ����ߺ�
	strKey = "LineName";
	oVariant = (long)m_uiNbLine;
	pElement->setAttribute(strKey, oVariant);
	// �õ����ߵĲ�㶨��
	strKey = "ReceiverSection";
	oVariant = m_strReceiverSection;
	pElement->setAttribute(strKey, oVariant);
}