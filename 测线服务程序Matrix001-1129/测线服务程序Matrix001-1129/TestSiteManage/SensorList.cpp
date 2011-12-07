#include "StdAfx.h"
#include "SensorList.h"

CSensorList::CSensorList()
{
}

CSensorList::~CSensorList()
{
}

/**
* ��ʼ��
* @param void
* @return void
*/
void CSensorList::OnInit()
{
	// ���������ļ�
	ParseXML();
}

/**
* ���¼���
* @param void
* @return void
*/
void CSensorList::OnReload()
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
void CSensorList::OnClose()
{
	// �첨����������0
	if(m_uiCountAll > 0)
	{
		// �첨��ָ��
		CSensorData* pSensor;
		while(FALSE == m_olsSensor.IsEmpty())
		{
			// �Ƴ�����
			pSensor = m_olsSensor.RemoveHead();
			// ɾ���첨��
			delete pSensor;
		}
		// ��ռ첨��������
		m_oSensorMap.RemoveAll();
	}
	m_uiCountAll = 0;
}

/**
* ���������ļ�����	SurveySetup��ApplySensor
* @param void
* @return void
*/
void CSensorList::OnSetupDataChangeForSurveySetupApplySensor()
{
	CString strKey;
	CXMLDOMNodeList oNodeList;
	CXMLDOMElement oElement;
	LPDISPATCH lpDispatch;

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
	// �õ�����
	lpDispatch = oElement.get_childNodes();
	oNodeList.AttachDispatch(lpDispatch);

	CSensorData oSensor;
	CSensorData* pSensor = NULL;
	for(unsigned int i = 0; i < m_uiCountAll; i++)
	{
		lpDispatch = oNodeList.get_item(i);
		oElement.AttachDispatch(lpDispatch);
		oSensor.ParseXML(&oElement);

		pSensor = NULL;
		pSensor = GetSensor(oSensor.m_uiNb);
		if(NULL != pSensor)
		{
			*pSensor = oSensor;
		}
	}
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
	// �õ�����
	lpDispatch = oElement.get_childNodes();
	oNodeList.AttachDispatch(lpDispatch);

	CSensorData* pSensor = NULL;
	for(unsigned int i = 0; i < m_uiCountAll; i++)
	{
		lpDispatch = oNodeList.get_item(i);
		oElement.AttachDispatch(lpDispatch);
		pSensor = new CSensorData;
		pSensor->ParseXML(&oElement);
		// ���Ӽ첨��
		m_olsSensor.AddTail(pSensor);
		// ����첨��������
		m_oSensorMap.SetAt(pSensor->m_uiNb, pSensor);
	}

	// ���һ��Ϊ������׼���Ŀռ첨��
	m_uiCountAll++;	// �첨��������1
	pSensor = new CSensorData;
	pSensor->m_uiSegdCode = 0;
	pSensor->m_strLabel = "Jumped";
	pSensor->m_fContinuityMin = 0.0;
	pSensor->m_fContinuityMax = 0.0;
	pSensor->m_fTilt = 0.0;
	pSensor->m_fNoise = 0.0;
	pSensor->m_fLeaKage = 0.0;
	pSensor->m_uiNb = 0;
	// ���Ӽ첨��
	m_olsSensor.AddTail(pSensor);
	// ����첨��������
	m_oSensorMap.SetAt(pSensor->m_uiNb, pSensor);
}

/**
* ���������ţ��õ��첨��ָ��
* @param unsigned int uiNb �첨����
* @return CSensorData* �첨��ָ�� NULL:��ָ��
*/
CSensorData* CSensorList::GetSensor(unsigned int uiNb)
{
	CSensorData* pSensor = NULL;
	// ���Ҽ첨��������
	if(TRUE == m_oSensorMap.Lookup(uiNb, pSensor))
	{
		return pSensor;
	}
	return NULL;
}