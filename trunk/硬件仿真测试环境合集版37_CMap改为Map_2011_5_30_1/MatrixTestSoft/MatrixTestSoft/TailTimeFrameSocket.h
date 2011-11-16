#pragma once
#include "InstrumentList.h"
#include <hash_map>
#include "LogFile.h"

using stdext::hash_map;
// CTailTimeFrameSocket
class CTailTimeFrame
{
public:
	CTailTimeFrame();
	virtual ~CTailTimeFrame();
private:
	// β��ʱ�̲�ѯ������ݽ��ջ���
	byte m_pTailTimeRecData[RcvFrameSize];
	// ʱ������֡
	byte m_pTimeDelayData[SndFrameSize];
private:
	// ����β��ʱ�̲�ѯ����
	void ProcTailTimeFrameOne(void);
	// ����β��ʱ�̲�ѯ֡
	BOOL PraseTailTimeFrame(void);
	// ʱ��ͬ������
	void TimeDelayCalculation(void);
	// ��ֹ������ѭ���������޷���Ӧ��Ϣ
	void ProcessMessages(void);
public:
	// �����б�ָ��
	CInstrumentList* m_pInstrumentList;
	// ԴIP��ַ
	unsigned int m_uiIPSource;
	// ����λ��������
	hash_map<unsigned int, CInstrument*> m_oInstrumentLocationMap;
	// ��־��ָ��
	CLogFile* m_pLogFile;
	// ����ָ��
	CWnd* m_pWnd;
	// Socket�׽���
	sockaddr_in m_RecvAddr, m_SendToAddr;
	SOCKET m_TailTimeSocket;
public:
	// ����ʱͳ��������֡
	void MakeTimeDelayFrameData(CInstrument* pInstrument, unsigned int uiTimeHigh, unsigned int uiTimeLow);
	// ����ʱͳ��������֡
	void SendTimeDelayFrameData(void);
	// �����豸�ı���ʱ��
	void OnSetTimeDelay(unsigned int uiTimeHigh, unsigned int uiTimeLow);
	// ��Ϣ������
	void OnReceive(void);
	// �ر�UDP�׽���
	void OnCloseUDP(void);
	// ����ô���·�ɷ����ʱͳ
	void TimeDelayCalculationLineRout(void);
};


