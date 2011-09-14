#include "StdAfx.h"
#include "FrameTail.h"

CFrameTail::CFrameTail()
{
}

CFrameTail::~CFrameTail()
{
}

/**
* ���ö���
* @param void
* @return void
*/
void CFrameTail::Reset()
{
	// ԴIP��ַ
	m_uiIPSource = 0;
	// Ŀ��IP��ַ
	m_uiIPAim = 0;
	// Ŀ��˿ں�
	m_usPortAim = 0;
	// ����� 1-��������Ӧ��2-��ѯ����Ӧ��3-AD���������ط�
	m_usCommand = 0;
	// ��������IP��ַ
	m_uiIPInstrument = 0;
	// ����SN��
	m_uiSN = 0;
	// �������� 1-����վ��2-��Դվ��3-�ɼ�վ
	m_uiInstrumentType = 0;
	// ����ϵͳʱ��
	m_uiTimeSystem = 0;
	// ·��IP��ַ��·�ɷ��� 1-�ϣ�2-�£�3-��4-��
	m_uiRoutIP = 0;
}

/**
* ����β��֡
* @param void
* @return bool true���ɹ���false��ʧ��
*/
bool CFrameTail::ParseFrame()
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
bool CFrameTail::ParseCommandWord()
{
	byte pData[5];	// ����������
	byte byCommandWord;	// ������
	int iMaxCommandWordCount = 5;	// ���������ٸ�������
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
		//�жϣ���������IP��ַ������
		if(0x03 == byCommandWord)
		{
			// ��������IP��ַ
			memcpy(&m_uiIPInstrument, &pData[1], 4);
		}

		//�жϣ�����������
		if(0x01 == byCommandWord)
		{
			// ����SN��
			memcpy(&m_uiSN, &pData[1], 4);
//			TRACE1("β��֡-����SN�ţ�%d\r\n", m_uiSN);
//			TRACE1("β��֡-����IP��ַ��%d\r\n", m_uiIPInstrument);
			// �������� 1-����վ��2-��Դվ��3-�ɼ�վ
			m_uiInstrumentType = m_uiSN % 4;
//			m_uiInstrumentType=3;			// temp add by zl 2011.3.15
		}

		//�жϣ�����ϵͳʱ��������
		if(0x04 == byCommandWord)
		{
			// ����ϵͳʱ��
			memcpy(&m_uiTimeSystem, &pData[1], 4);
		}

		//�жϣ�����·��IP��ַ������
		if(0x3F == byCommandWord)
		{
			// ·��IP��ַ
			memcpy(&m_uiRoutIP, &pData[1], 4);
//			if(m_uiRoutIP!=0x4)
//				m_uiInstrumentType=1;			// temp add by zl 2011.3.15
		}

		iCommandWordCount++;

		if(iCommandWordCount == iMaxCommandWordCount)	//���������ֽ�����
		{
			break;
		}
	}

	return true;
}