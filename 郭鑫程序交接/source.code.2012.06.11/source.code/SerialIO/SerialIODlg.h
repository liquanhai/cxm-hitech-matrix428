// SerialIODlg.h : ͷ�ļ�
//

#pragma once
#include "afxwin.h"

typedef struct __tagBLASTER_PROTOCOL
{
	char sp_[6];
	char sl_[8];
	char sn_[8];
	char si_;
	char seq_[3];
}BLASTER_PROTOCOL, *BLASTER_PROTOCOL_PTR;

// CSerialIODlg �Ի���
class CSerialIODlg : public CDialog
{
// ����
public:
	CSerialIODlg(CWnd* pParent = NULL);	// ��׼���캯��

	// �Ի�������
	enum { IDD = IDD_SERIALIO_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��

// ʵ��
protected:
	void output_log(CString const& log);
	void com_output(CString const& result_text);
	void parse_and_output_info(CString const& info);
	void echo_status(CString const& info);

protected:
	HICON m_hIcon;
	bool be_startup_;
	HANDLE com_port_; 
	CString recv_info_;


	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	DECLARE_MESSAGE_MAP()
public:
	CEdit output_edit_;
	CComboBox combobox_;
	afx_msg void OnBnClickedOk();
	CButton button_;
	CButton gps_check_;
};
