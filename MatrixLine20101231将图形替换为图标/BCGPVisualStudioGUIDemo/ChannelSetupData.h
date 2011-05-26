#pragma once

class CChannelSetupData
{
public:
	CChannelSetupData(void);
	~CChannelSetupData(void);

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
	/** Ұ�������Խ�� 0��δ���ԣ�1�����Ժϸ�2�����Բ��ϸ�3�����ź�*/
	byte m_byResistanceCheck;

	/** Ұ��©�����ֵ*/
	float m_fLeakageValue;
	/** Ұ��©����Խ�� 0��δ���ԣ�1�����Ժϸ�2�����Բ��ϸ�3�����ź�*/
	byte m_byLeakageCheck;

	/** Ұ����������ֵ*/
	float m_fNoiseValue;
	/** Ұ���������Խ�� 0��δ���ԣ�1�����Ժϸ�2�����Բ��ϸ�3�����ź�*/
	byte m_byNoiseCheck;

	/** Ұ����б�Ȳ���ֵ*/
	float m_fTiltValue;
	/** Ұ����б�Ȳ��Խ�� 0��δ���ԣ�1�����Ժϸ�2�����Բ��ϸ�3�����ź�*/
	byte m_byTiltCheck;

	/** Ұ����б��ģ�Ͳ���ֵ*/
	float m_fTiltModelValue;
	/** Ұ����б��ģ�Ͳ��Խ�� 0��δ���ԣ�1�����Ժϸ�2�����Բ��ϸ�3�����ź�*/
	byte m_byTiltModelCheck;

	/** Ұ����Խ�� 0��δ���ԣ�1�����Ժϸ�2�����Բ��ϸ�3�����ź�*/
	byte m_byCheck;

	/** ����������ֵ*/
	float m_fNoiseMonitorValue;
	/** ���������Խ�� 0��δ���ԣ�1�����Ժϸ�2�����Բ��ϸ�3�����ź�*/
	byte m_byNoiseMonitorCheck;

	/** �첨���Ƿ�����˳�ʼ����*/
	bool m_bTestOnField;

public: // ����
	// ���ݲ��ߺš����š�����ţ�����IP��ַ
	static unsigned int CreateIP(unsigned int uiNbLine, unsigned int uiNbPoint, unsigned int uiNbChannel);

	// �õ����Խ���ַ���
	CString GetTestResultString(unsigned int uiType);
	// �õ����Խ���ַ���
	CString GetTestResultString(byte byCheck, float m_fValue);
	// �õ����Խ��
	byte GetTestResultCheck(unsigned int uiType, float fSeismonitorLimit);
};
