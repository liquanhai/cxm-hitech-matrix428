#pragma once
#include "afxsock.h"
#include "Parameter.h"
#include "SaveFile.h"
// CPortMonitoringThreadSend

class CPortMonitoringThreadSend : public CWinThread
{
	DECLARE_DYNCREATE(CPortMonitoringThreadSend)

public:
	CPortMonitoringThreadSend();           // ��̬������ʹ�õ��ܱ����Ĺ��캯��
	virtual ~CPortMonitoringThreadSend();

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
	// �˿ڼ��ӷ��Ͷ˿�Socket
	CSocket m_hSocketSend;
public:
	// �߳̽����¼�
	HANDLE m_hThreadSendClose;
protected:
	// �̹߳رձ�־λ
	bool m_bClose;
	// ���ݽ��ջ���
	unsigned char m_ucudp_buf[8][256];
	// ���ݽ��ջ���������
	unsigned short m_usudp_count;
public:
	// ���ն˿�
	int m_iRecPort;
	// ���Ͷ˿�
	int m_iSendPort;
	// Ŀ��IP��ַ
	CString m_csIP;
protected:
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
	// ADC���ݲɼ�֡����
	unsigned int m_uiADCDataRecNum;
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
	// ��ʾADC��������֡������IP��ַ��֡�����Ͳ�������֡����
	CString m_csADCDataRecShow;
	// ����֡��
	unsigned int m_uiRecFrameNum;
	// ADC���ݲɼ���һ֡������ָ��ƫ����
	unsigned short m_usADCLastDataPoint;
public:
	// ��
	void OnOpen(void);
	// ֹͣ
	void OnStop(void);
	// ���ý���
	void OnReset(void);
	// ����PortMonitoringRecָ��
	CWnd* m_pwnd;
	// ����TabPortMonitoringָ��
	CWnd* m_pWndTab;
	// �����ļ����ָ��
	CSaveFile* m_pSaveFile;
};


