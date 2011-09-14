#include "StdAfx.h"
#include "FrameInterface.h"

CFrameInterface::CFrameInterface()
{
	// ������
	m_pData = &m_pFrameData[13];
}

CFrameInterface::~CFrameInterface()
{
}

/**
* ���ö���
* @param void
* @return void
*/
void CFrameInterface::Reset()
{

}

/**
* ����֡
* @param void
* @return bool true���ɹ���false��ʧ��
*/
bool CFrameInterface::ParseFrame()
{
	Reset();
	// ����֡ͷ
	ParseFrameHead();
	// ����������
	ParseCommandWord();
	return true;
}

/**
* ����֡ͷ
* @param void
* @return bool true���ɹ���false��ʧ��
*/
bool CFrameInterface::ParseFrameHead()
{
	int iPos = 0;
	iPos = iPos + 2;

	// ֡����
	memcpy(&m_usFrameSize, &m_pFrameData[iPos], 2);
	iPos = iPos + 2;

	// ֡����
	memcpy(&m_uiFrameCount, &m_pFrameData[iPos], 4);
	iPos = iPos + 4;

	// ֡����
	m_byFrameType = m_pFrameData[iPos];
	iPos = iPos + 1;

	// ����
	memcpy(&m_usCommand, &m_pFrameData[iPos], 2);
	iPos = iPos + 2;

	// �����ָ���
	memcpy(&m_usCommandCount, &m_pFrameData[iPos], 2);
	iPos = iPos + 2;

	// ����������
	m_usDataSize = m_usFrameSize - iPos - 3;

	return true;
}

/**
* ����������
* @param void
* @return bool true���ɹ���false��ʧ��
*/
bool CFrameInterface::ParseCommandWord()
{
	if(0 == m_usCommandCount)
	{
		return true;
	}

	int iPos = 0;

	switch(m_usCommand)
	{
	case 1:	// ����	1-Field ON/OFF		
		m_byFieldOperation = m_pData[iPos];	// Field ON/OFF
		break;

	case 2:	// ����	2-FormLine				
		memcpy(&m_uiSN, &m_pData[iPos], 4);	// �����豸��
		break;

	case 3:	// ����	3-Look		
		memcpy(&m_uiLookAuto, &m_pData[iPos], 4);	// �Ƿ��Զ�����
		iPos = iPos + 4;		
		memcpy(&m_uiTestResistance, &m_pData[iPos], 4);	// �������Ƿ����Resistance
		iPos = iPos + 4;		
		memcpy(&m_uiTestTilt, &m_pData[iPos], 4);	// �������Ƿ����Tilt
		iPos = iPos + 4;		
		memcpy(&m_uiTestLeakage, &m_pData[iPos], 4);	// �������Ƿ����Leakage
		break;

	case 4:	// ����	4-Test From InstrumentTestSetup
		memcpy(&m_uiTestNb, &m_pData[iPos], 4);	// ����������
		m_uiTestNb = m_uiTestNb + 1000;
		break;

	case 5:	// ����	5-Test From SensorTestSetup
		memcpy(&m_uiTestNb, &m_pData[iPos], 4);	// ����������
		m_uiTestNb = m_uiTestNb + 2000;
		break;

	case 6:	// ����	6-Test From MultipleTestSetup
		memcpy(&m_uiTestNb, &m_pData[iPos], 4);	// ����������
		m_uiTestNb = m_uiTestNb + 3000;
		break;

	case 7:	// ����	7-Test From SeismonitorTestSetup
		iPos = iPos + 1;
		memcpy(&m_uiTestNb, &m_pData[iPos], 4);	// ����������
		break;

	case 8:	// ����	8-Test From InstrumentView ����������ͼ�ġ�GO����ť
	case 9:	// ����	9-Test From SensorTestView	���Լ첨����ͼ�ġ�GO����ť
		memcpy(&m_uiTestAim, &m_pData[iPos], 4);	// ���Զ���	1-������2-�첨��
		iPos = iPos + 4;
		memcpy(&m_uiTestType, &m_pData[iPos], 4);	// ��������
		iPos = iPos + 4;
		m_strTestAbsoluteSpread = &m_pData[iPos];	// �������ж���
		break;

	case 10:	// ����	10-Test From SeismonitoView
		m_byTestOperation = m_pData[iPos];	// 1-�������ԣ�0-ֹͣ����
		iPos = iPos + 1;
		m_strTestAbsoluteSpread = &m_pData[iPos];	// �������ж���
		break;

	case 20:	// ����	20-���������ļ���������
		memcpy(&m_uiChangeAim, &m_pData[iPos], 4);	// ���ĵ�Ŀ��
		break;
	}
	return true;
}

