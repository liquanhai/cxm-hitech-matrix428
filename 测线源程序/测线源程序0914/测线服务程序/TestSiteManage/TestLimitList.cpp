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
	// ���������
	m_oTestLimitMap.RemoveAll();
	// ��������0
	if(m_uiCountAll > 0)
	{
		// ָ��
		CTestLimitData* pTestLimitData;
		while(FALSE == m_olsTestLimit.IsEmpty())
		{
			// �Ƴ�����
			pTestLimitData = m_olsTestLimit.RemoveHead();
			// ɾ��
			delete pTestLimitData;
		}
	}
	m_uiCountAll = 0;	// ����
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

	CTestLimitData* pTestLimitData = NULL;
	for(unsigned int i = 0; i < m_uiCountAll; i++)
	{
		lpDispatch = oNodeList.get_item(i);
		oElement.AttachDispatch(lpDispatch);
		pTestLimitData = new CTestLimitData;
		pTestLimitData->ParseXML(&oElement);
		// ���ӵ�����
		m_olsTestLimit.AddTail(pTestLimitData);
		// ���ӵ�������
		m_oTestLimitMap.SetAt(pTestLimitData->m_uiNb, pTestLimitData);
	}
}

/**
* ���������ţ��õ������о�����
* @param unsigned int uiIndex ������
* @return CTestLimitData* �����о�����ָ�� NULL����
*/
CTestLimitData* CTestLimitList::GetTestLimitDataByIndex(unsigned int uiIndex)
{
	CTestLimitData* pTestLimitData = NULL;
	POSITION pos = NULL;
	pos = m_olsTestLimit.FindIndex(uiIndex);
	if(NULL != pos)
	{
		pTestLimitData = m_olsTestLimit.GetAt(pos);
	}
	return pTestLimitData;
}

/**
* ���������ţ��õ������о�
* @param unsigned int uiIndex ������
* @return float �����о�
*/
float CTestLimitList::GetTestLimitValueByIndex(unsigned int uiIndex)
{
	CTestLimitData* pTestLimitData = NULL;
	if(TRUE == m_oTestLimitMap.Lookup(uiIndex, pTestLimitData))
	{
		return pTestLimitData->m_fLimit;
	}
	return 0.0;	
}

/**
* ���¼��ز��������ļ�
* @param void
* @return void
*/
void CTestLimitList::OnReloadTestSetupDataForApplyTestLimit()
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

	CTestLimitData oTestLimitData;
	CTestLimitData* pTestLimitData = NULL;
	for(unsigned int i = 0; i < m_uiCountAll; i++)
	{
		lpDispatch = oNodeList.get_item(i);
		oElement.AttachDispatch(lpDispatch);
		oTestLimitData.ParseXML(&oElement);
		pTestLimitData = GetTestLimitDataByIndex(i);
		*pTestLimitData = oTestLimitData;
	}
}