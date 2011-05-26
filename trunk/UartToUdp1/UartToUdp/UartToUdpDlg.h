// UartToUdpDlg.h : ͷ�ļ�
//

#pragma once
#include "afxwin.h"
#include "Parameter.h"
#include "CMSComm.h"
// CUartToUdpDlg �Ի���
#define UDPPortNb	18
class CUDPSocket;
class CUartToUdpDlg : public CDialog
{
// ����
public:
	CUartToUdpDlg(CWnd* pParent = NULL);	// ��׼���캯��
	virtual ~CUartToUdpDlg();


// �Ի�������
	enum { IDD = IDD_UARTTOUDP_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	// �ؼ�IDC_COMBO_SERIALPORT_BAUD�Ŀ��Ʊ���
	CComboBox m_comboSerialPortBaud;
	// �ؼ�IDC_COMBO_SERIALPORT_COM�Ŀ��Ʊ���
	CComboBox m_comboSerialPortCom;
	// �õ���ǰѡ��Ĵ��ں�
	int OnGetSerialPortCom(void);
	// �õ���ǰѡ��Ĳ�����
	int OnGetSerialPortBaud(void);
	// ����ͨѶ�ؼ��Ŀ��Ʊ���
	CMSComm m_ctrlMSComm1;
	afx_msg void OnBnClickedButtonOpenserialport();
	DECLARE_EVENTSINK_MAP()
	void OnCommMscomm1();
	
public:
	unsigned short *		m_uiPortNb;
	CUDPSocket* m_pUDPSocket[UDPPortNb];

	unsigned char uart_buf[8][1024];
	unsigned char uart_count;

	// �Ӵ��ڷ�������
	void OnSendFromSerialPort(unsigned char* TXDATA, unsigned int uiCount);
	// ��UDP��������
	void OnSendFromUDP(unsigned char* TXDATA, unsigned int uiCount);
};
