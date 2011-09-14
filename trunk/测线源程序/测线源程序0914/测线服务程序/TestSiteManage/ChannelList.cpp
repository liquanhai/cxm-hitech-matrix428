#include "StdAfx.h"
#include "ChannelList.h"

CChannelList::CChannelList()
{
}

CChannelList::~CChannelList()
{
}

/**
* ��ʼ��
* @param void
* @return void
*/
void CChannelList::OnInit()
{
	// ���ɲ������
	m_pArrayChannel = new CChannelSetupData[m_uiCountAll];
	// ���ɲ�����飬Ϊ�ֳ��������׼��
	m_pArrayChannelOutput = new CChannelSetupData[m_uiCountAll];
	// ʹ���в������
	m_uiCountUsed = 0;
	// ���в������
	m_uiCountFree = m_uiCountAll;
	for(unsigned int i = 0; i < m_uiCountAll; i++)
	{
		// ����ڲ�������е�λ��
		m_pArrayChannel[i].m_uiIndex = i;
		// ���¼��ز��
		m_pArrayChannel[i].OnReload();
	}
}

/**
* ����
* @param void
* @return void
*/
void CChannelList::OnReset()
{
	for(unsigned int i = 0; i < m_uiCountAll; i++)
	{
		// ���ò��
		m_pArrayChannel[i].OnReset();
	}
}

/**
* ���¼���
* @param void
* @return void
*/
void CChannelList::OnReload()
{
	// ʹ���в�������
	m_uiCountUsed = 0;
	// ���в������
	m_uiCountFree = m_uiCountAll;
	for(unsigned int i = 0; i < m_uiCountAll; i++)
	{
		// ���ò��
		m_pArrayChannel[i].OnReload();
	}
	// ���������
	m_oChannelMap.RemoveAll();
}

/**
* �ر�
* @param void
* @return void
*/
void CChannelList::OnClose()
{
	// ɾ���������
	delete[] m_pArrayChannel;
	// ɾ��������飬Ϊ�ֳ��������׼��
	delete[] m_pArrayChannelOutput;
	// ���������
	m_oChannelMap.RemoveAll();
}

/**
* �õ�һ�����в��
* @param void
* @return CChannelSetupData* ���в�� NULL��û�п��в��
*/
CChannelSetupData* CChannelList::GetFreeChannel()
{
	CChannelSetupData* pChannel = NULL;

	//�жϣ��п��в��
	if(m_uiCountFree > 0)
	{
		pChannel = &m_pArrayChannel[m_uiCountUsed];
		pChannel->m_bInUsed = true;	// ���ò��Ϊʹ����
		m_uiCountFree--;	// ���в��������1
		m_uiCountUsed++;	// ʹ���в��������1
	}
	return pChannel;
}

/**
* ���������������
* @param unsigned int uiIndex ������
* @param CChannelSetupData* pChannel ���ָ��
* @return void
*/
void CChannelList::AddChannelToMap(unsigned int uiIndex, CChannelSetupData* pChannel)
{
	m_oChannelMap.SetAt(uiIndex, pChannel);
}

/**
* ����������Ƿ��Ѽ���������
* @param unsigned int uiIndex ������
* @return BOOL TRUE���ǣ�FALSE����
*/
BOOL CChannelList::IfIndexExistInMap(unsigned int uiIndex)
{
	CChannelSetupData* pChannel = NULL;
	return m_oChannelMap.Lookup(uiIndex, pChannel);
}

/**
* ��������õ�һ�����
* @param unsigned int uiIndex ������
* @param CChannelSetupData* pChannel ���ָ�룬���õ���
* @return BOOL TRUE���ɹ���FALSE��ʧ��
*/
BOOL CChannelList::GetChannelFromMap(unsigned int uiIndex, CChannelSetupData* &pChannel)
{
	return m_oChannelMap.Lookup(uiIndex, pChannel);
}

/**
* ���������������ڲ�������еõ�һ�����
* @param unsigned int uiIndex ����������
* @return CChannelSetupData* ���
*/
CChannelSetupData* CChannelList::GetChannelByIndex(unsigned int uiIndex)
{
	return &m_pArrayChannel[uiIndex];
}

/**
* ���ݲ��ߺš����š�����ţ����������еõ����
* @param unsigned int uiNbLine ���ߺ�
* @param unsigned int uiNbPoint ����
* @param unsigned int uiNbChannel �����
* @return CChannelSetupData* ��� NULL��û�в��
*/
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

/**
* ���Ʋ�����鵽�������
* @param void
* @return void
*/
void CChannelList::CopyChannelArrayForOutput()
{
	memcpy(m_pArrayChannelOutput, m_pArrayChannel, sizeof(CChannelSetupData) * m_uiCountAll);
}