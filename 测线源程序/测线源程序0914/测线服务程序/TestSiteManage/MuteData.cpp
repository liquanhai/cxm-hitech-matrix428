#include "StdAfx.h"
#include "MuteData.h"

CMuteData::CMuteData()
{
}

CMuteData::~CMuteData()
{
}

/**
* ����XML
* @param CXMLDOMElement* pElement XML�ĵ��ڵ�ָ��
* @return void
*/
void CMuteData::ParseXML(CXMLDOMElement* pElement)
{
	CString strKey;
	strKey = "LineName";
	m_uiLineName = CXMLDOMTool::GetElementAttributeInt(pElement, strKey);
	strKey = "PointNb";
	m_uiPointNb = CXMLDOMTool::GetElementAttributeInt(pElement, strKey);
}