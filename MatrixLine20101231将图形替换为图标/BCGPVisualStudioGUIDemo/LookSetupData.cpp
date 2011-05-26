#include "StdAfx.h"
#include "LookSetupData.h"

CLookSetupData::CLookSetupData(void)
{
}

CLookSetupData::~CLookSetupData(void)
{
}

// ��ʼ��
void CLookSetupData::OnInit()
{
	// ���������ļ�
	ParseXML();
}

// ���¼���
void CLookSetupData::OnReload(void)
{
	// ���������ļ�
	ParseXML();
}

// �ر�
void CLookSetupData::OnClose()
{

}

// ���������ļ�
void CLookSetupData::ParseXML()
{
	CString strKey;
	CXMLDOMNodeList oNodeList;
	CXMLDOMElement oElement;
	LPDISPATCH lpDispatch;

	// �ҵ�Lookģʽ������
	strKey = "LookSetup";
	lpDispatch = m_pXMLDOMDocument->getElementsByTagName(strKey);
	oNodeList.AttachDispatch(lpDispatch);
	// �ҵ����
	lpDispatch = oNodeList.get_item(0);
	oElement.AttachDispatch(lpDispatch);

	strKey = "AutoLook";
	m_uiLookAuto = CXMLDOMTool::GetElementAttributeUnsignedInt(&oElement, strKey);
	strKey = "Resistance";
	m_uiTestResistance = CXMLDOMTool::GetElementAttributeUnsignedInt(&oElement, strKey);
	strKey = "Tilt";
	m_uiTestTilt = CXMLDOMTool::GetElementAttributeUnsignedInt(&oElement, strKey);
	strKey = "Leakage";
	m_uiTestLeakage = CXMLDOMTool::GetElementAttributeUnsignedInt(&oElement, strKey);
}

// ���������ļ�
void CLookSetupData::OnSave()
{
	CString strKey;
	CXMLDOMNodeList oNodeList;
	CXMLDOMElement oElement;
	LPDISPATCH lpDispatch;

	// �ҵ�Lookģʽ������
	strKey = "LookSetup";
	lpDispatch = m_pXMLDOMDocument->getElementsByTagName(strKey);
	oNodeList.AttachDispatch(lpDispatch);
	// �ҵ����
	lpDispatch = oNodeList.get_item(0);
	oElement.AttachDispatch(lpDispatch);

	COleVariant oVariant;
	strKey = "AutoLook";
	oVariant = (long)m_uiLookAuto;
	oElement.setAttribute(strKey, oVariant);
	strKey = "Resistance";
	oVariant = (long)m_uiTestResistance;
	oElement.setAttribute(strKey, oVariant);
	strKey = "Tilt";
	oVariant = (long)m_uiTestTilt;
	oElement.setAttribute(strKey, oVariant);
	strKey = "Leakage";
	oVariant = (long)m_uiTestLeakage;
	oElement.setAttribute(strKey, oVariant);
}