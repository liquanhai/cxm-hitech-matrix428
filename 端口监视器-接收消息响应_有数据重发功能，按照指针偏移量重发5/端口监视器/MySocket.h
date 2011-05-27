#pragma once

// CMySocket ����Ŀ��
class CPortMonitoringDlg;
class CMySocket : public CSocket
{
public:
	CMySocket(CPortMonitoringDlg* pTDoc);
	virtual ~CMySocket();
public:
	virtual void OnReceive(int nErrorCode);

protected:
	unsigned char udp_buf[8][1024];
	unsigned char udp_count;
	CPortMonitoringDlg* m_pTDoc;
	// UDP����ָ֡��ƫ����
	unsigned int m_uiUdpCount;
	// UDP���ջ�����
	unsigned char m_ucUdpBuf[8192];
};


