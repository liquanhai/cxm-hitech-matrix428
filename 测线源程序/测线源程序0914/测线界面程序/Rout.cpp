#include "stdafx.h"
#include "Rout.h"

CRout::CRout(void)
{
}

CRout::~CRout(void)
{
}

// ����
void CRout::OnReset(void)
{
	// �����Ƿ�ʹ����
	m_bInUsed = false;

	// ·�ɷ��� 1-�ϣ�2-�£�3-��4��
	m_uiRoutDirection = 0;
	// ·��ͷ����
	m_pHead = NULL;
	// ·��β����
	m_pTail = NULL;
	// ·��ͷ����
	m_uiSNHead = 0;
	// ·��β����
	m_uiSNTail = 0;
	// ·��ͷ����
	m_iIndexHead = -1;
	// ·��β����
	m_iIndexTail = -1;
	// ·��ʱ��
	m_uiRoutTime = 0;
	// �ϴ�ʱͳ����ʱ��
	m_uiDelayProcTime = 0;
}