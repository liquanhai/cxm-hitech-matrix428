#include "stdafx.h"
#include "ShotPointMap.h"
CShotPointMap::CShotPointMap(void)
{
	m_uiCountAll = 0;	// ����
	m_oShotPointMap.clear();
}

CShotPointMap::~CShotPointMap(void)
{
}
/**
* ���¼���
* @param void
* @return void
*/
void CShotPointMap::OnReload(void)
{
	m_uiCountAll = 0;	// ����
	m_oShotPointMap.clear();	// ���������
	ParseXML();	// ���������ļ�
}
/**
* ���������ļ�
* @param void
* @return void
*/
void CShotPointMap::ParseXML()
{
	CString strKey;
	CXMLDOMNodeList oNodeList;
	CXMLDOMElement oElement;
	LPDISPATCH lpDispatch;
	unsigned int i;
	unsigned int uiShotPoint = 0;
	typedef pair<unsigned int, unsigned int> value_type;

	// �ҵ�������
	strKey = "AbsoluteSetup";
	lpDispatch = m_pXMLDOMDocument->getElementsByTagName(strKey);
	oNodeList.AttachDispatch(lpDispatch);
	// �ҵ����
	lpDispatch = oNodeList.get_item(0);
	oElement.AttachDispatch(lpDispatch);
	// �õ�����
	strKey = "Count";
	m_uiCountAll = CXMLDOMTool::GetElementAttributeInt(&oElement, strKey);

	// �õ�����
	lpDispatch = oElement.get_childNodes();
	oNodeList.AttachDispatch(lpDispatch);

	for(i = 0; i < m_uiCountAll; i++)
	{
		lpDispatch = oNodeList.get_item(i);
		oElement.AttachDispatch(lpDispatch);
		strKey = "ShotPoint";
		uiShotPoint = CXMLDOMTool::GetElementAttributeInt(&oElement, strKey);
		value_type p(uiShotPoint, i);
		m_oShotPointMap.insert(p); 
	}
}