#pragma once

class CADCSet
{
public:
	CADCSet(void);
	~CADCSet(void);
public:
	// ADC����֡
	byte m_cFrameData[128];
	// ADC����֡ͷ
	void ADCSetFrameHead(unsigned int uiIPAim, bool bBroadCast);
	// ����ADC���õ�18ָ��
	int ADCCommand_18(int iPos, byte * cADCSet, unsigned int uiLength);
	// �����������
	void OnSetSine(void);
	// ����ֹͣ�ɼ�
	void OnStopSample(void);
	// �򿪵�Դ
	void OnOpenPower(void);
	// ��TB��Դ
	void OnOpenPowerTB(void);
	// �򿪿���
	void OnOpenSwitch(void);
	// ��TB����
	void OnOpenSwitchTB(void);
	// ��ADC�Ĵ���
	void OnADCRegisterRead(void);
	// дADC�Ĵ���
	void OnADCRegisterWrite(void);
	// ADC���ò�������
	void OnADCSetReturn(void);
	// ADC������ȡ����
	void OnADCReadContinuous(void);
	// ����TBʱ��
	void OnSetTB(unsigned int tnow);
};
