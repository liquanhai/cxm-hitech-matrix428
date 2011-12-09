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
* ����֡
* @param void
* @return bool true���ɹ���false��ʧ��
*/
bool CFrameInterface::ParseFrame()
{
	int iPos = 0;
	// ����֡ͷ
	iPos = ParseFrameHead();
	// ����������
	ParseCommandWord(iPos);
	return true;
}

/**
* ����֡ͷ
* @param void
* @return bool true���ɹ���false��ʧ��
*/
int CFrameInterface::ParseFrameHead()
{
	int iPos = 0;
	// ǰ��λΪ֡ͷ
	iPos = iPos + FramePacketSize2B;

	// ֡����
	memcpy(&m_usFrameSize, &m_pFrameData[iPos], FramePacketSize2B);
	iPos = iPos + FramePacketSize2B;

	// ֡����
	memcpy(&m_uiFrameCount, &m_pFrameData[iPos], FramePacketSize4B);
	iPos = iPos + FramePacketSize4B;

	// ֡����
	m_byFrameType = m_pFrameData[iPos];
	iPos = iPos + FrameCmdSize1B;

	// ����
	memcpy(&m_usCommand, &m_pFrameData[iPos], FramePacketSize2B);
	iPos = iPos + FramePacketSize2B;

	// �����ָ���
	memcpy(&m_usCommandCount, &m_pFrameData[iPos], FramePacketSize2B);
	iPos = iPos + FramePacketSize2B;

	// ����������Ϊ֡���ȼ�ȥ֮ǰ����Ⱥ�����У��λ��֡β
	m_usDataSize = (unsigned short)(m_usFrameSize - iPos - FrameCmdSize1B - FramePacketSize2B);

	return true;
}

