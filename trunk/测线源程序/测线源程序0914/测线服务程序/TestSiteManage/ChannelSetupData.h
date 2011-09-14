#pragma once

/**
*@brief ���������
*/
class CChannelSetupData
{
public:
	CChannelSetupData();
	~CChannelSetupData();

public: // ����
	/** �ڲ�������е�λ��*/
	unsigned int m_uiIndex;

	/** ����Ƿ�ʹ����*/
	bool m_bInUsed;

	/** ���ߺ�*/
	unsigned int m_uiNbLine;
	/** ����*/
	unsigned int m_uiNbPoint;
	/** ���������*/
	unsigned int m_uiIndexPoint;
	/** �����*/
	unsigned int m_uiNbChannel;
	/** IP��ַ*/
	unsigned int m_uiIP;

	/** �첨����*/
	unsigned int m_uiSensorNb;
	/** SegdCode*/
	unsigned int m_uiSegdCode;
	/** �Ƿ�������*/
	bool m_bJumped;
	/** �Ƿ��Ƶ�*/
	bool m_bMute;

	/** �����豸��*/
	unsigned int m_uiSN;

	/** ������ӵĲ��*/
	CChannelSetupData* m_pChannelLeft;
	/** ������ӵĲ��*/
	CChannelSetupData* m_pChannelRight;
	/** �������ӵĲ��*/
	CChannelSetupData* m_pChannelTop;
	/** �������ӵĲ��*/
	CChannelSetupData* m_pChannelDown;

	/** Ұ��������ֵ*/
	float m_fResistanceValue;
	/** Ұ�������Խ�� 0��δ���ԣ�1�����Ժϸ�2�����Բ��ϸ�3�����źţ�4��δ�ж�*/
	byte m_byResistanceCheck;
	/** Ұ���������оݣ�����*/
	float m_fResistanceLimitMin;
	/** Ұ���������оݣ�����*/
	float m_fResistanceLimitMax;

	/** Ұ��©�����ֵ*/
	float m_fLeakageValue;
	/** Ұ��©����Խ�� 0��δ���ԣ�1�����Ժϸ�2�����Բ��ϸ�3�����źţ�4��δ�ж�*/
	byte m_byLeakageCheck;
	/** Ұ��©������о�*/
	float m_fLeakageLimit;

	/** Ұ����������ֵ*/
	float m_fNoiseValue;
	/** Ұ���������Խ�� 0��δ���ԣ�1�����Ժϸ�2�����Բ��ϸ�3�����źţ�4��δ�ж�*/
	byte m_byNoiseCheck;
	/** Ұ�����������о�*/
	float m_fNoiseLimit;

	/** Ұ����б�Ȳ���ֵ*/
	float m_fTiltValue;
	/** Ұ����б�Ȳ��Խ�� 0��δ���ԣ�1�����Ժϸ�2�����Բ��ϸ�3�����źţ�4��δ�ж�*/
	byte m_byTiltCheck;
	/** Ұ����б�Ȳ����о�*/
	float m_fTiltLimit;

	/** Ұ����б��ģ�Ͳ���ֵ*/
	float m_fTiltModelValue;
	/** Ұ����б��ģ�Ͳ��Խ�� 0��δ���ԣ�1�����Ժϸ�2�����Բ��ϸ�3�����źţ�4��δ�ж�*/
	byte m_byTiltModelCheck;
	/** Ұ����б��ģ�Ͳ����о�*/
	float m_fTiltModelLimit;

	/** Ұ����Խ�� 0��δ���ԣ�1�����Ժϸ�2�����Բ��ϸ�3�����źţ�4��δ�ж�*/
	byte m_byCheck;

	/** ����������ֵ*/
	float m_fNoiseMonitorValue;
	/** ���������Խ�� 0��δ���ԣ�1�����Ժϸ�2�����Բ��ϸ�3�����źţ�4��δ�ж�*/
	byte m_byNoiseMonitorCheck;

	/** �첨���Ƿ�����˳�ʼ����*/
	byte m_byTestOnField;
	/** ��ʼ���Խ�� 0��δ���ԣ�1�����Ժϸ�2�����Բ��ϸ�3�����źţ�4��δ�ж�*/
	byte m_byOnFieldCheck;

public: // ����
	// ����
	void OnReset();
	// ���¼���
	void OnReload();

	// ���ݲ��ߺš����š�����ţ�����IP��ַ
	void CreateIP();
	// ���ݲ��ߺš����š�����ţ�����IP��ַ
	static unsigned int CreateIP(unsigned int uiNbLine, unsigned int uiNbPoint, unsigned int uiNbChannel);
	// �����Խ��
	void CheckResultAll();
	// ����ʼ���Խ��
	void CheckResultOnField(UINT uiTestResistance, UINT uiTestTilt, UINT uiTestLeakage);
};
