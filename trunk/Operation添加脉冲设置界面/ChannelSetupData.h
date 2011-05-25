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

public: // ����
	// ���ݲ��ߺš����š�����ţ�����IP��ַ
	static unsigned int CreateIP(unsigned int uiNbLine, unsigned int uiNbPoint, unsigned int uiNbChannel);
};
