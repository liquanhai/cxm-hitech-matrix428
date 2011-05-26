#include "StdAfx.h"
#include "ChannelList.h"

CChannelList::CChannelList(void)
{
}

CChannelList::~CChannelList(void)
{
}

// ��ʼ��
void CChannelList::OnInit()
{
	// ���ɲ������
	m_pArrayChannel = new CChannelSetupData[m_uiCountAll];
	// ʹ���в������
	m_uiCountUsed = 0;
	// ���в������
	m_uiCountFree = m_uiCountAll;

	m_uiNbPointMin = 100000;	// ��С����
	m_uiNbPointMax = 0;	// ������
	m_uiPointChannelCountMax = 0;	// ��������������
	m_uiNbLineCount = 0;	// ��������
	m_olsNbLine.RemoveAll();	// ���ߺŶ���
}

// �ر�
void CChannelList::OnClose()
{
	// ɾ���������
	delete[] m_pArrayChannel;
	// ���������
	m_oChannelMap.RemoveAll();
}

// ����
void CChannelList::OnReset()
{
	// ʹ���в�������
	m_uiCountUsed = 0;
	// ���в������
	m_uiCountFree = m_uiCountAll;
	// ���������
	m_oChannelMap.RemoveAll();

	m_uiNbPointMin = 100000;	// ��С����
	m_uiNbPointMax = 0;	// ������
	m_uiPointChannelCountMax = 0;	// ��������������
	m_uiNbLineCount = 0;	// ��������
	m_olsNbLine.RemoveAll();	// ���ߺŶ���
	m_oNbLineMap.RemoveAll();	// ���ߺ�������
}

// ����һ�������������
void CChannelList::AddChannelToMap(unsigned int uiIndex, CChannelSetupData* pChannel)
{
	m_oChannelMap.SetAt(uiIndex, pChannel);
}

// ����������Ƿ��Ѽ���������
BOOL CChannelList::IfIndexExistInMap(unsigned int uiIndex)
{
	CChannelSetupData* pChannel = NULL;
	return m_oChannelMap.Lookup(uiIndex, pChannel);
}

// ��������õ�һ�����
BOOL CChannelList::GetChannelFromMap(unsigned int uiIndex, CChannelSetupData* &pChannel)
{
	return m_oChannelMap.Lookup(uiIndex, pChannel);
}

// �õ�һ�����
CChannelSetupData* CChannelList::GetChannelByIndex(unsigned int uiIndex)
{
	return &m_pArrayChannel[uiIndex];
}

// �õ����
CChannelSetupData* CChannelList::GetChannel(unsigned int uiNbLine, unsigned int uiNbPoint, unsigned int uiNbChannel)
{
	CChannelSetupData* pChannel = NULL;
	unsigned int uiIP = CChannelSetupData::CreateIP(uiNbLine, uiNbPoint, uiNbChannel);
	if(TRUE == GetChannelFromMap(uiIP, pChannel))
	{
		return pChannel;
	}
	return NULL;
}

// �����ֳ�������ݶ���
void CChannelList::LoadSiteData()
{
	CString strFileName = "FileChannel.dat";
	CFile oFile;
	BOOL bData;
	bData = oFile.Open(strFileName, CFile::modeRead | CFile::typeBinary);
	ULONGLONG iByteCount = oFile.GetLength();
	unsigned int iChannelSize = sizeof(CChannelSetupData);
	if(iByteCount != iChannelSize * m_uiCountAll)
	{
		// ����SOS******
		oFile.Close();
		return;
	}
	iByteCount = oFile.Read(m_pArrayChannel, iChannelSize * m_uiCountAll);
	oFile.Close();

	m_uiCountUsed = 0;	// ʹ���в������
	m_uiNbLineCount = 0;	// ��������
	unsigned int uiNbLinePreview = 0;	//��һ�����ߺ�
	CChannelSetupData* pChannelSetupData;
	for(unsigned int i = 0; i < m_uiCountAll; i++)
	{
		pChannelSetupData = &m_pArrayChannel[i];
		if(true == pChannelSetupData->m_bInUsed)
		{
			if(pChannelSetupData->m_uiNbPoint < m_uiNbPointMin)
			{
				m_uiNbPointMin = pChannelSetupData->m_uiNbPoint;	// ��С����
			}
			if(pChannelSetupData->m_uiNbPoint > m_uiNbPointMax)
			{
				m_uiNbPointMax = pChannelSetupData->m_uiNbPoint;	// ������
			}
			if(pChannelSetupData->m_uiNbChannel > m_uiPointChannelCountMax)
			{
				m_uiPointChannelCountMax = pChannelSetupData->m_uiNbChannel;	// ��������������
			}
			if(uiNbLinePreview != pChannelSetupData->m_uiNbLine)
			{			
				m_olsNbLine.AddTail(pChannelSetupData->m_uiNbLine);		// ���ߺŶ���
				m_oNbLineMap.SetAt(pChannelSetupData->m_uiNbLine, m_uiNbLineCount);	// ���ߺ�������
				m_uiNbLineCount++;	// ��������
				uiNbLinePreview = pChannelSetupData->m_uiNbLine;				
			}

			m_oChannelMap.SetAt(pChannelSetupData->m_uiIP, pChannelSetupData);	// ����������
			m_uiCountUsed++;	// ʹ���в������
		}
		else
		{
			break;
		}
	}	
	m_uiCountFree = m_uiCountAll - m_uiCountUsed;	// ���в������
}