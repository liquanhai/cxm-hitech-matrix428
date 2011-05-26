#include "StdAfx.h"
#include "SpreadAbsoluteList.h"

CSpreadAbsoluteList::CSpreadAbsoluteList(void)
{
}

CSpreadAbsoluteList::~CSpreadAbsoluteList(void)
{
}

/**
* ��ʼ��
* @param void
* @return void
*/
void CSpreadAbsoluteList::OnInit()
{
	m_uiCountAll = 0;	// ����	
	ParseXML();	// ���������ļ�
}

/**
* ���¼���
* @param void
* @return void
*/
void CSpreadAbsoluteList::OnReload(void)
{
	m_uiCountAll = 0;	// ����
	m_olsSpreadAbsolute.RemoveAll();	// �Ƴ�����
	ParseXML();	// ���������ļ�
}

/**
* �ر�
* @param void
* @return void
*/
void CSpreadAbsoluteList::OnClose()
{
	m_uiCountAll = 0;	// ����
	m_olsSpreadAbsolute.RemoveAll();	// �Ƴ�����
}

/**
* ���������ļ�
* @param void
* @return void
*/
void CSpreadAbsoluteList::ParseXML()
{
	CString strKey;
	CXMLDOMNodeList oNodeList;
	CXMLDOMElement oElement;
	LPDISPATCH lpDispatch;
	unsigned int i;

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

	CSpreadAbsoluteData oSpread;
	for(i = 0; i < m_uiCountAll; i++)
	{
		lpDispatch = oNodeList.get_item(i);
		oElement.AttachDispatch(lpDispatch);
		oSpread.ParseXML(&oElement);
		// ����
		m_olsSpreadAbsolute.AddTail(oSpread);
	}
}

/**
* ���������ļ�
* @param void
* @return void
*/
void CSpreadAbsoluteList::OnSave()
{
	CString strKey;
	COleVariant oVariant;
	CXMLDOMNodeList oNodeList;
	CXMLDOMElement oElementParent, oElementChild;
	LPDISPATCH lpDispatch;

	// �ҵ�������
	strKey = "AbsoluteSetup";
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
	CSpreadAbsoluteData oSpread;
	for(unsigned int i = 0; i < m_uiCountAll; i++)
	{
		oSpread = m_olsSpreadAbsolute.RemoveHead();

		lpDispatch = m_pXMLDOMDocument->createTextNode(m_strTabChild);
		oElementParent.appendChild(lpDispatch);

		lpDispatch = m_pXMLDOMDocument->createElement("Record");
		oElementChild.AttachDispatch(lpDispatch);
		oSpread.AddToXML(&oElementChild);
		oElementParent.appendChild(lpDispatch);

		if(i == (m_uiCountAll - 1))
		{
			lpDispatch = m_pXMLDOMDocument->createTextNode(m_strTabParent);
			oElementParent.appendChild(lpDispatch);
		}		
	}
}
