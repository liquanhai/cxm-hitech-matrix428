#pragma once
#include "InstrumentList.h"
#include "ADCSet.h"
// CIPSetSocket ����Ŀ��

class CIPSetSocket : public CSocket
{
public:
	CIPSetSocket();
	virtual ~CIPSetSocket();
	virtual void OnReceive(int nErrorCode);
public:
	// ��������
	DWORD m_uiSN;
	// ������IP��ַ
	DWORD m_uiIPAddress;
	// �����б�ָ��
	CInstrumentList* m_oInstrumentList;
	// IP��ַ����Ӧ�𻺳�
	byte m_pIPSetReturnFrameData[256];
	// ����IP��ַ����Ӧ��֡����
	void ProcIPSetReturnFrameOne(void);
	// ����IP��ַ����Ӧ��֡
	BOOL ParseIPSetReturnFrame(void);
	// �豸�����ϵ�ͼ��ָ��
	HICON m_iconConnected;
	// ����ָ��
	CWnd* m_pwnd;
	// ADC������ָ��
	CADCSet* m_pADCSet;
	// Ŀ��˿�
	unsigned int m_uiSendPort;
	// ѡ����������
	int* m_pSelectObject;
};


