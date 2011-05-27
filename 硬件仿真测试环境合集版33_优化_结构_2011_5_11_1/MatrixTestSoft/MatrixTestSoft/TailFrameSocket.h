#pragma once
#include "InstrumentList.h"
// CTailFrameSocket ����Ŀ��

class CTailFrameSocket : public CSocket
{
public:
	CTailFrameSocket();
	virtual ~CTailFrameSocket();
	virtual void OnReceive(int nErrorCode);
private:
	// β���������ݻ���
	byte m_pTailFrameData[RcvFrameSize];
	// β��ʱ�̲�ѯ֡
	byte m_pTailTimeSendData[SndFrameSize];
	// ����SN��
	DWORD m_uiSN;
	// δ�յ�β������
	unsigned int m_uiTailRecCount;
	// β����ʼ������־λ
	bool m_bTailCountStart;
public:
	// �����б�ָ��
	CInstrumentList* m_pInstrumentList;
	// ԴIP��ַ
	CString m_csIPSource;
	// ���Ͷ˿�
	unsigned int m_uiSendPort;
	// β�����ձ�־λ
	BOOL m_bTailRec;
private:
	// ������β��
	void ProcTailFrameOne(void);
	// ����β��
	BOOL ParseTailFrame(void);
	// ����β��ʱ�̲�ѯ֡
	void MakeTailTimeFrameData(CInstrument* pInstrument);
	// ����β��ʱ�̲�ѯ֡
	void SendTailTimeFrameToSocket(void);
	// ��ֹ������ѭ���������޷���Ӧ��Ϣ
	void ProcessMessages(void);
public:
	// ����������β��ʱ�̲�ѯ֡
	void SendTailTimeFrame(void);
	// ���β��
	bool OnTailMonitor(void);
};


