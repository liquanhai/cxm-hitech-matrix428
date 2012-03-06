
#ifdef MATRIXSERVERDLL_EXPORTS
#define MATRIXSERVERDLL_API __declspec(dllexport)
#define MatrixServerDll_API extern "C" __declspec(dllexport)
#else
#define MATRIXSERVERDLL_API __declspec(dllimport)
#define MatrixServerDll_API extern "C" __declspec(dllimport)
#endif

#ifndef   _Instrument_H
#define   _Instrument_H

// �������Խṹ��
typedef struct Instrument_Struct 
{
	/** �����������е�λ��*/
	unsigned int m_uiIndex;
	/** �����Ƿ�ʹ����*/
	bool m_bInUsed;
	/** �����豸��*/
	unsigned int m_uiSN;
	/** �������� 1-����վ��2-��Դվ��3-�ɼ�վ��4-LCI*/
	int m_iInstrumentType;
	/** ����IP��ַ*/
	unsigned int m_uiIP;
	/** ����·��IP��ַ*/
	unsigned int m_uiRoutIP;
	/** ·�ɷ��� 1-�ϣ�2-�£�3-��4��*/
	int m_iRoutDirection;
	/** ·�ɵ�ַ �����߷��� �Ϸ�*/
	unsigned int m_uiRoutIPTop;
	/** ·�ɵ�ַ �����߷��� �·�*/
	unsigned int m_uiRoutIPDown;
	/** ·�ɵ�ַ �����߷��� ��*/
	unsigned int m_uiRoutIPLeft;
	/** ·�ɵ�ַ �����߷��� �ҷ�*/
	unsigned int m_uiRoutIPRight;
	/** ·�ɿ���*/
	byte m_byLAUXRoutOpenSet;
	/** ���ӵ����� �Ϸ�*/
	Instrument_Struct* m_pInstrumentTop;
	/** ���ӵ����� �·�*/
	Instrument_Struct* m_pInstrumentDown;
	/** ���ӵ����� ��*/
	Instrument_Struct* m_pInstrumentLeft;
	/** ���ӵ����� �ҷ�*/
	Instrument_Struct* m_pInstrumentRight;
	/** �װ�ʱ��*/
	unsigned int m_uiTimeHeadFrame;
	// 	/** β��ʱ��*/
	// 	unsigned int m_uiTailSysTime;
	/** β������*/
	int m_iTailFrameCount;
	/** ����ʱ��*/
	unsigned int m_uiDelayTime;
	/** ��������ϵͳʱ��*/
	unsigned int m_uiSystemTime;
	/** ��������ʱ��*/
	unsigned int m_uiNetTime;
	/** ��������״̬*/
	unsigned int m_uiNetState;
	/** ������������1*/
	unsigned int m_uiNetOrder;
	/** 16bitsʱ�䣬����ʱ�̵�λ*/
	unsigned short m_usReceiveTime;	
	/** 16bitsʱ�䣬����ʱ�̵�λ*/
	unsigned short m_usSendTime;
	/** 16bits ���߷�������β������ʱ��*/
	unsigned short m_usLineLeftReceiveTime;	
	/** 16bits ���߷�������β������ʱ��*/
	unsigned short m_usLineRightReceiveTime;	
	/** 16bits �����߷�������β������ʱ��*/
	unsigned short m_usCrossTopReceiveTime;	
	/** 16bits �����߷�����β������ʱ��*/
	unsigned short m_usCrossDownReceiveTime;	
	/** �ɼ�վ���Դվ�Ĺ㲥�˿�*/
	unsigned int m_uiBroadCastPort;
	/** ����*/
	int m_iLineNb;
	/** ����*/
	int m_iPointIndex;
	/** ��ǵ��*/
	unsigned int m_uiPointNb;
	// 	/** ���*/
	// 	unsigned int m_uiChannelNb;
	/** �Ƿ�������*/
	bool m_bJumpedChannel;
	/** �Ƿ����Ӽ첨��*/
	bool m_bSensor;
	/** �Ƿ�����*/
	bool m_bAux;
	/** �Ƿ����ӱ�ը��*/
	bool m_bBlastMachine;
	/** �Ƿ��ػص�*/
	bool m_bDetour;
	/** �Ƿ��ػص��Ͷ˱�ǵ�*/
	bool m_bDetourMarkerLow;
	/** �Ƿ��ػص��߶˱�ǵ�*/
	bool m_bDetourMarkerHigh;
	/** �Ƿ��ػص�ֹͣ���*/
	unsigned int m_uiStopMarking;
	/** �Ƿ��ǵ�*/
	bool m_bMarker;
	// �װ�λ���ȶ�����
	int m_iHeadFrameStableNum;
	/** �ڼ�������IP��ַ*/
	int m_iIPSetCount;
	/** IP��ַ�����Ƿ�ɹ�*/
	bool m_bIPSetOK;
	/** �ڼ���β��ʱ�̲�ѯ*/
	int m_iTailTimeQueryCount;
	/** β��ʱ�̲�ѯӦ�����*/
	int m_iTailTimeReturnCount;
	/** β��ʱ�̲�ѯ�Ƿ�ɹ�*/
	bool m_bTailTimeQueryOK;
	/** ����ʱ��������λ*/
	unsigned int m_uiTimeHigh;
	/** ����ʱ��������λ*/
	unsigned int m_uiTimeLow;
	/** �ڼ�����������ʱ��*/
	int m_iTimeSetCount;
	/** ����ʱͳ�ɹ�����*/
	int m_iTimeSetReturnCount;
	/** ����ʱ�������Ƿ�ɹ�*/
	bool m_bTimeSetOK;
	// ADC���������Ƿ�Ӧ��
	bool m_bADCSetReturn;
	// �����Ƿ������ADC��������
	bool m_bADCSet;
	// ������ʼADC���ݲɼ����óɹ�
	bool m_bADCStartSample;
	// ����ֹͣADC���ݲɼ����óɹ�
	bool m_bADCStopSample;
	// �����ѯ����֡��
	unsigned int m_uiErrorCodeQueryNum;
	// �����ѯӦ��֡��
	unsigned int m_uiErrorCodeReturnNum;
	// �ɼ�վ�͵�Դվ�������ݴ������
	int m_iFDUErrorCodeDataCount;
	// �ɼ�վ�͵�Դվ����������
	int m_iFDUErrorCodeCmdCount;
	// �ɼ�վ�͵�Դվ�������ݴ������
	char m_byFDUErrorCodeDataCountOld;
	// �ɼ�վ�͵�Դվ����������
	char m_byFDUErrorCodeCmdCountOld;

	// ����վ����A���ݹ���
	int m_iLAUXErrorCodeDataLineACount;
	// ����վ����B���ݹ���
	int m_iLAUXErrorCodeDataLineBCount;
	// ����վ������A���ݹ���
	int m_iLAUXErrorCodeDataLAUXLineACount;
	// ����վ������B���ݹ���
	int m_iLAUXErrorCodeDataLAUXLineBCount;
	// ����վ����ڹ���
	int m_iLAUXErrorCodeCmdCount;

	// ����վ����A���ݹ���
	char m_byLAUXErrorCodeDataLineACountOld;
	// ����վ����B���ݹ���
	char m_byLAUXErrorCodeDataLineBCountOld;
	// ����վ������A���ݹ���
	char m_byLAUXErrorCodeDataLAUXLineACountOld;
	// ����վ������B���ݹ���
	char m_byLAUXErrorCodeDataLAUXLineBCountOld;
	// ����վ����ڹ���
	char m_byLAUXErrorCodeCmdCountOld;

	// ʵ�ʽ���ADC����֡�������ط�֡��
	unsigned int m_uiADCDataActualRecFrameNum;
	// �ط���ѯ֡�õ���Ӧ��֡��
	unsigned int m_uiADCDataRetransmissionFrameNum;
	// Ӧ�ý���ADC����֡��������֡��
	unsigned int m_uiADCDataShouldRecFrameNum;
	// ADC����֡��ָ��ƫ����
	unsigned short m_usADCDataFramePoint;
	// ADC����֡����ʱ�ı���ʱ��
	unsigned int m_uiADCDataFrameSysTime;
	// ADC����֡��ʼ֡��
	int m_iADCDataFrameStartNum;
}m_oInstrumentStruct;

#endif