#include "StdAfx.h"
#include "TestProjectList.h"

CTestProjectList::CTestProjectList()
{

}

CTestProjectList::~CTestProjectList()
{
}

/**
* ��ʼ��
* @param void
* @return void
*/
void CTestProjectList::OnInit()
{
	// ���������ļ�
	ParseXML();
}

/**
* ���¼���
* @param void
* @return void
*/
void CTestProjectList::OnReload()
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
void CTestProjectList::OnClose()
{
	// ��������0
	if(m_uiCountAll > 0)
	{
		// ָ��
		CTestProject* pTestProject;
		while(FALSE == m_olsTestProject.IsEmpty())
		{
			// �Ƴ�����
			pTestProject = m_olsTestProject.RemoveHead();
			pTestProject->OnClose();
			// ɾ��
			delete pTestProject;
		}
	}
	m_uiCountAll = 0;	// ����
}

// ���������ļ�
void CTestProjectList::OnSave()
{
	// ������Ŀ���� 1-�������ԣ�2-�첨�����ԣ�3-���ϲ��ԣ�4-�������
	switch(m_uiProjectType)
	{
	case 1:
		// ����XML����������
		AddToXMLForInstrument();
		break;
	case 2:
		// ����XML���첨������
		AddToXMLForSensor();
		break;
	case 3:
		// ����XML�����ϲ���
		AddToXMLForMultiple();
		break;
	case 4:
		// ����XML���������
		AddToXMLForSeisMonitor();
		break;
	}
}

/**
* ���������ļ�
* @param void
* @return void
*/
void CTestProjectList::ParseXML()
{
	// ������Ŀ���� 1-�������ԣ�2-�첨�����ԣ�3-���ϲ��ԣ�4-�������
	switch(m_uiProjectType)
	{
	case 1:
		// ����XML����������
		ParseXMLForInstrument();
		break;
	case 2:
		// ����XML���첨������
		ParseXMLForSensor();
		break;
	case 3:
		// ����XML�����ϲ���
		ParseXMLForMultiple();
		break;
	case 4:
		// ����XML���������
		ParseXMLForSeisMonitor();
		break;
	}
}

/**
* ���������ļ�����������
* @param void
* @return void
*/
void CTestProjectList::ParseXMLForInstrument()
{
	CString strKey;
	CXMLDOMNodeList oNodeList;
	CXMLDOMElement oElement;
	LPDISPATCH lpDispatch;
	unsigned int i;

	// �ҵ�������
	strKey = "InstrumentTest";
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

	CTestProject* pTestProject = NULL;
	for(unsigned int i = 0; i < m_uiCountAll; i++)
	{
		lpDispatch = oNodeList.get_item(i);
		oElement.AttachDispatch(lpDispatch);
		pTestProject = new CTestProject;
		pTestProject->OnInit();
		pTestProject->m_uiProjectType = 1;	// ������Ŀ���� 1-�������ԣ�2-�첨�����ԣ�3-���ϲ��ԣ�4-�������
		pTestProject->ParseXML(&oElement);
		// ���ӵ�����
		m_olsTestProject.AddTail(pTestProject);
	}
}

/**
* ���������ļ����첨������
* @param void
* @return void
*/
void CTestProjectList::ParseXMLForSensor()
{
	CString strKey;
	CXMLDOMNodeList oNodeList;
	CXMLDOMElement oElement;
	LPDISPATCH lpDispatch;
	unsigned int i;

	// �ҵ�������
	strKey = "SensorTest";
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

	CTestProject* pTestProject = NULL;
	for(unsigned int i = 0; i < m_uiCountAll; i++)
	{
		lpDispatch = oNodeList.get_item(i);
		oElement.AttachDispatch(lpDispatch);
		pTestProject = new CTestProject;
		pTestProject->OnInit();
		pTestProject->m_uiProjectType = 2;	// ������Ŀ���� 1-�������ԣ�2-�첨�����ԣ�3-���ϲ��ԣ�4-�������
		pTestProject->ParseXML(&oElement);
		// ���ӵ�����
		m_olsTestProject.AddTail(pTestProject);
	}
}

/**
* ���������ļ������ϲ���
* @param void
* @return void
*/
void CTestProjectList::ParseXMLForMultiple()
{
	CString strKey;
	CXMLDOMNodeList oNodeList;
	CXMLDOMElement oElement;
	LPDISPATCH lpDispatch;
	unsigned int i;

	// �ҵ�������
	strKey = "MultipleTest";
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

	CTestProject* pTestProject = NULL;
	for(unsigned int i = 0; i < m_uiCountAll; i++)
	{
		lpDispatch = oNodeList.get_item(i);
		oElement.AttachDispatch(lpDispatch);
		pTestProject = new CTestProject;
		pTestProject->OnInit();
		pTestProject->m_uiProjectType = 3;	// ������Ŀ���� 1-�������ԣ�2-�첨�����ԣ�3-���ϲ��ԣ�4-�������
		pTestProject->ParseXML(&oElement);
		// ���ӵ�����
		m_olsTestProject.AddTail(pTestProject);
	}
}

