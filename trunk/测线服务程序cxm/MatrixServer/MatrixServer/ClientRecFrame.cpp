#include "StdAfx.h"
#include "ClientRecFrame.h"


CClientRecFrame::CClientRecFrame(void)
{
}


CClientRecFrame::~CClientRecFrame(void)
{
}
// ���ý���֡�ṹ��
void CClientRecFrame::OnResetRecFrameStruct(m_oCommFrameStructPtr pFrameStruct)
{
	memset(pFrameStruct, 0, sizeof(m_oCommFrameStruct));
}
// ��ʼ��
void CClientRecFrame::OnInit(void)
{
	m_uiCountFree = RecFrameStructNumMax;
	m_olsCommFrameStructFree.clear();
	InitializeCriticalSection(&m_oSecClientRecFrame);
	EnterCriticalSection(&m_oSecClientRecFrame);
	m_olsCommRecFrame.clear();
	LeaveCriticalSection(&m_oSecClientRecFrame);
	for(unsigned int i = 0; i < RecFrameStructNumMax; i++)
	{
		// ���ý���֡�ṹ��
		OnResetRecFrameStruct(&m_oCommFrameArray[i]);
		// �������ڿ��н���֡�ṹ�����β��
		m_olsCommFrameStructFree.push_back(&m_oCommFrameArray[i]);
	}
}

// �õ�һ�����н���֡�ṹ��
m_oCommFrameStructPtr CClientRecFrame::GetFreeRecFrameStruct(void)
{
	m_oCommFrameStructPtr pFrameStruct = NULL;
	list <m_oCommFrameStructPtr>::iterator iter;
	if(m_uiCountFree > 0)	//�п��н���֡�ṹ��
	{
		// �ӿ��ж����еõ�һ������֡�ṹ��
		iter = m_olsCommFrameStructFree.begin();
		pFrameStruct = *iter;
		m_olsCommFrameStructFree.pop_front();	
		m_uiCountFree--;	// ���н���֡�ṹ��������1
	}
	return pFrameStruct;
}
// ����һ�����н���֡�ṹ��
void CClientRecFrame::AddFreeRecFrameStruct(m_oCommFrameStructPtr pFrameStruct)
{
	//��ʼ������֡�ṹ��
	OnResetRecFrameStruct(pFrameStruct);
	//������ж���
	m_olsCommFrameStructFree.push_back(pFrameStruct);
	m_uiCountFree++;	// ���н���֡�ṹ��������1
}
// �ر�
void CClientRecFrame::OnClose(void)
{
	m_olsCommFrameStructFree.clear();
	EnterCriticalSection(&m_oSecClientRecFrame);
	m_olsCommRecFrame.clear();
	LeaveCriticalSection(&m_oSecClientRecFrame);
}

// ����֡
void CClientRecFrame::PhraseFrame(char* cpFrame, unsigned short usSize)
{
	int iPos = 0;
	unsigned short usCmd = 0;
	m_oCommFrameStructPtr pFrameStruct = NULL;
	pFrameStruct = GetFreeRecFrameStruct();
	// ֡���ݳ���
	pFrameStruct->m_usFrameInfoSize = usSize;
	memcpy(&usCmd, &cpFrame[iPos], 2);
	iPos += 2;
	// ֡��������
	if (usCmd & CmdReturnBit)
	{
		pFrameStruct->m_cCmdType = CmdTypeReturn;
	}
	else
	{
		pFrameStruct->m_cCmdType = CmdTypeSet;
	}
	// ֡�����֣�����֡�Ĺ���
	pFrameStruct->m_usCmd = usCmd & (!CmdReturnBit);
	// �����ʱ���
	memcpy(&pFrameStruct->m_uiServerTimeStep, &cpFrame[iPos], 4);
	iPos += 4;
	// �ͻ���ʱ���
	memcpy(&pFrameStruct->m_uiClientTimeStep, &cpFrame[iPos], 4);
	iPos += 4;
	// ����ˮ��
	memcpy(&pFrameStruct->m_uiPacketIndex, &cpFrame[iPos], 4);
	iPos += 4;
	// ������ˮ��
	memcpy(&pFrameStruct->m_uiCmdIndex, &cpFrame[iPos], 4);
	iPos += 4;
	// ��֡��
	memcpy(&pFrameStruct->m_uiFrameNum, &cpFrame[iPos], 4);
	iPos += 4;
	// ֡���
	memcpy(&pFrameStruct->m_uiFrameIndex, &cpFrame[iPos], 4);
	iPos += 4;
	// ֡����ִ�н��
	memcpy(&pFrameStruct->m_cResult, &cpFrame[iPos], 1);
	iPos += 1;
	// ֡����,���Ϊ��ѯ������֡���ݵ�ǰ�����ֽڷֱ����кź������
	memcpy(&pFrameStruct->m_pcFrameInfo, &cpFrame[iPos], usSize - 27);
	iPos += 27;
	EnterCriticalSection(&m_oSecClientRecFrame);
	m_olsCommRecFrame.push_back(pFrameStruct);
	LeaveCriticalSection(&m_oSecClientRecFrame);
}