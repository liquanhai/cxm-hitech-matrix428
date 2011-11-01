#pragma once

class CInstrument
{
public:
	CInstrument(void);
	~CInstrument(void);
public:
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
	// �豸�ߺ�
	int m_iLineIndex;
	// �����߷���1��2��3��4��
	unsigned int m_uiLineDirection;
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
	// ADC�����������
	unsigned int m_uiADCSetOperationNb;
	// ������ѡ�в���ɼ�ADC����
	int m_iSelectObject;
	// ������ѡ��Ϊ�����ɼ������洢����
	int m_iSelectObjectNoise;
	// �ڸ��豸֮ǰδ��ѡ���ͼ���豸����
	unsigned int m_uiUnCheckedNum;
	// �ɼ�վλ��
	unsigned int m_uiFDULocation;
public:
	// ���ó�Ա����
	void OnReset(void);
};
