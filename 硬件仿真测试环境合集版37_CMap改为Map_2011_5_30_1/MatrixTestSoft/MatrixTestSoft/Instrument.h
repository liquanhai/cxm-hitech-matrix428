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
	// �װ�������·�ɵ�ַ
	DWORD m_uiRoutAddress;
	// ����վ����LCI��·�ɵ�ַ
	DWORD m_uiRoutAddressTop;
	// ����վ����LCI��·�ɵ�ַ
	DWORD m_uiRoutAddressDown;
	// ����վ����LCI��·�ɵ�ַ
	DWORD m_uiRoutAddressLeft;
	// ����վ����LCI��·�ɵ�ַ
	DWORD m_uiRoutAddressRight;
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
	// ��������������
	unsigned int m_uiInstrumentType;
	// IP��ַ���óɹ���־λ
	bool m_bIPSetOK;
	// �豸λ�����
	int m_iLocation;
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
	// ������ָ���ϲ�����ָ��
	CInstrument* m_pInstrumentTop;
	// ������ָ���²�����ָ��
	CInstrument* m_pInstrumentDown;
	// ������ָ���������ָ��
	CInstrument* m_pInstrumentLeft;
	// ������ָ���Ҳ�����ָ��
	CInstrument* m_pInstrumentRight;
	// �����Ĺ㲥�˿�
	unsigned int m_uiBroadCastPort;
public:
	// ���ó�Ա����
	void OnReset(void);
};
