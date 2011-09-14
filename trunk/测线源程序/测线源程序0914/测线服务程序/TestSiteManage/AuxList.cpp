#include "StdAfx.h"
#include "AuxList.h"

CAuxList::CAuxList()
{
}

CAuxList::~CAuxList()
{
}

/**
* ��ʼ��
* @param void
* @return void
*/
void CAuxList::OnInit()
{
	// ���������ļ�
	ParseXML();
}

/**
* ���¼���
* @param void
* @return void
*/
void CAuxList::OnReload()
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
void CAuxList::OnClose()
{
	// �жϣ���������������0
	if(m_uiCountAll > 0)
	{
		// ������ָ��
		CAuxData* pAux = NULL;
		while(FALSE == m_olsAux.IsEmpty())
		{
			// �Ƴ�����
			pAux = m_olsAux.RemoveHead();
			// ɾ��������
			delete pAux;
		}
	}
	m_uiCountAll = 0;
}

/**
* ���������ļ�
* @param void
* @return void
*/
void CAuxList::ParseXML()
{
	CString strKey;
	CXMLDOMNodeList oNodeList;
	CXMLDOMElement oElement;
	LPDISPATCH lpDispatch;

	// �ҵ�������������
	strKey = "AuxSetup";
	lpDispatch = m_pXMLDOMDocument->getElementsByTagName(strKey);
	oNodeList.AttachDispatch(lpDispatch);
	// �ҵ����
	lpDispatch = oNodeList.get_item(0);
	oElement.AttachDispatch(lpDispatch);
	// �õ�����������
	strKey = "Count";
	m_uiCountAll = CXMLDOMTool::GetElementAttributeInt(&oElement, strKey);
	// �õ�����
	lpDispatch = oElement.get_childNodes();
	oNodeList.AttachDispatch(lpDispatch);

	CAuxData* pAux = NULL;
	for(unsigned int i = 0; i < m_uiCountAll; i++)
	{
		lpDispatch = oNodeList.get_item(i);
		oElement.AttachDispatch(lpDispatch);
		pAux = new CAuxData;
		pAux->ParseXML(&oElement);
		// ���Ӹ�����
		m_olsAux.AddTail(pAux);
	}
}

/**
* ����˳�������ţ��õ�������
* @param unsigned int uiIndex ������������
* @return CAuxData* ������ָ�� NULL:��ָ��
*/
CAuxData* CAuxList::GetAux(unsigned int uiIndex)
{
	CAuxData* pAux = NULL;
	POSITION pos = m_olsAux.FindIndex(uiIndex);
	if(NULL != pos)
	{
		pAux = m_olsAux.GetAt(pos);
	}	
	return pAux;
}

/**
* ���ݱ�ʶ�ţ��õ�������
* @param unsigned int uiNb ��������ʶ��
* @return CAuxData* ������ָ�� NULL:��ָ��
*/
CAuxData* CAuxList::GetAuxByNb(unsigned int uiNb)
{
	int iCount = m_olsAux.GetCount();
	POSITION pos = NULL;
	CAuxData* pAux = NULL;
	for(int i = 0; i < iCount; i++)
	{
		pos = m_olsAux.FindIndex(i);
		pAux = m_olsAux.GetAt(pos);
		if(pAux->m_uiNb == uiNb)
		{
			return pAux;
		}
	}
	return NULL;
}