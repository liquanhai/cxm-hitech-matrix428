#include "StdAfx.h"
#include "FrameIPSet.h"
#include "Matrixline.h"

CFrameIPSet::CFrameIPSet()
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

CFrameIPSet::~CFrameIPSet()
{
}

/**
* ���ö���
* @param void
* @return void
*/
void CFrameIPSet::Reset()
{
	// ԴIP��ַ
	m_uiIPSource = 0;
	// Ŀ��IP��ַ
	m_uiIPAim = 0xFFFFFFFF;
	// Ŀ��˿ں�
	m_usPortAim = 0;
	// ����� 1-��������Ӧ��2-��ѯ����Ӧ��3-AD���������ط�
	m_usCommand = 0;
	// ����SN��
	m_uiSN = 0;
	// �������� 1-����վ��2-��Դվ��3-�ɼ�վ
	m_uiInstrumentType = 0;
	// ��������IP
	m_uiIPInstrument = 0;
	// ·��IP��ַ��·�ɷ��� 1-��
	m_uiRoutIPTop = 0;
	// ·��IP��ַ��·�ɷ��� 2-��
	m_uiRoutIPDown = 0;
	// ·��IP��ַ��·�ɷ��� 3-��
	m_uiRoutIPLeft = 0;
	// ·��IP��ַ��·�ɷ��� 4-��
	m_uiRoutIPRight = 0;
	// ·��IP��ַ
	m_uiRoutIP = 0;
}

/**
* ����IP��ַ����Ӧ��֡
* @param void
* @return bool true���ɹ���false��ʧ��
*/
bool CFrameIPSet::ParseFrame()
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

//	TRACE1("IP��ַ����Ӧ��֡-����SN�ţ�%d\r\n", m_uiSN);
//	TRACE1("IP��ַ����Ӧ��֡-����IP��ַ��%d\r\n", m_uiIPInstrument);

	return true;
}

