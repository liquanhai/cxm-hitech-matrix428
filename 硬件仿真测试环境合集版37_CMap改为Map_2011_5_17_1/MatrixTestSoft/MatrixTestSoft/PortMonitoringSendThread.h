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
	unsigned char m_ucudp_buf[RcvBufNum][RcvFrameSize];
	// ���ݽ��ջ���������
	unsigned short m_usudp_count;
	// UDP����ָ֡��ƫ����
	unsigned int m_uiUdpCount;
	// UDP���ջ�����
	unsigned char m_ucUdpBuf[PortMonitoringBufSize];
public:
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
	unsigned int m_uiErrorCodeReturnCount[InstrumentNum];
	// ��¼Ӳ���豸�����ѯ�׸�Ӧ��֡
	unsigned char m_ucErrorCodeReturn[InstrumentNum][QueryErrorCodeNum];
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
	// ���ͷ�Socket
	CSocket m_SendSocket;
	// ���ն˿�
	int m_iRecPort;
	// ���Ͷ˿�
	int m_iSendPort;
	// Ŀ��IP��ַ
	CString m_csIP;
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
protected:
	// ����˿�����
	void OnAvoidIOBlock(SOCKET socket);
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
	// �˿ڼ��Ӵ�����
	void OnPortMonitoringProc(void);
	// ���ݴ���
	void OnProcess(int iCount);
};


