// GPSAnalysisDlg.h : ͷ�ļ�
//

#pragma once
#include "afxwin.h"
#include "RecThread.h"


// CGPSAnalysisDlg �Ի���
class CGPSAnalysisDlg : public CDialog
{
// ����
public:
	CGPSAnalysisDlg(CWnd* pParent = NULL);	// ��׼���캯��
// �Ի�������
	enum { IDD = IDD_GPSANALYSIS_DIALOG };

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
	// ֡��ʽѡ��
	CComboBox m_ctrlcomboFrameSelect;
	// ����GPS����֡����
	CEdit m_editSendFrame;
	// ����֡����
	byte m_pSendFrameData[256]; 
	// ���������߳�
	CRecThread m_RecThread;
public:
	afx_msg void OnCbnSelchangeComboFrameselect();
	afx_msg void OnBnClickedButtonSendgpsframe();
	// ����֡ͷ
	void MakeSendFrame(char* buf, int ilength);
	afx_msg void OnClose();
};
