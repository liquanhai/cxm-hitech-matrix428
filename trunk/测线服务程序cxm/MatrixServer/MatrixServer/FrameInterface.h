#pragma once
#include "Parameter.h"
/**
*@brief �������Ϳͻ���֮����Ϣ��������֡��
*
@note ֡���壺֡ͷ{0xEB90}(2) + ֡����(2) + ֡����(4) + ֡����(1) + ����(2) + �����ָ���(2) + ������( ) + У��λ(1) + ֡β{0x146F}(2)
@note ֡����Ϊ֡ͷ��֡β���ֽ���
@note ֡���ͣ�0x01-����֡����Ҫ�����֡��0x02-����֡��Ҫ�����֡��0x03-����֡����Ҫ�����֡��0x04-����֡��Ҫ�����֡��0xFF-����֡
@note 
@note ���Կͻ��˵����
@note ���� 1-Field ON/OFF�����ݸ���Ϊ1
@note ���� 2-FormLine�����ݸ���Ϊ1
@note ���� 3-Look�����ݸ���Ϊ1
@note ���� 4-Test From InstrumentTestSetup�����ݸ���Ϊ1
@note ���� 5-Test From SensorTestSetup�����ݸ���Ϊ1
@note ���� 6-Test From MultipleTestSetup�����ݸ���Ϊ1
@note ���� 7-Test From SeismonitorTestSetup�����ݸ���Ϊ1
@note ���� 8-Test From InstrumentView ����������ͼ�ġ�GO����ť�����ݸ���Ϊ1
@note ���� 9-Test From SensorTestView	���Լ첨����ͼ�ġ�GO����ť�����ݸ���Ϊ1
@note ���� 10-Test From SeismonitorView�����ݸ���Ϊ1
@note ���� 20-���������ļ�����������ݸ���Ϊ1
@note ���ĵ�Ŀ�� 1-SurveySetup��ApplyAll��2-SurveySetup��ApplySensor
@note ���ĵ�Ŀ�� 11-LayoutSetup��ApplyBlast��12-LayoutSetup��ApplyMarkers��13-LayoutSetup��ApplyAux��14-LayoutSetup��ApplyDetour��15-LayoutSetup��ApplyMute
@note ���ĵ�Ŀ�� 21-LookSetup��Apply
@note ���ĵ�Ŀ�� 31-TestSetup��ApplyInstrument��32-TestSetup��ApplySensor��33-TestSetup��ApplyMultiple��34-TestSetup��ApplySeisMonitor
@note ���ĵ�Ŀ�� 41-TestSetup��ApplyInstrumentTestBase��42-TestSetup��ApplySensorTestBase
@note ���ĵ�Ŀ�� 51-TestBaseSetup��ApplyInstrumentTestLimit��52-TestBaseSetup��ApplySensorTestLimit
@note ���ĵ�Ŀ�� 61-SpreadSetup��ApplySpreadSetupDataForAbsolute��62-SpreadSetup��ApplySpreadSetupDataForGeneric
@note 
@note �����ͻ��˵����
@note ���� 100-�ֳ�����������£����ݸ���Ϊ0
@note ���� 101-Server Field ON/OFF�����ݸ���Ϊ1
@note ���� 110-�ֳ�����������£����ݸ���Ϊ0
@note ���� (200+��������)-�ֳ�����������������ݸ���ΪN����������Ϊ1-22
*/
class CFrameInterface
{


public:
	CFrameInterface();
	~CFrameInterface();

public: // ����
	/** ֡����*/
	byte m_pFrameData[NetInterfaceBufSize];

	/** ԴIP��ַ*/
	CString m_strIPSource;
	/** Դ�˿ں�*/
	unsigned int  m_uiPortSource;
	/** Ŀ��IP��ַ*/
	CString m_strIPAim;
	/** Ŀ��˿ں�*/
	unsigned int  m_uiPortAim;

