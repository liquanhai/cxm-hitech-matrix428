#pragma once


// CTabEepromUpdata �Ի���

class CTabEepromUpdata : public CDialog
{
	DECLARE_DYNAMIC(CTabEepromUpdata)

public:
	CTabEepromUpdata(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CTabEepromUpdata();

// �Ի�������
	enum { IDD = IDD_DIALOG_EEPROM };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonUpdataInstrumentlist();
	afx_msg void OnBnClickedButtonMoverightOne();
	afx_msg void OnBnClickedButtonMoverightAll();
	afx_msg void OnBnClickedButtonMoveleftOne();
	afx_msg void OnBnClickedButtonMoveleftAll();
	afx_msg void OnBnClickedButtonReset();
};
