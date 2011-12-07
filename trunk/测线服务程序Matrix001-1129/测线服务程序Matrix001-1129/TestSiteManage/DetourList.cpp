#include "StdAfx.h"
#include "DetourList.h"

CDetourList::CDetourList()
{
}

CDetourList::~CDetourList()
{
}

/**
* ��ʼ��
* @param void
* @return void
*/
void CDetourList::OnInit()
{
	// ���������ļ�
	ParseXML();
}

/**
* ���¼���
* @param void
* @return void
*/
void CDetourList::OnReload()
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
void CDetourList::OnClose()
{
	// �жϣ��ػص���������0
	if(m_uiCountAll > 0)
	{
		// �ػص�ָ��
		CDetourData* pDetour = NULL;
		while(FALSE == m_olsDetour.IsEmpty())
		{
			// �Ƴ�����
			pDetour = m_olsDetour.RemoveHead();
			// ɾ���ػص�
			delete pDetour;
		}
	}
	m_uiCountAll = 0;	// ����
}

/**
* ���������ļ�
* @param void
* @return void
*/
void CDetourList::ParseXML()
{
	CString strKey;
	CXMLDOMNodeList oNodeList;
	CXMLDOMElement oElement;
	LPDISPATCH lpDispatch;

	// �ҵ��ػص�������
	strKey = "DetourSetup";
	lpDispatch = m_pXMLDOMDocument->getElementsByTagName(strKey);
	oNodeList.AttachDispatch(lpDispatch);
	// �ҵ����
	lpDispatch = oNodeList.get_item(0);
	oElement.AttachDispatch(lpDispatch);
	// �õ��ػص�����
	strKey = "Count";
	m_uiCountAll = CXMLDOMTool::GetElementAttributeInt(&oElement, strKey);
	// �õ�����
	lpDispatch = oElement.get_childNodes();
	oNodeList.AttachDispatch(lpDispatch);

	CDetourData* pDetour = NULL;
	for(unsigned int i = 0; i < m_uiCountAll; i++)
	{
		lpDispatch = oNodeList.get_item(i);
		oElement.AttachDispatch(lpDispatch);

		pDetour = new CDetourData;
		pDetour->ParseXML(&oElement);

		// �����ػص�
		m_olsDetour.AddTail(pDetour);
	}
}

/**
* ����˳�������ţ��õ��ػص�
* @param unsigned int uiIndex �ػص�������
* @return CDetourData* �ػص�ָ�� NULL:��ָ��
*/
CDetourData* CDetourList::GetDetour(unsigned int uiIndex)
{
	CDetourData* pDetour = NULL;
	POSITION pos = m_olsDetour.FindIndex(uiIndex);
	if(NULL != pos)
	{
		pDetour = m_olsDetour.GetAt(pos);
	}	
	return pDetour;
}