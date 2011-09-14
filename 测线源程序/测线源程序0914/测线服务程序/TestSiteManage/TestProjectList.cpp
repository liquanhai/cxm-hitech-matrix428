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
* ���¼����������������ļ�
* @param void
* @return void
*/
void CTestProjectList::OnReloadTestSetupDataForApplyInstrument()
{
	// ɾ��������Ŀ�����ݲ�������
	DeleteTestProjectByProjectType(1);
	// ����XML����������
	ParseXMLForInstrument();
}

/**
* ���¼��ؼ첨�����������ļ�
* @param void
* @return void
*/
void CTestProjectList::OnReloadTestSetupDataForApplySensor()
{
	// ɾ��������Ŀ�����ݲ�������
	DeleteTestProjectByProjectType(2);
	// ����XML���첨������
	ParseXMLForSensor();
}

/**
* ���¼��ظ��ϲ��Բ��������ļ�
* @param void
* @return void
*/
void CTestProjectList::OnReloadTestSetupDataForApplyMultiple()
{
	// ɾ��������Ŀ�����ݲ�������
	DeleteTestProjectByProjectType(3);
	// ����XML�����ϲ���
	ParseXMLForMultiple();
}

/**
* ���¼���������������ļ�
* @param void
* @return void
*/
void CTestProjectList::OnReloadTestSetupDataForApplySeisMonitor()
{
	// ɾ��������Ŀ�����ݲ�������
	DeleteTestProjectByProjectType(4);
	// ����XML���������
	ParseXMLForSeisMonitor();
}

/**
* ���ݲ�����Ŀ���ͣ�ɾ��������Ŀ
* @param unsigned int uiProjectType ������Ŀ���� 1-�������ԣ�2-�첨�����ԣ�3-���ϲ��ԣ�4-�������
* @return void
*/
void CTestProjectList::DeleteTestProjectByProjectType(unsigned int uiProjectType)
{
	if(0 == m_uiCountAll)
	{
		return;
	}
	
	CTestProject* pTestProject = NULL;
	POSITION pos = NULL;
	for(int i = (int)(m_uiCountAll - 1); i >= 0; i--)
	{
		pos = m_olsTestProject.FindIndex(i);
		pTestProject = m_olsTestProject.GetAt(pos);
		if(uiProjectType == 1)
		{
			if((pTestProject->m_uiTestNb > 1000) && (pTestProject->m_uiTestNb < 2000))
			{
				m_olsTestProject.RemoveAt(pos);
				m_oTestProjectMap.RemoveKey(pTestProject->m_uiTestNb);
				pTestProject->OnClose();
				delete pTestProject;
			}
		}
		else if(uiProjectType == 2)
		{
			if((pTestProject->m_uiTestNb > 2000) && (pTestProject->m_uiTestNb < 3000))
			{
				m_olsTestProject.RemoveAt(pos);
				m_oTestProjectMap.RemoveKey(pTestProject->m_uiTestNb);
				pTestProject->OnClose();
				delete pTestProject;
			}
		}
		else if(uiProjectType == 3)
		{
			if((pTestProject->m_uiTestNb > 3000) && (pTestProject->m_uiTestNb < 4000))
			{
				m_olsTestProject.RemoveAt(pos);
				m_oTestProjectMap.RemoveKey(pTestProject->m_uiTestNb);
				pTestProject->OnClose();
				delete pTestProject;
			}
		}
		else if(uiProjectType == 4)
		{
			if(pTestProject->m_uiTestNb == 4000)
			{
				m_olsTestProject.RemoveAt(pos);
				m_oTestProjectMap.RemoveKey(pTestProject->m_uiTestNb);
				pTestProject->OnClose();
				delete pTestProject;
			}
		}
	}
	m_uiCountAll = m_olsTestProject.GetCount();	// ����
}

/**
* �ر�
* @param void
* @return void
*/
void CTestProjectList::OnClose()
{
	// ���������
	m_oTestProjectMap.RemoveAll();
	// ��������0
	if(m_uiCountAll > 0)
	{
		// ָ��
		CTestProject* pTestProject;
		while(FALSE == m_olsTestProject.IsEmpty())
		{
			// �Ƴ�����
			pTestProject = m_olsTestProject.RemoveHead();
			pTestProject->OnReset();
			// ɾ��
			delete pTestProject;
		}
	}
	m_uiCountAll = 0;	// ����
}

