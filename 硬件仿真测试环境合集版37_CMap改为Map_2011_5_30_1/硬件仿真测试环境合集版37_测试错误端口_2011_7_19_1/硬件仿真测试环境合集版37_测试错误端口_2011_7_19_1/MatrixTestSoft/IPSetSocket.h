#pragma once
#include "InstrumentList.h"
#include "ADCSet.h"
#include "LogFile.h"
// CIPSetSocket ����Ŀ��

class CIPSet
{
public:
	CIPSet();
	virtual ~CIPSet();
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
	// ѡ����������
	int* m_pSelectObject;
	// �ɼ�վ�豸Button�ؼ�ID
	int m_iButtonIDFDU[InstrumentNum];
	// �ɼ�վ�豸����ѡ��Check�ؼ�ID
	int m_iCheckIDInstrumentFDU[InstrumentNum];
	// ��־��ָ��
	CLogFile* m_pLogFile;
	// Socket�׽���
	sockaddr_in m_RecvAddr;
	SOCKET m_IPSetSocket;
protected:
	// ����IP��ַ����Ӧ��֡����
	void ProcIPSetReturnFrameOne(void);
	// ����IP��ַ����Ӧ��֡
	BOOL ParseIPSetReturnFrame(void);
	// ��ʾ�豸����ͼ��
	void OnShowConnectedIcon(unsigned int uiIPAddress);
	// ��ֹ������ѭ���������޷���Ӧ��Ϣ
	void PorcessMessages(void);
public:
	// ��Ϣ������
	void OnReceive(void);
	// �ر�UDP�׽���
	void OnCloseUDP(void);
};


