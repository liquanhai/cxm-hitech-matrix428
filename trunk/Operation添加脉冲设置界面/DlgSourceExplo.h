#pragma once
#include "afxwin.h"
#include "SetupGridCtrl.h"
#include "..\common\OperaStruct.h"
#include "ShotSources.h"
// CDlgSourceExplo �Ի���

class CDlgSourceExplo : public CBCGPDialog
{
	DECLARE_DYNAMIC(CDlgSourceExplo)

public:
	CDlgSourceExplo(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgSourceExplo();

// �Ի�������
	enum { IDD = IDD_SOURCEEXPLODLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CStatic				m_ctrlGridLocation;
	CStatic				m_ctrlEditGridLocation;
	CGridCtrlList		m_wndListGrid;
	CGridCtrlEdit		m_wndEditGrid;

private:
	void	AppendRecord(CShotSource*	pShotSource);
	bool	ApplyRecord(int nRow,CShotSource*	pShotSource);
protected:
	afx_msg LRESULT OnGridItemClick(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnGridItemDblClk(WPARAM wParam, LPARAM lParam);	
	afx_msg void OnBnClickedBtnadd();
	afx_msg void OnBnClickedBtndelete();
	afx_msg void OnBnClickedBtnchange();
public:
	virtual BOOL OnInitDialog();
	void	Load(void);
	void	Apply(CShotSources *pOldSources,CShotSources *pNewSources);
	

};
