#include "StdAfx.h"
#include "LineList.h"

CLineList::CLineList(void)
{
}

CLineList::~CLineList(void)
{
}

/**
* ��ʼ��
* @param void
* @return void
*/
void CLineList::OnInit()
{	
	m_uiCountAll = 0;	// ʹ���в�������
	ParseXML();	// ���������ļ�
}

/**
* ���¼���
* @param void
* @return void
*/
void CLineList::OnReload()
{	
	m_uiCountAll = 0;	// ��������	
	m_olsLine.RemoveAll();	// ��ն���
	ParseXML();	// ���������ļ�
}

/**
* �ر�
* @param void
* @return void
*/
void CLineList::OnClose()
{
	m_uiCountAll = 0;	// ʹ���в�������	
	m_olsLine.RemoveAll();	// ��ն���
}

/**
* ���������ļ�
* @param void
* @return void
*/
void CLineList::ParseXML()
{
	CString strKey;
	CXMLDOMNodeList oNodeList;
	CXMLDOMElement oElement;
	LPDISPATCH lpDispatch;
	unsigned int i;

	// �ҵ�����������
	strKey = "SurverySetup";
	lpDispatch = m_pXMLDOMDocument->getElementsByTagName(strKey);
	oNodeList.AttachDispatch(lpDispatch);
	// �ҵ����
	lpDispatch = oNodeList.get_item(0);
	oElement.AttachDispatch(lpDispatch);
	// �õ���������
	strKey = "Count";
	m_uiCountAll = CXMLDOMTool::GetElementAttributeInt(&oElement, strKey);
	// �õ�Tab������
	strKey = "TabCount";
	m_uiTabCount = CXMLDOMTool::GetElementAttributeInt(&oElement, strKey);

	m_strTabChild = "\r\n";
	m_strTabParent = "\r\n";
	for(i = 0; i < m_uiTabCount; i++)
	{
		m_strTabChild = m_strTabChild + "\t";
	}
	for(i = 0; i < m_uiTabCount - 1; i++)
	{
		m_strTabParent = m_strTabParent + "\t";
	}

	// �õ�����
	lpDispatch = oElement.get_childNodes();
	oNodeList.AttachDispatch(lpDispatch);

	CLineSetupData oLineSetupData;
	for(unsigned int i = 0; i < m_uiCountAll; i++)
	{
		// �õ�XMLԪ��
		lpDispatch = oNodeList.get_item(i);
		oElement.AttachDispatch(lpDispatch);

		oLineSetupData.ParseXML(&oElement);
		// ������߶���
		m_olsLine.AddTail(oLineSetupData);
	}
}

/**
* ���������ļ�
* @param void
* @return void
*/
void CLineList::OnSave()
{
	CString strKey;
	COleVariant oVariant;
	CXMLDOMNodeList oNodeList;
	CXMLDOMElement oElementParent, oElementChild;
	LPDISPATCH lpDispatch;

	// �ҵ�����������
	strKey = "SurverySetup";
	lpDispatch = m_pXMLDOMDocument->getElementsByTagName(strKey);
	oNodeList.AttachDispatch(lpDispatch);
	// �ҵ����
	lpDispatch = oNodeList.get_item(0);
	oElementParent.AttachDispatch(lpDispatch);
	// ��������
	strKey = "Count";
	oVariant = (long)m_uiCountAll;
	oElementParent.setAttribute(strKey, oVariant);

	// ɾ�������ӽڵ�
	while(TRUE == oElementParent.hasChildNodes())
	{
		lpDispatch = oElementParent.get_firstChild();
		oElementParent.removeChild(lpDispatch);
	}
	// �����½ڵ�
	CLineSetupData oLineSetupData;
	for(unsigned int i = 0; i < m_uiCountAll; i++)
	{
		oLineSetupData = m_olsLine.RemoveHead();

		lpDispatch = m_pXMLDOMDocument->createTextNode(m_strTabChild);
		oElementParent.appendChild(lpDispatch);

		lpDispatch = m_pXMLDOMDocument->createElement("Record");
		oElementChild.AttachDispatch(lpDispatch);
		oLineSetupData.AddToXML(&oElementChild);
		oElementParent.appendChild(lpDispatch);
		
		if(i == (m_uiCountAll - 1))
		{
			lpDispatch = m_pXMLDOMDocument->createTextNode(m_strTabParent);
			oElementParent.appendChild(lpDispatch);
		}		
	}
}

