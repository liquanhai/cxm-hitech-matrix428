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
	CInstrumentList* m_pInstrumentList;
	// IP��ַ����Ӧ�𻺳�
	byte m_pIPSetReturnFrameData[256];
	// ����IP��ַ����Ӧ��֡����
	void ProcIPSetReturnFrameOne(void);
	// ����IP��ַ����Ӧ��֡
	BOOL ParseIPSetReturnFrame(void);
	// �ɼ�վ�豸�����ϵ�ͼ��ָ��
	HICON m_iconFDUConnected;
	// ����վ�豸�����ϵ�ͼ��ָ��
	HICON m_iconLAUXConnected;
	// ����ָ��
	CWnd* m_pwnd;
	// ADC������ָ��
	CADCSet* m_pADCSet;
	// Ŀ��˿�
	unsigned int m_uiSendPort;
	// ѡ����������
	int* m_pSelectObject;
	// ��ʾ�豸����ͼ��
	void OnShowConnectedIcon(unsigned int uiIPAddress);
	// �ɼ�վ�豸Button�ؼ�ID
	int m_iButtonIDFDU[GraphViewNum];
	// �ɼ�վ�豸����ѡ��Check�ؼ�ID
	int m_iCheckIDInstrumentFDU[GraphViewNum];
};


