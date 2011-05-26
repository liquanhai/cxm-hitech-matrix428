#pragma once
#include "InstrumentList.h"

// CTailFrameThread

class CTailFrameThread : public CWinThread
{
	DECLARE_DYNCREATE(CTailFrameThread)

public:
	CTailFrameThread();           // ��̬������ʹ�õ��ܱ����Ĺ��캯��
	virtual ~CTailFrameThread();
	virtual int Run();
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

protected:
	DECLARE_MESSAGE_MAP()
public:
	// ��ʼ��
	void OnInit(void);
	// �رղ������߳�
	void OnClose(void);
	// �̹߳رձ�־
	bool m_bclose;
	// �߳̽����¼�
	HANDLE m_hTailFrameThreadClose;
	// β������Socket
	CSocket m_TailFrameSocket;
	// β���������ݻ���
	byte m_pTailFrameData[256];
	// β��ʱ�̲�ѯ֡
	byte m_pTailTimeSendData[128];
	// β��ʱ�̲�ѯ������ݽ��ջ���
	byte m_pTailTimeRecData[256];
	// ʱ������֡
	byte m_pTimeDelayData[128];
	// β��ʱ�̲�ѯSocket
	CSocket m_TailTimeFrameSocket;
	// ����λ��������
	CMap<unsigned int, unsigned int, CInstrument*, CInstrument*> m_oInstrumentLocationMap;
	// ������β��
	void ProcTailFrameOne(void);
	// ����β��
	BOOL ParseTailFrame(void);
	// ����SN��
	DWORD m_uiSN;
	// �����б�ָ��
	CInstrumentList* m_oInstrumentList;
	// ����������β��ʱ�̲�ѯ֡
	void SendTailTimeFrame(void);
	// ����β��ʱ�̲�ѯ֡
	void MakeTailTimeFrameData(CInstrument* pInstrument);
	// ����β��ʱ�̲�ѯ֡
	void SendTailTimeFrameToSocket(void);
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
	// ����β��ʱ�̲�ѯ֡����
	unsigned int m_uiSendTailTimeFrameCount;
	// ���յ���β��ʱ�̲�ѯ֡����
	unsigned int m_uiRecTailTimeFrameCount;
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
};


