#include "StdAfx.h"
#include "TestProject.h"

CTestProject::CTestProject()
{
	OnInit();
}

CTestProject::~CTestProject()
{
}

/**
* ��ʼ��
* @param void
* @return void
*/
void CTestProject::OnInit()
{
	m_uiProjectType = 0;	// ������Ŀ���� 1-�������ԣ�2-�첨�����ԣ�3-���ϲ��ԣ�4-�������

	m_uiTestNb = 0;	// ������Ŀ������
	m_strAuxiliaryDescr = "";	// ����������
	m_strAbsoluteSpread = "";	// �������ж���
	m_uiDelayBetweenTest = 0;	// ÿ�β���֮��ļ�������룩
	m_uiRecordResult = 0;	// �Ƿ��¼��������  0-����¼��1-��¼
	m_uiRecordLength = 0;	// ���Լ�¼ʱ�䣨���룩
	m_uiTestFileNb = 0;	// �����ļ���
	m_uiCountAll = 0;	// ������������
}

/**
* ���¼���
* @param void
* @return void
*/
void CTestProject::OnReload()
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
void CTestProject::OnClose()
{
	m_olsTestRequest.RemoveAll();
	m_uiCountAll = 0;
}

/**
* ���������ļ�
* @param void
* @return void
*/
void CTestProject::ParseXML(CXMLDOMElement* pElement)
{
	// ������Ŀ���� 1-�������ԣ�2-�첨�����ԣ�3-���ϲ��ԣ�4-�������
	switch(m_uiProjectType)
	{
	case 1:
		// ����XML����������
		ParseXMLForInstrument(pElement);
		break;
	case 2:
		// ����XML���첨������
		ParseXMLForSensor(pElement);
		break;
	case 3:
		// ����XML�����ϲ���
		ParseXMLForMultiple(pElement);
		break;
	case 4:
		// ����XML���������
		ParseXMLForSeisMonitor(pElement);
		break;
	}
}

/**
* ����XML����������
* @param CXMLDOMElement* pElement XML�ĵ��ڵ�ָ��
* @return void
*/
void CTestProject::ParseXMLForInstrument(CXMLDOMElement* pElement)
{
	CString strKey;
	strKey = "TestNb";
	m_uiTestNb = CXMLDOMTool::GetElementAttributeUnsignedInt(pElement, strKey);	// ������Ŀ������
	strKey = "Recorded";
	m_uiRecordResult = CXMLDOMTool::GetElementAttributeUnsignedInt(pElement, strKey);	// �Ƿ��¼��������  0-����¼��1-��¼
	strKey = "RecordLength";
	m_uiRecordLength = CXMLDOMTool::GetElementAttributeUnsignedInt(pElement, strKey);	// ���Լ�¼ʱ�䣨���룩
	strKey = "AuxiliaryDescr";
	m_strAuxiliaryDescr = CXMLDOMTool::GetElementAttributeString(pElement, strKey);	// ����������
	strKey = "AbsoluteSpread";
	m_strAbsoluteSpread = CXMLDOMTool::GetElementAttributeString(pElement, strKey);	// �������ж���

	// ������������
	CTestRequest oTestRequest;
	// ����XML����������
	oTestRequest.ParseXMLForInstrument(pElement);
	m_olsTestRequest.AddTail(oTestRequest);	// ���ӵ�����
	m_uiCountAll = 1;
}

/**
* ����XML���첨������
* @param CXMLDOMElement* pElement XML�ĵ��ڵ�ָ��
* @return void
*/
void CTestProject::ParseXMLForSensor(CXMLDOMElement* pElement)
{
	CString strKey;
	strKey = "TestNb";
	m_uiTestNb = CXMLDOMTool::GetElementAttributeUnsignedInt(pElement, strKey);	// ������Ŀ������
	strKey = "Recorded";
	m_uiRecordResult = CXMLDOMTool::GetElementAttributeUnsignedInt(pElement, strKey);	// �Ƿ��¼��������  0-����¼��1-��¼	
	strKey = "AbsoluteSpread";
	m_strAbsoluteSpread = CXMLDOMTool::GetElementAttributeString(pElement, strKey);	// �������ж���

	// ������������
	CTestRequest oTestRequest;
	// ����XML���첨������
	oTestRequest.ParseXMLForSensor(pElement);	
	m_olsTestRequest.AddTail(oTestRequest);	// ���ӵ�����
	m_uiCountAll = 1;
}

