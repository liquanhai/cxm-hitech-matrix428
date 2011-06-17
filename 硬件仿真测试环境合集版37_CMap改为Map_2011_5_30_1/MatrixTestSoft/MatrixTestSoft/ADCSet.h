#pragma once
#include "TabADCSettings.h"
#include "Parameter.h"
#include "InstrumentList.h"
#include "LogFile.h"
class CADCSet : public CSocket
{
public:
	CADCSet(void);
	~CADCSet(void);
public:
	// ADC����֡
	unsigned char m_ucFrameData[SndFrameSize];
	// ԴIP��ַ
	CString m_csIPSource;
	// Ŀ��˿ں�
	unsigned int m_uiSendPort;
	// �豸��ָ��
	CInstrumentList* m_pInstrumentList;
	// ADC��������ѡ�����ָ��
	CTabADCSettings* m_pTabADCSettings;
	// �豸ѡ��ָ��
	int* m_pSelectObject;
	// ��־��ָ��
	CLogFile* m_pLogFile;
protected:
	// ���ݽ��ջ�����
	unsigned char udp_buf[RcvFrameSize];
	// ��Ưƫ����
	unsigned char m_ucZeroDrift[InstrumentNum][ADCZeroDriftWritebytesNum];
protected:
	// ��ֹ������ѭ���������޷���Ӧ��Ϣ
	void ProcessMessages(void);
	// ������ƯУ����ѯӦ��
	void OnProcADCZeroDriftReturn(int iPos);
public:
	// ADC����֡ͷ
	int ADCSetFrameHead(unsigned int uiIPAim, unsigned short	usCommand, unsigned short usPortAim);
	// ����ADC���õ�18ָ��
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
	// ����TBʱ��
	void OnSetTB(int iPos, unsigned int tnow, bool bSwitch);
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
	// ����CRCУ��ֵ
	void OnCRCCal(void);
	// ��TB����
	void OnSetTBSwitchOpen(int iPos);
	// ��ѯ�ɼ�վ�������
	void OnQueryErrorCodeFdu(int iPos);
	// ��ѯ����վ���ϼ���
	void OnQueryErrorCodeLAUX(int iPos);
	// ��ѯ��������
	void OnQueryErrorCode(void);
	// ADC��������
	void OnADCSet(void);
	// ADC���ݲɼ�ֹͣ
	void OnADCSampleStop(void);
	// ADC��ƯУ��
	void OnADCZeroDrift(void);
	// ADC����TBʱ�̿�ʼ�ɼ�
	void OnADCStartSample(unsigned int tnow);
	virtual void OnReceive(int nErrorCode);
};
