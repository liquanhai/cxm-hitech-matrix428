#pragma once

/**
*@brief ������������֡��
*/
class CFrameTestSet
{
public:
	CFrameTestSet();
	~CFrameTestSet();

public: // ����
	/** ֡��С*/
	int m_iFrameSize;
	/** ֡����*/
	byte m_pFrameData[256];
	/** ԴIP��ַ*/
	unsigned int m_uiIPSource;
	/** Ŀ��IP��ַ*/
	unsigned int m_uiIPAim;
	/** Ŀ��˿ں�*/
	unsigned short m_usPortAim;
	/** ����� 1-��������Ӧ��2-��ѯ����Ӧ��3-AD���������ط�*/
	unsigned short m_usCommand;

	/** AD�ɼ���ʼʱ��*/
	unsigned int m_uiADTimeBegin;
	/** AD�ɼ���ʼʱ�̸�λ*/
	unsigned int m_uiADTimeBeginHight;
	/** AD�ɼ���ʼʱ�̵�λ*/
	unsigned int m_uiADTimeBeginLow;
	/** �ɼ���ʼʱ��*/
	unsigned int m_uiCollectTimeBegin;
	/** �ɼ���ʼʱ�̸�λ*/
	unsigned int m_uiCollectTimeBeginHight;
	/** �ɼ���ʼʱ�̵�λ*/
	unsigned int m_uiCollectTimeBeginLow;
	/** �ɼ�����ʱ��*/
	unsigned int m_uiCollectTimeEnd;
	/** �ɼ�����ʱ�̸�λ*/
	unsigned int m_uiCollectTimeEndHight;
	/** �ɼ�����ʱ�̵�λ*/
	unsigned int m_uiCollectTimeEndLow;
	/** �ɼ���������˿�*/
	unsigned short m_usPortListen;
	/** ���ݲɼ������Ŀ��IP��ַ*/
	unsigned int m_uiIPDataOut;
	/** ���ݲɼ������Ŀ�Ķ˿�*/
	unsigned short m_usPortDataOut;
	/** ���ݲɼ������Ŀ�Ķ˿����� ad_cmd(15)=1���˿ڵ�����=0���˿ڲ���*/
	unsigned short m_usPortDataOutCMD;
	/** �����룺 ������������*/
	DWORD m_dwConfig;
	/** �����룺 �˲�����������0*/
	DWORD m_dwFilter17;
	/** �����룺 �˲�����������1*/
	DWORD m_dwFilter18;

	/** ������ ��λ΢��*/
	unsigned int m_uiSamplingRate;
	/** �˲�������*/
	unsigned int filter_hex;
	/** ��ͨ�˲�����*/
	float high_pass_freq;

public: // ����
	// ���ö���
	void Reset();
	// ���ɲ�������֡
	void MakeFrameDataForTestSet();
	// ���ɲ�������֡
	void MakeFrameDataForTestStart();
	// ���ɲ���ֹͣ֡
	void MakeFrameDataForTestEnd();
	// ADC����֡ͷ
	int ADCSetFrameHead(unsigned int uiIPAim, unsigned short	usCommand, unsigned short usPortAim);
// 	//����AD֡ͷ
// 	int MakeFrameHead();
// 	//���㲥
// 	int MakeFrameHead1();
	//����18������
	int ADCCommand_18(int iPos, byte * cADCSet, unsigned int uiLength);
	// �����������
	void OnSetSine(int iPos);
	// ����ֹͣ�ɼ�
	void OnStopSample(int iPos);
	// �򿪵�Դ
	void OnOpenPowerTBLow(int iPos);
	// ��TB��Դ
	void OnOpenPowerTBHigh(int iPos);
	// �򿪿���
	void OnOpenSwitchTBLow(int iPos);
	// ��TB����
	void OnOpenSwitchTBHigh(int iPos);
	// ��ADC�Ĵ���
	void OnADCRegisterRead(int iPos);
	// дADC�Ĵ���
	void OnADCRegisterWrite(int iPos, bool bSwitch);
	// ADC���ò�������
	void OnADCSetReturn(int iPos);
	// ADC������ȡ����
	void OnADCReadContinuous(int iPos);
	void OnNULL(int iPos);
	// ����TBʱ��
	void OnSetTB(int iPos, unsigned int tbh, unsigned int tbl, bool bSwitch);
//	int OnSetTB(unsigned int tnow);
	//����AD֡ͷ
//	int MakeFrameHead();
	//���㲥
//	int MakeFrameHead1();
	// ����Ư������Դ������
	void OnOpenPowerZeroDrift(int iPos);
	// ��ѯADC�Ĵ���
	void OnADCRegisterQuery(int iPos);
	// ADC���ݲɼ�ͬ��
	void OnADCSampleSynchronization(int iPos);
	// ADC��Ưƫ�ƽ���
	void OnADCZeroDriftCorrection(int iPos);
	// ADC��Ư���ã���IP��ַ��
	void OnADCZeroDriftSetFromIP(int iPos, unsigned char* ucZeroDrift);
	// ��TB����
	void OnSetTBSwitchOpen(int iPos);
	// �㲥��ѯ�ɼ�վTBʱ��
	void OnQueryTBTime(int iPos);
	int GetTB();
	void MakeFrameDataForADTestStart();
	void MakeFrameDataForADTestEnd();
};
