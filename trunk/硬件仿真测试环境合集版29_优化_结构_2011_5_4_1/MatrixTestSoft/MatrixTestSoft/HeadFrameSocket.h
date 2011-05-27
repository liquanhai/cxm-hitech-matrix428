#pragma once
#include "InstrumentList.h"

// CHeadFrameSocket ����Ŀ��

class CHeadFrameSocket : public CSocket
{
public:
	CHeadFrameSocket();
	virtual ~CHeadFrameSocket();
	virtual void OnReceive(int nErrorCode);
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
	CString m_csIPSource;
	// ���Ͷ˿�
	unsigned int m_uiSendPort;
	// ����ָ��
	CWnd* m_pwnd;
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
};