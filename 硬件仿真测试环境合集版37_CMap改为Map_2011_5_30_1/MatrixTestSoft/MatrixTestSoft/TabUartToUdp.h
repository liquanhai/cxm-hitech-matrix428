#pragma once
#include "afxwin.h"
#include "mscomm1.h"
#include "Parameter.h"
#include "LogFile.h"

// CTabUartToUdp �Ի���

class CTabUartToUdp : public CDialog
{
	DECLARE_DYNAMIC(CTabUartToUdp)

public:
	CTabUartToUdp(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CTabUartToUdp();

// �Ի�������
	enum { IDD = IDD_DIALOG_UARTTOUDP };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
private:
	// �ؼ�IDC_COMBO_SERIALPORT_COM�Ŀ��Ʊ���
	CComboBox m_comboSerialPortCom;
	// �ؼ�IDC_COMBO_SERIALPORT_BAUD�Ŀ��Ʊ���
	CComboBox m_comboSerialPortBaud;
	// �������ݽ�������
	unsigned char m_ucUartBuf[RcvBufNum][RcvFrameSize];
	// ���ڽ��ջ���������
	unsigned short m_usUartBufCount;
	// ���ڳɹ��������ݼ���
	unsigned int m_uiUartCount;
	// Socket�׽���
	sockaddr_in m_RecvAddr, m_SendToAddr;
	SOCKET m_UdpSocket;
	// UDP���ջ���������
	unsigned char m_ucUdpBuf[RcvBufNum][UartToUdpRcvSize];
	unsigned short m_usUdpBufCount;
public:
	// 	// ���ڽ����̺߳���������־λ
	// 	BOOL m_bUartThreadclose;
	// ����ͨѶ�ؼ��Ŀ��Ʊ���
	CMscomm1 m_ctrlMSComm1;
	// ѡ�񴮿ڶ˿ڵĸ�ѡ�����
	unsigned int m_uiSerialPortComCurSel;
	// ѡ�񴮿ڲ����ʵĸ�ѡ�����
	unsigned int m_uiSerialPortBaudCurSel;
	// UDP����Ŀ��˿�
	unsigned int m_uiSendPort;
	// UDP���ն˿�
	unsigned int m_uiRecPort;
	// ��������IP��ַ
	CString m_csIPAddress;
	// ��־��ָ��
	CLogFile* m_pLogFile;
private:
	// �õ���ǰѡ��Ĵ��ں�
	int OnGetSerialPortCom(void);
	// �õ���ǰѡ��Ĳ�����
	int OnGetSerialPortBaud(void);
	// ��UDP��������
	void OnSendFromUDP(unsigned char* TXDATA, unsigned int uiCount);
	// ��ֹ������ѭ���������޷���Ӧ��Ϣ
	void ProcessMessages(void);
	// ����˿�����
	void OnAvoidIOBlock(SOCKET socket);
	// �رմ���
	void OnCloseCom(void);
	// �ر�UDP�˿�
	void OnCloseUDP(void);
	// �Ӵ��ڷ�������
	void OnSendFromSerialPort(unsigned char* TXDATA, unsigned int uiCount);
	// ����UDP��SOCKET�׽��ֲ�����
	void OnCreateUDPSocket(void);
public:
	// ��ʼ������
	void OnInit(void);
	// ʹ�ܿؼ�
	void ControlEnable(void);
	// ���ÿؼ�
	void ControlDisable(void);
	// �򿪴���
	void OnOpenCom(void);
	// �رմ���
//	void OnCloseCom(void);
	// ���ڽ�������
//	void OnUartReceiveData(unsigned char* lpbuffer, unsigned int dwBytes);
	// �ر�
	void OnClose(void);
	afx_msg void OnBnClickedButtonSerialportOpen();
	afx_msg void OnBnClickedButtonSerialportClose();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg LRESULT OnSocket(WPARAM wParam, LPARAM lParam);
};
