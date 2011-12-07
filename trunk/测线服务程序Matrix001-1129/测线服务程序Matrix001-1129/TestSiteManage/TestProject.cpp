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
* ����
* @param void
* @return void
*/
void CTestProject::OnReset()
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
	// ��������0
	if(m_uiCountAll > 0)
	{
		// ָ��
		CTestRequest* pTestRequest;
		while(FALSE == m_olsTestRequest.IsEmpty())
		{
			// �Ƴ�����
			pTestRequest = m_olsTestRequest.RemoveHead();
			// ɾ��
			delete pTestRequest;
		}
	}
	m_uiCountAll = 0;
	m_olsTestRequestTemp.RemoveAll();	// ����������У���ʱ
	m_olsIP.RemoveAll();	// �μӲ���������IP��ַ����
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
	m_uiTestNb = m_uiTestNb + 1000;
	strKey = "Recorded";
	m_uiRecordResult = CXMLDOMTool::GetElementAttributeUnsignedInt(pElement, strKey);	// �Ƿ��¼��������  0-����¼��1-��¼
	strKey = "RecordLength";
	m_uiRecordLength = CXMLDOMTool::GetElementAttributeUnsignedInt(pElement, strKey);	// ���Լ�¼ʱ�䣨���룩
	strKey = "AuxiliaryDescr";
	m_strAuxiliaryDescr = CXMLDOMTool::GetElementAttributeString(pElement, strKey);	// ����������
	strKey = "AbsoluteSpread";
	m_strAbsoluteSpread = CXMLDOMTool::GetElementAttributeString(pElement, strKey);	// �������ж���
	m_uiDelayBetweenTest = 1000;	// ÿ�β���֮��ļ�������룩
	m_uiProjectType = 1;	// ������Ŀ���� 1-�������ԣ�2-�첨�����ԣ�3-���ϲ��ԣ�4-�������

	// ������������
	CTestRequest* pTestRequest = new CTestRequest;
	// ����XML����������
	pTestRequest->ParseXMLForInstrument(pElement);
	m_olsTestRequestTemp.AddTail(pTestRequest);	// ���ӵ���ʱ����
	// ����Ҫ��һ�β���ȫ����Ŀ�Ĳ���������������
	ReArrangeByTestType(pTestRequest);
	m_uiCountAll = m_olsTestRequest.GetCount();	// ������������
	delete pTestRequest;
	m_olsTestRequestTemp.RemoveAll();
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
	m_uiTestNb = m_uiTestNb + 2000;
	strKey = "Recorded";
	m_uiRecordResult = CXMLDOMTool::GetElementAttributeUnsignedInt(pElement, strKey);	// �Ƿ��¼��������  0-����¼��1-��¼	
	strKey = "AbsoluteSpread";
	m_strAbsoluteSpread = CXMLDOMTool::GetElementAttributeString(pElement, strKey);	// �������ж���
	m_strAuxiliaryDescr = "";	// ����������
	m_uiRecordLength = 1000;	// ���Լ�¼ʱ�䣨���룩
	m_uiDelayBetweenTest = 1000;	// ÿ�β���֮��ļ�������룩
	m_uiProjectType = 2;	// ������Ŀ���� 1-�������ԣ�2-�첨�����ԣ�3-���ϲ��ԣ�4-�������

	// ������������
	CTestRequest* pTestRequest = new CTestRequest;
	// ����XML���첨������
	pTestRequest->ParseXMLForSensor(pElement);	
	m_olsTestRequestTemp.AddTail(pTestRequest);	// ���ӵ���ʱ����
	// ����Ҫ��һ�β���ȫ����Ŀ�Ĳ������󣬼첨������
	ReArrangeByTestType(pTestRequest);
	m_uiCountAll = m_olsTestRequest.GetCount();	// ������������
	delete pTestRequest;
	m_olsTestRequestTemp.RemoveAll();
}

