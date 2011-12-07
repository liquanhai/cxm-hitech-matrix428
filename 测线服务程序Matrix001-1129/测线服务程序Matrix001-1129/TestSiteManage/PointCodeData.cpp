#include "StdAfx.h"
#include "PointCodeData.h"

CPointCodeData::CPointCodeData()
{
}

CPointCodeData::~CPointCodeData()
{
}

/**
* ����XML
* @param CXMLDOMElement* pElement XML�ĵ��ڵ�ָ��
* @return void
*/
void CPointCodeData::ParseXML(CXMLDOMElement* pElement)
{
	CString strKey;
	strKey = "Nb";
	m_uiNb = CXMLDOMTool::GetElementAttributeInt(pElement, strKey);
	strKey = "Label";
	m_strLabel = CXMLDOMTool::GetElementAttributeString(pElement, strKey);
	strKey = "SensorType";
	m_strSensorType = CXMLDOMTool::GetElementAttributeString(pElement, strKey);
}

/**
* �����첨������
* @param CSensorList* pSensorList �첨������ָ��
* @return void
*/
void CPointCodeData::ParseSensorType(CSensorList* pSensorList)
{
	// ת��ΪСд
	m_strSensorType.MakeLower();
	// ������ cs �� p0 �滻
	m_strSensorType.Replace(_T("cs"), _T("s0"));
	// ȥ����ʶ�� s
	m_strSensorType.Replace(_T("s"), _T(""));

	CString strPart;	// �첨��Nb�ַ���
	int iSensorType;	// �첨��Nb
	CSensorData* pSensorData;	// �첨��ָ��
	POSITION pos;	// λ��
	int iPos, iPosStart, iPosStartEnd;	// λ��
	int iCount, i;
	CList<int, int> lsPos;	// λ�ö���

	lsPos.AddTail(-1);
	iPosStart = 0;
	while(true)
	{
		// ���ҷָ���"+"
		iPos = m_strSensorType.Find('+', iPosStart);
		if(-1 == iPos)
		{
			break;
		}
		lsPos.AddTail(iPos);
		iPosStart = iPos + 1;
	}
	lsPos.AddTail(m_strSensorType.GetAllocLength());

	// �õ���ǵ� "+" ����
	iCount = lsPos.GetCount();
	for(i = 0; i < iCount - 1; i++)
	{
		pos = lsPos.FindIndex(i);
		iPosStart = lsPos.GetAt(pos) + 1;
		pos = lsPos.FindIndex(i + 1);
		iPosStartEnd = lsPos.GetAt(pos);
		// �õ��첨��Nb�ַ���
		strPart = m_strSensorType.Mid(iPosStart, iPosStartEnd - iPosStart);
		// �õ��첨��Nb 
		iSensorType = CXMLDOMTool::ConvertStringToInt(strPart);
		// �õ��첨������ָ��
		pSensorData = pSensorList->GetSensor(iSensorType);
		if(NULL != pSensorData)
		{
			// ����첨������β��
			m_olsSensor.AddTail(pSensorData);
		}
	}
	// ������Ӧ�ü첨������
	m_iSensorCount = m_olsSensor.GetCount();
}

/**
* ���������ţ��õ��첨��
* @param int iIndex ����˳��������
* @return CSensorData* �첨��ָ�� NULL��û�м첨��
*/
CSensorData* CPointCodeData::GetSensorData(int iIndex)
{
	CSensorData* pSensorData = NULL;
	POSITION pos;

	pos = m_olsSensor.FindIndex(iIndex);
	if(NULL != pos)
	{
		pSensorData = m_olsSensor.GetAt(pos);
	}
	return pSensorData;
}