/**
* ����������
* @param void
* @return bool true���ɹ���false��ʧ��
*/
bool CFrameIPSet::ParseCommandWord()
{
	byte pData[5];	// ����������
	byte byCommandWord;	// ������
	int iMaxCommandWordCount = 8;	// ���������ٸ�������
	int iCommandWordCount = 0;	// �����ּ���
	int i0x1FCount = 0;	// 0x1F�����ּ���

	while(true)
	{
		// �õ�����������
		memcpy(pData, &m_pFrameData[28 + iCommandWordCount * 5], 5);
		// ������
		byCommandWord = pData[0];

		// �жϣ���������
		if(0x0 == byCommandWord)
		{
			break;
		}

		// �жϣ�����������
		if(0x01 == byCommandWord)
		{
			// ����SN��
			memcpy(&m_uiSN, &pData[1], 4);
			// �������� 1-����վ��2-��Դվ��3-�ɼ�վ
			m_uiInstrumentType = m_uiSN % 4;
		}

		// �жϣ���������IP������
		if(0x03 == byCommandWord)
		{
			// ��������IP
			memcpy(&m_uiIPInstrument, &pData[1], 4);
		}

		// �жϣ�����·��IP��ַ����������
		if(0x1F == byCommandWord)
		{
			i0x1FCount++;
			switch(i0x1FCount)
			{
			case 1:
				// ·��IP��ַ��·�ɷ��� 1��
				memcpy(&m_uiRoutIPTop, &pData[1], 4);
				break;
			case 2:
				// ·��IP��ַ��·�ɷ��� 2��
				memcpy(&m_uiRoutIPDown, &pData[1], 4);
				break;
			case 3:
				// ·��IP��ַ��·�ɷ��� 3��
				memcpy(&m_uiRoutIPLeft, &pData[1], 4);
				break;
			case 4:
				// ·��IP��ַ��·�ɷ��� 4��
				memcpy(&m_uiRoutIPRight, &pData[1], 4);
				break;
			}
		}

		// �жϣ�����·��IP��ַ������
		if(0x3F == byCommandWord)
		{
			// ·��IP��ַ
			memcpy(&m_uiRoutIP, &pData[1], 4);
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
* ��������IP��ַ����֡
* @param void
* @return void
*/
/*
void CFrameIPSet::MakeFrameData()
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

	// ԴIP��ַ
	memcpy(&m_pFrameData[16], &m_uiIPSource, 4);
	// Ŀ��IP��ַ
	memcpy(&m_pFrameData[20], &m_uiIPAim, 4);
	// Ŀ��˿ں�
	memcpy(&m_pFrameData[24], &m_usPortAim, 2);
	// ����� 1-��������Ӧ��2-��ѯ����Ӧ��3-AD���������ط�
	memcpy(&m_pFrameData[26], &m_usCommand, 2);

//	TRACE1("IP��ַ����֡-����SN�ţ�%d\r\n", m_uiSN);
//	TRACE1("IP��ַ����֡-����IP��ַ��%d\r\n", m_uiIPInstrument);

	int iPos = 32;
	// ������������������
	m_pFrameData[iPos] = 0x01;
	iPos++;
	// ����SN��
	memcpy(&m_pFrameData[iPos], &m_uiSN, 4);
	iPos = iPos + 4;

	// ��������վ��IP��ַ����������
	m_pFrameData[iPos] = 0x03;
	iPos++;
	// ��������IP
	memcpy(&m_pFrameData[iPos], &m_uiIPInstrument, 4);
	iPos = iPos + 4;

	// �жϣ��������� 1-����վ ��Ҫ����·��IP��ַ
	if(1 == m_uiInstrumentType)
	{
		// ��������վ��·��IP��ַ����������
		m_pFrameData[iPos] = 0x1F;
		iPos++;
		// ·��IP��ַ��·�ɷ��� 3-��
		//memcpy(&m_pFrameData[iPos], &m_uiRoutIPLeft, 4);
		int itmp=0x33333333;
		memcpy(&m_pFrameData[iPos], &itmp, 4);
		iPos = iPos + 4;

		// ��������վ��·��IP��ַ����������
		m_pFrameData[iPos] = 0x1F;
		iPos++;
		// ·��IP��ַ��·�ɷ��� 4-��
		//memcpy(&m_pFrameData[iPos], &m_uiRoutIPRight, 4);
		itmp=0x44444444;
		memcpy(&m_pFrameData[iPos], &itmp, 4);
		iPos = iPos + 4;

		// ��������վ��·��IP��ַ����������
		m_pFrameData[iPos] = 0x1F;
		iPos++;
		// ·��IP��ַ��·�ɷ��� 1-��
		//memcpy(&m_pFrameData[iPos], &m_uiRoutIPTop, 4);
		itmp=0x11111111;					//by zl 04.12
		memcpy(&m_pFrameData[iPos], &itmp, 4);
		iPos = iPos + 4;

		// ��������վ��·��IP��ַ����������
		m_pFrameData[iPos] = 0x1F;
		iPos++;
		// ·��IP��ַ��·�ɷ��� 2-��
		//memcpy(&m_pFrameData[iPos], &m_uiRoutIPDown, 4);
		itmp=0x22222222;
		memcpy(&m_pFrameData[iPos], &itmp, 4);
		iPos = iPos + 4;

	}else
	{
		// ���ù㲥�˿�
		m_pFrameData[iPos] = 0x0a;
		iPos++;
		// �㲥����˿�0x5000
		int intPortADListen=PortADListen;
		memcpy(&m_pFrameData[iPos], &intPortADListen, 4);
		iPos = iPos + 4;
	}

	// ���������ֽ���
	m_pFrameData[iPos] = 0x00;
}
*/

void CFrameIPSet::MakeFrameData()
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

	// ԴIP��ַ
	memcpy(&m_pFrameData[16], &m_uiIPSource, 4);
	// Ŀ��IP��ַ
	memcpy(&m_pFrameData[20], &m_uiIPAim, 4);
	// Ŀ��˿ں�
	memcpy(&m_pFrameData[24], &m_usPortAim, 2);
	// ����� 1-��������Ӧ��2-��ѯ����Ӧ��3-AD���������ط�
	memcpy(&m_pFrameData[26], &m_usCommand, 2);

//	TRACE1("IP��ַ����֡-����SN�ţ�%d\r\n", m_uiSN);
//	TRACE1("IP��ַ����֡-����IP��ַ��%d\r\n", m_uiIPInstrument);

	int iPos = 32;
	// ������������������
	m_pFrameData[iPos] = 0x01;
	iPos++;
	// ����SN��
	memcpy(&m_pFrameData[iPos], &m_uiSN, 4);
	iPos = iPos + 4;

	// ��������վ��IP��ַ����������
	m_pFrameData[iPos] = 0x03;
	iPos++;
	// ��������IP
	memcpy(&m_pFrameData[iPos], &m_uiIPInstrument, 4);
	iPos = iPos + 4;

	// �жϣ��������� 1-����վ ��Ҫ����·��IP��ַ
	if(1 == m_uiInstrumentType)
	{
/*		//�½���վ����Ϊ0x11111111-0x44444444���ɽ���վ����Ϊ0x33333333-44,11-22
		// ��������վ��·��IP��ַ����������
		m_pFrameData[iPos] = 0x1F;
		iPos++;
		// ·��IP��ַ��·�ɷ��� 1-��
		//memcpy(&m_pFrameData[iPos], &m_uiRoutIPTop, 4);
		int itmp=0x11111111;					//by zl 04.12
		memcpy(&m_pFrameData[iPos], &itmp, 4);
		iPos = iPos + 4;

		// ��������վ��·��IP��ַ����������
		m_pFrameData[iPos] = 0x1F;
		iPos++;
		// ·��IP��ַ��·�ɷ��� 2-��
		//memcpy(&m_pFrameData[iPos], &m_uiRoutIPDown, 4);
		itmp=0x22222222;
		memcpy(&m_pFrameData[iPos], &itmp, 4);
		iPos = iPos + 4;
*/
		// ��������վ��·��IP��ַ����������
		m_pFrameData[iPos] = 0x1F;
		iPos++;
		// ·��IP��ַ��·�ɷ��� 3-��
		memcpy(&m_pFrameData[iPos], &m_uiRoutIPLeft, 4);
		//int itmp=0x33333333;
		int itmp=0x44444444;
		memcpy(&m_pFrameData[iPos], &itmp, 4);
		iPos = iPos + 4;

		// ��������վ��·��IP��ַ����������
		m_pFrameData[iPos] = 0x1F;
		iPos++;
		// ·��IP��ַ��·�ɷ��� 4-��
		memcpy(&m_pFrameData[iPos], &m_uiRoutIPRight, 4);
		//itmp=0x44444444;
		itmp=0x33333333;
		memcpy(&m_pFrameData[iPos], &itmp, 4);
		iPos = iPos + 4;

	// ��������վ��·��IP��ַ����������
		m_pFrameData[iPos] = 0x1F;
		iPos++;
		// ·��IP��ַ��·�ɷ��� 1-��
		memcpy(&m_pFrameData[iPos], &m_uiRoutIPTop, 4);
		itmp=0x11111111;					//by zl 04.12
		memcpy(&m_pFrameData[iPos], &itmp, 4);
		iPos = iPos + 4;

		// ��������վ��·��IP��ַ����������
		m_pFrameData[iPos] = 0x1F;
		iPos++;
		// ·��IP��ַ��·�ɷ��� 2-��
		memcpy(&m_pFrameData[iPos], &m_uiRoutIPDown, 4);
		itmp=0x22222222;
		memcpy(&m_pFrameData[iPos], &itmp, 4);
		iPos = iPos + 4;

		// ����·�ɿ���
		m_pFrameData[iPos] = 0x0F;
		iPos++;
		itmp=0;
		memcpy(&m_pFrameData[iPos], &itmp, 4);
		iPos = iPos + 4;
	}else
	{
		// ���ù㲥�˿�
		m_pFrameData[iPos] = 0x0a;
		iPos++;
		// �㲥����˿�0x5000
		int intPortADListen=PortADListen;
		memcpy(&m_pFrameData[iPos], &intPortADListen, 4);
		iPos = iPos + 4;
/*
		// ���ù㲥�˿�
		m_pFrameData[iPos] = 0x0a;
		iPos++;
		// �㲥����˿�0x5000
		intPortADListen=PortTimeListen;
		memcpy(&m_pFrameData[iPos], &intPortADListen, 4);
		iPos = iPos + 4;
*/		}

	// ���������ֽ���
	m_pFrameData[iPos] = 0x00;
}