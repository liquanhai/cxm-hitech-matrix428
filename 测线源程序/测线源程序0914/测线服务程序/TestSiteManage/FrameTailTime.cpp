#include "StdAfx.h"
#include "FrameTailTime.h"
#include "Matrixline.h"

CFrameTailTime::CFrameTailTime()
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

CFrameTailTime::~CFrameTailTime()
{
}

/**
* ���ö���
* @param void
* @return void
*/
void CFrameTailTime::Reset()
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
	m_uiIPSource = 0;
	// Ŀ��IP��ַ
	m_uiIPAim = 0;
	// Ŀ��˿ں�
	m_usPortAim = 0;
	// ����� 1-��������Ӧ��2-��ѯ����Ӧ��3-AD���������ط�
	m_usCommand = 0;

	m_usReceiveTime = 0;	// 16bitsʱ�䣬����ʱ�̵�λ
	m_usSendTime = 0;	// 16bitsʱ�䣬����ʱ�̵�λ

	m_usLineLeftReceiveTime = 0;	// 16bits ���߷�������β������ʱ��
	m_usLineRightReceiveTime = 0;	// 16bits ���߷�������β������ʱ��

	m_usCrossTopReceiveTime = 0;	// 16bits �����߷�������β������ʱ��
	m_usCrossDownReceiveTime = 0;	// 16bits �����߷�����β������ʱ��
}

/**
* ����β��ʱ�̲�ѯӦ��֡
* @param void
* @return bool true���ɹ���false��ʧ��
*/
bool CFrameTailTime::ParseFrame()
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
//	TRACE1("β��ʱ�̲�ѯӦ��֡-����IP��ַ��%d\r\n", m_uiIPSource);
	return true;
}

/**
* ����������
* @param void
* @return bool true���ɹ���false��ʧ��
*/
bool CFrameTailTime::ParseCommandWord()
{
	byte pData[5];	// ����������
	byte byCommandWord;	// ������
	int iMaxCommandWordCount = 9;	// ���������ٸ�������
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

		if(0x16 == byCommandWord)	// ������	0x16���ա�����ʱ�̵�λ
		{
			// 16bitsʱ�䣬����ʱ�̵�λ
			memcpy(&m_usReceiveTime, &pData[1], 2);
			// 16bitsʱ�䣬����ʱ�̵�λ
			memcpy(&m_usSendTime, &pData[3], 2);
		}
		if(0x1B == byCommandWord)	// ������	0x1B���ա�����ʱ�̵�λ
		{
			// 16bits ���߷�������β������ʱ��
			memcpy(&m_usLineLeftReceiveTime, &pData[3], 2);
			// 16bits ���߷�������β������ʱ��
			memcpy(&m_usLineRightReceiveTime, &pData[1], 2);
		}
		if(0x1C == byCommandWord)	// ������	0x1C���ա�����ʱ�̵�λ
		{
			// 16bits �����߷�������β������ʱ��
			memcpy(&m_usCrossTopReceiveTime, &pData[3], 2);
			// 16bits �����߷�����β������ʱ��
			memcpy(&m_usCrossDownReceiveTime, &pData[1], 2);
		}
		if(0x04 == byCommandWord)	// ������	0x04���ձ���ϵͳʱ�� by zl
		{
			
			memcpy(&m_uiTimeSystem, &pData[1], 4);
		}
		if(0x19 == byCommandWord)	// ������	0x19��������ʱ��
		{
			
			memcpy(&m_uiNetTime, &pData[1], 4);
		}
		if(0x0b == byCommandWord)	// ������	0x0b��������ʱ��
		{
			m_uiNetOrder=0;
			m_uiNetState=0;
			memcpy(&m_uiNetState, &pData[1], 1);
			memcpy(&m_uiNetOrder, &pData[2], 1);
		}
		if(0x1d == byCommandWord)	// ������	0x0b����վ����
		{
			
			memcpy(&m_uiNetState, &pData[1], 4);
		}
		if(0x1e == byCommandWord)	// ������	0x0b����վ����
		{
			;
			//m_uiNetOrder=0;
			//memcpy(&m_uiNetOrder, &pData[1], 2);
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
* ����β��ʱ�̲�ѯ֡
* @param void
* @return void
*/
void CFrameTailTime::MakeFrameData()
{
	// ԴIP��ַ
	memcpy(&m_pFrameData[16], &m_uiIPSource, 4);
	// Ŀ��IP��ַ
	memcpy(&m_pFrameData[20], &m_uiIPAim, 4);
//	TRACE1("β��ʱ�̲�ѯ֡-����IP��ַ��%d\r\n", m_uiIPAim);
	// Ŀ��˿ں�
	memcpy(&m_pFrameData[24], &m_usPortAim, 2);
	// ����� 1-��������Ӧ��2-��ѯ����Ӧ��3-AD���������ط�
	memcpy(&m_pFrameData[26], &m_usCommand, 2);

	int iPos = 32;
	unsigned int i17=PortTimeListen;
	
	if(1 != m_uiInstrumentType){
		i17=PortTimeListen;
		m_pFrameData[iPos] =0x17;
		iPos++;
		memcpy(&m_pFrameData[iPos], &i17, 4);
		iPos = iPos + 4;
	}

	// ������	0x16���ա�����ʱ�̵�λ
	m_pFrameData[iPos] = 0x16;
	iPos++;
	memset(&m_pFrameData[iPos], 0, 4);
	iPos = iPos + 4;
	// �������� 1-����վ
	if(1 == m_uiInstrumentType)
	{
		// ������	0x1B  ����վ����β������ʱ��
		m_pFrameData[iPos] = 0x1B;
		iPos++;
		memset(&m_pFrameData[iPos], 0, 4);
		iPos = iPos + 4;
		// ������	0x1C  ����վ������β������ʱ��
		m_pFrameData[iPos] = 0x1C;
		iPos++;
		memset(&m_pFrameData[iPos], 0, 4);
		iPos = iPos + 4;
		// ������	0x1D  ����վ����
		m_pFrameData[iPos] = 0x1D;
		iPos++;
		memset(&m_pFrameData[iPos], 0, 4);
		iPos = iPos + 4;
		// ������	0x1E  ����վ����ڹ���
		m_pFrameData[iPos] = 0x1E;
		iPos++;
		memset(&m_pFrameData[iPos], 0, 4);
		iPos = iPos + 4;
	}
	// ������	0x04���ա�����ʱ�̵�λ	by zl
	m_pFrameData[iPos] = 0x04;
	iPos++;
	memset(&m_pFrameData[iPos], 0, 4);
	iPos = iPos + 4;
	// ������	0x19����ʱ��	by zl
	m_pFrameData[iPos] = 0x19;
	iPos++;
	memset(&m_pFrameData[iPos], 0, 4);
	iPos = iPos + 4;
	if(1 != m_uiInstrumentType){
		// ������	0x0bӲ��״̬	by zl
		m_pFrameData[iPos] = 0x0b;
		iPos++;
		memset(&m_pFrameData[iPos], 0, 4);
		iPos = iPos + 4;
	}

	// ���������ֽ���
	m_pFrameData[iPos] = 0x00;
}
