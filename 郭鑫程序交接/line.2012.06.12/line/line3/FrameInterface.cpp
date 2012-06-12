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
* ����֡ͷ
* @param void
* @return bool true���ɹ���false��ʧ��
*/
bool CFrameInterface::ParseFrameHead()
{
	unsigned short iPos = 0;
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
	case 101:	// ���� 101-Server Field ON/OFF
		m_byFieldOperation = m_pData[iPos];	// Field ON/OFF
		break;
	}
	return true;
}

/**
* ����Ӧ��֡
* @param CFrameInterface* m_pFrameInterface �յ�֡
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
* @param unsigned int uiChangeAim ���Ŀ��
* @return void
*/
void CFrameInterface::MakeSiteDataOutputCmdFrame(unsigned int uiChangeAim)
{
	m_uiChangeAim = uiChangeAim;

	m_usFrameSize = 20;
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
	m_usCommand = 20;
	memcpy(&m_pFrameData[9], &m_usCommand, 2);
	// �����ָ���
	m_usCommandCount = 1;
	memcpy(&m_pFrameData[11], &m_usCommandCount, 2);

	int iPos = 13;
	memcpy(&m_pFrameData[iPos], &m_uiChangeAim, 4);
	iPos = iPos + 4;
	// У��λ
	m_pFrameData[iPos] = 0x00;
	iPos = iPos + 1;
	// ֡β{0x146F}
	m_pFrameData[iPos] = 0x14;
	iPos = iPos + 1;
	m_pFrameData[iPos] = 0x6F;
}

/**
* ����Field On/Off֡
* @param void
* @return void
*/
void CFrameInterface::MakeFieldFrame()
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
	// ����	1-Field ON/OFF
	m_usCommand = 1;
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
* ����FormLine֡
* @param unsigned int uiSN ����SN��
* @return void
*/
void CFrameInterface::MakeFormLineFrame(unsigned int uiSN)
{
	m_usFrameSize = 20;
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
	m_usCommand = 2;
	memcpy(&m_pFrameData[9], &m_usCommand, 2);
	// �����ָ���
	m_usCommandCount = 1;
	memcpy(&m_pFrameData[11], &m_usCommandCount, 2);

	int iPos = 13;
	memcpy(&m_pFrameData[iPos], &uiSN, 4);
	iPos = iPos + 4;

	// У��λ
	m_pFrameData[iPos] = 0x00;
	iPos = iPos + 1;
	// ֡β{0x146F}
	m_pFrameData[iPos] = 0x14;
	iPos = iPos + 1;
	m_pFrameData[iPos] = 0x6F;
}

/**
* ���ɲ�������֡���������öԻ���GO��ť
* @param unsigned short usCommand ���� 4-Test From InstrumentTestSetup��5-Test From SensorTestSetup��6-Test From MultipleTestSetup��7-Test From SeismonitorTestSetup
* @param UINT uiTestNb ����������
* @return void
*/
void CFrameInterface::MakeTestCmdFrameForTestSetup(unsigned short usCommand, UINT uiTestNb)
{
	m_usFrameSize = 20;
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
	m_usCommand = usCommand;
	memcpy(&m_pFrameData[9], &m_usCommand, 2);
	// �����ָ���
	m_usCommandCount = 1;
	memcpy(&m_pFrameData[11], &m_usCommandCount, 2);

	int iPos = 13;
	memcpy(&m_pFrameData[iPos], &uiTestNb, 4);
	iPos = iPos + 4;
	// У��λ
	m_pFrameData[iPos] = 0x00;
	iPos = iPos + 1;
	// ֡β{0x146F}
	m_pFrameData[iPos] = 0x14;
	iPos = iPos + 1;
	m_pFrameData[iPos] = 0x6F;
}

/**
* ���ɲ�������֡����Ӧ�������첨��ͼ����ͼ����GO��ť
* @param unsigned unsigned int uiTestAim ���Զ���	1-������2-�첨��
* @param unsigned unsigned int uiTestType ��������
* @param unsigned CString strTestAbsoluteSpread �������ж���
* @return void
*/
void CFrameInterface::MakeTestCmdFrameForGraphViewGOButton(unsigned int uiTestAim, unsigned int uiTestType, CString strTestAbsoluteSpread)
{	
	int iSizeAbsoluteSpread = strTestAbsoluteSpread.GetLength();

	m_usFrameSize = 26 + (unsigned short)iSizeAbsoluteSpread;
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
	if(1 == uiTestAim)
	{
		// ����
		m_usCommand = 8;	// ����	8-Test From InstrumentView ����������ͼ�ġ�GO����ť
	}
	else if(2 == uiTestAim)
	{
		// ����
		m_usCommand = 9;	// ����	9-Test From SensorTestView	���Լ첨����ͼ�ġ�GO����ť
	}

	memcpy(&m_pFrameData[9], &m_usCommand, 2);
	// �����ָ���
	m_usCommandCount = 1;
	memcpy(&m_pFrameData[11], &m_usCommandCount, 2);

	int iPos = 13;
	memcpy(&m_pFrameData[iPos], &uiTestAim, 4);
	iPos = iPos + 4;
	memcpy(&m_pFrameData[iPos], &uiTestType, 4);
	iPos = iPos + 4;
	memcpy(&m_pFrameData[iPos], strTestAbsoluteSpread.GetBuffer(), iSizeAbsoluteSpread);
	iPos = iPos + iSizeAbsoluteSpread;
	m_pFrameData[iPos] = 0;
	iPos = iPos + 1;
	m_pFrameData[iPos] = 0;
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
* ���ɲ�������֡����Ӧ�������ͼ����ͼSeismonitor��ť
* @param byte byTestOperation ���� 1-�������ԣ�0-ֹͣ����
* @param unsigned CString strTestAbsoluteSpread �������ж���
* @return void
*/
void CFrameInterface::MakeTestCmdFrameForGraphViewSeismonitorButton(byte byTestOperation, CString strTestAbsoluteSpread)
{	
	int iSizeAbsoluteSpread = strTestAbsoluteSpread.GetLength();

	m_usFrameSize = 19 + (unsigned short)iSizeAbsoluteSpread;
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
	m_usCommand = 10;	// ����	10-Test From SeismonitorView	���������������ͼ�ġ�Seismonitor����ť

	memcpy(&m_pFrameData[9], &m_usCommand, 2);
	// �����ָ���
	m_usCommandCount = 1;
	memcpy(&m_pFrameData[11], &m_usCommandCount, 2);

	int iPos = 13;
	m_pFrameData[iPos] = byTestOperation;
	iPos = iPos + 1;

	memcpy(&m_pFrameData[iPos], strTestAbsoluteSpread.GetBuffer(), iSizeAbsoluteSpread);
	iPos = iPos + iSizeAbsoluteSpread;
	m_pFrameData[iPos] = 0;
	iPos = iPos + 1;
	m_pFrameData[iPos] = 0;
	iPos = iPos + 1;
	// У��λ
	m_pFrameData[iPos] = 0x00;
	iPos = iPos + 1;
	// ֡β{0x146F}
	m_pFrameData[iPos] = 0x14;
	iPos = iPos + 1;
	m_pFrameData[iPos] = 0x6F;
}