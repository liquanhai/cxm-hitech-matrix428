#pragma once
#include "InstrumentList.h"
#include <hash_map>
#include "LogFile.h"
using namespace stdext;
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
	// ����SN��
	DWORD m_uiSN;
	// �豸������ʱ��
	DWORD m_uiNetTime;
	// �豸�ı���ʱ��
	DWORD m_uiSystemTime;
	// �豸β������ʱ��
	unsigned short m_usTailRecTime;
	// �豸β������ʱ��
	unsigned short m_usTailSendTime;
	// ʱ��������λ
	unsigned int m_uiTimeHigh;
	// ʱ��������λ
	unsigned int m_uiTimeLow;
	// ʱ��������������
	unsigned int m_uiDelayTimeCount;
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
	CWnd* m_pwnd;
	// Socket�׽���
	sockaddr_in addr, addr2;
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
};


