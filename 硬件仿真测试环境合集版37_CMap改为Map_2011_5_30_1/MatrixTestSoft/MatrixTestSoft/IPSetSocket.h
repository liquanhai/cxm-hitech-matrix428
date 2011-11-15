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
	// ����ָ��
	CWnd* m_pWnd;
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
	// ��ֹ������ѭ���������޷���Ӧ��Ϣ
	void PorcessMessages(void);
public:
	// ��Ϣ������
	void OnReceive(void);
	// �ر�UDP�׽���
	void OnCloseUDP(void);
};


