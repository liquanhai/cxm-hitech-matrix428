#pragma once
#include "Parameter.h"
#include "SaveFile.h"

// CSocketRec ����Ŀ��

class CSocketRec : public CSocket
{
public:
	CSocketRec();
	virtual ~CSocketRec();
	virtual void OnReceive(int nErrorCode);
protected:
	// ���ݽ��ջ���
	unsigned char m_ucudp_buf[8][SndFrameSize];
	// ���ݽ��ջ���������
	unsigned short m_usudp_count;
public:
	// ���ն˿�
	int m_iRecPort;
	// ���Ͷ˿�
	int m_iSendPort;
	// Ŀ��IP��ַ
	CString m_csIP;
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


