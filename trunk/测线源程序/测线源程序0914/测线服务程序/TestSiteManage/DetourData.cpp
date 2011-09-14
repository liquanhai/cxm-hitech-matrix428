#include "StdAfx.h"
#include "DetourData.h"

CDetourData::CDetourData()
{
}

CDetourData::~CDetourData()
{
}

/**
* ����XML
* @param CXMLDOMElement* pElement XML�ĵ��ڵ�ָ��
* @return void
*/
void CDetourData::ParseXML(CXMLDOMElement* pElement)
{
	CString strKey;
	strKey = "BoxTypeLow";
	m_uiBoxTypeLow = CXMLDOMTool::GetElementAttributeInt(pElement, strKey);
	strKey = "SNLow";
	m_uiSNLow = CXMLDOMTool::GetElementAttributeUnsignedInt(pElement, strKey);
	strKey = "ChannelNbLow";
	m_uiChannelNbLow = CXMLDOMTool::GetElementAttributeInt(pElement, strKey);
	strKey = "BoxTypeHigh";
	m_uiBoxTypeHigh = CXMLDOMTool::GetElementAttributeInt(pElement, strKey);
	strKey = "SNHigh";
	m_uiSNHigh = CXMLDOMTool::GetElementAttributeUnsignedInt(pElement, strKey);
	strKey = "ChannelNbHigh";
	m_uiChannelNbHigh = CXMLDOMTool::GetElementAttributeInt(pElement, strKey);
	strKey = "StopMarking";
	m_uiStopMarking = CXMLDOMTool::GetElementAttributeInt(pElement, strKey);

	// ��ǵ�Ͷ�
	m_oMarkerLow.m_uiBoxType = m_uiBoxTypeLow;
	m_oMarkerLow.m_uiSN = m_uiSNLow;
	m_oMarkerLow.m_uiChannelNb = m_uiChannelNbLow;

	// ��ǵ�߶�
	m_oMarkerHigh.m_uiBoxType = m_uiBoxTypeHigh;
	m_oMarkerHigh.m_uiSN = m_uiSNHigh;
	m_oMarkerHigh.m_uiChannelNb = m_uiChannelNbHigh;
}