#pragma once
#include "Parameter.h"
#include "SaveFile.h"
// CSocketSend ����Ŀ��

class CSocketSend : public CSocket
{
public:
	CSocketSend();
	virtual ~CSocketSend();
	virtual void OnReceive(int nErrorCode);
protected:
	// ���ݽ��ջ���
	unsigned char m_ucudp_buf[8][RcvFrameSize];
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
public:
	// ���ý���
	void OnReset(void);
	// ����PortMonitoringRecָ��
	CWnd* m_pwnd;
	// ����TabPortMonitoringָ��
	CWnd* m_pWndTab;
	// �����ļ����ָ��
	CSaveFile* m_pSaveFile;
	// �˿ڷַ�����
	BOOL m_bPortDistribution;
	// ��ֹ������ѭ���������޷���Ӧ��Ϣ
	unsigned short m_usADCLastDataPoint[GraphViewNum];
	void ProcessMessages(void);
};


