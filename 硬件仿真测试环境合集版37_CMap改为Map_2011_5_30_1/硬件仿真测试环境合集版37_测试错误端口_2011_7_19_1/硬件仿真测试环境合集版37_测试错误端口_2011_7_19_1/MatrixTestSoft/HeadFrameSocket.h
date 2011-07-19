#pragma once
#include "InstrumentList.h"
#include "LogFile.h"
// CHeadFrameSocket ����Ŀ��

class CHeadFrame
{
public:
	CHeadFrame();
	virtual ~CHeadFrame();
protected:
	// ��������
	DWORD m_uiSN;
	// �װ�ʱ��
	DWORD m_uiHeadFrameTime;
	// ·�ɵ�ַ
	DWORD m_uiRoutAddress;
	// �װ��������ݻ���
	byte m_pHeadFrameData[RcvFrameSize];
	// ����IP��ַ����
	byte m_pIPSetFrameData[SndFrameSize];
public:
	// �����б�ָ��
	CInstrumentList* m_pInstrumentList;
	// ԴIP��ַ
	unsigned int m_uiIPSource;
	// ����ָ��
	CWnd* m_pwnd;
	// ��־��ָ��
	CLogFile* m_pLogFile;
	// Socket�׽���
	sockaddr_in m_RecvAddr, m_SendToAddr;
	SOCKET m_HeadFrameSocket;
protected:
	// �������װ�
	void ProcHeadFrameOne();
	// �����װ�
	BOOL ParseHeadFrame(void);
	// ��ֹ������ѭ���������޷���Ӧ��Ϣ
	void ProcessMessages(void);
public:
	// ����IP��ַ����֡
	void MakeIPSetFrame(CInstrument* pInstrument, BOOL bSetIP);
	// ����IP��ַ����֡
	void SendIPSetFrame(void);
	// ���IP��ַ����Ӧ��֡
	bool OnMonitorIPSetReturn(void);
	// ��Ϣ������
	void OnReceive(void);
	// �ر�UDP�׽���
	void OnCloseUDP(void);
};