#pragma once
#include "afxwin.h"


// CSerialPortSettings �Ի���

class CSerialPortSettings : public CDialog
{
	DECLARE_DYNAMIC(CSerialPortSettings)

public:
	CSerialPortSettings(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CSerialPortSettings();

// �Ի�������
	enum { IDD = IDD_DIALOG_SERIALPORT_SETTINGS };

protected:
	virtual BOOL OnInitDialog();
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	// �ؼ�IDC_COMBO_SERIALPORT_DEVICE�ı���
	CComboBox m_comboSerialPortDevice;

	// �ؼ�IDC_COMBO_SERIALPORT_COM�ı���
	CComboBox m_comboSerialPortCom;

	// �ؼ�IDC_COMBO_SERIALPORT_BAUD�ı���
	CComboBox m_comboSerialPortBaud;
	// // �ؼ�IDC_COMBO_SERIALPORT_PARITY�ı���
	CComboBox m_comboSerialPortParity;
	// // �ؼ�IDC_COMBO_SERIALPORT_BYTESIZE�ı���
	CComboBox m_comboSerialPortBytesize;
	// // �ؼ�IDC_COMBO_SERIALPORT_STOPBITS�ı���
	CComboBox m_comboSerialPortStopbits;
};
