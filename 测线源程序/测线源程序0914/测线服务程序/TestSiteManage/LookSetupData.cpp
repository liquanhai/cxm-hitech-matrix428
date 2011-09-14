#include "StdAfx.h"
#include "LookSetupData.h"

CLookSetupData::CLookSetupData()
{
}

CLookSetupData::~CLookSetupData()
{
}

/**
* ��ʼ��
* @param void
* @return void
*/
void CLookSetupData::OnInit()
{
	// ���������ļ�
	ParseXML();
}

/**
* ���¼���
* @param void
* @return void
*/
void CLookSetupData::OnReload()
{
	// ���������ļ�
	ParseXML();
}

/**
* �ر�
* @param void
* @return void
*/
void CLookSetupData::OnClose()
{

}

/**
* ���������ļ�
* @param void
* @return void
*/
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