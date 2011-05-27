#pragma once
#include "Parameter.h"
#include "SaveFile.h"


// CPortMonitoringSendThread

class CPortMonitoringSendThread : public CWinThread
{
	DECLARE_DYNCREATE(CPortMonitoringSendThread)

public:
	CPortMonitoringSendThread();           // ��̬������ʹ�õ��ܱ����Ĺ��캯��
	virtual ~CPortMonitoringSendThread();

public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

protected:
	DECLARE_MESSAGE_MAP()
protected:
	// ���ݽ��ջ���
	unsigned char m_ucudp_buf[8][RcvFrameSize];
	// ���ݽ��ջ���������
	unsigned short m_usudp_count;
	// �װ�����
	unsigned int m_uiHeadFrameNum;
	// IP��ַ����Ӧ�����
	unsigned int m_uiIPSetReturnNum;
	// β������
	unsigned int m_uiTailFrameNum;
	// β��ʱ�̲�ѯӦ�����
	unsigned int m_uiTailTimeReturnNum;
	// ʱ������Ӧ�����
	unsigned int m_uiDelayTimeReturnNum;
	// ADC����Ӧ�����
	unsigned int m_uiADCSetReturnNum;
	// Ӳ���豸�����ѯӦ��֡����
	unsigned int m_uiErrorCodeReturnNum;
	// Ӳ���豸�����ѯӦ��֡����
	unsigned int m_uiErrorCodeReturnCount[GraphViewNum];
	// ��¼Ӳ���豸�����ѯ�׸�Ӧ��֡
	unsigned char m_ucErrorCodeReturn[GraphViewNum][4];
	// ��ʾ�װ�֡������SN���װ�ʱ��
	CString m_csHeadFrameShow;
	// ��ʾIP��ַ����Ӧ��֡������SN�����õ�IP��ַ
	CString m_csIPSetReturnShow;
	// ��ʾβ��֡������SN
	CString m_csTailFrameShow;
	// ��ʾβ��ʱ�̲�ѯӦ��֡������IP��ַ�Ͳ�ѯ���
	CString m_csTailTimeReturnShow;
	// ��ʾʱ������Ӧ��֡������IP��ַ����������
	CString m_csDelayTimeReturnShow;
	// ��ʾӲ������������
	CString m_csErrorCodeReturnShow;
public:
	// ���ͷ�Socket
	CSocket m_SendSocket;
	// ���ն˿�
	int m_iRecPort;
	// ���Ͷ˿�
	int m_iSendPort;
	// Ŀ��IP��ַ
	CString m_csIP;
	// ����PortMonitoringRecָ��
	CWnd* m_pwnd;
	// ����TabPortMonitoringָ��
	CWnd* m_pWndTab;
	// �����ļ����ָ��
	CSaveFile* m_pSaveFile;
	// �˿ڷַ�����
	BOOL m_bPortDistribution;
	// �̹߳رձ�־
	bool m_bclose;
	// �߳̽����¼�
	HANDLE m_hPortMonitoringSendThreadClose;
	// ����֡��
	unsigned int m_uiRecFrameNum;
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


