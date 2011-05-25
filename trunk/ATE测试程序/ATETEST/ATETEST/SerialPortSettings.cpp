// SerialPortSettings.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ATETEST.h"
#include "ATE.h"
#include "SerialPortSettings.h"


// CSerialPortSettings �Ի���

IMPLEMENT_DYNAMIC(CSerialPortSettings, CDialog)

CSerialPortSettings::CSerialPortSettings(CWnd* pParent /*=NULL*/)
	: CDialog(CSerialPortSettings::IDD, pParent)
{

}

CSerialPortSettings::~CSerialPortSettings()
{
}

void CSerialPortSettings::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_SERIALPORT_DEVICE, m_comboSerialPortDevice);
	DDX_Control(pDX, IDC_COMBO_SERIALPORT_COM, m_comboSerialPortCom);
	DDX_Control(pDX, IDC_COMBO_SERIALPORT_BAUD, m_comboSerialPortBaud);
	DDX_Control(pDX, IDC_COMBO_SERIALPORT_PARITY, m_comboSerialPortParity);
	DDX_Control(pDX, IDC_COMBO_SERIALPORT_BYTESIZE, m_comboSerialPortBytesize);
	DDX_Control(pDX, IDC_COMBO_SERIALPORT_STOPBITS, m_comboSerialPortStopbits);
}


BEGIN_MESSAGE_MAP(CSerialPortSettings, CDialog)
END_MESSAGE_MAP()


// CSerialPortSettings ��Ϣ�������
BOOL CSerialPortSettings::OnInitDialog()
{
	CDialog::OnInitDialog();

	//�豸ѡ������
	m_comboSerialPortDevice.SetWindowText( _T(Device0) );	//���ÿؼ���ʼ����ʾ
	m_comboSerialPortDevice.InsertString( 0, _T(Device0) );	//���������˵�ѡ��
	m_comboSerialPortDevice.InsertString( 1, _T(Device1) );
	
	//�˿�����
	m_comboSerialPortCom.SetWindowText( _T(COM0) );		//���ÿؼ���ʼ����ʾ
	m_comboSerialPortCom.InsertString( 0, _T(COM0) );	//���������˵�ѡ��
	m_comboSerialPortCom.InsertString( 1, _T(COM1) );
	m_comboSerialPortCom.InsertString( 2, _T(COM2) );
	m_comboSerialPortCom.InsertString( 3, _T(COM3) );
	m_comboSerialPortCom.InsertString( 4, _T(COM4) );
	m_comboSerialPortCom.InsertString( 5, _T(COM5) );
	m_comboSerialPortCom.InsertString( 6, _T(COM6) );
	m_comboSerialPortCom.InsertString( 7, _T(COM7) );
	m_comboSerialPortCom.InsertString( 8, _T(COM8) );

	//����������
	m_comboSerialPortBaud.SetWindowText( _T(BAUD0) );	//���ÿؼ���ʼ����ʾ
	m_comboSerialPortBaud.InsertString( 0, _T(BAUD0) );	//���������˵�ѡ��
	m_comboSerialPortBaud.InsertString( 1, _T(BAUD1) );
	m_comboSerialPortBaud.InsertString( 2, _T(BAUD2) );
	m_comboSerialPortBaud.InsertString( 3, _T(BAUD3) );
	m_comboSerialPortBaud.InsertString( 4, _T(BAUD4) );
	m_comboSerialPortBaud.InsertString( 5, _T(BAUD5) );
	m_comboSerialPortBaud.InsertString( 6, _T(BAUD6) );
	m_comboSerialPortBaud.InsertString( 7, _T(BAUD7) );
	m_comboSerialPortBaud.InsertString( 8, _T(BAUD8) );
	m_comboSerialPortBaud.InsertString( 9, _T(BAUD9) );
	m_comboSerialPortBaud.InsertString( 10, _T(BAUD10) );
	m_comboSerialPortBaud.InsertString( 11, _T(BAUD11) );

	//У��λ����
	m_comboSerialPortParity.SetWindowText( _T(PARITY0) );	//���ÿؼ���ʼ����ʾ
	m_comboSerialPortParity.InsertString( 0, _T(PARITY0) );	//���������˵�ѡ��
	m_comboSerialPortParity.InsertString( 1, _T(PARITY1) );
	m_comboSerialPortParity.InsertString( 2, _T(PARITY2) );

	//����λ����
	m_comboSerialPortBytesize.SetWindowText( _T(BYTESIZE0) );	//���ÿؼ���ʼ����ʾ
	m_comboSerialPortBytesize.InsertString( 0, _T(BYTESIZE0) );	//���������˵�ѡ��
	m_comboSerialPortBytesize.InsertString( 1, _T(BYTESIZE1) );
	m_comboSerialPortBytesize.InsertString( 2, _T(BYTESIZE2) );

	//ֹͣλ����
	m_comboSerialPortStopbits.SetWindowText( _T(STOPBITS0) );	//���ÿؼ���ʼ����ʾ
	m_comboSerialPortStopbits.InsertString( 0, _T(STOPBITS0) );	//���������˵�ѡ��
	m_comboSerialPortStopbits.InsertString( 1, _T(STOPBITS1) );

	return TRUE;
}