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
protected:
	// ��������
	DWORD m_uiSN;
	// ������IP��ַ
	DWORD m_uiIPAddress;
	// IP��ַ����Ӧ�𻺳�
	byte m_pIPSetReturnFrameData[RcvFrameSize];
public:
	// �����б�ָ��
	CInstrumentList* m_pInstrumentList;
	// �ɼ�վ�豸�����ϵ�ͼ��ָ��
	HICON m_iconFDUConnected;
	// ����վ�豸�����ϵ�ͼ��ָ��
	HICON m_iconLAUXConnected;
	// ����ָ��
	CWnd* m_pwnd;
	// Ŀ��˿�
	unsigned int m_uiSendPort;
	// ѡ����������
	int* m_pSelectObject;
	// �ɼ�վ�豸Button�ؼ�ID
	int m_iButtonIDFDU[InstrumentNum];
	// �ɼ�վ�豸����ѡ��Check�ؼ�ID
	int m_iCheckIDInstrumentFDU[InstrumentNum];
protected:
	// ����IP��ַ����Ӧ��֡����
	void ProcIPSetReturnFrameOne(void);
	// ����IP��ַ����Ӧ��֡
	BOOL ParseIPSetReturnFrame(void);
	// ��ʾ�豸����ͼ��
	void OnShowConnectedIcon(unsigned int uiIPAddress);
	// ��ֹ������ѭ���������޷���Ӧ��Ϣ
	void PorcessMessages(void);
};