/**
* ����Ӧ��֡
* @param CFrameInterface* m_pFrameInterface ����ָ֡��
* @return void
*/
void CFrameInterface::MakeReplyFrame(CFrameInterface* m_pFrameInterface)
{
	m_usFrameSize = 16;
	// ֡ͷ{0xEB90}
	m_pFrameData[0] = 0xEB;
	m_pFrameData[1] = 0x90;
	// ֡����
	memcpy(&m_pFrameData[2], &m_usFrameSize, 2);
	// ֡����
	memcpy(&m_pFrameData[4], &m_pFrameInterface->m_uiFrameCount, 4);
	// ֡���� 0xFF-����֡
	m_pFrameData[8] = 0xFF;
	// ����
	memcpy(&m_pFrameData[9], &m_pFrameInterface->m_usCommand, 2);
	// �����ָ���
	m_usCommandCount = 0;
	memcpy(&m_pFrameData[11], &m_pFrameInterface->m_usCommandCount, 2);
	// У��λ
	m_pFrameData[13] = 0x00;
	// ֡β{0x146F}
	m_pFrameData[14] = 0x14;
	m_pFrameData[15] = 0x6F;
}

/**
* �����ֳ��������֪ͨ����֡
* @param void
* @return void
*/
void CFrameInterface::MakeSiteDataOutputCmdFrame()
{
	m_usFrameSize = 16;
	// ֡ͷ{0xEB90}
	m_pFrameData[0] = 0xEB;
	m_pFrameData[1] = 0x90;
	// ֡����
	memcpy(&m_pFrameData[2], &m_usFrameSize, 2);
	// ֡����
	UINT iNow = GetTickCount();
	memcpy(&m_pFrameData[4], &iNow, 4);
	// ֡���� 0x01-����֡����Ҫ�����֡
	m_pFrameData[8] = 0x01;
	// ����
	m_usCommand = 100;
	memcpy(&m_pFrameData[9], &m_usCommand, 2);
	// �����ָ���
	m_usCommandCount = 0;
	memcpy(&m_pFrameData[11], &m_usCommandCount, 2);

	int iPos = 13;
	// У��λ
	m_pFrameData[iPos] = 0x00;
	iPos = iPos + 1;
	// ֡β{0x146F}
	m_pFrameData[iPos] = 0x14;
	iPos = iPos + 1;
	m_pFrameData[iPos] = 0x6F;
}

/**
* ����ServerField On/Off֡
* @param void
* @return void
*/
void CFrameInterface::MakeServerFieldFrame()
{
	m_usFrameSize = 17;
	// ֡ͷ{0xEB90}
	m_pFrameData[0] = 0xEB;
	m_pFrameData[1] = 0x90;
	// ֡����
	memcpy(&m_pFrameData[2], &m_usFrameSize, 2);
	// ֡����
	UINT iNow = GetTickCount();
	memcpy(&m_pFrameData[4], &iNow, 4);
	// ֡���� 0x01-����֡����Ҫ�����֡
	m_pFrameData[8] = 0x01;
	// ���� 101-Server Field ON/OFF
	m_usCommand = 101;
	memcpy(&m_pFrameData[9], &m_usCommand, 2);
	// �����ָ���
	m_usCommandCount = 1;
	memcpy(&m_pFrameData[11], &m_usCommandCount, 2);

	int iPos = 13;
	m_pFrameData[iPos] = m_byFieldOperation;
	iPos = iPos + 1;
	// У��λ
	m_pFrameData[iPos] = 0x00;
	iPos = iPos + 1;
	// ֡β{0x146F}
	m_pFrameData[iPos] = 0x14;
	iPos = iPos + 1;
	m_pFrameData[iPos] = 0x6F;
}

/**
* ���ɲ�������֡
* @param unsigned int uiTestType ��������
* @param unsigned unsigned int uiDataSize ÿ����������ռ���ֽ���
* @paramunsigned short usDataCount �������ݸ���
* @paramunsigned byte pData ��������
* @return void
*/
void CFrameInterface::CreateOutputDataFrameTest(unsigned int uiTestType, unsigned int uiDataSize, unsigned short usDataCount, byte* pData)
{
	unsigned short usDataLength = uiDataSize * usDataCount;
	m_usFrameSize = 16 + usDataLength;
	// ֡ͷ{0xEB90}
	m_pFrameData[0] = 0xEB;
	m_pFrameData[1] = 0x90;
	// ֡����
	memcpy(&m_pFrameData[2], &m_usFrameSize, 2);
	// ֡����
	UINT iNow = GetTickCount();
	memcpy(&m_pFrameData[4], &iNow, 4);
	// ֡���� 0x03-����֡����Ҫ�����֡
	m_pFrameData[8] = 0x03;
	// ����
	m_usCommand = 200 + (unsigned short)uiTestType;
	memcpy(&m_pFrameData[9], &m_usCommand, 2);
	// �����ָ���
	m_usCommandCount = usDataCount;
	memcpy(&m_pFrameData[11], &m_usCommandCount, 2);

	int iPos = 13;
	// ��������
	memcpy(&m_pFrameData[iPos], pData, usDataLength);
	iPos = iPos + usDataLength;
	// У��λ
	m_pFrameData[iPos] = 0x00;
	iPos = iPos + 1;
	// ֡β{0x146F}
	m_pFrameData[iPos] = 0x14;
	iPos = iPos + 1;
	m_pFrameData[iPos] = 0x6F;
}