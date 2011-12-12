#include "StdAfx.h"
#include "FrameHead.h"

CFrameHead::CFrameHead()
{
	// ֡��С
	m_iFrameSize = 256;
	Reset();
}

CFrameHead::~CFrameHead()
{
}

/**
* ���ö���
* @param void
* @return void
*/
void CFrameHead::Reset()
{
	// ԴIP��ַ
	m_uiIPSource = 0;
	// Ŀ��IP��ַ
	m_uiIPAim = 0;
	// Ŀ��˿ں�
	m_usPortAim = 0;
	// ����� 1-��������Ӧ��2-��ѯ����Ӧ��3-AD���������ط�
	m_usCommand = 0;
	// ����SN��
	m_uiSN = 0;
	// �����װ�ʱ��
	m_uiTimeHeadFrame = 0;
	// ·��IP��ַ
	m_uiRoutIP = 0;
}

/**
* �����װ�֡
* @param void
* @return bool true���ɹ���false��ʧ��
*/
bool CFrameHead::ParseFrame()
{
	// ���ö���
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
bool CFrameHead::ParseCommandWord()
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

		//�жϣ���������
		if(0x0 == byCommandWord)
		{
			break;
		}

		//�жϣ�����������
		if(0x01 == byCommandWord)
		{
			// ����SN��
			memcpy(&m_uiSN, &pData[1], 4);
		}
		//�жϣ��װ�ʱ��������
		if(0x02 == byCommandWord)
		{
			// �����װ�ʱ��
			memcpy(&m_uiTimeHeadFrame, &pData[1], 4);
//			TRACE1("�װ�֡-�װ�ʱ�̣�%d\r\n", m_uiTimeHeadFrame);
		}

		//�жϣ�����·��IP��ַ������
		if(0x3F == byCommandWord)	//
		{
			// ·��IP��ַ
			memcpy(&m_uiRoutIP, &pData[1], 4);
	//		if(m_uiSN==4353)
	//			m_uiRoutIP=0;
		}

		iCommandWordCount++;

		if(iCommandWordCount == iMaxCommandWordCount)	//���������ֽ�����
		{
			break;
		}
	}
	return true;
}

