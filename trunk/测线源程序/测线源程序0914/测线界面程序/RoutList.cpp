#include "stdafx.h"
#include "RoutList.h"

CRoutList::CRoutList(void)
{
}

CRoutList::~CRoutList(void)
{
}

// ��ʼ��
void CRoutList::OnInit()
{
	m_uiCountAll = 2048;	// ·������
	m_uiCountUsed = 0;	// ʹ��·������	
	m_pArrayRout = new CRout[m_uiCountAll];	// ����·������
}
// �ر�
void CRoutList::OnClose()
{
	// ɾ��·������
	delete[] m_pArrayRout;
}

// ����
void CRoutList::OnReset()
{
	m_uiCountUsed = 0;	// ʹ��·������	
	m_oRoutMap.RemoveAll();	// ·��������
}

// �����ֳ�·�����ݶ���
void CRoutList::LoadSiteData()
{
	CString strFileName = "..\\data\\FileRout.dat";
	CFile oFile;
	BOOL bData;
	bData = oFile.Open(strFileName, CFile::modeRead | CFile::typeBinary);
	ULONGLONG iByteCount = oFile.GetLength();
	unsigned int iRoutSize = sizeof(CRout);
	if(iByteCount != iRoutSize * m_uiCountAll)
	{
		// ����SOS******
		oFile.Close();
		return;
	}
	iByteCount = oFile.Read(m_pArrayRout, iRoutSize * m_uiCountAll);
	oFile.Close();

	m_uiCountUsed = 0;	// ʹ����·������
	CRout* pRout;
	for(unsigned int i = 0; i < m_uiCountAll; i++)
	{
		pRout = &m_pArrayRout[i];
		if(true == pRout->m_bInUsed)
		{
			m_oRoutMap.SetAt(pRout->m_uiRoutIP, pRout);	// ����·�ɵ�ַ������
			m_uiCountUsed++;	// ʹ����·������
		}
	}	
}