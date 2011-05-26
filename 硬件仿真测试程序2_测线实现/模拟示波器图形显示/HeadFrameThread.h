#pragma once
#include "InstrumentList.h"


// CHeadFrameThread

class CHeadFrameThread : public CWinThread
{
	DECLARE_DYNCREATE(CHeadFrameThread)

public:
	CHeadFrameThread();           // ��̬������ʹ�õ��ܱ����Ĺ��캯��
	virtual ~CHeadFrameThread();
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
	// �ر��̱߳�־λ
	bool m_bclose;
	// �װ�����Socket
	CSocket m_HeadFrameSocket;
	// IP��ַ����Socket
	CSocket m_IPSetSocket;
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
	// ������IP��ַ
	DWORD m_uiIPAddress;
	// �����б�ָ��
	CInstrumentList* m_oInstrumentList;
	// ����IP��ַ����֡
	void MakeIPSetFrame(CInstrument* pInstrument);
	// �װ��������ݻ���
	byte m_pHeadFrameData[256];
	// ����IP��ַ����
	byte m_pIPSetFrameData[256];
	// IP��ַ����Ӧ�𻺳�
	byte m_pIPSetReturnFrameData[256];
	// ����IP��ַ����֡
	void SendIPSetFrame(void);
	// ����IP��ַ����Ӧ��֡����
	void ProcIPSetReturnFrameOne(void);
	// ����IP��ַ����Ӧ��֡
	BOOL ParseIPSetReturnFrame(void);
};


