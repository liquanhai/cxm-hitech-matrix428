#include "StdAfx.h"
#include "OperationParseXML.h"

COperationParseXML::COperationParseXML(void)
{
}

COperationParseXML::~COperationParseXML(void)
{
}

int COperationParseXML::ParseOperationTable(LPCTSTR pstrXMLFilePath)
{
	/*
	CString strOLEObject;
	COleException oError;
	COleVariant oVariant;

	CXMLDOMDocument oXMLDOMDocument;
	CString strKey;
	CXMLDOMNodeList oNodeList;
	CXMLDOMElement oElement;
	LPDISPATCH lpDispatch;
	ULONG		m_dwCount;
try
{

	CoInitialize(NULL);
	// ����XML����
	strOLEObject ="msxml2.domdocument";
	BOOL bData = oXMLDOMDocument.CreateDispatch(strOLEObject, &oError);

	oVariant = "Matrix.xml";
	bData = oXMLDOMDocument.load(oVariant);

	// �ҵ����ڱ�����
	strKey =_T("SurverySetup");
	lpDispatch = oXMLDOMDocument.getElementsByTagName(strKey);
	oNodeList.AttachDispatch(lpDispatch);
	// �ҵ����
	lpDispatch = oNodeList.get_item(0);
	oElement.AttachDispatch(lpDispatch);
	// �õ�����
	strKey =_T("Count");
	m_dwCount = CXMLDOMTool::GetElementAttributeInt(&oElement, strKey);
	// �õ�����
	lpDispatch = oElement.get_childNodes();
	oNodeList.AttachDispatch(lpDispatch);


	// �ͷŶ���
	oXMLDOMDocument.DetachDispatch();
*/
	return 0;
}
catch (COleException* pe)
{
	TRACE (_T("COleException caught. SCODE = %x\n"), pe->m_sc);
	pe->Delete();

	return 0;
	
}
catch (CException* e)
{	
	return 0;
}
}

int COperationParseXML::ParseRecord(CXMLDOMElement* pElement)
{
// 	CString strKey;	// ����	
// 	// �õ����ߺ�
// 	strKey = "LineName";
// 	m_uiNbLine = CXMLDOMTool::GetElementAttributeInt(pElement, strKey);
// 	// �õ����ߵĲ�㶨��
// 	strKey = "ReceiverSection";
// 	m_strReceiverSection = CXMLDOMTool::GetElementAttributeString(pElement, strKey);
	return 0;
}
