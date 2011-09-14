#include "StdAfx.h"
#include "TestBaseData.h"

CTestBaseData::CTestBaseData()
{
}

CTestBaseData::~CTestBaseData()
{
}

/**
* ����XML
* @param CXMLDOMElement* pElement XML�ĵ��ڵ�ָ��
* @return void
*/
void CTestBaseData::ParseXML(CXMLDOMElement* pElement)
{
	CString strKey;
	strKey = "TestAim";
	m_uiTestAim = CXMLDOMTool::GetElementAttributeUnsignedInt(pElement, strKey);	// ��������Ŀ�� 1��������2���첨��
	strKey = "Nb";
	m_uiNb = CXMLDOMTool::GetElementAttributeUnsignedInt(pElement, strKey);	// ������
	strKey = "Descr";
	m_strDesc = CXMLDOMTool::GetElementAttributeString(pElement, strKey);	// ����
	strKey = "TestType";
	m_uiType = CXMLDOMTool::GetElementAttributeUnsignedInt(pElement, strKey);	// ��������
	strKey = "ADC";
	m_uiADC = CXMLDOMTool::GetElementAttributeUnsignedInt(pElement, strKey);	// ADC���� 0-�رգ�1-���ӵ��ڲ��������磻2-���ӵ��첨���ĵ�·�����
	strKey = "Gain";
	m_uiGain = CXMLDOMTool::GetElementAttributeUnsignedInt(pElement, strKey);	// ����
	strKey = "DAC";
	m_uiDAC = CXMLDOMTool::GetElementAttributeUnsignedInt(pElement, strKey);	// DAC���� 0-�رգ�1-���ӵ��ڲ��������磻2-���ӵ��첨��
	strKey = "Filter";
	m_uiFilter = CXMLDOMTool::GetElementAttributeUnsignedInt(pElement, strKey);	// �˲������� 1-0.8 LIN �����ԣ���2-0.8 MIN ����С��
	strKey = "SamplingRate";
	m_uiSamplingRate = CXMLDOMTool::GetElementAttributeUnsignedInt(pElement, strKey);	// ������ ��λ΢��
	strKey = "SamplingLength";
	m_uiSamplingLength = CXMLDOMTool::GetElementAttributeUnsignedInt(pElement, strKey);	// ����ʱ�� ��λ����
}

/**
* ����XML
* @param CXMLDOMElement* pElement XML�ĵ��ڵ�ָ��
* @return void
*/
void CTestBaseData::AddToXML(CXMLDOMElement* pElement)
{
	CString strKey;	// ����
	CString strData;
	COleVariant oVariant;

	strKey = "ADC";
	oVariant = (long)m_uiADC;
	pElement->setAttribute(strKey, oVariant);

	strKey = "Gain";
	oVariant = (long)m_uiGain;
	pElement->setAttribute(strKey, oVariant);

	strKey = "DAC";
	oVariant = (long)m_uiDAC;
	pElement->setAttribute(strKey, oVariant);

	strKey = "Filter";
	oVariant = (long)m_uiFilter;
	pElement->setAttribute(strKey, oVariant);

	strKey = "SamplingRate";
	oVariant = (long)m_uiSamplingRate;
	pElement->setAttribute(strKey, oVariant);

	strKey = "SamplingLength";
	oVariant = (long)m_uiSamplingLength;
	pElement->setAttribute(strKey, oVariant);
}