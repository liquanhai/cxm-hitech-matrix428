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
	// ���������
	m_oTestBaseMap.RemoveAll();
	// ��������0
	if(m_uiCountAll > 0)
	{
		// ָ��
		CTestBaseData* pTestBaseData;
		while(FALSE == m_olsTestBase.IsEmpty())
		{
			// �Ƴ�����
			pTestBaseData = m_olsTestBase.RemoveHead();
			// ɾ��
			delete pTestBaseData;
		}
	}
	m_uiCountAll = 0;	// ����
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
	long lData = oNodeList.get_length();
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

	CTestBaseData* pTestBaseData = NULL;
	for(unsigned int i = 0; i < m_uiCountAll; i++)
	{
		lpDispatch = oNodeList.get_item(i);
		oElement.AttachDispatch(lpDispatch);
		pTestBaseData = new CTestBaseData;
		pTestBaseData->ParseXML(&oElement);
		// ���ӵ�����
		m_olsTestBase.AddTail(pTestBaseData);
		// ���ӵ�������
		m_oTestBaseMap.SetAt(pTestBaseData->m_uiType, pTestBaseData);
	}
}

/**
* ���������ţ��õ����Ի�������
* @param unsigned int uiIndex ������
* @return CTestBaseData* ���Ի�������ָ�� NULL����
*/
CTestBaseData* CTestBaseList::GetTestBaseDataByIndex(unsigned int uiIndex)
{
	CTestBaseData* pTestBaseData = NULL;
	POSITION pos = NULL;
	pos = m_olsTestBase.FindIndex(uiIndex);
	if(NULL != pos)
	{
		pTestBaseData = m_olsTestBase.GetAt(pos);
	}
	return pTestBaseData;
}

/**
* ���ݲ������ͣ��õ����Ի�������
* @param unsigned int uiTestType ��������
* @return CTestBaseData* ���Ի�������ָ�� NULL����
*/
CTestBaseData* CTestBaseList::GetTestBaseDataByTestType(unsigned int uiTestType)
{
	CTestBaseData* pTestBaseData = NULL;
	m_oTestBaseMap.Lookup(uiTestType, pTestBaseData);
	return pTestBaseData;
}

/**
* ���¼��ز��������ļ�
* @param void
* @return void
*/
void CTestBaseList::OnReloadTestSetupDataForApplyTestBase()
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
	long lData = oNodeList.get_length();
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
	CTestBaseData* pTestBaseData = NULL;
	for(unsigned int i = 0; i < m_uiCountAll; i++)
	{
		lpDispatch = oNodeList.get_item(i);
		oElement.AttachDispatch(lpDispatch);
		oTestBaseData.ParseXML(&oElement);
		pTestBaseData = GetTestBaseDataByIndex(i);
		*pTestBaseData = oTestBaseData;
	}
}