/**
* ����XML�����ϲ���
* @param CXMLDOMElement* pElement XML�ĵ��ڵ�ָ��
* @return void
*/
void CTestProject::ParseXMLForMultiple(CXMLDOMElement* pElement)
{
	// ������������
	CXMLDOMNodeList oNodeList;
	CXMLDOMElement oElement;
	LPDISPATCH lpDispatch;
	unsigned int i;
	CString strKey;

	strKey = "TestNb";
	m_uiTestNb = CXMLDOMTool::GetElementAttributeUnsignedInt(pElement, strKey);	// ������Ŀ������
	strKey = "TestName";
	m_strTestName = CXMLDOMTool::GetElementAttributeString(pElement, strKey);	// ������Ŀ����
	strKey = "DelayBetweenTest";
	m_uiDelayBetweenTest = CXMLDOMTool::GetElementAttributeUnsignedInt(pElement, strKey);	//  ÿ�β���֮��ļ�������룩
	strKey = "RecordResults";
	m_uiRecordResult = CXMLDOMTool::GetElementAttributeUnsignedInt(pElement, strKey);	// �Ƿ��¼��������  0-����¼��1-��¼
	strKey = "RecordLength";
	m_uiRecordLength = CXMLDOMTool::GetElementAttributeUnsignedInt(pElement, strKey);	// ���Լ�¼ʱ�䣨���룩
	strKey = "AuxiliaryDescr";
	m_strAuxiliaryDescr = CXMLDOMTool::GetElementAttributeString(pElement, strKey);	// ����������
	strKey = "AbsoluteSpread";
	m_strAbsoluteSpread = CXMLDOMTool::GetElementAttributeString(pElement, strKey);	// �������ж���
	strKey = "TestFileNb";
	m_uiTestFileNb = CXMLDOMTool::GetElementAttributeUnsignedInt(pElement, strKey);	// �����ļ���
	// �õ�������������
	strKey = "Count";
	m_uiCountAll = CXMLDOMTool::GetElementAttributeInt(pElement, strKey);	// ������������
	// �õ�Tab������
	strKey = "TabCount";
	m_uiTabCount = CXMLDOMTool::GetElementAttributeInt(pElement, strKey);

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
	lpDispatch = pElement->get_childNodes();
	oNodeList.AttachDispatch(lpDispatch);
	CTestRequest oTestRequest;
	for(unsigned int i = 0; i < m_uiCountAll; i++)
	{
		lpDispatch = oNodeList.get_item(i);
		oElement.AttachDispatch(lpDispatch);
		oTestRequest.ParseXMLForMultiple(&oElement);
		m_olsTestRequest.AddTail(oTestRequest);	// ���ӵ�����
	}
}

/**
* ����XML���������
* @param CXMLDOMElement* pElement XML�ĵ��ڵ�ָ��
* @return void
*/
void CTestProject::ParseXMLForSeisMonitor(CXMLDOMElement* pElement)
{
	CString strKey;
	strKey = "AbsoluteSpread";
	m_strAbsoluteSpread = CXMLDOMTool::GetElementAttributeString(pElement, strKey);	// �������ж���
	m_uiCountAll = 0;	// ������������
}

/**
* ���������ļ�
* @param void
* @return void
*/
void CTestProject::AddToXML(CXMLDOMElement* pElement, CXMLDOMDocument* pXMLDOMDocument)
{
	// ������Ŀ���� 1-�������ԣ�2-�첨�����ԣ�3-���ϲ��ԣ�4-�������
	switch(m_uiProjectType)
	{
	case 1:
		// ����XML����������
		AddToXMLForInstrument(pElement);
		break;
	case 2:
		// ����XML���첨������
		AddToXMLForSensor(pElement);
		break;
	case 3:
		// ����XML�����ϲ���
		AddToXMLForMultiple(pElement, pXMLDOMDocument);
		break;
	case 4:
		// ����XML���������
		AddToXMLForSeisMonitor(pElement);
		break;
	}
}

