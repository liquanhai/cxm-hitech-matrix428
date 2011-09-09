#pragma once


#include "..\common\OperaStruct.h"
#include "DlgProcessImpulsive.h"
#include "SetupGridCtrl.h"
#include "ProcessTypes.h"
// CDlgProcessType �Ի���

class CDlgProcessType : public CBCGPDialog
{
	DECLARE_DYNAMIC(CDlgProcessType)

public:
	CDlgProcessType(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgProcessType();

// �Ի�������
	enum { IDD = IDD_PROCESSTYPEDLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()

public:
	/** ��׼���Ǹ߼� */
	int							m_ProcessSetup;
	/** �Ի����λ�� */
	CStatic						m_wndDlgLocation;
	/** ��������ѡ�� */
	CBCGPComboBox				m_ctrlProcessType;
	/** ���崦�����ͶԻ��� */
	CDlgProcessImpulsive		m_dlgImpulsive;
	
	CStatic						m_ctrlRefraction;
	CStatic						m_ctrlEditGridLocation;
	CStatic						m_ctrlListGridLocation;

	CGridCtrlList				m_wndListGrid;
	CGridCtrlEdit				m_wndEditGrid;
	
	// ��ը�������Ĳɼ�վSN
	DWORD m_dwFDUSN;
	// ��������
	DWORD m_dwRecordLen;
	// TB �����ı���ʶ��ʾ��
	CStatic m_ctrlTBWindow;
	// TB ���ڱ༭��
	CEdit m_EditTbWindow;
	// TB ����
	DWORD m_dwTBWindow;	
	// ������ʱ
	DWORD m_dwRefractionDelay;

private:
	// �����ڸöԻ����еĴ�������
	CProcessTypes		m_AllProcesses;
	// װ�ش�����������
	void    ShowProcessDialog(int nProcessType);
	void	AppendRecord(CProcessType* pProcessType);
	void	LoadProcess(CProcessType* pProcess);
	void	LoadImpulsive(CProcessImpulsive* pProcess);
	//void	LoadStackImpulsive(CProcessStackImpulsive* pProcess);

	// ���洦����������
	void	ApplyImpulsive(CProcessImpulsive* pProcess);
	CProcessType*	ApplyRecord(int nListRow);	
protected:
	afx_msg LRESULT OnGridItemClick(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnGridItemDblClk(WPARAM wParam, LPARAM lParam);	
public:
	virtual BOOL OnInitDialog();
	void	Load(void);
	
	afx_msg void OnBnClickedBtnadd();
	afx_msg void OnBnClickedBtnchange();
	afx_msg void OnBnClickedBtndelete();
	afx_msg void OnBnClickedBtnapply();
	afx_msg void OnBnClickedBtnreset();
};
