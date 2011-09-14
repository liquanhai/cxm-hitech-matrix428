#include "StdAfx.h"
#include "BlastMachineData.h"
#include "IPList.h"

CBlastMachineData::CBlastMachineData()
{
}

CBlastMachineData::~CBlastMachineData()
{
}

/**
* ����XML
* @param CXMLDOMElement* pElement XML�ĵ��ڵ�ָ��
* @return void
*/
void CBlastMachineData::ParseXML(CXMLDOMElement* pElement)
{
	CString strKey;
	strKey = "Nb";
	m_uiNb = CXMLDOMTool::GetElementAttributeInt(pElement, strKey);
	strKey = "Label";
	m_strLabel = CXMLDOMTool::GetElementAttributeString(pElement, strKey);
	strKey = "BoxType";
	m_uiBoxType = CXMLDOMTool::GetElementAttributeInt(pElement, strKey);
	strKey = "SN";
	m_uiSN = CXMLDOMTool::GetElementAttributeUnsignedInt(pElement, strKey);
	strKey = "ChannelNb";
	m_uiChannelNb = CXMLDOMTool::GetElementAttributeInt(pElement, strKey);
	strKey = "Gain";
	m_uiGain = CXMLDOMTool::GetElementAttributeInt(pElement, strKey);
	strKey = "DPGNb";
	m_uiDPGNb = CXMLDOMTool::GetElementAttributeInt(pElement, strKey);
	strKey = "Comments";
	m_strComments = CXMLDOMTool::GetElementAttributeString(pElement, strKey);

	// IP��ַ
	m_uiIP = CIPList::GetBlastMachineIP(m_uiNb);
}