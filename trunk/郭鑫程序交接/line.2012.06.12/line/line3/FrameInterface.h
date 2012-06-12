#pragma once

class CFrameInterface
{

// ֡���壺֡ͷ{0xEB90}(2) + ֡����(2) + ֡����(4) + ֡����(1) + ����(2) + �����ָ���(2) + ������( ) + У��λ(1) + ֡β{0x146F}(2)
// ֡����Ϊ֡ͷ��֡β���ֽ���
public:
	CFrameInterface();
	~CFrameInterface();

public: // ����
	/** ֡����*/
	byte m_pFrameData[65536];

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
	unsigned int m_uiSN;	// �����豸��

	// ����	3-Look
	UINT m_uiLookAuto;	// �Ƿ��Զ�����
	UINT m_uiTestResistance;	// �������Ƿ����Resistance
	UINT m_uiTestTilt;	// �������Ƿ����Tilt
	UINT m_uiTestLeakage;	// �������Ƿ����Leakage

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
	//////////////////////////////////////////////////////////////////////////
	// ����	20-���������ļ���������
	// ���ĵ�Ŀ��	1-SurveySetup��ApplyAll��2-SurveySetup��ApplySensor
	// ���ĵ�Ŀ��	11-LayoutSetup��ApplyBlast��12-LayoutSetup��ApplyMarkers��13-LayoutSetup��ApplyAux��14-LayoutSetup��ApplyDetour��15-LayoutSetup��ApplyMute
	// ���ĵ�Ŀ��	21-LookSetup��Apply
	// ���ĵ�Ŀ��	31-TestSetup��ApplyInstrument��32-TestSetup��ApplySensor��33-TestSetup��ApplyMultiple��34-TestSetup��ApplySeisMonitor
	// ���ĵ�Ŀ��	41-TestBaseSetup��ApplyInstrumentTestBase��42-TestBaseSetup��ApplySensorTestBase
	// ���ĵ�Ŀ��	51-TestBaseSetup��ApplyInstrumentTestLimit��52-TestBaseSetup��ApplySensorTestLimit
	// ���ĵ�Ŀ��	61-SpreadSetup��ApplySpreadSetupDataForAbsolute��62-SpreadSetup��ApplySpreadSetupDataForGeneric
	/** ���ĵ�Ŀ��*/
	unsigned int m_uiChangeAim;


public: // ����
	// ���ö���
	void Reset();
	// ����֡ͷ
	bool ParseFrameHead();
	// ����������
	bool ParseCommandWord();
	// ����Ӧ��֡
	void MakeReplyFrame(CFrameInterface* m_pFrameInterface);

	// �����ֳ��������֪ͨ����֡
	void MakeSiteDataOutputCmdFrame(unsigned int uiChangeAim);

	// ����Field On/Off֡
	void MakeFieldFrame();

	// ����FormLine֡
	void MakeFormLineFrame(unsigned int uiSN);

	// ���ɲ�������֡���������öԻ���GO��ť
	void MakeTestCmdFrameForTestSetup(unsigned short usCommand, UINT uiTestNb);

	// ���ɲ�������֡����Ӧ�������첨��ͼ����ͼ����GO��ť
	void MakeTestCmdFrameForGraphViewGOButton(unsigned int uiTestAim, unsigned int uiTestType, CString strTestAbsoluteSpread);
	// ���ɲ�������֡����Ӧ�������ͼ����ͼSeismonitor��ť
	void MakeTestCmdFrameForGraphViewSeismonitorButton(byte byTestOperation, CString strTestAbsoluteSpread);
};