/**
* ����XML�����ϲ���
* @param CXMLDOMElement* pElement XML�ĵ��ڵ�ָ��
* @return void
*/
void CTestProject::ParseXMLForMultiple(CXMLDOMElement* pElement)
{
	CString strKey;
	strKey = "TestNb";
	m_uiTestNb = CXMLDOMTool::GetElementAttributeUnsignedInt(pElement, strKey);	// ������Ŀ������
	m_uiTestNb = m_uiTestNb + 3000;
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
	m_uiProjectType = 3;	// ������Ŀ���� 1-�������ԣ�2-�첨�����ԣ�3-���ϲ��ԣ�4-�������

	// ������������
	CXMLDOMNodeList oNodeList;
	CXMLDOMElement oElement;
	LPDISPATCH lpDispatch;
	// �õ�������������
	strKey = "Count";
	unsigned int uiCountAll = CXMLDOMTool::GetElementAttributeInt(pElement, strKey);	// ������������
	// �õ�����
	lpDispatch = pElement->get_childNodes();
	oNodeList.AttachDispatch(lpDispatch);
	CTestRequest* pTestRequest = NULL;
	for(unsigned int i = 0; i < uiCountAll; i++)
	{
		lpDispatch = oNodeList.get_item(i);
		oElement.AttachDispatch(lpDispatch);
		pTestRequest = new CTestRequest;
		pTestRequest->ParseXMLForMultiple(&oElement);
		m_olsTestRequestTemp.AddTail(pTestRequest);	// ���ӵ���ʱ����
	}
	// �����ϲ��ԵĲ�������
	ReArrangeForMultiple();
	m_uiCountAll = m_olsTestRequest.GetCount();	// ������������
	while(FALSE == m_olsTestRequestTemp.IsEmpty())
	{		
		pTestRequest = m_olsTestRequestTemp.RemoveHead();	// �Ƴ�����		
		delete pTestRequest;	// ɾ��
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
	m_uiTestNb = 4000;	// ������Ŀ������
	m_strAuxiliaryDescr = "";	// ����������
	m_uiDelayBetweenTest = 0;	// ÿ�β���֮��ļ�������룩
	m_uiRecordResult = 0;	// �Ƿ��¼��������  0-����¼��1-��¼
	m_uiRecordLength = 86400000;	// ���Լ�¼ʱ�䣨���룩	24Сʱ
	m_uiProjectType = 4;	// ������Ŀ���� 1-�������ԣ�2-�첨�����ԣ�3-���ϲ��ԣ�4-�������

	// ������������
	CTestRequest* pTestRequest = new CTestRequest;
	pTestRequest->m_uiIndex = 1;	// ������	
	pTestRequest->m_uiAim = 2;	// ���Զ���	1-������2-�첨����3-ȫ��
	pTestRequest->m_uiType = 22;	// ��������
	pTestRequest->m_uiGain = 1600;	// ����
	pTestRequest->m_uiLoopNb = 0;	// ��ת����������
	pTestRequest->m_uiLoopCount = 0;	// ѭ������
	// ���ӵ�����
	m_olsTestRequest.AddTail(pTestRequest);
	m_uiCountAll = 1;	// ������������
}

/**
* ����Ҫ��һ�β���ȫ����Ŀ�Ĳ�������
* @param CTestRequest* pTestRequest ��������ָ��
* @return void
*/
void CTestProject::ReArrangeByTestType(CTestRequest* pTestRequest)
{
	if(30 == pTestRequest->m_uiType)	// 30 ����ȫ��������Ŀ
	{
		CTestRequest* pTestRequestNew = NULL;
		for(unsigned int i = 0; i < m_pTestBaseListInstrument->m_uiCountAll; i++)
		{
			pTestRequestNew = new CTestRequest;
			*pTestRequestNew = *pTestRequest;
			pTestRequestNew->m_uiType = m_pTestBaseListInstrument->GetTestBaseDataByIndex(i)->m_uiType;
			pTestRequest->m_uiAim =1;
			m_olsTestRequest.AddTail(pTestRequestNew);
		}
	}
	else if(40 == pTestRequest->m_uiType)	// 40 �첨��ȫ��������Ŀ
	{
		CTestRequest* pTestRequestNew = NULL;
		for(unsigned int i = 0; i < (m_pTestBaseListSensor->m_uiCountAll - 1); i++)
		{
			pTestRequestNew = new CTestRequest;
			*pTestRequestNew = *pTestRequest;
			pTestRequestNew->m_uiType = m_pTestBaseListSensor->GetTestBaseDataByIndex(i)->m_uiType;
			pTestRequest->m_uiAim =2;
			m_olsTestRequest.AddTail(pTestRequestNew);
		}
	}
	else if(50 == pTestRequest->m_uiType)	// 50 �����ͼ첨��ȫ��������Ŀ
	{
		CTestRequest* pTestRequestNew = NULL;
		unsigned int i;
		for(i = 0; i < m_pTestBaseListInstrument->m_uiCountAll; i++)
		{
			pTestRequestNew = new CTestRequest;
			*pTestRequestNew = *pTestRequest;
			pTestRequestNew->m_uiType = m_pTestBaseListInstrument->GetTestBaseDataByIndex(i)->m_uiType;
			pTestRequest->m_uiAim =1;
			m_olsTestRequest.AddTail(pTestRequestNew);
		}
		
		for(i = 0; i < (m_pTestBaseListSensor->m_uiCountAll - 1); i++)
		{
			pTestRequestNew = new CTestRequest;
			*pTestRequestNew = *pTestRequest;
			pTestRequestNew->m_uiType = m_pTestBaseListSensor->GetTestBaseDataByIndex(i)->m_uiType;
			pTestRequest->m_uiAim =1;
			m_olsTestRequest.AddTail(pTestRequestNew);
		}
	}
	else if(0 == pTestRequest->m_uiLoopNb)	// �ǿ�������
	{
		CTestRequest* pTestRequestNew = NULL;
		pTestRequestNew = new CTestRequest;
		*pTestRequestNew = *pTestRequest;
		// ���ò�������Ĳ���Ŀ�� 1-������2-�첨��
		SetTestRequestAim(pTestRequestNew);
		m_olsTestRequest.AddTail(pTestRequestNew);
	}
}

/**
* �����ϲ��ԵĲ�������
* @param void
* @return void
*/
void CTestProject::ReArrangeForMultiple()
{
	unsigned int uiCountAll = 0;
	unsigned int uiNbStart = 0;
	CTestRequest* pTestRequest = NULL;
	bool bStartFound = false;
	bool bLoopContinue = false;
	POSITION pos;

	uiCountAll = m_olsTestRequestTemp.GetCount();	// ������������
	pTestRequest = m_olsTestRequestTemp.GetHead();
	uiNbStart = pTestRequest->m_uiIndex;
	while(true)
	{
		for(unsigned int i = 0; i < uiCountAll; i++)
		{
			pos = m_olsTestRequestTemp.FindIndex(i);
			pTestRequest = m_olsTestRequestTemp.GetAt(pos);
			if((false == bStartFound) && (uiNbStart != pTestRequest->m_uiIndex))
			{
				continue;
			}
			else
			{
				bStartFound = true;
			}
			if((pTestRequest->m_uiLoopNb > 0) && (pTestRequest->m_uiLoopCount > 0))
			{
				uiNbStart = pTestRequest->m_uiLoopNb;
				pTestRequest->m_uiLoopCount--;
				bStartFound = false;
				bLoopContinue = true;
				break;
			}
			// ����Ҫ��һ�β���ȫ����Ŀ�Ĳ������󣬸��ϲ���
			ReArrangeByTestType(pTestRequest);
			bLoopContinue = false;
		}
		if(false == bLoopContinue)
		{
			break;
		}
	}
}

/**
* ���Ʋ�����Ŀ
* @param CTestProject* pTestProject ������Ŀָ��
* @return void
*/
void CTestProject::Clone(CTestProject* pTestProject)
{
	m_uiProjectType = pTestProject->m_uiProjectType;	// ������Ŀ���� 1-�������ԣ�2-�첨�����ԣ�3-���ϲ��ԣ�4-�������
	m_uiTestNb = pTestProject->m_uiTestNb;	// ������Ŀ������
	m_strAuxiliaryDescr = pTestProject->m_strAuxiliaryDescr;	// ����������
	m_strAbsoluteSpread = pTestProject->m_strAbsoluteSpread;	// �������ж���
	m_uiDelayBetweenTest = pTestProject->m_uiDelayBetweenTest;	// ÿ�β���֮��ļ�������룩
	m_uiRecordResult = pTestProject->m_uiRecordResult;	// �Ƿ��¼��������  0-����¼��1-��¼
	m_uiRecordLength = pTestProject->m_uiRecordLength;	// ���Լ�¼ʱ�䣨���룩
	m_uiTestFileNb = pTestProject->m_uiTestFileNb;	// �����ļ���
	m_uiCountAll = pTestProject->m_uiCountAll;	// ������������

	CTestRequest* pTestRequestNew = NULL;
	CTestRequest* pTestRequest = NULL;
	POSITION pos;
	for(unsigned int i = 0; i < m_uiCountAll; i++)
	{
		pos = pTestProject->m_olsTestRequest.FindIndex(i);
		pTestRequest = pTestProject->m_olsTestRequest.GetAt(pos);
		pTestRequestNew = new CTestRequest;
		*pTestRequestNew = *pTestRequest;
		m_olsTestRequest.AddTail(pTestRequestNew);
	}
}

/**
* ���ò�������Ĳ���Ŀ�� 1-������2-�첨��
* @param CTestRequest* pTestRequest ��������ָ��
* @return void
*/
void CTestProject::SetTestRequestAim(CTestRequest* pTestRequest)
{
	if(NULL != m_pTestBaseListInstrument->GetTestBaseDataByTestType(pTestRequest->m_uiType))
	{
		pTestRequest->m_uiAim = 1;
		return;
	}
	if(NULL != m_pTestBaseListSensor->GetTestBaseDataByTestType(pTestRequest->m_uiType))
	{
		pTestRequest->m_uiAim = 2;
		return;
	}
}

/**
* ���ݲ������ͣ��õ����Բ��Ի�������ָ��
* @param unsigned int uiType ��������
* @return CTestBaseData* ���Ի�������ָ�� NULL����
*/
CTestBaseData* CTestProject::GetTestBaseDataByTestType(unsigned int uiType)
{
	CTestBaseData* pTestBaseData = NULL;
	pTestBaseData = m_pTestBaseListInstrument->GetTestBaseDataByTestType(uiType);
	if(NULL != pTestBaseData)
	{
		return pTestBaseData;
	}
	pTestBaseData = m_pTestBaseListSensor->GetTestBaseDataByTestType(uiType);
	if(NULL != pTestBaseData)
	{
		return pTestBaseData;
	}
	return NULL;
}

/**
* ���ò�����Ŀ�����Բ�����ͼ
* @param unsigned int uiTestAim ���Զ���	1-������2-�첨����3-ȫ��
* @param unsigned int uiTestType ��������
* @return void
*/
void CTestProject::SetupTestProjectFromView(unsigned int uiTestAim, unsigned int uiTestType)
{
	// ������������
	CTestRequest* pTestRequest = new CTestRequest;
	pTestRequest->OnReset();

	pTestRequest->m_uiIndex = 1;	// ������	
	pTestRequest->m_uiAim = uiTestAim;	// ���Զ���	1-������2-�첨����3-ȫ��
	pTestRequest->m_uiType = uiTestType;	// ��������

	m_olsTestRequestTemp.AddTail(pTestRequest);	// ���ӵ���ʱ����
	// ����Ҫ��һ�β���ȫ����Ŀ�Ĳ�������
	ReArrangeByTestType(pTestRequest);
	m_uiCountAll = m_olsTestRequest.GetCount();	// ������������
	delete pTestRequest;
	pTestRequest = NULL;
	m_olsTestRequestTemp.RemoveAll();

	POSITION pos;
	CTestBaseData* pTestBaseData = NULL;
	for(unsigned int i = 0; i < m_uiCountAll; i++)
	{
		pos = m_olsTestRequest.FindIndex(i);
		pTestRequest = m_olsTestRequest.GetAt(pos);
		if(1 == uiTestAim)	// ���Զ���	1-������2-�첨����3-ȫ��
		{
			pTestBaseData = m_pTestBaseListInstrument->GetTestBaseDataByTestType(pTestRequest->m_uiType);
		}
		else if(2 == uiTestAim)	// ���Զ���	1-������2-�첨����3-ȫ��
		{
			pTestBaseData = m_pTestBaseListSensor->GetTestBaseDataByTestType(pTestRequest->m_uiType);
		}		
		pTestRequest->m_uiGain = pTestBaseData->m_uiGain;
	}
}

/**
* ���û���������Ŀ�������¼Ӽ첨���ĳ�ʼ����
* @param UINT uiTestResistance �������Ƿ����Resistance
* @param UINT uiTestTilt �������Ƿ����Tilt
* @param UINT uiTestLeakage �������Ƿ����Leakage
* @return void
*/
void CTestProject::SetupTestProjectForSensorTestOnField(UINT uiTestResistance, UINT uiTestTilt, UINT uiTestLeakage)
{
	CTestRequest* pTestRequestNew = NULL;
	if(1 == uiTestResistance)
	{
		pTestRequestNew = new CTestRequest;
		pTestRequestNew->m_uiIndex = 1;	// ������	
		pTestRequestNew->m_uiAim = 2;	// ���Զ���	1-������2-�첨����3-ȫ��
		pTestRequestNew->m_uiType = 15;	// ��������
		m_olsTestRequest.AddTail(pTestRequestNew);
	}
	if(1 == uiTestTilt)
	{
		pTestRequestNew = new CTestRequest;
		pTestRequestNew->m_uiIndex = 1;	// ������	
		pTestRequestNew->m_uiAim = 2;	// ���Զ���	1-������2-�첨����3-ȫ��
		pTestRequestNew->m_uiType = 20;	// ��������
		m_olsTestRequest.AddTail(pTestRequestNew);
	}
	if(1 == uiTestLeakage)
	{
		pTestRequestNew = new CTestRequest;
		pTestRequestNew->m_uiIndex = 1;	// ������	
		pTestRequestNew->m_uiAim = 2;	// ���Զ���	1-������2-�첨����3-ȫ��
		pTestRequestNew->m_uiType = 14;	// ��������
		m_olsTestRequest.AddTail(pTestRequestNew);
	}
	m_uiCountAll = m_olsTestRequest.GetCount();	// ������������

	POSITION pos;
	CTestBaseData* pTestBaseData = NULL;
	for(unsigned int i = 0; i < m_uiCountAll; i++)
	{
		pos = m_olsTestRequest.FindIndex(i);
		pTestRequestNew = m_olsTestRequest.GetAt(pos);
		pTestBaseData = m_pTestBaseListSensor->GetTestBaseDataByTestType(pTestRequestNew->m_uiType);		
		pTestRequestNew->m_uiGain = pTestBaseData->m_uiGain;
	}
}