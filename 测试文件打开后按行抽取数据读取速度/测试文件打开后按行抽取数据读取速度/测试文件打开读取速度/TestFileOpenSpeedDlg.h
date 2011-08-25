// TestFileOpenSpeedDlg.h : ͷ�ļ�
//

#pragma once


// CTestFileOpenSpeedDlg �Ի���
class CTestFileOpenSpeedDlg : public CDialog
{
// ����
public:
	CTestFileOpenSpeedDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_MY_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;
	CFile file;
	wchar_t* m_pbufRead;
	unsigned int m_uiSamplingRate;
	unsigned int m_uiFindLineCount;
	unsigned int m_uiBufSize;
	ULONGLONG m_ullPointer;
	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonTest();
	// ���ļ���ȡ����
	void OpenFile(CString csOpenFilePath);
};
