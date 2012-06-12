#include "StdAfx.h"
#include "SensorList.h"

CSensorList::CSensorList(void)
{
}

CSensorList::~CSensorList(void)
{
}

/**
* ��ʼ��
* @param void
* @return void
*/
void CSensorList::OnInit()
{
	m_uiCountAll = 0;	// �첨������	
	ParseXML();	// ���������ļ�
}

/**
* ���¼���
* @param void
* @return void
*/
void CSensorList::OnReload(void)
{
	m_uiCountAll = 0;	// �첨������
	m_olsSensor.RemoveAll();	// �Ƴ�����
	ParseXML();	// ���������ļ�
}

/**
* �ر�
* @param void
* @return void
*/
void CSensorList::OnClose()
{
	m_uiCountAll = 0;	// �첨������
	m_olsSensor.RemoveAll();	// �Ƴ�����
}

/**
* ���������ļ�
* @param void
* @return void
*/
void CSensorList::ParseXML()
{
	CString strKey;
	CXMLDOMNodeList oNodeList;
	CXMLDOMElement oElement;
	LPDISPATCH lpDispatch;
	unsigned int i;

	// �ҵ��첨��������
	strKey = "SensorSetup";
	lpDispatch = m_pXMLDOMDocument->getElementsByTagName(strKey);
	oNodeList.AttachDispatch(lpDispatch);
	// �ҵ����
	lpDispatch = oNodeList.get_item(0);
	oElement.AttachDispatch(lpDispatch);
	// �õ��첨������
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

	CSensorData oSensor;
	for(i = 0; i < m_uiCountAll; i++)
	{
		lpDispatch = oNodeList.get_item(i);
		oElement.AttachDispatch(lpDispatch);
		oSensor.ParseXML(&oElement);
		// ���Ӽ첨��
		m_olsSensor.AddTail(oSensor);
	}
}

/**
* ���������ļ�
* @param void
* @return void
*/
void CSensorList::OnSave()
{
	CString strKey;
	COleVariant oVariant;
	CXMLDOMNodeList oNodeList;
	CXMLDOMElement oElementParent, oElementChild;
	LPDISPATCH lpDispatch;

	// �ҵ��첨��������
	strKey = "SensorSetup";
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
	CSensorData oSensor;
	for(unsigned int i = 0; i < m_uiCountAll; i++)
	{
		oSensor = m_olsSensor.RemoveHead();

		lpDispatch = m_pXMLDOMDocument->createTextNode(m_strTabChild);
		oElementParent.appendChild(lpDispatch);

		lpDispatch = m_pXMLDOMDocument->createElement("Record");
		oElementChild.AttachDispatch(lpDispatch);
		oSensor.AddToXML(&oElementChild);
		oElementParent.appendChild(lpDispatch);

		if(i == (m_uiCountAll - 1))
		{
			lpDispatch = m_pXMLDOMDocument->createTextNode(m_strTabParent);
			oElementParent.appendChild(lpDispatch);
		}		
	}
}
