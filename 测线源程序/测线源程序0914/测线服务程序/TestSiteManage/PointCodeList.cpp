#include "StdAfx.h"
#include "PointCodeList.h"

CPointCodeList::CPointCodeList()
{
}

CPointCodeList::~CPointCodeList()
{
}

/**
* ��ʼ��
* @param void
* @return void
*/
void CPointCodeList::OnInit()
{
	// ���������ļ�
	ParseXML();
}

/**
* ���¼���
* @param void
* @return void
*/
void CPointCodeList::OnReload()
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
void CPointCodeList::OnClose()
{
	// �������������0
	if(m_uiCountAll > 0)
	{
		// �����ָ��
		CPointCodeData* pPointCode;
		while(FALSE == m_olsPointCode.IsEmpty())
		{
			// �Ƴ�����
			pPointCode = m_olsPointCode.RemoveHead();
			// ɾ�������
			delete pPointCode;
		}
		// ��յ����������
		m_oPointCodeMap.RemoveAll();
	}
	m_uiCountAll = 0;
}

/**
* ���������ļ�
* @param void
* @return void
*/
void CPointCodeList::ParseXML()
{
	CString strKey;
	CXMLDOMNodeList oNodeList;
	CXMLDOMElement oElement;
	LPDISPATCH lpDispatch;

	// �ҵ������������
	strKey = "PointCodeSetup";
	lpDispatch = m_pXMLDOMDocument->getElementsByTagName(strKey);
	oNodeList.AttachDispatch(lpDispatch);
	// �ҵ����
	lpDispatch = oNodeList.get_item(0);
	oElement.AttachDispatch(lpDispatch);
	// �õ����������
	strKey = "Count";
	m_uiCountAll = CXMLDOMTool::GetElementAttributeInt(&oElement, strKey);
	// �õ�����
	lpDispatch = oElement.get_childNodes();
	oNodeList.AttachDispatch(lpDispatch);

	CPointCodeData* pPointCode = NULL;

	for(unsigned int i = 0; i < m_uiCountAll; i++)
	{
		lpDispatch = oNodeList.get_item(i);
		oElement.AttachDispatch(lpDispatch);

		pPointCode = new CPointCodeData;
		pPointCode->ParseXML(&oElement);
		pPointCode->ParseSensorType(m_pSensorList);

		// ���ӵ����
		m_olsPointCode.AddTail(pPointCode);
		// ��������������
		m_oPointCodeMap.SetAt(pPointCode->m_uiNb, pPointCode);
	}
}

/**
* ���ݱ�ʶ�ţ��õ��첨��
* @param unsigned int uiNb ��ʶ��
* @return CSensorData* �첨��ָ�� NULL��û�м첨��
*/
CPointCodeData* CPointCodeList::GetPointCode(unsigned int uiNb)
{
	CPointCodeData* pPointCode = NULL;
	// ���ҵ����������
	if(TRUE == m_oPointCodeMap.Lookup(uiNb, pPointCode))
	{
		return pPointCode;
	}
	return NULL;
}