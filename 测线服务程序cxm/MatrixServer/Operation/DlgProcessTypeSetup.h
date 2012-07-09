#pragma once
// ���ݴ����������
#define PROCESS_IMPULSIVE		0		// ����
#define PROCESS_STACKIMPULSIVE	1		// �������
#define PROCESS_CORRELAFTER		2		// ���Ӻ����
#define PROCESS_CORRELBEFORE	3		// ����ǰ���
#define PROCESS_STACK			4		// �ɿ���Դ�������
// ��������ѡ��
#define PROCESS_STANDARD		0		// ��׼
#define PROCESS_ADVANCE			1		// �߼�

// CDlgProcessTypeSetup �Ի���

class CDlgProcessTypeSetup : public CBCGPDialog
{
	DECLARE_DYNAMIC(CDlgProcessTypeSetup)

public:
	CDlgProcessTypeSetup(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgProcessTypeSetup();

// �Ի�������
	enum { IDD = IDD_DIALOG_PROCESSSETUP };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	// ��������ѡ��
	int m_radioProcessSetup;
	afx_msg void OnBnClickedRadioStandard();
	afx_msg void OnBnClickedRadioAdvanced();
	// ��������ѡ��
	int m_cbindexProcessType;
	afx_msg void OnCbnSelchangeComboProcesstypeselect();
};
