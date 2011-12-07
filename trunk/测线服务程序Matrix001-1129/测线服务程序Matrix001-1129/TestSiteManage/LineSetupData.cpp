#include "StdAfx.h"
#include "LineSetupData.h"

CLineSetupData::CLineSetupData()
{
}

CLineSetupData::~CLineSetupData()
{
}

/**
* ����
* @param void
* @return void
*/
void CLineSetupData::OnReset()
{
	// �����Ƿ�ʹ����
	m_bInUsed = false;

	// ���ߺ�
	m_uiNbLine = 0;

	// �������ӵĲ���
	m_pLinelTop = NULL;
	// �������ӵĲ���
	m_pLinelDown = NULL;

	// �������
	m_uiPointCount = 0;
	// ���ͷָ��
	m_pPointHead = NULL;
	// ���βָ��
	m_pPointTail = NULL;

	// �������
	m_uiChannelCount = 0;
	// ���ͷָ��
	m_pChannelHead = NULL;
	// ���βָ��
	m_pChannelTail = NULL;

	// �����ϵĲ�㶨��
	m_strReceiverSection = "";
}

/**
* ����XML
* @param CXMLDOMElement* pElement XML�ĵ��ڵ�ָ��
* @return void
*/
void CLineSetupData::ParseXML(CXMLDOMElement* pElement)
{
	CString strKey;	// ����	
	// �õ����ߺ�
	strKey = "LineName";
	m_uiNbLine = CXMLDOMTool::GetElementAttributeInt(pElement, strKey);
	// �õ����ߵĲ�㶨��
	strKey = "ReceiverSection";
	m_strReceiverSection = CXMLDOMTool::GetElementAttributeString(pElement, strKey);
}

/**
* �������ӷ��򣬵õ����������һ���Ĳ��
* @param CPointSetupData* pPointSetupData ���
* @param unsigned int uiDirection ���ӷ��� 3����4����
* @return CPointSetupData* ���������һ���Ĳ�� NULL�����������һ���Ĳ�㲻����
*/
CPointSetupData* CLineSetupData::GetPointByDirection(CPointSetupData* pPointSetupData, unsigned int uiDirection)
{
	// �жϷ���
	switch(uiDirection)
	{
	case 3:	// ��
		{
			return GetPointLeft(pPointSetupData);
			break;
		}
	case 4:	// ��
		{
			return GetPointRight(pPointSetupData);
			break;
		}
	}
	return NULL;
}

/**
* �õ����������ӵĲ��
* @param CPointSetupData* pPointSetupData ���
* @return CPointSetupData* ���������һ���Ĳ�� NULL�����������һ���Ĳ�㲻����
*/
CPointSetupData* CLineSetupData::GetPointLeft(CPointSetupData* pPointSetupData)
{
	// ���Ϊ��
	if(NULL == pPointSetupData)
	{
		return NULL;
	}
	// ���Ϊ���Ĳ��ͷ
	if(m_pPointHead == pPointSetupData)
	{
		return NULL;
	}
	// �õ����������ӵĲ��
	return pPointSetupData->m_pPointLeft;
}

/**
* �õ�����ұ����ӵĲ��
* @param CPointSetupData* pPointSetupData ���
* @return CPointSetupData* ���������һ���Ĳ�� NULL�����������һ���Ĳ�㲻����
*/
CPointSetupData* CLineSetupData::GetPointRight(CPointSetupData* pPointSetupData)
{
	CPointSetupData* pPointSetupDataRight = NULL;
	// ���Ϊ��
	if(NULL == pPointSetupData)
	{
		return NULL;
	}
	// ���Ϊ���Ĳ��β
	if(m_pPointTail == pPointSetupData)
	{
		return NULL;
	}
	// �õ�����ұ����ӵĲ��
	return pPointSetupData->m_pPointRight;
}