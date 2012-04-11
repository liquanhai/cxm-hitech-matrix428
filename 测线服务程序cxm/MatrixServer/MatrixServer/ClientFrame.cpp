#include "StdAfx.h"
#include "ClientFrame.h"


CClientFrame::CClientFrame(void)
{
}


CClientFrame::~CClientFrame(void)
{
}

// ���ý���֡�ṹ��
void CClientFrame::OnResetRecFrameStruct(m_oCommFrameStructPtr pFrameStruct)
{
	memset(pFrameStruct, 0, sizeof(m_oCommFrameStruct));
}
// ��ʼ��
void CClientFrame::OnInit(void)
{
	m_uiCountFree = FrameStructNumMax;
	m_olsCommFrameFree.clear();
	InitializeCriticalSection(&m_oSecClientFrame);
	EnterCriticalSection(&m_oSecClientFrame);
	m_olsCommWorkFrame.clear();
	LeaveCriticalSection(&m_oSecClientFrame);
	for(unsigned int i = 0; i < FrameStructNumMax; i++)
	{
		// ���ý���֡�ṹ��
		OnResetRecFrameStruct(&m_oCommFrameArray[i]);
		// �������ڿ��н���֡�ṹ�����β��
		m_olsCommFrameFree.push_back(&m_oCommFrameArray[i]);
	}
}

// �õ�һ�����н���֡�ṹ��
m_oCommFrameStructPtr CClientFrame::GetFreeRecFrameStruct(void)
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
void CClientFrame::AddFreeRecFrameStruct(m_oCommFrameStructPtr pFrameStruct)
{
	//��ʼ������֡�ṹ��
	OnResetRecFrameStruct(pFrameStruct);
	//������ж���
	m_olsCommFrameFree.push_back(pFrameStruct);
	m_uiCountFree++;	// ���н���֡�ṹ��������1
}
// �ر�
void CClientFrame::OnClose(void)
{
	m_olsCommFrameFree.clear();
	EnterCriticalSection(&m_oSecClientFrame);
	m_olsCommWorkFrame.clear();
	LeaveCriticalSection(&m_oSecClientFrame);
}
