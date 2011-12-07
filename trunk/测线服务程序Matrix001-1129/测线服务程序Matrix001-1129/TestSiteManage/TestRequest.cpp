#include "StdAfx.h"
#include "TestRequest.h"

CTestRequest::CTestRequest()
{
	OnReset();
}

CTestRequest::~CTestRequest()
{
}

/**
* ����
* @param void
* @return void
*/
void CTestRequest::OnReset()
{
	m_uiIndex = 0;	// ������	
	m_uiAim = 0;	// ���Զ���	1-������2-�첨����3-ȫ��
	m_uiType = 0;	// ��������
	m_uiGain = 0;	// ����
	m_uiLoopNb = 0;	// ��ת����������
	m_uiLoopCount = 0;	// ѭ������
}

/**
* ����XML����������
* @param CXMLDOMElement* pElement XML�ĵ��ڵ�ָ��
* @return void
*/
void CTestRequest::ParseXMLForInstrument(CXMLDOMElement* pElement)
{
	m_uiIndex = 1;	// ������	
	m_uiAim = 1;	// ���Զ���	1-������2-�첨����3-ȫ��

	CString strKey;
	strKey = "TestType";
	m_uiType = CXMLDOMTool::GetElementAttributeUnsignedInt(pElement, strKey);
	strKey = "Gain";
	m_uiGain = CXMLDOMTool::GetElementAttributeUnsignedInt(pElement, strKey);
}

/**
* ����XML���첨������
* @param CXMLDOMElement* pElement XML�ĵ��ڵ�ָ��
* @return void
*/
void CTestRequest::ParseXMLForSensor(CXMLDOMElement* pElement)
{
	m_uiIndex = 1;	// ������	
	m_uiAim = 2;	// ���Զ���	1-������2-�첨����3-ȫ��
	m_uiGain = 1600;	// ����

	CString strKey;
	strKey = "TestType";
	m_uiType = CXMLDOMTool::GetElementAttributeUnsignedInt(pElement, strKey);
}

/**
* ����XML�����ϲ���
* @param CXMLDOMElement* pElement XML�ĵ��ڵ�ָ��
* @return void
*/
void CTestRequest::ParseXMLForMultiple(CXMLDOMElement* pElement)
{
	CString strKey;
	strKey = "LineNb";
	m_uiIndex = CXMLDOMTool::GetElementAttributeUnsignedInt(pElement, strKey);
	strKey = "TestType";
	m_uiType = CXMLDOMTool::GetElementAttributeUnsignedInt(pElement, strKey);
	strKey = "Gain";
	m_uiGain = CXMLDOMTool::GetElementAttributeUnsignedInt(pElement, strKey);
	strKey = "LoopLineNb";
	m_uiLoopNb = CXMLDOMTool::GetElementAttributeUnsignedInt(pElement, strKey);
	strKey = "NbLoops";
	m_uiLoopCount = CXMLDOMTool::GetElementAttributeUnsignedInt(pElement, strKey);

	m_uiAim = 3;	// ���Զ���	1-������2-�첨����3-ȫ��
}