#include "StdAfx.h"
#include "ClientCommFrame.h"


CClientCommFrame::CClientCommFrame(void)
{
	m_uiPacketIndex = 0;
	m_uiCmdIndex = 0;
}


CClientCommFrame::~CClientCommFrame(void)
{
}

// ���ý���֡�ṹ��
void CClientCommFrame::OnResetFrameStruct(m_oCommFrameStructPtr pFrameStruct)
{
	memset(pFrameStruct, 0, sizeof(m_oCommFrameStruct));
}
// ��ʼ��
void CClientCommFrame::OnInit(void)
{
	m_uiCountFree = FrameStructNumMax;
	m_olsCommFrameFree.clear();
	InitializeCriticalSection(&m_oSecClientFrame);
	m_olsCommWorkFrame.clear();
	m_oSndFrameMap.clear();
	for(unsigned int i = 0; i < FrameStructNumMax; i++)
	{
		// ���ý���֡�ṹ��
		OnResetFrameStruct(&m_oCommFrameArray[i]);
		// �������ڿ��н���֡�ṹ�����β��
		m_olsCommFrameFree.push_back(&m_oCommFrameArray[i]);
	}
}

// �õ�һ�����н���֡�ṹ��
m_oCommFrameStructPtr CClientCommFrame::GetFreeFrameStruct(void)
{
	m_oCommFrameStructPtr pFrameStruct = NULL;
	list <m_oCommFrameStructPtr>::iterator iter;
	if(m_uiCountFree > 0)	//�п��н���֡�ṹ��
	{
		// �ӿ��ж����еõ�һ������֡�ṹ��
		iter = m_olsCommFrameFree.begin();
		pFrameStruct = *iter;
		m_olsCommFrameFree.pop_front();	
		m_uiCountFree--;	// ���н���֡�ṹ��������1
	}
	else
	{
		// д�������־
	}
	return pFrameStruct;
}
// ����һ�����н���֡�ṹ��
void CClientCommFrame::AddFreeFrameStruct(m_oCommFrameStructPtr pFrameStruct)
{
	//��ʼ������֡�ṹ��
	OnResetFrameStruct(pFrameStruct);
	//������ж���
	m_olsCommFrameFree.push_back(pFrameStruct);
	m_uiCountFree++;	// ���н���֡�ṹ��������1
}
// �ر�
void CClientCommFrame::OnClose(void)
{
	m_olsCommFrameFree.clear();
	m_olsCommWorkFrame.clear();
	m_oSndFrameMap.clear();
	DeleteCriticalSection(&m_oSecClientFrame);
}

// �ж��������Ƿ��Ѽ���������
BOOL CClientCommFrame::IfFramePtrExistInSndMap(unsigned short m_usCmd, unsigned int m_uiServerTimeStep, 
	unsigned int m_uiPacketIndex, map<m_oSndFrameKey, m_oCommFrameStructPtr>* pMap)
{
	if (pMap == NULL)
	{
		return FALSE;
	}
	BOOL bResult = FALSE;
	m_oSndFrameKey Key(m_usCmd, m_uiServerTimeStep, m_uiPacketIndex);
	map<m_oSndFrameKey, m_oCommFrameStructPtr>::iterator iter;
	iter = pMap->find(Key);
	if (iter != pMap->end())
	{
		bResult = TRUE;
	}
	else
	{
		bResult = FALSE;
	}
	return bResult;
}
// ���Ӷ���������
void CClientCommFrame::AddFramePtrToSndMap(unsigned short m_usCmd, unsigned int m_uiServerTimeStep, 
	unsigned int m_uiPacketIndex, m_oCommFrameStructPtr pFrameStruct, 
	map<m_oSndFrameKey, m_oCommFrameStructPtr>* pMap)
{
	if ((pFrameStruct == NULL) || (pMap == NULL))
	{
		return;
	}
	m_oSndFrameKey Key(m_usCmd, m_uiServerTimeStep, m_uiPacketIndex);
	if (false == IfFramePtrExistInSndMap(m_usCmd, m_uiServerTimeStep, m_uiPacketIndex, pMap))
	{
		pMap->insert(map<m_oSndFrameKey, m_oCommFrameStructPtr>::value_type (Key, pFrameStruct));
	}
}
// �������������ţ���������õ�ָ��
m_oCommFrameStructPtr CClientCommFrame::GetFramePtrFromSndMap(unsigned short m_usCmd, unsigned int m_uiServerTimeStep, 
	unsigned int m_uiPacketIndex, map<m_oSndFrameKey, m_oCommFrameStructPtr>* pMap)
{
	if (pMap == NULL)
	{
		return NULL;
	}
	m_oSndFrameKey Key(m_usCmd, m_uiServerTimeStep, m_uiPacketIndex);
	map<m_oSndFrameKey, m_oCommFrameStructPtr>::iterator iter;
	iter = pMap->find(Key);
	if (iter == pMap->end())
	{
		return NULL;
	}
	return iter->second;
}
// ��������ɾ��������ָ�������ָ��
BOOL CClientCommFrame::DeleteFramePtrFromSndMap(unsigned short m_usCmd, unsigned int m_uiServerTimeStep, 
	unsigned int m_uiPacketIndex, map<m_oSndFrameKey, m_oCommFrameStructPtr>* pMap)
{
	if (pMap == NULL)
	{
		return FALSE;
	}
	BOOL bResult = FALSE;
	m_oSndFrameKey Key(m_usCmd, m_uiServerTimeStep, m_uiPacketIndex);
	map<m_oSndFrameKey, m_oCommFrameStructPtr>::iterator iter;
	iter = pMap->find(Key);
	if (iter != pMap->end())
	{
		pMap->erase(iter);
		bResult = TRUE;
	}
	else
	{
		bResult = FALSE;
	}
	return bResult;
}