/**
* ����������
* @param void
* @return bool true���ɹ���false��ʧ��
*/
bool CFrameInterface::ParseCommandWord(int iPos)
{
	if(0 == m_usCommandCount)
	{
		return true;
	}
	switch(m_usCommand)
	{
	case FieldCmd:	// ����	1-Field ON/OFF		
		m_byFieldOperation = m_pFrameData[iPos];	// Field ON/OFF
		break;
		// @@@@@@@@@��ʱ������Ϳͻ��˽��漰������ص�����
// 	case FormLineCmd:	// ����	2-FormLine				
// 		memcpy(&m_uiSN, &m_pFrameData[iPos], FramePacketSize4B);	// �����豸��
// 		break;
// 
// 	case LookCmd:	// ����	3-Look		
// 		memcpy(&m_uiLookAuto, &m_pFrameData[iPos], FramePacketSize4B);	// �Ƿ��Զ�����
// 		iPos = iPos + FramePacketSize4B;		
// 		memcpy(&m_uiTestResistance, &m_pFrameData[iPos], FramePacketSize4B);	// �������Ƿ����Resistance
// 		iPos = iPos + FramePacketSize4B;		
// 		memcpy(&m_uiTestTilt, &m_pFrameData[iPos], FramePacketSize4B);	// �������Ƿ����Tilt
// 		iPos = iPos + FramePacketSize4B;		
// 		memcpy(&m_uiTestLeakage, &m_pFrameData[iPos], FramePacketSize4B);	// �������Ƿ����Leakage
// 		break;
// 
// 	case InstrumentTestCmd:	// ����	4-Test From InstrumentTestSetup
// 		memcpy(&m_uiTestNb, &m_pFrameData[iPos], FramePacketSize4B);	// ����������
// 		m_uiTestNb = m_uiTestNb + 1000;
// 		break;
// 
// 	case SensorTestCmd:	// ����	5-Test From SensorTestSetup
// 		memcpy(&m_uiTestNb, &m_pFrameData[iPos], FramePacketSize4B);	// ����������
// 		m_uiTestNb = m_uiTestNb + 2000;
// 		break;
// 
// 	case MultipleTestCmd:	// ����	6-Test From MultipleTestSetup
// 		memcpy(&m_uiTestNb, &m_pFrameData[iPos], FramePacketSize4B);	// ����������
// 		m_uiTestNb = m_uiTestNb + 3000;
// 		break;
// 
// 	case SeismonitorTestCmd:	// ����	7-Test From SeismonitorTestSetup
// 		// @@@@@@@@@���ɳ���
// //		iPos = iPos + 1;
// 		memcpy(&m_uiTestNb, &m_pFrameData[iPos], FramePacketSize4B);	// ����������
// 		break;
// 
// 	case InstrumentViewTestCmd:	// ����	8-Test From InstrumentView ����������ͼ�ġ�GO����ť
// 	case SensorTestViewTestCmd:	// ����	9-Test From SensorTestView	���Լ첨����ͼ�ġ�GO����ť
// 		memcpy(&m_uiTestAim, &m_pFrameData[iPos], FramePacketSize4B);	// ���Զ���	1-������2-�첨��
// 		iPos = iPos + FramePacketSize4B;
// 		memcpy(&m_uiTestType, &m_pFrameData[iPos], FramePacketSize4B);	// ��������
// 		iPos = iPos + FramePacketSize4B;
// 		m_strTestAbsoluteSpread = &m_pFrameData[iPos];	// �������ж���
// 		break;
// 
// 	case SeismonitoViewTestCmd:	// ����	10-Test From SeismonitoView
// 		m_byTestOperation = m_pFrameData[iPos];	// 1-�������ԣ�0-ֹͣ����
// 		iPos = iPos + FrameCmdSize1B;
// 		m_strTestAbsoluteSpread = &m_pFrameData[iPos];	// �������ж���
// 		break;
// 		// @@@@@@@@@��ʱ������Ϳͻ��˽����������
// 	case 20:	// ����	20-���������ļ���������
// 		memcpy(&m_uiChangeAim, &m_pFrameData[iPos], FramePacketSize4B);	// ���ĵ�Ŀ��
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
	int iPos = 0;
	int iPosFrameSize = 0;
	// ֡ͷ{0xEB90}
	m_pFrameData[iPos] = FrameHeadHigh;
	iPos += FrameCmdSize1B;
	m_pFrameData[iPos] = FrameHeadLow;
	iPos += FrameCmdSize1B;
	// ֡����
	iPosFrameSize = iPos;
	iPos += FramePacketSize2B;
	// ֡����
	memcpy(&m_pFrameData[iPos], &m_pFrameInterface->m_uiFrameCount, FramePacketSize4B);
	iPos += FramePacketSize4B;
	// ֡���� 0xFF-����֡
	m_pFrameData[iPos] = FrameTypeReturnCmd;
	iPos += FrameCmdSize1B;
	// ����
	memcpy(&m_pFrameData[iPos], &m_pFrameInterface->m_usCommand, FramePacketSize2B);
	iPos += FramePacketSize2B;
	// �����ָ���
	m_usCommandCount = 0;
	memcpy(&m_pFrameData[iPos], &m_pFrameInterface->m_usCommandCount, FramePacketSize2B);
	iPos += FramePacketSize2B;
	// У��λ
	m_pFrameData[iPos] = SndFrameBufInit;
	iPos += FrameCmdSize1B;
	// ֡β{0x146F}
	m_pFrameData[iPos] = FrameTailHigh;
	iPos += FrameCmdSize1B;
	m_pFrameData[iPos] = FrameTailLow;
	iPos += FrameCmdSize1B;
	m_usFrameSize = (unsigned short)iPos;
	memcpy(&m_pFrameData[iPosFrameSize], &m_usFrameSize, FramePacketSize2B);
}

/**
* �����ֳ��������֪ͨ����֡
* @param void
* @return void
*/
void CFrameInterface::MakeSiteDataOutputCmdFrame()
{
	// @@@@@@@@@@@@@@@@@@@@@@@@@@@@û����
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

// /**
// * ���ɲ�������֡
// * @param unsigned int uiTestType ��������
// * @param unsigned unsigned int uiDataSize ÿ����������ռ���ֽ���
// * @paramunsigned short usDataCount �������ݸ���
// * @paramunsigned byte pData ��������
// * @return void
// */
// void CFrameInterface::CreateOutputDataFrameTest(unsigned int uiTestType, unsigned int uiDataSize, unsigned short usDataCount, byte* pData)
// {
// 	unsigned short usDataLength = (unsigned short)(uiDataSize * usDataCount);
// 	m_usFrameSize = 16 + usDataLength;
// 	// ֡ͷ{0xEB90}
// 	m_pFrameData[0] = 0xEB;
// 	m_pFrameData[1] = 0x90;
// 	// ֡����
// 	memcpy(&m_pFrameData[2], &m_usFrameSize, 2);
// 	// ֡����
// 	UINT iNow = GetTickCount();
// 	memcpy(&m_pFrameData[4], &iNow, 4);
// 	// ֡���� 0x03-����֡����Ҫ�����֡
// 	m_pFrameData[8] = 0x03;
// 	// ����
// 	m_usCommand = 200 + (unsigned short)uiTestType;
// 	memcpy(&m_pFrameData[9], &m_usCommand, 2);
// 	// �����ָ���
// 	m_usCommandCount = usDataCount;
// 	memcpy(&m_pFrameData[11], &m_usCommandCount, 2);
// 
// 	int iPos = 13;
// 	// ��������
// 	memcpy(&m_pFrameData[iPos], pData, usDataLength);
// 	iPos = iPos + usDataLength;
// 	// У��λ
// 	m_pFrameData[iPos] = 0x00;
// 	iPos = iPos + 1;
// 	// ֡β{0x146F}
// 	m_pFrameData[iPos] = 0x14;
// 	iPos = iPos + 1;
// 	m_pFrameData[iPos] = 0x6F;
// }