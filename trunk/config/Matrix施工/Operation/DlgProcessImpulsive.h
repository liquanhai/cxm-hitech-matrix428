#pragma once


// CDlgProcessImpulsive �Ի���
#include "SetupGridCtrl.h"
#include "..\common\OperaStruct.h"

class CDlgProcessImpulsive : public CBCGPDialog
{
	DECLARE_DYNAMIC(CDlgProcessImpulsive)

public:
	CDlgProcessImpulsive(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgProcessImpulsive();

// �Ի�������
	enum { IDD = IDD_PROCESSIMPULSIVEDLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()

public:
	/** �������� */
	CStatic				m_ctrlEditGridLocation;
	/** �������� */
	CStatic				m_ctrlListGridLocation;
	/** �б��������ʾ���и����� */
	CGridCtrlList		m_wndListGrid;
	/** �༭һ����������¼ */
	CGridCtrlEdit		m_wndEditGrid;

private:
	CProcessImpulsive*		m_pProcess;
	void	AppendRecord(AUXICHANNEL* pAuxiChannel);
	bool	ApplyRecord(int nRow,AUXICHANNEL* pAuxiChannel);
protected:
	afx_msg LRESULT OnGridItemClick(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnGridItemDblClk(WPARAM wParam, LPARAM lParam);	
	afx_msg void OnBnClickedBtnadd();
	afx_msg void OnBnClickedBtnchange();
	afx_msg void OnBnClickedBtndelete();
public:
	virtual BOOL OnInitDialog();
	void	Load(CProcessImpulsive* pProcess);
    void    Apply(CProcessImpulsive* pProcess);
	
};
