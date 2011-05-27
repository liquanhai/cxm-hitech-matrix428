#pragma once
#include "afxsock.h"
#include "Parameter.h"
#include "SaveFile.h"

// CPortMonitoringThreadRec

class CPortMonitoringThreadRec : public CWinThread
{
	DECLARE_DYNCREATE(CPortMonitoringThreadRec)

public:
	CPortMonitoringThreadRec();           // ��̬������ʹ�õ��ܱ����Ĺ��캯��
	virtual ~CPortMonitoringThreadRec();

public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

protected:
	DECLARE_MESSAGE_MAP()
public:
	// �̳߳�ʼ��
	void OnInit(void);
	// �̹߳ر�
	void OnClose(void);
	virtual int Run();
protected:
	// �˿ڼ��ӽ��ն˿�Socket
	CSocket m_hSocketRec;
public:
	// �߳̽����¼�
	HANDLE m_hThreadRecClose;
protected:
	// �̹߳رձ�־λ
	bool m_bClose;
	// ���ݽ��ջ���
	unsigned char m_ucudp_buf[8][128];
	// ���ݽ��ջ���������
	unsigned short m_usudp_count;
public:
	// ���ն˿�
	int m_iRecPort;
	// ���Ͷ˿�
	int m_iSendPort;
	// Ŀ��IP��ַ
	CString m_csIP;
	// ��
	void OnOpen(void);
	// ֹͣ
	void OnStop(void);
	// ���ý���
	void OnReset(void);
	// ����PortMonitoringSendָ��
	CWnd* m_pwnd;
	// ����TabPortMonitoringָ��
	CWnd* m_pWndTab;
	// �����ļ����ָ��
	CSaveFile* m_pSaveFile;
protected:
	// ��������
	unsigned int m_uiHeartBeatNum;
	// IP��ַ���ü���
	unsigned int m_uiIPSetNum;
	// β��ʱ�̲�ѯ����
	unsigned int m_uiTailTimeNum;
	// ʱ�����ü���
	unsigned int m_uiDelayTimeSetNum;
	// ADC���ü���
	unsigned int m_uiADCSetNum;
	// ����֡��
	unsigned int m_uiSendFrameNum;
};


