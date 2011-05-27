#pragma once
#include "InstrumentList.h"
// CTailFrameSocket ����Ŀ��

class CTailFrameSocket : public CSocket
{
public:
	CTailFrameSocket();
	virtual ~CTailFrameSocket();
	virtual void OnReceive(int nErrorCode);
public:
	// β���������ݻ���
	byte m_pTailFrameData[RcvFrameSize];
	// β��ʱ�̲�ѯ֡
	byte m_pTailTimeSendData[SndFrameSize];
	// ������β��
	void ProcTailFrameOne(void);
	// ����β��
	BOOL ParseTailFrame(void);
	// ����SN��
	DWORD m_uiSN;
	// �����б�ָ��
	CInstrumentList* m_pInstrumentList;
	// ����������β��ʱ�̲�ѯ֡
	void SendTailTimeFrame(void);
	// ����β��ʱ�̲�ѯ֡
	void MakeTailTimeFrameData(CInstrument* pInstrument);
	// ����β��ʱ�̲�ѯ֡
	void SendTailTimeFrameToSocket(void);
	// ԴIP��ַ
	CString m_csIPSource;
	// ���Ͷ˿�
	unsigned int m_uiSendPort;
	// β�����ձ�־λ
	BOOL m_bTailRec;
	// ��ֹ������ѭ���������޷���Ӧ��Ϣ
	void ProcessMessages(void);
};


