#pragma once
#include "afxwin.h"
#include "mscomm1.h"
#include "UartToUdpSocket.h"
#include "Parameter.h"

//__________________���ڶ˿ڶ���__________________
#define COM0 "COM1"
#define COM1 "COM2"
#define COM2 "COM3"
#define COM3 "COM4"
#define COM4 "COM5"
#define COM5 "COM6"
#define COM6 "COM7"
#define COM7 "COM8"
#define COM8 "COM9"
#define COM16	"COM17"

//__________________���ڲ����ʶ���________________
#define BAUD0 "300"
#define BAUD1 "600"
#define BAUD2 "1200"
#define BAUD3 "2400"
#define BAUD4 "4800"
#define BAUD5 "9600"
#define BAUD6 "19200"
#define BAUD7 "38400"
#define BAUD8 "43000"
#define BAUD9 "56000"
#define BAUD10 "57600"
#define BAUD11 "115200"

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
protected:
	// �ؼ�IDC_COMBO_SERIALPORT_COM�Ŀ��Ʊ���
	CComboBox m_comboSerialPortCom;
	// �ؼ�IDC_COMBO_SERIALPORT_BAUD�Ŀ��Ʊ���
	CComboBox m_comboSerialPortBaud;
	// ����ͨѶ�ؼ��Ŀ��Ʊ���
//	CMscomm1 m_ctrlMSComm1;
	// �õ���ǰѡ��Ĵ��ں�
	int OnGetSerialPortCom(void);
	// �õ���ǰѡ��Ĳ�����
	int OnGetSerialPortBaud(void);
	// ����תUDPͨѶSocket
	CUartToUdpSocket m_socketUartToUdp;
	// �������ݽ�������
	unsigned char m_ucUartBuf[8][RcvFrameSize];
	// ���ڽ��ջ���������
	unsigned short m_usUartBufCount;
	// ���ڳɹ��������ݼ���
	unsigned int m_uiUartCount;
	// ��UDP��������
	void OnSendFromUDP(unsigned char* TXDATA, unsigned int uiCount);
public:
	// ��ʼ������
	void OnInit(void);
	afx_msg void OnBnClickedButtonSerialportOpen();
	afx_msg void OnBnClickedButtonSerialportClose();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
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
	// ��ֹ������ѭ���������޷���Ӧ��Ϣ
	void ProcessMessages(void);
};
