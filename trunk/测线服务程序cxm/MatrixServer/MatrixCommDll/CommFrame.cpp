#include "stdafx.h"
#include "MatrixCommDll.h"

CCommFrame::CCommFrame(void)
{
}

CCommFrame::~CCommFrame(void)
{
}

// ���ý���֡�ṹ��
void CCommFrame::OnResetFrameStruct(m_oCommFrameStructPtr pFrameStruct)
{
	memset(pFrameStruct, 0, sizeof(m_oCommFrameStruct));
}
// ��ʼ��
void CCommFrame::OnInit(void)
{
	InitializeCriticalSection(&m_oSecClientFrame);
	EnterCriticalSection(&m_oSecClientFrame);
	m_uiCountFree = FrameStructNumMax;
	m_uiPacketIndex = 0;
	m_uiCmdIndex = 0;
	m_olsCommFrameFree.clear();
	m_olsCommWorkFrame.clear();
	OnResetProcBuf();
	for(unsigned int i = 0; i < FrameStructNumMax; i++)
	{
		// ���ý���֡�ṹ��
		OnResetFrameStruct(&m_oCommFrameArray[i]);
		// �������ڿ��н���֡�ṹ�����β��
		m_olsCommFrameFree.push_back(&m_oCommFrameArray[i]);
	}
	LeaveCriticalSection(&m_oSecClientFrame);
}

// �õ�һ�����н���֡�ṹ��
m_oCommFrameStructPtr CCommFrame::GetFreeFrameStruct(void)
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
void CCommFrame::AddFreeFrameStruct(m_oCommFrameStructPtr pFrameStruct)
{
	//��ʼ������֡�ṹ��
	OnResetFrameStruct(pFrameStruct);
	//������ж���
	m_olsCommFrameFree.push_back(pFrameStruct);
	m_uiCountFree++;	// ���н���֡�ṹ��������1
}

// �ر�
void CCommFrame::OnClose(void)
{
	m_olsCommFrameFree.clear();
	m_olsCommWorkFrame.clear();
	DeleteCriticalSection(&m_oSecClientFrame);
}

// �������ݴ�������
void CCommFrame::OnResetProcBuf(void)
{
	memset(m_cProcBuf, 0, ProcBufferSize);
}