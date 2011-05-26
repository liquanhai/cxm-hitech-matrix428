#pragma once
#include "InstrumentList.h"

// CHeadFrameSocket ����Ŀ��

class CHeadFrameSocket : public CSocket
{
public:
	CHeadFrameSocket();
	virtual ~CHeadFrameSocket();
	virtual void OnReceive(int nErrorCode);
public:
	// �������װ�
	void ProcHeadFrameOne();
	// �����װ�
	BOOL ParseHeadFrame(void);
	// ��������
	DWORD m_uiSN;
	// �װ�ʱ��
	DWORD m_uiHeadFrameTime;
	// ·�ɵ�ַ
	DWORD m_uiRoutAddress;

	// �����б�ָ��
	CInstrumentList* m_oInstrumentList;
	// ����IP��ַ����֡
	void MakeIPSetFrame(CInstrument* pInstrument);
	// �װ��������ݻ���
	byte m_pHeadFrameData[256];
	// ����IP��ַ����
	byte m_pIPSetFrameData[128];
	// ����IP��ַ����֡
	void SendIPSetFrame(void);
	// ԴIP��ַ
	CString m_csIPSource;
	// ���Ͷ˿�
	unsigned int m_uiSendPort;
};