	/** ֡����*/
	unsigned short m_usFrameSize;
	/** ֡����*/
	unsigned int m_uiFrameCount;
	/** ֡���� 0x01-����֡����Ҫ�����֡��0x02-����֡��Ҫ�����֡��0x03-����֡����Ҫ�����֡��0x04-����֡��Ҫ�����֡��0xFF-����֡*/
	byte m_byFrameType;
	/** ����*/
	unsigned short m_usCommand;
	/** �����ָ���*/
	unsigned short m_usCommandCount;
	/** ����������*/
	unsigned short m_usDataSize;
	/** ������*/
	byte* m_pData;

	// ����	1-Field ON/OFF
	// ���� 101-Server Field ON/OFF
	/**	FieldON/OFF 0��OFF��1��ON*/
	byte m_byFieldOperation;

	// ����	2-FormLine
	/** �����豸��*/
	unsigned int m_uiSN;

	// ����	3-Look
	/** �Ƿ��Զ�����*/
	UINT m_uiLookAuto;
	/** �������Ƿ����Resistance*/
	UINT m_uiTestResistance;
	/** �������Ƿ����Tilt*/
	UINT m_uiTestTilt;
	/** �������Ƿ����Leakage*/
	UINT m_uiTestLeakage;

	// ����	4-Test From InstrumentTestSetup
	// ����	5-Test From SensorTestSetup
	// ����	6-Test From MultipleTestSetup
	// ����	7-Test From SeismonitorTestSetup
	/** ����������*/
	UINT m_uiTestNb;

	// ����	8-Test From InstrumentView ����������ͼ�ġ�GO����ť
	// ����	9-Test From SensorTestView	���Լ첨����ͼ�ġ�GO����ť	
	/** ���Զ��� 1-������2-�첨��*/
	unsigned int m_uiTestAim;
	/** ��������*/
	unsigned int m_uiTestType;
	// ����	10-Test From SeismonitorView
	/** Ұ������������ 1-�������ԣ�0-ֹͣ����*/
	byte m_byTestOperation;
	/** �������ж���*/
	CString m_strTestAbsoluteSpread;

	// ����	20-���������ļ���������
	// ���ĵ�Ŀ��	1-SurveySetup��ApplyAll��2-SurveySetup��ApplySensor
	// ���ĵ�Ŀ��	11-LayoutSetup��ApplyBlast��12-LayoutSetup��ApplyMarkers��13-LayoutSetup��ApplyAux��14-LayoutSetup��ApplyDetour��15-LayoutSetup��ApplyMute
	// ���ĵ�Ŀ��	21-LookSetup��Apply
	// ���ĵ�Ŀ��	31-TestSetup��ApplyInstrument��32-TestSetup��ApplySensor��33-TestSetup��ApplyMultiple��34-TestSetup��ApplySeisMonitor
	// ���ĵ�Ŀ��	41-TestSetup��ApplyInstrumentTestBase��42-TestSetup��ApplySensorTestBase
	// ���ĵ�Ŀ��	51-TestSetup��ApplyInstrumentTestLimit��52-TestSetup��ApplySensorTestLimit
	// ���ĵ�Ŀ��	61-SpreadSetup��ApplySpreadSetupDataForAbsolute��62-SpreadSetup��ApplySpreadSetupDataForGeneric
	/** ���ĵ�Ŀ��*/
	unsigned int m_uiChangeAim;

public: // ����
	// ����֡
	bool ParseFrame();
	// ����֡ͷ
	int ParseFrameHead();
	// ����������
	bool ParseCommandWord(int iPos);
	// ����Ӧ��֡
	void MakeReplyFrame(CFrameInterface* m_pFrameInterface);

	// �����ֳ��������֪ͨ����֡
	void MakeSiteDataOutputCmdFrame();
	// ����Server Field On/Off֡
	void MakeServerFieldFrame();
// 	// ���ɲ�������֡
// 	void CreateOutputDataFrameTest(unsigned int uiTestType, unsigned int uiDataSize, unsigned short usDataCount, byte* pData);

};
