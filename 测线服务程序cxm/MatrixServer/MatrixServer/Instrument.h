#pragma once

/**
*@brief ������
*/
class CInstrument
{
public:
	CInstrument();
	~CInstrument();

public: //����
	/** �����������е�λ��*/
	unsigned int m_uiIndex;

	/** �����Ƿ�ʹ����*/
	bool m_bInUsed;

	/** �����豸��*/
	unsigned int m_uiSN;
	/** �������� 1-����վ��2-��Դվ��3-�ɼ�վ*/
	unsigned int m_uiInstrumentType;

	/** ����IP��ַ*/
	unsigned int m_uiIP;
	/** ����·��IP��ַ*/
	unsigned int m_uiRoutIP;
	/** ·�ɷ��� 1-�ϣ�2-�£�3-��4��*/
	unsigned int m_uiRoutDirection;
	/** ·�ɵ�ַ �����߷��� �Ϸ�*/
	unsigned int m_uiRoutIPTop;
	/** ·�ɵ�ַ �����߷��� �·�*/
	unsigned int m_uiRoutIPDown;
	/** ·�ɵ�ַ �����߷��� ��*/
	unsigned int m_uiRoutIPLeft;
	/** ·�ɵ�ַ �����߷��� �ҷ�*/
	unsigned int m_uiRoutIPRight;

// 	/** ���ӵ���һ��������վ*/
// 	CInstrument* m_pMainCrossNext;
// 	/** ���ӵ���һ��������վ*/
// 	CInstrument* m_pMainCrossPreview;
// 	/** ���ӵĽ���վ �Ϸ�*/
// 	CInstrument* m_pCrossTop;
// 	/** ���ӵĽ���վ �·�*/
// 	CInstrument* m_pCrossDown;
	/** ���ӵ����� �Ϸ�*/
	CInstrument* m_pInstrumentTop;
	/** ���ӵ����� �·�*/
	CInstrument* m_pInstrumentDown;
	/** ���ӵ����� ��*/
	CInstrument* m_pInstrumentLeft;
	/** ���ӵ����� �ҷ�*/
	CInstrument* m_pInstrumentRight;

// 	/** ���ӵ���һ��������վ*/
// 	unsigned int m_uiSNMainCrossNext;
// 	/** ���ӵ���һ��������վ*/
// 	unsigned int m_uiSNMainCrossPreview;
// 	/** ���ӵĽ���վ �Ϸ�*/
// 	unsigned int m_uiSNCrossTop;
// 	/** ���ӵĽ���վ �·�*/
// 	unsigned int m_uiSNCrossDown;
// 	/** ���ӵ����� ��*/
// 	unsigned int m_uiSNInstrumentLeft;
// 	/** ���ӵ����� �ҷ�*/
// 	unsigned int m_uiSNInstrumentRight;

// 	/** ���ӵ���һ��������վ*/
// 	int m_iIndexMainCrossNext;
// 	/** ���ӵ���һ��������վ*/
// 	int m_iIndexMainCrossPreview;
// 	/** ���ӵĽ���վ �Ϸ�*/
// 	int m_iIndexCrossTop;
// 	/** ���ӵĽ���վ �·�*/
// 	int m_iIndexCrossDown;
// 	/** ���ӵ����� ��*/
// 	int m_iIndexInstrumentLeft;
// 	/** ���ӵ����� �ҷ�*/
// 	int m_iIndexInstrumentRight;

	/** �װ�ʱ��*/
	unsigned int m_uiTimeHeadFrame;
	/** β������*/
	unsigned int m_uiTailFrameCount;
	/** ����ʱ��*/
	unsigned int m_uiTimeDelay;
	/** ��������ϵͳʱ��*/
	unsigned int m_uiTimeSystem;
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

	// �ɼ�վ���Դվ�Ĺ㲥�˿�
	unsigned int m_uiBroadCastPort;
// 	/** ����*/
// 	unsigned int m_uiLineNb;
// 	/** ���*/
// 	unsigned int m_uiPointNb;
// 	/** ���*/
// 	unsigned int m_uiChannelNb;

	/** �Ƿ�������*/
	bool m_bJumpedChannel;
	/** �Ƿ����Ӽ첨��*/
	bool m_bSensor;

// 	/** ����IP��ַ����ʱ��*/
// 	unsigned int m_uiIPDistributeTime;	

	/** �Ƿ�����*/
	bool m_bAux;
// 	/** ���������ʱ��*/
// 	unsigned int m_uiAuxTime;

	/** �Ƿ����ӱ�ը��*/
	bool m_bBlastMachine;
// 	/** ��ը�����ʱ��*/
// 	unsigned int m_uiBlastMachineTime;

