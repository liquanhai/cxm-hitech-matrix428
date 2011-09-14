#include "StdAfx.h"
#include "FrameTestData.h"

CFrameTestData::CFrameTestData()
{
	// ֡��С
	m_iFrameSize = 256;
	// ��������
	m_pData = &m_pFrameData[30];
	Reset();
}

CFrameTestData::~CFrameTestData()
{
}

/**
* ���ö���
* @param void
* @return void
*/
void CFrameTestData::Reset()
{
	// ԴIP��ַ
	m_uiIPSource = 0;
	// Ŀ��IP��ַ
	m_uiIPAim = 0;
	// Ŀ��˿ں�
	m_usPortAim = 0;
	// ����� 1-��������Ӧ��2-��ѯ����Ӧ��3-AD���������ط�
	m_usCommand = 0;

	// ��������
	m_usDataIndex = 0;
}

/**
* ������������֡
* @param void
* @return bool true���ɹ���false��ʧ��
*/
bool CFrameTestData::ParseFrame()
{
	Reset();
	// ԴIP��ַ
	memcpy(&m_uiIPSource, &m_pFrameData[16], 4);
	// Ŀ��IP��ַ
	memcpy(&m_uiIPAim, &m_pFrameData[20], 4);
	// Ŀ��˿ں�
	memcpy(&m_usPortAim, &m_pFrameData[24], 2);
	// ����� 1-��������Ӧ��2-��ѯ����Ӧ��3-AD���������ط�
	memcpy(&m_usCommand, &m_pFrameData[26], 2);
	// ��������
	memcpy(&m_usDataIndex, &m_pFrameData[28], 2);
//	TRACE1("��������֡-����IP��ַ��%d\r\n", m_uiIPSource);
//	TRACE1("��������֡-����������%d\r\n", m_usDataIndex);
	//if(m_usCommand==0x3 && m_usPortAim==0x5000)
	if(m_usCommand==0x3 )
		return true;
	else
		return false;
}