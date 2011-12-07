#include "StdAfx.h"
#include "MuteList.h"

CMuteList::CMuteList()
{
}

CMuteList::~CMuteList()
{
}

/**
* ��ʼ��
* @param void
* @return void
*/
void CMuteList::OnInit()
{
	// ���������ļ�
	ParseXML();
}

/**
* ���¼���
* @param void
* @return void
*/
void CMuteList::OnReload()
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
void CMuteList::OnClose()
{
	// �Ƶ���������0
	if(m_uiCountAll > 0)
	{
		// �Ƶ�ָ��
		CMuteData* pMute;
		while(FALSE == m_olsMute.IsEmpty())
		{
			// �Ƴ�����
			pMute = m_olsMute.RemoveHead();
			// ɾ���Ƶ�
			delete pMute;
		}
	}
	m_uiCountAll = 0;
}

/**
* ���������ļ�
* @param void
* @return void
*/
void CMuteList::ParseXML()
{
	CString strKey;
	CXMLDOMNodeList oNodeList;
	CXMLDOMElement oElement;
	LPDISPATCH lpDispatch;

	// �ҵ��Ƶ�������
	strKey = "MuteSetup";
	lpDispatch = m_pXMLDOMDocument->getElementsByTagName(strKey);
	oNodeList.AttachDispatch(lpDispatch);
	// �ҵ����
	lpDispatch = oNodeList.get_item(0);
	oElement.AttachDispatch(lpDispatch);
	// �õ��Ƶ�����
	strKey = "Count";
	m_uiCountAll = CXMLDOMTool::GetElementAttributeInt(&oElement, strKey);
	// �õ�����
	lpDispatch = oElement.get_childNodes();
	oNodeList.AttachDispatch(lpDispatch);

	CMuteData* pMute = NULL;

	for(unsigned int i = 0; i < m_uiCountAll; i++)
	{
		lpDispatch = oNodeList.get_item(i);
		oElement.AttachDispatch(lpDispatch);

		pMute = new CMuteData;
		pMute->ParseXML(&oElement);

		// �����Ƶ�
		m_olsMute.AddTail(pMute);
	}
}

/**
* ����˳�������ţ��õ��Ƶ�
* @param unsigned int uiIndex �Ƶ�������
* @return CMuteData* �Ƶ�ָ�� NULL:��ָ��
*/
CMuteData* CMuteList::GetMute(unsigned int uiIndex)
{
	POSITION pos = m_olsMute.FindIndex(uiIndex);
	CMuteData* pMute = m_olsMute.GetAt(pos);
	return pMute;
}
