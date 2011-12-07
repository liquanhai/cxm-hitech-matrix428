#include "StdAfx.h"
#include "BlastMachineList.h"

CBlastMachineList::CBlastMachineList()
{
}

CBlastMachineList::~CBlastMachineList()
{
}

/**
* ��ʼ��
* @param void
* @return void
*/
void CBlastMachineList::OnInit()
{
	// ���������ļ�
	ParseXML();
}

/**
* ���¼���
* @param void
* @return void
*/
void CBlastMachineList::OnReload()
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
void CBlastMachineList::OnClose()
{
	// ��ը����������������0
	if(m_uiCountAll > 0)
	{
		// ��ը��������ָ��
		CBlastMachineData* pBlastMachine = NULL;
		while(FALSE == m_olsBlastMachine.IsEmpty())
		{
			// �Ƴ�����
			pBlastMachine = m_olsBlastMachine.RemoveHead();
			// ɾ����ը��������
			delete pBlastMachine;
		}
	}
	m_uiCountAll = 0;
}

/**
* ���������ļ�
* @param void
* @return void
*/
void CBlastMachineList::ParseXML()
{
	CString strKey;
	CXMLDOMNodeList oNodeList;
	CXMLDOMElement oElement;
	LPDISPATCH lpDispatch;

	// �ҵ���ը��������������
	strKey = "BlastMachineSetup";
	lpDispatch = m_pXMLDOMDocument->getElementsByTagName(strKey);
	oNodeList.AttachDispatch(lpDispatch);
	// �ҵ����
	lpDispatch = oNodeList.get_item(0);
	oElement.AttachDispatch(lpDispatch);
	// �õ���ը������������
	strKey = "Count";
	m_uiCountAll = CXMLDOMTool::GetElementAttributeInt(&oElement, strKey);
	// �õ�����
	lpDispatch = oElement.get_childNodes();
	oNodeList.AttachDispatch(lpDispatch);

	CBlastMachineData* pBlastMachine = NULL;
	for(unsigned int i = 0; i < m_uiCountAll; i++)
	{
		lpDispatch = oNodeList.get_item(i);
		oElement.AttachDispatch(lpDispatch);
		pBlastMachine = new CBlastMachineData;
		pBlastMachine->ParseXML(&oElement);
		// ���ӱ�ը��������
		m_olsBlastMachine.AddTail(pBlastMachine);
	}
}

/**
* ����˳�������ţ��õ���ը��������
* @param unsigned int uiIndex ��ը��������������
* @return CBlastMachineData* ��ը��������ָ�� NULL:��ָ��
*/
CBlastMachineData* CBlastMachineList::GetBlastMachine(unsigned int uiIndex)
{
	CBlastMachineData* pBlastMachine = NULL;
	POSITION pos = m_olsBlastMachine.FindIndex(uiIndex);
	if(NULL != pos)
	{
		pBlastMachine = m_olsBlastMachine.GetAt(pos);
	}	
	return pBlastMachine;
}