/**
* ���������ļ�
* @param void
* @return void
*/
void CTestProjectList::ParseXML()
{
	m_uiCountAll = 0;	// ������������
	// ����XML����������
	ParseXMLForInstrument();
	// ����XML���첨������
	ParseXMLForSensor();
	// ����XML�����ϲ���
	ParseXMLForMultiple();
	// ����XML���������
	ParseXMLForSeisMonitor();
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

	// �ҵ�������
	strKey = "InstrumentTest";
	lpDispatch = m_pXMLDOMDocument->getElementsByTagName(strKey);
	oNodeList.AttachDispatch(lpDispatch);
	// �ҵ����
	lpDispatch = oNodeList.get_item(0);
	oElement.AttachDispatch(lpDispatch);
	// �õ�����
	strKey = "Count";
	unsigned int uiCountAll = CXMLDOMTool::GetElementAttributeInt(&oElement, strKey);
	m_uiCountAll = m_uiCountAll + uiCountAll;	// ����
	// �õ�����
	lpDispatch = oElement.get_childNodes();
	oNodeList.AttachDispatch(lpDispatch);

	CTestProject* pTestProject = NULL;
	for(unsigned int i = 0; i < uiCountAll; i++)
	{
		lpDispatch = oNodeList.get_item(i);
		oElement.AttachDispatch(lpDispatch);
		pTestProject = new CTestProject;
		pTestProject->m_pTestBaseListInstrument = m_pTestBaseListInstrument;	// �������Ի�����������ָ��
		pTestProject->m_pTestBaseListSensor = m_pTestBaseListSensor;	// �첨�����Ի�����������ָ��
		pTestProject->OnInit();
		pTestProject->ParseXMLForInstrument(&oElement);
		// ���ӵ�����
		m_olsTestProject.AddTail(pTestProject);
		// ���ӵ�������
		m_oTestProjectMap.SetAt(pTestProject->m_uiTestNb, pTestProject);
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

	// �ҵ�������
	strKey = "SensorTest";
	lpDispatch = m_pXMLDOMDocument->getElementsByTagName(strKey);
	oNodeList.AttachDispatch(lpDispatch);
	// �ҵ����
	lpDispatch = oNodeList.get_item(0);
	oElement.AttachDispatch(lpDispatch);
	// �õ�����
	strKey = "Count";
	unsigned int uiCountAll = CXMLDOMTool::GetElementAttributeInt(&oElement, strKey);
	m_uiCountAll = m_uiCountAll + uiCountAll;	// ����
	// �õ�����
	lpDispatch = oElement.get_childNodes();
	oNodeList.AttachDispatch(lpDispatch);

	CTestProject* pTestProject = NULL;
	for(unsigned int i = 0; i < uiCountAll; i++)
	{
		lpDispatch = oNodeList.get_item(i);
		oElement.AttachDispatch(lpDispatch);
		pTestProject = new CTestProject;
		pTestProject->m_pTestBaseListInstrument = m_pTestBaseListInstrument;	// �������Ի�����������ָ��
		pTestProject->m_pTestBaseListSensor = m_pTestBaseListSensor;	// �첨�����Ի�����������ָ��
		pTestProject->OnInit();
		pTestProject->ParseXMLForSensor(&oElement);
		// ���ӵ�����
		m_olsTestProject.AddTail(pTestProject);
		// ���ӵ�������
		m_oTestProjectMap.SetAt(pTestProject->m_uiTestNb, pTestProject);
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
	unsigned int uiCountProject = 0;	// ��Ч���ϲ�������

	// �ҵ�������
	strKey = "MultipleTest";
	lpDispatch = m_pXMLDOMDocument->getElementsByTagName(strKey);
	oNodeList.AttachDispatch(lpDispatch);
	// �ҵ����
	lpDispatch = oNodeList.get_item(0);
	oElement.AttachDispatch(lpDispatch);
	// �õ�����
	strKey = "Count";
	unsigned int uiCountAll = CXMLDOMTool::GetElementAttributeInt(&oElement, strKey);
	
	// �õ�����
	lpDispatch = oElement.get_childNodes();
	oNodeList.AttachDispatch(lpDispatch);

	CTestProject* pTestProject = NULL;
	for(unsigned int i = 0; i < uiCountAll; i++)
	{
		lpDispatch = oNodeList.get_item(i);
		oElement.AttachDispatch(lpDispatch);
		// �õ�������������
		strKey = "Count";
		unsigned int uiRequestCount = CXMLDOMTool::GetElementAttributeInt(&oElement, strKey);	// ������������
		if(0 < uiRequestCount)
		{
			pTestProject = new CTestProject;
			pTestProject->m_pTestBaseListInstrument = m_pTestBaseListInstrument;	// �������Ի�����������ָ��
			pTestProject->m_pTestBaseListSensor = m_pTestBaseListSensor;	// �첨�����Ի�����������ָ��
			pTestProject->OnInit();
			pTestProject->ParseXMLForMultiple(&oElement);
			// ���ӵ�����
			m_olsTestProject.AddTail(pTestProject);
			// ���ӵ�������
			m_oTestProjectMap.SetAt(pTestProject->m_uiTestNb, pTestProject);
			uiCountProject++;
		}
	}
	m_uiCountAll = m_uiCountAll + uiCountProject;	// ����
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
	m_uiCountAll = m_uiCountAll + 1;	// ����

	CTestProject* pTestProject = NULL;
	pTestProject = new CTestProject;
	pTestProject->m_pTestBaseListInstrument = m_pTestBaseListInstrument;	// �������Ի�����������ָ��
	pTestProject->m_pTestBaseListSensor = m_pTestBaseListSensor;	// �첨�����Ի�����������ָ��
	pTestProject->OnInit();
	pTestProject->ParseXMLForSeisMonitor(&oElement);
	// ���ӵ�����
	m_olsTestProject.AddTail(pTestProject);
	// ���ӵ�������
	m_oTestProjectMap.SetAt(pTestProject->m_uiTestNb, pTestProject);
}

/**
* �����������Ƿ��Ѽ���������
* @param unsigned int uiIndex ����������
* @return BOOL TRUE���ǣ�FALSE����
*/
BOOL CTestProjectList::IfIndexExistInMap(unsigned int uiIndex)
{
	CTestProject* pTestProject = NULL;
	return m_oTestProjectMap.Lookup(uiIndex, pTestProject);
}

/**
* �������������ţ���������õ�������Ŀָ��
* @param unsigned int uiIndex ������
* @param CTestProject* &pTestProject	������Ŀָ�룬���õ���
* @return BOOL TRUE���ɹ���FALSE��ʧ��
*/
BOOL CTestProjectList::GetTestProject(unsigned int uiIndex, CTestProject* &pTestProject)
{
	return m_oTestProjectMap.Lookup(uiIndex, pTestProject);
}