/**
* ����XML����������
* @param CXMLDOMElement* pElement XML�ĵ��ڵ�ָ��
* @return void
*/
void CTestProject::AddToXMLForInstrument(CXMLDOMElement* pElement)
{
	CString strKey;	// ����
	COleVariant oVariant;

	strKey = "TestNb";
	oVariant = (long)m_uiTestNb;
	pElement->setAttribute(strKey, oVariant);

	strKey = "Recorded";
	oVariant = (long)m_uiRecordResult;
	pElement->setAttribute(strKey, oVariant);

	strKey = "RecordLength";
	oVariant = (long)m_uiRecordLength;
	pElement->setAttribute(strKey, oVariant);

	strKey = "AuxiliaryDescr";
	oVariant = m_strAuxiliaryDescr;
	pElement->setAttribute(strKey, oVariant);

	strKey = "AbsoluteSpread";
	oVariant = m_strAbsoluteSpread;
	pElement->setAttribute(strKey, oVariant);

	// �����������
	CTestRequest oTestRequest = m_olsTestRequest.RemoveHead();
	oTestRequest.AddToXMLForInstrument(pElement);
}

/**
* ����XML���첨������
* @param CXMLDOMElement* pElement XML�ĵ��ڵ�ָ��
* @return void
*/
void CTestProject::AddToXMLForSensor(CXMLDOMElement* pElement)
{
	CString strKey;	// ����
	COleVariant oVariant;

	strKey = "TestNb";
	oVariant = (long)m_uiTestNb;
	pElement->setAttribute(strKey, oVariant);

	strKey = "Recorded";
	oVariant = (long)m_uiRecordResult;
	pElement->setAttribute(strKey, oVariant);

	strKey = "AbsoluteSpread";
	oVariant = m_strAbsoluteSpread;
	pElement->setAttribute(strKey, oVariant);

	// �����������
	CTestRequest oTestRequest = m_olsTestRequest.RemoveHead();
	oTestRequest.AddToXMLForSensor(pElement);
}

/**
* ����XML�����ϲ���
* @param CXMLDOMElement* pElement XML�ĵ��ڵ�ָ��
* @return void
*/
void CTestProject::AddToXMLForMultiple(CXMLDOMElement* pElement, CXMLDOMDocument* pXMLDOMDocument)
{
	CString strKey;	// ����
	COleVariant oVariant;

	strKey = "Count";
	oVariant = (long)m_uiCountAll;
	pElement->setAttribute(strKey, oVariant);

	strKey = "TestNb";
	oVariant = (long)m_uiTestNb;
	pElement->setAttribute(strKey, oVariant);

	strKey = "DelayBetweenTest";
	oVariant = (long)m_uiDelayBetweenTest;
	pElement->setAttribute(strKey, oVariant);

	strKey = "RecordResults";
	oVariant = (long)m_uiRecordResult;
	pElement->setAttribute(strKey, oVariant);

	strKey = "RecordLength";
	oVariant = (long)m_uiRecordLength;
	pElement->setAttribute(strKey, oVariant);

	strKey = "AuxiliaryDescr";
	oVariant = m_strAuxiliaryDescr;
	pElement->setAttribute(strKey, oVariant);

	strKey = "AbsoluteSpread";
	oVariant = m_strAbsoluteSpread;
	pElement->setAttribute(strKey, oVariant);

	strKey = "TestFileNb";
	oVariant = (long)m_uiTestFileNb;
	pElement->setAttribute(strKey, oVariant);

	CXMLDOMNodeList oNodeList;
	CXMLDOMElement oElementChild;
	LPDISPATCH lpDispatch;
	// ɾ�������ӽڵ�
	while(TRUE == pElement->hasChildNodes())
	{
		lpDispatch = pElement->get_firstChild();
		pElement->removeChild(lpDispatch);
	}

	// �����½ڵ�
	CTestRequest oTestRequest;
	for(unsigned int i = 0; i < m_uiCountAll; i++)
	{
		oTestRequest = m_olsTestRequest.RemoveHead();

		lpDispatch = pXMLDOMDocument->createTextNode(m_strTabChild);
		pElement->appendChild(lpDispatch);

		lpDispatch = pXMLDOMDocument->createElement("Record");
		oElementChild.AttachDispatch(lpDispatch);
		oTestRequest.AddToXMLForMultiple(&oElementChild);
		pElement->appendChild(lpDispatch);

		if(i == (m_uiCountAll - 1))
		{
			lpDispatch = pXMLDOMDocument->createTextNode(m_strTabParent);
			pElement->appendChild(lpDispatch);
		}		
	}
}

/**
* ����XML���������
* @param CXMLDOMElement* pElement XML�ĵ��ڵ�ָ��
* @return void
*/
void CTestProject::AddToXMLForSeisMonitor(CXMLDOMElement* pElement)
{
	CString strKey;	// ����
	COleVariant oVariant;

	strKey = "AbsoluteSpread";
	oVariant = m_strAbsoluteSpread;
	pElement->setAttribute(strKey, oVariant);
}