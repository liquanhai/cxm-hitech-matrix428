#pragma once
#include "InstrumentList.h"
#include <hash_map>
#include "LogFile.h"
using namespace stdext;
// CTailTimeFrameSocket
class CTailTimeFrameSocket : public CSocket
{
public:
	CTailTimeFrameSocket();
	virtual ~CTailTimeFrameSocket();
	virtual void OnReceive(int nErrorCode);
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
	CString m_csIPSource;
	// ���Ͷ˿�
	unsigned int m_uiSendPort;
	// ����λ��������
	hash_map<unsigned int, CInstrument*> m_oInstrumentLocationMap;
	// ��־��ָ��
	CLogFile* m_pLogFile;
	// ����ָ��
	CWnd* m_pwnd;
public:
	// ����ʱͳ��������֡
	void MakeTimeDelayFrameData(CInstrument* pInstrument, unsigned int uiTimeHigh, unsigned int uiTimeLow);
	// ����ʱͳ��������֡
	void SendTimeDelayFrameData(void);
	// �����豸�ı���ʱ��
	void OnSetTimeDelay(unsigned int uiTimeHigh, unsigned int uiTimeLow);
};


