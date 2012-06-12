#include "StdAfx.h"
#include "TestLimitList.h"

CTestLimitList::CTestLimitList()
{
}

CTestLimitList::~CTestLimitList()
{
}

/**
* ��ʼ��
* @param void
* @return void
*/
void CTestLimitList::OnInit()
{
	// ���������ļ�
	ParseXML();
}

/**
* ���¼���
* @param void
* @return void
*/
void CTestLimitList::OnReload()
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
void CTestLimitList::OnClose()
{
	m_oTestLimitDataMap.RemoveAll();
	m_olsTestLimit.RemoveAll();
	m_uiCountAll = 0;
}

/**
* ���������ļ�
* @param void
* @return void
*/
void CTestLimitList::ParseXML()
{
	CString strKey;
	CXMLDOMNodeList oNodeList;
	CXMLDOMElement oElement;
	LPDISPATCH lpDispatch;

	// �ҵ�������
	if(1 == m_uiAim)	// ���Զ���	1-������2-�첨��
	{
		strKey = "InstrumentTestLimit";
	}
	else if(2 == m_uiAim)	// ���Զ���	1-������2-�첨��
	{
		strKey = "SensorTestLimit";
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

	CTestLimitData oTestLimitData;
	for(unsigned int i = 0; i < m_uiCountAll; i++)
	{
		lpDispatch = oNodeList.get_item(i);
		oElement.AttachDispatch(lpDispatch);
		oTestLimitData.ParseXML(&oElement);
		// ���ӵ�����
		m_olsTestLimit.AddTail(oTestLimitData);
		// ���ӵ���������������
		m_oTestLimitDataMap.SetAt(oTestLimitData.m_uiNb, oTestLimitData);
	}
}

/**
* ���������ļ�
* @param void
* @return void
*/
void CTestLimitList::OnSave()
{
	CString strKey;
	COleVariant oVariant;
	CXMLDOMNodeList oNodeList;
	CXMLDOMElement oElementParent, oElementChild;
	LPDISPATCH lpDispatch;

	// �ҵ�������
	if(1 == m_uiAim)	// ���Զ���	1-������2-�첨��
	{
		strKey = "InstrumentTestLimit";
	}
	else if(2 == m_uiAim)	// ���Զ���	1-������2-�첨��
	{
		strKey = "SensorTestLimit";
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

		pos = m_olsTestLimit.FindIndex(i);
		CTestLimitData& oTestLimitData = m_olsTestLimit.GetAt(pos);

		oTestLimitData.AddToXML(&oElementChild);
	}
}