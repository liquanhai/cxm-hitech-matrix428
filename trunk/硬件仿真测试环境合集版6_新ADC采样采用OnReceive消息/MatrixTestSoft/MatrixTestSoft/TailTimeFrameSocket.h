#pragma once
#include "InstrumentList.h"
// CTailTimeFrameSocket ����Ŀ��

class CTailTimeFrameSocket : public CSocket
{
public:
	CTailTimeFrameSocket();
	virtual ~CTailTimeFrameSocket();
	virtual void OnReceive(int nErrorCode);
public:
	// β��ʱ�̲�ѯ������ݽ��ջ���
	byte m_pTailTimeRecData[256];
	// ʱ������֡
	byte m_pTimeDelayData[128];
	// ����λ��������
	CMap<unsigned int, unsigned int, CInstrument*, CInstrument*> m_oInstrumentLocationMap;
	// ����SN��
	DWORD m_uiSN;
	// �����б�ָ��
	CInstrumentList* m_oInstrumentList;
	// ����β��ʱ�̲�ѯ����
	void ProcTailTimeFrameOne(void);
	// ����β��ʱ�̲�ѯ֡
	BOOL PraseTailTimeFrame(void);
	// �豸������ʱ��
	DWORD m_uiNetTime;
	// �豸�ı���ʱ��
	DWORD m_uiSystemTime;
	// �豸β������ʱ��
	unsigned short m_usTailRecTime;
	// �豸β������ʱ��
	unsigned short m_usTailSendTime;
	// ʱ��ͬ������
	void TimeDelayCalculation(void);
	// ʱ��������λ
	int m_iTimeHigh;
	// ʱ��������λ
	int m_iTimeLow;
	// ����ʱͳ��������֡
	void MakeTimeDelayFrameData(CInstrument* pInstrument);
	// ����ʱͳ��������֡
	void SendTimeDelayFrameData(void);
	// ʱ��������������
	unsigned int m_uiDelayTimeCount;
	// ԴIP��ַ
	CString m_csIPSource;
	// ���Ͷ˿�
	unsigned int m_uiSendPort;
};


