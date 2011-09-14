#include "StdAfx.h"
#include "TestBaseList.h"

CTestBaseList::CTestBaseList()
{
}

CTestBaseList::~CTestBaseList()
{
}

/**
* ��ʼ��
* @param void
* @return void
*/
void CTestBaseList::OnInit()
{
	// ���������ļ�
	ParseXML();
}

/**
* ���¼���
* @param void
* @return void
*/
void CTestBaseList::OnReload()
{
	// �ر�
	OnClose();
	// ��ʼ��
	OnInit();
}

/**
* �ر�
* @param void
* @return void
*/
void CTestBaseList::OnClose()
{
	m_oTestBaseDataMap.RemoveAll();
	m_olsTestBase.RemoveAll();
	m_uiCountAll = 0;
}

/**
* ���������ļ�
* @param void
* @return void
*/
void CTestBaseList::ParseXML()
{
	CString strKey;
	CXMLDOMNodeList oNodeList;
	CXMLDOMElement oElement;
	LPDISPATCH lpDispatch;

	// �ҵ�������
	if(1 == m_uiAim)	// ���Զ���	1-������2-�첨��
	{
		strKey = "InstrumentTestBase";
	}
	else if(2 == m_uiAim)	// ���Զ���	1-������2-�첨��
	{
		strKey = "SensorTestBase";
	}
	else
	{
		return;
	}
	lpDispatch = m_pXMLDOMDocument->getElementsByTagName(strKey);
	oNodeList.AttachDispatch(lpDispatch);
	lpDispatch = oNodeList.nextNode();
	// �ҵ����
	lpDispatch = oNodeList.get_item(0);
	oElement.AttachDispatch(lpDispatch);
	// �õ�����
	strKey = "Count";
	m_uiCountAll = CXMLDOMTool::GetElementAttributeInt(&oElement, strKey);
	// �õ�����
	lpDispatch = oElement.get_childNodes();
	oNodeList.AttachDispatch(lpDispatch);

	CTestBaseData oTestBaseData;
	for(unsigned int i = 0; i < m_uiCountAll; i++)
	{
		lpDispatch = oNodeList.get_item(i);
		oElement.AttachDispatch(lpDispatch);
		oTestBaseData.ParseXML(&oElement);
		// ���ӵ�����
		m_olsTestBase.AddTail(oTestBaseData);
		// ���ӵ���������������
		m_oTestBaseDataMap.SetAt(oTestBaseData.m_uiType, oTestBaseData);
	}
}

/**
* ���������ļ�
* @param void
* @return void
*/
void CTestBaseList::OnSave()
{
	CString strKey;
	COleVariant oVariant;
	CXMLDOMNodeList oNodeList;
	CXMLDOMElement oElementParent, oElementChild;
	LPDISPATCH lpDispatch;

	// �ҵ�������
	if(1 == m_uiAim)	// ���Զ���	1-������2-�첨��
	{
		strKey = "InstrumentTestBase";
	}
	else if(2 == m_uiAim)	// ���Զ���	1-������2-�첨��
	{
		strKey = "SensorTestBase";
	}
	else
	{
		return;
	}
	lpDispatch = m_pXMLDOMDocument->getElementsByTagName(strKey);
	oNodeList.AttachDispatch(lpDispatch);
	// �ҵ����
	lpDispatch = oNodeList.get_item(0);
	oElementParent.AttachDispatch(lpDispatch);
	// �õ�����
	lpDispatch = oElementParent.get_childNodes();
	oNodeList.AttachDispatch(lpDispatch);

	// ���ýڵ�
	POSITION pos = NULL;
	for(unsigned int i = 0; i < m_uiCountAll; i++)
	{
		lpDispatch = oNodeList.get_item(i);
		oElementChild.AttachDispatch(lpDispatch);

		pos = m_olsTestBase.FindIndex(i);
		CTestBaseData& oTestBaseData = m_olsTestBase.GetAt(pos);

		oTestBaseData.AddToXML(&oElementChild);
	}
}