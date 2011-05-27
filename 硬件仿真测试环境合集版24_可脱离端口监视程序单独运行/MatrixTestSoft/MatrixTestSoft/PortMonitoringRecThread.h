#pragma once
#include "Parameter.h"
#include "SaveFile.h"


// CPortMonitoringRecThread

class CPortMonitoringRecThread : public CWinThread
{
	DECLARE_DYNCREATE(CPortMonitoringRecThread)

public:
	CPortMonitoringRecThread();           // ��̬������ʹ�õ��ܱ����Ĺ��캯��
	virtual ~CPortMonitoringRecThread();

public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

protected:
	DECLARE_MESSAGE_MAP()

protected:
	// ���ݽ��ջ���
	unsigned char m_ucudp_buf[8][SndFrameSize];
	// ���ݽ��ջ���������
	unsigned short m_usudp_count;
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
public:
	// ���շ�Socket
	CSocket m_RecSocket;
	// ���ն˿�
	int m_iRecPort;
	// ���Ͷ˿�
	int m_iSendPort;
	// Ŀ��IP��ַ
	CString m_csIP;
	// ����PortMonitoringSendָ��
	CWnd* m_pwnd;
	// ����TabPortMonitoringָ��
	CWnd* m_pWndTab;
	// �����ļ����ָ��
	CSaveFile* m_pSaveFile;
	// �̹߳رձ�־
	bool m_bclose;
	// �߳̽����¼�
	HANDLE m_hPortMonitoringRecThreadClose;
	// ����֡��
	unsigned int m_uiSendFrameNum;
public:
	virtual int Run();
	// ��ʼ��
	void OnInit(void);
	// ��
	void OnOpen(void);
	// ֹͣ
	void OnStop(void);
	// �ر�
	void OnClose(void);
	// ��ֹ������ѭ���������޷���Ӧ��Ϣ
	void ProcessMessages(void);
	// ���ý���
	void OnReset(void);
};


