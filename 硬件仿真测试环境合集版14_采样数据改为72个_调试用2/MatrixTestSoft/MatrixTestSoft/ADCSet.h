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
	void ADCSetFrameHead(unsigned int uiIPAim, bool bBroadCast, unsigned short	usCommand, unsigned short usPortAim);
	// ����ADC���õ�18ָ��
	int ADCCommand_18(int iPos, byte * cADCSet, unsigned int uiLength);
	// �����������
	void OnSetSine(void);
	// ����ֹͣ�ɼ�
	void OnStopSample(void);
	// �򿪵�Դ
	void OnOpenPowerTBLow(void);
	// ��TB��Դ
	void OnOpenPowerTBHigh(void);
	// �򿪿���
	void OnOpenSwitchTBLow(void);
	// ��TB����
	void OnOpenSwitchTBHigh(void);
	// ��ADC�Ĵ���
	void OnADCRegisterRead(void);
	// дADC�Ĵ���
	void OnADCRegisterWrite(void);
	// ADC���ò�������
	void OnADCSetReturn(void);
	// ADC������ȡ����
	void OnADCReadContinuous(bool bBroadCast);
	// ����TBʱ��
	void OnSetTB(unsigned int tnow);
	// ����Ư������Դ������
	void OnOpenPowerZeroDrift(void);
	// ��ѯADC�Ĵ���
	void OnADCRegisterQuery(void);
	// ADC���ݲɼ�ͬ��
	void OnADCSampleSynchronization(void);
	// ADC��Ưƫ�ƽ���
	void OnADCZeroDriftCorrection(void);
	// ADC��Ư���ã���IP��ַ��
	void OnADCZeroDriftSetFromIP(unsigned char* ucZeroDrift);
	// ADC��������ѡ�����ָ��
	CWnd* m_pWnd;
	// ��¼TB��ʼʱ��
	unsigned int m_uiTBTime;
};
