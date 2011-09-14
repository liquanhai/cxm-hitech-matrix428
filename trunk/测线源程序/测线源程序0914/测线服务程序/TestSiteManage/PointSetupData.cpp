#include "StdAfx.h"
#include "PointSetupData.h"

CPointSetupData::CPointSetupData()
{
}

CPointSetupData::~CPointSetupData()
{
}

/**
* ���¼���
* @param void
* @return void
*/
void CPointSetupData::OnReset()
{
	// ����Ƿ�ʹ����
	m_bInUsed = false;
	// �����
	m_iPointCode = 0;

	// ���ߺ�
	m_uiNbLine = 0;
	// ����
	m_uiNbPoint = 0;
	// ���������
	m_uiIndexPoint = 0;
	// �Ƿ��Ƶ�
	m_bMute = false;

	// ������ӵĲ��
	m_pPointLeft = NULL;
	// ������ӵĲ��
	m_pPointRight = NULL;
	// �������ӵĲ��
	m_pPointlTop = NULL;
	// �������ӵĲ��
	m_pPointlDown = NULL;

	// �������
	m_uiChannelCount = 0;
	// ���ͷָ��
	m_pChannelHead = NULL;
	// ���βָ��
	m_pChannelTail = NULL;
}

/**
* ���ݲ��ߺźͲ��ţ����ɲ��������
* @param void
* @return void
*/
void CPointSetupData::CreateIndexPoint()
{
	// ���������
	m_uiIndexPoint = CreateIndexPoint(m_uiNbLine, m_uiNbPoint);
}

/**
* ���ݲ��ߺźͲ��ţ����ɲ��������
* @param unsigned int uiNbLine ���ߺ�
* @param unsigned int uiNbPoint ����
* @return unsigned int ���������
*/
// 
unsigned int CPointSetupData::CreateIndexPoint(unsigned int uiNbLine, unsigned int uiNbPoint)
{
	// ���������
	return uiNbLine * 1000000 + uiNbPoint * 10;
}

/**
* �������ӷ��򣬵õ����������һ���Ĳ��
* @param CChannelSetupData* pChannelSetupData ���
* @param unsigned int uiDirection ���ӷ��� 3����4����
* @return CChannelSetupData* ���������һ���Ĳ�� NULL�����������һ���Ĳ��������
*/
CChannelSetupData* CPointSetupData::GetChannelRight(CChannelSetupData* pChannelSetupData, unsigned int uiDirection)
{
	// �жϷ���
	switch(uiDirection)
	{
	case 3:	// ��
		{
			return GetChannelLeft(pChannelSetupData);
			break;
		}
	case 4:	// ��
		{
			return GetChannelRight(pChannelSetupData);
			break;
		}
	}
	return NULL;
}

/**
* �õ����������ӵĲ��
* @param CChannelSetupData* pChannelSetupData ���
* @return CChannelSetupData* ���������һ���Ĳ�� NULL�����������һ���Ĳ��������
*/
CChannelSetupData* CPointSetupData::GetChannelLeft(CChannelSetupData* pChannelSetupData)
{
	// ���Ϊ��
	if(NULL == pChannelSetupData)
	{
		return NULL;
	}
	// ���Ϊ���Ĳ��ͷ
	if(m_pChannelHead == pChannelSetupData)
	{
		return NULL;
	}
	// �õ����������ӵĲ��
	return pChannelSetupData->m_pChannelLeft;
}

/**
* �õ�����ұ����ӵĲ��
* @param CChannelSetupData* pChannelSetupData ���
* @return CChannelSetupData* ���������һ���Ĳ�� NULL�����������һ���Ĳ��������
*/
CChannelSetupData* CPointSetupData::GetChannelRight(CChannelSetupData* pChannelSetupData)
{
	CChannelSetupData* pChannelSetupDataRight = NULL;
	// ���Ϊ��
	if(NULL == pChannelSetupData)
	{
		return NULL;
	}
	// ���Ϊ���Ĳ��β
	if(m_pChannelTail == pChannelSetupData)
	{
		return NULL;
	}
	// �õ�����ұ����ӵĲ��
	return pChannelSetupData->m_pChannelRight;
}