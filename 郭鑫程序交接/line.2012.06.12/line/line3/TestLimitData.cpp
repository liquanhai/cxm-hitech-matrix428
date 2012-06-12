#include "StdAfx.h"
#include "TestLimitData.h"

CTestLimitData::CTestLimitData()
{
}

CTestLimitData::~CTestLimitData()
{
}

/**
* ����XML
* @param CXMLDOMElement* pElement XML�ĵ��ڵ�ָ��
* @return void
*/
void CTestLimitData::ParseXML(CXMLDOMElement* pElement)
{
	CString strKey;
	strKey = "TestAim";
	m_uiTestAim = CXMLDOMTool::GetElementAttributeUnsignedInt(pElement, strKey);	// ��������Ŀ�� 1��������2���첨��
	strKey = "Nb";
	m_uiNb = CXMLDOMTool::GetElementAttributeUnsignedInt(pElement, strKey);	// ������
	strKey = "Descr";
	m_strDesc = CXMLDOMTool::GetElementAttributeString(pElement, strKey);	// ����
	strKey = "Unit";
	m_strUnit = CXMLDOMTool::GetElementAttributeString(pElement, strKey);	// ��λ
	strKey = "TestType";
	m_uiType = CXMLDOMTool::GetElementAttributeUnsignedInt(pElement, strKey);	// ��������
	strKey = "Limit";
	m_fLimit = CXMLDOMTool::GetElementAttributeFloat(pElement, strKey);	// �о�
}

/**
* ����XML
* @param CXMLDOMElement* pElement XML�ĵ��ڵ�ָ��
* @return void
*/
void CTestLimitData::AddToXML(CXMLDOMElement* pElement)
{
	CString strKey;	// ����
	CString strData;
	COleVariant oVariant;

	strKey = "Limit";
	oVariant = m_fLimit;
	pElement->setAttribute(strKey, oVariant);
}