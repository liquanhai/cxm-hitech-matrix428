#pragma once
#include "InstrumentList.h"
#include "LogFile.h"
// CTailFrameSocket ����Ŀ��

class CTailFrame
{
public:
	CTailFrame();
	virtual ~CTailFrame();
private:
	// β���������ݻ���
	byte m_pTailFrameData[RcvFrameSize];
	// β��ʱ�̲�ѯ֡
	byte m_pTailTimeSendData[SndFrameSize];
public:
	// ����SN��
	DWORD m_uiSN;
	// �����б�ָ��
	CInstrumentList* m_pInstrumentList;
	// ԴIP��ַ
	unsigned int m_uiIPSource;
	// ����վβ�����ձ�־λ
	BOOL m_bTailRecLAUX;
	// ����վ�յ�β������
	unsigned int m_uiTailRecLAUXCount;
	// �ɼ�վβ�����ձ�־λ
	BOOL m_bTailRecFDU;
	// �ɼ�վ�յ�β������
	unsigned int m_uiTailRecFDUCount;
	// ��־��ָ��
	CLogFile* m_pLogFile;
	// Socket�׽���
	sockaddr_in m_RecvAddr, m_SendToAddr;
	SOCKET m_TailFrameSocket;
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
	// ��Ϣ������
	void OnReceive(void);
	// �ر�UDP�׽���
	void OnCloseUDP(void);
};