	/** �Ƿ��ػص�*/
	bool m_bDetour;
	/** �Ƿ��ػص��Ͷ˱�ǵ�*/
	bool m_bDetourMarkerLow;
	/** �Ƿ��ػص��߶˱�ǵ�*/
	bool m_bDetourMarkerHigh;
	/** �Ƿ��ػص�ֹͣ���*/
	unsigned int m_uiStopMarking;
// 	/** �ػص����ʱ��*/
// 	unsigned int m_uiDetourLogoTime;
// 	/** �ػص����ʱ��*/
// 	unsigned int m_uiDetourTime;

	/** �Ƿ��ǵ�*/
	bool m_bMarker;
// 	/** ��ǵ���ʱ��*/
// 	unsigned int m_uiMarkerLogoTime;
// 	/** ��ǵ���ʱ��*/
// 	unsigned int m_uiMarkerTime;
	// �װ�λ���ȶ�����
	int m_iHeadFrameStableNum;

	/** �ڼ�������IP��ַ*/
	int m_iIPSetCount;
	/** IP��ַ�����Ƿ�ɹ�*/
	bool m_bIPSetOK;

	/** �ڼ���β��ʱ�̲�ѯ*/
	int m_iTailTimeQueryCount;
	/** β��ʱ�̲�ѯ�Ƿ�ɹ�*/
	bool m_bTailTimeQueryOK;

	/** ����ʱ��������λ*/
	unsigned int m_uiTimeHigh;
	/** ����ʱ��������λ*/
	unsigned int m_uiTimeLow;
	/** �ڼ�����������ʱ��*/
	int m_iTimeSetCount;
	/** ����ʱ�������Ƿ�ɹ�*/
	bool m_bTimeSetOK;

// 	/** ������ɾ��ʱ��ɾ������ 1-�ϣ�2-�£�3-��4��*/
// 	unsigned int m_uiDeleteDirection;

	/** ������������ֵ*/
	float m_fNoiseValue;
	/** �����������Խ�� 0��δ���ԣ�1�����Ժϸ�2�����Բ��ϸ�3�����źţ�4��δ�ж�*/
	byte m_byNoiseCheck;

	/** �����������ֵ*/
	float m_fDistortionValue;
	/** ����������Խ�� 0��δ���ԣ�1�����Ժϸ�2�����Բ��ϸ�3�����źţ�4��δ�ж�*/
	byte m_byDistortionCheck;

	/** ������������ֵ*/
	float m_fCrosstalkValue;
	/** �����������Խ�� 0��δ���ԣ�1�����Ժϸ�2�����Բ��ϸ�3�����źţ�4��δ�ж�*/
	byte m_byCrosstalkCheck;

	/** �����������ֵ*/
	float m_fGainValue;
	/** ����������Խ�� 0��δ���ԣ�1�����Ժϸ�2�����Բ��ϸ�3�����źţ�4��δ�ж�*/
	byte m_byGainCheck;
	/** ������λ����ֵ*/
	float m_fPhaseValue;
	/** ������λ���Խ�� 0��δ���ԣ�1�����Ժϸ�2�����Բ��ϸ�3�����źţ�4��δ�ж�*/
	byte m_byPhaseCheck;
	/** �����������λ���Խ�� 0��δ���ԣ�1�����Ժϸ�2�����Բ��ϸ�3�����źţ�4��δ�ж�*/
	byte m_byGainAndPhaseCheck;

	/** ������ģ����ֵ*/
	float m_fCMRRValue;
	/** ������ģ���Խ�� 0��δ���ԣ�1�����Ժϸ�2�����Բ��ϸ�3�����źţ�4��δ�ж�*/
	byte m_byCMRRCheck;

	/** �������Խ�� 0��δ���ԣ�1�����Ժϸ�2�����Բ��ϸ�3�����źţ�4��δ�ж�*/
	byte m_byCheck;

public: //����
	// ����
	void OnReset();
	// �õ����ӵ���һ������
	CInstrument* GetNextInstrument(unsigned int uiRoutDirection);
// 	// �õ��ɼ�վ
// 	CInstrument* GetInstrumentCollect(unsigned int uiRoutDirection);
// 	// �������ý���վβ������ʱ��
// 	void ResetInstrumentCrossTailFrameReceiveTime(unsigned int uiRoutDirection);
// 	// ��������β�����ա�����ʱ�̣����θ�2λ
// 	void ResetInstrumentTailFrameTime();
// 	// ���ݷ���õ�����վ·�ɵ�ַ
// 	unsigned int GetRoutIPByRoutDirection(unsigned int uiRoutDirection);
// 	// ���ݷ������ý���վ·�ɵ�ַ
// 	void SetRoutIPByRoutDirection(unsigned int uiRoutIP, unsigned int uiRoutDirection);

	// �����Խ��
	void CheckResultAll();
};