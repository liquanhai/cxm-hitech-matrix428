#include "StdAfx.h"
#include "MarkerList.h"

CMarkerList::CMarkerList()
{
}

CMarkerList::~CMarkerList()
{
}

/**
* ��ʼ��
* @param void
* @return void
*/
void CMarkerList::OnInit()
{
	// ���������ļ�
	ParseXML();
}

/**
* ���¼���
* @param void
* @return void
*/
void CMarkerList::OnReload()
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
void CMarkerList::OnClose()
{
	// ��ǵ���������0
	if(m_uiCountAll > 0)
	{
		// ��ǵ�ָ��
		CMarkerData* pMarker;
		while(FALSE == m_olsMarker.IsEmpty())
		{
			// �Ƴ�����
			pMarker = m_olsMarker.RemoveHead();
			// ɾ����ǵ�
			delete pMarker;
		}
	}
	m_uiCountAll = 0;
}

/**
* ���������ļ�
* @param void
* @return void
*/
void CMarkerList::ParseXML()
{
	CString strKey;
	CXMLDOMNodeList oNodeList;
	CXMLDOMElement oElement;
	LPDISPATCH lpDispatch;

	// �ҵ���ǵ�������
	strKey = "MarkerSetup";
	lpDispatch = m_pXMLDOMDocument->getElementsByTagName(strKey);
	oNodeList.AttachDispatch(lpDispatch);
	// �ҵ����
	lpDispatch = oNodeList.get_item(0);
	oElement.AttachDispatch(lpDispatch);
	// �õ���ǵ�����
	strKey = "Count";
	m_uiCountAll = CXMLDOMTool::GetElementAttributeInt(&oElement, strKey);
	// �õ�����
	lpDispatch = oElement.get_childNodes();
	oNodeList.AttachDispatch(lpDispatch);

	CMarkerData* pMarker = NULL;
	for(unsigned int i = 0; i < m_uiCountAll; i++)
	{
		lpDispatch = oNodeList.get_item(i);
		oElement.AttachDispatch(lpDispatch);
		pMarker = new CMarkerData;
		pMarker->ParseXML(&oElement);
		// ���ӱ�ǵ�
		m_olsMarker.AddTail(pMarker);
	}
}

/**
* ����˳�������ţ��õ���ǵ�
* @param unsigned int uiIndex ��ǵ�������
* @return CMarkerData* ��ǵ�ָ�� NULL:��ָ��
*/
CMarkerData* CMarkerList::GetMarker(unsigned int uiIndex)
{
	POSITION pos = m_olsMarker.FindIndex(uiIndex);
	CMarkerData* pMarker = m_olsMarker.GetAt(pos);
	return pMarker;
}