/**
* ���������ļ����������
* @param void
* @return void
*/
void CTestProjectList::ParseXMLForSeisMonitor()
{
	CString strKey;
	CXMLDOMNodeList oNodeList;
	CXMLDOMElement oElement;
	LPDISPATCH lpDispatch;

	// �ҵ�������
	strKey = "SeisMonitorTest";
	lpDispatch = m_pXMLDOMDocument->getElementsByTagName(strKey);
	oNodeList.AttachDispatch(lpDispatch);
	// �ҵ����
	lpDispatch = oNodeList.get_item(0);
	oElement.AttachDispatch(lpDispatch);
	m_uiCountAll = 1;	// ����

	CTestProject* pTestProject = NULL;
	pTestProject = new CTestProject;
	pTestProject->OnInit();
	pTestProject->m_uiProjectType = 4;	// ������Ŀ���� 1-�������ԣ�2-�첨�����ԣ�3-���ϲ��ԣ�4-�������
	pTestProject->ParseXML(&oElement);
	// ���ӵ�����
	m_olsTestProject.AddTail(pTestProject);
}

/**
* ���������ļ�����������
* @param void
* @return void
*/
void CTestProjectList::AddToXMLForInstrument()
{
	CString strKey;
	COleVariant oVariant;
	CXMLDOMNodeList oNodeList;
	CXMLDOMElement oElementParent, oElementChild;
	LPDISPATCH lpDispatch;

	// �ҵ�������
	strKey = "InstrumentTest";
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
	CTestProject* pTestProject = NULL;
	for(unsigned int i = 0; i < m_uiCountAll; i++)
	{
		pTestProject = m_olsTestProject.RemoveHead();

		lpDispatch = m_pXMLDOMDocument->createTextNode(m_strTabChild);
		oElementParent.appendChild(lpDispatch);

		lpDispatch = m_pXMLDOMDocument->createElement("Record");
		oElementChild.AttachDispatch(lpDispatch);
		pTestProject->AddToXML(&oElementChild, m_pXMLDOMDocument);
		delete pTestProject;
		oElementParent.appendChild(lpDispatch);

		if(i == (m_uiCountAll - 1))
		{
			lpDispatch = m_pXMLDOMDocument->createTextNode(m_strTabParent);
			oElementParent.appendChild(lpDispatch);
		}		
	}
}

/**
* ���������ļ����첨������
* @param void
* @return void
*/
void CTestProjectList::AddToXMLForSensor()
{
	CString strKey;
	COleVariant oVariant;
	CXMLDOMNodeList oNodeList;
	CXMLDOMElement oElementParent, oElementChild;
	LPDISPATCH lpDispatch;

	// �ҵ�������
	strKey = "SensorTest";
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
	CTestProject* pTestProject = NULL;
	for(unsigned int i = 0; i < m_uiCountAll; i++)
	{
		pTestProject = m_olsTestProject.RemoveHead();

		lpDispatch = m_pXMLDOMDocument->createTextNode(m_strTabChild);
		oElementParent.appendChild(lpDispatch);

		lpDispatch = m_pXMLDOMDocument->createElement("Record");
		oElementChild.AttachDispatch(lpDispatch);
		pTestProject->AddToXML(&oElementChild, m_pXMLDOMDocument);
		delete pTestProject;
		oElementParent.appendChild(lpDispatch);

		if(i == (m_uiCountAll - 1))
		{
			lpDispatch = m_pXMLDOMDocument->createTextNode(m_strTabParent);
			oElementParent.appendChild(lpDispatch);
		}		
	}
}

/**
* ���������ļ������ϲ��Բ���
* @param void
* @return void
*/
void CTestProjectList::AddToXMLForMultiple()
{
	CString strKey;
	COleVariant oVariant;
	CXMLDOMNodeList oNodeList;
	CXMLDOMElement oElementParent, oElementChild;
	LPDISPATCH lpDispatch;

	// �ҵ�������
	strKey = "MultipleTest";
	lpDispatch = m_pXMLDOMDocument->getElementsByTagName(strKey);
	oNodeList.AttachDispatch(lpDispatch);
	// �ҵ����
	lpDispatch = oNodeList.get_item(0);
	oElementParent.AttachDispatch(lpDispatch);
	// �õ�����
	lpDispatch = oElementParent.get_childNodes();
	oNodeList.AttachDispatch(lpDispatch);

	// ���ýڵ�����
	CTestProject* pTestProject = NULL;
	for(unsigned int i = 0; i < m_uiCountAll; i++)
	{
		lpDispatch = oNodeList.get_item(i);
		oElementChild.AttachDispatch(lpDispatch);
		POSITION pos = m_olsTestProject.FindIndex(i);
		pTestProject = m_olsTestProject.GetAt(pos);
		pTestProject->AddToXML(&oElementChild, m_pXMLDOMDocument);
	}
}

/**
* ���������ļ����������
* @param void
* @return void
*/
void CTestProjectList::AddToXMLForSeisMonitor()
{
	CString strKey;
	CXMLDOMNodeList oNodeList;
	CXMLDOMElement oElement;
	LPDISPATCH lpDispatch;

	// �ҵ�������
	strKey = "SeisMonitorTest";
	lpDispatch = m_pXMLDOMDocument->getElementsByTagName(strKey);
	oNodeList.AttachDispatch(lpDispatch);
	// �ҵ����
	lpDispatch = oNodeList.get_item(0);
	oElement.AttachDispatch(lpDispatch);

	CTestProject* pTestProject = m_olsTestProject.GetHead();
	pTestProject->AddToXML(&oElement, m_pXMLDOMDocument);
}