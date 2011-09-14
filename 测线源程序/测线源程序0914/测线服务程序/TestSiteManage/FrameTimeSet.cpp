#include "StdAfx.h"
#include "FrameTimeSet.h"

CFrameTimeSet::CFrameTimeSet()
{
	m_pFrameData[0] = 0x11;
	m_pFrameData[1] = 0x22;
	m_pFrameData[2] = 0x33;
	m_pFrameData[3] = 0x44;
	m_pFrameData[4] = 0x00;
	m_pFrameData[5] = 0x00;
	m_pFrameData[6] = 0x00;
	m_pFrameData[7] = 0x00;
	m_pFrameData[8] = 0x00;
	m_pFrameData[9] = 0x00;
	m_pFrameData[10] = 0x00;
	m_pFrameData[11] = 0x00;
	m_pFrameData[12] = 0x00;
	m_pFrameData[13] = 0x00;
	m_pFrameData[14] = 0x00;
	m_pFrameData[15] = 0x00;
	// ֡��С
	m_iFrameSize = 256;
	Reset();
}

CFrameTimeSet::~CFrameTimeSet()
{
}

/**
* ���ö���
* @param void
* @return void
*/
void CFrameTimeSet::Reset()
{
	// ԴIP��ַ
	m_uiIPSource = 0;
	// Ŀ��IP��ַ
	m_uiIPAim = 0;
	// Ŀ��˿ں�
	m_usPortAim = 0;
	// ����� 1-��������Ӧ��2-��ѯ����Ӧ��3-AD���������ط�
	m_usCommand = 0;
	// ����ʱ��������λ
	m_uiTimeHigh = 0;
	// ����ʱ��������λ
	m_uiTimeLow = 0;
}

/**
* ����ʱ������Ӧ��֡
* @param void
* @return bool true���ɹ���false��ʧ��
*/
bool CFrameTimeSet::ParseFrame()
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

	// ����������
	ParseCommandWord();

	return true;
}

/**
* ����������
* @param void
* @return bool true���ɹ���false��ʧ��
*/
bool CFrameTimeSet::ParseCommandWord()
{
	byte pData[5];	// ����������
	byte byCommandWord;	// ������
	int iMaxCommandWordCount = 4;	// ���������ٸ�������
	int iCommandWordCount = 0;	// �����ּ���

	while(true)
	{
		// �õ�����������
		memcpy(pData, &m_pFrameData[28 + iCommandWordCount * 5], 5);
		// ������
		byCommandWord = pData[0];

		if(0x0 == byCommandWord)	//��������
		{
			break;
		}
		if(0x05 == byCommandWord)	// ����ʱ��������λ
		{
			memcpy(&m_uiTimeHigh, &pData[1], 4);
		}
		if(0x06 == byCommandWord)	// ����ʱ��������λ
		{
			memcpy(&m_uiTimeLow, &pData[1], 4);
		}
		iCommandWordCount++;

		if(iCommandWordCount == iMaxCommandWordCount)	//���������ֽ�����
		{
			break;
		}
	}
	return true;
}

/**
* ��������ʱ���ַ����֡
* @param void
* @return void
*/
void CFrameTimeSet::MakeFrameData()
{
	// ԴIP��ַ
	memcpy(&m_pFrameData[16], &m_uiIPSource, 4);
	// Ŀ��IP��ַ
	memcpy(&m_pFrameData[20], &m_uiIPAim, 4);
	// Ŀ��˿ں�
	memcpy(&m_pFrameData[24], &m_usPortAim, 2);
	// ����� 1-��������Ӧ��2-��ѯ����Ӧ��3-AD���������ط�
	memcpy(&m_pFrameData[26], &m_usCommand, 2);

//	TRACE1("ʱ���ӳ�����֡-����IP��ַ��%d\r\n", m_uiIPAim);

	int iPos = 32;
	// ����ʱ��������λ
	m_pFrameData[iPos] = 0x05;
	iPos++;
	memcpy(&m_pFrameData[iPos], &m_uiTimeHigh, 4);
	iPos = iPos + 4;

	// ����ʱ��������λ
	m_pFrameData[iPos] = 0x06;
	iPos++;
	memcpy(&m_pFrameData[iPos], &m_uiTimeLow, 4);
	iPos = iPos + 4;

	// ���������ֽ���
	m_pFrameData[iPos] = 0x00;
}