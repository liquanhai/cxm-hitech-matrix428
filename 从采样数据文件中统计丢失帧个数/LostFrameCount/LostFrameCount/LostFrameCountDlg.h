// LostFrameCountDlg.h : ͷ�ļ�
//

#pragma once


// CLostFrameCountDlg �Ի���
class CLostFrameCountDlg : public CDialog
{
// ����
public:
	CLostFrameCountDlg(CWnd* pParent = NULL);	// ��׼���캯��
	virtual ~CLostFrameCountDlg();

// �Ի�������
	enum { IDD = IDD_LOSTFRAMECOUNT_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonCallostdataframe();
	// �ļ���ʼ���
	UINT m_uiFileStartNb;
	// �ļ��������
	UINT m_uiFileEndNb;
	// �����豸ÿ�ļ��洢���ݸ���
	UINT m_uiSaveADCDataFrameNum;
	// ���豸����
	UINT m_uiInstrumentTotalNum;
	// �����豸����
	UINT m_uiInstrumentSampleNum;
	// ����֡�Ĵ�С
	UINT m_uiFrameSize;
	afx_msg void OnBnClickedButtonFilepath();
	// �ļ���·��
	CString m_csFilePath;
	// ���㶪ʧ����֡����
	void OnCalLostDataFrameNum(void);
	// ��ʧ֡����ָ��
	unsigned int * m_uipLostFrameCount;
	// �������һ������������ļ�
	void OnCalLastFile(unsigned int uiLastFileNb);
	// �����Զ�������������ļ�
	void OnCalFinishFile(unsigned int uiFinishFileNb);
};
