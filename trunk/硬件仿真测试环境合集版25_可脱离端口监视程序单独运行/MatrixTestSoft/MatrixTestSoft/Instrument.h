#pragma once

class CInstrument
{
public:
	CInstrument(void);
	~CInstrument(void);

	// ����IP��ַ
	DWORD m_uiIPAddress;
	// ��������
	DWORD m_uiSN;
	// ·�ɵ�ַ
	DWORD m_uiRoutAddress;
	// �װ�ʱ��
	DWORD m_uiHeadFrameTime;
	// ����ϵͳʱ��
	DWORD m_uiSystemTime;
	// �װ�����
	int m_iHeadFrameCount;
	// β������
	int m_iTailFrameCount;
	// ���ó�Ա����
	void OnReset(void);
	// �����������е�λ��
	unsigned int m_uiIndex;
	// ����ʹ�ñ�־λ
	bool m_bInUsed;
	// �������������ͣ�0-δ���ã�1-�ӿ�վ��3-�ɼ�վ
	unsigned int m_uiInstrumentType;
	// IP��ַ���óɹ���־λ
	bool m_bIPSetOK;
	// �豸λ�����
	unsigned int m_uiLocation;
	// �豸������ʱ��
	DWORD m_uiNetTime;
	// �豸β������ʱ��
	unsigned short m_usTailRecTime;
	// �豸β������ʱ��
	unsigned short m_usTailSendTime;
	// β��ʱ�̲�ѯ�ɹ���־λ
	bool m_bTailTimeReturnOK;
	// β��ʱ�̲�ѯ���ڱ�־λ
	bool m_bTailTimeExpired;
	// ������β��ʱ�̲�ѯ֡
	bool m_bSendTailTimeFrame;
	// ADC�������ñ�־λ
	bool m_bADCSet;
	// IP��ַ�������
	unsigned int m_uiIPResetTimes;
};
